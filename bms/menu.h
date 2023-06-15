#pragma once

void outputMenu();                // 输出系统菜单
void add();                       // 添加用户卡信息到卡结构体变量，并屏幕显示
int getSize(const char *pString); // 计算字符数组中字符长度
void query();                     // 根据输入的卡号调用，查询是否有该卡，有的话，输出卡信息
void exitApp();                   // 退出应用程序
void logon();                     // 输入上机卡信息，查询到，输出上机卡信息
void settle();                    // 输入下机卡信息，查询到输出上机卡信息
void addMoney();                  // 充值
void refundMoney();               // 退费
void annul();                     // 注销卡