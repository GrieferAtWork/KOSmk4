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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_RPC_H
#define GUARD_KERNEL_INCLUDE_SCHED_RPC_H 1

#include <kernel/compiler.h>

#include <kernel/malloc-defs.h>
#include <kernel/types.h>

DECL_BEGIN

/* RPCs are served under the following, different circumstantial conditions.
 * NOTE: The order in which RPCs are executed (irregardless of their type)
 *       is never guarantied and can be completely random.
 *
 *                                                       ASYNCHRONOUS
 *                                                        |
 *                                                        |  SYNCHRONOUS
 *                                                        |   |
 *                                                        |   |  USER_RPC
 *                                                        |   |   |
 *                                                        |   |   |  USER_RPC_INTERRUPT
 *                                                        |   |   |   |
 *                                                        |   |   |   |  USER_RPC_SYNC_INTERRUPT
 *                                                        |   |   |   |   |
 *                                                        |   |   |   |   |  USER_RPC_SYNC_INTERRUPT_NONSYS
 * Condition                                              |   |   |   |   |   |
 *  Anytime EFLAGS.IF is set (at a quantum start)        [X]  -   -   -   -   -   (TASK_RPC_REASON_ASYNC)
 *  Anytime the thread calls `task_serve()'               -  [X]  -  #1  #1  #1   (TASK_RPC_REASON_SYNC)
 *  Anytime the thread returns to user-space              -  [X] [X] [X] #4  #5   (TASK_RPC_REASON_SYSCALL) (#3)
 *  Anytime the thread is in user-space                  [X] [X] [X] [X]  -   -   (TASK_RPC_REASON_ASYNCUSER)
 *  During `task_exit()'                                  -  [X] [X] [X] [X] [X]  (TASK_RPC_REASON_SHUTDOWN)
 * Special behavior                                       |   |   |   |   |
 *  Consume `E_INTERRUPT_USER_RPC' upon user return (#2)  -   -   -  [X] [X]
 *
 * #1: A `E_INTERRUPT_USER_RPC' exception way be thrown synchronously when
 *     user-level RPCs exist with the `TASK_USER_RPC_FINTR' flag set, which
 *     is then caught just prior to returning from the system call.
 * #2: `E_INTERRUPT_USER_RPC' is consumed _before_ the first RPC is invoked, though only
 *     if there is at least one RPC with the `TASK_SYNC_RPC_FNOTHROW' flag set.
 *     If another exception is thrown after than, only remaining RPCs with
 *    `TASK_SYNC_RPC_FNOTHROW' will be able to execute.
 * #3: Where `TASK_RPC_REASON_SYSCALL' would normally apply, `TASK_RPC_REASON_ASYNCUSER' is used
 *     instead if kernel-space was entered for something other than a system call, or when the
 *     RPC was scheduled as non-interrupting.
 * #4: Only if task_serve() was invoked during execution of the system call beforehand,
 *     and only if it was a system call that can be used as a cancellation point.
 * #5: Only if task_serve() was invoked during execution of the system call beforehand.
 *
 * Possible service reasons:
 *    ASYNCHRONOUS                   ---  { TASK_RPC_REASON_ASYNC, TASK_RPC_REASON_ASYNCUSER }
 *    SYNCHRONOUS                    ---  { TASK_RPC_REASON_ASYNCUSER, TASK_RPC_REASON_SYNC, TASK_RPC_REASON_SYSCALL }
 *    USER_RPC                       ---  { TASK_RPC_REASON_ASYNCUSER, TASK_RPC_REASON_SYSCALL }
 *    USER_RPC_INTERRUPT             ---  { TASK_RPC_REASON_ASYNCUSER, TASK_RPC_REASON_SYSCALL }
 *    USER_RPC_SYNC_INTERRUPT        ---  { TASK_RPC_REASON_SYSCALL }
 *    USER_RPC_SYNC_INTERRUPT_NONSYS ---  { TASK_RPC_REASON_ASYNCUSER, TASK_RPC_REASON_SYSCALL }
 * Also: Any RPC may be executed using `TASK_RPC_REASON_SHUTDOWN' as reason
 */


