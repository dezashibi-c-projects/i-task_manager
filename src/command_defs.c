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
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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

    do_arg_check(3);

    for (int i = arg_starts_at; i < argc; ++i)
    {
        printf("%s\n", argv[i]);
    }
}
