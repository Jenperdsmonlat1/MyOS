GLOBAL load_idt
EXTERN interrupt_handlers

%macro no_error_interrupt_handlers 1
GLOBAL interrupt_handlers_%1
interrupt_handlers_%1:
    cli
    push dword 0
    push dword %1
    jmp common_interrupt_handler
%endmacro

%macro error_interrupt_handlers 1
GLOBAL interrupt_handlers_%1
interrupt_handlers_%1:
    cli
    push dword %1
    jmp common_interrupt_handler
%endmacro

no_error_interrupt_handlers 0
no_error_interrupt_handlers 1
no_error_interrupt_handlers 2
no_error_interrupt_handlers 3
no_error_interrupt_handlers 4
no_error_interrupt_handlers 5
no_error_interrupt_handlers 6
no_error_interrupt_handlers 7
error_interrupt_handlers 8
no_error_interrupt_handlers 9
error_interrupt_handlers 10
error_interrupt_handlers 11
error_interrupt_handlers 12
error_interrupt_handlers 13
error_interrupt_handlers 14
no_error_interrupt_handlers 15
no_error_interrupt_handlers 16
error_interrupt_handlers 17
no_error_interrupt_handlers 18
no_error_interrupt_handlers 19
no_error_interrupt_handlers 20
no_error_interrupt_handlers 21
no_error_interrupt_handlers 22
no_error_interrupt_handlers 23
no_error_interrupt_handlers 24
no_error_interrupt_handlers 25
no_error_interrupt_handlers 26
no_error_interrupt_handlers 27
no_error_interrupt_handlers 28
no_error_interrupt_handlers 29
no_error_interrupt_handlers 30
no_error_interrupt_handlers 31

common_interrupt_handler:

    pusha
    call interrupt_handlers
    popa
    add esp, 8
    iret
    ;pusha
    ;mov ax, ds
    ;push eax

    ;mov ax, 0x10
    ;mov ds, ax
    ;mov es, ax
    ;mov fs, ax
    ;mov gs, ax
    ;call interrupt_handlers

    ;pop eax
    ;mov ds, ax
    ;mov es, ax
    ;mov fs, ax
    ;mov gs, ax
    ;popa

    ;add esp, 8
    ;sti
    ;iret

; The assembly function to load IDT
load_idt:

    mov eax, [esp+4]
    lidt [eax]
    ret
