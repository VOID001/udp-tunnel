include Makefile.header

OBJS = log.o main.o tun_alloc.o packet.o buffer.o

.PHONY = clean test all

run: udp-tunnel
	./udp-tunnel

udp-tunnel: $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^
	sudo setcap CAP_NET_ADMIN+eip udp-tunnel

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $*.o $<

run_test:
	make -C test testsuite
	test/testsuite

clean:
	- rm -f $(OBJS)
	- make -C test clean
