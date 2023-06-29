#include "io.h"

char waitkey() {
    char k;
    __asm__ __volatile__ ("inb $0x60, %0" : "=a"(k));
    return k;
}