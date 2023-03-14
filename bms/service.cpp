#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "model.h"
#include "global.h"
#include "card_file.h"
#include "card_service.h"
#include "billing_file.h"
#include "billing_service.h"
#include "service.h"
#include "money_file.h"

// ������:addCardInfo
// ����:��ӿ���Ϣ
// ����:card ����Ϣ�ṹ��
// ����ֵ:TRUE ����ɹ���FALSE ����ʧ��
int addCardInfo(Card card)
{
	// ������Ϣ���浽�ļ���
	if (TRUE == saveCard(&card, CARDPATH))
	{
		return TRUE;
	}
	return FALSE;
}

// ������:queryCardInfo
// ����:ģ����ѯ����Ϣ
// ����:pName:ָ���û������Ҫ��ѯ�Ŀ��ţ�pIndex:ָ���ѯ���Ŀ���Ϣ������
// ����ֵ:ָ����Ϣ�ṹ���ָ��
Card *queryCardInfo(const char *pName)
{
	Card *pCard = NULL;
	pCard = queryCard(pName);
	return pCard;
}

// ������:queryCardsInfo
// ����:ģ����ѯ����Ϣ
// ����:pName:ָ���û������Ҫ��ѯ�Ŀ���
//				pIndex:ָ���ѯ���Ŀ���Ϣ������
// ����ֵ:ָ����Ϣ�ṹ��ָ��
Card *queryCardsInfo(const char *pName, int *pIndex)
{
	Card *pCard = NULL;
	pCard = queryCards(pName, pIndex);
	return pCard;
}

// ������:doLogon
// ����:���ļ��ж�ȡ����Ϣ�������������в�ѯ����Ϣ,����ȡ���������е�λ��
// ����:pName:�ϻ����ţ�pPwd:�ϻ����� pInfo:ָ���ϻ��ṹ��
// ����ֵ:TRUE :�ϻ��ɹ� FALSE:�ϻ�ʧ��
int doLogon(const char *pName, const char *pPwd, LogonInfo *pInfo)
{
	Card *pCard = NULL;
	int nIndex = 0;	 // ����Ϣ�������е����������ڸ��¿���Ϣ
	Billing billing; // �Ʒ���Ϣ

	// ���ݿ��ź����룬�������л�ȡ����Ϣ�Ϳ���Ϣ�������е�����
	pCard = checkCard(pName, pPwd, &nIndex);

	// �������ϢΪ�գ���ʾû�иÿ���Ϣ���ϻ�ʧ��
	if (pCard == NULL)
	{
		return FALSE;
	}

	switch (pCard->nStatus)
	{
	case 1:
	{
		// �����״̬Ϊ1����ʾ�ÿ������ϻ�
		printf("�ÿ������ϻ���\n");
		return UNUSE;
		break;
	}
	case 2:
	{
		// ��״̬Ϊ2����ʾ�ÿ��Ѿ�ע��
		printf("�ÿ��Ѿ�ע����\n");
		return UNUSE;
		break;
	}
	case 3:
	{
		// �����״̬Ϊ3����ʾ���Ѿ�ʧЧ
		printf("�ÿ��Ѿ�ע����\n");
		return UNUSE;
		break;
	}
	default:
	{
		break;
	}
	}
	/*//�����״̬��Ϊ�㣬��ʾ�ÿ������ϻ�
	if (pCard->nStatus == 1)
	{
		printf("�ÿ������ϻ���\n");
		return UNUSE;
	}
	//��״̬Ϊ2����ʾ�ÿ��Ѿ�ע��
	if (pCard->nStatus == 2)
	{
		printf("�ÿ��Ѿ�ע����\n");
		return UNUSE;
	}
	//�����״̬Ϊ3����ʾ���Ѿ�ʧЧ
	if (pCard->nStatus == 3)
	{
		printf("�ÿ��Ѿ�ʧЧ��\n");
		return UNUSE;
	}*/
	// ������������ϻ�
	if (pCard->fBalance <= 0)
	{
		printf("���㣬���ֵ�����ϻ���\n");
		return ENOUGHMONEY;
	}

	// ��������ϻ������¿���Ϣ
	pCard->nStatus = 1;			   // ״̬Ϊ����ʹ��
	pCard->nUseCount++;			   // ʹ�ô�����1
	pCard->tLastTime = time(NULL); // �������ʹ��ʱ��Ϊ��ǰʱ��

	// �����ļ��еĿ���Ϣ
	if (FALSE == updateCard(pCard, CARDPATH, nIndex))
	{
		// �ļ�����ʧ�ܷ��أ����³ɹ��ż���������Ѽ�¼
		return FALSE;
	}
	// ������Ѽ�¼
	strcpy(billing.aCardName, pName); // �ϻ�����
	billing.tStart = time(NULL);	  // �ϻ�ʱ��
	billing.tEnd = 0;				  // �»�ʱ��
	billing.nStatus = 0;			  // ����״̬
	billing.fAmount = 0;			  // ���ѽ��
	billing.nDel = 0;				  // ɾ����ʶ

	// �Ƚ��Ʒ���Ϣ���浽�ļ���
	if (TRUE == saveBilling(&billing, BILLINGPATH))
	{
		// ��װ�ϻ���Ϣ
		strcpy(pInfo->aCardName, pName);
		pInfo->fBalance = pCard->fBalance;
		pInfo->tLogon = billing.tStart;
		return TRUE;
	}
	return FALSE;
}

