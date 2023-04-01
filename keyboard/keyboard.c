#include "keyboard.h"
#include <stdint.h>
#include <stdbool.h>
#include "../io/cursor/cursor.h"

char lettre = 0;


uint8_t get_bytes_from_keyboard() {
    /*uint8_t result;
    asm volatile("inb %1, %0" : "=a"(result) : "d"(KEYBOARD_ENCODER_READ_INPUT_BUFFER));
    return result;*/
    return inb(0x64);
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

char get_touche(char code) {

    switch(code) {        
        case TOUCHE_A:
            lettre = 'a';
            break;
        case TOUCHE_B:
            lettre = 'b';
            break;
        case TOUCHE_C:
            lettre = 'c';
            break;
        case TOUCHE_D:
            lettre = 'd';
            break;
        case TOUCHE_E:
            lettre = 'e';
            break;
        case TOUCHE_F:
            lettre = 'f';
            break;
        case TOUCHE_G:
            lettre = 'g';
            break;
        case TOUCHE_H:
            lettre = 'h';
            break;
        case TOUCHE_I:
            lettre = 'i';
            break;
        case TOUCHE_J:
            lettre = 'j';
            break;
        case TOUCHE_K:
            lettre = 'k';
            break;
        case TOUCHE_L:
            lettre = 'l';
            break;
        case TOUCHE_M:
            lettre = 'm';
            break;
        case TOUCHE_N:
            lettre = 'n';
            break;
        case TOUCHE_O:
            lettre = 'o';
            break;
        case TOUCHE_P:
            lettre = 'p';
            break;
        case TOUCHE_Q:
            lettre = 'q';
            break;
        case TOUCHE_R:
            lettre = 'r';
            break;
        case TOUCHE_S:
            lettre = 's';
            break;
        case TOUCHE_T:
            lettre = 't';
            break;
        case TOUCHE_U:
            lettre = 'u';
            break;
        case TOUCHE_V:
            lettre = 'v';
            break;
        case TOUCHE_W:
            lettre = 'w';
            break;
        case TOUCHE_X:
            lettre = 'x';
            break;
        case TOUCHE_Y:
            lettre = 'y';
            break;
        case TOUCHE_Z:
            lettre = 'z';
            break;
        case TOUCHE_UN:
            lettre = '1';
            break;
        case TOUCHE_DEUX:
            lettre = '2';
            break;
        case TOUCHE_TROIS:
            lettre = '3';
            break;
        case TOUCHE_QUATRE:
            lettre = '4';
            break;
        case TOUCHE_CINQ:
            lettre = '5';
            break;
        case TOUCHE_SIX:
            lettre = '6';
            break;
        case TOUCHE_SEPT:
            lettre = '7';
            break;
        case TOUCHE_HUIT:
            lettre = '8';
            break;
        case TOUCHE_NEUF:
            lettre = '9';
            break;
        case TOUCHE_ZERO:
            lettre = '0';
            break;
        default:
            lettre = '\0';
            break;
    }

    return lettre;
}
