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
#ifndef GUARD_KERNEL_SRC_FD_POLL_C
#define GUARD_KERNEL_SRC_FD_POLL_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define _TIME64_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/rt/except-handler.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/rpc.h>
#include <sched/sigmask.h>
#include <sched/tsc.h>

#include <hybrid/align.h>

#include <bits/os/sigset_with_size.h>
#include <bits/os/timespec.h>
#include <bits/os/timeval.h>
#include <compat/config.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/types.h>
#include <sys/poll.h>
#include <sys/select.h>

#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/os/sigset_with_size.h>
#include <compat/bits/os/timespec.h>
#include <compat/bits/os/timeval.h>
#include <compat/kos/types.h>
#include <compat/pointer.h>
#include <compat/signal.h>
#endif /* __ARCH_HAVE_COMPAT */

#if (defined(__ARCH_WANT_SYSCALL_SELECT) && defined(__ARCH_WANT_SYSCALL__NEWSELECT))
#include <kos/compat/linux-oldselect.h>
#endif /* __ARCH_WANT_SYSCALL_SELECT && __ARCH_WANT_SYSCALL__NEWSELECT */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_SELECT) && defined(__ARCH_WANT_COMPAT_SYSCALL__NEWSELECT))
#include <compat/kos/compat/linux-oldselect.h>
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SELECT && __ARCH_WANT_COMPAT_SYSCALL__NEWSELECT */

#undef sigmask

DECL_BEGIN

/************************************************************************/
/* poll(), ppoll(), ppoll64()                                           */
/* select(), select64(), pselect6(), pselect6_time64()                  */
/************************************************************************/
#undef WANT_SYS_POLL
#if (defined(__ARCH_WANT_SYSCALL_POLL) ||         \
     defined(__ARCH_WANT_SYSCALL_PPOLL) ||        \
     defined(__ARCH_WANT_SYSCALL_PPOLL_TIME64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL_TIME64))
#define WANT_SYS_POLL 1
#endif /* poll... */
#undef WANT_SYS_SELECT
#if (defined(__ARCH_WANT_SYSCALL_SELECT) ||               \
     defined(__ARCH_WANT_SYSCALL_SELECT64) ||             \
     defined(__ARCH_WANT_SYSCALL_SELECT_TIME64) ||        \
     defined(__ARCH_WANT_SYSCALL_PSELECT6) ||             \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SELECT) ||        \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SELECT64) ||      \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SELECT_TIME64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6) ||      \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6_TIME64))
#define WANT_SYS_SELECT 1
#endif /* select... */
#if (defined(__ARCH_WANT_SYSCALL_PPOLL) ||                  \
     defined(__ARCH_WANT_SYSCALL_PPOLL_TIME64) ||           \
     defined(__ARCH_WANT_SYSCALL_PSELECT6) ||               \
     defined(__ARCH_WANT_SYSCALL_PSELECT6_TIME64) ||        \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL) ||           \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL_TIME64) ||    \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6) ||        \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6_TIME64) || \
     defined(__ARCH_WANT_SYSCALL_EPOLL_PWAIT))
#define WANT_SYS_POLLSELECT_SIGSET 1
#endif /* p(poll|select)... */
#if (defined(__ARCH_WANT_SYSCALL_PPOLL) ||        \
     defined(__ARCH_WANT_SYSCALL_PPOLL_TIME64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL_TIME64))
#define WANT_SYS_POLL_SIGSET 1
#endif /* ppoll... */
#if (defined(__ARCH_WANT_SYSCALL_PSELECT6) ||        \
     defined(__ARCH_WANT_SYSCALL_PSELECT6_TIME64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6_TIME64))
#define WANT_SYS_SELECT_SIGSET 1
#endif /* pselect... */

#if defined(WANT_SYS_POLL) || defined(WANT_SYS_SELECT)
PRIVATE poll_mode_t KCALL do_poll_handle(struct handle &hnd,
                                         poll_mode_t what) {
	/* Always allow polling for these conditions. */
	what |= POLLERR | POLLHUP | POLLNVAL;
	/* Verify that the caller has access to the
	 * indicated  data  channel of  the handle. */
	if (what & POLLINMASK) {
		if unlikely(!IO_CANREAD(hnd.h_mode))
			return POLLERR;
	}
	if (what & POLLOUTMASK) {
		if unlikely(!IO_CANWRITE(hnd.h_mode))
			return POLLERR;
	}
	return handle_poll(hnd, what) & what;
}
#endif /* WANT_SYS_POLL || WANT_SYS_SELECT */

/* Low-level implementations for the user-space poll() and select() system calls. */
#ifdef WANT_SYS_POLL
PRIVATE size_t KCALL
do_poll_scan(NCX struct pollfd *fds, size_t nfds) {
	size_t i, result = 0;
	assert(!task_wasconnected());
	for (i = 0; i < nfds; ++i) {
		struct handle hnd;
		struct pollfd pfd;
		memcpy(&pfd, &fds[i], sizeof(struct pollfd));
		COMPILER_READ_BARRIER();
		if (pfd.fd < 0) {
			/* Negative fd values should simply be ignored */
			fds[i].revents = 0;
			continue;
		}
		TRY {
			hnd = handles_lookup(pfd.fd);
		} EXCEPT {
			if (!was_thrown(E_INVALID_HANDLE))
				RETHROW();
			fds[i].revents = POLLNVAL; /* Invalid handle. */
			continue;
		}
		TRY {
			poll_mode_t what;
#if 0 /* POSIX doesn't specify this... (as a matter of fact: certain bits _should_ be ignored) */
			if unlikely(pfd.events & ~(POLLINMASK | POLLPRI | POLLOUTMASK)) {
				fds[i].revents = POLLNVAL; /* Invalid poll mode. */
				goto decref_hnd_and_continue;
			}
#endif
#ifndef __OPTIMIZE_SIZE__
			/* No need to stay connected to a whole bunch of signals
			 * if  we  already know  we won't  wait  on any  of them */
			if (result != 0)
				task_disconnectall();
#endif /* !__OPTIMIZE_SIZE__ */
			/* Actually perform the poll. */
			what = do_poll_handle(hnd, pfd.events);
			if (what & (POLLINMASK | POLLPRI | POLLOUTMASK))
				++result; /* Got something! */
			fds[i].revents = what;
		} EXCEPT {
			/* Make sure that we're disconnected
			 * from  all  previous poll-signals! */
			task_disconnectall();
			decref(hnd);
			RETHROW();
		}
/*decref_hnd_and_continue:*/
		decref(hnd);
	}
	return result;
}

