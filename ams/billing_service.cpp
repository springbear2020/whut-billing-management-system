#include<stdlib.h>
#include<string.h>
#include<time.h>

#include"billing_service.h"
#include"model.h"//包含数据类型定义头文件
#include"global.h"  //包含全局定义头文件
#include"billing_file.h"

lpBillingNode billingList = NULL;//计费信息链表

//函数名：addBilling
//功能：上机时添加消费信息到文件
//参数：pName:上机卡号；pBilling:指向消费信息结构体
//返回值：TRUE:保存成功；FALSE:保存失败
int addBilling(const char* pName, Billing* pBilling)
{
	//将消费信息写入结构体
	strcpy_s(pBilling->aCardName, pName);//上机卡号
	pBilling->tStart = time(NULL);//上机时间
	pBilling->tEnd = 0;//下机时间
	pBilling->fAmount = 0;//消费金额
	pBilling->nStatus = 0;//消费状态：0-未结算，1-已经结算
	pBilling->nDel = 0;//删除标识：0-未删除，1-已删除

	//消费信息结构体写入文件
	if (saveBilling(pBilling, BILLINGPATH) == FALSE)
		return FALSE;
	return TRUE;
}

//函数名：initBillingList
//功能：初始化计费信息链表
//参数：void
//返回值：void
void initBillingList()
{
	lpBillingNode head = NULL;
	if (billingList == NULL)
	{
		head = (lpBillingNode)malloc(sizeof(BillingNode));
		head->next = NULL;
		billingList = head;
	}
}

//函数名：releaseBillingList
//功能：释放计费信息链表
//参数：void
//返回值：void
void releaseBillingList()
{
	lpBillingNode cur = billingList;
	lpBillingNode next = NULL;
	//销毁链表
	while (cur != NULL)
	{
		next = cur->next;//结点内存释放前，next保存其后继
		free(cur);//释放结点内存
		cur = next;
	}
	billingList = NULL;
}

//函数名：getBilling
//功能：从计费信息文件中，获取计费信息保存到链表中
//参数：void
//返回值：TRUE:获取信息成功；FALSE:获取信息失败
int getBilling()
{
	int nCount = 0;//计费信息数量
	Billing* pBilling = NULL;//计费信息
	lpBillingNode node = NULL;
	int i = 0;//循环变量
	lpBillingNode cur = NULL;

	//如果链表不为空，释放链表
	if (billingList != NULL)
		releaseBillingList();
	//初始化链表
	initBillingList();

	//获取计费信息数量
	nCount = getBillingCount(BILLINGPATH);
	//动态分配内存
	pBilling = (Billing*)malloc(sizeof(Billing) * nCount);

	if (pBilling != NULL)
	{
		//获取计费信息
		if (readBilling(pBilling, BILLINGPATH) == FALSE)
		{
			free(pBilling);
			return FALSE;
		}
		//将计费信息保存到链表中
		for (i = 0, node = billingList; i < nCount; i++)
		{
			//为当前结点分配内存
			cur = (lpBillingNode)malloc(sizeof(BillingNode));
			//如果分配失败，则在返回FALSE前，需要释放pBilling的内存
			if (cur == NULL)
			{
				free(pBilling);
				return FALSE;
			}
			//初始化新的空间，全部赋值为0
			memset(cur, 0, sizeof(BillingNode));
			//将数据添加到结点中
			cur->data = pBilling[i];
			cur->next = NULL;
			//将结点添加到链表中
			node->next = cur;
			node = cur;
		}
		free(pBilling);
		return TRUE;
	}
	return FALSE;
}

//函数名：queryBilling
//功能:在计费信息链表中，查询对应卡的计费信息，并获取其在链表中的索引号
//参数：pName：要查询的计费信息的卡号
//      pIndex：查询到的计费信息在链表中的索引号
//返回值：查询到的计费信息指针
Billing* queryBilling(const char* pName, int* pIndex)
{
	lpBillingNode node = NULL;
	int nIndex = 0;

	if (getBilling() == FALSE)
		return NULL;
	//遍历链表
	node = billingList;
	while (node != NULL)
	{
		//查询到卡号相同，并且没有结算的计费信息
		if (strcmp(node->data.aCardName, pName) == 0 && node->data.nStatus == 0)
			return &node->data;
		node = node->next;
		nIndex++;
		*pIndex = nIndex;
	}
	return NULL;
}