#include "gdt.h"
#include "../../io/serial_port/serial_port.h"

gdt_entry_t gdt_entry[5];
gdt_ptr_t gdt;

void init_gdt() {
    gdt.limit = (sizeof(gdt_entry) * 5) - 1;
    gdt.base = (uint32_t)&gdt_entry;

    gdt_encode_entry(0, 0, 0, 0, 0);
    gdt_encode_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_encode_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdt_encode_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    gdt_encode_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    load_gdt((uint32_t)&gdt);
    serial_print("[+]:GDT initialized\n", SERIAL_COM1_PORT);
}

void gdt_encode_entry(uint8_t number, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt_entry[number].base_low = (base & 0xFFFF);
    gdt_entry[number].base_middle = (base >> 16) & 0xFF;
    gdt_entry[number].base_high = (base >> 24) & 0xFF;

    gdt_entry[number].limit_low = (limit & 0xFFFF);
    gdt_entry[number].granularity = (limit >> 16) & 0x0F;
    gdt_entry[number].granularity |= granularity & 0xF0;
    gdt_entry[number].access = access;
}
