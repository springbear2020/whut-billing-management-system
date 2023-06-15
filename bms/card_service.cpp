#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "model.h"
#include "global.h"
#include "card_file.h"
#include "card_service.h"
#include "billing_service.h"

lpCardNode cardList = NULL; // ����Ϣ�������ͱ���

// ������:addCard
// ����:��ӿ���Ϣ���ṹ������
// ����:����Ϣ�ṹ��
// ����ֵ:����1����ӳɹ�������0��������ӣ�
int addCard(Card crd)
{
	// ����Ϣ���浽�ļ���
	if (TRUE == saveCard(&crd, CARDPATH))
	{
		return TRUE;
	}
	return FALSE;
}

// ������:queryCard
// ����:�ڽṹ�������в�ѯָ�����ŵ���Ϣ
// ����:�û������Ҫ��ѯ�Ŀ��ŵ�ַ
// ����ֵ:�ṹ�������в�ѯ���Ŀ���Ϣ��ַ��û���ҵ�����NULL
Card *queryCard(const char *pName)
{
	Card *pCard = NULL;
	lpCardNode p; // ���ڲ����е�����һ��ָ�������е�ÿ���ڵ�

	// �ӿ���Ϣ�ļ��ж�ȡ����Ϣ������ʧ�ܷ���NULL
	if (FALSE == getCard())
	{
		return NULL;
	}
	// ָ������ͷ�ڵ㣬���ڵ���
	p = cardList;
	// �������в���ָ������
	while (p != NULL)
	{
		if (strcmp(p->data.aName, pName) == 0)
		{
			pCard = &(p->data);
			return pCard;
		}
		else
		{
			p = p->next;
		}
	}
	// û���ҵ�������NULL
	return pCard;
}

// ������:getCard
// ����:�ӿ���Ϣ�ļ��У���ȡ����Ϣ
// ����:void
// ����ֵ:��ȡ�ɹ�����TRUE,���򷵻�FALSE
int getCard()
{
	int i = 0;
	Card *pCard = NULL;		// ��ȡ����һ������Ϣ
	int nCount = 0;			// ʵ�ʿ���Ϣ��
	lpCardNode node = NULL; // ��ǰβ�ڵ�
	lpCardNode cur = NULL;	// ��ӵ������еĽڵ�

	// ����������Ѿ����ڵ�����
	if (cardList != NULL)
	{
		releaseCardList();
	}
	// ��ʼ������
	initCardList();

	// ��ȡ�ļ��п���Ϣ��
	nCount = getCardCount(CARDPATH);

	if (nCount == 0)
	{
		return FALSE;
	}
	else if (nCount == -1)
	{
		printf("�ļ��޷��򿪣�\n");
		return FALSE;
	}
	// ��̬�����ڴ������������п���Ϣ���൱�ڽṹ�����飬pCard�൱��������
	pCard = (Card *)malloc(sizeof(Card) * nCount);
	if (pCard != NULL)
	{
		// �������FALSE�����ȡ����Ϣʧ��
		if (0 == readCard(pCard, CARDPATH))
		{
			free(pCard);
			return FALSE;
		}
		// ����ȡ�Ŀ���Ϣ�����浽������
		for (i = 0, node = cardList; i < nCount; i++)
		{
			// Ϊ�ڵ�����ڴ�
			cur = (lpCardNode)malloc(sizeof(CardNode));
			// �������ʧ�ܣ��򷵻�FALSE
			if (cur == NULL)
			{
				free(pCard);
				return FALSE;
			}
			// ��ʼ���µ��ڴ�ռ䣬ȫ����ֵΪ0
			memset(cur, 0, sizeof(CardNode));

			// ������Ϣ���浽�ڵ���
			cur->data = pCard[i];
			cur->next = NULL;

			// ���ڵ���ӵ������β��
			if (node != NULL)
			{
				node->next = cur;
				node = cur;
			}
		}
		// �ͷ��ڴ�
		free(pCard);
		return TRUE;
	}
	return FALSE;
}

