/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (c) 2025 RISCstar Solutions.
 *
 * Author: Raymond Mao <raymond.mao@riscstar.com>
 */

#ifndef _TIMER_H
#define _TIMER_H

#include <stdint.h>

long timer_init(uint64_t interval_ticks, void (*cb)(void));

#endif
