#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "model.h"
#include "global.h"
#include "card_file.h"
#include "card_service.h"
#include "billing_file.h"
#include "billing_service.h"
#include "service.h"
#include "money_file.h"

// 函数名:addCardInfo
// 功能:添加卡信息
// 参数:card 卡信息结构体
// 返回值:TRUE 保存成功；FALSE 保存失败
int addCardInfo(Card card)
{
	// 将卡信息保存到文件中
	if (TRUE == saveCard(&card, CARDPATH))
	{
		return TRUE;
	}
	return FALSE;
}

// 函数名:queryCardInfo
// 功能:模糊查询卡信息
// 参数:pName:指向用户输入的要查询的卡号；pIndex:指向查询到的卡信息数变量
// 返回值:指向卡信息结构体的指针
Card *queryCardInfo(const char *pName)
{
	Card *pCard = NULL;
	pCard = queryCard(pName);
	return pCard;
}

// 函数名:queryCardsInfo
// 功能:模糊查询卡信息
// 参数:pName:指向用户输入的要查询的卡号
//				pIndex:指向查询到的卡信息数变量
// 返回值:指向卡信息结构体指针
Card *queryCardsInfo(const char *pName, int *pIndex)
{
	Card *pCard = NULL;
	pCard = queryCards(pName, pIndex);
	return pCard;
}

// 函数名:doLogon
// 功能:从文件中读取卡信息到链表，在链表中查询卡信息,并获取其在链表中的位置
// 参数:pName:上机卡号；pPwd:上机密码 pInfo:指向上机结构体
// 返回值:TRUE :上机成功 FALSE:上机失败
int doLogon(const char *pName, const char *pPwd, LogonInfo *pInfo)
{
	Card *pCard = NULL;
	int nIndex = 0;	 // 卡信息在链表中的索引，用于更新卡信息
	Billing billing; // 计费信息

	// 根据卡号和密码，从链表中获取卡信息和卡信息在链表中的索引
	pCard = checkCard(pName, pPwd, &nIndex);

	// 如果卡信息为空，表示没有该卡信息，上机失败
	if (pCard == NULL)
	{
		return FALSE;
	}

	switch (pCard->nStatus)
	{
	case 1:
	{
		// 如果卡状态为1，表示该卡不能上机
		printf("该卡正在上机！\n");
		return UNUSE;
		break;
	}
	case 2:
	{
		// 卡状态为2，表示该卡已经注销
		printf("该卡已经注销！\n");
		return UNUSE;
		break;
	}
	case 3:
	{
		// 如果卡状态为3，表示卡已经失效
		printf("该卡已经注销！\n");
		return UNUSE;
		break;
	}
	default:
	{
		break;
	}
	}
	/*//如果卡状态不为零，表示该卡不能上机
	if (pCard->nStatus == 1)
	{
		printf("该卡正在上机！\n");
		return UNUSE;
	}
	//卡状态为2，表示该卡已经注销
	if (pCard->nStatus == 2)
	{
		printf("该卡已经注销！\n");
		return UNUSE;
	}
	//如果卡状态为3，表示卡已经失效
	if (pCard->nStatus == 3)
	{
		printf("该卡已经失效！\n");
		return UNUSE;
	}*/
	// 余额大于零才能上机
	if (pCard->fBalance <= 0)
	{
		printf("余额不足，请充值后再上机！\n");
		return ENOUGHMONEY;
	}

	// 如果可以上机，更新卡信息
	pCard->nStatus = 1;			   // 状态为正在使用
	pCard->nUseCount++;			   // 使用次数加1
	pCard->tLastTime = time(NULL); // 更新最后使用时间为当前时间

	// 更新文件中的卡信息
	if (FALSE == updateCard(pCard, CARDPATH, nIndex))
	{
		// 文件更新失败返回，更新成功才继续添加消费记录
		return FALSE;
	}
	// 添加消费记录
	strcpy(billing.aCardName, pName); // 上机卡号
	billing.tStart = time(NULL);	  // 上机时间
	billing.tEnd = 0;				  // 下机时间
	billing.nStatus = 0;			  // 消费状态
	billing.fAmount = 0;			  // 消费金额
	billing.nDel = 0;				  // 删除标识

	// 先将计费信息保存到文件中
	if (TRUE == saveBilling(&billing, BILLINGPATH))
	{
		// 组装上机信息
		strcpy(pInfo->aCardName, pName);
		pInfo->fBalance = pCard->fBalance;
		pInfo->tLogon = billing.tStart;
		return TRUE;
	}
	return FALSE;
}

// 函数名:releaseList
// 功能:退出应用程序，释放链表内存
// 参数:void
// 返回值:void
void releaseList()
{
	releaseCardList();	  // 释放卡信息链表内存
	releaseBillingList(); // 释放计费信息链表内存
}

