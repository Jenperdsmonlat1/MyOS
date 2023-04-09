#include "vga.h"
#include "../../io/cursor/cursor.h"
#include <stdint.h>

uint8_t terminal_color;
uint16_t *terminal_buffer;
size_t terminal_row;
size_t terminal_column;
uint8_t line_index;
uint32_t index;
uint16_t position;

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
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
        //terminal_row++;

        if (++terminal_row == VGA_HEIGHT) {
            terminal_row = 0;
        }
    }
}

void terminal_write(const char *data, size_t size) {

    for (size_t i = 0; i < size; i++) {
        if (data[i] == '\n') {
            terminal_row++;
            position = terminal_row * VGA_WIDTH;

            terminal_column = 0;
        } else if (data[i] == '\0') {
            terminal_putchar('\0');
        } else {
            terminal_putchar(data[i]);
            position++;
        }
    }

    move_cursor();
}

void clear_terminal(uint16_t **terminal_buffer, enum vga_color) {
    for (uint16_t i = 0; i < 4000; i++) {
        (*terminal_buffer)[i] = vga_entry(0x20, VGA_BLACK);
        index = 0;
    }
}

void move_cursor() {
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE);
    outb(FB_DATA_PORT, ((position >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE);
    outb(FB_DATA_PORT, position & 0x00FF);
}