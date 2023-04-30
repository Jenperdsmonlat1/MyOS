#include <stdint.h>
#include <stdbool.h>
#include "keyboard.h"
#include "../../io/cursor/cursor.h"
#include "../../io/pic/pic.h"
#include "../../libs/stdio/stdio.h"
#include "../../io/serial_port/serial_port.h"
#include "../../idt/irq/irq.h"
#include "../vga/text_mode/vga.h"


bool keyboard_status_enable = false;

void init_keyboard() {

    printf("[+]: Initialisation du clavier PS/2.\n");
    enable_keyboard();

    uint8_t interface_test_status = keyboard_interface_test();
    terminal_setcolor(VGA_LIGHT_MAGENTA);

    if (interface_test_status == 0)
        printf("[-]: Succes, aucune erreur.\n");
    else if (interface_test_status == 1)
        printf("[-]: La ligne d'horloge est bloque au niveau bas.\n");
    else if (interface_test_status == 2)
        printf("[-]: La ligne d'horloge est bloque a un niveau eleve.\n");
    else if (interface_test_status == 3)
        printf("[-]: La ligne d'horloge est bloque en haut.\n");
    else if (interface_test_status == 255)
        printf("[-]: Erreur generale.\n");

    set_scan_code(KEYBOARD_SCANCODE_2);
    register_interrupt_handler(IRQ1, &keyboard_callback);
    terminal_setcolor(VGA_GREEN);
    printf("[+]: Clavier PS/2 initialise.\n");
    terminal_setcolor(VGA_WHITE);
}

uint8_t get_keyboard_status() {
    return inb(KEYBOARD_CONTROLLER_READ);
}

void send_command(uint8_t command) {

    while (true) {
        if ((get_keyboard_status() & KEYBOARD_OUTPUT_BUFFER_STAT) == 0) {
            break;
        }
    }

    outb(KEYBOARD_CONTROLLER_WRITE, command);
}

uint8_t keyboard_enc_read_buffer() {
    return inb(KEYBOARD_ENCODER_READ_INPUT_BUFFER);
}

char get_code() {
    char character = 0;
    while ((character = keyboard_enc_read_buffer()) != 0) {
        if (character > 0) {
            return character;
        }
    }

    return character;
}

void print_touche(char scancode) {

    if (scancode == 0x00) {
        serial_print("[+]: Internal buffer overrun.\n", SERIAL_COM1_PORT);
    } else if ((scancode >= 0x1 || scancode <= 0x58) && (scancode >= 0x81 || scancode <= 0xD8)) {
        if (scancode == TOUCHE_A)
            printf("a");
        else if (scancode == TOUCHE_A)
            printf("b");
        else if (scancode == TOUCHE_B)
            printf("c");
        else if (scancode == TOUCHE_C)
            printf("d");
        else if (scancode == TOUCHE_D)
            printf("e");
        else if (scancode == TOUCHE_E)
            printf("f");
        else if (scancode == TOUCHE_F)
            printf("g");
        else if (scancode == TOUCHE_G)
            printf("h");
        else if (scancode == TOUCHE_H)
            printf("i");
        else if (scancode == TOUCHE_I)
            printf("j");
        else if (scancode == TOUCHE_J)
            printf("k");
        else if (scancode == TOUCHE_K)
            printf("l");
        else if (scancode == TOUCHE_L)
            printf("m");
        else if (scancode == TOUCHE_M)
            printf("n");
        else if (scancode == TOUCHE_N)
            printf("o");
        else if (scancode == TOUCHE_O)
            printf("p");
        else if (scancode == TOUCHE_P)
            printf("q");
        else if (scancode == TOUCHE_Q)
            printf("r");
        else if (scancode == TOUCHE_R)
            printf("s");
        else if (scancode == TOUCHE_S)
            printf("t");
        else if (scancode == TOUCHE_T)
            printf("u");
        else if (scancode == TOUCHE_U)
            printf("v");
        else if (scancode == TOUCHE_V)
            printf("w");
        else if (scancode == TOUCHE_W)
            printf("x");
        else if (scancode == TOUCHE_X)
            printf("y");
        else if (scancode == TOUCHE_Y)
            printf("z");
        else if (scancode == TOUCHE_Z)
            printf("z");
        else if(scancode == TOUCHE_ZERO)
            printf("0");
        else if (scancode == TOUCHE_UN)
            printf("1");
        else if (scancode == TOUCHE_DEUX)
            printf("2");
        else if (scancode == TOUCHE_TROIS)
            printf("3");
        else if (scancode == TOUCHE_QUATRE)
            printf("4");
        else if (scancode == TOUCHE_CINQ)
            printf("5");
        else if (scancode == TOUCHE_SIX)
            printf("6");
        else if (scancode == TOUCHE_SEPT)
            printf("7");
        else if (scancode == TOUCHE_HUIT)
            printf("8");
        else if (scancode == TOUCHE_NEUF)
            printf("9");
    }
}

uint8_t keyboard_interface_test() {
    
    send_command(KEYBOARD_INTERFACE_TEST);
    return keyboard_enc_read_buffer();
}

uint8_t enable_keyboard() {

    if (keyboard_status_enable == false) {
        send_command(KEYBOARD_ENABLE_KYBR);
        keyboard_status_enable = true;
        return 0;
    } else {
        return 1;
    }
}

uint8_t disable_keyboard() {
    if (keyboard_status_enable == true) {
        send_command(KEYBOARD_DISABLE_KYBR);
        keyboard_status_enable = false;
        return 0;
    } else {
        return 1;
    }
}

void set_scan_code(uint8_t scancode) {
    outb(KEYBOARD_ENCODER_SEND_COMMAND, KEYBOARD_SET_ATLERNATE_SCAN_CODE);
    outb(KEYBOARD_ENCODER_SEND_COMMAND, scancode);
}

void keyboard_callback(/*registers_t regs*/) {
    if (get_keyboard_status() & KEYBOARD_OUTPUT_BUFFER_STAT) {
        //char code = keyboard_enc_read_buffer();
        serial_print("[+]: Touche pressé !!!!\n", SERIAL_COM1_PORT);
        //print_touche(code);
    }

    PIC_endOfInterrupt(1);
}