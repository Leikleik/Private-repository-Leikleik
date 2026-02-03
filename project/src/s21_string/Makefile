CFLAGS = -Wall -Wextra -Werror -std=c11
ROOT_DIR = ../..
BUILD_DIR = $(ROOT_DIR)/build

TEST_SRCS = s21_string.c s21_string_test.c
TEXT_SRCS = s21_string.c text_processor.c

all: full_coverage_tests

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

strlen_tests: $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_SRCS) -o $(BUILD_DIR)/Quest_6

strcmp_tests: $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_SRCS) -o $(BUILD_DIR)/Quest_7

strcpy: $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_SRCS) -o $(BUILD_DIR)/Quest_8

strcat: $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_SRCS) -o $(BUILD_DIR)/Quest_9

strchr: $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_SRCS) -o $(BUILD_DIR)/Quest_10

strstr: $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_SRCS) -o $(BUILD_DIR)/Quest_11

full_coverage_tests: $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEST_SRCS) -o $(BUILD_DIR)/Quest_12

text_processor: $(BUILD_DIR)
	$(CC) $(CFLAGS) $(TEXT_SRCS) -o $(BUILD_DIR)/Quest_13

clean:
	rm -rf $(BUILD_DIR)/Quest_6 $(BUILD_DIR)/Quest_7 $(BUILD_DIR)/Quest_8 \
		$(BUILD_DIR)/Quest_9 $(BUILD_DIR)/Quest_10 $(BUILD_DIR)/Quest_11 \
		$(BUILD_DIR)/Quest_12 $(BUILD_DIR)/Quest_13

rebuild: clean all
