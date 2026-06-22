#ifndef GUI_WIDGET_H
#define GUI_WIDGET_H

#include "object.h"
#include "graphics.h"

typedef struct Widget Widget;
typedef struct WidgetClass WidgetClass;

struct WidgetClass {
    ObjectClass base;
};

struct Widget {
    Object base;
    int visible;
    int focused;
    Color bg_color;
    Color fg_color;
};

Widget *widget_new(void);
void widget_set_bounds(Widget *w, int x, int y, int width, int height);
void widget_set_colors(Widget *w, Color fg, Color bg);
void widget_show(Widget *w);
void widget_hide(Widget *w);

#endif
