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
#ifndef GUARD_KERNEL_SRC_SCHED_SIGACTION_C
#define GUARD_KERNEL_SRC_SCHED_SIGACTION_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/mman/event.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/pertask.h>
#include <sched/sigaction.h>
#include <sched/sigmask.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/minmax.h>
#include <hybrid/sched/atomic-lock.h>

#include <bits/os/sigaction.h>
#include <compat/config.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>

#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stdalign.h>
#include <stddef.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/os/sigaction.h>
#include <compat/kos/types.h>
#include <compat/pointer.h>
#include <compat/signal.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

/* [0..1][valid_if(!TASK_FKERNTHREAD)][lock(PRIVATE(THIS_TASK))]
 * User-space  signal   handlers   for   the   calling   thread. */
PUBLIC ATTR_PERTASK ATTR_ALIGN(REF struct sighand_ptr *) this_sighand_ptr = NULL;

DEFINE_PERTASK_FINI(fini_this_sighand_ptr);
PRIVATE NOBLOCK ATTR_USED NONNULL((1)) void
NOTHROW(KCALL fini_this_sighand_ptr)(struct task *__restrict thread) {
	xdecref(FORTASK(thread, this_sighand_ptr));
}


/* Lock for accessing any remote thread's this_sighand_ptr field */
#ifndef CONFIG_NO_SMP
PRIVATE struct atomic_lock sighand_ptr_change_lock = ATOMIC_LOCK_INIT;
#endif /* !CONFIG_NO_SMP */
#define sighand_ptr_change_lock_acquire() atomic_lock_acquire_smp(&sighand_ptr_change_lock)
#define sighand_ptr_change_lock_release() atomic_lock_release_smp(&sighand_ptr_change_lock)

/* Return the sighand pointer of the given thread. */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) REF struct sighand_ptr *
NOTHROW(FCALL task_getsighand_ptr)(struct task *__restrict thread) {
	REF struct sighand_ptr *result;
	sighand_ptr_change_lock_acquire();
	assert(FORTASK(thread, this_sighand_ptr));
	result = xincref(FORTASK(thread, this_sighand_ptr));
	sighand_ptr_change_lock_release();
	return result;
}

/* Exchange the sighand pointer of the calling thread. */
PUBLIC WUNUSED REF struct sighand_ptr *
NOTHROW(FCALL task_setsighand_ptr)(struct sighand_ptr *newsighand_ptr) {
	REF struct sighand_ptr *result;
	sighand_ptr_change_lock_acquire();
	result = PERTASK_GET(this_sighand_ptr);
	xincref(newsighand_ptr);
	PERTASK_SET(this_sighand_ptr, newsighand_ptr);
	sighand_ptr_change_lock_release();
	return result;
}



PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL sighand_ptr_destroy)(struct sighand_ptr *__restrict self) {
	if (self->sp_hand)
		sighand_decshare(self->sp_hand);
	kfree(self);
}




/* Acquire a lock to the underlying signal handler table that is associated
 * with the  given  `sighand_ptr',  either for  reading,  or  for  writing.
 * For reading:
 * >> struct sighand *h;
 * >> h = sighand_ptr_lockread(THIS_SIGHAND_PTR);
 * >> ...
 * >> sighand_endread(h);
 * For writing:
 * >> h = sighand_ptr_lockwrite();
 * >> ...
 * >> sighand_endwrite(h);
 * With that in mind, these function will perform the necessary unsharing  of
 * copy-on-write signal handler  tables, while still  keeping association  of
 * handlers in check when it comes to shared handler tables, as usually found
 * within the same process. */
PUBLIC WUNUSED NONNULL((1)) struct sighand *FCALL
sighand_ptr_lockread(struct sighand_ptr *__restrict ptr)
		THROWS(E_WOULDBLOCK) {
	struct sighand *result;
	bool lock_ok = true;
again:
	sighand_ptr_read(ptr);
	COMPILER_READ_BARRIER();
	result = ptr->sp_hand;
	COMPILER_READ_BARRIER();
	if (result != NULL)
		lock_ok = sighand_tryread(result);
	sighand_ptr_endread(ptr);
	if (!lock_ok) {
		task_yield();
		goto again;
	}
	return result;
}

