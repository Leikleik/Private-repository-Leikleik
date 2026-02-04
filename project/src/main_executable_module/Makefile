CFLAGS = -Wall -Wextra -Werror -std=c11
ROOT_DIR = ../..
BUILD_DIR = $(ROOT_DIR)/build

DATA_LIBS_DIR = ../data_libs
DATA_MODULE_DIR = ../data_module
DECISION_DIR = ../yet_another_decision_module

COMMON_SRCS = main_executable_module.c \
	$(DATA_LIBS_DIR)/data_io.c \
	$(DATA_LIBS_DIR)/data_stat.c \
	$(DATA_MODULE_DIR)/data_process.c \
	$(DECISION_DIR)/decision.c

COMMON_OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(notdir $(COMMON_SRCS)))

all: Quest_3

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/data_io.o: $(DATA_LIBS_DIR)/data_io.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/data_stat.o: $(DATA_LIBS_DIR)/data_stat.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/data_process.o: $(DATA_MODULE_DIR)/data_process.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/decision.o: $(DECISION_DIR)/decision.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

Quest_3: $(BUILD_DIR)/main_executable_module.o $(BUILD_DIR)/data_io.o \
	$(BUILD_DIR)/data_stat.o $(BUILD_DIR)/data_process.o $(BUILD_DIR)/decision.o
	$(CC) $(CFLAGS) $^ -o $(BUILD_DIR)/Quest_3 -lm

data_stat.a: $(BUILD_DIR)/data_stat.o | $(BUILD_DIR)
	ar rcs $(BUILD_DIR)/libdata_stat.a $(BUILD_DIR)/data_stat.o

build_with_static: $(BUILD_DIR)/main_executable_module.o $(BUILD_DIR)/data_io.o \
	$(BUILD_DIR)/data_process.o $(BUILD_DIR)/decision.o data_stat.a
	$(CC) $(CFLAGS) $(BUILD_DIR)/main_executable_module.o $(BUILD_DIR)/data_io.o \
		$(BUILD_DIR)/data_process.o $(BUILD_DIR)/decision.o -L$(BUILD_DIR) -ldata_stat \
		-o $(BUILD_DIR)/Quest_4 -lm

data_process.so: $(DATA_MODULE_DIR)/data_process.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -fPIC -shared $< -o $(BUILD_DIR)/data_process.so

build_with_dynamic: $(BUILD_DIR)/main_executable_module.o $(BUILD_DIR)/data_io.o \
	$(BUILD_DIR)/data_stat.o $(BUILD_DIR)/decision.o data_process.so
	$(CC) $(CFLAGS) -DDYNAMIC_LIB $(BUILD_DIR)/main_executable_module.o $(BUILD_DIR)/data_io.o \
		$(BUILD_DIR)/data_stat.o $(BUILD_DIR)/decision.o -L$(BUILD_DIR) -ldata_process \
		-o $(BUILD_DIR)/Quest_5 -lm

clean:
	rm -rf $(BUILD_DIR)/Quest_3 $(BUILD_DIR)/Quest_4 $(BUILD_DIR)/Quest_5 \
		$(BUILD_DIR)/*.o $(BUILD_DIR)/libdata_stat.a $(BUILD_DIR)/data_process.so

rebuild: clean all
