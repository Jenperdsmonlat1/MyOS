/* Cet en-tête contient toutes les fonctions ainsi que les structures nécessaires à
la création de la table de description globale.*/

#include <stdint.h>

struct gdt {
    uint16_t address;
    uint8_t size;
} __attribute__((packed));

uint8_t load_gdt(struct gdt *gdt);