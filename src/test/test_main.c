/*************************************************************************
    > File Name: test_main.c
    > Author: VOID_133
    > ################### 
    > Mail: ################### 
    > Created Time: Wed 16 Aug 2017 02:03:37 PM CST
 ************************************************************************/
#include <stdio.h>
#include "test.h"
#include "log.h"

//TODO: Give a summary of test result
//TODO: use assertion in test
int main(void) {
    test_logging();

    init_logger("stderr", DEBUG);
    log_infof(__func__, "running test_tun_alloc");
    test_tun_alloc();
    log_infof(__func__, "running test_tun_alloc done");
    log_infof(__func__, "running test_read_ip_header");
    test_read_ip_header();
    log_infof(__func__, "running test_read_ip_header done");
    log_infof(__func__, "running test_buffer");
    test_buf_read();
    log_infof(__func__, "running test_buffer done");
}

