/* Contient tous le prototypes de fonctions
ainsi que les macros nécéssaires à l'utilisation du PIC.*/

#ifndef _PIC_
#define _PIC_

#include <stdint.h>

#define PIC1 0x20
#define PIC2 0xA0
#define PIC_COMMAND(base) (base)
#define PIC_DATA(base) (base+1)
#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28

#define PIC_EOI 0x20
#define ICW1_ICW4 0x01
#define ICW1_SINGLE 0x02
#define ICW1_INTERVAL4 0x04
#define ICW1_LEVEL 0x08
#define ICW1_INIT 0x10

#define ICW4_8086 0x01
#define ICW4_AUTO 0x02
#define ICW4_BUF_SLAVE 0x08
#define ICW4_BUF_MASTER 0x0C
#define ICW4_SFNM 0x10

void setupPIC();
void PIC_endOfInterrupt(uint8_t irq);

#endif
