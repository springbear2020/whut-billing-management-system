#pragma once

void timeToString(time_t, char *pBuf); // 将time_t类型转化为字符串，字符串格式为“年-月-日 时：分”
time_t stringToTime(char *pTime);      // 将格式为“年-月-日 时：分”的字符串转化为time_t类型时间