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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_TASK_H
#define GUARD_KERNEL_INCLUDE_SCHED_TASK_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/arch/task.h>
#include <sched/pertask.h>

#include <hybrid/sequence/list.h>
#include <hybrid/typecore.h>

#ifdef __cplusplus
#include <asm/os/wait.h>  /* `__W_EXITCODE()' */
#include <bits/os/wait.h> /* `union wait' */
#endif /* __cplusplus */

#ifdef CONFIG_NO_KERNEL_STACK_GUARD
#undef CONFIG_HAVE_KERNEL_STACK_GUARD
#elif !defined(CONFIG_HAVE_KERNEL_STACK_GUARD)
#if !defined(NDEBUG) && 1
#define CONFIG_HAVE_KERNEL_STACK_GUARD 1
#endif /* !NDEBUG */
#endif /* !CONFIG_HAVE_KERNEL_STACK_GUARD */


DECL_BEGIN

/* Task state flags. */
#define TASK_FNORMAL       __UINT32_C(0x00000000) /* Normal task flags. */
#define TASK_FRUNNING      __UINT32_C(0x00000001) /* [lock(PRIVATE(THIS_CPU))] The task is currently running (`s_running' is valid). */
#define TASK_FTIMEOUT      __UINT32_C(0x00000002) /* [lock(CLEAR(THIS_TASK))] Set by the scheduler when waking a task due to a timeout. */
/*      TASK_F             __UINT32_C(0x00000004)  * ... */
/*      TASK_F             __UINT32_C(0x00000008)  * ... */
#define TASK_FSTARTING     __UINT32_C(0x00000010) /* [lock(WRITE_ONCE)] The thread is currently starting. */
#define TASK_FSTARTED      __UINT32_C(0x00000020) /* [lock(WRITE_ONCE)] The thread has been started. */
#define TASK_FTERMINATING  __UINT32_C(0x00000040) /* [lock(WRITE_ONCE)] The task has started the process of being terminated.
                                                   *                  - No further synchronous RPCs may be scheduled for execution
                                                   *                  - Implies `TASK_FKEEPCORE' (the task may no longer change its hosting CPU) */
#define TASK_FTERMINATED   __UINT32_C(0x00000080) /* [lock(WRITE_ONCE)] The task has been fully terminated.
                                                   *                  - No further RPCs of any kind may be scheduled for execution
                                                   *                  - The thread must no longer appear in the scheduler of any CPU. */
#define TASK_FKEEPCORE     __UINT32_C(0x00000100) /* [lock(PRIVATE(THIS_TASK))] Don't allow this task's core to change randomly. */
#define TASK_FSUSPENDED    __UINT32_C(0x00000200) /* [lock(PRIVATE(THIS_TASK))] Used internally to implement of SIGSTOP/SIGCONT */
/*      TASK_F             __UINT32_C(0x00000400)  * ... */
/*      TASK_F             __UINT32_C(0x00000800)  * ... */
/*      TASK_F             __UINT32_C(0x00001000)  * ... */
/*      TASK_F             __UINT32_C(0x00002000)  * ... */
/*      TASK_F             __UINT32_C(0x00004000)  * ... */
/*      TASK_F             __UINT32_C(0x00008000)  * ... */
#define TASK_FVFORK        __UINT32_C(0x00010000) /* [lock(CLEAR_ONCE(THIS_TASK))] This is a child-after-vfork() thread.
                                                   * When set, this causes exec() to create a new VM, rather than clear
                                                   * an existing one, alongside both exec() and task_exit() causing the
                                                   * thread to broadcast `THIS_TASKPID->tp_changed' after clearing this
                                                   * flag following a successful exec(), or a call to task_exit() */
#define TASK_FUSERPROCMASK __UINT32_C(0x00020000) /* [lock(READ(ATOMIC), WRITE(THIS_TASK))] Task has a `userprocmask'. (s.a. `this_userprocmask_address') */
#define TASK_FUSERPROCMASK_AFTER_VFORK \
                           __UINT32_C(0x00040000) /* [lock(PRIVATE(THIS_TASK))] `TASK_FUSERPROCMASK' was set after `TASK_FVFORK'. (s.a. `this_userprocmask_address') */
