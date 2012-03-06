CC=gcc
TESTS=$(wildcard *_test)
CFLAGS= -Wall -g -O2

all: kr_queue_test kr_threadpool_test

kr_queue.c : kr_queue.h

kr_queue_test.c: kr_queue.h

kr_threadpool.c: kr_threadpool.h kr_queue.c

%.o : %.c
	$(CC) $(CFLAGS) -c $<

kr_queue_test: kr_queue_test.c kr_queue.o
	$(CC) $(CFLAGS) $^ -o $@	

kr_threadpool_test: kr_threadpool_test.c kr_queue.o kr_threadpool.o
	$(CC) $(CFLAGS) -lpthread $^ -o $@

test: kr_queue_test kr_threadpool_test
	./kr_queue_test
	./kr_threadpool_test

clean:
	rm -rf *.o *_test