// ������:releaseList
// ����:�˳�Ӧ�ó����ͷ������ڴ�
// ����:void
// ����ֵ:void
void releaseList()
{
	releaseCardList();	  // �ͷſ���Ϣ�����ڴ�
	releaseBillingList(); // �ͷżƷ���Ϣ�����ڴ�
}

// ������:doSettle
// ����:�����»�����
// ����:pName:�»����ţ�pPwd:�»����룻pInfo:ָ���»���Ϣ�ṹ��
// ����ֵ:�»���Ϣֵ����ͬ����������ͬ��Ϣ
int doSettle(const char *pName, const char *pPwd, SettleInfo *pInfo)
{
	Card *pCard = NULL;
	Billing *pBilling = NULL;
	int nIndex = 0;		   // ����Ϣ�������е�������
	int nPosition = 0;	   // �Ʒ���Ϣ�������е�������
	double dbAmount = 0.0; // ���ѽ��
	float fBalance = 0.0;  // ���

	// ��ѯ�ϻ���
	pCard = checkCard(pName, pPwd, &nIndex);

	// ���Ϊ�գ���ʾû�иÿ���Ϣ����FALSE
	if (pCard == NULL)
	{
		printf("�޸ÿ���Ϣ�����������룡\n");
		return FALSE;
	}
	switch (pCard->nStatus)
	{
	case 0:
	{
		// �����״̬Ϊ0����ʾ�ÿ�δ�ϻ������»�
		printf("�ÿ�δ���ϻ���\n");
		return UNUSE;
		break;
	}
	case 2:
	{
		// ��״̬Ϊ2����ʾ�ÿ��Ѿ�ע��
		printf("�ÿ��Ѿ�ע����\n");
		return UNUSE;
		break;
	}
	case 3:
	{
		// �����״̬Ϊ3����ʾ���Ѿ�ʧЧ
		printf("�ÿ��Ѿ�ע����\n");
		return UNUSE;
		break;
	}
	default:
	{
		break;
	}
	}
	/*//�жϸÿ��Ƿ������ϻ���ֻ�������ϻ��Ŀ����ܽ����»�����
	if (pCard->nStatus == 0)
	{
		printf("�ÿ�δ�ϻ���\n");
		return UNUSE;
	}
	if(pCard->nStatus == 2)
	{
		printf("�ÿ��Ѿ�ע����\n");
		return UNUSE;
	}
	if (pCard->nStatus == 3)
	{
		printf("�ÿ��Ѿ�ʧЧ��\n");
		return UNUSE;
	}*/

	// ���ݿ��Ų�ѯ�Ʒ���Ϣ
	pBilling = queryBilling(pName, &nPosition);

	// �����ѯ�Ʒ���ϢΪ�գ���ʾ�»�ʧ��
	if (pBilling == NULL)
	{
		printf("�޸ÿ���Ϣ�����������룡\n");
		return FALSE;
	}
	// �������ѽ��
	dbAmount = getAmount(pBilling->tStart);

	// ������С�����ѽ����ܽ����»�
	fBalance = pCard->fBalance - (float)dbAmount;
	if (fBalance < 0)
	{
		return ENOUGHMONEY;
	}

	// ���¿���Ϣ
	pCard->fBalance = fBalance;	   // ���
	pCard->nStatus = 0;			   // ״̬
	pCard->tLastTime = time(NULL); // �ϴ�ʹ��ʱ��

	// �����ļ��еĿ���Ϣ
	if (FALSE == updateCard(pCard, CARDPATH, nIndex))
	{
		return FALSE;
	}
	// ���¼Ʒ���Ϣ
	pBilling->fAmount = (float)dbAmount; // ������Ϣ
	pBilling->nStatus = 1;				 // ״̬�ѽ���
	pBilling->tEnd = time(NULL);		 // �»�ʱ��

	// �����ļ��еļƷ���Ϣ
	if (FALSE == updateBilling(pBilling, BILLINGPATH, nPosition))
	{
		return FALSE;
	}
	// ��װ�»���Ϣ
	strcpy(pInfo->aCardName, pName);  // ����
	pInfo->fAmount = (float)dbAmount; // ���ѽ��
	pInfo->fBalance = fBalance;		  // ���
	pInfo->tStart = pBilling->tStart; // �ϻ�ʱ��
	pInfo->tEnd = time(NULL);		  // �»�ʱ��

	return TRUE;
}