/*      TASK_F             __UINT32_C(0x00080000)  * ... */
/*      TASK_F             __UINT32_C(0x00100000)  * ... */
/*      TASK_F             __UINT32_C(0x00200000)  * ... */
/*      TASK_F             __UINT32_C(0x00400000)  * ... */
/*      TASK_F             __UINT32_C(0x00800000)  * ... */
#define TASK_FGDB_STOPPED  __UINT32_C(0x01000000) /* Used internally by the gdbserver driver */
/*      TASK_F             __UINT32_C(0x02000000)  * ... */
/*      TASK_F             __UINT32_C(0x04000000)  * ... */
#define TASK_FCRITICAL     __UINT32_C(0x08000000) /* [lock(PRIVATE(THIS_TASK))] The thread is critical, and any attempting to task_exit() it causes kernel panic. */
/*      TASK_F             __UINT32_C(0x10000000)  * ... */
/*      TASK_F             __UINT32_C(0x20000000)  * ... */
/*      TASK_F             __UINT32_C(0x40000000)  * ... */
#define TASK_FKERNTHREAD   __UINT32_C(0x80000000) /* [const] The thread is running exclusively in kernel-space, and can never return to user-space. */


#ifdef __CC__

struct cpu;
struct vm;
struct scpustate;
struct task {
	struct task            *t_self;      /* [1..1][const][== this] Self-pointer (always at offset == 0) */
	WEAK refcnt_t           t_refcnt;    /* Task reference counter. */
	WEAK uintptr_t          t_flags;     /* Thread state & flags (Set of `TASK_F*'). */
	struct cpu             *t_cpu;       /* [1..1][lock(PRIVATE)] The CPU that this task is being hosted by.
	                                      * NOTE: Also accessible via the `this_cpu' field. */
	REF struct vm          *t_vm;        /* [1..1][lock(read(THIS_TASK || INTERN(lock)),
	                                      *             write(THIS_TASK && INTERN(lock)))]
	                                      * The VM used to host this task.
	                                      * NOTE: Also accessible via the `this_vm' field. */
	LLIST_NODE(struct task) t_vm_tasks;  /* [lock(t_vm->v_tasklock)] Chain of tasks using `t_vm' */
	size_t                  t_heapsz;    /* [const] Allocated heap size of this task. */
	union {
		struct task        *_t_next;     /* [0..1][lock(INTERNAL)] Next dead VM within the same VM. */
		struct scpustate   *t_state;     /* [lock(PRIVATE(t_cpu == THIS_CPU))]
		                                  * [valid_if(t_self != FORCPU(t_cpu, thiscpu_sched_current))]
		                                  * The CPU state to-be restored when execution of this task continues. */
	};
#define KEY_task_vm_dead__next_offsetafter __COMPILER_OFFSETAFTER(struct task, _t_next)
#define KEY_task_vm_dead__next(thread)     (thread)->_t_next
	/* ATTR_PERTASK-data goes here. */
};

DATDEF ATTR_PERTASK struct scpustate *this_sstate; /* ALIAS:THIS_TASK->t_state */


/* Allocate + initialize a new task.
 * TODO: Re-design this function so we don't leak uninitialized tasks through the VM
 * @param: task_vm: The vm inside of which the start will start initially. */
FUNDEF ATTR_MALLOC WUNUSED ATTR_RETNONNULL REF struct task *KCALL
task_alloc(struct vm *__restrict task_vm)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL task_destroy)(struct task *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct task, t_refcnt, task_destroy)


/* Generic prototype for the main-function of a kernel thread. */
typedef void (KCALL *thread_main_t)();

/* Setup `thread' to become a kernel-space thread
 * calling `thread_main' with the provided arguments.
 * TODO: Re-design this function so we don't leak uninitialized tasks through the VM
 * >> void KCALL kernel_main(char *a, char *b) {
 * >>      ....
 * >> }
 * >>
 * >> struct task *thread = task_alloc(&vm_kernel);
 * >> task_setup_kernel(thread, (thread_main_t)&kernel_main, "foo", "bar", NULL);
 * >> task_start(thread, TASK_START_FNORMAL);
 * >> decref(thread);
 * `thread_main' returning will automatically call `task_exit()' */
