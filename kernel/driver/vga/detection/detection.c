/* Ce script va permettre de détecter si un ordinateur
utilise un écran monochromatique ou en couleur*/

#include <vga/detection/detection.h>

uint16_t detect_bios_hardware() {
    const uint16_t *bda_detect_hardware = (const uint16_t*) 0x410;
    return *bda_detect_hardware;
}

enum video_type get_bios_video_type() {
    return (enum video_type) (detect_bios_hardware() & 0x30);
}