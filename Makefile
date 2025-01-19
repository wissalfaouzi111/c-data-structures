SET_DIR = set
SEN_DIR = sentinel
#DYN_DIR = dynamic 

BIN = sentinel_struc #dynamic_struc 

CC ?= cc
CPPFLAGS = -I ${SET_DIR} -I ${SEN_DIR} #-I ${DYN_DIR} 
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS =

.PHONY: all test build clean

all: build test

build: ${BIN}

test: build
	@echo "run tests:"
	@for e in ${BIN}; do \
	echo -n "$${e} -> "; ./$${e}; \
	done

clean:
	rm -f *.o ${BIN} *~

#for sentinel implentation
set_sentinel.o: ${SEN_DIR}/set_sentinel.c ${SEN_DIR}/set_sentinel.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${SEN_DIR}/set_sentinel.c -c

test_sentinel_struc.o: ${SEN_DIR}/test_sentinel_struc.c ${SEN_DIR}/set_sentinel.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${SEN_DIR}/test_sentinel_struc.c -c

sentinel_struc: test_sentinel_struc.o set_sentinel.o
	${CC} test_sentinel_struc.o set_sentinel.o -o $@ ${LDFLAGS}

#for dynamic implementation 
#set_dynamic.o: ${DYN_DIR}/set_dynamic.c ${DYN_DIR}/set_dynamic.h
#	${CC} ${CPPFLAGS} ${CFLAGS} ${DYN_DIR}/set_dynamic.c -c

#test_dynamic_struc.o: ${DYN_DIR}/test_dynamic_struc.c ${DYN_DIR}/set_dynamic.h
#	${CC} ${CPPFLAGS} ${CFLAGS} ${DYN_DIR}/test_dynamic_struc.c -c

#dynamic_struc: test_dynamic_struc.o set_dynamic.o
#	${CC} test_dynamic_struc.o set_dynamic.o -o $@



