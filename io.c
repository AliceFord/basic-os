#include "io.h"

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ __volatile__ ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

char waitkey() {
    char k;
    //__asm__ __volatile__ ("inb $0x60, %0" : "=a"(k));
    //while ((k = inb(0x60)) < 128);
    //while (inb(0x60) > 128);
    while (!(inb(0x64) & 0x1));
    k = inb(0x60);
    return k;
}