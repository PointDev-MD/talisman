#ifndef GUI_WINDOW_H
#define GUI_WINDOW_H

#include "widget.h"

#define MAX_WIDGETS 16

typedef struct {
    Widget base;
    Widget *widgets[MAX_WIDGETS];
    int widget_count;
    char title[32];
} Window;

Window *window_new(const char *title);
void window_destroy(Window *w);
void window_draw(Window *w);
void window_add_widget(Window *w, Widget *widget);
void window_remove_widget(Window *w, Widget *widget);
void window_set_position(Window *w, int x, int y);
void window_set_size(Window *w, int width, int height);
void window_set_title(Window *w, const char *title);

#endif
