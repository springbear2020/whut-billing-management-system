#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>

#include <stdio.h>
#include "model.h"

#include "global.h"

using namespace std;

// ������:aveMoney
// ����:����ֵ�˷���Ϣ���浽�ļ���
// ����:pMoney:��ֵ�˷ѽṹ�壻pPath:��ֵ�˷���Ϣ����·��
// ����ֵ:TRUE:����ɹ� FALSE:����ʧ��
int saveMoney(const Money *pMoney, const char *pPath)
{
	// ��׷�ӷ�ʽ�������Ʒ�ʽд��
	ofstream ofile(pPath, ios_base::out | ios_base::app | ios_base::binary);
	if (!ofile.is_open())
	{
		printf("�ļ��޷���ȷ�򿪣�����д���ֵ�˷���Ϣ!\n");
		ofile.close();
		return FALSE;
	}
	// ����ֵ�˷���Ϣ���浽�ļ���
	ofile.write((const char *)pMoney, sizeof(Money));

	// �ر��ļ�
	ofile.close();
	printf("----*****-----��ֵ�˷���Ϣ�ɹ������ļ�!-----*****----\n");
	return TRUE;
}
