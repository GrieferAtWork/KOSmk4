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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_POSIX_SIGNAL_H
#define GUARD_KERNEL_INCLUDE_SCHED_POSIX_SIGNAL_H 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/types.h>
#include <misc/atomic-ref.h>
#include <sched/arch/posix-signal.h>
#include <sched/pertask.h>
#include <sched/signal.h>

#include <hybrid/host.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <bits/siginfo-struct.h> /* struct __siginfo_struct */
#include <bits/sigset.h>         /* struct __sigset_struct */
#include <sys/wait.h>

#include <signal.h> /* SIG* */

#include <libc/string.h> /* __libc_memset() */

DECL_BEGIN

#ifndef NSIG
#define NSIG __NSIG
#endif /* !NSIG */

#define SIGACTION_SA_NOCLDSTOP 0x00000001 /* Don't send SIGCHLD when children stop (Ignored for anything other than SIGCLD). */
#define SIGACTION_SA_NOCLDWAIT 0x00000002 /* Don't create zombie on child death (Ignored for anything other than SIGCLD). */
#define SIGACTION_SA_SIGINFO   0x00000004 /* Invoke signal-catching function with three arguments instead of one. */
#define SIGACTION_SA_RESTORER  0x04000000 /* A user-supplied signal restore function was given. */
#define SIGACTION_SA_ONSTACK   0x08000000 /* Execute the handler on sigaltstack. */
#define SIGACTION_SA_RESTART   0x10000000 /* Restart restartable syscall on signal return. */
#define SIGACTION_SA_NODEFER   0x40000000 /* Don't automatically block the signal when its handler is being executed. */
#define SIGACTION_SA_RESETHAND 0x80000000 /* Delete the handler before it gets invoked. */

/* Special signal action functions. */
#define KERNEL_SIG_DFL   (__CCAST(user_sighandler_func_t)0)  /* [ACT] Default action. */
#define KERNEL_SIG_IGN   (__CCAST(user_sighandler_func_t)1)  /* [ACT] Ignore signal. */
/*      KERNEL_SIG_      (__CCAST(user_sighandler_func_t)2)   * Unused in kernel-space (is `SIG_HOLD' in user-space) */
#define KERNEL_SIG_TERM  (__CCAST(user_sighandler_func_t)3)  /* [ACT] Terminate the receiving process. */
#define KERNEL_SIG_EXIT  (__CCAST(user_sighandler_func_t)4)  /* [ACT] Terminate the receiving thread. */
/*      KERNEL_SIG_      (__CCAST(user_sighandler_func_t)5)   * ... */
/*      KERNEL_SIG_      (__CCAST(user_sighandler_func_t)6)   * ... */
/*      KERNEL_SIG_      (__CCAST(user_sighandler_func_t)7)   * ... */
#define KERNEL_SIG_CONT  (__CCAST(user_sighandler_func_t)8)  /* [ACT] Continue execution. */
#define KERNEL_SIG_STOP  (__CCAST(user_sighandler_func_t)9)  /* [ACT] Suspend execution. */
#define KERNEL_SIG_CORE  (__CCAST(user_sighandler_func_t)10) /* [ACT] Create a coredump and terminate. */
#define KERNEL_SIG_GET   (__CCAST(user_sighandler_func_t)11) /* Only get the current handler (accepted by `signal(2)') */


#define SIZEOF_USER_SIGINFO_T    __SI_USER_MAX_SIZE
#define SIZEOF_KERNEL_SIGINFO_T  __SI_KERNEL_MAX_SIZE

#ifdef __CC__

#ifndef __sigset_t_defined
#define __sigset_t_defined 1
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

#ifndef __siginfo_t_defined
#define __siginfo_t_defined 1
typedef struct __siginfo_struct siginfo_t;
#endif /* !__siginfo_t_defined */

struct ucontext;
typedef void (*user_sighandler_func_t)(signo_t signo);
typedef void (*user_sigaction_func_t)(signo_t signo, siginfo_t *info, struct ucontext *ctx);
typedef void (*user_sigrestore_func_t)(void);

struct kernel_sigmask {
	WEAK refcnt_t sm_refcnt;  /* Signal mask reference counter. */
	WEAK refcnt_t sm_share;   /* [<= sm_refcnt] Signal mask share counter.
	                           * NOTE: Only allowed to be incremented when `this == sigmask_getrd()' */
	sigset_t      sm_mask;    /* [const_if(sm_share > 1)] Set of signals. */
};

