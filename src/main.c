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

    for (int i = 0; i < argc; ++i)
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

// #include <stdio.h>
// #include <stdlib.h>

// void print_todo(TodoList* todo)
// {
//     Task* current = todo->head;
//     while (current != NULL)
//     {
//         printf("ID: %llu, %s\n", current->id, current->description);
//         current = current->next;
//     }
// }

// int main(void)
// {
//     TodoList todo;

//     todo_list_init(&todo);

//     todo_list_insert_end(&todo, "I go to school");
//     todo_list_insert_end(&todo, "I go to gym");
//     todo_list_insert_end(&todo, "I go everywhere!");

//     puts("Todo list contents:");
//     print_todo(&todo);

//     if (todo_list_task_delete_by_id(&todo, todo.head->id))
//     {
//         puts("task deleted successfully");
//     }
//     else
//     {
//         puts("task not found");
//     }

//     puts("Todo list contents after deletion:");
//     print_todo(&todo);

//     while (todo.head != NULL)
//     {
//         Task* temp = todo.head;
//         todo.head = todo.head->next;
//         task_memory_cleanup(temp);
//     }

//     return 0;
// }