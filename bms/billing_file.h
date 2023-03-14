#pragma once
#include "model.h"
// 函数声明
int saveBilling(const Billing *pBilling, const char *pPath);               // 保存计费信息
int readBilling(Billing *pBilling, const char *pPath);                     // 读取计费信息
int getBillingCount(const char *pPath);                                    // 获取文件中计费信息数量
int updateBilling(const Billing *pBilling, const char *pPath, int nIndex); // 更新计费信息文件中的一条信息