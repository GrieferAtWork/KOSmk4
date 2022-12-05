/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_EXCEPT_PERSONALITY_C
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_EXCEPT_PERSONALITY_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/rt/except-handler.h>
#include <kernel/rt/except-personality.h>
#include <kernel/x86/syscall-info.h>

#include <kos/bits/syscall-info.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/rpc.h>

#include <assert.h>
#include <stddef.h>

#include <libunwind/eh_frame.h>
#include <libunwind/errno.h>
#include <libunwind/register.h>
#include <libunwind/unwind.h>

DECL_BEGIN

/************************************************************************/
/* Personality functions for system calls                               */
/************************************************************************/


/* System calls encode their vector number  as the LSDA pointer, so  that
 * when  unwinding we can reverse-engineer that number in order to decide
 * on special actions to perform based on the called function, as well as
 * inform user-space of which function  caused the exception, as well  as
 * implement system call restarting. */
#define unwind_fde_getsysno(fde) ((uintptr_t)(fde)->f_lsdaaddr)


/* Only  `struct icpustate's helper macros include checks for `x86_userexcept_sysret',
 * such that registers are read from TLS memory instead. This is intended and actually
 * required since only `struct icpustate' allows for the assumption that the given CPU
 * state _actually_ belongs to the calling thread.
 *
 * However, there is one problem with this that is addressed here:
 *   - When `x86_userexcept_sysret' was injected (s.a. `userexcept_sysret_inject_nopr()'),
 *     then  IRET.EFLAGS was set to `0', which  regular unwinding will (correctly so) pick
 *     up on and apply when unwinding reaches `x86_userexcept_sysret' (as it may very well
 *     in any of the personality functions below)
 *   - When this happens, then the EFLAGS value used for loading RPC syscall information
 *     will  also be equal to `0', but this has as a consequence that we'd never realize
 *     when the system call was performed  with exceptions enabled (which user-space  is
 *     able to select using EFLAGS.DF)
 *   - As  such, we must manually check for this  situation and set the EXCEPT flag based
 *     on what is stored in `this_x86_sysret_iret', rather than the constant `0' normally
 *     unwound in this scenario.
 */
LOCAL NOBLOCK WUNUSED NONNULL((1, 2)) void
NOTHROW(FCALL syscall_info_amend_FEXCEPT)(struct rpc_syscall_info *__restrict self,
                                          struct ucpustate const *__restrict ustate) {
	if ((void *)ucpustate_getpc(ustate) == (void *)&x86_userexcept_sysret) {
		assert(!(self->rsi_flags & RPC_SYSCALL_INFO_FEXCEPT));
		assert(ucpustate_getpflags(ustate) == 0);
		if (PERTASK_TESTMASK(this_x86_sysret_iret.ir_Pflags, EFLAGS_DF))
			self->rsi_flags |= RPC_SYSCALL_INFO_FEXCEPT;
	}
}


/* The personality function used  to handle exceptions propagated  through
 * system calls. - Specifically, the special handling that is required for
 * servicing an RPC during `userexcept_handler()' */
INTERN ABNORMAL_RETURN WUNUSED NONNULL((1, 2)) unsigned int
NOTHROW(EXCEPT_PERSONALITY_CC x86_syscall_personality_asm32_int80)(struct unwind_fde_struct *__restrict fde,
                                                                   struct kcpustate *__restrict state) {
	struct ucpustate ustate;
	struct rpc_syscall_info sc_info;
	unwind_cfa_sigframe_state_t cfa;
	unwind_errno_t error;
	void const *pc;
	kcpustate_to_ucpustate(state, &ustate);
	pc = ucpustate_getpc(&ustate) - 1;
	error = unwind_fde_sigframe_exec(fde, &cfa, pc);
	if unlikely(error != UNWIND_SUCCESS)
		return EXCEPT_PERSONALITY_CONTINUE_UNWIND;
	error = unwind_cfa_sigframe_apply_sysret_safe(&cfa, fde, pc,
	                                              &unwind_getreg_kcpustate, state,
	                                              &unwind_setreg_ucpustate, &ustate);
	if unlikely(error != UNWIND_SUCCESS)
		return EXCEPT_PERSONALITY_CONTINUE_UNWIND;
	assert(ucpustate_isuser(&ustate) ||
	       ucpustate_getpc(&ustate) == (void const *)&x86_userexcept_sysret);
	gpregs_setpax(&ustate.ucs_gpregs, unwind_fde_getsysno(fde));
	rpc_syscall_info_get32_int80h(&sc_info, &ustate);
	syscall_info_amend_FEXCEPT(&sc_info, &ustate);
	userexcept_handler_ucpustate(&ustate, &sc_info);
	__builtin_unreachable();
}

