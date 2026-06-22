#ifndef GUI_TEXTBOX_H
#define GUI_TEXTBOX_H

#include "widget.h"

typedef struct {
    Widget base;
    char buffer[64];
    int cursor_pos;
} TextBox;

TextBox *textbox_new(void);
void textbox_destroy(TextBox *tbox);
void textbox_draw(TextBox *tbox);
void textbox_set_text(TextBox *tbox, const char *text);
const char *textbox_get_text(TextBox *tbox);
void textbox_append_char(TextBox *tbox, char c);
void textbox_backspace(TextBox *tbox);

#endif