DEFINE_REFCOUNT_FUNCTIONS(struct kernel_sigmask, sm_refcnt, kfree)

/* An empty signal mask used to initialize `this_sigmask' */
DATDEF struct kernel_sigmask empty_kernel_sigmask;

/* [0..1][lock(READ(ATOMIC), WRITE(THIS_TASK))]
 * Reference to the signal mask (set of signals being blocked) in the current thread.
 * NOTE: Only ever NULL for kernel-space threads! */
DATDEF ATTR_PERTASK ATOMIC_REF(struct kernel_sigmask) this_sigmask;

/* Return a pointer to the signal mask of the calling thread. */
#ifdef __INTELLISENSE__
FUNDEF ATTR_RETNONNULL WUNUSED struct kernel_sigmask *KCALL sigmask_getrd(void);
#else
#define sigmask_getrd() PERTASK_GET(this_sigmask.m_pointer)
#endif

/* Make sure that `this_sigmask' is allocated, and isn't being shared.
 * Then, always return `PERTASK_GET(this_sigmask)' */
FUNDEF ATTR_RETNONNULL WUNUSED struct kernel_sigmask *KCALL sigmask_getwr(void) THROWS(E_BADALLOC);

/* Check for pending signals that are no longer being masked. */
FUNDEF void FCALL sigmask_check(void) THROWS(E_INTERRUPT, E_WOULDBLOCK);

/* Same as `sigmask_check()', but if a signal gets triggered, act as though
 * it was being serviced after the current system call has exited with the
 * given `syscall_result' return value. (preventing system call restarting,
 * or indicating an interrupt exception to user-space)
 * If no signal was triggered, simply return normally.
 * This function is meant to be used to check for pending signals after the
 * original signal mask got restored following the completion of a `pselect()'
 * or `ppoll()' system call. (at which point a previously masked signal should
 * no longer cause the system call to fail and error out with -EINTR (to be
 * restarted), but instead return its normal value once returning from its
 * associated user-space signal handler (if any))
 * With this in mind, the call order for temporarily overriding the signal mask
 * for the purpose of a single system call looks like this:
 * >> sigset_t oldmask;
 * >> struct kernel_sigmask *mymask;
 * >> mymask = sigmask_getwr();
 * >> memcpy(&oldmask, &mymask->sm_mask, sizeof(sigset_t));
 * >> TRY {
 * >>     memcpy(&mymask->sm_mask, &newmask, sizeof(sigset_t));
 * >>     if unlikely(sigismember(&mymask->sm_mask, SIGKILL) ||
 * >>                 sigismember(&mymask->sm_mask, SIGSTOP)) {
 * >>         sigdelset(&mymask->sm_mask, SIGKILL);
 * >>         sigdelset(&mymask->sm_mask, SIGSTOP);
 * >>         COMPILER_BARRIER();
 * >>         sigmask_check();
 * >>     }
 * >> } EXCEPT {
 * >>     bool mandatory_were_masked;
 * >>     mandatory_were_masked = sigismember(&mymask->sm_mask, SIGKILL) ||
 * >>                             sigismember(&mymask->sm_mask, SIGSTOP);
 * >>     memcpy(&mymask->sm_mask, &oldmask, sizeof(sigset_t));
 * >>     if (mandatory_were_masked)
 * >>         sigmask_check_after_except();
 * >>     RETHROW();
 * >> }
 * >> TRY {
 * >>     result = do_my_system_call();
 * >> } EXCEPT {
 * >>     memcpy(&mymask->sm_mask, &oldmask, sizeof(sigset_t));
 * >>     sigmask_check_after_except();
 * >>     RETHROW();
 * >> }
 * >> memcpy(&mymask->sm_mask, &oldmask, sizeof(sigset_t));
 * >> sigmask_check_after_syscall(result);
 * >> return result;
 */
FUNDEF void FCALL
sigmask_check_after_syscall(syscall_ulong_t syscall_result)
		THROWS(E_INTERRUPT, E_WOULDBLOCK);

/* Same as `sigmask_check()', but should be called in order to have
 * user-space handle the currently set exception in case a signal
 * handler has to be invoked.
 * See the documentation of `sigmask_check_after_syscall()' for when
 * this function needs to be called. */
FUNDEF void FCALL
sigmask_check_after_except(void)
		THROWS(E_INTERRUPT, E_WOULDBLOCK);


struct rpc_syscall_info;

