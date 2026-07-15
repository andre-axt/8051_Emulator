TARGET = program

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -MMD -MP

DEBUG_MODE ?= MEMORY

ifeq ($(DEBUG_MODE), MEMORY)
    CFLAGS += -DDEBUG_MEMORY
endif

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(shell find $(SRC_DIR) -name "*.c")

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

DEBUG_TRACKER = .debug_mode_state
PREV_DEBUG_MODE := $(shell cat $(DEBUG_TRACKER) 2>/dev/null)

ifneq ($(DEBUG_MODE), $(PREV_DEBUG_MODE))
    $(shell echo "$(DEBUG_MODE)" > $(DEBUG_TRACKER))
    $(shell rm -f $(TARGET) $(OBJS))
endif

DEPS = $(OBJS:.o=.d)

INCLUDES = $(addprefix -I, $(shell find $(SRC_DIR) -type d))
CFLAGS += $(INCLUDES)

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Linking final executable: $@"
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "Compiling: $<"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up build files..."
	rm -rf $(OBJ_DIR) $(TARGET) $(DEBUG_TRACKER)

run: all
	./$(TARGET) $(ROM) $(DEBUG_MODE)

-include $(DEPS)

.PHONY: all clean run
