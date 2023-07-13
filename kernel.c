#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "io.h"
#include "std.h"
#include "kernel.h"
#include "pico.h"
 
/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
 
/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};
 
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}


static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
 
size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

extern void drive_write(void);

void terminal_initialize(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}
 
void terminal_update_cursor(int x, int y) {
	uint16_t pos = y * VGA_WIDTH + x;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);

	terminal_update_cursor(x+1, y);
}

void internal_terminal_putchar(char c) {
	if (c == '\n') {
		terminal_column = 0;
		terminal_row++;
		return;
	}

	if (c == '\0') {
		return;
	}

	if (c == '\b') {
		if (terminal_column == 0) {
			if (terminal_row != 0) {
				terminal_column = VGA_WIDTH - 1;
				terminal_row--;
			}
		} else {
			terminal_column--;
		}
		terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
		return;
	}

	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}
 
uint8_t terminal_putchar(char c, uint8_t input_index) {
	if (c == '\n') {
		terminal_column = 0;
		terminal_row++;
		terminal_update_cursor(terminal_column, terminal_row);
		return 3;  // newline
	}

	if (c == 0) {
		return 0;  // nothing
	}

	if (c == '\b') {
		if (input_index > 0) {
			if (terminal_column == 0) {
				if (terminal_row != 0) {
					terminal_column = VGA_WIDTH - 1;
					terminal_row--;
				}
			} else {
				terminal_column--;
			}
			terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
			return 2;  // backspace
		} else {
			return 0;  // nothing  
		}
	}

	if (c == '\x1b') {
		return 4;  // escape
	}

	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
	return 1;  // write char
}
 
void terminal_write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		internal_terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) {
	terminal_write(data, strlen(data));
}

void parse_command(const char* command) {
	if (strcmp(command, "test") == 0) {
		internal_terminal_putchar('Y');
	} else if (strcmp(command, "regout") == 0) {
		output_registers();
	} else if (strcmp(command, "alloctest") == 0) {
		char *a = (char*) malloc(1);
		char *b = (char*) malloc(1);
		char *c = (char*) malloc(1);
		*a = 'a';
		*c = 'c';
		*b = 'b';
		// drive_write();
		internal_terminal_putchar(*b);
		internal_terminal_putchar(*a);
		internal_terminal_putchar(*c);
	} else if (strcmp(command, "pico") == 0) {
		run_pico_editor();
	} else {
		terminal_write("Command: \'", 10);
		terminal_write(command, strlen(command));
		terminal_write("\' not found.\n", 13);
	}

	internal_terminal_putchar('>');
}

void kernel_main(void) {
	/* Initialize terminal interface */
	terminal_initialize();
 
	internal_terminal_putchar('>');

	//internal_terminal_putchar('\n');

	//output_registers();

	//drive_write();

	//__asm__ __volatile__("movb 0x03, %%ah");

	char input[256] = {0};
	uint8_t input_index = 0;

	while (true) {
    	char k = waitkey();
		char c = SCANCODE_SET_1[k];
		uint8_t status = terminal_putchar(c, input_index);
		if (status == 1) {
			input[input_index] = c;
			input_index++;
		} else if (status == 2) {
			input[input_index-1] = 0;
			input_index--;
		} else if (status == 3) {
			parse_command(input);

			//terminal_writestring(input); - log buffer
			memset(input, 0, 256);
			input_index = 0; 
		}
	}

	internal_terminal_putchar('!');
}
