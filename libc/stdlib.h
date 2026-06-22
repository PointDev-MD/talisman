#ifndef STDLIB_H
#define STDLIB_H

#include <stddef.h>

void malloc_init(void);
void *malloc(size_t size);
void free(void *ptr);

#endif
