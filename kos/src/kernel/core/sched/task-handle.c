/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
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
#include <kernel/handman.h>
#include <kernel/mman.h>
#include <kernel/personality.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/group.h>
#include <sched/posix-signal.h> /* task_raisesignalprocess() */
#include <sched/task.h>
#include <sched/tsc.h>

#include <compat/config.h>
#include <kos/except/reason/illop.h>
#include <kos/except/reason/inval.h>
#include <kos/io.h>
#include <kos/ioctl/pidfd.h>
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
DEFINE_HANDLE_REFCNT_FUNCTIONS(pidfd, struct taskpid);
INTERN void KCALL
handle_pidfd_stat(struct taskpid *__restrict self,
                  USER CHECKED struct stat *result) {
	bzero(result, sizeof(*result));
	/* TODO: st_atim: End of the latest quantum */
	/* TODO: st_mtim: Start of the latest quantum */
	/* TODO: st_ctim: Start of the latest quantum */
	/* TODO: st_btim: Thread creation time */
	(void)self;
}

INTERN void KCALL
handle_pidfd_pollconnect(struct taskpid *__restrict self, poll_mode_t what) {
	/* POLLINMASK: Terminated */
	if (what & POLLINMASK)
		task_connect_for_poll(&self->tp_changed);
}

INTERN ATTR_PURE WUNUSED poll_mode_t KCALL
handle_pidfd_polltest(struct taskpid *__restrict self, poll_mode_t what) {
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
require_pidfd_open(struct taskpid *__restrict self) {
	/* TODO */
	(void)self;
	COMPILER_IMPURE();
}




INTERN BLOCKING NONNULL((1)) syscall_slong_t KCALL
handle_pidfd_ioctl(struct taskpid *__restrict self, ioctl_t cmd,
                   USER UNCHECKED void *arg, iomode_t mode) THROWS(...) {
	switch (cmd) {

	case PIDFD_IOC_OPENPID: {
		struct handle hand;
		hand.h_type = HANDLE_TYPE_PIDFD;
		hand.h_mode = mode;
		hand.h_data = taskpid_getprocpid(self);
		require_pidfd_open((struct taskpid *)hand.h_data);
		return handles_install_openfd(hand, (USER UNCHECKED struct openfd *)arg);
	}	break;

	case PIDFD_IOC_OPENPPID: {
		struct handle hand;
		hand.h_type = HANDLE_TYPE_PIDFD;
		hand.h_mode = mode;
		hand.h_data = taskpid_getparentprocesspid(self);
		FINALLY_DECREF_UNLIKELY((struct taskpid *)hand.h_data);
		require_pidfd_open((struct taskpid *)hand.h_data);
		return handles_install_openfd(hand, (USER UNCHECKED struct openfd *)arg);
	}	break;

	case PIDFD_IOC_EXITCODE: {
		REF struct task *thread;
		union wait st;
		thread = taskpid_gettask(self);
		if (thread) {
			if (!(thread->t_flags & TASK_FTERMINATING)) {
				decref_unlikely(thread);
				THROW(E_ILLEGAL_BECAUSE_NOT_READY,
				      E_ILLEGAL_OPERATION_CONTEXT_TASK_NOT_EXITED,
				      taskpid_gettid_s(self));
			}
			decref_unlikely(thread);
		}
		validate_writable(arg, sizeof(union wait));
		st.w_status = self->tp_status;
		memcpy(arg, &st, sizeof(union wait));
		return 0;
	}	break;

	default:
		break;
	}
	switch (_IO_WITHSIZE(cmd, 0)) {

	case _IO_WITHSIZE(PIDFD_IOC_GETTID, 0):
		return ioctl_intarg_setpid(cmd, arg, taskpid_gettid_s(self));

	case _IO_WITHSIZE(PIDFD_IOC_GETPID, 0):
		return ioctl_intarg_setpid(cmd, arg, taskpid_getpid_s(self));

	case _IO_WITHSIZE(PIDFD_IOC_GETPPID, 0):
		return ioctl_intarg_setpid(cmd, arg, taskpid_getppid_s(self));

	case _IO_WITHSIZE(PIDFD_IOC_GETPGID, 0):
		return ioctl_intarg_setpid(cmd, arg, taskpid_getpgid_s(self));

	case _IO_WITHSIZE(PIDFD_IOC_GETSID, 0):
		return ioctl_intarg_setpid(cmd, arg, taskpid_getsid_s(self));

	default: break;
	}
	THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
	      E_INVALID_ARGUMENT_CONTEXT_IOCTL_COMMAND,
	      cmd);
}



