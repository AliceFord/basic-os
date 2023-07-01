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