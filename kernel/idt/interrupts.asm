global isr_handlers_table
global irq_handle_table
global load_idt
extern exceptions_handle
extern irq_handler

load_idt:

    mov eax, [esp+4]
    lidt [eax]
    ret

%macro isr_handle_error 1
isr_handle_%+%1:
    push dword %1
    
    pusha
    push eax
    call exceptions_handle

    pop eax

    popa
    add esp, 8
    iret
%endmacro

%macro isr_handle_no_error 1
isr_handle_%+%1:
    push dword 0
    push dword %1

    pusha
    push eax
    call exceptions_handle

    pop eax

    popa
    add esp, 8
    iret
%endmacro

%macro irq_handle 1
irq_handle_%+%1:
    cli
    push dword 0
    push dword %1+32
    pusha
    
    push eax
    call irq_handler
    
    pop eax
    popa
    add esp, 8
    sti
    iret
%endmacro

isr_handle_no_error 0
isr_handle_no_error 1
isr_handle_no_error 2
isr_handle_no_error 3
isr_handle_no_error 4
isr_handle_no_error 5
isr_handle_no_error 6
isr_handle_no_error 7
isr_handle_error 8
isr_handle_no_error 9
isr_handle_error 10
isr_handle_error 11
isr_handle_error 12
isr_handle_error 13
isr_handle_error 14
isr_handle_no_error 15
isr_handle_no_error 16
isr_handle_error 17
isr_handle_no_error 18
isr_handle_no_error 19
isr_handle_no_error 20
isr_handle_no_error 21
isr_handle_no_error 22
isr_handle_no_error 23
isr_handle_no_error 24
isr_handle_no_error 25
isr_handle_no_error 26
isr_handle_no_error 27
isr_handle_no_error 28
isr_handle_no_error 29
isr_handle_no_error 30
isr_handle_no_error 31

irq_handle 0
irq_handle 1
irq_handle 2
irq_handle 3
irq_handle 4
irq_handle 5
irq_handle 6
irq_handle 7
irq_handle 8
irq_handle 9
irq_handle 10
irq_handle 11
irq_handle 12
irq_handle 13
irq_handle 14
irq_handle 15

isr_handlers_table:
%assign i 0
%rep    32
    dd isr_handle_%+i
%assign i i+1
%endrep

irq_handle_table:
%assign i 0
%rep 15
    dd irq_handle_%+i
%assign i i+1
%endrep