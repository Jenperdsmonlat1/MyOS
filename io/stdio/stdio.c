#include <stddef.h>
#include <stdint.h>
#include "../../vga/vga.h"

size_t strlen(const char *string) {
    size_t len = 0;
    while (string[len]) {
        len++;
    }

    return len;
}

void print(char *string) {
    terminal_write(string, strlen(string));
}

void memset(uint8_t *dest, uint8_t val, uint32_t len) {
    uint8_t *temp = (uint8_t *)dest;
    for (; len != 0; len--) {
        *temp++ = val;
    }
}