PRIVATE size_t KCALL
do_poll(NCX struct pollfd *fds,
        size_t nfds, ktime_t abs_timeout) {
	size_t result;
	/* TODO: Special optimization for when  `abs_timeout == KTIME_NONBLOCK'!
	 *       In this case, it's  enough if we just  test all of the  handles
	 *       for their poll conditions, and forgo all of the signal handling */
again:
	/* Do the poll-scan. */
	result = do_poll_scan(fds, nfds);

	/* Check if any of the specified operations would block.
	 * If not, disconnect from any connected signal and indicate success. */
	if (result) {
		task_disconnectall();
		return result;
	}

	/* Wait for something to happen */
	if (!task_waitfor(abs_timeout))
		return 0; /* Timeout */

	/* Check to see what happened. */
	goto again;
}

PRIVATE size_t KCALL
do_poll_with_sigmask(NCX struct pollfd *fds,
                     size_t nfds, ktime_t abs_timeout,
                     sigset_t const *__restrict sigmask) {
	size_t result;
again:
	/* Do the poll-scan. */
	result = do_poll_scan(fds, nfds);

	/* Check if any of the specified operations would block.
	 * If not, disconnect from any connected signal and indicate success. */
	if (result) {
		task_disconnectall();
		return result;
	}

	/* Wait for something to happen */
	if (!task_waitfor_with_sigmask(sigmask, abs_timeout))
		return 0; /* Timeout */

	/* Check to see what happened. */
	goto again;
}
#endif /* WANT_SYS_POLL */

#ifdef WANT_SYS_SELECT
PRIVATE size_t KCALL
do_select_scan(size_t nfds,
               NCX fd_set *readfds,
               NCX fd_set *writefds,
               NCX fd_set *exceptfds) {
	typedef u8 fds_word_t;
	enum { BITS_PER_FDS_WORD = 8 };
	size_t nfds_words, i, result = 0;
	assert(!task_wasconnected());
	nfds_words = CEILDIV(nfds, BITS_PER_FDS_WORD);
	for (i = 0; i < nfds_words; ++i) {
		fds_word_t rbits, wbits, ebits, mask;
		fds_word_t new_rbits, new_wbits, new_ebits;
		unsigned int j, maxbits = BITS_PER_FDS_WORD;
		if (i == nfds_words - 1)
			maxbits = nfds % BITS_PER_FDS_WORD;
		rbits = wbits = ebits = 0;
		if (readfds)
			rbits = ((fds_word_t *)readfds)[i];
		if (writefds)
			wbits = ((fds_word_t *)writefds)[i];
		if (exceptfds)
			ebits = ((fds_word_t *)exceptfds)[i];
		if (!(rbits | wbits | ebits))
			continue;
		new_rbits = new_wbits = new_ebits = 0;
		for (j = 0, mask = 1; j < maxbits; ++j, mask <<= 1) {
			poll_mode_t what, mode;
			struct handle hnd;
			mode = 0;
			if (rbits & mask)
				mode |= POLLSELECT_READFDS;
			if (wbits & mask)
				mode |= POLLSELECT_WRITEFDS;
			if (ebits & mask)
				mode |= POLLSELECT_EXCEPTFDS;
			if (!mode)
				continue;
			hnd = handles_lookup_nosym(i * BITS_PER_FDS_WORD + j);
			TRY {
#ifndef __OPTIMIZE_SIZE__
				/* No need to stay connected to a whole bunch of signals
				 * if  we  already know  we won't  wait  on any  of them */
				if (result != 0)
					task_disconnectall();
#endif /* !__OPTIMIZE_SIZE__ */
				what = do_poll_handle(hnd, mode);
			} EXCEPT {
				/* Make sure that we're disconnected
				 * from  all  previous poll-signals! */
				task_disconnectall();
				decref(hnd);
				RETHROW();
			}
			assert(!(what & ~mode));
			decref(hnd);
			if (!what)
				continue;
			if (!result) {
				/* Clear all fd_set bits leading words. */
				if (readfds)
					bzero(readfds, i, sizeof(fds_word_t));
				if (writefds)
					bzero(writefds, i, sizeof(fds_word_t));
				if (exceptfds)
					bzero(exceptfds, i, sizeof(fds_word_t));
			}
			++result;
			if (what & POLLSELECT_READFDS)
				new_rbits |= mask;
			if (what & POLLSELECT_WRITEFDS)
				new_wbits |= mask;
			if (what & POLLSELECT_EXCEPTFDS)
				new_ebits |= mask;
		}
		if (result) {
			/* Update the fd-set words of all signaled FDs */
			if (readfds)
				((fds_word_t *)readfds)[i] = new_rbits;
			if (writefds)
				((fds_word_t *)writefds)[i] = new_wbits;
			if (exceptfds)
				((fds_word_t *)exceptfds)[i] = new_ebits;
		}
	}
	return result;
}

