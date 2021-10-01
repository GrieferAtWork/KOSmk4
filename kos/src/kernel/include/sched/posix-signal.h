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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_POSIX_SIGNAL_H
#define GUARD_KERNEL_INCLUDE_SCHED_POSIX_SIGNAL_H 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/types.h>
#include <sched/arch/posix-signal.h>
#include <sched/except-handler.h> /* CONFIG_HAVE_USERPROCMASK */
#include <sched/pertask.h>
#include <sched/signal.h>

#include <hybrid/host.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <bits/os/siginfo.h> /* struct __siginfo_struct */
#include <bits/os/sigset.h>  /* struct __sigset_struct */
#include <kos/aref.h>
#include <sys/wait.h>

#include <signal.h> /* SIG* */
#include <stdbool.h>

#include <libc/string.h> /* __libc_memset() */

#ifdef CONFIG_USE_NEW_RPC
#include <kernel/rt/except-handler.h> /* userexcept_sysret_inject_self() */
#include <sched/rpc.h>                /* task_serve() */

#define sigmask_check()                             task_serve()                    /* !DEPREACTED! */
#define sigmask_check_after_syscall(syscall_result) userexcept_sysret_inject_self() /* !DEPREACTED! */
#endif /* CONFIG_USE_NEW_RPC */


#ifndef NSIG
#define NSIG __NSIG
#endif /* !NSIG */

#define SIZEOF_USER_SIGINFO_T    __SI_USER_MAX_SIZE
#define SIZEOF_KERNEL_SIGINFO_T  __SI_KERNEL_MAX_SIZE

#ifdef __CC__
DECL_BEGIN

#ifndef __sigset_t_defined
#define __sigset_t_defined
typedef struct __sigset_struct sigset_t;
#endif /* !__sigset_t_defined */

#ifndef __siginfo_t_defined
#define __siginfo_t_defined
typedef struct __siginfo_struct siginfo_t;
#endif /* !__siginfo_t_defined */

struct ucontext;
typedef void (*user_sighandler_func_t)(signo_t signo);
typedef void (*user_sigaction_func_t)(signo_t signo, siginfo_t *info, struct ucontext *ctx);
typedef void (*user_sigrestore_func_t)(void);












/************************************************************************/
/* SIGNAL MASK                                                          */
/************************************************************************/
struct kernel_sigmask {
	WEAK refcnt_t sm_refcnt;  /* Signal mask reference counter. */
	WEAK refcnt_t sm_share;   /* [<= sm_refcnt] Signal mask share counter.
	                           * NOTE: Only allowed to be incremented when `this == sigmask_getrd()' */
	sigset_t      sm_mask;    /* [const_if(sm_share > 1)] Set of signals. */
};

DEFINE_REFCOUNT_FUNCTIONS(struct kernel_sigmask, sm_refcnt, kfree)

/* An empty signal mask used to initialize `this_kernel_sigmask' */
DATDEF struct kernel_sigmask kernel_sigmask_empty;

/* A full signal mask (i.e. one that blocks all signals (except for SIGKILL and SIGSTOP)) */
DATDEF struct kernel_sigmask kernel_sigmask_full;

#ifndef __kernel_sigmask_arref_defined
#define __kernel_sigmask_arref_defined
ARREF(kernel_sigmask_arref, kernel_sigmask);
#endif /* !__kernel_sigmask_arref_defined */

/* [0..1][lock(READ(ATOMIC), WRITE(THIS_TASK))]
 * Reference to the signal mask (set of signals being blocked) in the  current
 * thread. The pointed-to object is meaningless (but must still be valid) when
 * the associated thread make use of userprocmask.
 * NOTE: Only ever NULL for kernel-space threads! */
DATDEF ATTR_PERTASK struct kernel_sigmask_arref this_kernel_sigmask;

/* Return a pointer to the kernel signal mask of the calling thread. */
#define sigmask_kernel_getrd() PERTASK_GET(this_kernel_sigmask.arr_obj)

/* Make sure that `this_kernel_sigmask' is allocated, and isn't being
 * shared.  Then,  always  return  `PERTASK_GET(this_kernel_sigmask)' */
FUNDEF ATTR_RETNONNULL WUNUSED struct kernel_sigmask *KCALL
sigmask_kernel_getwr(void) THROWS(E_BADALLOC);