/* Special return value for RPC functions invoked with `TASK_RPC_REASON_SYSCALL'
 * When returned, the current system call is restarted without execution ever
 * returning back to user-space. */
#define TASK_RPC_RESTART_SYSCALL  (__CCAST(struct icpustate *)(-2))

#ifdef __CC__
struct task;
struct icpustate;
struct sig;
struct rpc_syscall_info;

/* Prototype for RPC callbacks being executed in remote threads.
 * NOTE: When executing an RPC callback, the preemption enabled/disable
 *       state is _NOT_ changed prior to execution! As such, preemption
 *       may or may not be enabled when a callback is invoked.
 * WARNING: This function is required to always return normally, or by throwing
 *          an exception. - It is not allowed to return by any other means, or
 *          not return at all (don't call `task_exit()'. - throw E_EXIT_THREAD).
 * WARNING: When scheduled with the `TASK_SYNC_RPC_FNOTHROW' flag,
 *          this function _must_ never throw an exception.
 * @param: arg:     The argument scheduled alongside the callback.
 * @param: state:   The CPU state at the time the target thread was interrupted.
 * @param: reason:  The reason why the RPC is being served now (One of `TASK_RPC_REASON_*')
 * @param: sc_info: [1..1][valid_if(reason == TASK_RPC_REASON_SYSCALL)] System call information.
 * @return: * :     The CPU state to restore (usually just `state' again).
 * @return: TASK_RPC_RESTART_SYSCALL: [valid_if(reason == TASK_RPC_REASON_SYSCALL)]
 *                                    The interrupted system call should be restarted
 *                                    without ever returning back to user-space. */
typedef WUNUSED NONNULL((2)) struct icpustate *
(FCALL *task_rpc_t)(void *arg,
                    struct icpustate *__restrict state,
                    unsigned int reason,
                    struct rpc_syscall_info const *sc_info);

#endif /* __CC__ */

/* RPC reason codes. */
#define TASK_RPC_REASON_ASYNC        0x0000 /* The RPC is being served asynchronous, following either an IPI
                                             * being served by the target CPU, or the target thread having been
                                             * preempted before, and now finding its next quantum to have begun.
                                             * NOTE: This reason is never set when the RPC was scheduled asynchronously. */
