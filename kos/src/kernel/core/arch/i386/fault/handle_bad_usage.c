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
#include <kernel/except.h>
#include <kernel/gdt.h>
#include <kernel/user.h>
#include <sched/except-handler.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <asm/registers.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <limits.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>

#include <libemu86/emu86.h>
#include <libinstrlen/instrlen.h>

DECL_BEGIN

#define BAD_USAGE_REASON_UD  0x0600
#define BAD_USAGE_REASON_SS  0x0c00
#define BAD_USAGE_REASON_GFP 0x0d00
#define BAD_USAGE_REASON(usage) ((usage) & 0xff00)
#define BAD_USAGE_ECODE(usage)  ((usage) & 0x00ff)

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

/* Configure for which instructions emulation should be attempted.
 * Any instruction enabled here will be emulated if not supported natively! */

#define EMU86_EMULATE_CONFIG_WANT_ADCX          1 /* Emulate non-standard instruction */
#define EMU86_EMULATE_CONFIG_WANT_ADOX          1 /* Emulate non-standard instruction */
#define EMU86_EMULATE_CONFIG_WANT_MULX          1 /* Emulate non-standard instruction */
#define EMU86_EMULATE_CONFIG_WANT_ANDN          1 /* Emulate non-standard instruction */
#define EMU86_EMULATE_CONFIG_WANT_ARITH         0
#define EMU86_EMULATE_CONFIG_WANT_ARITH2        0
#define EMU86_EMULATE_CONFIG_WANT_DAA           0
#define EMU86_EMULATE_CONFIG_WANT_DAS           0
#define EMU86_EMULATE_CONFIG_WANT_AAA           0
#define EMU86_EMULATE_CONFIG_WANT_AAS           0
#define EMU86_EMULATE_CONFIG_WANT_AAM           0
#define EMU86_EMULATE_CONFIG_WANT_AAD           0
#define EMU86_EMULATE_CONFIG_WANT_TZCNT         1 /* Emulate non-standard instruction */
#define EMU86_EMULATE_CONFIG_WANT_BSF           0
#define EMU86_EMULATE_CONFIG_WANT_LZCNT         1 /* Emulate non-standard instruction */
#define EMU86_EMULATE_CONFIG_WANT_BSR           0
#define EMU86_EMULATE_CONFIG_WANT_BITTEST       0
#define EMU86_EMULATE_CONFIG_WANT_BLSR          1 /* Emulate non-standard instruction */
#define EMU86_EMULATE_CONFIG_WANT_BLSMSK        1 /* Emulate non-standard instruction */
#define EMU86_EMULATE_CONFIG_WANT_BLSI          1 /* Emulate non-standard instruction */
#define EMU86_EMULATE_CONFIG_WANT_BOUND         0
#define EMU86_EMULATE_CONFIG_WANT_BSWAP         0
#define EMU86_EMULATE_CONFIG_WANT_CALL          0
#define EMU86_EMULATE_CONFIG_WANT_CBW           0
#define EMU86_EMULATE_CONFIG_WANT_CWD           0
#define EMU86_EMULATE_CONFIG_WANT_SETCC         (!CONFIG_LIBEMU86_WANT_64BIT) /* Only emulate in 32-bit kernels */
#define EMU86_EMULATE_CONFIG_WANT_CMOVCC        (!CONFIG_LIBEMU86_WANT_64BIT) /* Only emulate in 32-bit kernels */
#define EMU86_EMULATE_CONFIG_WANT_CMPS          0
#define EMU86_EMULATE_CONFIG_WANT_CMPXCHG       0 /* TODO: Try to emulate this! */
#define EMU86_EMULATE_CONFIG_WANT_CMPXCHG8B     0 /* TODO: Try to emulate this! */
#define EMU86_EMULATE_CONFIG_WANT_CMPXCHG16B    0 /* TODO: Try to emulate this! */
#define EMU86_EMULATE_CONFIG_WANT_CPUID         (!CONFIG_LIBEMU86_WANT_64BIT) /* Only emulate in 32-bit kernels */
#define EMU86_EMULATE_CONFIG_WANT_ENTER         0
#define EMU86_EMULATE_CONFIG_WANT_INVD          1 /* TODO: Check if this instruction always exists on x86_64 */
#define EMU86_EMULATE_CONFIG_WANT_WBINVD        1 /* TODO: Check if this instruction always exists on x86_64 */
#define EMU86_EMULATE_CONFIG_WANT_PREFETCHW     1 /* TODO: Check if this instruction always exists on x86_64 */
#define EMU86_EMULATE_CONFIG_WANT_PREFETCHNTA   1 /* TODO: Check if this instruction always exists on x86_64 */
#define EMU86_EMULATE_CONFIG_WANT_PREFETCH0     1 /* TODO: Check if this instruction always exists on x86_64 */
#define EMU86_EMULATE_CONFIG_WANT_PREFETCH1     1 /* TODO: Check if this instruction always exists on x86_64 */
#define EMU86_EMULATE_CONFIG_WANT_PREFETCH2     1 /* TODO: Check if this instruction always exists on x86_64 */
#define EMU86_EMULATE_CONFIG_WANT_CLDEMOTE      1 /* TODO: Check if this instruction always exists on x86_64 */
#define EMU86_EMULATE_CONFIG_WANT_HLT           0
#define EMU86_EMULATE_CONFIG_WANT_INCREG        0
#define EMU86_EMULATE_CONFIG_WANT_DECREG        0
#define EMU86_EMULATE_CONFIG_WANT_INT1          0
#define EMU86_EMULATE_CONFIG_WANT_INT3          0
#define EMU86_EMULATE_CONFIG_WANT_INT           0
#define EMU86_EMULATE_CONFIG_WANT_INTO          0
#define EMU86_EMULATE_CONFIG_WANT_IO            0
#define EMU86_EMULATE_CONFIG_WANT_IRET          0 /* TODO: Emulation for vm86 */
#define EMU86_EMULATE_CONFIG_WANT_JCC8          0
#define EMU86_EMULATE_CONFIG_WANT_JCC32         0
#define EMU86_EMULATE_CONFIG_WANT_JCXZ          0
#define EMU86_EMULATE_CONFIG_WANT_JMP8          0
#define EMU86_EMULATE_CONFIG_WANT_JMP32         0
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
#define EMU86_EMULATE_CONFIG_WANT_INCRM         0
#define EMU86_EMULATE_CONFIG_WANT_DECRM         0
#define EMU86_EMULATE_CONFIG_WANT_CALLRM        0
#define EMU86_EMULATE_CONFIG_WANT_LCALLRM       0
#define EMU86_EMULATE_CONFIG_WANT_JMPRM         0
#define EMU86_EMULATE_CONFIG_WANT_LJMPRM        0
#define EMU86_EMULATE_CONFIG_WANT_PUSHRM        0
#define EMU86_EMULATE_CONFIG_WANT_RDFSBASE      1 /* Emulate non-standard instruction */
#define EMU86_EMULATE_CONFIG_WANT_RDGSBASE      1 /* Emulate non-standard instruction */
#define EMU86_EMULATE_CONFIG_WANT_WRFSBASE      1 /* Emulate non-standard instruction */
#define EMU86_EMULATE_CONFIG_WANT_WRGSBASE      1 /* Emulate non-standard instruction */
#define EMU86_EMULATE_CONFIG_WANT_CLWB          1 /* TODO: Check if this instruction always exists on x86_64 */
#define EMU86_EMULATE_CONFIG_WANT_CLFLUSH       1 /* TODO: Check if this instruction always exists on x86_64 */
#define EMU86_EMULATE_CONFIG_WANT_CLFLUSHOPT    1 /* TODO: Check if this instruction always exists on x86_64 */
#define EMU86_EMULATE_CONFIG_WANT_LFENCE        1 /* Emulate non-standard instruction */
#define EMU86_EMULATE_CONFIG_WANT_SFENCE        1 /* Emulate non-standard instruction */
#define EMU86_EMULATE_CONFIG_WANT_MFENCE        1 /* Emulate non-standard instruction */
#define EMU86_EMULATE_CONFIG_WANT_MOVRM         0
#define EMU86_EMULATE_CONFIG_WANT_MOVBE         1 /* Emulate non-standard instruction */
#define EMU86_EMULATE_CONFIG_WANT_MOVIMM        0
#define EMU86_EMULATE_CONFIG_WANT_MOVMOFFS      0
#define EMU86_EMULATE_CONFIG_WANT_MOVS          0
#define EMU86_EMULATE_CONFIG_WANT_MOVSREG       0
#define EMU86_EMULATE_CONFIG_WANT_SYSCALL       CONFIG_LIBEMU86_WANT_64BIT
#define EMU86_EMULATE_CONFIG_WANT_SYSRET        0
#define EMU86_EMULATE_CONFIG_WANT_SYSENTER      1
#define EMU86_EMULATE_CONFIG_WANT_SYSEXIT       0
#define EMU86_EMULATE_CONFIG_WANT_SLDT          0
#define EMU86_EMULATE_CONFIG_WANT_LLDT          0
#define EMU86_EMULATE_CONFIG_WANT_STR           0
#define EMU86_EMULATE_CONFIG_WANT_LTR           0
#define EMU86_EMULATE_CONFIG_WANT_SGDT          0
#define EMU86_EMULATE_CONFIG_WANT_LGDT          0
#define EMU86_EMULATE_CONFIG_WANT_SIDT          0
#define EMU86_EMULATE_CONFIG_WANT_LIDT          0
#define EMU86_EMULATE_CONFIG_WANT_VERR          0
#define EMU86_EMULATE_CONFIG_WANT_VERW          0
#define EMU86_EMULATE_CONFIG_WANT_SMSW          0
#define EMU86_EMULATE_CONFIG_WANT_LMSW          0
#define EMU86_EMULATE_CONFIG_WANT_INVLPG        1
#define EMU86_EMULATE_CONFIG_WANT_LAR           0
#define EMU86_EMULATE_CONFIG_WANT_LSL           0



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

