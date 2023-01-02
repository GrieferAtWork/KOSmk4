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
#ifndef GUARD_APPS_SYSTEM_TEST_TEST_RPC_C
#define GUARD_APPS_SYSTEM_TEST_TEST_RPC_C 1
#define _KOS_SOURCE 1
#undef NDEBUG

#include <hybrid/compiler.h>

#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>
#include <kos/rpc.h>
#include <system-test/ctest.h>

#include <assert.h>
#include <errno.h>
#include <inttypes.h>
#include <syscall.h>
#include <threads.h>
#include <unistd.h>

DECL_BEGIN

PRIVATE int rpc_function_called = 0;

PRIVATE void
my_rpc_function(struct rpc_context *__restrict ctx,
                void *cookie) {
	EQ((void *)123, cookie);
	/* This is the context expected from `rpc_serve()' */
	EQ(RPC_REASONCTX_SYSINT, ctx->rc_context);
	EQ(SYS_rpc_serve, ctx->rc_scinfo.rsi_sysno);
	ISbitoff(RPC_SYSCALL_INFO_FEXCEPT, ctx->rc_scinfo.rsi_flags);
	EQ(-EINTR, ucpustate_getreturn(ctx->rc_state));
	++rpc_function_called;
}

PRIVATE void
my_rpc_function2(struct rpc_context *__restrict ctx,
                 void *cookie) {
	EQ((void *)123, cookie);

	/* Special case: kernel says that the system call was "interrupted",
	 *               when it actuality wasn't (returns is -EOK). This is
	 *               intended and a consequence of the special case that
	 *               is  trying to send  an RPC to  one's own thread (or
	 *               process)  while  that RPC  isn't masked,  and while
	 *               also passing the `RPC_JOIN_WAITFOR' flag. */
	EQ(RPC_REASONCTX_SYSINT, ctx->rc_context);
	EQ(SYS_rpc_schedule, ctx->rc_scinfo.rsi_sysno);
	ISbiton(RPC_SYSCALL_INFO_FEXCEPT, ctx->rc_scinfo.rsi_flags);
	EQ(-EOK, ucpustate_getreturn(ctx->rc_state));
	++rpc_function_called;
}

DEFINE_TEST(rpc) {
	rpc_function_called = 0;
	EQ(rpc_serve(), 0);

	/* Schedule the RPC (for the calling thread)
	 * Do this asynchronously so that the RPC will be pending until our
	 * thread  makes the next call to a system call that is marked as a
	 * cancellation point. */
	RpcExec(gettid(), RPC_SYNCMODE_CP | RPC_DOMAIN_THREAD | RPC_JOIN_ASYNC,
	        &my_rpc_function, (void *)123);

	EQ(0, rpc_function_called);
	errno = 0;
	EQ(-1, rpc_serve()); /* !!! cancellation point !!!    (think: `pthread_testcancel(3)') */
	EQerrno(EINTR);
	EQ(1, rpc_function_called);
	EQ(0, rpc_serve());
	EQ(0, rpc_serve());
	EQ(0, rpc_serve());
	EQ(1, rpc_function_called);

	/* When `RPC_JOIN_WAITFOR' is used, the sending thread is  suspended
	 * until the RPC program completes, at which point (since the target
	 * thread here is ourselves), execution  will have already been  re-
	 * directed to the RPC function above.
	 *
	 * A  special case exists when sending an  RPC to one's own thread. In
	 * this case  use of  `RPC_JOIN_WAITFOR' behaves  as expected,  though
	 * doesn't  result in the system call exiting with E_INTERRUPT (in the
	 * case where the given RPC program was executed in the context of the
	 * calling thread) */
	RpcExec(gettid(), RPC_SYNCMODE_CP | RPC_DOMAIN_THREAD | RPC_JOIN_WAITFOR,
	        &my_rpc_function2, (void *)123);

	EQ(2, rpc_function_called);
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_RPC_C */
