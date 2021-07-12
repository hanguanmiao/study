a.out: wc_purefle.c
	gcc -std=c11 -Wall -Wextra wc_purefle.c

wc_purefle.c: wc_purefle.l
	flex -o wc_purefle.c wc_purefle.l

clean:
	rm -rf wc_purefle.c a.out
