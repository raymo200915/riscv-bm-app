/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Regents of the University of California
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 * Copyright (c) 2025 RISCstar Solutions.
 */

#ifndef _SBI_H
#define _SBI_H

#include <stdint.h>
#include <stdarg.h>

struct sbi_ret {
        long error;
        long value;
};

/* place SBI call IDs here */
#define SBI_EXT_CONSOLE_PUTCHAR 1UL

enum sbi_ext_id {
#ifdef CONFIG_RISCV_SBI_V01
        SBI_EXT_0_1_SET_TIMER = 0x0,
        SBI_EXT_0_1_CONSOLE_PUTCHAR = 0x1,
        SBI_EXT_0_1_CONSOLE_GETCHAR = 0x2,
        SBI_EXT_0_1_CLEAR_IPI = 0x3,
        SBI_EXT_0_1_SEND_IPI = 0x4,
        SBI_EXT_0_1_REMOTE_FENCE_I = 0x5,
        SBI_EXT_0_1_REMOTE_SFENCE_VMA = 0x6,
        SBI_EXT_0_1_REMOTE_SFENCE_VMA_ASID = 0x7,
        SBI_EXT_0_1_SHUTDOWN = 0x8,
#endif
        SBI_EXT_BASE = 0x10,
        SBI_EXT_TIME = 0x54494D45,
        SBI_EXT_IPI = 0x735049,
        SBI_EXT_RFENCE = 0x52464E43,
        SBI_EXT_HSM = 0x48534D,
        SBI_EXT_SRST = 0x53525354,
        SBI_EXT_SUSP = 0x53555350,
        SBI_EXT_PMU = 0x504D55,
        SBI_EXT_DBCN = 0x4442434E,
        SBI_EXT_STA = 0x535441,
        SBI_EXT_NACL = 0x4E41434C,
        SBI_EXT_FWFT = 0x46574654,
        SBI_EXT_MPXY = 0x4D505859,

        /* Experimentals extensions must lie within this range */
        SBI_EXT_EXPERIMENTAL_START = 0x08000000,
        SBI_EXT_EXPERIMENTAL_END = 0x08FFFFFF,

        /* Vendor extensions must lie within this range */
        SBI_EXT_VENDOR_START = 0x09000000,
        SBI_EXT_VENDOR_END = 0x09FFFFFF,
};

enum sbi_ext_base_fid {
        SBI_EXT_BASE_GET_SPEC_VERSION = 0,
        SBI_EXT_BASE_GET_IMP_ID,
        SBI_EXT_BASE_GET_IMP_VERSION,
        SBI_EXT_BASE_PROBE_EXT,
        SBI_EXT_BASE_GET_MVENDORID,
        SBI_EXT_BASE_GET_MARCHID,
        SBI_EXT_BASE_GET_MIMPID,
};

enum sbi_ext_time_fid {
        SBI_EXT_TIME_SET_TIMER = 0,
};

enum sbi_ext_ipi_fid {
        SBI_EXT_IPI_SEND_IPI = 0,
};

enum sbi_ext_rfence_fid {
        SBI_EXT_RFENCE_REMOTE_FENCE_I = 0,
        SBI_EXT_RFENCE_REMOTE_SFENCE_VMA,
        SBI_EXT_RFENCE_REMOTE_SFENCE_VMA_ASID,
        SBI_EXT_RFENCE_REMOTE_HFENCE_GVMA_VMID,
        SBI_EXT_RFENCE_REMOTE_HFENCE_GVMA,
        SBI_EXT_RFENCE_REMOTE_HFENCE_VVMA_ASID,
        SBI_EXT_RFENCE_REMOTE_HFENCE_VVMA,
};

enum sbi_ext_hsm_fid {
        SBI_EXT_HSM_HART_START = 0,
        SBI_EXT_HSM_HART_STOP,
        SBI_EXT_HSM_HART_STATUS,
        SBI_EXT_HSM_HART_SUSPEND,
};

enum sbi_hsm_hart_state {
        SBI_HSM_STATE_STARTED = 0,
        SBI_HSM_STATE_STOPPED,
        SBI_HSM_STATE_START_PENDING,
        SBI_HSM_STATE_STOP_PENDING,
        SBI_HSM_STATE_SUSPENDED,
        SBI_HSM_STATE_SUSPEND_PENDING,
        SBI_HSM_STATE_RESUME_PENDING,
};

#ifdef CONFIG_RISCV_SBI_V01
void sbi_console_putchar(char ch);
void sbi_prints(const char *s);
void sbi_print_unsigned(uint64_t val, int base, int uppercase);
void sbi_print_signed(int64_t val);
void sbi_printf(const char *fmt, ...);
#endif
uint64_t sbi_get_spec_version(void);
uint64_t sbi_get_impl_id(void);
uint64_t sbi_get_impl_version(void);
long sbi_set_timer(uint64_t stime_value);

#endif
