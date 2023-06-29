/* ANY ISSUES ITS THIS I GUARANTEE */

ENTRY(_start)

SECTIONS
{
    . = 1M;

    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }

    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    /* rw data */
    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    /* uninitialized data */
    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }
}