# $@ = target file
# $< = first dependency
# $^ = all dependencies

# Directories
SRC_BOOT   = bootloader
SRC_KERNEL = kernel
SRC_LIBC   = libc
BUILD      = build
BIN        = bin
INCLUDE    = base/usr/include

# Tools
CC   = gcc
LD   = ld
NASM = nasm
OBJCOPY = objcopy

# Compiler flags
CFLAGS  = -m64 -O0 -ffreestanding -fno-pie -fno-stack-protector -fno-builtin
CFLAGS += -Wall -Wextra -Wno-unused-function -Wno-unused-parameter -Wstrict-prototypes -Wno-override-init
CFLAGS += -pedantic -Wwrite-strings
CFLAGS += -nostdinc -nostdlib -nodefaultlibs -MMD -MP
CFLAGS += -mcmodel=large  # Important for kernel code

# Linker flags
LDFLAGS = -m elf_x86_64 -T $(SRC_BOOT)/linker.ld --no-warn-rwx-segments

# Include flags
IFLAGS := $(addprefix -I, $(shell find $(INCLUDE) -type d))

# Auto-discover .c sources
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
BOOT_OBJS = $(BUILD)/bootloader/kernel-entry.o $(BUILD)/bootloader/interrupts.o

# All object files for kernel.bin
ALL_OBJS = $(BOOT_OBJS) $(C_OBJS)

# Targets
all: $(BIN)/os.img

run: $(BIN)/os.img
	qemu-system-x86_64 -drive format=raw,file=$<,index=0,if=floppy

debug: $(BIN)/os.img
	qemu-system-x86_64 -drive format=raw,file=$<,index=0,if=floppy -s -S

# Debug the Makefile
test:
	echo $(shell find kernel -name '*.c')


$(BIN)/os.img: $(BUILD)/bootloader/boot $(BIN)/kernel.bin
	cat $^ > $@

# Create binary kernel from ELF
$(BIN)/kernel.bin: $(BIN)/kernel.elf
	$(OBJCOPY) -O binary $< $@

# Link ELF kernel
$(BIN)/kernel.elf: $(ALL_OBJS) $(SRC_BOOT)/linker.ld | $(BIN)
	$(LD) $(LDFLAGS) -o $@ $(ALL_OBJS)

$(BUILD)/bootloader/boot: $(SRC_BOOT)/boot.asm | $(BUILD)/bootloader
	$(NASM) $< -i $(SRC_BOOT)/ -o $@

$(BUILD)/bootloader/kernel-entry.o: $(SRC_BOOT)/kernel-entry.asm | $(BUILD)/bootloader
	$(NASM) $< -f elf64 -o $@

$(BUILD)/bootloader/interrupts.o: $(SRC_BOOT)/interrupts.asm | $(BUILD)/bootloader
	$(NASM) $< -f elf64 -o $@

$(BUILD)/kernel/%.o: $(SRC_KERNEL)/%.c $(C_HDRS) | $(C_OBJ_DIRS)
	$(CC) $(CFLAGS) -g $(IFLAGS) -c -o $@ $<

$(BUILD)/libc/%.o: $(SRC_LIBC)/%.c $(C_HDRS) | $(C_OBJ_DIRS)
	$(CC) $(CFLAGS) -g $(IFLAGS) -c -o $@ $<

# Create directories if nonexistent
$(BIN) $(BUILD)/bootloader $(C_OBJ_DIRS):
	mkdir -p $@

# Include auto-generated dependency files
-include $(C_OBJS:.o=.d)

clean:
	$(RM) -r $(BUILD) $(BIN)/*.bin $(BIN)/*.elf $(BIN)/*.img

.PHONY: all run clean debug
