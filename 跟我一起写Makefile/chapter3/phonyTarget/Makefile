all : prog1 prog2 prog3

OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))
$(warning $(OBJECTS))


#.PHONY : all clean
prog1 : prog1.o utils.o
	cc -o prog1 prog1.o utils.o
prog2 : prog2.o
	cc -o prog2 prog2.o
prog3 : prog3.o sort.o utils.o
	cc -o prog3 prog3.o sort.o utils.o

clean:
	rm -rf prog1 prog2 prog3 $(OBJECTS)