#ifdef CONFIG_HAVE_USERPROCMASK
/* Return a pointer to the signal mask of the calling thread. */
FUNDEF WUNUSED USER CHECKED sigset_t const *KCALL sigmask_getrd(void) THROWS(E_SEGFAULT);

/* Make sure that `this_kernel_sigmask' is allocated, and isn't being shared.
 * Then, always return `PERTASK_GET(this_kernel_sigmask)'
 * NOTE: When  calling thread has  the `TASK_FUSERPROCMASK' flag set,
 *       then this function will return the address of the currently-
 *       assigned  user-space signal mask,  rather than its in-kernel
 *       counterpart! */
FUNDEF WUNUSED USER CHECKED sigset_t *KCALL sigmask_getwr(void) THROWS(E_BADALLOC, E_SEGFAULT, ...);
#else /* CONFIG_HAVE_USERPROCMASK */
#define sigmask_getrd() (&sigmask_kernel_getrd()->sm_mask)
#define sigmask_getwr() (&sigmask_kernel_getwr()->sm_mask)
#endif /* !CONFIG_HAVE_USERPROCMASK */


/* Check if a given `signo' is currently masked. This function
 * handles all of the special cases, including TASK_VFORK  and
 * TASK_USERPROCMASK, as well as making sure that SIGSTOP  and
 * SIGKILL are never considered to be masked. */
#ifdef CONFIG_HAVE_USERPROCMASK
FUNDEF ATTR_PURE WUNUSED bool FCALL sigmask_ismasked(signo_t signo) THROWS(E_SEGFAULT);
#else /* CONFIG_HAVE_USERPROCMASK */
FUNDEF NOBLOCK ATTR_PURE WUNUSED bool NOTHROW(FCALL sigmask_ismasked)(signo_t signo);
#endif /* !CONFIG_HAVE_USERPROCMASK */


#ifdef CONFIG_HAVE_USERPROCMASK
#define SIGMASK_ISMASKED_NOPF_NO  0 /* The signal isn't masked */
#define SIGMASK_ISMASKED_NOPF_YES 1 /* The signal is masked */
/* The signal may be masked, or it may not be, however due  to
 * the target thread running on a different CPU, or using VIO,
 * a faulty pointer, or memory  currently not loaded into  the
 * core for the backing memory of its usersigmask, the calling
 * thread cannot conclusively determine this. */
#define SIGMASK_ISMASKED_NOPF_FAULT (-2)

/* Non-faulting version of `sigmask_ismasked()'.
 * @return: * : One of `SIGMASK_ISMASKED_NOPF_*' */
FUNDEF NOBLOCK ATTR_PURE WUNUSED int
NOTHROW(FCALL sigmask_ismasked_nopf)(signo_t signo);
#else /* CONFIG_HAVE_USERPROCMASK */
#define SIGMASK_ISMASKED_NOPF_NO     false /* The signal isn't masked */
#define SIGMASK_ISMASKED_NOPF_YES    true  /* The signal is masked */
#define sigmask_ismasked_nopf(signo) sigmask_ismasked(signo)
#endif /* !CONFIG_HAVE_USERPROCMASK */
/************************************************************************/

/* Helper  function that can  be used to determine  the masking status for
 * an arbitrary signal within an  arbitrary thread. Not that  userprocmask
 * signals  can _ONLY_  be determined (at  all) when `self'  is running on
 * the same CPU as the calling thread. If this is not the case, and `self'
 * uses the  userprocmask mechanism,  then SIGMASK_ISMASKED_NOPF_FAULT  is
 * _always_ returned.
 * @param: allow_blocking_and_exception_when_self_is_THIS_TASK:
 *              Like the argument name says: When self == THIS_TASK,
 *              and this argument is true, then this call is allowed
 *              to block, as well as throw exceptions.
 * @return: * : One of `SIGMASK_ISMASKED_*' (see above) */
#ifdef CONFIG_HAVE_USERPROCMASK
FUNDEF NOBLOCK_IF(!allow_blocking_and_exception_when_self_is_THIS_TASK || self != THIS_TASK)
ATTR_PURE WUNUSED NONNULL((1)) int FCALL
sigmask_ismasked_in(struct task *__restrict self, signo_t signo,
                    bool allow_blocking_and_exception_when_self_is_THIS_TASK __DFL(false))
		THROWS(E_SEGFAULT); /* Is NOTHROW when `allow_blocking_and_exception_when_self_is_THIS_TASK == false && self == THIS_TASK' */
