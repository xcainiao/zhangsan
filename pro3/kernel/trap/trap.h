#include "types.h"

/* Trap Numbers */

/* Processor-defined: */
#define T_DIVIDE                0    // divide error
#define T_DEBUG                    1    // debug exception
#define T_NMI                    2    // non-maskable interrupt
#define T_BRKPT                    3    // breakpoint
#define T_OFLOW                    4    // overflow
#define T_BOUND                    5    // bounds check
#define T_ILLOP                    6    // illegal opcode
#define T_DEVICE                7    // device not available
#define T_DBLFLT                8    // double fault
// #define T_COPROC                9    // reserved (not used since 486)
#define T_TSS                    10    // invalid task switch segment
#define T_SEGNP                    11    // segment not present
#define T_STACK                    12    // stack exception
#define T_GPFLT                    13    // general protection fault
#define T_PGFLT                    14    // page fault
// #define T_RES                15    // reserved
#define T_FPERR                    16    // floating point error
#define T_ALIGN                    17    // aligment check
#define T_MCHK                    18    // machine check
#define T_SIMDERR                19    // SIMD floating point error

#define T_SYSCALL               0x80 // SYSCALL, ONLY FOR THIS PROJ

/* Hardware IRQ numbers. We receive these as (IRQ_OFFSET + IRQ_xx) */
#define IRQ_OFFSET                32    // IRQ 0 corresponds to int IRQ_OFFSET

#define IRQ_TIMER                0
#define IRQ_KBD                    1
#define IRQ_COM1                4
#define IRQ_IDE1                14
#define IRQ_IDE2                15
#define IRQ_ERROR                19
#define IRQ_SPURIOUS                31

/* *
 * These are arbitrarily chosen, but with care not to overlap
 * processor defined exceptions or interrupt vectors.
 * */
#define T_SWITCH_TOU                120    // user/kernel switch
#define T_SWITCH_TOK                121    // user/kernel switch


#define STS_TG32        0xF
#define STS_IG32        0xE

#define SETGATE(gate, istrap, sel, off, dpl) {            \
    (gate).gd_off_15_0 = (uint32_t)(off) & 0xffff;        \
    (gate).gd_ss = (sel);                                \
    (gate).gd_args = 0;                                    \
    (gate).gd_rsv1 = 0;                                    \
    (gate).gd_type = (istrap) ? STS_TG32 : STS_IG32;    \
    (gate).gd_s = 0;                                    \
    (gate).gd_dpl = (dpl);                                \
    (gate).gd_p = 1;                                    \
    (gate).gd_off_31_16 = (uint32_t)(off) >> 16;        \
}

struct gatedesc {
    unsigned gd_off_15_0 : 16;        // low 16 bits of offset in segment
    unsigned gd_ss : 16;            // segment selector
    unsigned gd_args : 5;            // # args, 0 for interrupt/trap gates
    unsigned gd_rsv1 : 3;            // reserved(should be zero I guess)
    unsigned gd_type : 4;            // type(STS_{TG,IG32,TG32})
    unsigned gd_s : 1;                // must be 0 (system)
    unsigned gd_dpl : 2;            // descriptor(meaning new) privilege level
    unsigned gd_p : 1;                // Present
    unsigned gd_off_31_16 : 16;        // high bits of offset in segment
};

struct pushregs {
    uint32_t reg_edi;
    uint32_t reg_esi;
    uint32_t reg_ebp;
    uint32_t reg_oesp;            /* Useless */
    uint32_t reg_ebx;
    uint32_t reg_edx;
    uint32_t reg_ecx;
    uint32_t reg_eax;
};

struct trapframe {
    struct pushregs tf_regs;
    uint16_t tf_gs;
    uint16_t tf_padding0;
    uint16_t tf_fs;
    uint16_t tf_padding1;
    uint16_t tf_es;
    uint16_t tf_padding2;
    uint16_t tf_ds;
    uint16_t tf_padding3;
    uint32_t tf_trapno;
    uint32_t tf_err;
    uintptr_t tf_eip;
    uint16_t tf_cs;
    uint16_t tf_padding4;
    uint32_t tf_eflags;
    uintptr_t tf_esp;
    uint16_t tf_ss;
    uint16_t tf_padding5;
} __attribute__((packed));



void idt_init(void);
void trap(struct trapframe *tf);
