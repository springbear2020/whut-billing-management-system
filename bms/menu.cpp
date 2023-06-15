#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "model.h"
#include "menu.h"
#include "card_service.h"
#include "global.h"
#include "tool.h"
#include "service.h"

using namespace std;

// ������:outputMenu
// ����:���ϵͳ�˵�
// ����:void
// ����ֵ:void
void outputMenu()
{ // ���ϵͳ�˵�
	printf("\n");
	printf("------�Ʒ�ϵͳ�˵�------\n");
	printf("*                      *\n");
	printf("*       1.��ӿ�       *\n");
	printf("*       2.��ѯ��       *\n");
	printf("*       3.�ϻ�         *\n");
	printf("*       4.�»�         *\n");
	printf("*       5.��ֵ         *\n");
	printf("*       6.�˷�         *\n");
	printf("*       7.��ѯͳ��     *\n");
	printf("*       8.ע����       *\n");
	printf("*       0.�˳�         *\n");
	printf("------------------------\n\n");
}

// ������:add
// ����:����û�����Ϣ�����ṹ�����������Ļ��ʾ
// ����:void
// ����ֵ:void
void add()
{
	Card card;
	char name[30];		  // ��ʱ���������û���
	char pwd[20];		  // ��ʱ������������
	struct tm *endTime;	  // ��ʱ��Ž�ֹ��ʱ��
	struct tm *startTime; // ��ʱ��ſ���ʱ��

	if ((endTime = (struct tm *)malloc(sizeof(struct tm))) == NULL)
	{
		exit(1);
	}
	if ((startTime = (struct tm *)malloc(sizeof(struct tm))) == NULL)
	{
		exit(1);
	}

	printf("�����뿨�ţ�����Ϊ1~18):");
	scanf("%s", name, 18);

	// �ж�������Ŀ��ų����Ƿ����Ҫ��
	if (getSize(name) >= 18)
	{
		printf("����Ŀ��ų��ȳ������ֵ!\n");
		return;
	}
	if (queryCardInfo(name) != NULL)
	{
		printf("����Ŀ����Ѿ����ڣ����������룡\n");
		return;
	}
	// ������Ŀ��ű��浽���ṹ�������
	strcpy_s(card.aName, name);

	printf("���������루����Ϊ1~8):");
	scanf("%s", pwd, 8);

	// �ж�����������Ƿ����Ҫ��
	if (getSize(pwd) >= 8)
	{
		printf("��������볤�ȳ������ֵ��\n");
		return;
	}
	// ����������뱣�浽���ṹ����
	strcpy_s(card.aPwd, pwd);

	printf("�����뿪����RMB)��");
	scanf("%f", &card.fBalance);

	printf("\n");

	card.fTotalUse = card.fBalance; // ��ӿ�ʱ���ۼƽ����ڿ������
	card.nDel = 0;					// ɾ����ʶ
	card.nStatus = 0;				// ��״̬
	card.nUseCount = 0;				// ʹ�ô���
	// ����ʱ�䣬�����ֹʱ�䣬���ʹ��ʱ�䶼Ĭ��Ϊ��ǰʱ��
	// time(NULL)��ȡ��ǰ����ʱ�䣨����ʱ�䣩��1970-01-01 00��00��00�����ڵ�����
	card.tStart = card.tEnd = card.tLastTime = time(NULL);

	// ���ݿ���ʱ������ֹʱ�䣬ÿ�ſ�����Ч��Ϊһ��
	localtime_s(startTime, &card.tStart); // ������ʱ��ת��Ϊ�ֽ�ʱ��
	localtime_s(endTime, &card.tEnd);
	endTime->tm_year = startTime->tm_year + 1;
	card.tEnd = mktime(endTime); // ���ֽ�ʱ��ת��Ϊ����ʱ��

	printf("----------------��ӵĿ�����Ϣ����----------------\n");
	printf("\t����\t����\t״̬\t�������\n");
	printf("\t%s\t%s\t%d\t%.2f\n", card.aName, card.aPwd, card.nStatus, card.fBalance);
	printf("--------------------------------------------------\n");

	// ����Ϣ����ļ���
	if (FALSE == addCardInfo(card))
	{
		printf("-----*****-----��ӿ���Ϣʧ�ܣ�-----*****-----\n");
	}
	else
	{
		printf("-----*****------��ӿ���Ϣ�ɹ���-----*****------\n\n");
	}
}

