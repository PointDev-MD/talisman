#ifndef GUI_GRAPHICS_H
#define GUI_GRAPHICS_H

#include <stdint.h>

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define VGA_BUFFER ((uint16_t *)0xB8000)

typedef uint8_t Color;

#define COLOR_BLACK 0x00
#define COLOR_BLUE 0x01
#define COLOR_GREEN 0x02
#define COLOR_CYAN 0x03
#define COLOR_RED 0x04
#define COLOR_MAGENTA 0x05
#define COLOR_BROWN 0x06
#define COLOR_LIGHT_GRAY 0x07
#define COLOR_DARK_GRAY 0x08
#define COLOR_LIGHT_BLUE 0x09
#define COLOR_LIGHT_GREEN 0x0A
#define COLOR_LIGHT_CYAN 0x0B
#define COLOR_LIGHT_RED 0x0C
#define COLOR_LIGHT_MAGENTA 0x0D
#define COLOR_YELLOW 0x0E
#define COLOR_WHITE 0x0F

typedef struct {
    int x, y;
    int width, height;
} Rect;

void graphics_clear(Color bg);
void graphics_draw_char(int x, int y, char c, Color fg, Color bg);
void graphics_draw_string(int x, int y, const char *str, Color fg, Color bg);
void graphics_draw_box(int x, int y, int width, int height, Color fg, Color bg);
void graphics_fill_rect(int x, int y, int width, int height, Color bg);
void graphics_draw_border(int x, int y, int width, int height, Color fg, Color bg);
void graphics_set_cursor(int x, int y);

#endif
