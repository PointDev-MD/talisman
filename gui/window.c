#include "window.h"
#include "graphics.h"
#include <stdlib.h>
#include <string.h>

static void window_class_destroy(Object *self) {
    free(self);
}

static void window_class_draw(Object *self) {
    Window *win = (Window *)self;
    
    int x = self->bounds.x;
    int y = self->bounds.y;
    int w = self->bounds.width;
    int h = self->bounds.height;
    
    graphics_draw_border(x, y, w, h, COLOR_LIGHT_CYAN, COLOR_BLUE);
    
    char title_bar[32] = "";
    if (win->title[0]) {
        title_bar[0] = ' ';
        strncpy(title_bar + 1, win->title, 29);
        title_bar[31] = 0;
    }
    graphics_draw_string(x + 1, y, title_bar, COLOR_WHITE, COLOR_BLUE);
}

static void window_class_handle_event(Object *self, int event_type, int param) {
}

static WidgetClass window_class = {
    .base = {
        .destroy = window_class_destroy,
        .draw = window_class_draw,
        .handle_event = window_class_handle_event,
    }
};

Window *window_new(const char *title) {
    Window *w = (Window *)malloc(sizeof(Window));
    if (w) {
        w->base.base.klass = (ObjectClass *)&window_class;
        w->base.base.bounds.x = 0;
        w->base.base.bounds.y = 0;
        w->base.base.bounds.width = 40;
        w->base.base.bounds.height = 15;
        w->base.visible = 1;
        w->base.focused = 0;
        w->base.bg_color = COLOR_BLUE;
        w->base.fg_color = COLOR_WHITE;
        w->widget_count = 0;
        if (title) {
            strncpy(w->title, title, 31);
            w->title[31] = 0;
        } else {
            w->title[0] = 0;
        }
    }
    return w;
}

void window_destroy(Window *w) {
    if (w) {
        object_destroy((Object *)w);
    }
}

void window_draw(Window *w) {
    if (w) {
        object_draw((Object *)w);
    }
}

void window_add_widget(Window *w, Widget *widget) {
    if (w && widget && w->widget_count < MAX_WIDGETS) {
        w->widgets[w->widget_count++] = widget;
    }
}

void window_remove_widget(Window *w, Widget *widget) {
    if (!w || !widget) return;
    
    for (int i = 0; i < w->widget_count; i++) {
        if (w->widgets[i] == widget) {
            for (int j = i; j < w->widget_count - 1; j++) {
                w->widgets[j] = w->widgets[j + 1];
            }
            w->widget_count--;
            break;
        }
    }
}

void window_set_position(Window *w, int x, int y) {
    if (w) {
        w->base.base.bounds.x = x;
        w->base.base.bounds.y = y;
    }
}

void window_set_size(Window *w, int width, int height) {
    if (w) {
        w->base.base.bounds.width = width;
        w->base.base.bounds.height = height;
    }
}

void window_set_title(Window *w, const char *title) {
    if (w && title) {
        strncpy(w->title, title, 31);
        w->title[31] = 0;
    }
}
