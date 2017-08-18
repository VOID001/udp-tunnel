#########################################################################
# File Name: set_tun.sh
# Author: VOID_133
# QQ: #########
# mail: ####@gmail.com
# Created Time: Wed 16 Aug 2017 09:24:35 PM CST
#########################################################################
#!/bin/bash

sudo ip addr add 10.1.1.0/24 dev udptun
sudo ip link set udptun up
