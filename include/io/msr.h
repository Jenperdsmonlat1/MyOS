/* Ce fichier contient les prototypes 
des fonctions permettant d'accéder au MSR. */

#ifndef _MSR_
#define _MSR_

#include <stdint.h>

extern void getMSR(uint32_t msr, uint32_t *lo, uint32_t *hi);
extern void setMSR(uint32_t msr, uint32_t lo, uint32_t hi);

#endif