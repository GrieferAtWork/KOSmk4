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
#ifndef GUARD_KERNEL_SRC_SCHED_POSIX_SIGNAL_C
#define GUARD_KERNEL_SRC_SCHED_POSIX_SIGNAL_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/coredump.h>
#include <kernel/except.h>
#include <kernel/paging.h> /* KERNELSPACE_HIGHMEM */
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <kernel/vm.h> /* DEFINE_PERVM_ONEXEC() */
#include <misc/atomic-ref.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/minmax.h>

#include <compat/config.h>
#include <kos/except/inval.h>
#include <sys/wait.h>

#include <assert.h>
#include <errno.h>
#include <sched.h>
#include <signal.h>
#include <string.h>

#include <librpc/rpc.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/sigaction-struct.h>
#include <compat/bits/siginfo-convert.h>
#include <compat/bits/siginfo-struct.h>
#include <compat/bits/timespec.h>
#include <compat/kos/types.h>
#include <compat/pointer.h>
#include <compat/signal.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

PUBLIC struct kernel_sigmask empty_kernel_sigmask = {
	/* .sm_refcnt = */ 2,
	/* .sm_share  = */ 2,
	/* .sm_mask   = */ { { 0 } }
};

/* [0..1][lock(READ(ATOMIC), WRITE(THIS_TASK))]
 * Reference to the signal mask (set of signals being blocked) in the current thread. */
PUBLIC ATTR_PERTASK ATOMIC_REF(struct kernel_sigmask) this_sigmask = ATOMIC_REF_INIT(&empty_kernel_sigmask);

/* [0..1][valid_if(!TASK_FKERNTHREAD)][lock(PRIVATE(THIS_TASK))]
 * User-space signal handlers for the calling thread. */
PUBLIC ATTR_PERTASK REF struct sighand_ptr *this_sighand_ptr = NULL;


DEFINE_PERTASK_CLONE(clone_posix_signals);
PRIVATE ATTR_USED void KCALL
clone_posix_signals(struct task *__restrict new_thread, uintptr_t flags) {
	/* Clone the current signal mask. */
	if (sigmask_getrd() == &empty_kernel_sigmask) {
		/* Nothing to do here! */
	} else {
		REF struct kernel_sigmask *mask;
		mask = PERTASK(this_sigmask).get();
		assert(mask != &empty_kernel_sigmask);
		ATOMIC_FETCHINC(mask->sm_share);
		COMPILER_WRITE_BARRIER();
		FORTASK(new_thread, this_sigmask).m_pointer = mask; /* Inherit reference. */
		COMPILER_WRITE_BARRIER();
	}
	if (flags & CLONE_SIGHAND) {
		/* Must share signal handlers. */
		REF struct sighand_ptr *myptr;
		myptr = PERTASK_GET(this_sighand_ptr);
		if (!myptr) {
			/* Must allocate the signal handler table pointer so we can share it! */
			myptr = (REF struct sighand_ptr *)kmalloc(sizeof(struct sighand_ptr),
			                                          GFP_NORMAL);
			myptr->sp_refcnt = 2;
			atomic_rwlock_init(&myptr->sp_lock);
			myptr->sp_hand = NULL;
			assert(!PERTASK_GET(this_sighand_ptr));
			PERTASK_SET(this_sighand_ptr, myptr);
		} else {
			incref(myptr);
		}
		FORTASK(new_thread, this_sighand_ptr) = myptr;
	} else {
		/* Set signal handlers of the thread as a copy of the caller. */
		struct sighand_ptr *myptr;
		myptr = PERTASK_GET(this_sighand_ptr);
		if (!myptr) {
			/* No handlers -> Nothing to copy (the new thread will also use default handlers!) */
		} else {
			REF struct sighand_ptr *newptr;
			struct sighand *myhand;
			newptr = (REF struct sighand_ptr *)kmalloc(sizeof(struct sighand_ptr),
			                                           GFP_NORMAL);
again_lock_myptr:
			TRY {
				sync_read(myptr);
				COMPILER_READ_BARRIER();
				myhand = myptr->sp_hand;
				COMPILER_READ_BARRIER();
				if (!myhand) {
					/* No handlers -> Nothing to copy (the new thread will also use default handlers!) */
					sync_endread(myptr);
				} else {
					if (!sync_trywrite(myhand)) {
						sync_endread(myptr);
						task_yield();
						goto again_lock_myptr;
					}
					sync_endread(myptr);
					sighand_incshare(myhand);
					sync_endwrite(myhand);

					/* Still share the handler table as copy-on-write. */
					atomic_rwlock_init(&newptr->sp_lock);
					newptr->sp_refcnt = 1;
					newptr->sp_hand = myhand;
				}
			} EXCEPT {
				kfree(newptr);
				RETHROW();
			}
			FORTASK(new_thread, this_sighand_ptr) = newptr;
		}
	}
}


DEFINE_PERTASK_FINI(fini_posix_signals);
PRIVATE NOBLOCK ATTR_USED void
NOTHROW(KCALL fini_posix_signals)(struct task *__restrict thread) {
	struct kernel_sigmask *mask;
	mask = FORTASK(thread, this_sigmask).m_pointer;
	if (mask != &empty_kernel_sigmask)
		decref(mask);
	xdecref(FORTASK(thread, this_sighand_ptr));
}



/* Make sure that `this_sigmask' is allocated, and isn't being shared.
 * Then, always return `PERTASK_GET(this_sigmask)' */
PUBLIC ATTR_RETNONNULL WUNUSED struct kernel_sigmask *KCALL
sigmask_getwr(void) THROWS(E_BADALLOC) {
	struct kernel_sigmask *result;
	result = sigmask_getrd();
	if (ATOMIC_READ(result->sm_share) > 1) {
		/* Unshare. */
		struct kernel_sigmask *copy;
		copy = (struct kernel_sigmask *)kmalloc(sizeof(struct kernel_sigmask),
		                                        GFP_CALLOC);
		memcpy(&copy->sm_mask, &result->sm_mask, sizeof(copy->sm_mask));
		copy->sm_refcnt = 1;
		copy->sm_share  = 1;
		result = PERTASK(this_sigmask).exchange_inherit_new(copy);
		if (result != &empty_kernel_sigmask) {
			ATOMIC_FETCHDEC(result->sm_share);
			decref_unlikely(result);
		}
		result = copy;
	}
	return result;
}



PUBLIC NOBLOCK void
NOTHROW(KCALL sighand_destroy)(struct sighand *__restrict self) {
	unsigned int i;
	for (i = 0; i < NSIG - 1; ++i)
		xdecref(self->sh_actions[i].sa_mask);
	kfree(self);
}

PUBLIC NOBLOCK void
NOTHROW(KCALL sighand_ptr_destroy)(struct sighand_ptr *__restrict self) {
	if (self->sp_hand)
		sighand_decshare(self->sp_hand);
	kfree(self);
}




/* Acquire a lock to the underlying signal handler table that is associated
 * with the given `sighand_ptr', either for reading, or for writing.
 * For reading:
 * >> struct sighand *h;
 * >> h = sighand_ptr_lockread(THIS_SIGHAND_PTR);
 * >> ...
 * >> sync_endread(h);
 * For writing:
 * >> h = sighand_ptr_lockwrite();
 * >> ...
 * >> sync_endwrite(h);
 * With that in mind, these function will perform the necessary unsharing of
 * copy-on-write signal handler tables, while still keeping association of
 * handlers in check when it comes to shared handler tables, as usually found
 * within the same process. */
PUBLIC struct sighand *KCALL
sighand_ptr_lockread(struct sighand_ptr *__restrict ptr)
		THROWS(E_WOULDBLOCK) {
	struct sighand *result;
	bool lock_ok;
again:
	sync_read(&ptr->sp_lock);
	COMPILER_READ_BARRIER();
	result = ptr->sp_hand;
	COMPILER_READ_BARRIER();
	lock_ok = !result ? true : sync_tryread(result);
	sync_endread(&ptr->sp_lock);
	if (!lock_ok) {
		task_yield();
		goto again;
	}
	return result;
}

PUBLIC ATTR_RETNONNULL struct sighand *KCALL
sighand_ptr_lockwrite(void) THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct sighand *result;
	struct sighand_ptr *ptr;
	bool lock_ok;
again_read_thread_ptr:
	ptr = THIS_SIGHAND_PTR;
	if (!ptr) {
		/* No handlers allocated (yet). - Allocate it now as an empty handler table.
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
	sync_read(ptr);
	COMPILER_READ_BARRIER();
	result = ptr->sp_hand;
	COMPILER_READ_BARRIER();
	if (!result) {
		sync_endread(ptr);
		/* Lazily allocate the signal handler table. */
		result = (struct sighand *)kmalloc(sizeof(struct sighand), GFP_CALLOC);
		atomic_rwlock_cinit_write(&result->sh_lock); /* Init in write-mode */
		result->sh_share = 1;
		TRY {
			sync_write(ptr);
		} EXCEPT {
			kfree(result);
			RETHROW();
		}
		COMPILER_BARRIER();
		if likely(!ptr->sp_hand) {
			ptr->sp_hand = result;
			sync_endwrite(ptr);
			return result;
		}
		/* Race condition: another thread also allocated the handler table in the mean time! */
		sync_endwrite(ptr);
		kfree(result);
		goto again_lock_ptr;
	}
	/* Got the handler table! - Now to lock it. */
	lock_ok = sync_trywrite(result);
	sync_endread(ptr);
	if (!lock_ok) {
		task_yield();
		goto again_lock_ptr;
	}
	/* At this point we have a write-lock to the handler table.
	 * Now we must verify that the table isn't being shared, and
	 * if it is being shared, we must unshare it and replace it
	 * with a copy. */
	if (ATOMIC_READ(result->sh_share) > 1) {
		struct sighand *copy;
		sync_endwrite(result);
		copy = (struct sighand *)kmalloc(sizeof(struct sighand), GFP_NORMAL);
		TRY {
			unsigned int i;
again_lock_ptr_for_copy:
			sync_write(ptr);
			COMPILER_READ_BARRIER();
			result = ptr->sp_hand;
			COMPILER_READ_BARRIER();
			if (!sync_tryread(result)) {
				sync_endwrite(ptr);
				task_yield();
				goto again_lock_ptr_for_copy;
			}
			if unlikely(ATOMIC_READ(result->sh_share) <= 1) {
				/* The handler table already got unshared in the mean time...
				 * No need to initialize + save our copy! */
				sync_endwrite(ptr);
				if (!sync_tryupgrade(result)) {
					sync_endread(result);
					kfree(copy);
					task_yield();
					goto again_lock_ptr;
				}
				kfree(copy);
				return result;
			}
			/* Initialize the new copy as a duplicate of the old handler table. */
			memcpy(copy->sh_actions,
			       result->sh_actions,
			       sizeof(result->sh_actions));
			/* Load references to signal masks. */
			for (i = 0; i < NSIG - 1; ++i)
				xincref(copy->sh_actions[i].sa_mask);
			sync_endread(result);
			copy->sh_share = 1; /* Only 1 sighand_ptr will use this copy (for now) */
			atomic_rwlock_init_write(&copy->sh_lock);
			/* Store the copy in the thread-local sighand_ptr */
			COMPILER_WRITE_BARRIER();
			ptr->sp_hand = copy;
			COMPILER_WRITE_BARRIER();
			sync_endwrite(ptr);
		} EXCEPT {
			kfree(copy);
			RETHROW();
		}
		/* NOTE: At this point we're still holding a write-lock to `copy',
		 *       which we're eventually going to propagate to the caller. */
		/* Drop the share reference from the old handler table. */
		sighand_decshare(result);
		/* Return newly constructed copy of the handler table. */
		result = copy;
	}
	return result;
}


/* Return the default action to perform when faced with `signo' configured as `KERNEL_SIG_DFL'
 * @return: * : One of `KERNEL_SIG_*' (excluding `KERNEL_SIG_DFL' and `KERNEL_SIG_GET') */
PUBLIC NOBLOCK WUNUSED ATTR_CONST user_sighandler_func_t
NOTHROW(KCALL sighand_default_action)(signo_t signo) {
	user_sighandler_func_t result;
	result = KERNEL_SIG_IGN;
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
		result = KERNEL_SIG_CORE;
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
		result = KERNEL_SIG_TERM;
		break;

	case SIGCONT:
		result = KERNEL_SIG_CONT;
		break;

	case SIGSTOP:
	case SIGTSTP:
	case SIGTTIN:
	case SIGTTOU:
		result = KERNEL_SIG_STOP;
		break;

	default: break;
	}
	return result;
}


