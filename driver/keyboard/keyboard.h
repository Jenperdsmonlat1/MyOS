/* Cet en-tête définie les fonctions utiles à l'affichage des caractères tapés à l'écran
On récupère le code de la touche pressé et on regarde à quel caractère ASCII celle-ci correspond

ce code utilise un clavier QWERTY. Il faudra donc l'adapter afin de pouvoir l'utiliser sur un clavier AZERTY
*/

#include <stdint.h>

//#define KEYBOARD_PORT 0x60

enum TOUCHES {
    TOUCHE_F1 = 0x05,
    TOUCHE_F2 = 0x06,
    TOUCHE_F3 = 0x04,
    TOUCHE_F4 = 0x0C,
    TOUCHE_F5 = 0x03,
    TOUCHE_F6 = 0x0B,
    TOUCHE_F7 = 0x83,
    TOUCHE_F8 = 0x0A,
    TOUCHE_F9 = 0x01,
    TOUCHE_F10 = 0x09,
    TOUCHE_F11 = 0x78,
    TOUCHE_F12 = 0x07,
    TOUCHE_A = 0x1C,
    TOUCHE_B = 0x32,
    TOUCHE_C = 0x21,
    TOUCHE_D = 0x23,
    TOUCHE_E = 0x24,
    TOUCHE_F = 0x2B,
    TOUCHE_G = 0x34,
    TOUCHE_H = 0x33,
    TOUCHE_I = 0x43,
    TOUCHE_J = 0x3B,
    TOUCHE_K = 0x42,
    TOUCHE_L = 0x4B,
    TOUCHE_M = 0x3A,
    TOUCHE_N = 0x31,
    TOUCHE_O = 0x44,
    TOUCHE_P = 0x4D,
    TOUCHE_Q = 0x15,
    TOUCHE_R = 0x2D,
    TOUCHE_S = 0x1B,
    TOUCHE_T = 0x2C,
    TOUCHE_U = 0x3C,
    TOUCHE_V = 0x2A,
    TOUCHE_W = 0x1D,
    TOUCHE_X = 0x22,
    TOUCHE_Y = 0x35,
    TOUCHE_Z = 0x1A,
    TOUCHE_UN = 0x16,
    TOUCHE_DEUX = 0x1E,
    TOUCHE_TROIS = 0x26,
    TOUCHE_QUATRE = 0x25,
    TOUCHE_CINQ = 0x2E,
    TOUCHE_SIX = 0x36,
    TOUCHE_SEPT = 0x3D,
    TOUCHE_HUIT = 0x3E,
    TOUCHE_NEUF = 0x46,
    TOUCHE_ZERO = 0x45,
};

enum KEYBOARD_ENCODER_IO {
    KEYBOARD_ENCODER_READ_INPUT_BUFFER = 0x60,
    KEYBOARD_ENCODER_SEND_COMMAND = 0x60
};

enum KEYBOARD_CONTROLLER_IO {
    KEYBOARD_CONTROLLER_READ = 0x64,
    KEYBOARD_CONTROLLER_WRITE = 0x64
};


void init_keyboard();
uint8_t get_bytes_from_keyboard();
char get_code();
void print_touche(char code);
void keyboard_callback(/*registers_t regs*/);
