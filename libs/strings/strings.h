/* Cet en-tête contient toutes les fonctions relatives 
aux manipulations sur les chaînes de caractères.*/

#include <stdint.h>


void strcat(char *first_string, char *second_string);
void chareplace(char *string, char character, char character_to_replace);
void strcpy(char *source, char *destination);

uint16_t strcmp(char *first_string, char *second_string);
uint16_t strchr(char *string, char *research);
uint16_t strlen(const char *string);