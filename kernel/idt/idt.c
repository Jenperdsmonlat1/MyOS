#include <idt/idt.h>
#include <libs/stdio.h>
#include <io/pic.h>
#include <idt/irq/irq.h>
#include <keyboard/keyboard.h>
#include <io/serial_port.h>
#include <vga/text_mode/vga.h>
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

    char *vector_number = 0;
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entries_t) * 256 - 1;

    for (uint8_t vector = 0; vector < 32; vector++) {
        set_idt_descriptor(vector, isr_handlers_table[vector], 0x8E);
        serial_print("[-]: Setting ISR at vector: ", SERIAL_COM1_PORT);
        itoa(vector, vector_number, 10);
        serial_print(vector_number, SERIAL_COM1_PORT);
        serial_putchar('\n', SERIAL_COM1_PORT);
    }

    serial_print("[+]: Configuration du PIC.\n", SERIAL_COM1_PORT);
    setupPIC();

    for (uint8_t vector = 32; vector < 48; vector++) {
        set_idt_descriptor(vector, irq_handle_table[vector-32], 0x8E);
        serial_print("[-]: Setting IRQ at vector: ", SERIAL_COM1_PORT);
        itoa(vector, vector_number, 10);
        serial_print(vector_number, SERIAL_COM1_PORT);
        serial_putchar('\n', SERIAL_COM1_PORT);
    }

    load_idt((uint32_t)&idtr);
    asm volatile("sti");

    serial_print("[+]: IDT initialized\n", SERIAL_COM1_PORT);
    
    terminal_setcolor(VGA_GREEN);
    printf("[+]: IDT initialise.\n");
    terminal_setcolor(VGA_WHITE);
}
