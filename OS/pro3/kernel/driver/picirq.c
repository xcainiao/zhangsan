#include "types.h"
#include "x86.h"
#include "picirq.h"

#define IO_PIC1             0x20    // Master (IRQs 0-7)
#define IO_PIC2             0xA0    // Slave (IRQs 8-15)

#define IRQ_SLAVE           2       // IRQ at which slave connects to master

static uint16_t irq_mask = 0xFFFF & ~(1 << IRQ_SLAVE);
static bool did_init = 0;

static void pic_setmask(uint16_t mask) {
    irq_mask = mask;
    if (did_init) {
        outb(IO_PIC1 + 1, mask);
        outb(IO_PIC2 + 1, mask >> 8);
    }
}

void
pic_enable(unsigned int irq) {
    pic_setmask(irq_mask & ~(1 << irq));
}

void pic_init(void) {
    did_init = 1;
    outb(IO_PIC1 + 1, 0xFF);
    outb(IO_PIC2 + 1, 0xFF);
    outb(IO_PIC1, 0x11);
    outb(IO_PIC1 + 1, IRQ_OFFSET);
    outb(IO_PIC1 + 1, 1 << IRQ_SLAVE);
    outb(IO_PIC1 + 1, 0x3);
    outb(IO_PIC2, 0x11);    // ICW1
    outb(IO_PIC2 + 1, IRQ_OFFSET + 8);  // ICW2
    outb(IO_PIC2 + 1, IRQ_SLAVE);       // ICW3
    outb(IO_PIC2 + 1, 0x3);             // ICW4
    outb(IO_PIC1, 0x68);    // clear specific mask
    outb(IO_PIC1, 0x0a);    // read IRR by default
    outb(IO_PIC2, 0x68);    // OCW3
    outb(IO_PIC2, 0x0a);    // OCW3
    if (irq_mask != 0xFFFF) {
        pic_setmask(irq_mask);
    }
}
void intr_enable(void) 
{
    sti();
}
