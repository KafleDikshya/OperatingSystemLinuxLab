shell: shell.o

	gcc -o $@ $^



shell.o: shell.c

	gcc -c $^ -o $@
