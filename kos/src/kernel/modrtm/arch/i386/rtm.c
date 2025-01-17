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
#ifndef GUARD_MODRTM_ARCH_I386_RTM_C
#define GUARD_MODRTM_ARCH_I386_RTM_C 1
#define DISABLE_BRANCH_PROFILING

#include <hybrid/host.h>

#ifdef __x86_64__
#define LIBEMU86_CONFIG_WANT_16BIT 0
#define LIBEMU86_CONFIG_WANT_32BIT 1
#define LIBEMU86_CONFIG_WANT_64BIT 1
#else /* __x86_64__ */
#define LIBEMU86_CONFIG_WANT_16BIT 1
#define LIBEMU86_CONFIG_WANT_32BIT 1
#define LIBEMU86_CONFIG_WANT_64BIT 0
#endif /* !__x86_64__ */

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/user.h>
#include <kernel/x86/gdt.h>
#include <sched/cpu.h>
#include <sched/rpc.h>

#include <hybrid/sched/preemption.h>

#include <asm/cpu-flags.h>
#include <asm/cpu-msr.h>
#include <asm/intrin.h>
#include <asm/rtm.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <errno.h>
#include <int128.h>
#include <inttypes.h>
#include <stddef.h> /* UINT32_C */
#include <stdint.h> /* UINT32_C */
#include <string.h>

#include <libemu86/emu86.h>

#include "../../memory.h"
#include "../../rtm.h"

/* System call numbers */
#include <syscall.h>
#ifdef __x86_64__
#include <asm/syscalls32_d.h>
#endif /* __x86_64__ */

#undef HAVE_RTM_EMULATION_TRACE
#if !defined(NDEBUG) && 0
#define HAVE_RTM_EMULATION_TRACE 1
#include <kernel/printk.h>
#include <kernel/syslog.h>

#include <libdisasm/disassembler.h>
#endif /* !NDEBUG */

DECL_BEGIN

/* Configure general library implementation */
#define EMU86_EMULATE_CONFIG_ONLY_MEMORY              0 /* Emulate all instructions (as opposed to only those that access memory) */
#define EMU86_EMULATE_CONFIG_CHECKUSER                1 /* Restrict system instructions in user-space */
#define EMU86_EMULATE_CONFIG_CHECKERROR               0 /* Disabled instruction don't need to be checked for errors */
#define EMU86_EMULATE_CONFIG_ONLY_CHECKERROR          1 /* Default: Any instruction not explicitly configured defaults to `#define EMU86_EMULATE_CONFIG_WANT_... 0' */
#define EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC 1 /* Don't include code-paths for basic instructions that are assumed to always be available */
#define EMU86_EMULATE_CONFIG_CHECKLOCK                1 /* We don't actually care about lock prefixes, but we must still
                                                         * assert  that they're only  used on white-listed instructions. */
#define EMU86_EMULATE_CONFIG_IGNORE_LOCK              1 /* Lock prefixes  don't mean  anything in  RTM mode,  since all  modifications
                                                         * that  may possible  be made to  memory will instead  appear in thread-local
                                                         * caches, meaning that having special handling for atomic instruction doesn't
                                                         * make any sense. */
#define EMU86_EMULATE_CONFIG_ALLOW_USER_STAC_CLAC     1 /* Allow user-space to make use of stac/clac */

/* Configure ISA extensions */
#ifdef CONFIG_X86ISA_ENABLE_LOCK_EXTENSIONS
#define EMU86_EMULATE_CONFIG_LOCK_SHIFT  1 /* [enabled] Accept `lock' for shl/shr/sal/sar/rol/ror/rcl/rcr */
#define EMU86_EMULATE_CONFIG_LOCK_SHIFT2 1 /* [enabled] Accept `lock' for shld/shrd */
#define EMU86_EMULATE_CONFIG_LOCK_ARPL   1 /* [enabled] Accept `lock' for arpl */
#else /* CONFIG_X86ISA_ENABLE_LOCK_EXTENSIONS */
#define EMU86_EMULATE_CONFIG_LOCK_SHIFT  0 /* [not enabled] Accept `lock' for shl/shr/sal/sar/rol/ror/rcl/rcr */
#define EMU86_EMULATE_CONFIG_LOCK_SHIFT2 0 /* [not enabled] Accept `lock' for shld/shrd */
#define EMU86_EMULATE_CONFIG_LOCK_ARPL   0 /* [not enabled] Accept `lock' for arpl */
#endif /* !CONFIG_X86ISA_ENABLE_LOCK_EXTENSIONS */