/* Suspend execution of the calling thread by setting `TASK_FSUSPENDED',
 * and keep the thread suspended until `task_sigcont()' is called.
 * This is used to implement SIGSTOP/SIGCONT behavior.
 * @param: stop_code: The stop code (created with `W_STOPCODE(signo)') */
PUBLIC void KCALL task_sigstop(int stop_code)
		THROWS(E_WOULDBLOCK, E_INTERRUPT) {
	struct taskpid *pid = THIS_TASKPID;
	printk(KERN_DEBUG "[sig] Stop execution of thread %u\n",
	       (unsigned int)task_getrootpid_s());
	/* NOTE: The write order here is highly important! */
	ATOMIC_STORE(pid->tp_status.w_status, stop_code);    /* #1: Set the stop status */
	ATOMIC_FETCHOR(THIS_TASK->t_flags, TASK_FSUSPENDED); /* #2: Set the suspended flag */
	sig_broadcast(&pid->tp_changed);                     /* #3: Broadcast that our status changed. */
	/* #4: Wait for the SUSPENDED flag to go away */
	TRY {
		do {
			task_connect(&pid->tp_changed);
			if unlikely(!(ATOMIC_READ(THIS_TASK->t_flags) & TASK_FSUSPENDED)) {
				/* Race condition: we were already re-awoken. */
				task_disconnectall();
				break;
			}
			/* Wait for tp_changed to be broadcast. */
			task_waitfor();
		} while (ATOMIC_READ(THIS_TASK->t_flags) & TASK_FSUSPENDED);
	} EXCEPT {
		/* TODO: What about E_INTERRUPT_USER? - With this, any kind of RPC
		 *       or POSIX-SIGNAL would resume execution of a stopped thread! */

		/* Unset the STOP status */
		task_sigcont(THIS_TASK);
		RETHROW();
	}
}

/* Continue execution in `thread', if that thread is currently suspended
 * due to having called `task_sigstop()'
 * WARNING: A race condition exists where `thread' may not have started waiting
 *          yet, in which case this function will return `false', indicating
 *          that the given thread wasn't actually woken.
 * @return: true:  Successfully set `thread' to continue execution
 * @return: false: Either `thread' hasn't started sleeping, or was already continued. */
PUBLIC NOBLOCK bool
NOTHROW(KCALL task_sigcont)(struct task *__restrict thread) {
	struct taskpid *pid;
	if (!(ATOMIC_FETCHAND(thread->t_flags, ~TASK_FSUSPENDED) & TASK_FSUSPENDED))
		return false; /* Not suspended */
	printk(KERN_DEBUG "[sig] Resume execution of thread %u\n",
	       (unsigned int)task_getrootpid_of_s(thread));
	/* Now we must wake up the thread! */
	pid = FORTASK(thread, this_taskpid);
	ATOMIC_STORE(pid->tp_status.w_status, __W_CONTINUED);
	sig_broadcast(&pid->tp_changed);
	return true;
}




/* Reset the current handler for `signo' when `current_action' matches the currently set action.
 * This function should be called by kernel-space signal delivery implementations to implement the
 * behavior of `SIGACTION_SA_RESETHAND' when handling a signal.
 * @return: true:  Successfully reset the handler
 * @return: false: The given `current_action' didn't match the currently set action. */
PUBLIC bool KCALL
sighand_reset_handler(signo_t signo,
                      struct kernel_sigaction const *__restrict current_action)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct sighand *hand;
	assert(signo != 0);
	assert(signo < NSIG);
	if unlikely(!THIS_SIGHAND_PTR)
		return false;
	hand = sighand_ptr_lockwrite();
	if (memcmp(current_action,
	           &hand->sh_actions[signo - 1],
	           sizeof(struct kernel_sigaction)) != 0) {
		sync_endwrite(hand);
		return false;
	}
	/* Reset the action. */
	memset(&hand->sh_actions[signo - 1],
	       0, sizeof(struct kernel_sigaction));
	sync_endwrite(hand);
	/* Drop the reference held by the `sh_actions' vector.
	 * Note however that since the caller must have copied that action at one point,
	 * they must currently be holding a reference to its `sa_mask', meaning that
	 * decref-ing that field mustn't be able to destroy the mask object! */
	xdecref_nokill(current_action->sa_mask);
	return true;
}



PRIVATE struct icpustate *FCALL
set_syscall_return(struct icpustate *__restrict state, syscall_ulong_t value) {
#ifdef __x86_64__
	state->ics_gpregs.gp_rax = (u64)(uintptr_t)value;
#elif defined(__i386__)
	state->ics_gpregs.gp_eax = (u32)(uintptr_t)value;
#else
#error Unsupported arch
#endif
	return state;
}



PRIVATE struct icpustate *FCALL
task_sigmask_check_rpc_handler(void *UNUSED(arg),
                               struct icpustate *__restrict state,
                               unsigned int reason,
                               struct rpc_syscall_info const *sc_info) {
	assert(reason == TASK_RPC_REASON_ASYNCUSER ||
	       reason == TASK_RPC_REASON_SYSCALL ||
	       reason == TASK_RPC_REASON_SHUTDOWN);
	assert((reason == TASK_RPC_REASON_SYSCALL) == (sc_info != NULL));
	if likely(reason != TASK_RPC_REASON_SHUTDOWN) {
		struct icpustate *new_state;
		/* Check for unmasked signals. */
		new_state = sigmask_check_s(state, sc_info);
		if (reason == TASK_RPC_REASON_SYSCALL ||
		    new_state != TASK_RPC_RESTART_SYSCALL) {
			/* Apply the new signal state.
			 * Note that we return `TASK_RPC_RESTART_SYSCALL' when a system
			 * call got interrupted, but no pending signals actually got
			 * unmasked. */
			state = new_state;
		}
	}
	return state;
}

PRIVATE struct icpustate *FCALL
task_sigmask_check_rpc_handler_after_syscall(void *arg,
                                             struct icpustate *__restrict state,
                                             unsigned int reason,
                                             struct rpc_syscall_info const *sc_info) {
	assert(reason == TASK_RPC_REASON_ASYNCUSER ||
	       reason == TASK_RPC_REASON_SYSCALL ||
	       reason == TASK_RPC_REASON_SHUTDOWN);
	assert((reason == TASK_RPC_REASON_SYSCALL) == (sc_info != NULL));
	if likely(reason != TASK_RPC_REASON_SHUTDOWN) {
		struct icpustate *new_state;
		/* Check for unmasked signals. */
		if (reason == TASK_RPC_REASON_SYSCALL)
			state = set_syscall_return(state, (syscall_ulong_t)arg);
		new_state = sigmask_check_s(state, NULL); /* After syscall -> Don't allow for restarting! */
		if (reason == TASK_RPC_REASON_SYSCALL ||
		    new_state != TASK_RPC_RESTART_SYSCALL) {
			/* Apply the new signal state.
			 * Note that we return `TASK_RPC_RESTART_SYSCALL' when a system
			 * call got interrupted, but no pending signals actually got
			 * unmasked. */
			state = new_state;
		}
	}
	return state;
}

/* handle the given signal and update `state' */
PRIVATE struct icpustate *FCALL
handle_signal(struct sigqueue_entry *__restrict info,
              struct icpustate *__restrict state,
              struct rpc_syscall_info const *sc_info)
		THROWS(E_SEGFAULT, E_WOULDBLOCK) {
	struct kernel_sigaction action;
	struct sighand *myhand;
	struct sighand_ptr *myhandptr;
	/* Figure out what action to handle the signal with. */
again_gethand:
	myhandptr = THIS_SIGHAND_PTR;
	if (!myhandptr)
		goto default_action;
	assert(info->sqe_info.si_signo != 0);
	assert(info->sqe_info.si_signo < NSIG);
	myhand = sighand_ptr_lockread(myhandptr);
	if (!myhand) {
		/* Default action. */
default_action:
		memset(&action, 0, sizeof(action));
		assert(action.sa_handler == KERNEL_SIG_DFL);
	} else {
		memcpy(&action,
		       &myhand->sh_actions[info->sqe_info.si_signo - 1],
		       sizeof(action));
		xincref(action.sa_mask);
		sync_endread(myhand);
	}
	/* Check for default signal action. */
	if (action.sa_handler == KERNEL_SIG_DFL)
		action.sa_handler = sighand_default_action(info->sqe_info.si_signo);

	/* Actually handle the signal */
	switch ((uintptr_t)(void *)action.sa_handler) {

#undef __CCAST
#define __CCAST(T) /* nothing */

	case KERNEL_SIG_IGN:
		xdecref_unlikely(action.sa_mask);
#if 0 /* `SA_RESETHAND' only affects user-space signal handler functions */
		if ((action.sa_flags & SIGACTION_SA_RESETHAND) &&
		    unlikely(!sighand_reset_handler(info->sqe_info.si_signo, &action)))
			goto again_gethand;
#endif
		goto dont_handle;

	case KERNEL_SIG_CORE:
		xdecref_unlikely(action.sa_mask);
		/* Create a coredump */
		coredump_create_for_signal(state, &info->sqe_info);
		THROW(E_EXIT_PROCESS, W_EXITCODE(1, info->sqe_info.si_signo));

	case KERNEL_SIG_TERM:
		xdecref_unlikely(action.sa_mask);
		THROW(E_EXIT_PROCESS, W_EXITCODE(1, info->sqe_info.si_signo));

	case KERNEL_SIG_EXIT:
		xdecref_unlikely(action.sa_mask);
		THROW(E_EXIT_THREAD, W_EXITCODE(1, info->sqe_info.si_signo));

	case KERNEL_SIG_CONT:
		xdecref_unlikely(action.sa_mask);
#if 0 /* `SA_RESETHAND' only affects user-space signal handler functions */
		if ((action.sa_flags & SIGACTION_SA_RESETHAND) &&
		    unlikely(!sighand_reset_handler(info->sqe_info.si_signo, &action)))
			goto again_gethand;
#endif
		/* Continue execution. */
		task_sigcont(THIS_TASK);
		goto dont_handle;

	case KERNEL_SIG_STOP:
		/* TODO: Mask additional signals by looking at `SIGACTION_SA_NODEFER' and `action.sa_mask' */
		xdecref_unlikely(action.sa_mask);
#if 0 /* `SA_RESETHAND' only affects user-space signal handler functions */
		if ((action.sa_flags & SIGACTION_SA_RESETHAND) &&
		    unlikely(!sighand_reset_handler(info->sqe_info.si_signo, &action)))
			goto again_gethand;
#endif
		/* Suspend execution. */
		task_sigstop(W_STOPCODE(info->sqe_info.si_signo));
		goto dont_handle;

#undef __CCAST
#define __CCAST(T) (T)
	default: break;
	}
	/* Raise the given signal in user-space. */
	TRY {
		state = sighand_raise_signal(state,
		                             &action,
		                             &info->sqe_info,
		                             sc_info);
	} EXCEPT {
		xdecref_unlikely(action.sa_mask);
		RETHROW();
	}
	xdecref_unlikely(action.sa_mask);
	if unlikely(!state)
		goto again_gethand; /* SIGACTION_SA_RESETHAND... */
dont_handle:
	return state;
}

PRIVATE struct icpustate *FCALL
task_signal_rpc_handler(void *arg,
                        struct icpustate *__restrict state,
                        unsigned int reason,
                        struct rpc_syscall_info const *sc_info) {
	struct sigqueue_entry *info;
	assert(reason == TASK_RPC_REASON_ASYNCUSER ||
	       reason == TASK_RPC_REASON_SYSCALL ||
	       reason == TASK_RPC_REASON_SHUTDOWN);
	assert((reason == TASK_RPC_REASON_SYSCALL) == (sc_info != NULL));
	info = (struct sigqueue_entry *)arg;
	assert(info->sqe_info.si_signo != 0);
	assert(info->sqe_info.si_signo < NSIG);
	TRY {
		if likely(reason != TASK_RPC_REASON_SHUTDOWN) {
			struct kernel_sigmask *mymask;
			mymask = sigmask_getrd();
			/* Make sure that the signal isn't being masked (the RPC may have been delivered
			 * after our current thread masked the signal, meaning that the signal being raised
			 * still triggered the RPC) */
			if unlikely(mymask && sigismember(&mymask->sm_mask, info->sqe_info.si_signo)) {
				/* Mark the signal as pending within the current thread. */
				struct sigqueue *pertask_pending;
				struct sigqueue_entry *next;
				pertask_pending = &THIS_SIGQUEUE;
				do {
					next = ATOMIC_READ(pertask_pending->sq_queue);
					if unlikely(next == SIGQUEUE_SQ_QUEUE_TERMINATED)
						goto dont_handle; /* Might happen if the signal was delivered before the thread exited.
						                   * But then again, shouldn't `reason == TASK_RPC_REASON_SHUTDOWN' be
						                   * in this case? - Anyways: better be safe! */
					info->sqe_next = next;
					COMPILER_WRITE_BARRIER();
				} while (!ATOMIC_CMPXCH_WEAK(pertask_pending->sq_queue, next, info));
				sig_broadcast(&pertask_pending->sq_newsig);
				/* Restart the interrupted system call without letting userspace know. */
				if (reason == TASK_RPC_REASON_SYSCALL)
					return TASK_RPC_RESTART_SYSCALL;
				goto done;
			}
			/* Actually handle the signal */
			state = handle_signal(info,
			                      state,
			                      sc_info);
		}
	} EXCEPT {
		kfree(info);
		RETHROW();
	}
dont_handle:
	kfree(info);
done:
	return state;
}

