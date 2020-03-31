/*[[[magic
// Optimize this file for size
local opt = options.setdefault("GCC.options",[]);
opt.removeif([](e) -> e.startswith("-O"));
opt.append("-Os");
]]]*/
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_HANDLE_BAD_USAGE_C
#define GUARD_KERNEL_CORE_ARCH_I386_HANDLE_BAD_USAGE_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING 1

#include "decode.h" /* TODO: Remove me! */
/**/

#ifdef CONFIG_USE_HANDLE_BAD_USAGE
#include <hybrid/host.h>

#ifdef __x86_64__
#define CONFIG_LIBEMU86_WANT_16BIT 0
#define CONFIG_LIBEMU86_WANT_32BIT 1
#define CONFIG_LIBEMU86_WANT_64BIT 1
#else /* __x86_64__ */
#define CONFIG_LIBEMU86_WANT_16BIT 1
#define CONFIG_LIBEMU86_WANT_32BIT 1
#define CONFIG_LIBEMU86_WANT_64BIT 0
#endif /* !__x86_64__ */

#include <kernel/compiler.h>

#include <kernel/arch/cpuid.h>
#include <kernel/debugtrap.h>
#include <kernel/emulock.h>
#include <kernel/except.h>
#include <kernel/gdt.h>
#include <kernel/printk.h>
#include <kernel/restart-interrupt.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/except-handler.h>
#include <sched/pid.h>
#include <sched/rpc.h>
#include <sched/task.h>
#include <sched/userkern.h>

#include <hybrid/overflow.h>

#include <asm/cpu-flags.h>
#include <asm/registers.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <assert.h>
#include <limits.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>

#include <libemu86/emu86.h>
#include <libinstrlen/instrlen.h>

#ifndef CONFIG_NO_USERKERN_SEGMENT
#include <libvio/access.h>
#include <libviocore/viocore.h>
#endif /* !CONFIG_NO_USERKERN_SEGMENT */

#ifdef __x86_64__
#include <int128.h>
#endif /* __x86_64__ */

DECL_BEGIN

#define BAD_USAGE_REASON_UD  0x0600
#define BAD_USAGE_REASON_SS  0x0c00
#define BAD_USAGE_REASON_GFP 0x0d00
#define BAD_USAGE_INTNO(usage)  (((usage) & 0xff00) >> 8)
#define BAD_USAGE_REASON(usage) ((usage) & 0xff00)
#define BAD_USAGE_ECODE(usage)  ((usage) & 0x00ff) /* FIXME: Segment selector error codes can be up to 16 bits (not just 8)! */

PRIVATE ATTR_RETNONNULL NONNULL((1)) struct icpustate *FCALL
x86_handle_bad_usage(struct icpustate *__restrict state, u16 usage);


#define EMU86_EMULATE_CONFIG_DONT_USE_HYBRID_BIT 1
#define EMU86_EMULATE_CONFIG_DONT_USE_HYBRID_BSWAP 1
#define EMU86_EMULATE_CONFIG_ONLY_MEMORY 0
#define EMU86_EMULATE_CONFIG_CHECKUSER 1
#define EMU86_EMULATE_CONFIG_CHECKERROR 1
#define EMU86_EMULATE_CONFIG_ONLY_CHECKERROR 1
#define EMU86_EMULATE_CONFIG_ONLY_CHECKERROR_NO_BASIC 1
#define EMU86_EMULATE_CONFIG_FSGSBASE_32BIT 1
#define EMU86_EMULATE_CONFIG_ALLOW_USER_STAC_CLAC 1

/* Configure for which instructions emulation should be attempted.
 * Any instruction enabled here will be emulated if not supported natively! */

#define EMU86_EMULATE_CONFIG_WANT_ADCX          1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_ADOX          1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_MULX          1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_ANDN          1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_ARITH         0
#define EMU86_EMULATE_CONFIG_WANT_ARITH2        0
#define EMU86_EMULATE_CONFIG_WANT_DAA           0
#define EMU86_EMULATE_CONFIG_WANT_DAS           0
#define EMU86_EMULATE_CONFIG_WANT_AAA           0
#define EMU86_EMULATE_CONFIG_WANT_AAS           0
#define EMU86_EMULATE_CONFIG_WANT_AAM           0
#define EMU86_EMULATE_CONFIG_WANT_AAD           0
#define EMU86_EMULATE_CONFIG_WANT_TZCNT         1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_BSF           0
#define EMU86_EMULATE_CONFIG_WANT_LZCNT         1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_BSR           0
#define EMU86_EMULATE_CONFIG_WANT_BITTEST       0
#define EMU86_EMULATE_CONFIG_WANT_BLSR          1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_BLSMSK        1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_BLSI          1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_BOUND         0
#define EMU86_EMULATE_CONFIG_WANT_BSWAP         (!CONFIG_LIBEMU86_WANT_64BIT) /* Only available on 486+ (emulate in 32-bit mode) */
#define EMU86_EMULATE_CONFIG_WANT_CALL          0
#define EMU86_EMULATE_CONFIG_WANT_CBW           0
#define EMU86_EMULATE_CONFIG_WANT_CWD           0
#define EMU86_EMULATE_CONFIG_WANT_SETCC         (!CONFIG_LIBEMU86_WANT_64BIT) /* Only available on 486+ (emulate in 32-bit mode) */
#define EMU86_EMULATE_CONFIG_WANT_CMOVCC        (!CONFIG_LIBEMU86_WANT_64BIT) /* Only available on 486+ (emulate in 32-bit mode) */
#define EMU86_EMULATE_CONFIG_WANT_CMPS          0
#if (defined(CONFIG_EMULOCK_HAVE_CMPXCHB) && defined(CONFIG_EMULOCK_HAVE_CMPXCHW) && \
     defined(CONFIG_EMULOCK_HAVE_CMPXCHL) &&                                         \
     (!CONFIG_LIBEMU86_WANT_64BIT || defined(CONFIG_EMULOCK_HAVE_CMPXCHQ)))
