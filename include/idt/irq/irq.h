/* Cet en-tête contient toutes les fonctions relatives
à la gestion des interruptions.*/

#ifndef _IRQ_
#define _IRQ_

#include <stdint.h>

typedef struct registers registers_t;
struct registers {
    uint32_t ax;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t interrupt, error;
    uint32_t eip, cs, eflag, useresp, ss;
};

typedef void (*isr_t)(registers_t);

void register_interrupt_handler(uint8_t n, isr_t handler);
void exceptions_handle(registers_t regs);
void irq_handler(registers_t regs);

extern void *isr_handlers_table[];
extern void *irq_handle_table[];

#endif
