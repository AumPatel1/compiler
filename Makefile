# Define the compiler to use
CC = gcc

# Define any compile-time flags
CFLAGS = -Wall -g

# Define the target executable
TARGET = Compiler

# Define the source files
SRCS = Compilers.c Reader.c MainReader.c

# Define the object files
OBJS = $(SRCS:.c=.o)

# Define the header files
HEADERS = Compilers.h Reader.h

# Default rule
all: $(TARGET)

# Rule to link the object files into the target executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the project
clean:
	rm -f $(OBJS) $(TARGET)