#define EMU86_EMULATE_CONFIG_WANT_CMPXCHG       1
#else /* ... */
#define EMU86_EMULATE_CONFIG_WANT_CMPXCHG       0
#endif /* !... */
#if defined(__x86_64__) || defined(CONFIG_EMULOCK_HAVE_CMPXCHQ)
#define EMU86_EMULATE_CONFIG_WANT_CMPXCHG8B     1
#else /* __x86_64__ || CONFIG_EMULOCK_HAVE_CMPXCHQ */
#define EMU86_EMULATE_CONFIG_WANT_CMPXCHG8B     0
#endif /* !__x86_64__ && !CONFIG_EMULOCK_HAVE_CMPXCHQ */
#if CONFIG_LIBEMU86_WANT_64BIT && defined(CONFIG_EMULOCK_HAVE_CMPXCHX)
#define EMU86_EMULATE_CONFIG_WANT_CMPXCHG16B    1
#else /* CONFIG_LIBEMU86_WANT_64BIT && CONFIG_EMULOCK_HAVE_CMPXCHX */
#define EMU86_EMULATE_CONFIG_WANT_CMPXCHG16B    0
#endif /* !CONFIG_LIBEMU86_WANT_64BIT || !CONFIG_EMULOCK_HAVE_CMPXCHX */
#define EMU86_EMULATE_CONFIG_WANT_CPUID         (!CONFIG_LIBEMU86_WANT_64BIT) /* Only available on 486+ (emulate in 32-bit mode) */
#define EMU86_EMULATE_CONFIG_WANT_ENTER         0
#define EMU86_EMULATE_CONFIG_WANT_INVD          (!CONFIG_LIBEMU86_WANT_64BIT) /* Only available on 486+ (emulate in 32-bit mode) */
#define EMU86_EMULATE_CONFIG_WANT_WBINVD        (!CONFIG_LIBEMU86_WANT_64BIT) /* Only available on 486+ (emulate in 32-bit mode) */
#define EMU86_EMULATE_CONFIG_WANT_PREFETCHW     1 /* TODO: Check if this instruction always exists on x86_64 */
#define EMU86_EMULATE_CONFIG_WANT_PREFETCHNTA   1 /* TODO: Check if this instruction always exists on x86_64 */
#define EMU86_EMULATE_CONFIG_WANT_PREFETCH0     1 /* TODO: Check if this instruction always exists on x86_64 */
#define EMU86_EMULATE_CONFIG_WANT_PREFETCH1     1 /* TODO: Check if this instruction always exists on x86_64 */
#define EMU86_EMULATE_CONFIG_WANT_PREFETCH2     1 /* TODO: Check if this instruction always exists on x86_64 */
#define EMU86_EMULATE_CONFIG_WANT_CLDEMOTE      1 /* TODO: Check if this instruction always exists on x86_64 */
#define EMU86_EMULATE_CONFIG_WANT_HLT           0
#define EMU86_EMULATE_CONFIG_WANT_INC_REG       0
#define EMU86_EMULATE_CONFIG_WANT_DEC_REG       0
#define EMU86_EMULATE_CONFIG_WANT_INT1          0
#define EMU86_EMULATE_CONFIG_WANT_INT3          0
#define EMU86_EMULATE_CONFIG_WANT_INT           0
#define EMU86_EMULATE_CONFIG_WANT_INTO          0
#define EMU86_EMULATE_CONFIG_WANT_IO            0
#define EMU86_EMULATE_CONFIG_WANT_IRET          0 /* TODO: vm86 support */
#define EMU86_EMULATE_CONFIG_WANT_JCC_DISP8     0
#define EMU86_EMULATE_CONFIG_WANT_JCC_DISP32    0
#define EMU86_EMULATE_CONFIG_WANT_JCXZ          0
#define EMU86_EMULATE_CONFIG_WANT_JMP_DISP8     0
#define EMU86_EMULATE_CONFIG_WANT_JMP_DISP32    0
#define EMU86_EMULATE_CONFIG_WANT_LCALL         0
#define EMU86_EMULATE_CONFIG_WANT_LEA           0
#define EMU86_EMULATE_CONFIG_WANT_LEAVE         0
#define EMU86_EMULATE_CONFIG_WANT_LJMP          0
#define EMU86_EMULATE_CONFIG_WANT_LODS          0
#define EMU86_EMULATE_CONFIG_WANT_LOOPNE        0
#define EMU86_EMULATE_CONFIG_WANT_LOOPE         0
#define EMU86_EMULATE_CONFIG_WANT_LOOP          0
#define EMU86_EMULATE_CONFIG_WANT_LRET          0
#define EMU86_EMULATE_CONFIG_WANT_LXS           0
#define EMU86_EMULATE_CONFIG_WANT_INC_RM        0
#define EMU86_EMULATE_CONFIG_WANT_DEC_RM        0
#define EMU86_EMULATE_CONFIG_WANT_CALL_RM       0
#define EMU86_EMULATE_CONFIG_WANT_LCALL_RM      0
#define EMU86_EMULATE_CONFIG_WANT_JMP_RM        0
#define EMU86_EMULATE_CONFIG_WANT_LJMP_RM       0
#define EMU86_EMULATE_CONFIG_WANT_PUSH_RM       0
#define EMU86_EMULATE_CONFIG_WANT_RDFSBASE      1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_RDGSBASE      1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_WRFSBASE      1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_WRGSBASE      1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_CLWB          1 /* TODO: Check if this instruction always exists on x86_64 */
#define EMU86_EMULATE_CONFIG_WANT_CLFLUSH       1 /* TODO: Check if this instruction always exists on x86_64 */
#define EMU86_EMULATE_CONFIG_WANT_CLFLUSHOPT    1 /* TODO: Check if this instruction always exists on x86_64 */
#define EMU86_EMULATE_CONFIG_WANT_LFENCE        1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_SFENCE        1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_MFENCE        1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_MOV_RM        0
#define EMU86_EMULATE_CONFIG_WANT_MOVBE         1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_MOV_IMM       0
#define EMU86_EMULATE_CONFIG_WANT_XABORT        1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_XBEGIN        1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_MOV_MOFFS     0
#define EMU86_EMULATE_CONFIG_WANT_MOVNTI        1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_MOVS          0
#define EMU86_EMULATE_CONFIG_WANT_MOV_SREG      0
#define EMU86_EMULATE_CONFIG_WANT_MOVSX         0
#define EMU86_EMULATE_CONFIG_WANT_MOVSXD        0
#define EMU86_EMULATE_CONFIG_WANT_MOVZX         0
#define EMU86_EMULATE_CONFIG_WANT_ARPL          0
#define EMU86_EMULATE_CONFIG_WANT_NOP_RM        1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_PEXT          1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_PDEP          1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_BZHI          1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_SLDT          0
#define EMU86_EMULATE_CONFIG_WANT_LLDT          0
#define EMU86_EMULATE_CONFIG_WANT_STR           0
#define EMU86_EMULATE_CONFIG_WANT_LTR           0
#define EMU86_EMULATE_CONFIG_WANT_SGDT          0
#define EMU86_EMULATE_CONFIG_WANT_LGDT          0
#define EMU86_EMULATE_CONFIG_WANT_XEND          1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_XTEST         1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_SIDT          0
#define EMU86_EMULATE_CONFIG_WANT_LIDT          0
#define EMU86_EMULATE_CONFIG_WANT_VERR          0
#define EMU86_EMULATE_CONFIG_WANT_VERW          0
#define EMU86_EMULATE_CONFIG_WANT_SMSW          0
#define EMU86_EMULATE_CONFIG_WANT_LMSW          0
#define EMU86_EMULATE_CONFIG_WANT_INVLPG        (!CONFIG_LIBEMU86_WANT_64BIT) /* Only available on 486+ (emulate in 32-bit mode) */
#define EMU86_EMULATE_CONFIG_WANT_LAR           0
#define EMU86_EMULATE_CONFIG_WANT_LSL           0
#define EMU86_EMULATE_CONFIG_WANT_POPCNT        1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_PUSHA         0
#define EMU86_EMULATE_CONFIG_WANT_POPA          0
#define EMU86_EMULATE_CONFIG_WANT_PUSHF         0 /* TODO: vm86 support */
#define EMU86_EMULATE_CONFIG_WANT_POPF          0 /* TODO: vm86 support */
#define EMU86_EMULATE_CONFIG_WANT_PUSH_IMM      0
#define EMU86_EMULATE_CONFIG_WANT_PUSH_REG      0
#define EMU86_EMULATE_CONFIG_WANT_POP_REG       0
#define EMU86_EMULATE_CONFIG_WANT_POP_RM        0
#define EMU86_EMULATE_CONFIG_WANT_PUSH_ES       0
#define EMU86_EMULATE_CONFIG_WANT_POP_ES        0
#define EMU86_EMULATE_CONFIG_WANT_PUSH_CS       0
#define EMU86_EMULATE_CONFIG_WANT_PUSH_SS       0
#define EMU86_EMULATE_CONFIG_WANT_POP_SS        0
#define EMU86_EMULATE_CONFIG_WANT_PUSH_DS       0
#define EMU86_EMULATE_CONFIG_WANT_POP_DS        0
#define EMU86_EMULATE_CONFIG_WANT_PUSH_FS       0
#define EMU86_EMULATE_CONFIG_WANT_POP_FS        0
#define EMU86_EMULATE_CONFIG_WANT_PUSH_GS       0
#define EMU86_EMULATE_CONFIG_WANT_POP_GS        0
#define EMU86_EMULATE_CONFIG_WANT_RET           0
#define EMU86_EMULATE_CONFIG_WANT_RORX          1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_SAHF          0
#define EMU86_EMULATE_CONFIG_WANT_LAHF          0
#define EMU86_EMULATE_CONFIG_WANT_SALC          0
#define EMU86_EMULATE_CONFIG_WANT_SCAS          0
#define EMU86_EMULATE_CONFIG_WANT_SHIFT         0
#define EMU86_EMULATE_CONFIG_WANT_SHIFT2        1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_BEXTR         1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_SHIFTX        1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_STAC          1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_CLAC          1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_CMC           0
#define EMU86_EMULATE_CONFIG_WANT_CLC           0
#define EMU86_EMULATE_CONFIG_WANT_STC           0
#define EMU86_EMULATE_CONFIG_WANT_CLD           0
#define EMU86_EMULATE_CONFIG_WANT_STD           0
#define EMU86_EMULATE_CONFIG_WANT_CLI           0 /* TODO: vm86 support */
#define EMU86_EMULATE_CONFIG_WANT_STI           0 /* TODO: vm86 support */
#define EMU86_EMULATE_CONFIG_WANT_STOS          0
#define EMU86_EMULATE_CONFIG_WANT_SYSCALL       CONFIG_LIBEMU86_WANT_64BIT
#define EMU86_EMULATE_CONFIG_WANT_SYSRET        0
#define EMU86_EMULATE_CONFIG_WANT_SYSENTER      1
#define EMU86_EMULATE_CONFIG_WANT_SYSEXIT       0
#define EMU86_EMULATE_CONFIG_WANT_XADD          (!CONFIG_LIBEMU86_WANT_64BIT) /* Only available on 486+ (emulate in 32-bit mode) */
#define EMU86_EMULATE_CONFIG_WANT_XCHG_RM       0
#define EMU86_EMULATE_CONFIG_WANT_NOP           0
#define EMU86_EMULATE_CONFIG_WANT_PAUSE         0
#define EMU86_EMULATE_CONFIG_WANT_XCHG_REG      0
#define EMU86_EMULATE_CONFIG_WANT_XLATB         0
#define EMU86_EMULATE_CONFIG_WANT_XOP_BLCFILL   1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_XOP_BLSFILL   1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_XOP_BLCS      1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_XOP_TZMSK     1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_XOP_BLCIC     1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_XOP_BLSIC     1 /* Emulate non-standard instructions */
#define EMU86_EMULATE_CONFIG_WANT_XOP_T1MSKC    1 /* Emulate non-standard instructions */



