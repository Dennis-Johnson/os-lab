cc = clang
flags = -pedantic -Wall

all: sender receiver

sender: sender.c
	$(cc) $(flags) sender.c -o sender

recevier: recevier.c
	$(cc) $(flags) receiver.c -o receiver

clean:
	rm -f sender receiver *.o