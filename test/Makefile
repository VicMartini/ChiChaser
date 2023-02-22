#gcc test.c munit.c munit.h ../HashTable.c ../List.c
CC = gcc
CFLAGS = -Wall -O3 -std=c99


SOURCES = test.c munit.c ../RomaVictor.c ../GrafoSt21.c ../List.c ../HashTable.c ../dimacs.c ../darray.c ../VerticeSt.c ../queue.c
OBJ = $(SOURCES:.c=.o)
TARGET = test

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^


.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJ)
