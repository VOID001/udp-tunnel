/*************************************************************************
    > File Name: test_buffer.c
    > Author: VOID_133
    > ################### 
    > Mail: ################### 
    > Created Time: Thu 17 Aug 2017 09:48:35 PM CST
 ************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stddef.h>
#include <time.h>
#include <stdio.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "log.h"
#include "buffer.h"

const char buffer[] = {
    0x01, 0x0b, 0x0d, 0x0e, 0x05, 0xac
};

char resbuf[6] = {};


int mock_packet();

void test_buf_read() {
    char *tmpfile = tmpnam(NULL);
    int fd = mock_packet(tmpfile);
    int tmp;
    IPBuf *ipbuf;
    ipbuf = (IPBuf *)malloc(sizeof(ipbuf));
    ipbuf->buf = (char *)malloc(sizeof(char) * MAX_BUF_LEN);
    // #1 When buffer is empty, read a whole packet
    buf_read(ipbuf, fd, resbuf, 6);

    if ((tmp = strcmp(resbuf, buffer)) != 0) {
        log_errorf(__func__, "strcmp expect to return 0, %d returned", tmp);
        return ;
    }

    // #2 When buffer is not empty, read from buffer
    if (lseek(fd, 0, SEEK_SET) < 0) {
        log_errorf(__func__, "lseek error: %s", strerror(errno));
        return ;
    }
    buf_clear(ipbuf);
    buf_read(ipbuf, fd, resbuf, 1);
    buf_read(ipbuf, fd, resbuf, 1);
    if (resbuf[0] != buffer[1]) {
        log_errorf(__func__, "resbuf expect to be 0x%02x, 0x%02x returned", buffer[1], resbuf[0]);
        return ;
    }

    // #3 When buffer is not empty, but read till end, read all
    if (lseek(fd, 0, SEEK_SET) < 0) {
        log_errorf(__func__, "lseek error: %s", strerror(errno));
        return ;
    }
    tmp = buf_read(ipbuf, fd, resbuf, 200);
    if (tmp != sizeof(buffer) - 2) {
        log_errorf(__func__, "actual_read expceted to be %d, %d returned", sizeof(buffer) - 2, tmp);
    }
    close(fd);
    return ;
}

void test_buf_seek() {

}

void test_buf_clear() {

}

int mock_packet(char *file) {
    int fd = open(file, O_RDWR | O_CREAT);
    int newfd;
    if (fd < 0) {
        log_errorf(__func__, "open tmpfile error: %s", strerror(errno));
        return -1;
    }
    if(write(fd, buffer, sizeof(buffer)) !=  sizeof(buffer)) {
        log_errorf(__func__, "write packet to tmpfile error: %s", strerror(errno));
        return -1;
    }
    // TODO: Maybe we do not need dup?
    newfd = dup(fd);
    close(fd);
    return newfd;
}
