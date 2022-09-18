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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_EPOLL_RPC_C
#define GUARD_APPS_SYSTEM_TEST_TEST_EPOLL_RPC_C 1
#define _KOS_SOURCE 1 /* epoll RPCs are a KOS-extension. */
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/rpc.h>
#include <kos/types.h>
#include <sys/epoll.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

DECL_BEGIN

PRIVATE sig_atomic_t myrpc_called = 0;

PRIVATE NONNULL((1)) void
myrpc(struct rpc_context *__restrict ctx, void *cookie) {
	EQup(ctx->rc_context, RPC_REASONCTX_ASYNC);
	EQp(cookie, (void *)0x1234);
	++myrpc_called;
}


DEFINE_TEST(epoll_rpc) {
	fd_t epfd;
	fd_t pipes[2];
	struct epoll_event ee;
	char data[5];
	myrpc_called = 0;

	NEd(-1, (epfd = epoll_create1(EPOLL_CLOEXEC | EPOLL_CLOFORK)));
	EQd(0, pipe(pipes)); /* NOLINT */

	/* Setup a monitor that gets triggered as soon
	 * as  reading from the pipe becomes possible. */
	ee.events   = EPOLLIN;
	ee.data.ptr = (void *)0x1234;
	EQu(0, myrpc_called);
	EQd(0, epoll_rpc_exec(epfd, pipes[0], &ee, gettid(),
	                      RPC_SYNCMODE_ASYNC | RPC_SYSRESTART_RESTART | RPC_DOMAIN_THREAD,
	                      &myrpc));
	EQu(0, myrpc_called);

	/* Write some data to the pipe. */
	EQss(5, write(pipes[1], "Hello", 5));

	/* Because we're using async RPCs, the RPC should have already been invoked!
	 * WARNING: Normally when sending RPCs, there's the possibility that the RPC
	 *          getting send to another thread  brings with it a delivery  delay
	 *          because  the RPC may still be in  transit for a short time after
	 *          it got send.
	 * However, since in this example the call to `write(2)' asserting the EPOLLIN event
	 * simply causes the RPC  to be send back  to the our own  thread (meaning that  the
	 * entire RPC delivery process happens synchronously), no such transit-delay  exists
	 * which allows us to immediately assert that the RPC already finished. */
	COMPILER_READ_BARRIER();
	EQu(1, myrpc_called);

	/* Also  make sure that the in-pipe data is correct (though that's
	 * kind-of a given and not ~really~ related to testing epoll RPCs) */
	EQss(5, read(pipes[0], data, 5));
	EQd(0, bcmp(data, "Hello", 5));

	/* Cleanup */
	EQd(0, close(pipes[0]));
	EQd(0, close(pipes[1]));
	EQd(0, close(epfd));
}

DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_EPOLL_RPC_C */
