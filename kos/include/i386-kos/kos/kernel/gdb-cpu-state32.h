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
#ifndef _I386_KOS_KOS_KERNEL_GDB_CPU_STATE32_H
#define _I386_KOS_KOS_KERNEL_GDB_CPU_STATE32_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <kos/anno.h>
#include <bits/types.h>
#include <hybrid/host.h>
#include <kos/kernel/cpu-state32.h>

#if !defined(__INTELLISENSE__)
#include <kos/kernel/cpu-state-helpers32.h>
#include <asm/cpu-flags.h>
#include <asm/intrin.h>

#ifdef __KERNEL__
#include <sched/arch/task.h>
#endif /* __KERNEL__ */
#endif /* !__INTELLISENSE__ */

__SYSDECL_BEGIN

#if defined(__i386__) && !defined(__x86_64__)
#define GDB_REGISTER_MAXSIZE GDB_REGISTER_I386_MAXSIZE
#define GDB_REGISTER_PC      GDB_REGISTER_I386_EIP
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
#define GDB_REGISTER_I386_FPUCS  0x1b /* fs_fcs (fiseg) */
#define GDB_REGISTER_I386_FPUIP  0x1c /* fs_fip (fioff) */
#define GDB_REGISTER_I386_FPUDS  0x1d /* fs_fds (foseg) */
#define GDB_REGISTER_I386_FPUDP  0x1e /* fs_fdp (fooff) */
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


#ifdef __CC__

#ifndef __x86_64__
#define gdb_cpustate32              gdb_cpustate
#define GDB_CPUSTATE_PC             GDB_CPUSTATE32_PC
#define GDB_CPUSTATE_SP             GDB_CPUSTATE32_SP
#define gdb_cpustate_from_icpustate gdb_cpustate32_from_icpustate32
#define gdb_cpustate_from_scpustate gdb_cpustate32_from_scpustate32
#define gdb_cpustate_from_ucpustate gdb_cpustate32_from_ucpustate32
#define gdb_cpustate_from_kcpustate gdb_cpustate32_from_kcpustate32
#define gdb_cpustate_from_lcpustate gdb_cpustate32_from_lcpustate32
#define gdb_cpustate_from_fcpustate gdb_cpustate32_from_fcpustate32
#define gdb_cpustate_to_icpustate   gdb_cpustate32_to_icpustate32
#define gdb_cpustate_to_scpustate   gdb_cpustate32_to_scpustate32
#define gdb_cpustate_to_ucpustate   gdb_cpustate32_to_ucpustate32
#define gdb_cpustate_to_kcpustate   gdb_cpustate32_to_kcpustate32
#define gdb_cpustate_to_lcpustate   gdb_cpustate32_to_lcpustate32
#define gdb_cpustate_to_fcpustate   gdb_cpustate32_to_fcpustate32
#endif /* !__x86_64__ */

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

#define GDB_CPUSTATE32_PC(x) ((x).gcs_eip)
#define GDB_CPUSTATE32_SP(x) ((x).gcs_esp)

struct icpustate32;
struct scpustate32;
struct ucpustate32;
struct kcpustate32;
struct lcpustate32;
struct fcpustate32;

/* Convert between GDB cpu states and other states used by the system. */
__LOCAL void gdb_cpustate32_from_icpustate32(struct gdb_cpustate32 *__restrict dst, struct icpustate32 const *__restrict src);
__LOCAL void gdb_cpustate32_from_scpustate32(struct gdb_cpustate32 *__restrict dst, struct scpustate32 const *__restrict src);
__LOCAL void gdb_cpustate32_from_ucpustate32(struct gdb_cpustate32 *__restrict dst, struct ucpustate32 const *__restrict src);
__LOCAL void gdb_cpustate32_from_kcpustate32(struct gdb_cpustate32 *__restrict dst, struct kcpustate32 const *__restrict src);
__LOCAL void gdb_cpustate32_from_lcpustate32(struct gdb_cpustate32 *__restrict dst, struct lcpustate32 const *__restrict src);
__LOCAL void gdb_cpustate32_from_fcpustate32(struct gdb_cpustate32 *__restrict dst, struct fcpustate32 const *__restrict src);
__LOCAL struct icpustate32 *gdb_cpustate32_to_icpustate32(struct icpustate32 *__restrict dst, struct gdb_cpustate32 const *__restrict src) __THROWS(E_SEGFAULT);
__LOCAL struct scpustate32 *gdb_cpustate32_to_scpustate32(struct scpustate32 *__restrict dst, struct gdb_cpustate32 const *__restrict src) __THROWS(E_SEGFAULT);
__LOCAL struct ucpustate32 *gdb_cpustate32_to_ucpustate32(struct ucpustate32 *__restrict dst, struct gdb_cpustate32 const *__restrict src);
__LOCAL struct kcpustate32 *gdb_cpustate32_to_kcpustate32(struct kcpustate32 *__restrict dst, struct gdb_cpustate32 const *__restrict src);
__LOCAL struct lcpustate32 *gdb_cpustate32_to_lcpustate32(struct lcpustate32 *__restrict dst, struct gdb_cpustate32 const *__restrict src);
__LOCAL struct fcpustate32 *gdb_cpustate32_to_fcpustate32(struct fcpustate32 *__restrict dst, struct gdb_cpustate32 const *__restrict src);