PRIVATE struct icpustate *FCALL
task_signal_rpc_handler_after_syscall(void *arg,
                                      struct icpustate *__restrict state,
                                      unsigned int reason,
                                      struct rpc_syscall_info const *sc_info) {
	struct sigqueue_entry *info;
	assert(reason == TASK_RPC_REASON_ASYNCUSER ||
	       reason == TASK_RPC_REASON_SYSCALL ||
	       reason == TASK_RPC_REASON_SHUTDOWN);
	assert((reason == TASK_RPC_REASON_SYSCALL) == (sc_info != NULL));
	info = (struct sigqueue_entry *)arg;
	assert(info->sqe_info.si_signo != 0);
	assert(info->sqe_info.si_signo < NSIG);
	TRY {
		if likely(reason != TASK_RPC_REASON_SHUTDOWN) {
			struct kernel_sigmask *mymask;
			if (reason == TASK_RPC_REASON_SYSCALL)
				state = set_syscall_return(state, (syscall_ulong_t)(uintptr_t)info->sqe_next);
			mymask = sigmask_getrd();
			/* Make sure that the signal isn't being masked (the RPC may have been delivered
			 * after our current thread masked the signal, meaning that the signal being raised
			 * still triggered the RPC. - Schedule the ) */
			if unlikely(mymask && sigismember(&mymask->sm_mask, info->sqe_info.si_signo)) {
				/* Mark the signal as pending within the current thread. */
				struct sigqueue *pertask_pending;
				struct sigqueue_entry *next;
				pertask_pending = &THIS_SIGQUEUE;
				do {
					next = ATOMIC_READ(pertask_pending->sq_queue);
					if unlikely(next == SIGQUEUE_SQ_QUEUE_TERMINATED)
						goto dont_handle; /* Might happen if the signal was delivered before the thread exited.
						                   * But then again, shouldn't `reason == TASK_RPC_REASON_SHUTDOWN' be
						                   * in this case? - Anyways: better be safe! */
					info->sqe_next = next;
					COMPILER_WRITE_BARRIER();
				} while (!ATOMIC_CMPXCH_WEAK(pertask_pending->sq_queue, next, info));
				sig_broadcast(&pertask_pending->sq_newsig);
				/* Restart the interrupted system call without letting userspace know. */
				if (reason == TASK_RPC_REASON_SYSCALL)
					return TASK_RPC_RESTART_SYSCALL;
				goto done;
			}
			/* Actually handle the signal */
			state = handle_signal(info,
			                      state,
			                      NULL);
		}
	} EXCEPT {
		kfree(info);
		RETHROW();
	}
dont_handle:
	kfree(info);
done:
	return state;
}


/* Deliver the given signal `info' to some thread apart of the process lead by `process_leader'
 * If all threads are masking the given signal, schedule the signal as pending for the process.
 * @return: true:  Success (either delivered, or scheduled as pending).
 * @return: false: The given process has terminated. */
PRIVATE bool KCALL
deliver_signal_to_some_thread_in_process(struct task *__restrict process_leader,
                                         /*inherit(always)*/ struct sigqueue_entry *__restrict info,
                                         gfp_t rpc_flags)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_INTERRUPT_USER_RPC);


/* Same as `task_signal_rpc_handler', but masked signals as process signals. */
PRIVATE struct icpustate *FCALL
task_process_signal_rpc_handler(void *arg,
                                struct icpustate *__restrict state,
                                unsigned int reason,
                                struct rpc_syscall_info const *sc_info) {
	struct sigqueue_entry *info;
	assert(reason == TASK_RPC_REASON_ASYNCUSER ||
	       reason == TASK_RPC_REASON_SYSCALL ||
	       reason == TASK_RPC_REASON_SHUTDOWN);
	assert((reason == TASK_RPC_REASON_SYSCALL) == (sc_info != NULL));
	info = (struct sigqueue_entry *)arg;
	assert(info->sqe_info.si_signo != 0);
	assert(info->sqe_info.si_signo < NSIG);
	TRY {
		if likely(reason != TASK_RPC_REASON_SHUTDOWN) {
			struct kernel_sigmask *mymask;
			mymask = sigmask_getrd();
			/* Make sure that the signal isn't being masked (the RPC may have been delivered
			 * after our current thread masked the signal, meaning that the signal being raised
			 * still triggered the RPC) */
			if unlikely(mymask && sigismember(&mymask->sm_mask, info->sqe_info.si_signo))
				goto deliver_to_some_thread;
			/* Actually handle the signal */
			state = handle_signal(info,
			                      state,
			                      sc_info);
		}
	} EXCEPT {
		kfree(info);
		RETHROW();
	}
	kfree(info);
done:
	return state;
deliver_to_some_thread:
	/* Deliver the signal to some other thread... */
	deliver_signal_to_some_thread_in_process(task_getprocess(),
	                                         info,
	                                         GFP_NORMAL);
	/* Restart the interrupted system call without letting userspace know. */
	if (reason == TASK_RPC_REASON_SYSCALL)
		return TASK_RPC_RESTART_SYSCALL;
	goto done;
}





LOCAL ATTR_NORETURN void KCALL
send_signal_rpc_to_self(/*inherit(always)*/ struct sigqueue_entry *__restrict entry) {
	TRY {
		task_schedule_user_rpc(THIS_TASK,
		                       &task_signal_rpc_handler,
		                       entry,
		                       TASK_USER_RPC_FINTR,
		                       GFP_NORMAL);
		__builtin_unreachable();
	} EXCEPT {
		if (error_code() != ERROR_CODEOF(E_INTERRUPT_USER_RPC))
			kfree(entry);
		RETHROW();
	}
}

LOCAL ATTR_NORETURN void KCALL
send_signal_rpc_to_self_after_syscall(/*inherit(always)*/ struct sigqueue_entry *__restrict entry,
                                      syscall_ulong_t syscall_result) {
	TRY {
		entry->sqe_next = (struct sigqueue_entry *)(void *)(uintptr_t)syscall_result;
		task_schedule_user_rpc(THIS_TASK,
		                       &task_signal_rpc_handler_after_syscall,
		                       entry,
		                       TASK_USER_RPC_FINTR,
		                       GFP_NORMAL);
		__builtin_unreachable();
	} EXCEPT {
		if (error_code() != ERROR_CODEOF(E_INTERRUPT_USER_RPC))
			kfree(entry);
		RETHROW();
	}
}

LOCAL NOBLOCK NONNULL((1, 2)) void
NOTHROW(KCALL restore_perthread_pending_signals)(struct sigqueue *__restrict myqueue,
                                                 struct sigqueue_entry *__restrict pending) {
	/* Restore all signals pending for the calling thread. */
	if unlikely(!ATOMIC_CMPXCH(myqueue->sq_queue, NULL, pending)) {
		struct sigqueue_entry *last, *next;
		last = pending;
		while (last->sqe_next)
			last = last->sqe_next;
		do {
			next = ATOMIC_READ(myqueue->sq_queue);
			last->sqe_next = next;
			COMPILER_WRITE_BARRIER();
		} while (!ATOMIC_CMPXCH_WEAK(myqueue->sq_queue, next, pending));
	}
}


/* Check for pending signals that are no longer being masked. */
PUBLIC void FCALL
sigmask_check(void) THROWS(E_INTERRUPT, E_WOULDBLOCK) {
	struct kernel_sigmask *mask;
	struct sigqueue *myqueue;
	struct process_sigqueue *prqueue;
	struct sigqueue_entry *pending, **piter, *iter;
	mask = sigmask_getrd();
	myqueue = &THIS_SIGQUEUE;
	/* Temporarily steal all pending per-thread signals. */
	do {
		pending = ATOMIC_READ(myqueue->sq_queue);
		if (!pending)
			goto no_perthread_pending; /* No signals are pending for the calling thread */
		if unlikely(pending == SIGQUEUE_SQ_QUEUE_TERMINATED)
			return; /* Shouldn't happen: The calling thread is currently terminating. */
	} while (!ATOMIC_CMPXCH_WEAK(myqueue->sq_queue, pending, NULL));
	/* Go through pending signals and check if there are any that aren't being masked. */
	iter  = pending;
	piter = &pending;
	do {
		if (!sigismember(&mask->sm_mask, iter->sqe_info.si_signo)) {
			/* Found one that's not being masked. */
			*piter = iter->sqe_next;
			if (pending)
				restore_perthread_pending_signals(myqueue, pending);
			/* Deliver the signal to ourself */
			send_signal_rpc_to_self(iter);
			break;
		}
	} while ((iter = *(piter = &iter->sqe_next)) != NULL);

	/* Restore all signals pending for the calling thread. */
	restore_perthread_pending_signals(myqueue, pending);
no_perthread_pending:
	/* With per-task signals checked, also check for per-process signals */
	prqueue = &THIS_PROCESS_SIGQUEUE;
	sync_read(prqueue);
	for (iter = prqueue->psq_queue.sq_queue;
	     iter; iter = iter->sqe_next) {
		if (sigismember(&mask->sm_mask, iter->sqe_info.si_signo))
			continue;
		/* Found an unmasked signal. */
		sync_endread(prqueue);
		/* Send an RPC to ourself to service the signals.
		 * Note that we use an RPC including another call to sigmask_check()
		 * here, since there is a chance that the calling thread will mask
		 * the affected signal before `sigmask_check_s()' gets invoked, in
		 * which case if we had stolen the pending signal from the process's
		 * list of pending signal, no other thread will be able to handle
		 * to handle the signal before we can, and we'd have to send even
		 * more RPCs between all of the threads within the current process
		 * before we find someone that's actually able to service the signal! */
		task_schedule_user_rpc(THIS_TASK,
		                       &task_sigmask_check_rpc_handler,
		                       NULL,
		                       TASK_USER_RPC_FINTR,
		                       GFP_NORMAL);
		__builtin_unreachable();
	}
	sync_endread(prqueue);
}


PUBLIC void FCALL
sigmask_check_after_syscall(syscall_ulong_t syscall_result)
		THROWS(E_INTERRUPT, E_WOULDBLOCK) {
	struct kernel_sigmask *mask;
	struct sigqueue *myqueue;
	struct process_sigqueue *prqueue;
	struct sigqueue_entry *pending, **piter, *iter;
	mask = sigmask_getrd();
	myqueue = &THIS_SIGQUEUE;
	/* Temporarily steal all pending per-thread signals. */
	do {
		pending = ATOMIC_READ(myqueue->sq_queue);
		if (!pending)
			goto no_perthread_pending; /* No signals are pending for the calling thread */
		if unlikely(pending == SIGQUEUE_SQ_QUEUE_TERMINATED)
			return; /* Shouldn't happen: The calling thread is currently terminating. */
	} while (!ATOMIC_CMPXCH_WEAK(myqueue->sq_queue, pending, NULL));
	/* Go through pending signals and check if there are any that aren't being masked. */
	iter  = pending;
	piter = &pending;
	do {
		if (!sigismember(&mask->sm_mask, iter->sqe_info.si_signo)) {
			/* Found one that's not being masked. */
			*piter = iter->sqe_next;
			if (pending)
				restore_perthread_pending_signals(myqueue, pending);
			/* Deliver the signal to ourself */
			send_signal_rpc_to_self_after_syscall(iter, syscall_result);
			break;
		}
	} while ((iter = *(piter = &iter->sqe_next)) != NULL);

	/* Restore all signals pending for the calling thread. */
	restore_perthread_pending_signals(myqueue, pending);
no_perthread_pending:
	/* With per-task signals checked, also check for per-process signals */
	prqueue = &THIS_PROCESS_SIGQUEUE;
	sync_read(prqueue);
	for (iter = prqueue->psq_queue.sq_queue;
	     iter; iter = iter->sqe_next) {
		if (sigismember(&mask->sm_mask, iter->sqe_info.si_signo))
			continue;
		/* Found an unmasked signal. */
		sync_endread(prqueue);
		/* Send an RPC to ourself to service the signals.
		 * Note that we use an RPC including another call to sigmask_check()
		 * here, since there is a chance that the calling thread will mask
		 * the affected signal before `sigmask_check_s()' gets invoked, in
		 * which case if we had stolen the pending signal from the process's
		 * list of pending signal, no other thread will be able to handle
		 * to handle the signal before we can, and we'd have to send even
		 * more RPCs between all of the threads within the current process
		 * before we find someone that's actually able to service the signal! */
		task_schedule_user_rpc(THIS_TASK,
		                       &task_sigmask_check_rpc_handler_after_syscall,
		                       (void *)syscall_result,
		                       TASK_USER_RPC_FINTR,
		                       GFP_NORMAL);
		__builtin_unreachable();
	}
	sync_endread(prqueue);
}

