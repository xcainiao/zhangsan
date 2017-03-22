#include <x86.h>
#define LPTPORT         0x378

static void delay(void) 
{
    inb(0x84);
    inb(0x84);
    inb(0x84);
    inb(0x84);
}

void putc(int c) 
{
    int i;
    for (i = 0; !(inb(LPTPORT + 1) & 0x80) && i < 12800; i ++) {
        delay();
    }   
    outb(LPTPORT + 0, c); 
    outb(LPTPORT + 2, 0x08 | 0x04 | 0x01);
    outb(LPTPORT + 2, 0x08);
}
void puts(char *s)
{
    while(*s)
    {
        putc(*s);
        *(s++);
    }
}