// ������:getSize
// ����:�����ַ��������ַ�����
// ����:�ַ�������
// ����ֵ:�ַ�����
int getSize(const char *pString)
{
	int nSize = 0;
	// �����ַ������ַ�����
	while (*(pString + nSize) != '\0')
	{
		nSize++;
	}
	// �����ַ�����
	return nSize;
}

// ������:query
// ����:��������Ŀ��ŵ��ã���ѯ�Ƿ��иÿ����еĻ����������Ϣ
// ����:void
// ����ֵ:void
void query()
{
	char name[18]; // ���Ҫ��ѯ���û���
	Card *pCard = NULL;
	char aLastTime[30]; // ���ָ����ʽ�ַ�����ʱ��
	int icha = 0;
	int nIndex = 0;
	int i; // ��ѯ������Ϣ����

	printf("������Ҫ��ѯ�Ŀ���(����1~18):");
	scanf("%s", name, 18);

	printf("1.��ȷ��ѯ||2.ģ����ѯ(����1��2����");
	scanf("%d", &icha);

	if (icha == 1)
	{
		pCard = queryCardInfo(name);
	}
	else if (icha == 2)
	{
		pCard = queryCardsInfo(name, &nIndex);
	}
	else
	{
		do
		{
			printf("�������\n���������룺");
			scanf("%d", &icha);
		} while (icha != 1 && icha != 2);
		if (icha == 1)
		{
			pCard = queryCard(name);
		}
		else if (icha == 2)
		{
			pCard = queryCards(name, &nIndex);
		}
	}

	if (pCard == NULL)
	{
		printf("----*****-----û�иÿ�����Ϣ��-----*****----\n");
	}
	else
	{
		if (icha == 1)
		{
			printf("-------------******-------------��ѯ���Ŀ���Ϣ����-------------******-------------\n");
			// ������ı�ͷ
			printf("\t����\t״̬\t���\t�ۼƽ��\tʹ�ô���\t�ϴ�ʹ��ʱ��\n");

			// ��time_t����ʱ��ת��Ϊ�ַ������ַ�����ʽΪ����-��-�� ʱ���֡�
			timeToString(pCard->tLastTime, aLastTime);
			// ����鵽�Ŀ���Ϣ
			printf("\t%s\t%d\t%.2f\t%.2f\t%10d\t\t%s\n", pCard->aName, pCard->nStatus, pCard->fBalance, pCard->fTotalUse, pCard->nUseCount, aLastTime);
			printf("----------------------------------------------------------------------------------\n");
		}
		else // ģ����ѯ������
		{
			printf("-------------******-------------��ѯ���Ŀ���Ϣ����-------------******-------------\n");
			// ������ı�ͷ
			printf("\t����\t״̬\t���\t�ۼƽ��\tʹ�ô���\t�ϴ�ʹ��ʱ��\n");

			for (i = 0; i < nIndex; i++)
			{
				// ��time_t����ʱ��ת��Ϊ�ַ������ַ�����ʽΪ"��-��-�� ʱ����"
				timeToString(pCard[i].tLastTime, aLastTime); // �ṹ��ָ�뵱��������

				// �����ѯ���Ŀ���Ϣ
				printf("\t%s\t%d\t%.2f\t%.2f\t%10d\t\t%s\n", pCard[i].aName, pCard[i].nStatus, pCard[i].fBalance, pCard[i].fTotalUse, pCard[i].nUseCount, aLastTime);
				printf("----------------------------------------------------------------------------------\n");
			}

			// �ͷŶ�̬������ڴ�
			free(pCard);
		}
		pCard = NULL;
	}
}

// ������:exitApp
// ����:�˳�Ӧ�ó���
// ����:void
// ����ֵ:void
void exitApp()
{
	releaseList();
}

