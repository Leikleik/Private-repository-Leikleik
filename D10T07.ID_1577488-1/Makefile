CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
BUILD_DIR = build

.PHONY: all clean door_struct list_test stack_test print_module documentation_module

all: door_struct list_test stack_test print_module documentation_module

door_struct: $(BUILD_DIR)/Quest_1

list_test: $(BUILD_DIR)/Quest_2

stack_test: $(BUILD_DIR)/Quest_3

print_module: CFLAGS += -DPRINT_MODULE_ONLY
print_module: $(BUILD_DIR)/Quest_4

documentation_module: CFLAGS += -DDOCUMENTATION_MODULE
documentation_module: $(BUILD_DIR)/Quest_5

$(BUILD_DIR)/Quest_1: src/dmanager_module.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR)/Quest_2: src/list.c src/list_test.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/Quest_3: src/stack.c src/stack_test.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/Quest_4: src/print_module.c src/main_module_entry_point.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/Quest_5: src/print_module.c src/main_module_entry_point.c src/documentation_module.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR)
