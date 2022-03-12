#include<iostream>
#include<fstream>

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"card_file.h"
#include"model.h"
#include"global.h"
#include"tool.h"

#define CARDCHARNUM 256  //�ӿ���Ϣ�ļ���ȡ���ַ������ֵ

using namespace std;

//��������saveCard
//���ܣ�������Ϣ���浽�ļ���
//������pCard:ָ��Ҫ����Ŀ���Ϣ�ṹ�壻 pPath:������ļ�·��
//����ֵ������ɹ�����TRUE,ʧ�ܷ���FALSE
int saveCard(const Card* pCard, const char* pPath)
{
	char aStart[30];//���ת�����ʱ���ַ���
	char aEnd[30];//���ת�����ʱ���ַ���
	char aLast[30];//���ת�����ʱ���ַ���

	timeToString(pCard->tStart, aStart);
	timeToString(pCard->tEnd, aEnd);
	timeToString(pCard->tLastTime, aLast);

	ofstream ofile(pPath, ios_base::out | ios_base::app);//��׷�ӷ�ʽд��
	if (!ofile.is_open())
	{
		cerr << "�ļ��޷������򿪣�����д�뿨��Ϣ��\n" << endl;
		exit(EXIT_FAILURE);
	}
	//���ļ���д����Ϣ
	ofile << pCard->aName << "##" << pCard->aPwd << "##" << pCard->nStatus << "##";
	ofile << aStart << "##" << aEnd << "##" << pCard->fTotalUse << "##" << aLast << "##";
	ofile << pCard->nUseCount << "##" << pCard->fBalance << "##" << pCard->nDel << endl;
	ofile.close();

	cout << "----******----����Ϣ�ɹ������ļ���-----******----" << endl;
	return TRUE;
}

//��������readCard
//���ܣ����ļ��ж�ȡ����Ϣ���ṹ������
//������pCard��ָ��ṹ�����飻pPath���ļ�·��
//����ֵ����ȷ��ȡ����TRUE,���򷵻�FALSE
int readCard(Card* pCard, const char* pPath)
{
	int nIndex = 0;//����Ϣ����
	char aBuf[CARDCHARNUM] = { 0 };//������ļ��ж�ȡ��һ������
	int i = 0;//�ṹ�������±�

	ifstream ifile;
	//Ĭ����ֻ����ʽ���ļ�
	ifile.open(pPath);
	if (ifile.is_open()) 
		while (!ifile.eof())
		{
			memset(aBuf, 0, CARDCHARNUM);//����ַ�����
			ifile.getline(aBuf, CARDCHARNUM);//��ȡһ�п���Ϣ
			if (strlen(aBuf) != 0)
				pCard[i] = praseCard(aBuf);
			i++;
		}
	else{
		cout << "�ļ��޷���ȷ�򿪣����ܶ�ȡ����Ϣ��\n" << endl;
		ifile.close();
		return FALSE;
	}
	//�ر��ļ�
	ifile.close();
	return TRUE;
}

//��������praseCard
//���ܣ���һ������Ϣ�ַ������������һ�����ṹ��
//����������Ϣ�ַ���
//����ֵ�����ṹ��
Card praseCard(char* pBuf)
{
	Card card;
	char flag[10][20];//��ʱ��ŷ���
	char* str;//ÿ�ν����������ַ���
	char* buf;
	int index = 0;//�����±�

	buf = pBuf;//��һ�ε���strtok����ʱ��bufΪ�����ַ���
	while ((str = strtok(buf, "##")) != NULL)
	{
		strcpy_s(flag[index], str);
		buf = NULL;//�������strtok����ʱ����һ������ΪNULL
		index++;
	}
	//�ָ�����ݱ��浽�ṹ����
	strcpy_s(card.aName, flag[0]);
	strcpy_s(card.aPwd, flag[1]);
	card.nStatus = atoi(flag[2]);
	card.tStart = stringToTime(flag[3]);
	card.tEnd = stringToTime(flag[4]);
	card.fTotalUse = atof(flag[5]);
	card.tLastTime = stringToTime(flag[6]);
	card.nUseCount = atoi(flag[7]);
	card.fBalance = atof(flag[8]);
	card.nDel = atoi(flag[9]);
	//���ؿ���Ϣ�ṹ��
	return card;
}

