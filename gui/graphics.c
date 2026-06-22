#include "graphics.h"

void graphics_clear(Color bg) {
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
        VGA_BUFFER[i] = (uint16_t)(' ' | (bg << 4));
    }
}

void graphics_draw_char(int x, int y, char c, Color fg, Color bg) {
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        return;
    }
    int pos = y * SCREEN_WIDTH + x;
    uint16_t attr = (uint16_t)(bg << 4) | fg;
    VGA_BUFFER[pos] = (uint16_t)c | (attr << 8);
}

void graphics_draw_string(int x, int y, const char *str, Color fg, Color bg) {
    int pos = x;
    while (*str && pos < SCREEN_WIDTH) {
        graphics_draw_char(pos++, y, *str++, fg, bg);
    }
}

void graphics_draw_box(int x, int y, int width, int height, Color fg, Color bg) {
    for (int i = 0; i < width; i++) {
        graphics_draw_char(x + i, y, '-', fg, bg);
        graphics_draw_char(x + i, y + height - 1, '-', fg, bg);
    }
    for (int i = 0; i < height; i++) {
        graphics_draw_char(x, y + i, '|', fg, bg);
        graphics_draw_char(x + width - 1, y + i, '|', fg, bg);
    }
    graphics_draw_char(x, y, '+', fg, bg);
    graphics_draw_char(x + width - 1, y, '+', fg, bg);
    graphics_draw_char(x, y + height - 1, '+', fg, bg);
    graphics_draw_char(x + width - 1, y + height - 1, '+', fg, bg);
}

void graphics_fill_rect(int x, int y, int width, int height, Color bg) {
    for (int cy = y; cy < y + height; cy++) {
        for (int cx = x; cx < x + width; cx++) {
            if (cx >= 0 && cx < SCREEN_WIDTH && cy >= 0 && cy < SCREEN_HEIGHT) {
                graphics_draw_char(cx, cy, ' ', COLOR_WHITE, bg);
            }
        }
    }
}

void graphics_draw_border(int x, int y, int width, int height, Color fg, Color bg) {
    graphics_fill_rect(x, y, width, height, bg);
    graphics_draw_box(x, y, width, height, fg, bg);
}

void graphics_set_cursor(int x, int y) {
}
