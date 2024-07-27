# ***************************************************************************************
#    Project: Task Manager (todo list) using Linked List
#    File: Makefile
#    Date: 2024-07-27
#    Author: Navid Dezashibi
#    Contact: navid@dezashibi.com
#    Website: https://www.dezashibi.com | https://github.com/dezashibi
#    License:
#     Please refer to the LICENSE file in the repository or website for more information
#     about the licensing of this work. If you have any questions or concerns,
#     please feel free to contact me at the email address provided above.
# ***************************************************************************************
# *  Description: Read the readme file for more information
# ***************************************************************************************

# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -pedantic

# Executable name
TARGET = todo_c.exe

# Directories
SRCDIR = src
OBJDIR = obj
BUILDDIR = build

# Source files
SRCS = $(wildcard $(SRCDIR)/*.c)

# Object files
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

# Default target
all: $(BUILDDIR)/$(TARGET)

# Run the target
run: $(BUILDDIR)/$(TARGET)
	./$(BUILDDIR)/$(TARGET)

# Rule to link the object files and create the executable
$(BUILDDIR)/$(TARGET): $(OBJS)
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# Rule to compile source files into object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the build files
clean:
	rm -f $(BUILDDIR)/$(TARGET) $(OBJS)
	rm -rf $(OBJDIR) $(BUILDDIR)

# Phony targets
.PHONY: all clean
