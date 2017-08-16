/*************************************************************************
    > File Name: netlib.h
    > Author: VOID_133
    > ################### 
    > Mail: ################### 
    > Created Time: Wed 16 Aug 2017 03:49:53 PM CST
 ************************************************************************/

#ifndef _NETLIB_H
#define _NETLIB_H
#include <stddef.h>

int tun_alloc(char *dev);
int read_ip_header(int fd);
void hexstr(char *dest, void *addr, size_t size_n);

#endif
