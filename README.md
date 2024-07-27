# Task Manager (todo list) using Linked List

I want to create a Task Manager application in C. This application will manage a list of tasks, allowing users to add, remove, display, save, and load tasks from a file.
Each task will have a description and a status (e.g., pending or completed).
The application will utilize a linked list to manage tasks dynamically, ensuring efficient memory usage and easy management of tasks.

## Design Decisions

I would go for `enum` over boolean as it's going to be more fun. so:

```c
typedef enum
{
    NOT_STARTED,
    ON_GOING,
    DONE,
    CANCELLED,
} TaskState;
```
