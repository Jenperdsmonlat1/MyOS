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
		   obj/idt.o \
		   obj/gdt.o \
		   obj/load_gdt.o \
		   obj/interrupts.o \
		   obj/pic.o

LINKFILE = linker.ld

%.o:%.asm
	nasm $(NASMPARAMS) -o $@ $<
	mv $@ obj/$@

%.o:%.c
	i686-elf-gcc -c $< -o $@ $(GCCPARAMS)
	mv $@ obj/$@

all:
	mkdir obj
	nasm $(NASMPARAMS) -o boot.o boot/boot.asm
	nasm $(NASMPARAMS) -o interrupts.o idt/interrupts.asm
	nasm $(NASMPARAMS) -o load_gdt.o gdt/load_gdt.asm
	nasm $(NASMPARAMS) -o cursor.o io/cursor/cursor.asm
	i686-elf-gcc -c kernel/kernel.c -o kernel.o $(GCCPARAMS)
	i686-elf-gcc -c io/serial_port/serial_port.c -o serial_port.o $(GCCPARAMS)
	i686-elf-gcc -c io/stdio/stdio.c -o stdio.o $(GCCPARAMS)
	i686-elf-gcc -c driver/keyboard/keyboard.c -o keyboard.o $(GCCPARAMS)
	i686-elf-gcc -c driver/vga/vga.c -o vga.o $(GCCPARAMS)
	i686-elf-gcc -c idt/idt.c -o idt.o $(GCCPARAMS)
	i686-elf-gcc -c gdt/gdt.c -o gdt.o $(GCCPARAMS)
	i686-elf-gcc -c io/pic/pic.c -o pic.o $(GCCPARAMS)
	mv boot.o obj/boot.o
	mv interrupts.o obj/interrupts.o
	mv cursor.o obj/cursor.o
	mv kernel.o obj/kernel.o
	mv serial_port.o obj/serial_port.o
	mv stdio.o obj/stdio.o
	mv keyboard.o obj/keyboard.o
	mv vga.o obj/vga.o
	mv idt.o obj/idt.o
	mv pic.o obj/pic.o
	mv gdt.o obj/gdt.o
	mv load_gdt.o obj/load_gdt.o
	
myos.bin: $(OBJFILES) $(LINKFILE)
	i686-elf-gcc -T $(LINKFILE) -o $@ $(OBJFILES) $(GCCLINKING)

myos.iso:
	cp myos.bin iso/boot/myos.bin
	grub-mkrescue -o myos.iso iso

clean:
	rm -rv myos.*
	rm -rv obj
	rm -rv iso/boot/myos.bin

run:
	qemu-system-i386 -cdrom myos.iso -serial pty

run-debug:
	qemu-system-i386 -s -S myos.iso -no-reboot -no-shutdown -M smm=off -d int -D /dev/stdout
