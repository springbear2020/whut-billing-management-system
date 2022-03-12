#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"card_service.h"
#include"model.h"
#include"global.h"
#include"card_file.h"


//Card aCard[50];//卡结构体数组
//int nCount = 0;//卡结构体数组的实际信息数
lpCardNode cardList = NULL;//卡信息链表类型变量


//函数名：addcard
//功能：添加卡信息到结构体数组
//参数：卡信息结构体
//返回值：整数1：添加成功；整数0：不能添加
int addCard(Card crd)
{
	/*if (nCount < 50)//注释掉，待删除
	{//数组未满，添加一条卡信息
		strcpy(aCard[nCount].aName, crd.aName);
		strcpy(aCard[nCount].aPwd, crd.aPwd);
		aCard[nCount].nStatus = crd.nStatus;
		aCard[nCount].tStart = crd.tStart;
		aCard[nCount].tEnd = crd.tEnd;
		aCard[nCount].fTotalUse = crd.fTotalUse;
		aCard[nCount].tLastTime = crd.tLastTime;
		aCard[nCount].nUseCount = crd.nUseCount;
		aCard[nCount].fBalance = crd.fBalance;
		aCard[nCount].nDel = crd.nDel;

		nCount++;//计算自增1
		return TRUE;
	}
	else
	{
		printf("数组已满，不能添加！");
		return FALSE;
	}              */
	if (TRUE == saveCard(&crd, CARDPATH))
		return TRUE;
	else
		return FALSE;
}

/*
//函数名：queryCard
//功能：在结构体数组中查找指定卡号的卡信息
//参数：用户输入的要查询的卡号地址
//返回值：结构体数组中查询到的卡信息地址，没有找到返回NULL
Card* queryCard(const char* pName)
{
	Card* pCard = NULL;
	int i;

	//如果从卡信息文件中读取卡信息失败，则返回NULL
	if (getCard() == FALSE)
		return NULL;

	//在结构体数组中查找指定卡号
	for (i = 0; i < nCount; i++)
		if (strcmp(aCard[i].aName, pName) == 0)
		{//在结构体数组中找到，返回卡信息地址
			pCard = &aCard[i];
			return pCard;
		}
	//没有找到，返回NULL
	return pCard;
}
*/

//函数名：querycard
//功能：在链表中查找指定卡号的卡信息
//参数：用户输入的要查询的卡号地址
//返回值：链表中查询到的卡信息地址，没有找到返回NULL
Card* queryCard(const char* pName)
{
	Card* pCard = NULL;
	lpCardNode p;//用于查找中迭代，一次指向链表中的每个结点

	//从卡信息文件中读取卡信息到链表，失败返回NULL
	if (getCard() == FALSE)
		return NULL;
	//指向链表头表头，用于迭代
	p = cardList;
	//在链表中查找指定卡号
	while (p != NULL)
	{
		if (strcmp(p->data.aName, pName) == 0)
		{
			pCard = &(p->data);
				return pCard;
		}
		else
			p=p->next;
	}
	//没有找到，返回NULL
	return pCard;
}