/* The personality function used  to handle exceptions propagated  through
 * system calls. - Specifically, the special handling that is required for
 * servicing an RPC during `userexcept_handler()' */
INTERN ABNORMAL_RETURN WUNUSED NONNULL((1, 2)) unsigned int
NOTHROW(EXCEPT_PERSONALITY_CC x86_syscall_personality_asm32_sysenter)(struct unwind_fde_struct *__restrict fde,
                                                                      struct kcpustate *__restrict state) {
	struct ucpustate ustate;
	struct rpc_syscall_info sc_info;
	unwind_cfa_sigframe_state_t cfa;
	unwind_errno_t error;
	void const *pc;
	kcpustate_to_ucpustate(state, &ustate);
	pc = ucpustate_getpc(&ustate) - 1;
	error = unwind_fde_sigframe_exec(fde, &cfa, pc);
	if unlikely(error != UNWIND_SUCCESS)
		return EXCEPT_PERSONALITY_CONTINUE_UNWIND;
	error = unwind_cfa_sigframe_apply_sysret_safe(&cfa, fde, pc,
	                                              &unwind_getreg_kcpustate, state,
	                                              &unwind_setreg_ucpustate, &ustate);
	if unlikely(error != UNWIND_SUCCESS)
		return EXCEPT_PERSONALITY_CONTINUE_UNWIND;
	assert(ucpustate_isuser(&ustate) ||
	       ucpustate_getpc(&ustate) == (void const *)&x86_userexcept_sysret);
	gpregs_setpax(&ustate.ucs_gpregs, unwind_fde_getsysno(fde));
	rpc_syscall_info_get32_sysenter_nx(&sc_info, &ustate);
	syscall_info_amend_FEXCEPT(&sc_info, &ustate);
	userexcept_handler_ucpustate(&ustate, &sc_info);
	__builtin_unreachable();
}



#ifdef __x86_64__

/* The personality function used  to handle exceptions propagated  through
 * system calls. - Specifically, the special handling that is required for
 * servicing an RPC during `userexcept_handler()' */
INTERN ABNORMAL_RETURN WUNUSED NONNULL((1, 2)) unsigned int
NOTHROW(EXCEPT_PERSONALITY_CC x86_syscall_personality_asm64_syscall)(struct unwind_fde_struct *__restrict fde,
                                                                     struct kcpustate *__restrict state) {
	struct ucpustate ustate;
	struct rpc_syscall_info sc_info;
	unwind_cfa_sigframe_state_t cfa;
	unwind_errno_t error;
	void const *pc;
	kcpustate_to_ucpustate(state, &ustate);
	pc = ucpustate_getpc(&ustate) - 1;
	error = unwind_fde_sigframe_exec(fde, &cfa, pc);
	if unlikely(error != UNWIND_SUCCESS)
		return EXCEPT_PERSONALITY_CONTINUE_UNWIND;
	error = unwind_cfa_sigframe_apply_sysret_safe(&cfa, fde, pc,
	                                              &unwind_getreg_kcpustate, state,
	                                              &unwind_setreg_ucpustate, &ustate);
	if unlikely(error != UNWIND_SUCCESS)
		return EXCEPT_PERSONALITY_CONTINUE_UNWIND;
	assert(ucpustate_isuser(&ustate) ||
	       ucpustate_getpc(&ustate) == (void const *)&x86_userexcept_sysret);
	gpregs_setpax(&ustate.ucs_gpregs, unwind_fde_getsysno(fde));
	rpc_syscall_info_get64_int80h(&sc_info, &ustate);
	syscall_info_amend_FEXCEPT(&sc_info, &ustate);
	userexcept_handler_ucpustate(&ustate, &sc_info);
	__builtin_unreachable();
}
#endif /* __x86_64__ */