#define TASK_RPC_REASON_ASYNCUSER    0x0001 /* Similar to `TASK_RPC_REASON_ASYNC', however this may still be a valid
                                             * reason for synchronous kernel-space RPCs, as the RPC is being served
                                             * while the thread (and conversely `state') points into user-space.
                                             * -> This is the type used for asynchronous POSIX-Signals in user-space.
                                             * NOTE: This type or reason may also be used when an RPC is served after
                                             *       returning from a non-syscall system interrupt returning to user-space. */
#define TASK_RPC_REASON_SYNC         0x0002 /* The RPC is being served because the thread was about to start blocking
                                             * as a result of calling `task_serve()', or was already in the process of
                                             * being blocked.
                                             * This is usually the most likely reason for a synchronous RPC being served,
                                             * as most threads spent their time waiting for some block lock, if not waiting
                                             * for user- or network input. */
#define TASK_RPC_REASON_SYSCALL      0x0003 /* This reason acts as a sort of hybrid between `TASK_RPC_REASON_ASYNCUSER'
                                             * and `TASK_RPC_REASON_SYNC', though only appearing when the RPC has been
                                             * scheduled for executing prior to the thread returning to user-space the next time.
                                             * This reason is only set if the target thread had previously been executing a
                                             * system call which may been interrupted if the RPC was scheduled as a USER_RPC_INTERRUPT
                                             * mode, in which case the RPC executed for this reason is expected to either
                                             * throw an exception to-be propagated to user-space, or to update `state' in
                                             * a reasonable way in order to either emulate, or restart expected user-space
                                             * behavior for the interrupted system call.
                                             * The passed CPU state here describes the state to which the the system call would
                                             * have returned, with all registered (except for the PC register) restored to the
                                             * values they had when the system call originally began, while unknown registers
                                             * are filled with stub values.
                                             * -> This is the type used by POSIX-Signals to interrupt system calls,
                                             *    where restartable system calls have their state altered to repeat the
                                             *    instruction used to generate the system call such that it will get
                                             *    invoked again when the signal handler returns.
                                             * WARNING: This reason can only be produced when RPC functions are being served
                                             *          after a system call was interrupted through use of USER_RPC_INTERRUPT.
                                             *          If RPC functions are being served before returning to user-space without
                                             *          the aid of an exception, the used reason will be `TASK_RPC_REASON_ASYNCUSER'
                                             *          instead. */
#define TASK_RPC_REASON_SHUTDOWN     0x0004 /* The RPC is being serviced because the hosting thread is currently exiting.
                                             * This reason is given in one of two cases:
                                             *  - To service any remaining synchronous RPC that is when `task_exit()' is called
                                             *  - To service an asynchronous RPC when the target thread has terminated, but wasn't
                                             *    yet terminated when `task_schedule_asynchronous_rpc()' already returned `true'
                                             *    WARNING: In this case, the RPC is executed by an arbitrary thread on the same
                                             *             CPU that the thread was scheduled on between the associated call to
                                             *             `task_schedule_asynchronous_rpc()', and the thread being terminated.
                                             *             Note that this is never the actual intended target thread!
                                             * Any exception thrown when this reason is given will simply be discarded,
                                             * though non-signaling exceptions will be logged using `printk(KERN_ERR)' */



/* General-purpose RPC flags. */
#define TASK_RPC_FNORMAL   0x0000 /* Normal RPC flags. */
#define TASK_RPC_FWAITFOR  0x1000 /* When sending an IPI to a different CPU, wait for that CPU to acknowledge
                                   * having received the IPI, rather than allowing the IPI to be delivered
                                   * asynchronously. */
#define TASK_RPC_FDONTWAKE 0x2000 /* Don't wake up the target thread using a sporadic wake-up. */
#define TASK_RPC_FHIGHPRIO 0x4000 /* The RPC has high priority. - When the target is hosted by the same
                                   * core as the caller, yield to the target thread when preemption was
                                   * enabled, before returning at the start of a new quantum. */
#define TASK_RPC_FLOWPRIO  0x8000 /* The RPC has low priority and doesn't require the target
                                   * to be re-schedule for being executed as soon as possible.
                                   * When not set, the target thread is scheduled to resume execution
                                   * at the start of the next quantum on the target CPU. */


/* Synchronous RPC flags. */
#define TASK_SYNC_RPC_FNORMAL  0x0000 /* Normal RPC flags. */
#define TASK_SYNC_RPC_FNOTHROW 0x0010 /* The RPC may be serviced by `task_serve_nx()'. */


/* User RPC flags. */
#define TASK_USER_RPC_FNORMAL     0x0000 /* Normal RPC flags. */
#define TASK_USER_RPC_FINTR       0x0002 /* Generate an interrupting RPC. */
#define TASK_USER_RPC_FSYNC       0x0004 /* Generate a `USER_RPC_SYNC_INTERRUPT' (must be used with `TASK_USER_RPC_FINTR').
                                          * -> The RPC is only handled when returning from a cancelation-point system call,
                                          *    after that system call had previously invoked `task_serve()' */
#define TASK_USER_RPC_FNONSYSCALL 0x0400 /* Generate a `USER_RPC_SYNC_INTERRUPT_NONSYS' (must be used with `TASK_USER_RPC_FINTR|TASK_USER_RPC_FSYNC').
                                          * -> For use with `TASK_USER_RPC_FSYNC': Also accept non-cancelation-point
                                          *    system calls, as well as interrupts caused by things other than system
                                          *    calls. */
#define TASK_USER_RPC_FNOTHROW    0x0010 /* The RPC may be serviced by `task_serve_nx()'. */


