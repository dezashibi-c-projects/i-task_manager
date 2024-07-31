// ***************************************************************************************
//    Project: Task Manager (todo list) using Linked List
//    File: command_defs.h
//    Date: 2024-07-28
//    Author: Navid Dezashibi
//    Contact: navid@dezashibi.com
//    Website: https://www.dezashibi.com | https://github.com/dezashibi
//    License:
//     Please refer to the LICENSE file, repository or website for more information about
//     the licensing of this work. If you have any questions or concerns,
//     please feel free to contact me at the email address provided above.
// ***************************************************************************************
// *  Description: refer to readme file.
// ***************************************************************************************

#ifndef COMMAND_DEFS__H__
#define COMMAND_DEFS__H__

#include "command.h"

/**
 * @brief invoke function for `version` command
 *
 * This function prints build information
 *
 * @param cmd reference to the invoked command
 * @param argc command line argument count.
 * @param argv command line arguments.
 * @return 0
 */
def_invoke_fn_as(version_fn);

/**
 * @brief invoke function for `list` command
 *
 * Lists all the available task from the storage file
 *
 * @param cmd reference to the invoked command
 * @param argc command line argument count.
 * @param argv command line arguments.
 * @return void
 */
def_invoke_fn_as(list_fn);

/**
 * @brief invoke function for `add` command
 *
 * Adds a new task to the storage file and prints them all
 *
 * @param cmd reference to the invoked command
 * @param argc command line argument count.
 * @param argv command line arguments.
 * @return void
 */
def_invoke_fn_as(add_fn);

/**
 * @brief invoke function for `state` command
 *
 * changes the state for given task and prints them all
 *
 * @param cmd reference to the invoked command
 * @param argc command line argument count.
 * @param argv command line arguments.
 * @return void
 */
def_invoke_fn_as(state_fn);

/**
 * @brief invoke function for `add` command
 *
 * deletes the given task from the storage file and prints them all
 *
 * @param cmd reference to the invoked command
 * @param argc command line argument count.
 * @param argv command line arguments.
 * @return void
 */
def_invoke_fn_as(delete_fn);

#endif // COMMAND_DEFS__H__
