#ifndef STRING_H
#define STRING_H

#include <stddef.h>

size_t strlen(const char *s);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
int strcmp(const char *a, const char *b);

#endif