#define EMU86_EMULATE_DECL          PRIVATE
#define EMU86_EMULATE_ATTR          ATTR_RETNONNULL NONNULL((1))
#define EMU86_EMULATE_RETURN()      return _state
#define EMU86_EMULATE_RETURN_TYPE   struct icpustate *
#define EMU86_EMULATE_NOTHROW       /* nothing */
#define EMU86_EMULATE_CC            FCALL
#define EMU86_EMULATE_NAME          x86_handle_bad_usage
#define EMU86_EMULATE_HELPER_DECL   PRIVATE
#define EMU86_EMULATE_ARGS          struct icpustate *__restrict _state, u16 usage
#define EMU86_EMULATE_HELPER_ATTR   NONNULL((1))
#define EMU86_EMULATE_HELPER_ARGS   struct icpustate *__restrict _state
#define EMU86_EMULATE_HELPER_PARAM  _state
#define EMU86_EMULATE_HELPER_ARGS_  EMU86_EMULATE_HELPER_ARGS,
#define EMU86_EMULATE_HELPER_PARAM_ EMU86_EMULATE_HELPER_PARAM,

#if 0 /* Unused... */
PRIVATE NONNULL((1)) void FCALL
loophint(struct icpustate *__restrict state) {
	if (icpustate_getpreemption(state)) {
		task_serve();
		task_yield();
	}
}
#define EMU86_EMULATE_LOOPHINT() loophint(_state)
#else
#define EMU86_EMULATE_LOOPHINT() DONT_USE
#endif

#undef EMU86_EMULATE_RETURN_AFTER_INT  /* Not needed because we don't emulate the instruction */
#undef EMU86_EMULATE_RETURN_AFTER_INT1 /* Not needed because we don't emulate the instruction */
#undef EMU86_EMULATE_RETURN_AFTER_INT3 /* Not needed because we don't emulate the instruction */
#undef EMU86_EMULATE_RETURN_AFTER_INTO /* Not needed because we don't emulate the instruction */
#undef EMU86_EMULATE_THROW_BOUNDERR    /* Not needed because we don't emulate the instruction */


PRIVATE ATTR_NORETURN NOBLOCK void
NOTHROW(FCALL unwind)(struct icpustate *__restrict self) {
#if EXCEPT_BACKTRACE_SIZE != 0
	{
		unsigned int i;
		for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i)
			PERTASK_SET(this_exception_trace[i], (void *)0);
	}
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	x86_userexcept_unwind_interrupt(self);
}

#define EMU86_EMULATE_TRY \
	TRY
#define EMU86_EMULATE_EXCEPT     \
	EXCEPT {                     \
		complete_except(_state); \
	}

#define EMU86_EMULATE_TRY_SWITCH \
	TRY
#define EMU86_EMULATE_EXCEPT_SWITCH                               \
	EXCEPT {                                                      \
		complete_except_switch(_state, EMU86_OPCODE(), op_flags); \
	}

/* Fill in missing exception pointer. */
PRIVATE ATTR_NORETURN NOBLOCK void
NOTHROW(FCALL complete_except)(struct icpustate *__restrict self) {
	error_class_t cls = PERTASK_GET(this_exception_class);
	if (cls == E_SEGFAULT) {
		uintptr_t flags;
		flags = PERTASK_GET(this_exception_pointers[1]);
#ifdef __KERNEL__
		if (icpustate_isuser(self))
#endif /* __KERNEL__ */
		{
			/* The fault happened due to a user-space access */
			flags |= E_SEGFAULT_CONTEXT_USERCODE;
		}
#ifdef __x86_64__
		/* The fault uses a non-canonical address (shouldn't actually happen...) */
		if (ADDR_IS_NONCANON(PERTASK_GET(this_exception_pointers[0])))
			flags |= E_SEGFAULT_CONTEXT_NONCANON;
#endif /* __x86_64__ */
		PERTASK_SET(this_exception_pointers[1], flags);
	}
	/* Fill in the fault address. */
	{
		void const *pc, *next_pc;
		pc      = (void const *)icpustate_getpc(self);
		next_pc = instruction_succ(pc);
		if (next_pc)
			icpustate_setpc(self, (uintptr_t)next_pc);
		PERTASK_SET(this_exception_faultaddr, (void *)pc);
	}
	unwind(self);
}

/* Fill in missing exception pointer. */
PRIVATE ATTR_NORETURN NOBLOCK void
NOTHROW(FCALL complete_except_switch)(struct icpustate *__restrict self,
                                      uintptr_t opcode, uintptr_t op_flags) {
	error_class_t cls = PERTASK_GET(this_exception_class);
	if (cls == E_ILLEGAL_INSTRUCTION) {
		if (!PERTASK_GET(this_exception_pointers[0]))
			PERTASK_SET(this_exception_pointers[0], opcode);
		if (!PERTASK_GET(this_exception_pointers[1]))
			PERTASK_SET(this_exception_pointers[1], op_flags);
	}
	complete_except(self);
}

PRIVATE ATTR_NORETURN NONNULL((1)) void FCALL
throw_illegal_instruction_exception(struct icpustate *__restrict state,
                                    error_code_t code, uintptr_t opcode,
                                    uintptr_t op_flags, uintptr_t ptr2,
                                    uintptr_t ptr3, uintptr_t ptr4,
                                    uintptr_t ptr5) {
	unsigned int i;
	void const *pc, *next_pc;
	pc      = (void const *)icpustate_getpc(state);
	next_pc = instruction_succ(pc);
	if (next_pc)
		icpustate_setpc(state, (uintptr_t)next_pc);
	PERTASK_SET(this_exception_code, code);
	PERTASK_SET(this_exception_faultaddr, (void *)pc);
	PERTASK_SET(this_exception_pointers[0], opcode);
	PERTASK_SET(this_exception_pointers[1], op_flags);
	PERTASK_SET(this_exception_pointers[2], ptr2);
	PERTASK_SET(this_exception_pointers[3], ptr3);
	PERTASK_SET(this_exception_pointers[4], ptr4);
	PERTASK_SET(this_exception_pointers[5], ptr5);
	for (i = 6; i < EXCEPTION_DATA_POINTERS; ++i)
		PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_enabled() && (kernel_debugtrap_on & KERNEL_DEBUGTRAP_ON_ILLEGAL_INSTRUCTION))
		kernel_debugtrap(state, SIGILL);
	unwind(state);
}

PRIVATE ATTR_NORETURN NONNULL((1)) void FCALL
throw_exception(struct icpustate *__restrict state,
                error_code_t code, uintptr_t ptr0, uintptr_t ptr1) {
	unsigned int i;
	void const *pc, *next_pc;
	pc      = (void const *)icpustate_getpc(state);
	next_pc = instruction_succ(pc);
	if (next_pc)
		icpustate_setpc(state, (uintptr_t)next_pc);
	PERTASK_SET(this_exception_code, code);
	PERTASK_SET(this_exception_faultaddr, (void *)pc);
	PERTASK_SET(this_exception_pointers[0], ptr0);
	PERTASK_SET(this_exception_pointers[1], ptr1);
	for (i = 2; i < EXCEPTION_DATA_POINTERS; ++i)
		PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
	unwind(state);
}

PRIVATE ATTR_NORETURN NONNULL((1)) void FCALL
throw_generic_unknown_instruction(struct icpustate *__restrict state,
                                  u16 usage, uintptr_t opcode,
                                  emu86_opflags_t op_flags) {

	/* Produce some default exception. */
	if (BAD_USAGE_REASON(usage) == BAD_USAGE_REASON_UD) {
		/* #UD simply results in a generic BAD_OPCODE exception! */
		throw_illegal_instruction_exception(state,
		                                    ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPCODE),
		                                    opcode, op_flags, 0, 0, 0, 0);
	} else {
		u16 segval;
		if (BAD_USAGE_REASON(usage) == BAD_USAGE_REASON_SS) {
			segval = icpustate_getss(state);
		} else {
			switch (op_flags & EMU86_F_SEGMASK) {
			case EMU86_F_SEGFS: segval = icpustate_getfs(state); break;
			case EMU86_F_SEGGS: segval = icpustate_getgs(state); break;
#ifndef __x86_64__
			case EMU86_F_SEGES: segval = icpustate_getes(state); break;
			case EMU86_F_SEGCS: segval = icpustate_getcs(state); break;
			case EMU86_F_SEGSS: segval = icpustate_getss(state); break;
#endif /* !__x86_64__ */
			default: segval = icpustate_getds(state); break;
			}
		}
		if (!segval && BAD_USAGE_ECODE(usage) == 0) {
			/* Throw a NULL-segment exception. */
			throw_illegal_instruction_exception(state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER),
			                                    opcode, op_flags, E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD,
			                                    X86_REGISTER_SEGMENT_ES + EMU86_F_SEGREG(op_flags),
			                                    0, 0);
		}
