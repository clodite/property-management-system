#include "header.h"
#include "function.h"
#include "struct.h"

struct time timestamp_to_time(int t)
{
    // using time.h

    struct tm start_time = {0}; // the real timestamp of start_time (2025)
    start_time.tm_year = 2025 - 1900;
    start_time.tm_mon = 3 - 1;
    start_time.tm_mday = 14;
    start_time.tm_hour = 0;

    time_t start_timestamp = mktime(&start_time);
    time_t timestamp_diff = t * 3600;
    time_t real_timestamp = start_timestamp + timestamp_diff;

    struct tm *timenow = localtime(&real_timestamp);

    struct time result;
    result.year = timenow->tm_year + 1900;
    result.month = timenow->tm_mon + 1;
    result.day = timenow->tm_mday;
    result.hour = timenow->tm_hour;

    return result;
}