/* Asynchronous RPC flags. */
#define TASK_ASYNC_RPC_FNORMAL 0x0000 /* Normal RPC flags. */



#ifdef __CC__
/* Schedule a synchronous RPC to be serviced by `target'
 * NOTE: When `target' is the calling thread, these functions
 *       will throw an `E_INTERRUPT_USER_RPC' exception when
 *       the `TASK_USER_RPC_FINTR' flag is set.
 * @param: mode:   Set of `TASK_RPC_F* | TASK_USER_RPC_F*'
 * @return: true:  The RPC has been scheduled.
 * @return: false: The RPC could not be scheduled, because
 *                `target' has terminated, or is terminating.
 * @return: false: The target thread has the `TASK_FKERNTHREAD' flag
 *                 set, meaning it can never return to user-space,
 *                 since it only exists in kernel-space. */
FUNDEF NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) NONNULL((1, 2)) bool KCALL
task_schedule_user_rpc(struct task *__restrict target,
                       task_rpc_t func,
                       void *arg DFL(__NULLPTR),
                       uintptr_t mode DFL(TASK_RPC_FNORMAL|TASK_USER_RPC_FNORMAL),
                       gfp_t rpc_gfp DFL(GFP_NORMAL))
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_INTERRUPT_USER_RPC);

/* No-except variants of the above functions.
 * @return: * : One of `TASK_SCHEDULE_USER_RPC_*' */
FUNDEF NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) NONNULL((1, 2)) int
NOTHROW(KCALL task_schedule_user_rpc_nx)(struct task *__restrict target,
                                         task_rpc_t func,
                                         void *arg DFL(__NULLPTR),
                                         uintptr_t mode DFL(TASK_RPC_FNORMAL | TASK_USER_RPC_FNORMAL),
                                         gfp_t rpc_gfp DFL(GFP_NORMAL));
#define TASK_SCHEDULE_USER_RPC_INTERRUPTED 1    /* The calling thread is the same as the target, and `TASK_USER_RPC_FINTR' was set
                                                 * NOTE: This return value still indicates success! */
#define TASK_SCHEDULE_USER_RPC_SUCCESS     0    /* The RPC was successfully delivered. */
#define TASK_SCHEDULE_USER_RPC_TERMINATED  (-1) /* The target thread has already terminated. */
#define TASK_SCHEDULE_USER_RPC_KERNTHREAD  (-2) /* The target thread is a kernel thread that never reaches user-space. */
#define TASK_SCHEDULE_USER_RPC_BADALLOC    (-3) /* `kmalloc_nx(..., rpc_gfp)' returned `NULL'. */
#define TASK_SCHEDULE_USER_RPC_WASOK(x)    ((x) >= 0) /* When `false', `arg' wasn't inherited */
#endif /* __CC__ */


#ifdef __CC__
/* Schedule a synchronous RPC to be serviced by `target'
 * NOTE: When `target' is the calling thread, the RPC will
 *       still be serviced the next time `task_serve()' is
 *       called, or in case `task_exit()' is called before
 *       then, it will be serviced at that point.
 * @param: mode:   Set of `TASK_RPC_F* | TASK_SYNC_RPC_F*'
 * @return: true:  The RPC has been scheduled.
 * @return: false: The RPC could not be scheduled, because
 *                `target' has terminated, or is terminating. */
