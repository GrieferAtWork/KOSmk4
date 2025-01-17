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
#ifndef _I386_KOS_KOS_KERNEL_BITS_GDB_CPU_STATE32_H
#define _I386_KOS_KOS_KERNEL_BITS_GDB_CPU_STATE32_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

#include <bits/types.h>

__SYSDECL_BEGIN

#if defined(__i386__) && !defined(__x86_64__)
#define GDB_REGISTER_MAXSIZE GDB_REGISTER_I386_MAXSIZE
#define GDB_REGISTER_COUNT   GDB_REGISTER_I386_COUNT
#define GDB_REGISTER_PC      GDB_REGISTER_I386_EIP
#define gdb_cpustate32       gdb_cpustate
#endif /* __i386__ && !__x86_64__ */
#define GDB_REGISTER_I386_MAXSIZE 16 /* Max register size (including extended registers). */

#define GDB_REGISTER_I386_EAX    0x00 /* [C] Accumulator register */
#define GDB_REGISTER_I386_ECX    0x01 /* [C] Count register */
#define GDB_REGISTER_I386_EDX    0x02 /* [C] Data register */
#define GDB_REGISTER_I386_EBX    0x03 /* [P] Base register */
#define GDB_REGISTER_I386_ESP    0x04 /* [P] Stack pointer */
#define GDB_REGISTER_I386_EBP    0x05 /* [P] Frame base pointer */
#define GDB_REGISTER_I386_ESI    0x06 /* [C] Source pointer */
#define GDB_REGISTER_I386_EDI    0x07 /* [C] Destination pointer */
#define GDB_REGISTER_I386_EIP    0x08 /* Instruction pointer */
#define GDB_REGISTER_I386_EFLAGS 0x09 /* Flags register */
#define GDB_REGISTER_I386_CS     0x0a /* Code segment */
#define GDB_REGISTER_I386_SS     0x0b /* Stack segment */
#define GDB_REGISTER_I386_DS     0x0c /* D (destination) segment register */
#define GDB_REGISTER_I386_ES     0x0d /* E (source) segment register */
#define GDB_REGISTER_I386_FS     0x0e /* F segment register */
#define GDB_REGISTER_I386_GS     0x0f /* G segment register */
#define GDB_REGISTER_I386_ST0    0x10 /* %st(0) */
#define GDB_REGISTER_I386_ST1    0x11 /* %st(1) */
#define GDB_REGISTER_I386_ST2    0x12 /* %st(2) */
#define GDB_REGISTER_I386_ST3    0x13 /* %st(3) */
#define GDB_REGISTER_I386_ST4    0x14 /* %st(4) */
#define GDB_REGISTER_I386_ST5    0x15 /* %st(5) */
#define GDB_REGISTER_I386_ST6    0x16 /* %st(6) */
#define GDB_REGISTER_I386_ST7    0x17 /* %st(7) */
#define GDB_REGISTER_I386_FCW    0x18 /* fs_fcw (fctrl) */
#define GDB_REGISTER_I386_FSW    0x19 /* fs_fsw (fstat) */
#define GDB_REGISTER_I386_FTW    0x1a /* fs_ftw (ftag) */
#define GDB_REGISTER_I386_FCS    0x1b /* fs_fcs (fiseg) */
#define GDB_REGISTER_I386_FIP    0x1c /* fs_fip (fioff) */
#define GDB_REGISTER_I386_FDS    0x1d /* fs_fds (foseg) */
#define GDB_REGISTER_I386_FDP    0x1e /* fs_fdp (fooff) */
#define GDB_REGISTER_I386_FOP    0x1f /* fs_fop (fop) */
#define GDB_REGISTER_I386_XMM0   0x20 /* %xmm0 */
#define GDB_REGISTER_I386_XMM1   0x21 /* %xmm1 */
#define GDB_REGISTER_I386_XMM2   0x22 /* %xmm2 */
#define GDB_REGISTER_I386_XMM3   0x23 /* %xmm3 */
#define GDB_REGISTER_I386_XMM4   0x24 /* %xmm4 */
#define GDB_REGISTER_I386_XMM5   0x25 /* %xmm5 */
#define GDB_REGISTER_I386_XMM6   0x26 /* %xmm6 */
#define GDB_REGISTER_I386_XMM7   0x27 /* %xmm7 */
#define GDB_REGISTER_I386_MXCSR  0x28 /* %mxcsr */
#define GDB_REGISTER_I386_FSBASE 0x30 /* %fs.base */
#define GDB_REGISTER_I386_GSBASE 0x31 /* %gs.base */
#define GDB_REGISTER_I386_COUNT  0x32


#ifdef __CC__
struct gdb_cpustate32 {
	/* The basic register state that is used by the `g' / `G' commands. */
	__u32 gcs_eax;    /* [C] Accumulator register */
	__u32 gcs_ecx;    /* [C] Count register */
	__u32 gcs_edx;    /* [C] Data register */
	__u32 gcs_ebx;    /* [P] Base register */
	__u32 gcs_esp;    /* [P] Stack pointer */
	__u32 gcs_ebp;    /* [P] Frame base pointer */
	__u32 gcs_esi;    /* [C] Source pointer */
	__u32 gcs_edi;    /* [C] Destination pointer */
	__u32 gcs_eip;    /* Instruction pointer */
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

#endif /* !_I386_KOS_KOS_KERNEL_BITS_GDB_CPU_STATE32_H */
