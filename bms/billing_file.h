#pragma once
#include "model.h"
// ��������
int saveBilling(const Billing *pBilling, const char *pPath);               // ����Ʒ���Ϣ
int readBilling(Billing *pBilling, const char *pPath);                     // ��ȡ�Ʒ���Ϣ
int getBillingCount(const char *pPath);                                    // ��ȡ�ļ��мƷ���Ϣ����
int updateBilling(const Billing *pBilling, const char *pPath, int nIndex); // ���¼Ʒ���Ϣ�ļ��е�һ����Ϣ