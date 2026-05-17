# $@ = target file
# $< = first dependency
# $^ = all dependencies

# Directories
SRC_BOOT   = src/boot
SRC_KERNEL = src/kernel
BUILD      = build
BIN        = bin
INCLUDE    = base/usr/include

# Tools
CC   = gcc
LD   = ld
NASM = nasm

# Flags
KERNEL_CFLAGS  = -m32 -O0 -ffreestanding -fno-pie -fno-stack-protector
KERNEL_CFLAGS += -Wall -Wextra -Wno-unused-function -Wno-unused-parameter -Wstrict-prototypes
KERNEL_CFLAGS += -pedantic -Wwrite-strings

LDFLAGS = -m elf_i386 -T $(SRC_BOOT)/linker.ld --oformat binary

KERNEL_INCLUDE = $(INCLUDE)/kernel

# Auto-discover .c files
C_SRCS_ROOT = $(wildcard $(SRC_KERNEL)/*.c)
C_SRCS_MISC = $(wildcard $(SRC_KERNEL)/misc/*.c)
C_SRCS_IO = $(wildcard $(SRC_KERNEL)/io/*.c)

C_OBJS_ROOT = $(patsubst $(SRC_KERNEL)/%.c,      $(BUILD)/kernel/%.o,      $(C_SRCS_ROOT))
C_OBJS_MISC = $(patsubst $(SRC_KERNEL)/misc/%.c,  $(BUILD)/kernel/misc/%.o, $(C_SRCS_MISC))
C_OBJS_IO = $(patsubst $(SRC_KERNEL)/io/%.c,  $(BUILD)/kernel/io/%.o, $(C_SRCS_IO))

C_OBJS = $(C_OBJS_ROOT) $(C_OBJS_MISC) $(C_OBJS_IO)

# Headers
C_HDRS = $(wildcard $(INCLUDE)/kernel/*.h) $(wildcard $(INCLUDE)/kernel/*/*.h)

# Boot object files
BOOT_OBJS = $(BUILD)/boot/kernel-entry.o $(BUILD)/boot/interrupts.o

# All object files for kernel.bin
KERNEL_OBJS = $(BOOT_OBJS) $(C_OBJS)

# Default target
all: $(BIN)/os-image.bin

# Run in QEMU
run: $(BIN)/os-image.bin
	qemu-system-i386 -drive format=raw,file=$<,index=0,if=floppy

# Final OS image
$(BIN)/os-image.bin: $(BIN)/mbr.bin $(BIN)/kernel.bin
	cat $^ > $@

# Kernel binary
$(BIN)/kernel.bin: $(KERNEL_OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

# MBR
$(BIN)/mbr.bin: $(SRC_BOOT)/mbr.asm | $(BIN)
	$(NASM) -I$(SRC_BOOT)/ $< -f bin -o $@

# Boot ASM objects
$(BUILD)/boot/kernel-entry.o: $(SRC_BOOT)/kernel-entry.asm | $(BUILD)/boot
	$(NASM) $< -f elf32 -o $@

$(BUILD)/boot/interrupts.o: $(SRC_BOOT)/interrupts.asm | $(BUILD)/boot
	$(NASM) $< -f elf32 -o $@

# C kernel root objects
$(BUILD)/kernel/%.o: $(SRC_KERNEL)/%.c $(C_HDRS) | $(BUILD)/kernel
	$(CC) $(KERNEL_CFLAGS) -nostdlib -g -I$(KERNEL_INCLUDE) -c -o $@ $<

# C kernel misc objects
$(BUILD)/kernel/misc/%.o: $(SRC_KERNEL)/misc/%.c $(C_HDRS) | $(BUILD)/kernel/misc
	$(CC) $(KERNEL_CFLAGS) -nostdlib -g -I$(KERNEL_INCLUDE) -c -o $@ $<

# C kernel io objects
$(BUILD)/kernel/io/%.o: $(SRC_KERNEL)/io/%.c $(C_HDRS) | $(BUILD)/kernel/io
	$(CC) $(KERNEL_CFLAGS) -nostdlib -g -I$(KERNEL_INCLUDE) -c -o $@ $<

# Create output dirs
$(BIN):
	mkdir -p $@

$(BUILD)/boot:
	mkdir -p $@

$(BUILD)/kernel:
	mkdir -p $@

$(BUILD)/kernel/misc:
	mkdir -p $@

$(BUILD)/kernel/io:
	mkdir -p $@

clean:
	$(RM) -r $(BUILD) $(BIN)/*.bin

.PHONY: all run clean