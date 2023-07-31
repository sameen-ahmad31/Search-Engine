.PHONY: clean build all

# compilation settings
CC = gcc
CFLAGS = -I$(INCLUDE_DIR) -Wall -Wextra -Werror -pedantic -std=gnu99 -pedantic -Wmissing-prototypes -Wstrict-prototypes -Wold-style-definition -g

# directory paths
INCLUDE_DIR = ./
SRC_DIR = ./
OBJ_DIR = ./

# file lists
CFILES = search.c hashmap.c functions.c
OBJS = search.o hashmap.o functions.o

# binary
BIN = search

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< -lm

$(BIN): $(OBJS)
	$(CC) -o $@ $(OBJS) -lm

clean:
	rm -f $(OBJS) $(BIN) *~