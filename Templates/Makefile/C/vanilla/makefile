
CC = gcc

NAME = main

SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)

PKG_CONF = glib-2.0

CFLAGS = $(if $(PKG_CONF),$(shell pkg-config --cflags $(PKG_CONF))) -g
CFLAGS += -MMD -MP

LDFLAGS = $(if $(PKG_CONF),$(shell pkg-config --libs $(PKG_CONF))) -lrt -lm

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $< -c -o $@ $(CFLAGS)
	
run: all
	./$(NAME)
	
gdb: all
	gdb --args ./$(NAME)
	
valgrind: all
	valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all -v ./$(NAME)
	
-include $(OBJS:.o=.d)
