#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>     //包含时间类型头文件//[函数名] 

//函数:timeToString
//功能:将time_t类型转化为字符串，字符串格式为“年-月-日 时：分”
//参数:time_t t:需要转化的时间，char*pBuf:转化之后的字符串
//返回值:void
void timeToString(time_t t, char* pBuf)
{
	struct tm* timeinfo;

	if ((timeinfo = (struct tm*)malloc(sizeof(struct tm))) == NULL)
	{
		exit(1);
	}
	localtime_s(timeinfo,&t);
	strftime(pBuf, 20, "%Y-%m-%d %H:%M", timeinfo);
}

//函数名:stringToTime
//功能:将格式为“年-月-日 时：分”的字符串转化为time_t类型时间
//参数:char* pTime:“年-月-日 时：分”格式的字符串
//返回值: time_t:转化后的时间类型，从1970年到改时间的秒数
time_t stringToTime(char* pTime)
{
	struct tm tm1;
	time_t time1;

	sscanf_s(pTime, "%d-%d-%d %d:%d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday, &tm1.tm_hour, &tm1.tm_min);
	tm1.tm_year -= 1900;//年份为从1970年开始
	tm1.tm_mon -= 1;
	tm1.tm_sec = 0;
	tm1.tm_isdst=-1;

	time1 = mktime(&tm1);

	return time1;
}