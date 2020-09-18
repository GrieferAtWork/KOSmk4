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
#ifndef GUARD_KERNEL_SRC_SCHED_EXCEPT_HANDLER_C
#define GUARD_KERNEL_SRC_SCHED_EXCEPT_HANDLER_C 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/paging.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <kernel/vm.h>       /* DEFINE_PERVM_ONEXEC() */
#include <kernel/vm/futex.h> /* vm_futex_broadcast() */
#include <sched/except-handler.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <compat/config.h>
#include <kos/except-handler.h>
#include <kos/except/reason/inval.h>

#include <errno.h>
#include <sched.h>
#include <signal.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/except-handler.h>
#include <compat/kos/types.h>
#include <compat/pointer.h>
#include <compat/signal.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

/* User-space exception handler mode for the current thread. */
PUBLIC ATTR_PERTASK struct user_except_handler this_user_except_handler = {
	/* .ueh_mode    = */ EXCEPT_HANDLER_MODE_DISABLED,
	/* .ueh_handler = */ NULL,
	/* .ueh_stack   = */ EXCEPT_HANDLER_SP_CURRENT,
};

/* [0..1] User-space TID address used to implement functionality such as `pthread_join()'
 *        When the associated thread exits, it will:
 *        >> pid_t *addr = PERTASK_GET(this_tid_address);
 *        >> if (addr) {
 *        >>     TRY {
 *        >>         *addr = 0;
 *        >>         vm_futex_broadcast(addr);
 *        >>     } EXCEPT {
 *        >>         if (!was_thrown(E_SEGFAULT) ||
 *        >>             (PERTASK_GET(this_exception_args.e_segfault.s_addr) != (uintptr_t)addr))
 *        >>             error_printf("...");
 *        >>     }
 *        >> }
 * When a new thread is created by clone(), the `CLONE_CHILD_CLEARTID' flag will cause
 * the given `ctid' to be used as the initial value for `this_tid_address', while the
 * `CLONE_CHILD_SETTID' flag will cause the same address to be filled with the thread's
 * TID. */
PUBLIC ATTR_PERTASK USER CHECKED pid_t *this_tid_address = NULL;
DEFINE_PERTASK_ONEXIT(onexit_this_tid_address);
INTERN ATTR_USED void NOTHROW(KCALL onexit_this_tid_address)(void) {
	USER CHECKED pid_t *addr;
	addr = PERTASK_GET(this_tid_address);
	if (addr) {
		TRY {
			/* Special case for vfork when the kernel supports userprocmask. */
#ifdef CONFIG_HAVE_USERPROCMASK
			uintptr_t my_flags = PERTASK_GET(this_task.t_flags);
			if (my_flags & TASK_FVFORK) {
				if unlikely(my_flags & TASK_FUSERPROCMASK_AFTER_VFORK) {
					USER CHECKED struct userprocmask *um;
					um = (USER CHECKED struct userprocmask *)addr;
					/* Handle the special case of a vfork()'d thread having
					 * initialized their parent thread's userprocmask data
					 * structure.
					 * This is needed because userprocmask is part of a
					 * thread's user-space TLS state, which itself is part
					 * of that process's VM, which is the very thing that gets
					 * shared during a call to vfork(), meaning that we must
					 * uninitialize it if it wasn't the parent who did the init! */
					ATOMIC_WRITE(um->pm_sigmask, NULL);
				}
				return;
			}
#endif /* CONFIG_HAVE_USERPROCMASK */
			ATOMIC_WRITE(*addr, 0);
			vm_futex_broadcast(addr);
		} EXCEPT {
			/* Explicitly handle E_SEGFAULT:addr as a no-op */
			if (!was_thrown(E_SEGFAULT) ||
			    (PERTASK_GET(this_exception_args.e_segfault.s_addr) != (uintptr_t)addr)) {
				/* We can't RETHROW() the exception since our function
				 * has to be NOTHROW() (especially so since we're called
				 * as part of thread cleanup)
				 * Because of this, dump all other errors that happen here. */
				error_printf("Broadcasting tid_address=%p", addr);
			}
		}
	}
}


