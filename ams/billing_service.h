#pragma once
#include"model.h"
//函数声明
int addBilling(const char* pName, Billing* pBilling);//上机时添加消费信息到文件
void initBillingList();//初始化计费信息链表
void releaseBillingList();//释放计费信息链表
int getBilling();//从计费信息文件中，获取计费信息保存到链表中
Billing* queryBilling(const char* pName, int* pIndex);//在计费信息链表中，查询对应卡的计费信息，并获取其在链表中的索引号

