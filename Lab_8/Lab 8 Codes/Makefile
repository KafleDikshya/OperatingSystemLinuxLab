CC = gcc

CFLAGS = -g -Wall

EXE = fdump file_stat traverse

all : $(EXE)

fdump : fdump.c hexdump.o 
	$(CC) $(CFLAGS) hexdump.o fdump.c -o fdump

hexdump : hexdump.o
	$(CC) -o hexdump hexdump.o

file_stat.o: file_stat.c
	$(CC) -c $(CFLAGS) file_stat.c

traverse: traverse.o
	$(CC) -o traverse traverse.o
	
traverse.o: traverse.c
	$(CC) -c $(CFLAGS) traverse.c
		 
clean:
	rm -rf *.o fdump file_stat traverse
