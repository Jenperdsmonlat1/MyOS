/* En-tête contenant toutes les fonctions ainsi que les macros
et les structures utiles pour gérer les exceptions.*/

#include <stdint.h>

typedef struct idt_entries idt_entries_t;
struct idt_entries {
    uint16_t isr_low;
    uint16_t kernel_cs;
    uint8_t reserved;
    uint8_t attributes;
    uint16_t isr_high;
} __attribute__((packed));

typedef struct idtr idtr_t;
struct idtr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

__attribute__((noreturn))
void exceptions_handle(void/*uint8_t interrupt*/);
void set_idt_descriptor(uint8_t vector, void *isr, uint8_t flag);
void init_idt(void);

extern void *isr_handlers_table[];