/* Same as `sigmask_check()', but should be called in order to have
 * user-space handle the currently set exception in case a signal
 * handler has to be invoked.
 * See the documentation of `sigmask_check_after_syscall()' for when
 * this function needs to be called. */
PUBLIC void FCALL
sigmask_check_after_except(void)
		THROWS(E_INTERRUPT, E_WOULDBLOCK) {
	/* TODO: implement this properly! */
	sigmask_check();
}


/* Same as `sigmask_check()', but service signals immediately.
 * @param: sc_info: A system call that may be restarted, or NULL.
 * @return: * :                       The updated cpu-state.
 * @return: TASK_RPC_RESTART_SYSCALL: Nothing was handled. */
PUBLIC struct icpustate *FCALL
sigmask_check_s(struct icpustate *__restrict state,
                struct rpc_syscall_info const *sc_info)
		THROWS(E_WOULDBLOCK, E_SEGFAULT) {
	bool did_handle_something = false;
	struct kernel_sigmask *mask;
	struct sigqueue *myqueue;
	struct process_sigqueue *prqueue;
	struct sigqueue_entry *pending, **piter, *iter;
	mask = sigmask_getrd();
	myqueue = &THIS_SIGQUEUE;
	/* Temporarily steal all pending per-thread signals. */
	do {
		pending = ATOMIC_READ(myqueue->sq_queue);
		if (!pending)
			goto no_perthread_pending; /* No signals are pending for the calling thread */
		if unlikely(pending == SIGQUEUE_SQ_QUEUE_TERMINATED)
			return state; /* Shouldn't happen: The calling thread is currently terminating. */
	} while (!ATOMIC_CMPXCH_WEAK(myqueue->sq_queue, pending, NULL));
	/* Go through pending signals and check if there are any that aren't being masked. */
	iter  = pending;
	piter = &pending;
again_iter:
	do {
		if (!sigismember(&mask->sm_mask, iter->sqe_info.si_signo)) {
			/* Found one that's not being masked. */
			*piter = iter->sqe_next;
			if (pending)
				restore_perthread_pending_signals(myqueue, pending);
			/* Handle the signal */
			TRY {
				state = handle_signal(iter,
				                      state,
				                      sc_info);
			} EXCEPT {
				restore_perthread_pending_signals(myqueue, pending);
				kfree(iter);
				RETHROW();
			}
			kfree(iter);
			did_handle_something = true;
			/* Try to handle even more signals. */
			iter = *piter;
			if (!iter)
				break;
			goto again_iter;
		}
	} while ((iter = *(piter = &iter->sqe_next)) != NULL);

	/* Restore all signals pending for the calling thread. */
	restore_perthread_pending_signals(myqueue, pending);
no_perthread_pending:
	/* With per-task signals checked, also check for per-process signals */
	prqueue = &THIS_PROCESS_SIGQUEUE;
	/* Quick check: are there any pending signals? */
again_lock_prqueue:
	if (ATOMIC_READ(prqueue->psq_queue.sq_queue) != NULL) {
		bool has_write_lock;
		sync_read(prqueue);
		has_write_lock = false;
again_scan_prqueue:
		for (piter = &prqueue->psq_queue.sq_queue;
			 (iter = *piter) != NULL; piter = &iter->sqe_next) {
			if (sigismember(&mask->sm_mask, iter->sqe_info.si_signo))
				continue;
			/* Found an unmasked signal.
			 * -> Upgrade our lock to write-mode so we can steal it! */
			if (!has_write_lock) {
				has_write_lock = true;
				if unlikely(!sync_upgrade(prqueue))
					goto again_scan_prqueue;
			}
			/* Steal the current entry. */
			*piter = iter->sqe_next;
			sync_endwrite(prqueue);
			has_write_lock = false;
			/* Handle this signal. */
			TRY {
				state = handle_signal(iter,
				                      state,
				                      sc_info);
			} EXCEPT {
				kfree(iter);
				RETHROW();
			}
			kfree(iter);
			did_handle_something = true;
			/* Search for more unmasked process signals. */
			goto again_lock_prqueue;
		}
		if unlikely(has_write_lock) {
			sync_endwrite(prqueue);
		} else {
			sync_endread(prqueue);
		}
	}
	if (!did_handle_something)
		return TASK_RPC_RESTART_SYSCALL;
	return state;
}




/* Check if the given `thread' is masking `signo' */
LOCAL NOBLOCK bool
NOTHROW(KCALL is_thread_masking_signal)(struct task *__restrict thread,
                                        signo_t signo) {
	bool result;
	REF struct kernel_sigmask *mask;
	assert(!(thread->t_flags & TASK_FKERNTHREAD));
	mask = FORTASK(thread, this_sigmask).get();
	result = sigismember(&mask->sm_mask, signo);
	decref_unlikely(mask);
	return result;
}


STATIC_ASSERT(SIGACTION_SA_NOCLDSTOP == SA_NOCLDSTOP);
STATIC_ASSERT(SIGACTION_SA_NOCLDWAIT == SA_NOCLDWAIT);
STATIC_ASSERT(SIGACTION_SA_SIGINFO == SA_SIGINFO);
STATIC_ASSERT(SIGACTION_SA_RESTORER == SA_RESTORER);
STATIC_ASSERT(SIGACTION_SA_ONSTACK == SA_ONSTACK);
STATIC_ASSERT(SIGACTION_SA_RESTART == SA_RESTART);
STATIC_ASSERT(SIGACTION_SA_NODEFER == SA_NODEFER);
STATIC_ASSERT(SIGACTION_SA_RESETHAND == SA_RESETHAND);

/* Check if `self' contains any handlers set to
 * SIG_IGN that wouldn't be set as such by default. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL sighand_has_nondefault_sig_ign)(struct sighand const *__restrict self) {
	unsigned int i;
	for (i = 0; i < NSIG - 1; ++i) {
		/* Check if the handler's action is SIG_IGN */
		if (self->sh_actions[i].sa_handler != KERNEL_SIG_IGN)
			continue; /* Something other than SIG_IGN */
		/* Check if the default action is something other than SIG_IGN */
		if (sighand_default_action(i + 1) == KERNEL_SIG_IGN)
			continue; /* Default would also be SIG_IGN */
		/* Found one! */
		return true;
	}
	return false;
}


/* During exec(), all signal handler dispositions of the calling thread are reset */
DEFINE_PERVM_ONEXEC(onexec_posix_signals_reset_action);
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
		 * `sighand_default_action()' returns something else. */
		if (!sighand_has_nondefault_sig_ign(hand)) {
			sync_endread(hand);
			goto done_handptr;
		}
		/* We have to create a new, custom set of signal handlers... */
		/* NOTE: Use GFP_CALLOC because `KERNEL_SIG_DFL = 0', and we only
		 *       need to inherit handlers that were marked as `SIG_IGN' */
		newhand = (REF struct sighand *)kmalloc_nx(sizeof(struct sighand),
		                                           GFP_CALLOC | GFP_ATOMIC);
		if (!newhand) {
			sync_endread(hand);
			newhand = (REF struct sighand *)kmalloc(sizeof(struct sighand), GFP_CALLOC);
			TRY {
				hand = sighand_ptr_lockread(handptr);
			} EXCEPT {
				kfree(newhand);
				assert(!PERTASK_GET(this_sighand_ptr));
				PERTASK_SET(this_sighand_ptr, handptr);
				RETHROW();
			}
			if unlikely(!hand) {
				kfree(newhand);
				goto done_handptr;
			}
			if (sighand_has_nondefault_sig_ign(hand)) {
				sync_endread(hand);
				kfree(newhand);
				goto done_handptr;
			}
		}
		/* Copy handlers that have their disposition set to SIG_IGN.
		 * However, don't copy anything else about those handlers,
		 * or any other handlers for that matter.
		 * Especially of note is that we also don't copy signal masks,
		 * since those wouldn't actually matter for SIG_IGN handlers. */
		for (i = 0; i < NSIG - 1; ++i) {
			if (hand->sh_actions[i].sa_handler == KERNEL_SIG_IGN)
				newhand->sh_actions[i].sa_handler = KERNEL_SIG_IGN;
		}
		atomic_rwlock_cinit(&newhand->sh_lock);
		newhand->sh_share = 1;
		sync_endread(hand);
		if (!isshared(handptr)) {
			/* We can re-use `handptr' to point to `newhand' */
			TRY {
				/* This really shouldn't block since handptr isn't shared.
				 * ... But better to be safe than sorry. */
				sync_write(&handptr->sp_lock);
			} EXCEPT {
				kfree(newhand);
				decref(handptr);
				assert(!PERTASK_GET(this_sighand_ptr));
				PERTASK_SET(this_sighand_ptr, handptr);
				RETHROW();
			}
			assert(!isshared(handptr));
			hand = handptr->sp_hand;    /* Inherit reference */
			handptr->sp_hand = newhand; /* Inherit reference */
			sync_endwrite(&handptr->sp_lock);
			/* Restore the old hand-pointer for the calling thread. */
			assert(!PERTASK_GET(this_sighand_ptr));
			PERTASK_SET(this_sighand_ptr, handptr);
			/* Now that we're using `newhand', drop
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
				assert(!PERTASK_GET(this_sighand_ptr));
				PERTASK_SET(this_sighand_ptr, handptr);
				RETHROW();
			}
			newhandptr->sp_refcnt = 1;
			atomic_rwlock_init(&newhandptr->sp_lock);
			newhandptr->sp_hand = newhand; /* Inherit reference */
			assert(!PERTASK_GET(this_sighand_ptr));
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
do_sigaction(signo_t signo,
             CHECKED USER struct sigaction const *act,
             CHECKED USER struct sigaction *oact) {
	struct kernel_sigaction ohandler;
	struct sighand *hand;
	if unlikely(signo <= 0 || signo >= NSIG)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
		      signo);
	if (!act) {
		if (oact) {
			struct sighand_ptr *handptr;
			handptr = THIS_SIGHAND_PTR;
			if (handptr) {
				hand = sighand_ptr_lockread(handptr);
				if (!hand)
					goto no_old_handler;
				memcpy(&ohandler,
				       &hand->sh_actions[signo - 1],
				       sizeof(ohandler));
				xincref(ohandler.sa_mask);
				sync_endread(hand);
inherit_and_copy_ohandler:
				FINALLY_XDECREF(ohandler.sa_mask);
				COMPILER_WRITE_BARRIER();
				oact->sa_handler  = ohandler.sa_handler;
				oact->sa_flags    = ohandler.sa_flags;
				oact->sa_restorer = ohandler.sa_restore;
				if (ohandler.sa_mask) {
					memcpy(&oact->sa_mask,
					       &ohandler.sa_mask->sm_mask,
					       sizeof(sigset_t));
				} else {
					memset(&oact->sa_mask, 0,
					       sizeof(sigset_t));
				}
				COMPILER_WRITE_BARRIER();
			} else {
no_old_handler:
				memset(oact, 0, sizeof(*oact));
			}
		}
	} else {
		struct kernel_sigaction nhandler;
		COMPILER_READ_BARRIER();
		nhandler.sa_handler = act->sa_handler;
		nhandler.sa_flags   = act->sa_flags;
		COMPILER_READ_BARRIER();
#ifndef KERNELSPACE_HIGHMEM
		if ((uintptr_t)nhandler.sa_handler >= (uintptr_t)KERNEL_SIG_GET)
#endif /* !KERNELSPACE_HIGHMEM */
		{
			validate_executable((void const *)nhandler.sa_handler);
		}
		VALIDATE_FLAGSET(nhandler.sa_flags,
		                 SA_NOCLDSTOP | SA_NOCLDWAIT | SA_SIGINFO |
		                 SA_RESTORER | SA_ONSTACK | SA_RESTART |
		                 SA_NODEFER | SA_RESETHAND | SA_INTERRUPT,
		                 E_INVALID_ARGUMENT_CONTEXT_SIGACTION_ACT_FLAGS);
		COMPILER_BARRIER();
		nhandler.sa_restore = NULL;
		if (nhandler.sa_flags & SA_RESTORER) {
			nhandler.sa_restore = act->sa_restorer;
			COMPILER_READ_BARRIER();
			validate_executable((void const *)nhandler.sa_restore);
		}
		COMPILER_BARRIER();
		nhandler.sa_mask = NULL;
		/* Check if the given signal set is empty. */
		{
			size_t i;
			for (i = 0; i < COMPILER_LENOF(act->sa_mask.__val); ++i) {
				REF struct kernel_sigmask *mask;
				if (act->sa_mask.__val[i] == 0)
					continue;
				COMPILER_READ_BARRIER();
				/* Must allocate a custom signal mask. */
				mask = (REF struct kernel_sigmask *)kmalloc(sizeof(struct kernel_sigmask),
				                                            GFP_NORMAL);
				TRY {
					COMPILER_READ_BARRIER();
					memcpy(&mask->sm_mask, &act->sa_mask, sizeof(sigset_t));
					COMPILER_READ_BARRIER();
				} EXCEPT {
					kfree(mask);
					RETHROW();
				}
				mask->sm_refcnt  = 1;
				mask->sm_share   = 1;
				nhandler.sa_mask = mask;
				break;
			}
		}
		COMPILER_BARRIER();
		TRY {
			hand = sighand_ptr_lockwrite();
		} EXCEPT {
			kfree(nhandler.sa_mask);
			RETHROW();
		}
		/* Change the signal action. */
		memcpy(&ohandler, &hand->sh_actions[signo - 1], sizeof(ohandler));
		memcpy(&hand->sh_actions[signo - 1], &nhandler, sizeof(nhandler));
		sync_endwrite(hand);
		/* Check if user-space also wants to get the old action. */
		if (oact)
			goto inherit_and_copy_ohandler;
		xdecref(ohandler.sa_mask);
	}
}
#endif /* WANT_SIGACTION */

