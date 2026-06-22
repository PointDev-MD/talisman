#ifndef GUI_LABEL_H
#define GUI_LABEL_H

#include "widget.h"

typedef struct {
    Widget base;
    char text[64];
} Label;

Label *label_new(const char *text);
void label_destroy(Label *lbl);
void label_draw(Label *lbl);
void label_set_text(Label *lbl, const char *text);

#endif
