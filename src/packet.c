/*************************************************************************
    > File Name: udp.c
    > Author: VOID_133
    > ################### 
    > Mail: ################### 
    > Created Time: Wed 16 Aug 2017 02:55:07 PM CST
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
#include <netinet/udp.h>
#include <errno.h>
#include <assert.h>

#include "log.h"
#include "netlib.h"


// this function read the udp header
// and then return the udp packet length
int read_udp_header(int fd) {
    struct udphdr udp_header;
    read(fd, (void *)&udp_header, 64);
    return 0;
}

int read_ip_header(int fd) {
    char buffer[32];
    char hexbuff[4096];
    int nread;
    if ((nread = read(fd, buffer, 32)) < 0) {
        log_errorf(__func__, "read call error %s", strerror(errno));
        return nread;
    }
    hexstr(hexbuff, (void *)buffer, 32);
    log_infof(__func__, "bytes:\n%s", hexbuff);
    return 0;
}

void hexstr(char *dest, void *addr, size_t size_n) {
    const uint8_t *c = addr;
    assert(addr);
    printf("Dumping %zu bytes from %p:\n", size_n, addr);
    char *p = dest;
    while (size_n > 0) {
        unsigned i;
        for (i = 0; i < 16; i++) {
            if (i < size_n)
                sprintf(p, "%02x ", c[i]);
            else
                sprintf(p, "   ");
            p += 3;
        }
        for (i = 0; i < 16; i++) {
            if (i < size_n)
                sprintf(p, "%c", c[i] >= 32 && c[i] < 127 ? c[i] : '.');
            else
                sprintf(p, " ");
            p++;
        }
        sprintf(p++, "\n");
        c += 16;
        if (size_n <= 16)
            break;
        size_n -= 16;
    }
    return;
}