//函数名：getcard
//功能：从卡信息文件中，获取卡信息，保存到结构体数组中
//参数：void
//返回值：读取成功返回TRUE,否则返回FALSE
int getCard()
{
	int i = 0;
	Card* pCard = NULL;//读取到的一条卡信息
	int nCount = 0;//实际卡信息数
	lpCardNode node = NULL;//当前尾结点
	lpCardNode cur = NULL;//添加到链表中的结点
	
	//清楚链表中已经存在的数据
	if (cardList != NULL)
		releaseCardList();
	
	//初始化链表
	initCardList();

	//获取文件中卡信息个数
	nCount = getCardCount(CARDPATH);
	if (nCount == 0)
		return FALSE;
	else if (nCount == -1)
	{
		printf("文件无法打开！\n\n");
		return FALSE;
	}

	//动态分配内存用来保存所有卡信息，相当于结构体数组，pCard相当于数组名
	pCard = (Card*)malloc(sizeof(Card) * nCount);
	if (pCard != NULL)
	{	//如果返回FALSE,表示读取卡信息失败
		if (readCard(pCard, CARDPATH) == 0)
		{
			free(pCard);
			return FALSE;
		}
		//将读取到的卡信息保存到链表中
		for (i = 0, node = cardList; i < nCount; i++)
		{
			//为结点分配内存
			cur = (lpCardNode)malloc(sizeof(CardNode));
			//如果分配内存失败，则返回
			if (cur == NULL)
			{
				free(pCard);
				return FALSE;
			}
			//初始化新的空间，全部赋值为0
			memset(cur, 0, sizeof(CardNode));

			//将卡信息保存到结点中
			cur->data = pCard[i];//结构体指针当数组名使用
			cur->next = NULL;

			//将结点添加到链表尾部
			node->next = cur;
			node = cur;
		}

		//释放内存
		free(pCard);
		return TRUE;
	}
	return FALSE;
}
	/*
	//清除结构体数组中已经存在的数据
	memset(aCard, 0, 50 * sizeof(Card));//清空数组

	//获取文件中的信息个数
	nCount = getCardCount(CARDPATH);
	if (nCount == 0)
		return FALSE;
	else if (nCount == -1)
	{
		printf("文件无法打开！");
		return FALSE;
	}
	//如果返回NULL，表示读取卡信息失败
	if (readCard(aCard, CARDPATH) == 0)
		return FALSE;
	return TRUE;
	
	*/



//函数名：initCardList
//功能：初始化卡信息链表
//参数：void
//返回值：int型，TRUE表示成功，FALSE表示失败
int initCardList()
{
	lpCardNode head = NULL;
	if (cardList == NULL)
	{
		//为链表结点分配内存
		head = (lpCardNode)malloc(sizeof(CardNode));

		//如果分配成功，则将链表指向
		if (head != NULL)
		{
			head->next = NULL;
			cardList = head;
			return TRUE;
		}		
	}
	return FALSE;
}

//函数名：releaseCardList
//功能：释放卡信息链表
//参数：void
//返回值：void
void releaseCardList()
{
	lpCardNode cur = cardList;
	lpCardNode next = NULL;

	while (cur != NULL)
	{
		next = cur->next;//释放cur结点前，用next保存它的后继结点
		free(cur);//释放cur结点
		cur = next;
	}
	cardList = NULL;
}

//函数名：queryCards
//功能：在卡信息链表中，模糊查询包含的所有卡信息
//参数：pName：指向用户输入的要查询的卡号；pIndex：指向查到的卡信息数变量
//返回值：指向卡信息结构体指针
Card* queryCards(const char* pName, int* pIndex)
{
	lpCardNode node = NULL;
	Card* pCard = NULL;//保存查询到的符合条件的卡信息

	//从卡信息文件中读取卡信息到链表，失败则返回NULL
	if (getCard() == FALSE)
		return NULL;

	//首先分配一个Card大小内存空间
	pCard = (Card*)malloc(sizeof(Card));
	if (pCard == NULL)
		return NULL;

	//从链表的头结点指向的下一个结点开始遍历
	node = cardList->next;

	//遍历链表，结点为空表示到达链表尾部
	while (node != NULL)
	{
		//判断在遍历到的结点卡号中，查找是否包含pName字符串
		if (strstr(node->data.aName, pName) != NULL)
		{
			//如果有，则保存结点中的数据
			pCard[*pIndex] = node->data;
			(*pIndex)++;

			//重新为指针分配内存，包含已有的内容
			pCard = (Card*)realloc(pCard, ((*pIndex) + 1) * sizeof(Card));
		}

		//移到链表的下一个结点
		node = node->next;
	}
	return pCard;
}