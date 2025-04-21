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

#include <kos/except.h>
#include <kos/futex.h>
#include <kos/rpc.h>
#include <kos/types.h>
#include <linux/timerfd.h>
#include <sys/epoll.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/timerfd.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <atomic.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>


DECL_BEGIN

PRIVATE lfutex_t myrpc_called = 0;

PRIVATE NONNULL((1)) void
myrpc(struct rpc_context *__restrict ctx, void *cookie) {
	syslog(LOG_DEBUG, "timerfd: in myrpc\n");
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
	EQ(0, myrpc_called);
	ee.events   = EPOLLIN;
	ee.data.ptr = (void *)0x1234;
	EQ(0, epoll_rpc_exec(epfd, tfd, &ee, gettid(),
	                     RPC_SYNCMODE_ASYNC | RPC_SYSRESTART_RESTART | RPC_DOMAIN_THREAD,
	                     &myrpc));
	EQ(0, myrpc_called);

	/* Now program the timerfd to indicate readable in the near future. */
	bzero(&its, sizeof(its));
	its.it_value.tv_nsec = 10000000; /* 1/100th of a second */
/*FIXME:
[2025-04-21T18:15:44.635611427:trace ][12][test:timerfd] kos/src/apps/system-test/test-timerfd.c:62
[2025-04-21T18:15:44.635727853:trace ][12] sys_write(fd: STDOUT_FILENO, buf: "test:timerfd\e[K\n", bufsize: 16)
[2025-04-21T18:15:44.637976495:trace ][12][rtld] Lazy resolve "timerfd_create" in "/bin/system-test" (to 000000000E090798 from "/lib64/libc.so")
[2025-04-21T18:15:44.638141148:trace ][12] sys_timerfd_create(clock_id: CLOCK_REALTIME, flags: 0000000000000800)
[2025-04-21T18:15:44.642989930:trace ][12][rtld] Lazy resolve "timerfd_gettime" in "/bin/system-test" (to 000000000E0908B4 from "/lib64/libc.so")
[2025-04-21T18:15:44.643183815:trace ][12] sys_timerfd_gettime(timerfd: 6, otmr: 0x7fffff50)
[2025-04-21T18:15:44.643327855:trace ][12] sys_read(fd: 6, buf: 0x7ffffdf8, bufsize: 7)
[2025-04-21T18:15:44.645267985:trace ][12][except] Translate exception 0x2:0x6,E_INVALID_ARGUMENT_BAD_VALUE[0xc0a,0x7] into errno=-EINVAL
[2025-04-21T18:15:44.645505197:trace ][12] sys_read(fd: 6, buf: 0x7ffffdf8, bufsize: 8)
[2025-04-21T18:15:44.645638501:trace ][12][except] Translate exception 0x5:0x0,E_WOULDBLOCK into errno=-EAGAIN
[2025-04-21T18:15:44.645775511:trace ][12][rtld] Lazy resolve "timerfd_settime" in "/bin/system-test" (to 000000000E09080F from "/lib64/libc.so")
[2025-04-21T18:15:44.645920062:trace ][12] sys_timerfd_settime(timerfd: 6, flags: 0000000000000000, utmr: 000000007FFFFF50, otmr: NULL)
[2025-04-21T18:15:44.646106279:trace ][12] sys_fcntl(fd: 6, command: F_GETFL, arg: (void)0)
[2025-04-21T18:15:44.646213255:trace ][12] sys_fcntl(fd: 6, command: F_SETFL, arg: 0)
[2025-04-21T18:15:44.646294157:trace ][12] sys_read(fd: 6, buf: 0x7ffffdf8, bufsize: 8)
[2025-04-21T18:15:44.657898941:trace ][12] sys_fcntl(fd: 6, command: F_GETFL, arg: (void)0)
[2025-04-21T18:15:44.658033140:trace ][12] sys_fcntl(fd: 6, command: F_SETFL, arg: O_NONBLOCK)
[2025-04-21T18:15:44.658120609:trace ][12] sys_read(fd: 6, buf: 0x7ffffdf8, bufsize: 8)
[2025-04-21T18:15:44.658326200:trace ][12][except] Translate exception 0x5:0x0,E_WOULDBLOCK into errno=-EAGAIN
[2025-04-21T18:15:44.658453110:trace ][12] sys_ioctl(fd: 6, command: _IOW('T',0x0,uint64_t), arg: {e9 03 00 00 00 00 00 00})
[2025-04-21T18:15:44.658598791:trace ][12] sys_read(fd: 6, buf: 0x7ffffdf8, bufsize: 8)
[2025-04-21T18:15:44.658690154:trace ][12] sys_read(fd: 6, buf: 0x7ffffdf8, bufsize: 8)
[2025-04-21T18:15:44.658951662:trace ][12][except] Translate exception 0x5:0x0,E_WOULDBLOCK into errno=-EAGAIN
[2025-04-21T18:15:44.659082865:trace ][12] sys_epoll_create1(flags: 0)
[2025-04-21T18:15:44.664579620:trace ][12] sys_epoll_ctl(epfd: 7, op: EPOLL_CTL_RPC_PROG, fd: 6, info: {events:EPOLLIN,data:{0x7ffffcc0}})
[2025-04-21T18:15:44.676004126:trace ][12] sys_timerfd_settime(timerfd: 6, flags: 0000000000000000, utmr: 000000007FFFFF50, otmr: NULL)
[2025-04-21T18:15:44.677552140:trace ][12] timerfd: in myrpc
[2025-04-21T18:15:44.678162105:trace ][12][rtld] Lazy resolve "futex_wakeall" in "/bin/system-test" (to 000000000E01521A from "/lib64/libc.so")
[2025-04-21T18:15:44.678349424:trace ][12] sys_lfutex(uaddr: 0x6b8258, futex_op: 0000000000000000, val: 18446744073709551615, timeout: NULL, val2: 0)
[2025-04-21T18:15:44.678527058:trace ][12] sys_Xksigreturn()
[2025-04-21T18:15:44.679673966:trace ][12][rtld] Lazy resolve "__afailf" in "/bin/system-test" (to 000000000E0A6CDD from "/lib64/libc.so")
[2025-04-21T18:15:44.680969366:trace ][12] sys_ioctl(fd: STDERR_FILENO, command: TCGETA, arg: 0x7fffed28)
[2025-04-21T18:15:44.681446451:trace ][12] sys_write(fd: STDERR_FILENO, buf: "Assertion Failure [pc=", bufsize: 22)
[2025-04-21T18:15:44.681716246:trace ][12] sys_write(fd: STDERR_FILENO, buf: "0000000000", bufsize: 10)
[2025-04-21T18:15:44.681864324:trace ][12] sys_write(fd: STDERR_FILENO, buf: "43B044", bufsize: 6)
[2025-04-21T18:15:44.681968568:trace ][12] sys_write(fd: STDERR_FILENO, buf: "]\n", bufsize: 2)
[2025-04-21T18:15:44.681626381:error ][12] Assertion Failure [pc=000000000043B044]
[2025-04-21T18:15:44.683991121:trace ][12] sys_write(fd: STDERR_FILENO, buf: "kos/src/apps/system-test/test-timerfd.c", bufsize: 39)
[2025-04-21T18:15:44.684192930:trace ][12] sys_write(fd: STDERR_FILENO, buf: "(", bufsize: 1)
[2025-04-21T18:15:44.684274983:trace ][12] sys_write(fd: STDERR_FILENO, buf: "120", bufsize: 3)
[2025-04-21T18:15:44.684465290:trace ][12] sys_write(fd: STDERR_FILENO, buf: ") : ", bufsize: 4)
[2025-04-21T18:15:44.684542997:trace ][12] sys_write(fd: STDERR_FILENO, buf: "test_timerfd", bufsize: 12)
[2025-04-21T18:15:44.684635147:trace ][12] sys_write(fd: STDERR_FILENO, buf: " : ", bufsize: 3)
[2025-04-21T18:15:44.685029679:trace ][12] sys_write(fd: STDERR_FILENO, buf: "0 == timerfd_settime(tfd, 0, &its, NULL)", bufsize: 40)
[2025-04-21T18:15:44.685262929:trace ][12] sys_write(fd: STDERR_FILENO, buf: "\n", bufsize: 1)
[2025-04-21T18:15:44.684189607:error ][12] kos/src/apps/system-test/test-timerfd.c(120) : test_timerfd : 0 == timerfd_settime(tfd, 0, &its, NULL)
[2025-04-21T18:15:44.685274624:trace ][12] sys_write(fd: STDERR_FILENO, buf: "0 == 268444224\n", bufsize: 15)
[2025-04-21T18:15:44.688987373:error ][12] 0 == 268444224
[2025-04-21T18:15:44.689219090:trace ][12] sys_coredump(curr_state: 000000007FFFF2C8, orig_state: 0000000000000000, traceback_vector: 0000000000000000, traceback_length: 0, reason: 000000007FFFF3D8, unwind_error: 0000000000000045)
[2025-04-21T18:15:44.691729628:error ][12][coredump] Creating coredump...
assert.expr: "0 == timerfd_settime(tfd, 0, &its, NULL)"
assert.file: "kos/src/apps/system-test/test-timerfd.c"
assert.line: 120
assert.func: "test_timerfd"
assert.mesg: "0 == 268444224"	*/
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
/*FIXME:
[2025-04-21T18:16:28.428882190:trace ][18][test:timerfd] kos/src/apps/system-test/test-timerfd.c:62
[2025-04-21T18:16:28.429009871:trace ][18] sys_write(fd: STDOUT_FILENO, buf: "test:timerfd\e[K\n", bufsize: 16)
[2025-04-21T18:16:28.429391770:trace ][18][rtld] Lazy resolve "timerfd_create" in "/bin/system-test" (to 000000000E090798 from "/lib64/libc.so")
[2025-04-21T18:16:28.429577007:trace ][18] sys_timerfd_create(clock_id: CLOCK_REALTIME, flags: 0000000000000800)
[2025-04-21T18:16:28.431203386:trace ][18][rtld] Lazy resolve "timerfd_gettime" in "/bin/system-test" (to 000000000E0908B4 from "/lib64/libc.so")
[2025-04-21T18:16:28.431374292:trace ][18] sys_timerfd_gettime(timerfd: 6, otmr: 0x7fffff50)
[2025-04-21T18:16:28.431679575:trace ][18] sys_read(fd: 6, buf: 0x7ffffdf8, bufsize: 7)
[2025-04-21T18:16:28.431877031:trace ][18][except] Translate exception 0x2:0x6,E_INVALID_ARGUMENT_BAD_VALUE[0xc0a,0x7] into errno=-EINVAL
[2025-04-21T18:16:28.432075541:trace ][18] sys_read(fd: 6, buf: 0x7ffffdf8, bufsize: 8)
[2025-04-21T18:16:28.432206863:trace ][18][except] Translate exception 0x5:0x0,E_WOULDBLOCK into errno=-EAGAIN
[2025-04-21T18:16:28.432337715:trace ][18][rtld] Lazy resolve "timerfd_settime" in "/bin/system-test" (to 000000000E09080F from "/lib64/libc.so")
[2025-04-21T18:16:28.432498168:trace ][18] sys_timerfd_settime(timerfd: 6, flags: 0000000000000000, utmr: 000000007FFFFF50, otmr: NULL)
[2025-04-21T18:16:28.432803686:trace ][18] sys_fcntl(fd: 6, command: F_GETFL, arg: (void)0)
[2025-04-21T18:16:28.432915745:trace ][18] sys_fcntl(fd: 6, command: F_SETFL, arg: 0)
[2025-04-21T18:16:28.433027216:trace ][18] sys_read(fd: 6, buf: 0x7ffffdf8, bufsize: 8)
[2025-04-21T18:16:28.443368356:trace ][18] sys_fcntl(fd: 6, command: F_GETFL, arg: (void)0)
[2025-04-21T18:16:28.443562168:trace ][18] sys_fcntl(fd: 6, command: F_SETFL, arg: O_NONBLOCK)
[2025-04-21T18:16:28.443712519:trace ][18] sys_read(fd: 6, buf: 0x7ffffdf8, bufsize: 8)
[2025-04-21T18:16:28.444126336:trace ][18][except] Translate exception 0x5:0x0,E_WOULDBLOCK into errno=-EAGAIN
[2025-04-21T18:16:28.444332012:trace ][18] sys_ioctl(fd: 6, command: _IOW('T',0x0,uint64_t), arg: {e9 03 00 00 00 00 00 00})
[2025-04-21T18:16:28.444539449:trace ][18] sys_read(fd: 6, buf: 0x7ffffdf8, bufsize: 8)
[2025-04-21T18:16:28.444793401:trace ][18] sys_read(fd: 6, buf: 0x7ffffdf8, bufsize: 8)
[2025-04-21T18:16:28.444933298:trace ][18][except] Translate exception 0x5:0x0,E_WOULDBLOCK into errno=-EAGAIN
[2025-04-21T18:16:28.445107377:trace ][18] sys_epoll_create1(flags: 0)
[2025-04-21T18:16:28.449856236:trace ][18] sys_epoll_ctl(epfd: 7, op: EPOLL_CTL_RPC_PROG, fd: 6, info: {events:EPOLLIN,data:{0x7ffffcc0}})
[2025-04-21T18:16:28.462366692:trace ][18] sys_timerfd_settime(timerfd: 6, flags: 0000000000000000, utmr: 000000007FFFFF50, otmr: NULL)
[2025-04-21T18:16:28.464063446:trace ][18] timerfd: in myrpc
[2025-04-21T18:16:28.464762803:trace ][18][rtld] Lazy resolve "futex_wakeall" in "/bin/system-test" (to 000000000E01521A from "/lib64/libc.so")
[2025-04-21T18:16:28.464962371:trace ][18] sys_lfutex(uaddr: 0x6b8258, futex_op: 0000000000000000, val: 18446744073709551615, timeout: NULL, val2: 0)
[2025-04-21T18:16:28.465447018:trace ][18] sys_Xksigreturn()
[2025-04-21T18:16:28.465697094:trace ][18][rtld] Lazy resolve "futex_waitwhile" in "/bin/system-test" (to 000000000E0152CC from "/lib64/libc.so")
[2025-04-21T18:16:28.465971014:trace ][18][rtld] Lazy resolve "poll" in "/bin/system-test" (to 000000000E034F87 from "/lib64/libc.so")
[2025-04-21T18:16:28.466165061:trace ][18] sys_ppoll(fds: [{fd:6,events:POLLIN}], nfds: 1, timeout_ts: {tv_sec:0,tv_nsec:0}, sigmask: NULL, sigsetsize: 128)
[2025-04-21T18:16:28.466466468:trace ][18][rtld] Lazy resolve "__afailf" in "/bin/system-test" (to 000000000E0A6CDD from "/lib64/libc.so")
[2025-04-21T18:16:28.467887990:trace ][18] sys_ioctl(fd: STDERR_FILENO, command: TCGETA, arg: 0x7fffed28)
[2025-04-21T18:16:28.468180587:trace ][18] sys_write(fd: STDERR_FILENO, buf: "Assertion Failure [pc=", bufsize: 22)
[2025-04-21T18:16:28.468413278:trace ][18] sys_write(fd: STDERR_FILENO, buf: "0000000000", bufsize: 10)
[2025-04-21T18:16:28.468505016:trace ][18] sys_write(fd: STDERR_FILENO, buf: "43B1C7", bufsize: 6)
[2025-04-21T18:16:28.468655484:trace ][18] sys_write(fd: STDERR_FILENO, buf: "]\n", bufsize: 2)
[2025-04-21T18:16:28.468340804:error ][18] Assertion Failure [pc=000000000043B1C7]
[2025-04-21T18:16:28.470649631:trace ][18] sys_write(fd: STDERR_FILENO, buf: "kos/src/apps/system-test/test-timerfd.c", bufsize: 39)
[2025-04-21T18:16:28.470789763:trace ][18] sys_write(fd: STDERR_FILENO, buf: "(", bufsize: 1)
[2025-04-21T18:16:28.470923551:trace ][18] sys_write(fd: STDERR_FILENO, buf: "132", bufsize: 3)
[2025-04-21T18:16:28.471007302:trace ][18] sys_write(fd: STDERR_FILENO, buf: ") : ", bufsize: 4)
[2025-04-21T18:16:28.471093401:trace ][18] sys_write(fd: STDERR_FILENO, buf: "test_timerfd", bufsize: 12)
[2025-04-21T18:16:28.471283572:trace ][18] sys_write(fd: STDERR_FILENO, buf: " : ", bufsize: 3)
[2025-04-21T18:16:28.471710169:trace ][18] sys_write(fd: STDERR_FILENO, buf: "1 == poll(pfd, 1, 0)", bufsize: 20)
[2025-04-21T18:16:28.471873088:trace ][18] sys_write(fd: STDERR_FILENO, buf: "\n", bufsize: 1)
[2025-04-21T18:16:28.470787061:error ][18] kos/src/apps/system-test/test-timerfd.c(132) : test_timerfd : 1 == poll(pfd, 1, 0)
[2025-04-21T18:16:28.472053432:trace ][18] sys_write(fd: STDERR_FILENO, buf: "1 == 0\n", bufsize: 7)
[2025-04-21T18:16:28.472165883:error ][18] 1 == 0
[2025-04-21T18:16:28.472369092:trace ][18] sys_coredump(curr_state: 000000007FFFF2C8, orig_state: 0000000000000000, traceback_vector: 0000000000000000, traceback_length: 0, reason: 000000007FFFF3D8, unwind_error: 0000000000000045)
[2025-04-21T18:16:28.473282279:error ][18][coredump] Creating coredump...
assert.expr: "1 == poll(pfd, 1, 0)"
assert.file: "kos/src/apps/system-test/test-timerfd.c"
assert.line: 132
assert.func: "test_timerfd"
assert.mesg: "1 == 0"*/
		EQ(1, poll(pfd, 1, 0));
		EQ(POLLIN, pfd[0].revents);
		EQ(1, poll(pfd, 1, 0));
		EQ(POLLIN, pfd[0].revents);
	}

	/* Scheduling an RPC while the timer is already ready must immediately invoke the RPC */
	EQ(1, myrpc_called);
	ee.events   = EPOLLIN;
	ee.data.ptr = (void *)0x1234;
	EQ(0, epoll_rpc_exec(epfd, tfd, &ee, gettid(),
	                     RPC_SYNCMODE_ASYNC | RPC_SYSRESTART_RESTART | RPC_DOMAIN_THREAD,
	                     &myrpc));
	EQ(2, myrpc_called);

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