FUNDEF NOBLOCK ATTR_RETNONNULL NONNULL((1, 2)) struct task *
NOTHROW(VCALL task_setup_kernel)(struct task *__restrict thread,
                                 thread_main_t thread_main,
                                 size_t argc DFL(0), ...);
#endif /* __CC__ */


#define TASK_START_FNORMAL   0x0000 /* Normal task startup flags. */
#define TASK_START_FHIGHPRIO 0x0001 /* Attempt to start the task with high priority, essentially
                                     * meaning that when preemption was enabled when `task_start()'
                                     * was called, and `thread' is scheduled for execution on the
                                     * same CPU as the calling thread, then `thread' will receive
                                     * its first quantum before `task_start()' returns. */
#ifdef __CC__
/* Start executing the given task on the CPU it has been assigned.
 * HINT: By default, `task_alloc()' will assign new tasks to the boot CPU.
 * @return: * : Always re-returns `thread' */
FUNDEF NOBLOCK ATTR_RETNONNULL NONNULL((1)) struct task *
NOTHROW(FCALL task_start)(struct task *__restrict thread, unsigned int flags);

/* Default flags used for `task_start()'
 * These can be controlled by /proc:
 *  - TASK_START_FHIGHPRIO == /proc/sys/kernel/sched_child_runs_first */
DATDEF unsigned int task_start_default_flags;

#ifdef __cplusplus
extern "C++" {
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL ATTR_RETNONNULL NONNULL((1)) struct task *
NOTHROW(FCALL task_start)(struct task *__restrict thread) {
	return task_start(thread, task_start_default_flags);
}
} /* extern "C++" */
#endif /* __cplusplus */


#ifndef __this_task_defined
#define __this_task_defined 1
DATDEF ATTR_PERTASK struct task this_task; /* The current task (for use with `PERTASK') */
#endif /* !__this_task_defined */

DATDEF struct task _boottask; /* The boot task (aka. `/proc/1'; aka. `/bin/init') */
DATDEF struct task _bootidle; /* The idle thread for the boot CPU */

/* [const] VM node referring to the kernel stack of the current thread.
 * WARNING: These structures for `_boottask' and `_bootidle' are not actually part of the kernel VM!
 * WARNING: You cannot assume that your stack-pointer is always located within `THIS_KERNEL_STACK',
 *          as KOS may use special, arch-specific stacks to deal with certain CPU exceptions that
 *          require execution on a separate stack (such as the #DF-stack on x86)
 *          To determine available/used stack memory, use the function below.
 */
DATDEF ATTR_PERTASK struct vm_node const this_kernel_stacknode;
DATDEF ATTR_PERTASK struct vm_datapart const this_kernel_stackpart;
#ifdef CONFIG_HAVE_KERNEL_STACK_GUARD
DATDEF ATTR_PERTASK struct vm_node const this_kernel_stackguard;
#endif /* CONFIG_HAVE_KERNEL_STACK_GUARD */

#define THIS_KERNEL_STACK      (&PERTASK(this_kernel_stacknode))
#define THIS_KERNEL_STACK_PART (&PERTASK(this_kernel_stackpart))

/* Return some rough estimates for the available/used stack memory.
 * `get_stack_avail()' is usually called prior to `alloca()' in order to
 * ensure that sufficient memory remains available after the allocation
 * was made. (for example: the max CFI remember-stack size is directly
 * determined by the amount of available stack memory) */
FUNDEF NOBLOCK ATTR_PURE WUNUSED size_t NOTHROW(KCALL get_stack_avail)(void);
FUNDEF NOBLOCK ATTR_PURE WUNUSED size_t NOTHROW(KCALL get_stack_inuse)(void);

