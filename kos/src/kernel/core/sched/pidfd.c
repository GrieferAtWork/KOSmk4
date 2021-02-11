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
#ifndef GUARD_KERNEL_SRC_SCHED_PIDFD_C
#define GUARD_KERNEL_SRC_SCHED_PIDFD_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/personality.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>

#include <compat/config.h>
#include <kos/except/reason/inval.h>
#include <kos/io.h>
#include <kos/kernel/handle.h>

#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/os/siginfo-convert.h>
#include <compat/bits/os/siginfo.h>
#include <compat/signal.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

#ifdef __ARCH_WANT_SYSCALL_PIDFD_OPEN
DEFINE_SYSCALL2(fd_t, pidfd_open,
                pid_t, pid,
                syscall_ulong_t, flags) {
	unsigned int result;
	struct handle hand;
	REF struct taskpid *thread_pid;
	if unlikely(flags != 0) {
		THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
		      E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_FLAGS);
	}
	thread_pid = pidns_lookup(THIS_PIDNS, (upid_t)pid);
	FINALLY_DECREF_UNLIKELY(thread_pid);
	if (!has_personality(KP_PIDFD_OPEN_THREAD)) {
		REF struct task *thread;
		thread = taskpid_gettask_srch(thread_pid);
		FINALLY_DECREF_UNLIKELY(thread);
		/* Only allow pidfd_open() for process leaders */
		if unlikely(!task_isprocessleader_p(thread)) {
			THROW(E_INVALID_ARGUMENT_BAD_STATE,
			      E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_NOTALEADER);
		}
	}
	/* TODO: Verify that the caller can access `pid' */
	hand.h_type = HANDLE_TYPE_TASK;
	hand.h_mode = IO_RDWR | IO_CLOEXEC;
	hand.h_data = thread_pid;
	/* Install the handle within our handle namespace. */
	result = handle_install(THIS_HANDLE_MANAGER, hand);
	return (fd_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PIDFD_OPEN */


#ifdef __ARCH_WANT_SYSCALL_PIDFD_GETFD
DEFINE_SYSCALL3(fd_t, pidfd_getfd,
                fd_t, pidfd,
                fd_t, foreign_fd,
                syscall_ulong_t, flags) {
	unsigned int result;
	REF struct handle foreign_handle;
	REF struct task *thread;
	REF struct handle_manager *handman;
	if unlikely(flags != 0) {
		THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
		      E_INVALID_ARGUMENT_CONTEXT_PIDFD_GETFD_FLAGS);
	}
	thread = handle_get_task((unsigned int)pidfd);
	{
		FINALLY_DECREF_UNLIKELY(thread);
		handman = task_gethandlemanager(thread);
	}
	{
		FINALLY_DECREF_UNLIKELY(handman);
		/* XXX: Support  for symbolic handles? It'd be kind-of
		 *      neat to access, say, PWD of a process by doing
		 *      `pidfd_getfd(pidfd_open(PID), AT_FDCWD)' as an
		 *      alias for `open("/proc/[PID]/cwd")'... */
		foreign_handle = handle_lookupin((unsigned int)foreign_fd, handman);
	}
	TRY {
		foreign_handle.h_mode &= ~IO_CLOFORK;
		foreign_handle.h_mode |= IO_CLOEXEC;
		/* Install the handle into our own table. */
		result = handle_install(THIS_HANDLE_MANAGER,
		                        foreign_handle);
	} EXCEPT {
		decref_unlikely(foreign_handle);
		RETHROW();
	}
	decref_unlikely(foreign_handle);
	return (fd_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PIDFD_GETFD */


#if (defined(__ARCH_WANT_SYSCALL_PIDFD_SEND_SIGNAL) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PIDFD_SEND_SIGNAL))

PRIVATE errno_t KCALL
pidfd_send_signal_impl(fd_t pidfd,
                       siginfo_t const *__restrict info,
                       syscall_ulong_t flags) {
	REF struct task *target;
	if unlikely(flags != 0) {
		THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
		      E_INVALID_ARGUMENT_CONTEXT_PIDFD_PIDFD_SEND_SIGNAL_FLAGS);
	}
	target = handle_get_task((unsigned int)pidfd);
	FINALLY_DECREF_UNLIKELY(target);
	/* Don't allow sending arbitrary signals to other processes. */
	if ((info->si_code >= 0 || info->si_code == SI_TKILL) &&
	    (task_getprocess_of(target) != task_getprocess()))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE,
		      info->si_code);
	if (info->si_signo != 0) {
		if (!task_raisesignalprocess(target, info))
			THROW(E_PROCESS_EXITED, task_getpid_of_s(target));
	}
	return -EOK;
}


#ifdef __ARCH_WANT_SYSCALL_PIDFD_SEND_SIGNAL
INTDEF NONNULL((1)) void KCALL /* from "posix-signal.c" */
siginfo_from_user(siginfo_t *__restrict info, signo_t usigno,
                  USER UNCHECKED siginfo_t const *uinfo);
DEFINE_SYSCALL4(errno_t, pidfd_send_signal,
                fd_t, pidfd, signo_t, usigno,
                USER UNCHECKED siginfo_t const *, uinfo,
                syscall_ulong_t, flags) {
	siginfo_t info;
	siginfo_from_user(&info, usigno, uinfo);
	return pidfd_send_signal_impl(pidfd, &info, flags);
}
#endif /* __ARCH_WANT_SYSCALL_PIDFD_SEND_SIGNAL */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PIDFD_SEND_SIGNAL
INTDEF NONNULL((1)) void KCALL /* from "posix-signal.c" */
siginfo_from_compat_user(siginfo_t *__restrict info, signo_t usigno,
                         USER UNCHECKED compat_siginfo_t const *uinfo);
DEFINE_COMPAT_SYSCALL4(errno_t, pidfd_send_signal,
                       fd_t, pidfd, signo_t, usigno,
                       USER UNCHECKED compat_siginfo_t const *, uinfo,
                       syscall_ulong_t, flags) {
	siginfo_t info;
	siginfo_from_compat_user(&info, usigno, uinfo);
	return pidfd_send_signal_impl(pidfd, &info, flags);
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PIDFD_SEND_SIGNAL */

#endif /* __ARCH_WANT_SYSCALL_PIDFD_SEND_SIGNAL || __ARCH_WANT_COMPAT_SYSCALL_PIDFD_SEND_SIGNAL */


DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_PIDFD_C */
