/*
 * Main event loop
 */
#include <stdlib.h>
#include "log.h"
#include "netlib.h"
#include "buffer.h"

int main(int argc, char **argv) {
    int tun_fd = -1;
    char tun_name[] = "udptun";
    init_logger("stderr", DEBUG);
    log_infof("udp-tun started, version 0.1");
    // TODO: get options

    // Create kernel tunnel
    tun_fd = tun_alloc(tun_name);
    log_infof("tunnel create success, devname: %s", tun_name);
    
    // Waiting for the package to be processed
    // start the pacakge loop
    
    IPBuf *ipbuf;
    ipbuf = (IPBuf *)malloc(sizeof(ipbuf));
    ipbuf->buf = (char *)malloc(sizeof(char) * MAX_BUF_LEN);
    ipbuf->offset = 0;
    ipbuf->length = 0;
    while(1) {
        // first read the udp header
        read_ip_header(ipbuf, tun_fd);
    }

    // Logic part
}
