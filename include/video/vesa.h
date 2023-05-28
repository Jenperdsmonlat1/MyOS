/* Ce fichier contient les en-têtes permettant
d'utiliser le mode VESA graphique au lieu du mode
VGA plutôt nul. */

#ifndef _VESA_
#define _VESA_

#include <stdint.h>

typedef struct VesaInfosStruct VesaInfosStruct_t;
struct VesaInfosStruct {
	uint8_t Sgnature[4];
	uint16_t VbeVersion;
	uint16_t OEMNamePtr[2];
	uint8_t Capabilities[4];
	uint16_t VideoModeInfos[2];
	uint16_t CountOf64KBlocks;
	uint16_t OEMSoftwareRevision;
	uint32_t OEMVendorNamePtr;
	uint32_t OEMProductNamePtr;
	uint32_t OEMProductRevisionPtr;
	uint8_t Reserved[222];
	uint8_t OEMData[256];
} __attribute__((packed));

typedef struct VesaModeInfosStruct VesaModeInfosStruct_t;
struct VesaModeInfosStruct {
	uint16_t attributes;
	uint8_t window_a;
	uint8_t window_b;
	uint16_t granularity;
	uint16_t window_size;
	uint16_t segment_a;
	uint16_t segment_b;
	uint32_t win_func_ptr;
	uint16_t pitch;
	uint16_t width;
	uint16_t height;
	uint8_t w_char;
	uint8_t y_char;
	uint8_t planes;
	uint8_t bpp;
	uint8_t banks;
	uint8_t memory_model;
	uint8_t bank_size;
	uint8_t images_pages;
	uint8_t reserved0;
	uint8_t red_mask;
	uint8_t red_position;
	uint8_t green_mask;
	uint8_t green_position;
	uint8_t blue_mask;
	uint8_t blue_position;
	uint8_t reserved_mask;
	uint8_t reserved_position;
	uint8_t direct_color_attributes;
	uint32_t framebuffer;
	uint32_t off_screen_mem_off;
	uint16_t off_screen_mem_size;
	uint8_t reserved1[206];
} __attribute__((packed));


extern VesaInfosStruct_t _get_vesa_infos();
extern VesaModeInfosStruct_t _get_vesa_mode_infos();
extern uint16_t _set_vesa_mode();

void init_vesa();
void draw_vesa_pixel(uint32_t *framebuffer, uint16_t pitch, uint8_t bpp, uint32_t pos_x, uint32_t pos_y, uint32_t color);
void draw_vesa_rect(uint32_t pos_x, uint32_t pos_y, uint32_t width, uint32_t height, uint32_t color);
void draw_vesa_line(uint32_t pos_x, uint32_t pos_y, uint32_t width, uint32_t color);

#endif