PRIVATE size_t KCALL
do_select(size_t nfds,
          NCX fd_set *readfds,
          NCX fd_set *writefds,
          NCX fd_set *exceptfds,
          ktime_t abs_timeout) {
	size_t result;
again:
	/* Do the select-scan. */
	result = do_select_scan(nfds, readfds, writefds, exceptfds);

	/* Check if any of the specified operations would block.
	 * If not, disconnect from any connected signal and indicate success. */
	if (result) {
		task_disconnectall();
		return result;
	}

	/* Wait for something to happen */
	if (!task_waitfor(abs_timeout))
		return 0; /* Timeout */

	/* Check to see what happened. */
	goto again;
}

PRIVATE size_t KCALL
do_select_with_sigmask(size_t nfds,
                       NCX fd_set *readfds,
                       NCX fd_set *writefds,
                       NCX fd_set *exceptfds,
                       ktime_t abs_timeout,
                       sigset_t const *__restrict sigmask) {
	size_t result;
again:
	/* Do the select-scan. */
	result = do_select_scan(nfds, readfds, writefds, exceptfds);

	/* Check if any of the specified operations would block.
	 * If not, disconnect from any connected signal and indicate success. */
	if (result) {
		task_disconnectall();
		return result;
	}

	/* Wait for something to happen */
	if (!task_waitfor_with_sigmask(sigmask, abs_timeout))
		return 0; /* Timeout */

	/* Check to see what happened. */
	goto again;
}
#endif /* WANT_SYS_SELECT */

