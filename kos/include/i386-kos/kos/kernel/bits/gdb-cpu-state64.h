/* Copyright (c) 2019-2025 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_KOS_KERNEL_BITS_GDB_CPU_STATE64_H
#define _I386_KOS_KOS_KERNEL_BITS_GDB_CPU_STATE64_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

#include <bits/types.h>

__SYSDECL_BEGIN

#ifdef __x86_64__
#define GDB_REGISTER_MAXSIZE GDB_REGISTER_X86_64_MAXSIZE
#define GDB_REGISTER_COUNT   GDB_REGISTER_X86_64_COUNT
#define GDB_REGISTER_PC      GDB_REGISTER_X86_64_RIP
#define gdb_cpustate64       gdb_cpustate
#endif /* __x86_64__ */
#define GDB_REGISTER_X86_64_MAXSIZE 16 /* Max register size (including extended registers). */

/* For no reason what-so-ever, GDB uses a totally f%*$ed up ordering for GP register 0-7 */
#define GDB_REGISTER_X86_64_RAX    0x00 /* 64-bit [C] Accumulator register */
#define GDB_REGISTER_X86_64_RBX    0x01 /* 64-bit [P] Base register */
#define GDB_REGISTER_X86_64_RCX    0x02 /* 64-bit [C] Count register */
#define GDB_REGISTER_X86_64_RDX    0x03 /* 64-bit [C] Data register */
#define GDB_REGISTER_X86_64_RSI    0x04 /* 64-bit [C] Source pointer */
#define GDB_REGISTER_X86_64_RDI    0x05 /* 64-bit [C] Destination pointer */
#define GDB_REGISTER_X86_64_RBP    0x06 /* 64-bit [P] Frame base pointer */
#define GDB_REGISTER_X86_64_RSP    0x07 /* 64-bit [P] Stack pointer */
#define GDB_REGISTER_X86_64_R8     0x08 /* 64-bit %r8 */
#define GDB_REGISTER_X86_64_R9     0x09 /* 64-bit %r9 */
#define GDB_REGISTER_X86_64_R10    0x0a /* 64-bit %r10 */
#define GDB_REGISTER_X86_64_R11    0x0b /* 64-bit %r11 */
#define GDB_REGISTER_X86_64_R12    0x0c /* 64-bit %r12 */
#define GDB_REGISTER_X86_64_R13    0x0d /* 64-bit %r13 */
#define GDB_REGISTER_X86_64_R14    0x0e /* 64-bit %r14 */
#define GDB_REGISTER_X86_64_R15    0x0f /* 64-bit %r15 */
#define GDB_REGISTER_X86_64_RIP    0x10 /* 64-bit Instruction pointer */
#define GDB_REGISTER_X86_64_RFLAGS 0x11 /* 32-bit Flags register */
#define GDB_REGISTER_X86_64_CS     0x12 /* 32-bit Code segment */
#define GDB_REGISTER_X86_64_SS     0x13 /* 32-bit Stack segment */
#define GDB_REGISTER_X86_64_DS     0x14 /* 32-bit D (destination) segment register */
#define GDB_REGISTER_X86_64_ES     0x15 /* 32-bit E (source) segment register */
#define GDB_REGISTER_X86_64_FS     0x16 /* 32-bit F segment register */
#define GDB_REGISTER_X86_64_GS     0x17 /* 32-bit G segment register */
#define GDB_REGISTER_X86_64_ST0    0x18 /* 80-bit %st(0) */
#define GDB_REGISTER_X86_64_ST1    0x19 /* 80-bit %st(1) */
#define GDB_REGISTER_X86_64_ST2    0x1a /* 80-bit %st(2) */
#define GDB_REGISTER_X86_64_ST3    0x1b /* 80-bit %st(3) */
#define GDB_REGISTER_X86_64_ST4    0x1c /* 80-bit %st(4) */
#define GDB_REGISTER_X86_64_ST5    0x1d /* 80-bit %st(5) */
#define GDB_REGISTER_X86_64_ST6    0x1e /* 80-bit %st(6) */
#define GDB_REGISTER_X86_64_ST7    0x1f /* 80-bit %st(7) */
#define GDB_REGISTER_X86_64_FCW    0x20 /* 32-bit fs_fcw (fctrl) */
#define GDB_REGISTER_X86_64_FSW    0x21 /* 32-bit fs_fsw (fstat) */
#define GDB_REGISTER_X86_64_FTW    0x22 /* 32-bit fs_ftw (ftag) */
#define GDB_REGISTER_X86_64_FCS    0x23 /* 32-bit fs_fcs (fiseg) */
#define GDB_REGISTER_X86_64_FIP    0x24 /* 32-bit fs_fip (fioff) */
#define GDB_REGISTER_X86_64_FDS    0x25 /* 32-bit fs_fds (foseg) */
#define GDB_REGISTER_X86_64_FDP    0x26 /* 32-bit fs_fdp (fooff) */
#define GDB_REGISTER_X86_64_FOP    0x27 /* 32-bit fs_fop (fop) */
#define GDB_REGISTER_X86_64_XMM0   0x28 /* 128-bit %xmm0 */
#define GDB_REGISTER_X86_64_XMM1   0x29 /* 128-bit %xmm1 */
#define GDB_REGISTER_X86_64_XMM2   0x2a /* 128-bit %xmm2 */
#define GDB_REGISTER_X86_64_XMM3   0x2b /* 128-bit %xmm3 */
#define GDB_REGISTER_X86_64_XMM4   0x2c /* 128-bit %xmm4 */
#define GDB_REGISTER_X86_64_XMM5   0x2d /* 128-bit %xmm5 */
#define GDB_REGISTER_X86_64_XMM6   0x2e /* 128-bit %xmm6 */
#define GDB_REGISTER_X86_64_XMM7   0x2f /* 128-bit %xmm7 */
#define GDB_REGISTER_X86_64_XMM8   0x30 /* 128-bit %xmm8 */
#define GDB_REGISTER_X86_64_XMM9   0x31 /* 128-bit %xmm9 */
#define GDB_REGISTER_X86_64_XMM10  0x32 /* 128-bit %xmm10 */
#define GDB_REGISTER_X86_64_XMM11  0x33 /* 128-bit %xmm11 */
#define GDB_REGISTER_X86_64_XMM12  0x34 /* 128-bit %xmm12 */
#define GDB_REGISTER_X86_64_XMM13  0x35 /* 128-bit %xmm13 */
#define GDB_REGISTER_X86_64_XMM14  0x36 /* 128-bit %xmm14 */
#define GDB_REGISTER_X86_64_XMM15  0x37 /* 128-bit %xmm15 */
#define GDB_REGISTER_X86_64_MXCSR  0x38 /* 32-bit %mxcsr */
#define GDB_REGISTER_X86_64_FSBASE 0x40 /* 64-bit %fs.base */
#define GDB_REGISTER_X86_64_GSBASE 0x41 /* 64-bit %gs.base */
#define GDB_REGISTER_X86_64_COUNT  0x42


