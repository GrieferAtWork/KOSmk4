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
#ifndef GUARD_KERNEL_SRC_MISC_EXCEPT_SYSCALL_C
#define GUARD_KERNEL_SRC_MISC_EXCEPT_SYSCALL_C 1
#define _GNU_SOURCE 1

/* System calls and meta-data tracking for stuff relating to exception handling */

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/mman/event.h>     /* DEFINE_PERMMAN_ONEXEC() */
#include <kernel/mman/mpartmeta.h> /* mman_broadcastfutex() */
#include <kernel/paging.h>
#include <kernel/rt/except-syscall.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/group.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/sigmask.h>
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
PUBLIC ATTR_PERTASK ATTR_ALIGN(struct user_except_handler) this_user_except_handler = {
	.ueh_mode    = EXCEPT_HANDLER_MODE_DISABLED,
	.ueh_handler = NULL,
	.ueh_stack   = EXCEPT_HANDLER_SP_CURRENT,
};

/* [0..1][lock(PRIVATE(THIS_TASK))]
 * User-space TID address used to implement functionality such as `pthread_join()'
 * When the associated thread exits, it will:
 *     >> pid_t *addr = PERTASK_GET(this_tid_address);
 *     >> if (addr) {
 *     >>     TRY {
 *     >>         *addr = 0;
 *     >>         mman_broadcastfutex(addr);
 *     >>     } EXCEPT {
 *     >>         if (!was_thrown(E_SEGFAULT) ||
 *     >>             PERTASK_NE(this_exception_args.e_segfault.s_addr, (uintptr_t)addr))
 *     >>             except_printf("...");
 *     >>     }
 *     >> }
 * When a new thread is created by clone(), the `CLONE_CHILD_CLEARTID' flag will  cause
 * the given `ctid' to be used as  the initial value for `this_tid_address', while  the
 * `CLONE_CHILD_SETTID' flag will cause the same address to be filled with the thread's
 * TID. */
PUBLIC ATTR_PERTASK ATTR_ALIGN(USER CHECKED pid_t *) this_tid_address = NULL;

