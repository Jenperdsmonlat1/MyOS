#include "pit.h"
#include <stdint.h>
#include "../../idt/irq/irq.h"
#include "../../libs/stdio/stdio.h"
#include "../serial_port/serial_port.h"
#include "../cursor/cursor.h"
#include "../../driver/vga/text_mode/vga.h"


char *timer;
uint32_t time = 0;

static void pit_callback(registers_t regs) {
    
    time++;
}

void init_pit(uint8_t frequency) {

    printf("[+]: Initialisation du PIT.\n");

    register_interrupt_handler(IRQ0, &pit_callback);

    uint32_t divisor = 1193182 / frequency;
    outb(MODE_COMMAND_REGISTER, 0x36);

    outb(CHANNEL_ZERO, (uint8_t)(divisor & 0xFF));
    outb(CHANNEL_ZERO, (uint8_t)((divisor >> 8) & 0xFF));
    //serial_print("[+]: PIT initialisé", SERIAL_COM1_PORT);
    terminal_setcolor(VGA_GREEN);
    printf("[+]: PIT initialise.\n");
    terminal_setcolor(VGA_WHITE);
}

void timer_wait(uint32_t delay) {

    uint32_t eticks = 0;
    eticks = time + delay;
    while (time < eticks);
}

void make_beep(uint32_t frequency) {

    uint32_t div;
    uint8_t tmp;

    div = 1193182 / frequency;
    outb(MODE_COMMAND_REGISTER, 0xB6);
    outb(CHANNEL_DEUX, (uint8_t)(div & 0xFF));
    outb(CHANNEL_DEUX, (uint8_t)((div >> 8) & 0xFF));

    tmp = inb(PIT_IO_PORT);
    if (tmp != (tmp | 3)) {
        outb(PIT_IO_PORT, tmp | 3);
    }
}

void shutup() {

    uint8_t tmp = inb(PIT_IO_PORT) & 0xFC;
    outb(PIT_IO_PORT, tmp);
}

uint32_t read_pit_count() {

    asm volatile("cli");

    outb(MODE_COMMAND_REGISTER, 0b0000000);
    uint32_t count = inb(CHANNEL_ZERO);
    count |= inb(CHANNEL_ZERO) << 8;

    return count;
}

void write_pit_count(uint32_t value) {

    asm volatile("cli");

    outb(CHANNEL_ZERO, (value & 0xFF));
    outb(CHANNEL_ZERO, ((value >> 8) & 0xFF));
}
