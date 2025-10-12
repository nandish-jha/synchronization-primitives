# Nandish Jha NAJ474 11282001
# Part 1 - Barbershop Problem



CC = gcc
CFLAGS = -g -std=gnu90 -Wall -pedantic
LIB_PATH = /student/cmpt332/pthreads/lib/Linuxx86_64/
LIBS = -lpthreads
CFLAGS += -I/student/cmpt332/pthreads

.PHONY: all clean

all: barbershop

barbershop: Lab3.synchproblem.o Lab3.testsynchproblem.o
	$(CC) $(CFLAGS) -o barbershop Lab3.synchproblem.o Lab3.testsynchproblem.o -L$(LIB_PATH) $(LIBS)

Lab3.synchproblem.o: Lab3.synchproblem.c
	$(CC) $(CFLAGS) -c Lab3.synchproblem.c

Lab3.testsynchproblem.o: Lab3.testsynchproblem.c
	$(CC) $(CFLAGS) -c Lab3.testsynchproblem.c

clean:
	clear
	rm -f *.o barbershop