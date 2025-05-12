/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_TIMERFD_C
#define GUARD_APPS_SYSTEM_TEST_TEST_TIMERFD_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/futex.h>
#include <kos/rpc.h>
#include <kos/types.h>
#include <linux/timerfd.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/timerfd.h>
#include <system-test/ctest.h>

#include <atomic.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>

DECL_BEGIN

PRIVATE lfutex_t myrpc_called = 0;

PRIVATE NONNULL((1)) void
myrpc(struct rpc_context *__restrict ctx, void *cookie) {
#if 1
	syslog(LOG_DEBUG, "timerfd: in myrpc\n");
#else
	if (ctx->rc_context == RPC_REASONCTX_SYSCALL ||
	    ctx->rc_context == RPC_REASONCTX_SYSINT) {
		syslog(LOG_DEBUG,
		       "timerfd: in myrpc: "
		       "rc_scinfo: {rsi_flags:%#Ix,rsi_sysno:%#Ix,rsi_regs:{%#Ix,%#Ix,%#Ix,%#Ix,%#Ix,%#Ix}} "
		       "{eax:%#Ix,ecx:%#Ix,edx:%#Ix,ebx:%#Ix,esp:%#Ix,ebp:%#Ix,esi:%#Ix,edi:%#Ix"
		       ",ds:%#I16x,es:%#I16x,fs:%#I16x,gs:%#I16x,cs:%#I16x,ss:%#I16x"
		       ",eflags:%#Ix,eip:%#Ix}\n",
		       ctx->rc_scinfo.rsi_flags,
		       ctx->rc_scinfo.rsi_sysno,
		       ctx->rc_scinfo.rsi_regs[0],
		       ctx->rc_scinfo.rsi_regs[1],
		       ctx->rc_scinfo.rsi_regs[2],
		       ctx->rc_scinfo.rsi_regs[3],
		       ctx->rc_scinfo.rsi_regs[4],
		       ctx->rc_scinfo.rsi_regs[5],
		       ctx->rc_state->ucs_gpregs.gp_eax,
		       ctx->rc_state->ucs_gpregs.gp_ecx,
		       ctx->rc_state->ucs_gpregs.gp_edx,
		       ctx->rc_state->ucs_gpregs.gp_ebx,
		       ctx->rc_state->ucs_gpregs.gp_esp,
		       ctx->rc_state->ucs_gpregs.gp_ebp,
		       ctx->rc_state->ucs_gpregs.gp_esi,
		       ctx->rc_state->ucs_gpregs.gp_edi,
		       ctx->rc_state->ucs_sgregs.sg_ds16,
		       ctx->rc_state->ucs_sgregs.sg_es16,
		       ctx->rc_state->ucs_sgregs.sg_fs16,
		       ctx->rc_state->ucs_sgregs.sg_gs16,
		       ctx->rc_state->ucs_cs16,
		       ctx->rc_state->ucs_ss16,
		       ctx->rc_state->ucs_eflags,
		       ctx->rc_state->ucs_eip);
	} else {
		syslog(LOG_DEBUG,
		       "timerfd: in myrpc"
		       "{eax:%#Ix,ecx:%#Ix,edx:%#Ix,ebx:%#Ix,esp:%#Ix,ebp:%#Ix,esi:%#Ix,edi:%#Ix"
		       ",ds:%#I16x,es:%#I16x,fs:%#I16x,gs:%#I16x,cs:%#I16x,ss:%#I16x"
		       ",eflags:%#Ix,eip:%#Ix}\n",
		       ctx->rc_state->ucs_gpregs.gp_eax,
		       ctx->rc_state->ucs_gpregs.gp_ecx,
		       ctx->rc_state->ucs_gpregs.gp_edx,
		       ctx->rc_state->ucs_gpregs.gp_ebx,
		       ctx->rc_state->ucs_gpregs.gp_esp,
		       ctx->rc_state->ucs_gpregs.gp_ebp,
		       ctx->rc_state->ucs_gpregs.gp_esi,
		       ctx->rc_state->ucs_gpregs.gp_edi,
		       ctx->rc_state->ucs_sgregs.sg_ds16,
		       ctx->rc_state->ucs_sgregs.sg_es16,
		       ctx->rc_state->ucs_sgregs.sg_fs16,
		       ctx->rc_state->ucs_sgregs.sg_gs16,
		       ctx->rc_state->ucs_cs16,
		       ctx->rc_state->ucs_ss16,
		       ctx->rc_state->ucs_eflags,
		       ctx->rc_state->ucs_eip);
	}
#endif
	(void)ctx;
	EQ((void *)0x1234, cookie);
	atomic_inc(&myrpc_called);
	futex_wake(&myrpc_called);
}