PUBLIC ATTR_RETNONNULL WUNUSED struct sighand *FCALL
sighand_ptr_lockwrite(void) THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct sighand *result;
	struct sighand_ptr *ptr;
	bool lock_ok;
again_read_thread_ptr:
	ptr = THIS_SIGHAND_PTR;
	if (!ptr) {
		/* No handlers allocated (yet).  - Allocate it now  as an empty handler  table.
		 * NOTE: this can easily be done by zero-initializing the signal handler table. */
		result = (struct sighand *)kmalloc(sizeof(struct sighand), GFP_CALLOC);
		TRY {
			ptr = (struct sighand_ptr *)kmalloc(sizeof(struct sighand_ptr), GFP_NORMAL);
		} EXCEPT {
			kfree(result);
			RETHROW();
		}
		ptr->sp_hand = result;
		atomic_rwlock_cinit_write(&result->sh_lock);
		result->sh_share = 1;
		ptr->sp_refcnt = 1;
		atomic_rwlock_init(&ptr->sp_lock);
		if (!ATOMIC_CMPXCH(PERTASK(this_sighand_ptr), NULL, ptr)) {
			COMPILER_READ_BARRIER();
			/* Race condition: someone else already allocated the sighand_ptr for `thread' */
			kfree(result);
			kfree(ptr);
			goto again_read_thread_ptr;
		}
		return result;
	}
again_lock_ptr:
	sighand_ptr_read(ptr);
	COMPILER_READ_BARRIER();
	result = ptr->sp_hand;
	COMPILER_READ_BARRIER();
	if (!result) {
		sighand_ptr_endread(ptr);
		/* Lazily allocate the signal handler table. */
		result = (struct sighand *)kmalloc(sizeof(struct sighand), GFP_CALLOC);
		atomic_rwlock_cinit_write(&result->sh_lock); /* Init in write-mode */
		result->sh_share = 1;
		TRY {
			sighand_ptr_write(ptr);
		} EXCEPT {
			kfree(result);
			RETHROW();
		}
		COMPILER_BARRIER();
		if likely(!ptr->sp_hand) {
			ptr->sp_hand = result;
			sighand_ptr_endwrite(ptr);
			return result;
		}
		/* Race condition: another thread also allocated the handler table in the mean time! */
		sighand_ptr_endwrite(ptr);
		kfree(result);
		goto again_lock_ptr;
	}

	/* Got the handler table! - Now to lock it. */
	lock_ok = sighand_trywrite(result);
	sighand_ptr_endread(ptr);
	if (!lock_ok) {
		task_yield();
		goto again_lock_ptr;
	}

	/* At  this point we have a write-lock to the handler table.
	 * Now we must verify that the table isn't being shared, and
	 * if it is being shared, we must unshare it and replace  it
	 * with a copy. */
	if (ATOMIC_READ(result->sh_share) > 1) {
		struct sighand *copy;
		sighand_endwrite(result);
		copy = (struct sighand *)kmalloc(sizeof(struct sighand), GFP_NORMAL);
		TRY {
again_lock_ptr_for_copy:
			sighand_ptr_write(ptr);
			COMPILER_READ_BARRIER();
			result = ptr->sp_hand;
			COMPILER_READ_BARRIER();
			if (!sighand_tryread(result)) {
				sighand_ptr_endwrite(ptr);
				task_yield();
				goto again_lock_ptr_for_copy;
			}
			if unlikely(ATOMIC_READ(result->sh_share) <= 1) {
				/* The handler table already got unshared in the mean time...
				 * No need to initialize + save our copy! */
				sighand_ptr_endwrite(ptr);
				if (!sighand_tryupgrade(result)) {
					sighand_endread(result);
					kfree(copy);
					task_yield();
					goto again_lock_ptr;
				}
				kfree(copy);
				return result;
			}
			/* Initialize the new copy as a duplicate of the old handler table. */
			memcpy(copy->sh_actions, result->sh_actions, sizeof(result->sh_actions));
			sighand_endread(result);
			copy->sh_share = 1; /* Only 1 sighand_ptr will use this copy (for now) */
			atomic_rwlock_init_write(&copy->sh_lock);
			/* Store the copy in the thread-local sighand_ptr */
			COMPILER_WRITE_BARRIER();
			ptr->sp_hand = copy;
			COMPILER_WRITE_BARRIER();
			sighand_ptr_endwrite(ptr);
		} EXCEPT {
			kfree(copy);
			RETHROW();
		}
		/* NOTE: At this point we're still holding a write-lock to `copy',
		 *       which we're eventually going to propagate to the  caller. */
		/* Drop the share reference from the old handler table. */
		sighand_decshare(result);
		/* Return newly constructed copy of the handler table. */
		result = copy;
	}
	return result;
}


