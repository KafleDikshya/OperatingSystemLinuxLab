fork-ex: fork-ex.c

	gcc fork-ex.c -o fork-ex



zombie: zombie.o

	gcc -o $@ $^



zombie.o: zombie.c

	gcc -c $^ -o $@



shell: shell.o

	gcc -o $@ $^



shell.o: shell.c

	gcc -c $^ -o $@
