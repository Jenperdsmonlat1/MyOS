#include "idt.h"
#include "../io/stdio/stdio.h"
#include "../io/pic/pic.h"
#include <stdint.h>

__attribute__((aligned(0x10)))
static idt_entries_t idt[256];

static idtr_t idtr;

void set_idt_descriptor(uint8_t vector, void *isr, uint8_t flag) {
    idt_entries_t *descriptor = &idt[vector];
    descriptor->isr_low = (uint32_t)isr & 0xFFFF;
    descriptor->kernel_cs = 0x08;
    descriptor->reserved = 0;
    descriptor->attributes = flag;
    descriptor->isr_high = (uint32_t)isr >> 16;
}

void init_idt(void) {
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entries_t) * 256 - 1;

    for (uint8_t vector = 0; vector < 32; vector++) {
        set_idt_descriptor(vector, isr_handlers_table[vector], 0x8E);
    }

    asm volatile("lidt %0" : : "m"(idtr));
    asm volatile("sti");
}

void exceptions_handle(/*uint8_t interrupt*/) {
    print("[+] - Exception handleled: ");
    //print((char *)interrupt);
    asm volatile("cli; hlt");
    PIC_endOfInterrupt(1);
}
