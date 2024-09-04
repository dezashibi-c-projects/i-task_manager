// ***************************************************************************************
//    Project: Task Manager (todo list) using Linked List
//    File: utils.h
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

#ifndef UTILS__H__
#define UTILS__H__

#include <stddef.h>

#ifdef _WIN32
#define PATH_SEP '\\'
#else
#define PATH_SEP '/'
#endif

#define ID_COL_WIDTH 16
#define DESCRIPTION_COL_WIDTH 40
#define STATE_COL_WIDTH 15

/**
 * @brief generates unique id number based on date and time
 *
 * It works on windows and POSIX systems.
 * `NOTE: To make it more unique I've added the total size
 * of the linked list to the generated number`
 */
unsigned long long generate_unique_id(size_t seed);

/**
 * @brief Function to replace the file part of a path with a new file name
 *
 * @param path a path to a file
 * @param new_file file name that must be replaced with current file name in `path`
 *
 * @return allocated `char*` result
 *
 * `NOTE: it allocates memory`
 */
char* replace_file_in_path(const char* path, const char* new_file);

//////////////////////// TABLE PRINTER HELPERS /////////////////////////////

void print_char_n_times(char ch, int n);

void table_print_border();

void table_print_title();

#endif // UTILS__H__
