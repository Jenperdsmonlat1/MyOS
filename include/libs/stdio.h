/* Contient toutes les fonctions utiles permettant 
d'obtenir les entrées utilisateurs et afficher du texte et autre.*/

#ifndef _STDIO_
#define _STDIO_

#include <stdint.h>

void printf(const char *string);
void putchar(char character);
char *itoa(int16_t number, char *dest, uint8_t base);
void reverse(char *source, char *dest);
uint32_t *convertInBinary(uint32_t number);

#endif
