#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

#include"menu.h"
#include"model.h"
#include"card_service.h"
#include"global.h"
#include"tool.h"
#include"service.h"

//函数名：outputMenu
//功能：输出系统菜单
//参数：void
//返回值：void
void outputMenu()
{   //输出系统菜单
	printf("------计费系统菜单------\n");
	printf("*                      *\n");
	printf("*       1.添加卡       *\n");
	printf("*       2.查询卡       *\n");
	printf("*       3.上机         *\n");
	printf("*       4.下机         *\n");
	printf("*       5.充值         *\n");
	printf("*       6.退费         *\n");
	printf("*       7.查询统计     *\n");
	printf("*       8.注销卡       *\n");
	printf("*       0.退出         *\n");
	printf("------------------------\n\n");
}

//函数名：add
//功能：添加用户信息到卡结构体变量，并屏幕显示
//参数：void
//返回值：void
void add()
{
	Card card;
	char name[30];//临时存放输入的用户名
	char pwd[20];//临时存放输入的密码
	struct tm* endTime;//临时存放截止时间
	struct tm* startTime;//临时存放开卡时间

	printf("请输入卡号(长度为1-18):");
	scanf("%s", &name);
	if (getSize(name) >= 18) //判断输入的卡号长度是否符合要求
		printf("输入的卡号长度超过最大值");
	//判断输入的卡号是否存在
	if (queryCardInfo(name) != NULL)
	{
		printf("输入的卡号已存在！请重新输入！\n\n");
		return;
	}
	strcpy(card.aName, name);//将输入的卡号保存到卡结构体变量中

	printf("请输入密码(长度为1-8):");
	scanf("%s", &pwd);
	if (getSize(pwd) >= 8)//判断输入的密码长度是否符合要求
		printf("输入的密码长度超过最大值！");
	strcpy(card.aPwd, pwd);//将输入的密码保存到卡结构体中

	printf("请输入开卡金额（RMB):");
	scanf("%f", &card.fBalance);

	card.fTotalUse = card.fBalance;//添加卡时，累计金额等于开卡金额
	card.nDel = 0;//删除标识
	card.nStatus = 0;//卡状态
	card.nUseCount = 0;//使用次数
	//开卡时间，截止时间，最后使用时间都默认为当前时间
	//time（NULL）获取当前绝对时间（日历时间），1970-01-01 00;00；00 起到现在的秒数
	card.tStart = card.tEnd = card.tLastTime = time(NULL);

	//根据开卡时间，计算截止时间，每张卡的有效期为一年
	startTime = localtime(&card.tStart);//将日历时间转换为分解时间
	endTime = localtime(&card.tEnd);
	endTime->tm_year = startTime->tm_year + 1;
	card.tEnd = mktime(endTime);//将分解时间转换为日历时间

	//输出添加卡的信息
	printf("\n");
	printf("----------------添加的卡信息如下----------------\n");
	printf("\t卡号\t密码\t状态\t开卡金额\n");
	printf("\t%s\t%s\t%s\t%.2f\n", card.aName, card.aPwd, card.nStatus, card.fBalance);

	//卡信息添加到文件中
//	if (FALSE == addCard(card))
	if(addCardInfo(card)==FALSE)
		printf("----******------添加卡信息失败！----******------\n\n");
	else
		printf("----******------添加卡信息成功！----******------\n\n");
}

//函数名：getSize
//功能：计算字符数组中字符长度
//参数：字符数组名
//返回值：字符个数
int getSize(const char* pString)
{
	int nSize = 0;

	//计算字符串的字符个数
	while (*(pString + nSize) != '\0')
		nSize++;

	//返回字符个数
	return nSize;
}

