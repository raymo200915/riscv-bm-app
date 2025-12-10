/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2025 RISCstar Solutions.
 *
 * Author: Raymond Mao <raymond.mao@riscstar.com>
 */

#include "sbi.h"

static inline struct sbi_ret sbi_legacy_ecall(uint64_t which,
                                	      uint64_t arg0,
                                	      uint64_t arg1,
                                	      uint64_t arg2)
{
	register uint64_t a0 asm("a0") = arg0;
	register uint64_t a1 asm("a1") = arg1;
	register uint64_t a2 asm("a2") = arg2;
	register uint64_t a7 asm("a7") = which;

	asm volatile ("ecall"
		      : "+r"(a0), "+r"(a1)
		      : "r"(a2), "r"(a7)
		      : "memory");

	struct sbi_ret ret = {
		.error = (long)a0,
		.value = (long)a1,
	};

	return ret;
}

static inline struct sbi_ret sbi_ecall(uint64_t ext, uint64_t fid,
                        	       uint64_t arg0, uint64_t arg1,
                        	       uint64_t arg2, uint64_t arg3)
{
	register uint64_t a0 asm("a0") = arg0;
	register uint64_t a1 asm("a1") = arg1;
	register uint64_t a2 asm("a2") = arg2;
	register uint64_t a3 asm("a3") = arg3;
	register uint64_t a6 asm("a6") = fid;
	register uint64_t a7 asm("a7") = ext;

	asm volatile ("ecall"
		      : "+r"(a0), "+r"(a1)
		      : "r"(a2), "r"(a3), "r"(a6), "r"(a7)
		      : "memory");

	struct sbi_ret ret = {
		.error = (long)a0,
		.value = (long)a1,
	};

	return ret;
}

#ifdef CONFIG_RISCV_SBI_V01

void sbi_console_putchar(char ch)
{
	(void)sbi_legacy_ecall(SBI_EXT_0_1_CONSOLE_PUTCHAR,
			       (uint64_t)ch, 0, 0);
}

void sbi_prints(const char *s)
{
	while (*s) {
		if (*s == '\n')
			sbi_console_putchar('\r');  /* CRLF */
		sbi_console_putchar(*s++);
	}
}

void sbi_print_unsigned(uint64_t val, int base, int uppercase)
{
	char buf[32];
	const char *digits = uppercase ?
		"0123456789ABCDEF" : "0123456789abcdef";
	int i = 0;

	if (!val) {
		sbi_console_putchar('0');
		return;
	}

	while (val && i < (int)sizeof(buf)) {
		buf[i++] = digits[val % base];
		val /= base;
	}

	while (i--)
		sbi_console_putchar(buf[i]);
}

void sbi_print_signed(int64_t val)
{
	if (val < 0) {
		sbi_console_putchar('-');
		val = -val;
	}
	sbi_print_unsigned((uint64_t)val, 10, 0);
}

void sbi_printf(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);

	while (*fmt) {
		if (*fmt != '%') {
			sbi_console_putchar(*fmt++);
			continue;
		}
		fmt++;  // skip '%'

		switch (*fmt) {
		case '%':
			sbi_console_putchar('%');
			break;
		case 'c': {
			int c = va_arg(ap, int);

			sbi_console_putchar(c);
			break;
		}
		case 's': {
			const char *s = va_arg(ap, const char *);

			if (!s)
				s = "(null)";
			sbi_prints(s);
			break;
		}
		case 'd':
		case 'i': {
			int64_t v = va_arg(ap, int64_t);

			sbi_print_signed(v);
			break;
		}
		case 'u': {
			uint64_t v = va_arg(ap, uint64_t);

			sbi_print_unsigned(v, 10, 0);
			break;
		}
		case 'x':
		case 'X': {
			uint64_t v = va_arg(ap, uint64_t);

			sbi_print_unsigned(v, 16, *fmt == 'X');
			break;
		}
		default:
			sbi_console_putchar('%');
			sbi_console_putchar(*fmt);
			break;
		}

		fmt++;
	}

	va_end(ap);
}

#endif

inline uint64_t sbi_get_spec_version(void)
{
	struct sbi_ret ret =
		sbi_ecall(SBI_EXT_BASE, SBI_EXT_BASE_GET_SPEC_VERSION,
			  0, 0, 0, 0);
	return ret.value;
}

inline uint64_t sbi_get_impl_id(void)
{
	struct sbi_ret ret =
		sbi_ecall(SBI_EXT_BASE, SBI_EXT_BASE_GET_IMP_ID,
			  0, 0, 0, 0);
	return ret.value;
}

inline uint64_t sbi_get_impl_version(void)
{
	struct sbi_ret ret =
		sbi_ecall(SBI_EXT_BASE, SBI_EXT_BASE_GET_IMP_VERSION,
			  0, 0, 0, 0);
	return ret.value;
}

long sbi_set_timer(uint64_t stime_value)
{
	struct sbi_ret ret =
		sbi_ecall(SBI_EXT_TIME, SBI_EXT_TIME_SET_TIMER,
			  stime_value, 0, 0, 0);
	return ret.error;
}
