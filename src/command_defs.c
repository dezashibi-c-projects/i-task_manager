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
#include <limits.h>
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

    FILE* fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        fprintf(stderr, FG_RED "error: " COLOR_RESET "cannot open the storage file, please add a new task using `add` command first\n");
        free(file_name);
        exit(EXIT_FAILURE);
    }

    unsigned long long id;
    int state;
    char description[MAX_TOK_SIZE];

    while (fscanf(fp, "%llu \"%[^\"]\" %d", &id, description, &state) == 3)
    {
        // Validate the id (no need to check for negative as it's unsigned)
        if (id > ULLONG_MAX)
        {
            fprintf(stderr, FG_RED "Invalid id, exceeds maximum value: %llu\n" COLOR_RESET, id);
            continue;
        }

        // Validate the description
        if (strlen(description) <= 0 || strlen(description) >= MAX_TOK_SIZE)
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

        printf("Id: %lld\n", id);
        printf("Description: %s\n", description);
        printf("State: %d\n", state);
        printf("---------------------\n");
    }

    // Check if the loop ended due to an error in fscanf
    if (!feof(fp))
    {
        fprintf(stderr, FG_RED "Error reading the file or invalid format\n" COLOR_RESET);
    }

    free(file_name);
    fclose(fp);
}
