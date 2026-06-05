; arm bootloader
.code16
.org 0x7c00

.globl _start
.text

_start:
    cli
    xor %ax, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %ss
    mov $0x7c00, %sp

    mov $message, %si
    call print_string

hang:
    hlt
    jmp hang

print_string:
    mov $0x0e, %ah
.print_loop:
    lodsb
    cmp $0, %al
    je .done
    int $0x10
    jmp .print_loop
.done:
    ret

message:
    .ascii "LARPIX bootloader loaded.\r\n"
    .byte 0

    .fill 510-($-$$), 1, 0
    .word 0xaa55
