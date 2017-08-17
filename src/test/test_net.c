/*************************************************************************
    > File Name: test_net.c
    > Author: VOID_133
    > ################### 
    > Mail: ################### 
    > Created Time: Wed 16 Aug 2017 03:48:38 PM CST
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

#include "test.h"
#include "log.h"
#include "netlib.h"
#include "buffer.h"

void test_tun_alloc() {
    char tun_name[] = "udptun";
    int tun;
    if ((tun = tun_alloc(tun_name)) < 0) {
        log_errorf(__func__, "An error occurred while allocating tun.");
        print_process(error);
    }
    close(tun);
}

void test_read_ip_header() {
    char tun_name[] = "udptun";
    int tun, err;
    IPBuf *ipbuf;
    ipbuf = (IPBuf *)malloc(sizeof(ipbuf));
    ipbuf->buf = (char *)malloc(sizeof(char) * MAX_BUF_LEN);
    if ((tun = tun_alloc(tun_name)) < 0) {
        log_errorf(__func__, "An error occurred while allocating tun.");
        print_process(error);
        return;
    }
    if ((err = read_ip_header(NULL, tun)) < 0) {
        log_errorf(__func__, "An error occurred while reading ip header.");
        print_process(error);
    }
    close(tun);
}
