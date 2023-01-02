/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_RT_EXCEPT_HANDLER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_RT_EXCEPT_HANDLER_H 1

/* Special kernel exception handlers (for system calls, posix signals, etc.) */

#include <kernel/compiler.h>

#include <kernel/arch/rt/except-handler.h>
#include <kernel/types.h>

#include <bits/os/sigaction.h> /* `struct kernel_sigaction' */
#include <kos/bits/syscall-info.h>
#include <kos/rpc.h>

/*
 * ==================================================================================================
 * ============================ Userspace <--> RPC control flow overview ============================
 * ==================================================================================================
 *
 * ```
 *  userexcept_sysret_inject_nopr() <─┐
 *     │                              │
 *     v                              │
 * [userexcept_sysret]                │
 *  ^ [serve RPCs]                    │
 *  │      │                          │
 *  │      │                       ╔══╧════════╗
 *  │      └─────────────────────> ║ USERSPACE ║ <──────┐
 *  │                              ╚════════╤══╝        │
 *  │                                 ^     │           │
 *  │                                 │     │           │
 *  └───────────┬─────────────────────┘     │       `userexcept_callhandler()' or
 *              │                           v       `userexcept_callsignal()' or
 *              │   ┌───────────── SyscallEntry     `userexcept_seterrno()'
 *              │   │                 ┌────┐            ^
 *              │   v                 │[*] │            │
 *     ┌─────> Syscall ──> THROW() ───┤    v            │
 *     │          │                   │  [userexcept_handler]
 *     │          v                   │      [serve RPCs (and handle `E_INTERRUPT_USER_RPC')]
 *     │    [task_serve()]            │      [- When no RPCs got handled (as can happen with RPCs that ]
 *     │          │                   │      [  can only be served when inside special system calls, as]
 *     │          v                   │    ┌─[  required by `RPC_SYNCMODE_F_REQUIRE_CP'), restart the  ]
 *     │    [THROW(E_INTERRUPT_USER_RPC)]  │ [  system call after marking them _RPC_CONTEXT_INACTIVE.  ]
 *     │                                   │ [  The flag is later cleared in `userexcept_sysret'       ]
 *     │                                   │
 *     └───────────────────────────────────┘
 * ```
 *
 * ==================================================================================================
 * [*] Exception handling figuratively "scrapes" by syscall entry points. The
 *     same also goes  for exceptions thrown  during non-syscall  interrupts,
 *     which  must also be restartable in the  above model. In this case, you
 *     may can read `Syscall' as `Interrupt'.
 * ==================================================================================================
 */


#ifdef __CC__
DECL_BEGIN

struct icpustate;
struct task;
struct taskpid;


/* Throw the current exception (which must _NOT_ be E_INTERRUPT_USER_RPC)
 * at the the given `state' and  perform all of the necessary  unwinding.
 *
 * This  function should  be used  for throwing  exception from interrupt
 * handlers (read: CPU exception handler), such as page-faults & similar. */
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL except_throw_current_at_icpustate)(struct icpustate *__restrict state);



/* Arch-specific function:
 * Try to invoke the user-space exception handler for `error'
 * WARNING: Because this function writes to the user-space stack,
 *          it  is  capable of  throwing an  `E_SEGFAULT' itself.
 * @param: state:   The user-space CPU state (note that `icpustate_isuser(state)' is assumed!)
 * @param: sc_info: When  non-NULL, information about  the system call  that caused the exception.
 *                  Otherwise, if this argument is `NULL', the exception was caused by user-space,
 *                  such as a user-space program causing an `E_SEGFAULT', as opposed to the kernel
 *                  throwing an `E_FSERROR_FILE_NOT_FOUND'
 *            HINT: Additional information about how the system call was invoked can be
 *                  extracted from `sc_info->rsi_flags' (s.a. `<kos/asm/rpc-method.h>')
 * @return: NULL:   User-space does not define an exception handler.
 * @return: * :     The updated interrupt CPU state, modified to invoke the
 *                  user-space exception handler once user-space  execution
 *                  resumes. */
FUNDEF WUNUSED NONNULL((1, 3)) struct icpustate *FCALL
userexcept_callhandler(struct icpustate *__restrict state,
                       struct rpc_syscall_info const *sc_info,
                       struct exception_data const *__restrict error)
		THROWS(E_SEGFAULT);

