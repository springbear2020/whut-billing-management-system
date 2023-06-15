#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>

#include <stdio.h>
#include "model.h"

#include "global.h"

using namespace std;

// 函数名:aveMoney
// 功能:将充值退费信息保存到文件中
// 参数:pMoney:充值退费结构体；pPath:充值退费信息保存路径
// 返回值:TRUE:保存成功 FALSE:保存失败
int saveMoney(const Money *pMoney, const char *pPath)
{
	// 以追加方式，二进制方式写入
	ofstream ofile(pPath, ios_base::out | ios_base::app | ios_base::binary);
	if (!ofile.is_open())
	{
		printf("文件无法正确打开！不能写入充值退费信息!\n");
		ofile.close();
		return FALSE;
	}
	// 将充值退费信息保存到文件中
	ofile.write((const char *)pMoney, sizeof(Money));

	// 关闭文件
	ofile.close();
	printf("----*****-----充值退费信息成功存入文件!-----*****----\n");
	return TRUE;
}
