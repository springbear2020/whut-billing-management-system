#pragma once
#include <time.h>

typedef struct Card
{
	char aName[18];	  // 卡号
	char aPwd[8];	  // 密码
	int nStatus;	  // 卡状态 （0-未上机；1-正在上机；2-已注销；3-失效）
	time_t tStart;	  // 开卡时间
	time_t tEnd;	  // 卡的截止时间
	float fTotalUse;  // 累计金额
	time_t tLastTime; // 最后使用时间
	int nUseCount;	  // 使用次数
	float fBalance;	  // 余额
	int nDel;		  // 删除标识（0-未删除；1-删除）
} Card;

typedef struct CardNote
{
	Card data;			   // 节点数据区
	struct CardNote *next; // 指向下一个节点的指针
} CardNode, *lpCardNode;

// 消费信息结构体
typedef struct Billing
{
	char aCardName[18]; // 卡号
	time_t tStart;		// 上机时间
	time_t tEnd;		// 下机时间
	float fAmount;		// 消费金额
	int nStatus;		// 消费状态0-未结算；1-已经结算
	int nDel;			// 删除标识，0-未删除，1-已删除
} Billing;

// 上机信息结构体
typedef struct LogonIofo
{
	char aCardName[18]; // 上机卡号
	time_t tLogon;		// 上机时间
	float fBalance;		// 上机时卡余额
} LogonInfo;

// 计费信息节点
typedef struct BillingNode
{
	Billing data;
	struct BillingNode *next;
} BillingNode, *lpBillingNode;

// 下机信息结构体
typedef struct SettleInfo
{
	char aCardName[18]; // 卡号
	time_t tStart;		// 上机时间
	time_t tEnd;		// 下机时间
	float fAmount;		// 消费金额
	float fBalance;		// 余额
} SettleInfo;

// 充值退费结构体
typedef struct Money
{
	char aCardName[18]; // 卡号
	time_t tTime;		// 充值退费时间
	int nStatus;		// 状态 0-充值；1-退费
	float fMoney;		// 充值退费金额
	int nDel;			// 删除标识，0-未删除，1-删除
} Money;

// 充值退费信息结构体
typedef struct MoneyInfo
{
	char aCardName[18]; // 卡号
	float fMoney;		// 充值退费金额
	float fBalance;		// 余额
} MoneyInfo;