/* Same as `sigmask_check()', but service signals immediately.
 * @param: sc_info: A system call that may be restarted, or NULL.
 * @return: * :                       The updated cpu-state.
 * @return: TASK_RPC_RESTART_SYSCALL: Nothing was handled. */
FUNDEF struct icpustate *FCALL
sigmask_check_s(struct icpustate *__restrict state,
                struct rpc_syscall_info const *sc_info)
		THROWS(E_WOULDBLOCK, E_SEGFAULT);


struct kernel_sigaction {
	union {
		USER CHECKED user_sighandler_func_t sa_handler;   /* [1..1][valid_if(!SIGACTION_SA_ONSTACK)] Normal signal handler */
		USER CHECKED user_sigaction_func_t  sa_sigaction; /* [1..1][valid_if(SIGACTION_SA_ONSTACK)] Extended signal handler */
	};
	USER CHECKED user_sigrestore_func_t     sa_restore;   /* [1..1][valid_if(SIGACTION_SA_RESTORER)] Signal handler restore function. */
	uintptr_t                               sa_flags;     /* Signal handler flags (Set of `SIGACTION_SA_*'). */
	REF struct kernel_sigmask              *sa_mask;      /* [0..1] Mask of additional signals to block during execution of the handler
	                                                       * NOTE: When NULL, no additional signals been to be blocked.
	                                                       * NOTE: The pointed-to mask is [const] if its reference counter is `> 1' */
};

struct sighand {
	/* Descriptor for how signals ought to be handled. */
	struct atomic_rwlock    sh_lock;              /* Lock for this signal handler descriptor. */
	WEAK refcnt_t           sh_share;             /* [lock(INC(sh_lock),DEC(ATOMIC))]
	                                               * Amount of unrelated processes sharing this sighand. */
	struct kernel_sigaction sh_actions[NSIG - 1]; /* Signal handlers. */
};
__DEFINE_SYNC_PROXY(struct sighand, sh_lock)

FUNDEF NOBLOCK void NOTHROW(KCALL sighand_destroy)(struct sighand *__restrict self);
#define sighand_incshare(self) __hybrid_atomic_incfetch((self)->sh_share, __ATOMIC_SEQ_CST)
#define sighand_decshare(self) (__hybrid_atomic_decfetch((self)->sh_share, __ATOMIC_SEQ_CST) || (sighand_destroy(self), 0))

struct sighand_ptr {
	/* Secondary indirection for sighand that allows
	 * for copy-on-write between different processes
	 * that were fork()-ed from each other.
	 * Because of the fact that fork() would otherwise have to
	 * copy the sighand table, only to have a likely following
	 * call to exec() destroy that table again, we simply share
	 * the sighand table between the old and new process until
	 * either one of the processes dies or calls exec(), or until
	 * one of them attempts to modify the sighand table, in which
	 * case this indirection allows for lazy copy-on-write. */
	WEAK refcnt_t        sp_refcnt;      /* Amount of threads using `sp_hand' */
	struct atomic_rwlock sp_lock;        /* Lock for the `sp_hand' pointer. */
	REF struct sighand  *sp_hand;        /* [0..1][ref(sh_share)][lock(sp_lock,WRITE_ONCE[ALLOW_EXCHANGE])]
	                                      * Pointer to the shared signal handler table. */
};
__DEFINE_SYNC_PROXY(struct sighand_ptr, sp_lock)

FUNDEF NOBLOCK void NOTHROW(KCALL sighand_ptr_destroy)(struct sighand_ptr *__restrict self);
DEFINE_REFCOUNT_FUNCTIONS(struct sighand_ptr, sp_refcnt, sighand_ptr_destroy)

/* [0..1][valid_if(!TASK_FKERNTHREAD)][lock(PRIVATE(THIS_TASK))]
 * User-space signal handlers for the calling thread. */
DATDEF ATTR_PERTASK REF struct sighand_ptr *this_sighand_ptr;
#define THIS_SIGHAND_PTR        PERTASK_GET(this_sighand_ptr)



/* Acquire a lock to the underlying signal handler table that is associated
 * with the given `sighand_ptr', either for reading, or for writing.
 * For reading:
 * >> struct sighand *h;
 * >> h = sighand_ptr_lockread(THIS_SIGHAND_PTR);
 * >> if (h) {
 * >>     ...
 * >>     sync_endread(h);
 * >> } else {
 * >>     ...  // Use default behavior (s.a. `sighand_default_action()')
 * >> }
 * For writing:
 * >> h = sighand_ptr_lockwrite();
 * >> ...
 * >> sync_endwrite(h);
 * With that in mind, these function will perform the necessary unsharing of
 * copy-on-write signal handler tables, while still keeping association of
 * handlers in check when it comes to shared handler tables, as usually found
 * within the same process. */
