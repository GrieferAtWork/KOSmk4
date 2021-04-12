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
#ifdef __INTELLISENSE__
#include "personality.c"
//#define DEFINE_NORMAL 1
#define DEFINE_BREAK 1
#endif /* __INTELLISENSE__ */

#if (defined(DEFINE_NORMAL) + defined(DEFINE_BREAK)) != 1
#error "Must #define exactly one of `DEFINE_NORMAL' or `DEFINE_BREAK'"
#endif

#ifdef DEFINE_NORMAL
#define FUNC(x)                           x
#define IFELSE_BREAK(if_normal, if_break) if_normal
#define UNUSED_IF_BREAK(x)                x
#else /* DEFINE_NORMAL */
#define FUNC(x)                           x##_break
#define IFELSE_BREAK(if_normal, if_break) if_break
#define UNUSED_IF_BREAK                   UNUSED
#endif /* !DEFINE_NORMAL */

DECL_BEGIN

#ifndef HALT_UNHANDLED_EXCEPTION_DEFINED
#define HALT_UNHANDLED_EXCEPTION_DEFINED 1
INTDEF void FCALL /* TODO: Get rid of this */
halt_unhandled_exception(unsigned int error,
                         struct kcpustate *__restrict unwind_state);
#endif /* !HALT_UNHANDLED_EXCEPTION_DEFINED */


/* The personality function used  to handle exceptions propagated  through
 * system calls. - Specifically, the special handling that is required for
 * servicing an RPC as `rpc_serve_user_redirection_all' */
INTERN unsigned int
NOTHROW(KCALL FUNC(x86_syscall_personality_asm32_int80))(struct unwind_fde_struct *__restrict fde,
                                                         struct kcpustate *__restrict state,
                                                         byte_t *UNUSED_IF_BREAK(lsda)) {
	struct ucpustate ustate;
	unsigned int error;
	struct rpc_syscall_info info;
	kcpustate_to_ucpustate(state, &ustate);
	{
		unwind_cfa_sigframe_state_t cfa;
		void const *pc = (void const *)(ucpustate_getpc(&ustate) - 1);
		error = unwind_fde_sigframe_exec(fde, &cfa, pc);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
		error = unwind_cfa_sigframe_apply(&cfa, fde, pc,
		                                  &unwind_getreg_kcpustate, state,
		                                  &unwind_setreg_ucpustate, &ustate);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
	}
	/* Check if the return state actually points into user-space,
	 * or  alternatively:  indicates  a  user-space  redirection. */
	if (ucpustate_iskernel(&ustate) &&
	    ucpustate_getpc(&ustate) != (uintptr_t)&x86_rpc_user_redirection)
		return DWARF_PERSO_ABORT_SEARCH;
#ifdef DEFINE_NORMAL
	/* System calls encode their vector number  as the LSDA pointer, so  that
	 * when  unwinding we can reverse-engineer that number in order to decide
	 * on special actions to perform based on the called function, as well as
	 * inform user-space of which function  caused the exception, as well  as
	 * implement system call restarting. */
	gpregs_setpax(&ustate.ucs_gpregs, (uintptr_t)lsda);
#endif /* DEFINE_NORMAL */
	rpc_syscall_info_get32_int80h(&info, &ustate);
	x86_userexcept_unwind(&ustate, &info);
err:
	halt_unhandled_exception(error, state);
	return DWARF_PERSO_ABORT_SEARCH;
}

/* The personality function used  to handle exceptions propagated  through
 * system calls. - Specifically, the special handling that is required for
 * servicing an RPC as `rpc_serve_user_redirection_all' */
