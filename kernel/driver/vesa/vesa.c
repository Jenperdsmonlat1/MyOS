#include <stdint.h>
#include <video/vesa.h>
#include <io/serial_port.h>

VesaInfosStruct_t vesa_infos;
VesaModeInfosStruct_t vesa_mode_infos;

void init_vesa() {

    vesa_infos = _get_vesa_infos();
    vesa_mode_infos = _get_vesa_mode_infos();

    uint16_t state = _set_vesa_mode();
    if (state == 0x004F) {
        serial_print("[+]: Le mode VESA est active.\n", SERIAL_COM1_PORT);
    } else {
        serial_print("[+]: Impossible d'activer le mode VESA.\n", SERIAL_COM1_PORT);
    }
}

void draw_vesa_pixel(uint32_t *framebuffer, uint16_t pitch, uint8_t bpp, uint32_t pos_x, uint32_t pos_y, uint32_t color) {

	uint32_t pixel = pos_x * bpp + pos_y * pitch;
    framebuffer[pixel] = color & 0xFF;
    framebuffer[pixel + 1] = (color >> 8) & 0xFF;
    framebuffer[pixel + 2] = (color >> 16) & 0xFF;
}

void draw_vesa_rect(uint32_t pos_x, uint32_t pos_y, uint32_t width, uint32_t height, uint32_t color) {

    for (uint32_t i = pos_x; i < width+pos_x; i++) {
        for (uint32_t j = pos_y; i < height+pos_y; j++) {
            draw_vesa_pixel(vesa_mode_infos.framebuffer, vesa_mode_infos.pitch, vesa_mode_infos.bpp, i, j, color);
        }
    }
}

void draw_vesa_line(uint32_t pos_x, uint32_t pos_y, uint32_t width, uint32_t color) {

    for (uint32_t i = pos_x; i < width+pos_x; i++) {
        draw_vesa_pixel(vesa_mode_infos.framebuffer, vesa_mode_infos.pitch, vesa_mode_infos.bpp, i, pos_y, color);
    }
}