FUNDEF NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) NONNULL((1, 2)) bool KCALL
task_schedule_synchronous_rpc(struct task *__restrict target,
                              task_rpc_t func,
                              void *arg DFL(__NULLPTR),
                              uintptr_t mode DFL(TASK_RPC_FNORMAL | TASK_SYNC_RPC_FNORMAL),
                              gfp_t rpc_gfp DFL(GFP_NORMAL))
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* No-except variants of the above functions.
 * @return: * : One of `TASK_SCHEDULE_SYNCHRONOUS_RPC_*' */
FUNDEF NOBLOCK_IF(rpc_gfp & GFP_ATOMIC) NONNULL((1, 2)) int
NOTHROW(KCALL task_schedule_synchronous_rpc_nx)(struct task *__restrict target,
                                                task_rpc_t func,
                                                void *arg DFL(__NULLPTR),
                                                uintptr_t mode DFL(TASK_RPC_FNORMAL | TASK_SYNC_RPC_FNORMAL),
                                                gfp_t rpc_gfp DFL(GFP_NORMAL));
#define TASK_SCHEDULE_SYNCHRONOUS_RPC_SUCCESS     0    /* The RPC was successfully delivered. */
#define TASK_SCHEDULE_SYNCHRONOUS_RPC_TERMINATED  (-1) /* The target thread has already terminated. */
#define TASK_SCHEDULE_SYNCHRONOUS_RPC_BADALLOC    (-2) /* `kmalloc_nx(..., rpc_gfp)' returned `NULL'. */
#endif /* __CC__ */




#ifdef __CC__
/* Schedule an asynchronous RPC to be serviced by `target'
 * WARNING: When `target' is the calling thread, `func' will be executed
 *          before this function returns, regardless of preemption having
 *          been enabled at the time of the call being made!
 * @param: mode:   Set of `TASK_RPC_F* | TASK_ASYNC_RPC_F*'
 * @return: true:  The RPC has been scheduled.
 *                 If the task is running on a different core and terminates in the mean
 *                 time, `func' will be invoked from a different thread on some CPU which
 *                 `target' used to run under at one point, using `TASK_RPC_REASON_SHUTDOWN'
 *                 If this happening isn't an option, use `task_exec_asynchronous_rpc()' instead.
 * @return: false: The RPC could not be scheduled, because `target' has terminated. */
FUNDEF NOBLOCK NONNULL((1, 2)) bool
NOTHROW(KCALL task_schedule_asynchronous_rpc)(struct task *__restrict target,
                                              task_rpc_t func,
                                              void *arg DFL(__NULLPTR),
                                              uintptr_t mode DFL(TASK_RPC_FNORMAL | TASK_ASYNC_RPC_FNORMAL));
#endif /* __CC__ */


#ifdef __CC__
/* Similar to `task_schedule_asynchronous_rpc()', but in case the target thread is hosted by
 * a different core, wait for confirmation that the RPC has been properly scheduled by that
 * core, ensuring that the target thread terminating before then results in `false' being returned.
 * When waiting, call `task_tryyield()' repeatedly, meaning that scheduling can only change threads
 * if preemption hasn't been disabled by the caller.
 * @param: mode:   Set of `TASK_RPC_F* | TASK_ASYNC_RPC_F*'
 * @return: true:  The RPC has been scheduled and is guarantied to be executed.
 * @return: false: The RPC could not be scheduled because `target' has terminated. */
FUNDEF NOBLOCK_IF(!PREEMPTION_ENABLED()) NONNULL((1, 2)) bool
NOTHROW(KCALL task_exec_asynchronous_rpc)(struct task *__restrict target,
                                          task_rpc_t func,
                                          void *arg DFL(__NULLPTR),
                                          uintptr_t mode DFL(TASK_RPC_FNORMAL | TASK_ASYNC_RPC_FNORMAL));

/* Same as `task_exec_asynchronous_rpc()', but pass a variable
 * amount of argument data to `func' when executed in `target',
 * such that `func:arg' will point to a `bufsize' byte long copy
 * of memory containing the same data as `buf'.
 * Note however that modifications done to `buf' by `func'
 * may not be visible in the provided buffer.
 * @param: mode:   Set of `TASK_RPC_F* | TASK_ASYNC_RPC_F*' */
