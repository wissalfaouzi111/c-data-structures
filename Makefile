SET_DIR = set
SEN_DIR = sentinel
DYN_DIR = dynamic
LNK_DIR = link
BIN = sentinel_struc dynamic_struc link_struc

CC ?= cc
CPPFLAGS = -I ${SET_DIR} -I ${SEN_DIR} -I ${DYN_DIR} -I ${LNK_DIR}
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
set_dynamic.o: ${DYN_DIR}/set_dynamic.c ${DYN_DIR}/set_dynamic.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${DYN_DIR}/set_dynamic.c -c

test_dynamic_struc.o: ${DYN_DIR}/test_dynamic_struc.c ${DYN_DIR}/set_dynamic.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${DYN_DIR}/test_dynamic_struc.c -c

dynamic_struc: test_dynamic_struc.o set_dynamic.o
	${CC} test_dynamic_struc.o set_dynamic.o -o $@ ${LDFLAGS}

#link

link.o: ${LNK_DIR}/link.c ${LNK_DIR}/link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LNK_DIR}/link.c -c

set_link.o: ${LNK_DIR}/set_link.c ${LNK_DIR}/set_link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LNK_DIR}/set_link.c -c

test_link_struc.o : ${LNK_DIR}/test_link_struc.c ${LNK_DIR}/set_link.h ${LNK_DIR}/link.h
	${CC} ${CPPFLAGS} ${CFLAGS} ${LNK_DIR}/test_link_struc.c -c

link_struc: test_link_struc.o set_link.o link.o
	${CC} test_link_struc.o set_link.o link.o -o $@ ${LDFLAGS}


af_sentinel: ${SET_DIR}/affectation.c set_sentinel.o
	${CC} ${CPPFLAGS} ${CFLAGS} -D SENTINEL $< -o affectation.o -c
	${CC} ${CPPFLAGS} ${CFLAGS} set_sentinel.o affectation.o -o $@

af_dynamic: ${SET_DIR}/affectation.c set_dynamic.o
	${CC} ${CPPFLAGS} ${CFLAGS} -D DYNAMIC $< -o affectation.o -c
	${CC} ${CPPFLAGS} ${CFLAGS} set_dynamic.o affectation.o -o $@

af_link: ${SET_DIR}/affectation.c link.o set_link.o
	${CC} ${CPPFLAGS} ${CFLAGS} -D LINK $< -o affectation.o -c
	${CC} ${CPPFLAGS} ${CFLAGS} link.o set_link.o affectation.o -o $@