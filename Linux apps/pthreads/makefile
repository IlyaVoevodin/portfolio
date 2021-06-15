.PHONY: all clean

all: pro
%.c:%.o
pro: vector.o thread.o main.o
	gcc -o pro -pthread main.o vector.o thread.o
main.o: main.c
	gcc -c main.c
vector.o: vector.c vector.h
	gcc -c vector.c
thread.o: thread.c thread.h
	gcc -c thread.c
clean:
	rm -r *.o pro
