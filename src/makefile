OBJS = main.o tgaimage.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: clear tgaimage.o main.o renderer run open

clear: 
	printf "\033c"

tgaimage.o: tgaimage.cpp tgaimage.h
	$(CC) $(CFLAGS) tgaimage.cpp

main.o: main.cpp tgaimage.h
	$(CC) $(CFLAGS) main.cpp 
	
renderer: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o renderer

run: renderer
	./renderer

open: output.tga
	open output.tga