#if !defined(__INTELLISENSE__)
__LOCAL void
gdb_cpustate32_from_icpustate32(struct gdb_cpustate32 *__restrict dst,
                                struct icpustate32 const *__restrict src) {
	dst->gcs_eax    = src->ics_gpregs.gp_eax;
	dst->gcs_ecx    = src->ics_gpregs.gp_ecx;
	dst->gcs_edx    = src->ics_gpregs.gp_edx;
	dst->gcs_ebx    = src->ics_gpregs.gp_ebx;
	dst->gcs_esp    = icpustate32_getesp(src);
	dst->gcs_ebp    = src->ics_gpregs.gp_ebp;
	dst->gcs_esi    = src->ics_gpregs.gp_esi;
	dst->gcs_edi    = src->ics_gpregs.gp_edi;
	dst->gcs_eip    = icpustate32_geteip(src);
	dst->gcs_eflags = icpustate32_geteflags(src);
	dst->gcs_cs     = icpustate32_getcs(src);
	dst->gcs_ss     = icpustate32_getss(src);
	dst->gcs_ds     = icpustate32_getds(src);
	dst->gcs_es     = icpustate32_getes(src);
	dst->gcs_fs     = icpustate32_getfs(src);
	dst->gcs_gs     = icpustate32_getgs(src);
}

__LOCAL void
gdb_cpustate32_from_scpustate32(struct gdb_cpustate32 *__restrict dst,
                                struct scpustate32 const *__restrict src) {
	dst->gcs_eax    = src->scs_gpregs.gp_eax;
	dst->gcs_ecx    = src->scs_gpregs.gp_ecx;
	dst->gcs_edx    = src->scs_gpregs.gp_edx;
	dst->gcs_ebx    = src->scs_gpregs.gp_ebx;
	dst->gcs_esp    = scpustate32_getesp(src);
	dst->gcs_ebp    = src->scs_gpregs.gp_ebp;
	dst->gcs_esi    = src->scs_gpregs.gp_esi;
	dst->gcs_edi    = src->scs_gpregs.gp_edi;
	dst->gcs_eip    = src->scs_irregs_k.ir_eip;
	dst->gcs_eflags = src->scs_irregs_k.ir_eflags;
	dst->gcs_cs     = src->scs_irregs_k.ir_cs16;
	dst->gcs_ss     = scpustate32_getss(src);
	dst->gcs_ds     = scpustate32_getds(src);
	dst->gcs_es     = scpustate32_getes(src);
	dst->gcs_fs     = scpustate32_getfs(src);
	dst->gcs_gs     = scpustate32_getgs(src);
}

__LOCAL void
gdb_cpustate32_from_ucpustate32(struct gdb_cpustate32 *__restrict dst,
                                struct ucpustate32 const *__restrict src) {
	dst->gcs_eax    = src->ucs_gpregs.gp_eax;
	dst->gcs_ecx    = src->ucs_gpregs.gp_ecx;
	dst->gcs_edx    = src->ucs_gpregs.gp_edx;
	dst->gcs_ebx    = src->ucs_gpregs.gp_ebx;
	dst->gcs_esp    = src->ucs_gpregs.gp_esp;
	dst->gcs_ebp    = src->ucs_gpregs.gp_ebp;
	dst->gcs_esi    = src->ucs_gpregs.gp_esi;
	dst->gcs_edi    = src->ucs_gpregs.gp_edi;
	dst->gcs_eip    = src->ucs_eip;
	dst->gcs_eflags = src->ucs_eflags;
	dst->gcs_cs     = src->ucs_cs16;
	dst->gcs_ss     = src->ucs_ss16;
	dst->gcs_ds     = src->ucs_sgregs.sg_ds16;
	dst->gcs_es     = src->ucs_sgregs.sg_es16;
	dst->gcs_fs     = src->ucs_sgregs.sg_fs16;
	dst->gcs_gs     = src->ucs_sgregs.sg_gs16;
}

