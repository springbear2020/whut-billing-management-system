#pragma once
//函数声明
void timeToString(time_t t, char* pBuf);//将time_t类型转换为字符串，字符串格式为“年-月-日 时：分”
time_t stringToTime(char* pTime);//将格式为“年-月-日 时：分”的字符串转换为time_t类型时间