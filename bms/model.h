#pragma once
#include <time.h>

typedef struct Card
{
	char aName[18];	  // ����
	char aPwd[8];	  // ����
	int nStatus;	  // ��״̬ ��0-δ�ϻ���1-�����ϻ���2-��ע����3-ʧЧ��
	time_t tStart;	  // ����ʱ��
	time_t tEnd;	  // ���Ľ�ֹʱ��
	float fTotalUse;  // �ۼƽ��
	time_t tLastTime; // ���ʹ��ʱ��
	int nUseCount;	  // ʹ�ô���
	float fBalance;	  // ���
	int nDel;		  // ɾ����ʶ��0-δɾ����1-ɾ����
} Card;

typedef struct CardNote
{
	Card data;			   // �ڵ�������
	struct CardNote *next; // ָ����һ���ڵ��ָ��
} CardNode, *lpCardNode;

// ������Ϣ�ṹ��
typedef struct Billing
{
	char aCardName[18]; // ����
	time_t tStart;		// �ϻ�ʱ��
	time_t tEnd;		// �»�ʱ��
	float fAmount;		// ���ѽ��
	int nStatus;		// ����״̬0-δ���㣻1-�Ѿ�����
	int nDel;			// ɾ����ʶ��0-δɾ����1-��ɾ��
} Billing;

// �ϻ���Ϣ�ṹ��
typedef struct LogonIofo
{
	char aCardName[18]; // �ϻ�����
	time_t tLogon;		// �ϻ�ʱ��
	float fBalance;		// �ϻ�ʱ�����
} LogonInfo;

// �Ʒ���Ϣ�ڵ�
typedef struct BillingNode
{
	Billing data;
	struct BillingNode *next;
} BillingNode, *lpBillingNode;

// �»���Ϣ�ṹ��
typedef struct SettleInfo
{
	char aCardName[18]; // ����
	time_t tStart;		// �ϻ�ʱ��
	time_t tEnd;		// �»�ʱ��
	float fAmount;		// ���ѽ��
	float fBalance;		// ���
} SettleInfo;

// ��ֵ�˷ѽṹ��
typedef struct Money
{
	char aCardName[18]; // ����
	time_t tTime;		// ��ֵ�˷�ʱ��
	int nStatus;		// ״̬ 0-��ֵ��1-�˷�
	float fMoney;		// ��ֵ�˷ѽ��
	int nDel;			// ɾ����ʶ��0-δɾ����1-ɾ��
} Money;

// ��ֵ�˷���Ϣ�ṹ��
typedef struct MoneyInfo
{
	char aCardName[18]; // ����
	float fMoney;		// ��ֵ�˷ѽ��
	float fBalance;		// ���
} MoneyInfo;