__LOCAL void
gdb_cpustate32_from_kcpustate32(struct gdb_cpustate32 *__restrict dst,
                                struct kcpustate32 const *__restrict src) {
	dst->gcs_eax    = src->kcs_gpregs.gp_eax;
	dst->gcs_ecx    = src->kcs_gpregs.gp_ecx;
	dst->gcs_edx    = src->kcs_gpregs.gp_edx;
	dst->gcs_ebx    = src->kcs_gpregs.gp_ebx;
	dst->gcs_esp    = src->kcs_gpregs.gp_esp;
	dst->gcs_ebp    = src->kcs_gpregs.gp_ebp;
	dst->gcs_esi    = src->kcs_gpregs.gp_esi;
	dst->gcs_edi    = src->kcs_gpregs.gp_edi;
	dst->gcs_eip    = src->kcs_eip;
	dst->gcs_eflags = src->kcs_eflags;
	dst->gcs_cs     = SEGMENT_KERNEL_CODE;
	dst->gcs_ss     = SEGMENT_KERNEL_DATA;
	dst->gcs_ds     = __rdds();
	dst->gcs_es     = __rdes();
	dst->gcs_fs     = __rdfs();
	dst->gcs_gs     = __rdgs();
}

__LOCAL void
gdb_cpustate32_from_lcpustate32(struct gdb_cpustate32 *__restrict dst,
                                struct lcpustate32 const *__restrict src) {
	dst->gcs_eax    = 0;
	dst->gcs_ecx    = 0;
	dst->gcs_edx    = 0;
	dst->gcs_ebx    = src->lcs_ebx;
	dst->gcs_esp    = src->lcs_esp;
	dst->gcs_ebp    = src->lcs_ebp;
	dst->gcs_esi    = src->lcs_esi;
	dst->gcs_edi    = src->lcs_edi;
	dst->gcs_eip    = src->lcs_eip;
	dst->gcs_eflags = __rdflags();
	dst->gcs_cs     = SEGMENT_KERNEL_CODE;
	dst->gcs_ss     = SEGMENT_KERNEL_DATA;
	dst->gcs_ds     = __rdds();
	dst->gcs_es     = __rdes();
	dst->gcs_fs     = __rdfs();
	dst->gcs_gs     = __rdgs();
}

__LOCAL void
gdb_cpustate32_from_fcpustate32(struct gdb_cpustate32 *__restrict dst,
                                struct fcpustate32 const *__restrict src) {
	dst->gcs_eax    = src->fcs_gpregs.gp_eax;
	dst->gcs_ecx    = src->fcs_gpregs.gp_ecx;
	dst->gcs_edx    = src->fcs_gpregs.gp_edx;
	dst->gcs_ebx    = src->fcs_gpregs.gp_ebx;
	dst->gcs_esp    = src->fcs_gpregs.gp_esp;
	dst->gcs_ebp    = src->fcs_gpregs.gp_ebp;
	dst->gcs_esi    = src->fcs_gpregs.gp_esi;
	dst->gcs_edi    = src->fcs_gpregs.gp_edi;
	dst->gcs_eip    = src->fcs_eip;
	dst->gcs_eflags = src->fcs_eflags;
	dst->gcs_cs     = src->fcs_sgregs.sg_cs16;
	dst->gcs_ss     = src->fcs_sgregs.sg_ss16;
	dst->gcs_ds     = src->fcs_sgregs.sg_ds16;
	dst->gcs_es     = src->fcs_sgregs.sg_es16;
	dst->gcs_fs     = src->fcs_sgregs.sg_fs16;
	dst->gcs_gs     = src->fcs_sgregs.sg_gs16;
}