#ifdef __x86_64__
		/* On x86_64, a #GPF is thrown when attempting to access a non-canonical address.
		 * However, the kernel expects that the only exception that might be thrown when
		 * accessing some unchecked pointer is an E_SEGFAULT (or E_WOULDBLOCK when pre-
		 * emption is currently disabled).
		 * Emu86 already tried to inspect the source instruction to determine the faulting
		 * memory address. However there are literally thousands of different X86
		 * instructions that take a memory operand, and we can only know about so many
		 * before we run into one that may not even have existed at the time this
		 * decoder was written.
		 * So despite the fact that we haven't managed to figure out the faulting memory
		 * address, simply assume that a 0-error-code is indicative of a instruction that
		 * tried to access a non-canonical address.
		 * In this case, we set the first non-canonical address as faulting address.
		 * Also: we don't know if it was a write that caused the problem, so we just
		 *       always act like it was an unspecific access to an unmapped page. */
		if (BAD_USAGE_REASON(usage) == BAD_USAGE_REASON_GFP && BAD_USAGE_ECODE(usage) == 0) {
			printk(KERN_WARNING "[gpf] Assuming Segmentation fault at ? [pc=%p,opcode=%#Ix,opflags=%#I32x] [tid=%u]\n",
			       (void *)icpustate_getpc(state), opcode, op_flags, (unsigned int)task_getroottid_s());
			throw_exception(state,
			                ERROR_CODEOF(E_SEGFAULT_UNMAPPED),
			                X86_64_ADDRBUS_NONCANON_MIN,
			                icpustate_isuser(state)
			                ? E_SEGFAULT_CONTEXT_NONCANON | E_SEGFAULT_CONTEXT_USERCODE
			                : E_SEGFAULT_CONTEXT_NONCANON);
		}
#endif /* __x86_64__ */
		/* If the error originated from user-space, default to assuming it's
		 * because of some privileged instruction not explicitly handled (maybe
		 * because we don't know about it, or maybe because of some other reason). */
		if (icpustate_isuser(state)) {
			/* #GPF is also thrown when EFLAGS.AC is set, and the caller originates from user-space.
			 * When EFLAGS.AC is set, we default to throwing an `E_SEGFAULT_UNALIGNED' exception! */
			if (icpustate_getpflags(state) & EFLAGS_AC) {
				throw_exception(state,
				                ERROR_CODEOF(E_SEGFAULT_UNALIGNED), 0,
				                icpustate_isuser(state)
				                ? E_SEGFAULT_CONTEXT_NONCANON | E_SEGFAULT_CONTEXT_USERCODE
				                : E_SEGFAULT_CONTEXT_NONCANON);
			}
			throw_illegal_instruction_exception(state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE),
			                                    opcode, op_flags, 0, 0, 0, 0);
		}
		/* In kernel space, this one's a wee bit more complicated... */
		throw_illegal_instruction_exception(state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_X86_INTERRUPT),
		                                    opcode, op_flags, BAD_USAGE_INTNO(usage),
		                                    BAD_USAGE_ECODE(usage), segval, 0);
	}
}

PRIVATE ATTR_NORETURN NONNULL((1)) void FCALL
throw_unsupported_instruction(struct icpustate *__restrict state,
                              u16 usage, uintptr_t opcode, uintptr_t op_flags) {
	if (BAD_USAGE_REASON(usage) == BAD_USAGE_REASON_UD) {
		/* An unsupported instruction caused a #UD
		 * -> Throw an UNSUPPORTED_OPCODE exception */
		throw_illegal_instruction_exception(state,
		                                    ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE),
		                                    opcode, op_flags, 0, 0, 0, 0);
	} else {
		/* An unsupported instruction caused a #GPF or #SS
		 * -> Handle the exception the same way we do for unknown instructions! */
		throw_generic_unknown_instruction(state, usage, opcode, op_flags);
	}
}

#define _EMU86_GETOPCODE()        EMU86_OPCODE()
#define _EMU86_GETOPCODE_RMREG()  E_ILLEGAL_INSTRUCTION_X86_OPCODE(EMU86_OPCODE(), modrm.mi_reg)
#define EMU86_EMULATE_RETURN_UNKNOWN_INSTRUCTION()           throw_generic_unknown_instruction(_state, usage, _EMU86_GETOPCODE(), op_flags)
#define EMU86_EMULATE_RETURN_UNKNOWN_INSTRUCTION_RMREG()     throw_generic_unknown_instruction(_state, usage, _EMU86_GETOPCODE_RMREG(), op_flags)
#define EMU86_EMULATE_RETURN_PRIVILEGED_INSTRUCTION()        throw_illegal_instruction_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE), _EMU86_GETOPCODE(), op_flags, 0, 0, 0, 0)
#define EMU86_EMULATE_RETURN_PRIVILEGED_INSTRUCTION_RMREG()  throw_illegal_instruction_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE), _EMU86_GETOPCODE_RMREG(), op_flags, 0, 0, 0, 0)
#define EMU86_EMULATE_RETURN_EXPECTED_MEMORY_MODRM()         throw_illegal_instruction_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND), _EMU86_GETOPCODE(), op_flags, E_ILLEGAL_INSTRUCTION_BAD_OPERAND_ADDRMODE, 0, 0, 0)
#define EMU86_EMULATE_RETURN_EXPECTED_MEMORY_MODRM_RMREG()   throw_illegal_instruction_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND), _EMU86_GETOPCODE_RMREG(), op_flags, E_ILLEGAL_INSTRUCTION_BAD_OPERAND_ADDRMODE, 0, 0, 0)
#define EMU86_EMULATE_RETURN_EXPECTED_REGISTER_MODRM()       throw_illegal_instruction_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND), _EMU86_GETOPCODE(), op_flags, E_ILLEGAL_INSTRUCTION_BAD_OPERAND_ADDRMODE, 0, 0, 0)
#define EMU86_EMULATE_RETURN_EXPECTED_REGISTER_MODRM_RMREG() throw_illegal_instruction_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND), _EMU86_GETOPCODE_RMREG(), op_flags, E_ILLEGAL_INSTRUCTION_BAD_OPERAND_ADDRMODE, 0, 0, 0)
#define EMU86_EMULATE_RETURN_UNEXPECTED_PREFIX()             throw_illegal_instruction_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX), _EMU86_GETOPCODE(), op_flags, 0, 0, 0, 0)
#define EMU86_EMULATE_RETURN_UNEXPECTED_PREFIX_RMREG()       throw_illegal_instruction_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_X86_BAD_PREFIX), _EMU86_GETOPCODE_RMREG(), op_flags, 0, 0, 0, 0)
#define EMU86_EMULATE_RETURN_UNSUPPORTED_INSTRUCTION()       throw_unsupported_instruction(_state, usage, _EMU86_GETOPCODE(), op_flags)
#define EMU86_EMULATE_RETURN_UNSUPPORTED_INSTRUCTION_RMREG() throw_unsupported_instruction(_state, usage, _EMU86_GETOPCODE_RMREG(), op_flags)
#define EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(how, regno, regval, offset)          \
	throw_illegal_instruction_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER), \
	                                    _EMU86_GETOPCODE(), op_flags, how, regno, regval, offset)
#define EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER_RMREG(how, regno, regval, offset)    \
	throw_illegal_instruction_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER), \
	                                    _EMU86_GETOPCODE_RMREG(), op_flags, how, regno, regval, offset)
#define EMU86_EMULATE_RETURN_AFTER_XEND()                                                               \
	throw_illegal_instruction_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE), \
	                                    _EMU86_GETOPCODE_RMREG(), op_flags, 0, 0, 0, 0)

#define EMU86_EMULATE_GETOPFLAGS() emu86_opflagsof_icpustate(_state)
#define EMU86_EMULATE_TRANSLATEADDR_IS_NOOP 1
#define EMU86_EMULATE_TRANSLATEADDR(addr) (addr)
#define EMU86_GETCR4_UMIP_IS_ZERO 1 /* TODO: Support me! */
#define EMU86_GETCR4_UMIP() 0       /* TODO: Support me! */


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
#define EMU86_EMULATE_INVLPG(addr)               pagedir_syncall()
#define EMU86_EMULATE_LAR(segment_index, result) DONT_USE
#define EMU86_EMULATE_LSL(segment_index, result) DONT_USE

#ifdef __x86_64__
#define NEED_return_unsupported_instruction
#define EMU86_EMULATE_RETURN_AFTER_SYSCALL()                              \
	do {                                                                  \
		if unlikely(icpustate_getcs(_state) != SEGMENT_USER_CODE64_RPL) { \
			/* Only allowed from 64-bit user-space. */                    \
			EMU86_SETPCPTR(REAL_START_IP());                              \
			goto return_unsupported_instruction;                          \
		}                                                                 \
		/* syscall emulation */                                           \
		x86_syscall_emulate64_int80h_r(_state);                           \
	} __WHILE0
#define NEED_return_unsupported_instruction
#define EMU86_EMULATE_RETURN_AFTER_SYSENTER()      \
	do {                                           \
		/* Only allowed from 32-bit user-space. */ \
		if unlikely(!EMU86_F_IS32(op_flags))       \
			goto return_unsupported_instruction;   \
		__hybrid_assert(EMU86_ISUSER());           \
		/* sysenter emulation */                   \
		x86_syscall_emulate32_sysenter_r(_state);  \
		__builtin_unreachable();                   \
	} __WHILE0
#else /* __x86_64__ */
#define EMU86_EMULATE_RETURN_AFTER_SYSENTER()      \
	do {                                           \
		__hybrid_assert(EMU86_ISUSER());           \
		x86_syscall_emulate32_sysenter_r(_state);  \
		__builtin_unreachable();                   \
	} __WHILE0
#endif /* !__x86_64__ */


