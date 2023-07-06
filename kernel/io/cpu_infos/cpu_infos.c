#include <cpu_infos.h>
#include <stdint.h>
#include <cpuid.h>
#include <libs/stdio.h>

regs_t registers;

static void get_cpu_brand(uint32_t eax) {

    registers.eax = eax;
    __cpuid(0, registers.eax, registers.ebx, registers.ecx, registers.edx);

}

static void get_cpu_vendor() {

    registers.eax = 0;
    __cpuid(0, registers.eax, registers.ebx, registers.ecx, registers.edx);
}

void print_cpu_brand() {

    printf("[-]: CPU brand: ");
    get_cpu_brand(0x80000002);
    /*printf(registers.eax);
    printf(registers.ebx);
    printf(registers.ecx);
    printf(registers.edx);*/

    get_cpu_brand(0x80000003);
    /*printf(registers.eax);
    printf(registers.ebx);
    printf(registers.ecx);
    printf(registers.edx);*/

    get_cpu_brand(0x80000004);
    /*printf(registers.eax);
    printf(registers.ebx);
    printf(registers.ecx);
    printf(registers.edx);*/
}

void print_cpu_vendor() {

    printf("[+]: CPU Vendor: ");
    get_cpu_vendor();
}