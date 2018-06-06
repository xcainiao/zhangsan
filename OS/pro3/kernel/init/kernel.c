#include "picirq.h"
#include "trap.h"
#include "clock.h"

void start(void)
{
    pic_init();
    idt_init();
    clock_init();
    intr_enable();
    while(1);
}



