#
#	https://www.partow.net/programming/makefile/index.html
#

CC       := gcc
CCFLAGS  := -pedantic-errors -Wall -Wextra
VK_LIB   := /usr/local/lib
VK_INC   := /usr/local/include
LDFLAGS  := -L${VK_LIB} -L/usr/X11R6/lib -lvk -lvkhelp -lXmu -lXpm -lXm -lXt -lX11 -lstdc++ ${VK_LIB}/libvk.a ${VK_LIB}/libvkhelp.a
OBJ_DIR  := ./objects
BIN_DIR  := ./target
BINARY   := panel
INCLUDE  := -I${VK_INC} -I/usr/X11R6/include
SRC      := $(wildcard *.C) 
OBJECTS  := $(SRC:%.C=$(OBJ_DIR)/%.o)

all: build $(BIN_DIR)/$(BINARY)

$(OBJ_DIR)/%.o: %.C
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) $(INCLUDE) -c $< -o $@ $(LDFLAGS)

$(BIN_DIR)/$(BINARY): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) -o $(BIN_DIR)/$(BINARY) $^ $(LDFLAGS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CCFLAGS += -DDEBUG -g
debug: all

release: CCFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(BIN_DIR)/*