/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_KOS_KERNEL_GDB_CPU_STATE64_H
#define _I386_KOS_KOS_KERNEL_GDB_CPU_STATE64_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <bits/types.h>
#include <kos/anno.h>
#include <kos/kernel/cpu-state64.h>
#include <kos/kernel/cpu-state-helpers64.h>
#include <kos/kernel/paging.h>

#if !defined(__INTELLISENSE__) || 1
#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/kernel/gdt.h>
#endif /* !__INTELLISENSE__ */

__SYSDECL_BEGIN

#ifdef __x86_64__
#define GDB_REGISTER_MAXSIZE GDB_REGISTER_X86_64_MAXSIZE
#define GDB_REGISTER_PC      GDB_REGISTER_X86_64_RIP
#endif /* __x86_64__ */
#define GDB_REGISTER_X86_64_MAXSIZE 16 /* Max register size (including extended registers). */

#define GDB_REGISTER_X86_64_RAX    0x00 /* 64-bit [C] Accumulator register */
#define GDB_REGISTER_X86_64_RCX    0x01 /* 64-bit [C] Count register */
#define GDB_REGISTER_X86_64_RDX    0x02 /* 64-bit [C] Data register */
#define GDB_REGISTER_X86_64_RBX    0x03 /* 64-bit [P] Base register */
#define GDB_REGISTER_X86_64_RSP    0x04 /* 64-bit [P] Stack pointer */
#define GDB_REGISTER_X86_64_RBP    0x05 /* 64-bit [P] Frame base pointer */
#define GDB_REGISTER_X86_64_RSI    0x06 /* 64-bit [C] Source pointer */
#define GDB_REGISTER_X86_64_RDI    0x07 /* 64-bit [C] Destination pointer */
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
#define GDB_REGISTER_X86_64_FPUCS  0x23 /* 32-bit fs_fcs (fiseg) */
#define GDB_REGISTER_X86_64_FPUIP  0x24 /* 32-bit fs_fip (fioff) */
#define GDB_REGISTER_X86_64_FPUDS  0x25 /* 32-bit fs_fds (foseg) */
#define GDB_REGISTER_X86_64_FPUDP  0x26 /* 32-bit fs_fdp (fooff) */
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


#ifdef __CC__

#ifdef __x86_64__
#define gdb_cpustate64              gdb_cpustate
#define GDB_CPUSTATE_PC             GDB_CPUSTATE64_PC
#define GDB_CPUSTATE_SP             GDB_CPUSTATE64_SP
#define gdb_cpustate_from_icpustate gdb_cpustate64_from_icpustate64
#define gdb_cpustate_from_scpustate gdb_cpustate64_from_scpustate64
#define gdb_cpustate_from_ucpustate gdb_cpustate64_from_ucpustate64
#define gdb_cpustate_from_kcpustate gdb_cpustate64_from_kcpustate64
#define gdb_cpustate_from_lcpustate gdb_cpustate64_from_lcpustate64
#define gdb_cpustate_from_fcpustate gdb_cpustate64_from_fcpustate64
#define gdb_cpustate_to_icpustate   gdb_cpustate64_to_icpustate64
#define gdb_cpustate_to_scpustate   gdb_cpustate64_to_scpustate64
#define gdb_cpustate_to_ucpustate   gdb_cpustate64_to_ucpustate64
#define gdb_cpustate_to_kcpustate   gdb_cpustate64_to_kcpustate64
#define gdb_cpustate_to_lcpustate   gdb_cpustate64_to_lcpustate64
#define gdb_cpustate_to_fcpustate   gdb_cpustate64_to_fcpustate64
#endif /* !__x86_64__ */

