// ***************************************************************************************
//    Project: Task Manager (todo list) using Linked List
//    File: task.c
//    Date: 2024-07-27
//    Author: Navid Dezashibi
//    Contact: navid@dezashibi.com
//    Website: https://www.dezashibi.com | https://github.com/dezashibi
//    License:
//     Please refer to the LICENSE file, repository or website for more information about
//     the licensing of this work. If you have any questions or concerns,
//     please feel free to contact me at the email address provided above.
// ***************************************************************************************
// *  Description: Refer to the header file or read the readme file for more information
// ***************************************************************************************

#include "task.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Task* task_create(const char* description, size_t count)
{
    Task* new_task = malloc(sizeof(Task));
    if (new_task == NULL)
    {
        fprintf(stderr, "%s on %d: Memory allocation failed\n", __FILE__, __LINE__);
        exit(1);
    }

    new_task->id = generate_unique_id(count);
    new_task->state = NOT_STARTED;

    new_task->description = malloc((strlen(description) + 1) * sizeof(char));
    if (new_task->description == NULL)
    {
        fprintf(stderr, "%s on %d: Memory allocation failed\n", __FILE__, __LINE__);
        free(new_task);
        exit(1);
    }
    strcpy(new_task->description, description);

    new_task->next = NULL;

    return new_task;
}

void task_memory_cleanup(Task* task)
{
    free(task->description);
    free(task);
}

Task* todo_list_task_find_by_id(TodoList* todo_list, unsigned long long id, Task** previous)
{
    Task* current = todo_list->head;
    *previous = NULL;

    while (current != NULL)
    {
        if (current->id == id)
        {
            return current;
        }

        *previous = current;
        current = current->next;
    }

    return NULL; // Not Found
}

bool todo_list_task_delete_by_id(TodoList* todo_list, unsigned long long id)
{
    Task* previous = NULL;
    Task* task_to_delete = todo_list_task_find_by_id(todo_list, id, &previous);

    if (task_to_delete == NULL)
    {
        return false; // task not found
    }

    if (previous == NULL)
    {
        // Task to delete is the head;
        todo_list->head = task_to_delete->next;
    }
    else
    {
        previous->next = task_to_delete->next;
    }

    if (task_to_delete == todo_list->tail)
    {
        todo_list->tail = previous;
    }

    task_memory_cleanup(task_to_delete);
    todo_list->size--;

    return true;
}

void todo_list_init(TodoList* todo_list)
{
    todo_list->head = NULL;
    todo_list->tail = NULL;
    todo_list->size = 0;
}

void todo_list_insert_end(TodoList* todo_list, const char* description)
{
    Task* new_task = task_create(description, todo_list->size);

    if (todo_list->tail == NULL)
    {
        todo_list->head = todo_list->tail = new_task;
    }
    else
    {
        todo_list->tail->next = new_task;
        todo_list->tail = new_task;
    }

    todo_list->size++;
}
