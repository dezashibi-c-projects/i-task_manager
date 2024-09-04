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
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

char* replace_file_in_path(const char* path, const char* new_file)
{
    // Find the last occurrence of the directory separator
    const char* last_sep = strrchr(path, PATH_SEP);

    // Calculate the length of the directory part
    size_t dir_length = (last_sep != NULL) ? (last_sep - path + 1) : 0;

    // Allocate memory for the new path
    size_t new_path_length = dir_length + strlen(new_file) + 1;
    char* new_path = (char*)malloc(new_path_length);

    if (new_path == NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Copy the directory part to the new path
    if (dir_length > 0)
    {
        strncpy(new_path, path, dir_length);
    }

    // Append the new file name
    strcpy(new_path + dir_length, new_file);

    return new_path;
}

//////////////////////// TABLE PRINTER HELPERS /////////////////////////////

void print_char_n_times(char ch, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c", ch);
    }
}

void table_print_border()
{
    printf("%s", FG_WHITE);
    printf("+");

    print_char_n_times('-', ID_COL_WIDTH);

    printf("+");

    print_char_n_times('-', DESCRIPTION_COL_WIDTH);

    printf("+");

    print_char_n_times('-', STATE_COL_WIDTH);

    puts("+");
    printf("%s", COLOR_RESET);
}

void table_print_title()
{
    printf("%s", FG_WHITE "| " FG_LGREEN);
    printf("%-*s ", ID_COL_WIDTH - 2, "Id");

    printf("%s", FG_WHITE "| " FG_LGREEN);
    printf("%-*s ", DESCRIPTION_COL_WIDTH - 2, "Description");

    printf("%s", FG_WHITE "| " FG_LGREEN);
    printf("%-*s ", STATE_COL_WIDTH - 2, "State");

    puts(FG_WHITE "|" COLOR_RESET);
}
