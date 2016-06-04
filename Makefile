PREFIX=/usr/local
DESTDIR=
LIBDIR=${PREFIX}/lib
INCDIR=${PREFIX}/include

CFLAGS+=-g -Wall -O2 -DDEBUG -fPIC
LIBS=-lev -levbuffsock -lcurl
AR=ar
AR_FLAGS=rc
RANLIB=ranlib

ifeq (1, $(findstring 1, $(WITH_JANSSON)))
LIBS+=-ljansson
CFLAGS+=-DWITH_JANSSON
else
LIBS+=-ljson-c
endif

all: libnsq test

libnsq: libnsq.a

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

libnsq.a: command.o reader.o nsqd_connection.o http.o message.o nsqlookupd.o
	$(AR) $(AR_FLAGS) $@ $^
	$(RANLIB) $@

test: test.o libnsq.a
	$(CC) -o $@ $^ $(LIBS)

clean:
	rm -rf libnsq.a test test.dSYM *.o

.PHONY: install clean all

install:
	install -m 755 -d ${DESTDIR}${INCDIR}
	install -m 755 -d ${DESTDIR}${LIBDIR}
	install -m 755 libnsq.a ${DESTDIR}${LIBDIR}/libnsq.a
	install -m 755 nsq.h ${DESTDIR}${INCDIR}/nsq.h
