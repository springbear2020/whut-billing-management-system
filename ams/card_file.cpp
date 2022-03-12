#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"card_file.h"
#include"model.h"
#include"global.h"
#include"tool.h"


using namespace std;

//函数名：saveCard
//功能：将卡信息保存到文件中
//参数：pCard:指向要保存的卡信息结构体； pPath:保存的文件路径
//返回值：保存成功返回TRUE,失败返回FALSE
int saveCard(const Card* pCard, const char* pPath)
{
	char aStart[30];//存放转换后的时间字符串
	char aEnd[30];//存放转换后的时间字符串
	char aLast[30];//存放转换后的时间字符串

	timeToString(pCard->tStart, aStart);
	timeToString(pCard->tEnd, aEnd);
	timeToString(pCard->tLastTime, aLast);

	ofstream ofile(pPath, ios_base::out | ios_base::app);//以追加方式写入
	if (!ofile.is_open())
	{
		cerr << "文件无法正常打开！不能写入卡信息！\n" << endl;
		exit(EXIT_FAILURE);
	}
	//向文件中写入信息
	ofile << pCard->aName << "##" << pCard->aPwd << "##" << pCard->nStatus << "##";
	ofile << aStart << "##" << aEnd << "##" << pCard->fTotalUse << "##" << aLast << "##";
	ofile << pCard->nUseCount << "##" << pCard->fBalance << "##" << pCard->nDel << endl;
	ofile.close();

	cout << "----******----卡信息成功存入文件！-----******----" << endl;
	return TRUE;
}

#define CARDCHARNUM 256  //从卡信息文件读取得字符数最大值

//函数名：readCard
//功能：从文件中读取卡信息到结构体数组
//参数：pCard：指向结构体数组；pPath：文件路径
//返回值：正确读取返回TRUE,否则返回FALSE
int readCard(Card* pCard, const char* pPath)
{
	int nIndex = 0;//卡信息数量
	char aBuf[CARDCHARNUM] = { 0 };//保存从文件中读取的一行数据
	int i = 0;//结构体数组下标

	ifstream ifile;
	//默认以只读方式打开文件
	ifile.open(pPath);
	if (ifile.is_open()) 
		while (!ifile.eof())
		{
			memset(aBuf, 0, CARDCHARNUM);//清空字符数组
			ifile.getline(aBuf, CARDCHARNUM);//读取一行卡信息
			if (strlen(aBuf) != 0)
				pCard[i] = praseCard(aBuf);
			i++;
		}
	else{
		cout << "文件无法正确打开！不能读取卡信息！\n" << endl;
		ifile.close();
		return FALSE;
	}
	//关闭文件
	ifile.close();
	return TRUE;
}

//函数名：praseCard
//功能：将一条卡信息字符串解析后放入一个卡结构体
//参数：卡信息字符串
//返回值：卡结构体
Card praseCard(char* pBuf)
{
	Card card;
	char flag[10][20];//临时存放分量
	char* str;//每次解析出来的字符串
	char* buf;
	int index = 0;//数组下标

	buf = pBuf;//第一次调用strtok函数时，buf为解析字符串
	while ((str = strtok(buf, "##")) != NULL)
	{
		strcpy(flag[index], str);
		buf = NULL;//后面调用strtok函数时，第一个参数为NULL
		index++;
	}
	//分割的内容保存到结构体中
	strcpy(card.aName, flag[0]);
	strcpy(card.aPwd, flag[1]);
	card.nStatus = atoi(flag[2]);
	card.tStart = stringToTime(flag[3]);
	card.tEnd = stringToTime(flag[4]);
	card.fTotalUse = atof(flag[5]);
	card.tLastTime = stringToTime(flag[6]);
	card.nUseCount = atoi(flag[7]);
	card.fBalance = atof(flag[8]);
	card.nDel = atoi(flag[9]);
	//返回卡信息结构体
	return card;
}

//函数名：getCardCount
//功能：获取卡信息文件中卡信息数量
//参数：文件路径
//返回值：卡信息数量
int getCardCount(const char* pPath)
{
	int nIndex = 0;//卡信息数量
	char aBuf[CARDCHARNUM] = { 0 };//保存从文件中读取的数据

	ifstream ifile;
	//默认以只读的方式打开文件
	ifile.open(pPath);
	if(ifile.is_open())
		//遍历文件
		while (!ifile.eof())
		{
			memset(aBuf, 0, CARDCHARNUM);//清空字符数组
			ifile.getline(aBuf, CARDCHARNUM);//读取一行卡信息
			if (strlen(aBuf) != 0)
				nIndex++;
		}
	else
	{
		cout << "文件无法正确打开！不能读取卡信息！\n" << endl;
		ifile.close();
		return -1;
	}
	//关闭文件
	ifile.close();
	return nIndex;
}