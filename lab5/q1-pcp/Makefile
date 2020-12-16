cc = gcc
flags = -pedantic -Wall

all: producer consumer

producer:	producer.c
	$(cc) $(flags) producer.c -o producer

consumer:	consumer.c
	$(cc) $(flags) consumer.c -o consumer

clean:
	rm -f producer consumer *.o

