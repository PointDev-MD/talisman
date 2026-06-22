#include "label.h"
#include "graphics.h"
#include <stdlib.h>
#include <string.h>

static void label_class_destroy(Object *self) {
    free(self);
}

static void label_class_draw(Object *self) {
    Label *lbl = (Label *)self;
    Widget *w = (Widget *)self;
    
    if (!w->visible) return;
    
    int x = self->bounds.x;
    int y = self->bounds.y;
    
    graphics_draw_string(x, y, lbl->text, w->fg_color, w->bg_color);
}

static void label_class_handle_event(Object *self, int event_type, int param) {
}

static WidgetClass label_class = {
    .base = {
        .destroy = label_class_destroy,
        .draw = label_class_draw,
        .handle_event = label_class_handle_event,
    }
};

Label *label_new(const char *text) {
    Label *lbl = (Label *)malloc(sizeof(Label));
    if (lbl) {
        lbl->base.base.klass = (ObjectClass *)&label_class;
        lbl->base.base.bounds.x = 0;
        lbl->base.base.bounds.y = 0;
        lbl->base.base.bounds.width = 64;
        lbl->base.base.bounds.height = 1;
        lbl->base.visible = 1;
        lbl->base.focused = 0;
        lbl->base.bg_color = COLOR_BLACK;
        lbl->base.fg_color = COLOR_WHITE;
        if (text) {
            strncpy(lbl->text, text, 63);
            lbl->text[63] = 0;
        } else {
            lbl->text[0] = 0;
        }
    }
    return lbl;
}

void label_destroy(Label *lbl) {
    if (lbl) {
        object_destroy((Object *)lbl);
    }
}

void label_draw(Label *lbl) {
    if (lbl) {
        object_draw((Object *)lbl);
    }
}

void label_set_text(Label *lbl, const char *text) {
    if (lbl && text) {
        strncpy(lbl->text, text, 63);
        lbl->text[63] = 0;
    }
}