// 函数名:doSettle
// 功能:进行下机操作
// 参数:pName:下机卡号；pPwd:下机密码；pInfo:指向下机信息结构体
// 返回值:下机信息值，不同情况下输出不同信息
int doSettle(const char *pName, const char *pPwd, SettleInfo *pInfo)
{
	Card *pCard = NULL;
	Billing *pBilling = NULL;
	int nIndex = 0;		   // 卡信息在链表中的索引号
	int nPosition = 0;	   // 计费信息在链表中的索引号
	double dbAmount = 0.0; // 消费金额
	float fBalance = 0.0;  // 余额

	// 查询上机卡
	pCard = checkCard(pName, pPwd, &nIndex);

	// 如果为空，表示没有该卡信息返回FALSE
	if (pCard == NULL)
	{
		printf("无该卡信息，请重新输入！\n");
		return FALSE;
	}
	switch (pCard->nStatus)
	{
	case 0:
	{
		// 如果卡状态为0，表示该卡未上机不能下机
		printf("该卡未上上机！\n");
		return UNUSE;
		break;
	}
	case 2:
	{
		// 卡状态为2，表示该卡已经注销
		printf("该卡已经注销！\n");
		return UNUSE;
		break;
	}
	case 3:
	{
		// 如果卡状态为3，表示卡已经失效
		printf("该卡已经注销！\n");
		return UNUSE;
		break;
	}
	default:
	{
		break;
	}
	}
	/*//判断该卡是否正在上机，只有正在上机的卡才能进行下机操作
	if (pCard->nStatus == 0)
	{
		printf("该卡未上机！\n");
		return UNUSE;
	}
	if(pCard->nStatus == 2)
	{
		printf("该卡已经注销！\n");
		return UNUSE;
	}
	if (pCard->nStatus == 3)
	{
		printf("该卡已经失效！\n");
		return UNUSE;
	}*/

	// 根据卡号查询计费信息
	pBilling = queryBilling(pName, &nPosition);

	// 如果查询计费信息为空，表示下机失败
	if (pBilling == NULL)
	{
		printf("无该卡信息，请重新输入！\n");
		return FALSE;
	}
	// 计算消费金额
	dbAmount = getAmount(pBilling->tStart);

	// 如果金额小于消费金额，则不能进行下机
	fBalance = pCard->fBalance - (float)dbAmount;
	if (fBalance < 0)
	{
		return ENOUGHMONEY;
	}

	// 更新卡信息
	pCard->fBalance = fBalance;	   // 余额
	pCard->nStatus = 0;			   // 状态
	pCard->tLastTime = time(NULL); // 上次使用时间

	// 更新文件中的卡信息
	if (FALSE == updateCard(pCard, CARDPATH, nIndex))
	{
		return FALSE;
	}
	// 更新计费信息
	pBilling->fAmount = (float)dbAmount; // 消费信息
	pBilling->nStatus = 1;				 // 状态已结算
	pBilling->tEnd = time(NULL);		 // 下机时间

	// 更新文件中的计费信息
	if (FALSE == updateBilling(pBilling, BILLINGPATH, nPosition))
	{
		return FALSE;
	}
	// 组装下机信息
	strcpy(pInfo->aCardName, pName);  // 卡号
	pInfo->fAmount = (float)dbAmount; // 消费金额
	pInfo->fBalance = fBalance;		  // 余额
	pInfo->tStart = pBilling->tStart; // 上机时间
	pInfo->tEnd = time(NULL);		  // 下机时间

	return TRUE;
}

// 函数名:getAmount
// 功能:根据上机时间计算消费金额
// 参数:上机时间
// 返回值:消费金额
double getAmount(time_t tStart)
{
	double dbAmount = 0;	  // 消费金额
	int nCount = 0;			  // 上机的时间单元数，每个单元15分钟
	int nSec = 0;			  // 消费时间（单位：秒）
	int nMinutes = 0;		  // 消费时间（单位：分钟）
	time_t tEnd = time(NULL); // 结算时间为当前时间

	// 计算消费时长
	nSec = (int)(tEnd - tStart);
	nMinutes = nSec / 60;
	// 计算消费的时间单元数
	if (nMinutes % UNIT == 0)
	{
		nCount = nMinutes / UNIT; // 整除
	}
	else
	{
		nCount = nMinutes / UNIT + 1; // 不整除
	}
	// 计算消费金额
	dbAmount = nCount * CHARGE;
	return dbAmount;
}