#ifndef __siginfo_t_defined
#define __siginfo_t_defined
struct __siginfo_struct;
typedef struct __siginfo_struct siginfo_t;
#endif /* !__siginfo_t_defined */

/* Update the given  `state' to raise  the specified `siginfo'  as
 * a user-space signal  within the calling  thread. The caller  is
 * responsible  to  handle   special  signal  handlers   (`SIG_*')
 * before calling this function! This function should only be used
 * to  enqueue the execution of a signal handler with a user-space
 * entry point.
 *
 * Functionality  like  `SA_RESETHAND', or  system call
 * restart selection must be implemented by the caller.
 *
 * @param: state:   The CPU state describing the return to user-space.
 * @param: action:  The signal action to perform.
 * @param: siginfo: The signal that is being raised.
 * @param: sc_info: When  non-NULL, `sc_info' describes a system call
 *                  that will be restarted once the user-space signal
 *                  handler returns. No additional  should-really-be-
 *                  re-started  logic is done  by this function (iow:
 *                  such logic must be implemented by the caller)
 * @return: * :     The updated CPU state. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct icpustate *FCALL
userexcept_callsignal(struct icpustate *__restrict state,
                      struct kernel_sigaction const *__restrict action,
                      siginfo_t const *__restrict siginfo,
                      struct rpc_syscall_info const *sc_info)
		THROWS(E_SEGFAULT);


/* Arch-specific function:
 * Translate the current exception into an errno and set that errno
 * as the return value of  the system call described by  `sc_info'. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct icpustate *FCALL
userexcept_seterrno(struct icpustate *__restrict state,
                    struct rpc_syscall_info const *__restrict sc_info,
                    struct exception_data const *__restrict error)
		THROWS(E_SEGFAULT);



/* High-level exception handler that must be called by _all_ interrupts
 * and system call invocation wrappers.  This function is very  special
 * in that it _only_ returns when the associated interrupt/syscall must
 * be restarted immediately (for whatever reason).
 *
 * When  anything else needs to be done  in order to handle the currently
 * set exception, then this function won't return normally, but will load
 * the (at that point modified) `state' directly (via `cpu_apply(3)')
 *
 * The implementation of this function serves the function  documented
 * in <kos/rpc.md> under the name `generic_interrupt_or_system_call()'
 *
 * WARNING: When this function returns, it will have cleared the current
 *          exception, as it is also capable of handling (some)  errors,
 *          most notably `E_INTERRUPT_USER_RPC'! */
FUNDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL userexcept_handler)(struct icpustate *__restrict state,
                                  struct rpc_syscall_info const *sc_info);

/* Helper function to implement ENOSYS handling. */
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1, 2)) void
NOTHROW(FCALL userexcept_handler_nosys)(struct icpustate *__restrict state,
                                        struct rpc_syscall_info const *__restrict sc_info);


#ifndef __sigset_t_defined
#define __sigset_t_defined
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

/* Same as `userexcept_handler()', but use the given `sigmask'
 * instead of the calling thread's thread-local one. Used  for
 * the implementation of `sigsuspend(2)' */
FUNDEF ABNORMAL_RETURN ATTR_RETNONNULL WUNUSED NONNULL((1, 3)) struct icpustate *
NOTHROW(FCALL userexcept_handler_with_sigmask)(struct icpustate *__restrict state,
                                               struct rpc_syscall_info const *sc_info,
                                               sigset_t const *__restrict sigmask);


/* Arch-specific function:
 * Wrapper around `userexcept_handler()' for use in implementing `except_unwind()'.
 * This function will (safely) construct  a complete `struct icpustate' at the  far
 * end of the  calling thread's  stack and populate  with with  register info  from
 * `state'.  Afterwards,  it will  force-unwind the  kernel stack  such that  it is
 * located  immediately at the new state. Once that is done, a call to the portable
 * function `userexcept_handler(<state>, sc_info)' is  made, and  if that  function
 * returns  normally,  either  `syscall_emulate_r(..., sc_info)'  if  non-NULL,  or
 * directly load the associated state by means of `cpu_apply_icpustate()'. */
FUNDEF ABNORMAL_RETURN ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL userexcept_handler_ucpustate)(struct ucpustate *__restrict state,
                                            struct rpc_syscall_info const *sc_info);

/* This is the function that is injected by `userexcept_sysret_inject_nopr()',
 * as well as related functions.
 *
 * The   implementation  of  this  function  serves  the  function
 * documented in <kos/rpc.md> under the name `handle_sysret_rpc()' */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL userexcept_sysret)(struct icpustate *__restrict state);


