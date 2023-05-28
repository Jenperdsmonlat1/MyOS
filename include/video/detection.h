/* Ce script va permettre de détecter si un ordinateur
utilise un écran monochromatique ou en couleur*/

#ifndef _DETECTION_
#define _DETECTION_

#include <stdint.h>

enum video_type {
    VIDEO_TYPE_NONE = 0x00,
    VIDEO_TYPE_COLOUR = 0x20,
    VIDEO_TYPE_MONOCHROME = 0x30
};

uint16_t detect_bios_hardware();
enum video_type get_bios_video_type();

#endif
