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
#include "colors.h"
#include "utils.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FORMAT "%llu \"%[^\"]\" %d"

Task* task_create(unsigned long long id, const char* description, TaskState state, size_t count)
{
    Task* new_task = malloc(sizeof(Task));
    if (new_task == NULL)
    {
        fprintf(stderr, "%s on %d: Memory allocation failed\n", __FILE__, __LINE__);
        exit(1);
    }

    new_task->id = id == 0 ? generate_unique_id(count) : id;
    new_task->state = state;

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

void todo_list_insert_end(TodoList* todo_list, Task* task)
{
    if (todo_list->tail == NULL)
    {
        todo_list->head = todo_list->tail = task;
    }
    else
    {
        todo_list->tail->next = task;
        todo_list->tail = task;
    }

    todo_list->size++;
}

void task_print(Task* task, bool highlighted)
{
    if (highlighted)
        printf("%s", BG_BLUE);

    printf("%s", FG_WHITE "| " FG_LBLUE);
    printf("%-*lld ", ID_COL_WIDTH - 2, task->id);

    printf("%s", FG_WHITE "| " FG_GRAY);
    printf("%-*s ", DESCRIPTION_COL_WIDTH - 2, task->description);

    printf("%s", FG_WHITE "| ");

    switch (task->state)
    {
    case NOT_STARTED:
        printf("%s", FG_GRAY);
        printf("%-*s ", STATE_COL_WIDTH - 2, "Not Started");
        break;

    case ON_GOING:
        printf("%s", FG_YELLOW);
        printf("%-*s ", STATE_COL_WIDTH - 2, "On Going");
        break;

    case DONE:
        printf("%s", FG_GREEN);
        printf("%-*s ", STATE_COL_WIDTH - 2, "Done");
        break;

    case CANCELLED:
        printf("%s", FG_RED);
        printf("%-*s ", STATE_COL_WIDTH - 2, "Cancelled");
        break;

    default:
        break;
    }

    puts(FG_WHITE "|" COLOR_RESET);
}

void todo_list_print(TodoList* todo_list, Task* highlighted_task)
{
    table_print_border();
    table_print_title();
    table_print_border();

    Task* current = todo_list->head;
    while (current != NULL)
    {
        task_print(current, (highlighted_task != NULL && current->id == highlighted_task->id) ? true : false);

        current = current->next;
    }

    table_print_border();

    // Total Row
    printf("%s", FG_WHITE "| " FG_LGREEN);

    char total[ID_COL_WIDTH];
    snprintf(total, ID_COL_WIDTH - 1, "Total: %zu", todo_list->size);
    total[ID_COL_WIDTH] = '\0';
    printf("%-*s ", ID_COL_WIDTH - 2, total);

    printf("%s", FG_WHITE "  " FG_LGREEN);
    printf("%-*s ", DESCRIPTION_COL_WIDTH - 2, " ");

    printf("%s", FG_WHITE "  " FG_LGREEN);
    printf("%-*s ", STATE_COL_WIDTH - 2, " ");

    puts(FG_WHITE "|" COLOR_RESET);

    table_print_border();
}

void todo_list_load_from_file(TodoList* todo_list, const char* file_name)
{
    FILE* fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        fprintf(stderr, FG_RED "error: " COLOR_RESET "cannot open the storage file, please add a new task using `add` command first\n");
        return;
    }

    unsigned long long id;
    int state;
    char description[DESCRIPTION_COL_WIDTH];

    while (fscanf(fp, DATA_FORMAT, &id, description, &state) == 3)
    {
        // Validate the id (no need to check for negative as it's unsigned)
        if (id > ULLONG_MAX)
        {
            fprintf(stderr, FG_RED "Invalid id, exceeds maximum value: %llu\n" COLOR_RESET, id);
            continue;
        }

        // Validate the description
        if (strlen(description) <= 0 || strlen(description) >= DESCRIPTION_COL_WIDTH)
        {
            fprintf(stderr, FG_RED "Invalid description: %s\n" COLOR_RESET, description);
            continue;
        }

        // Validate state
        if (state < NOT_STARTED || state > CANCELLED)
        {
            fprintf(stderr, FG_RED "Invalid state: %d, it must be 0, 1, 2 or 3\n" COLOR_RESET, state);
            continue;
        }

        Task* new_task = task_create(id, description, state, todo_list->size);
        todo_list_insert_end(todo_list, new_task);
    }

    // Check if the loop ended due to an error in fscanf
    if (!feof(fp))
    {
        fprintf(stderr, FG_RED "Error reading the file or invalid format\n" COLOR_RESET);
    }

    fclose(fp);
}
