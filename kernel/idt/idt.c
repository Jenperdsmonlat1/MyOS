#include <idt/idt.h>
#include <libs/stdio.h>
#include <libs/stdlib.h>
#include <io/pic.h>
#include <idt/irq/irq.h>
#include <video/vga_text.h>
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

    printf("[+]: Chargement de IDT.\n");

    asm volatile("cli");

    memset(&idt, 0, sizeof(idt_entries_t) * 256);
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entries_t) * 256 - 1;

    for (uint8_t vector = 0; vector < 3; vector++) {
        set_idt_descriptor(vector, isr_handlers_table[vector], 0x8E);
    }

    set_idt_descriptor(3, isr_handlers_table[3], 0x8F);
    set_idt_descriptor(4, isr_handlers_table[4], 0x8F);

    for (uint8_t vector = 5; vector < 32; vector++) {
        set_idt_descriptor(vector, isr_handlers_table[vector], 0x8E);
    }

    for (uint8_t vector = 32; vector < 48; vector++) {
        set_idt_descriptor(vector, irq_handle_table[vector-32], 0x8E);
    }

    PICremap();

    load_idt((uint32_t)&idtr);
    asm volatile("sti");

    
    terminal_setcolor(VGA_GREEN);
    printf("[+]: IDT initialise.\n");
    terminal_setcolor(VGA_WHITE);
}