// 函数名:doAddMoney
// 功能:进行充值操作
// 参数:pName:充值卡的卡号；pPwd:充值卡的密码；pMoneyInfo:充值信息
// 返回值:充值结果，TRUE:充值成功;FALSE：充值失败
int doAddMoney(const char *pName, const char *pPwd, MoneyInfo *pMoneyInfo)
{
	Card *pCard = NULL;
	int nIndex = 0; // 卡信息在链表中的索引号
	Money sMoney;
	// 查询卡充值
	pCard = checkCard(pName, pPwd, &nIndex);

	// 如果卡信息为空，表示没有该卡信息，充值失败
	if (pCard == NULL)
	{
		printf("无该卡信息，不能充值！\n");
		return FALSE;
	}
	// 判断该卡是否未使用或正在上机，只有未使用和正在上机的卡才能进行充值操作
	if (pCard->nStatus != 0 && pCard->nStatus != 1)
	{
		return FALSE;
	}
	// 如果可以充值，更新卡信息
	pCard->fBalance += pMoneyInfo->fMoney;
	pCard->fTotalUse += pMoneyInfo->fMoney;

	// 更新文件中的卡信息文件
	if (FALSE == updateCard(pCard, CARDPATH, nIndex))
	{
		return FALSE;
	}
	// 组装充值信息
	strcpy(sMoney.aCardName, pCard->aName);
	sMoney.tTime = time(NULL);
	sMoney.nStatus = 0;
	sMoney.fMoney = pMoneyInfo->fMoney;
	sMoney.nDel = 0;

	// 将充值记录保存到文件中
	if (TRUE == saveMoney(&sMoney, MONEYPATH))
	{
		// 组装界面显示的充值信息
		strcpy(pMoneyInfo->aCardName, sMoney.aCardName);
		pMoneyInfo->fBalance = pCard->fBalance;

		return TRUE;
	}
	return FALSE;
}

// 函数名:doRefundMoney
// 功能:进行退费操作
// 参数:pName:退费卡的卡号；pPwd:退费卡的密码；pMoneyInfo:充值退费信息结构体
// 返回值:充值结果，TRUE:充值成功;FALSE：充值失败
int doRefundMoney(const char *pName, const char *pPwd, MoneyInfo *pMoneyInfo)
{
	Card *pCard = NULL;
	int nIndex = 0;		  // 卡信息在链表中的索引号
	float fBalance = 0.0; // 卡的余额
	Money sMoney;

	// 查询退费卡
	pCard = checkCard(pName, pPwd, &nIndex);

	// 如果为空，表示没有该卡信息，返回FALSE
	if (pCard == NULL)
	{
		printf("无该卡信息，不能退费！\n");
		return FALSE;
	}

	// 判断该卡是否未使用，只有未使用的卡才能进行退费操作
	if (pCard->nStatus != 0)
	{
		return UNUSE;
	}

	// 如果余额小于等于零，则不能进行退费
	fBalance = pCard->fBalance;
	if (fBalance <= 0)
	{
		return ENOUGHMONEY;
	}

	// 更新卡信息
	pCard->fBalance = 0;		  // 余额
	pCard->fTotalUse -= fBalance; // 累计金额

	// 更新文件中的卡信息
	if (FALSE == updateCard(pCard, CARDPATH, nIndex))
	{
		return FALSE;
	}

	// 组合退费信息
	strcpy(sMoney.aCardName, pCard->aName);
	sMoney.tTime = time(NULL);
	sMoney.nStatus = 1;
	sMoney.fMoney = fBalance;
	sMoney.nDel = 0;

	// 更新文件中的充值退费信息
	if (TRUE == saveMoney(&sMoney, MONEYPATH))
	{
		// 组装退费信息
		strcpy(pMoneyInfo->aCardName, sMoney.aCardName);
		pMoneyInfo->fMoney = sMoney.fMoney;
		pMoneyInfo->fBalance = pCard->fBalance;

		return TRUE;
	}
	return FALSE;
}

// 函数名:annulCard
// 功能:注销卡
// 参数:pCard
// 返回值:TRUE 注销成功；FALSE 注销失败
int annulCard(Card *pCard)
{
	Card *pCurCard = NULL;
	int nIndex = -1; // 卡信息在链表中的索引

	if (pCard == NULL)
	{
		return FALSE;
	}
	// 根据卡号和密码，查询卡信息
	pCurCard = checkCard(pCard->aName, pCard->aPwd, &nIndex);

	if (pCurCard == NULL)
	{
		return FALSE;
	}
	// 只有未上机的卡才能注销
	if (pCurCard->nStatus != 0)
	{
		return FALSE;
	}
	// 保存注销卡的余额
	pCard->fBalance = pCurCard->fBalance;

	// 更新注销卡信息
	pCurCard->nStatus = 2;			  // 状态未已注销
	pCurCard->nDel = 1;				  // 删除标识为已删除
	pCurCard->fBalance = 0;			  // 卡余额为0
	pCurCard->tLastTime = time(NULL); // 最后使用时间为当前时间

	// 更新卡在文件中的信息
	if (FALSE == updateCard(pCurCard, CARDPATH, nIndex))
	{
		return FALSE;
	}
	return TRUE;
}