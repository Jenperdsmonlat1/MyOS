#include "../io/stdio/stdio.h"
#include "../keyboard/keyboard.h"
#include "../io/serial_port/serial_port.h"
#include "../vga/vga.h"

void loop_input();
void write_on_com();

void kernel_main() {

    terminal_init(VGA_LIGHT_BLUE, VGA_BLACK);
    print("Coucou le monde.");
    write_on_com();
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

void write_on_com() {
    set_bauds_speed_rate(SERIAL_COM1_PORT, 0x02);
    configure_line(SERIAL_COM1_PORT);
    serial_print("Coucou le monde", SERIAL_COM1_PORT);
}