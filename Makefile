TARGET = program

CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -MMD -MP

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(shell find $(SRC_DIR) -name "*.c")

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

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
	rm -rf $(OBJ_DIR) $(TARGET)

run: all
	./$(TARGET) $(ROM)

-include $(DEPS)

.PHONY: all clean run
