# Makefile for the ARTAMS CLI Project

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I./core
LDFLAGS = -lm

# Source directories
CORE_DIR = core
CLI_DIR = cli

# Source files
CORE_SRCS = $(wildcard $(CORE_DIR)/*.c)
CLI_SRCS = $(wildcard $(CLI_DIR)/*.c)
SRCS = $(CORE_SRCS) $(CLI_SRCS)

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = artams_cli

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)
	rm -f core/*.o cli/*.o

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run
