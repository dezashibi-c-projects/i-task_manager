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

/**
 * @brief generates unique id number based on date and time
 *
 * It works on windows and POSIX systems.
 * `NOTE: To make it more unique I've added the total size
 * of the linked list to the generated number`
 */
unsigned long long generate_unique_id(size_t seed);

#endif // UTILS__H__