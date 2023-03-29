/*
Ce fichier contient toutes les fonctions utiles permettant
de réaliser des dessins en mode VGA.
*/

#include <stdint.h>

#define VGA_ADDRESS 0xA0000

enum vga_size {
    VGA_WIDTH = 320,
    VGA_HEIGHT = 200
};

void putpixel(
    int8_t pos_x, int8_t pos_y, uint8_t COLOR);