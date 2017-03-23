#include "types.h"
#include "trap.h"
#include "x86.h"
#include "stdio.h"
#include "clock.h"

#define TICK_NUM 100


#define SEG_KTEXT    1
#define GD_KTEXT    ((SEG_KTEXT) << 3)
#define DPL_KERNEL    (0)
#define DPL_USER    (3)


/* *
 * Interrupt descriptor table:
 *
 * Must be built at run time because shifted function addresses can't
 * be represented in relocation records.
 * */
static struct gatedesc idt[256] = {{0}};

static struct pseudodesc idt_pd = {
    sizeof(idt) - 1, (uintptr_t)idt
};

/* idt_init - initialize IDT to each of the entry points in kern/trap/vectors.S */
void idt_init(void) {
     /* LAB1 YOUR CODE : STEP 2 */
     /* (1) Where are the entry addrs of each Interrupt Service Routine (ISR)?
      *     All ISR's entry addrs are stored in __vectors. where is uintptr_t __vectors[] ?
      *     __vectors[] is in kern/trap/vector.S which is produced by tools/vector.c
      *     (try "make" command in lab1, then you will find vector.S in kern/trap DIR)
      *     You can use  "extern uintptr_t __vectors[];" to define this extern variable which will be used later.
      * (2) Now you should setup the entries of ISR in Interrupt Description Table (IDT).
      *     Can you see idt[256] in this file? Yes, it's IDT! you can use SETGATE macro to setup each item of IDT
      * (3) After setup the contents of IDT, you will let CPU know where is the IDT by using 'lidt' instruction.
      *     You don't know the meaning of this instruction? just google it! and check the libs/x86.h to know more.
      *     Notice: the argument of lidt is idt_pd. try to find it!
      */
    extern uintptr_t __vectors[];
    int i;
    for (i = 0; i < sizeof(idt) / sizeof(struct gatedesc); i ++) {
        SETGATE(idt[i], 0, GD_KTEXT, __vectors[i], DPL_KERNEL);
    }
	// set for switch from user to kernel
    SETGATE(idt[T_SWITCH_TOK], 0, GD_KTEXT, __vectors[T_SWITCH_TOK], DPL_USER);
	// load the IDT
    lidt(&idt_pd);
}

static void trap_dispatch(struct trapframe *tf) 
{
    switch (tf->tf_trapno) 
    {
        case IRQ_OFFSET + IRQ_TIMER:
            ticks ++;
            if (ticks % 100 == 0)
            {
                putc('a');
                ticks = 0;
            }
            break;
        default:
            putc('.');
    }
}

void trap(struct trapframe *tf) 
{
    trap_dispatch(tf);
}

