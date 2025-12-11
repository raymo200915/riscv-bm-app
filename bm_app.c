/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2025 RISCstar Solutions.
 *
 * Author: Raymond Mao <raymond.mao@riscstar.com>
 */

#include <stdint.h>
#include "sbi.h"
#include "timer.h"

static void print_opensbi_version(void)
{
	uint32_t spec = (uint32_t)sbi_get_spec_version();
	uint32_t impl = (uint32_t)sbi_get_impl_id();
	uint32_t iver = (uint32_t)sbi_get_impl_version();

	uint32_t spec_major = (spec >> 24) & 0xff;
	uint32_t spec_minor = spec & 0x00ffffff;

	uint32_t impl_major = (iver >> 16) & 0xffff;
	uint32_t impl_minor = iver & 0xffff;

	sbi_printf("SBI Spec Version: %u.%u\n", spec_major, spec_minor);

	if (impl == 1)
		sbi_printf("SBI Implementation: OpenSBI\n");
	else
		sbi_printf("SBI Implementation ID: %u\n", impl);

	sbi_printf("OpenSBI Version: %u.%u\n", impl_major, impl_minor);
}

void main(void)
{
	uint64_t ticks_per_second = 10000000ULL;
	long ret;

	sbi_printf("\nWelcome to OpenSBI bare-metal app!\n");
	print_opensbi_version();

	ret = timer_init(ticks_per_second, 0);
	if (!ret)
		sbi_printf("Init timer successfully %d ticks/s",
			   ticks_per_second);

	while (1)
		__asm__ volatile ("wfi");
}