#ifdef __x86_64__
#define EMU86_SETFSBASE(v) \
	__wrmsr(IA32_FS_BASE, (uintptr_t)(v))
/* NOTE: When the access originates from user-space, we must write to `IA32_KERNEL_GS_BASE',
 *       since the kernel has executed `swapgs' upon exiting user-space. Because of this,
 *       the current %gs.base is `THIS_TASK', while `IA32_KERNEL_GS_BASE' contains the
 *       saved user-space %gs.base! */
#define EMU86_SETGSBASE(v)             \
	__wrmsr(icpustate64_isuser(_state) \
	        ? IA32_KERNEL_GS_BASE      \
	        : IA32_GS_BASE,            \
	        (uintptr_t)(v))
#else /* __x86_64__ */
#define EMU86_SETFSBASE(v) setfsbase(_state, (uintptr_t)(v))
#define EMU86_SETGSBASE(v) setgsbase((uintptr_t)(v))
PRIVATE void FCALL
setfsbase(struct icpustate32 *__restrict state, uintptr_t value) {
	u16 myfs = icpustate_getfs_novm86(state) & ~3;
	if (myfs == SEGMENT_USER_FSBASE)
		set_user_fsbase_noreload(value);
	else if (myfs == SEGMENT_USER_GSBASE)
		set_user_gsbase_noreload(value);
	else {
		/* Don't allow user-space to set the bases of any other segment.
		 * As such, throw an exception indicating a privileged register (which SOME_SEGMENT.base is) */
		THROW(E_ILLEGAL_INSTRUCTION_REGISTER, 0,
		      E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
		      X86_REGISTER_SEGMENT_FS, myfs, value);
	}
	update_user_fsbase();
}

PRIVATE void FCALL
setgsbase(uintptr_t value) {
	u16 mygs = __rdgs() & ~3;
	if (mygs == SEGMENT_USER_GSBASE)
		set_user_gsbase_noreload(value);
	else if (mygs == SEGMENT_USER_FSBASE)
		set_user_fsbase_noreload(value);
	else {
		/* Don't allow user-space to set the bases of any other segment.
		 * As such, throw an exception indicating a privileged register (which SOME_SEGMENT.base is) */
		THROW(E_ILLEGAL_INSTRUCTION_REGISTER, 0,
		      E_ILLEGAL_INSTRUCTION_REGISTER_WRPRV,
		      X86_REGISTER_SEGMENT_GS, mygs, value);
	}
	update_user_gsbase();
}
#endif /* !__x86_64__ */


#define EMU86_ISUSER() icpustate_isuser(_state)

#ifdef __x86_64__
#define EMU86_EMULATE_VM86    0
#define EMU86_ISUSER_NOVM86() EMU86_ISUSER()
#else /* __x86_64__ */
#define EMU86_EMULATE_VM86 1
#define EMU86_EMULATE_VM86_GETIF()            0 /* TODO */
#define EMU86_EMULATE_VM86_SETIF(v)           (void)0
#define EMU86_EMULATE_RETURN_AFTER_HLT_VM86() /* TODO */
#define EMU86_ISUSER_NOVM86() icpustate_isuser_novm86(_state)
#define EMU86_ISVM86()        icpustate_isvm86(_state)
#endif /* !__x86_64__ */



/* Special handling for user-space address range validation:
 * Because our version of libemu86 is the one responsible for emulating
 * instruction that may not necessarily be known to the host CPU, there
 * also exists the case where user-space is trying to perform a memory
 * access to its UKERN segment, using an instruction that is not natively
 * known to the host CPU.
 * In this case, when trying to emulate the instruction, we would normally
 * notice that user-space is trying to access a kernel-space address.
 * However, the UKERN segment exists as an overlay on-top of kernel-space,
 * and as such any memory access originating from user-space, and targeting
 * a kernel-space address (while also overlapping with the UKERN segment),
 * must be dispatched through VIO. */
#ifndef CONFIG_NO_USERKERN_SEGMENT
PRIVATE struct icpustate *FCALL
dispatch_userkern_vio_r(struct icpustate *__restrict state) {
	struct vio_emulate_args args;
	struct vm *myvm = THIS_VM;

	/* The VIO emulation will span the entirety of the KERNRESERVE node. */
	args.vea_ptrlo = vm_node_getmin(&myvm->v_kernreserve);
	args.vea_ptrhi = vm_node_getmax(&myvm->v_kernreserve);

	/* Load VM component pointers. */
	args.vea_args.va_block = myvm->v_kernreserve.vn_block;
	args.vea_args.va_part  = myvm->v_kernreserve.vn_part;
	assert(args.vea_args.va_block);
	assert(args.vea_args.va_part);
	assert(args.vea_args.va_part->dp_block == args.vea_args.va_block);
	assert(args.vea_args.va_part->dp_state == VM_DATAPART_STATE_VIOPRT);
	assert(args.vea_args.va_block->db_vio);

	/* Load the VIO dispatch table */
	args.vea_args.va_ops = args.vea_args.va_block->db_vio;

	/* Setup meta-data for where VIO is mapped
	 * Since we know that the USERKERN VIO mapping consists of
	 * only a single data part, this part is quite simple. */
	args.vea_args.va_acmap_page   = args.vea_ptrlo;
	args.vea_args.va_acmap_offset = 0;
	args.vea_args.va_state        = state;
	args.vea_addr                 = 0;

	/* Emulate the instruction. */
	viocore_emulate(&args);

#ifndef __x86_64__
	/* NOTE: No need to deal with kernel ss/esp redirection, because we only
	 *       ever get called for user-space VIO access (s.a. the fact that
	 *       this function is only used to deal with userkern memory access,
	 *       which in turn can only ever happen from user-space) */
#endif /* !__x86_64__ */

	/* Return the updated CPU state. */
	return args.vea_args.va_state;
}


#define EMU86_VALIDATE_READABLE(addr, num_bytes)                         \
	do {                                                                 \
		if ((uintptr_t)(addr) >= KERNELSPACE_BASE)                       \
			assert_user_address_range(_state, (void *)(uintptr_t)(addr), \
			                          num_bytes, true, false);           \
	} __WHILE0
#define EMU86_VALIDATE_WRITABLE(addr, num_bytes)                         \
	do {                                                                 \
		if ((uintptr_t)(addr) >= KERNELSPACE_BASE)                       \
			assert_user_address_range(_state, (void *)(uintptr_t)(addr), \
			                          num_bytes, false, true);           \
	} __WHILE0
#define EMU86_VALIDATE_READWRITE(addr, num_bytes)                        \
	do {                                                                 \
		if ((uintptr_t)(addr) >= KERNELSPACE_BASE)                       \
			assert_user_address_range(_state, (void *)(uintptr_t)(addr), \
			                          num_bytes, true, true);            \
	} __WHILE0
PRIVATE void KCALL
assert_user_address_range(struct icpustate *__restrict state,
                          void const *addr, size_t num_bytes,
                          bool reading, bool writing) {
	uintptr_t endaddr;
	if unlikely(OVERFLOW_UADD((uintptr_t)addr, num_bytes, &endaddr) ||
	            endaddr > KERNELSPACE_BASE) {
		struct vm *myvm = THIS_VM;
		pageid_t pageid = PAGEID_ENCODE((uintptr_t)addr);
		/* Dispatch the current instruction through VIO */
		if (pageid >= vm_node_getminpageid(&myvm->v_kernreserve) &&
		    pageid <= vm_node_getmaxpageid(&myvm->v_kernreserve)) {
			/* Rewind the kernel stack such that `%(r|e)sp = state' before calling this function!
			 * There is no need to keep the instruction emulation payload of `handle_bad_usage()'
			 * on-stack when re-starting emulation for the purpose of dispatching userkern VIO. */
			kernel_restart_interrupt(state, &dispatch_userkern_vio_r);
		}
		/* ERROR: User-space is trying to access kernel-space! */
		THROW(E_SEGFAULT_UNMAPPED, addr,
		      (writing && !reading)
		      ? E_SEGFAULT_CONTEXT_USERCODE | E_SEGFAULT_CONTEXT_WRITING
		      : E_SEGFAULT_CONTEXT_USERCODE);
	}
}
#else /* !CONFIG_NO_USERKERN_SEGMENT */
#define EMU86_VALIDATE_READABLE(addr, num_bytes)  validate_readable(addr, num_bytes)
#define EMU86_VALIDATE_WRITABLE(addr, num_bytes)  validate_writable(addr, num_bytes)
#define EMU86_VALIDATE_READWRITE(addr, num_bytes) validate_readwrite(addr, num_bytes)
#endif /* CONFIG_NO_USERKERN_SEGMENT */




#ifdef __x86_64__

#define EMU86_EMULATE_VALIDATE_BEFORE_OPCODE_DECODE(pc) \
	assert_canonical_pc(_state, (void const *)(pc))
