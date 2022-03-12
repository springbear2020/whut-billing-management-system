#pragma once
#include"model.h"
//函数声明
int addCardInfo(Card card);//添加卡信息
Card* queryCardInfo(const char* pName);//精确查询卡信息
Card* queryCardsInfo(const char* pName, int* pIndex);//模糊查询卡信息
int doLogon(const char* pName, const char* pPwd, LogonInfo* pInfo);//进行上机操作
void releaseList();//退出应用程序时，释放链表内存
int doSettle(const char* pName, const char* pPwd, SettleInfo* pInfo);//进行下机操作
double getAmount(time_t tStart);//根据上机时间，计算消费金额