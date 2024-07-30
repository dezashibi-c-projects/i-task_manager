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

/**
 * @brief Create a task object
 *
 * Creates and allocates memory for a new `Task` instance
 *
 * @param description the description for the new task
 * @param size_t count the number of total tasks so far
 *
 * @return a pointer to newly created `Task` with allocated memory
 *
 * `Note: it allocates memory`
 */
Task* task_create(const char* description, size_t count);

/**
 * @brief Frees the task memory
 *
 * @param task pointer to the task to be freed
 */
void task_memory_cleanup(Task* task);

/**
 * @brief Finds and returns a task by its id
 *
 * @param todo_list the TodoList Linked List
 * @param id the id of the task to be found
 * @param previous pointer to the previous member in the Linked List for further determination of the placement
 *
 * @return pointer to the found task
 */
Task* todo_list_task_find_by_id(TodoList* todo_list, unsigned long long id, Task** previous);

/**
 * @brief Deletes a task by its id
 *
 * @param todo_list the TodoList Linked List
 * @param id the id of the task to be deleted
 *
 * @returns whether the task was found and deleted or its not found
 */
bool todo_list_task_delete_by_id(TodoList* todo_list, unsigned long long id);

/**
 * @brief Initializes the TodoList to make it ready for usage
 *
 * @param todo_list a pointer to the newly defined TodoList instance variable
 */
void todo_list_init(TodoList* todo_list);

/**
 * @brief Creates and inserts a new task with passed description in the passed todo_list
 *
 * @param todo_list
 * @param description
 */
void todo_list_insert_end(TodoList* todo_list, const char* description);

/**
 * @brief Prints the formatted table of the passed pointer to the TodoList
 *
 * @param todo_list
 */
void todo_list_print(TodoList* todo_list);

/**
 * @brief Reads data from the todo list storage file and fills the passed pointer to TodoList
 *
 * @param todo_list
 */
void todo_list_load_from_file(TodoList* todo_list);

#endif // TASK__H__