FUNDEF struct sighand *KCALL
sighand_ptr_lockread(struct sighand_ptr *__restrict ptr)
		THROWS(E_WOULDBLOCK);
FUNDEF ATTR_RETNONNULL struct sighand *KCALL
sighand_ptr_lockwrite(void) THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Return the default action to perform when faced with `signo' configured as `KERNEL_SIG_DFL'
 * @return: * : One of `KERNEL_SIG_*' (excluding `KERNEL_SIG_DFL' and `KERNEL_SIG_GET') */
FUNDEF NOBLOCK WUNUSED ATTR_CONST user_sighandler_func_t
NOTHROW(KCALL sighand_default_action)(u32 signo);


/* Reset the current handler for `signo' when `current_action' matches the currently set action.
 * This function should be called by kernel-space signal delivery implementations to implement the
 * behavior of `SIGACTION_SA_RESETHAND' when handling a signal.
 * @return: true:  Successfully reset the handler
 * @return: false: The given `current_action' didn't match the currently set action. */
FUNDEF bool KCALL
sighand_reset_handler(u32 signo,
                      struct kernel_sigaction const *__restrict current_action)
		THROWS(E_WOULDBLOCK, E_BADALLOC);


struct icpustate;
struct rpc_syscall_info;
/* Update the given `state' to raise the specified `siginfo'
 * as a user-space signal within the calling thread.
 * NOTE: The caller is responsible to handle special signal
 *       handlers (`KERNEL_SIG_*') before calling this function!
 *       This function should only be used to enqueue the execution
 *       of a signal handler with a user-space entry point.
 * @param: state:   The interrupt CPU state describing the return to user-space.
 * @param: action:  The signal action to perform.
 * @param: siginfo: The signal that is being raised.
 * @param: sc_info: When non-NULL, `sc_info' describes a system call that may be restarted.
 *                  Note however that ontop of this, [restart({auto,must,dont})]
 *                  logic will still be applied, which is done in cooperation
 *                  with the system call restart database.
 * @return: * :     The updated CPU state.
 * @return: NULL:   The `SIGACTION_SA_RESETHAND' flag was set, but `action'
 *                  differs from the set handler. */
FUNDEF WUNUSED struct icpustate *KCALL
sighand_raise_signal(struct icpustate *__restrict state,
                     struct kernel_sigaction const *__restrict action,
                     USER CHECKED siginfo_t const *siginfo,
                     struct rpc_syscall_info const *sc_info)
		THROWS(E_SEGFAULT, E_WOULDBLOCK);

/* Suspend execution of the calling thread by setting `TASK_FSUSPENDED',
 * and keep the thread suspended until `task_sigcont()' is called.
 * This is used to implement SIGSTOP/SIGCONT behavior.
 * @param: stop_code: The stop code (created with `W_STOPCODE(signo)') */
FUNDEF void KCALL task_sigstop(int stop_code) THROWS(E_WOULDBLOCK,E_INTERRUPT);

/* Continue execution in `thread', if that thread is currently suspended
 * due to having called `task_sigstop()'
 * WARNING: A race condition exists where `thread' may not have started waiting
 *          yet, in which case this function will return `false', indicating
 *          that the given thread wasn't actually woken.
 * @return: true:  Successfully set `thread' to continue execution
 * @return: false: Either `thread' hasn't started sleeping, or was already continued. */
FUNDEF NOBLOCK bool NOTHROW(KCALL task_sigcont)(struct task *__restrict thread);



struct sigqueue_entry {
	/* Descriptor for a signal that was send, but was
	 * blocked and thereby scheduled to be received later. */
	struct sigqueue_entry *sqe_next;  /* [owned][0..1] Next queued signal. */
	siginfo_t              sqe_info;  /* Signal information. */
};

/* Raise a posix signal within a given thread `target'
 * @return: true:   Successfully scheduled/enqueued the signal for delivery to `target'
 * @return: false:  The given thread `target' has already terminated execution.
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE: The signal number in `info' is ZERO(0) or > `_NSIG'
 * @throw: E_INTERRUPT_USER_RPC:        `target' is the calling thread, and the signal isn't being blocked at the moment. */
