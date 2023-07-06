#include <libs/stdio.h>
#include <video/vga_text.h>
#include <video/vga_graphics.h>
#include <idt/idt.h>
#include <gdt/gdt.h>
#include <keyboard/keyboard.h>
#include <timer/pit.h>
#include <timer/rtc.h>
#include <stdint.h>
#include <multiboot.h>
#include <sound/sound_blaster.h>
#include <pci/pci.h>


static char *days[] = {
    "Dimanche",
    "Lundi",
    "Mardi",
    "Mercredi",
    "Jeudi",
    "Vendredi",
    "Samedi",
};

static char *months[] = {
    "Janvier",
    "Fevrier",
    "Mars",
    "Avril",
    "Mai",
    "Juin",
    "Juillet",
    "Aout",
    "Septembre",
    "Octobre",
    "Novembre",
    "Decembre"
};

static inline void print_date() {

    char day[3], year[5];
    uint16_t years, day_, day_get, years_get;
    
    day_ = get_register_infos(DAY_OF_MONTH);
    day_get = (day_ & 0x0F) + ((day_ / 16) * 10);
    itoa(day_get, day, 10);

    years = get_register_infos(YEAR);
    years_get = 2000 + (years & 0x0F) + ((years / 16) * 10);

    itoa(years_get, year, 10);
    
    printf("[kernel]: Date du jour: ");
    printf(days[get_register_infos(WEEKDAY) - 1]);
    printf(" ");
    printf(day);
    printf(" ");
    printf(months[get_register_infos(MONTHS) - 1]);
    printf(" ");
    printf(year);
    printf("\n");
}

void kernel_main(multiboot_info_t *multiboot_struct, uint32_t magic_number) {

    terminal_init(VGA_WHITE, VGA_BLACK);

    if (magic_number == 0x2BADB002) {
        terminal_setcolor(VGA_LIGHT_BLUE);
        printf("[+]: Nombre magique confirme.\n");
        terminal_setcolor(VGA_WHITE);
    } else {
        terminal_setcolor(VGA_LIGHT_RED);
        printf("[+]: Nombre magique incorrect.\n");
        terminal_setcolor(VGA_WHITE);
    }

    init_gdt();
    init_idt();
    init_pit(50);
    init_keyboard();
    initPCI();
    setup_rtc();
    init_sound_blaster();
    
    printf("[kernel]: Welcome.\n");
    print_date();

    for (;;) {
        asm ("hlt");
    }
}
