CXX = g++
DEPS_BIN = g++
CXXFLAGS = -g -std=c++11
LDFLAGS = -g
LDLIB = -lvulkan
AR = ar
ARFLAGS = rc
MKDIR = mkdir
MKDIRFLAGS = -p

PREFIX = ~/.local/
BIN_DIR = bin/
INCLUDE_DIR = include/
LIB_DIR = lib/

PKG_NAME = pkg-name

SOURCES = src/main.cpp src/application.cpp src/vk/instance_builder.cpp src/vk/instance.cpp

# exemple: HEADERS = include/pkg-name/test.hpp
HEADERS =

BIN = bin/main


#bin/...: ...
bin/main: build/src/main.o build/src/application.o build/src/vk/instance_builder.o build/src/vk/instance.o

# exemple: LIB = lib/libtest.a
LIB =

# exemple: lib/libtest.a: build/src/test.o
#lib/...: ...
