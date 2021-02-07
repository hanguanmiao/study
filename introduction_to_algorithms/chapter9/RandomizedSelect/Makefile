PROM=RandomizedSelect.out

ABSDIR=$(shell pwd)
SRCS=$(shell find ${ABSDIR} -type f -name "*.cpp")
DEPS=$(shell find ${ABSDIR} -type f -name "*.h")
OBJS=$(patsubst %.cpp,%.o,${SRCS})

MAKE=g++
CPPFLAGS=-std=c++11 -Wall -Wextra -g -O0
CPPFLAG=

#$(warning ${CPPFLAG})

${PROM}: ${OBJS}
	${MAKE} ${CPPFLAGS} -o ${PROM} $^ ${CPPFLAG}

%.o: %.c ${DEPS}
	${MAKE} ${CPPFLAGS} -o $@ -c $< ${CPPFLAG}

clean:
	rm -rf ${PROM} ${OBJS}