//函数名：query
//功能：根据输入的卡号，调用，查询是否有该卡，有的话，输出该卡信息
//参数：void
//返回值：void
void query()
{
	char name[18];        //存放要查询的用户名
	Card* pCard = NULL;
	char aLastTime[30];//存放指定格式字符串的时间
	int icha = 0;
	int nIndex = 0;
	int i;                  //查询到卡信息数量


	printf("请输入要查询的卡号(长度1~18):");
	scanf("%s", name);

	printf("1.精确查询||2.模糊查询(输入1或2):");
	scanf("%d", &icha);



	if (icha == 1)
		pCard = queryCardInfo(name);
	else if (icha == 2)
		pCard = queryCardsInfo(name, &nIndex);
	else
	{
		do {
			printf("输入错误！\n请重新输入：");
			scanf("%d", &icha);
		} while (icha != 1 && icha != 2);

		if (icha == 1)
			pCard = queryCard(name);
		else if (icha == 2)
			pCard = queryCards(name, &nIndex);

	}

	if (pCard == NULL)
	{
		printf("----******------没有该卡信息！------******----\n");
		printf("\n");
	}
	else
	{
		if (icha == 1)
		{
			printf("-------------******-------------查询到的卡信息如下-------------******-------------\n");
			//输出表格的表头
			printf("\t卡号\t状态\t余额\t累计金额\t使用次数\t上次使用时间\n");

			//将time_t类型时间转换为字符串，字符串格式为“年-月-日 时：分”
			timeToString(pCard->tLastTime, aLastTime);
			//输出查到的卡信息
			printf("\t%s\t%d\t%.2f\t%.2f\t%10d\t\t%s\n", pCard->aName, pCard->nStatus, pCard->fBalance, pCard->fTotalUse, pCard->nUseCount, aLastTime);
			printf("----------------------------------------------------------------------------------\n");
			printf("\n");

		}
		else if (icha == 2)   //模糊查询结果输出
		{
			for (i = 0; i < nIndex; i++)
			{
				printf("-------------******-------------查询到的卡信息如下-------------******-------------\n");
				//输出表格的表头
				printf("\t卡号\t状态\t余额\t累计金额\t使用次数\t上次使用时间\n");

				//将time_t类型时间转化为字符串，字符串格式为"年-月-日 时：分"
				timeToString(pCard[i].tLastTime, aLastTime);   //结构体指针当数组名用

				//输出查询到的卡信息
				printf("\t%s\t%d\t%.2f\t%.2f\t%10d\t\t%s\n", pCard[i].aName, pCard[i].nStatus, pCard[i].fBalance, pCard[i].fTotalUse, pCard[i].nUseCount, aLastTime);
				printf("----------------------------------------------------------------------------------\n");

			}
			//释放动态分配的内存
			free(pCard);

		}

		else
			;
		pCard = NULL;
	}
}


//函数名：exitApp
//功能：退出应用程序
//参数：void
//返回值：void
void exitApp()
{
	releaseList();
}

//函数名：logon
//功能：输入上机卡信息，查询到，输出上机卡信息
//参数：void
//返回值：void
void logon()
{
	char aName[30] = { 0 };//上机卡号
	char aPwd[20] = { 0 };//上机卡密码
//  Card* pCard = NULL;
	LogonInfo* pInfo = NULL;
	int nResult = 0;
	char aLastTime[30];//存放指定格式字符串的时间

	//提示并接收上机卡号
	printf("请输入上机的卡号(长度为1~18)：");
	scanf("%s", &aName);
	//判断输入的卡号是否符合要求
	if (getSize(aName) >= 18)
	{
		printf("输入的卡号长度超过最大值！\n");
		return;
	}
	//提示并接收上机密码
	printf("请输入上机密码(长度为1~8):");
	scanf("%s", &aPwd);
	//判断输入的密码是否符合要求
	if (getSize(aPwd) >= 8)
	{
		printf("输入的密码长度超过最大值!\n");
		return;
	}

	//开始上机，获取上机结果
	pInfo = (LogonInfo*)malloc(sizeof(LogonInfo));
	nResult = doLogon(aName, aPwd,pInfo);
	switch (nResult)
	{
	case 0:printf("---------上机失败！---------\n"); break;
	case 1:
		//将time_t类型时间转换为字符串，字符串格式为年-月-日 时:分
		timeToString(pInfo->tLogon, aLastTime);//结构体指针当数组名使用

		printf("----***-----上机的卡信息如下-----***---\n");
		//输出表格的表头
		printf("\t卡号\t余额\t上机时间\n");

		//输出查到的卡信息
		printf("\t%s\t%.2f\t%s\n", pInfo->aCardName, pInfo->fBalance, aLastTime);
		printf("---------上机成功！---------\n");
		printf("\n");
		break;
	case 2:printf("---------该卡不能使用！---------\n"); break;
	case 3:printf("---------余额不足！---------\n"); break;
	}
	//释放上机信息
	free(pInfo);

}

