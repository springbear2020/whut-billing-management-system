#pragma once

void timeToString(time_t, char *pBuf); // ��time_t����ת��Ϊ�ַ������ַ�����ʽΪ����-��-�� ʱ���֡�
time_t stringToTime(char *pTime);      // ����ʽΪ����-��-�� ʱ���֡����ַ���ת��Ϊtime_t����ʱ��