CC = gcc
CFLAGS = -Wall -Wextra -std=c99

SRCS = my_custom_printf.c test.c
OBJS = $(SRCS:.c=.o)
EXEC = test

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
    $(CC) $(CFLAGS) -o $@ $^

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    $(RM) $(EXEC) $(OBJS)

