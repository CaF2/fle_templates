###########################################
#
#	Copyright (c) 2016 Florian Evaldsson
#
#	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
#	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
#	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
###########################################

NAME := prog_name

VERSION := 0.1

OUTPUT := $(NAME)

CC := gcc

SRCS := $(wildcard ./src/*.c)

BUILD_DIR := .build
INC_DIR := inc

PKG_CONF_LIBS := 

CFLAGS := -g -Wall
CFLAGS += $(shell pkg-config --cflags $(PKG_CONF_LIBS))
CFLAGS += -I./inc -I./inc/gen

LDFLAGS := $(shell pkg-config --libs $(PKG_CONF_LIBS))
LDFLAGS += -shared

OBJS := $(addprefix $(BUILD_DIR)/,$(notdir $(SRCS:.c=.o)))
HEADERS := $(addprefix $(INC_DIR)/gen/,$(notdir $(SRCS:.c=.h)))

DEPS := $(OBJS:.o=.d)

########### TARGETS ETC ###########

all: $(OUTPUT)
	
$(OUTPUT): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o: src/%.c $(HEADERS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -MT $@ -MMD -MF $(BUILD_DIR)/$*.d -c $< -o $@

inc/gen:
	mkdir -p $@
	
inc/gen/%.h: src/%.c | inc/gen
	@$(shell OUT=$$(makeheaders -h $<); if ! [ "$$OUT" == "$$(cat $@)" ]; then echo "$$OUT" > $@;echo "echo 'generating $@...'"; fi)

clean:
	rm -f $(OBJS) $(OUTPUT) $(HEADERS)

run: $(OUTPUT)
	./$<
	
valgrind: all
	valgrind --track-origins=yes --tool=memcheck --leak-check=full --show-leak-kinds=all ./$(NAME)
	
gdb:
	gdb --args ./run

-include $(DEPS)

