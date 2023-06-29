#ifndef IO_H
#define IO_H
#endif

#include <stdint.h>

char waitkey();
static inline void outb(uint16_t port, uint8_t val);
static inline uint8_t inb(uint16_t port);