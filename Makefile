# TODO: More platform support! (switch wen)

ifndef CURDIR
	CURDIR := $(shell pwd)
endif

CC=g++
CFLAGS=-ggdb -std=c++23 -idirafter $(CURDIR)/glad/include -D DATA_DIR="../demo_data" -Wno-macro-redefined
LIBS=-lm -lglfw

# Do I really need all this? No. Do I want it anyway? Hell yeah. 
ifeq ($(OS),Windows_NT)
    CFLAGS += -D WIN32
	LIBS += -mwindows
    ifeq ($(PROCESSOR_ARCHITEW6432),AMD64)
        CFLAGS += -D AMD64
    else
        ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
            CFLAGS += -D AMD64
        endif
		ifeq ($(PROCESSOR_ARCHITECTURE),IA64)
			CFLAGS += -D IA64
		endif
		ifeq ($(PROCESSOR_ARCHITECTURE),EM64T)
			CFLAGS += -D EM64T
		endif
		ifeq ($(PROCESSOR_ARCHITECTURE),ARM64)
			CFLAGS += -D ARM
		endif
        ifeq ($(PROCESSOR_ARCHITECTURE),x86)
            CFLAGS += -D IA32
        endif
    endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Linux)
        CFLAGS += -D LINUX `pkg-config --cflags gtk+-3.0`
		LIBS += -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lXxf86vm -lXinerama -lXcursor `pkg-config --libs gtk+-3.0`  `pkg-config --cflags --libs openal`
    endif
    ifeq ($(UNAME_S),Darwin)
		# Apple is extremely retarded so we have to do a few tricks

		# Pretty normal declarations, just define APPLE and enable building ObjC++ for Boxer
        CFLAGS += -D APPLE -ObjC++

		# This is where the real retardation starts. Including OpenGL/AL absolutely floods your compiler output with deprecation warnings making it impossible to find errors.
		CFLAGS += -D GL_SILENCE_DEPRECATION -Wno-deprecated-declarations

		# And of course, Apple has their own obtuse way of linking libraries
		LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenAL
    endif
    UNAME_P := $(shell uname -m)
    ifeq ($(UNAME_P),x86_64)
        CFLAGS += -D AMD64
    endif
    ifneq ($(filter %86,$(UNAME_P)),)
        CFLAGS += -D IA32
    endif
    ifneq ($(filter arm%,$(UNAME_P)),)
        CFLAGS += -D ARM
    endif
endif


SRC_DIR=src
OBJ_DIR=build/obj
BUILD_DIR=build

SRCS=$(shell find $(SRC_DIR) -type f \( -name '*.cpp' -o -name '*.c' -o -name '*.m' -o -name '*.mm' \)) glad/src/glad.c
OBJS=$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, \
	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, \
	$(patsubst $(SRC_DIR)/%.m, $(OBJ_DIR)/%.o, \
	$(patsubst $(SRC_DIR)/%.mm, $(OBJ_DIR)/%.o, \
	$(patsubst glad/src/%.c, $(OBJ_DIR)/%.o, $(SRCS))))))

all: $(BUILD_DIR)/engine

$(BUILD_DIR)/engine: $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.m
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.mm
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: glad/src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

run: all
	./$(BUILD_DIR)/engine $(CURDIR)/demo_data

