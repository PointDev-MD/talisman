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

    mov $0x0e, %ah
    mov $'B', %al
    int $0x10

    xor %ax, %ax
    xor %dx, %dx
    mov $0x02, %ah
    mov $0x01, %al
    mov $0x01, %ch
    mov $0x01, %cl
    mov $0x01, %dl
    mov $0x1000, %bx
    mov %bx, %es
    xor %bx, %bx
    int $0x13

    jnc load_ok

    mov $'E', %al
    mov $0x0e, %ah
    int $0x10
    jmp hang

load_ok:
    cli
    mov $0x2401, %ax
    int $0x15
    
    leal gdt_desc, %eax
    lgdt (%eax)
    
    mov %cr0, %eax
    or $0x00000001, %eax
    mov %eax, %cr0

    ljmpl $0x08, $prot_mode

.code32
prot_mode:
    mov $0x10, %eax
    mov %eax, %ds
    mov %eax, %es
    mov %eax, %ss
    mov $0x7000, %esp
    
    call 0x10000
    hlt

hang:
    hlt
    jmp hang

.align 16
gdt:
    .long 0, 0
    .long 0x0000ffff, 0x00009a00
    .long 0x0000ffff, 0x00009200

gdt_desc:
    .word (gdt_desc - gdt - 1)
    .long gdt

    .org 0x7dfe
    .word 0xaa55