#ifdef __ARCH_WANT_SYSCALL_PIDFD_OPEN
DEFINE_SYSCALL2(fd_t, pidfd_open,
                pid_t, pid,
                syscall_ulong_t, flags) {
	struct handle hand;
	REF struct taskpid *target;
	struct taskpid *mypid = task_gettaskpid();
	if unlikely(flags != 0) {
		THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
		      E_INVALID_ARGUMENT_CONTEXT_PIDFD_OPEN_FLAGS,
		      flags);
	}
	target = pidns_lookup_srch(mypid->tp_ns, pid);
	FINALLY_DECREF_UNLIKELY(target);

	/* Only allow pidfd_open() for process leaders
	 * NOTE: Programs that don't want to rely on `KP_PIDFD_OPEN_THREAD' can do:
	 *    >> char buf[lengthof("/proc/" PRIMAXd)];
	 *    >> sprintf(buf, "/proc/%d", tid);
	 *    >> temp = open(buf, O_RDONLY);
	 *    >> struct fdcast cast;
	 *    >> bzero(&cast, sizeof(cast));
	 *    >> cast.fc_rqtyp         = HANDLE_TYPE_PIDFD;
	 *    >> cast.fc_resfd.of_mode = OPENFD_MODE_AUTO;
	 *    >> ioctl(temp, FD_IOC_CAST, &cast);
	 *    >> close(temp);
	 *    >> return cast.fc_resfd.of_hint;
	 */
	if (!taskpid_isaprocess(target) && !has_personality(KP_PIDFD_OPEN_THREAD))
		THROW(E_PROCESS_EXITED, pid);

	/* Verify that the caller can access `pid' */
	require_pidfd_open(target);

	hand.h_type = HANDLE_TYPE_PIDFD;
	hand.h_mode = IO_RDWR | IO_CLOEXEC;
	hand.h_data = target;

	/* Install the handle within our handle namespace. */
	return handles_install(hand);
}
#endif /* __ARCH_WANT_SYSCALL_PIDFD_OPEN */


#ifdef __ARCH_WANT_SYSCALL_PIDFD_GETFD
DEFINE_SYSCALL3(fd_t, pidfd_getfd,
                fd_t, pidfd,
                fd_t, foreign_fd,
                syscall_ulong_t, flags) {
	REF struct handle foreign_handle;
	REF struct task *thread;
	REF struct handman *thread_handman;
	if unlikely(flags != 0) {
		THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
		      E_INVALID_ARGUMENT_CONTEXT_PIDFD_GETFD_FLAGS);
	}
	thread         = handles_lookuptask(pidfd);
	thread_handman = task_gethandman(thread);
	decref_unlikely(thread);
	{
		FINALLY_DECREF_UNLIKELY(thread_handman);
		/* XXX: Support  for symbolic handles? It'd be kind-of
		 *      neat to access, say, PWD of a process by doing
		 *      `pidfd_getfd(pidfd_open(PID), AT_FDCWD)' as an
		 *      alias for `open("/proc/[PID]/cwd")'... */
		foreign_handle = handman_lookup(thread_handman, foreign_fd);
	}
	RAII_FINALLY { decref_unlikely(foreign_handle); };
	foreign_handle.h_mode &= ~IO_CLOFORK;
	foreign_handle.h_mode |= IO_CLOEXEC;
	/* Install the handle into our own table. */
	return handles_install(foreign_handle);
}
#endif /* __ARCH_WANT_SYSCALL_PIDFD_GETFD */


#if (defined(__ARCH_WANT_SYSCALL_PIDFD_SEND_SIGNAL) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PIDFD_SEND_SIGNAL))

PRIVATE NONNULL((2)) errno_t KCALL
pidfd_send_signal_impl(fd_t pidfd,
                       siginfo_t const *__restrict info,
                       syscall_ulong_t flags) {
	REF struct taskpid *target;
	if unlikely(flags != 0) {
		THROW(E_INVALID_ARGUMENT_RESERVED_ARGUMENT,
		      E_INVALID_ARGUMENT_CONTEXT_PIDFD_PIDFD_SEND_SIGNAL_FLAGS,
		      flags);
	}
	target = handles_lookuppidfd(pidfd);
	FINALLY_DECREF_UNLIKELY(target);
	/* Don't allow sending arbitrary signals to other processes. */
	if ((info->si_code >= 0 || info->si_code == SI_TKILL) &&
	    (taskpid_getprocpid(target) != task_getprocpid()))
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RAISE_SIGINFO_BADCODE,
		      info->si_code);
	if (info->si_signo != 0) {
		if (!task_raisesignalprocess(target, info))
			THROW(E_PROCESS_EXITED, taskpid_gettid_s(target));
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
