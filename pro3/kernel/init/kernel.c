#include "stdio.h"
#include "picirq.h"
#include "trap.h"
#include "clock.h"

void start(void)
{
    pic_init();
    idt_init();
    clock_init();
    intr_enable();
    puts("aaaaa\n");
    while(1);
}