//��������getCardCount
//���ܣ���ȡ����Ϣ�ļ��п���Ϣ����
//�������ļ�·��
//����ֵ������Ϣ����
int getCardCount(const char* pPath)
{
	int nIndex = 0;//����Ϣ����
	char aBuf[CARDCHARNUM] = { 0 };//������ļ��ж�ȡ������

	ifstream ifile;
	//Ĭ����ֻ���ķ�ʽ���ļ�
	ifile.open(pPath);
	if(ifile.is_open())
		//�����ļ�
		while (!ifile.eof())
		{
			memset(aBuf, 0, CARDCHARNUM);//����ַ�����
			ifile.getline(aBuf, CARDCHARNUM);//��ȡһ�п���Ϣ
			if (strlen(aBuf) != 0)
				nIndex++;
		}
	else
	{
		cout << "�ļ��޷���ȷ�򿪣����ܶ�ȡ����Ϣ��\n" << endl;
		ifile.close();
		return -1;
	}
	//�ر��ļ�
	ifile.close();
	return nIndex;
}

//��������updateCard
//���ܣ����¿���Ϣ�ļ��ж�Ӧ��һ������Ϣ
//������pCard�����º�Ŀ����� pPath������Ϣ�ļ���·��
//      nIndex:��Ҫ���µĿ���Ϣ���ļ��еĿ����
//����ֵ��TRUE:���³ɹ���FALSE:����ʧ��
int updateCard(const Card* pCard, const char* pPath, int nIndex)
{
	char aBuf[CARDCHARNUM] = { 0 };
	char aStart[30];//���ת�����ʱ���ַ���
	char aEnd[30];//���ת�����ʱ���ַ���
	char aLast[30];//���ת�����ʱ���ַ���
	int nLine = 0;//�ļ��е�ǰ�����
	long lPosition = 0;//�ļ�λ�ñ��

	//��time_t����ʱ��ת��Ϊ�ַ������ַ�����ʽΪ����-��-�� ʱ���֡�
	timeToString(pCard->tStart, aStart);
	timeToString(pCard->tEnd, aEnd);
	timeToString(pCard->tLastTime, aLast);

	//�Զ�дģʽ���ļ�����Ĭ�Ϸ�ʽ�����ʧ�ܣ�����FALSE
	fstream iofile(pPath, ios_base::out | ios_base::in);
	if (!iofile.is_open())
	{
		cout << "�ļ��޷���ȷ�򿪣����ܸ��¿���Ϣ��" << endl;
		iofile.close();
		return FALSE;
	}

	//�����ļ�����ȡ�����ļ��е�λ��
	while ((!iofile.eof()) && (nLine < nIndex))
	{
		memset(aBuf, 0, CARDCHARNUM);//����ַ�����
		//���ж�ȡ�ļ���Ϣ
		iofile.getline(aBuf, CARDCHARNUM);
		//��ȡ�ļ���ʶλ�ã����һ�����ҵ���λ��
		lPosition = iofile.tellg();
		nLine++;
	}
	//�Ƶ��ļ���ʶλ��
	//ע��ָ�����ڸ�������Ϣ֮����֮ǰ������
	//����õ��Ķ�ָ������һ������Ϣ��ͷ��Ҫ�Ƶ���������Ϣ��ͷ��
	iofile.seekp(lPosition - strlen(aBuf) - 2, ios::beg);

	//���ļ�д����µĿ���Ϣ
	iofile << pCard->aName << "##" << pCard->aPwd << "##" << pCard->nStatus << "##";
	iofile << aStart << "##" << aEnd << "##" << pCard->fTotalUse << "##" << aLast << "##";
	iofile << pCard->nUseCount << "##" << pCard->fBalance << "##" << pCard->nDel << endl;

	cout << "----******----����Ϣ���µ��ļ��ɹ���-----******----" << endl << endl;

	//�ر��ļ�
	iofile.close();
	return TRUE;
}