/* link.ld */
OUTPUT_ARCH(riscv)
ENTRY(_start)

SECTIONS
{
    /* Match to the same load address for u-boot.itb: 0x80200000 */
    . = 0x80200000;

    .text : ALIGN(4)
    {
        *(.text._start)
        *(.text*)
    }

    .rodata : ALIGN(4)
    {
        *(.rodata*)
    }

    .data : ALIGN(4)
    {
        *(.data*)
    }

    .bss : ALIGN(4)
    {
        *(.bss*)
        *(COMMON)
    }
}

