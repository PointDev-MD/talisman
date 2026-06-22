#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include "widget.h"

typedef void (*ButtonCallback)(struct Button *btn);

typedef struct {
    Widget base;
    char label[32];
    ButtonCallback callback;
    int pressed;
} Button;

Button *button_new(const char *label);
void button_destroy(Button *btn);
void button_draw(Button *btn);
void button_set_label(Button *btn, const char *label);
void button_set_callback(Button *btn, ButtonCallback callback);
void button_click(Button *btn);

#endif
