include Makefile.header

OBJS = log.o main.o

.PHONY = clean test all

run: udp-tunnel
	./udp-tunnel

udp-tunnel: $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $*.o $<

run_test:
	make -C test testsuite
	test/testsuite

clean:
	- rm -f $(OBJS)
	- make -C test clean
