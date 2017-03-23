#ifndef WEENSYOS_X86_H
#define WEENSYOS_X86_H
#include "types.h"

/* Pseudo-descriptors used for LGDT, LLDT(not used) and LIDT instructions. */
struct pseudodesc {
    uint16_t pd_lim;        // Limit
    uint32_t pd_base;        // Base address
} __attribute__ ((packed));


#define DECLARE_X86_FUNCTION(function_prototype) \
    static inline function_prototype __attribute__((always_inline))

DECLARE_X86_FUNCTION(uint8_t    inb(int port));
DECLARE_X86_FUNCTION(void       outb(int port, uint8_t data));

DECLARE_X86_FUNCTION(void lidt(struct pseudodesc *pd));
DECLARE_X86_FUNCTION(void sti(void));

static inline uint8_t inb(int port)
{
	uint8_t data;
	asm volatile("inb %w1,%0" : "=a" (data) : "d" (port));
	return data;
}

static inline void outb(int port, uint8_t data) 
{
    asm volatile ("outb %0, %w1" :: "a" (data), "d" (port));
}
/*
static inline void outb(int port, uint8_t data)
{
    asm volatile("outb %0,%w1" : : "a" (data), "d" (port));
}
*/

static inline void lidt(struct pseudodesc *pd) 
{
        asm volatile ("lidt (%0)" :: "r" (pd));
}

static inline void sti(void) 
{
    asm volatile ("sti");
}
#endif
