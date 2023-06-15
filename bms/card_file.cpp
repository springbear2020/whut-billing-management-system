#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tool.h"
#include "model.h"
#include "global.h"
#include "card_file.h"

using namespace std;

// 函数名:saveCard
// 功能:将卡信息保存到文件中
// 参数: pCard:只想要保存的卡信息结构体；pPath:保存的文件路径
// 返回值:保存成功返回TRUE,失败返回FALSE;
int saveCard(const Card *pCard, const char *pPath)
{
	// 以追加方式，二进制方式写入
	ofstream ofile(pPath, ios_base::out | ios_base::app | ios_base::binary);
	if (!ofile.is_open())
	{
		printf("文件无法正确打开！不能写入卡信息!\n");
		ofile.close();
		return FALSE;
	}
	// 将卡信息保存到文件中
	ofile.write((const char *)pCard, sizeof(Card));

	// 关闭文件
	ofile.close();
	printf("----*****-----卡信息成功存入文件!-----*****----\n");
	return TRUE;
}

// 函数名:readCard
// 功能:从文件中读取卡信息到结构体数组
// 参数:pCard：指向结构体数组；pPath：文件路径
// 返回值:确读取返回TRUE,否则返回FALSE
int readCard(Card *pCard, const char *pPath)
{
	int nIndex = 0;

	// 以二进制方式读取
	ifstream ifile(pPath, ios_base::in | ios_base::binary);
	if (!ifile.is_open())
	{
		printf("文件无法正确打开！不能读取卡信息!\n");
		ifile.close();
		return FALSE;
	}
	else
	{
		// 遍历文件读取文件内容
		while (!ifile.eof())
		{
			if (!ifile.read((char *)(&pCard[nIndex]), sizeof(Card)))
				;
			else
			{
				nIndex++;
			}
		}
		// 关闭文件
		ifile.close();
		return TRUE;
	}
}

// 函数名:getCardCount
// 功能:获取卡信息文件中，卡信息数量
// 参数:文件路径
// 返回值:卡信息数量
int getCardCount(const char *pPath)
{
	int nCount = 0; // 卡信息数量
	Card *pCard = (Card *)malloc(sizeof(Card));
	// 以二进制方式读取
	ifstream ifile(pPath, ios_base::in | ios_base::binary);
	if (!ifile.is_open())
	{
		printf("文件无法正确打开！不能统计卡信息数量!\n");
		ifile.close();
		return -1; //-1表示文件没有正确打开
	}
	else
	{ // 遍历文件
		while (!ifile.eof())
		{
			if (!ifile.read((char *)pCard, sizeof(Card)))
				;
			else
			{
				nCount++;
			}
		}
		// 关闭文件
		ifile.close();
		free(pCard);
		return nCount;
	}
}

// 函数名:updateCard
// 功能:更新卡信息文件中的一条卡信息
// 参数:pCard 更新后的卡内容 pPath卡信息文件路径 nIndex 需要更新的卡信息在文件中的卡序号
// 返回值:TRUE 更新成功 FALSE 更新失败
int updateCard(const Card *pCard, const char *pPath, int nIndex)
{
	int nCount = 0;
	long lPosition = 0;
	Card pbBuf;

	// 以读写模式，二进制模式打开文件，如果失败返回FALSE
	fstream iofile(pPath, ios_base::out | ios_base::in | ios_base::binary);
	if (!iofile.is_open())
	{
		printf("文件无法正确打开！不能更新卡信息！\n");
		iofile.close();
		return FALSE;
	}
	// 遍历文件，获取消费信息在文件中的位置
	while ((!iofile.eof()) && (nCount < nIndex))
	{
		if (!iofile.read((char *)(&pbBuf), sizeof(Card)))
			;
		else
		{
			// 获取文件标识位置，最后一次找到的位置
			lPosition = (long)iofile.tellg();
		}
		nCount++;
	}
	// 移动到文件标识位置
	// 注意指针是在该条消费之后还是之前！！！
	// 上面得到的读写指针在下一条信息开头，要移动到本条信息开头处
	iofile.seekp((__int64)lPosition - sizeof(Card), ios_base::beg);
	// 更新消费信息到文件
	iofile.write((const char *)(pCard), sizeof(Card));
	printf("----*****----卡信息更新到文件成功！----*****----\n");
	// 关闭文件
	iofile.close();
	return TRUE;
}
