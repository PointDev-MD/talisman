#include <stdint.h>

uint32_t read_cr0(void) {
    uint32_t value;
    __asm__("mov %%cr0, %0" : "=r" (value));
    return value;
}

void write_cr0(uint32_t value) {
    __asm__("mov %0, %%cr0" :: "r" (value));
}

void halt_cpu(void) {
    __asm__("hlt");
}
