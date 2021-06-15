.PHONY: greet build rebuild run clean 

%.o:%.c

greet:
	@echo "Terminating make - please specify target explicitly"
	@echo "    build   : fast rebuild / build"
	@echo "    rebuild : full rebuild"
	@echo "    run     : run after fast rebuild / build"
	@echo "    clean   : perform full clean"

build:  prog

rebuild: clean prog
	
run: 
	./prog $(N) $(OPT)
clean: 
	rm -rvf *.o prog

prog: main.o Print.o Search.o Input.o
	gcc -o prog main.o Print.o Search.o Input.o

Input.o: Input.c Input.h
	gcc -c -o Input.o Input.c

Print.o: Print.c Print.h Input.h
	gcc -c -o Print.o Print.c

Search.o: Search.c Search.h Input.h
	gcc -c -o Search.o Search.c

main.o: main.c Print.h Search.h Input.h
	gcc -c -o main.o main.c



