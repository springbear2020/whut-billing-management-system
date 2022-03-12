#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>

#include"card_sevice.h"
#include"model.h"
#include"global.h"

Card aCard[50];//卡结构体数组
int nCount = 0;//卡结构体数组的实际信息数

//函数名：addcard
//功能：添加卡信息到结构体数组
//参数：卡信息结构体
//返回值：整数1：添加成功；整数0：不能添加
int addCard(Card crd)
{
	if (nCount < 50)
	{//数组未满，添加一条卡信息
		strcpy(aCard[nCount].aName, crd. aName);
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
	}
}

//函数名：queryCard
//功能：在结构体数组中查找指定卡号的卡信息
//参数：用户输入的要查询的卡号地址
//返回值：结构体数组中查询到的卡信息地址，没有找到返回NULL
Card* queryCard(const char* pName)
{
	Card* pCard = NULL;
	int i;
	for(i=0;i<nCount;i++)
		if (strcmp(aCard[i].aName, pName) == 0)
		{//在结构体数组中找到，返回卡信息地址
			pCard = &aCard[i];
			return pCard;
		}
	//没有找到，返回NULL
	return pCard;
}
