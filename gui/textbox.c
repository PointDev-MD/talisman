#include "textbox.h"
#include "graphics.h"
#include <stdlib.h>
#include <string.h>

static void textbox_class_destroy(Object *self) {
    free(self);
}

static void textbox_class_draw(Object *self) {
    TextBox *tbox = (TextBox *)self;
    Widget *w = (Widget *)self;
    
    if (!w->visible) return;
    
    int x = self->bounds.x;
    int y = self->bounds.y;
    int width = self->bounds.width;
    
    graphics_fill_rect(x, y, width, 1, COLOR_WHITE);
    graphics_draw_string(x, y, "[ TextBox ]", COLOR_BLACK, COLOR_WHITE);
}

static void textbox_class_handle_event(Object *self, int event_type, int param) {
}

static WidgetClass textbox_class = {
    .base = {
        .destroy = textbox_class_destroy,
        .draw = textbox_class_draw,
        .handle_event = textbox_class_handle_event,
    }
};

TextBox *textbox_new(void) {
    TextBox *tbox = (TextBox *)malloc(sizeof(TextBox));
    if (tbox) {
        tbox->base.base.klass = (ObjectClass *)&textbox_class;
        tbox->base.base.bounds.x = 0;
        tbox->base.base.bounds.y = 0;
        tbox->base.base.bounds.width = 20;
        tbox->base.base.bounds.height = 1;
        tbox->base.visible = 1;
        tbox->base.focused = 0;
        tbox->base.bg_color = COLOR_WHITE;
        tbox->base.fg_color = COLOR_BLACK;
        tbox->cursor_pos = 0;
        tbox->buffer[0] = 0;
    }
    return tbox;
}

void textbox_destroy(TextBox *tbox) {
    if (tbox) {
        object_destroy((Object *)tbox);
    }
}

void textbox_draw(TextBox *tbox) {
    if (tbox) {
        object_draw((Object *)tbox);
    }
}

void textbox_set_text(TextBox *tbox, const char *text) {
    if (tbox && text) {
        strncpy(tbox->buffer, text, 63);
        tbox->buffer[63] = 0;
        tbox->cursor_pos = 0;
    }
}

const char *textbox_get_text(TextBox *tbox) {
    if (tbox) {
        return tbox->buffer;
    }
    return "";
}

void textbox_append_char(TextBox *tbox, char c) {
    if (tbox && tbox->cursor_pos < 63) {
        tbox->buffer[tbox->cursor_pos++] = c;
        tbox->buffer[tbox->cursor_pos] = 0;
    }
}

void textbox_backspace(TextBox *tbox) {
    if (tbox && tbox->cursor_pos > 0) {
        tbox->buffer[--tbox->cursor_pos] = 0;
    }
}
