#include <stdint.h>

static inline long sbi_call(long ext, long fid,
			    long arg0, long arg1,
			    long arg2, long arg3)
{
	(void)arg1;

	register long a0 asm("a0") = arg0;
	register long a1 asm("a1") = 0;
	register long a2 asm("a2") = arg2;
	register long a3 asm("a3") = arg3;
	register long a6 asm("a6") = fid;
	register long a7 asm("a7") = ext;

	asm volatile ("ecall"
		      : "+r"(a0), "+r"(a1)
		      : "r"(a2), "r"(a3), "r"(a6), "r"(a7)
		      : "memory");
	return a0;
}

#define SBI_EXT_CONSOLE_PUTCHAR 0x01

static void sbi_putc(char ch)
{
	sbi_call(SBI_EXT_CONSOLE_PUTCHAR, 0, ch, 0, 0, 0);
}

static void print(const char *s)
{
	while (*s) {
		sbi_putc(*s++);
	}
}

void _start(void)
{
	print("\r\n======================================\r\n");
	print(" Welcome to OpenSBI bare-metal app!\r\n");
	print(" Running in its own payload \r\n");
	print("======================================\r\n\r\n");

	while (1) {
		asm volatile ("wfi");
	}
}