/************************************************************************/
/* Personality functions for restartable interrupt handlers             */
/************************************************************************/
/* Don't look; this is super hacked together and works in tandem
 * with   `idt/idt32-exception.S'   and  `idt/idt64-exception.S' */

/* The following registers are passed (unmodified) to LSDA: %Pbx, %Pbp
 * LSDA   is   passed   via   register:   [i386:'%edi', x86_64:'%r12']
 * The CPU state is passed via register `%R_fcall0P' */
extern void ASMCALL _x86_xintr_userexcept_unwind(void);

#ifdef __x86_64__
#define _GCC_ASM_R_fcall0P "D"
#else /* __x86_64__ */
#define _GCC_ASM_R_fcall0P "c"
#endif /* !__x86_64__ */

#ifdef __x86_64__
#define x86_xintr1_userexcept_unwind(st, lsda)                  \
	do {                                                        \
		__register void const *r12 __asm__("%r12") = (lsda);    \
		__asm__ __volatile__("jmp _x86_xintr_userexcept_unwind" \
		                     :                                  \
		                     : "r"                (r12)         \
		                     , _GCC_ASM_R_fcall0P (st));        \
		__builtin_unreachable();                                \
	}	__WHILE0
#define x86_xintr2_userexcept_unwind(st, lsda, ecode)           \
	do {                                                        \
		__register void const *r12 __asm__("%r12") = (lsda);    \
		__asm__ __volatile__("jmp _x86_xintr_userexcept_unwind" \
		                     :                                  \
		                     : "r"                (r12)         \
		                     , "b"                (ecode)       \
		                     , _GCC_ASM_R_fcall0P (st));        \
		__builtin_unreachable();                                \
	}	__WHILE0
#define x86_xintr3_userexcept_unwind(st, lsda, ecode, addr)     \
	do {                                                        \
		__register void const *r12 __asm__("%r12") = (lsda);    \
		__asm__ __volatile__("movq %%rax, %%rbp\n\t"            \
		                     "jmp _x86_xintr_userexcept_unwind" \
		                     :                                  \
		                     : "b"                (ecode)       \
		                     , "r"                (r12)         \
		                     , "a"                (addr)        \
		                     , _GCC_ASM_R_fcall0P (st));        \
		__builtin_unreachable();                                \
	}	__WHILE0
#else /* __x86_64__ */
#define x86_xintr1_userexcept_unwind(st, lsda)                  \
	do {                                                        \
		__asm__ __volatile__("jmp _x86_xintr_userexcept_unwind" \
		                     :                                  \
		                     : "D"                (lsda)        \
		                     , _GCC_ASM_R_fcall0P (st));        \
		__builtin_unreachable();                                \
	}	__WHILE0
#define x86_xintr2_userexcept_unwind(st, lsda, ecode)           \
	do {                                                        \
		__asm__ __volatile__("jmp _x86_xintr_userexcept_unwind" \
		                     :                                  \
		                     : "D"                (lsda)        \
		                     , "b"                (ecode)       \
		                     , _GCC_ASM_R_fcall0P (st));        \
		__builtin_unreachable();                                \
	}	__WHILE0
extern void ASMCALL _x86_xintr3_userexcept_unwind(void);
#define x86_xintr3_userexcept_unwind(st, lsda, ecode, addr)      \
	do {                                                         \
		__asm__ __volatile__("movl %%eax, %%ebp\n\t"             \
		                     "jmp _x86_xintr3_userexcept_unwind" \
		                     :                                   \
		                     : "D"                (lsda)         \
		                     , "b"                (ecode)        \
		                     , "a"                (addr)         \
		                     , _GCC_ASM_R_fcall0P (st));         \
		__builtin_unreachable();                                 \
	}	__WHILE0
#endif /* !__x86_64__ */

INTERN ABNORMAL_RETURN WUNUSED NONNULL((1, 2)) unsigned int
NOTHROW(EXCEPT_PERSONALITY_CC x86_xintr1_userexcept_personality)(struct unwind_fde_struct *__restrict fde,
                                                                 struct kcpustate *__restrict state) {
	struct icpustate *st;
	st = (struct icpustate *)state->kcs_gpregs.gp_Psp;
	if (!icpustate_isuser(st))
		return EXCEPT_PERSONALITY_CONTINUE_UNWIND;
	/* Unwind into user-space. */
	PREEMPTION_ENABLE();
	x86_xintr1_userexcept_unwind(st, fde->f_lsdaaddr);
}