DEFINE_PERMMAN_ONEXEC(reset_user_except_handler);
PRIVATE ATTR_USED NOBLOCK void
NOTHROW(KCALL reset_user_except_handler)(void) {
	struct user_except_handler *hand;
	hand            = &PERTASK(this_user_except_handler);
	hand->ueh_mode  = EXCEPT_HANDLER_MODE_DISABLED;
	hand->ueh_stack = EXCEPT_HANDLER_SP_CURRENT;
	/* Reset the TID address of the calling thread. */
	PERTASK_SET(this_tid_address, (pid_t *)NULL);
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




#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
PRIVATE void KCALL
load_userprocmask_into_kernelspace(USER CHECKED struct userprocmask *ctl) {
	USER UNCHECKED sigset_t *old_sigset;
	size_t old_sigsetsize;
	sigset_t newmask;

	/* Read the old userprocmask descriptor's final signal mask into
	 * the kernel mask buffer of the current thread. Once we've done
	 * that we'll no longer need to access `ctl' */
	old_sigset     = ctl->pm_sigmask;
	old_sigsetsize = ctl->pm_sigsize;
	COMPILER_BARRIER();
	validate_readable(old_sigset, old_sigsetsize);
	if (old_sigsetsize > sizeof(sigset_t))
		old_sigsetsize = sizeof(sigset_t);
	memset(mempcpy(&newmask, old_sigset, old_sigsetsize),
	       0xff, sizeof(sigset_t) - old_sigsetsize);
	sigdelset(&newmask, SIGKILL);
	sigdelset(&newmask, SIGSTOP);

	/* Install the updated signal mask. */
	memcpy(&THIS_KERNEL_SIGMASK, &newmask, sizeof(sigset_t));
}
#endif /* CONFIG_HAVE_KERNEL_USERPROCMASK */






/************************************************************************/
/* set_tid_address()                                                    */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SET_TID_ADDRESS
DEFINE_SYSCALL1(pid_t, set_tid_address,
                USER UNCHECKED pid_t *, tidptr) {
	validate_writable_opt(tidptr, sizeof(*tidptr));
#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
	/* Disable userprocmask, if it was enabled. */
	if unlikely(PERTASK_TESTMASK(this_task.t_flags, TASK_FUSERPROCMASK)) {
		USER CHECKED struct userprocmask *old_ctl;
		old_ctl = PERTASK_GET(this_userprocmask_address);

		/* Load the final userprocmask into kernelspace */
		load_userprocmask_into_kernelspace(old_ctl);

		/* Clear  the userprocmask flag(s), the same way a
		 * call `sys_set_userprocmask_address(NULL)' would
		 * have. */
		ATOMIC_AND(PERTASK(this_task.t_flags),
		           ~(TASK_FUSERPROCMASK |
		             TASK_FUSERPROCMASK_AFTER_VFORK));
	}
#endif /* CONFIG_HAVE_KERNEL_USERPROCMASK */
	PERTASK_SET(this_tid_address, tidptr);
	return task_gettid();
}
#endif /* __ARCH_WANT_SYSCALL_SET_TID_ADDRESS */




#ifdef CONFIG_HAVE_KERNEL_USERPROCMASK
#ifdef __ARCH_WANT_SYSCALL_SET_USERPROCMASK_ADDRESS
DEFINE_SYSCALL1(errno_t, set_userprocmask_address,
                USER UNCHECKED struct userprocmask *, ctl) {
	if unlikely(PERTASK_TESTMASK(this_task.t_flags, TASK_FUSERPROCMASK)) {
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
		ATOMIC_AND(PERTASK(this_task.t_flags),
		           ~(TASK_FUSERPROCMASK |
		             TASK_FUSERPROCMASK_AFTER_VFORK));
	} else {
		size_t sigsetsize, overflow;
		sigset_t initial_pending;
		uintptr_t initial_flags;
		USER UNCHECKED sigset_t *new_sigset;

		/* Enable USERPROCMASK mode. */
		validate_readwrite_opt(ctl, sizeof(*ctl));
		COMPILER_BARRIER();

		/* Load the address for the initial signal mask. We'll be copying
		 * our threads kernel signal mask into this field for the purpose
		 * of initialization. */
		new_sigset = ctl->pm_sigmask;
		sigsetsize = ctl->pm_sigsize;
		COMPILER_BARRIER();
		validate_readwrite(new_sigset, sigsetsize);
		overflow = 0;
		if (sigsetsize > sizeof(sigset_t)) {
			overflow   = sigsetsize - sizeof(sigset_t);
			sigsetsize = sizeof(sigset_t);
		}

		/* Initialize the user's initial signal mask with
		 * what was  their thread's  signal mask  before. */
		{
			sigset_t const *kmask = &THIS_KERNEL_SIGMASK;
			memset(mempcpy(new_sigset, kmask, sigsetsize),
			       0xff, sizeof(sigset_t) - sigsetsize);
		}

		/* Fill in the initial set of pending signals for user-space. */
		sigemptyset(&initial_pending);
		task_rpc_pending_sigset(&initial_pending);
		proc_rpc_pending_sigset(&initial_pending);
		if (sigsetsize < sizeof(sigset_t)) {
			/* Clear pending bits that will be invisible to user-space. */
			bzero((byte_t *)&initial_pending + sigsetsize,
			      sizeof(sigset_t) - sigsetsize);
		}

		/* If any signals are pending, set the HASPENDING flag. */
		initial_flags = USERPROCMASK_FLAG_NORMAL;
		if (!sigisemptyset(&initial_pending))
			initial_flags |= USERPROCMASK_FLAG_HASPENDING;

		/* Populate   user-space   with  information
		 * about the initial set of pending signals. */
		bzero(mempcpy(&ctl->pm_pending,
		              &initial_pending,
		              sigsetsize),
		      overflow);

		/* Set the has-pending flag _AFTER_ filling in the pending set. */
		COMPILER_BARRIER();
		ctl->pm_flags = initial_flags;

		/* Finally, initialize the TID field to that of the calling thread. */
		COMPILER_BARRIER();
		ctl->pm_mytid = task_gettid();

		/* Store the controller address for our thread. */
		PERTASK_SET(this_userprocmask_address, ctl);

		{
			struct task *me = THIS_TASK;
			uintptr_t old_flags;

			/* Turn on the USERPROCMASK bit in our thread. */
			old_flags = ATOMIC_FETCHOR(me->t_flags, TASK_FUSERPROCMASK);

			/* If USERPROCMASK wasn't enabled before, and we're a VFORK thread,
			 * then we must also set the `TASK_FUSERPROCMASK_AFTER_VFORK' flag,
			 * such that the process of clearing the `TASK_FVFORK' flag  during
			 * exec() or exit() will also write NULL to `ctl->pm_sigmask' */
			if ((old_flags & (TASK_FUSERPROCMASK | TASK_FVFORK)) == TASK_FVFORK)
				ATOMIC_OR(me->t_flags, TASK_FUSERPROCMASK_AFTER_VFORK);
		}

		/* No need to call `userexcept_sysret_inject_self()' here since the
		 * effective signal mask shouldn't  have changed (because we  wrote
		 * the thread's old mask into the buffer it provided) */
	}
done:
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SET_USERPROCMASK_ADDRESS */
#endif /* CONFIG_HAVE_KERNEL_USERPROCMASK */


DECL_END

#endif /* !GUARD_KERNEL_SRC_MISC_EXCEPT_SYSCALL_C */