//函数名：settle
//功能：输入下机卡信息，查询到，输出上机卡信息
//参数：void
//返回值：void
void settle()
{
	char aName[18] = { 0 };//卡号
	char aPwd[8] = { 0 };//密码
	int nResult = -1;//下机结果
	SettleInfo* pInfo = NULL;//下机信息
	char aStartTime[30] = { 0 };//上机时间
	char aEndTime[30] = { 0 };//下机时间

	//为下机信息动态分配内存
	pInfo = (SettleInfo*)malloc(sizeof(SettleInfo));

	printf("请输入下机卡号(长度为1~18):");//输入提示
	scanf("%s", &aName);
	printf("请输入下机密码(长度为1~8):");//输入提示
	scanf("%s", &aPwd);

	//进行下机
	nResult = doSettle(aName, aPwd, pInfo);

	//根据下机结果，提示不同信息
	printf("\n");
	printf("------------******------------下机信息如下------------******------------\n");
	
	switch (nResult)
	{
	case 0://下机失败
		printf("下机失败!\n"); break;
	case 1://下机成功
		//输出表格的表头
		printf("\t卡号\t消费\t余额\t上机时间\t下机时间\n");

		//上机时间默认为卡的最后使用时间，后面添加计费额信息后，使用计费时间
		//将time_t类型时间转换为字符串，字符串格式为"年-月-日 时：分"
		timeToString(pInfo->tStart, aStartTime);
		timeToString(pInfo->tEnd, aEndTime);
		
		//输出下机卡信息
		printf("\t%s\t%.2f\t%.2f\t%s\t%s\n\n", pInfo->aCardName, pInfo->fAmount, pInfo->fBalance, aStartTime, aEndTime);
		printf("------------******------------下机成功！------------******------------\n");
		break;
	case 2://正在使用或已注销
		printf("该卡未在使用！\n"); break;
	case 3://余额不足
		printf("卡余额不足\n"); break;
	default:
		break;
	}
	free(pInfo);
}

//函数名：addMoney
//功能：充值
//参数：void
//返回值：void
/*void addMoney()
{
	char aName[18] = { 0 };//卡号
	char aPwd[8] = { 0 };//密码
	float fAmount = 0;//充值金额
	MoneyInfo sMoneyInfo;//充值信息

	printf("请输入要充值的卡号（长度为1~18）:");//输入提示
	scanf("%s", &aName);
	printf("请输入充值卡的密码（长度为1~8）:");//输入提示
	scanf("%s", &aPwd);
	printf("请输入充值金额（RMB）：");//输入提示
	scanf("%lf", &fAmount);

	//保存充值金额
	sMoneyInfo.fMoney = fAmount;

	//判断充值是否成功
	if (doAddMoney(aName, aPwd, &sMoneyInfo) == TRUE)
	{
		//提示充值信息
		printf("-----***-----充值信息如下-----***-----\n");
		//输出表格表头
		printf("\t卡号\t充值金额\t余额\n");
		//输出充值卡信息
		printf("\t%s\t%2f\t%.2f\n\n", sMoneyInfo.aCardName, sMoneyInfo.fMoney, sMoneyInfo.fBalance);
	}
	else
		printf("------充值失败！------\n");
}
*/
void addMoney()
{
	char aName[18] = { 0 };		//卡号
	char aPwd[8] = { 0 };			//密码
	float fAmount = 0;			//充值金额
	MoneyInfo sMoneyInfo;		//充值卡信息

	printf("请输入充值的卡号（长度1~18）：");
	scanf_s("%s", aName, 18);
	//判断输入的卡号是否符合要求
	if (getSize(aName) >= 18)
	{
		printf("输入的卡号长度超过最大值！\n");
		return;
	}

	printf("请输入充值密码（长度1~8）：");
	scanf_s("%s", aPwd, 8);
	//判断输入的密码是否符合要求
	if (getSize(aPwd) >= 8)
	{
		printf("输入的密码长度超过最大值！\n");
		return;
	}

	printf( "请输入充值金额（RMB)：");
	scanf(" %lf",fAmount);

	//保存充值金额
	sMoneyInfo.fMoney = fAmount;
	//判断是否保存成功
	if (TRUE == doAddMoney(aName, aPwd, &sMoneyInfo))
	{
		//提示充值信息
		printf("-----***---充值信息如下---***-----\n");
		//输出表格头
		printf("\t卡号\t充值金额\t余额\n");
		//输出充值卡信息
		printf("\t%s\t%.2f    \t%.2f\n", sMoneyInfo.aCardName, sMoneyInfo.fMoney, sMoneyInfo.fBalance);
	}
	else
	{
		printf("-------充值失败！-------\n");
	}
}
