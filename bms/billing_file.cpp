#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <istream>

#include "model.h"
#include "global.h"

using namespace std;

// ������:saveBilling
// ����:����Ʒ���Ϣ
// ����:pBilling:�Ʒ���Ϣ�ṹָ�룻pPath:����Ʒ���Ϣ�ļ�·��
// ����ֵ:TRUE:����ɹ���FALSE:����ʧ��
int saveBilling(const Billing *pBilling, const char *pPath)
{
	// ��׷�ӷ�ʽ�������Ʒ�ʽд��
	ofstream ofile(pPath, ios_base::out | ios_base::app | ios_base::binary);
	if (!ofile.is_open())
	{
		printf("�ļ��޷���ȷ�򿪣�����д��Ʒ���Ϣ!\n");
		ofile.close();
		return FALSE;
	}
	// ���Ʒ���Ϣ���浽�ļ���
	ofile.write((const char *)pBilling, sizeof(Billing));

	// �ر��ļ�
	ofile.close();
	printf("----*****-----�Ʒ���Ϣ�ɹ������ļ�!-----*****----\n");
	return TRUE;
}

// ������:readBilling
// ����:��ȡ�Ʒ���Ϣ
// ����:pBilling:�Ʒ���Ϣ�ṹ��ָ��  pPath
// ����ֵ:TRUE ��ȡ�ɹ�  FALSE ��ȡʧ��
int readBilling(Billing *pBilling, const char *pPath)
{
	int nIndex = 0;

	// �Զ����Ʒ�ʽ��ȡ
	ifstream ifile(pPath, ios_base::in | ios_base::binary);
	if (!ifile.is_open())
	{
		printf("�ļ��޷���ȷ�򿪣����ܶ�ȡ�Ʒ���Ϣ!\n");
		ifile.close();
		return FALSE;
	}
	else
	{
		// �����ļ���ȡ�ļ�����
		while (!ifile.eof())
		{
			if (!ifile.read((char *)(&pBilling[nIndex]), sizeof(Billing)))
				;
			else
			{
				nIndex++;
			}
		}
		// �ر��ļ�
		ifile.close();
		return TRUE;
	}
}

// ������:getBillingCount
// ����:��ȡ�ļ��мƷ���Ϣ����
// ����:�Ʒ���Ϣ�ļ�·��
// ����ֵ:�Ʒ���Ϣ����
int getBillingCount(const char *pPath)
{
	int nCount = 0;
	Billing *pBilling = (Billing *)malloc(sizeof(Billing));
	// �Զ����Ʒ�ʽ��ȡ
	ifstream ifile(pPath, ios_base::in | ios_base::binary);
	if (!ifile.is_open())
	{ // �����ļ�
		printf("�ļ��޷���ȷ�򿪣����ܶ�ȡ�Ʒ���Ϣ!\n");
		ifile.close();
		return FALSE;
	}
	else
	{
		while (!ifile.eof())
		{
			if (!ifile.read((char *)pBilling, sizeof(Billing)))
				;
			else
			{
				nCount++;
			}
		}
		// �ر��ļ�
		ifile.close();
		free(pBilling);
		return nCount;
	}
}

// ������:updateBilling
// ����:���¼Ʒ���Ϣ�ļ��е�һ����Ϣ
// ����:pBilling:ָ��Ʒ���Ϣ�ṹ�壻pPath:�Ʒ���Ϣ�ļ�·����nIndex:�Ʒ���Ϣ���
// ����ֵ:TREU:�ɹ���FALSE:ʧ��
int updateBilling(const Billing *pBilling, const char *pPath, int nIndex)
{
	int nCount = 0;
	long lPosition = 0;
	Billing pbBuf;

	// �Զ�дģʽ��������ģʽ���ļ������ʧ�ܷ���FALSE
	fstream iofile(pPath, ios_base::out | ios_base::in | ios_base::binary);
	if (!iofile.is_open())
	{
		printf("�ļ��޷���ȷ�򿪣����ܸ���������Ϣ��\n");
		iofile.close();
		return FALSE;
	}
	// �����ļ�����ȡ������Ϣ���ļ��е�λ��
	while ((!iofile.eof()) && (nCount < nIndex))
	{
		if (!iofile.read((char *)(&pbBuf), sizeof(Billing)))
			;
		else
		{
			// ��ȡ�ļ���ʶλ�ã����һ���ҵ���λ��
			lPosition = (long)iofile.tellg();
		}
		nCount++;
	}
	// �ƶ����ļ���ʶλ��
	// ע��ָ�����ڸ�������֮����֮ǰ������
	// ����õ��Ķ�дָ������һ����Ϣ��ͷ��Ҫ�ƶ���������Ϣ��ͷ��
	iofile.seekp((__int64)lPosition - sizeof(Billing), ios_base::beg);
	// ����������Ϣ���ļ�
	iofile.write((const char *)(pBilling), sizeof(Billing));
	printf("----*****----������Ϣ���µ��ļ��ɹ���----*****----\n");
	// �ر��ļ�
	iofile.close();
	return TRUE;
}