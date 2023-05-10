/* Ce fichier contient quelques fonctions permettant
d'obtenir des informations sur le processeur.*/

#ifndef _CPUID_
#define _CPUID_

#include <stdint.h>

typedef struct cpuid cpuid_t;
struct cpuid {
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
};

extern void _cpuid();
cpuid_t get_cpu_infos(cpuid_t cpu_struct);
uint32_t get_processor_type();
uint32_t get_cpu_model();
uint32_t get_cpu_family();

#endif