#else /* CONFIG_HAVE_USERPROCMASK */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) int
NOTHROW(FCALL sigmask_ismasked_in)(struct task *__restrict self, signo_t signo);
#define sigmask_ismasked_in(self, signo, ...) sigmask_ismasked_in(self, signo)
#endif /* !CONFIG_HAVE_USERPROCMASK */












/************************************************************************/
/* SIGNAL ACTION DEFINITIONS                                            */
/************************************************************************/
struct kernel_sigaction {
	union {
		USER CHECKED user_sighandler_func_t sa_handler;   /* [1..1][valid_if(!SA_ONSTACK)] Normal signal handler */
		USER CHECKED user_sigaction_func_t  sa_sigaction; /* [1..1][valid_if(SA_ONSTACK)] Extended signal handler */
	};
	USER CHECKED user_sigrestore_func_t     sa_restore;   /* [1..1][valid_if(SA_RESTORER)] Signal handler restore function. */
	uintptr_t                               sa_flags;     /* Signal handler flags (Set of `SA_*'). */
	REF struct kernel_sigmask              *sa_mask;      /* [0..1] Mask of additional signals to block during execution of the handler
	                                                       * NOTE:  When   NULL,   no   additional  signals   been   to   be   blocked.
	                                                       * NOTE:  The pointed-to  mask is [const]  if its reference  counter is `> 1' */
};

struct sighand {
	/* Descriptor for how signals ought to be handled. */
	struct atomic_rwlock    sh_lock;              /* Lock for this signal handler descriptor. */
	WEAK refcnt_t           sh_share;             /* [lock(INC(sh_lock), DEC(ATOMIC))]
	                                               * Amount of unrelated processes sharing this sighand. */
	struct kernel_sigaction sh_actions[NSIG - 1]; /* Signal handlers. */
};
__DEFINE_SYNC_PROXY(struct sighand, sh_lock)

FUNDEF NOBLOCK void NOTHROW(KCALL sighand_destroy)(struct sighand *__restrict self);
#define sighand_incshare(self) \
	__hybrid_atomic_inc((self)->sh_share, __ATOMIC_SEQ_CST)
#define sighand_decshare(self)                                             \
	(void)(__hybrid_atomic_decfetch((self)->sh_share, __ATOMIC_SEQ_CST) || \
	       (sighand_destroy(self), 0))

struct sighand_ptr {
	/* Secondary indirection for sighand that allows
	 * for copy-on-write between different processes
	 * that were fork()-ed from each other.
	 * Because of the  fact that fork()  would otherwise have  to
	 * copy the sighand  table, only to  have a likely  following
	 * call to exec() destroy that  table again, we simply  share
	 * the sighand table  between the old  and new process  until
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
 * User-space  signal   handlers   for   the   calling   thread. */
DATDEF ATTR_PERTASK REF struct sighand_ptr *this_sighand_ptr;
#define THIS_SIGHAND_PTR        PERTASK_GET(this_sighand_ptr)

/* Return the sighand pointer of the given thread. */
FUNDEF NOBLOCK WUNUSED NONNULL((1)) REF struct sighand_ptr *
NOTHROW(FCALL task_getsighand_ptr)(struct task *__restrict thread);

/* Exchange the sighand pointer of the calling thread. */
FUNDEF WUNUSED REF struct sighand_ptr *
NOTHROW(FCALL task_setsighand_ptr)(struct sighand_ptr *newsighand_ptr);



/* Acquire a lock to the underlying signal handler table that is associated
 * with the  given  `sighand_ptr',  either for  reading,  or  for  writing.
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
 * With that in mind, these function will perform the necessary unsharing  of
 * copy-on-write signal handler  tables, while still  keeping association  of
 * handlers in check when it comes to shared handler tables, as usually found
 * within the same process. */
FUNDEF struct sighand *KCALL
sighand_ptr_lockread(struct sighand_ptr *__restrict ptr)
		THROWS(E_WOULDBLOCK);
FUNDEF ATTR_RETNONNULL struct sighand *KCALL
sighand_ptr_lockwrite(void) THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Return the default action to perform when faced with `signo' configured as `SIG_DFL'
 * @return: * : One of `SIG_*' (excluding `SIG_DFL' and `SIG_GET') */
FUNDEF NOBLOCK WUNUSED ATTR_CONST user_sighandler_func_t
NOTHROW(KCALL sighand_default_action)(signo_t signo);


