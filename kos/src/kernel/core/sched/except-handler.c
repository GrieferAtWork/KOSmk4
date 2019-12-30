/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
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
#include <sched/task.h>

#include <compat/config.h>
#include <kos/except-handler.h>
#include <kos/except-inval.h>

#include <errno.h>
#include <signal.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/sigstack.h>
#include <compat/kos/except-handler.h>
#include <compat/kos/types.h>
#include <compat/pointer.h>
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
 *        >>             error_data()->e_pointers[0] != (uintptr_t)addr)
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
	pid_t *addr = PERTASK_GET(this_tid_address);
	if (addr) {
		TRY {
			*addr = 0;
			vm_futex_broadcast(addr);
		} EXCEPT {
			/* Explicitly handle E_SEGFAULT:addr as a no-op */
			if (!was_thrown(E_SEGFAULT) ||
			    error_data()->e_pointers[0] != (uintptr_t)addr) {
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
                                         uintptr_t UNUSED(flags)) {
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
		validate_writable(pmode, sizeof(*pmode));
		COMPILER_WRITE_BARRIER();
		*pmode = exc->ueh_mode;
	}
	if (phandler) {
		validate_writable(phandler, sizeof(*phandler));
		COMPILER_WRITE_BARRIER();
		*phandler = (compat_except_handler_t)(uintptr_t)(void *)exc->ueh_handler;
	}
	if (phandler_sp) {
		validate_writable(phandler_sp, sizeof(*phandler_sp));
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





/************************************************************************/
/* set_tid_address()                                                    */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SET_TID_ADDRESS
DEFINE_SYSCALL1(pid_t, set_tid_address,
                USER UNCHECKED pid_t *, tidptr) {
	validate_writable(tidptr, sizeof(*tidptr));
	PERTASK_SET(this_tid_address, tidptr);
	return task_gettid();
}
#endif /* __ARCH_WANT_SYSCALL_SET_TID_ADDRESS */



DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_EXCEPT_HANDLER_C */
