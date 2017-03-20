#include "kernel.h"
#include "x86.h"
#include "lib.h"

void start(void)
{
	console_clear();

	cursorpos = console_printf(cursorpos, 0x0700, "hello world");
    
    while(1);
}



