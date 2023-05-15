/* Ce fichier header contient quelques définitions 
de fonctions utiles pour afficher du texte à l'écran avec VGA*/

#ifndef _VGA_
#define _VGA_

/* On importe les en-têtes utiles*/
#include <stddef.h>
#include <stdint.h>

/* stddef.h contient des macros et fonctions utiles tels que size_t
 (type non signé du résultat de la taille d'un opérateur)*/

/* stdint.h contient des macros premettant de déclarer des ensembles de types entiers avec des tailles spécifiques
Très utile, tout au long du projet, on n'utilisera pas les mots clés tels que int, long ou char mais les macros de cet en-tête afin 
d'être le plus précis possible quant aux données que l'on utilise.*/

#define VGA_ADDRESS 0xB8000 // Adresse mémoire à partir de laquelle nous allons pouvoir afficher notre texte.
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// Énumération contenant les différentes couleur que nous allons pouvoir afficher à l'écran.
enum vga_color {
    VGA_BLACK = 0,
    VGA_BLUE = 1,
    VGA_GREEN = 2,
    VGA_CYAN = 3,
    VGA_RED = 4,
    VGA_MAGENTA = 5,
    VGA_BROWN = 6,
    VGA_LIGHT_GREY = 7,
    VGA_DARK_GREY = 8,
    VGA_LIGHT_BLUE = 9,
    VGA_LIGHT_GREEN = 10,
    VGA_LIGHT_CYAN = 11,
    VGA_LIGHT_RED = 12,
    VGA_LIGHT_MAGENTA = 13,
    VGA_LIGHT_BROWN = 14,
    VGA_WHITE = 15
};

// Permet de modifier la couleur des caractères à l'écran.
/*static inline uint8_t vga_entry_color(
    enum vga_color fg, enum vga_color bg);

static inline uint16_t vga_entry(
    unsigned char uc, uint8_t color);
*/

// Initialize le terminal.
void terminal_init(enum vga_color fg, enum vga_color bg);

// Modifie la couleur du terminal.
void terminal_setcolor(uint8_t color);

void terminal_putentryat(
    char character, uint8_t color, size_t x, size_t y);

void terminal_putchar(char c);

void terminal_write(
    const char *data, size_t size);

void clear_terminal(uint16_t **terminal_buffer, enum vga_color);
void move_cursor();

#endif
