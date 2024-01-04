/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_SCHED_SIGACTION_H
#define GUARD_KERNEL_INCLUDE_SCHED_SIGACTION_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <hybrid/sched/atomic-rwlock.h>

#include <asm/os/signal.h>
#include <bits/os/sigaction.h> /* `struct kernel_sigaction' */

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

#ifndef __sighandler_t_defined
#define __sighandler_t_defined
typedef __sighandler_t sighandler_t;
#endif /* !__sighandler_t_defined */

struct sighand {
	/* Descriptor for how signals ought to be handled. */
	struct atomic_rwlock    sh_lock;              /* Lock for this signal handler descriptor. */
	WEAK refcnt_t           sh_share;             /* [lock(INC(sh_lock), DEC(ATOMIC))]
	                                               * Amount of unrelated processes sharing this sighand. */
	struct kernel_sigaction sh_actions[NSIG - 1]; /* Signal handlers. */
};

/* Helper macros for working with `struct sighand::sh_lock' */
#define _sighand_reap(self)        (void)0
#define sighand_reap(self)         (void)0
#define sighand_mustreap(self)     0
#define sighand_write(self)        atomic_rwlock_write(&(self)->sh_lock)
#define sighand_write_nx(self)     atomic_rwlock_write_nx(&(self)->sh_lock)
#define sighand_trywrite(self)     atomic_rwlock_trywrite(&(self)->sh_lock)
#define sighand_endwrite(self)     (atomic_rwlock_endwrite(&(self)->sh_lock), sighand_reap(self))
#define _sighand_endwrite(self)    atomic_rwlock_endwrite(&(self)->sh_lock)
#define sighand_read(self)         atomic_rwlock_read(&(self)->sh_lock)
#define sighand_read_nx(self)      atomic_rwlock_read_nx(&(self)->sh_lock)
#define sighand_tryread(self)      atomic_rwlock_tryread(&(self)->sh_lock)
#define _sighand_endread(self)     atomic_rwlock_endread(&(self)->sh_lock)
#define sighand_endread(self)      (void)(atomic_rwlock_endread_ex(&(self)->sh_lock) && (sighand_reap(self), 0))
#define _sighand_end(self)         atomic_rwlock_end(&(self)->sh_lock)
#define sighand_end(self)          (void)(atomic_rwlock_end_ex(&(self)->sh_lock) && (sighand_reap(self), 0))
#define sighand_upgrade(self)      atomic_rwlock_upgrade(&(self)->sh_lock)
#define sighand_upgrade_nx(self)   atomic_rwlock_upgrade_nx(&(self)->sh_lock)
#define sighand_tryupgrade(self)   atomic_rwlock_tryupgrade(&(self)->sh_lock)
#define sighand_downgrade(self)    atomic_rwlock_downgrade(&(self)->sh_lock)
#define sighand_reading(self)      atomic_rwlock_reading(&(self)->sh_lock)
#define sighand_writing(self)      atomic_rwlock_writing(&(self)->sh_lock)
#define sighand_canread(self)      atomic_rwlock_canread(&(self)->sh_lock)
#define sighand_canwrite(self)     atomic_rwlock_canwrite(&(self)->sh_lock)
#define sighand_waitread(self)     atomic_rwlock_waitread(&(self)->sh_lock)
#define sighand_waitwrite(self)    atomic_rwlock_waitwrite(&(self)->sh_lock)
#define sighand_waitread_nx(self)  atomic_rwlock_waitread_nx(&(self)->sh_lock)
#define sighand_waitwrite_nx(self) atomic_rwlock_waitwrite_nx(&(self)->sh_lock)

#ifndef ____os_free_defined
#define ____os_free_defined
FUNDEF NOBLOCK void NOTHROW(KCALL __os_free)(VIRT void *ptr) ASMNAME("kfree");
#endif /* !____os_free_defined */
#define sighand_destroy(self) __os_free(self)

#define sighand_incshare(self) \
	__hybrid_atomic_inc(&(self)->sh_share, __ATOMIC_SEQ_CST)
#define sighand_decshare(self)                                              \
	(void)(__hybrid_atomic_decfetch(&(self)->sh_share, __ATOMIC_SEQ_CST) || \
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
	REF struct sighand  *sp_hand;   /* [0..1][ref(sh_share)][lock(sp_lock,WRITE_ONCE[ALLOW_EXCHANGE])]
	                                 * Pointer to the shared signal handler table. */
};

