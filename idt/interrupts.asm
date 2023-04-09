global isr_handlers_table
extern exceptions_handle

%macro isr_handle_error 1
isr_handle_%+%1:
    ;pusha
    ;push dword %1
    call exceptions_handle
    ;popa
    ;add esp, 8
    iret
%endmacro

%macro isr_handle_no_error 1
isr_handle_%+%1:
    ;pusha
    ;push dword 0
    ;push dword %1
    call exceptions_handle
    ;popa
    ;add esp, 8
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


isr_handlers_table:
%assign i 0
%rep    32
    dd isr_handle_%+i
%assign i i+1
%endrep
