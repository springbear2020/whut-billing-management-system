#pragma once

int addCardInfo(Card card);                                                    // 添加卡信息
Card *queryCardInfo(const char *pName);                                        // 模糊查询卡信息
Card *queryCardsInfo(const char *pName, int *pIndex);                          // 模糊查询卡信息
int doLogon(const char *pName, const char *pPwd, LogonInfo *pInfo);            // 从文件中读取卡信息到链表，在链表中查询卡信息,并获取其在链表中的位置
void releaseList();                                                            // 退出应用程序，释放链表内存
int doSettle(const char *pName, const char *pPwd, SettleInfo *pInfo);          // 进行下机操作
double getAmount(time_t tStart);                                               // 根据上机时间计算消费金额
int doAddMoney(const char *pName, const char *pPwd, MoneyInfo *pMoneyInfo);    // 进行充值操作
int doRefundMoney(const char *pName, const char *pPwd, MoneyInfo *pMoneyInfo); // 进行退费操作
int annulCard(Card *pCard);                                                    // 注销卡