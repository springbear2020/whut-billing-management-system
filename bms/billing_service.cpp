#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "model.h"
#include "global.h"
#include "billing_file.h"

lpBillingNode billingList = NULL;

// 函数名:addBilling
// 功能:上机时添加消费信息到文件
// 参数:pName:上机卡号；pBilling:指向消费信息结构体
// 返回值:TRUE：保存成功；FALSE:保存失败
int addBilling(const char *pName, Billing *pBilling)
{
	// 将消费信息写入结构体
	strcpy(pBilling->aCardName, pName); // 上机卡号
	pBilling->tStart = time(NULL);		// 上机时间
	pBilling->tEnd = 0;					// 下机时间
	pBilling->fAmount = 0;				// 消费金额
	pBilling->nStatus = 0;				// 消费状态 0-未结算；1-已结算
	pBilling->nDel = 0;					// 删除标识，0-未删除；1-已删除

	if (FALSE == saveBilling(pBilling, BILLINGPATH))
	{
		return FALSE;
	}
	return TRUE;
}

// 函数名:initBillingList
// 功能:初始化计费信息链表
// 参数:void
// 返回值:void
void initBillingList()
{
	lpBillingNode head = NULL;
	if (billingList == NULL)
	{
		head = (lpBillingNode)malloc(sizeof(BillingNode));
		if (head == NULL)
		{
			exit(1);
		}
		head->next = NULL;
		billingList = head;
	}
}

// 函数名:releaseBillingList
// 功能:释放计费信息链表
// 参数:void
// 返回值:void
void releaseBillingList()
{
	lpBillingNode cur = billingList;
	lpBillingNode next = NULL;
	// 销毁链表
	while (cur != NULL)
	{
		next = cur->next; // 节点内存释放，next保存其后继
		free(cur);		  // 释放节点内存
		cur = next;
	}
	billingList = NULL;
}

// 函数名:getBilling
// 功能:从计费文件中，获取计费信息保存到链表中
// 参数:void
// 返回值:TRUE：获取信息成功；FALSE:获取信息失败
int getBilling()
{
	int nCount = 0; // 计费信息数量
	Billing *pBilling = NULL;
	lpBillingNode node = NULL;
	int i = 0; // 循环变量
	lpBillingNode cur = NULL;

	// 如果初始链表不为空，释放链表
	if (billingList != NULL)
	{
		releaseBillingList();
	}
	// 初始化链表
	initBillingList();

	// 获取计费信息数量
	nCount = getBillingCount(BILLINGPATH);
	// 动态分配内存
	pBilling = (Billing *)malloc(sizeof(Billing) * nCount);
	if (pBilling == 0)
	{
		exit(1);
	}
	if (pBilling != NULL)
	{
		// 获取计费信息
		if (FALSE == readBilling(pBilling, BILLINGPATH))
		{
			free(pBilling);
			return FALSE;
		}
		// 将计费信息保存到链表中
		for (i = 0, node = billingList; i < nCount; i++)
		{
			// 为当前节点分配内存
			cur = (lpBillingNode)malloc(sizeof(BillingNode));

			// 如果分配失败则在返回FALSE前，需要释放pBilling内存
			if (cur == NULL)
			{
				free(pBilling);
				return FALSE;
			}
			// 初始化新的空间，全部复制为零
			memset(cur, 0, sizeof(BillingNode));
			// 将数据添加到节点中
			cur->data = pBilling[i];
			cur->next = NULL;
			// 将节点添加到链表中
			if (node == 0)
			{
				exit(1);
			}
			node->next = cur;
			node = cur;
		}
		free(pBilling);
		return TRUE;
	}
	return FALSE;
}

// 函数名:queryBilling
// 功能:在计费信息链表中，查询对应卡的计费信息，并获取其在链表中的索引号
// 参数:pName:要查询的计费信息的卡号；pIndex:要查询的计费信息在链表中的索引号
// 返回值:查询到的计费信息指针
Billing *queryBilling(const char *pName, int *pIndex)
{
	lpBillingNode node = NULL;
	int nIndex = 0;
	if (FALSE == getBilling())
	{
		return NULL;
	}
	// 遍历链表
	node = billingList;
	while (node != NULL)
	{
		// 查询到的卡号相同，并且没有结算的计费信息
		if (strcmp(node->data.aCardName, pName) == 0 && node->data.nStatus == 0)
		{
			return &node->data;
		}
		node = node->next;
		nIndex++;
		*pIndex = nIndex;
	}
	return NULL;
}