/* Returns the bounds of the currently used kernel-space stack.
 * @param: pbase: Filled with a pointer to the lowest-address byte that is still apart of the stack.
 * @param: pend:  Filled with a pointer one past the highest-address byte that is still apart of the stack. */
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL get_current_stack)(void **pbase, void **pend);
FUNDEF NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL get_stack_for)(void **pbase, void **pend, void *sp);



/* =============================================================================
 *  LOW LEVEL SLEEP / WAKE FUNCTIONS
 * =============================================================================
 * -> Used to implement everything else there is about scheduling. */

/* Enter a sleeping state and return once being woken (true), or
 * once the given `abs_timeout' (which must be global) expires (false)
 * NOTES:
 *   - Special values for `abs_timeout' are:
 *     - KTIME_NONBLOCK (or anything `< ktime()'): Essentially does the same as task_yield()
 *     - KTIME_INFINITE:                           Never times out
 *   - Even if the caller has disabled preemption prior to the call,
 *     it will be re-enabled once this function returns.
 *   - This function is the bottom-most (and still task-level) API
 *     for conserving CPU cycles using preemption, in that this
 *     function is even used to implement `task_waitfor()'.
 *     The functions used to implement this one no longer work on tasks, but on CPUs!
 *   - If the thread is transferred to a different CPU while sleeping, a sporadic
 *     wakeup will be triggered, causing `task_sleep()' to return `true'.
 *   - When this function returns as the result of a timeout, then you may
 *     act as though that `ktime() > abs_timeout' (but note that this isn't
 *     actually an invariant, as your task may have been moved to a different
 *     CPU after waking up, at which point `ktime()' may have a slight offset)
 * The proper way of using this function is as follows:
 * >> while (SHOULD_WAIT()) { // Test some condition for which to wait
 * >>     PREEMPTION_DISABLE();
 * >>     // Test again now that interrupts are disabled
 * >>     // This test is required to prevent a race condition
 * >>     // where the condition is signaled between it being
 * >>     // changed and interrupts being disabled.
 * >>     COMPILER_READ_BARRIER();
 * >>     if (!SHOULD_WAIT()) {
 * >>         PREEMPTION_ENABLE();
 * >>         break;
 * >>     }
 * >>     // Serve RPC functions (when TRUE is returned, preemption was re-enabled)
 * >>     if (task_serve()) continue;
 * >>     // Do the actual sleep.
 * >>     if (!task_sleep(TIMEOUT))
 * >>         return DID_TIME_OUT;
 * >> }
 * >> return WAS_SIGNALED;
 * The sleeping thread should then be woken as follows:
 * >> SET_SHOULD_WAIT(false);
 * >> task_wake(waiting_thread); */
FUNDEF __BOOL NOTHROW(FCALL task_sleep)(ktime_t abs_timeout DFL(KTIME_INFINITE));

/* Force sleep until `abs_timeout' has passed. Any sporadic interrupts are
 * handled by simply continuing to sleep, until a timeout event happens. */
#define task_sleep_until(abs_timeout) \
	do {                              \
	} while (task_sleep(abs_timeout))

#define TASK_WAKE_FNORMAL   0x0000 /* Normal wake-up flags. */
#define TASK_WAKE_FWAITFOR  0x1000 /* When sending an IPI to a different CPU, wait for that CPU to acknowledge
                                    * having received the IPI, rather than allowing the IPI to be delivered
                                    * asynchronously. */
#define TASK_WAKE_FHIGHPRIO 0x4000 /* The wake-up has high priority. - Yield to the target thread
                                    * when preemption was enabled, before returning at the start
                                    * of a new quantum. */


/* Re-schedule the given `thread' if it was unscheduled (entered a sleeping state).
 * Using this function, a ~sporadic interrupt~ is implemented.
 * If the thread hasn't been unscheduled, this function is a no-op.
 * NOTE: This function is used in the implementation of `sig_send'
 * @param: flags:  Set of `TASK_WAKE_F*'
 * @return: true:  The task was woken, or wasn't sleeping.
 * @return: false: The given task has terminated. */
FUNDEF NOBLOCK NONNULL((1)) __BOOL
NOTHROW(FCALL task_wake)(struct task *__restrict thread,
                         unsigned int flags DFL(TASK_WAKE_FNORMAL));

