SHELL := /bin/sh

CC = gcc
AS = as --32
LD = ld -m elf_i386
OBJCOPY = objcopy

BOOT_SRC = boot/boot.s
BOOT_OBJ = boot.o
BOOT_BIN = boot.bin

KERNEL_SRCS = kernel/kernel.c cpu/cpu.c drivers/serial.c gui/graphics.c gui/object.c gui/widget.c gui/window.c gui/button.c gui/label.c gui/textbox.c gui/desktop.c gui/gui.c libc/string.c libc/stdlib.c
KERNEL_OBJS = $(KERNEL_SRCS:.c=.o)
KERNEL_BIN = kernel.bin

IMAGE = talisman.img
ISO = talisman.iso

LD_SCRIPT = linker.ld

CFLAGS = -m32 -nostdlib -fno-builtin -fno-stack-protector -ffreestanding -I. -Ilibc
ASFLAGS =
BOOT_LDFLAGS = -Ttext 0x7c00 -e _start
KERNEL_LDFLAGS = -T $(LD_SCRIPT) -e kernel_main
OBJCOPYFLAGS = -O binary

.PHONY: all clean run

all: $(IMAGE) $(ISO)

$(BOOT_OBJ): $(BOOT_SRC)
	$(AS) $(ASFLAGS) -o $@ $<

$(BOOT_BIN): $(BOOT_OBJ)
	$(LD) -m elf_i386 $(BOOT_LDFLAGS) -o boot.elf $<
	$(OBJCOPY) $(OBJCOPYFLAGS) boot.elf $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(KERNEL_BIN): $(KERNEL_OBJS)
	$(LD) -m elf_i386 $(KERNEL_LDFLAGS) -o kernel.tmp.elf $^
	$(OBJCOPY) $(OBJCOPYFLAGS) kernel.tmp.elf $@
	rm kernel.tmp.elf

$(IMAGE): $(BOOT_BIN) $(KERNEL_BIN)
	dd if=/dev/zero of=$@ bs=512 count=2880
	dd if=$(BOOT_BIN) of=$@ bs=512 count=1 conv=notrunc

$(ISO): $(BOOT_BIN) $(KERNEL_BIN)
	mkdir -p iso_root
	cp $(BOOT_BIN) iso_root/
	cp $(KERNEL_BIN) iso_root/
	genisoimage -o $@ -b iso_root/$(BOOT_BIN) -c boot.cat -no-emul-boot -boot-load-size 4 iso_root/ 2>/dev/null || mkisofs -o $@ -b iso_root/$(BOOT_BIN) -c boot.cat -no-emul-boot -boot-load-size 4 iso_root/ 2>/dev/null || (echo "ISO tools not available, skipping ISO creation"; touch $@)

clean:
	rm -f $(BOOT_OBJ) boot.elf $(BOOT_BIN) $(KERNEL_OBJS) $(KERNEL_BIN) $(IMAGE) $(ISO) boot.cat
	rm -rf iso_root

