fb3-5: fb3-5.l fb3-5.y fb3-5.h fb3-5funcs.c
	bison -d fb3-5.y
	flex -ofb3-5.lex.c fb3-5.l
	gcc -o $@ -g -O0 fb3-5.tab.c fb3-5.lex.c fb3-5funcs.c -lm

clean:
	rm -rf fb3-5.tab.c fb3-5.tab.h fb3-5.lex.c fb3-5
