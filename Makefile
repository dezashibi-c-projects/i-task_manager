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
DEBUGFLAGS = -g -O0
RELEASEFLAGS = -O2
CFLAGS = -Wall -Wextra -pedantic

# Executable name
TARGET = todo_c.exe

# Directories
SRCDIR = src
OBJDIR = obj
BUILDDIR = build
RELEASEDIR = release
DEBUGOBJDIR = $(OBJDIR)/debug
RELEASEOBJDIR = $(OBJDIR)/release

# Source files
SRCS = $(wildcard $(SRCDIR)/*.c)

# Object files
DEBUGOBJS = $(patsubst $(SRCDIR)/%.c,$(DEBUGOBJDIR)/%.o,$(SRCS))
RELEASEOBJS = $(patsubst $(SRCDIR)/%.c,$(RELEASEOBJDIR)/%.o,$(SRCS))

BUILDCMD = $(CC) $(CFLAGS)
BUILDDEBUG = $(BUILDCMD) $(DEBUGFLAGS)
BUILDRELEASE = $(BUILDCMD) $(RELEASEFLAGS)

# Memory check via valgrind works on Linux only
VALGRINDCMD = valgrind --leak-check=yes $(BUILDDIR)/$(TARGET)

ifeq ($(OS),Windows_NT)
	VALGRINDCMD = @echo "sorry, valgrind does not work on windows, please consider using WSL or a Linux machine."
endif

# Default target
all: $(BUILDDIR)/$(TARGET)

# Run the target
run: $(BUILDDIR)/$(TARGET)
	./$(BUILDDIR)/$(TARGET)

# Rule to link the object files and create the executable (debug)
$(BUILDDIR)/$(TARGET): $(DEBUGOBJS)
	mkdir -p $(BUILDDIR)
	$(BUILDDEBUG) -o $@ $(DEBUGOBJS)

# Rule to compile source files into object files (debug)
$(DEBUGOBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(DEBUGOBJDIR)
	$(BUILDDEBUG) -c $< -o $@

# Rule to link the object files and create the executable (release)
$(RELEASEDIR)/$(TARGET): $(RELEASEOBJS)
	mkdir -p $(RELEASEDIR)
	$(BUILDRELEASE) -o $@ $(RELEASEOBJS)

# Rule to compile source files into object files (release)
$(RELEASEOBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(RELEASEOBJDIR)
	$(BUILDRELEASE) -c $< -o $@

# Uses valgrind to check the debug build for memory leaks
memcheck: $(BUILDDIR)/$(TARGET)
	$(VALGRINDCMD)

release: $(RELEASEDIR)/$(TARGET)

# Clean up the build/release files
clean:
	rm -f $(BUILDDIR)/$(TARGET) $(DEBUGOBJS) $(RELEASEOBJS)
	rm -rf $(OBJDIR) $(BUILDDIR) $(RELEASEDIR)

# Phony targets
.PHONY: all run clean memcheck release
