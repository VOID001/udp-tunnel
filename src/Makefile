CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -Waddress -Wconversion -g
LDFLAGS =
CPPFLAGS = -I$(CURDIR)/include

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(SRCS)))

# Export all varibles
export

default: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@
	$(SETCAP) $@

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@

.PHONY: test
test: $(OBJS)
	$(MAKE) -C test

.PHONY: clean
clean:
	$(DEL) $(OBJS)
	$(DEL) $(TARGET)
	$(MAKE) -C test clean
