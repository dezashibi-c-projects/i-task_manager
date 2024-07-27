// ***************************************************************************************
//    Project: Task Manager (todo list) using Linked List
//    File: utils.c
//    Date: 2024-07-27
//    Author: Navid Dezashibi
//    Contact: navid@dezashibi.com
//    Website: https://www.dezashibi.com | https://github.com/dezashibi
//    License:
//     Please refer to the LICENSE file, repository or website for more information about
//     the licensing of this work. If you have any questions or concerns,
//     please feel free to contact me at the email address provided above.
// ***************************************************************************************
// *  Description: Read the readme file for more information
// ***************************************************************************************

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long generate_unique_id(size_t seed)
{
    // Get the current time
    time_t now = time(NULL);
    struct tm local_time;
#ifdef _WIN32
    localtime_s(&local_time, &now);
#else
    localtime_r(&now, &local_time);
#endif

    // Format the unique ID based on the current date and time
    unsigned long long id = (local_time.tm_year + 1900) * 10000000000ULL +
                            (local_time.tm_mon + 1) * 100000000ULL +
                            local_time.tm_mday * 1000000ULL +
                            local_time.tm_hour * 10000ULL +
                            local_time.tm_min * 100ULL +
                            local_time.tm_sec + seed;

    return id;
}
