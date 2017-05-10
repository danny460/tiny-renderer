OUTPUT = output.tga
OBJS = main.o tgaimage.o geometry.o model.o 
CC = g++
DEBUG = -g
CPP11 = -std=c++11
CFLAGS = -Wall -c $(DEBUG) $(CPP11) 
LFLAGS = -Wall $(DEBUG) $(CPP11)


all: clear tgaimage.o model.o main.o renderer run open

clear: 
	printf "\033c"

geometry.o: geometry.cpp geometry.h
	$(CC) $(CFLAGS) geometry.cpp

tgaimage.o: tgaimage.cpp tgaimage.h
	$(CC) $(CFLAGS) tgaimage.cpp

model.o: model.cpp model.h geometry.h tgaimage.h
	$(CC) $(CFLAGS) model.cpp

main.o: main.cpp tgaimage.h model.h
	$(CC) $(CFLAGS) main.cpp 
	
renderer: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o renderer.out

run: renderer
	./renderer.out

open: $(OUTPUT)
	open $(OUTPUT)
