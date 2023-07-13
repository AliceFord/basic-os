#include "io.h"
#include "std.h"
#include "kernel.h"

void outb(uint16_t port, uint8_t val) {
    __asm__ __volatile__ ("outb %0, %1" : : "a"(val), "Nd"(port));
}

uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ __volatile__ ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

char waitkey() {
    char k;
    while (!(inb(0x64) & 0x1));
    k = inb(0x60);
    return k;
}

void output_registers() {
    uint32_t reg;
    char buffer[10];

    __asm__ __volatile__("movl %%eax, %0" : "=r"(reg));
    itoa(reg, buffer, 16);
    terminal_writestring("eax: ");
    terminal_writestring(buffer);
    internal_terminal_putchar('\n');

    __asm__ __volatile__("movl %%ebx, %0" : "=r"(reg));
    itoa(reg, buffer, 16);
    terminal_writestring("ebx: ");
    terminal_writestring(buffer);
    internal_terminal_putchar('\n');

    __asm__ __volatile__("movl %%ecx, %0" : "=r"(reg));
    itoa(reg, buffer, 16);
    terminal_writestring("ecx: ");
    terminal_writestring(buffer);
    internal_terminal_putchar('\n');

    __asm__ __volatile__("movl %%edx, %0" : "=r"(reg));
    itoa(reg, buffer, 16);
    terminal_writestring("edx: ");
    terminal_writestring(buffer);
    internal_terminal_putchar('\n');

    __asm__ __volatile__("movl %%esp, %0" : "=r"(reg));
    itoa(reg, buffer, 16);
    terminal_writestring("esp: ");
    terminal_writestring(buffer);
    internal_terminal_putchar('\n');

    __asm__ __volatile__("movl %%ebp, %0" : "=r"(reg));
    itoa(reg, buffer, 16);
    terminal_writestring("ebp: ");
    terminal_writestring(buffer);
    internal_terminal_putchar('\n');

    __asm__ __volatile__("movl %%esi, %0" : "=r"(reg));
    itoa(reg, buffer, 16);
    terminal_writestring("esi: ");
    terminal_writestring(buffer);
    internal_terminal_putchar('\n');

    __asm__ __volatile__("movl %%edi, %0" : "=r"(reg));
    itoa(reg, buffer, 16);
    terminal_writestring("edi: ");
    terminal_writestring(buffer);
    internal_terminal_putchar('\n');
}