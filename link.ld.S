ENTRY(_start)

SECTIONS
{
#ifdef BM_S_MODE
  . = 0x80200000;
#else
  . = 0x80000000;
#endif

  .text : ALIGN(4)
  {
    *(.text.entry)   /* _start is at here */
    *(.text*)
    *(.rodata*)
  }

  .data : ALIGN(4)
  {
    *(.data*)
    *(.sdata*)
  }

  .bss (NOLOAD) : ALIGN(4)
  {
    *(.bss*)
    *(COMMON)
    *(.sbss*)
    *(.scommon*)
  }

  . = ALIGN(16);
  _stack_top = . + 0x4000;  /* 16KB stack */
}