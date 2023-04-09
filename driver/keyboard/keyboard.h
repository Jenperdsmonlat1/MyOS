/* Cet en-tête définie les fonctions utiles à l'affichage des caractères tapés à l'écran
On récupère le code de la touche pressé et on regarde à quel caractère ASCII celle-ci correspond

ce code utilise un clavier QWERTY. Il faudra donc l'adapter afin de pouvoir l'utiliser sur un clavier AZERTY
*/

#include <stdint.h>

//#define KEYBOARD_PORT 0x60

#define TOUCHE_F1 0x05
#define TOUCHE_F2 0x06
#define TOUCHE_F3 0x04
#define TOUCHE_F4 0x0C
#define TOUCHE_F5 0x03
#define TOUCHE_F6 0x0B
#define TOUCHE_F7 0x83
#define TOUCHE_F8 0x0A
#define TOUCHE_F9 0x01
#define TOUCHE_F10 0x09
#define TOUCHE_F11 0x78
#define TOUCHE_F12 0x07

#define TOUCHE_A 0x1C
#define TOUCHE_B 0x32
#define TOUCHE_C 0x21
#define TOUCHE_D 0x23
#define TOUCHE_E 0x24
#define TOUCHE_F 0x2B
#define TOUCHE_G 0x34
#define TOUCHE_H 0x33
#define TOUCHE_I 0x43
#define TOUCHE_J 0x3B
#define TOUCHE_K 0x42
#define TOUCHE_L 0x4B
#define TOUCHE_M 0x3A
#define TOUCHE_N 0x31
#define TOUCHE_O 0x44
#define TOUCHE_P 0x4D
#define TOUCHE_Q 0x15
#define TOUCHE_R 0x2D
#define TOUCHE_S 0x1B
#define TOUCHE_T 0x2C
#define TOUCHE_U 0x3C
#define TOUCHE_V 0x2A
#define TOUCHE_W 0x1D
#define TOUCHE_X 0x22
#define TOUCHE_Y 0x35
#define TOUCHE_Z 0x1A

#define TOUCHE_UN 0x16
#define TOUCHE_DEUX 0x1E
#define TOUCHE_TROIS 0x26
#define TOUCHE_QUATRE 0x25
#define TOUCHE_CINQ 0x2E
#define TOUCHE_SIX 0x36
#define TOUCHE_SEPT 0x3D
#define TOUCHE_HUIT 0x3E
#define TOUCHE_NEUF 0x46
#define TOUCHE_ZERO 0x45

enum KEYBOARD_ENCODER_IO {
    KEYBOARD_ENCODER_READ_INPUT_BUFFER = 0x60,
    KEYBOARD_ENCODER_SEND_COMMAND = 0x60
};

enum KEYBOARD_CONTROLLER_IO {
    KEYBOARD_CONTROLLER_READ = 0x64,
    KEYBOARD_CONTROLLER_WRITE = 0x64
};


uint8_t get_bytes_from_keyboard();
unsigned char get_code();
void print_touche(char code);
