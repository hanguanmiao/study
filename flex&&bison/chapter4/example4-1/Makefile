# Makefile for pmysql
CC = gcc -g -O0 
LEX = flex
YACC = bison
CFLAGS = -DYYDEBUG=1

PROGRAMS = pmysql

all: ${PROGRAMS}

pmysql: pmysql.tab.o pmysql.o
	${CC} -o $@ pmysql.tab.o pmysql.o

pmysql.tab.c pmysql.tab.h: pmysql.y
	${YACC} -vd pmysql.y

pmysql.c: pmysql.l
	${LEX} -o $*.c $<

.SUFFIXES: .pgm .l .y .c

clean:
	rm -rf ${PROGRAMS} pmysql.tab.o pmysql.o pmysql.tab.c pmysql.tab.h pmysql.c