// ������:logon
// ����:�����ϻ�����Ϣ����ѯ��������ϻ�����Ϣ
// ����:void
// ����ֵ:void
void logon()
{
	char aName[30] = {0}; // �ϻ�����
	char aPwd[20] = {0};  // �ϻ�����
	char aLastTime[30];	  // ���ָ����ʽ�ַ�����ʱ��
	LogonIofo *pInfo = NULL;
	int nResult = 0;

	// ��ʾ�������ϻ�����
	printf("�������ϻ��Ŀ��ţ�����Ϊ0~18����");
	scanf("%s", aName, 30);
	// �ж�����Ŀ����Ƿ����Ҫ��
	if (getSize(aName) >= 18)
	{
		printf("����Ŀ��ų��ȳ������ֵ��\n");
		return;
	}
	// ��ʾ�������ϻ�����
	printf("�������ϻ����루����Ϊ1~8����");
	scanf("%s", aPwd, 20);
	// �ж�����������Ƿ����Ҫ��
	if (getSize(aPwd) >= 8)
	{
		printf("��������볤�ȳ������ֵ��\n");
		return;
	}
	// ��ʼ�ϻ�����ȡ�ϻ����
	pInfo = (LogonInfo *)malloc(sizeof(LogonInfo));
	if (pInfo == NULL)
	{
		exit(1);
	}
	// �����ϻ��������ʾ��ͬ��Ϣ
	nResult = doLogon(aName, aPwd, pInfo);

	switch (nResult)
	{
	case 0:
		printf("�ϻ�ʧ��!\n");
		break;
	case 1:
		printf("------***------�ϻ���Ϣ����------***------\n");
		// ������ı�ͷ
		printf("\t����\t���\t�ϻ�ʱ��\n");

		// ��time_t����ʱ��ת��Ϊ�ַ������ַ�����ʽΪ����-��-�� ʱ���֡�
		timeToString(pInfo->tLogon, aLastTime); // �ṹָ�뵱������ʹ��

		// ����ϻ�����Ϣ
		printf("\t%s\t%.2f\t%s\n", pInfo->aCardName, pInfo->fBalance, aLastTime);
		printf("------------------------------------------\n");
		printf("---------�ϻ��ɹ���---------\n");
		break;
	case 2:
		printf("---------�ÿ�����ʹ��!---------\n");
		break;
	case 3:
		printf("---------���㣡---------\n");
		break;
	}
	// �ͷ��ϻ���Ϣ
	free(pInfo);
}

// ������:settle
// ����:�����»�����Ϣ����ѯ������ϻ�����Ϣ
// ����:void
// ����ֵ:void
void settle()
{
	char aName[18] = {0};	   // ����
	char aPwd[8] = {0};		   // ����
	int nResult = -1;		   // �»����
	SettleInfo *pInfo = NULL;  // �»�����Ϣ
	char aStartTime[30] = {0}; // �ϻ�ʱ��
	char aEndTime[30] = {0};   // �»�ʱ��

	// Ϊ�»���Ϣ��̬�����ڴ�
	pInfo = (SettleInfo *)malloc(sizeof(SettleInfo));
	if (pInfo == 0)
	{
		exit(1);
	}
	printf("�������»����ţ�����1~18����");
	scanf("%s", aName, 18);
	// �ж�����Ŀ����Ƿ����Ҫ��
	if (getSize(aName) >= 18)
	{
		printf("����Ŀ��ų��ȳ������ֵ��\n");
		return;
	}

	printf("�������»����루����1~8��:");
	scanf("%s", aPwd, 8);
	// �ж�����������Ƿ����Ҫ��
	if (getSize(aPwd) >= 8)
	{
		printf("��������볤�ȳ������ֵ��\n");
		return;
	}

	// �����»�
	nResult = doSettle(aName, aPwd, pInfo);

	// �����»��������ʾ��ͬ��Ϣ
	printf("\n");
	printf("--------------*****--------------�»���Ϣ����--------------*****--------------\n");
	switch (nResult)
	{
	case 0: // �»�ʧ��
	{
		printf("�»�ʧ�ܣ�\n");
		break;
	}
	case 1: // �»��ɹ�
	{
		// �������ͷ
		printf("\t����\t����\t���\t\t�ϻ�ʱ��\t\t�»�ʱ��\n");
		// ���ϻ�ʱ��Ĭ��Ϊ�������ʹ��ʱ�䣬������ӼƷ���Ϣ��ʹ�üƷ���Ϣʱ��
		// ��time_t����ʱ��ת��Ϊ�ַ������ַ�����ʽΪ����-��-�� ʱ���֡�
		timeToString(pInfo->tStart, aStartTime);
		timeToString(pInfo->tEnd, aEndTime);

		// ����»�����Ϣ
		printf("\t%s\t%.2f\t%.2f", pInfo->aCardName, pInfo->fAmount, pInfo->fBalance);
		printf("\t\t%s\t%s\n", aStartTime, aEndTime);
		printf("---------------------------------------------------------------------------\n");
		printf("�»��ɹ���\n");
		break;
	}
	case 2: // ����ʹ�û���ע��
	{
		printf("�ÿ�δ��ʹ�ã�\n");
		break;
	}
	case 3: // ������
	{
		printf("�����㣡\n");
		break;
	}
	default:
	{
		break;
	}
	}
	// �ͷŶ�̬�����ڴ�
	free(pInfo);
}

