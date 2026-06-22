#include "widget.h"
#include <stdlib.h>

static void widget_class_destroy(Object *self) {
    free(self);
}

static void widget_class_draw(Object *self) {
}

static void widget_class_handle_event(Object *self, int event_type, int param) {
}

static WidgetClass widget_class = {
    .base = {
        .destroy = widget_class_destroy,
        .draw = widget_class_draw,
        .handle_event = widget_class_handle_event,
    }
};

Widget *widget_new(void) {
    Widget *w = (Widget *)malloc(sizeof(Widget));
    if (w) {
        w->base.klass = (ObjectClass *)&widget_class;
        w->base.bounds.x = 0;
        w->base.bounds.y = 0;
        w->base.bounds.width = 10;
        w->base.bounds.height = 1;
        w->visible = 1;
        w->focused = 0;
        w->bg_color = COLOR_BLACK;
        w->fg_color = COLOR_WHITE;
    }
    return w;
}

void widget_set_bounds(Widget *w, int x, int y, int width, int height) {
    if (w) {
        w->base.bounds.x = x;
        w->base.bounds.y = y;
        w->base.bounds.width = width;
        w->base.bounds.height = height;
    }
}

void widget_set_colors(Widget *w, Color fg, Color bg) {
    if (w) {
        w->fg_color = fg;
        w->bg_color = bg;
    }
}

void widget_show(Widget *w) {
    if (w) {
        w->visible = 1;
    }
}

void widget_hide(Widget *w) {
    if (w) {
        w->visible = 0;
    }
}
