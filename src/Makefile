include Makefile.header
OBJS = util.o

.PHONY = clean test

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $*.o $<

run_test:
	make -C test testsuite
	test/testsuite

clean:
	- rm -f $(OBJS)
	- make -C test clean
