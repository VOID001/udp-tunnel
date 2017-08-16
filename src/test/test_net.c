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

void test_tun_alloc() {
    char tun_name[] = "test_tun";
    int err;
    if ((err = tun_alloc(tun_name)) < 0) {
        log_errorf(__func__, "failed");
    }
}
