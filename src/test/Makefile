TEST_SRCS = $(wildcard *.c)
# Excluding outter main
TEST_OBJS = $(filter-out $(BUILD_DIR)/main.o, $(OBJS))
TEST_OBJS += $(patsubst %.c, $(BUILD_DIR)/%.o, $(notdir $(TEST_SRCS)))

TEST_TARGET = $(BUILD_DIR)/testsuite

default:
	$(MAKE) $(TEST_TARGET)
	$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@
	$(SETCAP) $@

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^ -o $@

.PHONY: clean
clean:
	$(DEL) $(TEST_OBJS)
	$(DEL) $(TEST_TARGET)
