// ***************************************************************************************
//    Project: Task Manager (todo list) using Linked List
//    File: command_defs.c
//    Date: 2024-07-28
//    Author: Navid Dezashibi
//    Contact: navid@dezashibi.com
//    Website: https://www.dezashibi.com | https://github.com/dezashibi
//    License:
//     Please refer to the LICENSE input_file, repository or website for more information about
//     the licensing of this work. If you have any questions or concerns,
//     please feel free to contact me at the email address provided above.
// ***************************************************************************************
// *  Description: refer to readme input_file.
// ***************************************************************************************

#include "command_defs.h"
#include "colors.h"
#include "command.h"
#include "task.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define STORAGE_FILE "todo_storage.txt"

def_invoke_fn_as(version_fn)
{
    (void)cmd;
    (void)argc;
    (void)argv;

    puts(FG_LRED "Version: 1.0.0" COLOR_RESET);
    puts(FG_LGREEN "Programmed by Navid Dezashibi" COLOR_RESET);
    puts(FG_LGREEN "Built on: "__DATE__
                   " - "__TIME__ COLOR_RESET);
}

def_invoke_fn_as(list_fn)
{
    (void)cmd;

    do_arg_check(2);
    (void)arg_starts_at;

    // make sure the storage file is close to the executable
    char* file_name = replace_file(argv[0], STORAGE_FILE);

    TodoList todo_list;
    todo_list_init(&todo_list);

    todo_list_load_from_file(&todo_list, file_name);

    free(file_name);

    todo_list_print(&todo_list, NULL);

    while (todo_list.head != NULL)
    {
        Task* temp = todo_list.head;
        todo_list.head = todo_list.head->next;
        task_memory_cleanup(temp);
    }
}

def_invoke_fn_as(add_fn)
{
    (void)cmd;

    do_arg_check(3);

    // make sure the storage file is close to the executable
    char* file_name = replace_file(argv[0], STORAGE_FILE);

    TodoList todo_list;
    todo_list_init(&todo_list);

    todo_list_load_from_file(&todo_list, file_name);

    Task* new_task = task_create(0, argv[arg_starts_at], NOT_STARTED, todo_list.size);
    todo_list_insert_end(&todo_list, new_task);

    todo_list_print(&todo_list, new_task);

    // update the storage file
    todo_list_save_to_file(&todo_list, file_name);

    free(file_name);

    while (todo_list.head != NULL)
    {
        Task* temp = todo_list.head;
        todo_list.head = todo_list.head->next;
        task_memory_cleanup(temp);
    }
}

def_invoke_fn_as(state_fn)
{
    (void)cmd;

    do_arg_check(4);

    // make sure the storage file is close to the executable
    char* file_name = replace_file(argv[0], STORAGE_FILE);

    TodoList todo_list;
    todo_list_init(&todo_list);

    todo_list_load_from_file(&todo_list, file_name);

    int new_state;
    unsigned long long id;

    sscanf(argv[arg_starts_at], "%llu", &id);
    sscanf(argv[arg_starts_at + 1], "%d", &new_state);

    printf("%d, %llu, %d\n", arg_starts_at, id, new_state);

    Task* previous = NULL;
    Task* task = todo_list_task_find_by_id(&todo_list, id, &previous);
    if (task == NULL)
    {
        puts(FG_RED "error: " COLOR_RESET "task not found");
        todo_list_print(&todo_list, task);
        goto cleanup;
    }
    task->state = new_state;

    todo_list_print(&todo_list, task);

    // update the storage file
    todo_list_save_to_file(&todo_list, file_name);

cleanup:
    free(file_name);

    while (todo_list.head != NULL)
    {
        Task* temp = todo_list.head;
        todo_list.head = todo_list.head->next;
        task_memory_cleanup(temp);
    }
}

def_invoke_fn_as(delete_fn)
{
    (void)cmd;

    do_arg_check(3);

    // make sure the storage file is close to the executable
    char* file_name = replace_file(argv[0], STORAGE_FILE);

    TodoList todo_list;
    todo_list_init(&todo_list);

    todo_list_load_from_file(&todo_list, file_name);

    unsigned long long id;
    sscanf(argv[arg_starts_at], "%llu", &id);

    bool result = todo_list_task_delete_by_id(&todo_list, id);

    if (!result)
    {
        puts(FG_RED "error: " COLOR_RESET "task not found");
        todo_list_print(&todo_list, NULL);
        goto cleanup;
    }

    todo_list_print(&todo_list, NULL);

    // update the storage file
    todo_list_save_to_file(&todo_list, file_name);

cleanup:
    free(file_name);

    while (todo_list.head != NULL)
    {
        Task* temp = todo_list.head;
        todo_list.head = todo_list.head->next;
        task_memory_cleanup(temp);
    }
}