/* Return the default action to perform when faced with `signo' configured as `SIG_DFL'
 * @return: * : One of `SIG_*' (excluding `SIG_DFL' and `SIG_GET') */
PUBLIC NOBLOCK ATTR_CONST WUNUSED sighandler_t
NOTHROW(FCALL sighand_default_action)(signo_t signo) {
	sighandler_t result;
	result = SIG_IGN;
	switch (signo) {

	case SIGQUIT:
	case SIGILL:
	case SIGABRT:
	case SIGFPE:
	case SIGSEGV:
	case SIGBUS:
	case SIGSYS:
	case SIGTRAP:
	case SIGXCPU:
	case SIGXFSZ:
#if defined(SIGIOT) && SIGIOT != SIGABRT
	case SIGIOT:
#endif /* SIGIOT != SIGABRT */
#if defined(SIGUNUSED) && SIGUNUSED != SIGSYS
	case SIGUNUSED:
#endif /* SIGUNUSED != SIGSYS */
		result = SIG_CORE;
		break;

	case SIGHUP:
	case SIGINT:
	case SIGKILL:
	case SIGPIPE:
	case SIGALRM:
	case SIGTERM:
	case SIGUSR1:
	case SIGUSR2:
	case SIGPOLL:
	case SIGPROF:
	case SIGVTALRM:
#ifdef SIGEMT
	case SIGEMT:
#endif /* SIGEMT */
	case SIGSTKFLT:
#if defined(SIGIO) && SIGIO != SIGPOLL
	case SIGIO:
#endif /* SIGIO != SIGPOLL */
	case SIGPWR:
#ifdef SIGLOST
	case SIGLOST:
#endif /* SIGLOST */
		result = SIG_TERM;
		break;

	case SIGCONT:
		result = SIG_CONT;
		break;

	case SIGSTOP:
	case SIGTSTP:
	case SIGTTIN:
	case SIGTTOU:
		result = SIG_STOP;
		break;

	default: break;
	}
	return result;
}

/* Copies the calling thread's action for `signo' into `*action' */
PUBLIC NONNULL((2)) void FCALL
sighand_getaction(signo_t signo, struct kernel_sigaction *__restrict action)
		THROWS(E_WOULDBLOCK) {
	struct sighand_ptr *ptr;
	assert(sigvalid(signo));
	ptr = THIS_SIGHAND_PTR;
	if (!ptr) {
default_sighand:
		action->sa_handler = SIG_DFL;
		action->sa_flags   = 0;
		sigemptyset(&action->sa_mask);
	} else {
		struct sighand *hand;
		hand = sighand_ptr_lockread(ptr);
		if unlikely(!hand)
			goto default_sighand;
		memcpy(action, &hand->sh_actions[signo - 1],
		       sizeof(struct kernel_sigaction));
		sighand_endread(hand);
	}
}

PUBLIC ATTR_PURE WUNUSED sighandler_t FCALL
sighand_gethandler(signo_t signo)
		THROWS(E_WOULDBLOCK) {
	sighandler_t result = SIG_DFL;
	struct sighand_ptr *ptr;
	struct sighand *hand;
	assert(sigvalid(signo));
	ptr = THIS_SIGHAND_PTR;
	if (ptr == NULL)
		goto done;
	hand = sighand_ptr_lockread(ptr);
	if (hand == NULL)
		goto done;
	result = hand->sh_actions[signo - 1].sa_handler;
	sighand_endread(hand);
done:
	return result;
}





/* Reset  the current handler for `signo' when  `current_action' matches the currently set action.
 * This function should be called by kernel-space signal delivery implementations to implement the
 * behavior of `SA_RESETHAND' when handling a signal.
 * @return: true:  Successfully reset the handler
 * @return: false: The given `current_action' didn't match the currently set action. */
