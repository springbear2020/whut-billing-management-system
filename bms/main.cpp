#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "menu.h"

// ��������main
// ���ܣ�������ں���
// ������void
// ����ֵ��0������������˳�����0�������쳣
int main()
{
	int choice; // choice��ʾ�û��Ĳ˵����

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t");
	printf("*��ӭ�����շѹ���ϵͳ*");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t");
	system("pause");
	system("cls");

	do
	{
		outputMenu(); // �������ã����ϵͳ�˵�

		printf("������˵�����(0--8):"); // ������ʾ
		scanf("%d", &choice);
		printf("\n");

		switch (choice)
		{
		case 1:
			printf("\t*��ӿ�*\n\n");
			add();
			break;
		case 2:
			printf("\t*��ѯ��*\n\n");
			query();
			break;
		case 3:
			printf("\t*�ϻ�*\n\n");
			logon();
			break;
		case 4:
			printf("\t*�»�*\n\n");
			settle();
			break;
		case 5:
			printf("\t*��ֵ*\n\n");
			addMoney();
			break;
		case 6:
			printf("\t*����*\n\n");
			refundMoney();
			break;
		case 7:
			printf("\t*��ѯͳ��*\n\n");
			break;
		case 8:
			printf("\t*ע����*\n\n");
			annul();
			break;
		case 0:
			printf("лл��ʹ�ñ�ϵͳ!\n\n");
			exitApp();
			break;
		default:
			printf("������Ĳ˵��������!����������!\n\n");
			break;
		}
	} while (choice != 0);

	return 0;
}
