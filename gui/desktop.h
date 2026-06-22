#ifndef GUI_DESKTOP_H
#define GUI_DESKTOP_H

#include "window.h"

typedef struct Desktop Desktop;

Desktop *desktop_new(void);
void desktop_destroy(Desktop *desktop);
void desktop_draw(Desktop *desktop);
void desktop_add_window(Desktop *desktop, Window *window);
void desktop_remove_window(Desktop *desktop, Window *window);
void desktop_handle_event(Desktop *desktop, int event_type, int param);

#endif
