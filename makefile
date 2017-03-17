target: procos.img

OBJDIR  = obj
BOOT_OBJS = $(OBJDIR)/bootstart.o $(OBJDIR)/boot.o

CC	= gcc
CXX	= c++
AS	= as
AR	= ar
LD	= ld

OBJCOPY = objcopy

QUME = qemu-system-i386

CFLAGS	:= $(CFLAGS) $(DEFS) $(LABDEFS) -Os -ffreestanding -fomit-frame-pointer -I. -MD -Wall -Wno-format -Wno-unused -Werror -ggdb -nostdinc
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


$(OBJDIR)/bootsector: $(BOOT_OBJS)
	$(call link,-N -e start -Ttext 0x7C00 -o $@.out $^)
	$(OBJCOPY) -S -O binary -j .text $@.out $@

$(OBJDIR)/boot.o: $(OBJDIR)/%.o: boot.c
	mkdir -p $(@D)
	$(call compile,-nostdinc -c $< -o $@)

$(OBJDIR)/bootstart.o: bootstart.S
	$(call compile,-DWEENSYOS_KERNEL -nostdinc -c $< -o $@)


$(OBJDIR)/mkbootdisk: build/mkbootdisk.c
	mkdir -p $(@D)
	$(HOSTCC) -I. -o $(OBJDIR)/mkbootdisk build/mkbootdisk.c


procos.img: $(OBJDIR)/mkbootdisk $(OBJDIR)/bootsector
	$(OBJDIR)/mkbootdisk $(OBJDIR)/bootsector > $@

run: procos.img
	$(QUME) -drive file=procos.img,index=0,media=disk,format=raw

clean:
	rm -rf $(OBJDIR) .gdbinit *.img core *.core
