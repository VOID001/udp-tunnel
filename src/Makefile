include Makefile.header
OBJS = log.o

.PHONY = clean test all

all:

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $*.o $<

run_test:
	make -C test testsuite
	test/testsuite

clean:
	- rm -f $(OBJS)
	- make -C test clean