__LOCAL struct icpustate32 *
gdb_cpustate32_to_icpustate32(struct icpustate32 *__restrict dst,
                              struct gdb_cpustate32 const *__restrict src) __THROWS(E_SEGFAULT) {
	struct icpustate32 *result = dst;
	if (!(src->gcs_eflags & EFLAGS_VM) && !(src->gcs_cs & 3)) {
		result = (struct icpustate32 *)((src->gcs_esp) -
		                              (OFFSET_ICPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL));
	}
	result->ics_gpregs.gp_eax      = src->gcs_eax;
	result->ics_gpregs.gp_ecx      = src->gcs_ecx;
	result->ics_gpregs.gp_edx      = src->gcs_edx;
	result->ics_gpregs.gp_ebx      = src->gcs_ebx;
	result->ics_gpregs.gp_ebp      = src->gcs_ebp;
	result->ics_gpregs.gp_esi      = src->gcs_esi;
	result->ics_gpregs.gp_edi      = src->gcs_edi;
	result->ics_fs                 = src->gcs_fs;
	result->ics_es                 = src->gcs_es;
	result->ics_ds                 = src->gcs_ds;
	icpustate32_seteip(result, src->gcs_eip);
	icpustate32_seteflags(result,src->gcs_eflags);
	icpustate32_setcs(result, src->gcs_cs);
	if (src->gcs_eflags & EFLAGS_VM) {
		result->ics_irregs_v.ir_esp = src->gcs_esp;
		result->ics_irregs_v.ir_ss  = src->gcs_ss;
		result->ics_irregs_v.ir_es  = src->gcs_es;
		result->ics_irregs_v.ir_ds  = src->gcs_ds;
		result->ics_irregs_v.ir_fs  = src->gcs_fs;
		result->ics_irregs_v.ir_gs  = src->gcs_gs;
	} else {
		if (src->gcs_cs & 3) {
			result->ics_irregs_u.ir_ss  = src->gcs_ss;
			result->ics_irregs_u.ir_esp = src->gcs_esp;
		}
		/* Reload GS if it has changed. */
		if (src->gcs_gs != __rdgs())
			__wrgs(src->gcs_gs);
	}
	return result;
}

__LOCAL struct scpustate32 *
gdb_cpustate32_to_scpustate32(struct scpustate32 *__restrict dst,
                              struct gdb_cpustate32 const *__restrict src) __THROWS(E_SEGFAULT) {
	struct scpustate32 *result = dst;
	if (!(src->gcs_eflags & EFLAGS_VM) && !(src->gcs_cs & 3)) {
		result = (struct scpustate32 *)((src->gcs_esp) -
		                                (OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL));
	}
	result->scs_gpregs.gp_eax      = src->gcs_eax;
	result->scs_gpregs.gp_ecx      = src->gcs_ecx;
	result->scs_gpregs.gp_edx      = src->gcs_edx;
	result->scs_gpregs.gp_ebx      = src->gcs_ebx;
	result->scs_gpregs.gp_ebp      = src->gcs_ebp;
	result->scs_gpregs.gp_esi      = src->gcs_esi;
	result->scs_gpregs.gp_edi      = src->gcs_edi;
	result->scs_sgregs.sg_gs       = src->gcs_gs;
	result->scs_sgregs.sg_fs       = src->gcs_fs;
	result->scs_sgregs.sg_es       = src->gcs_es;
	result->scs_sgregs.sg_ds       = src->gcs_ds;
	result->scs_irregs_k.ir_eip    = src->gcs_eip;
	result->scs_irregs_k.ir_eflags = src->gcs_eflags;
	result->scs_irregs_k.ir_cs     = src->gcs_cs;
	if (src->gcs_eflags & EFLAGS_VM) {
		result->scs_irregs_v.ir_esp = src->gcs_esp;
		result->scs_irregs_v.ir_ss  = src->gcs_ss;
		result->scs_irregs_v.ir_es  = src->gcs_es;
		result->scs_irregs_v.ir_ds  = src->gcs_ds;
		result->scs_irregs_v.ir_fs  = src->gcs_fs;
		result->scs_irregs_v.ir_gs  = src->gcs_gs;
	} else if (src->gcs_cs & 3) {
		result->scs_irregs_u.ir_ss  = src->gcs_ss;
		result->scs_irregs_u.ir_esp = src->gcs_esp;
	}
	return result;
}

