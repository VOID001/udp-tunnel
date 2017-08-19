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
#sudo ip route replace 203.5.5.5 dev udptun
sudo iptables -A OUTPUT -t mangle -p UDP -d 202.118.17.142 -j MARK --set-mark 0x1
sudo ip rule add fwmark 0x1 table udptun.out
# We need to add a routing table here
sudo ip route add default dev udptun table udptun.out