// ������:initCardList()
// ����:��ʼ������Ϣ����
// ����:void
// ����ֵ:int�ͣ�TRUE��ʾ�ɹ���FALSE��ʾʧ��
int initCardList()
{
	lpCardNode head = NULL;
	if (cardList == NULL)
	{
		// Ϊ����ͷ�ڵ�����ڴ�
		head = (lpCardNode)malloc(sizeof(CardNode));

		// �������ɹ�
		if (head != NULL)
		{
			head->next = NULL;
			cardList = head;
			return TRUE;
		}
	}
	return FALSE;
}

// ������:releaseCardList
// ����:�ͷſ���Ϣ����
// ����:void
// ����ֵ:void
void releaseCardList()
{
	lpCardNode cur = cardList;
	lpCardNode next = NULL;

	while (cur != NULL)
	{
		next = cur->next; // �ͷŽڵ�ǰ��next�������ĺ�̽ڵ�
		free(cur);		  // �ͷ�cur�ڵ�
		cur = next;
	}
	cardList = NULL;
}

// ������:queryCards
// ����:�ڿ���Ϣ�����У�ģ����ѯ���������п���Ϣ
// ����:pName:ָ���û���Ҫ��ѯ�Ŀ��ţ�pIndex��ָ���ѯ���Ŀ���Ϣ����
// ����ֵ:ָ����Ϣ�ṹ���ָ��
Card *queryCards(const char *pName, int *pIndex)
{
	lpCardNode node = NULL;
	Card *pCard = NULL; // �����ѯ���ķ��������Ŀ���Ϣ
	Card *x = NULL;

	// �ӿ���Ϣ�ļ��ж�ȡ����Ϣ������ʧ�ܷ���NULL
	if (FALSE == getCard())
	{
		return NULL;
	}

	// ���ȷ���һ��Card��С���ڴ�ռ�
	pCard = (Card *)malloc(sizeof(Card));
	if (pCard == NULL)
	{
		return NULL;
	}

	// �������ͷ�ڵ�ָ�����һ����㿪ʼ����
	node = cardList->next;

	// ���������ڵ�Ϊ�ձ�ʾ��������β��
	while (node != NULL)
	{
		// �ж��ڱ��������Ŀ����У������Ƿ����Ҫ���ҵ��ַ���
		if (strstr(node->data.aName, pName) != NULL)
		{
			// ������򱣴��������
			pCard[*pIndex] = node->data;
			(*pIndex)++;

			// ����Ϊָ������ڴ棬�������е�����
			x = (Card *)realloc(pCard, ((*pIndex) + 1) * sizeof(Card));
			if (x != NULL)
			{
				pCard = x;
			}
		}

		// �ƶ����������һ�����
		node = node->next;
	}
	return pCard;
}

// ������:checkCard
// ����:���ļ��ж�ȡ����Ϣ�������������в�ѯ����Ϣ,����ȡ���������е�λ��
// ����:pName:�ϻ����ţ�pPwd:�ϻ�����  pIndex:���ؿ���������
// ����ֵ:�ϻ����ṹ��
Card *checkCard(const char *pName, const char *pPwd, int *pIndex)
{
	lpCardNode cardNode = NULL; // ��ǰ�ڵ�
	int nIndex = 0;				// �ϻ����ڿ���Ϣ�����е�������
	// Billing* pBilling = NULL;

	// ������ļ��л�ȡ����Ϣʧ�ܣ����ϻ�ʧ��
	if (FALSE == getCard())
	{
		return FALSE;
	}
	// ָ������
	cardNode = cardList;
	// ��������
	while (cardNode != NULL)
	{
		// �����ϻ������жϿ��ź������Ƿ���ȷ
		if ((strcmp(cardNode->data.aName, pName) == 0) && (strcmp(cardNode->data.aPwd, pPwd) == 0))
		{
			// ���ؿ���Ϣ�ڵ����ݵĵ�ַ
			*pIndex = nIndex;
			return &cardNode->data;
		}
		cardNode = cardNode->next;
		nIndex++;
	}
	return NULL;
}
