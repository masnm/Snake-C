CC=gcc
flags=-g
sdl=`pkg-config sdl2 --libs`

all:
	$(CC) -o main.out main.c $(flags) $(sdl)
	./main.out
