#ifndef KERNEL_H
#define KERNEL_H

#include <stdint.h>

void kernel_main(void);
void kernel_panic(const char *message);

#endif // KERNEL_H