PRIVATE NONNULL((1)) void FCALL
loophint(struct icpustate *__restrict state) {
	if (icpustate_getpreemption(state)) {
		task_serve();
		task_yield();
	}
}

#define EMU86_EMULATE_LOOPHINT() loophint(_state)

#undef EMU86_EMULATE_RETURN_AFTER_INT  /* Not needed because we don't emulate the instruction */
#undef EMU86_EMULATE_RETURN_AFTER_INT1 /* Not needed because we don't emulate the instruction */
#undef EMU86_EMULATE_RETURN_AFTER_INT3 /* Not needed because we don't emulate the instruction */
#undef EMU86_EMULATE_RETURN_AFTER_INTO /* Not needed because we don't emulate the instruction */
#undef EMU86_EMULATE_THROW_BOUNDERR    /* Not needed because we don't emulate the instruction */

#define EMU86_EMULATE_TRY_SWITCH \
	TRY
#define EMU86_EMULATE_EXCEPT_SWITCH              \
	EXCEPT {                                     \
		complete_except(_state, EMU86_OPCODE()); \
	}
/* Fill in missing exception pointer. */
PRIVATE ATTR_NORETURN NOBLOCK void
NOTHROW(FCALL complete_except)(struct icpustate *__restrict self, uintptr_t opcode) {
	error_class_t cls = PERTASK_GET(this_exception_class);
	if (cls == E_ILLEGAL_INSTRUCTION) {
		if (!PERTASK_GET(this_exception_pointers[0]))
			PERTASK_SET(this_exception_pointers[0], opcode);
	} else if (cls == E_SEGFAULT) {
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
	PERTASK_SET(this_exception_faultaddr, (void *)icpustate_getpc(self));
#if EXCEPT_BACKTRACE_SIZE != 0
	{
		unsigned int i;
		for (i = 0; i < EXCEPT_BACKTRACE_SIZE; ++i)
			PERTASK_SET(this_exception_trace[i], (void *)0);
	}
#endif /* EXCEPT_BACKTRACE_SIZE != 0 */
	x86_userexcept_unwind_interrupt(self);
}

PRIVATE ATTR_NORETURN NONNULL((1)) void FCALL
throw_exception(struct icpustate *__restrict state,
                error_code_t code, uintptr_t opcode,
                uintptr_t ptr1, uintptr_t ptr2,
                uintptr_t ptr3, uintptr_t ptr4) {
	unsigned int i;
	void const *pc, *next_pc;
	pc      = (void const *)icpustate_getpc(state);
	next_pc = instruction_succ(pc);
	if (next_pc)
		icpustate_setpc(state, (uintptr_t)next_pc);
	PERTASK_SET(this_exception_code, code);
	PERTASK_SET(this_exception_faultaddr, (void *)pc);
	PERTASK_SET(this_exception_pointers[0], opcode);
	PERTASK_SET(this_exception_pointers[1], ptr1);
	PERTASK_SET(this_exception_pointers[2], ptr2);
	PERTASK_SET(this_exception_pointers[3], ptr3);
	PERTASK_SET(this_exception_pointers[4], ptr4);
	for (i = 5; i < EXCEPTION_DATA_POINTERS; ++i)
		PERTASK_SET(this_exception_pointers[i], (uintptr_t)0);
	/* Try to trigger a debugger trap (if enabled) */
	if (kernel_debugtrap_enabled() && (kernel_debugtrap_on & KERNEL_DEBUGTRAP_ON_ILLEGAL_INSTRUCTION))
		kernel_debugtrap(state, SIGILL);
	x86_userexcept_unwind_interrupt(state);
}

#define _EMU86_GETOPCODE()        EMU86_OPCODE()
#define _EMU86_GETOPCODE_RMREG()  E_ILLEGAL_INSTRUCTION_X86_OPCODE(EMU86_OPCODE(), modrm.mi_reg)
#define EMU86_EMULATE_RETURN_UNKNOWN_INSTRUCTION()           throw_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPCODE), _EMU86_GETOPCODE(), 0, 0, 0, 0)
#define EMU86_EMULATE_RETURN_UNKNOWN_INSTRUCTION_RMREG()     throw_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPCODE), _EMU86_GETOPCODE_RMREG(), 0, 0, 0, 0)
#define EMU86_EMULATE_RETURN_PRIVILEGED_INSTRUCTION()        throw_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE), _EMU86_GETOPCODE(), 0, 0, 0, 0)
#define EMU86_EMULATE_RETURN_PRIVILEGED_INSTRUCTION_RMREG()  throw_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_PRIVILEGED_OPCODE), _EMU86_GETOPCODE_RMREG(), 0, 0, 0, 0)
#define EMU86_EMULATE_RETURN_EXPECTED_MEMORY_MODRM()         throw_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND), _EMU86_GETOPCODE(), E_ILLEGAL_INSTRUCTION_BAD_OPERAND_ADDRMODE, 0, 0, 0)
#define EMU86_EMULATE_RETURN_EXPECTED_MEMORY_MODRM_RMREG()   throw_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND), _EMU86_GETOPCODE_RMREG(), E_ILLEGAL_INSTRUCTION_BAD_OPERAND_ADDRMODE, 0, 0, 0)
#define EMU86_EMULATE_RETURN_EXPECTED_REGISTER_MODRM()       throw_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND), _EMU86_GETOPCODE(), E_ILLEGAL_INSTRUCTION_BAD_OPERAND_ADDRMODE, 0, 0, 0)
#define EMU86_EMULATE_RETURN_EXPECTED_REGISTER_MODRM_RMREG() throw_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND), _EMU86_GETOPCODE_RMREG(), E_ILLEGAL_INSTRUCTION_BAD_OPERAND_ADDRMODE, 0, 0, 0)
#define EMU86_EMULATE_RETURN_UNEXPECTED_LOCK()               throw_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND), _EMU86_GETOPCODE(), op_flags, 0, 0, 0)
#define EMU86_EMULATE_RETURN_UNEXPECTED_LOCK_RMREG()         throw_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_BAD_OPERAND), _EMU86_GETOPCODE_RMREG(), op_flags, 0, 0, 0)
#define EMU86_EMULATE_RETURN_UNSUPPORTED_INSTRUCTION()       throw_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE), _EMU86_GETOPCODE(), 0, 0, 0, 0)
#define EMU86_EMULATE_RETURN_UNSUPPORTED_INSTRUCTION_RMREG() throw_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_UNSUPPORTED_OPCODE), _EMU86_GETOPCODE_RMREG(), 0, 0, 0, 0)
#define EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER(how, regno, regval, offset) \
	throw_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER),            \
	                _EMU86_GETOPCODE(), how, regno, regval, offset)
