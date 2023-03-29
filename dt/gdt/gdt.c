#include "gdt.h"
#include <stdint.h>

uint8_t load_gdt(struct gdt *gdt) {

    asm volatile("mov %0, %eax; \
                  lgdt [eax];"
                  : "d"(gdt));

    return 0;
}