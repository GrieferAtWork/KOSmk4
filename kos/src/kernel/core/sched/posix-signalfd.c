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
#ifndef GUARD_KERNEL_SRC_SCHED_POSIX_SIGNALFD_C
#define GUARD_KERNEL_SRC_SCHED_POSIX_SIGNALFD_C 1

#include <kernel/compiler.h>

#include <kernel/aio.h>
#include <kernel/except.h>
#include <kernel/handle-proto.h>
#include <kernel/handle.h>
#include <kernel/iovec.h>
#include <kernel/malloc.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>
#include <sched/posix-signalfd.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>

#include <hybrid/atomic.h>

#include <kos/except/reason/inval.h>
#include <sys/poll.h>
#include <sys/signalfd.h>

#include <assert.h>
#include <signal.h>
#include <string.h>

DECL_BEGIN

/* Handle object type integration */
DEFINE_HANDLE_REFCNT_FUNCTIONS(signalfd, struct signalfd);

PRIVATE ATTR_MALLOC ATTR_RETNONNULL WUNUSED REF struct signalfd *KCALL
signalfd_create(USER CHECKED sigset_t const *mask) THROWS(E_BADALLOC, E_SEGFAULT) {
	struct signalfd *result;
	result = signalfd_alloc();
	result->sf_refcnt = 1;
	TRY {
		memcpy(&result->sf_mask, mask, sizeof(sigset_t));
	} EXCEPT {
		signalfd_free(result);
		RETHROW();
	}
	/* Make sure that we never include SIGKILL or SIGSTOP in the mask. */
	sigdelset(&result->sf_mask, SIGKILL);
	sigdelset(&result->sf_mask, SIGSTOP);
	return result;
}

INTERN size_t KCALL
handle_signalfd_read(struct signalfd *__restrict self,
                     USER CHECKED void *dst,
                     size_t num_bytes, iomode_t mode) {
	size_t result;
	assert(!task_wasconnected());
	if unlikely(num_bytes < sizeof(struct signalfd_siginfo)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNALFD_BUFSIZE,
		      num_bytes);
	}
	result = 0;
	for (;;) {
		struct pending_rpc *rpc;
		USER CHECKED struct signalfd_siginfo *usi;
		rpc = task_rpc_pending_steal_posix_signal(&self->sf_mask);
		if (!rpc)
			rpc = proc_rpc_pending_steal_posix_signal(&self->sf_mask);
		if (!rpc) {
			if (mode & IO_NONBLOCK) {
				if (result)
					break; /* At least something was already read. */
				if (mode & IO_NODATAZERO)
					break;
				THROW(E_WOULDBLOCK_WAITFORSIGNAL);
			}
			assert(!task_wasconnected());
			task_connect(&PERTASK(this_rpcs_sig));
			TRY {
				task_connect(&THIS_PROCESS_RPCS.ppr_more);
				rpc = task_rpc_pending_steal_posix_signal(&self->sf_mask);
				if (!rpc)
					rpc = proc_rpc_pending_steal_posix_signal(&self->sf_mask);
			} EXCEPT {
				task_disconnectall();
				RETHROW();
			}
			if likely(!rpc) {
				/* NOTE: Signals that aren't  masked by the  calling thread will  be
				 *       handled normally when this right here calls `task_serve()'.
				 * As such, trying  to signals  not masked in  the calling  thread's
				 * signal mask from a signalfd is inherently racy and while allowed,
				 * really shouldn't be done  as there is no  way to predict if  some
				 * signal is read from the signalfd, or handled the normal way.
				 *
				 * As the solution, user-space code should ensure that no signal
				 * contained in the signalfd's mask is unmasked in the  thread's
				 * signal mask at the time the read(2) is made! */
				task_waitfor();
				continue;
			}
			task_disconnectall();
		}
		assert(rpc);
		assert(!(rpc->pr_flags & RPC_CONTEXT_KERN));
		assert(rpc->pr_flags & RPC_CONTEXT_SIGNAL);
		usi = (USER CHECKED struct signalfd_siginfo *)dst;

		/* Fill in the user-space signalfd info buffer. */
		{
			RAII_FINALLY { pending_rpc_free(rpc); };
			COMPILER_WRITE_BARRIER();
			usi->ssi_signo   = rpc->pr_psig.si_signo;
			usi->ssi_errno   = rpc->pr_psig.si_errno;
			usi->ssi_code    = rpc->pr_psig.si_code;
			usi->ssi_pid     = rpc->pr_psig.si_pid;
			usi->ssi_uid     = rpc->pr_psig.si_uid;
			usi->ssi_fd      = rpc->pr_psig.si_fd;
			usi->ssi_tid     = rpc->pr_psig.si_timerid;
			usi->ssi_band    = rpc->pr_psig.si_band;
			usi->ssi_overrun = rpc->pr_psig.si_overrun;
			usi->ssi_trapno  = 0; /* ??? */
			usi->ssi_status  = rpc->pr_psig.si_status;
			usi->ssi_int     = rpc->pr_psig.si_int;
			usi->ssi_ptr     = (u64)(uintptr_t)rpc->pr_psig.si_ptr;
			usi->ssi_utime   = rpc->pr_psig.si_utime;
			usi->ssi_stime   = rpc->pr_psig.si_stime;
			usi->ssi_addr    = (u64)(uintptr_t)rpc->pr_psig.si_addr;
			memset(usi->__pad, 0, sizeof(usi->__pad));
			COMPILER_WRITE_BARRIER();
		}

		result += sizeof(struct signalfd_siginfo);
		num_bytes -= sizeof(struct signalfd_siginfo);
		if (num_bytes < sizeof(struct signalfd_siginfo))
			break;
		dst = (byte_t *)dst + sizeof(struct signalfd_siginfo);
	}
	return result;
}


