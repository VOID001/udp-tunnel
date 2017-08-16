/*
 * Main event loop
 */
#include "log.h"
#include "netlib.h"

int main(int argc, char **argv) {
    int tun_fd = -1;
    init_logger("stderr", INFO);
    log_infof(__func__, "udp-tun started, version 0.1");
    // TODO: get options

    // Create kernel tunnel
    tun_fd = tun_alloc("udptun");
    log_infof(__func__, "tunnel create success, devname: %s", "udptun");
    
    // Waiting for the package to be processed
    // start the pacakge loop
    while(1) {
        // first read the udp header
    }

    // Logic part
}
