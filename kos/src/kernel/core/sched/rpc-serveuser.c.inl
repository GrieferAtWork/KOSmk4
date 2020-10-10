/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "rpc.c"
#define RPC_SERVE_ALL 1
#endif /* __INTELLISENSE__ */

DECL_BEGIN

/* Serve RPC functions as the result of user-space being re-directed asynchronously.
 * This function is called from an arch-specific assembly function that is used to
 * redirect where a system call or interrupt would return to, if the previous return
 * location was somewhere in user-space.
 * On x86, that is `x86_rpc_user_redirection()', found in `/arch/i386/sched32.S' */
#ifdef RPC_SERVE_ALL
INTERN WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL rpc_serve_user_redirection_all)(struct icpustate *__restrict state,
                                              unsigned int reason,
                                              struct rpc_syscall_info const *sc_info,
                                              bool *prestart_system_call)
#else /* RPC_SERVE_ALL */
INTERN WUNUSED NONNULL((1)) struct icpustate *
NOTHROW(FCALL rpc_serve_async_user_redirection)(struct icpustate *__restrict state)
#endif /* !RPC_SERVE_ALL */
{
	struct rpc_entry *chain;
	struct exception_info last_error;
	struct exception_info *tls_error;
#ifndef RPC_SERVE_ALL
	struct icpustate *new_state;
#endif /* !RPC_SERVE_ALL */
	bool consume_rpc_interrupt = false;
#ifdef RPC_SERVE_ALL
	bool must_restart_syscall;
	must_restart_syscall = reason == TASK_RPC_REASON_SYSCALL;
#endif /* RPC_SERVE_ALL */
	tls_error = error_info();
	memcpy(&last_error, tls_error, sizeof(last_error));
again_capture_chain:
	chain = ATOMIC_XCH(PERTASK(this_rpcs_pending), NULL);
again_chain:
	if (chain) {
		/* Service _all_ pending RPC functions (except for `RPC_KIND_USER_SYNC' without `RPC_KIND_CANSERVE'). */
		if (chain->re_kind & RPC_KIND_USER_SYNC) {
			assertf(chain->re_kind & RPC_KIND_INTERRUPT,
			        "`RPC_KIND_USER_SYNC' cannot be used without `RPC_KIND_INTERRUPT'\n"
			        "An exception `E_INTERRUPT_USER_RPC' is needed to allow for `TASK_RPC_REASON_SYSCALL' "
			        "as reason. - Otherwise, user-level RPCs are serviced as `TASK_RPC_REASON_ASYNCUSER', "
			        "with the associated context pointing to what will be loaded when the system call returns.");
			if (!(chain->re_kind & RPC_KIND_CANSERVE)) {
				/* Can't service this one right now. - Re-schedule it for execution at a later point! */
				struct rpc_entry *more;
				struct rpc_entry *temp, **pchain;
restore_rpc:
				more   = chain->re_next;
				pchain = &PERTASK(this_rpcs_pending);
				do {
					temp = ATOMIC_READ(*pchain);
					chain->re_next = temp;
				} while (!ATOMIC_CMPXCH_WEAK(*pchain, temp, chain));
				chain                 = more;
				consume_rpc_interrupt = true;
				goto again_chain;
			}
			/* Check if the RPC only allows for SYSCALL as reason.
			 * If so, unset its current serviceability status and re-schedule
			 * it as pending (this can happen if we got here during a #PF)
			 * Also: Don't service in the case of a system call that isn't
			 *       a cancellation point. */
#ifdef RPC_SERVE_ALL
			if (!(chain->re_kind & RPC_KIND_NONSYSCALL) &&
			    (reason != TASK_RPC_REASON_SYSCALL ||
			     !kernel_syscall_iscp(sc_info->rsi_sysno)))
#else /* RPC_SERVE_ALL */
			if (!(chain->re_kind & RPC_KIND_NONSYSCALL))
#endif /* !RPC_SERVE_ALL */
			{
				chain->re_kind &= ~RPC_KIND_CANSERVE;
				goto restore_rpc;
			}
		}
#ifdef RPC_SERVE_ALL
		must_restart_syscall = false;
#endif /* RPC_SERVE_ALL */
		if ((chain->re_kind & RPC_KIND_MASK) != RPC_KIND_USER) {
			if (chain->re_kind & RPC_KIND_NOTHROW)
				ATOMIC_DEC(PERTASK(this_rpc_pending_sync_count_nx));
			ATOMIC_DEC(PERTASK(this_rpc_pending_sync_count));
		}
		{
			struct rpc_entry *more, *last;
			/* Restore all additional RPC functions so that the RPC counters remain consistent
			 * when invoking the RPC callbacks (this is required in case one of the callbacks
			 * does something that might block, in which case task_serve() would be called, at
			 * which point it would break if the RPC counters are out-of-sync) */
			more = chain->re_next;
			if (more) {
				last = more;
				while (last->re_next)
					last = last->re_next;
				reinsert_pending_rpcs(more, last);
			}
		}
		TRY {
#ifndef RPC_SERVE_ALL
			new_state = (*chain->re_func)(chain->re_arg,
			                              state,
			                              TASK_RPC_REASON_ASYNCUSER,
			                              NULL);
			if unlikely(new_state != state)
				goto load_new_state;
			assert(new_state != TASK_RPC_RESTART_SYSCALL);
#else /* !RPC_SERVE_ALL */
			struct icpustate *new_state;
			new_state = (*chain->re_func)(chain->re_arg,
			                              state,
			                              reason,
			                              sc_info);
			if (new_state == TASK_RPC_RESTART_SYSCALL) {
				assert(reason == TASK_RPC_REASON_SYSCALL);
				must_restart_syscall = true;
				new_state            = state;
			}
			state = new_state;
#endif /* RPC_SERVE_ALL */
		} EXCEPT {
			assertf(!(chain->re_kind & RPC_KIND_NOTHROW),
			        "Exception thrown by NOTHROW RPC at %p",
			        chain->re_func);
			assert(tls_error->ei_code != E_OK);
			STATIC_ASSERT(ERRORCLASS_ISLOWPRIORITY(ERROR_CLASS(ERROR_CODEOF(E_INTERRUPT_USER_RPC))));
			/* Propagate only the more important exception. */
			if (last_error.ei_code == E_OK ||
			    ERRORCLASS_ISLOWPRIORITY(last_error.ei_class) ||
			    ERRORCLASS_ISHIGHPRIORITY(tls_error->ei_class))
				memcpy(&last_error, tls_error, sizeof(last_error));
		}
		if (chain->re_kind & RPC_KIND_INTERRUPT)
			consume_rpc_interrupt = true;
		rpcentry_free(chain);
		/* Try to capture more RPC chain entires. */
		goto again_capture_chain;
	}
	/* Consume `E_INTERRUPT_USER_RPC' exception */
	if (consume_rpc_interrupt &&
	    last_error.ei_code == ERROR_CODEOF(E_INTERRUPT_USER_RPC)) {
		last_error.ei_code = E_OK;
#ifdef RPC_SERVE_ALL
		if (must_restart_syscall) {
			assert(reason == TASK_RPC_REASON_SYSCALL);
			*prestart_system_call = must_restart_syscall;
		}
#endif /* RPC_SERVE_ALL */
	}

	/* Set the last exception. */
	memcpy(tls_error, &last_error, sizeof(last_error));
	return state;
#ifndef RPC_SERVE_ALL
load_new_state:
	if (chain->re_kind & RPC_KIND_INTERRUPT)
		consume_rpc_interrupt = true;
	if (last_error.ei_code == ERROR_CODEOF(E_INTERRUPT_USER_RPC) && consume_rpc_interrupt)
		last_error.ei_code = E_OK;
	memcpy(tls_error, &last_error, sizeof(last_error));
	rpcentry_free(chain);
	/* Let the caller load the new state, then continue serving pending RPCs. */
	return new_state;
#endif /* !RPC_SERVE_ALL */
}

#undef RPC_SERVE_ALL


DECL_END
