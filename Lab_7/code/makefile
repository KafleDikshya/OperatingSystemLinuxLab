CC = gcc -I ./include
CFLAGS = -std=gnu99 -Wall -g #-DDEBUG

INC = ./include
SRC = ./src


vpath %.h ./include
vpath %.c ./src

EXECS = memory-test1 memory-test2 memory-test3 frag-eval

all: $(EXECS)

allocator.o: allocator.h allocator.c dnode.h dlist.h
	$(CC) $(CFLAGS) -c $(SRC)/allocator.c -o allocator.o

dnode.o: dnode.h dnode.c
	$(CC) $(CFLAGS) -c $(SRC)/dnode.c -o dnode.o

dlist.o: dlist.h dlist.c dnode.h
	$(CC) $(CFLAGS) -c $(SRC)/dlist.c -o dlist.o

dlisttest: $(SRC)/dlisttest.c dnode.o dlist.o
	$(CC) $(CFLAGS) dnode.o dlist.o $(SRC)/dlisttest.c -o dlisttest

memory-test1: $(SRC)/memory-test1.c dnode.o dlist.o allocator.o
	$(CC) $(CFLAGS) dnode.o dlist.o allocator.o $(SRC)/memory-test1.c -o memory-test1

memory-test2: $(SRC)/memory-test2.c dnode.o dlist.o allocator.o
	$(CC) $(CFLAGS) dnode.o dlist.o allocator.o $(SRC)/memory-test2.c -o memory-test2

memory-test3: $(SRC)/memory-test3.c dnode.o dlist.o allocator.o
	$(CC) $(CFLAGS) dnode.o dlist.o allocator.o $(SRC)/memory-test3.c -o memory-test3

frag-eval: $(SRC)/frag-eval.c dnode.o dlist.o allocator.o
	$(CC) $(CFLAGS) dnode.o dlist.o allocator.o $(SRC)/frag-eval.c -o frag-eval
