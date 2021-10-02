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
#ifndef GUARD_KERNEL_SRC_SCHED_RPC_PROGRAM_C
#define GUARD_KERNEL_SRC_SCHED_RPC_PROGRAM_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_RPC
#include <sched/rpc-internal.h>
#include <sched/rpc.h>

#include <kos/except.h>
#include <kos/rpc.h>
#include <assert.h>

#include <libunwind/arch-register.h>

DECL_BEGIN

/* Execute a user-space RPC program
 * @param: reason:  One of `_RPC_REASONCTX_ASYNC', `_RPC_REASONCTX_SYNC' or `_RPC_REASONCTX_SYSCALL'
 * @param: sc_info: [valid_if(reason == _RPC_REASONCTX_SYSCALL)] System call information. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) rpc_cpustate_t *FCALL
task_userrpc_runprogram(rpc_cpustate_t *__restrict state,
                        struct pending_user_rpc const *__restrict rpc,
                        unsigned int reason,
                        struct rpc_syscall_info const *sc_info) {
	assert(reason == _RPC_REASONCTX_ASYNC ||
	       reason == _RPC_REASONCTX_SYNC ||
	       reason == _RPC_REASONCTX_SYSCALL);

	/* NOTE: When the system call isn't restarted, we're also responsible
	 *       to write -EINTR to the system call return value, or to have
	 *       the RPC program return to the user-space exception handler
	 *       with an E_INTERRUPT already pushed onto the stack! */

	(void)state;
	(void)rpc;
	(void)reason;
	(void)sc_info;
	THROW(E_NOT_IMPLEMENTED_TODO);

	/* TODO */
	return state;
}

DECL_END

#endif /* CONFIG_USE_NEW_RPC */

#endif /* !GUARD_KERNEL_SRC_SCHED_RPC_PROGRAM_C */
