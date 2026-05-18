# $@ = target file
# $< = first dependency
# $^ = all dependencies

# Directories
SRC_BOOT   = src/boot
SRC_KERNEL = src/kernel
SRC_LIBC   = src/libc
BUILD      = build
BIN        = bin
INCLUDE    = base/usr/include

# Tools
CC   = gcc
LD   = ld
NASM = nasm

# Compiler flags
CFLAGS  = -m32 -O0 -ffreestanding -fno-pie -fno-stack-protector
CFLAGS += -Wall -Wextra -Wno-unused-function -Wno-unused-parameter -Wstrict-prototypes
CFLAGS += -pedantic -Wwrite-strings
CFLAGS += -nostdinc -nostdlib -MMD -MP

#linker flags
LDFLAGS = -m elf_i386 -T $(SRC_BOOT)/linker.ld --oformat binary

# include flags
IFLAGS := $(addprefix -I, $(shell find $(INCLUDE) -type d))

# AUto-discover .c sources
KERNEL_SRCS := $(shell find $(SRC_KERNEL) -name '*.c')
LIBC_SRCS   := $(shell find $(SRC_LIBC)   -name '*.c')

KERNEL_OBJS := $(patsubst $(SRC_KERNEL)/%.c, $(BUILD)/kernel/%.o, $(KERNEL_SRCS))
LIBC_OBJS   := $(patsubst $(SRC_LIBC)/%.c,   $(BUILD)/libc/%.o,   $(LIBC_SRCS))

C_OBJS := $(KERNEL_OBJS) $(LIBC_OBJS)

# Auto-discover all .h headers recursively
C_HDRS := $(shell find $(INCLUDE) -name '*.h')

# Derive the unique set of build subdirs we'll need to create
C_OBJ_DIRS := $(sort $(dir $(C_OBJS)))

# Boot object files
BOOT_OBJS = $(BUILD)/boot/kernel-entry.o $(BUILD)/boot/interrupts.o

# All object files for kernel.bin
ALL_OBJS = $(BOOT_OBJS) $(C_OBJS)

# Targets
all: $(BIN)/os-image.bin

run: $(BIN)/os-image.bin
	qemu-system-i386 -drive format=raw,file=$<,index=0,if=floppy

$(BIN)/os-image.bin: $(BIN)/mbr.bin $(BIN)/kernel.bin
	cat $^ > $@

$(BIN)/kernel.bin: $(ALL_OBJS) | $(BIN)
	$(LD) $(LDFLAGS) -o $@ $^

$(BIN)/mbr.bin: $(SRC_BOOT)/mbr.asm | $(BIN)
	$(NASM) -I$(SRC_BOOT)/ $< -f bin -o $@

$(BUILD)/boot/kernel-entry.o: $(SRC_BOOT)/kernel-entry.asm | $(BUILD)/boot
	$(NASM) $< -f elf32 -o $@

$(BUILD)/boot/interrupts.o: $(SRC_BOOT)/interrupts.asm | $(BUILD)/boot
	$(NASM) $< -f elf32 -o $@


# Compiling - one rule per directory
$(BUILD)/kernel/%.o: $(SRC_KERNEL)/%.c $(C_HDRS) | $(C_OBJ_DIRS)
	$(CC) $(CFLAGS) -g $(IFLAGS) -c -o $@ $<

$(BUILD)/libc/%.o: $(SRC_LIBC)/%.c $(C_HDRS) | $(C_OBJ_DIRS)
	$(CC) $(CFLAGS) -g $(IFLAGS) -c -o $@ $<

# Create directories if nonexistent
$(BIN) $(BUILD)/boot $(C_OBJ_DIRS):
	mkdir -p $@

# Include auto-generated dependency files
-include $(C_OBJS:.o=.d)

clean:
	$(RM) -r $(BUILD) $(BIN)/*.bin

.PHONY: all run clean