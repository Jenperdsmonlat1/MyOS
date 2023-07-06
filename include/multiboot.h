/* Ce fichier contient l'en-tête multiboot permettant 
d'obtenir toutes les informations au démarrage de l'OS.*/


#ifndef _MULTIBOOT_
#define _MULTIBOOT_

#include <stdint.h>

typedef struct multiboot_header multiboot_header_t;
struct multiboot_header {
    uint32_t magic;
    uint32_t flags;
    uint32_t checksum;
    uint32_t header_address;
    uint32_t load_address;
    uint32_t load_end_address;
    uint32_t bss_end_address;
    uint32_t entry_address;
    uint32_t mode_type;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
};

typedef struct multiboot_aout_symbol_table multiboot_aout_symbol_table_t;
struct multiboot_aout_symbol_table {
    uint32_t tabsize;
    uint32_t strsize;
    uint32_t addr;
    uint32_t reserved;
};

typedef struct multiboot_elf_section_header_table multiboot_elf_section_header_table_t;
struct multiboot_elf_section_header_table {
    uint32_t num;
    uint32_t size;
    uint32_t addr;
    uint32_t shndx;
};

typedef struct multiboot_info multiboot_info_t;
struct multiboot_info {
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_device;
    uint32_t cmdline;
    uint32_t mods_count;
    uint32_t mods_addr;

    union {
        multiboot_aout_symbol_table_t aout_sym;
        multiboot_elf_section_header_table_t elf_sec;
    } u;

    uint32_t mmap_length;
    uint32_t mmap_addr;
    uint32_t drives_length;
    uint32_t drives_addr;
    uint32_t config_table;
    uint32_t boot_loader_name;
    uint32_t apm_table;
    uint32_t vbe_control_info;
    uint32_t vbe_mode_info;
    uint32_t vbe_mode;
    uint32_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;
    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t framebuffer_bpp;
    uint8_t framebuffer_type;

    union {
        struct {
            uint32_t framebuffer_palette_addr;
            uint16_t framebuffer_palette_num_colors;
        };

        struct {
            uint8_t framebuffer_red_field_position;
            uint8_t framebuffer_red_mask_size;
            uint8_t framebuffer_green_field_position;
            uint8_t framebuffer_green_mask_size;
            uint8_t framebuffer_blue_field_position;
            uint8_t framebuffer_blue_mask_size;
        };
    };
};

typedef struct multiboot_color multiboot_color_t;
struct multiboot_color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

typedef struct multiboot_mmap_entry multiboot_memory_map_t;
struct multiboot_mmap_entry {
    uint32_t size;
    uint64_t addr;
    uint64_t len;
    uint32_t type;
} __attribute__((packed));

typedef struct multiboot_mod_list multiboot_module_t;
struct multiboot_mod_list {
    uint32_t mod_start;
    uint32_t mod_end;
    uint32_t cmdline;
    uint32_t pad;
};

typedef struct multiboot_apm_info multiboot_apm_info_t;
struct multiboot_apm_info {
    uint16_t version;
    uint16_t cseg;
    uint32_t offset;
    uint16_t cseg_16;
    uint16_t dseg;
    uint16_t flags;
    uint16_t cseg_len;
    uint16_t cseg_16_len;
    uint16_t dseg_len;
};

#endif