/* Configure instructions */
#define EMU86_EMULATE_CONFIG_WANT_ADCX          1
#define EMU86_EMULATE_CONFIG_WANT_ADOX          1
#define EMU86_EMULATE_CONFIG_WANT_MULX          1
#define EMU86_EMULATE_CONFIG_WANT_ANDN          1
#define EMU86_EMULATE_CONFIG_WANT_ARITH         1
#define EMU86_EMULATE_CONFIG_WANT_ARITH2        1
#define EMU86_EMULATE_CONFIG_WANT_DAA           1
#define EMU86_EMULATE_CONFIG_WANT_DAS           1
#define EMU86_EMULATE_CONFIG_WANT_AAA           1
#define EMU86_EMULATE_CONFIG_WANT_AAM           1
#define EMU86_EMULATE_CONFIG_WANT_AAD           1
#define EMU86_EMULATE_CONFIG_WANT_TZCNT         1
#define EMU86_EMULATE_CONFIG_WANT_BSF           1
#define EMU86_EMULATE_CONFIG_WANT_LZCNT         1
#define EMU86_EMULATE_CONFIG_WANT_BSR           1
#define EMU86_EMULATE_CONFIG_WANT_BITTEST       1
#define EMU86_EMULATE_CONFIG_WANT_BLSR          1
#define EMU86_EMULATE_CONFIG_WANT_BLSMSK        1
#define EMU86_EMULATE_CONFIG_WANT_BLSI          1
#define EMU86_EMULATE_CONFIG_WANT_BOUND         1
#define EMU86_EMULATE_CONFIG_WANT_BSWAP         1
#define EMU86_EMULATE_CONFIG_WANT_CALL          1
#define EMU86_EMULATE_CONFIG_WANT_CBW           1
#define EMU86_EMULATE_CONFIG_WANT_CWD           1
#define EMU86_EMULATE_CONFIG_WANT_CLTS          0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_SETCC         1
#define EMU86_EMULATE_CONFIG_WANT_CMOVCC        1
#define EMU86_EMULATE_CONFIG_WANT_CMPS          1
#define EMU86_EMULATE_CONFIG_WANT_CMPXCHG       1
#define EMU86_EMULATE_CONFIG_WANT_CMPXCHG8B     1
#define EMU86_EMULATE_CONFIG_WANT_CMPXCHG16B    1
#define EMU86_EMULATE_CONFIG_WANT_CPUID         1 /* Emulated with the real cpuid instruction */
#define EMU86_EMULATE_CONFIG_WANT_ENTER         1
#define EMU86_EMULATE_CONFIG_WANT_INVD          1
#define EMU86_EMULATE_CONFIG_WANT_WBINVD        1
#define EMU86_EMULATE_CONFIG_WANT_PREFETCHW     1
#define EMU86_EMULATE_CONFIG_WANT_PREFETCHNTA   1
#define EMU86_EMULATE_CONFIG_WANT_PREFETCH0     1
#define EMU86_EMULATE_CONFIG_WANT_PREFETCH1     1
#define EMU86_EMULATE_CONFIG_WANT_PREFETCH2     1
#define EMU86_EMULATE_CONFIG_WANT_CLDEMOTE      1
#define EMU86_EMULATE_CONFIG_WANT_HLT           0 /* Not allowed! */
#define EMU86_EMULATE_CONFIG_WANT_INC_REG       1
#define EMU86_EMULATE_CONFIG_WANT_DEC_REG       1
#define EMU86_EMULATE_CONFIG_WANT_INT1          0 /* Not allowed! */
#define EMU86_EMULATE_CONFIG_WANT_INT3          1 /* Requires special handling! (s.a. `_XABORT_DEBUG') */
#define EMU86_EMULATE_CONFIG_WANT_INT           1 /* Requires special handling! (restricted syscall emulation) */
#define EMU86_EMULATE_CONFIG_WANT_INTO          1 /* Requires special handling! */
#define EMU86_EMULATE_CONFIG_WANT_IO            0 /* Not allowed! */
#define EMU86_EMULATE_CONFIG_WANT_IRET          1 /* Not allowed to change segment register! */
#define EMU86_EMULATE_CONFIG_WANT_JCC_DISP8     1
#define EMU86_EMULATE_CONFIG_WANT_JCC_DISP32    1
#define EMU86_EMULATE_CONFIG_WANT_JCXZ          1
#define EMU86_EMULATE_CONFIG_WANT_JMP_DISP8     1
#define EMU86_EMULATE_CONFIG_WANT_JMP_DISP32    1
#define EMU86_EMULATE_CONFIG_WANT_LCALL         1 /* Not allowed to change segment register! */
#define EMU86_EMULATE_CONFIG_WANT_LEA           1
#define EMU86_EMULATE_CONFIG_WANT_LEAVE         1
#define EMU86_EMULATE_CONFIG_WANT_LJMP          1 /* Not allowed to change segment register! */
#define EMU86_EMULATE_CONFIG_WANT_LODS          1
#define EMU86_EMULATE_CONFIG_WANT_LOOPNE        1
#define EMU86_EMULATE_CONFIG_WANT_LOOPE         1
#define EMU86_EMULATE_CONFIG_WANT_LOOP          1
#define EMU86_EMULATE_CONFIG_WANT_LRET          1 /* Not allowed to change segment register! */
#define EMU86_EMULATE_CONFIG_WANT_LXS           1 /* Not allowed to change segment register! */
#define EMU86_EMULATE_CONFIG_WANT_INC_RM        1
#define EMU86_EMULATE_CONFIG_WANT_DEC_RM        1
#define EMU86_EMULATE_CONFIG_WANT_CALL_RM       1
#define EMU86_EMULATE_CONFIG_WANT_LCALL_RM      1 /* Not allowed to change segment register! */
#define EMU86_EMULATE_CONFIG_WANT_JMP_RM        1
#define EMU86_EMULATE_CONFIG_WANT_LJMP_RM       1 /* Not allowed to change segment register! */
#define EMU86_EMULATE_CONFIG_WANT_PUSH_RM       1
#define EMU86_EMULATE_CONFIG_WANT_RDFSBASE      1
#define EMU86_EMULATE_CONFIG_WANT_RDGSBASE      1
#define EMU86_EMULATE_CONFIG_WANT_WRFSBASE      0 /* Not allowed! (changing segment bases is too complex) */
#define EMU86_EMULATE_CONFIG_WANT_WRGSBASE      0 /* Not allowed! (changing segment bases is too complex) */
#define EMU86_EMULATE_CONFIG_WANT_CLWB          1
#define EMU86_EMULATE_CONFIG_WANT_CLFLUSH       1
#define EMU86_EMULATE_CONFIG_WANT_CLFLUSHOPT    1
#define EMU86_EMULATE_CONFIG_WANT_LFENCE        1
#define EMU86_EMULATE_CONFIG_WANT_SFENCE        1
#define EMU86_EMULATE_CONFIG_WANT_MFENCE        1
#define EMU86_EMULATE_CONFIG_WANT_TPAUSE        0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_STMXCSR       0 /* Not allowed! (fpu is too complex (for now)) */
#define EMU86_EMULATE_CONFIG_WANT_LDMXCSR       0 /* Not allowed! (fpu is too complex (for now)) */
#define EMU86_EMULATE_CONFIG_WANT_MOV_RM        1
#define EMU86_EMULATE_CONFIG_WANT_MOVBE         1
#define EMU86_EMULATE_CONFIG_WANT_MOV_CREG      0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_MOVDIR64B     1
#define EMU86_EMULATE_CONFIG_WANT_MOV_DREG      0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_MOV_IMM       1
#define EMU86_EMULATE_CONFIG_WANT_XABORT        1 /* Mandatory core instruction! */
#define EMU86_EMULATE_CONFIG_WANT_XBEGIN        1 /* Mandatory core instruction! */
#define EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS     1
#define EMU86_EMULATE_CONFIG_WANT_MOVNTI        1
#define EMU86_EMULATE_CONFIG_WANT_MOVS          1
#define EMU86_EMULATE_CONFIG_WANT_MOV_SREG      0 /* Not allowed! (changing segments is too complex) */
#define EMU86_EMULATE_CONFIG_WANT_MOVSX         1
#define EMU86_EMULATE_CONFIG_WANT_MOVSXD        1
#define EMU86_EMULATE_CONFIG_WANT_MOVZX         1
#define EMU86_EMULATE_CONFIG_WANT_ARPL          1
#define EMU86_EMULATE_CONFIG_WANT_RDMSR         0 /* No, but see `EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED' below! */
#define EMU86_EMULATE_CONFIG_WANT_WRMSR         0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_RDTSC         1
#define EMU86_EMULATE_CONFIG_WANT_RDPMC         1
#define EMU86_EMULATE_CONFIG_WANT_RDPID         1
#define EMU86_EMULATE_CONFIG_WANT_RDTSCP        1
#define EMU86_EMULATE_CONFIG_WANT_SWAPGS        0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_RDRAND        0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_RDSEED        0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_NOP_RM        1
#define EMU86_EMULATE_CONFIG_WANT_PEXT          1
#define EMU86_EMULATE_CONFIG_WANT_PDEP          1
#define EMU86_EMULATE_CONFIG_WANT_BZHI          1
#define EMU86_EMULATE_CONFIG_WANT_SLDT          0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_LLDT          0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_STR           0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_LTR           0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_SGDT          0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_LGDT          0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_XEND          1 /* Mandatory core instruction! */
#define EMU86_EMULATE_CONFIG_WANT_XTEST         1 /* Mandatory core instruction! */
#define EMU86_EMULATE_CONFIG_WANT_XGETBV        0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_XSETBV        0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_MCOMMIT       1
#define EMU86_EMULATE_CONFIG_WANT_CLZERO        1
#define EMU86_EMULATE_CONFIG_WANT_SIDT          0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_LIDT          0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_VERR          0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_VERW          0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_SMSW          0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_LMSW          0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_INVLPG        0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_LAR           0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_LSL           0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_POPCNT        1
#define EMU86_EMULATE_CONFIG_WANT_PUSHA         1
#define EMU86_EMULATE_CONFIG_WANT_POPA          1
#define EMU86_EMULATE_CONFIG_WANT_PUSHF         1
#define EMU86_EMULATE_CONFIG_WANT_POPF          1
#define EMU86_EMULATE_CONFIG_WANT_PUSH_IMM      1
#define EMU86_EMULATE_CONFIG_WANT_PUSH_REG      1
#define EMU86_EMULATE_CONFIG_WANT_POP_REG       1
#define EMU86_EMULATE_CONFIG_WANT_POP_RM        1
#define EMU86_EMULATE_CONFIG_WANT_PUSH_ES       1
#define EMU86_EMULATE_CONFIG_WANT_POP_ES        1 /* Not allowed to change segment register! */
#define EMU86_EMULATE_CONFIG_WANT_PUSH_CS       1
#define EMU86_EMULATE_CONFIG_WANT_PUSH_SS       1
#define EMU86_EMULATE_CONFIG_WANT_POP_SS        1 /* Not allowed to change segment register! */
#define EMU86_EMULATE_CONFIG_WANT_PUSH_DS       1
#define EMU86_EMULATE_CONFIG_WANT_POP_DS        1 /* Not allowed to change segment register! */
#define EMU86_EMULATE_CONFIG_WANT_PUSH_FS       1
#define EMU86_EMULATE_CONFIG_WANT_POP_FS        1 /* Not allowed to change segment register! */
#define EMU86_EMULATE_CONFIG_WANT_PUSH_GS       1
#define EMU86_EMULATE_CONFIG_WANT_POP_GS        1 /* Not allowed to change segment register! */
#define EMU86_EMULATE_CONFIG_WANT_RET           1
#define EMU86_EMULATE_CONFIG_WANT_RORX          1
#define EMU86_EMULATE_CONFIG_WANT_SAHF          1
#define EMU86_EMULATE_CONFIG_WANT_LAHF          1
#define EMU86_EMULATE_CONFIG_WANT_SALC          1
#define EMU86_EMULATE_CONFIG_WANT_SCAS          1
#define EMU86_EMULATE_CONFIG_WANT_SHIFT         1
#define EMU86_EMULATE_CONFIG_WANT_SHIFT2        1
#define EMU86_EMULATE_CONFIG_WANT_BEXTR         1
#define EMU86_EMULATE_CONFIG_WANT_SHIFTX        1
#define EMU86_EMULATE_CONFIG_WANT_STAC          1
#define EMU86_EMULATE_CONFIG_WANT_CLAC          1
#define EMU86_EMULATE_CONFIG_WANT_ENCLS         0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_ENCLU         0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_MONITOR       0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_MWAIT         0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_STGI          0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_CLGI          0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_CMC           1
#define EMU86_EMULATE_CONFIG_WANT_CLC           1
#define EMU86_EMULATE_CONFIG_WANT_STC           1
#define EMU86_EMULATE_CONFIG_WANT_CLD           1
#define EMU86_EMULATE_CONFIG_WANT_STD           1
#define EMU86_EMULATE_CONFIG_WANT_CLI           0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_STI           0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_STOS          1
#define EMU86_EMULATE_CONFIG_WANT_SYSCALL       1 /* Requires special handling! (restricted syscall emulation) */
#define EMU86_EMULATE_CONFIG_WANT_SYSRET        0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_SYSENTER      1 /* Requires special handling! (restricted syscall emulation) */
#define EMU86_EMULATE_CONFIG_WANT_SYSEXIT       0 /* Not allowed! (too complex) */
#define EMU86_EMULATE_CONFIG_WANT_XADD          1
#define EMU86_EMULATE_CONFIG_WANT_XCHG_RM       1
#define EMU86_EMULATE_CONFIG_WANT_NOP           1
#define EMU86_EMULATE_CONFIG_WANT_PAUSE         1 /* Still just a no-op */
#define EMU86_EMULATE_CONFIG_WANT_XCHG_REG      1
#define EMU86_EMULATE_CONFIG_WANT_XLATB         1
#define EMU86_EMULATE_CONFIG_WANT_XOP_BLCFILL   1
#define EMU86_EMULATE_CONFIG_WANT_XOP_BLSFILL   1
#define EMU86_EMULATE_CONFIG_WANT_XOP_BLCS      1
#define EMU86_EMULATE_CONFIG_WANT_XOP_TZMSK     1
#define EMU86_EMULATE_CONFIG_WANT_XOP_BLCIC     1
#define EMU86_EMULATE_CONFIG_WANT_XOP_BLSIC     1
#define EMU86_EMULATE_CONFIG_WANT_XOP_T1MSKC    1
#define EMU86_EMULATE_CONFIG_WANT_XOP_BLCMSK    1
#define EMU86_EMULATE_CONFIG_WANT_XOP_BLCI      1
#define EMU86_EMULATE_CONFIG_WANT_XOP_BEXTR_IMM 1

#define EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED          1 /* Emulate rdmsr for certain registers */
#define EMU86_EMULATE_CONFIG_WANT_RDMSR_EMULATED_FSGSBASE 1 /* Emulate rdmsr for IA32_(FS|GS)_BASE */
#define EMU86_EMULATE_CONFIG_WANT_WRMSR_EMULATED          0 /* We don't allow FSGSBASE modifications in RTM-mode! */
#define EMU86_EMULATE_CONFIG_FSGSBASE_32BIT               1 /* Enable FSGSBASE in 32-bit mode. */



#ifndef __x86_64__
PRIVATE WUNUSED NONNULL((1)) u32
NOTHROW(KCALL i386_getsegment_base)(struct icpustate32 const *__restrict state,
                                    u8 segment_regno) {
	u32 result;
	u16 segment_index;
	preemption_flag_t was;
	struct segment *seg;
	struct desctab dt;

#ifndef __I386_NO_VM86
	if (icpustate_isvm86(state)) {
		switch (segment_regno) {
		case EMU86_R_ES: segment_index = icpustate32_getes_vm86(state); break;
		case EMU86_R_CS: segment_index = icpustate32_getcs(state); break;
		case EMU86_R_SS: segment_index = icpustate32_getss(state); break;
		case EMU86_R_DS: segment_index = icpustate32_getds_vm86(state); break;
		case EMU86_R_FS: segment_index = icpustate32_getfs_vm86(state); break;
		case EMU86_R_GS: segment_index = icpustate32_getgs_vm86(state); break;
		default: __builtin_unreachable();
		}
		return segment_index << 4;
	}
#endif /* !__I386_NO_VM86 */

	/* Determine the segment's index. */
	switch (segment_regno) {
	case EMU86_R_ES: segment_index = icpustate_getes_novm86(state); break;
	case EMU86_R_CS: segment_index = icpustate_getcs(state); break;
	case EMU86_R_SS: segment_index = icpustate_getss(state); break;
	case EMU86_R_DS: segment_index = icpustate_getds_novm86(state); break;
	case EMU86_R_FS: segment_index = icpustate_getfs_novm86(state); break;
	case EMU86_R_GS: segment_index = icpustate_getgs_novm86(state); break;
	default: __builtin_unreachable();
	}

	/* Handle known segment indices without disabling preemption. */
	switch (segment_index & ~3) {

	case SEGMENT_KERNEL_CODE:
	case SEGMENT_KERNEL_DATA:
	case SEGMENT_USER_CODE32:
	case SEGMENT_USER_DATA32:
		return 0;

	case SEGMENT_KERNEL_FSBASE:
		if (icpustate_isuser(state)) {
err_complex:
			THROW(E_ILLEGAL_OPERATION);
		}
		return (u32)THIS_TASK;

	case SEGMENT_USER_FSBASE:
		return x86_get_user_fsbase();

	case SEGMENT_USER_GSBASE:
		return x86_get_user_gsbase();

	default:
		break;
	}

	preemption_pushoff(&was);
	__sgdt(&dt);
	if (segment_index & 4) {
		/* LDT index. */
		u16 ldt = __sldt() & ~7;
		if unlikely(!ldt || ldt > dt.dt_limit) {
			preemption_pop(&was);
			goto err_complex;
		}
		seg = (struct segment *)((byte_t *)dt.dt_base + ldt);
		dt.dt_base  = segment_rdbaseX(seg);
		dt.dt_limit = (uint16_t)segment_rdlimit(seg);
	}
	segment_index &= ~7;
	if (!segment_index || segment_index > dt.dt_limit) {
		preemption_pop(&was);
		goto err_complex;
	}
	seg = (struct segment *)((byte_t *)dt.dt_base + segment_index);
	if (seg->s_descriptor.d_dpl != 3 && icpustate_isuser(state)) {
		/* User-space can't read the base address of a privileged segment! */
		preemption_pop(&was);
		goto err_complex;
	}
	result = segment_rdbaseX(seg);
	preemption_pop(&was);
	return result;
}
#endif /* !__x86_64__ */


