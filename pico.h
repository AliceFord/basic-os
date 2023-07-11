#ifndef PICO_H
#define PICO_H
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

extern size_t terminal_row;
extern size_t terminal_column;
extern uint8_t terminal_color;
extern uint16_t* terminal_buffer;

void run_pico_editor();

