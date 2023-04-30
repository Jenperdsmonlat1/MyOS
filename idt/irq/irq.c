#include "irq.h"
#include "../idt.h"
#include "../../io/pic/pic.h"
#include "../../libs/stdio/stdio.h"
#include "../../driver/vga/text_mode/vga.h"
#include <stdint.h>

isr_t interrupt_handler[16];

char *exceptions_list_message[] = {
    "Division by zero exception",
    "Debug exception",
    "Non maskable interrupt",
    "Breakpoint exception",
    "Into detected overflow",
    "Out of bound exception",
    "Invalid opcode exception",
    "No coprocessor exception",
    "Double fault",
    "Coprocessor segment overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown interrupt exception",
    "Coprocessor fault",
    "Alignment check exception",
    "Machine check exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void register_interrupt_handler(uint8_t n, isr_t handler) {
    interrupt_handler[n] = handler;
}

void exceptions_handle(uint8_t interrupt) {

    terminal_setcolor(VGA_RED);
    printf("[kernel]: Exception handleled: ");
    printf(exceptions_list_message[interrupt]);
    terminal_setcolor(VGA_WHITE);

    asm volatile("cli; hlt");
    PIC_endOfInterrupt(interrupt);
}

void irq_handler(uint8_t interrupt) {

    PIC_endOfInterrupt(interrupt);
}