#ifdef __ARCH_WANT_SYSCALL_RT_SIGACTION
DEFINE_SYSCALL4(errno_t, rt_sigaction, signo_t, signo,
                UNCHECKED USER struct sigaction const *, act,
                UNCHECKED USER struct sigaction *, oact,
                size_t, sigsetsize) {
	if unlikely(sigsetsize != sizeof(sigset_t)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	}
	/* Validate user-structure pointers. */
	validate_readable_opt(act, sizeof(*act));
	validate_writable_opt(oact, sizeof(*oact));
	do_sigaction(signo, act, oact);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGACTION */

#ifdef __ARCH_WANT_SYSCALL_SIGACTION
DEFINE_SYSCALL3(errno_t, sigaction, signo_t, signo,
                UNCHECKED USER struct sigaction const *, act,
                UNCHECKED USER struct sigaction *, oact) {
	return sys_rt_sigaction(signo, act, oact, sizeof(sigset_t));
}
#endif /* __ARCH_WANT_SYSCALL_SIGACTION */

#if defined(__ARCH_WANT_COMPAT_SYSCALL_RT_SIGACTION) || \
    defined(__ARCH_WANT_COMPAT_SYSCALL_SIGACTION)
PRIVATE void KCALL
compat_sigaction_to_sigaction(CHECKED USER struct compat_sigaction const *self,
                              struct sigaction *__restrict result) {
	*(void **)&result->sa_handler  = (void *)self->sa_handler;
	memcpy(&result->sa_mask, &self->sa_mask, MIN(sizeof(sigset_t), sizeof(compat_sigset_t)));
	__STATIC_IF(sizeof(sigset_t) > sizeof(compat_sigset_t)) {
		memset((byte_t *)&result->sa_mask + sizeof(compat_sigset_t), 0,
		       sizeof(sigset_t) - sizeof(compat_sigset_t));
	}
	result->sa_flags = self->sa_flags;
	*(void **)&result->sa_restorer  = (void *)self->sa_restorer;
}

PRIVATE void KCALL
sigaction_to_compat_sigaction(struct sigaction const *__restrict self,
                              CHECKED USER struct compat_sigaction *result) {
	typedef compat_funptr(void, , compat_sigrestorer_t, (void));
	result->sa_handler = (compat_sighandler_t)(uintptr_t)(void *)self->sa_handler;
	memcpy(&result->sa_mask, &self->sa_mask, MIN(sizeof(sigset_t), sizeof(compat_sigset_t)));
	__STATIC_IF(sizeof(compat_sigset_t) > sizeof(sigset_t)) {
		memset((byte_t *)&result->sa_mask + sizeof(sigset_t), 0,
		       sizeof(compat_sigset_t) - sizeof(sigset_t));
	}
	result->sa_flags = self->sa_flags;
	result->sa_restorer = (compat_sigrestorer_t)(uintptr_t)(void *)self->sa_restorer;
}

PRIVATE errno_t KCALL
do_compat_sigaction(compat_signo_t signo,
                    UNCHECKED USER struct compat_sigaction const *act,
                    UNCHECKED USER struct compat_sigaction *oact) {
	struct sigaction real_act, real_oact;
	/* Validate user-structure pointers. */
	validate_readable_opt(act, sizeof(*act));
	validate_writable_opt(oact, sizeof(*oact));
	if (act)
		compat_sigaction_to_sigaction(act, &real_act);
	do_sigaction(signo,
	             act ? &real_act : NULL,
	             oact ? &real_oact : NULL);
	if (oact)
		sigaction_to_compat_sigaction(&real_oact, oact);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SIGACTION */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RT_SIGACTION
DEFINE_COMPAT_SYSCALL4(compat_errno_t, rt_sigaction, compat_signo_t, signo,
                       UNCHECKED USER struct compat_sigaction const *, act,
                       UNCHECKED USER struct compat_sigaction *, oact,
                       size_t, sigsetsize) {
	if unlikely(sigsetsize != sizeof(sigset_t)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	}
	return do_compat_sigaction(signo, act, oact);
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RT_SIGACTION */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SIGACTION
DEFINE_COMPAT_SYSCALL3(compat_errno_t, sigaction, compat_signo_t, signo,
                       UNCHECKED USER struct compat_sigaction const *, act,
                       UNCHECKED USER struct compat_sigaction *, oact) {
	return do_compat_sigaction(signo, act, oact);
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SIGACTION */

#ifdef __ARCH_WANT_SYSCALL_SIGNAL
DEFINE_SYSCALL2(sighandler_t, signal,
                signo_t, signo,
                UNCHECKED USER sighandler_t, handler) {
	struct sigaction oact, act;
	if (handler == KERNEL_SIG_GET) {
		do_sigaction(signo, NULL, &oact);
	} else {
		memset(&act, 0, sizeof(act));
		act.sa_handler = handler;
		do_sigaction(signo, &act, &oact);
	}
	return oact.sa_handler;
}
#endif /* __ARCH_WANT_SYSCALL_SIGNAL */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SIGNAL
DEFINE_COMPAT_SYSCALL2(sighandler_t, signal,
                       compat_signo_t, signo,
                       UNCHECKED USER sighandler_t, handler) {
	struct sigaction oact, act;
	if (handler == KERNEL_SIG_GET) {
		do_sigaction(signo, NULL, &oact);
	} else {
		memset(&act, 0, sizeof(act));
		act.sa_handler = handler;
		do_sigaction(signo, &act, &oact);
	}
	return oact.sa_handler;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SIGNAL */





/************************************************************************/
/* sigprocmask(), rt_sigprocmask()                                      */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_RT_SIGPROCMASK
#undef sigmask
LOCAL void KCALL
sigmask_ensure_unmasked_mandatory_after_syscall(struct kernel_sigmask *__restrict sigmask,
                                                syscall_ulong_t syscall_result) {
	/* Make sure that everything got written. */
	COMPILER_BARRIER();
	/* Ensure that SIGKILL and SIGSTOP aren't masked.
	 * If either got accidentally (or intentionally) got masked, unmask them
	 * and manually check for pending signals (in case some got delivered between
	 * the point when they got masked, and the point when we unmask them below) */
	if unlikely(sigismember(&sigmask->sm_mask, SIGKILL) ||
	            sigismember(&sigmask->sm_mask, SIGSTOP)) {
		sigdelset(&sigmask->sm_mask, SIGKILL);
		sigdelset(&sigmask->sm_mask, SIGSTOP);
		COMPILER_BARRIER();
		sigmask_check_after_syscall(syscall_result);
	}
}

LOCAL void KCALL
sigmask_ensure_unmasked_mandatory_after_except(struct kernel_sigmask *__restrict sigmask) {
	/* Make sure that everything got written. */
	COMPILER_BARRIER();
	/* Ensure that SIGKILL and SIGSTOP aren't masked.
	 * If either got accidentally (or intentionally) got masked, unmask them
	 * and manually check for pending signals (in case some got delivered between
	 * the point when they got masked, and the point when we unmask them below) */
	if unlikely(sigismember(&sigmask->sm_mask, SIGKILL) ||
	            sigismember(&sigmask->sm_mask, SIGSTOP)) {
		sigdelset(&sigmask->sm_mask, SIGKILL);
		sigdelset(&sigmask->sm_mask, SIGSTOP);
		COMPILER_BARRIER();
		sigmask_check_after_except();
	}
}

DEFINE_SYSCALL4(errno_t, rt_sigprocmask, syscall_ulong_t, how,
                UNCHECKED USER sigset_t const *, set,
                UNCHECKED USER sigset_t *, oset, size_t, sigsetsize) {
	struct kernel_sigmask *sigmask;
	if unlikely(sigsetsize != sizeof(sigset_t))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	validate_readable_opt(set, sizeof(*set));
	validate_writable_opt(oset, sizeof(*oset));
	if (!set) {
		if (oset) {
			sigmask = sigmask_getrd();
			assert(sigmask);
			memcpy(oset, &sigmask->sm_mask, sizeof(sigset_t));
		}
	} else {
		sigmask = sigmask_getwr();
		assert(sigmask);
		if (oset)
			memcpy(oset, &sigmask->sm_mask, sizeof(sigset_t));
		switch (how) {

		case SIG_BLOCK:
			TRY {
				sigorset(&sigmask->sm_mask, &sigmask->sm_mask, set);
			} EXCEPT {
				/* Also check for unmasked signals on error.
				 * User-space may have intentionally set up the mask such that
				 * it generates a #PF after some of the mandatory signals got
				 * masked, in which case they would remain masked if we didn't
				 * check for them here as well. */
				sigmask_ensure_unmasked_mandatory_after_except(sigmask);
				RETHROW();
			}
			sigmask_ensure_unmasked_mandatory_after_syscall(sigmask, -EOK);
			break;

		case SIG_UNBLOCK: {
			size_t i;
			/* No need to check for mandatory masks being clear, since
			 * this command is only able to clear masks from the get-go. */
			/* sigandnset(&sigmask->sm_mask, &sigmask->sm_mask, set); */
			for (i = 0; i < COMPILER_LENOF(sigmask->sm_mask.__val); ++i)
				sigmask->sm_mask.__val[i] &= ~set->__val[i];
			/* Since signals (may) have just gotten unmasked, check if we're
			 * now able to handle any of the pending signals. */
			sigmask_check_after_syscall(-EOK);
		}	break;

		case SIG_SETMASK:
			TRY {
				memcpy(&sigmask->sm_mask, set, sizeof(sigset_t));
			} EXCEPT {
				/* Same as with `SIG_BLOCK': Check that mandatory signals remain under control. */
				sigmask_ensure_unmasked_mandatory_after_except(sigmask);
				RETHROW();
			}
			/* Make sure that mandatory signals are in check */
			sigdelset(&sigmask->sm_mask, SIGKILL);
			sigdelset(&sigmask->sm_mask, SIGSTOP);
			COMPILER_BARRIER();
			/* Always check for pending signals, since
			 * anything may have happened to our mask. */
			sigmask_check_after_syscall(-EOK);
			break;

		default:
			THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
			      E_INVALID_ARGUMENT_CONTEXT_SIGPROCMASK_HOW,
			      how);
		}
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGPROCMASK */

#ifdef __ARCH_WANT_SYSCALL_SIGPROCMASK
DEFINE_SYSCALL3(errno_t, sigprocmask, syscall_ulong_t, how,
                UNCHECKED USER sigset_t const *, set,
                UNCHECKED USER sigset_t *, oset) {
	return sys_rt_sigprocmask(how, set, oset, sizeof(sigset_t));
}
#endif /* __ARCH_WANT_SYSCALL_SIGPROCMASK */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SIGPROCMASK
DEFINE_COMPAT_SYSCALL3(errno_t, sigprocmask, syscall_ulong_t, how,
                       UNCHECKED USER compat_sigset_t const *, set,
                       UNCHECKED USER compat_sigset_t *, oset) {
	return sys_rt_sigprocmask(how, set, oset, sizeof(compat_sigset_t));
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SIGPROCMASK */





/************************************************************************/
/* sgetmask(), ssetmask()                                               */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SGETMASK
DEFINE_SYSCALL0(syscall_ulong_t, sgetmask) {
	syscall_ulong_t result;
	struct kernel_sigmask *mymask;
	mymask = sigmask_getrd();
	assert(mymask);
#if __SIZEOF_SIGSET_T__ < __SIZEOF_SYSCALL_LONG_T__
	result = 0;
#endif /* __SIZEOF_SIGSET_T__ < __SIZEOF_SYSCALL_LONG_T__ */
	memcpy(&result, &mymask->sm_mask,
	       MIN(sizeof(mymask->sm_mask), sizeof(result)));
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_SGETMASK */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SGETMASK
DEFINE_COMPAT_SYSCALL0(syscall_ulong_t, sgetmask) {
	compat_syscall_ulong_t result;
	struct kernel_sigmask *mymask;
	mymask = sigmask_getrd();
	assert(mymask);
#if __SIZEOF_SIGSET_T__ < __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T
	result = 0;
#endif /* __SIZEOF_SIGSET_T__ < __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T */
	memcpy(&result, &mymask->sm_mask,
	       MIN(sizeof(mymask->sm_mask), sizeof(result)));
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SGETMASK */

#ifdef __ARCH_WANT_SYSCALL_SSETMASK
DEFINE_SYSCALL1(syscall_ulong_t, ssetmask, syscall_ulong_t, sigmask) {
	syscall_ulong_t result;
	struct kernel_sigmask *mymask;
	mymask = sigmask_getwr();
#if __SIZEOF_SIGSET_T__ < __SIZEOF_SYSCALL_LONG_T__
	result = 0;
#endif /* __SIZEOF_SIGSET_T__ < __SIZEOF_SYSCALL_LONG_T__ */
	memcpy(&result, &mymask->sm_mask,
	       MIN(sizeof(mymask->sm_mask), sizeof(result)));
	memcpy(&mymask->sm_mask, &sigmask,
	       MIN(sizeof(mymask->sm_mask), sizeof(sigmask)));
#if __SIZEOF_SIGSET_T__ > __SIZEOF_SYSCALL_LONG_T__
	memset((byte_t *)&mymask->sm_mask + sizeof(sigmask),
	       0, sizeof(mymask->sm_mask) - sizeof(sigmask));
#endif /* __SIZEOF_SIGSET_T__ > __SIZEOF_SYSCALL_LONG_T__ */
	/* Make sure that these two signals aren't being masked! */
	sigdelset(&mymask->sm_mask, SIGKILL);
	sigdelset(&mymask->sm_mask, SIGSTOP);
	sigmask_check_after_syscall(result);
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_SSETMASK */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SSETMASK
DEFINE_COMPAT_SYSCALL1(syscall_ulong_t, ssetmask, syscall_ulong_t, sigmask) {
	compat_syscall_ulong_t result;
	compat_syscall_ulong_t used_sigmask;
	struct kernel_sigmask *mymask;
	mymask = sigmask_getwr();
	used_sigmask = (compat_syscall_ulong_t)sigmask;
#if __SIZEOF_SIGSET_T__ < __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T
	result = 0;
#endif /* __SIZEOF_SIGSET_T__ < __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T */
	memcpy(&result, &mymask->sm_mask,
	       MIN(sizeof(mymask->sm_mask), sizeof(result)));
	memcpy(&mymask->sm_mask, &used_sigmask,
	       MIN(sizeof(mymask->sm_mask), sizeof(used_sigmask)));
#if __SIZEOF_SIGSET_T__ > __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T
	memset((byte_t *)&mymask->sm_mask + sizeof(used_sigmask),
	       0, sizeof(mymask->sm_mask) - sizeof(used_sigmask));
#endif /* __SIZEOF_SIGSET_T__ > __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T */
	/* Make sure that these two signals aren't being masked! */
	sigdelset(&mymask->sm_mask, SIGKILL);
	sigdelset(&mymask->sm_mask, SIGSTOP);
	sigmask_check_after_syscall(result);
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SSETMASK */


LOCAL WUNUSED ATTR_PURE NONNULL((1)) size_t KCALL
get_pid_indirection(struct task const *__restrict thread) {
	struct taskpid *pid = FORTASK(thread, this_taskpid);
	return likely(pid) ? pid->tp_pidns->pn_indirection : 0;
}

LOCAL WUNUSED ATTR_PURE NONNULL((1)) upid_t KCALL
taskpid_getpid_ind(struct taskpid *__restrict self, size_t ind) {
	if likely(ind <= self->tp_pidns->pn_indirection)
		return self->tp_pids[ind];
	return 0;
}





/************************************************************************/
/* kill(), tgkill(), tkill()                                            */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_KILL
DEFINE_SYSCALL2(errno_t, kill, pid_t, pid, signo_t, signo) {
	REF struct task *target;
	struct taskpid *mypid;
	siginfo_t info;
	memset(&info, 0, sizeof(siginfo_t));
	/* Make sure we've been given a valid signal number. */
	if unlikely(signo <= 0 || signo >= NSIG)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO, signo);
	info.si_signo = signo;
	info.si_errno = 0;
	info.si_code  = SI_USER;
	info.si_uid   = cred_geteuid();
	mypid         = THIS_TASKPID;
	if (pid > 0) {
		/* Kill the thread matching `pid'. */
		target = pidns_lookup_task(THIS_PIDNS, (upid_t)pid);
		FINALLY_DECREF_UNLIKELY(target);
		info.si_pid = taskpid_getpid_ind(mypid, get_pid_indirection(target));
		if (!task_raisesignalthread(target, &info))
			THROW(E_PROCESS_EXITED, task_gettid_of_s(target));
	} else if (pid == 0) {
		/* Kill all processes in the calling thread's process group. */
		target = task_getprocessgroupleader_srch();
		goto do_inherit_target_and_raise_processgroup;
	} else if (pid == -1) {
		/* TODO: Kill all processes that we're allowed to (except for pid=1). */
		THROW(E_NOT_IMPLEMENTED_TODO);
	} else {
		/* Kill the entirety of a process group. */
		target = pidns_lookup_task(THIS_PIDNS, (upid_t)-pid);
do_inherit_target_and_raise_processgroup:
		FINALLY_DECREF_UNLIKELY(target);
		info.si_pid = taskpid_getpid_ind(mypid, get_pid_indirection(target));;
		if (!task_raisesignalprocessgroup(target, &info))
			THROW(E_PROCESS_EXITED, task_getpid_of_s(target));
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_KILL */

#ifdef __ARCH_WANT_SYSCALL_TGKILL
DEFINE_SYSCALL3(errno_t, tgkill,
                pid_t, tgid, pid_t, pid,
                signo_t, signo) {
	REF struct task *target;
	if unlikely(signo < 0 || signo >= NSIG)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO,
		      signo);
	if unlikely(pid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID,
		      pid);
	if unlikely(tgid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_TGID,
		      tgid);
	target = pidns_lookup_task(THIS_PIDNS, (upid_t)pid);
	FINALLY_DECREF_UNLIKELY(target);
	/* Check if the given TGID matches the group of this thread. */
	if (taskpid_getpid_s(task_getprocesspid_of(target)) != (upid_t)tgid) {
		/* Maybe not necessarily exited, but no need to create a new exception type for this... */
		THROW(E_PROCESS_EXITED, tgid);
	}
	/* Don't deliver signal `0'. - It's used to test access. */
	if (signo != 0) {
		siginfo_t info;
		memset(&info, 0, sizeof(siginfo_t));
		info.si_signo = signo;
		info.si_errno = 0;
		info.si_code  = SI_TKILL;
		info.si_uid   = cred_geteuid();
		info.si_pid   = taskpid_getpid_ind(THIS_TASKPID, get_pid_indirection(target));
		if (!task_raisesignalthread(target, &info))
			THROW(E_PROCESS_EXITED, task_gettid_of_s(target));
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_TGKILL */

#ifdef __ARCH_WANT_SYSCALL_TKILL
DEFINE_SYSCALL2(errno_t, tkill, pid_t, pid, signo_t, signo) {
	REF struct task *target;
	if unlikely(signo < 0 || signo >= NSIG)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO, signo);
	if unlikely(pid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID, pid);
	target = pidns_lookup_task(THIS_PIDNS, (upid_t)pid);
	FINALLY_DECREF_UNLIKELY(target);
	/* Don't deliver signal `0'. - It's used to test access. */
	if (signo != 0) {
		siginfo_t info;
		memset(&info, 0, sizeof(siginfo_t));
		info.si_signo = signo;
		info.si_errno = 0;
		info.si_code  = SI_TKILL;
		info.si_uid   = cred_geteuid();
		info.si_pid   = taskpid_getpid_ind(THIS_TASKPID, get_pid_indirection(target));
		if (!task_raisesignalthread(target, &info))
			THROW(E_PROCESS_EXITED, task_gettid_of_s(target));
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_TKILL */





/************************************************************************/
/* rt_sigqueueinfo(), rt_tgsigqueueinfo()                               */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_RT_SIGQUEUEINFO
DEFINE_SYSCALL3(errno_t, rt_sigqueueinfo,
                pid_t, tgid, signo_t, signo,
                USER UNCHECKED siginfo_t const *, uinfo) {
	REF struct task *target;
	siginfo_t info;
	if unlikely(tgid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID, tgid);
	if unlikely(signo < 0 || signo >= NSIG)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO, signo);
	validate_readable(uinfo, sizeof(siginfo_t));
	memcpy(&info, uinfo, sizeof(siginfo_t));
	COMPILER_READ_BARRIER();
	info.si_signo = signo;
	target        = pidns_lookup_task(THIS_PIDNS, (upid_t)tgid);
	FINALLY_DECREF_UNLIKELY(target);
	/* Don't allow sending arbitrary signals to other processes. */
	if ((info.si_code >= 0 || info.si_code == SI_TKILL) &&
	    (task_getprocess_of(target) != task_getprocess()))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE,
		      info.si_code);
	if (signo != 0) {
		if (!task_raisesignalprocess(target, &info))
			THROW(E_PROCESS_EXITED, task_getpid_of_s(target));
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGQUEUEINFO */

#ifdef __ARCH_WANT_SYSCALL_RT_TGSIGQUEUEINFO
DEFINE_SYSCALL4(errno_t, rt_tgsigqueueinfo,
                pid_t, tgid, pid_t, tid, signo_t, signo,
                USER UNCHECKED siginfo_t const *, uinfo) {
	siginfo_t info;
	REF struct task *target;
	struct task *leader;
	if unlikely(tgid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID, tgid);
	if unlikely(tid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID, tid);
	if unlikely(signo < 0 || signo >= NSIG)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO, signo);
	validate_readable(uinfo, sizeof(siginfo_t));
	memcpy(&info, uinfo, sizeof(siginfo_t));
	COMPILER_READ_BARRIER();
	info.si_signo = signo;
	target = pidns_lookup_task(THIS_PIDNS, (upid_t)tid);
	FINALLY_DECREF_UNLIKELY(target);
	/* Don't allow sending arbitrary signals to other processes. */
	leader = task_getprocess_of(target);
	if ((info.si_code >= 0 || info.si_code == SI_TKILL) && leader != task_getprocess())
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE,
		      info.si_code);
	/* Check if the thread-group ID matches that of the leader of the requested thread-group. */
	if (task_gettid_of_s(leader) != (upid_t)tgid)
		THROW(E_PROCESS_EXITED, tgid);
	if (signo != 0) {
		if (!task_raisesignalthread(target, &info))
			THROW(E_PROCESS_EXITED, task_gettid_of_s(target));
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_RT_TGSIGQUEUEINFO */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RT_SIGQUEUEINFO
DEFINE_COMPAT_SYSCALL3(errno_t, rt_sigqueueinfo,
                       pid_t, tgid, signo_t, signo,
                       USER UNCHECKED compat_siginfo_t const *, uinfo) {
	REF struct task *target;
	siginfo_t info;
	if unlikely(tgid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID, tgid);
	if unlikely(signo < 0 || signo >= NSIG)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO, signo);
	validate_readable(uinfo, sizeof(compat_siginfo_t));
	compat_siginfo_to_siginfo(uinfo, &info);
	COMPILER_READ_BARRIER();
	info.si_signo = signo;
	target        = pidns_lookup_task(THIS_PIDNS, (upid_t)tgid);
	FINALLY_DECREF_UNLIKELY(target);
	/* Don't allow sending arbitrary signals to other processes. */
	if ((info.si_code >= 0 || info.si_code == SI_TKILL) &&
	    (task_getprocess_of(target) != task_getprocess()))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE,
		      info.si_code);
	if (signo != 0) {
		if (!task_raisesignalprocess(target, &info))
			THROW(E_PROCESS_EXITED, task_getpid_of_s(target));
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RT_SIGQUEUEINFO */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RT_TGSIGQUEUEINFO
DEFINE_COMPAT_SYSCALL4(errno_t, rt_tgsigqueueinfo,
                       pid_t, tgid, pid_t, tid, signo_t, signo,
                       USER UNCHECKED compat_siginfo_t const *, uinfo) {
	siginfo_t info;
	REF struct task *target;
	struct task *leader;
	if unlikely(tgid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID, tgid);
	if unlikely(tid <= 0)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_PID, tid);
	if unlikely(signo < 0 || signo >= NSIG)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGNO, signo);
	validate_readable(uinfo, sizeof(compat_siginfo_t));
	compat_siginfo_to_siginfo(uinfo, &info);
	COMPILER_READ_BARRIER();
	info.si_signo = signo;
	target = pidns_lookup_task(THIS_PIDNS, (upid_t)tid);
	FINALLY_DECREF_UNLIKELY(target);
	/* Don't allow sending arbitrary signals to other processes. */
	leader = task_getprocess_of(target);
	if ((info.si_code >= 0 || info.si_code == SI_TKILL) && leader != task_getprocess())
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE,
		      info.si_code);
	/* Check if the thread-group ID matches that of the leader of the requested thread-group. */
	if (task_gettid_of_s(leader) != (upid_t)tgid)
		THROW(E_PROCESS_EXITED, tgid);
	if (signo != 0) {
		if (!task_raisesignalthread(target, &info))
			THROW(E_PROCESS_EXITED, task_gettid_of_s(target));
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RT_TGSIGQUEUEINFO */





/************************************************************************/
/* rt_sigtimedwait(), rt_sigtimedwait64()                               */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT) ||        \
     defined(__ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT64) ||      \
     defined(__ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT64))
#define WANT_SIGTIMEDWAIT 1
#endif /* ... */

#ifdef WANT_SIGTIMEDWAIT
/* @return: NULL : No signal was detected
 * @return: *    : The accepted signal entry (must be inherited by the caller) */
PRIVATE struct sigqueue_entry *KCALL
signal_try_steal_pending(sigset_t const *__restrict these) {
	struct kernel_sigmask *mask;
	struct sigqueue *myqueue;
	struct process_sigqueue *prqueue;
	struct sigqueue_entry *pending, **piter, *iter;
	bool has_write_lock = false;
	mask = sigmask_getrd();
	myqueue = &THIS_SIGQUEUE;
	/* Temporarily steal all pending per-thread signals. */
	do {
		pending = ATOMIC_READ(myqueue->sq_queue);
		if (!pending)
			goto no_perthread_pending; /* No signals are pending for the calling thread */
		if unlikely(pending == SIGQUEUE_SQ_QUEUE_TERMINATED)
			return NULL; /* Shouldn't happen: The calling thread is currently terminating. */
	} while (!ATOMIC_CMPXCH_WEAK(myqueue->sq_queue, pending, NULL));
	/* Go through pending signals and check if there are any that aren't being masked. */
	iter  = pending;
	piter = &pending;
	do {
		if (sigismember(these, iter->sqe_info.si_signo)) {
			/* Found one that's not being masked. */
			*piter = iter->sqe_next;
			if (pending)
				restore_perthread_pending_signals(myqueue, pending);
			/* Got a signal! */
			return iter;
		}
	} while ((iter = *(piter = &iter->sqe_next)) != NULL);
	/* Must also check if there is a pending signal
	 * that isn't masked by our active signal mask. */
	iter  = pending;
	piter = &pending;
	do {
		if (!sigismember(&mask->sm_mask, iter->sqe_info.si_signo)) {
			/* Found one that's not being masked. */
			*piter = iter->sqe_next;
			if (pending)
				restore_perthread_pending_signals(myqueue, pending);
			/* Deliver the signal to ourself */
			send_signal_rpc_to_self(iter);
			break;
		}
	} while ((iter = *(piter = &iter->sqe_next)) != NULL);
	/* Restore all signals pending for the calling thread. */
	restore_perthread_pending_signals(myqueue, pending);
no_perthread_pending:
	/* With per-task signals checked, also check for per-process signals */
	prqueue = &THIS_PROCESS_SIGQUEUE;
	sync_read(prqueue);
again_scan_prqueue:
	piter = &prqueue->psq_queue.sq_queue;
	while ((iter = *piter) != NULL) {
		if (sigismember(these, iter->sqe_info.si_signo)) {
			if (!has_write_lock) {
				has_write_lock = true;
				if (!sync_upgrade(prqueue))
					goto again_scan_prqueue;
			}
			/* Steal this signal packet. */
			*piter = iter->sqe_next;
			sync_endwrite(prqueue);
			return iter;
		}
		piter = &iter->sqe_next;
	}
	if (has_write_lock)
		sync_downgrade(prqueue);
	/* Must also check if there is a pending signal
	 * that isn't masked by our active signal mask. */
	for (iter = prqueue->psq_queue.sq_queue;
	     iter; iter = iter->sqe_next) {
		if (sigismember(&mask->sm_mask, iter->sqe_info.si_signo))
			continue;
		/* Found an unmasked signal. */
		sync_endread(prqueue);
		task_schedule_user_rpc(THIS_TASK,
		                       &task_sigmask_check_rpc_handler,
		                       NULL,
		                       TASK_USER_RPC_FINTR,
		                       GFP_NORMAL);
		__builtin_unreachable();
	}
	sync_endread(prqueue);
	return NULL;
}


/* @return: 0 : The timeout has expired
 * @return: * : The accepted signal number */
PRIVATE syscall_ulong_t KCALL
signal_waitfor(CHECKED USER sigset_t const *uthese,
               CHECKED USER siginfo_t *uinfo,
               struct timespec const *abs_timeout) {
	sigset_t these;
	syscall_ulong_t result;
	assert(!task_isconnected());
	memcpy(&these, uthese, sizeof(sigset_t));
	COMPILER_BARRIER();
	/* Make sure that we don't steal these signals */
	sigdelset(&these, SIGKILL);
	sigdelset(&these, SIGSTOP);
	COMPILER_WRITE_BARRIER();
	for (;;) {
		struct sigqueue_entry *ent;
		ent = signal_try_steal_pending(&these);
		if (ent) {
copy_and_free_ent_info:
			result = ent->sqe_info.si_signo;
			if (uinfo) {
				TRY {
					memcpy(uinfo, &ent->sqe_info, sizeof(siginfo_t));
				} EXCEPT {
					kfree(ent);
					RETHROW();
				}
			}
			kfree(ent);
			break;
		}
		/* Connect to the signals that get broadcast when new signals arrive. */
		TRY {
			task_connect(&THIS_SIGQUEUE.sq_newsig);
			task_connect(&THIS_PROCESS_SIGQUEUE.psq_queue.sq_newsig);
			/* Check for pending signals once again, now that
			 * we're interlocked their them possibly appearing. */
			ent = signal_try_steal_pending(&these);
			if unlikely(ent) {
				task_disconnectall();
				goto copy_and_free_ent_info;
			}
		} EXCEPT {
			task_disconnectall();
			RETHROW();
		}
		/* Wait for new signals to be delivered. */
		if (!task_waitfor(abs_timeout)) {
			result = 0;
			break;
		}
	}
	return result;
}
#endif /* WANT_SIGTIMEDWAIT */

#ifdef __ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT
DEFINE_SYSCALL4(syscall_slong_t, rt_sigtimedwait,
                UNCHECKED USER sigset_t const *, uthese,
                UNCHECKED USER siginfo_t *, uinfo,
                UNCHECKED USER struct timespec32 const *, uts,
                size_t, sigsetsize) {
	syscall_slong_t result;
	/* Validate user-structure pointers. */
	validate_readable(uthese, sigsetsize);
	validate_writable(uinfo, sizeof(siginfo_t));
	if (uts) {
		struct timespec tms;
		validate_readable(uts, sizeof(*uts));
		COMPILER_READ_BARRIER();
		tms.tv_sec  = (time_t)uts->tv_sec;
		tms.tv_nsec = uts->tv_nsec;
		COMPILER_READ_BARRIER();
		if (tms.tv_sec || tms.tv_nsec)
			tms += realtime();
		result = (syscall_slong_t)signal_waitfor(uthese, uinfo, &tms);
	} else {
		result = (syscall_slong_t)signal_waitfor(uthese, uinfo, NULL);
	}
	if (!result)
		result = -EAGAIN; /* Posix says EAGAIN for this. */
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT */

#ifdef __ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT64
DEFINE_SYSCALL4(syscall_slong_t, rt_sigtimedwait64,
                UNCHECKED USER sigset_t const *, uthese,
                UNCHECKED USER siginfo_t *, uinfo,
                UNCHECKED USER struct timespec64 const *, uts,
                size_t, sigsetsize) {
	syscall_slong_t result;
	/* Validate user-structure pointers. */
	validate_readable(uthese, sigsetsize);
	validate_writable(uinfo, sizeof(siginfo_t));
	if (uts) {
		struct timespec tms;
		validate_readable(uts, sizeof(*uts));
		COMPILER_READ_BARRIER();
		tms.tv_sec  = (time_t)uts->tv_sec;
		tms.tv_nsec = uts->tv_nsec;
		COMPILER_READ_BARRIER();
		if (tms.tv_sec || tms.tv_nsec)
			tms += realtime();
		result = (syscall_slong_t)signal_waitfor(uthese, uinfo, &tms);
	} else {
		result = (syscall_slong_t)signal_waitfor(uthese, uinfo, NULL);
	}
	if (!result)
		result = -EAGAIN; /* Posix says EAGAIN for this. */
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGTIMEDWAIT64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT
DEFINE_COMPAT_SYSCALL4(syscall_slong_t, rt_sigtimedwait,
                       UNCHECKED USER compat_sigset_t const *, uthese,
                       UNCHECKED USER compat_siginfo_t *, uinfo,
                       UNCHECKED USER struct compat_timespec32 const *, uts,
                       size_t, sigsetsize) {
	syscall_slong_t result;
	siginfo_t info;
	/* Validate user-structure pointers. */
	validate_readable(uthese, sigsetsize);
	validate_writable(uinfo, sizeof(compat_siginfo_t));
	compat_siginfo_to_siginfo(uinfo, &info);
	if (uts) {
		struct timespec tms;
		validate_readable(uts, sizeof(*uts));
		COMPILER_READ_BARRIER();
		tms.tv_sec  = (time_t)uts->tv_sec;
		tms.tv_nsec = uts->tv_nsec;
		COMPILER_READ_BARRIER();
		if (tms.tv_sec || tms.tv_nsec)
			tms += realtime();
		result = (syscall_slong_t)signal_waitfor(uthese, &info, &tms);
	} else {
		result = (syscall_slong_t)signal_waitfor(uthese, &info, NULL);
	}
	if (!result)
		result = -EAGAIN; /* Posix says EAGAIN for this. */
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT64
DEFINE_COMPAT_SYSCALL4(syscall_slong_t, rt_sigtimedwait64,
                       UNCHECKED USER compat_sigset_t const *, uthese,
                       UNCHECKED USER compat_siginfo_t *, uinfo,
                       UNCHECKED USER struct compat_timespec64 const *, uts,
                       size_t, sigsetsize) {
	syscall_slong_t result;
	siginfo_t info;
	/* Validate user-structure pointers. */
	validate_readable(uthese, sigsetsize);
	validate_writable(uinfo, sizeof(compat_siginfo_t));
	compat_siginfo_to_siginfo(uinfo, &info);
	if (uts) {
		struct timespec tms;
		validate_readable(uts, sizeof(*uts));
		COMPILER_READ_BARRIER();
		tms.tv_sec  = (time_t)uts->tv_sec;
		tms.tv_nsec = uts->tv_nsec;
		COMPILER_READ_BARRIER();
		if (tms.tv_sec || tms.tv_nsec)
			tms += realtime();
		result = (syscall_slong_t)signal_waitfor(uthese, &info, &tms);
	} else {
		result = (syscall_slong_t)signal_waitfor(uthese, &info, NULL);
	}
	if (!result)
		result = -EAGAIN; /* Posix says EAGAIN for this. */
	return result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RT_SIGTIMEDWAIT64 */





/************************************************************************/
/* rt_sigsuspend(), sigsuspend()                                        */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_RT_SIGSUSPEND
#undef sigmask
LOCAL void KCALL
sigmask_ensure_unmasked_mandatory(struct kernel_sigmask *__restrict sigmask) {
	/* Make sure that everything got written. */
	COMPILER_BARRIER();
	/* Ensure that SIGKILL and SIGSTOP aren't masked.
	 * If either got accidentally (or intentionally) got masked, unmask them
	 * and manually check for pending signals (in case some got delivered between
	 * the point when they got masked, and the point when we unmask them below) */
	if unlikely(sigismember(&sigmask->sm_mask, SIGKILL) ||
	            sigismember(&sigmask->sm_mask, SIGSTOP)) {
		sigdelset(&sigmask->sm_mask, SIGKILL);
		sigdelset(&sigmask->sm_mask, SIGSTOP);
		COMPILER_BARRIER();
		sigmask_check();
	}
}

PRIVATE struct icpustate *FCALL
sys_rt_sigsuspend_impl(struct icpustate *__restrict state,
                       USER UNCHECKED sigset_t const *uthese,
                       struct rpc_syscall_info const *sc_info) {
	struct kernel_sigmask *mymask;
	sigset_t oldmask;
	validate_readable(uthese, sizeof(sigset_t));
	mymask = sigmask_getwr();
	memcpy(&oldmask, &mymask->sm_mask, sizeof(sigset_t));
	TRY {
		memcpy(&mymask->sm_mask, uthese, sizeof(sigset_t));
	} EXCEPT {
		/* Always restore the old signal mask and check for signals,
		 * so-as to prevent signals that always have to be masked from
		 * ever being unmasked. */
		memcpy(&mymask->sm_mask, &oldmask, sizeof(sigset_t));
		sigmask_check();
		RETHROW();
	}
	TRY {
		/* Make sure that mandatory signals aren't masked. */
		sigmask_ensure_unmasked_mandatory(mymask);

		/* Check if there are any pending signals which we should serve.
		 * NOTE: This _has_ to be an immediate signal mask check.
		 *       (see the explanation below, especially case #1) */

		/* XXX: POSIX says that we should only handle SIG_TERM (which we do
		 *      unconditionally), as well as custom user-space signal handlers.
		 *      Currently, this call to `sigmask_check_s()' will also return
		 *      something other than `TASK_RPC_RESTART_SYSCALL' for other
		 *      dispositions (including SIG_IGN).
		 * POSIX doesn't say if we're allowed to do this as an extension, but
		 * in general I already feel like allowing sigsuspend() to return for
		 * unmasked signals, irregardless of their disposition is the most
		 * correct thing to do (i.e. what we're already doing at the moment).
		 *
		 * So if it turns our that POSIX _really_ doesn't want us to have sigsuspend()
		 * return for SIG_IGN (i.e. I come across a program that relies on POSIX
		 * compliant behavior, and patching it would be too complicated), the there
		 * should at the very least be a KP_* personality (<kos/personality.h>) to
		 * have the sigsuspend() return irregardless of disposition! */
		state = sigmask_check_s(state, sc_info);
		if (state == TASK_RPC_RESTART_SYSCALL) {
			/* Wait forever until something happens.
			 * NOTE: Once a signal become available, task_serve() will
			 *       throw an exception that will do one of 2 things.
			 * In every case, our EXCEPT below will get executed,
			 * and we will restore the previous signal mask.
			 * Afterwards, execution will end up in `task_signal_rpc_handler()',
			 * which will check if the original signal mask (the one we've restored
			 * below) is blocking the signal.
			 *
			 *   #1: If it is, then it will schedule the signal as pending for our thread,
			 *       and unconditionally restart our interrupted system call, which will
			 *       cause control flow to re-enter this function.
			 *       Only at that point, our call to `sigmask_check_s()' will notice that
			 *       an unmasked signal is available, which will cause it to IMMEDIATELY
			 *       update the real user-space `state' to point to the associated signal
			 *       handler.
			 *       Note my use of IMMEDIATELY. It is important that we can handle signals
			 *       directly, and not make use of `sigmask_check()' at that point, since
			 *       that function will throw an E_INTERRUPT if an unmasked signal is present,
			 *       which would cause the EXCEPT below to restore the old signal mask, before
			 *       `task_signal_rpc_handler()' would notice that it was called for a signal
			 *       that is being masked, which would result in it scheduling the signal as
			 *       pending, and forceably restarting our system call, only for us to end up
			 *       at the call to `sigmask_check()', which would do the same over and over,
			 *       leading to us being stuck in a soft-lock.
			 *
			 *   #2: Old user-space also didn't have the signal blocked (unlikely case,
			 *       since the whole idea behind sigsuspend() is to allow user-space a
			 *       way of performing interlocked waits for signals, such that it can
			 *       be guarantied that waiting never starts if a signal was marked as
			 *       pending between a prior call to sigprocmask(2) and now)
			 *       In this case, `task_signal_rpc_handler()' will do the job of handling
			 *       the signal by performing the user-space requested signal-handle operation.
			 */
			for (;;) {
				PREEMPTION_DISABLE();
				/* Service RPC callbacks (which include the handling of signals) */
				if (task_serve())
					continue;
				/* Sleep until the next sporadic wakeup */
				task_sleep();
			}
		}
	} EXCEPT {
		/* Restore the old mask. */
		memcpy(&mymask->sm_mask, &oldmask, sizeof(sigset_t));
		sigmask_check_after_except();
		RETHROW();
	}
	/* Restore the old signal mask.
	 * FIXME: This is wrong! We only get here after we're received a signal. However,
	 *        the associated handler may have already changed the signal mask once
	 *        again (by or'ing it with its own mask), such that us restoring the old
	 *        mask here will over-ride its efforts.
	 *     -> The correct thing to do here would be not to use `sigmask_check_s()'
	 *        above, but instead use a custom function that will restore `oldmask'
	 *        _before_ calling `handle_signal()' for the first time. */
	memcpy(&mymask->sm_mask, &oldmask, sizeof(sigset_t));
	sigmask_check();

	return state;
}

PRIVATE WUNUSED NONNULL((2)) struct icpustate *FCALL
syscall_rt_sigsuspend_rpc(void *UNUSED(arg),
                          struct icpustate *__restrict state,
                          unsigned int reason,
                          struct rpc_syscall_info const *sc_info) {
	if (reason == TASK_RPC_REASON_SYSCALL) {
		state = sys_rt_sigsuspend_impl(state,
		                               (USER UNCHECKED sigset_t const *)sc_info->rsi_regs[0],
		                               sc_info);
	}
	return state;
}


DEFINE_SYSCALL2(errno_t, rt_sigsuspend,
                USER UNCHECKED sigset_t const *, uthese,
                size_t, sigsetsize) {
	(void)uthese;
	if unlikely(sigsetsize != sizeof(sigset_t)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	}
	/* Send an RPC to ourself, so we can gain access to the user-space register state. */
	task_schedule_user_rpc(THIS_TASK,
	                       &syscall_rt_sigsuspend_rpc,
	                       NULL,
	                       TASK_RPC_FHIGHPRIO |
	                       TASK_USER_RPC_FINTR,
	                       GFP_NORMAL);
	__builtin_unreachable();
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGSUSPEND */

#ifdef __ARCH_WANT_SYSCALL_SIGSUSPEND
DEFINE_SYSCALL1(errno_t, sigsuspend,
                USER UNCHECKED sigset_t const *, uthese) {
	return sys_rt_sigsuspend(uthese, sizeof(sigset_t));
}
#endif /* __ARCH_WANT_SYSCALL_SIGSUSPEND */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SIGSUSPEND
DEFINE_COMPAT_SYSCALL1(errno_t, sigsuspend,
                       USER UNCHECKED compat_sigset_t const *, uthese) {
	return sys_rt_sigsuspend(uthese, sizeof(compat_sigset_t));
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SIGSUSPEND */





/************************************************************************/
/* rt_sigpending(), sigpending()                                        */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_RT_SIGPENDING
/* Gather the set of pending signals. */
LOCAL void KCALL
signal_gather_pending(sigset_t *__restrict these) {
	struct kernel_sigmask *mymask;
	struct sigqueue *myqueue;
	struct process_sigqueue *prqueue;
	struct sigqueue_entry *pending, **piter, *iter;
	mymask = sigmask_getrd();
	myqueue = &THIS_SIGQUEUE;
	/* Temporarily steal all pending per-thread signals. */
	do {
		pending = ATOMIC_READ(myqueue->sq_queue);
		if (!pending)
			goto no_perthread_pending; /* No signals are pending for the calling thread */
		if unlikely(pending == SIGQUEUE_SQ_QUEUE_TERMINATED)
			return; /* Shouldn't happen: The calling thread is currently terminating. */
	} while (!ATOMIC_CMPXCH_WEAK(myqueue->sq_queue, pending, NULL));
	iter  = pending;
	piter = &pending;
	do {
		if (!sigismember(&mymask->sm_mask, iter->sqe_info.si_signo)) {
			/* Found one that's not being masked. */
			*piter = iter->sqe_next;
			if (pending)
				restore_perthread_pending_signals(myqueue, pending);
			/* Deliver the signal to ourself */
			send_signal_rpc_to_self(iter);
			break;
		}
		sigaddset(these, iter->sqe_info.si_signo);
	} while ((iter = *(piter = &iter->sqe_next)) != NULL);
	/* Restore all signals pending for the calling thread. */
	restore_perthread_pending_signals(myqueue, pending);
no_perthread_pending:
	/* With per-task signals checked, also check for per-process signals */
	prqueue = &THIS_PROCESS_SIGQUEUE;
	sync_read(prqueue);
	for (iter = prqueue->psq_queue.sq_queue;
	     iter; iter = iter->sqe_next) {
		if (sigismember(&mymask->sm_mask, iter->sqe_info.si_signo)) {
			sigaddset(these, iter->sqe_info.si_signo);
			continue;
		}
		/* Found an unmasked signal. */
		sync_endread(prqueue);
		task_schedule_user_rpc(THIS_TASK,
		                       &task_sigmask_check_rpc_handler,
		                       NULL,
		                       TASK_USER_RPC_FINTR,
		                       GFP_NORMAL);
		__builtin_unreachable();
	}
	sync_endread(prqueue);
}

DEFINE_SYSCALL2(errno_t, rt_sigpending,
                UNCHECKED USER sigset_t *, uset,
                size_t, sigsetsize) {
	sigset_t pending;
	/* Validate the user-space signal set pointer. */
	if unlikely(sigsetsize != sizeof(sigset_t))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	validate_writable(uset, sizeof(sigset_t));
	memset(&pending, 0, sizeof(pending));
	signal_gather_pending(&pending);
	COMPILER_WRITE_BARRIER();
	memcpy(uset, &pending, sizeof(pending));
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_RT_SIGPENDING */

#ifdef __ARCH_WANT_SYSCALL_SIGPENDING
DEFINE_SYSCALL1(errno_t, sigpending,
                UNCHECKED USER sigset_t *, uset) {
	return sys_rt_sigpending(uset, sizeof(sigset_t));
}
#endif /* __ARCH_WANT_SYSCALL_SIGPENDING */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SIGPENDING
DEFINE_COMPAT_SYSCALL1(errno_t, sigpending,
                       UNCHECKED USER compat_sigset_t *, uset) {
	return sys_rt_sigpending(uset, sizeof(compat_sigset_t));
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SIGPENDING */




DECL_END

#ifndef __INTELLISENSE__
#define DELIVER_NX 1
#include "posix-signal-deliver.c.inl"
#include "posix-signal-deliver.c.inl"
#endif /* !__INTELLISENSE__ */


#endif /* !GUARD_KERNEL_SRC_SCHED_POSIX_SIGNAL_C */