/* Status codes returned by `x86_emulate_rtm_instruction' */
typedef enum {
	X86_RTM_STATUS_CONTINUE = 0, /* Instruction completed normally (continue execution) */
	X86_RTM_STATUS_COMPLETE,     /* [xend]   Complete the transaction and update the caller's register state */
	X86_RTM_STATUS_ABORT,        /* [xabort] Abort with the status code already stored in `%Pax' */
} x86_rtm_status_t;


#ifdef __x86_64__
#define DEFINE_REGISTERp(c) \
	union {                 \
		uintptr_t r_p##c;   \
		u64       r_r##c;   \
		u32       r_e##c;   \
		u16       r_##c;    \
		u8        r_##c##l; \
	}
#define DEFINE_REGISTERx(c)  \
	union {                  \
		uintptr_t r_p##c##x; \
		u64       r_r##c##x; \
		u32       r_e##c##x; \
		u16       r_##c##x;  \
		struct {             \
			u8    r_##c##l;  \
			u8    r_##c##h;  \
		};                   \
	}
#else /* __x86_64__ */
#define DEFINE_REGISTERp(c) \
	union {                 \
		uintptr_t r_p##c;   \
		u32       r_e##c;   \
		u16       r_##c;    \
		u8        r_##c##l; \
	}
#define DEFINE_REGISTERx(c)  \
	union {                  \
		uintptr_t r_p##c##x; \
		u32       r_e##c##x; \
		u16       r_##c##x;  \
		struct {             \
			u8    r_##c##l;  \
			u8    r_##c##h;  \
		};                   \
	}
#endif /* !__x86_64__ */

struct rtm_machstate {
	/* Machine state during execution of RTM code. */
	struct icpustate const *r_icstate;     /* [1..1][const] The underlying interrupt cpu-state.
	                                        * Used when trying to read segment register values. */
	struct rtm_memory       r_mem;         /* RTM memory buffer. */
	union {
#ifdef __x86_64__
		u64                 r_gpregs[16];   /* General purpose registers */
		u8                  r_gpregsb[128]; /* ... */
		u16                 r_gpregsw[64];  /* ... */
		u32                 r_gpregsl[32];  /* ... */
		u64                 r_gpregsq[16];  /* ... */
#else /* __x86_64__ */
		u32                 r_gpregs[8];    /* General purpose registers */
		u8                  r_gpregsb[32];  /* ... */
		u16                 r_gpregsw[16];  /* ... */
		u32                 r_gpregsl[8];   /* ... */
#endif /* !__x86_64__ */
		struct {
			DEFINE_REGISTERx(a);
			DEFINE_REGISTERx(c);
			DEFINE_REGISTERx(d);
			DEFINE_REGISTERx(b);
			DEFINE_REGISTERp(sp);
			DEFINE_REGISTERp(bp);
			DEFINE_REGISTERp(si);
			DEFINE_REGISTERp(di);
#ifdef __x86_64__
			u64             r_r8;
			u64             r_r9;
			u64             r_r10;
			u64             r_r11;
			u64             r_r12;
			u64             r_r13;
			u64             r_r14;
			u64             r_r15;
#endif /* __x86_64__ */
		};
	};
	DEFINE_REGISTERp(ip);    /* Instruction pointer */
	DEFINE_REGISTERp(flags); /* Flags register */
#ifdef __x86_64__
	uintptr_t               r_fsbase;  /* %fs.base (or (uintptr_t)-1 before first use) */
	uintptr_t               r_gsbase;  /* %gs.base (or (uintptr_t)-1 before first use) */
#else /* __x86_64__ */
	union {
		struct {
			uintptr_t       r_esbase;  /* %es.base (or (uintptr_t)-1 before first use) */
			uintptr_t       r_csbase;  /* %cs.base */
			uintptr_t       r_ssbase;  /* %ss.base */
			uintptr_t       r_dsbase;  /* %ds.base */
			uintptr_t       r_fsbase;  /* %fs.base (or (uintptr_t)-1 before first use) */
			uintptr_t       r_gsbase;  /* %gs.base (or (uintptr_t)-1 before first use) */
		};
		uintptr_t           r_sgbase[6];
	};
#endif /* !__x86_64__ */
	uintptr_t               r_nesting; /* RTM nesting level (when > 0, RTM is being nested) */
};

/* Helpers for system call argument register access */
#define RTM_MACHSTATE_SYSCALL_I386_ARG0(self) (self)->r_ebx
#define RTM_MACHSTATE_SYSCALL_I386_ARG1(self) (self)->r_ecx
#define RTM_MACHSTATE_SYSCALL_I386_ARG2(self) (self)->r_edx
#define RTM_MACHSTATE_SYSCALL_I386_ARG3(self) (self)->r_esi
#ifdef __x86_64__
#define RTM_MACHSTATE_SYSCALL_X86_64_ARG0(self) (self)->r_rdi
#define RTM_MACHSTATE_SYSCALL_X86_64_ARG1(self) (self)->r_rsi
#define RTM_MACHSTATE_SYSCALL_X86_64_ARG2(self) (self)->r_rdx
#define RTM_MACHSTATE_SYSCALL_X86_64_ARG3(self) (self)->r_r10
#define RTM_MACHSTATE_SYSCALL_ARG0 RTM_MACHSTATE_SYSCALL_X86_64_ARG0
#define RTM_MACHSTATE_SYSCALL_ARG1 RTM_MACHSTATE_SYSCALL_X86_64_ARG1
#define RTM_MACHSTATE_SYSCALL_ARG2 RTM_MACHSTATE_SYSCALL_X86_64_ARG2
#define RTM_MACHSTATE_SYSCALL_ARG3 RTM_MACHSTATE_SYSCALL_X86_64_ARG3
#else /* __x86_64__ */
#define RTM_MACHSTATE_SYSCALL_ARG0 RTM_MACHSTATE_SYSCALL_I386_ARG0
#define RTM_MACHSTATE_SYSCALL_ARG1 RTM_MACHSTATE_SYSCALL_I386_ARG1
#define RTM_MACHSTATE_SYSCALL_ARG2 RTM_MACHSTATE_SYSCALL_I386_ARG2
#define RTM_MACHSTATE_SYSCALL_ARG3 RTM_MACHSTATE_SYSCALL_I386_ARG3
#endif /* !__x86_64__ */




#define DEFINE_SEGMENT_BASE_GETTER(name, field, getvalue)        \
	PRIVATE NOBLOCK WUNUSED NONNULL((1)) uintptr_t               \
	NOTHROW(FCALL name)(struct rtm_machstate *__restrict self) { \
		uintptr_t result;                                        \
		result = self->field;                                    \
		if (result == (uintptr_t)-1) {                           \
			result      = getvalue;                              \
			self->field = result;                                \
		}                                                        \
		return result;                                           \
	}
#ifdef __x86_64__
#define rtm_machstate_get_dsbase(self) 0
#define rtm_machstate_get_esbase(self) 0
#define rtm_machstate_get_csbase(self) 0
#define rtm_machstate_get_ssbase(self) 0
DEFINE_SEGMENT_BASE_GETTER(rtm_machstate_get_fsbase, r_fsbase, (uintptr_t)__rdfsbase())
#ifdef CONFIG_MODRTM_USERSPACE_ONLY
DEFINE_SEGMENT_BASE_GETTER(rtm_machstate_get_gsbase, r_gsbase,
                           (uintptr_t)__rdmsr(IA32_KERNEL_GS_BASE))
#else /* CONFIG_MODRTM_USERSPACE_ONLY */
DEFINE_SEGMENT_BASE_GETTER(rtm_machstate_get_gsbase, r_gsbase,
                           self->r_mem.rm_chkuser
                           ? (uintptr_t)__rdmsr(IA32_KERNEL_GS_BASE)
                           : (uintptr_t)__rdgsbase())
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
#else /* __x86_64__ */
DEFINE_SEGMENT_BASE_GETTER(rtm_machstate_get_esbase, r_esbase, i386_getsegment_base(self->r_icstate, EMU86_R_ES))
#define rtm_machstate_get_csbase(self) (uintptr_t)(self)->r_csbase /* i386_getsegment_base(self->r_icstate, EMU86_R_CS)) */
#define rtm_machstate_get_ssbase(self) (uintptr_t)(self)->r_ssbase /* i386_getsegment_base(self->r_icstate, EMU86_R_SS)) */
#define rtm_machstate_get_dsbase(self) (uintptr_t)(self)->r_dsbase /* i386_getsegment_base(self->r_icstate, EMU86_R_DS)) */
DEFINE_SEGMENT_BASE_GETTER(rtm_machstate_get_fsbase, r_fsbase, i386_getsegment_base(self->r_icstate, EMU86_R_FS))
DEFINE_SEGMENT_BASE_GETTER(rtm_machstate_get_gsbase, r_gsbase, i386_getsegment_base(self->r_icstate, EMU86_R_GS))
#endif /* !__x86_64__ */
#undef DEFINE_SEGMENT_BASE_GETTER



#define ABORT_WITH(status) \
	(self->r_pax = (status), X86_RTM_STATUS_ABORT)


PRIVATE NONNULL((1)) x86_rtm_status_t FCALL
x86_emulate_rtm_instruction(struct rtm_machstate *__restrict self);



#ifdef __x86_64__
#define EMU86_EMULATE_RETURN_AFTER_SYSCALL() \
	return x86_emulate_rtm_instruction_syscall(self, op_flags)
#define EMU86_EMULATE_RETURN_AFTER_SYSENTER() \
	return x86_emulate_rtm_instruction_syscall(self, op_flags)
#else /* __x86_64__ */
#define EMU86_EMULATE_RETURN_AFTER_SYSCALL() \
	return x86_emulate_rtm_instruction_syscall(self)
#define EMU86_EMULATE_RETURN_AFTER_SYSENTER() \
	return x86_emulate_rtm_instruction_syscall(self)
