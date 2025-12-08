#include <stdint.h>

#ifdef BM_S_MODE

#define SBI_EXT_CONSOLE_PUTCHAR 1UL

static inline void putchar(char ch)
{
	register unsigned long a0 asm("a0") = (unsigned long)(uint8_t)ch;
	register unsigned long a7 asm("a7") = SBI_EXT_CONSOLE_PUTCHAR;

	asm volatile ("ecall"
		      : "+r"(a0)
		      : "r"(a7)
		      : "memory");
}

#else /* via UART MMIO in M-mode */

#define UART0_BASE      0x10000000UL
#define UART_RBR        0
#define UART_THR        0
#define UART_LSR        5
#define UART_LSR_THRE   (1 << 5)

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
	print("\n[BM] main() reached!\n");
	print(" Welcome to OpenSBI bare-metal app!\n");
	print(" Running in its own payload\n\n");

	while (1) {
		__asm__ volatile ("wfi");
	}
}
