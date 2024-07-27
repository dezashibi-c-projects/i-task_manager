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
#include <stdio.h>
#include <stdlib.h>

void print_todo(TodoList* todo)
{
    Task* current = todo->head;
    while (current != NULL)
    {
        printf("ID: %llu, %s\n", current->id, current->description);
        current = current->next;
    }
}

int main(void)
{
    TodoList todo;

    todo_list_init(&todo);

    todo_list_insert_end(&todo, "I go to school");
    todo_list_insert_end(&todo, "I go to gym");
    todo_list_insert_end(&todo, "I go everywhere!");

    puts("Todo list contents:");
    print_todo(&todo);

    if (task_delete(&todo, todo.head->id))
    {
        puts("task deleted successfully");
    }
    else
    {
        puts("task not found");
    }

    puts("Todo list contents after deletion:");
    print_todo(&todo);

    while (todo.head != NULL)
    {
        Task* temp = todo.head;
        todo.head = todo.head->next;
        free(temp->description);
        free(temp);
    }

    return 0;
}