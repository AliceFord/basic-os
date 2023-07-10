CC = ~/opt/cross/bin/i686-elf

drivedata.o: drivedata.asm
	nasm -f elf32 drivedata.asm -o drivedata.o

%.o: %.c
	$(CC)-gcc -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

all: kernel.o io.o std.o drivedata.o
	$(CC)-as boot.s -o boot.o
	$(CC)-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o drivedata.o kernel.o io.o std.o -lgcc

	cp myos.bin isodir/boot/myos.bin
	grub-mkrescue /usr/lib/grub/i386-pc -o myos.iso isodir

clean:
	rm *.o
