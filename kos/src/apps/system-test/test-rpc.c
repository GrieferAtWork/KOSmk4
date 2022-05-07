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
	EQp(cookie, (void *)123);
	/* This is the context expected from `rpc_serve()' */
	EQup(ctx->rc_context, RPC_REASONCTX_SYSINT);
	EQup(ctx->rc_scinfo.rsi_sysno, SYS_rpc_serve);
	assert(!(ctx->rc_scinfo.rsi_flags & RPC_SYSCALL_INFO_FEXCEPT));
	EQup(ucpustate_getreturn(ctx->rc_state), -EINTR);
	++rpc_function_called;
}

PRIVATE void
my_rpc_function2(struct rpc_context *__restrict ctx,
                 void *cookie) {
	EQp(cookie, (void *)123);
	/* Special case: kernel says that the system call was "interrupted",
	 *               when it actuality wasn't (returns is -EOK). This is
	 *               intended and a consequence of the special case that
	 *               is  trying to send  an RPC to  one's own thread (or
	 *               process)  while  that RPC  isn't masked,  and while
	 *               also passing the `RPC_JOIN_WAITFOR' flag. */
	EQup(ctx->rc_context, RPC_REASONCTX_SYSINT);
	EQup(ctx->rc_scinfo.rsi_sysno, SYS_rpc_schedule);
	assertf(ctx->rc_scinfo.rsi_flags & RPC_SYSCALL_INFO_FEXCEPT,
	        "ctx->rc_scinfo.rsi_flags = %#" PRIxPTR,
	        ctx->rc_scinfo.rsi_flags);
	EQup(ucpustate_getreturn(ctx->rc_state), -EOK);
	++rpc_function_called;
}

DEFINE_TEST(rpc) {
	rpc_function_called = 0;
	EQd(rpc_serve(), 0);

	/* Schedule the RPC (for the calling thread)
	 * Do this asynchronously so that the RPC will be pending until our
	 * thread  makes the next call to a system call that is marked as a
	 * cancellation point. */
	RpcExec(gettid(), RPC_SYNCMODE_CP | RPC_DOMAIN_THREAD | RPC_JOIN_ASYNC,
	        &my_rpc_function, (void *)123);

	EQd(rpc_function_called, 0);
	errno = 0;
	EQd(rpc_serve(), -1); /* !!! cancellation point !!!    (think: `pthread_testcancel(3)') */
	EQd(errno, EINTR);
	EQd(rpc_function_called, 1);
	EQd(rpc_serve(), 0);
	EQd(rpc_serve(), 0);
	EQd(rpc_serve(), 0);
	EQd(rpc_function_called, 1);

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

	EQd(rpc_function_called, 2);
}


DECL_END

#endif /* !GUARD_APPS_SYSTEM_TEST_TEST_RPC_C */
