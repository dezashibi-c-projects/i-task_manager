// ***************************************************************************************
//    Project: Task Manager (todo list) using Linked List
//    File: task.h
//    Date: 2024-07-27
//    Author: Navid Dezashibi
//    Contact: navid@dezashibi.com
//    Website: https://www.dezashibi.com | https://github.com/dezashibi
//    License:
//     Please refer to the LICENSE file, repository or website for more information about
//     the licensing of this work. If you have any questions or concerns,
//     please feel free to contact me at the email address provided above.
// ***************************************************************************************
// *  Description: Header file including definition of `Task` type and `TaskNode`
// *               The iteration is going to be done through implementation a very basic
// *               Linked List.
// *               Read the readme file for more information
// ***************************************************************************************

#ifndef TASK__H__
#define TASK__H__

#include "utils.h"

#include <stdbool.h>
#include <stddef.h>

typedef enum
{
    NOT_STARTED,
    ON_GOING,
    DONE,
    CANCELLED,
} TaskState;

typedef struct Task
{
    unsigned long long id;
    char* description;
    TaskState state;
    struct Task* next;
} Task;

typedef struct
{
    Task* head;
    Task* tail;
    size_t size;
} TodoList;

Task* task_create(const char* description, size_t count);
void task_memory_cleanup(Task* task);
Task* todo_list_task_find_by_id(TodoList* todo_list, unsigned long long id, Task** previous);
bool todo_list_task_delete_by_id(TodoList* todo_list, unsigned long long id);
void todo_list_init(TodoList* todo_list);
void todo_list_insert_end(TodoList* todo_list, const char* description);

#endif // TASK__H__