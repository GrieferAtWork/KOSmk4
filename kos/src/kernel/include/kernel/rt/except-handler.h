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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_RT_EXCEPT_HANDLER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_RT_EXCEPT_HANDLER_H 1

/* Special kernel exception handlers (for system calls, posix signals, etc.) */

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/arch/except-handler.h>

#include <kos/bits/syscall-info.h>
#include <kos/rpc.h>

#ifdef CONFIG_USE_NEW_RPC
#ifdef __CC__
DECL_BEGIN

/* TODO: `userexcept_sysret_inject' replaces `task_enable_redirect_usercode_rpc' */
/* TODO: `userexcept_sysret_inject_safe' replaces `task_redirect_usercode_rpc' */

struct icpustate;
struct task;

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

/* Arch-specific function:
 * Translate the current exception into an errno and set that errno
 * as the return value of  the system call described by  `sc_info'. */
FUNDEF WUNUSED NONNULL((1, 2, 3)) struct icpustate *
NOTHROW(FCALL userexcept_seterrno)(struct icpustate *__restrict state,
                                   struct rpc_syscall_info const *__restrict sc_info,
                                   struct exception_data const *__restrict error);



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
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL userexcept_handler)(struct icpustate *__restrict state,
                                  struct rpc_syscall_info *sc_info);

/* Arch-specific function:
 * Wrapper around `userexcept_handler()' for use in implementing `error_unwind()'.
 * This  function will (safely) construct a complete `struct icpustate' at the far
 * end of the  calling thread's stack  and populate with  with register info  from
 * `state'. Afterwards, it  will force-unwind  the kernel  stack such  that it  is
 * located immediately at the new state. Once that is done, a call to the portable
 * function `userexcept_handler(<state>, sc_info)'  is made,  and that  function's
 * return value is passed to `cpu_apply_icpustate()' */
FUNDEF ATTR_NORETURN NONNULL((1)) void
NOTHROW(FCALL userexcept_handler_ucpustate)(struct ucpustate *__restrict state,
                                            struct rpc_syscall_info *sc_info);


/* This is the function that is injected by `userexcept_sysret_inject()',
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
 * space,  unless  this function  (or  `userexcept_sysret_inject()') was
 * called yet again.
 * NOTE: The  given `state' must point to user-space, and be located at
 *       the very end of the kernel stack. This requirement is asserted
 *       internally by this function! */
FUNDEF NOPREEMPT ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL userexcept_sysret_inject_with_state)(struct icpustate *__restrict state);


/* Arch-specific function:
 * Inject a call to `userexcept_sysret()' that is performed before `thread'
 * returns  back to user-space the next time. This function works correctly
 * even when `thread == THIS_TASK', or when the injection has already  been
 * performed (either by a  prior call to  this function, or  by use of  the
 * sibling function `userexcept_sysret_inject_with_state()'), in which case
 * the call is silent no-op.
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
FUNDEF NOPREEMPT WUNUSED NONNULL((1)) void
NOTHROW(FCALL userexcept_sysret_inject)(struct task *__restrict thread);



/* High-level wrapper for `userexcept_sysret_inject()' that makes all of
 * the right decisions to only ever call `userexcept_sysret_inject()' in
 * a valid context: using IPIs to make the call from the same CPU as the
 * one  currently hosting `thread', and ensuring that the thread has yet
 * to terminate.
 * Additionally, this function will make a call to `task_wake()'  once
 * the injection has completed, meaning that `thread' will wake up and
 * either immediatly  start executing  `userexcept_sysret()', or  will
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
FUNDEF WUNUSED NONNULL((1)) void
NOTHROW(FCALL userexcept_sysret_inject_safe)(struct task *__restrict thread,
                                             syscall_ulong_t rpc_flags);


DECL_END
#endif /* __CC__ */
#endif /* CONFIG_USE_NEW_RPC */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_RT_EXCEPT_HANDLER_H */
