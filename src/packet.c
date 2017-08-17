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


// read the udp header
// and then return the udp packet length
int read_udp_header(int fd) {
    struct udphdr udp_header;
    read(fd, (void *)&udp_header, 64);
    return 0;
}

// read the ip header
// and then return the ip packet length
int read_ip_header(int fd) {
    char buffer[65536];
    char hexbuff[65536 * 8];
    int nread = 0;                  // nread is also errno
    int ip_header_len = 0;      // IP header len in bytes

    // First read & discard tun header
    // We can only read a WHOLE packet once, cannot read in stream
    // TODO: How to read it in stream?
    memset(buffer, 0, sizeof(buffer));
    if ((nread = read(fd, buffer, 2048)) < 0) {
        log_errorf(__func__, "read 4 bytes call error: %d %s", nread, strerror(errno));
        return nread;
    }
    hexstr(hexbuff, (void *)buffer, nread);
    log_debugf(__func__, "bytes:\n%s", hexbuff);
    // if ((nread = read(fd, buffer, 1)) != 1) {
    //     log_errorf(__func__, "read 1 byte call error: %d %s", nread, strerror(errno));
    //     return nread;
    // }

    // ip_header_len = (buffer[1] & 0x0f) * 4;
    // if ((nread = read(fd, buffer + nread, ip_header_len - 1)) != ip_header_len - 1) {
    //     log_errorf(__func__, "read call error %s", strerror(errno));
    //     return nread;
    // }

    // hexstr(hexbuff, (void *)buffer, 24);
    // log_debugf(__func__, "bytes:\n%s", hexbuff);
    return 0;
}

void hexstr(char *dest, void *addr, size_t size_n) {
    const uint8_t *c = addr;
    assert(addr);
    log_debugf(__func__, "Dumping %zu bytes from %p:", size_n, addr);
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
