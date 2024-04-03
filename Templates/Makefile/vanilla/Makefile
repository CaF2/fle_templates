###########################################
#
#	Copyright (c) 2024 Florian Evaldsson
#
#	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
#	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
#	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
###########################################

-include user.mk

CC = gcc
CXX = g++

NAME = main

ARGS =

SRCS_C = $(wildcard *.c)
SRCS_CPP = $(wildcard *.cpp)

OBJS = $(SRCS_CPP:=.o) $(SRCS_C:=.o)

PKG_CONF = glib-2.0

CFLAGS = $(if $(PKG_CONF),$(shell pkg-config --cflags $(PKG_CONF))) -g
CFLAGS += -MMD -MP

CXXFLAGS = $(if $(PKG_CONF),$(shell pkg-config --cflags $(PKG_CONF))) -g
CXXFLAGS += -MMD -MP

LDFLAGS = $(if $(PKG_CONF),$(shell pkg-config --libs $(PKG_CONF))) -lrt -lm

CFLAGS += $(if $(NO_ASAN),,-fsanitize=address)
CXXFLAGS += $(if $(NO_ASAN),,-fsanitize=address)
LDFLAGS += $(if $(NO_ASAN),,-fsanitize=address)

###########

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)

%.c.o: %.c
	$(CC) $< -c -o $@ $(CFLAGS)
	
%.cpp.o: %.cpp
	$(CXX) $< -c -o $@ $(CXXFLAGS)
	
run: all
	./$(NAME) $(ARGS)
	
gdb: all
	gdb --args ./$(NAME) $(ARGS)

lldb: all
	lldb -- ./$(NAME) $(ARGS)
	
valgrind: all
	valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all -v --log-file="$(NAME).valgrind.txt" ./$(NAME) $(ARGS)

-include $(OBJS:.o=.d)
