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
        fprintf(stderr, "%s on %s: Memory allocation failed\n", __FILE__, __LINE__);
        exit(1);
    }

    new_task->id = generate_unique_id(count);

    new_task->description = malloc((strlen(description) + 1) * sizeof(char));
    if (new_task->description == NULL)
    {
        fprintf(stderr, "%s on %s: Memory allocation failed\n", __FILE__, __LINE__);
        free(new_task);
        exit(1);
    }
    strcpy(new_task->description, description);

    new_task->next = NULL;

    return new_task;
}

bool task_delete(TodoList* todo, unsigned long long id)
{
    Task* current = todo->head;
    Task* previous = NULL;

    while (current != NULL)
    {
        if (current->id == id)
        {
            if (previous == NULL)
            {
                // Node to delete is the head
                todo->head = current->next;
            }
            else
            {
                previous->next = current->next;
            }

            if (current == todo->tail)
            {
                todo->tail = previous;
            }

            free(current);
            todo->size--;

            return true; // deletion is successful
        }

        previous = current;
        current = current->next;
    }

    return false; // task was not found
}

void todo_list_init(TodoList* todo)
{
    todo->head = NULL;
    todo->tail = NULL;
    todo->size = 0;
}

void todo_list_insert_end(TodoList* todo, const char* description)
{
    Task* new_task = task_create(description, todo->size);

    if (todo->tail == NULL)
    {
        todo->head = todo->tail = new_task;
    }
    else
    {
        todo->tail->next = new_task;
        todo->tail = new_task;
    }

    todo->size++;
}