#endif /* !__x86_64__ */
PRIVATE NONNULL((1)) x86_rtm_status_t FCALL
x86_emulate_rtm_instruction_syscall(struct rtm_machstate *__restrict self
#ifdef __x86_64__
                                    ,
                                    emu86_opflags_t op_flags
#endif /* __x86_64__ */
                                    ) {
	syscall_ulong_t sysno;
	sysno = self->r_pax;
#ifdef HAVE_RTM_EMULATION_TRACE
	printk(KERN_TRACE "[rtm] syscall: %#Ix\n", sysno);
#endif /* HAVE_RTM_EMULATION_TRACE */

#ifdef __x86_64__
	if (EMU86_F_IS32(op_flags)) {
		sysno = sysno & UINT32_C(0xffffffff);
		switch (sysno) {

		case __NR32_rtm_test:
			sysno = SYS_rtm_test;
			break;

		case __NR32_rtm_abort:
			/* Explicit RTM abort
			 * HINT: %ebx is the first system call argument register in 32-bit mode. */
			return ABORT_WITH(_XABORT_EXPLICIT |
			                  ((RTM_MACHSTATE_SYSCALL_I386_ARG0(self) << _XABORT_CODE_S) &
			                   _XABORT_CODE_M));

		case __NR32_rtm_end:
			sysno = SYS_rtm_end;
			break;

		case __NR32_rtm_begin:
			sysno = SYS_rtm_begin;
			break;

		/* Custom system calls. */
#ifdef rtm_sys_syslog
		case __NR32_syslog:
			self->r_pax = rtm_sys_syslog(&self->r_mem,
			                             (syscall_ulong_t)RTM_MACHSTATE_SYSCALL_I386_ARG0(self),
			                             (char const *)(uintptr_t)RTM_MACHSTATE_SYSCALL_I386_ARG1(self),
			                             (size_t)RTM_MACHSTATE_SYSCALL_I386_ARG2(self));
			return X86_RTM_STATUS_CONTINUE;
#endif /* rtm_sys_syslog */

#ifdef rtm_sys_rpc_serve
		case __NR32_rpc_serve:
			sysno = SYS_rpc_serve;
			break;
#endif /* rtm_sys_rpc_serve */

#ifdef rtm_sys_gettid
		case __NR32_gettid:
			sysno = SYS_gettid;
			break;
#endif /* rtm_sys_gettid */

#ifdef rtm_sys_getpid
		case __NR32_getpid:
			sysno = SYS_getpid;
			break;
#endif /* rtm_sys_getpid */

#ifdef rtm_sys_sched_yield
		case __NR32_sched_yield:
			sysno = SYS_sched_yield;
			break;
#endif /* rtm_sys_sched_yield */

		default:
			/* Unsupported system call! */
			sysno = SYS_pause; /* Anything that isn't supported will do here! */
			break;
		}
	}
#endif /* __x86_64__ */
	switch (sysno) {

	case SYS_rtm_begin:
		/* Nested RTM support */
		if unlikely(self->r_nesting == (uintptr_t)-1)
			return ABORT_WITH(_XABORT_CAPACITY);
		++self->r_nesting;
		self->r_pax = _XBEGIN_STARTED; /* System call return value */
		return X86_RTM_STATUS_CONTINUE;

	case SYS_rtm_end:
		/* End an RTM operation (but do support nesting!) */
		if (!self->r_nesting)
			return X86_RTM_STATUS_COMPLETE;
		--self->r_nesting;
		self->r_pax = -EOK; /* System call return value */
		return X86_RTM_STATUS_CONTINUE;

	case SYS_rtm_abort:
		/* Explicit RTM abort
		 * HINT: %ebx is the first system call argument register in 32-bit mode.
		 * HINT: %rdi is the first system call argument register in 64-bit mode. */
		return ABORT_WITH(_XABORT_EXPLICIT |
		                  (((u32)RTM_MACHSTATE_SYSCALL_ARG0(self) << _XABORT_CODE_S) &
		                   _XABORT_CODE_M));

	case SYS_rtm_test:
		self->r_pax = 1; /* System call return value */
		/* This system  call  is  special, in  that  it  has 2  return  values  when
		 * called in the context of an `int80', `sysenter' or `syscall' instruction.
		 *
		 * The non-emulated  counterpart to  this can  be found  in
		 * `/kos/src/kernel/core/arch/i386/syscall/fastpass-impl.S'
		 */
		self->r_pflags &= ~EFLAGS_ZF;
		return X86_RTM_STATUS_CONTINUE;

	/* Custom system calls. */
#ifdef rtm_sys_syslog
	case SYS_syslog:
		self->r_pax = rtm_sys_syslog(&self->r_mem,
		                             (syscall_ulong_t)RTM_MACHSTATE_SYSCALL_ARG0(self),
		                             (char const *)(uintptr_t)RTM_MACHSTATE_SYSCALL_ARG1(self),
		                             (size_t)RTM_MACHSTATE_SYSCALL_ARG2(self));
		return X86_RTM_STATUS_CONTINUE;
#endif /* rtm_sys_syslog */

#ifdef rtm_sys_rpc_serve
	case SYS_rpc_serve:
		self->r_pax = rtm_sys_rpc_serve(&self->r_mem);
		return X86_RTM_STATUS_CONTINUE;
#endif /* rtm_sys_rpc_serve */

#ifdef rtm_sys_gettid
	case SYS_gettid:
		self->r_pax = rtm_sys_gettid(&self->r_mem);
		return X86_RTM_STATUS_CONTINUE;
#endif /* rtm_sys_gettid */

#ifdef rtm_sys_getpid
	case SYS_getpid:
		self->r_pax = rtm_sys_getpid(&self->r_mem);
		return X86_RTM_STATUS_CONTINUE;
#endif /* rtm_sys_getpid */

#ifdef rtm_sys_sched_yield
	case SYS_sched_yield:
		self->r_pax = rtm_sys_sched_yield(&self->r_mem);
		return X86_RTM_STATUS_CONTINUE;
#endif /* rtm_sys_sched_yield */

	default:
		break;
	}
	/* Any unsupported system call will result in an RTM abort. */
	return ABORT_WITH(_XABORT_FAILED);
}

#ifdef __x86_64__
#define EMU86_EMULATE_RETURN_AFTER_INT(intno) \
	return x86_emulate_rtm_instruction_int(self, intno, op_flags)
#else /* __x86_64__ */
#define EMU86_EMULATE_RETURN_AFTER_INT(intno) \
	return x86_emulate_rtm_instruction_int(self, intno)
#endif /* !__x86_64__ */
PRIVATE NONNULL((1)) x86_rtm_status_t FCALL
x86_emulate_rtm_instruction_int(struct rtm_machstate *__restrict self,
                                u8 intno
#ifdef __x86_64__
                                ,
                                emu86_opflags_t op_flags
#endif /* __x86_64__ */
                                ) {
	if (intno == 0x80) {
		/* syscall emulation */
#ifdef __x86_64__
		return x86_emulate_rtm_instruction_syscall(self, op_flags);
#else /* __x86_64__ */
		return x86_emulate_rtm_instruction_syscall(self);
#endif /* !__x86_64__ */
	}
	if (intno == 0x03)
		return ABORT_WITH(_XABORT_DEBUG);
	return ABORT_WITH(_XABORT_FAILED);
}


#define EMU86_EMULATE_DECL          PRIVATE
#define EMU86_EMULATE_ATTR          NONNULL((1))
#define EMU86_EMULATE_RETURN()      return X86_RTM_STATUS_CONTINUE
#define EMU86_EMULATE_RETURN_TYPE   x86_rtm_status_t
#define EMU86_EMULATE_NOTHROW       /* nothing */
#define EMU86_EMULATE_CC            FCALL
#define EMU86_EMULATE_NAME          x86_emulate_rtm_instruction
#define EMU86_EMULATE_ARGS          struct rtm_machstate *__restrict self
#define EMU86_EMULATE_HELPER_ATTR   __ATTR_NONNULL((1))
#define EMU86_EMULATE_HELPER_ARGS   struct rtm_machstate *__restrict self /* Arguments for helper functions */
#define EMU86_EMULATE_HELPER_PARAM  self                                  /* Parameters passed to helper functions */


#define EMU86_EMULATE_NO_IMPLICIT_RETURN_AFTER_INT 1
#define EMU86_EMULATE_RETURN_AFTER_INT1() \
	return ABORT_WITH(_XABORT_FAILED)
#define EMU86_EMULATE_RETURN_AFTER_INT3() \
	return ABORT_WITH(_XABORT_FAILED) /* #BP */
#define EMU86_EMULATE_RETURN_AFTER_INTO() \
	return ABORT_WITH(_XABORT_FAILED) /* #OF */
#define EMU86_EMULATE_THROW_BOUNDERR(bound_idx, bound_min, bound_max) \
	return ABORT_WITH(_XABORT_FAILED) /* #BR */
#define EMU86_EMULATE_RETURN_UNKNOWN_INSTRUCTION() \
	return ABORT_WITH(_XABORT_FAILED) /* #UD */
#define EMU86_EMULATE_THROW_SEGFAULT_UNALIGNED(addr, context, req_alignment) \
	return ABORT_WITH(_XABORT_FAILED)
#define EMU86_EMULATE_THROW_DIVIDE_ERROR() \
	return ABORT_WITH(_XABORT_FAILED)

#define EMU86_EMULATE_GETOPFLAGS()          emu86_opflags_from_icpustate(self->r_icstate)
#define EMU86_EMULATE_TRANSLATEADDR_IS_NOOP 1
#define EMU86_EMULATE_TRANSLATEADDR(addr) (addr)
#define EMU86_GETCR4_UMIP_IS_ZERO 1 /* TODO: Support me! */
#define EMU86_GETCR4_UMIP()       0 /* TODO: Support me! */
#define EMU86_GETCR4_DE_IS_ONE    1 /* TODO: Support me! */
#define EMU86_GETCR4_DE()         1 /* TODO: Support me! */

/* Tell libemu86 how to emulate certain instructions. */
#define EMU86_EMULATE_SLDT()                     DONT_USE
#define EMU86_EMULATE_LLDT(segment_index)        DONT_USE
#define EMU86_EMULATE_STR()                      DONT_USE
#define EMU86_EMULATE_LTR(segment_index)         DONT_USE
#define EMU86_EMULATE_VERR(segment_index)        DONT_USE
#define EMU86_EMULATE_VERW(segment_index)        DONT_USE
#define EMU86_EMULATE_SGDT(limit, base)          DONT_USE
#define EMU86_EMULATE_LGDT(limit, base)          DONT_USE
#define EMU86_EMULATE_LIDT(limit, base)          DONT_USE
#define EMU86_EMULATE_SMSW()                     DONT_USE
#define EMU86_EMULATE_LMSW(value)                DONT_USE
#define EMU86_EMULATE_INVLPG(addr)               DONT_USE
#define EMU86_EMULATE_LAR(segment_index, result) DONT_USE
#define EMU86_EMULATE_LSL(segment_index, result) DONT_USE

#define EMU86_EMULATE_RDCR0()  DONT_USE
#define EMU86_EMULATE_WRCR0(v) DONT_USE
#define EMU86_EMULATE_RDCR2()  DONT_USE
#define EMU86_EMULATE_WRCR2(v) DONT_USE
#define EMU86_EMULATE_RDCR3()  DONT_USE
#define EMU86_EMULATE_WRCR3(v) DONT_USE
#define EMU86_EMULATE_RDCR4()  DONT_USE
#define EMU86_EMULATE_WRCR4(v) DONT_USE
#define EMU86_EMULATE_RDCR8()  DONT_USE
#define EMU86_EMULATE_WRCR8(v) DONT_USE

#define EMU86_EMULATE_RDDR0()  DONT_USE
#define EMU86_EMULATE_WRDR0(v) DONT_USE
#define EMU86_EMULATE_RDDR1()  DONT_USE
#define EMU86_EMULATE_WRDR1(v) DONT_USE
#define EMU86_EMULATE_RDDR2()  DONT_USE
#define EMU86_EMULATE_WRDR2(v) DONT_USE
#define EMU86_EMULATE_RDDR3()  DONT_USE
#define EMU86_EMULATE_WRDR3(v) DONT_USE
#define EMU86_EMULATE_RDDR6()  DONT_USE
#define EMU86_EMULATE_WRDR6(v) DONT_USE
#define EMU86_EMULATE_RDDR7()  DONT_USE
#define EMU86_EMULATE_WRDR7(v) DONT_USE

#define EMU86_EMULATE_RDMSR(index)                     DONT_USE
#define EMU86_EMULATE_WRMSR(index, value)              DONT_USE
#define EMU86_EMULATE_CLTS()                           DONT_USE
#define EMU86_EMULATE_SWAPGS()                         DONT_USE
#define EMU86_EMULATE_TPAUSE(want_c01, tsc_deadline)   DONT_USE
#define EMU86_EMULATE_XGETBV(index)                    DONT_USE
#define EMU86_EMULATE_XSETBV(index, value)             DONT_USE
#define EMU86_EMULATE_MONITOR(addr, extensions, hints) DONT_USE
#define EMU86_EMULATE_MWAIT(ecx, edx)                  DONT_USE
#define EMU86_EMULATE_ENCLS(leaf)                      DONT_USE
#define EMU86_EMULATE_ENCLU(leaf)                      DONT_USE
#define EMU86_EMULATE_LDMXCSR(mxcsr)                   DONT_USE