FUNDEF NOBLOCK_IF(rpc_flags & GFP_ATOMIC) NONNULL((1)) bool KCALL
task_raisesignalthread(struct task *__restrict target,
                       USER CHECKED siginfo_t *info,
                       gfp_t rpc_flags DFL(GFP_NORMAL))
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE,
		       E_INTERRUPT_USER_RPC, E_SEGFAULT);

/* Noexcept variant of `task_raisesignalthread()'
 * @return: * : One of `TASK_RAISESIGNALTHREAD_NX_*' */
FUNDEF NOBLOCK_IF(rpc_flags & GFP_ATOMIC) NONNULL((1)) int
NOTHROW(KCALL task_raisesignalthread_nx)(struct task *__restrict target,
                                         USER CHECKED siginfo_t *info,
                                         gfp_t rpc_flags DFL(GFP_NORMAL));
#define TASK_RAISESIGNALTHREAD_NX_INTERRUPTED   1  /* Successfully raised the signal (and the target is the caller) */
#define TASK_RAISESIGNALTHREAD_NX_SUCCESS       0  /* Successfully raised the signal */
#define TASK_RAISESIGNALTHREAD_NX_TERMINATED  (-1) /* The specified target thread has terminated */
#define TASK_RAISESIGNALTHREAD_NX_KERNTHREAD  (-2) /* The specified target thread is a kernel thread */
#define TASK_RAISESIGNALTHREAD_NX_BADALLOC    (-3) /* The allocation failed, or would have blocked. */
#define TASK_RAISESIGNALTHREAD_NX_BADSIGNO    (-4) /* The signal number associated with `info' is bad. */
#define TASK_RAISESIGNALTHREAD_NX_SEGFAULT    (-5) /* The given `info' structure points to a faulty memory address. */
#define TASK_RAISESIGNALTHREAD_NX_WOULDBLOCK  (-6) /* The operation would have blocked. */



/* Raise a posix signal within a given process that `target' is apart of
 * @return: true:  Successfully scheduled/enqueued the signal for delivery to `target'
 * @return: false: The given process `target' has already terminated execution.
 * @return: false: The given process `target' is a kernel thread.
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE: The signal number in `info' is ZERO(0) or >= `_NSIG+1'
 * @throw: E_INTERRUPT_USER_RPC:         The calling thread is apart of the same process,
 *                                       and the signal isn't being blocked at the moment. */
FUNDEF NOBLOCK_IF(rpc_flags & GFP_ATOMIC) NONNULL((1)) bool KCALL
task_raisesignalprocess(struct task *__restrict target,
                        USER CHECKED siginfo_t *info,
                        gfp_t rpc_flags DFL(GFP_NORMAL))
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE,
		       E_INTERRUPT_USER_RPC, E_SEGFAULT);



/* Noexcept variant of `task_raisesignalprocess()'
 * @return: * : One of `TASK_RAISESIGNALTHREAD_NX_*' */
FUNDEF NOBLOCK_IF(rpc_flags & GFP_ATOMIC) NONNULL((1)) int
NOTHROW(KCALL task_raisesignalprocess_nx)(struct task *__restrict target,
                                          USER CHECKED siginfo_t *info,
                                          gfp_t rpc_flags DFL(GFP_NORMAL));



/* Send a signal to every process within the same process group that `target' is apart of.
 * @return: * : The number of processes to which the signal was delivered. */
FUNDEF NOBLOCK_IF(rpc_flags & GFP_ATOMIC) NONNULL((1)) size_t KCALL
task_raisesignalprocessgroup(struct task *__restrict target,
                             USER CHECKED siginfo_t *info,
                             gfp_t rpc_flags DFL(GFP_NORMAL))
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE,
		       E_INTERRUPT_USER_RPC, E_PROCESS_EXITED);

/* Noexcept variant of `task_raisesignalprocessgroup()'
 * @return: * : The number of processes to which the signal was delivered,
 *              or one of `TASK_RAISESIGNALPROCESSGROUP_NX_*' */
FUNDEF NOBLOCK_IF(rpc_flags & GFP_ATOMIC) NONNULL((1)) ssize_t
NOTHROW(KCALL task_raisesignalprocessgroup_nx)(struct task *__restrict target,
                                               USER CHECKED siginfo_t *info,
                                               gfp_t rpc_flags DFL(GFP_NORMAL));
