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

.PHONY: build
build:
	mkdir build &>/dev/null || true
	$(MAKE) -C src

.PHONY: if
if:
	$(IFUTIL) tuntap add mode tun dev $(DEV)
	$(IFUTIL) addr add $(IP)/$(CIDR) dev $(DEV)
	$(IFUTIL) link set dev $(DEV) up

.PHONY: unif
unif:
	sudo ip tuntap del mode tun dev $(DEV)

.PHONY: run
run: $(TARGET)
	$(MAKE) if
	$(TARGET) || true # TODO: how to continue?
	$(MAKE) unif

.PHONY: test
test:
	$(MAKE) -C src test

.PHONY: clean
clean:
	$(MAKE) -C src clean
