#include "pic.h"
#include "../cursor/cursor.h"
#include "../serial_port/serial_port.h"
#include "../../driver/vga/text_mode/vga.h"
#include "../../libs/stdio/stdio.h"
#include <stdint.h>

void setupPIC() {

    uint8_t mask_pic1 = inb(PIC1);
    uint8_t mask_pic2 = inb(PIC2);
    printf("[+]: Configuration du PIC.\n");

    outb(PIC_COMMAND(PIC1), ICW1_INIT | ICW1_ICW4);
    outb(PIC_COMMAND(PIC2), ICW1_INIT | ICW1_ICW4);
    outb(PIC_DATA(PIC1), PIC1_START_INTERRUPT);
    outb(PIC_DATA(PIC2), PIC2_START_INTERRUPT);
    outb(PIC_DATA(PIC1), 4);
    outb(PIC_DATA(PIC2), 2);
    outb(PIC_DATA(PIC1), ICW4_8086);
    outb(PIC_DATA(PIC2), ICW4_8086);

    serial_print("[+]: PIC initialized\n", SERIAL_COM1_PORT);
    
    terminal_setcolor(VGA_GREEN);
    printf("[+]: PIC configure.\n");
    terminal_setcolor(VGA_WHITE);

    outb(PIC_DATA(PIC1), mask_pic1);
    outb(PIC_DATA(PIC2), mask_pic2);
}

void PIC_endOfInterrupt(uint8_t irq) {

    if (irq >= 40) {
        outb(PIC_COMMAND(PIC2), PIC_EOI);
    } else {
        outb(PIC_COMMAND(PIC1), PIC_EOI);
    }
}