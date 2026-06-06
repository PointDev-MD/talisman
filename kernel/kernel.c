#include <stdint.h>

static volatile uint16_t *const VGA_BUFFER = (uint16_t *)0xB8000;
static uint16_t cursor_pos = 0;

static void put_char(char c, uint8_t color) {
    if (c == '\n') {
        cursor_pos = ((cursor_pos / 80) + 1) * 80;
        return;
    }

    VGA_BUFFER[cursor_pos++] = (uint16_t)c | ((uint16_t)color << 8);

    if (cursor_pos >= 80 * 25) {
        cursor_pos = 0;
    }
}

static void print(const char *str) {
    while (*str) {
        put_char(*str++, 0x0F);
    }
}

void kernel_main(void) {
    print("larpix kernel started\n");
    for (;;) {
        __asm__("hlt");
    }
}