
CC=gcc
CFLAGS= -Wall  -Wextra -O3 -std=c99  -std=c11 

# the macro DEPS, which is the set of .h files on which the .c files depend
DEPS=List.h rQuickSort.h HashTable.h GrafoSt21.h RomaVictor.h dimacs.h darray.h VerticeSt.h queue.h UnleashHell.h


OBJ=main.o rQuickSort.o GrafoSt21.o dimacs.o List.o RomaVictor.o HashTable.o darray.o VerticeSt.o queue.o UnleashHell.o

# we define a rule that applies to all files ending in the .o suffix.
# The rule says that the .o file depends upon the .c version of the file and the .h
# files included in the DEPS macro.
# The rule then says that to generate the .o file, make needs to compile the .c 
# file using the compiler defined in the CC macro.
# The -c flag says to generate the object file, the -o $@ says to put the output of 
# the compilation in the file named on the left side of the :,
# the $< is the first item in the dependencies list, and the CFLAGS macro is defined as above.
%.o: %.c $(DEPS)
	$(CC)  -c -o $@ $< $(CFLAGS)

# use the special macros $@ and $^, which are the left and right sides of the :,
# respectively, to make the overall compilation rule more general.
chichaser: $(OBJ)
	$(CC)  -o $@ $^ $(CFLAGS)


.PHONY: clean

all:  main

clean:
	rm -f *.o
	rm -f chichaser
