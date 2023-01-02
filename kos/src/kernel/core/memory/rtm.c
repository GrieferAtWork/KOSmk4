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
#ifndef GUARD_KERNEL_SRC_MEMORY_RTM_C
#define GUARD_KERNEL_SRC_MEMORY_RTM_C 1

#include <kernel/compiler.h>

#include <kernel/mman/rtm.h>

#ifdef ARCH_HAVE_RTM
#include <kernel/mman/driver.h>
#include <kernel/syscall.h>
#include <sched/rpc.h>

#include <kos/except.h>
#include <kos/except/reason/illop.h>
#include <kos/rtm.h>

#include <errno.h>
#include <stddef.h>

#ifndef ARCH_RTM_DRIVER_NAME
#error "Arch forgot to `#define ARCH_RTM_DRIVER_NAME'"
#endif /* !ARCH_RTM_DRIVER_NAME */

DECL_BEGIN

/* [0..1] The currently installed RTM driver hooks. */
PUBLIC struct mrtm_driver_hooks_awref mrtm_hooks = AWREF_INIT(NULL);

#ifdef __ARCH_WANT_SYSCALL_RTM_BEGIN
INTERN struct icpustate *FCALL
sys_rtm_begin_impl(struct icpustate *__restrict state) {
	REF struct mrtm_driver_hooks *hooks;
	/* Lookup RTM hooks. */
	hooks = awref_get(&mrtm_hooks);
	if unlikely(!hooks) {
		REF struct driver *rtm_driver;
		/* Lazily load the RTM driver. */
		TRY {
			rtm_driver = driver_insmod(ARCH_RTM_DRIVER_NAME);
		} EXCEPT {
			goto throw_illegal_op;
		}
		/* Check if hooks have become available now. */
		{
			FINALLY_DECREF_UNLIKELY(rtm_driver);
			hooks = awref_get(&mrtm_hooks);
		}
		if unlikely(!hooks)
			goto throw_illegal_op;
	}
	{
		FINALLY_DECREF_UNLIKELY(hooks);
		/* Perform an RTM operation for user-space. */
		state = mrtm_exec(&hooks->rdh_hooks, state);
		return state;
	}
throw_illegal_op:
	mrtm_setnosys(state);
	return state;
}


PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
syscall_rtm_begin_rpc(struct rpc_context *__restrict ctx,
                      void *UNUSED(cookie)) {
	REF struct mrtm_driver_hooks *hooks;
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;
	/* Lookup RTM hooks. */
	hooks = awref_get(&mrtm_hooks);
	if unlikely(!hooks) {
		REF struct driver *rtm_driver;
		/* Lazily load the RTM driver. */
		TRY {
			rtm_driver = driver_insmod(ARCH_RTM_DRIVER_NAME);
		} EXCEPT {
			goto throw_illegal_op;
		}
		/* Check if hooks have become available now. */
		{
			FINALLY_DECREF_UNLIKELY(rtm_driver);
			hooks = awref_get(&mrtm_hooks);
		}
		if unlikely(!hooks) {
throw_illegal_op:
			mrtm_setnosys(ctx->rc_state);
			return;
		}
	}
	{
		/* Perform an RTM operation for user-space. */
		FINALLY_DECREF_UNLIKELY(hooks);
		ctx->rc_state = mrtm_exec(&hooks->rdh_hooks, ctx->rc_state);
	}

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL0(rtm_status_t, rtm_begin) {
	/* Send an RPC to ourself, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&syscall_rtm_begin_rpc, NULL);
	__builtin_unreachable();
}
#endif /* __ARCH_WANT_SYSCALL_RTM_BEGIN */

#ifdef __ARCH_WANT_SYSCALL_RTM_END
DEFINE_SYSCALL0(errno_t, rtm_end) {
	/* This system call is an illegal operation outside of RTM mode. */
	THROW(E_ILLEGAL_OPERATION, E_ILLEGAL_OPERATION_CONTEXT_NOT_RTM);
}
#endif /* __ARCH_WANT_SYSCALL_RTM_END */

#ifdef __ARCH_WANT_SYSCALL_RTM_ABORT
DEFINE_SYSCALL1(errno_t, rtm_abort, syscall_ulong_t, code) {
	/* This system call is a no-op outside of RTM mode. */
	COMPILER_IMPURE();
	(void)code;
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_RTM_ABORT */

#ifdef __ARCH_WANT_SYSCALL_RTM_TEST
DEFINE_SYSCALL0(syscall_ulong_t, rtm_test) {
	/* No RTM operation in progress */
	COMPILER_IMPURE();
	return 0;
}
#endif /* __ARCH_WANT_SYSCALL_RTM_TEST */

DECL_END
#endif /* ARCH_HAVE_RTM */

#endif /* !GUARD_KERNEL_SRC_MEMORY_RTM_C */