DEFINE_PERTASK_CLONE(clone_user_except_handler);
PRIVATE ATTR_USED NOBLOCK void
NOTHROW(KCALL clone_user_except_handler)(struct task *__restrict new_thread,
                                         uintptr_t flags) {
	(void)flags;
	memcpy(&FORTASK(new_thread, this_user_except_handler),
	       &PERTASK(this_user_except_handler),
	       sizeof(struct user_except_handler));
}

DEFINE_PERVM_ONEXEC(reset_user_except_handler);
PRIVATE ATTR_USED NOBLOCK void
NOTHROW(KCALL reset_user_except_handler)(void) {
	struct user_except_handler *hand;
	hand            = &PERTASK(this_user_except_handler);
	hand->ueh_mode  = EXCEPT_HANDLER_MODE_DISABLED;
	hand->ueh_stack = EXCEPT_HANDLER_SP_CURRENT;
	/* Reset the TID address of the calling thread. */
	PERTASK_SET(this_tid_address, (pid_t *)NULL);
#ifdef CONFIG_HAVE_USERPROCMASK
	/* Clear the userprocmask flag for our thread.
	 * Note that our caller will have already loaded userspace's
	 * final process mask into our kernel-space sigmask buffer.
	 *
	 * s.a. `kernel_do_execveat_impl()' */
	ATOMIC_FETCHAND(THIS_TASK->t_flags, ~TASK_FUSERPROCMASK);
#endif /* CONFIG_HAVE_USERPROCMASK */
}





