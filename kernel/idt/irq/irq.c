#include <idt/irq/irq.h>
#include <idt/idt.h>
#include <io/pic.h>
#include <io/serial_port.h>
#include <libs/stdio.h>
#include <vga/text_mode/vga.h>
#include <keyboard/keyboard.h>
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

void exceptions_handle(registers_t regs) {

    terminal_setcolor(VGA_RED);
    printf("[kernel]: Exception handleled: ");
    printf(exceptions_list_message[regs.interrupt]);
    printf(itoa(regs.interrupt, "", 10));
    terminal_setcolor(VGA_WHITE);

    asm ("cli; hlt");
}

void irq_handler(registers_t regs) {

    serial_print("[-]: IRQ: ", SERIAL_COM1_PORT);
    serial_print(itoa(regs.interrupt, "", 10), SERIAL_COM1_PORT);
    serial_print("\n", SERIAL_COM1_PORT);

    if (interrupt_handler[regs.interrupt] != 0) {
        isr_t handler = interrupt_handler[regs.interrupt - 32];
        handler(regs);
    }

    PIC_endOfInterrupt(regs.interrupt);
}
