#include <gdt/gdt.h>
#include <io/serial_port.h>
#include <vga/text_mode/vga.h>
#include <libs/stdio.h>

gdt_entry_t gdt_entries[5];
gdt_ptr_t gdt;

void init_gdt() {

    printf("[+]: Chargement de la GDT.\n");
    gdt.limit = (sizeof(gdt_entry_t) * 3) - 1;
    gdt.base = (uint32_t)&gdt_entries;

    gdt_encode_entry(0, 0, 0, 0, 0);
    gdt_encode_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_encode_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdt_encode_entry(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    gdt_encode_entry(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    load_gdt((uint32_t)&gdt);
    serial_print("[+]: GDT initialized\n", SERIAL_COM1_PORT);

    terminal_setcolor(VGA_GREEN);
    printf("[+]: GDT initialise.\n");
    terminal_setcolor(VGA_WHITE);
}

void gdt_encode_entry(uint8_t number, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt_entries[number].base_low = (base & 0xFFFF);
    gdt_entries[number].base_middle = (base >> 16) & 0xFF;
    gdt_entries[number].base_high = (base >> 24) & 0xFF;

    gdt_entries[number].limit_low = (limit & 0xFFFF);
    //gdt_entries[number].granularity = (limit >> 16) & 0x0F;
    gdt_entries[number].granularity |= gran & 0xF0;
    gdt_entries[number].access = access;
}
