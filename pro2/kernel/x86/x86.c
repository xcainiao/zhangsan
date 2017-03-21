#include "kernel.h"
#include "x86.h"
#include "lib.h"

void console_clear(void)
{
	int i;
    uint16_t *cursorpos;
    uint32_t *intcur;
    intcur = (uint32_t *)0x60000;
    *intcur = (uint32_t)0xB8000;
    cursorpos = (uint16_t *) 0xB8000;
	for (i = 0; i < 80 * 25; i++)
		cursorpos[i] = ' ' | 0x0700;
	outb(0x3D4, 14);
	outb(0x3D5, 0 / 256);
	outb(0x3D4, 15);
	outb(0x3D5, 0 % 256);
}

