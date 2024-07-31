// ***************************************************************************************
//    Project: Task Manager (todo list) using Linked List
//    File: main.c
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

#include "task.h"

#include "colors.h"
#include "command.h"
#include "command_defs.h"
#include "global.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

def_commands = {
    {"version", "shows version and build information", version_fn},
    {"list", "Lists all the available tasks from the todo storage in a table.", list_fn},
    {"add", "Adds a new task with the given description, be sure to put description in double quotes\n<id> \"<description in double quote>\"", add_fn},
    {"state", "Changes the state of given task id, <id> <new state>, states are 0, 1, 2, 3 as Not Started, On Going, Done and Cancelled", state_fn},
    {"delete", "Deletes the passed task by its id <id>", delete_fn},
};
def_commands_size = (sizeof(commands) / sizeof(commands[0]));

int main(int argc, char* argv[])
{
    puts("Task Manager (todo list) using Linked List");

    if (argc < 2)
    {
        puts(FG_RED "error: " COLOR_RESET "not enough number of arguments\n\t" FG_GREEN "./todo_c.exe <op> <...args>\n" COLOR_RESET);

        show_help();

        return -1;
    }

    Command* cmd = get_command(argv[1]);

    if (cmd == NULL)
    {
        printf(FG_RED "error: " COLOR_RESET "command '%s' not found\n", argv[1]);

        show_help();

        return -1;
    }

    line_token_t temp_argv;
    bool must_fail = false;

    check_argc_size(argc, false);

    strcpy(temp_argv[0], argv[0]);
    strcpy(temp_argv[1], argv[1]);

    for (int i = 2; i < argc; ++i)
    {

        check_token_size(argv[i], false);

        strcpy(temp_argv[i], argv[i]);
    }

    if (must_fail)
        return -1;

    cmd->invoke(cmd, argc, temp_argv);

cleanup:
    return 0;
}
