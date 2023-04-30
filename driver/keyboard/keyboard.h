/* Cet en-tête définie les fonctions utiles à l'affichage des caractères tapés à l'écran
On récupère le code de la touche pressé et on regarde à quel caractère ASCII celle-ci correspond

ce code utilise un clavier QWERTY. Il faudra donc l'adapter afin de pouvoir l'utiliser sur un clavier AZERTY
*/

#include <stdint.h>


enum touches {
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

enum keyboard_encoder_io {
    KEYBOARD_ENCODER_READ_INPUT_BUFFER = 0x60,
    KEYBOARD_ENCODER_SEND_COMMAND = 0x60
};

enum keyboard_controller_io {
    KEYBOARD_CONTROLLER_READ = 0x64,
    KEYBOARD_CONTROLLER_WRITE = 0x64
};

enum keyboard_controller_stats {
    KEYBOARD_OUTPUT_BUFFER_STAT = 0x01,
    KEYBOARD_INPUT_BUFFER_STAT = 0x02,
    KEYBOARD_SYSTEM_FLAG = 0x04,
    KEYBOARD_COMMAND_DATA = 0x08,
    KEYBOARD_LOCKED = 0x10,
    KEYBOARD_AUX_OUTPUT_BUFFER_FULL = 0x20,
    KEYBOARD_TIMEOUT = 0x40,
    KEYBOARD_PARITY_ERROR = 0x80
};

enum keyboard_encoder_command {
    KEYBOARD_SET_LED = 0xED,
    KEYBOARD_ECHO_COMMAND = 0xEE,
    KEYBOARD_SET_ATLERNATE_SCAN_CODE = 0xF0,
    KEYBOARD_SEND_2_NEXT_BYTES= 0xF2,
    KEYBOARD_REPEAT_RATE = 0xF3,
    KEYBOARD_ENABLE = 0xF4,
    KEYBOARD_RESET_WAIT_ENABLING = 0xF5,
    KEYBOARD_RESET_BEGIN_SCANNING = 0xF6,
    KEYBOARD_SET_AUTOREPEAT = 0xF7,
    KEYBOARD_SET_KEY_BREAK_MAKE_CODE = 0xF8,
    KEYBOARD_GENERATE_MAKE_CODE = 0xF9,
    KEYBOARD_ALL_KEYS_AUTOREPEAT_SEND_MAKE_BREAK = 0xFA,
    KEYBOARD_SET_SINGLE_KEY_AUTOREPEAT = 0xFB,
    KEYBOARD_SET_SINGLE_KEY_MAKE_BREAK = 0xFC,
    KEYBOARD_SET_SINGLE_KEY_BREAK = 0xFD,
    KEYBOARD_RESEND_LAST_RESULT = 0xFE,
    KEYBOARD_RESET_KEYBOARD = 0xFF
};

enum keyboard_scan_code {
    KEYBOARD_SCANCODE_1 = 0x02,
    KEYBOARD_SCANCODE_2 = 0x04,
    KEYBOARD_SCANCODE_4 = 0x08
};

enum keyboard_return_codes {
    KEYBOARD_INTERNAL_BUFFER_OVERRUN = 0x00,
    KEYBOARD_ID_F2_COMMAND = 0x83AB,
    KEYBOARD_LEFT_SHIFT_MAKE_CODE = 0xAA,
    KEYBOARD_ECHO_COMMAND_RESULT = 0xEE,
    KEYBOARD_ACK_COMMAND = 0xFA,
    KEYBOARD_BAT_FAILD = 0xFC,
    KEYBOARD_DIAGNOSTIC_FAILURE = 0xFD,
    KEYBOARD_RESEND_LAST_COMMAND = 0xFE,
    KEYBOARD_ERROR = 0xFF
};

enum keyboard_controller_command {
    KEYBOARD_READ_COMMAND_BYTE = 0x20,
    KEYBOARD_WRITE_COMMAND_BYTE = 0x60,
    KEYBOARD_SELF_TEST = 0xAA,
    KEYBOARD_INTERFACE_TEST = 0xAB,
    KEYBOARD_DISABLE_KYBR = 0xAD,
    KEYBOARD_ENABLE_KYBR = 0xAE,
    KEYBOARD_READ_INPUT_PORT = 0xC0,
    KEYBOARD_READ_OUTPUT_PORT = 0xD0,
    KEYBOARD_WRITE_OUTPUT_PORT = 0xD1,
    KEYBOARD_READ_TEST_INPUT = 0xE0,
    KEYBOARD_SYSTEM_RESET = 0xFE,
    KEYBOARD_DISABLE_MOUSE_PORT = 0xA7,
    KEYBOARD_ENABLE_MOUSE_PORT = 0xA8,
    KEYBOARD_TEST_MOUSE_PORT = 0xA9,
    KEYBOARD_WRITE_TO_MOUSE = 0xD4
};

void init_keyboard();
uint8_t get_keyboard_status();
uint8_t keyboard_enc_read_buffer();
void send_command(uint8_t command);
char get_code();
void print_touche(char scancode);
uint8_t keyboard_interface_test();
uint8_t enable_keyboard();
uint8_t disable_keyboard();
void set_scan_code(uint8_t scancode);
void keyboard_callback(/*registers_t regs*/);
