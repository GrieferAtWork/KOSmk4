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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_RPC_H
#define GUARD_KERNEL_INCLUDE_SCHED_RPC_H 1

#include <kernel/compiler.h>

#include <kernel/malloc-defs.h>
#include <kernel/types.h>

#include <bits/os/sigset.h>
#include <kos/rpc.h>

#ifdef __CC__
DECL_BEGIN

#ifndef __sigset_t_defined
#define __sigset_t_defined
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */


/* High-level RPC scheduling function.
 * This is the kernel-equivalent of the userspace `rpc_exec()' from <kos/rpc.h>
 *
 * @param: flags: Set of RPC flags (MUST contain `RPC_CONTEXT_KERN'):
 *   - RPC_CONTEXT_KERN:           Mandatory flag
 *   - RPC_CONTEXT_NOEXCEPT:       The given `func' never throws and may be served by `task_serve_nx()'
 *   - RPC_SYNCMODE_F_ALLOW_ASYNC: Schedule  as an asynchronous RPC (be _very_ careful about these, as
 *                                 the given `func' must act like an interrupt handler and be NOBLOCK)
 *   - RPC_SYNCMODE_F_USER:        Only  allowed  when  `!(thread->t_flags & TASK_FKERNTHREAD)':   Force
 *                                 unwind the current system call the next time `thread' makes a call to
 *                                 `task_serve()'  (if the thread is currently sleeping, it will be send
 *                                 a sporadic interrupt which should cause it to call that function once
 *                                 again). Once unwinding all to  way to userspace has finished,  invoke
 *                                 `func' in the context to which  the syscall returns. Note that  here,
 *                                 `func'  is allowed  to transition  the `ctx->rc_context'  it is given
 *                                 from `RPC_REASONCTX_SYSCALL' to `RPC_REASONCTX_SYSRET', in which case
 *                                 the system call/interrupt will not be restarted.
 *   - RPC_SYNCMODE_F_SYSRET:      May only be used when  combined with `RPC_SYNCMODE_F_USER', in  which
 *                                 case the RPC will only be invoked the next time that `thread' returns
 *                                 to user-space (or immediately if `thread' is currently in user-space)
 *                                 Note though that an in-progress, blocking system call isn't  aborted.
 *   - RPC_PRIORITY_F_HIGH:        When  `thread' is hosted by the same CPU as the caller, gift the rest
 *                                 of the calling thread's current quantum to `thread' and have it start
 *                                 executing even before this function returns.
 * @return: true:  Success
 * @return: false: Failure because `thread' has already terminated. */
FUNDEF NONNULL((1, 3)) __BOOL KCALL
task_rpc_exec(struct task *__restrict thread, syscall_ulong_t flags,
              prpc_exec_callback_t func, void *cookie DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Helper wrapper for executing the given RPC `func' after
 * unwind the current system  call. This is identical  to:
 * >> task_rpc_exec(THIS_TASK, RPC_CONTEXT_KERN | RPC_SYNCMODE_F_USER, func, cookie);
 * >> THROW(E_INTERRUPT_USER_RPC); */
FUNDEF ATTR_NORETURN NONNULL((1)) void KCALL
task_rpc_userunwind(prpc_exec_callback_t func, void *cookie DFL(__NULLPTR))
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_INTERRUPT_USER_RPC);



/* Arch-specific function:
 * Serve pending, synchronous (and asynchronous) RPCs.
 * NOTE: If the caller was previously  disabled preemption, it will  remain
 *       disabled  if  there  were no  RPC  functions had  to  be executed.
 *       Otherwise, preemption will become enabled, and `true' is returned,
 *       or an exception thrown by an RPC function gets propagated.
 * WARNING: Do not call this function unconditionally!
 *          Only call it if you're certain to be about to start  blocking
 *          in a context where a reset of your current context would have
 *          the potential to resolve the  block. (Reset here meaning  the
 *          current system call being restarted)
 * @return: true:  RPC  functions  may  have  been  been  executed, and
 *                 preemption was re-enabled if it was disabled before.
 * @return: false: No  RPC needed to be served, and preemption
 *                 remains disabled if it was disabled before. */
FUNDEF BLOCKING __BOOL (FCALL task_serve)(void) THROWS(E_INTERRUPT_USER_RPC, ...);

/* Literally the same as `task_serve()',  but doesn't include the  inline
 * optimization that tests for `TASK_FRPC' before calling `task_serve()'.
 * Call this one if you're fairly certain that RPCs are really pending. */
FUNDEF BLOCKING __BOOL (FCALL _task_serve)(void) THROWS(E_INTERRUPT_USER_RPC, ...) ASMNAME("task_serve");

/* Arch-specific function:
 * Same as `task_serve()', but only sevice RPCs that were scheduled as no-throw.
 * @return: * : Set of `TASK_SERVE_*' */
FUNDEF BLOCKING WUNUSED unsigned int NOTHROW(FCALL task_serve_nx)(void);

/* Same as `task_serve()', but use the given `sigmask'
 * instead of the  calling thread's thread-local  one.
 * Used for the implementation of `sigsuspend(2)' */
FUNDEF BLOCKING NONNULL((1)) __BOOL FCALL
task_serve_with_sigmask(sigset_t const *__restrict sigmask)
		THROWS(E_INTERRUPT_USER_RPC, ...);


/* Automatically updates `state' to include the intended return value for `task_serve()'! */
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL
task_serve_with_icpustate(struct icpustate *__restrict state)
		THROWS(E_INTERRUPT_USER_RPC, ...);
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
task_serve_with_icpustate_and_sigmask(struct icpustate *__restrict state,
                                      sigset_t const *__restrict sigmask)
		THROWS(E_INTERRUPT_USER_RPC, ...);
FUNDEF BLOCKING ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL task_serve_with_icpustate_nx)(struct icpustate *__restrict state);

#if !defined(__OPTIMIZE_SIZE__) && !defined(__INTELLISENSE__)
DECL_END
#include <sched/task.h>
#include <sched/pertask.h>
DECL_BEGIN
/* Inline optimizations for task service calls: when `TASK_FRPC' isn't set, serve calls are no-ops. */
#define task_serve()    (PERTASK_TESTMASK(((struct task *)0)->t_flags, TASK_FRPC) && (task_serve)())
#define task_serve_nx() (PERTASK_TESTMASK(((struct task *)0)->t_flags, TASK_FRPC) ? (task_serve_nx)() : TASK_SERVE_NX_NORMAL)
#endif /* !__OPTIMIZE_SIZE__ && !__INTELLISENSE__ */

DECL_END
#endif /* __CC__ */

/* Return values for `task_serve_nx()' */
#define TASK_SERVE_NX_NORMAL 0x00 /* Nothing was executed, or needed to be. */
#define TASK_SERVE_NX_EXCEPT 0x01 /* FLAG: Pending RPC functions that can only be serviced by `task_serve()' still remain. */
#define TASK_SERVE_NX_DIDRUN 0x02 /* FLAG: NX RPC functions may have been executed (but preemption was definitely re-enabled). */

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_RPC_H */
