CFLAGS = -Wall -ansi -pedantic -o2
CC = gcc

all: make_main

make_main : main.o utilities.o vector.o gps.o error.o arguments.o
	$(CC) $(CFLAGS) -o make_main main.o utilities.o vector.o gps.o error.o arguments.o 

main.o : main.c utilities.h vector.h gps.h error.h arguments.h types.h
	$(CC) $(CFLAGS) -o main.o -c main.c

utilities.o: utilities.c utilities.h types.h
	$(CC) $(CFLAGS) -o utilities.o -c utilities.c

vector.o: vector.c vector.h types.h
	$(CC) $(CFLAGS) -o vector.o -c vector.c

gps.o: gps.c gps.h types.h
	$(CC) $(CFLAGS) -o gps.o -c gps.c

error.o: error.c error.h types.h
	$(CC) $(CFLAGS) -o error.o -c error.c

arguments.o: arguments.c arguments.h types.h
	$(CC) $(CFLAGS) -o arguments.o -c arguments.c


