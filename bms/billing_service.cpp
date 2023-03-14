#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "model.h"
#include "global.h"
#include "billing_file.h"

lpBillingNode billingList = NULL;

// ������:addBilling
// ����:�ϻ�ʱ���������Ϣ���ļ�
// ����:pName:�ϻ����ţ�pBilling:ָ��������Ϣ�ṹ��
// ����ֵ:TRUE������ɹ���FALSE:����ʧ��
int addBilling(const char *pName, Billing *pBilling)
{
	// ��������Ϣд��ṹ��
	strcpy(pBilling->aCardName, pName); // �ϻ�����
	pBilling->tStart = time(NULL);		// �ϻ�ʱ��
	pBilling->tEnd = 0;					// �»�ʱ��
	pBilling->fAmount = 0;				// ���ѽ��
	pBilling->nStatus = 0;				// ����״̬ 0-δ���㣻1-�ѽ���
	pBilling->nDel = 0;					// ɾ����ʶ��0-δɾ����1-��ɾ��

	if (FALSE == saveBilling(pBilling, BILLINGPATH))
	{
		return FALSE;
	}
	return TRUE;
}

// ������:initBillingList
// ����:��ʼ���Ʒ���Ϣ����
// ����:void
// ����ֵ:void
void initBillingList()
{
	lpBillingNode head = NULL;
	if (billingList == NULL)
	{
		head = (lpBillingNode)malloc(sizeof(BillingNode));
		if (head == NULL)
		{
			exit(1);
		}
		head->next = NULL;
		billingList = head;
	}
}

// ������:releaseBillingList
// ����:�ͷżƷ���Ϣ����
// ����:void
// ����ֵ:void
void releaseBillingList()
{
	lpBillingNode cur = billingList;
	lpBillingNode next = NULL;
	// ��������
	while (cur != NULL)
	{
		next = cur->next; // �ڵ��ڴ��ͷţ�next��������
		free(cur);		  // �ͷŽڵ��ڴ�
		cur = next;
	}
	billingList = NULL;
}

// ������:getBilling
// ����:�ӼƷ��ļ��У���ȡ�Ʒ���Ϣ���浽������
// ����:void
// ����ֵ:TRUE����ȡ��Ϣ�ɹ���FALSE:��ȡ��Ϣʧ��
int getBilling()
{
	int nCount = 0; // �Ʒ���Ϣ����
	Billing *pBilling = NULL;
	lpBillingNode node = NULL;
	int i = 0; // ѭ������
	lpBillingNode cur = NULL;

	// �����ʼ����Ϊ�գ��ͷ�����
	if (billingList != NULL)
	{
		releaseBillingList();
	}
	// ��ʼ������
	initBillingList();

	// ��ȡ�Ʒ���Ϣ����
	nCount = getBillingCount(BILLINGPATH);
	// ��̬�����ڴ�
	pBilling = (Billing *)malloc(sizeof(Billing) * nCount);
	if (pBilling == 0)
	{
		exit(1);
	}
	if (pBilling != NULL)
	{
		// ��ȡ�Ʒ���Ϣ
		if (FALSE == readBilling(pBilling, BILLINGPATH))
		{
			free(pBilling);
			return FALSE;
		}
		// ���Ʒ���Ϣ���浽������
		for (i = 0, node = billingList; i < nCount; i++)
		{
			// Ϊ��ǰ�ڵ�����ڴ�
			cur = (lpBillingNode)malloc(sizeof(BillingNode));

			// �������ʧ�����ڷ���FALSEǰ����Ҫ�ͷ�pBilling�ڴ�
			if (cur == NULL)
			{
				free(pBilling);
				return FALSE;
			}
			// ��ʼ���µĿռ䣬ȫ������Ϊ��
			memset(cur, 0, sizeof(BillingNode));
			// ��������ӵ��ڵ���
			cur->data = pBilling[i];
			cur->next = NULL;
			// ���ڵ���ӵ�������
			if (node == 0)
			{
				exit(1);
			}
			node->next = cur;
			node = cur;
		}
		free(pBilling);
		return TRUE;
	}
	return FALSE;
}

// ������:queryBilling
// ����:�ڼƷ���Ϣ�����У���ѯ��Ӧ���ļƷ���Ϣ������ȡ���������е�������
// ����:pName:Ҫ��ѯ�ļƷ���Ϣ�Ŀ��ţ�pIndex:Ҫ��ѯ�ļƷ���Ϣ�������е�������
// ����ֵ:��ѯ���ļƷ���Ϣָ��
Billing *queryBilling(const char *pName, int *pIndex)
{
	lpBillingNode node = NULL;
	int nIndex = 0;
	if (FALSE == getBilling())
	{
		return NULL;
	}
	// ��������
	node = billingList;
	while (node != NULL)
	{
		// ��ѯ���Ŀ�����ͬ������û�н���ļƷ���Ϣ
		if (strcmp(node->data.aCardName, pName) == 0 && node->data.nStatus == 0)
		{
			return &node->data;
		}
		node = node->next;
		nIndex++;
		*pIndex = nIndex;
	}
	return NULL;
}
