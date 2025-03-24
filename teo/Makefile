CC = gcc  // defines a variable which specifies the compiler used
CFLAGS = -Wall -Wextra -std=c99   // the compiler flags

SRCS = my_custom_printf.c main.c  //the source files
OBJS = $(SRCS:.c=.o) //which specifies the object files to be created from the source files
TARGET = custom_printf_test // the name of the executable

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

clean:  // a rule that specifies how to clean up the project directory by removing generated files.
    rm -f $(OBJS) $(TARGET)
//