PUBLIC WUNUSED NONNULL((2)) bool FCALL
sighand_reset_handler(signo_t signo,
                      struct kernel_sigaction const *__restrict current_action)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct sighand *hand;
	assert(sigvalid(signo));
	if unlikely(!THIS_SIGHAND_PTR)
		return false;
	hand = sighand_ptr_lockwrite();
	if (bcmp(current_action,
	         &hand->sh_actions[signo - 1],
	         sizeof(struct kernel_sigaction)) != 0) {
		sighand_endwrite(hand);
		return false;
	}

	/* Reset the action. */
	bzero(&hand->sh_actions[signo - 1], sizeof(struct kernel_sigaction));
	sighand_endwrite(hand);
	return true;
}



/* Check  if  `self' contains  any handlers  set to
 * SIG_IGN that wouldn't be set as such by default. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL sighand_has_nondefault_sig_ign)(struct sighand const *__restrict self) {
	unsigned int i;
	for (i = 0; i < lengthof(self->sh_actions); ++i) {
		/* Check if the handler's action is SIG_IGN */
		if (self->sh_actions[i].sa_handler != SIG_IGN)
			continue; /* Something other than SIG_IGN */
		/* Check if the default action is something other than SIG_IGN */
		if (sighand_default_action(i + 1) == SIG_IGN)
			continue; /* Default would also be SIG_IGN */
		/* Found one! */
		return true;
	}
	return false;
}


/* During exec(), all signal handler dispositions of the calling thread are reset */
DEFINE_PERMMAN_ONEXEC(onexec_posix_signals_reset_action);
INTERN void KCALL onexec_posix_signals_reset_action(void) {
	REF struct sighand_ptr *handptr;
	/* Posix says that signals set to SIG_IGN should remain SIG_IGN after exec(). */
	handptr = ATOMIC_XCH(PERTASK(this_sighand_ptr), NULL);
	if (handptr) {
		struct sighand *hand;
		REF struct sighand *newhand;
		unsigned int i;
		hand = sighand_ptr_lockread(handptr);
		if unlikely(!hand)
			goto done_handptr;
		/* Check if there are any signals set to SIG_IGN, for which
		 * `sighand_default_action()'   returns   something   else. */
		if (!sighand_has_nondefault_sig_ign(hand)) {
			sighand_endread(hand);
			goto done_handptr;
		}
		/* We have to create a new, custom set of signal handlers... */
		/* NOTE: Use GFP_CALLOC  because  `SIG_DFL = 0',  and  we  only
		 *       need to inherit handlers that were marked as `SIG_IGN' */
		newhand = (REF struct sighand *)kmalloc_nx(sizeof(struct sighand),
		                                           GFP_CALLOC | GFP_ATOMIC);
		if (!newhand) {
			sighand_endread(hand);
			newhand = (REF struct sighand *)kmalloc(sizeof(struct sighand), GFP_CALLOC);
			TRY {
				hand = sighand_ptr_lockread(handptr);
			} EXCEPT {
				kfree(newhand);
				assert(!PERTASK_TEST(this_sighand_ptr));
				PERTASK_SET(this_sighand_ptr, handptr);
				RETHROW();
			}
			if unlikely(!hand) {
				kfree(newhand);
				goto done_handptr;
			}
			if (sighand_has_nondefault_sig_ign(hand)) {
				sighand_endread(hand);
				kfree(newhand);
				goto done_handptr;
			}
		}
		/* Copy handlers that have their disposition set to SIG_IGN.
		 * However,  don't copy anything  else about those handlers,
		 * or any other handlers for that matter.
		 * Especially of note is that we also don't copy signal masks,
		 * since  those wouldn't actually matter for SIG_IGN handlers. */
		for (i = 0; i < lengthof(hand->sh_actions); ++i) {
			if (hand->sh_actions[i].sa_handler == SIG_IGN)
				newhand->sh_actions[i].sa_handler = SIG_IGN;
		}
		atomic_rwlock_cinit(&newhand->sh_lock);
		newhand->sh_share = 1;
		sighand_endread(hand);
		if (!isshared(handptr)) {
			/* We can re-use `handptr' to point to `newhand' */
			TRY {
				/* This really shouldn't block since handptr isn't shared.
				 * ... But better to be safe than sorry. */
				sighand_ptr_write(handptr);
			} EXCEPT {
				kfree(newhand);
				decref(handptr);
				assert(!PERTASK_TEST(this_sighand_ptr));
				PERTASK_SET(this_sighand_ptr, handptr);
				RETHROW();
			}
			assert(!isshared(handptr));
			hand = handptr->sp_hand;    /* Inherit reference */
			handptr->sp_hand = newhand; /* Inherit reference */
			sighand_ptr_endwrite(handptr);
			/* Restore the old hand-pointer for the calling thread. */
			assert(!PERTASK_TEST(this_sighand_ptr));
			PERTASK_SET(this_sighand_ptr, handptr);
			/* Now that we're  using `newhand',  drop
			 * our shared reference from the original */
			sighand_decshare(hand);
		} else {
			/* Must allocate a new `handptr' */
			REF struct sighand_ptr *newhandptr;
			TRY {
				newhandptr = (REF struct sighand_ptr *)kmalloc(sizeof(struct sighand_ptr),
				                                               GFP_NORMAL);
			} EXCEPT {
				kfree(newhand);
				decref(handptr);
				assert(!PERTASK_TEST(this_sighand_ptr));
				PERTASK_SET(this_sighand_ptr, handptr);
				RETHROW();
			}
			newhandptr->sp_refcnt = 1;
			atomic_rwlock_init(&newhandptr->sp_lock);
			newhandptr->sp_hand = newhand; /* Inherit reference */
			assert(!PERTASK_TEST(this_sighand_ptr));
			PERTASK_SET(this_sighand_ptr, newhandptr); /* Inherit reference */
done_handptr:
			decref(handptr);
		}
	}
}