/* Reset  the current handler for `signo' when  `current_action' matches the currently set action.
 * This function should be called by kernel-space signal delivery implementations to implement the
 * behavior of `SA_RESETHAND' when handling a signal.
 * @return: true:  Successfully reset the handler
 * @return: false: The given `current_action' didn't match the currently set action. */
FUNDEF bool KCALL
sighand_reset_handler(signo_t signo,
                      struct kernel_sigaction const *__restrict current_action)
		THROWS(E_WOULDBLOCK, E_BADALLOC);
/************************************************************************/












/************************************************************************/
/* SIGNAL SCHEDULING                                                    */
/************************************************************************/
#ifndef CONFIG_USE_NEW_RPC
/* Check for pending signals that are no longer being masked. */
FUNDEF void FCALL sigmask_check(void) THROWS(E_INTERRUPT, E_WOULDBLOCK);

/* Same as `sigmask_check()', but if a signal gets triggered, act as though
 * it was being serviced after the current system call has exited with  the
 * given `syscall_result' return value. (preventing system call restarting,
 * or indicating an interrupt exception to user-space)
 * If no signal was triggered, simply return normally.
 * This function is meant to  be used to check  for pending signals after  the
 * original signal mask got restored following the completion of a `pselect()'
 * or `ppoll()' system call. (at which point a previously masked signal should
 * no longer cause the system  call to fail and error  out with -EINTR (to  be
 * restarted), but instead  return its  normal value once  returning from  its
 * associated user-space signal handler (if any))
 * With this in mind, the call order for temporarily overriding the signal mask
 * for the purpose of a single system call looks like this:
 * >> sigset_t oldmask;
 * >> USER CHECKED sigset_t *mymask;
 * >> mymask = sigmask_getwr();
 * >> memcpy(&oldmask, mymask, sizeof(sigset_t));
 * >> TRY {
 * >>     memcpy(mymask, &newmask, sizeof(sigset_t));
 * >> } EXCEPT {
 * >>     memcpy(mymask, &oldmask, sizeof(sigset_t));
 * >>     RETHROW();
 * >> }
 * >> TRY {
 * >>     result = do_my_system_call();
 * >> } EXCEPT {
 * >>     memcpy(mymask, &oldmask, sizeof(sigset_t));
 * >>     sigmask_check_after_except();
 * >>     RETHROW();
 * >> }
 * >> memcpy(mymask, &oldmask, sizeof(sigset_t));
 * >> sigmask_check_after_syscall(result);
 * >> return result;
 */
FUNDEF void FCALL
sigmask_check_after_syscall(syscall_ulong_t syscall_result)
		THROWS(E_INTERRUPT, E_WOULDBLOCK);


/* Same as `sigmask_check()', but should be called in order to have
 * user-space handle the currently set  exception in case a  signal
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

struct icpustate;
struct rpc_syscall_info;
/* Update the given  `state' to raise  the specified `siginfo'  as
 * a user-space signal  within the calling  thread. The caller  is
 * responsible  to handle special signal handlers (`SIG_*')
 * before calling this function! This function should only be used
 * to  enqueue the execution of a signal handler with a user-space
 * entry point.
 * @param: state:   The CPU state describing the return to user-space.
 * @param: action:  The signal action to perform.
 * @param: siginfo: The signal that is being raised.
 * @param: sc_info: When non-NULL, `sc_info'  describes a system  call
 *                  that may be restarted. Note however that ontop  of
 *                  this, [restart({auto,must,dont})] logic will still
 *                  be applied, which is done in cooperation with  the
 *                  system call restart database.
 * @return: * :     The updated CPU state.
 * @return: NULL:   The `SA_RESETHAND' flag was set,
 *                  but `action' differs from the set handler. */
FUNDEF WUNUSED NONNULL((1, 2)) struct icpustate *KCALL
userexcept_callsignal(struct icpustate *__restrict state,
                      struct kernel_sigaction const *__restrict action,
                      USER CHECKED siginfo_t const *siginfo,
                      struct rpc_syscall_info const *sc_info)
		THROWS(E_SEGFAULT, E_WOULDBLOCK);

/* Suspend execution of the calling thread by setting `TASK_FSUSPENDED',
 * and keep  the  thread  suspended until  `task_sigcont()'  is  called.
 * This is used to implement SIGSTOP/SIGCONT behavior.
 * @param: stop_code: The stop code (created with `W_STOPCODE(signo)') */
