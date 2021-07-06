fb3-5: fb3-5.l fb3-5.y fb3-5.h
	bison -d fb3-5.y
	flex -ofb3-5.lex.c fb3-5.l
	gcc -o $@ fb3-5.tab.c fb3-5.lex.c fb3-5funcs.c -lfl

clean:
	rm -rf fb3-5.tab.c fb3-5.tab.h fb3-5.lex.c fb3-5
