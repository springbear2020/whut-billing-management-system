#pragma once

int addCardInfo(Card card);                                                    // ��ӿ���Ϣ
Card *queryCardInfo(const char *pName);                                        // ģ����ѯ����Ϣ
Card *queryCardsInfo(const char *pName, int *pIndex);                          // ģ����ѯ����Ϣ
int doLogon(const char *pName, const char *pPwd, LogonInfo *pInfo);            // ���ļ��ж�ȡ����Ϣ�������������в�ѯ����Ϣ,����ȡ���������е�λ��
void releaseList();                                                            // �˳�Ӧ�ó����ͷ������ڴ�
int doSettle(const char *pName, const char *pPwd, SettleInfo *pInfo);          // �����»�����
double getAmount(time_t tStart);                                               // �����ϻ�ʱ��������ѽ��
int doAddMoney(const char *pName, const char *pPwd, MoneyInfo *pMoneyInfo);    // ���г�ֵ����
int doRefundMoney(const char *pName, const char *pPwd, MoneyInfo *pMoneyInfo); // �����˷Ѳ���
int annulCard(Card *pCard);                                                    // ע����