INTERN ABNORMAL_RETURN WUNUSED NONNULL((1, 2)) unsigned int
NOTHROW(EXCEPT_PERSONALITY_CC x86_xintr2_userexcept_personality)(struct unwind_fde_struct *__restrict fde,
                                                                 struct kcpustate *__restrict state) {
	struct icpustate *st;
	uintptr_t ecode;
	st = (struct icpustate *)state->kcs_gpregs.gp_Psp;
	if (!icpustate_isuser(st))
		return EXCEPT_PERSONALITY_CONTINUE_UNWIND;
	/* Unwind into user-space. */
	PREEMPTION_ENABLE();
	ecode = state->kcs_gpregs.gp_Pbx;
	x86_xintr2_userexcept_unwind(st, fde->f_lsdaaddr, ecode);
}

INTERN ABNORMAL_RETURN WUNUSED NONNULL((1, 2)) unsigned int
NOTHROW(EXCEPT_PERSONALITY_CC x86_xintr3_userexcept_personality)(struct unwind_fde_struct *__restrict fde,
                                                                 struct kcpustate *__restrict state) {
	struct icpustate *st;
	uintptr_t ecode;
	void *addr;
#ifdef __x86_64__
	st = (struct icpustate *)state->kcs_gpregs.gp_Psp;
#else /* __x86_64__ */
	st = (struct icpustate *)(state->kcs_gpregs.gp_Psp + 4);
#endif /* !__x86_64__ */
	if (!icpustate_isuser(st))
		return EXCEPT_PERSONALITY_CONTINUE_UNWIND;
	/* Unwind into user-space. */
	PREEMPTION_ENABLE();
	addr  = (void *)state->kcs_gpregs.gp_Pbp;
	ecode = state->kcs_gpregs.gp_Pbx;
	x86_xintr3_userexcept_unwind(st, fde->f_lsdaaddr, ecode, addr);
}
/************************************************************************/






/* A helpful, predefined  personality function  that is meant  to be  used for  assembly
 * function which need to be able to handle exceptions in a fairly user-friendly manner.
 * NOTE: In order to define handlers, make use of the macros defined above.
 * NOTE: When   the  handler  is   entered,  callee-clobber  registers   may  have  been  clobbered
 *       if the exception was thrown  by a called function  that didn't encode CFI  instrumentation
 *       for preserving those  registers. All other  registers have  the same value  as they  would
 *       have had after a throwing function had returned normally, or before a throwing instruction
 *       had been invoked (with the obvious exception of `%Pip')
 *       Separately, you may include `DW_CFA_GNU_args_size' directives within your function,
 *       which  are recognized as adjustments for `%esp'  and are applied prior to execution
 *       or the specified handler. */
PUBLIC WUNUSED NONNULL((1, 2)) unsigned int
NOTHROW(EXCEPT_PERSONALITY_CC x86_asm_except_personality)(struct unwind_fde_struct *__restrict fde,
                                                          struct kcpustate *__restrict state) {
	struct x86_asm_except_entry const *ent;
	void const *pc = kcpustate_getpc(state);
	ent = (struct x86_asm_except_entry const *)fde->f_lsdaaddr;
	if (ent) {
		for (; ent->ee_entry != 0; ++ent) {
			/* NOTE: Compare while keeping in mind that `pc' points
			 *       _after_  the  faulting /  calling instruction. */
			if (pc > ent->ee_start && pc <= ent->ee_end) {
				if (ent->ee_mask != (uintptr_t)-1) {
					except_code_t code = except_code();
					if (EXCEPT_SUBCLASS(ent->ee_mask) != 0
					    ? ent->ee_mask != code
					    : EXCEPT_CLASS(ent->ee_mask) != EXCEPT_CLASS(code))
						continue; /* Different mask. */
				}
				kcpustate_setpc(state, ent->ee_entry);
				return EXCEPT_PERSONALITY_EXECUTE_HANDLER;
			}
		}
	}
	return EXCEPT_PERSONALITY_CONTINUE_UNWIND;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_EXCEPT_PERSONALITY_C */