PRIVATE void KCALL
assert_canonical_pc(struct icpustate *__restrict state,
                    void const *pc) {
	/* Make sure that the program counter is canonical! */
	if unlikely(ADDR_IS_NONCANON(pc)) {
		/* Special case: Non-canonical program counter
		 * Just like with #PF for `%cr2 == %rip', handle this case by trying to
		 * restore the original RIP-value from `0(%rsp)', assuming that the RIP
		 * register ended up getting corrupted due to a bad `call', rather than
		 * a bad `jmp' */
		uintptr_t callsite_pc;
		uintptr_t sp = icpustate_getsp(state);
		bool is_compat;
		unsigned int i;
		callsite_pc = (uintptr_t)pc;
		if (sp >= KERNELSPACE_BASE && icpustate_isuser(state))
			goto set_noncanon_pc_exception;
		is_compat = icpustate_is32bit(state);
		if (is_compat) {
			callsite_pc = (uintptr_t)*(u32 *)sp;
		} else {
			callsite_pc = *(uintptr_t *)sp;
		}
		/* Verify the call-site program counter. */
		if (icpustate_isuser(state) ? (callsite_pc >= USERSPACE_END)
		                            : (callsite_pc < KERNELSPACE_BASE)) {
			callsite_pc = (uintptr_t)pc;
			goto set_noncanon_pc_exception;
		}
		icpustate_setpc(state, callsite_pc);
		icpustate_setsp(state, is_compat ? sp + 4 : sp + 8);
		{
			void const *call_instr;
			call_instr = instruction_pred((void *)callsite_pc);
			if likely(call_instr)
				callsite_pc = (uintptr_t)call_instr;
		}
set_noncanon_pc_exception:
		PERTASK_SET(this_exception_faultaddr, (void *)callsite_pc);
		PERTASK_SET(this_exception_code, ERROR_CODEOF(E_SEGFAULT_UNMAPPED));
		PERTASK_SET(this_exception_pointers[0], (uintptr_t)pc);
		PERTASK_SET(this_exception_pointers[1],
		            (uintptr_t)(E_SEGFAULT_CONTEXT_USERCODE |
		                        E_SEGFAULT_CONTEXT_NONCANON |
		                        E_SEGFAULT_CONTEXT_EXEC));
		if (!icpustate_isuser(state)) {
			PERTASK_SET(this_exception_pointers[1],
			            (uintptr_t)(E_SEGFAULT_CONTEXT_NONCANON |
			                        E_SEGFAULT_CONTEXT_EXEC));
		}
		for (i = 2; i < EXCEPTION_DATA_POINTERS; ++i)
			PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
		icpustate_setpc(state, callsite_pc);
		printk(KERN_DEBUG "[segfault] PC-Fault at %p [pc=%p] [#GPF] [tid=%u]\n",
		       pc, callsite_pc, (unsigned int)task_getroottid_s());
		unwind(state);
	}
}

#undef EMU86_UNSUPPORTED_MEMACCESS_IS_NOOP
#define EMU86_UNSUPPORTED_MEMACCESS(addr, num_bytes, reading, writing) \
	assert_canonical_address(_state, addr, num_bytes, reading, writing)
PRIVATE void KCALL
assert_canonical_address(struct icpustate *__restrict state,
                         void *addr, size_t num_bytes,
                         bool reading, bool writing) {
	assert(reading || writing);
	if unlikely(ADDR_IS_NONCANON((byte_t *)addr) ||
	            ADDR_IS_NONCANON((byte_t *)addr + num_bytes - 1)) {
		printk(KERN_DEBUG "[segfault] Fault at %p [pc=%p,%s] [#GPF] [tid=%u]\n",
		       addr, icpustate_getpc(state),
		       reading && writing ? "rw" : reading ? "ro" : "wo",
		       (unsigned int)task_getroottid_s());
		/* NOTE: When reading+writing, then the read always comes first, so even
		 *       though the instruction would have also performed a write, the
		 *       read happening first means that we mustn't set the WRITING flag. */
		THROW(E_SEGFAULT_UNMAPPED,
		      addr,
		      (writing && !reading)
		      ? E_SEGFAULT_CONTEXT_NONCANON | E_SEGFAULT_CONTEXT_WRITING
		      : E_SEGFAULT_CONTEXT_NONCANON);
	}
}

#define EMU86_EMULATE_THROW_SEGFAULT_UNMAPPED_NONCANON(addr) \
	THROW(E_SEGFAULT_UNMAPPED, addr, E_SEGFAULT_CONTEXT_NONCANON)
#undef EMU86_VALIDATE_CANONICAL_IS_NOOP
#define EMU86_VALIDATE_CANONICAL(addr)                            \
	do {                                                          \
		if unlikely(ADDR_IS_NONCANON(addr))                       \
			EMU86_EMULATE_THROW_SEGFAULT_UNMAPPED_NONCANON(addr); \
	} __WHILE0
#else /* __x86_64__ */
#define EMU86_UNSUPPORTED_MEMACCESS_IS_NOOP 1
#define EMU86_UNSUPPORTED_MEMACCESS(addr, num_bytes, reading, writing) (void)0
#endif /* !__x86_64__ */

#define EMU86_GETFLAGS()            icpustate_getpflags(_state)
#define EMU86_SETFLAGS(v)           icpustate_setpflags(_state, v)
#define EMU86_MSKFLAGS(mask, value) icpustate_mskpflags(_state, mask, value)
#define EMU86_GETPCPTR()            (byte_t *)icpustate_getpc(_state)
#define EMU86_SETPCPTR(v)           icpustate_setpc(_state, (__uintptr_t)(v))
#define EMU86_GETIPREG()            (uintptr_t)EMU86_GETPCPTR()
#define EMU86_SETIPREG(v)           EMU86_SETPCPTR(v)
#define EMU86_GETSTACKPTR()         (byte_t *)icpustate_getsp(_state)
#ifdef __x86_64__
#define EMU86_SETSTACKPTR(v)        icpustate64_setrsp(_state, (__uintptr_t)(v))
#else /* __x86_64__ */
#define EMU86_SETSTACKPTR(v)        (_state = icpustate_setsp_p(_state, (__uintptr_t)(v)))
#endif /* !__x86_64__ */
#define EMU86_GETSPREG()            (uintptr_t)icpustate_getsp(_state)
#define EMU86_SETSPREG(v)           EMU86_SETSTACKPTR(v)


#ifdef __x86_64__
/* x86_64 only supports a flat address space for es, cs, ss, and ds */
#define EMU86_GETSEGBASE_IS_NOOP_ES 1
#define EMU86_GETSEGBASE_IS_NOOP_CS 1
#define EMU86_GETSEGBASE_IS_NOOP_SS 1
#define EMU86_GETSEGBASE_IS_NOOP_DS 1
#define EMU86_GETSEGBASE(segment_regno)          \
	((segment_regno) == EMU86_R_FS               \
	 ? __rdfsbase()                              \
	 : (segment_regno) == EMU86_R_GS             \
	   ? (EMU86_ISUSER()                         \
	      ? (void *)__rdmsr(IA32_KERNEL_GS_BASE) \
	      : __rdgsbase())                        \
	   : 0)
#define EMU86_GETDSBASE() 0
#define EMU86_GETESBASE() 0
#define EMU86_GETCSBASE() 0
#define EMU86_GETSSBASE() 0
#define EMU86_GETFSBASE() __rdfsbase()
#define EMU86_GETGSBASE() (EMU86_ISUSER() ? (void *)__rdmsr(IA32_KERNEL_GS_BASE) : __rdgsbase())
#else /* __x86_64__ */

/* 32-bit mode supports non-zero bases for any segment! */
#define EMU86_GETSEGBASE(segment_regno) \
	i386_getsegment_base(_state, segment_regno)
#define EMU86_GETDSBASE() EMU86_GETSEGBASE(EMU86_R_DS)
#define EMU86_GETESBASE() EMU86_GETSEGBASE(EMU86_R_ES)
#define EMU86_GETCSBASE() EMU86_GETSEGBASE(EMU86_R_CS)
#define EMU86_GETSSBASE() EMU86_GETSEGBASE(EMU86_R_SS)
#define EMU86_GETFSBASE() EMU86_GETSEGBASE(EMU86_R_FS)
#define EMU86_GETGSBASE() EMU86_GETSEGBASE(EMU86_R_GS)
PRIVATE WUNUSED NONNULL((1)) u32
NOTHROW(KCALL i386_getsegment_base)(struct icpustate32 *__restrict state,
                                    u8 segment_regno) {
	u32 result;
	u16 segment_index;
	pflag_t was;
	struct segment *seg;
	struct desctab dt;
	/* Determine the segment's index. */
	switch (segment_regno) {

	case EMU86_R_ES:
		segment_index = icpustate_getes(state);
		break;

	case EMU86_R_CS:
		segment_index = icpustate_getcs(state);
		break;

	case EMU86_R_SS:
		segment_index = icpustate_getcs(state);
		break;

	case EMU86_R_DS:
		segment_index = icpustate_getds(state);
		break;

	case EMU86_R_FS:
		segment_index = icpustate_getfs(state);
		break;

	case EMU86_R_GS:
		segment_index = __rdgs();
		break;

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
		return (u32)THIS_TASK;

	case SEGMENT_USER_FSBASE:
		return get_user_fsbase();

	case SEGMENT_USER_GSBASE:
		return get_user_gsbase();

	default:
		break;
	}

	was = PREEMPTION_PUSHOFF();
	__sgdt(&dt);
	if (segment_index & 4) {
		/* LDT index. */
		u16 ldt = __sldt() & ~7;
		if unlikely(!ldt || ldt > dt.dt_limit) {
			PREEMPTION_POP(was);
			/* Deal with an invalid / disabled LDT by throwing an error indicating an invalid LDT. */
			THROW(E_ILLEGAL_INSTRUCTION_REGISTER,
			      0,                                    /* opcode */
			      E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD, /* what */
			      X86_REGISTER_MISC_LDT,                /* regno */
			      ldt);                                 /* regval */
		}
		seg = (struct segment *)((byte_t *)dt.dt_base + ldt);
		dt.dt_base  = segment_rdbaseX(seg);
		dt.dt_limit = (uint16_t)segment_rdlimit(seg);
	}
	segment_index &= ~7;
	if (!segment_index || segment_index > dt.dt_limit) {
		PREEMPTION_POP(was);
		THROW(E_ILLEGAL_INSTRUCTION_REGISTER,
		      0,                                       /* opcode */
		      E_ILLEGAL_INSTRUCTION_REGISTER_WRBAD,    /* what */
		      X86_REGISTER_SEGMENT_ES + segment_regno, /* regno */
		      segment_index);                          /* regval */
	}
	seg = (struct segment *)((byte_t *)dt.dt_base + segment_index);
	result = segment_rdbaseX(seg);
	PREEMPTION_POP(was);
	return result;
}
#endif /* !__x86_64__ */

