###########################################
#
#	Copyright (c) 2024 Florian Evaldsson
#
#	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
#	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
#	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
###########################################

CC = gcc

LIB_DIR = lib
BIN_DIR = bin

############################
# FUNCTIONS
############################

ifndef NOUSERMK
-include user.mk
endif

DECLARE_LIB_VARIABLES = \
	$(eval $(1)_LIB_SHARED_OBJECT = $(LIB_DIR)/lib$($(1)_LIB_NAME).so) \
	$(eval $(1)_LIB_STATIC_OBJECT = $(LIB_DIR)/lib$($(1)_LIB_NAME).a)
	
DECLARE_BIN_VARIABLES = \
	$(eval $(1)_BIN_EXE = $(BIN_DIR)/$($(1)_BIN_NAME))

GET_OBJ_FILES_POST=$(foreach VV,$(subst /source/,/obj/,$(1)),$(if $(findstring $(2),$(VV)),$(VV),$(2)/obj/$(VV)))
GET_OBJ_FILES=$(call GET_OBJ_FILES_POST,$(1:=.o),$(2))

############################
# COMMON FLAGS
############################

COMMON_PKG_CONF = glib-2.0

COMMON_CFLAGS = $(if $(COMMON_PKG_CONF),$(shell pkg-config --cflags $(COMMON_PKG_CONF))) -g
COMMON_CFLAGS += -MMD -MP

COMMON_LDFLAGS = $(if $(COMMON_PKG_CONF),$(shell pkg-config --libs $(COMMON_PKG_CONF))) -lrt -lm -L$(LIB_DIR)

COMMON_CFLAGS += $(if $(NO_ASAN),,-fsanitize=address)
COMMON_LDFLAGS += $(if $(NO_ASAN),,-fsanitize=address)

############################
# PROGRAM LIBRARIES
############################

PROC = USRLIB1

$(PROC)_LIB_NAME = usrlib1

$(PROC)_LIB_DIR = common/usrlib1

