/*************************************************************************
    > File Name: test_main.c
    > Author: VOID_133
    > ################### 
    > Mail: ################### 
    > Created Time: Wed 16 Aug 2017 02:03:37 PM CST
 ************************************************************************/
#include<stdio.h>
#include "test.h"
#include "log.h"

//TODO: Give a summary of test result
//TODO: use assertion in test
int main(void) {
    test_logging();

    init_logger("stderr", DEBUG);
    test_tun_alloc();
}