/************************************************************************/
/* get_exception_handler(), set_exception_handler()                     */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_GET_EXCEPTION_HANDLER
DEFINE_SYSCALL3(errno_t, get_exception_handler,
                USER UNCHECKED syscall_ulong_t *, pmode,
                USER UNCHECKED except_handler_t *, phandler,
                USER UNCHECKED void **, phandler_sp) {
	struct user_except_handler *exc;
	exc = &PERTASK(this_user_except_handler);
	if (pmode) {
		validate_writable(pmode, sizeof(*pmode));
		COMPILER_WRITE_BARRIER();
		*pmode = exc->ueh_mode;
	}
	if (phandler) {
		validate_writable(phandler, sizeof(*phandler));
		COMPILER_WRITE_BARRIER();
		*phandler = exc->ueh_handler;
	}
	if (phandler_sp) {
		validate_writable(phandler_sp, sizeof(*phandler_sp));
		COMPILER_WRITE_BARRIER();
		*phandler_sp = exc->ueh_stack;
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_GET_EXCEPTION_HANDLER */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_GET_EXCEPTION_HANDLER
DEFINE_COMPAT_SYSCALL3(errno_t, get_exception_handler,
                       USER UNCHECKED compat_syscall_ulong_t *, pmode,
                       USER UNCHECKED compat_except_handler_t *, phandler,
                       USER UNCHECKED compat_ptr(void) *, phandler_sp) {
	struct user_except_handler *exc;
	exc = &PERTASK(this_user_except_handler);
	if (pmode) {
		compat_validate_writable(pmode, sizeof(*pmode));
		COMPILER_WRITE_BARRIER();
		*pmode = exc->ueh_mode;
	}
	if (phandler) {
		compat_validate_writable(phandler, sizeof(*phandler));
		COMPILER_WRITE_BARRIER();
		*phandler = (compat_except_handler_t)(uintptr_t)(void *)exc->ueh_handler;
	}
	if (phandler_sp) {
		compat_validate_writable(phandler_sp, sizeof(*phandler_sp));
		COMPILER_WRITE_BARRIER();
		*phandler_sp = exc->ueh_stack;
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_GET_EXCEPTION_HANDLER */

#ifdef __ARCH_WANT_SYSCALL_SET_EXCEPTION_HANDLER
DEFINE_SYSCALL3(errno_t, set_exception_handler,
                syscall_ulong_t, mode,
                USER UNCHECKED except_handler_t, handler,
                USER UNCHECKED void *, handler_sp) {
	struct user_except_handler *exc;
	exc = &PERTASK(this_user_except_handler);
	if ((mode & EXCEPT_HANDLER_MODE_MASK) > EXCEPT_HANDLER_MODE_SIGHAND)
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_SET_EXCEPTION_HANDLER_MODE,
		      mode & EXCEPT_HANDLER_MODE_MASK);
	VALIDATE_FLAGSET(mode & ~EXCEPT_HANDLER_MODE_MASK,
	                 EXCEPT_HANDLER_FLAG_ONESHOT |
	                 EXCEPT_HANDLER_FLAG_SETHANDLER |
	                 EXCEPT_HANDLER_FLAG_SETSTACK,
	                 E_INVALID_ARGUMENT_CONTEXT_SET_EXCEPTION_HANDLER_MODE);
	if (mode & EXCEPT_HANDLER_FLAG_SETHANDLER)
		validate_executable((void *)handler);
	if (mode & EXCEPT_HANDLER_FLAG_SETSTACK) {
		if (handler_sp != EXCEPT_HANDLER_SP_CURRENT) {
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
			validate_writable((byte_t *)handler_sp - 1, 1);
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
			validate_writable((byte_t *)handler_sp, 1);
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
		}
		exc->ueh_stack = handler_sp;
	}
	if (mode & EXCEPT_HANDLER_FLAG_SETHANDLER)
		exc->ueh_handler = handler;
	exc->ueh_mode &= ~(EXCEPT_HANDLER_FLAG_ONESHOT);
	exc->ueh_mode |= mode & (EXCEPT_HANDLER_FLAG_ONESHOT |
	                         EXCEPT_HANDLER_FLAG_SETHANDLER |
	                         EXCEPT_HANDLER_FLAG_SETSTACK);
	if ((mode & EXCEPT_HANDLER_MODE_MASK) != EXCEPT_HANDLER_MODE_UNCHANGED) {
		exc->ueh_mode &= ~EXCEPT_HANDLER_MODE_MASK;
		exc->ueh_mode |= mode & EXCEPT_HANDLER_MODE_MASK;
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SET_EXCEPTION_HANDLER */





/************************************************************************/
/* sigaltstack()                                                        */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SIGALTSTACK
DEFINE_SYSCALL2(errno_t, sigaltstack,
                USER UNCHECKED struct sigaltstack const *, ss,
                USER UNCHECKED struct sigaltstack *, oss) {
	void *sp;
	if (oss) {
		validate_writable(oss, sizeof(*oss));
		COMPILER_WRITE_BARRIER();
		sp = PERTASK_GET(this_user_except_handler.ueh_stack);
		oss->ss_flags = 0;
		if (sp == EXCEPT_HANDLER_SP_CURRENT) {
			oss->ss_sp   = NULL;
			oss->ss_size = 0;
		} else {
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
#ifdef KERNELSPACE_HIGHMEM
			if unlikely((uintptr_t)sp <= PAGESIZE) {
				oss->ss_sp   = 0;
				oss->ss_size = (uintptr_t)sp;
			} else {
				oss->ss_sp   = (void *)PAGESIZE;
				oss->ss_size = (uintptr_t)sp - PAGESIZE;
			}
#else /* KERNELSPACE_HIGHMEM */
			if unlikely((uintptr_t)sp <= KERNEL_CEILING) {
				oss->ss_sp   = 0;
				oss->ss_size = (uintptr_t)sp;
			} else {
				oss->ss_sp   = (void *)KERNEL_CEILING;
				oss->ss_size = (uintptr_t)sp - KERNEL_CEILING;
			}
#endif /* !KERNELSPACE_HIGHMEM */
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
#ifdef KERNELSPACE_HIGHMEM
			oss->ss_sp   = sp;
			oss->ss_size = (uintptr_t)KERNELSPACE_BASE - (uintptr_t)sp;
#else /* KERNELSPACE_HIGHMEM */
			oss->ss_sp   = sp;
			oss->ss_size = sp == 0 ? (uintptr_t)-1 : (uintptr_t)0 - (uintptr_t)sp;
#endif /* !KERNELSPACE_HIGHMEM */
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
		}
	}
	if (ss) {
		validate_readable(ss, sizeof(*ss));
		COMPILER_READ_BARRIER();
		if (ss->ss_flags & SS_DISABLE)
			sp = EXCEPT_HANDLER_SP_CURRENT;
		else {
			sp = ss->ss_sp;
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
			sp = (byte_t *)sp + ss->ss_size;
#endif /* __ARCH_STACK_GROWS_DOWNWARDS */
			/* Validate that the given stack pointer is actually writable. */
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
			validate_writable((byte_t *)sp - 1, 1);
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
			validate_writable(sp, 1);
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
		}
		PERTASK_SET(this_user_except_handler.ueh_stack, sp);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SIGALTSTACK */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_SIGALTSTACK
DEFINE_COMPAT_SYSCALL2(errno_t, sigaltstack,
                       USER UNCHECKED struct compat_sigaltstack const *, ss,
                       USER UNCHECKED struct compat_sigaltstack *, oss) {
	void *sp;
	if (oss) {
		validate_writable(oss, sizeof(*oss));
		COMPILER_WRITE_BARRIER();
		sp = PERTASK_GET(this_user_except_handler.ueh_stack);
		oss->ss_flags = 0;
		if (sp == EXCEPT_HANDLER_SP_CURRENT) {
			oss->ss_sp   = (compat_ptr(void))NULL;
			oss->ss_size = 0;
		} else {
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
#ifdef KERNELSPACE_HIGHMEM
			if unlikely((uintptr_t)sp <= PAGESIZE) {
				oss->ss_sp   = (compat_ptr(void))0;
				oss->ss_size = (compat_size_t)(uintptr_t)sp;
			} else {
				oss->ss_sp   = (compat_ptr(void))(void *)PAGESIZE;
				oss->ss_size = (compat_size_t)(uintptr_t)sp - PAGESIZE;
			}
#else /* KERNELSPACE_HIGHMEM */
			if unlikely((uintptr_t)sp <= KERNEL_CEILING) {
				oss->ss_sp   = (compat_ptr(void))0;
				oss->ss_size = (compat_size_t)(uintptr_t)sp;
			} else {
				oss->ss_sp   = (compat_ptr(void))(void *)KERNEL_CEILING;
				oss->ss_size = (compat_size_t)((uintptr_t)sp - KERNEL_CEILING);
			}
#endif /* !KERNELSPACE_HIGHMEM */
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
#ifdef KERNELSPACE_HIGHMEM
			oss->ss_sp   = (compat_ptr(void))sp;
			oss->ss_size = (compat_size_t)((uintptr_t)KERNELSPACE_BASE - (uintptr_t)sp);
#else /* KERNELSPACE_HIGHMEM */
			oss->ss_sp   = (compat_ptr(void))sp;
			oss->ss_size = (compat_size_t)(sp == 0 ? (uintptr_t)-1 : (uintptr_t)0 - (uintptr_t)sp);
#endif /* !KERNELSPACE_HIGHMEM */
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
		}
	}
	if (ss) {
		validate_readable(ss, sizeof(*ss));
		COMPILER_READ_BARRIER();
		if (ss->ss_flags & SS_DISABLE)
			sp = EXCEPT_HANDLER_SP_CURRENT;
		else {
			sp = ss->ss_sp;
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
			sp = (byte_t *)sp + ss->ss_size;
#endif /* __ARCH_STACK_GROWS_DOWNWARDS */
			/* Validate that the given stack pointer is actually writable. */
#ifdef __ARCH_STACK_GROWS_DOWNWARDS
			validate_writable((byte_t *)sp - 1, 1);
#else /* __ARCH_STACK_GROWS_DOWNWARDS */
			validate_writable(sp, 1);
#endif /* !__ARCH_STACK_GROWS_DOWNWARDS */
		}
		PERTASK_SET(this_user_except_handler.ueh_stack, sp);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SIGALTSTACK */




#ifdef CONFIG_HAVE_USERPROCMASK
PRIVATE void KCALL
load_userprocmask_into_kernelspace(USER CHECKED struct userprocmask *ctl) {
	USER UNCHECKED sigset_t *old_sigset;
	struct kernel_sigmask *kernel_mask;
	/* Read the old userprocmask descriptor's final signal mask into
	 * the kernel mask buffer of the current thread. Once we've done
	 * that we'll no longer need to access `ctl' */
	old_sigset = ATOMIC_READ(ctl->pm_sigmask);
	validate_readable(old_sigset, sizeof(sigset_t));
	kernel_mask = sigmask_kernel_getwr();
	TRY {
		memcpy(&kernel_mask->sm_mask, old_sigset, sizeof(sigset_t));
	} EXCEPT {
		/* Make sure that SIGKILL and SIGSTOP are never masked
		 * Note however that we don't need to check for them to be
		 * pending, since our thread is still in `TASK_FUSERPROCMASK'
		 * mode, meaning that the is-pending check isn't actually
		 * using our thread's kernel signal mask! */
		sigdelset(&kernel_mask->sm_mask, SIGKILL);
		sigdelset(&kernel_mask->sm_mask, SIGSTOP);
		RETHROW();
	}
	sigdelset(&kernel_mask->sm_mask, SIGKILL);
	sigdelset(&kernel_mask->sm_mask, SIGSTOP);
}
#endif /* CONFIG_HAVE_USERPROCMASK */






/************************************************************************/
/* set_tid_address()                                                    */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SET_TID_ADDRESS
DEFINE_SYSCALL1(pid_t, set_tid_address,
                USER UNCHECKED pid_t *, tidptr) {
	validate_writable_opt(tidptr, sizeof(*tidptr));
#ifdef CONFIG_HAVE_USERPROCMASK
	/* Disable userprocmask, if it was enabled. */
	if unlikely(PERTASK_GET(this_task.t_flags) & TASK_FUSERPROCMASK) {
		USER CHECKED struct userprocmask *old_ctl;
		old_ctl = PERTASK_GET(this_userprocmask_address);
		/* Load the final userprocmask into kernelspace */
		load_userprocmask_into_kernelspace(old_ctl);
		/* Clear the userprocmask flag(s), the same way a
		 * call `sys_set_userprocmask_address(NULL)' would
		 * have. */
		ATOMIC_FETCHAND(THIS_TASK->t_flags, ~(TASK_FUSERPROCMASK |
		                                      TASK_FUSERPROCMASK_AFTER_VFORK));
	}
#endif /* CONFIG_HAVE_USERPROCMASK */
	PERTASK_SET(this_tid_address, tidptr);
	return task_gettid();
}
#endif /* __ARCH_WANT_SYSCALL_SET_TID_ADDRESS */




#ifdef CONFIG_HAVE_USERPROCMASK
#ifdef __ARCH_WANT_SYSCALL_SET_USERPROCMASK_ADDRESS
PRIVATE NOBLOCK NONNULL((1, 2)) void
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

/* Gather the set of pending signals. */
PRIVATE void KCALL
gather_pending_signals(sigset_t *__restrict these) {
	struct sigqueue *myqueue;
	struct process_sigqueue *prqueue;
	struct sigqueue_entry *pending, **piter, *iter;
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
		sigaddset(these, iter->sqe_info.si_signo);
	} while ((iter = *(piter = &iter->sqe_next)) != NULL);
	/* Restore all signals pending for the calling thread. */
	restore_perthread_pending_signals(myqueue, pending);
no_perthread_pending:
	/* With per-task signals checked, also check for per-process signals */
	prqueue = &THIS_PROCESS_SIGQUEUE;
	sync_read(prqueue);
	for (iter = prqueue->psq_queue.sq_queue; iter; iter = iter->sqe_next)
		sigaddset(these, iter->sqe_info.si_signo);
	sync_endread(prqueue);
}


DEFINE_SYSCALL1(errno_t, set_userprocmask_address,
                USER UNCHECKED struct userprocmask *, ctl) {
	if unlikely(PERTASK_GET(this_task.t_flags) & TASK_FUSERPROCMASK) {
		USER CHECKED struct userprocmask *old_ctl;
		old_ctl = PERTASK_GET(this_userprocmask_address);
		/* Check for special case: Nothing changed. */
		if unlikely(old_ctl == ctl)
			goto done;
		/* Load the final userprocmask into kernelspace */
		load_userprocmask_into_kernelspace(old_ctl);
	}
	if unlikely(!ctl) {
		/* Disable USERPROCMASK mode. */
		PERTASK_SET(this_userprocmask_address, (struct userprocmask *)NULL);
		ATOMIC_FETCHAND(THIS_TASK->t_flags, ~(TASK_FUSERPROCMASK |
		                                      TASK_FUSERPROCMASK_AFTER_VFORK));
	} else {
		size_t sigsetsize;
		USER UNCHECKED sigset_t *new_sigset;
		/* Enable USERPROCMASK mode. */
		validate_readwrite_opt(ctl, sizeof(*ctl));
		COMPILER_BARRIER();

		/* Verify that the controller's idea of the size of a signal set matches our's */
		sigsetsize = ATOMIC_READ(ctl->pm_sigsize);
		if (sigsetsize != sizeof(sigset_t)) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
			      sigsetsize);
		}

		/* Load the address for the initial signal mask. We'll be copying
		 * our threads kernel signal mask into this field for the purpose
		 * of initialization. */
		new_sigset = ATOMIC_READ(ctl->pm_sigmask);
		COMPILER_BARRIER();
		validate_readwrite(new_sigset, sizeof(sigset_t));

		/* Initialize the user's initial signal mask with what was their
		 * thread's signal mask before. */
		{
			struct kernel_sigmask *kernel_mask;
			kernel_mask = sigmask_kernel_getrd();
			memcpy(new_sigset, &kernel_mask->sm_mask, sizeof(sigset_t));
		}

		/* Fill in the initial set of pending signals for user-space. */
		{
			sigset_t pending;
			sigemptyset(&pending);
			gather_pending_signals(&pending);
			COMPILER_BARRIER();
			memcpy(&ctl->pm_pending, &pending, sizeof(sigset_t));
			COMPILER_BARRIER();
		}

		/* Finally, initialize the TID field to that of the calling thread. */
		ctl->pm_mytid = task_gettid();
		COMPILER_BARRIER();

		/* Store the controller address for our thread. */
		PERTASK_SET(this_userprocmask_address, ctl);

		/* Turn on the USERPROCMASK bit in our thread. */
		{
			uintptr_t old_flags;
			old_flags = ATOMIC_FETCHOR(THIS_TASK->t_flags, TASK_FUSERPROCMASK);
			/* If USERPROCMASK wasn't enabled before, and we're a VFORK thread,
			 * then we must also set the `TASK_FUSERPROCMASK_AFTER_VFORK' flag,
			 * such that the process of clearing the `TASK_FVFORK' flag during
			 * exec() or exit() will also write NULL to `ctl->pm_sigmask' */
			if ((old_flags & (TASK_FUSERPROCMASK | TASK_FVFORK)) == TASK_FVFORK)
				ATOMIC_FETCHOR(THIS_TASK->t_flags, TASK_FUSERPROCMASK_AFTER_VFORK);
		}

		/* NOTE: ___Don't___ call `sigmask_check()' here! Assuming that the user
		 *       calls that function when appropriate, none of the pending signals
		 *       would currently be unmasked, and even if they were, we mustn't
		 *       check for them here, since this system call isn't a cancellation
		 *       point! */
	}
done:
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SET_USERPROCMASK_ADDRESS */
#endif /* CONFIG_HAVE_USERPROCMASK */



DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_EXCEPT_HANDLER_C */