FUNDEF NOBLOCK_IF(!PREEMPTION_ENABLED()) NONNULL((1, 2)) bool
NOTHROW(KCALL task_exec_asynchronous_rpc_v)(struct task *__restrict target,
                                            task_rpc_t func,
                                            void const *buf DFL(__NULLPTR),
                                            size_t bufsize DFL(0),
                                            uintptr_t mode DFL(TASK_RPC_FNORMAL | TASK_ASYNC_RPC_FNORMAL));


/* Execute a given RPC function using the caller's source
 * location, and `TASK_RPC_REASON_ASYNC' as reason for execution.
 * Then, load the `icpustate' returned by `func' and continue
 * execution there (when `func' doesn't modify `state' and
 * re-returns it, this function then returns normally) */
FUNDEF NOBLOCK NONNULL((1)) void FCALL
task_rpc_exec_here(task_rpc_t func, void *arg DFL(__NULLPTR));

/* Similar to `task_rpc_exec_here()', but don't restore modifications made
 * to the register state, or the register state return by `func'. - Simply
 * return normally, or by throwing an exception.
 * The reason that will be given to `func' is `TASK_RPC_REASON_SHUTDOWN' */
FUNDEF NOBLOCK NONNULL((1)) void FCALL
task_rpc_exec_here_onexit(task_rpc_t func, void *arg DFL(__NULLPTR));

/* Modify `state' to insert an asynchronous call to the given RPC function.
 * When that function then returns, the old state will restored.
 * The reason passed to `func' is either `TASK_RPC_REASON_ASYNCUSER' if the
 * old state points into user-space, or `TASK_RPC_REASON_ASYNC' if not. */
FUNDEF NOBLOCK ATTR_RETNONNULL NONNULL((1, 2)) struct scpustate *
NOTHROW(FCALL task_push_asynchronous_rpc)(struct scpustate *__restrict state,
                                          task_rpc_t func,
                                          void *arg DFL(__NULLPTR));

/* Same as `task_push_asynchronous_rpc()', but pass a copy
 * of the given buffer as value for `arg' to the given `func'. */
FUNDEF NOBLOCK ATTR_RETNONNULL NONNULL((1, 2)) struct scpustate *
NOTHROW(FCALL task_push_asynchronous_rpc_v)(struct scpustate *__restrict state,
                                            task_rpc_t func,
                                            void const *buf DFL(__NULLPTR),
                                            size_t bufsize DFL(0));

/* An arch-specific function used to re-direct the given task's user-space
 * return target to instead point back towards a kernel-space function which is then
 * able to service RPC functions scheduled using `task_(schedule|exec)_user_[s]rpc()'
 * On x86, this is done by modifying the IRET tail at the top of the target thread's stack:
 *   >> FORTASK(self,this_x86_rpc_redirection_iret).ir_eip    = GET_USERCODE_IRET(self)->ir_eip;
 *   >> FORTASK(self,this_x86_rpc_redirection_iret).ir_cs     = GET_USERCODE_IRET(self)->ir_cs;
 *   >> FORTASK(self,this_x86_rpc_redirection_iret).ir_eflags = GET_USERCODE_IRET(self)->ir_eflags;
 *   >> GET_USERCODE_IRET(self)->ir_eip                  = &x86_rpc_user_redirection;
 *   >> GET_USERCODE_IRET(self)->ir_cs                   = SEGMENT_KERNEL_CODE;
 *   >> GET_USERCODE_IRET(self)->ir_eflags               = 0;
 * NOTE: The caller must ensure that preemption is disabled,
 *       and that `self' is hosted by the calling CPU.
 *       Additionally, the caller must ensure that `self' has
 *       neither terminated, nor is actually set up to be a
 *       kernel-space thread.
 * @return: true:  Successfully redirected the given thread.
 * @return: false: The given thread has already been redirected. */
