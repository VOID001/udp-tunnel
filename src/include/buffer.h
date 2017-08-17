/*************************************************************************
    > File Name: buffer.h
    > Author: VOID_133
    > Buffer structure define and function prototypes 
    > Mail: ################### 
    > Created Time: Thu 17 Aug 2017 11:51:14 AM CST
 ************************************************************************/
#ifndef _BUFFER_H
#define _BUFFER_H

// Read packet to IP buffer
#include <stddef.h>

#define MAX_BUF_LEN 8192
typedef struct buffer {
    int offset;
    int length;
    char *buf;
} IPBuf;

int buf_read(IPBuf *ipbuf, int fd, char *buffer, size_t nread);
int buf_seek(IPBuf *ipbuf, size_t seek_count);
void buf_clear(IPBuf *ipbuf);

#endif
