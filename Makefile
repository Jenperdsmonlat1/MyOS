GCCPARAMS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
GCCLINKING = -ffreestanding -O2 -nostdlib -lgcc
NASMPARAMS = -felf32

OBJFILES = obj/kernel.o \
		   obj/vga.o \
		   obj/boot.o \
		   obj/keyboard.o

LINKFILE = linker.ld

%.o: boot/%.asm
	nasm $(NASMPARAMS) -o $@ $<
	mv $@ obj/$@

%.o:kernel/%.c
	i686-elf-gcc -c $< -o $@ $(GCCPARAMS)
	mv $@ obj/$@

%.o: vga/%.c
	i686-elf-gcc -c $< -o $@ $(GCCPARAMS)
	mv $@ obj/$@

%.o: keyboard/%.c
	i686-elf-gcc -c $< -o $@ $(GCCPARAMS)
	mv $@ obj/$@

myos.bin: $(OBJFILES) $(LINKFILE)
	i686-elf-gcc -T $(LINKFILE) -o $@ $(OBJFILES) $(GCCLINKING)

myos.iso:
	mkdir -p iso/boot/grub
	cp myos.bin iso/boot/myos.bin
	
	touch grub.cfg
	echo "menuentry 'myos' {" > grub.cfg
	echo "	multiboot /boot/myos.bin" >> grub.cfg
	echo "}" >> grub.cfg
	
	mv grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso iso

clean:
	rm -rv myos.*
	rm -rv obj/*.*
	rm -rv iso/

run:
	qemu-system-i386 -cdrom myos.iso