#include <stdint.h>
#include "../gui/gui.h"
#include "../gui/window.h"
#include "../gui/button.h"
#include "../gui/label.h"
#include "../libc/stdlib.h"

void kernel_main(void) {
    malloc_init();
    
    GUI *gui = gui_init();
    if (gui) {
        Desktop *desktop = gui_get_desktop(gui);
        
        Window *main_window = window_new("System");
        if (main_window) {
            window_set_position(main_window, 5, 2);
            window_set_size(main_window, 40, 15);
            desktop_add_window(desktop, main_window);
        }
        
        gui_run(gui);
    }
    
    for (;;) {
        __asm__("hlt");
    }
}