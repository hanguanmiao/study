a.out: combine3.o
	gcc -o $@ -std=c11 -Wall -Wextra -O2 combine3.o

combine3.o: combine3.c
	gcc -o $@ -std=c11 -Wall -Wextra -O2 -c combine3.c

clean:
	rm -rf a.out combine3.o
