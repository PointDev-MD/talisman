#include "button.h"
#include "graphics.h"
#include <stdlib.h>
#include <string.h>

static void button_class_destroy(Object *self) {
    free(self);
}

static void button_class_draw(Object *self) {
    Button *btn = (Button *)self;
    Widget *w = (Widget *)self;
    
    if (!w->visible) return;
    
    int x = self->bounds.x;
    int y = self->bounds.y;
    int width = self->bounds.width;
    
    graphics_fill_rect(x, y, width, 1, COLOR_CYAN);
    graphics_draw_string(x, y, "[ Button ]", COLOR_BLACK, COLOR_CYAN);
}

static void button_class_handle_event(Object *self, int event_type, int param) {
}

static WidgetClass button_class = {
    .base = {
        .destroy = button_class_destroy,
        .draw = button_class_draw,
        .handle_event = button_class_handle_event,
    }
};

Button *button_new(const char *label) {
    Button *btn = (Button *)malloc(sizeof(Button));
    if (btn) {
        btn->base.base.klass = (ObjectClass *)&button_class;
        btn->base.base.bounds.x = 0;
        btn->base.base.bounds.y = 0;
        btn->base.base.bounds.width = 12;
        btn->base.base.bounds.height = 1;
        btn->base.visible = 1;
        btn->base.focused = 0;
        btn->base.bg_color = COLOR_CYAN;
        btn->base.fg_color = COLOR_BLACK;
        btn->pressed = 0;
        btn->callback = NULL;
        if (label) {
            strncpy(btn->label, label, 31);
            btn->label[31] = 0;
        } else {
            btn->label[0] = 0;
        }
    }
    return btn;
}

void button_destroy(Button *btn) {
    if (btn) {
        object_destroy((Object *)btn);
    }
}

void button_draw(Button *btn) {
    if (btn) {
        object_draw((Object *)btn);
    }
}

void button_set_label(Button *btn, const char *label) {
    if (btn && label) {
        strncpy(btn->label, label, 31);
        btn->label[31] = 0;
    }
}

void button_set_callback(Button *btn, ButtonCallback callback) {
    if (btn) {
        btn->callback = callback;
    }
}

void button_click(Button *btn) {
    if (btn && btn->callback) {
        btn->callback(btn);
    }
}
