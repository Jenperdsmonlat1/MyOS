/* Contient toutes les fonctions pour réaliser des dessins
en mode graphique.*/

#include <stdint.h>

#define VGA_GRAPHIC_ADDRESS_MODE 0xA0000

void putpixel(uint32_t x, uint32_t y, uint8_t color);