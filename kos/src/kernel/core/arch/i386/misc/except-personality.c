/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MISC_EXCEPT_PERSONALITY_C
#define GUARD_KERNEL_CORE_ARCH_I386_MISC_EXCEPT_PERSONALITY_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>
#ifdef CONFIG_USE_NEW_RPC
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
#include <libunwind/unwind.h>

DECL_BEGIN

/************************************************************************/
/* Personality functions for system calls                               */
/************************************************************************/

/* The personality function used  to handle exceptions propagated  through
 * system calls. - Specifically, the special handling that is required for
 * servicing an RPC as `rpc_serve_user_redirection_all' */
INTERN WUNUSED NONNULL((1, 2)) unsigned int
NOTHROW(EXCEPT_PERSONALITY_CC x86_syscall_personality_asm32_int80)(struct unwind_fde_struct *__restrict fde,
                                                                   struct kcpustate *__restrict state) {
	struct ucpustate ustate;
	struct rpc_syscall_info sc_info;
	unwind_cfa_sigframe_state_t cfa;
	unsigned int error;
	void const *pc;
	kcpustate_to_ucpustate(state, &ustate);
	pc = ucpustate_getpc(&ustate) - 1;
	error = unwind_fde_sigframe_exec(fde, &cfa, pc);
	if unlikely(error != UNWIND_SUCCESS)
		return EXCEPT_PERSONALITY_CONTINUE_UNWIND;
	error = unwind_cfa_sigframe_apply(&cfa, fde, pc,
	                                  &unwind_getreg_kcpustate, state,
	                                  &unwind_setreg_ucpustate, &ustate);
	if unlikely(error != UNWIND_SUCCESS)
		return EXCEPT_PERSONALITY_CONTINUE_UNWIND;
	assert(ucpustate_iskernel(&ustate) ||
	       ucpustate_getpc(&ustate) == (void const *)&x86_userexcept_sysret);
	/* System calls encode their vector number  as the LSDA pointer, so  that
	 * when  unwinding we can reverse-engineer that number in order to decide
	 * on special actions to perform based on the called function, as well as
	 * inform user-space of which function  caused the exception, as well  as
	 * implement system call restarting. */
	gpregs_setpax(&ustate.ucs_gpregs, (uintptr_t)fde->f_persofun);
	rpc_syscall_info_get32_int80h(&sc_info, &ustate);
	userexcept_handler_ucpustate(&ustate, &sc_info);
}

/* The personality function used  to handle exceptions propagated  through
 * system calls. - Specifically, the special handling that is required for
 * servicing an RPC as `rpc_serve_user_redirection_all' */
INTERN WUNUSED NONNULL((1, 2)) unsigned int
NOTHROW(EXCEPT_PERSONALITY_CC x86_syscall_personality_asm32_sysenter)(struct unwind_fde_struct *__restrict fde,
                                                                      struct kcpustate *__restrict state) {
	struct ucpustate ustate;
	unsigned int error;
	struct rpc_syscall_info sc_info;
	kcpustate_to_ucpustate(state, &ustate);
	{
		unwind_cfa_sigframe_state_t cfa;
		void const *pc = ucpustate_getpc(&ustate) - 1;
		error = unwind_fde_sigframe_exec(fde, &cfa, pc);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
		error = unwind_cfa_sigframe_apply(&cfa, fde, pc,
		                                  &unwind_getreg_kcpustate, state,
		                                  &unwind_setreg_ucpustate, &ustate);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
	}
	assert(ucpustate_iskernel(&ustate) ||
	       ucpustate_getpc(&ustate) == (void const *)&x86_userexcept_sysret);
	/* System calls encode their vector number  as the LSDA pointer, so  that
	 * when  unwinding we can reverse-engineer that number in order to decide
	 * on special actions to perform based on the called function, as well as
	 * inform user-space of which function  caused the exception, as well  as
	 * implement system call restarting. */
	gpregs_setpax(&ustate.ucs_gpregs, (uintptr_t)fde->f_lsdaaddr);
	rpc_syscall_info_get32_sysenter_nx(&sc_info, &ustate);
	userexcept_handler_ucpustate(&ustate, &sc_info);
err:
	return EXCEPT_PERSONALITY_CONTINUE_UNWIND;
}



#ifdef __x86_64__

/* The personality function used  to handle exceptions propagated  through
 * system calls. - Specifically, the special handling that is required for
 * servicing an RPC as `rpc_serve_user_redirection_all' */
INTERN WUNUSED NONNULL((1, 2)) unsigned int
NOTHROW(EXCEPT_PERSONALITY_CC x86_syscall_personality_asm64_syscall)(struct unwind_fde_struct *__restrict fde,
                                                                     struct kcpustate *__restrict state) {
	struct ucpustate ustate;
	unsigned int error;
	struct rpc_syscall_info sc_info;
	kcpustate_to_ucpustate(state, &ustate);
	{
		unwind_cfa_sigframe_state_t cfa;
		void const *pc = ucpustate_getpc(&ustate) - 1;
		error = unwind_fde_sigframe_exec(fde, &cfa, pc);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
		error = unwind_cfa_sigframe_apply(&cfa, fde, pc,
		                                  &unwind_getreg_kcpustate, state,
		                                  &unwind_setreg_ucpustate, &ustate);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
	}
	assert(ucpustate_iskernel(&ustate) ||
	       ucpustate_getpc(&ustate) == (void const *)&x86_userexcept_sysret);
	/* System calls encode their vector number  as the LSDA pointer, so  that
	 * when  unwinding we can reverse-engineer that number in order to decide
	 * on special actions to perform based on the called function, as well as
	 * inform user-space of which function  caused the exception, as well  as
	 * implement system call restarting. */
	gpregs_setpax(&ustate.ucs_gpregs, (uintptr_t)fde->f_persofun);
	rpc_syscall_info_get64_int80h(&sc_info, &ustate);
	userexcept_handler_ucpustate(&ustate, &sc_info);
err:
	return EXCEPT_PERSONALITY_CONTINUE_UNWIND;
}
#endif /* __x86_64__ */















/************************************************************************/
/* Personality functions for restartable interrupt handlers             */
/************************************************************************/
/* Don't look; this is super hacked together and works in tandem with
 * `idt/exceptidt32-exception.S'  and   `idt/exceptidt64-exception.S' */

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

INTERN WUNUSED NONNULL((1, 2)) unsigned int
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

INTERN WUNUSED NONNULL((1, 2)) unsigned int
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

INTERN WUNUSED NONNULL((1, 2)) unsigned int
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
	addr  = (void *)state->kcs_gpregs.gp_Pbx;
	ecode = state->kcs_gpregs.gp_Pbx;
	x86_xintr3_userexcept_unwind(st, fde->f_lsdaaddr, ecode, addr);
}
/************************************************************************/

DECL_END
#endif /* CONFIG_USE_NEW_RPC */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MISC_EXCEPT_PERSONALITY_C */
