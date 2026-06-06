#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdint.h>

void console_init(void);
void console_clear(void);
void console_putc(char c);
void console_write(const char* str);

#endif // CONSOLE_H