#ifdef __ARCH_WANT_SYSCALL_POLL
DEFINE_SYSCALL3(ssize_t, poll,
                NCX UNCHECKED struct pollfd *, fds,
                size_t, nfds, syscall_slong_t, timeout) {
	size_t result;
	validate_readwritem(fds, nfds, sizeof(struct pollfd));
	if (timeout < 0) {
		result = do_poll(fds, nfds, KTIME_INFINITE);
	} else if (timeout == 0) {
		result = do_poll(fds, nfds, KTIME_NONBLOCK);
	} else {
		ktime_t then = ktime();
		then += relktime_from_milliseconds((uintptr_t)timeout);
		result = do_poll(fds, nfds, then);
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_POLL */


#if (defined(__ARCH_WANT_SYSCALL_PPOLL) ||        \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL) || \
     defined(__ARCH_WANT_SYSCALL_PPOLL_TIME64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PPOLL_TIME64))
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *
sys_ppoll_generic(struct icpustate *__restrict state,
                  struct rpc_syscall_info *__restrict sc_info,
                  NCX UNCHECKED struct pollfd *fds, size_t nfds, ktime_t abs_timeout,
                  NCX UNCHECKED sigset_t const *sigmask, size_t sigsetsize) {
	size_t result;
	validate_readwritem(fds, nfds, sizeof(struct pollfd));
	if (sigmask) {
		sigset_t these;
		validate_readable(sigmask, sigsetsize);
		if (sigsetsize > sizeof(sigset_t))
			sigsetsize = sizeof(sigset_t);
		memset(mempcpy(&these, sigmask, sigsetsize),
		       0xff, sizeof(sigset_t) - sigsetsize);

		/* These signals cannot be masked.  */
		sigdelset_nmi(&these);

		/* Prepare the calling thread for a sigsuspend() operation. */
		sigmask_prepare_sigsuspend();
again:
		TRY {
			result = do_poll_with_sigmask(fds, nfds, abs_timeout, &these);
		} EXCEPT {
			/* This function  only returns  normally
			 * when the syscall should be restarted. */
			state = userexcept_handler_with_sigmask(state, sc_info, &these);
			PERTASK_SET(this_exception_code, 1); /* Prevent internal fault */
			goto again;
		}
	} else {
		result = do_poll(fds, nfds, abs_timeout);
	}
	icpustate_setreturn(state, result);
	return state;
}
#endif /* ppoll... */

#ifdef __ARCH_WANT_SYSCALL_PPOLL
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
sys_ppoll_impl(struct icpustate *__restrict state,
               struct rpc_syscall_info *__restrict sc_info) {
	NCX UNCHECKED struct pollfd *fds                  = (NCX UNCHECKED struct pollfd *)sc_info->rsi_regs[0];
	size_t nfds                                        = (size_t)sc_info->rsi_regs[1];
	NCX UNCHECKED struct timespec32 const *timeout_ts = (NCX UNCHECKED struct timespec32 const *)sc_info->rsi_regs[2];
	NCX UNCHECKED sigset_t const *sigmask             = (NCX UNCHECKED sigset_t const *)sc_info->rsi_regs[3];
	size_t sigsetsize                                  = (size_t)sc_info->rsi_regs[4];
	ktime_t abs_timeout;
	abs_timeout = KTIME_INFINITE;
	if (timeout_ts) {
		validate_readable(timeout_ts, sizeof(*timeout_ts));
		abs_timeout = relktime_from_user_rel(timeout_ts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	return sys_ppoll_generic(state, sc_info, fds, nfds, abs_timeout, sigmask, sigsetsize);
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_ppoll_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_ppoll_impl(ctx->rc_state, &ctx->rc_scinfo);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL5(ssize_t, ppoll,
                NCX UNCHECKED struct pollfd *, fds, size_t, nfds,
                NCX UNCHECKED struct timespec32 const *, timeout_ts,
                NCX UNCHECKED sigset_t const *, sigmask,
                size_t, sigsetsize) {
	size_t result;
	ktime_t abs_timeout;
	if (sigmask) {
		(void)sigsetsize;
		/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
		task_rpc_userunwind(&sys_ppoll_rpc, NULL);
		__builtin_unreachable();
	}
	validate_readwritem(fds, nfds, sizeof(struct pollfd));
	abs_timeout = KTIME_INFINITE;
	if (timeout_ts) {
		validate_readable(timeout_ts, sizeof(*timeout_ts));
		abs_timeout = relktime_from_user_rel(timeout_ts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_poll(fds, nfds, abs_timeout);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PPOLL */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PPOLL
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
sys_compat_ppoll_impl(struct icpustate *__restrict state,
                      struct rpc_syscall_info *__restrict sc_info) {
	NCX UNCHECKED struct pollfd *fds                         = (NCX UNCHECKED struct pollfd *)sc_info->rsi_regs[0];
	size_t nfds                                               = (size_t)sc_info->rsi_regs[1];
	NCX UNCHECKED struct compat_timespec32 const *timeout_ts = (NCX UNCHECKED struct compat_timespec32 const *)sc_info->rsi_regs[2];
	NCX UNCHECKED compat_sigset_t const *sigmask             = (NCX UNCHECKED compat_sigset_t const *)sc_info->rsi_regs[3];
	size_t sigsetsize                                         = (size_t)sc_info->rsi_regs[4];
	ktime_t abs_timeout;
	abs_timeout = KTIME_INFINITE;
	if (timeout_ts) {
		validate_readable(timeout_ts, sizeof(*timeout_ts));
		abs_timeout = relktime_from_user_rel(timeout_ts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	return sys_ppoll_generic(state, sc_info, fds, nfds, abs_timeout, sigmask, sigsetsize);
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_compat_ppoll_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_compat_ppoll_impl(ctx->rc_state, &ctx->rc_scinfo);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_COMPAT_SYSCALL5(ssize_t, ppoll,
                       NCX UNCHECKED struct pollfd *, fds, size_t, nfds,
                       NCX UNCHECKED struct compat_timespec32 const *, timeout_ts,
                       NCX UNCHECKED compat_sigset_t const *, sigmask,
                       size_t, sigsetsize) {
	size_t result;
	ktime_t abs_timeout;
	if (sigmask) {
		(void)sigsetsize;
		/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
		task_rpc_userunwind(&sys_compat_ppoll_rpc, NULL);
		__builtin_unreachable();
	}
	compat_validate_readwritem(fds, nfds, sizeof(struct pollfd));
	abs_timeout = KTIME_INFINITE;
	if (timeout_ts) {
		compat_validate_readable(timeout_ts, sizeof(*timeout_ts));
		abs_timeout = relktime_from_user_rel(timeout_ts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_poll(fds, nfds, abs_timeout);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PPOLL */

#ifdef __ARCH_WANT_SYSCALL_PPOLL_TIME64
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
sys_ppoll_time64_impl(struct icpustate *__restrict state,
                             struct rpc_syscall_info *__restrict sc_info) {
	NCX UNCHECKED struct pollfd *fds                  = (NCX UNCHECKED struct pollfd *)sc_info->rsi_regs[0];
	size_t nfds                                        = (size_t)sc_info->rsi_regs[1];
	NCX UNCHECKED struct timespec64 const *timeout_ts = (NCX UNCHECKED struct timespec64 const *)sc_info->rsi_regs[2];
	NCX UNCHECKED sigset_t const *sigmask             = (NCX UNCHECKED sigset_t const *)sc_info->rsi_regs[3];
	size_t sigsetsize                                  = (size_t)sc_info->rsi_regs[4];
	ktime_t abs_timeout;
	abs_timeout = KTIME_INFINITE;
	if (timeout_ts) {
		validate_readable(timeout_ts, sizeof(*timeout_ts));
		abs_timeout = relktime_from_user_rel(timeout_ts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	return sys_ppoll_generic(state, sc_info, fds, nfds, abs_timeout, sigmask, sigsetsize);
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_ppoll_time64_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_ppoll_time64_impl(ctx->rc_state, &ctx->rc_scinfo);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL5(ssize_t, ppoll_time64,
                NCX UNCHECKED struct pollfd *, fds, size_t, nfds,
                NCX UNCHECKED struct timespec64 const *, timeout_ts,
                NCX UNCHECKED sigset_t const *, sigmask,
                size_t, sigsetsize) {
	size_t result;
	ktime_t abs_timeout;
	if (sigmask) {
		(void)sigsetsize;
		/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
		task_rpc_userunwind(&sys_ppoll_time64_rpc, NULL);
		__builtin_unreachable();
	}
	validate_readwritem(fds, nfds, sizeof(struct pollfd));
	abs_timeout = KTIME_INFINITE;
	if (timeout_ts) {
		validate_readable(timeout_ts, sizeof(*timeout_ts));
		abs_timeout = relktime_from_user_rel(timeout_ts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_poll(fds, nfds, abs_timeout);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PPOLL_TIME64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PPOLL_TIME64
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
sys_compat_ppoll_time64_impl(struct icpustate *__restrict state,
                             struct rpc_syscall_info *__restrict sc_info) {
	NCX UNCHECKED struct pollfd *fds                         = (NCX UNCHECKED struct pollfd *)sc_info->rsi_regs[0];
	size_t nfds                                               = (size_t)sc_info->rsi_regs[1];
	NCX UNCHECKED struct compat_timespec64 const *timeout_ts = (NCX UNCHECKED struct compat_timespec64 const *)sc_info->rsi_regs[2];
	NCX UNCHECKED compat_sigset_t const *sigmask             = (NCX UNCHECKED compat_sigset_t const *)sc_info->rsi_regs[3];
	size_t sigsetsize                                         = (size_t)sc_info->rsi_regs[4];
	ktime_t abs_timeout;
	abs_timeout = KTIME_INFINITE;
	if (timeout_ts) {
		validate_readable(timeout_ts, sizeof(*timeout_ts));
		abs_timeout = relktime_from_user_rel(timeout_ts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	return sys_ppoll_generic(state, sc_info, fds, nfds, abs_timeout, sigmask, sigsetsize);
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_compat_ppoll_time64_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_compat_ppoll_time64_impl(ctx->rc_state, &ctx->rc_scinfo);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_COMPAT_SYSCALL5(ssize_t, ppoll_time64,
                       NCX UNCHECKED struct pollfd *, fds, size_t, nfds,
                       NCX UNCHECKED struct compat_timespec64 const *, timeout_ts,
                       NCX UNCHECKED compat_sigset_t const *, sigmask,
                       size_t, sigsetsize) {
	size_t result;
	ktime_t abs_timeout;
	if (sigmask) {
		(void)sigsetsize;
		/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
		task_rpc_userunwind(&sys_compat_ppoll_time64_rpc, NULL);
		__builtin_unreachable();
	}
	compat_validate_readwritem(fds, nfds, sizeof(struct pollfd));
	abs_timeout = KTIME_INFINITE;
	if (timeout_ts) {
		compat_validate_readable(timeout_ts, sizeof(*timeout_ts));
		abs_timeout = relktime_from_user_rel(timeout_ts);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_poll(fds, nfds, abs_timeout);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PPOLL_TIME64 */

#if (defined(__ARCH_WANT_SYSCALL_SELECT) || \
     defined(__ARCH_WANT_SYSCALL__NEWSELECT))
#ifdef __ARCH_WANT_SYSCALL__NEWSELECT
DEFINE_SYSCALL5(ssize_t, _newselect, size_t, nfds,
                NCX UNCHECKED fd_set *, readfds,
                NCX UNCHECKED fd_set *, writefds,
                NCX UNCHECKED fd_set *, exceptfds,
                NCX UNCHECKED struct timeval32 *, timeout)
#else /* __ARCH_WANT_SYSCALL__NEWSELECT */
DEFINE_SYSCALL5(ssize_t, select, size_t, nfds,
                NCX UNCHECKED fd_set *, readfds,
                NCX UNCHECKED fd_set *, writefds,
                NCX UNCHECKED fd_set *, exceptfds,
                NCX UNCHECKED struct timeval32 *, timeout)
#endif /* !__ARCH_WANT_SYSCALL__NEWSELECT */
{
	size_t result;
	ktime_t abs_timeout;
	validate_readwritem_opt(readfds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	validate_readwritem_opt(writefds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	validate_readwritem_opt(exceptfds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_select(nfds, readfds, writefds,
	                   exceptfds, abs_timeout);
	return (ssize_t)result;
}

#if (defined(__ARCH_WANT_SYSCALL_SELECT) && \
     defined(__ARCH_WANT_SYSCALL__NEWSELECT))
DEFINE_SYSCALL1(ssize_t, select,
                NCX UNCHECKED struct sel_arg_struct const *, arg) {
	ulongptr_t n;                         /* nfds argument */
	NCX UNCHECKED fd_set *inp;           /* Read fd-set */
	NCX UNCHECKED fd_set *outp;          /* Write fd-set */
	NCX UNCHECKED fd_set *exp;           /* Except fd-set */
	NCX UNCHECKED struct timeval32 *tvp; /* Timeout argument */
	validate_readable(arg, sizeof(*arg));
	COMPILER_READ_BARRIER();
	n    = arg->n;
	inp  = arg->inp;
	outp = arg->outp;
	exp  = arg->exp;
	tvp  = arg->tvp;
	COMPILER_READ_BARRIER();
	return sys__newselect(n, inp, outp, exp, tvp);
}
#endif /* __ARCH_WANT_SYSCALL_SELECT && __ARCH_WANT_SYSCALL__NEWSELECT */
#endif /* __ARCH_WANT_SYSCALL_SELECT || __ARCH_WANT_SYSCALL__NEWSELECT */

#if (defined(__ARCH_WANT_SYSCALL_SELECT64) || \
     defined(__ARCH_WANT_SYSCALL_SELECT_TIME64))
#ifdef __ARCH_WANT_SYSCALL_SELECT64
DEFINE_SYSCALL5(ssize_t, select64, size_t, nfds,
                NCX UNCHECKED fd_set *, readfds,
                NCX UNCHECKED fd_set *, writefds,
                NCX UNCHECKED fd_set *, exceptfds,
                NCX UNCHECKED struct timeval64 *, timeout)
#else /* __ARCH_WANT_SYSCALL_SELECT64 */
DEFINE_SYSCALL5(ssize_t, select_time64, size_t, nfds,
                NCX UNCHECKED fd_set *, readfds,
                NCX UNCHECKED fd_set *, writefds,
                NCX UNCHECKED fd_set *, exceptfds,
                NCX UNCHECKED struct timeval64 *, timeout)
#endif /* !__ARCH_WANT_SYSCALL_SELECT64 */
{
	size_t result;
	ktime_t abs_timeout;
	validate_readwritem_opt(readfds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	validate_readwritem_opt(writefds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	validate_readwritem_opt(exceptfds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_select(nfds, readfds, writefds,
	                   exceptfds, abs_timeout);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_SELECT64 || __ARCH_WANT_SYSCALL_SELECT_TIME64 */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_SELECT) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL__NEWSELECT))
PRIVATE ssize_t KCALL
compat_sys_select_impl(size_t nfds,
                       NCX UNCHECKED fd_set *readfds,
                       NCX UNCHECKED fd_set *writefds,
                       NCX UNCHECKED fd_set *exceptfds,
                       NCX UNCHECKED struct compat_timeval32 *timeout) {
	size_t result;
	ktime_t abs_timeout;
	compat_validate_readwritem_opt(readfds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	compat_validate_readwritem_opt(writefds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	compat_validate_readwritem_opt(exceptfds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		compat_validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_select(nfds, readfds, writefds,
	                   exceptfds, abs_timeout);
	return (ssize_t)result;
}

#ifdef __ARCH_WANT_COMPAT_SYSCALL__NEWSELECT
DEFINE_COMPAT_SYSCALL5(ssize_t, _newselect, size_t, nfds,
                       NCX UNCHECKED fd_set *, readfds,
                       NCX UNCHECKED fd_set *, writefds,
                       NCX UNCHECKED fd_set *, exceptfds,
                       NCX UNCHECKED struct compat_timeval32 *, timeout)
#else /* __ARCH_WANT_COMPAT_SYSCALL__NEWSELECT */
DEFINE_COMPAT_SYSCALL5(ssize_t, select, size_t, nfds,
                       NCX UNCHECKED fd_set *, readfds,
                       NCX UNCHECKED fd_set *, writefds,
                       NCX UNCHECKED fd_set *, exceptfds,
                       NCX UNCHECKED struct compat_timeval32 *, timeout)
#endif /* !__ARCH_WANT_COMPAT_SYSCALL__NEWSELECT */
{
	return compat_sys_select_impl(nfds,
	                              readfds,
	                              writefds,
	                              exceptfds,
	                              timeout);
}

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_SELECT) && \
     defined(__ARCH_WANT_COMPAT_SYSCALL__NEWSELECT))
DEFINE_COMPAT_SYSCALL1(ssize_t, select,
                       NCX UNCHECKED struct compat_sel_arg_struct const *, arg) {
	compat_ulongptr_t n;                     /* nfds argument */
	compat_ptr(fd_set) inp;                  /* Read fd-set */
	compat_ptr(fd_set) outp;                 /* Write fd-set */
	compat_ptr(fd_set) exp;                  /* Except fd-set */
	compat_ptr(struct compat_timeval32) tvp; /* Timeout argument */
	compat_validate_readable(arg, sizeof(*arg));
	COMPILER_READ_BARRIER();
	n    = arg->n;
	inp  = arg->inp;
	outp = arg->outp;
	exp  = arg->exp;
	tvp  = arg->tvp;
	COMPILER_READ_BARRIER();
	return compat_sys_select_impl(n, inp, outp, exp, tvp);
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SELECT && __ARCH_WANT_COMPAT_SYSCALL__NEWSELECT */
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SELECT || __ARCH_WANT_COMPAT_SYSCALL__NEWSELECT */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_SELECT64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_SELECT_TIME64))
#ifdef __ARCH_WANT_COMPAT_SYSCALL_SELECT64
DEFINE_COMPAT_SYSCALL5(ssize_t, select64, size_t, nfds,
                       NCX UNCHECKED fd_set *, readfds,
                       NCX UNCHECKED fd_set *, writefds,
                       NCX UNCHECKED fd_set *, exceptfds,
                       NCX UNCHECKED struct compat_timeval64 *, timeout)
#else /* __ARCH_WANT_COMPAT_SYSCALL_SELECT64 */
DEFINE_COMPAT_SYSCALL5(ssize_t, select_time64, size_t, nfds,
                       NCX UNCHECKED fd_set *, readfds,
                       NCX UNCHECKED fd_set *, writefds,
                       NCX UNCHECKED fd_set *, exceptfds,
                       NCX UNCHECKED struct compat_timeval64 *, timeout)
#endif /* !__ARCH_WANT_COMPAT_SYSCALL_SELECT64 */
{
	size_t result;
	ktime_t abs_timeout;
	compat_validate_readwritem_opt(readfds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	compat_validate_readwritem_opt(writefds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	compat_validate_readwritem_opt(exceptfds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		compat_validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_select(nfds, readfds, writefds,
	                   exceptfds, abs_timeout);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_SELECT64 */

#if (defined(__ARCH_WANT_SYSCALL_PSELECT6) ||        \
     defined(__ARCH_WANT_SYSCALL_PSELECT6_TIME64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_PSELECT6_TIME64))
PRIVATE ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *
sys_pselect_generic(struct icpustate *__restrict state,
                    struct rpc_syscall_info *__restrict sc_info, size_t nfds,
                    NCX UNCHECKED fd_set *readfds, NCX UNCHECKED fd_set *writefds,
                    NCX UNCHECKED fd_set *exceptfds, ktime_t abs_timeout,
                    NCX UNCHECKED sigset_t const *sigmask, size_t sigsetsize) {
	size_t result;
	validate_readwritem_opt(readfds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	validate_readwritem_opt(writefds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	validate_readwritem_opt(exceptfds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	if (sigmask) {
		sigset_t these;
		validate_readable(sigmask, sigsetsize);
		if (sigsetsize > sizeof(sigset_t))
			sigsetsize = sizeof(sigset_t);
		memset(mempcpy(&these, sigmask, sigsetsize),
			   0xff, sizeof(sigset_t) - sigsetsize);

		/* These signals cannot be masked.  */
		sigdelset(&these, SIGSTOP);
		sigdelset(&these, SIGKILL);

		/* Prepare the calling thread for a sigsuspend() operation. */
		sigmask_prepare_sigsuspend();
again:
		TRY {
			result = do_select_with_sigmask(nfds, readfds, writefds, exceptfds, abs_timeout, &these);
		} EXCEPT {
			/* This function  only returns  normally
			 * when the syscall should be restarted. */
			state = userexcept_handler_with_sigmask(state, sc_info, &these);
			PERTASK_SET(this_exception_code, 1); /* Prevent internal fault */
			goto again;
		}
	} else {
		result = do_select(nfds, readfds, writefds, exceptfds, abs_timeout);
	}
	icpustate_setreturn(state, result);
	return state;
}

#endif /* pselect... */

#ifdef __ARCH_WANT_SYSCALL_PSELECT6
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
sys_pselect6_impl(struct icpustate *__restrict state,
                  struct rpc_syscall_info *__restrict sc_info) {
	size_t nfds                                                          = (size_t)sc_info->rsi_regs[0];
	NCX UNCHECKED fd_set *readfds                                       = (NCX UNCHECKED fd_set *)sc_info->rsi_regs[1];
	NCX UNCHECKED fd_set *writefds                                      = (NCX UNCHECKED fd_set *)sc_info->rsi_regs[2];
	NCX UNCHECKED fd_set *exceptfds                                     = (NCX UNCHECKED fd_set *)sc_info->rsi_regs[3];
	NCX UNCHECKED struct timespec32 const *timeout                      = (NCX UNCHECKED struct timespec32 const *)sc_info->rsi_regs[4];
	NCX UNCHECKED struct sigset_with_size const *sigmask_sigset_and_len = (NCX UNCHECKED struct sigset_with_size const *)sc_info->rsi_regs[5];
	struct sigset_with_size ss;
	ktime_t abs_timeout;
	memcpy(&ss, validate_readable(sigmask_sigset_and_len, sizeof(ss)), sizeof(ss));
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	return sys_pselect_generic(state, sc_info, nfds, readfds, writefds,
	                           exceptfds, abs_timeout,
	                           ss.sws_sigset, ss.sws_sigsiz);
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_pselect6_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_pselect6_impl(ctx->rc_state, &ctx->rc_scinfo);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL6(ssize_t, pselect6, size_t, nfds,
                NCX UNCHECKED fd_set *, readfds,
                NCX UNCHECKED fd_set *, writefds,
                NCX UNCHECKED fd_set *, exceptfds,
                NCX UNCHECKED struct timespec32 const *, timeout,
                NCX UNCHECKED struct sigset_with_size const *, sigmask_sigset_with_size) {
	size_t result;
	ktime_t abs_timeout;
	validate_readable(sigmask_sigset_with_size, sizeof(*sigmask_sigset_with_size));
	if (sigmask_sigset_with_size->sws_sigset) {
		/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
		task_rpc_userunwind(&sys_pselect6_rpc, NULL);
		__builtin_unreachable();
	}
	validate_readwritem_opt(readfds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	validate_readwritem_opt(writefds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	validate_readwritem_opt(exceptfds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_select(nfds, readfds, writefds, exceptfds, abs_timeout);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PSELECT6 */

#ifdef __ARCH_WANT_SYSCALL_PSELECT6_TIME64
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
sys_pselect6_time64_impl(struct icpustate *__restrict state,
                         struct rpc_syscall_info *__restrict sc_info) {
	size_t nfds                                                          = (size_t)sc_info->rsi_regs[0];
	NCX UNCHECKED fd_set *readfds                                       = (NCX UNCHECKED fd_set *)sc_info->rsi_regs[1];
	NCX UNCHECKED fd_set *writefds                                      = (NCX UNCHECKED fd_set *)sc_info->rsi_regs[2];
	NCX UNCHECKED fd_set *exceptfds                                     = (NCX UNCHECKED fd_set *)sc_info->rsi_regs[3];
	NCX UNCHECKED struct timespec64 const *timeout                      = (NCX UNCHECKED struct timespec64 const *)sc_info->rsi_regs[4];
	NCX UNCHECKED struct sigset_with_size const *sigmask_sigset_and_len = (NCX UNCHECKED struct sigset_with_size const *)sc_info->rsi_regs[5];
	struct sigset_with_size ss;
	ktime_t abs_timeout;
	memcpy(&ss, validate_readable(sigmask_sigset_and_len, sizeof(ss)), sizeof(ss));
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	return sys_pselect_generic(state, sc_info, nfds, readfds, writefds,
	                           exceptfds, abs_timeout,
	                           ss.sws_sigset, ss.sws_sigsiz);
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_pselect6_time64_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_pselect6_time64_impl(ctx->rc_state, &ctx->rc_scinfo);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL6(ssize_t, pselect6_time64, size_t, nfds,
                NCX UNCHECKED fd_set *, readfds,
                NCX UNCHECKED fd_set *, writefds,
                NCX UNCHECKED fd_set *, exceptfds,
                NCX UNCHECKED struct timespec64 const *, timeout,
                NCX UNCHECKED struct sigset_with_size const *, sigmask_sigset_and_len) {
	size_t result;
	ktime_t abs_timeout;
	validate_readable(sigmask_sigset_and_len, sizeof(*sigmask_sigset_and_len));
	if (sigmask_sigset_and_len->sws_sigset) {
		/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
		task_rpc_userunwind(&sys_pselect6_time64_rpc, NULL);
		__builtin_unreachable();
	}
	validate_readwritem_opt(readfds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	validate_readwritem_opt(writefds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	validate_readwritem_opt(exceptfds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_select(nfds, readfds, writefds, exceptfds, abs_timeout);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_PSELECT6_TIME64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PSELECT6
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
sys_compat_pselect6_impl(struct icpustate *__restrict state,
                         struct rpc_syscall_info *__restrict sc_info) {
	size_t nfds                                                                 = (size_t)sc_info->rsi_regs[0];
	NCX UNCHECKED fd_set *readfds                                              = (NCX UNCHECKED fd_set *)sc_info->rsi_regs[1];
	NCX UNCHECKED fd_set *writefds                                             = (NCX UNCHECKED fd_set *)sc_info->rsi_regs[2];
	NCX UNCHECKED fd_set *exceptfds                                            = (NCX UNCHECKED fd_set *)sc_info->rsi_regs[3];
	NCX UNCHECKED struct compat_timespec32 const *timeout                      = (NCX UNCHECKED struct compat_timespec32 const *)sc_info->rsi_regs[4];
	NCX UNCHECKED struct compat_sigset_with_size const *sigmask_sigset_and_len = (NCX UNCHECKED struct compat_sigset_with_size const *)sc_info->rsi_regs[5];
	struct compat_sigset_with_size ss;
	ktime_t abs_timeout;
	memcpy(&ss, compat_validate_readable(sigmask_sigset_and_len, sizeof(ss)), sizeof(ss));
	COMPILER_READ_BARRIER();
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		compat_validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	return sys_pselect_generic(state, sc_info, nfds, readfds, writefds, exceptfds, abs_timeout,
	                           (sigset_t const *)(void *)ss.sws_sigset, ss.sws_sigsiz);
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_compat_pselect6_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_compat_pselect6_impl(ctx->rc_state, &ctx->rc_scinfo);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_COMPAT_SYSCALL6(ssize_t, pselect6, size_t, nfds,
                       NCX UNCHECKED fd_set *, readfds,
                       NCX UNCHECKED fd_set *, writefds,
                       NCX UNCHECKED fd_set *, exceptfds,
                       NCX UNCHECKED struct compat_timespec32 const *, timeout,
                       NCX UNCHECKED struct compat_sigset_with_size const *, sigmask_sigset_and_len) {
	size_t result;
	ktime_t abs_timeout;
	compat_validate_readable(sigmask_sigset_and_len, sizeof(*sigmask_sigset_and_len));
	if (sigmask_sigset_and_len->sws_sigset) {
		/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
		task_rpc_userunwind(&sys_compat_pselect6_rpc, NULL);
		__builtin_unreachable();
	}
	compat_validate_readwritem_opt(readfds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	compat_validate_readwritem_opt(writefds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	compat_validate_readwritem_opt(exceptfds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		compat_validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_select(nfds, readfds, writefds, exceptfds, abs_timeout);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PSELECT6 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_PSELECT6_TIME64
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) struct icpustate *FCALL
sys_compat_pselect6_time64_impl(struct icpustate *__restrict state,
                                struct rpc_syscall_info *__restrict sc_info) {
	size_t nfds                                                                 = (size_t)sc_info->rsi_regs[0];
	NCX UNCHECKED fd_set *readfds                                              = (NCX UNCHECKED fd_set *)sc_info->rsi_regs[1];
	NCX UNCHECKED fd_set *writefds                                             = (NCX UNCHECKED fd_set *)sc_info->rsi_regs[2];
	NCX UNCHECKED fd_set *exceptfds                                            = (NCX UNCHECKED fd_set *)sc_info->rsi_regs[3];
	NCX UNCHECKED struct compat_timespec64 const *timeout                      = (NCX UNCHECKED struct compat_timespec64 const *)sc_info->rsi_regs[4];
	NCX UNCHECKED struct compat_sigset_with_size const *sigmask_sigset_and_len = (NCX UNCHECKED struct compat_sigset_with_size const *)sc_info->rsi_regs[5];
	struct compat_sigset_with_size ss;
	ktime_t abs_timeout;
	memcpy(&ss, compat_validate_readable(sigmask_sigset_and_len, sizeof(ss)), sizeof(ss));
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		compat_validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	return sys_pselect_generic(state, sc_info, nfds, readfds, writefds, exceptfds, abs_timeout,
	                           (sigset_t const *)(void *)ss.sws_sigset, ss.sws_sigsiz);
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_compat_pselect6_time64_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the actual system call. */
	ctx->rc_state = sys_compat_pselect6_time64_impl(ctx->rc_state, &ctx->rc_scinfo);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_COMPAT_SYSCALL6(ssize_t, pselect6_time64, size_t, nfds,
                       NCX UNCHECKED fd_set *, readfds,
                       NCX UNCHECKED fd_set *, writefds,
                       NCX UNCHECKED fd_set *, exceptfds,
                       NCX UNCHECKED struct compat_timespec64 const *, timeout,
                       NCX UNCHECKED struct compat_sigset_with_size const *, sigmask_sigset_and_len) {
	size_t result;
	ktime_t abs_timeout;
	compat_validate_readable(sigmask_sigset_and_len, sizeof(*sigmask_sigset_and_len));
	if (sigmask_sigset_and_len->sws_sigset) {
		/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
		task_rpc_userunwind(&sys_compat_pselect6_time64_rpc, NULL);
		__builtin_unreachable();
	}
	compat_validate_readwritem_opt(readfds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	compat_validate_readwritem_opt(writefds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	compat_validate_readwritem_opt(exceptfds, CEILDIV(nfds, __NFDBITS), __SIZEOF_FD_MASK);
	abs_timeout = KTIME_INFINITE;
	if (timeout) {
		compat_validate_readable(timeout, sizeof(*timeout));
		abs_timeout = relktime_from_user_rel(timeout);
		if (abs_timeout != 0)
			abs_timeout += ktime();
	}
	result = do_select(nfds, readfds, writefds, exceptfds, abs_timeout);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_PSELECT6_TIME64 */




/************************************************************************/
/* pause()                                                              */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_PAUSE
DEFINE_SYSCALL0(errno_t, pause) {
	for (;;) {
		assert(!task_wasconnected());
		/* Wait forever (equivalent to `select(0, NULL, NULL, NULL, NULL)')
		 * NOTE: `task_waitfor()' calls `task_serve()', which may in turn throw
		 *       `E_INTERRUPT' when  a signal  gets  delivered to  our  thread. */
		task_waitfor();
	}
	/* Can't get here... */
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_PAUSE */

DECL_END

#endif /* !GUARD_KERNEL_SRC_FD_POLL_C */