DEFINE_TEST(timerfd) {
	fd_t tfd;
	fd_t epfd;
	struct itimerspec its;
	uint64_t tickets;
	struct epoll_event ee;
	NE(-1, (tfd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK)));
	memset(&its, 0xcc, sizeof(its));
	EQ(0, timerfd_gettime(tfd, &its));
	EQ(0, its.it_value.tv_sec);
	EQ(0, its.it_value.tv_nsec);
	EQ(0, its.it_interval.tv_sec);
	EQ(0, its.it_interval.tv_nsec);

	EQ(-1, read(tfd, &tickets, 7));
	EQerrno(EINVAL);

	EQ(-1, read(tfd, &tickets, 8));
	EQerrno(EAGAIN);

	/* Arm the timerfd. */
	its.it_value.tv_nsec = 10000000; /* 1/100th of a second */
	EQ(0, timerfd_settime(tfd, 0, &its, NULL));

	/* This operation here will block for 1/100th of a second */
	memset(&tickets, 0xcc, sizeof(tickets));
	EQ(0, fcntl(tfd, F_SETFL, fcntl(tfd, F_GETFL) & ~O_NONBLOCK));
	EQ(8, read(tfd, &tickets, 8));
	EQ(1, tickets);

	EQ(0, fcntl(tfd, F_SETFL, fcntl(tfd, F_GETFL) | O_NONBLOCK));
	EQ(-1, read(tfd, &tickets, 8));
	EQerrno(EAGAIN);

	tickets = 1001;
	EQ(0, ioctl(tfd, TFD_IOC_SET_TICKS, &tickets));

	memset(&tickets, 0xcc, sizeof(tickets));
	EQ(8, read(tfd, &tickets, 8));
	EQ(1001, tickets);
	EQ(-1, read(tfd, &tickets, 8));
	EQerrno(EAGAIN);

	/* Now make sure that epoll-based waiting with RPCs also works
	 * (iow: that you're able to pre-program epoll to send RPCs to
	 * a program at a pre-defined point in time). */
	NE(-1, (epfd = epoll_create1(0)));
	EQ(0, atomic_read(&myrpc_called));
	ee.events   = EPOLLIN;
	ee.data.ptr = (void *)0x1234;
	EQ(0, epoll_rpc_exec(epfd, tfd, &ee, gettid(),
	                     RPC_SYNCMODE_ASYNC | RPC_SYSRESTART_RESTART | RPC_DOMAIN_THREAD,
	                     &myrpc));
	EQ(0, atomic_read(&myrpc_called));

	/* Now program the timerfd to indicate readable in the near future. */
	bzero(&its, sizeof(its));
	its.it_value.tv_nsec = 10000000; /* 1/100th of a second */
	EQ(0, timerfd_settime(tfd, 0, &its, NULL));

	/* And now wait for the RPC to go out and arrive. */
	NE(-1, TEMP_FAILURE_RETRY(futex_waitwhile(&myrpc_called, 0)));
	EQ(1, myrpc_called);

	/* Check if poll() that the timerfd is still ready */
	{
		struct pollfd pfd[1];
		pfd[0].events  = POLLIN;
		pfd[0].fd      = tfd;
		pfd[0].revents = 0;
		EQ(1, poll(pfd, 1, -1));
		EQ(POLLIN, pfd[0].revents);
		EQ(1, poll(pfd, 1, -1));
		EQ(POLLIN, pfd[0].revents);
	}

	/* Scheduling an RPC while the timer is already ready must immediately invoke the RPC */
	EQ(1, atomic_read(&myrpc_called));
	ee.events   = EPOLLIN;
	ee.data.ptr = (void *)0x1234;
	EQ(0, epoll_rpc_exec(epfd, tfd, &ee, gettid(),
	                     RPC_SYNCMODE_ASYNC | RPC_SYSRESTART_RESTART | RPC_DOMAIN_THREAD,
	                     &myrpc));
	EQ(2, atomic_read(&myrpc_called));

	/* Consume the timer-ready flag */
	EQ(0, fcntl(tfd, F_SETFL, fcntl(tfd, F_GETFL) & ~O_NONBLOCK));
	EQ(8, read(tfd, &tickets, 8));
	EQ(1, tickets);

	/* Assert that another call would block. */
	EQ(0, fcntl(tfd, F_SETFL, fcntl(tfd, F_GETFL) | O_NONBLOCK));
	EQ(-1, read(tfd, &tickets, 8));
	EQerrno(EAGAIN);

	/* Cleanup... */
	EQ(0, close(epfd));
	EQ(0, close(tfd));
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_TIMERFD_C */