struct __ATTR_PACKED gdb_cpustate64 {
	/* The basic register state that is used by the `g' / `G' commands. */
	__u64 gcs_rax;    /* [C] Accumulator register */
	__u64 gcs_rcx;    /* [C] Count register */
	__u64 gcs_rdx;    /* [C] Data register */
	__u64 gcs_rbx;    /* [P] Base register */
	__u64 gcs_rsp;    /* [P] Stack pointer */
	__u64 gcs_rbp;    /* [P] Frame base pointer */
	__u64 gcs_rsi;    /* [C] Source pointer */
	__u64 gcs_rdi;    /* [C] Destination pointer */
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

#define GDB_CPUSTATE64_PC(x) ((x).gcs_rip)
#define GDB_CPUSTATE64_SP(x) ((x).gcs_rsp)

struct icpustate64;
struct scpustate64;
struct ucpustate64;
struct kcpustate64;
struct lcpustate64;
struct fcpustate64;

/* Convert between GDB cpu states and other states used by the system. */
__LOCAL void gdb_cpustate64_from_gpregsnsp64_and_irregs64(struct gdb_cpustate64 *__restrict dst,
                                                          struct gpregsnsp64 const *__restrict gpregs,
                                                          struct irregs64 const *__restrict irregs);
__LOCAL void gdb_cpustate64_from_icpustate64(struct gdb_cpustate64 *__restrict dst, struct icpustate64 const *__restrict src);
__LOCAL void gdb_cpustate64_from_scpustate64(struct gdb_cpustate64 *__restrict dst, struct scpustate64 const *__restrict src);
__LOCAL void gdb_cpustate64_from_ucpustate64(struct gdb_cpustate64 *__restrict dst, struct ucpustate64 const *__restrict src);
__LOCAL void gdb_cpustate64_from_kcpustate64(struct gdb_cpustate64 *__restrict dst, struct kcpustate64 const *__restrict src);
__LOCAL void gdb_cpustate64_from_lcpustate64(struct gdb_cpustate64 *__restrict dst, struct lcpustate64 const *__restrict src);
__LOCAL void gdb_cpustate64_from_fcpustate64(struct gdb_cpustate64 *__restrict dst, struct fcpustate64 const *__restrict src);
__LOCAL struct icpustate64 *gdb_cpustate64_to_icpustate64(struct icpustate64 *__restrict dst, struct gdb_cpustate64 const *__restrict src);
__LOCAL struct scpustate64 *gdb_cpustate64_to_scpustate64(struct scpustate64 *__restrict dst, struct gdb_cpustate64 const *__restrict src);
__LOCAL struct ucpustate64 *gdb_cpustate64_to_ucpustate64(struct ucpustate64 *__restrict dst, struct gdb_cpustate64 const *__restrict src);
__LOCAL struct kcpustate64 *gdb_cpustate64_to_kcpustate64(struct kcpustate64 *__restrict dst, struct gdb_cpustate64 const *__restrict src);
__LOCAL struct lcpustate64 *gdb_cpustate64_to_lcpustate64(struct lcpustate64 *__restrict dst, struct gdb_cpustate64 const *__restrict src);
__LOCAL struct fcpustate64 *gdb_cpustate64_to_fcpustate64(struct fcpustate64 *__restrict dst, struct gdb_cpustate64 const *__restrict src);



#if !defined(__INTELLISENSE__) || 1
__LOCAL void
gdb_cpustate64_from_gpregsnsp64_and_irregs64(struct gdb_cpustate64 *__restrict dst,
                                             struct gpregsnsp64 const *__restrict gpregs,
                                             struct irregs64 const *__restrict irregs) {
	dst->gcs_rax    = gpregs->gp_rax;
	dst->gcs_rcx    = gpregs->gp_rcx;
	dst->gcs_rdx    = gpregs->gp_rdx;
	dst->gcs_rbx    = gpregs->gp_rbx;
	dst->gcs_rsp    = irregs->ir_rsp;
	dst->gcs_rbp    = gpregs->gp_rbp;
	dst->gcs_rsi    = gpregs->gp_rsi;
	dst->gcs_rdi    = gpregs->gp_rdi;
	dst->gcs_r8     = gpregs->gp_r8;
	dst->gcs_r9     = gpregs->gp_r9;
	dst->gcs_r10    = gpregs->gp_r10;
	dst->gcs_r11    = gpregs->gp_r11;
	dst->gcs_r12    = gpregs->gp_r12;
	dst->gcs_r13    = gpregs->gp_r13;
	dst->gcs_r14    = gpregs->gp_r14;
	dst->gcs_r15    = gpregs->gp_r15;
	dst->gcs_rip    = irregs->ir_rip;
	dst->gcs_eflags = (__u32)irregs->ir_rflags;
	dst->gcs_cs     = (__u32)irregs->ir_cs16;
	dst->gcs_ss     = (__u32)irregs->ir_ss16;
}


__LOCAL void
gdb_cpustate64_from_icpustate64(struct gdb_cpustate64 *__restrict dst,
                                struct icpustate64 const *__restrict src) {
	gdb_cpustate64_from_gpregsnsp64_and_irregs64(dst, &src->ics_gpregs, &src->ics_irregs);
	dst->gcs_ds = __rdds();
	dst->gcs_es = __rdes();
	dst->gcs_fs = __rdfs();
	dst->gcs_gs = __rdgs();
}

__LOCAL void
gdb_cpustate64_from_scpustate64(struct gdb_cpustate64 *__restrict dst,
                                struct scpustate64 const *__restrict src) {
	gdb_cpustate64_from_gpregsnsp64_and_irregs64(dst, &src->scs_gpregs, &src->scs_irregs);
	dst->gcs_ds = src->scs_sgregs.sg_ds16;
	dst->gcs_es = src->scs_sgregs.sg_es16;
	dst->gcs_fs = src->scs_sgregs.sg_fs16;
	dst->gcs_gs = src->scs_sgregs.sg_gs16;
}

__LOCAL void
gdb_cpustate64_from_ucpustate64(struct gdb_cpustate64 *__restrict dst,
                                struct ucpustate64 const *__restrict src) {
	dst->gcs_rax    = src->ucs_gpregs.gp_rax;
	dst->gcs_rcx    = src->ucs_gpregs.gp_rcx;
	dst->gcs_rdx    = src->ucs_gpregs.gp_rdx;
	dst->gcs_rbx    = src->ucs_gpregs.gp_rbx;
	dst->gcs_rsp    = src->ucs_gpregs.gp_rsp;
	dst->gcs_rbp    = src->ucs_gpregs.gp_rbp;
	dst->gcs_rsi    = src->ucs_gpregs.gp_rsi;
	dst->gcs_rdi    = src->ucs_gpregs.gp_rdi;
	dst->gcs_r8     = src->ucs_gpregs.gp_r8;
	dst->gcs_r9     = src->ucs_gpregs.gp_r9;
	dst->gcs_r10    = src->ucs_gpregs.gp_r10;
	dst->gcs_r11    = src->ucs_gpregs.gp_r11;
	dst->gcs_r12    = src->ucs_gpregs.gp_r12;
	dst->gcs_r13    = src->ucs_gpregs.gp_r13;
	dst->gcs_r14    = src->ucs_gpregs.gp_r14;
	dst->gcs_r15    = src->ucs_gpregs.gp_r15;
	dst->gcs_rip    = src->ucs_rip;
	dst->gcs_eflags = (__u32)src->ucs_rflags;
	dst->gcs_cs     = (__u32)src->ucs_cs16;
	dst->gcs_ss     = (__u32)src->ucs_ss16;
	dst->gcs_ds     = (__u32)src->ucs_sgregs.sg_ds16;
	dst->gcs_es     = (__u32)src->ucs_sgregs.sg_es16;
	dst->gcs_fs     = (__u32)src->ucs_sgregs.sg_fs16;
	dst->gcs_gs     = (__u32)src->ucs_sgregs.sg_gs16;
}

__LOCAL void
gdb_cpustate64_from_kcpustate64(struct gdb_cpustate64 *__restrict dst,
                                struct kcpustate64 const *__restrict src) {
	dst->gcs_rax    = src->kcs_gpregs.gp_rax;
	dst->gcs_rcx    = src->kcs_gpregs.gp_rcx;
	dst->gcs_rdx    = src->kcs_gpregs.gp_rdx;
	dst->gcs_rbx    = src->kcs_gpregs.gp_rbx;
	dst->gcs_rsp    = src->kcs_gpregs.gp_rsp;
	dst->gcs_rbp    = src->kcs_gpregs.gp_rbp;
	dst->gcs_rsi    = src->kcs_gpregs.gp_rsi;
	dst->gcs_rdi    = src->kcs_gpregs.gp_rdi;
	dst->gcs_r8     = src->kcs_gpregs.gp_r8;
	dst->gcs_r9     = src->kcs_gpregs.gp_r9;
	dst->gcs_r10    = src->kcs_gpregs.gp_r10;
	dst->gcs_r11    = src->kcs_gpregs.gp_r11;
	dst->gcs_r12    = src->kcs_gpregs.gp_r12;
	dst->gcs_r13    = src->kcs_gpregs.gp_r13;
	dst->gcs_r14    = src->kcs_gpregs.gp_r14;
	dst->gcs_r15    = src->kcs_gpregs.gp_r15;
	dst->gcs_rip    = src->kcs_rip;
	dst->gcs_eflags = (__u32)src->kcs_rflags;
	if (dst->gcs_rip >= KERNELSPACE_BASE) {
		dst->gcs_cs = SEGMENT_KERNEL_CODE;
		dst->gcs_ss = SEGMENT_KERNEL_DATA;
	} else {
		dst->gcs_cs = SEGMENT_USER_CODE_RPL;
		dst->gcs_ss = SEGMENT_USER_DATA_RPL;
	}
	dst->gcs_ds = SEGMENT_CURRENT_DATA_RPL;
	dst->gcs_es = SEGMENT_CURRENT_DATA_RPL;
	dst->gcs_fs = SEGMENT_CURRENT_DATA_RPL;
	dst->gcs_gs = SEGMENT_CURRENT_DATA_RPL;
}

__LOCAL void
gdb_cpustate64_from_lcpustate64(struct gdb_cpustate64 *__restrict dst,
                                struct lcpustate64 const *__restrict src) {
	dst->gcs_rax    = 0;
	dst->gcs_rcx    = 0;
	dst->gcs_rdx    = 0;
	dst->gcs_rbx    = src->lcs_rbx;
	dst->gcs_rsp    = src->lcs_rsp;
	dst->gcs_rbp    = src->lcs_rbp;
	dst->gcs_rsi    = 0;
	dst->gcs_rdi    = 0;
	dst->gcs_r8     = 0;
	dst->gcs_r9     = 0;
	dst->gcs_r10    = 0;
	dst->gcs_r11    = 0;
	dst->gcs_r12    = src->lcs_r12;
	dst->gcs_r13    = src->lcs_r13;
	dst->gcs_r14    = src->lcs_r14;
	dst->gcs_r15    = src->lcs_r15;
	dst->gcs_rip    = src->lcs_rip;
	dst->gcs_eflags = 0;
	if (dst->gcs_rip >= KERNELSPACE_BASE) {
		dst->gcs_cs = SEGMENT_KERNEL_CODE;
		dst->gcs_ss = SEGMENT_KERNEL_DATA;
	} else {
		dst->gcs_cs = SEGMENT_USER_CODE_RPL;
		dst->gcs_ss = SEGMENT_USER_DATA_RPL;
	}
	dst->gcs_ds = SEGMENT_CURRENT_DATA_RPL;
	dst->gcs_es = SEGMENT_CURRENT_DATA_RPL;
	dst->gcs_fs = SEGMENT_CURRENT_DATA_RPL;
	dst->gcs_gs = SEGMENT_CURRENT_DATA_RPL;
}

__LOCAL void
gdb_cpustate64_from_fcpustate64(struct gdb_cpustate64 *__restrict dst,
                                struct fcpustate64 const *__restrict src) {
	dst->gcs_rax    = src->fcs_gpregs.gp_rax;
	dst->gcs_rcx    = src->fcs_gpregs.gp_rcx;
	dst->gcs_rdx    = src->fcs_gpregs.gp_rdx;
	dst->gcs_rbx    = src->fcs_gpregs.gp_rbx;
	dst->gcs_rsp    = src->fcs_gpregs.gp_rsp;
	dst->gcs_rbp    = src->fcs_gpregs.gp_rbp;
	dst->gcs_rsi    = src->fcs_gpregs.gp_rsi;
	dst->gcs_rdi    = src->fcs_gpregs.gp_rdi;
	dst->gcs_r8     = src->fcs_gpregs.gp_r8;
	dst->gcs_r9     = src->fcs_gpregs.gp_r9;
	dst->gcs_r10    = src->fcs_gpregs.gp_r10;
	dst->gcs_r11    = src->fcs_gpregs.gp_r11;
	dst->gcs_r12    = src->fcs_gpregs.gp_r12;
	dst->gcs_r13    = src->fcs_gpregs.gp_r13;
	dst->gcs_r14    = src->fcs_gpregs.gp_r14;
	dst->gcs_r15    = src->fcs_gpregs.gp_r15;
	dst->gcs_rip    = src->fcs_rip;
	dst->gcs_eflags = (__u32)src->fcs_rflags;
	dst->gcs_cs     = (__u32)src->fcs_sgregs.sg_cs16;
	dst->gcs_ss     = (__u32)src->fcs_sgregs.sg_ss16;
	dst->gcs_ds     = (__u32)src->fcs_sgregs.sg_ds16;
	dst->gcs_es     = (__u32)src->fcs_sgregs.sg_es16;
	dst->gcs_fs     = (__u32)src->fcs_sgregs.sg_fs16;
	dst->gcs_gs     = (__u32)src->fcs_sgregs.sg_gs16;
}


__LOCAL struct icpustate64 *
gdb_cpustate64_to_icpustate64(struct icpustate64 *__restrict dst,
                              struct gdb_cpustate64 const *__restrict src) {
	dst->ics_gpregs.gp_rax    = src->gcs_rax;
	dst->ics_gpregs.gp_rcx    = src->gcs_rcx;
	dst->ics_gpregs.gp_rdx    = src->gcs_rdx;
	dst->ics_gpregs.gp_rbx    = src->gcs_rbx;
	dst->ics_irregs.ir_rsp    = src->gcs_rsp;
	dst->ics_gpregs.gp_rbp    = src->gcs_rbp;
	dst->ics_gpregs.gp_rsi    = src->gcs_rsi;
	dst->ics_gpregs.gp_rdi    = src->gcs_rdi;
	dst->ics_gpregs.gp_r8     = src->gcs_r8;
	dst->ics_gpregs.gp_r9     = src->gcs_r9;
	dst->ics_gpregs.gp_r10    = src->gcs_r10;
	dst->ics_gpregs.gp_r11    = src->gcs_r11;
	dst->ics_gpregs.gp_r12    = src->gcs_r12;
	dst->ics_gpregs.gp_r13    = src->gcs_r13;
	dst->ics_gpregs.gp_r14    = src->gcs_r14;
	dst->ics_gpregs.gp_r15    = src->gcs_r15;
	icpustate64_setrip(dst, src->gcs_rip);
	icpustate64_setrflags(dst, src->gcs_eflags);
	icpustate64_setcs(dst, src->gcs_cs);
	icpustate64_setss(dst, src->gcs_ss);
	return dst;
}

__LOCAL struct scpustate64 *
gdb_cpustate64_to_scpustate64(struct scpustate64 *__restrict dst,
                              struct gdb_cpustate64 const *__restrict src) {
	dst->scs_gpregs.gp_rax    = src->gcs_rax;
	dst->scs_gpregs.gp_rcx    = src->gcs_rcx;
	dst->scs_gpregs.gp_rdx    = src->gcs_rdx;
	dst->scs_gpregs.gp_rbx    = src->gcs_rbx;
	dst->scs_irregs.ir_rsp    = src->gcs_rsp;
	dst->scs_gpregs.gp_rbp    = src->gcs_rbp;
	dst->scs_gpregs.gp_rsi    = src->gcs_rsi;
	dst->scs_gpregs.gp_rdi    = src->gcs_rdi;
	dst->scs_gpregs.gp_r8     = src->gcs_r8;
	dst->scs_gpregs.gp_r9     = src->gcs_r9;
	dst->scs_gpregs.gp_r10    = src->gcs_r10;
	dst->scs_gpregs.gp_r11    = src->gcs_r11;
	dst->scs_gpregs.gp_r12    = src->gcs_r12;
	dst->scs_gpregs.gp_r13    = src->gcs_r13;
	dst->scs_gpregs.gp_r14    = src->gcs_r14;
	dst->scs_gpregs.gp_r15    = src->gcs_r15;
	dst->scs_irregs.ir_rip    = src->gcs_rip;
	dst->scs_irregs.ir_rflags = src->gcs_eflags;
	dst->scs_irregs.ir_cs     = src->gcs_cs;
	dst->scs_irregs.ir_ss     = src->gcs_ss;
	dst->scs_sgregs.sg_ds     = src->gcs_ds;
	dst->scs_sgregs.sg_es     = src->gcs_es;
	dst->scs_sgregs.sg_fs     = src->gcs_fs;
	dst->scs_sgregs.sg_gs     = src->gcs_gs;
	return dst;
}

__LOCAL struct ucpustate64 *
gdb_cpustate64_to_ucpustate64(struct ucpustate64 *__restrict dst,
                              struct gdb_cpustate64 const *__restrict src) {
	dst->ucs_gpregs.gp_rax = src->gcs_rax;
	dst->ucs_gpregs.gp_rcx = src->gcs_rcx;
	dst->ucs_gpregs.gp_rdx = src->gcs_rdx;
	dst->ucs_gpregs.gp_rbx = src->gcs_rbx;
	dst->ucs_gpregs.gp_rsp = src->gcs_rsp;
	dst->ucs_gpregs.gp_rbp = src->gcs_rbp;
	dst->ucs_gpregs.gp_rsi = src->gcs_rsi;
	dst->ucs_gpregs.gp_rdi = src->gcs_rdi;
	dst->ucs_gpregs.gp_r8  = src->gcs_r8;
	dst->ucs_gpregs.gp_r9  = src->gcs_r9;
	dst->ucs_gpregs.gp_r10 = src->gcs_r10;
	dst->ucs_gpregs.gp_r11 = src->gcs_r11;
	dst->ucs_gpregs.gp_r12 = src->gcs_r12;
	dst->ucs_gpregs.gp_r13 = src->gcs_r13;
	dst->ucs_gpregs.gp_r14 = src->gcs_r14;
	dst->ucs_gpregs.gp_r15 = src->gcs_r15;
	dst->ucs_rip           = src->gcs_rip;
	dst->ucs_rflags        = src->gcs_eflags;
	dst->ucs_cs            = src->gcs_cs;
	dst->ucs_ss            = src->gcs_ss;
	dst->ucs_sgregs.sg_ds  = src->gcs_ds;
	dst->ucs_sgregs.sg_es  = src->gcs_es;
	dst->ucs_sgregs.sg_fs  = src->gcs_fs;
	dst->ucs_sgregs.sg_gs  = src->gcs_gs;
	return dst;
}

__LOCAL struct kcpustate64 *
gdb_cpustate64_to_kcpustate64(struct kcpustate64 *__restrict dst,
                              struct gdb_cpustate64 const *__restrict src) {
	dst->kcs_gpregs.gp_rax = src->gcs_rax;
	dst->kcs_gpregs.gp_rcx = src->gcs_rcx;
	dst->kcs_gpregs.gp_rdx = src->gcs_rdx;
	dst->kcs_gpregs.gp_rbx = src->gcs_rbx;
	dst->kcs_gpregs.gp_rsp = src->gcs_rsp;
	dst->kcs_gpregs.gp_rbp = src->gcs_rbp;
	dst->kcs_gpregs.gp_rsi = src->gcs_rsi;
	dst->kcs_gpregs.gp_rdi = src->gcs_rdi;
	dst->kcs_gpregs.gp_r8  = src->gcs_r8;
	dst->kcs_gpregs.gp_r9  = src->gcs_r9;
	dst->kcs_gpregs.gp_r10 = src->gcs_r10;
	dst->kcs_gpregs.gp_r11 = src->gcs_r11;
	dst->kcs_gpregs.gp_r12 = src->gcs_r12;
	dst->kcs_gpregs.gp_r13 = src->gcs_r13;
	dst->kcs_gpregs.gp_r14 = src->gcs_r14;
	dst->kcs_gpregs.gp_r15 = src->gcs_r15;
	dst->kcs_rip           = src->gcs_rip;
	dst->kcs_rflags        = src->gcs_eflags;
	return dst;
}

__LOCAL struct lcpustate64 *
gdb_cpustate64_to_lcpustate64(struct lcpustate64 *__restrict dst,
                              struct gdb_cpustate64 const *__restrict src) {
	dst->lcs_rbx = src->gcs_rbx;
	dst->lcs_rsp = src->gcs_rsp;
	dst->lcs_rbp = src->gcs_rbp;
	dst->lcs_r12 = src->gcs_r12;
	dst->lcs_r13 = src->gcs_r13;
	dst->lcs_r14 = src->gcs_r14;
	dst->lcs_r15 = src->gcs_r15;
	dst->lcs_rip = src->gcs_rip;
	return dst;
}

__LOCAL struct fcpustate64 *
gdb_cpustate64_to_fcpustate64(struct fcpustate64 *__restrict dst,
                              struct gdb_cpustate64 const *__restrict src) {
	dst->fcs_gpregs.gp_rax = src->gcs_rax;
	dst->fcs_gpregs.gp_rcx = src->gcs_rcx;
	dst->fcs_gpregs.gp_rdx = src->gcs_rdx;
	dst->fcs_gpregs.gp_rbx = src->gcs_rbx;
	dst->fcs_gpregs.gp_rsp = src->gcs_rsp;
	dst->fcs_gpregs.gp_rbp = src->gcs_rbp;
	dst->fcs_gpregs.gp_rsi = src->gcs_rsi;
	dst->fcs_gpregs.gp_rdi = src->gcs_rdi;
	dst->fcs_gpregs.gp_r8  = src->gcs_r8;
	dst->fcs_gpregs.gp_r9  = src->gcs_r9;
	dst->fcs_gpregs.gp_r10 = src->gcs_r10;
	dst->fcs_gpregs.gp_r11 = src->gcs_r11;
	dst->fcs_gpregs.gp_r12 = src->gcs_r12;
	dst->fcs_gpregs.gp_r13 = src->gcs_r13;
	dst->fcs_gpregs.gp_r14 = src->gcs_r14;
	dst->fcs_gpregs.gp_r15 = src->gcs_r15;
	dst->fcs_rip           = src->gcs_rip;
	dst->fcs_rflags        = src->gcs_eflags;
	dst->fcs_sgregs.sg_cs  = src->gcs_cs;
	dst->fcs_sgregs.sg_ss  = src->gcs_ss;
	dst->fcs_sgregs.sg_ds  = src->gcs_ds;
	dst->fcs_sgregs.sg_es  = src->gcs_es;
	dst->fcs_sgregs.sg_fs  = src->gcs_fs;
	dst->fcs_sgregs.sg_gs  = src->gcs_gs;
	return dst;
}



#endif /* !__INTELLISENSE__ */


#endif /* __CC__ */


__SYSDECL_END

#endif /* !_I386_KOS_KOS_KERNEL_GDB_CPU_STATE64_H */
