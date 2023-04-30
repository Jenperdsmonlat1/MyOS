/* Cet en-tête contient toutes les fonctions relatives
à la gestion des interruptions.*/

#include <stdint.h>

enum IRQ {
    IRQ0 = 0,
    IRQ1 = 1,
    IRQ2 = 2,
    IRQ3 = 3,
    IRQ4 = 4,
    IRQ5 = 5,
    IRQ6 = 6,
    IRQ7 = 7,
    IRQ8 = 8,
    IRQ9 = 9,
    IRQ10 = 10,
    IRQ11 = 11,
    IRQ12 = 12,
    IRQ13 = 13,
    IRQ14 = 14,
    IRQ15 = 15,
};

typedef struct registers registers_t;
struct registers {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, eax, ecx;
    uint32_t interrupt, error;
    uint32_t eip, cs, eflag, ss;
};

typedef void (*isr_t)(registers_t);

void register_interrupt_handler(uint8_t n, isr_t handler);
void exceptions_handle(uint8_t interrupt);
void irq_handler(uint8_t interrupt);

extern void *isr_handlers_table[];
extern void *irq_handle_table[];
