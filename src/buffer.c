/*************************************************************************
    > File Name: buffer.c
    > Author: VOID_133
    > Read network packet and buffer it
    > Mail: ################### 
    > Created Time: Thu 17 Aug 2017 11:51:04 AM CST
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
#include <errno.h>

#include "buffer.h"
#include "log.h"

#define MAX_IP_PACKET 8192

// buf read will perform actions as below
// if ipbuf is empty / read to the end, read from fd
// else read from ipbuf->buffer
// both case will return exactly nread bytes (or if no more to read, < nread bytes) in buffer
// and return value
int buf_read(IPBuf *ipbuf, int fd, char *buffer, size_t nread) {
    int actual_read = 0;
    int discard = 0;

    // no IPBuf, fallback to read
    if (ipbuf == NULL) {
        return read(fd, buffer, nread);
    }

    if (!ipbuf->length || ipbuf->offset == ipbuf->length) {
        // Read from fd
        if ((actual_read = read(fd, ipbuf->buf, MAX_IP_PACKET)) < 0) {
            log_errorf(__func__, "read from fd error: %s", strerror(errno));
            return actual_read;
        }
        ipbuf->length = actual_read;
        ipbuf->offset = 0;
    }
    actual_read = nread;
    if (ipbuf->offset + nread > ipbuf->length) {
        actual_read = ipbuf->length - ipbuf->offset;
        discard = 1;
    }

    if(memcpy(buffer, ipbuf->buf + ipbuf->offset, sizeof(char) * actual_read) == NULL) {
        log_errorf(__func__, "memcpy error, no enough memory");
        return -1;
    }
    ipbuf->offset += actual_read ;

    if (discard) {
        buf_clear(ipbuf);
    }
    return actual_read;
}

// buf_seek when seek to end return -1
// else return 0
int buf_seek(IPBuf *ipbuf, size_t seek_count) {
    if (ipbuf->offset + seek_count > ipbuf->length) {
        ipbuf->offset = ipbuf->length;
        return -1;
    }
    ipbuf->offset = ipbuf->offset + seek_count;
    return 0;
}

// buf_clear will clear the ipbuf
void buf_clear(IPBuf *ipbuf) {
    ipbuf->length = 0;
    ipbuf->offset = 0;
}


