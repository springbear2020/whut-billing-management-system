#pragma once
#include "model.h"
// ��������
int saveCard(const Card *pCard, const char *pPath);               // ������Ϣ���浽�ļ���
int readCard(Card *pCard, const char *pPath);                     // ���ļ��ж�ȡ����Ϣ���ṹ������
int getCardCount(const char *pPath);                              // ��ȡ����Ϣ�ļ��У�����Ϣ����
int updateCard(const Card *pCard, const char *pPath, int nIndex); // ���¿���Ϣ�ļ��е�һ������Ϣ