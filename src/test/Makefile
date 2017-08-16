include ../Makefile.header
TESTOBJS = test_log.o test_main.o test_net.o
OBJS = ../log.o ../tun_alloc.o ../packet.o


#CFLAGS = -Wall -Wextra -Waddress -Wconversion -g
#CPPFLAGS = -I../include
#CC = gcc

testsuite: $(OBJS) $(TESTOBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^
	sudo setcap CAP_NET_ADMIN+eip testsuite

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $*.o $<

clean:
	rm -f $(TESTOBJS) testsuite
