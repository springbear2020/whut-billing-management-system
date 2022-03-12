#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<istream>

#include"model.h"
#include"global.h"

using namespace std;

//函数名:saveBilling
//功能:保存计费信息
//参数:pBilling:计费信息结构指针；pPath:保存计费信息文件路径
//返回值:TRUE:保存成功；FALSE:保存失败
int saveBilling(const Billing* pBilling, const char* pPath)
{
	//以追加方式，二进制方式写入
	ofstream ofile(pPath, ios_base::out | ios_base::app | ios_base::binary);
	if (!ofile.is_open())
	{
		printf("文件无法正确打开！不能写入计费信息!\n");
		ofile.close();
		return FALSE;
	}
	//将计费信息保存到文件中
	ofile.write((const char *)pBilling, sizeof(Billing));

	//关闭文件
	ofile.close();
	printf("----*****-----计费信息成功存入文件!-----*****----\n");
	return TRUE;
}

//函数名:readBilling
//功能:读取计费信息
//参数:pBilling:计费信息结构体指针  pPath
//返回值:TRUE 读取成功  FALSE 读取失败
int readBilling(Billing* pBilling, const char* pPath)
{
	int nIndex = 0;

	//以二进制方式读取
	ifstream ifile(pPath, ios_base::in | ios_base::binary);
	if(!ifile.is_open())
	{
		printf("文件无法正确打开！不能读取计费信息!\n");
		ifile.close();
		return FALSE;
	}
	else
	{
		//遍历文件读取文件内容
		while (!ifile.eof())
		{
			if (!ifile.read((char*)(&pBilling[nIndex]), sizeof(Billing)))
				;
			else
			{
				nIndex++;
			}
				
		}
		//关闭文件
		ifile.close();
		return TRUE;
	}
}

//函数名:getBillingCount
//功能:获取文件中计费信息数量
//参数:计费信息文件路径
//返回值:计费信息数量
int getBillingCount(const char* pPath)
{
	int nCount = 0;
	Billing* pBilling = (Billing*)malloc(sizeof(Billing));
	//以二进制方式读取
	ifstream ifile(pPath, ios_base::in | ios_base::binary);
	if (!ifile.is_open())
	{    //遍历文件
		printf("文件无法正确打开！不能读取计费信息!\n");
		ifile.close();
		return FALSE;
	}
	else
	{
		while (!ifile.eof())
		{
			if (!ifile.read((char*)pBilling, sizeof(Billing)))
				;
			else
			{
				nCount++;
			}
		}
		//关闭文件
		ifile.close();
		free(pBilling);
		return nCount;
	}
}

//函数名:updateBilling
//功能:更新计费信息文件中的一条信息
//参数:pBilling:指向计费信息结构体；pPath:计费信息文件路径；nIndex:计费信息序号
//返回值:TREU:成功；FALSE:失败
int updateBilling(const Billing* pBilling, const char* pPath, int nIndex)
{
	int nCount = 0;
	long lPosition = 0;
	Billing pbBuf;

	//以读写模式，二进制模式打开文件，如果失败返回FALSE
	fstream iofile(pPath, ios_base::out | ios_base::in | ios_base::binary);
	if (!iofile.is_open())
	{
		printf("文件无法正确打开！不能更新消费信息！\n");
		iofile.close();
		return FALSE;
	}
	//遍历文件，获取消费信息在文件中的位置
	while ((!iofile.eof()) && (nCount < nIndex))
	{
		if (!iofile.read((char*)(&pbBuf), sizeof(Billing)))
			;
		else
		{
			//获取文件标识位置，最后一次找到的位置
			lPosition = (long)iofile.tellg();
		}
		nCount++;
	}
	//移动到文件标识位置
	//注意指针是在该条消费之后还是之前！！！
	//上面得到的读写指针在下一条信息开头，要移动到本条信息开头处
	iofile.seekp((__int64)lPosition - sizeof(Billing), ios_base::beg);
	//更新消费信息到文件
	iofile.write((const char*)(pBilling), sizeof(Billing));
	printf("----*****----消费信息更新到文件成功！----*****----\n");
	//关闭文件
	iofile.close();
	return TRUE;
}