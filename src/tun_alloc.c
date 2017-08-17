/*************************************************************************
    > File Name: tun_alloc.c
    > Author: VOID_133
    > ################### 
    > Mail: ################### 
    > Created Time: Wed 16 Aug 2017 02:55:16 PM CST
 ************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stddef.h>
#include <time.h>
#include <net/if.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "log.h"

// Create a tunnel device (persistently)
int tun_alloc(char *dev) {
    int fd, err;
    struct ifreq ifr;
    char tun_root[] = "/dev/net/tun";

    memset(&ifr, 0, sizeof(ifr));
    if((fd = open(tun_root, O_RDWR)) < 0) {
        log_fatalf(__func__, "fail to open clone device tun, %s", strerror(errno));
        // program exit
    }
    log_debugf(__func__, "tunnel fd = %d", fd);
    ifr.ifr_flags = IFF_TUN;
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);

    if((err = ioctl(fd, TUNSETIFF, (void *)&ifr)) < 0) {
        close(fd);
        log_fatalf(__func__, "fail to create tunnel, %s", strerror(errno));
    }

    if((err = ioctl(fd, TUNSETPERSIST, 1)) < 0) {
        close(fd);
        log_fatalf(__func__, "fail to set tunnel to persist, %s", strerror(errno));
    }

    strcpy(dev, ifr.ifr_name);
    return fd;
}