INTERN unsigned int
NOTHROW(KCALL FUNC(x86_syscall_personality_asm32_sysenter))(struct unwind_fde_struct *__restrict fde,
                                                            struct kcpustate *__restrict state,
                                                            byte_t *UNUSED_IF_BREAK(lsda)) {
	struct ucpustate ustate;
	unsigned int error;
	struct rpc_syscall_info info;
	kcpustate_to_ucpustate(state, &ustate);
	{
		unwind_cfa_sigframe_state_t cfa;
		void const *pc = (void const *)(ucpustate_getpc(&ustate) - 1);
		error = unwind_fde_sigframe_exec(fde, &cfa, pc);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
		error = unwind_cfa_sigframe_apply(&cfa, fde, pc,
		                                  &unwind_getreg_kcpustate, state,
		                                  &unwind_setreg_ucpustate, &ustate);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
	}
	/* Check if the return state actually points into user-space,
	 * or  alternatively:  indicates  a  user-space  redirection. */
	if (ucpustate_iskernel(&ustate) &&
	    ucpustate_getpc(&ustate) != (uintptr_t)&x86_rpc_user_redirection)
		return DWARF_PERSO_ABORT_SEARCH;
#ifdef DEFINE_NORMAL
	/* System calls encode their vector number  as the LSDA pointer, so  that
	 * when  unwinding we can reverse-engineer that number in order to decide
	 * on special actions to perform based on the called function, as well as
	 * inform user-space of which function  caused the exception, as well  as
	 * implement system call restarting. */
	gpregs_setpax(&ustate.ucs_gpregs, (uintptr_t)lsda);
#endif /* DEFINE_NORMAL */
	rpc_syscall_info_get32_sysenter_nx(&info, &ustate);
	x86_userexcept_unwind(&ustate, &info);
err:
	halt_unhandled_exception(error, state);
	return DWARF_PERSO_ABORT_SEARCH;
}



#ifdef __x86_64__

/* The personality function used  to handle exceptions propagated  through
 * system calls. - Specifically, the special handling that is required for
 * servicing an RPC as `rpc_serve_user_redirection_all' */
INTERN unsigned int
NOTHROW(KCALL FUNC(x86_syscall_personality_asm64_syscall))(struct unwind_fde_struct *__restrict fde,
                                                           struct kcpustate *__restrict state,
                                                           byte_t *UNUSED_IF_BREAK(lsda)) {
	struct ucpustate ustate;
	unsigned int error;
	struct rpc_syscall_info info;
	kcpustate_to_ucpustate(state, &ustate);
	{
		unwind_cfa_sigframe_state_t cfa;
		void const *pc = (void const *)(ucpustate_getpc(&ustate) - 1);
		error = unwind_fde_sigframe_exec(fde, &cfa, pc);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
		error = unwind_cfa_sigframe_apply(&cfa, fde, pc,
		                                  &unwind_getreg_kcpustate, state,
		                                  &unwind_setreg_ucpustate, &ustate);
		if unlikely(error != UNWIND_SUCCESS)
			goto err;
	}
	/* Check if the return state actually points into user-space,
	 * or  alternatively:  indicates  a  user-space  redirection. */
	if (ucpustate_iskernel(&ustate) &&
	    ucpustate_getpc(&ustate) != (uintptr_t)&x86_rpc_user_redirection)
		return DWARF_PERSO_ABORT_SEARCH;
#ifdef DEFINE_NORMAL
	/* System calls encode their vector number  as the LSDA pointer, so  that
	 * when  unwinding we can reverse-engineer that number in order to decide
	 * on special actions to perform based on the called function, as well as
	 * inform user-space of which function  caused the exception, as well  as
	 * implement system call restarting. */
	gpregs_setpax(&ustate.ucs_gpregs, (uintptr_t)lsda);
#endif /* DEFINE_NORMAL */
	rpc_syscall_info_get64_int80h(&info, &ustate);
	x86_userexcept_unwind(&ustate, &info);
err:
	halt_unhandled_exception(error, state);
	return DWARF_PERSO_ABORT_SEARCH;
}
#endif /* __x86_64__ */



DECL_END

#undef FUNC
#undef IFELSE_BREAK
#undef UNUSED_IF_BREAK
#undef DEFINE_NORMAL
#undef DEFINE_BREAK
