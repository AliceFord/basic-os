.set ALIGN,	1<<0
.set MEMINFO,	1<<1
.set FLAGS,	ALIGN | MEMINFO
.set MAGIC,	0x1BADB002
.set CHECKSUM,	-(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* stack */

.section .bss
.align 16
stack_bottom:
.skip 16384
stack_top:

.section .text
.global _start
.type _start, @function
_start:
	/* 32 bit protected mode */

	mov $stack_top, %esp

	/* lots of important stuff here, for instance exceptions, GDT, paging */

	call kernel_main

	cli
1:	hlt  /* loop forever */
	jmp 1b

.size _start, . - _start  /* current location - start */
