include ../Makefile.header
TESTOBJS = test_log.o test_main.o
OBJS = ../log.o


#CFLAGS = -Wall -Wextra -Waddress -Wconversion -g
#CPPFLAGS = -I../include
#CC = gcc

testsuite: $(OBJS) $(TESTOBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $*.o $<

clean:
	rm -f $(TESTOBJS) testsuite