/* Arch-specific function:
 * If not done already, modify  `state' such that rather than  returning
 * to  user-space (which the  caller is responsible to  ensure by use of
 * `assert(icpustate_isuser(state))'), it will make a round-trip through
 * arch-specific wrappers which  eventually call  `userexcept_sysret()'.
 * Once that function  returns, execution will  finally resume in  user-
 * space,  unless  this function  (or `userexcept_sysret_inject_nopr()')
 * was called yet again.
 * NOTE: The  given `state' must point to user-space, and be located at
 *       the very end of the kernel stack. This requirement is asserted
 *       internally by this function! */
FUNDEF NOBLOCK NOPREEMPT ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL userexcept_sysret_inject_with_state_nopr)(struct icpustate *__restrict state);


/* Arch-specific function:
 * Inject a call to `userexcept_sysret()' that is performed before `thread'
 * returns  back to user-space the next time. This function works correctly
 * even when `thread == THIS_TASK', or when the injection has already  been
 * performed (either by a  prior call to  this function, or  by use of  the
 * sibling function `userexcept_sysret_inject_with_state_nopr()'), in which
 * case the call is silent no-op.
 *
 * However, the caller still has to ensure `thread' won't make any  kernel-
 * user transitions for the duration of this call. The only way this can be
 * done, which this function also internally asserts to be the case, is  by
 * disabling preemption (hence the `NOPREEMPT'), and ensuring that `thread'
 * is hosted by  the current cpu  (iow: `thread->t_cpu == THIS_CPU').  When
 * either of these conditions aren't met, this function causes kernel panic
 *
 * Additionally, the caller must also ensure that `thread' is still running
 * and  has  yet   to  terminate  (iow:   `TASK_FTERMINATING'  isn't   set) */
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL userexcept_sysret_inject_nopr)(struct task *__restrict thread);

/* Check if the calling thread's IRET tail was redirected. */
#ifndef ARCH_HAVE_USEREXCEPT_SYSRET_INJECTED
FUNDEF NOBLOCK WUNUSED __BOOL
NOTHROW(FCALL userexcept_sysret_injected)(void);
#endif /* !ARCH_HAVE_USEREXCEPT_SYSRET_INJECTED */

/* Same as `userexcept_sysret_injected()', but allowed to given false
 * positives, though  is  _NOT_  allowed to  given  false  negatives. */
#ifndef ARCH_HAVE_USEREXCEPT_SYSRET_MAYBE_INJECTED
#define userexcept_sysret_maybe_injected() userexcept_sysret_injected()
#endif /* !ARCH_HAVE_USEREXCEPT_SYSRET_MAYBE_INJECTED */


/* Repeat a given expression if  the caller's IRET tail  might
 * have been redirected after/during the first call. This way,
 * we can assert that the  `expr' is called with a  consistent
 * context in regards to sysret having been injected.
 *
 * This is highly important to prevent an inconsistent register
 * state in situations such as exception unwinding, as a random
 * sysret injection can alter  stack values while they're  also
 * being read by the  unwind system, which assumes  consistency
 * in regards to memory reads.
 *
 * Also note that when preemption is disabled, you do not need
 * to make use of this, as preemption being enabled is one  of
 * the requirements for sysret to be randomly injected. */
#if 0
#define _call_with_consistent_sysret(expr)                            \
	({                                                                \
		__BOOL __cwfsr_was      = userexcept_sysret_maybe_injected(); \
		__auto_type __cwfsr_res = expr;                               \
		if (!__cwfsr_was && userexcept_sysret_maybe_injected())       \
			__cwfsr_res = expr;                                       \
		__cwfsr_res;                                                  \
	})
#else
/* Less efficient after re-direct, but still guaranties consistency. */
#define _call_with_consistent_sysret(expr)      \
	({                                          \
		__auto_type __cwfsr_res = expr;         \
		if (userexcept_sysret_maybe_injected()) \
			__cwfsr_res = expr;                 \
		__cwfsr_res;                            \
	})
#endif


/* Helper macros to perform the specified operations in a manner that is safe
 * to be done with preemption enabled, even in a situation where unwinding is
 * done  on the caller  thread's stack, and even  if another thread redirects
 * the caller's IRET tail while unwinding is being performed. */
