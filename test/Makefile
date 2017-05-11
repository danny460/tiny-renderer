INC_DIR = ../src/
OBJS = geometry.test.o
CC = g++
DEBUG = -g
CPP11 = -std=c++11
INCLUDE = -I$(INC_DIR)
CFLAGS = -Wall -c $(DEBUG) $(CPP11) $(INCLUDE)
LFLAGS = -Wall $(DEBUG) $(CPP11)

all: clear compile link run

clear: 
	printf "\033c"

compile: geometry.test.cpp catch.hpp ../src/geometry.h
	$(CC) $(CFLAGS) geometry.test.cpp

link: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o test.out	

run: test.out
	./test.out
