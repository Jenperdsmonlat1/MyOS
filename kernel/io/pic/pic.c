#include <io/pic.h>
#include <io/cursor.h>
#include <io/serial_port.h>
#include <vga/text_mode/vga.h>
#include <libs/stdio.h>
#include <stdint.h>

void setupPIC() {

    printf("[+]: Configuration du PIC.\n");

    outb(PIC_COMMAND(PIC1), ICW1_INIT | ICW1_ICW4);
    outb(PIC_COMMAND(PIC2), ICW1_INIT | ICW1_ICW4);
    outb(PIC_DATA(PIC1), PIC1_START_INTERRUPT);
    outb(PIC_DATA(PIC2), PIC2_START_INTERRUPT);
    outb(PIC_DATA(PIC1), 0x04);
    outb(PIC_DATA(PIC2), 0x02);
    outb(PIC_DATA(PIC1), ICW4_8086);
    outb(PIC_DATA(PIC2), ICW4_8086);
    outb(PIC_DATA(PIC1), 0xFF);
    outb(PIC_DATA(PIC2), 0xFF);

    serial_print("[+]: PIC initialized\n", SERIAL_COM1_PORT);
    terminal_setcolor(VGA_GREEN);
    printf("[+]: PIC configure.\n");
    terminal_setcolor(VGA_WHITE);
}

void PIC_endOfInterrupt(uint8_t irq) {

    if (irq >= 40) {
        outb(PIC_COMMAND(PIC2), PIC_EOI);
    } else {
        outb(PIC_COMMAND(PIC1), PIC_EOI);
    }
}