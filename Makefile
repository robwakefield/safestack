CC = clang
CFLAGS = -O0
CFLAGS_SAFESTACK = -fsanitize=safe-stack $(CFLAGS)
BUILD_DIR = build

all: buf_overflow local_overflow control_flow_overflow # smash_me

buf_overflow: examples/buf_overflow.c
	$(CC) $(CFLAGS_SAFESTACK) -o $(BUILD_DIR)/examples/buf_overflow_safestack examples/buf_overflow.c
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/examples/buf_overflow examples/buf_overflow.c
	objdump -d $(BUILD_DIR)/examples/buf_overflow_safestack > $(BUILD_DIR)/examples/buf_overflow_safestack.asm 
	objdump -d $(BUILD_DIR)/examples/buf_overflow > $(BUILD_DIR)/examples/buf_overflow.asm

local_overflow: examples/local_overflow.c
	$(CC) $(CFLAGS_SAFESTACK) -o $(BUILD_DIR)/examples/local_overflow_safestack examples/local_overflow.c
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/examples/local_overflow examples/local_overflow.c

control_flow_overflow: examples/control_flow_overflow.c
	$(CC) $(CFLAGS_SAFESTACK) -o $(BUILD_DIR)/examples/control_flow_overflow_safestack examples/control_flow_overflow.c
	$(CC) $(CFLAGS) -fno-stack-protector -o $(BUILD_DIR)/examples/control_flow_overflow examples/control_flow_overflow.c

# smash_me: examples/smash_me.c
# 	$(CC) $(CFLAGS_SAFESTACK) -fno-stack-protector -o $(BUILD_DIR)/examples/smash_me_safestack examples/smash_me.c
# 	$(CC) $(CFLAGS) -fno-stack-protector -o $(BUILD_DIR)/examples/smash_me examples/smash_me.c

clean:
	rm -f $(BUILD_DIR)/examples/*
