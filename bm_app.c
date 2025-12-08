#include <stdint.h>
#include "bm_app.h"

#ifdef BM_S_MODE

static inline void putchar(char ch)
{
	register unsigned long a0 asm("a0") = (unsigned long)(uint8_t)ch;
	register unsigned long a7 asm("a7") = SBI_EXT_CONSOLE_PUTCHAR;

	asm volatile ("ecall"
		      : "+r"(a0)
		      : "r"(a7)
		      : "memory");
}

#else

/* for QEMU test only via UART MMIO when app is running in M-mode */

static inline void putchar(char ch)
{
	volatile uint8_t *uart = (volatile uint8_t *)UART0_BASE;

	while (!(uart[UART_LSR] & UART_LSR_THRE))
		;

	uart[UART_THR] = (uint8_t)ch;
}

#endif

static void print(const char *s)
{
	while (*s) {
		if (*s == '\n')
			putchar('\r');
		putchar(*s++);
	}
}

void main(void)
{
	print(" \nWelcome to OpenSBI bare-metal app!\n");

	while (1) {
		__asm__ volatile ("wfi");
	}
}
