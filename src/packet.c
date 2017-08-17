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
#include <arpa/inet.h>

#include "log.h"
#include "netlib.h"
#include "buffer.h"


// read the udp header
// and then return the udp packet length
int read_udp_header(int fd) {
    struct udphdr udp_header;
    read(fd, (void *)&udp_header, 64);
    return 0;
}

// read the ip header
// and then return the ip packet length
int read_ip_header(IPBuf *ipbuf,int fd) {
    char buffer[32];
    char hexbuff[1024];
    int nread = 0;                  // nread is also errno
    int ip_header_len = 0;      // IP header len in bytes
    int ip_packet_len = 0;

    // First read & discard tun header
    // We can only read a WHOLE packet once, cannot read in stream
    // TODO: How to read it in stream?
    memset(buffer, 0, sizeof(buffer));

    if ((nread = buf_read(ipbuf, fd, buffer, 4)) < 0) {
        log_errorf(__func__, "read 4 bytes call error: %d %s", nread, strerror(errno));
        return nread;
    }
    hexstr(hexbuff, (void *)buffer, nread);
    // log_debugf(__func__, "bytes:\n%s", hexbuff);

    // Check if it's a UDP packet, if not, return
    if(*(int32_t *)buffer != 0x00080000) {
        buf_clear(ipbuf);
        return 0;
    }

    if ((nread = buf_read(ipbuf, fd, buffer, 1)) != 1) {
        log_errorf(__func__, "read 1 byte call error: %d %s", nread, strerror(errno));
        return nread;
    }

    ip_header_len = (buffer[0] & 0x0f) * 4;
    log_debugf(__func__, "ip_header_len =  %d buffer[0] = %02x", ip_header_len, buffer[0]);

    if ((nread = buf_read(ipbuf, fd, buffer + nread, ip_header_len - 1)) != ip_header_len - 1) {
        log_errorf(__func__, "read call error %s", strerror(errno));
        return nread;
    }

    log_debugf(__func__, "ip packet len = %d buffer[1] = %02x", 0, ntohs(*(int16_t *)(buffer + 2)));
    ip_packet_len = ntohs(*(int16_t *)(buffer + 2));

    hexstr(hexbuff, (void *)buffer, 24);
    log_debugf(__func__, "bytes:\n%s", hexbuff);
    return ip_packet_len;
}

void hexstr(char *dest, void *addr, size_t size_n) {
    const uint8_t *c = addr;
    assert(addr);
    // log_debugf(__func__, "Dumping %zu bytes from %p:", size_n, addr);
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
    p[strlen(p) - 1] = 0;
    return;
}
