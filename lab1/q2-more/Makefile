cc = gcc
flags = -Wall -pedantic

main: main.c
	$(cc) $(flags) -o main main.c

debug: main.c
	$(cc) $(flags) -g -o debug main.c

clean:
	rm main debug 
	rm -rf debug.dSYM
