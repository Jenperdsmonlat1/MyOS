GCCPARAMS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
GCCLINKING = -ffreestanding -O2 -nostdlib -lgcc
NASMPARAMS = -felf32

OBJFILES = obj/kernel.o \
		   obj/vga.o \
		   obj/boot.o \
		   obj/keyboard.o \
		   obj/cursor.o \
		   obj/stdio.o \
		   obj/serial_port.o \
		   obj/gdt.o \
		   obj/load_gdt.o \
		   obj/idt.o \
		   obj/interrupts.o \
		   obj/pic.o

LINKFILE = linker.ld

%.o:boot/%.asm
	nasm $(NASMPARAMS) -o $@ $<
	mv $@ obj/$@

%.o:dt/gdt/%.c
	i686-elf-gcc -c $< -o $@ $(GCCPARAMS)
	mv $@ obj/$@

%.o:dt/gdt/%.asm
	nasm $(NASMPARAMS) -o $@ $<
	mv $@ obj/$@

%.o:dt/idt/%.c
	i686-elf-gcc -c $< -o $@ $(GCCPARAMS)
	mv $@ obj/$@

%.o:dt/idt/%.asm
	nasm $(NASMPARAMS) -o $@ $<
	mv $@ obj/$@

%.o:kernel/%.c
	i686-elf-gcc -c $< -o $@ $(GCCPARAMS)
	mv $@ obj/$@

%.o:vga/%.c
	i686-elf-gcc -c $< -o $@ $(GCCPARAMS)
	mv $@ obj/$@

%.o:io/cursor/%.asm
	nasm $(NASMPARAMS) $< -o $@
	mv $@ obj/$@

%.o:keyboard/%.c
	i686-elf-gcc -c $< -o $@ $(GCCPARAMS)
	mv $@ obj/$@

%.o:io/stdio/%.c
	i686-elf-gcc -c $< -o $@ $(GCCPARAMS)
	mv $@ obj/$@

%.o:io/serial_port/%.c
	i686-elf-gcc -c $< -o $@ $(GCCPARAMS)
	mv $@ obj/$@

%.o:io/pic/%.c
	i686-elf-gcc -c $< -o $@ $(GCCPARAMS)
	mv $@ obj/$@

all:
	nasm $(NASMPARAMS) -o load_gdt.o dt/gdt/load_gdt.asm
	nasm $(NASMPARAMS) -o boot.o boot/boot.asm
	nasm $(NASMPARAMS) -o interrupts.o dt/idt/interrupts.asm
	nasm $(NASMPARAMS) -o cursor.o io/cursor/cursor.asm
	i686-elf-gcc -c kernel/kernel.c -o kernel.o $(GCCPARAMS)
	i686-elf-gcc -c io/serial_port/serial_port.c -o serial_port.o $(GCCPARAMS)
	i686-elf-gcc -c io/stdio/stdio.c -o stdio.o $(GCCPARAMS)
	i686-elf-gcc -c keyboard/keyboard.c -o keyboard.o $(GCCPARAMS)
	i686-elf-gcc -c vga/vga.c -o vga.o $(GCCPARAMS)
	i686-elf-gcc -c dt/idt/idt.c -o idt.o $(GCCPARAMS)
	i686-elf-gcc -c dt/gdt/gdt.c -o gdt.o $(GCCPARAMS)
	i686-elf-gcc -c io/pic/pic.c -o pic.o $(GCCPARAMS)
	mv load_gdt.o obj/load_gdt.o
	mv boot.o obj/boot.o
	mv interrupts.o obj/interrupts.o
	mv cursor.o obj/cursor.o
	mv kernel.o obj/kernel.o
	mv serial_port.o obj/serial_port.o
	mv stdio.o obj/stdio.o
	mv keyboard.o obj/keyboard.o
	mv vga.o obj/vga.o
	mv idt.o obj/idt.o
	mv gdt.o obj/gdt.o
	mv pic.o obj/pic.o
	
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

run-with-serial:
	qemu-system-i386 -cdrom myos.iso -serial pty

run-debug:
	qemu-system-i386 -cdrom myos.iso -no-reboot -no-shutdown -M smm=off -d int