#define EMU86_EMULATE_RDTSC_INDIRECT() __rdtsc()
#define EMU86_EMULATE_RDTSC()          __rdtsc()

/* Return the OS-specific ID for the current CPU (same as the `IA32_TSC_AUX' MSR) */
#define EMU86_EMULATE_RDPID() emulate_rdpid()
PRIVATE ATTR_PURE WUNUSED u32 KCALL emulate_rdpid(void) {
	return THIS_CPU->c_id;
}

#define EMU86_EMULATE_RDTSCP(tsc_aux) emulate_rdtscp(&(tsc_aux))
LOCAL WUNUSED NONNULL((1)) u64 KCALL
emulate_rdtscp(u32 *__restrict p_tsc_aux) {
	u64 tsc;
	preemption_flag_t was;
	/* To guaranty that the hosting CPU doesn't change  during
	 * execution here, temporarily disable preemption, so that
	 * the TSC and CPU-ID are consistent with each other! */
	preemption_pushoff(&was);
	COMPILER_BARRIER();
	*p_tsc_aux = EMU86_EMULATE_RDPID();
	tsc        = EMU86_EMULATE_RDTSC_INDIRECT();
	COMPILER_BARRIER();
	preemption_pop(&was);
	return tsc;
}

#undef EMU86_EMULATE_CONFIG_WANT_RDPMC
#define EMU86_EMULATE_CONFIG_WANT_RDPMC 0   /* TODO: Emulate */
#define EMU86_EMULATE_RDPMC(index) DONT_USE /* TODO: Emulate */

#define EMU86_EMULATE_RDRAND16(result) DONT_USE
#define EMU86_EMULATE_RDRAND32(result) DONT_USE
#define EMU86_EMULATE_RDRAND64(result) DONT_USE
#define EMU86_EMULATE_RDSEED16(result) DONT_USE
#define EMU86_EMULATE_RDSEED32(result) DONT_USE
#define EMU86_EMULATE_RDSEED64(result) DONT_USE

/* Configure user-visible CR4 bits as fixed. */
#define EMU86_GETCR4_UMIP_IS_ONE 1 /* Disable access to some super-visor-mode instructions */
#define EMU86_GETCR4_DE_IS_ONE   1 /* Disallow use of %dr4 and %dr5 */
#define EMU86_GETCR4_TSD_IS_ZERO 1 /* Allow user-space use of `rdtsc' and `rdtscp' */
#define EMU86_GETCR4_PCE_IS_ZERO 1 /* Allow user-space use of `rdpmc' */


#ifdef CONFIG_MODRTM_USERSPACE_ONLY
#define EMU86_ISUSER() 1
#define EMU86_ISUSER_IS_ONE 1
#else /* CONFIG_MODRTM_USERSPACE_ONLY */
#define EMU86_ISUSER() self->r_mem.rm_chkuser
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */

#if defined(__x86_64__) || defined(__I386_NO_VM86)
#define EMU86_EMULATE_CONFIG_VM86 0
#define EMU86_ISUSER_NOVM86()     EMU86_ISUSER()
#ifdef EMU86_ISUSER_IS_ONE
#define EMU86_ISUSER_NOVM86_IS_ONE 1
#endif /* EMU86_ISUSER_IS_ONE */
#else /* __x86_64__ || __I386_NO_VM86 */
#define EMU86_EMULATE_CONFIG_VM86             1
#define EMU86_EMULATE_VM86_GETIF()            0 /* TODO */
#define EMU86_EMULATE_VM86_SETIF(v)           (void)0
#define EMU86_EMULATE_RETURN_AFTER_HLT_VM86() DONT_USE
#ifdef CONFIG_MODRTM_USERSPACE_ONLY
#define EMU86_ISUSER_NOVM86()                 (!icpustate32_isvm86(self->r_icstate))
#else /* CONFIG_MODRTM_USERSPACE_ONLY */
#define EMU86_ISUSER_NOVM86()                 (self->r_mem.rm_chkuser && !icpustate32_isvm86(self->r_icstate))
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */
#define EMU86_ISVM86()                        (icpustate32_isvm86(self->r_icstate))
#endif /* !__x86_64__ && !__I386_NO_VM86 */

#define EMU86_UNSUPPORTED_MEMACCESS_IS_NOOP 1
#define EMU86_UNSUPPORTED_MEMACCESS(addr, num_bytes, reading, writing) (void)0

#define EMU86_GETFLAGS()            self->r_pflags
#define EMU86_SETFLAGS(v)           (void)(self->r_pflags = (v))
#define EMU86_MSKFLAGS(mask, value) (void)(self->r_pflags = (self->r_pflags & (mask)) | (value))
#define EMU86_GETIPREG()            (uintptr_t)self->r_pip
#define EMU86_SETIPREG(v)           (void)(self->r_pip = (uintptr_t)(v))
#define EMU86_GETSPREG()            (uintptr_t)self->r_psp
#define EMU86_SETSPREG(v)           (void)(self->r_psp = (uintptr_t)(v))

#define EMU86_GETPCPTR()            (byte_t *)self->r_pip
#define EMU86_SETPCPTR(v)           (void)(self->r_pip = (uintptr_t)(v))
#define EMU86_GETSTACKPTR()         (byte_t *)self->r_psp
#define EMU86_SETSTACKPTR(v)        (void)(self->r_psp = (uintptr_t)(v))

#define EMU86_GETDSBASE() rtm_machstate_get_dsbase(self)
#define EMU86_GETESBASE() rtm_machstate_get_esbase(self)
#define EMU86_GETCSBASE() rtm_machstate_get_csbase(self)
#define EMU86_GETSSBASE() rtm_machstate_get_ssbase(self)
#define EMU86_GETFSBASE() rtm_machstate_get_fsbase(self)
#define EMU86_GETGSBASE() rtm_machstate_get_gsbase(self)

#ifdef __x86_64__
#define EMU86_GETSEGBASE_IS_NOOP_ES 1
#define EMU86_GETSEGBASE_IS_NOOP_CS 1
#define EMU86_GETSEGBASE_IS_NOOP_SS 1
#define EMU86_GETSEGBASE_IS_NOOP_DS 1
#define EMU86_GETSEGBASE(segment_regno) \
	((segment_regno) == EMU86_R_FS      \
	 ? EMU86_GETFSBASE()                \
	 : (segment_regno) == EMU86_R_GS    \
	   ? EMU86_GETGSBASE()              \
	   : 0)
#else /* __x86_64__ */
/* 32-bit mode supports non-zero bases for any segment! */
#define EMU86_GETSEGBASE(segment_regno) i386_get_rtm_segment_base(self, segment_regno)
PRIVATE WUNUSED NONNULL((1)) u32
NOTHROW(KCALL i386_get_rtm_segment_base)(struct rtm_machstate *__restrict self,
                                         u8 segment_regno) {
	u32 result;
	result = self->r_sgbase[segment_regno];
	if (result == (u32)-1) {
		result = i386_getsegment_base(self->r_icstate,
		                              segment_regno);
		self->r_sgbase[segment_regno] = result;
	}
	return result;
}
#endif /* !__x86_64__ */

#define EMU86_SEGADDR(segbase, segoffset)     (byte_t *)(uintptr_t)((segbase) + (segoffset))
#define EMU86_GETES()                         icpustate_getes(self->r_icstate)
#define EMU86_GETCS()                         icpustate_getcs(self->r_icstate)
#define EMU86_GETSS()                         icpustate_getss(self->r_icstate)
#define EMU86_GETDS()                         icpustate_getds(self->r_icstate)
#define EMU86_GETFS()                         icpustate_getfs(self->r_icstate)
#define EMU86_GETGS()                         icpustate_getgs(self->r_icstate)
#define EMU86_EMULATE_PUSH(new_sp, num_bytes) (void)0
#define EMU86_EMULATE_POP(old_sp, num_bytes)  (void)0
#define EMU86_SETES(v)                         \
	do {                                       \
		if (EMU86_GETES() != (v))              \
			return ABORT_WITH(_XABORT_FAILED); \
	}	__WHILE0
#define EMU86_SETCS(v)                         \
	do {                                       \
		if (EMU86_GETCS() != (v))              \
			return ABORT_WITH(_XABORT_FAILED); \
	}	__WHILE0
#define EMU86_SETSS(v)                         \
	do {                                       \
		if (EMU86_GETSS() != (v))              \
			return ABORT_WITH(_XABORT_FAILED); \
	}	__WHILE0
#define EMU86_SETDS(v)                         \
	do {                                       \
		if (EMU86_GETDS() != (v))              \
			return ABORT_WITH(_XABORT_FAILED); \
	}	__WHILE0
#define EMU86_SETFS(v)                         \
	do {                                       \
		if (EMU86_GETFS() != (v))              \
			return ABORT_WITH(_XABORT_FAILED); \
	}	__WHILE0
#define EMU86_SETGS(v)                         \
	do {                                       \
		if (EMU86_GETGS() != (v))              \
			return ABORT_WITH(_XABORT_FAILED); \
	}	__WHILE0
#define EMU86_SETSEG(regno, value)             \
	do {                                       \
		if (EMU86_GETSEG(regno) != (value))    \
			return ABORT_WITH(_XABORT_FAILED); \
	}	__WHILE0
#define EMU86_SETREGP(regno, value, op_flags) DONT_USE /* Unused */

#define EMU86_VALIDATE_IO(portno, num_ports) DONE_USE
#define EMU86_EMULATE_INB(portno, result)    DONT_USE
#define EMU86_EMULATE_INW(portno, result)    DONT_USE
#define EMU86_EMULATE_INL(portno, result)    DONT_USE
#define EMU86_EMULATE_OUTB(portno, value)    DONT_USE
#define EMU86_EMULATE_OUTW(portno, value)    DONT_USE
#define EMU86_EMULATE_OUTL(portno, value)    DONT_USE


#ifdef EMU86_EMULATE_CONFIG_WANT_CPUID
#define EMU86_EMULATE_HANDLE_CPUID() cpuid(self)
PRIVATE WUNUSED NONNULL((1)) void
NOTHROW(KCALL cpuid)(struct rtm_machstate *__restrict self) {
	u32 eax, ecx, edx, ebx;
	__cpuid2(self->r_eax, self->r_ecx,
	         &eax, &ecx, &edx, &ebx);
	self->r_pax = eax;
	self->r_pcx = ecx;
	self->r_pdx = edx;
	self->r_pbx = ebx;
}
#endif /* EMU86_EMULATE_CONFIG_WANT_CPUID */

