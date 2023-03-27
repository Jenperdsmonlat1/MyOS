MBALIGN  equ  1 << 0            ; align loaded modules on page boundaries
MEMINFO  equ  1 << 1            ; provide memory map
MBFLAGS  equ  MBALIGN | MEMINFO ; this is the Multiboot 'flag' field
MAGIC    equ  0x1BADB002        ; 'magic number' lets bootloader find the header
CHECKSUM equ -(MAGIC + MBFLAGS) 

SECTION .multiboot
align 4 ; Alignement des valeurs
    dd MAGIC ; Nombre magique permettant d'indiquer au bootloader qu'il s'agit d'un kernel
    dd MBALIGN | MEMINFO ; Drapeau
    dd CHECKSUM ; Checksum

SECTION .bss
align 16
stack_bottom: RESB 16384
stack_top:


SECTION .text
global _start:function (_start.end - _start)
extern kernel_main

_start:

    mov esp, stack_top ; initialiser la pile avec 16 kilo octect.
    call kernel_main ; appeler la fonction kernel_main écrite en C
    cli

.hang: hlt
    jmp .hang
.end: