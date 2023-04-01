#include <stdint.h>
#include "idt.h"
#include "../../io/pic/pic.h"
#include "../../io/stdio/stdio.h"
#include "../../io/serial_port/serial_port.h"

idt_gate_t idt_gate[256];
idt_t idt;


void set_idt_gate(int number, uint32_t handler) {
    idt_gate[number].low_offset = handler & 0xFFFF;
    idt_gate[number].selector = 0x08;
    idt_gate[number].zero = 0;
    idt_gate[number].attributes = 0x8E;
    idt_gate[number].high_offset = (handler >> 16) & 0xFFFF;
}

void init_idt() {
    idt.base = (uint32_t)&idt_gate;
    idt.limite = 256 * sizeof(idt_gate_t) - 1;

    set_idt_gate(0, (uint32_t)interrupt_handlers_0);
    set_idt_gate(1, (uint32_t)interrupt_handlers_1);
    set_idt_gate(2, (uint32_t)interrupt_handlers_2);
    set_idt_gate(3, (uint32_t)interrupt_handlers_3);
    set_idt_gate(4, (uint32_t)interrupt_handlers_4);
    set_idt_gate(5, (uint32_t)interrupt_handlers_5);
    set_idt_gate(6, (uint32_t)interrupt_handlers_6);
    set_idt_gate(7, (uint32_t)interrupt_handlers_7);
    set_idt_gate(8, (uint32_t)interrupt_handlers_8);
    set_idt_gate(9, (uint32_t)interrupt_handlers_9);
    set_idt_gate(10, (uint32_t)interrupt_handlers_10);
    set_idt_gate(11, (uint32_t)interrupt_handlers_11);
    set_idt_gate(12, (uint32_t)interrupt_handlers_12);
    set_idt_gate(13, (uint32_t)interrupt_handlers_13);
    set_idt_gate(14, (uint32_t)interrupt_handlers_14);
    set_idt_gate(15, (uint32_t)interrupt_handlers_15);
    set_idt_gate(16, (uint32_t)interrupt_handlers_16);
    set_idt_gate(17, (uint32_t)interrupt_handlers_17);
    set_idt_gate(18, (uint32_t)interrupt_handlers_18);
    set_idt_gate(19, (uint32_t)interrupt_handlers_19);
    set_idt_gate(20, (uint32_t)interrupt_handlers_20);
    set_idt_gate(21, (uint32_t)interrupt_handlers_21);
    set_idt_gate(22, (uint32_t)interrupt_handlers_22);
    set_idt_gate(23, (uint32_t)interrupt_handlers_23);
    set_idt_gate(24, (uint32_t)interrupt_handlers_24);
    set_idt_gate(25, (uint32_t)interrupt_handlers_25);
    set_idt_gate(26, (uint32_t)interrupt_handlers_26);
    set_idt_gate(27, (uint32_t)interrupt_handlers_27);
    set_idt_gate(28, (uint32_t)interrupt_handlers_28);
    set_idt_gate(29, (uint32_t)interrupt_handlers_29);
    set_idt_gate(30, (uint32_t)interrupt_handlers_30);
    set_idt_gate(31, (uint32_t)interrupt_handlers_31);

    load_idt((uint32_t)&idt);
    serial_print("[+]:IDT initialized\n", SERIAL_COM1_PORT);
}

void interrupt_handlers(stack_state_t stack) {
    
    print("Interrupt received: ");
    print((char *)&stack.int_number);
    PIC_endOfInterrupt(stack.int_number);
}
