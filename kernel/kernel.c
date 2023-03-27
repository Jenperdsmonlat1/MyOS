#include "../vga/vga.h"
#include "../keyboard/keyboard.h"
#include <stdbool.h>

void loop_input();

void kernel_main() {

    terminal_init(VGA_LIGHT_RED, VGA_BLACK);
    printf("Coucou le monde.");
//    loop_input();
}

void loop_input() {

    char character = 0;
    char keycode = 0;

    do {
        keycode = get_code();
        character = get_touche(keycode);
        terminal_putchar(character);
    } while (character > 0);
}