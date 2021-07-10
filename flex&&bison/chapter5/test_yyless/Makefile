a.out: test_yyless.o
	gcc -o $@ test_yyless.o -lfl

test_yyless.c: test_yyless.l
	flex -o $*.c $<

.SUFFIXS: .l


clean: 
	rm -rf a.out test_yyless.c test_yyless.o