#define TASK_RAISESIGNALPROCESSGROUP_NX_SUCCESS       0  /* Successfully raised the signal */
#define TASK_RAISESIGNALPROCESSGROUP_NX_TERMINATED  (-1) /* The specified target process has terminated */
#define TASK_RAISESIGNALPROCESSGROUP_NX_KERNTHREAD  (-2) /* The specified target process is apart of the kernel */
#define TASK_RAISESIGNALPROCESSGROUP_NX_BADALLOC    (-3) /* The allocation failed, or would have blocked. */
#define TASK_RAISESIGNALPROCESSGROUP_NX_BADSIGNO    (-4) /* The signal number associated with `info' is bad. */
#define TASK_RAISESIGNALPROCESSGROUP_NX_SEGFAULT    (-5) /* The given `info' structure points to a faulty memory address. */
#define TASK_RAISESIGNALPROCESSGROUP_NX_WOULDBLOCK  (-6) /* The operation would have blocked. */
#define TASK_RAISESIGNALPROCESSGROUP_NX_INTERRUPTED (-7) /* Successfully raised the signal (and one of the targets was the caller) */



#ifdef __cplusplus
extern "C++" {
/* Simplified variants of the functions above that directly take a kernel-space SIGNO */
LOCAL ATTR_ARTIFICIAL NOBLOCK_IF(rpc_flags & GFP_ATOMIC) NONNULL((1)) bool KCALL
task_raisesignalthread(struct task *__restrict target,
                       u32 signo,
                       gfp_t rpc_flags DFL(GFP_NORMAL))
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE,
		       E_INTERRUPT_USER_RPC, E_SEGFAULT) {
	siginfo_t info;
	__libc_memset(&info, 0, sizeof(info));
	info.si_signo = signo;
	return task_raisesignalprocess(target, &info, rpc_flags);
}

LOCAL ATTR_ARTIFICIAL NOBLOCK_IF(rpc_flags & GFP_ATOMIC) NONNULL((1)) int
NOTHROW(KCALL task_raisesignalthread_nx)(struct task *__restrict target,
                                         u32 signo,
                                         gfp_t rpc_flags DFL(GFP_NORMAL)) {
	siginfo_t info;
	__libc_memset(&info, 0, sizeof(info));
	info.si_signo = signo;
	return task_raisesignalthread_nx(target, &info, rpc_flags);
}

LOCAL ATTR_ARTIFICIAL NOBLOCK_IF(rpc_flags & GFP_ATOMIC) NONNULL((1)) bool KCALL
task_raisesignalprocess(struct task *__restrict target,
                        u32 signo,
                        gfp_t rpc_flags DFL(GFP_NORMAL))
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE,
		       E_INTERRUPT_USER_RPC, E_SEGFAULT) {
	siginfo_t info;
	__libc_memset(&info, 0, sizeof(info));
	info.si_signo = signo;
	return task_raisesignalprocess(target, &info, rpc_flags);
}

LOCAL ATTR_ARTIFICIAL NOBLOCK_IF(rpc_flags & GFP_ATOMIC) NONNULL((1)) int
NOTHROW(KCALL task_raisesignalprocess_nx)(struct task *__restrict target,
                                          u32 signo,
                                          gfp_t rpc_flags DFL(GFP_NORMAL)) {
	siginfo_t info;
	__libc_memset(&info, 0, sizeof(info));
	info.si_signo = signo;
	return task_raisesignalprocess_nx(target, &info, rpc_flags);
}

LOCAL ATTR_ARTIFICIAL NOBLOCK_IF(rpc_flags & GFP_ATOMIC) NONNULL((1)) size_t KCALL
task_raisesignalprocessgroup(struct task *__restrict target,
                             u32 signo,
                             gfp_t rpc_flags DFL(GFP_NORMAL))
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE,
		       E_INTERRUPT_USER_RPC) {
	siginfo_t info;
	__libc_memset(&info, 0, sizeof(info));
	info.si_signo = signo;
	return task_raisesignalprocessgroup(target, &info, rpc_flags);
}

LOCAL ATTR_ARTIFICIAL NOBLOCK_IF(rpc_flags & GFP_ATOMIC) NONNULL((1)) ssize_t
NOTHROW(KCALL task_raisesignalprocessgroup_nx)(struct task *__restrict target,
                                               u32 signo,
                                               gfp_t rpc_flags DFL(GFP_NORMAL)) {
	siginfo_t info;
	__libc_memset(&info, 0, sizeof(info));
	info.si_signo = signo;
	return task_raisesignalprocessgroup_nx(target, &info, rpc_flags);
}


}
#endif /* __cplusplus */


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_POSIX_SIGNAL_H */
