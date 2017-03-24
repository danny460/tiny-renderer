OUTPUT = output.tga
OBJS = main.o tgaimage.o model.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: clear tgaimage.o model.o main.o renderer run open

clear: 
	printf "\033c"

tgaimage.o: tgaimage.cpp tgaimage.h
	$(CC) $(CFLAGS) tgaimage.cpp

model.o: model.cpp model.h geometry.h
	$(CC) $(CFLAGS) model.cpp

main.o: main.cpp tgaimage.h model.h
	$(CC) $(CFLAGS) main.cpp 
	
renderer: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o renderer.out

run: renderer
	./renderer.out

open: $(OUTPUT)
	open $(OUTPUT)