#ifdef __x86_64__
/* Offsets to 8-bit registers, both with and without EMU86_F_HASREX */
PRIVATE uintptr_t const mach_breg_offset[2][16] = {
	[/* EMU86_F_HASREX = */ 0] = {
		[EMU86_R_AL]   = offsetof(struct rtm_machstate, r_al),  /* %al */
		[EMU86_R_CL]   = offsetof(struct rtm_machstate, r_cl),  /* %cl */
		[EMU86_R_DL]   = offsetof(struct rtm_machstate, r_dl),  /* %dl */
		[EMU86_R_BL]   = offsetof(struct rtm_machstate, r_bl),  /* %bl */
		[EMU86_R_AH]   = offsetof(struct rtm_machstate, r_ah),  /* %ah */
		[EMU86_R_CH]   = offsetof(struct rtm_machstate, r_ch),  /* %ch */
		[EMU86_R_DH]   = offsetof(struct rtm_machstate, r_dh),  /* %dh */
		[EMU86_R_BH]   = offsetof(struct rtm_machstate, r_bh),  /* %bh */
		[EMU86_R_R8L]  = offsetof(struct rtm_machstate, r_r8),  /* %r8l */
		[EMU86_R_R9L]  = offsetof(struct rtm_machstate, r_r9),  /* %r9l */
		[EMU86_R_R10L] = offsetof(struct rtm_machstate, r_r10), /* %r10l */
		[EMU86_R_R11L] = offsetof(struct rtm_machstate, r_r11), /* %r11l */
		[EMU86_R_R12L] = offsetof(struct rtm_machstate, r_r12), /* %r12l */
		[EMU86_R_R13L] = offsetof(struct rtm_machstate, r_r13), /* %r13l */
		[EMU86_R_R14L] = offsetof(struct rtm_machstate, r_r14), /* %r14l */
		[EMU86_R_R15L] = offsetof(struct rtm_machstate, r_r15), /* %r15l */
	},
	[/* EMU86_F_HASREX = */ 1] = {
		[EMU86_R_AL]   = offsetof(struct rtm_machstate, r_al),  /* %al */
		[EMU86_R_CL]   = offsetof(struct rtm_machstate, r_cl),  /* %cl */
		[EMU86_R_DL]   = offsetof(struct rtm_machstate, r_dl),  /* %dl */
		[EMU86_R_BL]   = offsetof(struct rtm_machstate, r_bl),  /* %bl */
		[EMU86_R_SPL]  = offsetof(struct rtm_machstate, r_spl), /* %spl */
		[EMU86_R_BPL]  = offsetof(struct rtm_machstate, r_bpl), /* %bpl */
		[EMU86_R_SIL]  = offsetof(struct rtm_machstate, r_sil), /* %sil */
		[EMU86_R_DIL]  = offsetof(struct rtm_machstate, r_dil), /* %dil */
		[EMU86_R_R8L]  = offsetof(struct rtm_machstate, r_r8),  /* %r8l */
		[EMU86_R_R9L]  = offsetof(struct rtm_machstate, r_r9),  /* %r9l */
		[EMU86_R_R10L] = offsetof(struct rtm_machstate, r_r10), /* %r10l */
		[EMU86_R_R11L] = offsetof(struct rtm_machstate, r_r11), /* %r11l */
		[EMU86_R_R12L] = offsetof(struct rtm_machstate, r_r12), /* %r12l */
		[EMU86_R_R13L] = offsetof(struct rtm_machstate, r_r13), /* %r13l */
		[EMU86_R_R14L] = offsetof(struct rtm_machstate, r_r14), /* %r14l */
		[EMU86_R_R15L] = offsetof(struct rtm_machstate, r_r15), /* %r15l */
	}
};

#define REG8(id, op_flags) \
	(*((u8 *)self + mach_breg_offset[!!((op_flags) & EMU86_F_HASREX)][id]))
#define REG16(id)                   self->r_gpregsw[(id)*4]
#define REG32(id)                   self->r_gpregsl[(id)*2]
#define REG64(id)                   self->r_gpregsq[id]
#define EMU86_GETREGQ(regno)        REG64(regno)
#define EMU86_SETREGW(regno, value) REG16(regno) = (u16)(value)
#define EMU86_SETREGL(regno, value) REG64(regno) = (u64)(u32)(value) /* 32-bit register writes clear the upper 32 bits */
#define EMU86_SETREGQ(regno, value) REG64(regno) = (u64)(value)
#else /* __x86_64__ */
PRIVATE uintptr_t const mach_breg_offset[8] = {
	[EMU86_R_AL] = offsetof(struct rtm_machstate, r_al), /* %al */
	[EMU86_R_CL] = offsetof(struct rtm_machstate, r_cl), /* %cl */
	[EMU86_R_DL] = offsetof(struct rtm_machstate, r_dl), /* %dl */
	[EMU86_R_BL] = offsetof(struct rtm_machstate, r_bl), /* %bl */
	[EMU86_R_AH] = offsetof(struct rtm_machstate, r_ah), /* %ah */
	[EMU86_R_CH] = offsetof(struct rtm_machstate, r_ch), /* %ch */
	[EMU86_R_DH] = offsetof(struct rtm_machstate, r_dh), /* %dh */
	[EMU86_R_BH] = offsetof(struct rtm_machstate, r_bh), /* %bh */
};
#define REG8(id, ...)               (*((u8 *)self + mach_breg_offset[id]))
#define REG16(id)                   self->r_gpregsw[(id)*2]
#define REG32(id)                   self->r_gpregsl[id]
#define EMU86_SETREGW(regno, value) REG16(regno) = (u16)(value)
#define EMU86_SETREGL(regno, value) REG32(regno) = (u32)(value)
#endif /* !__x86_64__ */
#define EMU86_GETREGB(regno, op_flags)        REG8(regno, op_flags)
#define EMU86_SETREGB(regno, value, op_flags) REG8(regno, op_flags) = (u8)(value)
#define EMU86_GETREGW(regno)                  REG16(regno)
#define EMU86_GETREGL(regno)                  REG32(regno)

#define EMU86_GETIP()           (u16)self->r_ip
#define EMU86_SETIP(v)          self->r_ip = (u16)(v)
#define EMU86_GETEIP()          (u32)self->r_eip
#define EMU86_SETEIP(v)         self->r_eip = (u32)(v)
#ifdef __x86_64__
#define EMU86_GETRIP()          (u64)self->r_rip
#define EMU86_SETRIP(v)         self->r_rip = (u64)(v)
#endif /* __x86_64__ */
#define EMU86_GETAL()           self->r_al
#define EMU86_GETCL()           self->r_cl
#define EMU86_GETDL()           self->r_dl
#define EMU86_GETBL()           self->r_bl
#define EMU86_SETAL(v)          self->r_al = (u8)(v)
#define EMU86_SETCL(v)          self->r_cl = (u8)(v)
#define EMU86_SETDL(v)          self->r_dl = (u8)(v)
#define EMU86_SETBL(v)          self->r_bl = (u8)(v)
#define EMU86_GETAH()           self->r_ah
#define EMU86_GETCH()           self->r_ch
#define EMU86_GETDH()           self->r_dh
#define EMU86_GETBH()           self->r_bh
#define EMU86_SETAH(v)          self->r_ah = (u8)(v)
#define EMU86_SETCH(v)          self->r_ch = (u8)(v)
#define EMU86_SETDH(v)          self->r_dh = (u8)(v)
#define EMU86_SETBH(v)          self->r_bh = (u8)(v)
#define EMU86_GETAX()           self->r_ax
#define EMU86_GETCX()           self->r_cx
#define EMU86_GETDX()           self->r_dx
#define EMU86_GETBX()           self->r_bx
#define EMU86_GETSP()           self->r_sp
#define EMU86_GETBP()           self->r_bp
#define EMU86_GETSI()           self->r_si
#define EMU86_GETDI()           self->r_di
#define EMU86_SETAX(v)          self->r_eax = (u32)(u16)(v)
#define EMU86_SETCX(v)          self->r_ecx = (u32)(u16)(v)
#define EMU86_SETDX(v)          self->r_edx = (u32)(u16)(v)
#define EMU86_SETBX(v)          self->r_ebx = (u32)(u16)(v)
#define EMU86_SETSP(v)          self->r_esp = (u32)(u16)(v)
#define EMU86_SETBP(v)          self->r_ebp = (u32)(u16)(v)
#define EMU86_SETSI(v)          self->r_esi = (u32)(u16)(v)
#define EMU86_SETDI(v)          self->r_edi = (u32)(u16)(v)
#define EMU86_GETEAX()          self->r_eax
#define EMU86_GETECX()          self->r_ecx
#define EMU86_GETEDX()          self->r_edx
#define EMU86_GETEBX()          self->r_ebx
#define EMU86_GETESP()          self->r_esp
#define EMU86_GETEBP()          self->r_ebp
#define EMU86_GETESI()          self->r_esi
#define EMU86_GETEDI()          self->r_edi
#define EMU86_SETEAX(v)         self->r_eax = (u32)(v)
#define EMU86_SETECX(v)         self->r_ecx = (u32)(v)
#define EMU86_SETEDX(v)         self->r_edx = (u32)(v)
#define EMU86_SETEBX(v)         self->r_ebx = (u32)(v)
#define EMU86_SETESP(v)         self->r_esp = (u32)(v)
#define EMU86_SETEBP(v)         self->r_ebp = (u32)(v)
#define EMU86_SETESI(v)         self->r_esi = (u32)(v)
#define EMU86_SETEDI(v)         self->r_edi = (u32)(v)
#ifdef __x86_64__
#define EMU86_GETRAX()          self->r_rax
#define EMU86_GETRCX()          self->r_rcx
#define EMU86_GETRDX()          self->r_rdx
#define EMU86_GETRBX()          self->r_rbx
#define EMU86_GETRSP()          self->r_rsp
#define EMU86_GETRBP()          self->r_rbp
#define EMU86_GETRSI()          self->r_rsi
#define EMU86_GETRDI()          self->r_rdi
#define EMU86_SETRAX(v)         self->r_rax = (u64)(v)
#define EMU86_SETRCX(v)         self->r_rcx = (u64)(v)
#define EMU86_SETRDX(v)         self->r_rdx = (u64)(v)
#define EMU86_SETRBX(v)         self->r_rbx = (u64)(v)
#define EMU86_SETRSP(v)         self->r_rsp = (u64)(v)
#define EMU86_SETRBP(v)         self->r_rbp = (u64)(v)
#define EMU86_SETRSI(v)         self->r_rsi = (u64)(v)
#define EMU86_SETRDI(v)         self->r_rdi = (u64)(v)
#endif /* __x86_64__ */
#define EMU86_GETPAX(...)       self->r_pax
#define EMU86_GETPCX(...)       self->r_pcx
#define EMU86_GETPDX(...)       self->r_pdx
#define EMU86_GETPBX(...)       self->r_pbx
#define EMU86_GETPSP(...)       self->r_psp
#define EMU86_GETPBP(...)       self->r_pbp
#define EMU86_GETPSI(...)       self->r_psi
#define EMU86_GETPDI(...)       self->r_pdi
#define EMU86_SETPAX(v, ...)    self->r_pax = (uintptr_t)(v)
#define EMU86_SETPCX(v, ...)    self->r_pcx = (uintptr_t)(v)
#define EMU86_SETPDX(v, ...)    self->r_pdx = (uintptr_t)(v)
#define EMU86_SETPBX(v, ...)    self->r_pbx = (uintptr_t)(v)
#define EMU86_SETPSP(v, ...)    self->r_psp = (uintptr_t)(v)
#define EMU86_SETPBP(v, ...)    self->r_pbp = (uintptr_t)(v)
#define EMU86_SETPSI(v, ...)    self->r_psi = (uintptr_t)(v)
#define EMU86_SETPDI(v, ...)    self->r_pdi = (uintptr_t)(v)


