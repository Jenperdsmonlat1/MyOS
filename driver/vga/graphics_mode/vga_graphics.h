/* Cet en-tête contient toutes les prototypes de fonctions
utiles pour utiliser VGA en mode graphique*/

#include <stdint.h>
#include <stdbool.h>

#define VGA_GRAPHIC_ADDRESS 0xA0000

#define VGA_MISC_REGISTER 0x3C2
#define VGA_CRTC_INDEX_PORT 0x3D4
#define VGA_CRTC_DATA_PORT 0x3D5
#define VGA_SEQUENCER_INDEX 0x3C4
#define VGA_SEQUENCER_DATA 0x3C5
#define VGA_GRAPHICS_CONTROLLER_INDEX 0x3CE
#define VGA_GRAPHICS_CONTROLLER_DATA 0x3CF
#define VGA_ATTRIBUTES_CONTROLLER_INDEX 0x3C0
#define VGA_ATTRIBUTES_CONTROLLER_READ 0x3C1
#define VGA_ATTRIBUTES_CONTROLLER_WRITE 0x3C0
#define VGA_ATTRIBUTES_CONTROLLER_RESET 0x3DA

void init_vga();
bool write_registers(uint8_t *registers);
void putpixel(uint16_t x, uint16_t y, uint8_t color);
void draw_rect(uint16_t width, uint16_t height, uint16_t x, uint16_t y, uint8_t color);
void draw_line(uint16_t width, uint16_t x, uint16_t y, uint8_t color);
//void draw_circle(uint16_t rayon, uint8_t color);

void draw_char(uint8_t character, uint16_t pos_x, uint16_t pos_y, uint8_t color);
void draw_string(char *string, uint16_t pos_x, uint16_t pos_y, uint8_t color);