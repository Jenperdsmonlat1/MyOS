/* Ce fichier contient quelques fonctions pratiques
permettant d'afficher les informations du processeur.*/

#ifndef _CPU_INFOS_
#define _CPU_INFOS_

#include <stdint.h>

typedef struct regs regs_t;
struct regs {
    int8_t *eax, *ebx, *ecx, *edx;
};

void print_cpu_brand();
void print_cpu_vendor();

#endif