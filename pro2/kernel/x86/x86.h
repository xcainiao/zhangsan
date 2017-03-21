#ifndef WEENSYOS_X86_H
#define WEENSYOS_X86_H
#include "types.h"


#define DECLARE_X86_FUNCTION(function_prototype) \
    static inline function_prototype __attribute__((always_inline))

DECLARE_X86_FUNCTION(uint8_t    inb(int port));
DECLARE_X86_FUNCTION(void       outb(int port, uint8_t data));

static inline uint8_t inb(int port)
{
	uint8_t data;
	asm volatile("inb %w1,%0" : "=a" (data) : "d" (port));
	return data;
}


static inline void outb(int port, uint8_t data)
{
    asm volatile("outb %0,%w1" : : "a" (data), "d" (port));
}
#endif
