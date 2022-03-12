#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<time.h>

#include"tool.h"

//函数名：timeToString
//功能：将time_t类型转换为字符串，字符串格式为“年-月-日 时：分”
//参数：time_t t：需要转换的时间，char* pBuf:转换之后的字符串
//返回值：void
void timeToString(time_t t, char* pBuf)
{
	struct tm* timeinfo;

	timeinfo = localtime(&t);
	strftime(pBuf, 20, "%Y-%m-%d %H:%M", timeinfo);
}

//函数名：stringToTime
//功能：将格式为“年-月-日 时：分”的字符串转换为time_t类型时间
//参数：char *pTime:“年-月-日 时：分”格式的字符串
//返回值：time_t:转换后的时间类型，从1970到该时间的秒数
time_t stringToTime(char* pTime)
{
	struct tm tml;
	time_t time1;

	sscanf(pTime, "%d-%d-%d %d:%d", &tml.tm_year, &tml.tm_mon, &tml.tm_mday, &tml.tm_hour, &tml.tm_min);

	tml.tm_year -= 1900;//年份从1900年开始
	tml.tm_mon -= 1;//月份为0~11
	tml.tm_sec = 0;
	tml.tm_isdst = -1;

	time1 = mktime(&tml);

	return time1;
}