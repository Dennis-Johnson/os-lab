cc = gcc
flags = -pedantic -Wall

all: reader writer

reader:	reader.c
	$(cc) $(flags) reader.c -o reader

writer:	writer.c
	$(cc) $(flags) writer.c -o writer

clean:
	rm -f reader writer *.o

