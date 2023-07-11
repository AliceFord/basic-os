#include "pico.h"
#include "std.h"
#include "kernel.h"
#include "io.h"

void run_pico_editor() {
    terminal_writestring("pico");

    uint16_t input_index = 0;
    char input[1024];
    uint8_t k;
    char c;
    uint8_t status;

    while (true) {
        k = waitkey();
        c = SCANCODE_SET_1[k];
        char buf[10];
        itoa(k, buf, 10);
        terminal_writestring(buf);
        status = terminal_putchar(c, input_index);  // wtf bug
        if (status == 1) {
            input[input_index] = c;
            input_index++;
        } else if (status == 2) {
            input[input_index-1] = 0;
            input_index--;
        } else if (status == 3) {
            input[input_index] = '\n';
            input_index++;
            terminal_column = 0;
            terminal_update_cursor(terminal_column, ++terminal_row);
        }
    }
}