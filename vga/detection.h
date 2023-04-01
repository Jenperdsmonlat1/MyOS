/* Ce script va permettre de détecter si un ordinateur
utilise un écran monochromatique ou en couleur*/

#include <stdint.h>

enum video_type {
    VIDEO_TYPE_NONE = 0x00,
    VIDEO_TYPE_COLOUR = 0x20,
    VIDEO_TYPE_MONOCHROME = 0x30
};

uint16_t detect_bios_hardware();
enum video_type get_bios_video_type();
