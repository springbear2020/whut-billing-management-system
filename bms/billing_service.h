#pragma once

#include "model.h"

int addBilling(const char *pName, Billing *pBilling);  // �ϻ�ʱ���������Ϣ���ļ�
void initBillingList();                                // ��ʼ���Ʒ���Ϣ����
void releaseBillingList();                             // �ͷżƷ���Ϣ����
int getBilling();                                      // �ӼƷ��ļ��У���ȡ�Ʒ���Ϣ���浽������
Billing *queryBilling(const char *pName, int *pIndex); // �ڼƷ���Ϣ�����У���ѯ��Ӧ���ļƷ���Ϣ������ȡ���������е�������