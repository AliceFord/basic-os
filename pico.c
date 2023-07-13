#include "pico.h"
#include "std.h"
#include "kernel.h"
#include "io.h"

#define BYTE(b) *code_write = b; code_write++

uint8_t *compile(char *input) {
    uint8_t *code_ptr = (uint8_t*)malloc(1024);
    uint8_t *code_write = code_ptr;

    char current[20] = {0};
    char regA[4] = {0};
    char regB[4] = {0};
    char valA[5] = {0};
    uint8_t code_index = 0;

    while (*input != '\0') {
        uint8_t maxI = 19;
        for (uint8_t i = 0; i < 20; i++) {  // max line length 20
            if (*(input+i) == '\n') {
                maxI = i;
                break;
            } 
            current[i] = *(input+i);
        }

        input += maxI + 1;

        if (strncmp(current, "mov", 3) == 0) {  // mov
            char *spacePos = strchr(current, ' ');
            char *commaPos = strchr(current, ',');

            if (spacePos == 0 || commaPos == 0) {
                internal_terminal_putchar('l');
                // error
            }

            uint8_t aLen = (uint8_t)(commaPos - spacePos - 1);
            if (strncmp(current+4, "ah", 2) == 0) {  // if AH
                BYTE(0xb4);
                BYTE(0x21);
            }
        } else {
            internal_terminal_putchar('e');
            // error
        }

        memset(current, 0, 20);
    }

    BYTE(0xc3);  // ret - VERY important

    return code_ptr;
}

void run_pico_editor() {
    terminal_writestring("pico\n");

    uint16_t input_index = 0;
    char input[1024] = {0};
    char k;
    char c;
    uint8_t status;

    char outbyte = 'a';

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
        } else if (status == 4) {
            uint8_t *code_location = compile(input);

            __asm__ __volatile__("mov %0, %%eax" : : "r"(code_location)); // 0x104000
            __asm__ __volatile__("call *%eax");
            //__asm__ __volatile__("mov 0x21, %ah");
            __asm__ __volatile__("mov %%ah, %0" : "=r"(outbyte));
            
            //output_registers();

            internal_terminal_putchar(outbyte);
        }
    }
}