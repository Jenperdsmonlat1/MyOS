#include <stddef.h>
#include "../../vga/vga.h"

size_t strlen(const char *string) {
    size_t len = 0;
    while (string[len]) {
        len++;
    }

    return len;
}

void print(const char *string) {
    terminal_write(string, strlen(string));
}