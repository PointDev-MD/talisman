#include "gui.h"
#include "graphics.h"
#include <stdlib.h>

struct GUI {
    Desktop *desktop;
};

GUI *gui_init(void) {
    GUI *gui = (GUI *)malloc(sizeof(GUI));
    if (gui) {
        graphics_clear(COLOR_BLUE);
        gui->desktop = desktop_new();
    }
    return gui;
}

void gui_shutdown(GUI *gui) {
    if (gui) {
        if (gui->desktop) {
            desktop_destroy(gui->desktop);
        }
        free(gui);
    }
}

void gui_run(GUI *gui) {
    if (!gui) return;
    
    for (;;) {
        gui_draw(gui);
        __asm__("hlt");
    }
}

void gui_draw(GUI *gui) {
    if (gui && gui->desktop) {
        desktop_draw(gui->desktop);
    }
}

Desktop *gui_get_desktop(GUI *gui) {
    if (gui) {
        return gui->desktop;
    }
    return NULL;
}
