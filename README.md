# TALISMAN Operating Sys
Talisman is a general operating system developed by Tacoma. It is the spiritual successor to `pointOS`.

## Build

Run:

    make

This produces:

- `boot.o`
- `boot.elf`
- `boot.bin`

## Run

To boot the generated image in QEMU:

    qemu-system-i386 -drive format=raw,file=boot.bin

Or as a floppy:

    qemu-system-i386 -fda boot.bin

## Create a floppy image

Create a raw floppy image and copy the boot sector into it:

    dd if=/dev/zero of=boot.img bs=512 count=2880
    dd if=boot.bin of=boot.img conv=notrunc

Then boot the floppy image:

    qemu-system-i386 -fda boot.img