INTERN NONNULL((1)) void KCALL
handle_signalfd_pollconnect(struct signalfd *__restrict UNUSED(self),
                            poll_mode_t what) {
	if (what & POLLINMASK) {
		task_connect_for_poll(&PERTASK(this_rpcs_sig));
		task_connect_for_poll(&THIS_PROCESS_RPCS.ppr_more);
	}
}




INTERN ATTR_PURE WUNUSED NONNULL((1)) poll_mode_t KCALL
handle_signalfd_polltest(struct signalfd *__restrict self,
                         poll_mode_t what) {
	if (what & POLLINMASK) {
		if (task_rpc_pending_oneof(&self->sf_mask) ||
		    proc_rpc_pending_oneof(&self->sf_mask))
			return POLLINMASK;
	}
	return 0;
}





/************************************************************************/
/* signalfd(), signalfd4()                                              */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SIGNALFD4

PRIVATE ATTR_NOINLINE void KCALL
update_signalfd(unsigned int fd,
                USER CHECKED sigset_t const *sigmask) {
	struct signalfd *sfd;
	sigset_t newmask;
	struct handle hnd = handle_lookup(fd);
	RAII_FINALLY { decref_unlikely(hnd); };

	/* Make sure that it's a SIGNALFD handle. */
	if (hnd.h_type != HANDLE_TYPE_SIGNALFD) {
		THROW(E_INVALID_HANDLE_FILETYPE,
		      fd,
		      HANDLE_TYPE_SIGNALFD,
		      hnd.h_type,
		      handle_typekind(&hnd),
		      HANDLE_TYPEKIND_GENERIC);
	}
	sfd = (struct signalfd *)hnd.h_data;
	COMPILER_BARRIER();
	memcpy(&newmask, sigmask, sizeof(sigset_t));
	COMPILER_BARRIER();

	/* Always remove  SIGKILL and  SIGSTOP from  the new  mask
	 * before applying it, thus ensuring  that at no point  in
	 * time a signalfd descriptor exists that would be capable
	 * of handling these 2 signal. */
	sigdelset(&newmask, SIGKILL);
	sigdelset(&newmask, SIGSTOP);
	COMPILER_BARRIER();
	memcpy(&sfd->sf_mask, &newmask, sizeof(sigset_t));

	/* The online documentation does not specify if a  thread
	 * currently waiting on  a signalfd should  wake up  when
	 * the mask changes. Especially considering that doing so
	 * would require an additional signal to be added to  the
	 * `struct signalfd' just for the purpose of listening to
	 * mask changes.
	 * However,  looking  at  the  linux  kernel  source,  it  seems
	 * to  do  something  in-between of  not  doing it  at  all, and
	 * doing  it  correctly, by  simply  waking up  any  thread that
	 * is  currently waiting  for the  signal queues  of the calling
	 * thread, meaning that the wakeup wouldn't work if the signalfd
	 * was shared between processes,  with one process updating  the
	 * mask  not  actually causing  the  other to  get  the message.
	 * Oh well... Just mirror what linux does... */
	sig_broadcast(&PERTASK(this_rpcs_sig));
	sig_broadcast(&THIS_PROCESS_RPCS.ppr_more);
}

DEFINE_SYSCALL4(fd_t, signalfd4, fd_t, fd,
                USER UNCHECKED sigset_t const *, sigmask,
                size_t, sigsetsize, syscall_ulong_t, flags) {
	unsigned int result;
	REF struct signalfd *sfd;
	/* NOTE: Yes, validate `flags' even in the `fd == -1' case
	 *       when they're not even used. (linux does the same) */
	VALIDATE_FLAGSET(flags,
	                 SFD_NONBLOCK | SFD_CLOEXEC | SFD_CLOFORK,
	                 E_INVALID_ARGUMENT_CONTEXT_SIGNALFD_FLAGS);
	if unlikely(sigsetsize != sizeof(sigset_t)) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_SIGNAL_SIGSET_SIZE,
		      sigsetsize);
	}
	validate_readable(sigmask, sizeof(sigset_t));
	if (fd != -1) {
		/* Update an existing signalfd descriptor. */
		result = (unsigned int)fd;
		update_signalfd(result, sigmask);
	} else {
		sfd = signalfd_create(sigmask);
		TRY {
			struct handle hnd;
			hnd.h_data = sfd;
			hnd.h_type = HANDLE_TYPE_SIGNALFD;
			hnd.h_mode = IO_RDONLY; /* Write-access would just throw `E_FSERROR_UNSUPPORTED_OPERATION' regardlessly... */
			if (flags & SFD_NONBLOCK)
				hnd.h_mode |= IO_NONBLOCK;
			if (flags & SFD_CLOEXEC)
				hnd.h_mode |= IO_CLOEXEC;
			if (flags & SFD_CLOFORK)
				hnd.h_mode |= IO_CLOFORK;
			result = handle_install(THIS_HANDLE_MANAGER, hnd);
		} EXCEPT {
			destroy(sfd);
			RETHROW();
		}
		decref_unlikely(sfd);
	}
	return (fd_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_SIGNALFD4 */

#ifdef __ARCH_WANT_SYSCALL_SIGNALFD
DEFINE_SYSCALL3(fd_t, signalfd, fd_t, fd,
                USER UNCHECKED sigset_t const *, sigmask,
                size_t, sigsetsize) {
	return sys_signalfd4(fd, sigmask, sigsetsize, 0);
}
#endif /* __ARCH_WANT_SYSCALL_SIGNALFD */

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_POSIX_SIGNALFD_C */
