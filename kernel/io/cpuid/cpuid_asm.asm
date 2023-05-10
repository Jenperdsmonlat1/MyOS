; Ce fichier contient une fonction écrite
; en assembleur contenant des informations sur le processeur.

extern get_cpu_infos

_cpuid:

    xor eax, eax
    xor ebx, ebx
    xor ecx, ecx
    xor edx, edx

    mov eax, 1
    cpuid

    push eax
    push ebx
    push ecx
    push edx
    call get_cpu_infos

    pop edx
    pop ecx
    pop ebx
    pop eax
    ret
