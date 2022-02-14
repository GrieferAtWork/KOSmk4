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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SIGACTION_H
#define GUARD_KERNEL_INCLUDE_SCHED_SIGACTION_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/sync/atomic-rwlock.h>

#include <asm/os/signal.h>
#include <bits/os/sigaction.h>

#ifndef NSIG
#define NSIG __NSIG
#endif /* !NSIG */

#ifdef __CC__
DECL_BEGIN

/************************************************************************/
/* SIGNAL ACTION DEFINITIONS                                            */
/************************************************************************/

#ifndef __siginfo_t_defined
#define __siginfo_t_defined
struct __siginfo_struct;
typedef struct __siginfo_struct siginfo_t;
#endif /* !__siginfo_t_defined */

struct ucontext;
typedef void (*user_sighandler_func_t)(signo_t signo);
typedef void (*user_sigaction_func_t)(signo_t signo, siginfo_t *info, struct ucontext *ctx);
typedef void (*user_sigrestore_func_t)(void);


struct kernel_sigaction_ { /* TODO: Remove me once kernel's sizeof(sigset_t) gets reduced */
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
	struct atomic_rwlock     sh_lock;              /* Lock for this signal handler descriptor. */
	WEAK refcnt_t            sh_share;             /* [lock(INC(sh_lock), DEC(ATOMIC))]
	                                                * Amount of unrelated processes sharing this sighand. */
	struct kernel_sigaction_ sh_actions[NSIG - 1]; /* Signal handlers. */
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
	WEAK refcnt_t        sp_refcnt; /* Amount of threads using `sp_hand' */
	struct atomic_rwlock sp_lock;   /* Lock for the `sp_hand' pointer. */
	/* TODO: Couldn't this structure be implemented much more nicely with `AXREF()'? */
	REF struct sighand  *sp_hand;   /* [0..1][ref(sh_share)][lock(sp_lock,WRITE_ONCE[ALLOW_EXCHANGE])]
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
FUNDEF WUNUSED NONNULL((1)) struct sighand *KCALL
sighand_ptr_lockread(struct sighand_ptr *__restrict ptr)
		THROWS(E_WOULDBLOCK);
FUNDEF ATTR_RETNONNULL WUNUSED struct sighand *KCALL
sighand_ptr_lockwrite(void) THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Return the default action to perform when faced with `signo' configured as `SIG_DFL'
 * @return: * : One of `SIG_*' (excluding `SIG_DFL' and `SIG_GET') */
FUNDEF NOBLOCK ATTR_CONST WUNUSED user_sighandler_func_t
NOTHROW(KCALL sighand_default_action)(signo_t signo);


/* Reset  the current handler for `signo' when  `current_action' matches the currently set action.
 * This function should be called by kernel-space signal delivery implementations to implement the
 * behavior of `SA_RESETHAND' when handling a signal.
 * @return: true:  Successfully reset the handler
 * @return: false: The given `current_action' didn't match the currently set action. */
FUNDEF bool KCALL
sighand_reset_handler(signo_t signo,
                      struct kernel_sigaction_ const *__restrict current_action)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SIGACTION_H */
