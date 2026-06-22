#include "desktop.h"
#include "graphics.h"
#include <stdlib.h>

#define MAX_WINDOWS 8

typedef struct {
    Window *windows[MAX_WINDOWS];
    int window_count;
} DesktopData;

struct Desktop {
    DesktopData data;
};

Desktop *desktop_new(void) {
    Desktop *d = (Desktop *)malloc(sizeof(Desktop));
    if (d) {
        d->data.window_count = 0;
        for (int i = 0; i < MAX_WINDOWS; i++) {
            d->data.windows[i] = NULL;
        }
    }
    return d;
}

void desktop_destroy(Desktop *desktop) {
    if (desktop) {
        for (int i = 0; i < desktop->data.window_count; i++) {
            if (desktop->data.windows[i]) {
                window_destroy(desktop->data.windows[i]);
            }
        }
        free(desktop);
    }
}

void desktop_draw(Desktop *desktop) {
    if (!desktop) return;
    
    graphics_clear(COLOR_BLUE);
    
    for (int i = 0; i < 80; i++) {
        graphics_draw_char(i, 24, '=', COLOR_LIGHT_GRAY, COLOR_BLUE);
    }
    graphics_draw_string(2, 24, " Talisman Desktop ", COLOR_LIGHT_GRAY, COLOR_BLUE);
    
    for (int i = 0; i < desktop->data.window_count; i++) {
        if (desktop->data.windows[i]) {
            window_draw(desktop->data.windows[i]);
        }
    }
}

void desktop_add_window(Desktop *desktop, Window *window) {
    if (desktop && window && desktop->data.window_count < MAX_WINDOWS) {
        desktop->data.windows[desktop->data.window_count++] = window;
    }
}

void desktop_remove_window(Desktop *desktop, Window *window) {
    if (!desktop || !window) return;
    
    for (int i = 0; i < desktop->data.window_count; i++) {
        if (desktop->data.windows[i] == window) {
            for (int j = i; j < desktop->data.window_count - 1; j++) {
                desktop->data.windows[j] = desktop->data.windows[j + 1];
            }
            desktop->data.window_count--;
            break;
        }
    }
}

void desktop_handle_event(Desktop *desktop, int event_type, int param) {
}