/* Memory accessors */
#define DEFINE_MEMORY_FUNCTIONS(bwlq, T)                                                \
	PRIVATE WUNUSED NONNULL((1)) T KCALL                                                \
	rtm_read##bwlq(struct rtm_machstate *__restrict self, NCX void const *addr) {      \
		T result;                                                                       \
		rtm_memory_read(&self->r_mem, addr, &result, sizeof(T));                        \
		return result;                                                                  \
	}                                                                                   \
	PRIVATE NONNULL((1)) void KCALL                                                     \
	rtm_write##bwlq(struct rtm_machstate *__restrict self, NCX void *addr, T value) {  \
		rtm_memory_write(&self->r_mem, addr, &value, sizeof(T));                        \
	}                                                                                   \
	PRIVATE WUNUSED NONNULL((1)) T KCALL                                                \
	rtm_xch##bwlq(struct rtm_machstate *__restrict self, NCX void *addr, T value) {    \
		T result;                                                                       \
		rtm_memory_read(&self->r_mem, addr, &result, sizeof(T));                        \
		rtm_memory_write(&self->r_mem, addr, &value, sizeof(T));                        \
		return result;                                                                  \
	}                                                                                   \
	PRIVATE NONNULL((1)) T KCALL                                                        \
	rtm_fetchadd##bwlq(struct rtm_machstate *__restrict self, NCX void *addr, T rhs) { \
		T result, newval;                                                               \
		rtm_memory_read(&self->r_mem, addr, &result, sizeof(T));                        \
		newval = result + rhs;                                                          \
		rtm_memory_write(&self->r_mem, addr, &newval, sizeof(T));                       \
		return result;                                                                  \
	}                                                                                   \
	PRIVATE NONNULL((1)) T KCALL                                                        \
	rtm_fetchsub##bwlq(struct rtm_machstate *__restrict self, NCX void *addr, T rhs) { \
		T result, newval;                                                               \
		rtm_memory_read(&self->r_mem, addr, &result, sizeof(T));                        \
		newval = result - rhs;                                                          \
		rtm_memory_write(&self->r_mem, addr, &newval, sizeof(T));                       \
		return result;                                                                  \
	}                                                                                   \
	PRIVATE NONNULL((1)) T KCALL                                                        \
	rtm_fetchand##bwlq(struct rtm_machstate *__restrict self, NCX void *addr, T rhs) { \
		T result, newval;                                                               \
		rtm_memory_read(&self->r_mem, addr, &result, sizeof(T));                        \
		newval = result & rhs;                                                          \
		rtm_memory_write(&self->r_mem, addr, &newval, sizeof(T));                       \
		return result;                                                                  \
	}                                                                                   \
	PRIVATE NONNULL((1)) T KCALL                                                        \
	rtm_fetchor##bwlq(struct rtm_machstate *__restrict self, NCX void *addr, T rhs) {  \
		T result, newval;                                                               \
		rtm_memory_read(&self->r_mem, addr, &result, sizeof(T));                        \
		newval = result | rhs;                                                          \
		rtm_memory_write(&self->r_mem, addr, &newval, sizeof(T));                       \
		return result;                                                                  \
	}                                                                                   \
	PRIVATE NONNULL((1)) T KCALL                                                        \
	rtm_fetchxor##bwlq(struct rtm_machstate *__restrict self, NCX void *addr, T rhs) { \
		T result, newval;                                                               \
		rtm_memory_read(&self->r_mem, addr, &result, sizeof(T));                        \
		newval = result ^ rhs;                                                          \
		rtm_memory_write(&self->r_mem, addr, &newval, sizeof(T));                       \
		return result;                                                                  \
	}
DEFINE_MEMORY_FUNCTIONS(b, u8)
DEFINE_MEMORY_FUNCTIONS(w, u16)
DEFINE_MEMORY_FUNCTIONS(l, u32)
#ifdef __x86_64__
DEFINE_MEMORY_FUNCTIONS(q, u64)
#endif /* __x86_64__ */
#undef DEFINE_MEMORY_FUNCTIONS

#define DEFINE_CMPXCH_FUNCTIONS(bwlq, T)                              \
	PRIVATE NONNULL((1)) T KCALL                                      \
	rtm_cmpxch##bwlq(struct rtm_machstate *__restrict self,           \
	                 NCX void *addr, T oldval, T newval) {           \
		T result;                                                     \
		rtm_memory_read(&self->r_mem, addr, &result, sizeof(T));      \
		if (CMPXCH_OPERANDS_EQ(result, oldval))                       \
			rtm_memory_write(&self->r_mem, addr, &newval, sizeof(T)); \
		return result;                                                \
	}
#define CMPXCH_OPERANDS_EQ(a, b) a == b
DEFINE_CMPXCH_FUNCTIONS(b, u8)
DEFINE_CMPXCH_FUNCTIONS(w, u16)
DEFINE_CMPXCH_FUNCTIONS(l, u32)
DEFINE_CMPXCH_FUNCTIONS(q, u64)
#undef CMPXCH_OPERANDS_EQ
#ifdef __x86_64__
#define CMPXCH_OPERANDS_EQ(a, b) (bcmp(&a, &b, 16) == 0)
DEFINE_CMPXCH_FUNCTIONS(x, uint128_t)
#undef CMPXCH_OPERANDS_EQ
#endif /* __x86_64__ */
#undef DEFINE_CMPXCH_FUNCTIONS

#define EMU86_MEMREADB(addr)                                                  rtm_readb(self, (void *)(uintptr_t)(addr))
#define EMU86_MEMREADW(addr)                                                  rtm_readw(self, (void *)(uintptr_t)(addr))
#define EMU86_MEMREADL(addr)                                                  rtm_readl(self, (void *)(uintptr_t)(addr))
#define EMU86_MEMWRITEB(addr, v)                                              rtm_writeb(self, (void *)(uintptr_t)(addr), (u8)(v))
#define EMU86_MEMWRITEW(addr, v)                                              rtm_writew(self, (void *)(uintptr_t)(addr), (u16)(v))
#define EMU86_MEMWRITEL(addr, v)                                              rtm_writel(self, (void *)(uintptr_t)(addr), (u32)(v))
#define EMU86_MEM_ATOMIC_CMPXCH_OR_WRITEB(addr, oldval, newval, force_atomic) (rtm_writeb(self, (void *)(uintptr_t)(addr), (u8)(newval)), true)
#define EMU86_MEM_ATOMIC_CMPXCH_OR_WRITEW(addr, oldval, newval, force_atomic) (rtm_writew(self, (void *)(uintptr_t)(addr), (u16)(newval)), true)
#define EMU86_MEM_ATOMIC_CMPXCH_OR_WRITEL(addr, oldval, newval, force_atomic) (rtm_writel(self, (void *)(uintptr_t)(addr), (u32)(newval)), true)
#define EMU86_MEM_ATOMIC_XCHB(addr, addend, force_atomic)                     rtm_xchb(self, (void *)(uintptr_t)(addr), (u8)(addend))
#define EMU86_MEM_ATOMIC_XCHW(addr, addend, force_atomic)                     rtm_xchw(self, (void *)(uintptr_t)(addr), (u16)(addend))
#define EMU86_MEM_ATOMIC_XCHL(addr, addend, force_atomic)                     rtm_xchl(self, (void *)(uintptr_t)(addr), (u32)(addend))
#define EMU86_MEM_ATOMIC_FETCHADDB(addr, addend, force_atomic)                rtm_fetchaddb(self, (void *)(uintptr_t)(addr), (u8)(addend))
#define EMU86_MEM_ATOMIC_FETCHADDW(addr, addend, force_atomic)                rtm_fetchaddw(self, (void *)(uintptr_t)(addr), (u16)(addend))
#define EMU86_MEM_ATOMIC_FETCHADDL(addr, addend, force_atomic)                rtm_fetchaddl(self, (void *)(uintptr_t)(addr), (u32)(addend))
#define EMU86_MEM_ATOMIC_FETCHSUBB(addr, addend, force_atomic)                rtm_fetchsubb(self, (void *)(uintptr_t)(addr), (u8)(addend))
#define EMU86_MEM_ATOMIC_FETCHSUBW(addr, addend, force_atomic)                rtm_fetchsubw(self, (void *)(uintptr_t)(addr), (u16)(addend))
#define EMU86_MEM_ATOMIC_FETCHSUBL(addr, addend, force_atomic)                rtm_fetchsubl(self, (void *)(uintptr_t)(addr), (u32)(addend))
#define EMU86_MEM_ATOMIC_FETCHANDB(addr, addend, force_atomic)                rtm_fetchandb(self, (void *)(uintptr_t)(addr), (u8)(addend))
#define EMU86_MEM_ATOMIC_FETCHANDW(addr, addend, force_atomic)                rtm_fetchandw(self, (void *)(uintptr_t)(addr), (u16)(addend))
#define EMU86_MEM_ATOMIC_FETCHANDL(addr, addend, force_atomic)                rtm_fetchandl(self, (void *)(uintptr_t)(addr), (u32)(addend))
#define EMU86_MEM_ATOMIC_FETCHORB(addr, addend, force_atomic)                 rtm_fetchorb(self, (void *)(uintptr_t)(addr), (u8)(addend))
#define EMU86_MEM_ATOMIC_FETCHORW(addr, addend, force_atomic)                 rtm_fetchorw(self, (void *)(uintptr_t)(addr), (u16)(addend))
#define EMU86_MEM_ATOMIC_FETCHORL(addr, addend, force_atomic)                 rtm_fetchorl(self, (void *)(uintptr_t)(addr), (u32)(addend))
#define EMU86_MEM_ATOMIC_FETCHXORB(addr, addend, force_atomic)                rtm_fetchxorb(self, (void *)(uintptr_t)(addr), (u8)(addend))
#define EMU86_MEM_ATOMIC_FETCHXORW(addr, addend, force_atomic)                rtm_fetchxorw(self, (void *)(uintptr_t)(addr), (u16)(addend))
#define EMU86_MEM_ATOMIC_FETCHXORL(addr, addend, force_atomic)                rtm_fetchxorl(self, (void *)(uintptr_t)(addr), (u32)(addend))
#define EMU86_MEM_ATOMIC_CMPXCHB(addr, oldval, newval, force_atomic)          rtm_cmpxchb(self, (void *)(uintptr_t)(addr), (u8)(oldval), (u8)(newval))
#define EMU86_MEM_ATOMIC_CMPXCHW(addr, oldval, newval, force_atomic)          rtm_cmpxchw(self, (void *)(uintptr_t)(addr), (u16)(oldval), (u16)(newval))
#define EMU86_MEM_ATOMIC_CMPXCHL(addr, oldval, newval, force_atomic)          rtm_cmpxchl(self, (void *)(uintptr_t)(addr), (u32)(oldval), (u32)(newval))
#define EMU86_MEM_ATOMIC_CMPXCHQ(addr, oldval, newval, force_atomic)          rtm_cmpxchq(self, (void *)(uintptr_t)(addr), (u64)(oldval), (u64)(newval))
#ifdef __x86_64__
#define EMU86_MEMREADQ(addr)                                                  rtm_readq(self, (void *)(uintptr_t)(addr))
#define EMU86_MEMWRITEQ(addr, v)                                              rtm_writeq(self, (void *)(uintptr_t)(addr), (u64)(v))
#define EMU86_MEM_ATOMIC_CMPXCH_OR_WRITEQ(addr, oldval, newval, force_atomic) (rtm_writeq(self, (void *)(uintptr_t)(addr), (u64)(newval)), true)
#define EMU86_MEM_ATOMIC_XCHQ(addr, addend, force_atomic)                     rtm_xchq(self, (void *)(uintptr_t)(addr), (u64)(addend))
#define EMU86_MEM_ATOMIC_FETCHADDQ(addr, addend, force_atomic)                rtm_fetchaddq(self, (void *)(uintptr_t)(addr), (u64)(addend))
#define EMU86_MEM_ATOMIC_FETCHSUBQ(addr, addend, force_atomic)                rtm_fetchsubq(self, (void *)(uintptr_t)(addr), (u64)(addend))
#define EMU86_MEM_ATOMIC_FETCHANDQ(addr, addend, force_atomic)                rtm_fetchandq(self, (void *)(uintptr_t)(addr), (u64)(addend))
#define EMU86_MEM_ATOMIC_FETCHORQ(addr, addend, force_atomic)                 rtm_fetchorq(self, (void *)(uintptr_t)(addr), (u64)(addend))
#define EMU86_MEM_ATOMIC_FETCHXORQ(addr, addend, force_atomic)                rtm_fetchxorq(self, (void *)(uintptr_t)(addr), (u64)(addend))
#define EMU86_MEM_ATOMIC_CMPXCHX(addr, oldval, newval, force_atomic)          rtm_cmpxchx(self, (void *)(uintptr_t)(addr), oldval, newval)
#endif /* __x86_64__ */

