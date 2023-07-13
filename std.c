#include "std.h"

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void strrev(char str[]) {
	int len = strlen(str);

	char tmp;
	for (int i = 0; i < len / 2; i++) {
		tmp = str[len-i-1];
		str[len-i-1] = str[i];
		str[i] = tmp;
	}
}

void itoa(size_t value, char buf[], int base) {
	// ONLY WORKS FOR BASE 16 RN

	size_t i = 0;

	while (value) {
		uint8_t current = value & 0xF;
		if (current < 0xa) buf[i] = current + 0x30;
		else buf[i] = current + 0x57;
		i++;
		value = value >> 4;
	}

	strrev(buf);
}

void memset(void *str, char c, size_t n) {
	for (size_t i = 0; i < n; i++) {
	     *(char*) str = c;
	     str++;
	}
}

int strcmp(const char *str1, const char *str2) {
	while (*str1 == *str2) {
		str1++;
		str2++;

		if (*str1 == 0 && *str2 == 0) {
			return 0;
		} else if (*str1 == 0 || *str2 == 0) {
			return 1;
		}
	}
	
	return 1;
}

int strncmp(const char *str1, const char *str2, size_t n) {
	while (*str1 == *str2) {
		str1++;
		str2++;
		n--;

		if (n == 0) return 0;

		if (*str1 == 0 && *str2 == 0) {
			return 0;
		} else if (*str1 == 0 || *str2 == 0) {
			return 1;
		}
	}
	
	return 1;
}

char *strchr(const char *string, int c) {
	while (*string != '\0') {
		if (*string == c) {
			return (char*)string;
		}
		string++;
	}
	return 0;
}

volatile void* mem_top = (volatile void*)0x104000;

void *malloc(size_t size) {
	void *out = mem_top;
	mem_top += size;
	return out;
}