#ifdef __CC__
struct __ATTR_PACKED gdb_cpustate64 {
	/* The basic register state that is used by the `g' / `G' commands. */
	__u64 gcs_rax;    /* [C] Accumulator register */
	__u64 gcs_rbx;    /* [P] Base register */
	__u64 gcs_rcx;    /* [C] Count register */
	__u64 gcs_rdx;    /* [C] Data register */
	__u64 gcs_rsi;    /* [C] Source pointer */
	__u64 gcs_rdi;    /* [C] Destination pointer */
	__u64 gcs_rbp;    /* [P] Frame base pointer */
	__u64 gcs_rsp;    /* [P] Stack pointer */
	__u64 gcs_r8;     /* %r8 */
	__u64 gcs_r9;     /* %r9 */
	__u64 gcs_r10;    /* %r10 */
	__u64 gcs_r11;    /* %r11 */
	__u64 gcs_r12;    /* %r12 */
	__u64 gcs_r13;    /* %r13 */
	__u64 gcs_r14;    /* %r14 */
	__u64 gcs_r15;    /* %r15 */
	__u64 gcs_rip;    /* Instruction pointer */
	__u32 gcs_eflags; /* Flags register */
	__u32 gcs_cs;     /* Code segment (zero-extended) */
	__u32 gcs_ss;     /* Stack segment (zero-extended) */
	__u32 gcs_ds;     /* D (destination) segment register (zero-extended) */
	__u32 gcs_es;     /* E (source) segment register (zero-extended) */
	__u32 gcs_fs;     /* F segment register (zero-extended) */
	__u32 gcs_gs;     /* G segment register (zero-extended) */
};
#endif /* __CC__ */

__SYSDECL_END

#endif /* !_I386_KOS_KOS_KERNEL_BITS_GDB_CPU_STATE64_H */
