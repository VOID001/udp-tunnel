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
    if((nread = read(fd, buffer, 32)) < 0) {
        log_errorf(__func__, "read call error %s", strerror(errno));
        return nread;
    }
    hexstr(hexbuff, (void *)buffer, 32);
    log_infof(__func__, "bytes:\n %s", hexstr);
    return 0;
}

void hexstr(char *dest, void *addr, int size_n) {
    //TODO: convert bytes in addr to hexdump format
    // and output to dest
}
