#include<stdio.h>
#include"menu.h"

int main()
{
	int choice;//choice表示用户的选择

	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\t\t\t\t\t\t*欢迎进入收费管理系统*\n\n\n\n\n");

	do {
		outputMenu();//函数调用

		choice = -1;//变量初始化

		printf("\t\t\t\t\t\t请输入菜单项编号(0--8):");//输入提示
		scanf_s("%d", &choice);
		printf("\n");

		fflush(stdin);
		
		switch (choice) {
		case 1:printf("\t\t\t\t\t\t-----添加卡-----\n\n"); break;
		case 2:printf("\t\t\t\t\t\t-----查询卡-----\n\n"); break;
		case 3:printf("\t\t\t\t\t\t-----上机-----\n\n"); break;
		case 4:printf("\t\t\t\t\t\t-----下机-----\n\n"); break;
		case 5:printf("\t\t\t\t\t\t-----充值-----\n\n"); break;
		case 6:printf("\t\t\t\t\t\t-----消费-----\n\n"); break;
		case 7:printf("\t\t\t\t\t\t-----查询统计------\n\n"); break;
		case 8:printf("\t\t\t\t\t\t-----注销卡-----\n\n"); break;
		case 0:printf("\t\t\t\t\t\t谢谢您使用本系统!\n\n"); break;
		default:printf("\t\t\t\t\t\t您输入的菜单编号有误!请重新输入!\n\n"); break;
		}
	} while (choice != 0);
	
	return 0;
}