// ������:getAmount
// ����:�����ϻ�ʱ��������ѽ��
// ����:�ϻ�ʱ��
// ����ֵ:���ѽ��
double getAmount(time_t tStart)
{
	double dbAmount = 0;	  // ���ѽ��
	int nCount = 0;			  // �ϻ���ʱ�䵥Ԫ����ÿ����Ԫ15����
	int nSec = 0;			  // ����ʱ�䣨��λ���룩
	int nMinutes = 0;		  // ����ʱ�䣨��λ�����ӣ�
	time_t tEnd = time(NULL); // ����ʱ��Ϊ��ǰʱ��

	// ��������ʱ��
	nSec = (int)(tEnd - tStart);
	nMinutes = nSec / 60;
	// �������ѵ�ʱ�䵥Ԫ��
	if (nMinutes % UNIT == 0)
	{
		nCount = nMinutes / UNIT; // ����
	}
	else
	{
		nCount = nMinutes / UNIT + 1; // ������
	}
	// �������ѽ��
	dbAmount = nCount * CHARGE;
	return dbAmount;
}

// ������:doAddMoney
// ����:���г�ֵ����
// ����:pName:��ֵ���Ŀ��ţ�pPwd:��ֵ�������룻pMoneyInfo:��ֵ��Ϣ
// ����ֵ:��ֵ�����TRUE:��ֵ�ɹ�;FALSE����ֵʧ��
int doAddMoney(const char *pName, const char *pPwd, MoneyInfo *pMoneyInfo)
{
	Card *pCard = NULL;
	int nIndex = 0; // ����Ϣ�������е�������
	Money sMoney;
	// ��ѯ����ֵ
	pCard = checkCard(pName, pPwd, &nIndex);

	// �������ϢΪ�գ���ʾû�иÿ���Ϣ����ֵʧ��
	if (pCard == NULL)
	{
		printf("�޸ÿ���Ϣ�����ܳ�ֵ��\n");
		return FALSE;
	}
	// �жϸÿ��Ƿ�δʹ�û������ϻ���ֻ��δʹ�ú������ϻ��Ŀ����ܽ��г�ֵ����
	if (pCard->nStatus != 0 && pCard->nStatus != 1)
	{
		return FALSE;
	}
	// ������Գ�ֵ�����¿���Ϣ
	pCard->fBalance += pMoneyInfo->fMoney;
	pCard->fTotalUse += pMoneyInfo->fMoney;

	// �����ļ��еĿ���Ϣ�ļ�
	if (FALSE == updateCard(pCard, CARDPATH, nIndex))
	{
		return FALSE;
	}
	// ��װ��ֵ��Ϣ
	strcpy(sMoney.aCardName, pCard->aName);
	sMoney.tTime = time(NULL);
	sMoney.nStatus = 0;
	sMoney.fMoney = pMoneyInfo->fMoney;
	sMoney.nDel = 0;

	// ����ֵ��¼���浽�ļ���
	if (TRUE == saveMoney(&sMoney, MONEYPATH))
	{
		// ��װ������ʾ�ĳ�ֵ��Ϣ
		strcpy(pMoneyInfo->aCardName, sMoney.aCardName);
		pMoneyInfo->fBalance = pCard->fBalance;

		return TRUE;
	}
	return FALSE;
}

