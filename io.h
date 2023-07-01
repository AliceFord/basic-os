#ifndef IO_H
#define IO_H
#endif

#include <stdint.h>

char waitkey();
inline void outb(uint16_t port, uint8_t val);
inline uint8_t inb(uint16_t port);

void output_registers();
