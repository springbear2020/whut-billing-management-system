#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#include"menu.h"

//函数名：main
//功能：程序入口函数
//参数：void
//返回值：0代表程序正常退出；非0：程序异常
int main()
{
	int choice;//choice表示用户的菜单编号

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t");
	printf("*欢迎进入收费管理系统*");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t");
	system("pause");
	system("cls");

	do {
		outputMenu();//函数调用，输出系统菜单

		printf("请输入菜单项编号(0--8):");//输入提示
		scanf("%d", &choice);
		printf("\n");

		switch (choice) {
		case 1:printf("\t*添加卡*\n\n"); add(); break;
		case 2:printf("\t*查询卡*\n\n"); query(); break;
		case 3:printf("\t*上机*\n\n"); logon(); break;
		case 4:printf("\t*下机*\n\n"); settle(); break;
		case 5:printf("\t*充值*\n\n"); addMoney(); break;
		case 6:printf("\t*消费*\n\n"); refundMoney(); break;
		case 7:printf("\t*查询统计*\n\n"); break;
		case 8:printf("\t*注销卡*\n\n"); annul(); break;
		case 0:printf("谢谢您使用本系统!\n\n"); exitApp();  break;
		default:printf("您输入的菜单编号有误!请重新输入!\n\n"); break;
		}
	} while (choice != 0);

	return 0;
}


