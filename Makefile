SHELL := /bin/bash

AS = as --32
LD = ld -m elf_i386
OBJCOPY = objcopy

SRC = boot/boot.s
OBJ = boot.o
ELF = boot.elf
BIN = boot.bin
LD_SCRIPT = linker.ld

ASFLAGS =
LDFLAGS = -T $(LD_SCRIPT) -e _start
OBJCOPYFLAGS = -O binary

.PHONY: all clean

all: $(BIN)

$(OBJ): $(SRC)
	$(AS) $(ASFLAGS) -o $@ $<

$(ELF): $(OBJ) $(LD_SCRIPT)
	$(LD) $(LDFLAGS) -o $@ $<

$(BIN): $(ELF)
	$(OBJCOPY) $(OBJCOPYFLAGS) $< $@

clean:
	rm -f $(OBJ) $(ELF) $(BIN)
