#include "vga.h"

uint8_t terminal_color;
uint16_t *terminal_buffer;
size_t terminal_row;
size_t terminal_column;

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char *string) {
    size_t len = 0;
    while (string[len]) {
        len++;
    }

    return len;
}

void terminal_init(enum vga_color fg, enum vga_color bg) {

    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(fg, bg);
    terminal_buffer = (uint16_t *)VGA_ADDRESS;

    for (size_t i = 0; i < VGA_HEIGHT; i++) {
        for (size_t j = 0; j < VGA_WIDTH; j++) {
            const size_t index = i * VGA_WIDTH + j;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_setcolor(uint8_t color) {
    terminal_color = color;
}

void terminal_putentryat(char character, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(character, color);
}

void terminal_putchar(char c) {
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);

    if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;

        if (++terminal_row == VGA_HEIGHT) {
            terminal_row = 0;
        }
    }
}

void terminal_write(const char *data, size_t size) {

    for (size_t i = 0; i < size; i++) {
        terminal_putchar(data[i]);
    }
}

void printf(const char *string) {
    terminal_write(string, strlen(string));
}

void clear_terminal(uint16_t **terminal_buffer, enum vga_color) {
    for (uint16_t i = 0; i < 4000; i++) {
        (*terminal_buffer)[i] = vga_entry(0x20, VGA_BLACK);
    }
}