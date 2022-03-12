#pragma once
#include"model.h"
//函数声明
int saveCard(const Card* pCard, const char* pPath); //将卡信息保存到文件中
int readCard(Card* pCard, const char* pPath);//从文件中读取卡信息到结构体数组
Card praseCard(char* pBuf);//将一条卡信息字符串解析后放入一个卡结构体
int getCardCount(const char* pPath);//获取卡信息文件中卡信息数量