// ������:doRefundMoney
// ����:�����˷Ѳ���
// ����:pName:�˷ѿ��Ŀ��ţ�pPwd:�˷ѿ������룻pMoneyInfo:��ֵ�˷���Ϣ�ṹ��
// ����ֵ:��ֵ�����TRUE:��ֵ�ɹ�;FALSE����ֵʧ��
int doRefundMoney(const char *pName, const char *pPwd, MoneyInfo *pMoneyInfo)
{
	Card *pCard = NULL;
	int nIndex = 0;		  // ����Ϣ�������е�������
	float fBalance = 0.0; // �������
	Money sMoney;

	// ��ѯ�˷ѿ�
	pCard = checkCard(pName, pPwd, &nIndex);

	// ���Ϊ�գ���ʾû�иÿ���Ϣ������FALSE
	if (pCard == NULL)
	{
		printf("�޸ÿ���Ϣ�������˷ѣ�\n");
		return FALSE;
	}

	// �жϸÿ��Ƿ�δʹ�ã�ֻ��δʹ�õĿ����ܽ����˷Ѳ���
	if (pCard->nStatus != 0)
	{
		return UNUSE;
	}

	// ������С�ڵ����㣬���ܽ����˷�
	fBalance = pCard->fBalance;
	if (fBalance <= 0)
	{
		return ENOUGHMONEY;
	}

	// ���¿���Ϣ
	pCard->fBalance = 0;		  // ���
	pCard->fTotalUse -= fBalance; // �ۼƽ��

	// �����ļ��еĿ���Ϣ
	if (FALSE == updateCard(pCard, CARDPATH, nIndex))
	{
		return FALSE;
	}

	// ����˷���Ϣ
	strcpy(sMoney.aCardName, pCard->aName);
	sMoney.tTime = time(NULL);
	sMoney.nStatus = 1;
	sMoney.fMoney = fBalance;
	sMoney.nDel = 0;

	// �����ļ��еĳ�ֵ�˷���Ϣ
	if (TRUE == saveMoney(&sMoney, MONEYPATH))
	{
		// ��װ�˷���Ϣ
		strcpy(pMoneyInfo->aCardName, sMoney.aCardName);
		pMoneyInfo->fMoney = sMoney.fMoney;
		pMoneyInfo->fBalance = pCard->fBalance;

		return TRUE;
	}
	return FALSE;
}

// ������:annulCard
// ����:ע����
// ����:pCard
// ����ֵ:TRUE ע���ɹ���FALSE ע��ʧ��
int annulCard(Card *pCard)
{
	Card *pCurCard = NULL;
	int nIndex = -1; // ����Ϣ�������е�����

	if (pCard == NULL)
	{
		return FALSE;
	}
	// ���ݿ��ź����룬��ѯ����Ϣ
	pCurCard = checkCard(pCard->aName, pCard->aPwd, &nIndex);

	if (pCurCard == NULL)
	{
		return FALSE;
	}
	// ֻ��δ�ϻ��Ŀ�����ע��
	if (pCurCard->nStatus != 0)
	{
		return FALSE;
	}
	// ����ע���������
	pCard->fBalance = pCurCard->fBalance;

	// ����ע������Ϣ
	pCurCard->nStatus = 2;			  // ״̬δ��ע��
	pCurCard->nDel = 1;				  // ɾ����ʶΪ��ɾ��
	pCurCard->fBalance = 0;			  // �����Ϊ0
	pCurCard->tLastTime = time(NULL); // ���ʹ��ʱ��Ϊ��ǰʱ��

	// ���¿����ļ��е���Ϣ
	if (FALSE == updateCard(pCurCard, CARDPATH, nIndex))
	{
		return FALSE;
	}
	return TRUE;
}