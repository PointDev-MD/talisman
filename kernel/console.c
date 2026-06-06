#include "console.h"
#include <stdint.h>

static uint16_t* video_memory = (uint16_t*)0xB8000;
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

static void console_scroll() {
    if (cursor_y >= 25) {
        for (int i = 0; i < 24 * 80; i++) {
            video_memory[i] = video_memory[i + 80];
        }
        for (int i = 24 * 80; i < 25 * 80; i++) {
            video_memory[i] = (0x0F << 8) | ' ';
        }
        cursor_y = 24;
    }
}