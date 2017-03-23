target: procos.img


CC	= gcc
CXX	= c++
AS	= as
AR	= ar
LD	= ld

OBJCOPY = objcopy
OBJDUMP = objdump
 
QUME = qemu-system-i386

CFLAGS	:= -O1 -ffreestanding -fomit-frame-pointer -Ikernel/def/ -Ikernel/init/ -Ikernel/libs/ -Ikernel/x86/ -Ikernel/trap/ -Ikernel/driver/ -MD -Wall -Wno-format -Wno-unused -Werror -ggdb -nostdinc 
# Include -fno-stack-protector if the option exists.
CFLAGS	+= $(shell $(CC) -fno-stack-protector -E -x c /dev/null >/dev/null 2>&1 && echo -fno-stack-protector)
# Include -m32 if the option exists (x86_64).
CFLAGS	+= $(shell $(CC) -m32 -E -x c /dev/null >/dev/null 2>&1 && echo -m32)

LDFLAGS := $(LDFLAGS)
# Link for 32-bit targets if on x86_64.
LDFLAGS += $(shell $(LD) -m elf_i386 --help >/dev/null 2>&1 && echo -m elf_i386)

compile = $(CC) $(CFLAGS)  $(1)
link = $(LD) $(LDFLAGS) $(1)

HOSTCC = gcc


OBJDIR  = obj
KERNEL = kernel


BOOT_OBJS = $(OBJDIR)/bootstart.o $(OBJDIR)/boot.o 
KERNEL_OBJS = $(OBJDIR)/kernel.o \
			  $(OBJDIR)/stdio.o \
			  $(OBJDIR)/picirq.o \
			  $(OBJDIR)/trap.o \
			  $(OBJDIR)/clock.o \
			  $(OBJDIR)/vectors.o \
			  $(OBJDIR)/trapentry.o 

#kernel ----------------------------------------------------------
$(OBJDIR)/lib.o: $(KERNEL)/lib/lib.c 
	$(call compile, -c $< -o $@)

$(OBJDIR)/x86.o: $(KERNEL)/x86/x86.c 
	$(call compile, -c $< -o $@)

$(OBJDIR)/kernel.o: $(KERNEL)/init/kernel.c 
	$(call compile, -c $< -o $@)

$(OBJDIR)/stdio.o: $(KERNEL)/libs/stdio.c 
	$(call compile, -c $< -o $@)

$(OBJDIR)/picirq.o: $(KERNEL)/driver/picirq.c 
	$(call compile, -c $< -o $@)

$(OBJDIR)/trap.o: $(KERNEL)/trap/trap.c 
	$(call compile, -c $< -o $@)

$(OBJDIR)/clock.o: $(KERNEL)/driver/clock.c 
	$(call compile, -c $< -o $@)

$(OBJDIR)/vectors.o: $(KERNEL)/trap/vectors.S 
	$(call compile, -c $< -o $@)

$(OBJDIR)/trapentry.o: $(KERNEL)/trap/trapentry.S 
	$(call compile, -c $< -o $@)

$(OBJDIR)/kernel: $(KERNEL_OBJS) $(KERNEL_LINKER_FILES)
	$(call link,-e start -Ttext 0x100000 -o $@ $(KERNEL_OBJS) )


#bootload ----------------------------------------------------------
$(OBJDIR)/bootsector: $(BOOT_OBJS)
	$(call link,-N -e start -Ttext 0x7C00 -o $@.out $^,LINK)
	$(OBJCOPY) -S -O binary -j .text $@.out $@

$(OBJDIR)/boot.o:  boot/boot.c
	mkdir -p $(@D)
	$(call compile,-nostdinc -c $< -o $@)

$(OBJDIR)/bootstart.o: boot/bootstart.S
	$(call compile,-DWEENSYOS_KERNEL -nostdinc -c $< -o $@)

$(OBJDIR)/mkbootdisk: build/mkbootdisk.c
	mkdir -p $(@D)
	$(HOSTCC) -I. -o $(OBJDIR)/mkbootdisk build/mkbootdisk.c

procos.img: $(OBJDIR)/mkbootdisk $(OBJDIR)/bootsector $(OBJDIR)/kernel
	$(OBJDIR)/mkbootdisk $(OBJDIR)/bootsector $(OBJDIR)/kernel > $@

run: procos.img
	$(QUME) -parallel stdio -drive file=procos.img,index=0,media=disk,format=raw

run-gdb: procos.img
	$(QUME) -net none -parallel file:log.txt -k en-us  -S -gdb tcp::20000 -drive file=procos.img,index=0,media=disk,format=raw 
clean:
	rm -rf $(OBJDIR) *.img *.core
