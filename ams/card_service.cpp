#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"model.h"
#include"global.h"
#include"card_file.h"
#include"card_service.h"
#include"billing_service.h"


lpCardNode cardList = NULL;  //卡信息链表类型变量

//函数名:addCard
//功能:添加卡信息到结构体数组
//参数:卡信息结构体
//返回值:整数1：添加成功；整数0：不能添加；
int addCard(Card crd)
{
	  //将信息保存到文件中
	if (TRUE == saveCard(&crd, CARDPATH))
	{
		return TRUE;
	}
	return FALSE;
}

//函数名:queryCard
//功能:在结构体数组中查询指定卡号的信息
//参数:用户输入的要查询的卡号地址
//返回值:结构体数组中查询到的卡信息地址，没有找到返回NULL
Card* queryCard(const char* pName)
{
	Card* pCard = NULL;
	lpCardNode p;    //用于查找中迭代，一次指向链表中的每个节点

	//从卡信息文件中读取卡信息到链表，失败返回NULL
	if (FALSE == getCard())
	{
		return NULL;
	}
	//指向链表头节点，用于迭代
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
		{
			p = p->next;
		}
	}
	//没有找到，返回NULL
	return pCard;
}

//函数名:getCard
//功能:从卡信息文件中，获取卡信息
//参数:void
//返回值:读取成功返回TRUE,否则返回FALSE
int getCard()
{
	int i = 0;
	Card* pCard = NULL;       //读取到的一条卡信息
	int nCount = 0;          //实际卡信息数
	lpCardNode node = NULL;//当前尾节点
	lpCardNode cur = NULL;//添加到链表中的节点

	//清除链表中已经存在的数据
	if (cardList != NULL)
	{
		releaseCardList();
	}
	//初始化链表
	initCardList();

	//获取文件中卡信息数
	nCount = getCardCount(CARDPATH);

	if (nCount == 0)
	{
		return FALSE;
	}
	else if (nCount == -1)
	{
		printf("文件无法打开！\n");
		return FALSE;
	}
	//动态分配内存用来保存所有卡信息，相当于结构体数组，pCard相当于数组名
	pCard = (Card*)malloc(sizeof(Card) * nCount);
	if (pCard != NULL)
	{
		//如果返回FALSE代表读取卡信息失败
		if (0 == readCard(pCard, CARDPATH))
		{
			free(pCard);
			return FALSE;
		}
		//将读取的卡信息，保存到链表中
		for (i = 0, node = cardList; i < nCount; i++)
		{
			//为节点分配内存
			cur = (lpCardNode)malloc(sizeof(CardNode));
			//如果分配失败，则返回FALSE
			if (cur == NULL)
			{
				free(pCard);
				return FALSE;
			}
			//初始化新的内存空间，全部赋值为0
			memset(cur, 0, sizeof(CardNode));

			//将卡信息保存到节点中
			cur->data = pCard[i];
			cur->next = NULL;

			//将节点添加到链表的尾部
			if (node != NULL)
			{
				node->next = cur;
				node = cur;
			}
		}
		//释放内存
		free(pCard);
		return TRUE;
	}
	return FALSE;
}

//函数名:initCardList()
//功能:初始化卡信息链表
//参数:void
//返回值:int型，TRUE表示成功，FALSE表示失败
int initCardList()
{   
	lpCardNode head = NULL;
	if (cardList == NULL)
	{
		//为链表头节点分配内存
		head = (lpCardNode)malloc(sizeof(CardNode));

		//如果分配成功
		if (head != NULL)
		{
			head->next = NULL;
			cardList = head;
			return TRUE;
		}
	}
	return FALSE;
}

//函数名:releaseCardList
//功能:释放卡信息链表
//参数:void
//返回值:void
void releaseCardList()
{
	lpCardNode cur = cardList;
	lpCardNode next = NULL;

	while (cur != NULL)
	{
		next = cur->next;    //释放节点前用next保存它的后继节点
		free(cur);            //释放cur节点
		cur = next;
	}
	cardList = NULL;

}

//函数名:queryCards
//功能:在卡信息链表中，模糊查询包含的所有卡信息
//参数:pName:指向用户所要查询的卡号；pIndex：指向查询到的卡信息数量
//返回值:指向卡信息结构体的指针
Card* queryCards(const char* pName, int* pIndex)
{
	lpCardNode node = NULL;
	Card* pCard = NULL; //保存查询到的符合条件的卡信息
	Card* x = NULL;

	//从卡信息文件中读取卡信息到链表，失败返回NULL
	if (FALSE == getCard())
	{
		return NULL;
	}

	//首先分配一个Card大小的内存空间
	pCard = (Card*)malloc(sizeof(Card));
	if (pCard == NULL)
	{
		return NULL;
	}

	//从链表的头节点指向的下一个结点开始遍历
	node = cardList->next;

	//遍历链表，节点为空表示到达链表尾部
	while (node != NULL)
	{
		//判断在遍历到结点的卡号中，查找是否包含要查找的字符串
		if (strstr(node->data.aName, pName) != NULL)
		{
			//如果有则保存结点的数据
			pCard[*pIndex] = node->data;
			(*pIndex)++;

			//从新为指针分配内存，包含已有的内容
			x = (Card*)realloc(pCard, ((*pIndex) + 1) * sizeof(Card));
			if (x != NULL)
			{
				pCard = x;
			}
		}
		
		//移动到链表的下一个结点
		node = node->next;

	}
	return pCard;
}

//函数名:checkCard
//功能:从文件中读取卡信息到链表，在链表中查询卡信息,并获取其在链表中的位置
//参数:pName:上机卡号；pPwd:上机密码  pIndex:返回卡的索引号
//返回值:上机卡结构体
Card* checkCard(const char* pName, const char* pPwd,int* pIndex)
{
	lpCardNode cardNode = NULL;    //当前节点
	int nIndex = 0;//上机卡在卡信息链表中的索引号
	//Billing* pBilling = NULL;

	//如果从文件中获取卡信息失败，则上机失败
	if (FALSE == getCard())
	{
		return FALSE;
	}
	//指向链表
	cardNode = cardList;
	//遍历链表
	while (cardNode != NULL)
	{
		//查找上机卡，判断卡号和密码是否正确
		if ((strcmp(cardNode->data.aName, pName) == 0) && (strcmp(cardNode->data.aPwd, pPwd) == 0))
		{
			//返回卡信息节点数据的地址
			*pIndex = nIndex;
			return &cardNode->data;
		}
		cardNode = cardNode->next;
		nIndex++;
	}
	return NULL;
}
