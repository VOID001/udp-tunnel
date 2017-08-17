#ifndef _TEST_H
#define _TEST_H

#include <stddef.h>

typedef enum { pass, failure, error } run_state;

extern unsigned test_ret_temp;

void run_test(void (*pf[])(), size_t size);
void print_process(run_state);
void assert_true(int);

void test_logging();
void test_example();
void test_tun_alloc();
void test_read_ip_header();

#endif
