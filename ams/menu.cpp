#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

#include<string.h>
#include<time.h>

#include"model.h"
#include"menu.h"
#include"card_sevice.h"
#include"global.h"
#include"tool.h"

//函数名：outputMenu
//功能：输出系统菜单
//参数：void
//返回值：void
void outputMenu() 
{   //输出系统菜单
	printf("------计费系统菜单------\n");
	printf("*                      *\n");
	printf("*       1.添加卡       *\n");
	printf("*       2.查询卡       *\n");
	printf("*       3.上机         *\n");
	printf("*       4.下机         *\n");
	printf("*       5.充值         *\n");
	printf("*       6.退费         *\n");
	printf("*       7.查询统计     *\n");
	printf("*       8.注销卡       *\n");
	printf("*       0.退出         *\n");
	printf("------------------------\n\n");
}

//函数名：add
//功能：添加用户信息到卡结构体变量，并屏幕显示
//参数：void
//返回值：void
void add()
{
	Card card;
	char name[30];//临时存放输入的用户名
	char pwd[20];//临时存放输入的密码
	struct tm* endTime;//临时存放截止时间
	struct tm* startTime;//临时存放开卡时间

	printf("请输入卡号(长度为1~18):");
	scanf("%s", &name);
	if (getSize(name) >= 18) //判断输入的卡号长度是否符合要求
		printf("输入的卡号长度超过最大值");
	//判断输入的卡号是否存在
	if (queryCard(name) != NULL)
	{
		printf("输入的卡号已存在！请重新输入！\n\n");
		return;
	}
	strcpy_s(card.aName, name);//将输入的卡号保存到卡结构体变量中

	printf("请输入密码(长度为1~8):");
	scanf("%s", &pwd);
	if (getSize(pwd) >= 8)//判断输入的密码长度是否符合要求
		printf("输入的密码长度超过最大值！");
	strcpy_s(card.aPwd, pwd);//将输入的密码保存到卡结构体中

	printf("请输入开卡金额（RMB):");
	scanf("%f", &card.fBalance);

	card.fTotalUse = card.fBalance;//添加卡时，累计金额等于开卡金额
	card.nDel = 0;//删除标识
	card.nStatus = 0;//卡状态
	card.nUseCount = 0;//使用次数
	//开卡时间，截止时间，最后使用时间都默认为当前时间
	//time（NULL）获取当前绝对时间（日历时间），1970-01-01 00;00；00 起到现在的秒数
	card.tStart = card.tEnd = card.tLastTime = time(NULL);

	//根据开卡时间，计算截止时间，每张卡的有效期为一年
	startTime = localtime(&card.tStart );//将日历时间转换为分解时间
	endTime = localtime(&card.tEnd);
	endTime->tm_year = startTime->tm_year + 1;
	card.tEnd = mktime(endTime);//将分解时间转换为日历时间

	//输出添加卡的信息
	printf("\n");
	printf("----------------添加的卡信息如下----------------\n");
	printf("\t卡号\t密码\t状态\t开卡金额\n");
	printf("\t%s\t%s\t%s\t%.2f\n", card.aName, card.aPwd, card.nStatus, card.fBalance);

	//卡信息添加到结构体数组中
	if (FALSE == addCard(card))
		printf("----******------添加卡信息失败！----******------\n\n");
	else
		printf("----******------添加卡信息成功！----******------\n\n");
}
//函数名：getSize
//功能：计算字符数组中字符长度
//参数：字符数组名
//返回值：字符个数
int getSize(const char* pString)
{
	int nSize = 0;

	//计算字符串的字符个数
	while (*(pString + nSize) != '\0')
		nSize++;

	//返回字符个数
	return nSize;
}

//函数名：query
//功能：根据输入的卡号，调用，查询是否有该卡，有的话，输出该卡信息
//参数：void
//返回值：void
void query()
{
	char name[18] = {0};//存放要查询的用户名
	Card* pCard = NULL;
	char aLastTime[30];//存放指定格式字符串的时间
//	struct tm* timeinfo;//临时存放从time_t转换过来的tm结构时间

	printf("请输入要查询的卡号(长度为1~18):");
	scanf("%s", &name);

	//从结构体数组中查找卡信息
	pCard = queryCard(name);

	//如果pCard为NULL，表示没有该卡信息
	if (pCard == NULL)
		printf("----******------没有该卡信息！------******----");
	else
	{
		printf("-------------******-------------查询到的卡信息如下-------------******-------------\n");
		//输出表格的表头
		printf("\t卡号\t状态\t余额\t累计金额\t使用次数\t上次使用时间\n");
		//将time_t类型时间转换为字符串，字符串格式为年-月-日 时：分
//		timeinfo = localtime(&(pCard->tLastTime));//time_t类型时间转换成tm结构时间
//		strftime(aLastTime, 20,"%Y-%m-%d %H:%M" , timeinfo);//tm结构时间输出为指定格式字符串
		timeToString(pCard->tLastTime, aLastTime);


		//输出查到的卡信息
		printf("\t%s\t%s\t%.2f\t%.2f\t\t%d\t\t%s\n", pCard->aName, pCard->nStatus, pCard->fBalance, pCard->fTotalUse, pCard->nUseCount, aLastTime);
		printf("----------------------------------------------------------------------------------\n");
	}
}