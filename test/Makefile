#gcc test.c munit.c munit.h ../HashTable.c ../List.c
CC = gcc
#OBJ = test.o munit.o GrafoSt.o List.o HashTable.o dimacs.o

test: test.c munit.c 
	$(CC) -g -c test.c munit.c ../GrafoSt.c ../List.c ../HashTable.c ../dimacs.c ../darray.c ../VerticeSt.c munit.h
	$(CC) -g -o test $(OBJ) munit.o test.o GrafoSt.o List.o HashTable.o dimacs.o darray.o VerticeSt.o

.PHONY: clean

clean:
	rm -f *.o
	rm -f test
