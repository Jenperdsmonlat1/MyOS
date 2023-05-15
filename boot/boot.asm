MBALIGN  equ  1 << 0
MEMINFO  equ  1 << 1
MBFLAGS  equ  MBALIGN | MEMINFO
MAGIC    equ  0x1BADB002
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
    push eax ; placer la structure multiboot_info_t sur la pile
    push ebx ; placer le nombre magic sur la pile
    call kernel_main ; appeler la fonction kernel_main (eax, et ebx) sont maintenant les arguments de cette fonction
    ; cli: On désactive les interruptions.

.hang: hlt
    jmp .hang
.end:
