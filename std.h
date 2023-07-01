#ifndef STD_H
#define STD_H
#endif

#include <stdint.h>
#include <stddef.h>

size_t strlen(const char* str);
void strrev(char str[]);
void itoa(size_t value, char buf[], int base);
