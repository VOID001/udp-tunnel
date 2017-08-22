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
#include "test.h"
#include "netlib.h"

const char buffer[] = {
    'b', 'u', 'f', 'f', 'e', 0
};

char resbuf[6] = {};


int mock_packet();

void test_buf_read() {
    char hexbuff[1024];
    char *tmpfile = tmpnam(NULL);
    int fd = mock_packet(tmpfile);
    // try
    int tmp;
    // TODO: Add a function to init ipbuf
    IPBuf *ipbuf;
    ipbuf = (IPBuf *)malloc(sizeof(ipbuf));
    ipbuf->buf = (char *)malloc(sizeof(char) * MAX_BUF_LEN);
    ipbuf->length = 0;
    ipbuf->offset = 0;
    // #1 When buffer is empty, read a whole packet
    log_infof("#1 When buffer is empty, read a whole packet");
    buf_read(ipbuf, fd, resbuf, 6);

    if ((tmp = strcmp(resbuf, buffer)) != 0) {
        log_errorf("strcmp expect to return 0, %d returned\nresbuf = %s, buffer = %s", tmp, resbuf, buffer);
        print_process(failure);
        return ;
    }
    hexstr(hexbuff, (void *)resbuf, 6);
    log_debugf("bytes:\n%s", hexbuff);

    // #2 When buffer is not empty, read from buffer
    log_infof("#2 When buffer is not empty, read from buffer");
    if (lseek(fd, 0, SEEK_SET) < 0) {
        log_errorf("lseek error: %s", strerror(errno));
        print_process(error);
        return ;
    }
    buf_clear(ipbuf);
    buf_read(ipbuf, fd, resbuf, 1);
    buf_read(ipbuf, fd, resbuf, 1);
    if (resbuf[0] != buffer[1]) {
        log_errorf("resbuf expect to be 0x%02x, 0x%02x returned", buffer[1], resbuf[0]);
        print_process(failure);
        return ;
    }

    // #3 When buffer is not empty, but read till end, read all
    log_infof("#3 When buffer is not empty but read till end, read all");
    if (lseek(fd, 0, SEEK_SET) < 0) {
        log_errorf("lseek error: %s", strerror(errno));
        return ;
    }
    tmp = buf_read(ipbuf, fd, resbuf, 200);
    if (tmp != sizeof(buffer) - 2) {
        log_errorf("actual_read expceted to be %d, %d returned", sizeof(buffer) - 2, tmp);
        print_process(failure);
    }

    hexstr(hexbuff, (void *)resbuf, 4);
    log_debugf("bytes:\n%s", hexbuff);

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
        log_errorf("open tmpfile error: %s", strerror(errno));
        return -1;
    }
    if (write(fd, buffer, sizeof(buffer)) !=  sizeof(buffer)) {
        log_errorf("write packet to tmpfile error: %s", strerror(errno));
        return -1;
    }
    // TODO: Maybe we do not need dup?
    newfd = dup(fd);
    close(fd);
    lseek(newfd, 0, SEEK_SET);
    return newfd;
}
