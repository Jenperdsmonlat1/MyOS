#include <idt/irq/irq.h>
#include <idt/idt.h>
#include <io/pic.h>
#include <io/serial_port.h>
#include <libs/stdio.h>
#include <video/vga_text.h>
#include <keyboard/keyboard.h>
#include <stdint.h>
#include <timer/pit.h>

isr_t interrupt_handler[16];

char *exceptions_list_message[] = {
    "Division by zero exception\n",
    "Debug exception\n",
    "Non maskable interrupt\n",
    "Breakpoint exception\n",
    "Into detected overflow\n",
    "Out of bound exception\n",
    "Invalid opcode exception\n",
    "No coprocessor exception\n",
    "Double fault\n",
    "Coprocessor segment overrun\n",
    "Bad TSS\n",
    "Segment not present\n",
    "Stack fault\n",
    "General protection fault\n",
    "Page fault\n",
    "Unknown interrupt exception\n",
    "Coprocessor fault\n",
    "Alignment check exception\n",
    "Machine check exception\n",
    "Reserved\n",
    "Reserved\n",
    "Reserved\n",
    "Reserved\n",
    "Reserved\n",
    "Reserved\n",
    "Reserved\n",
    "Reserved\n",
    "Reserved\n",
    "Reserved\n",
    "Reserved\n",
    "Reserved\n",
    "Reserved\n"
};

void register_interrupt_handler(uint8_t number, isr_t handler) {
    interrupt_handler[number] = handler;
}

void exceptions_handle(registers_t regs) {

    terminal_setcolor(VGA_RED);
    printf("[kernel]: Exception handleled: ");
    printf(exceptions_list_message[regs.interrupt]);
    terminal_setcolor(VGA_WHITE);

    asm volatile("cli; hlt");
}

void irq_handler(registers_t regs) {

    if (interrupt_handler[regs.interrupt - 32] != 0) {
        isr_t handler = interrupt_handler[regs.interrupt - 32];
        handler(regs);
    }

    PIC_endOfInterrupt(regs);
}
