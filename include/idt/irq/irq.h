/* Cet en-tête contient toutes les fonctions relatives
à la gestion des interruptions.*/

#ifndef _IRQ_
#define _IRQ_

#include <stdint.h>

typedef struct registers registers_t;
struct registers {
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t interrupt, error;
    uint32_t eip, cs, eflag;
} __attribute__((packed));

void register_interrupt_handler(uint8_t number, void (*handler)(registers_t *regs));
void exceptions_handle(registers_t regs);
void irq_handler(registers_t *regs);

extern void *isr_handlers_table[];
extern void *irq_handle_table[];

#endif