// ������:addMoney
// ����:��ֵ
// ����:void
// ����ֵ:void
void addMoney()
{
	char aName[18] = {0}; // ����
	char aPwd[8] = {0};	  // ����
	float fAmount = 0;	  // ��ֵ���
	MoneyInfo sMoneyInfo; // ��ֵ����Ϣ

	printf("�������ֵ�Ŀ��ţ�����1~18����");
	scanf("%s", aName, 18);
	// �ж�����Ŀ����Ƿ����Ҫ��
	if (getSize(aName) >= 18)
	{
		printf("����Ŀ��ų��ȳ������ֵ��\n");
		return;
	}

	printf("�������ֵ���루����1~8����");
	scanf("%s", aPwd, 8);
	// �ж�����������Ƿ����Ҫ��
	if (getSize(aPwd) >= 8)
	{
		printf("��������볤�ȳ������ֵ��\n");
		return;
	}

	cout << "�������ֵ��RMB)��";
	cin >> fAmount;
	cin.clear();
	cin.sync();

	// �����ֵ���
	sMoneyInfo.fMoney = fAmount;
	// �ж��Ƿ񱣴�ɹ�
	if (TRUE == doAddMoney(aName, aPwd, &sMoneyInfo))
	{
		// ��ʾ��ֵ��Ϣ
		printf("-----***-----��ֵ��Ϣ����-----***-----\n");
		// ������ͷ
		printf("\t����\t��ֵ���\t���\n");
		// �����ֵ����Ϣ
		printf("\t%s\t%.2f    \t%.2f\n", sMoneyInfo.aCardName, sMoneyInfo.fMoney, sMoneyInfo.fBalance);
		printf("--------------------------------------\n");
	}
	else
	{
		printf("-------��ֵʧ�ܣ�-------\n");
	}
}

// ������:refundMoney
// ����:�˷�
// ����:void
// ����ֵ:void
void refundMoney()
{
	char aName[18] = {0}; // ����
	char aPwd[8] = {0};	  // ����
	int nResult = -1;	  // �˷ѽ��
	MoneyInfo sMoneyInfo; // �˷���Ϣ

	printf("�������˷ѿ��ţ�����1~18����");
	scanf("%s", aName, 18);
	// �ж�����Ŀ����Ƿ����Ҫ��
	if (getSize(aName) >= 18)
	{
		printf("����Ŀ��ų��ȳ������ֵ��\n");
		return;
	}

	printf("�������˷����루����1~8����");
	scanf("%s", aPwd, 8);
	// �ж�����������Ƿ����Ҫ��
	if (getSize(aPwd) >= 8)
	{
		printf("��������볤�ȳ������ֵ��\n");
		return;
	}

	// �����˷�
	nResult = doRefundMoney(aName, aPwd, &sMoneyInfo);
	// �����˷ѽ������ʾ��ͬ��Ϣ
	switch (nResult)
	{
	case 0:
	{
		printf("�˷�ʧ�ܣ�\n");
		break;
	}
	case 1:
	{
		// ��ʾ�˷���Ϣ
		printf("------***----�˷���Ϣ����----***------\n");
		printf("\t����\t�˷ѽ��\t���\n");
		// �����ֵ����Ϣ
		printf("\t%s\t%.2f   \t%.2f\n", sMoneyInfo.aCardName, sMoneyInfo.fMoney, sMoneyInfo.fBalance);
		printf("--------------------------------------\n");
		break;
	}
	case 2:
	{
		printf("------�ÿ�����ʹ�û��Ѿ�ע����------\n");
		break;
	}
	case 3:
	{
		printf("------�����㣡------\n");
		break;
	}
	default:
	{
		break;
	}
	}
}

// ������:annul
// ����:ע����
// ����:void
// ����ֵ:void
void annul()
{
	Card card;

	printf("������ע�������ţ�����1~18����");
	scanf("%s", card.aName, 18);
	printf("���������루����1~8����");
	scanf("%s", card.aPwd, 8);

	if (FALSE == annulCard(&card))
	{
		printf("---------ע����ʧ��---------\n");
		return;
	}
	else
	{
		// ��ʾע������Ϣ
		printf("---***---ע����Ϣ����---***---\n");
		// ������ͷ
		printf("\t����\t�˿���\n");
		printf("\t%s\t%.2f\n", card.aName, card.fBalance);
		printf("------------------------------\n");

		return;
	}
}