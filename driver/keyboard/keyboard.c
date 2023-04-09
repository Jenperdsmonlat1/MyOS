#include "keyboard.h"
#include <stdint.h>
#include <stdbool.h>
#include "../../io/cursor/cursor.h"
#include "../../io/stdio/stdio.h"
#include "../../idt/idt.h"


uint8_t get_bytes_from_keyboard() {
    /*uint8_t result;
    asm volatile("inb %1, %0" : "=a"(result) : "d"(KEYBOARD_ENCODER_READ_INPUT_BUFFER));
    return result;*/
    return inb(KEYBOARD_ENCODER_READ_INPUT_BUFFER);
}

unsigned char get_code() {
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
            print("a");
            break;
        case TOUCHE_B:
            print("b");
            break;
        case TOUCHE_C:
            print("c");
            break;
        case TOUCHE_D:
            print("d");
            break;
        case TOUCHE_E:
            print("e");
            break;
        case TOUCHE_F:
            print("f");
            break;
        case TOUCHE_G:
            print("g");
            break;
        case TOUCHE_H:
            print("h");
            break;
        case TOUCHE_I:
            print("i");
            break;
        case TOUCHE_J:
            print("j");
            break;
        case TOUCHE_K:
            print("k");
            break;
        case TOUCHE_L:
            print("l");
            break;
        case TOUCHE_M:
            print("m");
            break;
        case TOUCHE_N:
            print("n");
            break;
        case TOUCHE_O:
            print("o");
            break;
        case TOUCHE_P:
            print("p");
            break;
        case TOUCHE_Q:
            print("q");
            break;
        case TOUCHE_R:
            print("r");
            break;
        case TOUCHE_S:
            print("s");
            break;
        case TOUCHE_T:
            print("t");
            break;
        case TOUCHE_U:
            print("u");
            break;
        case TOUCHE_V:
            print("v");
            break;
        case TOUCHE_W:
            print("w");
            break;
        case TOUCHE_X:
            print("x");
            break;
        case TOUCHE_Y:
            print("y");
            break;
        case TOUCHE_Z:
            print("z");
            break;
        case TOUCHE_UN:
            print("1");
            break;
        case TOUCHE_DEUX:
            print("2");
            break;
        case TOUCHE_TROIS:
            print("3");
            break;
        case TOUCHE_QUATRE:
            print("4");
            break;
        case TOUCHE_CINQ:
            print("5");
            break;
        case TOUCHE_SIX:
            print("6");
            break;
        case TOUCHE_SEPT:
            print("7");
            break;
        case TOUCHE_HUIT:
            print("8");
            break;
        case TOUCHE_NEUF:
            print("9");
            break;
        case TOUCHE_ZERO:
            print("0");
            break;
        default:
            print("\0");
            break;
    }
}
