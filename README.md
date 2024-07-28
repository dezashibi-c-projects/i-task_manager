# Task Manager (todo list) using Linked List

I want to create a Task Manager application in C. This application will manage a list of tasks, allowing users to add, remove, display, save, and load tasks from a file.
Each task will have a description and a status (e.g., pending or completed).
The application will utilize a linked list to manage tasks dynamically, ensuring efficient memory usage and easy management of tasks.

## Design Decisions

I would go for `enum` over boolean for task's state as it's going to be more fun and I can use colors for each state.

So here's the `enum` for task's state:

```c
typedef enum
{
    NOT_STARTED,
    ON_GOING,
    DONE,
    CANCELLED,
} TaskState;
```

Here's the `Task` struct and the Linked List:

```c
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
```

**NOTE:** I would use a unique id generator based on date and time in an `unsigned long long` number field to address tasks instead of searching and comparing the descriptions.

## Introducing memory check and improving `Makefile`

It's a good time to use the good old friend `valgrind` as this project involves various memory allocations and de-allocations. also as using `valgrind` needs debug symbols to be available `-g`
then I thought "well, I might want to have my executable optimized" so with that in mind, I've tweaked and improved my `Makefile` to support for these new targets: `release`, `memcheck`.

The `obj` folder now holds object files for different targets (`debug` and `release`) separately, the default build is for sure `debug` that is built into `all` target.

Running `make memcheck` ensures that I've got no memory leaked:

```bash
valgrind --leak-check=yes build/todo_c.exe
==20928== Memcheck, a memory error detector
==20928== Copyright (C) 2002-2024, and GNU GPL'd, by Julian Seward et al.
==20928== Using Valgrind-3.23.0 and LibVEX; rerun with -h for copyright info
==20928== Command: build/todo_c.exe
==20928== 
Todo list contents:
ID: 20240728085122, I go to school
ID: 20240728085123, I go to gym
ID: 20240728085124, I go everywhere!
task deleted successfully
Todo list contents after deletion:
ID: 20240728085123, I go to gym
ID: 20240728085124, I go everywhere!
==20928== 
==20928== HEAP SUMMARY:
==20928==     in use at exit: 0 bytes in 0 blocks
==20928==   total heap usage: 15 allocs, 15 frees, 6,489 bytes allocated
==20928== 
==20928== All heap blocks were freed -- no leaks are possible
==20928== 
==20928== For lists of detected and suppressed errors, rerun with: -s
==20928== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

## Dealing with data

I want to make this a command line tool something with various commands that uses a specific file close to itself to save and load data:

- `list` lists all the data if there is no file available or there is no entry it returns `No Entry - please use 'add' command to add new task`
- `add` this commands receives a description which must be sent inside double quotes, then it generates a new entry and returns the task id as well. one other option can be to list the tasks all and highlight the newly created task which is more fun so I will go for this.
- `state` sets the state of the given task id to the given state: 0 is not started, 1 is on going, 2 is done and 3 is cancelled. any other values or wrong task id will show proper error messages.
- `edit` gets task id and description and will change the task's description.
- `delete` gets task id and delete it while returns its last content including id, description and state.
- `reset` first shows the tasks to be deleted, then asks the user if they are sure about this, and if so all the tasks will be deleted.

**NOTE:** Not only after adding a new task but after each operation the overall list of tasks will be displayed.

**NOTE2:** I would also to colorize task's state like one specific color per state.

**NOTE3:** I will use background color for the newly added or changed tasks.