/* Helper macros for working with `struct sighand_ptr::sp_lock' */
#define _sighand_ptr_reap(self)        (void)0
#define sighand_ptr_reap(self)         (void)0
#define sighand_ptr_mustreap(self)     0
#define sighand_ptr_write(self)        atomic_rwlock_write(&(self)->sp_lock)
#define sighand_ptr_write_nx(self)     atomic_rwlock_write_nx(&(self)->sp_lock)
#define sighand_ptr_trywrite(self)     atomic_rwlock_trywrite(&(self)->sp_lock)
#define sighand_ptr_endwrite(self)     (atomic_rwlock_endwrite(&(self)->sp_lock), sighand_ptr_reap(self))
#define _sighand_ptr_endwrite(self)    atomic_rwlock_endwrite(&(self)->sp_lock)
#define sighand_ptr_read(self)         atomic_rwlock_read(&(self)->sp_lock)
#define sighand_ptr_read_nx(self)      atomic_rwlock_read_nx(&(self)->sp_lock)
#define sighand_ptr_tryread(self)      atomic_rwlock_tryread(&(self)->sp_lock)
#define _sighand_ptr_endread(self)     atomic_rwlock_endread(&(self)->sp_lock)
#define sighand_ptr_endread(self)      (void)(atomic_rwlock_endread_ex(&(self)->sp_lock) && (sighand_ptr_reap(self), 0))
#define _sighand_ptr_end(self)         atomic_rwlock_end(&(self)->sp_lock)
#define sighand_ptr_end(self)          (void)(atomic_rwlock_end_ex(&(self)->sp_lock) && (sighand_ptr_reap(self), 0))
#define sighand_ptr_upgrade(self)      atomic_rwlock_upgrade(&(self)->sp_lock)
#define sighand_ptr_upgrade_nx(self)   atomic_rwlock_upgrade_nx(&(self)->sp_lock)
#define sighand_ptr_tryupgrade(self)   atomic_rwlock_tryupgrade(&(self)->sp_lock)
#define sighand_ptr_downgrade(self)    atomic_rwlock_downgrade(&(self)->sp_lock)
#define sighand_ptr_reading(self)      atomic_rwlock_reading(&(self)->sp_lock)
#define sighand_ptr_writing(self)      atomic_rwlock_writing(&(self)->sp_lock)
#define sighand_ptr_canread(self)      atomic_rwlock_canread(&(self)->sp_lock)
#define sighand_ptr_canwrite(self)     atomic_rwlock_canwrite(&(self)->sp_lock)
#define sighand_ptr_waitread(self)     atomic_rwlock_waitread(&(self)->sp_lock)
#define sighand_ptr_waitwrite(self)    atomic_rwlock_waitwrite(&(self)->sp_lock)
#define sighand_ptr_waitread_nx(self)  atomic_rwlock_waitread_nx(&(self)->sp_lock)
#define sighand_ptr_waitwrite_nx(self) atomic_rwlock_waitwrite_nx(&(self)->sp_lock)


FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL sighand_ptr_destroy)(struct sighand_ptr *__restrict self);
DEFINE_REFCNT_FUNCTIONS(struct sighand_ptr, sp_refcnt, sighand_ptr_destroy)

/* [0..1][lock(PRIVATE(THIS_TASK))]
 * User-space signal handlers for the calling thread. */
/* TODO: This field should be changed to [1..1] */
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
 * >>     sighand_endread(h);
 * >> } else {
 * >>     ...  // Use default behavior (s.a. `sighand_default_action()')
 * >> }
 * For writing:
 * >> h = sighand_ptr_lockwrite();
 * >> ...
 * >> sighand_endwrite(h);
 * With that in mind, these function will perform the necessary unsharing  of
 * copy-on-write signal handler  tables, while still  keeping association  of
 * handlers in check when it comes to shared handler tables, as usually found
 * within the same process. */
FUNDEF WUNUSED NONNULL((1)) struct sighand *FCALL
sighand_ptr_lockread(struct sighand_ptr *__restrict ptr)
		THROWS(E_WOULDBLOCK);
FUNDEF ATTR_RETNONNULL WUNUSED struct sighand *FCALL
sighand_ptr_lockwrite(void)
		THROWS(E_WOULDBLOCK, E_BADALLOC);

/* Return the default action to perform when faced with `signo' configured as `SIG_DFL'
 * @return: * : One of `SIG_*' (excluding `SIG_DFL' and `SIG_GET') */
FUNDEF NOBLOCK ATTR_CONST WUNUSED sighandler_t
NOTHROW(FCALL sighand_default_action)(signo_t signo);


/* Reset  the current handler for `signo' when  `current_action' matches the currently set action.
 * This function should be called by kernel-space signal delivery implementations to implement the
 * behavior of `SA_RESETHAND' when handling a signal.
 * @return: true:  Successfully reset the handler
 * @return: false: The given `current_action' didn't match the currently set action. */
FUNDEF WUNUSED NONNULL((2)) bool FCALL
sighand_reset_handler(signo_t signo, struct kernel_sigaction const *__restrict current_action)
		THROWS(E_WOULDBLOCK, E_BADALLOC);


/* Copies the calling thread's action for `signo' into `*action' */
FUNDEF NONNULL((2)) void FCALL
sighand_getaction(signo_t signo, struct kernel_sigaction *__restrict action)
		THROWS(E_WOULDBLOCK);
FUNDEF ATTR_PURE WUNUSED sighandler_t FCALL
sighand_gethandler(signo_t signo)
		THROWS(E_WOULDBLOCK);



DECL_END
#endif /* __CC__ */


#endif /* !GUARD_KERNEL_INCLUDE_SCHED_SIGACTION_H */
