/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2025 RISCstar Solutions.
 *
 * Author: Raymond Mao <raymond.mao@riscstar.com>
 */

#include "timer.h"
#include "sbi.h"

static uint64_t g_interval_ticks = 0;
static void (*g_timer_cb)(void) = 0;

static void timer_isr(void)
{
	/* TODO */
}

static void trap_init(void)
{
	/* TODO */
}

static inline uint64_t rdtime(void)
{
	uint64_t v;
	asm volatile ("rdtime %0" : "=r"(v));
	return v;
}

static void timer_register_callback(void (*cb)(void))
{
	g_timer_cb = cb;
}

long timer_init(uint64_t interval_ticks, void (*cb)(void))
{
	uint64_t now = rdtime();

	g_interval_ticks = interval_ticks;

	if (cb)
		timer_register_callback(cb);
	else
		timer_register_callback(timer_isr);

	trap_init();

	return sbi_set_timer(now + g_interval_ticks);
}
