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
#ifndef GUARD_KERNEL_SRC_SCHED_TASK_HANDLE_C
#define GUARD_KERNEL_SRC_SCHED_TASK_HANDLE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/mman.h>
#include <kernel/personality.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>

#include <compat/config.h>
#include <kos/except/reason/inval.h>
#include <kos/io.h>
#include <kos/ioctl/task.h>
#include <kos/kernel/handle.h>
#include <sys/stat.h>
#include <sys/wait.h>

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

/* Task HOP functions */
DEFINE_HANDLE_REFCNT_FUNCTIONS(task, struct taskpid);
INTERN void KCALL
handle_task_stat(struct taskpid *__restrict self,
                 USER CHECKED struct stat *result) {
	memset(result, 0, sizeof(*result));
	/* TODO: st_ctim: Thread creation time? */
	/* TODO: st_atim: End of the latest quantum */
	/* TODO: st_mtim: Start of the latest quantum */
	(void)self;
}

INTERN void KCALL
handle_task_pollconnect(struct taskpid *__restrict self, poll_mode_t what) {
	/* POLLINMASK: Terminated */
	if (what & POLLINMASK)
		task_connect_for_poll(&self->tp_changed);
}

INTERN ATTR_PURE WUNUSED poll_mode_t KCALL
handle_task_polltest(struct taskpid *__restrict self, poll_mode_t what) {
	poll_mode_t result = 0;
	/* POLLINMASK: Terminated */
	if (what & POLLINMASK) {
		if (WIFEXITED(self->tp_status))
			result |= POLLINMASK;
	}
	return result;
}


/* Ensure that the calling thread has permission to do `pidfd_open(self)' */
PRIVATE NONNULL((1)) void FCALL
require_pidfd_open(struct task *__restrict self) {
	/* TODO */
	(void)self;
	COMPILER_IMPURE();
}