FUNDEF void KCALL task_sigstop(int stop_code) THROWS(E_WOULDBLOCK,E_INTERRUPT);

/* Continue execution in `thread', if that thread is currently suspended
 * due to having called `task_sigstop()'
 * WARNING: A race condition exists where `thread' may not have started waiting
 *          yet, in which  case this function  will return `false',  indicating
 *          that the given thread wasn't actually woken.
 * @return: true:  Successfully set `thread' to continue execution
 * @return: false: Either `thread' hasn't started sleeping, or was already continued. */
FUNDEF NOBLOCK bool NOTHROW(KCALL task_sigcont)(struct task *__restrict thread);

struct sigqueue_entry {
	/* Descriptor for  a signal  that  was send,  but  was
	 * blocked and thereby scheduled to be received later. */
	struct sigqueue_entry *sqe_next;  /* [owned][0..1] Next queued signal. */
	siginfo_t              sqe_info;  /* Signal information. */
};
#endif /* !CONFIG_USE_NEW_RPC */


/* Raise a posix signal within a given thread `target'
 * @return: true:  Successfully scheduled/enqueued the signal for delivery to `target'
 * @return: false: The given thread `target' has already terminated execution.
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE: The signal number in `info' is ZERO(0) or > `_NSIG'
 * @throw: E_INTERRUPT_USER_RPC:        `target' is the calling thread, and the signal isn't being blocked at the moment. */
FUNDEF NONNULL((1)) bool KCALL
task_raisesignalthread(struct task *__restrict target,
                       USER CHECKED siginfo_t const *info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE,
		       E_INTERRUPT_USER_RPC, E_SEGFAULT);

/* Raise a posix signal within a given process that `target' is apart of
 * @return: true:  Successfully scheduled/enqueued the signal for delivery to `target'
 * @return: false: The given process `target' has already terminated execution.
 * @return: false: The given process `target' is a kernel thread.
 * @throw: E_INVALID_ARGUMENT_BAD_VALUE: The signal number in `info' is ZERO(0) or >= `_NSIG+1'
 * @throw: E_INTERRUPT_USER_RPC:         The calling thread is apart of the same  process,
 *                                       and the signal isn't being blocked at the moment. */
FUNDEF NONNULL((1)) bool KCALL
task_raisesignalprocess(struct task *__restrict target,
                        USER CHECKED siginfo_t const *info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE,
		       E_INTERRUPT_USER_RPC, E_SEGFAULT);


/* Send a signal to every process within the same process group that `target' is apart of.
 * @return: * : The number of processes to which the signal was delivered. */
FUNDEF NONNULL((1)) size_t KCALL
task_raisesignalprocessgroup(struct task *__restrict target,
                             USER CHECKED siginfo_t const *info)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE,
		       E_INTERRUPT_USER_RPC, E_PROCESS_EXITED);



#ifdef __cplusplus
extern "C++" {
/* Simplified variants of the functions above that directly take a kernel-space SIGNO */
LOCAL ATTR_ARTIFICIAL NONNULL((1)) bool KCALL
task_raisesignalthread(struct task *__restrict target, signo_t signo)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE,
		       E_INTERRUPT_USER_RPC, E_SEGFAULT) {
	siginfo_t info;
	__libc_memset(&info, 0, sizeof(info));
	info.si_signo = signo;
	return task_raisesignalthread(target, &info);
}

LOCAL ATTR_ARTIFICIAL NONNULL((1)) bool KCALL
task_raisesignalprocess(struct task *__restrict target, signo_t signo)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE,
		       E_INTERRUPT_USER_RPC, E_SEGFAULT) {
	siginfo_t info;
	__libc_memset(&info, 0, sizeof(info));
	info.si_signo = signo;
	return task_raisesignalprocess(target, &info);
}

LOCAL ATTR_ARTIFICIAL NONNULL((1)) size_t KCALL
task_raisesignalprocessgroup(struct task *__restrict target, signo_t signo)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INVALID_ARGUMENT_BAD_VALUE,
		       E_INTERRUPT_USER_RPC) {
	siginfo_t info;
	__libc_memset(&info, 0, sizeof(info));
	info.si_signo = signo;
	return task_raisesignalprocessgroup(target, &info);
}

}
#endif /* __cplusplus */

DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_SCHED_POSIX_SIGNAL_H */
