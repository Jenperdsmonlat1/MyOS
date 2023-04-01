/* En-tête contenant toutes les structures et fonctions
utiles pour la table de description des interruptions.*/

#include <stdint.h>

typedef struct idt_gate idt_gate_t;
struct idt_gate {
    uint16_t low_offset;
    uint16_t selector;
    uint8_t zero;
    uint8_t attributes;
    uint16_t high_offset;
} __attribute__((packed));

typedef struct idt idt_t;
struct idt {
    uint32_t base;
    uint16_t limite;
} __attribute__((packed));

typedef struct stack_state stack_state_t;
struct stack_state {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, eax, edx, ecx, ebx;
    uint32_t int_number, error_number;
    uint32_t eip, cs, flags, useresp, ss;
} __attribute__((packed));

void interrupt_handlers(stack_state_t stack);
extern void load_idt(uint32_t);
void set_idt_gate(int number, uint32_t handler);
void init_idt();

extern void interrupt_handlers_0();
extern void interrupt_handlers_1();
extern void interrupt_handlers_2();
extern void interrupt_handlers_3();
extern void interrupt_handlers_4();
extern void interrupt_handlers_5();
extern void interrupt_handlers_6();
extern void interrupt_handlers_7();
extern void interrupt_handlers_8();
extern void interrupt_handlers_9();
extern void interrupt_handlers_10();
extern void interrupt_handlers_11();
extern void interrupt_handlers_12();
extern void interrupt_handlers_13();
extern void interrupt_handlers_14();
extern void interrupt_handlers_15();
extern void interrupt_handlers_16();
extern void interrupt_handlers_17();
extern void interrupt_handlers_18();
extern void interrupt_handlers_19();
extern void interrupt_handlers_20();
extern void interrupt_handlers_21();
extern void interrupt_handlers_22();
extern void interrupt_handlers_23();
extern void interrupt_handlers_24();
extern void interrupt_handlers_25();
extern void interrupt_handlers_26();
extern void interrupt_handlers_27();
extern void interrupt_handlers_28();
extern void interrupt_handlers_29();
extern void interrupt_handlers_30();
extern void interrupt_handlers_31();