#define unwind_cfa_apply_sysret_safe(self, fde, absolute_pc, reg_getter, reg_getter_arg, reg_setter, reg_setter_arg) \
	_call_with_consistent_sysret(unwind_cfa_apply(self, fde, absolute_pc, reg_getter, reg_getter_arg, reg_setter, reg_setter_arg))
#define unwind_cfa_sigframe_apply_sysret_safe(self, fde, absolute_pc, reg_getter, reg_getter_arg, reg_setter, reg_setter_arg) \
	_call_with_consistent_sysret(unwind_cfa_sigframe_apply(self, fde, absolute_pc, reg_getter, reg_getter_arg, reg_setter, reg_setter_arg))
#define unwind_sysret_safe(absolute_pc, reg_getter, reg_getter_arg, reg_setter, reg_setter_arg) \
	_call_with_consistent_sysret(unwind(absolute_pc, reg_getter, reg_getter_arg, reg_setter, reg_setter_arg))




/* Arch-specific function: Behaves identical to:
 * >> preemption_flag_t was;
 * >> preemption_pushoff(&was);
 * >> userexcept_sysret_inject_nopr(THIS_TASK);
 * >> preemption_pop(&was);
 * This function can be used to force checks for RPCs (including  posix
 * signals) to be performed _after_ a  system has completed (even in  a
 * scenario where the system call completes successfully). This kind of
 * functionality is required for some POSIX-signal-related system calls */
FUNDEF NOBLOCK void
NOTHROW(FCALL userexcept_sysret_inject_self)(void);



/* High-level wrapper  for `userexcept_sysret_inject_nopr()'  that makes  all
 * of the right decisions to only ever call `userexcept_sysret_inject_nopr()'
 * in  a valid context: using IPIs to make  the call from the same CPU as the
 * one  currently hosting `thread',  and ensuring that the  thread has yet to
 * terminate.
 * Additionally, this function will make a call to `task_wake()'  once
 * the injection has completed, meaning that `thread' will wake up and
 * either immediately start  executing `userexcept_sysret()', or  will
 * handle a sporadic interrupt via a call to `task_serve()'.
 *
 * Note that the  actual injection may  complete asynchronously when  an
 * IPI  is used. Because of this, there is no way to check if the inject
 * was actually successful, or might have failed due to `thread' exiting
 * before the inject could be made.
 *
 * This function is used by `task_rpc_schedule()' (s.a. <kos/rpc.md>)
 *
 * @param: rpc_flags: Set of `0 | RPC_PRIORITY_F_HIGH', or one of
 *                    `RPC_PRIORITY_NORMAL',  `RPC_PRIORITY_HIGH'
 *                    Other flags are silently ignored. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL userexcept_sysret_inject_safe)(struct task *__restrict thread,
                                             syscall_ulong_t rpc_flags);

/* Check if `_RPC_GETSIGNO(rpc_flags)' is currently masked by `thread' (thereby
 * also marking the associated bit  as pending within its userprocmask,  should
 * `thread' be using one). Only if  that signal vector isn't currently  masked,
 * proceed to do the same as also done by `userexcept_sysret_inject_safe()'.
 *
 * The  userprocmask is accessed purely via *_nopf functions (hence the NOBLOCK),
 * and if doing this  fails, act as  though the signal  vector isn't masked,  and
 * proceed with calling `userexcept_sysret_inject_nopr()', resulting in the given
 * `thread' eventually calling `userexcept_sysret()'  which will repeat the  test
 * masked signals (at which point _it_ is  able to use the non-*_nopf variant  of
 * the masking test function `sigmask_ismasked()')
 *
 * Additionally, this function will also set the `TASK_FRPC' just before making
 * the call to `userexcept_sysret_inject_nopr()' (though obviously only if such
 * a call actually ends up being made) */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL userexcept_sysret_inject_and_marksignal_safe)(struct task *__restrict thread,
                                                            syscall_ulong_t rpc_flags);


/* Invoke  `userexcept_sysret_inject_safe()'  for every  thread  apart of
 * `proc', as well as set the `TASK_FRPC' flag for each of those threads. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL userexcept_sysret_injectproc_safe)(struct taskpid *__restrict proc,
                                                 syscall_ulong_t rpc_flags);
/* Invoke `userexcept_sysret_inject_and_marksignal_safe()' for every thread apart of `proc' */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL userexcept_sysret_injectproc_and_marksignal_safe)(struct taskpid *__restrict proc,
                                                                syscall_ulong_t rpc_flags);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_RT_EXCEPT_HANDLER_H */
