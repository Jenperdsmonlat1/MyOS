#include <timer/rtc.h>
#include <io/cursor.h>
#include <libs/stdio.h>
#include <video/vga_text.h>

void setup_rtc() {

    printf("[+]: Configuration de RTC.\n");
    
    DISABLE_INTERRUPT();
    terminal_setcolor(VGA_LIGHT_MAGENTA);
    printf("[+]: Desactivation des interruptions.\n");
    outb(RTC_REGISTER_NUMBER, 0x8B);
    outb(RTC_IO_PORT, 0x20);
    ENABLE_INTERRUPT();
    printf("[+]: Reactivation des interruptions.\n");
    
    terminal_setcolor(VGA_GREEN);
    printf("[+]: RTC configure.\n");
    terminal_setcolor(VGA_WHITE);
}

uint8_t get_register_infos(uint8_t reg) {

    outb(RTC_REGISTER_NUMBER, reg);
    return inb(RTC_IO_PORT);
}