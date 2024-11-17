CC = clang
CFLAGS = -fsanitize=safe-stack -Wall -Wextra
BUILD_DIR = build

all: main unsafe

main: examples/main.c
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/examples/main examples/main.c

unsafe: exploits/unsafe.c
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/exploits/unsafe exploits/unsafe.c

clean:
	rm -f $(BUILD_DIR)/examples/* $(BUILD_DIR)/exploits/*
