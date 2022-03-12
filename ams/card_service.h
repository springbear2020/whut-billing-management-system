#pragma once
#include"model.h"
//函数声明
int addCard(Card crd);//添加卡信息到结构体数组
Card* queryCard(const char* pName);//在结构体数组中查询指定卡号的信息
int getCard();//从卡信息文件中，获取卡信息
int initCardList();//初始化卡信息链表
void releaseCardList();//释放卡信息链表
Card* queryCards(const char* pName, int* pIndex);//在卡信息链表中，模糊查询包含的所有卡信息
Card* checkCard(const char* pName, const char* pPwd, int* pIndex);//从文件中读取卡信息到链表，在链表中查询卡信息,并获取其在链表中的位置