__LOCAL struct ucpustate32 *
gdb_cpustate32_to_ucpustate32(struct ucpustate32 *__restrict dst,
                              struct gdb_cpustate32 const *__restrict src) {
	dst->ucs_gpregs.gp_eax = src->gcs_eax;
	dst->ucs_gpregs.gp_ecx = src->gcs_ecx;
	dst->ucs_gpregs.gp_edx = src->gcs_edx;
	dst->ucs_gpregs.gp_ebx = src->gcs_ebx;
	dst->ucs_gpregs.gp_esp = src->gcs_esp;
	dst->ucs_gpregs.gp_ebp = src->gcs_ebp;
	dst->ucs_gpregs.gp_esi = src->gcs_esi;
	dst->ucs_gpregs.gp_edi = src->gcs_edi;
	dst->ucs_eip           = src->gcs_eip;
	dst->ucs_eflags        = src->gcs_eflags;
	dst->ucs_cs            = src->gcs_cs;
	dst->ucs_ss            = src->gcs_ss;
	dst->ucs_sgregs.sg_ds  = src->gcs_ds;
	dst->ucs_sgregs.sg_es  = src->gcs_es;
	dst->ucs_sgregs.sg_fs  = src->gcs_fs;
	dst->ucs_sgregs.sg_gs  = src->gcs_gs;
	return dst;
}

__LOCAL struct kcpustate32 *
gdb_cpustate32_to_kcpustate32(struct kcpustate32 *__restrict dst,
                              struct gdb_cpustate32 const *__restrict src) {
	dst->kcs_gpregs.gp_eax = src->gcs_eax;
	dst->kcs_gpregs.gp_ecx = src->gcs_ecx;
	dst->kcs_gpregs.gp_edx = src->gcs_edx;
	dst->kcs_gpregs.gp_ebx = src->gcs_ebx;
	dst->kcs_gpregs.gp_esp = src->gcs_esp;
	dst->kcs_gpregs.gp_ebp = src->gcs_ebp;
	dst->kcs_gpregs.gp_esi = src->gcs_esi;
	dst->kcs_gpregs.gp_edi = src->gcs_edi;
	dst->kcs_eip           = src->gcs_eip;
	dst->kcs_eflags        = src->gcs_eflags;
	if __unlikely(src->gcs_cs != SEGMENT_KERNEL_CODE)
		__wrcs(src->gcs_cs);
	if __unlikely(src->gcs_cs != SEGMENT_KERNEL_DATA)
		__wrss(src->gcs_ss);
	__wrds(src->gcs_ds);
	__wres(src->gcs_es);
	__wrfs(src->gcs_fs);
	__wrgs(src->gcs_gs);
	return dst;
}

__LOCAL struct lcpustate32 *
gdb_cpustate32_to_lcpustate32(struct lcpustate32 *__restrict dst,
                              struct gdb_cpustate32 const *__restrict src) {
	dst->lcs_edi = src->gcs_edi;
	dst->lcs_esi = src->gcs_esi;
	dst->lcs_ebp = src->gcs_ebp;
	dst->lcs_esp = src->gcs_esp;
	dst->lcs_ebx = src->gcs_ebx;
	dst->lcs_eip = src->gcs_eip;
	if __unlikely(src->gcs_cs != SEGMENT_KERNEL_CODE)
		__wrcs(src->gcs_cs);
	if __unlikely(src->gcs_cs != SEGMENT_KERNEL_DATA)
		__wrss(src->gcs_ss);
	__wrds(src->gcs_ds);
	__wres(src->gcs_es);
	__wrfs(src->gcs_fs);
	__wrgs(src->gcs_gs);
	return dst;
}

__LOCAL struct fcpustate32 *
gdb_cpustate32_to_fcpustate32(struct fcpustate32 *__restrict dst,
                              struct gdb_cpustate32 const *__restrict src) {
	dst->fcs_gpregs.gp_eax = src->gcs_eax;
	dst->fcs_gpregs.gp_ecx = src->gcs_ecx;
	dst->fcs_gpregs.gp_edx = src->gcs_edx;
	dst->fcs_gpregs.gp_ebx = src->gcs_ebx;
	dst->fcs_gpregs.gp_esp = src->gcs_esp;
	dst->fcs_gpregs.gp_ebp = src->gcs_ebp;
	dst->fcs_gpregs.gp_esi = src->gcs_esi;
	dst->fcs_gpregs.gp_edi = src->gcs_edi;
	dst->fcs_eip           = src->gcs_eip;
	dst->fcs_eflags        = src->gcs_eflags;
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

#endif /* !_I386_KOS_KOS_KERNEL_GDB_CPU_STATE32_H */
