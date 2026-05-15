# $@ = target file
# $< = first dependency
# $^ = all dependencies

# Directories
SRC_BOOT   = src/boot
SRC_KERNEL = src/kernel
BUILD      = build
BIN        = bin

# Tools
CC   = gcc
LD   = ld
NASM = nasm

# Flags
CFLAGS  = -O0 -fno-pie -fno-stack-protector -m32 -ffreestanding -I$(SRC_KERNEL)
LDFLAGS = -m elf_i386 -T $(SRC_BOOT)/linker.ld --oformat binary -L$(BUILD)

# Auto-discover all .c files in src/kernel
C_SRCS  = $(wildcard $(SRC_KERNEL)/*.c)
C_OBJS  = $(patsubst $(SRC_KERNEL)/%.c, $(BUILD)/%.o, $(C_SRCS))

# Auto-discover all .h files (used as dependencies)
C_HDRS  = $(wildcard $(SRC_KERNEL)/*.h)

# Boot object files
BOOT_OBJS = $(BUILD)/kernel-entry.o $(BUILD)/interrupts.o

# All object files for kernel.bin
KERNEL_OBJS = $(BOOT_OBJS) $(C_OBJS)

# Default target
all: $(BIN)/os-image.bin

# Run in QEMU
run: $(BIN)/os-image.bin
	qemu-system-i386 -fda $<

# Final OS image
$(BIN)/os-image.bin: $(BIN)/mbr.bin $(BIN)/kernel.bin
	cat $^ > $@

# Kernel binary
$(BIN)/kernel.bin: $(KERNEL_OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

# MBR
$(BIN)/mbr.bin: $(SRC_BOOT)/mbr.asm
	$(NASM) -I$(SRC_BOOT)/ $< -f bin -o $@

# Boot ASM objects
$(BUILD)/kernel-entry.o: $(SRC_BOOT)/kernel-entry.asm
	$(NASM) $< -f elf32 -o $@

$(BUILD)/interrupts.o: $(SRC_BOOT)/interrupts.asm
	$(NASM) $< -f elf32 -o $@

# C kernel objects — recompile if any header changes
$(BUILD)/%.o: $(SRC_KERNEL)/%.c $(C_HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Create output dirs if missing
$(BIN) $(BUILD):
	mkdir -p $@

# Make sure dirs exist before building
$(KERNEL_OBJS): | $(BUILD)
$(BIN)/mbr.bin: | $(BIN)

clean:
	$(RM) -r $(BUILD)/*.o $(BIN)/*.bin

.PHONY: all run clean