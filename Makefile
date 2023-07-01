CC = ~/opt/cross/bin/i686-elf

%.o: %.c
	$(CC)-gcc -c $< -o $@ -std=gnu99 -ffreestanding -O2 -Wall -Wextra

all: kernel.o io.o std.o mem.o
	$(CC)-as boot.s -o boot.o
	$(CC)-gcc -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o io.o std.o mem.o -lgcc

	cp myos.bin isodir/boot/myos.bin
	grub-mkrescue /usr/lib/grub/i386-pc -o myos.iso isodir

clean:
	rm *.o
