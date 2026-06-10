#ifndef CPU_H
#define CPU_H

#include <stdint.h>

uint32_t read_cr0(void);
void write_cr0(uint32_t value);
void halt_cpu(void);

#endif