/* Wake `thread' while impersonating `caller', where `caller' must some
 * running thread from the calling CPU. - This function is used to wake
 * up waiting threads during task exit, where at the point where the exit
 * status is broadcast, the exiting thread (THIS_TASK) can no longer be
 * used to send signals (since `task_wake()' has to look at things such
 * as the prev/next thread within the scheduler ring, which would have
 * already become invalid at that point, since the true calling thread
 * could no longer be considered apart of the scheduler ring)
 *
 * When calling this function, the caller must ensure that their current
 * CPU will no change, which can be done most easily by simply disabling
 * preemption, or setting the `TASK_FKEEPCORE' flag.
 *
 * The given `caller' is used when `thread' is running on `THIS_CPU',
 * in which case `thread' will be re-scheduled in relation to `caller',
 * where-as the regular `task_wake()' does this re-scheduling in relation
 * to `THIS_TASK'
 *
 * @param: flags:  Set of `TASK_WAKE_F*'
 * @return: true:  The task was woken, or wasn't sleeping.
 * @return: false: The given task has terminated. */
FUNDEF NOBLOCK NONNULL((1, 2)) __BOOL
NOTHROW(FCALL task_wake_as)(struct task *thread, struct task *caller,
                            unsigned int flags DFL(TASK_WAKE_FNORMAL));

/* Terminate the calling thread immediately.
 * WARNING: Do not call this function to terminate a thread.
 *          It would work, but exception handlers would not
 *          get unwound and resources would be leaked.
 *          If you wish to exit your current thread, just
 *          throw an `E_EXIT_THREAD' error instead.
 * This function is called by the unhandled exception handler
 * when it encounters an `E_EXIT_THREAD' error, or when exception
 * data cannot be propagated to userspace in the event of an
 * interrupt throwing some error, whilst originating from user-space.
 * @param: w_status: The task's exit status (mustn't be `WIFSTOPPED()' or `WIFCONTINUED()').
 *                   This argument is ignored for kernel-threads.
 * WARNING: Calling this function from an IDLE task, or any other
 *          task that is critical will cause the kernel to PANIC! */
FUNDEF ATTR_NORETURN void
NOTHROW(FCALL task_exit)(int w_status DFL(__W_EXITCODE(0, 0)));

#ifdef __cplusplus
extern "C++" {
FORCELOCAL ATTR_ARTIFICIAL ATTR_NORETURN void
NOTHROW(FCALL task_exit)(union wait status) {
	task_exit(status.w_status);
}
} /* extern "C++" */
#endif /* __cplusplus */


/* Pause execution for short moment, allowing other CPU cores to catch up.
 * This function is similar to `task_yield()', but intended to be used for
 * helping synchronization between multiple cores. - If no such functionality
 * exists on the host system, this is a no-op. */
#ifndef CONFIG_NO_SMP
FUNDEF NOBLOCK void NOTHROW(KCALL task_pause)(void);
#else /* !CONFIG_NO_SMP */
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void NOTHROW(KCALL task_pause)(void) { }
#endif /* CONFIG_NO_SMP */

/* Try to yield execution in the calling thread, but never thrown an exception.
 * `task_tryyield_or_pause()' is exactly the same as `task_tryyield()', however
 * it may execute `task_pause()' when preemption is disabled, before returning. */
#ifndef __task_tryyield_defined
#define __task_tryyield_defined 1
FUNDEF NOBLOCK_IF(!PREEMPTION_ENABLED()) unsigned int NOTHROW(KCALL task_tryyield)(void);
#endif /* !__task_tryyield_defined */
FUNDEF NOBLOCK_IF(!PREEMPTION_ENABLED()) unsigned int NOTHROW(KCALL task_tryyield_or_pause)(void);
#endif /* __CC__ */
#define TASK_TRYYIELD_SUCCESS             0x0000 /* Successfully yielded execution to another thread (guarantied to be ZERO(0)). */
#define TASK_TRYYIELD_PREEMPTION_DISABLED 0x0001 /* Yielding now is impossible because preemption is disabled.
                                                  * When `task_tryyield_or_pause()' was used, and the kernel has configured
                                                  * itself for multiple cores, `task_pause()' will be executed in this case. */
