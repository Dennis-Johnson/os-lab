CC = gcc
FLAGS = -pedantic -Wall

all: main

main: main.c
	$(CC) $(FLAGS) -o main main.c -pthread

clean:
	rm -f main *.o
