###############################################################################
# INTERRUPT HANDLERS
#
#   This assembly code defines handlers for the traps (software interrupts)
#   understood by procos: that is, its system calls.
#   It also contains some magic code that allows fancy boot loaders to boot
#   procos.
#
#   There is no need to understand this code in detail!
#
###############################################################################

.text

# First, some magic that makes WeensyOS follow the "Multiboot" standard.
# This magic must come first in the binary.


.globl multiboot_start
multiboot_start:
	movl $0x200000, %esp
	pushl $0
	popfl
	call start

