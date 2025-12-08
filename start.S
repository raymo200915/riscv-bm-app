    .section .text.entry
    .globl _start
_start:
    # Initial stack pointer to _stack_top
    la  sp, _stack_top

    # Jump to C main()
    call main

1:
    wfi
    j 1b