#define TASK_TRYYIELD_NO_SUCCESSOR        0x0002 /* There is no other task to which one could yield.
                                                  * If the kernel has configured itself for multiple cores,
                                                  * `task_pause()' instruction was called in this case (regardless
                                                  * of `task_tryyield()' or `task_tryyield_or_pause()' being used). */


#ifdef __CC__
/* Yield the remainder of the calling thread's current quantum
 * to allow another thread to start running prematurely.
 * @throw: E_WOULDBLOCK_PREEMPTED: Preemption has been disabled. */
#ifndef __task_yield_defined
#define __task_yield_defined 1
FUNDEF void (KCALL task_yield)(void) THROWS(E_WOULDBLOCK_PREEMPTED);
FUNDEF WUNUSED __BOOL NOTHROW(KCALL task_yield_nx)(void);
#endif /* !__task_yield_defined */
#endif /* __CC__ */





#if 0
#define TASK_CLONE_CSIGNAL        0x000000ff /* Signal mask to be sent at exit. */
#define TASK_CLONE_VM             0x00000100 /* Set if VM shared between processes. */
#define TASK_CLONE_FS             0x00000200 /* Set if fs info shared between processes. */
#define TASK_CLONE_FILES          0x00000400 /* Set if open files shared between processes. */
#define TASK_CLONE_SIGHAND        0x00000800 /* Set if signal handlers shared. */
/*      TASK_CLONE_               0x00001000  * ... */
#define TASK_CLONE_PTRACE         0x00002000 /* Set if tracing continues on the child. */
#define TASK_CLONE_VFORK          0x00004000 /* Set if the parent wants the child to wake it up on mm_release. */
#define TASK_CLONE_PARENT         0x00008000 /* Set if we want to have the same parent as the cloner. */
#define TASK_CLONE_THREAD         0x00010000 /* Set to add to same thread group. */
#define TASK_CLONE_NEWNS          0x00020000 /* Set to create new namespace. */
#define TASK_CLONE_SYSVSEM        0x00040000 /* Set to shared SVID SEM_UNDO semantics. */
#define TASK_CLONE_SETTLS         0x00080000 /* Set TLS info. */
#define TASK_CLONE_PARENT_SETTID  0x00100000 /* Store TID in userlevel buffer before MM copy. */
#define TASK_CLONE_CHILD_CLEARTID 0x00200000 /* Register exit futex and memory location to clear. */
#define TASK_CLONE_DETACHED       0x00400000 /* Create clone detached. */
#define TASK_CLONE_UNTRACED       0x00800000 /* Set if the tracing process can't force CLONE_PTRACE on this clone. */
#define TASK_CLONE_CHILD_SETTID   0x01000000 /* Store TID in userlevel buffer in the child. */
/*      TASK_CLONE_               0x02000000  * ... */
#define TASK_CLONE_NEWUTS         0x04000000 /* New utsname group. */
#define TASK_CLONE_NEWIPC         0x08000000 /* New ipcs. */
#define TASK_CLONE_NEWUSER        0x10000000 /* New user namespace. */
#define TASK_CLONE_NEWPID         0x20000000 /* New pid namespace. */
#define TASK_CLONE_NEWNET         0x40000000 /* New network namespace. */
#define TASK_CLONE_IO             0x80000000 /* Clone I/O context. */

/* High-level kernel interface for the clone(2) system call.
 * @param: clone_flags: Set of `TASK_CLONE_*' */
FUNDEF ATTR_MALLOC WUNUSED ATTR_RETNONNULL REF struct task *
(KCALL task_create)(struct ucpustate const *__restrict init_state,
                    uintptr_t clone_flags, void *tls_val,
                    USER CHECKED pid_t *parent_tidptr,
                    USER CHECKED pid_t *child_tidptr)
		THROWS(E_WOULDBLOCK, E_BADALLOC);
#endif



DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_TASK_H */