INTERN BLOCKING NONNULL((1)) syscall_slong_t KCALL
handle_task_ioctl(struct taskpid *__restrict self, ioctl_t cmd,
                  USER UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	switch (cmd) {

	case TASK_IOC_GETTID: {
		validate_writable(arg, sizeof(pid_t));
		*(USER CHECKED pid_t *)arg = taskpid_getpid(self, THIS_PIDNS);
		return 0;
	}	break;

	case TASK_IOC_GETPID: {
		REF struct task *thread;
		validate_writable(arg, sizeof(pid_t));
		thread = taskpid_gettask_srch(self);
		FINALLY_DECREF_UNLIKELY(thread);
		*(USER CHECKED pid_t *)arg = task_getpid_of_s(thread);
		return 0;
	}	break;

	case TASK_IOC_GETPPID: {
		REF struct task *thread;
		REF struct taskpid *parent_pid;
		validate_writable(arg, sizeof(pid_t));
		thread = taskpid_gettask_srch(self);
		{
			FINALLY_DECREF_UNLIKELY(thread);
			parent_pid = task_getprocessparentpid_of(thread);
		}
		if unlikely(!parent_pid)
			THROW(E_NO_SUCH_PROCESS);
		FINALLY_DECREF_UNLIKELY(parent_pid);
		*(USER CHECKED pid_t *)arg = taskpid_getpid(parent_pid, THIS_PIDNS);
		return 0;
	}	break;

	case TASK_IOC_GETPGID: {
		REF struct task *thread;
		REF struct taskpid *group_pid;
		validate_writable(arg, sizeof(pid_t));
		thread = taskpid_gettask_srch(self);
		{
			FINALLY_DECREF_UNLIKELY(thread);
			group_pid = task_getprocessgroupleaderpid_of(thread);
		}
		if unlikely(!group_pid)
			THROW(E_NO_SUCH_PROCESS);
		FINALLY_DECREF_UNLIKELY(group_pid);
		*(USER CHECKED pid_t *)arg = taskpid_getpid(group_pid, THIS_PIDNS);
		return 0;
	}	break;

	case TASK_IOC_GETSID: {
		REF struct task *thread;
		REF struct taskpid *session_pid;
		validate_writable(arg, sizeof(pid_t));
		thread = taskpid_gettask_srch(self);
		{
			FINALLY_DECREF_UNLIKELY(thread);
			session_pid = task_getsessionleaderpid_of(thread);
		}
		if unlikely(!session_pid)
			THROW(E_NO_SUCH_PROCESS);
		FINALLY_DECREF_UNLIKELY(session_pid);
		*(USER CHECKED pid_t *)arg = taskpid_getpid(session_pid, THIS_PIDNS);
		return 0;
	}	break;

	case TASK_IOC_OPENPID: {
		struct handle hand;
		REF struct task *thread;
		thread = taskpid_gettask_srch(self);
		FINALLY_DECREF_UNLIKELY(thread);
		thread = task_getprocess_of(thread);
		require_pidfd_open(thread);
		hand.h_type = HANDLE_TYPE_TASK;
		hand.h_mode = mode;
		hand.h_data = FORTASK(thread, this_taskpid);
		return handle_installopenfd((USER UNCHECKED struct openfd *)arg, hand);
	}	break;

	case TASK_IOC_OPENPPID: {
		struct handle hand;
		REF struct task *thread;
		thread = taskpid_gettask_srch(self);
		{
			FINALLY_DECREF_UNLIKELY(thread);
			thread = task_getprocessparent_of(thread);
		}
		if unlikely(!thread)
			THROW(E_NO_SUCH_PROCESS);
		FINALLY_DECREF_UNLIKELY(thread);
		require_pidfd_open(thread);
		hand.h_type = HANDLE_TYPE_TASK;
		hand.h_mode = mode;
		hand.h_data = FORTASK(thread, this_taskpid);
		return handle_installopenfd((USER UNCHECKED struct openfd *)arg, hand);
	}	break;

	case TASK_IOC_OPENPGID: {
		struct handle hand;
		REF struct task *thread;
		thread = taskpid_gettask_srch(self);
		{
			FINALLY_DECREF_UNLIKELY(thread);
			thread = task_getprocessgroupleader_srch_of(thread);
		}
		FINALLY_DECREF_UNLIKELY(thread);
		require_pidfd_open(thread);
		hand.h_type = HANDLE_TYPE_TASK;
		hand.h_mode = mode;
		hand.h_data = FORTASK(thread, this_taskpid);
		return handle_installopenfd((USER UNCHECKED struct openfd *)arg, hand);
	}	break;

	case TASK_IOC_OPENSID: {
		struct handle hand;
		REF struct task *thread;
		thread = taskpid_gettask_srch(self);
		{
			FINALLY_DECREF_UNLIKELY(thread);
			thread = task_getsessionleader_srch_of(thread);
		}
		FINALLY_DECREF_UNLIKELY(thread);
		require_pidfd_open(thread);
		hand.h_type = HANDLE_TYPE_TASK;
		hand.h_mode = mode;
		hand.h_data = FORTASK(thread, this_taskpid);
		return handle_installopenfd((USER UNCHECKED struct openfd *)arg, hand);
	}	break;

	default:
		break;
	}
	THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
	      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
	      cmd);
}



#ifdef __ARCH_WANT_SYSCALL_PIDFD_OPEN
DEFINE_SYSCALL2(fd_t, pidfd_open,
                pid_t, pid,
                syscall_ulong_t, flags) {
	unsigned int result;
	struct handle hand;
	REF struct taskpid *thread_pid;
	REF struct task *thread;
	if unlikely(flags != 0) {
		THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
		      E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_FLAGS);
	}
	thread_pid = pidns_lookup(THIS_PIDNS, (upid_t)pid);
	FINALLY_DECREF_UNLIKELY(thread_pid);
	thread = taskpid_gettask_srch(thread_pid);
	{
		FINALLY_DECREF_UNLIKELY(thread);
		/* Only allow pidfd_open() for process leaders */
		if (!task_isprocessleader_p(thread) && !has_personality(KP_PIDFD_OPEN_THREAD)) {
			THROW(E_INVALID_ARGUMENT_BAD_STATE,
			      E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_NOTALEADER);
		}

		/* Verify that the caller can access `pid' */
		require_pidfd_open(thread);
	}

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
	RAII_FINALLY { decref_unlikely(foreign_handle); };
	foreign_handle.h_mode &= ~IO_CLOFORK;
	foreign_handle.h_mode |= IO_CLOEXEC;
	/* Install the handle into our own table. */
	result = handle_install(THIS_HANDLE_MANAGER,
	                        foreign_handle);
	return (fd_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PIDFD_GETFD */


#if (defined(__ARCH_WANT_SYSCALL_PIDFD_SEND_SIGNAL) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PIDFD_SEND_SIGNAL))

PRIVATE NONNULL((2)) errno_t KCALL
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

#endif /* !GUARD_KERNEL_SRC_SCHED_TASK_HANDLE_C */
