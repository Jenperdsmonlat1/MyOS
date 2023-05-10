#include <stdint.h>
#include <io/cpuid.h>

cpuid_t cpu_struct;

cpuid_t get_cpu_infos(cpuid_t cpu_struct) {
    return cpu_struct;
}

uint32_t get_processor_type() {
    
    cpu_struct = get_cpu_infos(cpu_struct);
    return (cpu_struct.eax >> 12) & 0x3;
}

uint32_t get_cpu_model() {

    cpu_struct = get_cpu_infos(cpu_struct);
    return (cpu_struct.eax >> 4) & 0xF;
}

uint32_t get_cpu_family() {

    cpu_struct = get_cpu_infos(cpu_struct);
    return (cpu_struct.eax >> 8) & 0xF;
}