/************************************************************************/
/* sigaction(), rt_sigaction(), signal()                                */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_SIGACTION) ||           \
     defined(__ARCH_WANT_SYSCALL_RT_SIGACTION) ||        \
     defined(__ARCH_WANT_SYSCALL_SIGNAL) ||              \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SIGACTION) ||    \
     defined(__ARCH_WANT_COMPAT_SYSCALL_RT_SIGACTION) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SIGNAL))
#define WANT_SIGACTION 1
#endif /* ... */

#ifdef WANT_SIGACTION
PRIVATE void KCALL
sys_sigaction_impl(signo_t signo,
                   CHECKED USER struct kernel_sigaction const *act,
                   CHECKED USER struct kernel_sigaction *oact,
                   size_t sigsetsize) {
	struct kernel_sigaction ohandler;
	struct sighand *hand;
	size_t overflow = 0;
	if (sigsetsize > sizeof(sigset_t)) {
		overflow   = sigsetsize - sizeof(sigset_t);
		sigsetsize = sizeof(sigset_t);
	}
	if unlikely(!sigvalid(signo)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_BAD_SIGNO,
		      signo);
	}
	if (!act) {
		if (oact) {
			struct sighand_ptr *handptr;
			handptr = THIS_SIGHAND_PTR;
			if (handptr) {
				hand = sighand_ptr_lockread(handptr);
				if (!hand)
					goto no_old_handler;
				memcpy(&ohandler, &hand->sh_actions[signo - 1],
				       sizeof(struct kernel_sigaction));
				sighand_endread(hand);
copy_old_handler:
				COMPILER_WRITE_BARRIER();
				memset(mempcpy(oact, &ohandler,
				               offsetof(struct kernel_sigaction, sa_mask) +
				               sigsetsize),
				       0xff, overflow);
				COMPILER_WRITE_BARRIER();
			} else {
no_old_handler:
				bzero(oact, sizeof(*oact));
			}
		}
	} else {
		struct kernel_sigaction nhandler;
		memset(mempcpy(&nhandler, act, offsetof(struct kernel_sigaction, sa_mask) + sigsetsize),
		       0xff, sizeof(sigset_t) - sigsetsize);
		COMPILER_READ_BARRIER();
#ifndef KERNELSPACE_HIGHMEM
		if ((uintptr_t)nhandler.sa_handler >= __SIG_GET)
#endif /* !KERNELSPACE_HIGHMEM */
		{
			validate_executable((void const *)nhandler.sa_handler);
		}
#ifdef __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER
		if (nhandler.sa_flags & SA_RESTORER)
			validate_executable((void const *)nhandler.sa_restorer);
#endif /* __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER */
		VALIDATE_FLAGSET(nhandler.sa_flags,
		                 SA_NOCLDSTOP | SA_NOCLDWAIT | SA_SIGINFO |
		                 SA_RESTORER | SA_ONSTACK | SA_RESTART |
		                 SA_NODEFER | SA_RESETHAND | SA_INTERRUPT,
		                 E_INVALID_ARGUMENT_CONTEXT_SIGACTION_ACT_FLAGS);

		/* Actually change signal actions. */
		hand = sighand_ptr_lockwrite();
		memcpy(&ohandler, &hand->sh_actions[signo - 1], sizeof(struct kernel_sigaction));
		memcpy(&hand->sh_actions[signo - 1], &nhandler, sizeof(struct kernel_sigaction));
		sighand_endwrite(hand);

		/* Check if user-space also wants to get the old action. */
		if (oact != NULL)
			goto copy_old_handler;
	}
}
#endif /* WANT_SIGACTION */

