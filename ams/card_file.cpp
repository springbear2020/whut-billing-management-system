#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<fstream>

/*#include<stdio.h>
#include<string.h>
#include<stdlib.h>*/

#include"model.h"
#include"global.h"
#include"tool.h"
#include"card_file.h"

using namespace std;

//函数名：saveCard
//功能：将卡信息保存到文件中
//参数：pCard:指向要保存的卡信息结构体； pPath:保存的文件路径
//返回值：保存成功返回TRUE,失败返回FALSE
extern int saveCard(const Card* pCard, const char* pPath)
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
		cerr << "文件无法正常打开！不能写入卡信息！" << endl;
		exit(EXIT_FAILURE);
	}
	//向文件中写入信息
	ofile << pCard->aName << "##" << pCard->aPwd << "##" << pCard->nStatus << "##";
	ofile << aStart << "##" << aEnd << "##" << pCard->fTotalUse << "##" << aLast << "##";
	ofile << pCard->nUseCount << "##" << pCard->fBalance << "##" << pCard->nDel << endl;
	ofile.close();

	cout << endl;
	cout << "----******-----卡信息成功存入文件！------******----" << endl << endl;
	return TRUE;
}
