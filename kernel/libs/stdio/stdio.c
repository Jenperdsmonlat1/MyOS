#include <libs/stdio.h>
#include <libs/strings.h>
#include <vga/text_mode/vga.h>
#include <stdint.h>
#include <stdbool.h>


void printf(const char *string) {
    terminal_write(string, strlen(string));
}

void putchar(char character) {
    terminal_putchar(character);
}

char *itoa(int16_t number, char *dest, uint8_t base) {

    int i = 0;
    bool isNeg = false;
    char source[10];

    if (number == 0) {
        source[i++] = '0';
        source[i] = '\0';
        return dest;
    }

    if (number < 0 && base == 10) {
        isNeg = true;
        number = -number;
    }

    do {
        int result = number % base;
        source[i++] = (result > 9) ? (result - 10) + 'a' : result + '0';
        number /= base;
    } while (number != 0);

    if (isNeg) {
        dest[i++] = '-';
    }

    source[i++] = '\0';
    reverse(source, dest);
    return dest;
}

void reverse(char *source, char *dest) {
    
    uint16_t len = strlen(source), j = 0;
    
    for (int16_t i = len - 1; i > -1; i--) {
        dest[j] = source[i];
        j++;
    }
}