FUNDEF NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL task_enable_redirect_usercode_rpc)(struct task *__restrict self);

/* High-level variant of `task_enable_redirect_usercode_rpc':
 * This function automatically performs all of the necessary locking, checks and IPIs
 * in order to execute `task_enable_redirect_usercode_rpc()' for `target' within the
 * proper context.
 * @return: true:  Successfully redirected the given thread (though it may have already been redirected before).
 * @return: false: The RPC could not be scheduled because `target' has terminated.
 *        WARNING: The target may still terminate before the RPC can be servied,
 *                 though this has to be detected in some different manner. */
FUNDEF NOBLOCK NONNULL((1)) bool
NOTHROW(KCALL task_redirect_usercode_rpc)(struct task *__restrict target, uintptr_t mode);



/* Serve pending, synchronous (and asynchronous) RPCs.
 * NOTE: If the caller was previously disabled preemption, it will remain
 *       disabled if there were no RPC functions had to be executed.
 *       Otherwise, preemption will become enabled, and `true' is returned,
 *       or an exception thrown by an RPC function gets propagated.
 * WARNING: Do not call this function unconditionally!
 *          Only call it if you're certain to be about to start blocking
 *          in a context where a reset of your current context would have
 *          the potential to resolve the block. (Reset here meaning the
 *          current system call being restarted)
 * @return: true:  At least one RPC function was executed, and
 *                 preemption was re-enabled if it was disabled before.
 * @return: false: No RPC needed to be served, and preemption
 *                 remains disabled if it was disabled before. */
FUNDEF bool KCALL task_serve(void) THROWS(...);

/* Same as `task_serve()', but only sevice RPCs that were scheduled as no-throw.
 * @return: * : Set of `TASK_SERVE_*' */
FUNDEF WUNUSED unsigned int NOTHROW(KCALL task_serve_nx)(void);
#endif /* __CC__ */
#define TASK_SERVE_NX_NOOP     0 /* Nothing was executed, or needed to be. */
#define TASK_SERVE_NX_XPENDING 1 /* FLAG: Pending RPC functions that can only be serviced by `task_serve()' still remain. */
#define TASK_SERVE_NX_DIDRUN   2 /* FLAG: NX RPC functions were executed. */


#ifdef __CC__

/* Prototype for a cleanup helper functions which is allowed to block.
 * This type of function may be used to deal with cleanup operations that
 * way require blocking, and serviced whenever either `task_serve()' or
 * `task_serve_nx()' are called.
 * @param: pfun: A self-pointer to the function being called.
 * @return: * :  A self-pointer to the next function, or `NULL' when finished.
 * @return: BLOCKING_CLEANUP_RETURN_XPENDING:
 *               The caller must service X-RPCs before the cleanup function can succeed.
 *               NOTE: May only be returned when `action' it set to `BLOCKING_CLEANUP_ACTION_SERVICE'
 * Used as follows:
 * >> struct mydata {
 * >>     void *a;
 * >>     void *b;
 * >>     void *c;
 * >> };
 * >> // Must re-use 2 pointers in the structure to-be cleaned up
 * >> // in order to form a singly-linked list of cleanup operations.
 * >> #define MYDATA_FUN_FIELD   a
 * >> #define MYDATA_NXT_FIELD   b
 * >> PRIVATE void *NOTHROW(FCALL blocking_mydata_destroy)(void *pfun, unsigned int action) {
 * >>     void *result;
 * >>     struct mydata *self;
 * >>     self = COMPILER_CONTAINER_OF((void **)pfun,struct mydata,MYDATA_FUN_FIELD);
 * >>     if (action == BLOCKING_CLEANUP_ACTION_GETNEXT)
 * >>         return &self->MYDATA_NXT_FIELD;
 * >>     do_blocking_destory(self); // Something that may block, but is nothrow and eventually frees `self'
 * >>     return result;
 * >> }
 * >> PRIVATE NOBLOCK void
 * >> NOTHROW(FCALL mydata_destroy)(struct mydata *__restrict self) {
 * >>     // Set the function to-be called during cleanup.
 * >>     self->MYDATA_FUN_FIELD = (void *)&blocking_mydata_destroy;
 * >>     // Schedule the function for execution.
 * >>     BLOCKING_CLEANUP_SCHEDULE(self,MYDATA_FUN_FIELD,MYDATA_NXT_FIELD);
 * >> } */