#define EMU86_SEGADDR(segbase, segoffset) (byte_t *)(uintptr_t)((segbase) + (segoffset))
#define EMU86_GETES() icpustate_getes(_state)
#define EMU86_GETCS() icpustate_getcs(_state)
#define EMU86_GETSS() icpustate_getss(_state)
#define EMU86_GETDS() icpustate_getds(_state)
#define EMU86_GETFS() icpustate_getfs(_state)
#define EMU86_GETGS() icpustate_getgs(_state)
#define EMU86_EMULATE_PUSH(new_sp, num_bytes) (void)0
#define EMU86_EMULATE_POP(old_sp, num_bytes)  (void)0
#define EMU86_VALIDATE_IO(portno, num_ports)  (void)0

/* None of the instructions that should get emulated can modify segment registers. */
#define EMU86_SETES(v) DONT_USE
#define EMU86_SETCS(v) DONT_USE
#define EMU86_SETSS(v) DONT_USE
#define EMU86_SETDS(v) DONT_USE
#define EMU86_SETFS(v) DONT_USE
#define EMU86_SETGS(v) DONT_USE

#define EMU86_EMULATE_INB(portno, result) DONT_USE /* TODO: vm86 support */
#define EMU86_EMULATE_INW(portno, result) DONT_USE /* TODO: vm86 support */
#define EMU86_EMULATE_INL(portno, result) DONT_USE /* TODO: vm86 support */
#define EMU86_EMULATE_OUTB(portno, value) DONT_USE /* TODO: vm86 support */
#define EMU86_EMULATE_OUTW(portno, value) DONT_USE /* TODO: vm86 support */
#define EMU86_EMULATE_OUTL(portno, value) DONT_USE /* TODO: vm86 support */

#define EMU86_SETSEG(regno, value)       DONT_USE
#define EMU86_MODRM_MEMADDR_NOSEGBASE(modrm, op_flags) DONT_USE /* Unused */
#define EMU86_SETREGP(regno, value, op_flags)          DONT_USE /* Unused */



/* Emulation for `cpuid' on i386.
 * For this, fill registers with data from the cpu-local features tables. */
#if EMU86_EMULATE_CONFIG_WANT_CPUID
#define EMU86_EMULATE_HANDLE_CPUID() cpuid(_state)
PRIVATE WUNUSED NONNULL((1)) void
NOTHROW(KCALL cpuid)(struct icpustate *__restrict state) {
	struct cpuinfo const *info = &CURRENT_X86_CPUID;
	if ((u32)state->ics_gpregs.gp_pax & UINT32_C(0x80000000)) {
		switch ((u32)state->ics_gpregs.gp_pax) {
		case UINT32_C(0x80000000):
			state->ics_gpregs.gp_pax = info->ci_80000000a;
			state->ics_gpregs.gp_pbx = info->ci_0b;
			state->ics_gpregs.gp_pcx = info->ci_0c;
			state->ics_gpregs.gp_pdx = info->ci_0d;
			break;
		case UINT32_C(0x80000001):
			state->ics_gpregs.gp_pax = 0;
			state->ics_gpregs.gp_pbx = 0;
			state->ics_gpregs.gp_pcx = info->ci_80000001c;
			state->ics_gpregs.gp_pdx = info->ci_80000001d;
			break;
		case UINT32_C(0x80000002):
			state->ics_gpregs.gp_pax = info->ci_80000002a;
			state->ics_gpregs.gp_pbx = info->ci_80000002b;
			state->ics_gpregs.gp_pcx = info->ci_80000002c;
			state->ics_gpregs.gp_pdx = info->ci_80000002d;
			break;
		case UINT32_C(0x80000003):
			state->ics_gpregs.gp_pax = info->ci_80000003a;
			state->ics_gpregs.gp_pbx = info->ci_80000003b;
			state->ics_gpregs.gp_pcx = info->ci_80000003c;
			state->ics_gpregs.gp_pdx = info->ci_80000003d;
			break;
		case UINT32_C(0x80000004):
		default:
			state->ics_gpregs.gp_pax = info->ci_80000004a;
			state->ics_gpregs.gp_pbx = info->ci_80000004b;
			state->ics_gpregs.gp_pcx = info->ci_80000004c;
			state->ics_gpregs.gp_pdx = info->ci_80000004d;
			break;
		}
	} else {
		switch ((u32)state->ics_gpregs.gp_pax) {
		case 0:
			state->ics_gpregs.gp_pax = info->ci_0a;
			state->ics_gpregs.gp_pbx = info->ci_0b;
			state->ics_gpregs.gp_pcx = info->ci_0c;
			state->ics_gpregs.gp_pdx = info->ci_0d;
			break;
		case 1:
			state->ics_gpregs.gp_pax = info->ci_1a;
			state->ics_gpregs.gp_pbx = info->ci_1b;
			state->ics_gpregs.gp_pcx = info->ci_1c;
			state->ics_gpregs.gp_pdx = info->ci_1d;
			break;
		case 2 ... 7:
		default:
			state->ics_gpregs.gp_pax = 0;
			state->ics_gpregs.gp_pbx = info->ci_7b;
			state->ics_gpregs.gp_pcx = info->ci_7c;
			state->ics_gpregs.gp_pdx = info->ci_7d;
			break;
		}
	}
}
#endif /* EMU86_EMULATE_CONFIG_WANT_CPUID */


#define DEFINE_DO_ATOMIC_CMPXCH(bwlq, Nbits)                                 \
	PRIVATE NONNULL((1)) u##Nbits KCALL                                      \
	do_atomic_cmpxch##bwlq(struct icpustate **__restrict pstate,             \
	                       USER CHECKED u##Nbits *addr, u##Nbits oldval,     \
	                       u##Nbits newval, bool force_atomic) {             \
		u##Nbits result;                                                     \
		if (force_atomic) {                                                  \
			result = x86_emulock_cmpxch##bwlq(pstate, addr, oldval, newval); \
		} else {                                                             \
			COMPILER_READ_BARRIER();                                         \
			result = *addr;                                                  \
			COMPILER_READ_BARRIER();                                         \
			if (result == oldval) {                                          \
				COMPILER_WRITE_BARRIER();                                    \
				*addr = newval;                                              \
				COMPILER_WRITE_BARRIER();                                    \
			}                                                                \
		}                                                                    \
		return result;                                                       \
	}

#define DEFINE_DO_ATOMIC_CMPXCH_OR_WRITE(bwlq, Nbits)                               \
	PRIVATE NONNULL((1)) bool KCALL                                                 \
	do_atomic_cmpxch##bwlq##_or_write(struct icpustate **__restrict pstate,         \
	                                  USER CHECKED u##Nbits *addr, u##Nbits oldval, \
	                                  u##Nbits newval, bool force_atomic) {         \
		u##Nbits result;                                                            \
		if (force_atomic) {                                                         \
			result = x86_emulock_cmpxch##bwlq(pstate, addr, oldval, newval);        \
		} else {                                                                    \
			*addr = newval;                                                         \
			return true;                                                            \
		}                                                                           \
		return result == oldval;                                                    \
	}



/************************************************************************/
/* ATOMIC 128-BIT COMPARE-EXCHANGE                                      */
/************************************************************************/
#if EMU86_EMULATE_CONFIG_WANT_CMPXCHG16B
#ifndef CONFIG_EMULOCK_HAVE_CMPXCHX
#error "Bad configuration"
#endif /* CONFIG_EMULOCK_HAVE_CMPXCHX */
#define EMU86_MEM_ATOMIC_CMPXCHX(addr, oldval, newval, force_atomic) \
	do_atomic_cmpxchx((struct icpustate **)&_state, (uint128_t *)(addr), oldval, newval, force_atomic)
