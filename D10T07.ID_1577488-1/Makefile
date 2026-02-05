CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
BUILD_DIR = build

.PHONY: all clean door_struct list_test stack_test print_module documentation_module bst_create_test bst_insert_test bst_traverse_test

all: door_struct list_test stack_test print_module documentation_module bst_create_test bst_insert_test bst_traverse_test

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


bst_create_test: $(BUILD_DIR)/Quest_6

bst_insert_test: $(BUILD_DIR)/Quest_7

bst_traverse_test: $(BUILD_DIR)/Quest_8

$(BUILD_DIR)/Quest_6: src/bst.c src/bst_create_test.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/Quest_7: src/bst.c src/bst_insert_test.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/Quest_8: src/bst.c src/bst_traverse_test.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR)
