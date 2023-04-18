#include "keyboard.h"
#include <stdint.h>
#include <stdbool.h>
#include "../../io/cursor/cursor.h"
#include "../../libs/stdio/stdio.h"
#include "../../idt/irq/irq.h"
#include "../vga/text_mode/vga.h"

void init_keyboard() {

    /*do {
        outb(0xF0, 0x41);
        outb(0xF4, 0x00);
    } while ((result = inb(0x64)) != 0xFA);*/
    printf("[+]: Initialisation du clavier PS/2.\n");
    outb(0xF0, 0x41);
    outb(0xF4, 0x00);
    register_interrupt_handler(IRQ1, &keyboard_callback);

    terminal_setcolor(VGA_GREEN);
    printf("[+]: Clavier PS/2 initialise.\n");
    terminal_setcolor(VGA_WHITE);
}

uint8_t get_bytes_from_keyboard() {
    /*uint8_t result;
    asm volatile("inb %1, %0" : "=a"(result) : "d"(KEYBOARD_ENCODER_READ_INPUT_BUFFER));
    return result;*/
    return inb(KEYBOARD_ENCODER_READ_INPUT_BUFFER);
}

char get_code() {
    char character = 0;
    while ((character = get_bytes_from_keyboard()) != 0) {
        if (character > 0) {
            return character;
        }
    }

    return character;
}

void print_touche(char code) {

    switch(code) {        
        case TOUCHE_A:
            printf("a");
            break;
        case TOUCHE_B:
            printf("b");
            break;
        case TOUCHE_C:
            printf("c");
            break;
        case TOUCHE_D:
            printf("d");
            break;
        case TOUCHE_E:
            printf("e");
            break;
        case TOUCHE_F:
            printf("f");
            break;
        case TOUCHE_G:
            printf("g");
            break;
        case TOUCHE_H:
            printf("h");
            break;
        case TOUCHE_I:
            printf("i");
            break;
        case TOUCHE_J:
            printf("j");
            break;
        case TOUCHE_K:
            printf("k");
            break;
        case TOUCHE_L:
            printf("l");
            break;
        case TOUCHE_M:
            printf("m");
            break;
        case TOUCHE_N:
            printf("n");
            break;
        case TOUCHE_O:
            printf("o");
            break;
        case TOUCHE_P:
            printf("p");
            break;
        case TOUCHE_Q:
            printf("q");
            break;
        case TOUCHE_R:
            printf("r");
            break;
        case TOUCHE_S:
            printf("s");
            break;
        case TOUCHE_T:
            printf("t");
            break;
        case TOUCHE_U:
            printf("u");
            break;
        case TOUCHE_V:
            printf("v");
            break;
        case TOUCHE_W:
            printf("w");
            break;
        case TOUCHE_X:
            printf("x");
            break;
        case TOUCHE_Y:
            printf("y");
            break;
        case TOUCHE_Z:
            printf("z");
            break;
        case TOUCHE_UN:
            printf("1");
            break;
        case TOUCHE_DEUX:
            printf("2");
            break;
        case TOUCHE_TROIS:
            printf("3");
            break;
        case TOUCHE_QUATRE:
            printf("4");
            break;
        case TOUCHE_CINQ:
            printf("5");
            break;
        case TOUCHE_SIX:
            printf("6");
            break;
        case TOUCHE_SEPT:
            printf("7");
            break;
        case TOUCHE_HUIT:
            printf("8");
            break;
        case TOUCHE_NEUF:
            printf("9");
            break;
        case TOUCHE_ZERO:
            printf("0");
            break;
        default:
            printf("\0");
            break;
    }
}

void keyboard_callback(/*registers_t regs*/) {
    char code = get_code();
    putchar(code);
}