typedef void * /*NOTHROW*/ (FCALL *blocking_cleanup_t)(void *pfun, unsigned int action);
#define BLOCKING_CLEANUP_ACTION_SERVICE 0x0000 /* Service the operation. */
#define BLOCKING_CLEANUP_ACTION_GETNEXT 0x0001 /* Return a pointer to the next-function-field. */

/* The cleanup operation cannot be performed because there are
 * pending X-RPC functions scheduled for the calling thread. */
#define BLOCKING_CLEANUP_RETURN_XPENDING ((void *)-1)

/* Chain of blocking cleanup functions (serviced every
 * time `task_serve()' or `task_serve_nx()' is called)
 * Additionally, functions from this chain will also be
 * serviced by the IDLE thread, the same way any other
 * IDLE job would be. */
DATDEF WEAK void *blocking_cleanup_chain;

/* Service blocking cleanup operations.
 * @return: * : One of `BLOCKING_CLEANUP_SERVICE_*' */
FUNDEF unsigned int NOTHROW(FCALL blocking_cleanup_service)(void);
#endif /* __CC__ */
#define BLOCKING_CLEANUP_SERVICE_NONE 0 /* No blocking cleanup operations were serviced. */
#define BLOCKING_CLEANUP_SERVICE_XRPC 1 /* In order to service remaining blocking cleanup operations, the
                                         * caller must first call `task_serve()' in order to service pending
                                         * X-RPC functions. */
#define BLOCKING_CLEANUP_SERVICE_DONE 2 /* All outstanding, blocking cleanup operations were serviced. */

#ifdef __CC__
/* Try to find some thread that can be used to service blocking cleanup
 * operations, potentially waking it up so it will service them.
 * If no such thread can be found, return without doing anything.
 * -> This function is merely used to prevent blocking cleanup
 *    operations from blocking indefinitely, by explicitly going
 *    out of our way to get some other thread to do the dirty work
 *    for us. */
FUNDEF NOBLOCK void NOTHROW(FCALL blocking_cleanup_prioritize)(void);

/* Helper macro to schedule a blocking cleanup operation. */
#define BLOCKING_CLEANUP_SCHEDULE(data, fun_field, nxt_field)                                                          \
	do {                                                                                                               \
		void *_bcs_next;                                                                                               \
		do                                                                                                             \
			*(void **)&(data)->nxt_field = _bcs_next = __hybrid_atomic_load(blocking_cleanup_chain, __ATOMIC_ACQUIRE); \
		while (!__hybrid_atomic_cmpxch_weak(blocking_cleanup_chain, _bcs_next, *(void **)&(data)->fun_field,           \
		                                    __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));                                      \
		blocking_cleanup_prioritize();                                                                                 \
	} __WHILE0
#define BLOCKING_CLEANUP_SCHEDULE_P(data, fun_path, nxt_path)                                                       \
	do {                                                                                                            \
		void *_bcs_next;                                                                                            \
		do                                                                                                          \
			*(void **)&nxt_path(data) = _bcs_next = __hybrid_atomic_load(blocking_cleanup_chain, __ATOMIC_ACQUIRE); \
		while (!__hybrid_atomic_cmpxch_weak(blocking_cleanup_chain, _bcs_next, *(void **)&fun_path(data),           \
		                                    __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST));                                   \
		blocking_cleanup_prioritize();                                                                              \
	} __WHILE0

#endif /* __CC__ */



DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_RPC_H */
