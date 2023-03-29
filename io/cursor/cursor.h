#ifndef INCLUDE_CURSOR
#define INCLUDE_CURSOR

#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5
#define FB_HIGH_BYTE 14
#define FB_LOW_BYTE 15

void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);

#endif