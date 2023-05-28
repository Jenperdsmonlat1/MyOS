/* Cet en-tête contient toutes les fonctions ainsi que les structures nécessaires à
la création de la table de description globale.*/

#ifndef _GDT_
#define _GDT_

#include <stdint.h>

typedef struct gdt_entry_struct gdt_entry_t;
struct gdt_entry_struct {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

typedef struct gdt_ptr_struct gdt_ptr_t;
struct gdt_ptr_struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));


extern void load_gdt(uint32_t);
void init_gdt();
void gdt_encode_entry(
    uint8_t number, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

#endif
