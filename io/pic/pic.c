#include "pic.h"
#include "../cursor/cursor.h"
#include "../serial_port/serial_port.h"
#include <stdint.h>

void setupPIC() {

    outb(PIC_COMMAND(PIC1), ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC_COMMAND(PIC2), ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC_DATA(PIC1), PIC1_START_INTERRUPT);
    io_wait();
    outb(PIC_DATA(PIC2), PIC2_START_INTERRUPT);
    io_wait();
    outb(PIC_DATA(PIC1), 4);
    io_wait();
    outb(PIC_DATA(PIC2), 2);
    io_wait();
    outb(PIC_DATA(PIC1), ICW4_8086);
    io_wait();
    outb(PIC_DATA(PIC2), ICW4_8086);
    io_wait();

    serial_print("[+]:PIC initialized\n", SERIAL_COM1_PORT);
}

void PIC_endOfInterrupt(uint8_t irq) {

    if (irq >= 8) {
        outb(PIC_COMMAND(PIC2), PIC_EOI);
    } else {
        outb(PIC_COMMAND(PIC1), PIC_EOI);
    }
}
