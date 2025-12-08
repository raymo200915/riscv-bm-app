/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2025 RISCstar Solutions.
 *
 * Authors:
 *   Raymond Mao <raymond.mao@riscstar.com>
 */

#ifndef __BM_APP_H__
#define __BM_APP_H__

#ifdef BM_S_MODE

/* place SBI call IDs here */
#define SBI_EXT_CONSOLE_PUTCHAR 1UL

#else

/* for QEMU test only via UART MMIO when app is running in M-mode */

/* UART base address defined by QEMU virt machine */
#define UART0_BASE      0x10000000UL
/* UART register offset defined in uart8250.c */
#define UART_RBR        0
#define UART_THR        0
#define UART_LSR        5
#define UART_LSR_THRE   (1 << 5)

#endif

#endif
