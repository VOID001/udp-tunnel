#########################################################################
# File Name: remove_tun.sh
# Author: VOID_133
# QQ: #########
# mail: ####@gmail.com
# Created Time: Sat 19 Aug 2017 12:34:51 PM CST
#########################################################################
#!/bin/bash

sudo iptables -D OUTPUT -t mangle -p udp -d 202.118.17.142 -j MARK --set-mark 0x1
sudo ip link delete dev udptun
sudo ip route delete default table udptun.out
sudo ip rule delete fwmark 0x1
