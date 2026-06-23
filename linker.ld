OUTPUT_ARCH(i386)
ENTRY(kernel_main)

SECTIONS
{
    . = 0x10000;

    .text :
    {
        *(.text*)
        *(.rodata*)
        *(.data*)
    }

    .bss :
    {
        *(.bss COMMON)
    }
}
