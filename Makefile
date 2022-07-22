CC=gcc
CFLAGS=-lm -I.

main: main.o
	$(CC) -o main main.o $(CFLAGS)

clean:
	rm -f ./*.o