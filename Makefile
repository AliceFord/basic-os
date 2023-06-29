CC = ~/opt/cross/bin/i686-elf

full:
	$(CC)-as boot.s -o boot.o
	$(CC)-gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	$(CC)-gcc -c io.c -o io.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
	$(CC)-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o io.o -lgcc

	cp myos.bin isodir/boot/myos.bin
	grub-mkrescue /usr/lib/grub/i386-pc -o myos.iso isodir