#ifdef __ARCH_WANT_SYSCALL_RT_SIGACTION
DEFINE_SYSCALL4(errno_t, rt_sigaction, signo_t, signo,
                UNCHECKED USER struct kernel_sigaction const *, act,
                UNCHECKED USER struct kernel_sigaction *, oact,
                size_t, sigsetsize) {
	/* Validate user-structure pointers. */
	validate_readable_opt(act, offsetof(struct kernel_sigaction, sa_mask) + sigsetsize);
	validate_writable_opt(oact, offsetof(struct kernel_sigaction, sa_mask) + sigsetsize);
	sys_sigaction_impl(signo, act, oact, sigsetsize);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGACTION */

#ifdef __ARCH_WANT_SYSCALL_SIGACTION
DEFINE_SYSCALL3(errno_t, sigaction, signo_t, signo,
                UNCHECKED USER struct __old_kernel_sigaction const *, old_act,
                UNCHECKED USER struct __old_kernel_sigaction *, old_oact) {
	alignas(alignof(struct kernel_sigaction))
	byte_t _buf_act[offsetof(struct kernel_sigaction, sa_mask) +
	                sizeof(struct __old_sigset_struct)];
	alignas(alignof(struct kernel_sigaction))
	byte_t _buf_oact[offsetof(struct kernel_sigaction, sa_mask) +
	                 sizeof(struct __old_sigset_struct)];
	struct kernel_sigaction *act  = NULL;
	struct kernel_sigaction *oact = NULL;
	if (old_act != NULL) {
		validate_readable(old_act, sizeof(*old_act));
		act = (struct kernel_sigaction *)_buf_act;
		act->sa_handler = (typeof(act->sa_handler))(uintptr_t)(void *)old_act->sa_handler;
		act->sa_flags   = (typeof(act->sa_flags))old_act->sa_flags;
#ifdef __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER
		act->sa_restorer = (typeof(act->sa_restorer))(uintptr_t)(void *)old_act->sa_restorer;
#endif /* __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER */
		memcpy(&act->sa_mask, &old_act->sa_mask, sizeof(struct __old_sigset_struct));
	}
	if (old_oact != NULL) {
		validate_writable(old_oact, sizeof(*old_oact));
		oact = (struct kernel_sigaction *)_buf_oact;
	}
	sys_sigaction_impl(signo, act, oact, sizeof(struct __old_sigset_struct));
	if (old_oact != NULL) {
		old_oact->sa_handler = (typeof(old_oact->sa_handler))(uintptr_t)(void *)oact->sa_handler;
		old_oact->sa_flags   = (typeof(old_oact->sa_flags))oact->sa_flags;
#ifdef __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER
		old_oact->sa_restorer = (typeof(old_oact->sa_restorer))(uintptr_t)(void *)oact->sa_restorer;
#endif /* __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER */
		memcpy(&old_oact->sa_mask, &oact->sa_mask, sizeof(struct __old_sigset_struct));
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SIGACTION */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RT_SIGACTION
DEFINE_COMPAT_SYSCALL4(compat_errno_t, rt_sigaction, compat_signo_t, signo,
                       UNCHECKED USER struct __compat_kernel_sigaction const *, compat_act,
                       UNCHECKED USER struct __compat_kernel_sigaction *, compat_oact,
                       size_t, sigsetsize) {
	size_t overflow = 0;
	struct kernel_sigaction _buf_act, _buf_oact;
	struct kernel_sigaction *act  = NULL;
	struct kernel_sigaction *oact = NULL;

	/* Figure out the offsets of fields in `struct __compat_kernel_sigaction' */
#define CALCULATE_OFFSETOF(field)                              \
	(offsetof(struct __compat_kernel_sigaction, field) >       \
	 offsetof(struct __compat_kernel_sigaction, sa_mask)       \
	 ? (offsetof(struct __compat_kernel_sigaction, sa_mask) +  \
	    sigsetsize +                                           \
	    (offsetof(struct __compat_kernel_sigaction, field) -   \
	     offsetof(struct __compat_kernel_sigaction, sa_mask))) \
	 : offsetof(struct __compat_kernel_sigaction, field))
	size_t const offsetof_sa_mask = offsetof(struct __compat_kernel_sigaction, sa_mask);
	size_t offsetof_sa_handler    = CALCULATE_OFFSETOF(sa_handler);
	size_t offsetof_sa_flags      = CALCULATE_OFFSETOF(sa_flags);
#ifdef __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER
	size_t offsetof_sa_restorer = CALCULATE_OFFSETOF(sa_restorer);
#endif /* __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER */
#undef CALCULATE_OFFSETOF

	/* Access the named field of a `struct __compat_kernel_sigaction *self' */
#define compat_kernel_sigaction_field(self, field) \
	(*((typeof(&((struct __compat_kernel_sigaction *)0)->field))((byte_t *)(self) + offsetof_##field)))

	/* Limit how large the sigsets we accept can get. */
	if (sigsetsize > sizeof(sigset_t)) {
		overflow   = sigsetsize - sizeof(sigset_t);
		sigsetsize = sizeof(sigset_t);
	}
	if (compat_act != NULL) {
		validate_readable(compat_act, sizeof(*compat_act));
		act = &_buf_act;
		act->sa_handler = (typeof(act->sa_handler))(uintptr_t)(void *)compat_kernel_sigaction_field(compat_act, sa_handler);
		act->sa_flags   = (typeof(act->sa_flags))compat_kernel_sigaction_field(compat_act, sa_flags);
#ifdef __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER
		act->sa_restorer = (typeof(act->sa_restorer))(uintptr_t)(void *)compat_kernel_sigaction_field(compat_act, sa_restorer);
#endif /* __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER */
		memcpy(&act->sa_mask, &compat_kernel_sigaction_field(compat_act, sa_mask), sizeof(struct __old_sigset_struct));
	}
	if (compat_oact != NULL) {
		validate_writable(compat_oact, sizeof(*compat_oact));
		oact = &_buf_oact;
	}
	sys_sigaction_impl(signo, act, oact, sigsetsize);
	if (compat_oact != NULL) {
		compat_kernel_sigaction_field(compat_oact, sa_handler) = (typeof(compat_oact->sa_handler))(uintptr_t)(void *)oact->sa_handler;
		compat_kernel_sigaction_field(compat_oact, sa_flags)   = (typeof(compat_oact->sa_flags))oact->sa_flags;
#ifdef __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER
		compat_kernel_sigaction_field(compat_oact, sa_restorer) = (typeof(compat_oact->sa_restorer))(uintptr_t)(void *)oact->sa_restorer;
#endif /* __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER */
		memset(mempcpy(&compat_kernel_sigaction_field(compat_oact, sa_mask),
		               &oact->sa_mask, sigsetsize),
		       0xff, overflow);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RT_SIGACTION */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SIGACTION
DEFINE_COMPAT_SYSCALL3(compat_errno_t, sigaction, compat_signo_t, signo,
                       UNCHECKED USER struct __compat_old_kernel_sigaction const *, old_act,
                       UNCHECKED USER struct __compat_old_kernel_sigaction *, old_oact) {
	alignas(alignof(struct kernel_sigaction))
	byte_t _buf_act[offsetof(struct kernel_sigaction, sa_mask) +
	                sizeof(struct __old_sigset_struct)];
	alignas(alignof(struct kernel_sigaction))
	byte_t _buf_oact[offsetof(struct kernel_sigaction, sa_mask) +
	                 sizeof(struct __old_sigset_struct)];
	struct kernel_sigaction *act  = NULL;
	struct kernel_sigaction *oact = NULL;
	if (old_act != NULL) {
		validate_readable(old_act, sizeof(*old_act));
		act = (struct kernel_sigaction *)_buf_act;
		act->sa_handler = (typeof(act->sa_handler))(uintptr_t)(void *)old_act->sa_handler;
		act->sa_flags   = (typeof(act->sa_flags))old_act->sa_flags;
#ifdef __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER
		act->sa_restorer = (typeof(act->sa_restorer))(uintptr_t)(void *)old_act->sa_restorer;
#endif /* __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER */
		memcpy(&act->sa_mask, &old_act->sa_mask, sizeof(struct __old_sigset_struct));
	}
	if (old_oact != NULL) {
		validate_writable(old_oact, sizeof(*old_oact));
		oact = (struct kernel_sigaction *)_buf_oact;
	}
	sys_sigaction_impl(signo, act, oact, sizeof(struct __old_sigset_struct));
	if (old_oact != NULL) {
		old_oact->sa_handler = (typeof(old_oact->sa_handler))(uintptr_t)(void *)oact->sa_handler;
		old_oact->sa_flags   = (typeof(old_oact->sa_flags))oact->sa_flags;
#ifdef __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER
		old_oact->sa_restorer = (typeof(old_oact->sa_restorer))(uintptr_t)(void *)oact->sa_restorer;
#endif /* __ARCH_HAVE_KERNEL_SIGACTION_SA_RESTORER */
		memcpy(&old_oact->sa_mask, &oact->sa_mask, sizeof(struct __old_sigset_struct));
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SIGACTION */

#ifdef __ARCH_WANT_SYSCALL_SIGNAL
DEFINE_SYSCALL2(sighandler_t, signal,
                signo_t, signo,
                UNCHECKED USER sighandler_t, handler) {
	alignas(alignof(struct kernel_sigaction))
	byte_t _buf_act[offsetof(struct kernel_sigaction, sa_mask)];
	alignas(alignof(struct kernel_sigaction))
	byte_t _buf_oact[offsetof(struct kernel_sigaction, sa_mask)];
	struct kernel_sigaction *act  = (struct kernel_sigaction *)_buf_act;
	struct kernel_sigaction *oact = (struct kernel_sigaction *)_buf_oact;
	if ((void *)handler == (void *)SIG_GET) {
		sys_sigaction_impl(signo, NULL, oact, 0);
	} else {
		bzero(act, offsetof(struct kernel_sigaction, sa_mask));
		act->sa_handler = (typeof(act->sa_handler))(void *)handler;
		sys_sigaction_impl(signo, act, oact, 0);
	}
	return (sighandler_t)(uintptr_t)(void *)oact->sa_handler;
}
#endif /* __ARCH_WANT_SYSCALL_SIGNAL */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SIGNAL
DEFINE_COMPAT_SYSCALL2(compat_sighandler_t, signal,
                       compat_signo_t, signo,
                       UNCHECKED USER compat_sighandler_t, handler) {
	alignas(alignof(struct kernel_sigaction))
	byte_t _buf_act[offsetof(struct kernel_sigaction, sa_mask)];
	alignas(alignof(struct kernel_sigaction))
	byte_t _buf_oact[offsetof(struct kernel_sigaction, sa_mask)];
	struct kernel_sigaction *act  = (struct kernel_sigaction *)_buf_act;
	struct kernel_sigaction *oact = (struct kernel_sigaction *)_buf_oact;
	if ((void *)handler == (void *)SIG_GET) {
		sys_sigaction_impl(signo, NULL, oact, 0);
	} else {
		bzero(act, offsetof(struct kernel_sigaction, sa_mask));
		act->sa_handler = (typeof(act->sa_handler))(void *)handler;
		sys_sigaction_impl(signo, act, oact, 0);
	}
	return (compat_sighandler_t)(uintptr_t)(void *)oact->sa_handler;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SIGNAL */

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_SIGACTION_C */
