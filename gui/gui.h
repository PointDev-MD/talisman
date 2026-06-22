#ifndef GUI_GUI_H
#define GUI_GUI_H

#include "desktop.h"

typedef struct GUI GUI;

GUI *gui_init(void);
void gui_shutdown(GUI *gui);
void gui_run(GUI *gui);
void gui_draw(GUI *gui);
Desktop *gui_get_desktop(GUI *gui);

#endif
