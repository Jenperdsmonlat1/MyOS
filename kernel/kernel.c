#include "../io/stdio/stdio.h"
#include "../vga/vga.h"
#include "../dt/gdt/gdt.h"
#include "../dt/idt/idt.h"
#include "../io/pic/pic.h"

void init_descriptor_tables();

void kernel_main() {

    init_descriptor_tables();
    terminal_init(VGA_GREEN, VGA_MAGENTA);
    print("Coucou le monde.");
    asm volatile("int $0x3");
}

void init_descriptor_tables() {
    init_gdt();
    init_idt();
    setupPIC();
}
