/*************************************************************************
    > File Name: udp.c
    > Author: VOID_133
    > ################### 
    > Mail: ################### 
    > Created Time: Wed 16 Aug 2017 02:55:07 PM CST
 ************************************************************************/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdarg.h>
#include<string.h>
#include<stddef.h>
#include<time.h>
#include<stdio.h>
#include<stdio.h>
#include<netinet/udp.h>


// this function read the udp header
// and then return the udp packet length
int read_udp_header(int fd) {
    struct udphdr udp_header;
    read(fd, (void *)&udp_header, 64);
    return 0;
}

int read_ip_header(int fd) {

}