#define EMU86_EMULATE_THROW_ILLEGAL_INSTRUCTION_REGISTER_RMREG(how, regno, regval, offset) \
	throw_exception(_state, ERROR_CODEOF(E_ILLEGAL_INSTRUCTION_REGISTER),                  \
	                _EMU86_GETOPCODE_RMREG(), how, regno, regval, offset)
#define EMU86_EMULATE_GETOPFLAGS() emu86_opflagsof_icpustate(_state)
#define EMU86_EMULATE_TRANSLATEADDR_IS_NOOP 1
#define EMU86_EMULATE_TRANSLATEADDR(addr) (addr)
#define EMU86_GETCR4_UMIP_IS_ZERO 1
#define EMU86_GETCR4_UMIP() 0 /* TODO: Support me! */


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
#define EMU86_SETGSBASE(v) setgsbase(_state, (uintptr_t)(v))
PRIVATE NONNULL((1)) void FCALL
setfsbase(struct icpustate *__restrict state, uintptr_t value) {
	u16 myfs = __rdfs() & ~3;
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

PRIVATE NONNULL((1)) void FCALL
setgsbase(struct icpustate *__restrict state, uintptr_t value) {
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
#define EMU86_ISVM86() (EMU86_GETFLAGS() & EFLAGS_VM)
#endif /* !__x86_64__ */
#define EMU86_VALIDATE_READABLE(addr, num_bytes) validate_readable((void const *)(uintptr_t)(addr), num_bytes)
#define EMU86_VALIDATE_WRITABLE(addr, num_bytes) validate_writable((void *)(uintptr_t)(addr), num_bytes)


#ifdef __x86_64__
PRIVATE void KCALL
assert_canonical_address(void *addr, size_t num_bytes,
                         bool reading, bool writing) {
	(void)reading;
	if (ADDR_IS_NONCANON((byte_t *)addr) ||
	    ADDR_IS_NONCANON((byte_t *)addr + num_bytes - 1)) {
		THROW(E_SEGFAULT_UNMAPPED,
		      addr,
		      writing ? E_SEGFAULT_CONTEXT_NONCANON | E_SEGFAULT_CONTEXT_WRITING
		              : E_SEGFAULT_CONTEXT_NONCANON);
	}
}
#define EMU86_UNSUPPORTED_MEMACCESS(addr, num_bytes, reading, writing) \
	assert_canonical_address(addr, num_bytes, reading, writing)
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
	i386_getsegment_base(self->vea_args.va_state, segment_regno)
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