$(PROC)_LIB_SRCS = $(wildcard $($(PROC)_LIB_DIR)/src/*.c)

$(PROC)_LIB_OBJS = $(call GET_OBJ_FILES,$($(PROC)_BIN_SRCS),$($(PROC)_BIN_DIR))

$(PROC)_LIB_CFLAGS =
$(PROC)_LIB_LDFLAGS =

$(PROC)_LIB_EXPORT_CFLAGS = -I$($(PROC)_LIB_DIR)/include
$(PROC)_LIB_EXPORT_LDFLAGS =

$(call DECLARE_LIB_VARIABLES,$(PROC))

############################
# PROGRAM BINARIES
############################

PROC = USRBINARY1

$(PROC)_BIN_NAME = usrbinary1
$(PROC)_BIN_ARGS = 

$(PROC)_BIN_DIR = usrbinary1

$(PROC)_BIN_SRCS = $(wildcard $($(PROC)_BIN_DIR)/src/*.c)

$(PROC)_BIN_OBJS = $(call GET_OBJ_FILES,$($(PROC)_BIN_SRCS),$($(PROC)_BIN_DIR))


$(PROC)_BIN_BUILD_DEPS = $($(PROC)_LIB_STATIC_OBJECT)

$(PROC)_BIN_CFLAGS = $($(PROC)_LIB_EXPORT_CFLAGS)
$(PROC)_BIN_LDFLAGS = $($(PROC)_LIB_EXPORT_LDFLAGS)

############################
# COMPILATION VARIABLES
############################

BINARIES = USRBINARY1
LIBRARIES = USRLIB1

CLEAN_FILES =

all: $(foreach VV,$(BINARIES),$($(VV)_BIN_NAME))

%/obj:
	mkdir -p $@
	
$(BIN_DIR) $(LIB_DIR):
	mkdir -p $@

###

define GENERATE_LIBRARY_COMPILE
$(call GET_OBJ_FILES,$(2)/source/%.c,$($(1)_LIB_DIR)): $(2)/source/%.c $($(1)_LIB_MAKE_CC_DEPS) | $(patsubst %/,%,$(call GET_OBJ_FILES_POST,$(2)/source/,$($(1)_LIB_DIR))) $($(1)_LIB_CREATE_DIRS)
	$(CC) $$< -c -o $$@ $($(1)_LIB_CFLAGS) $(COMMON_CFLAGS) -I$($(1)_LIB_DIR)/include
	
$(call GET_OBJ_FILES,$(2)/source/%.cpp,$($(1)_LIB_DIR)): $(2)/source/%.cpp $($(1)_LIB_MAKE_CC_DEPS) | $(patsubst %/,%,$(call GET_OBJ_FILES_POST,$(2)/source/,$($(1)_LIB_DIR))) $($(1)_LIB_CREATE_DIRS)
	$(CXX) $$< -c -o $$@ $($(1)_LIB_CXXFLAGS) $(COMMON_CXXFLAGS) -I$($(1)_LIB_DIR)/include
endef

define GENERATE_LIBRARY
$(eval $(1)_LIB_SHARED_OBJECT = $(LIB_DIR)/lib$($(1)_LIB_NAME).so)
$(eval $(1)_LIB_STATIC_OBJECT = $(LIB_DIR)/lib$($(1)_LIB_NAME).a)
CLEAN_FILES += $($(1)_LIB_SHARED_OBJECT) $($(1)_LIB_STATIC_OBJECT)  $($(1)_LIB_OBJS) $($(1)_LIB_OBJS:.o=.d)

$($(1)_LIB_CREATE_DIRS):
	mkdir -p $$@

.PHONY: $($(1)_LIB_NAME)
$($(1)_LIB_NAME): $(LIB_DIR)/lib$($(1)_LIB_NAME).so $(LIB_DIR)/lib$($(1)_LIB_NAME).a

$($(1)_LIB_SHARED_OBJECT): $($(1)_LIB_OBJS) $($(1)_LIB_BUILD_DEPS) $($(1)_LIB_MAKE_DEPS) | $(LIB_DIR)
	$(CXX) $($(1)_LIB_OBJS) $($(1)_LIB_BUILD_DEPS) -shared -o $$@ $(COMMON_LDFLAGS) $($(1)_LIB_LDFLAGS)

$($(1)_LIB_STATIC_OBJECT): $($(1)_LIB_OBJS) $($(1)_LIB_BUILD_DEPS) $($(1)_LIB_MAKE_DEPS) | $(LIB_DIR)
	ar rcs $$@ $($(1)_LIB_OBJS) $($(1)_LIB_BUILD_DEPS)

$(foreach VV,$(patsubst %/source/,%, $(sort $(dir $($(1)_LIB_SRCS)))),$(eval $(call GENERATE_LIBRARY_COMPILE,$(1),$(VV))))

-include $($(1)_LIB_OBJS:.o=.d)
endef
$(foreach VV,$(LIBRARIES),$(eval $(call GENERATE_LIBRARY,$(VV))))

###

define GENERATE_BINARY_COMPILE
$(call GET_OBJ_FILES,$(2)/source/%.c,$($(1)_BIN_DIR)): $(2)/source/%.c $($(1)_BIN_MAKE_CC_DEPS) | $(patsubst %/,%,$(call GET_OBJ_FILES_POST,$(2)/source/,$($(1)_BIN_DIR))) $($(1)_BIN_CREATE_DIRS)
	$(CC) $$< -c -o $$@ $($(1)_BIN_CFLAGS) $(COMMON_CFLAGS) -I$($(1)_BIN_DIR)/include
	
$(call GET_OBJ_FILES,$(2)/source/%.cpp,$($(1)_BIN_DIR)): $(2)/source/%.cpp $($(1)_BIN_MAKE_CC_DEPS) | $(patsubst %/,%,$(call GET_OBJ_FILES_POST,$(2)/source/,$($(1)_BIN_DIR))) $($(1)_BIN_CREATE_DIRS)
	$(CXX) $$< -c -o $$@ $($(1)_BIN_CXXFLAGS) $(COMMON_CXXFLAGS) -I$($(1)_BIN_DIR)/include
endef

define GENERATE_BINARY
$(eval $(1)_BIN_EXE = $(BIN_DIR)/$($(1)_BIN_NAME))
CLEAN_FILES += $($(1)_BIN_EXE)  $($(1)_BIN_OBJS) $($(1)_BIN_OBJS:.o=.d)

$($(1)_BIN_CREATE_DIRS):
	mkdir -p $$@

.PHONY: $($(1)_BIN_NAME)
$($(1)_BIN_NAME): $(BIN_DIR)/$($(1)_BIN_NAME)

$($(1)_BIN_EXE): $($(1)_BIN_OBJS) $($(1)_BIN_BUILD_DEPS) $($(1)_BIN_MAKE_DEPS) | $(BIN_DIR)
	$(CXX) $($(1)_BIN_OBJS) $($(1)_BIN_BUILD_DEPS) -o $$@  $(COMMON_LDFLAGS) $($(1)_BIN_LDFLAGS)

$(foreach VV,$(patsubst %/source/,%, $(sort $(dir $($(1)_BIN_SRCS)))),$(eval $(call GENERATE_BINARY_COMPILE,$(1),$(VV))))

.PHONY: $($(1)_BIN_NAME).run
$($(1)_BIN_NAME).run: $($(1)_BIN_NAME)
	$(BIN_DIR)/$($(1)_BIN_NAME) $($(1)_BIN_ARGS)

.PHONY: $($(1)_BIN_NAME).gdb
$($(1)_BIN_NAME).gdb: $($(1)_BIN_NAME)
	gdb --args $(BIN_DIR)/$($(1)_BIN_NAME) $($(1)_BIN_ARGS)

.PHONY: $($(1)_BIN_NAME).lldb
$($(1)_BIN_NAME).lldb: $($(1)_BIN_NAME)
	lldb -- $(BIN_DIR)/$($(1)_BIN_NAME) $($(1)_BIN_ARGS)

.PHONY: $($(1)_BIN_NAME).valgrind
$($(1)_BIN_NAME).valgrind: $($(1)_BIN_NAME)
	valgrind --leak-check=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="$($(1)_BIN_NAME).valgrind.txt" -v $(BIN_DIR)/$($(1)_BIN_NAME) $($(1)_BIN_ARGS)

-include $($(1)_BIN_OBJS:.o=.d)
endef
$(foreach VV,$(BINARIES),$(eval $(call GENERATE_BINARY,$(VV))))

clean:
	rm -rf $(CLEAN_FILES)

###

