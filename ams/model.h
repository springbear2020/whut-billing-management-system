#pragma once
#include<time.h>
typedef struct Card
{
	char aName[18];//卡号
	char aPwd[8];//密码
	int nStatus;//卡状态（0-未上机；1-正在上机；2-已注销；3-失效）
	time_t tStart;//开卡时间
	time_t tEnd;//卡的截止时间
	float fTotalUse;//累计金额
	time_t tLastTime;//最后使用时间
	int nUseCount;//使用次数
	float fBalance;//余额
	int nDel;//删除标识（0-未删除；1-删除）
}Card;