#define EMU86_VALIDATE_READABLE(addr, num_bytes)  (void)0
#define EMU86_VALIDATE_WRITABLE(addr, num_bytes)  (void)0
#define EMU86_VALIDATE_READWRITE(addr, num_bytes) (void)0
#define EMU86_VALIDATE_READABLE_IS_NOOP  1
#define EMU86_VALIDATE_WRITABLE_IS_NOOP  1
#define EMU86_VALIDATE_READWRITE_IS_NOOP 1

/* Verify that we only ever run user-space code in user-space
 * TODO: When the  PC-pointer is  part  of kernel-space,  we  should
 *       instead dispatch to UKERN and emulate `userkern_syscall()'! */
#ifdef CONFIG_MODRTM_USERSPACE_ONLY
#define EMU86_EMULATE_VALIDATE_BEFORE_OPCODE_DECODE(start_pc) \
	validate_executable((void *)(start_pc))
#else /* CONFIG_MODRTM_USERSPACE_ONLY */
#define EMU86_EMULATE_VALIDATE_BEFORE_OPCODE_DECODE(start_pc) \
	do {                                                      \
		if (mach.r_mem.rm_mem_avl.rm_chkuser)                 \
			validate_executable((void *)(start_pc));          \
	}	__WHILE0
#endif /* !CONFIG_MODRTM_USERSPACE_ONLY */


/* RTM instruction emulation to allow for nesting. */
#define EMU86_EMULATE_RETURN_AFTER_XBEGIN(fallback_ip) \
	do {                                               \
		if unlikely(self->r_nesting == (uintptr_t)-1)  \
			return ABORT_WITH(_XABORT_CAPACITY);       \
		++self->r_nesting;                             \
		return X86_RTM_STATUS_CONTINUE;                \
	}	__WHILE0
#define EMU86_EMULATE_RETURN_AFTER_XABORT(code) \
	return ABORT_WITH(_XABORT_EXPLICIT | (((u32)(code) << _XABORT_CODE_S) & _XABORT_CODE_M))
#define EMU86_EMULATE_RETURN_AFTER_XEND()   \
	do {                                    \
		if (!self->r_nesting)               \
			return X86_RTM_STATUS_COMPLETE; \
		--self->r_nesting;                  \
		return X86_RTM_STATUS_CONTINUE;     \
	}	__WHILE0
#define EMU86_EMULATE_XTEST()      1
#define EMU86_EMULATE_XTEST_IS_ONE 1

/* Handle the current exception by returning the `_XABORT_*' exit code. */
PRIVATE u32 KCALL rtm_handle_exception(void) {
	u32 result;
	except_class_t cls = except_class();
	if (EXCEPTCLASS_ISRTLPRIORITY(cls))
		RETHROW();
#ifndef NDEBUG
	except_printf("Emulating RTM");
#endif /* !NDEBUG */
	result = _XABORT_FAILED;
	if (cls == EXCEPT_CLASS(EXCEPT_CODEOF(E_BADALLOC)))
		result = _XABORT_CAPACITY;
	return result;
}


PRIVATE ATTR_RETNONNULL NONNULL((1)) struct icpustate *FCALL
x86_emulate_xbegin(struct icpustate *__restrict state,
                   void const *fallback_ip) {
	struct rtm_machstate mach;
	x86_rtm_status_t status;
	mach.r_icstate = state;
	rtm_memory_init(&mach.r_mem, icpustate_isuser(state));
	mach.r_pax = gpregs_getpax(&state->ics_gpregs);
	mach.r_pcx = gpregs_getpcx(&state->ics_gpregs);
	mach.r_pdx = gpregs_getpdx(&state->ics_gpregs);
	mach.r_pbx = gpregs_getpbx(&state->ics_gpregs);
	mach.r_psp = icpustate_getpsp(state);
	mach.r_pbp = gpregs_getpbp(&state->ics_gpregs);
	mach.r_psi = gpregs_getpsi(&state->ics_gpregs);
	mach.r_pdi = gpregs_getpdi(&state->ics_gpregs);
#ifdef __x86_64__
	mach.r_r8  = state->ics_gpregs.gp_r8;
	mach.r_r9  = state->ics_gpregs.gp_r9;
	mach.r_r10 = state->ics_gpregs.gp_r10;
	mach.r_r11 = state->ics_gpregs.gp_r11;
	mach.r_r12 = state->ics_gpregs.gp_r12;
	mach.r_r13 = state->ics_gpregs.gp_r13;
	mach.r_r14 = state->ics_gpregs.gp_r14;
	mach.r_r15 = state->ics_gpregs.gp_r15;
#endif /* __x86_64__ */
	mach.r_pip    = icpustate_getpip(state);
	mach.r_pflags = icpustate_getpflags(state);
	mach.r_fsbase = (uintptr_t)-1;
	mach.r_gsbase = (uintptr_t)-1;
#ifndef __x86_64__
	mach.r_esbase = (uintptr_t)-1;
	mach.r_csbase = i386_getsegment_base(state, EMU86_R_CS);
	mach.r_ssbase = i386_getsegment_base(state, EMU86_R_SS);
	mach.r_dsbase = i386_getsegment_base(state, EMU86_R_DS);
#endif /* !__x86_64__ */
	mach.r_nesting = 0;
	for (;;) {
		TRY {
#ifdef HAVE_RTM_EMULATION_TRACE
			printk(KERN_TRACE "[rtm] Emulate %p: ",
			       (void *)mach.r_pip);
			disasm_single(&syslog_printer, SYSLOG_LEVEL_TRACE, (void *)mach.r_pip,
			              disassembler_target_from_icpustate(mach.r_icstate),
			              DISASSEMBLER_FNOADDR);
			printk(KERN_TRACE "\t# "
			                  "a=%#" PRIxPTR " "
			                  "c=%#" PRIxPTR " "
			                  "d=%#" PRIxPTR " "
			                  "b=%#" PRIxPTR " "
			                  "sp=%#" PRIxPTR " "
			                  "bp=%#" PRIxPTR " "
			                  "si=%#" PRIxPTR " "
			                  "di=%#" PRIxPTR
#ifdef __x86_64__
			                  " "
			                  "8=%#" PRIxPTR " "
			                  "9=%#" PRIxPTR " "
			                  "10=%#" PRIxPTR " "
			                  "11=%#" PRIxPTR " "
			                  "12=%#" PRIxPTR " "
			                  "13=%#" PRIxPTR " "
			                  "14=%#" PRIxPTR " "
			                  "15=%#" PRIxPTR
#endif /* __x86_64__ */
			                  "\n",
			       mach.r_pax, mach.r_pcx, mach.r_pdx, mach.r_pbx,
			       mach.r_psp, mach.r_pbp, mach.r_psi, mach.r_pdi
#ifdef __x86_64__
			       ,
			       mach.r_r8, mach.r_r9, mach.r_r10, mach.r_r11,
			       mach.r_r12, mach.r_r13, mach.r_r14, mach.r_r15
#endif /* __x86_64__ */
			       );
#endif /* HAVE_RTM_EMULATION_TRACE */
			/* Execute the next instruction */
			status = x86_emulate_rtm_instruction(&mach);
		} EXCEPT {
			mach.r_pax = rtm_handle_exception();
			goto rtm_failure;
		}
		/* Check the instruction status code. */
		if (status != X86_RTM_STATUS_CONTINUE)
			break;
		/* Serve user-level  interrupts between  instructions.
		 * This is necessary to ensure that stuff like  CRTL+C
		 * still works properly when the user-program contains
		 * an infinite loop. */
		task_serve();
	}
	/* Check if RTM instruction emulation indicates a successful completion. */
	if (status != X86_RTM_STATUS_COMPLETE)
		goto rtm_failure;
	TRY {
		/* Try to apply the new memory image to main RAM. */
		if (!rtm_memory_apply(&mach.r_mem)) {
			mach.r_pax = _XABORT_CONFLICT;
			goto rtm_failure;
		}
	} EXCEPT {
		mach.r_pax = rtm_handle_exception();
		goto rtm_failure;
	}
	rtm_memory_fini(&mach.r_mem);
	/* Success! -> Load the updated register state. */
	gpregs_setpax(&state->ics_gpregs, mach.r_pax);
	gpregs_setpcx(&state->ics_gpregs, mach.r_pcx);
	gpregs_setpdx(&state->ics_gpregs, mach.r_pdx);
	gpregs_setpbx(&state->ics_gpregs, mach.r_pbx);
	gpregs_setpbp(&state->ics_gpregs, mach.r_pbp);
	gpregs_setpsi(&state->ics_gpregs, mach.r_psi);
	gpregs_setpdi(&state->ics_gpregs, mach.r_pdi);
#ifdef __x86_64__
	state->ics_gpregs.gp_r8  = mach.r_r8;
	state->ics_gpregs.gp_r9  = mach.r_r9;
	state->ics_gpregs.gp_r10 = mach.r_r10;
	state->ics_gpregs.gp_r11 = mach.r_r11;
	state->ics_gpregs.gp_r12 = mach.r_r12;
	state->ics_gpregs.gp_r13 = mach.r_r13;
	state->ics_gpregs.gp_r14 = mach.r_r14;
	state->ics_gpregs.gp_r15 = mach.r_r15;
#endif /* __x86_64__ */
	icpustate_setpip(state, mach.r_pip);
	icpustate_setpflags(state, mach.r_pflags);
#ifdef __x86_64__
	icpustate_setpsp(state, mach.r_psp);
#else /* __x86_64__ */
	state = icpustate_setpsp_p(state, mach.r_psp);
#endif /* !__x86_64__ */
	return state;
rtm_failure:
	rtm_memory_fini(&mach.r_mem);
	if (mach.r_nesting > 0)
		mach.r_pax |= _XABORT_NESTED;
	/* Copy the RTM status code from the machine register state. */
	state->ics_gpregs.gp_Pax = mach.r_pax;
	/* Redirect execution to resume at `fallback_ip' */
	icpustate_setpc(state, fallback_ip);
	return state;
}

INTERN struct mrtm_driver_hooks rtm_hooks = {
	.rdh_driver = &drv_self,
	.rdh_hooks  = {
		.rh_xbegin = &x86_emulate_xbegin
	}
};


#ifndef __INTELLISENSE__
#undef THROW
#define THROW DONT_THROW_EXCEPTIONS
#include "../../../../../include/libemu86/emulate.c.inl"
#endif /* !__INTELLISENSE__ */

DECL_END

#endif /* !GUARD_MODRTM_ARCH_I386_RTM_C */
