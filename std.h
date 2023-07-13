#ifndef STD_H
#define STD_H
#endif

#include <stdint.h>
#include <stddef.h>

size_t strlen(const char* str);
void strrev(char str[]);
// void strcpy(char dest[], const char src[]);
// void strcat(char dest[], const char src[]);
char *strchr(const char *string, int c);
int strcmp(const char *str1, const char *str2);
int strncmp(const char *str1, const char *str2, size_t n);
void itoa(size_t value, char buf[], int base);
void memset(void *str, char c, size_t n);
// void memcpy(void *dest, const void *src, size_t n); these come later
// void *memmove(void *dest, const void *src, size_t n);
// int memcmp(const void *str1, const void *str2, size_t n);
// void *memchr(const void *str, int c, size_t n);

void *malloc(size_t size);