PRIVATE NONNULL((1)) uint128_t KCALL
do_atomic_cmpxchx(struct icpustate **__restrict pstate,
                  USER CHECKED uint128_t *addr, uint128_t oldval,
                  uint128_t newval, bool force_atomic) {
	uint128_t result;
	if (force_atomic) {
		result = x86_emulock_cmpxchx(pstate, addr, oldval, newval);
	} else {
		COMPILER_READ_BARRIER();
		result = *addr;
		COMPILER_READ_BARRIER();
		if (uint128_eq128(result, oldval)) {
			COMPILER_WRITE_BARRIER();
			*addr = newval;
			COMPILER_WRITE_BARRIER();
		}
	}
	return result;
}
#endif /* EMU86_EMULATE_CONFIG_WANT_CMPXCHG16B */


/************************************************************************/
/* ATOMIC 64-BIT COMPARE-EXCHANGE                                       */
/************************************************************************/
#if EMU86_EMULATE_CONFIG_WANT_CMPXCHG8B
#ifdef __x86_64__
#define EMU86_MEM_ATOMIC_CMPXCH_OR_WRITEQ(addr, oldval, newval, force_atomic) \
	__hybrid_atomic_cmpxch(*(u64 *)(addr), oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#define EMU86_MEM_ATOMIC_CMPXCHQ(addr, oldval, newval, force_atomic)      \
	__hybrid_atomic_cmpxch_val(*(u64 *)(addr), oldval, newval, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)
#elif defined(CONFIG_EMULOCK_HAVE_CMPXCHQ)
#define EMU86_MEM_ATOMIC_CMPXCHQ(addr, oldval, newval, force_atomic) \
	do_atomic_cmpxchq((struct icpustate **)&_state, (u64 *)(addr), (u64)(oldval), (u64)(newval), force_atomic)
#define EMU86_MEM_ATOMIC_CMPXCH_OR_WRITEQ(addr, oldval, newval, force_atomic) \
	do_atomic_cmpxchq_or_write((struct icpustate **)&_state, (u64 *)(addr), (u64)(oldval), (u64)(newval), force_atomic)
DEFINE_DO_ATOMIC_CMPXCH(q, 64)
/*DEFINE_DO_ATOMIC_CMPXCH_OR_WRITE(q, 64)*/ /* Unused */
#else /* ... */
#error "Bad configuration"
#endif /* !... */
#endif /* EMU86_EMULATE_CONFIG_WANT_CMPXCHG8B */


/************************************************************************/
/* ATOMIC 64-BIT COMPARE-EXCHANGE                                       */
/************************************************************************/
#if EMU86_EMULATE_CONFIG_WANT_CMPXCHG
#define EMU86_MEM_ATOMIC_CMPXCHB(addr, oldval, newval, force_atomic) \
	do_atomic_cmpxchb((struct icpustate **)&_state, (u8 *)(addr), (u8)(oldval), (u8)(newval), force_atomic)
#define EMU86_MEM_ATOMIC_CMPXCHW(addr, oldval, newval, force_atomic) \
	do_atomic_cmpxchw((struct icpustate **)&_state, (u16 *)(addr), (u16)(oldval), (u16)(newval), force_atomic)
#define EMU86_MEM_ATOMIC_CMPXCHL(addr, oldval, newval, force_atomic) \
	do_atomic_cmpxchl((struct icpustate **)&_state, (u32 *)(addr), (u32)(oldval), (u32)(newval), force_atomic)
#define EMU86_MEM_ATOMIC_CMPXCH_OR_WRITEB(addr, oldval, newval, force_atomic) \
	do_atomic_cmpxchb_or_write((struct icpustate **)&_state, (u8 *)(addr), (u8)(oldval), (u8)(newval), force_atomic)
#define EMU86_MEM_ATOMIC_CMPXCH_OR_WRITEW(addr, oldval, newval, force_atomic) \
	do_atomic_cmpxchw_or_write((struct icpustate **)&_state, (u16 *)(addr), (u16)(oldval), (u16)(newval), force_atomic)
#define EMU86_MEM_ATOMIC_CMPXCH_OR_WRITEL(addr, oldval, newval, force_atomic) \
	do_atomic_cmpxchl_or_write((struct icpustate **)&_state, (u32 *)(addr), (u32)(oldval), (u32)(newval), force_atomic)
DEFINE_DO_ATOMIC_CMPXCH(b, 8)
/*DEFINE_DO_ATOMIC_CMPXCH_OR_WRITE(b, 8)*/ /* Unused */
DEFINE_DO_ATOMIC_CMPXCH(w, 16)
/*DEFINE_DO_ATOMIC_CMPXCH_OR_WRITE(w, 16)*/ /* Unused */
DEFINE_DO_ATOMIC_CMPXCH(l, 32)
/*DEFINE_DO_ATOMIC_CMPXCH_OR_WRITE(l, 32)*/ /* Unused */
#endif /* EMU86_EMULATE_CONFIG_WANT_CMPXCHG */

#undef DEFINE_DO_ATOMIC_CMPXCH
#undef DEFINE_DO_ATOMIC_CMPXCH_OR_WRITE


/* None of these should ever be used */
#ifdef __x86_64__
#define EMU86_MEM_ATOMIC_CMPXCHB(addr, oldval, newval, force_atomic) DONE_USE
#define EMU86_MEM_ATOMIC_CMPXCHW(addr, oldval, newval, force_atomic) DONE_USE
#define EMU86_MEM_ATOMIC_CMPXCHL(addr, oldval, newval, force_atomic) DONE_USE
#endif /* __x86_64__ */

#define EMU86_MEM_ATOMIC_XCHB(addr, addend, force_atomic) DONT_USE
#define EMU86_MEM_ATOMIC_XCHW(addr, addend, force_atomic) DONT_USE
#define EMU86_MEM_ATOMIC_XCHL(addr, addend, force_atomic) DONT_USE
#define EMU86_MEM_ATOMIC_XCHQ(addr, addend, force_atomic) DONT_USE

#ifdef __x86_64__ /* Needed to emulate xadd on i386 */
#define EMU86_MEM_ATOMIC_FETCHADDB(addr, addend, force_atomic) DONT_USE
#define EMU86_MEM_ATOMIC_FETCHADDW(addr, addend, force_atomic) DONT_USE
#define EMU86_MEM_ATOMIC_FETCHADDL(addr, addend, force_atomic) DONT_USE
#endif /* __x86_64__ */
#define EMU86_MEM_ATOMIC_FETCHADDQ(addr, addend, force_atomic) DONT_USE

#define EMU86_MEM_ATOMIC_FETCHSUBB(addr, addend, force_atomic) DONT_USE
#define EMU86_MEM_ATOMIC_FETCHSUBW(addr, addend, force_atomic) DONT_USE
#define EMU86_MEM_ATOMIC_FETCHSUBL(addr, addend, force_atomic) DONT_USE
#define EMU86_MEM_ATOMIC_FETCHSUBQ(addr, addend, force_atomic) DONT_USE

#define EMU86_MEM_ATOMIC_FETCHANDB(addr, addend, force_atomic) DONT_USE
#define EMU86_MEM_ATOMIC_FETCHANDW(addr, addend, force_atomic) DONT_USE
#define EMU86_MEM_ATOMIC_FETCHANDL(addr, addend, force_atomic) DONT_USE
#define EMU86_MEM_ATOMIC_FETCHANDQ(addr, addend, force_atomic) DONT_USE

#define EMU86_MEM_ATOMIC_FETCHORB(addr, addend, force_atomic) DONT_USE
#define EMU86_MEM_ATOMIC_FETCHORW(addr, addend, force_atomic) DONT_USE
#define EMU86_MEM_ATOMIC_FETCHORL(addr, addend, force_atomic) DONT_USE
#define EMU86_MEM_ATOMIC_FETCHORQ(addr, addend, force_atomic) DONT_USE

#define EMU86_MEM_ATOMIC_FETCHXORB(addr, addend, force_atomic) DONT_USE
#define EMU86_MEM_ATOMIC_FETCHXORW(addr, addend, force_atomic) DONT_USE
#define EMU86_MEM_ATOMIC_FETCHXORL(addr, addend, force_atomic) DONT_USE
#define EMU86_MEM_ATOMIC_FETCHXORQ(addr, addend, force_atomic) DONT_USE



DECL_END

#ifndef __INTELLISENSE__
#include "../../../../../../include/libemu86/emulate.c.inl"
#endif /* !__INTELLISENSE__ */

DECL_BEGIN


INTERN struct icpustate *FCALL
x86_handle_stackfault(struct icpustate *__restrict state, uintptr_t ecode) {
	return x86_handle_bad_usage(state, BAD_USAGE_REASON_SS | ecode);
}

INTERN struct icpustate *FCALL
x86_handle_gpf(struct icpustate *__restrict state, uintptr_t ecode) {
	return x86_handle_bad_usage(state, BAD_USAGE_REASON_GFP | ecode);
}

INTERN struct icpustate *FCALL
x86_handle_illegal_instruction(struct icpustate *__restrict state) {
	return x86_handle_bad_usage(state, BAD_USAGE_REASON_UD);
}


DECL_END
#endif /* CONFIG_USE_HANDLE_BAD_USAGE */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_HANDLE_BAD_USAGE_C */
