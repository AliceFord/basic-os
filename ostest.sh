if grub-file --is-x86-multiboot myos.bin; then
	echo multiboot working
else
	echo multiboot fail!!!
fi
