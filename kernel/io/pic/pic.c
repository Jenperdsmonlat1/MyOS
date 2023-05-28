#include <io/pic.h>
#include <io/cursor.h>
#include <io/serial_port.h>
#include <video/vga_text.h>
#include <libs/stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <idt/irq/irq.h>

void PICremap() {

    printf("[+]: Configuration du PIC.\n");

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC1_DATA, PIC1_START_INTERRUPT);
    io_wait();
    outb(PIC2_DATA, PIC2_START_INTERRUPT);
    io_wait();
    outb(PIC1_DATA, 0x04);
    io_wait();
    outb(PIC2_DATA, 0x02);
    io_wait();
    outb(PIC1_DATA, ICW4_8086);
    io_wait();
    outb(PIC2_DATA, ICW4_8086);
    io_wait();

    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);

    serial_print("[+]: PIC initialized\n", SERIAL_COM1_PORT);
    terminal_setcolor(VGA_GREEN);
    printf("[+]: PIC configure.\n");
    terminal_setcolor(VGA_WHITE);
}

bool disable_PIC() {

    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);
    return true;
}

bool enable_PIC() {

    outb(PIC1_DATA, 0x00);
    outb(PIC2_DATA, 0x00);
    return true;
}

bool mask_IRQ(uint8_t irq) {

    uint16_t port;
    uint8_t value;

    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }

    value = inb(port) | (1 << irq);
    outb(port, value);

    return true;
}

bool unmask_IRQ(uint8_t irq) {

    uint16_t port;
    uint8_t value;

    if (irq < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq -= 8;
    }

    value = inb(port) & ~(1 << irq);
    outb(port, value);
    
    return true;
}

void PIC_endOfInterrupt(registers_t regs) {

    if (regs.interrupt >= 40) {
        outb(PIC1_COMMAND, PIC_EOI);
    } else {
        outb(PIC2_COMMAND, PIC_EOI);
    }
}