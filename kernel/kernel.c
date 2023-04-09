#include "../io/stdio/stdio.h"
#include "../driver/vga/vga.h"
#include "../idt/idt.h"
#include "../gdt/gdt.h"
#include "../io/pic/pic.h"
#include <stdbool.h>


void kernel_main() {

    terminal_init(VGA_LIGHT_MAGENTA, VGA_BLUE);
    
    print("[+] Initialisation de GDT.\n");
    init_gdt();
    print("[+] Initialisation de IDT.\n");
    init_idt();
    print("[+] Configuration du PIC.\n");
    setupPIC();

    print("Coucou le monde.\n");
    asm volatile("int $0x3");
}
