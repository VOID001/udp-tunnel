DEL = rm -f
MAKE = make
SETCAP = sudo setcap CAP_NET_ADMIN+eip

# Net device related
IFUTIL = sudo ip
DEV = udptun
IP = 10.1.1.0
CIDR = 24

BUILD_DIR = $(CURDIR)/build
TARGET = $(BUILD_DIR)/udp-tunnel

export

$(TARGET):
	- mkdir build
	$(MAKE) -C src

.PHONY: run
run: $(TARGET)
	- $(IFUTIL) tuntap add mode tun dev $(DEV)
	- $(IFUTIL) addr add $(IP)/$(CIDR) dev $(DEV)
	- $(IFUTIL) link set dev $(DEV) up
	trap "$(IFUTIL) tuntap del mode tun dev $(DEV)" INT && \
		$(TARGET)

.PHONY: test
test:
	$(MAKE) -C src test

.PHONY: clean
clean:
	$(MAKE) -C src clean
