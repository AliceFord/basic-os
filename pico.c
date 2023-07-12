#include "pico.h"
#include "std.h"
#include "kernel.h"
#include "io.h"

void run_pico_editor() {
    terminal_writestring("pico");

    uint16_t input_index = 0;
    char input[1024];
    char k;
    char c;
    uint8_t status;

    uint8_t test;

    // // Testing
    // // Jump to code, resume operation, return with ret

    // uint8_t *code_ptr = (uint8_t*)malloc(6);  // malloc?0x104000
    // *code_ptr = 0xb4;
    // *(code_ptr+1) = 0x21;
    // *(code_ptr+2) = 0x90;
    // *(code_ptr+3) = 0x90;
    // *(code_ptr+4) = 0x90;
    // *(code_ptr+5) = 0xc3;

    // // jump to code
    // __asm__ __volatile__("mov %0, %%eax" : : "r"(code_ptr));

    // __asm__ __volatile__("call *%eax");

    // // move eax into test
    // __asm__ __volatile__("mov %%ah, %0" : "=r"(test));

    // //__asm__ __volatile__("call 0x104000");

    // internal_terminal_putchar(test);

    // __asm__ __volatile__("nop");
    // __asm__ __volatile__("nop");
    // __asm__ __volatile__("nop");
    // __asm__ __volatile__("nop");
    // __asm__ __volatile__("nop");

    while (true) {
        k = waitkey();
        c = SCANCODE_SET_1[k];
        if (k < 0x00) continue;  // hacky way to ignore key release, super weird bug here somewhere
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
        }
    }
}