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
#ifdef __INTELLISENSE__
#define _KOS_SOURCE 1
//#define DEFINE_sys_rpc_schedule
#define DEFINE_compat_sys_rpc_schedule
#endif /* __INTELLISENSE__ */

#include <kernel/compiler.h>

#include <kernel/except.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/rt/except-handler.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/pid.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/signal.h>

#include <hybrid/atomic.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/rpc.h>

#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>

#ifdef DEFINE_compat_sys_rpc_schedule
#include <compat/config.h>
#endif /* DEFINE_compat_sys_rpc_schedule */

DECL_BEGIN

#if (defined(DEFINE_sys_rpc_schedule) + \
     defined(DEFINE_compat_sys_rpc_schedule)) != 1
#error "Must #define exactly one of these"
#endif /* ... */


#ifdef DEFINE_compat_sys_rpc_schedule
DEFINE_COMPAT_SYSCALL5(errno_t, rpc_schedule,
                       pid_t, target_tid, syscall_ulong_t, mode,
                       USER UNCHECKED void const *, program,
                       __ARCH_COMPAT_PTR(USER UNCHECKED void const) USER UNCHECKED const *, params,
                       size_t, max_param_count)
#else /* DEFINE_compat_sys_rpc_schedule */
DEFINE_SYSCALL5(errno_t, rpc_schedule,
                pid_t, target_tid, syscall_ulong_t, mode,
                USER UNCHECKED void const *, program,
                USER UNCHECKED void const *USER UNCHECKED const *, params,
                size_t, max_param_count)
#endif /* !DEFINE_compat_sys_rpc_schedule */
{
	REF struct task *target;
	REF struct pending_rpc *rpc;
	VALIDATE_FLAGSET(mode,
	                 RPC_SIGNO_MASK | RPC_SYNCMODE_F_ALLOW_ASYNC |
	                 RPC_SYNCMODE_F_REQUIRE_SC | RPC_SYNCMODE_F_REQUIRE_CP |
	                 RPC_SYSRESTART_F_AUTO | RPC_SYSRESTART_F_DONT |
	                 RPC_PRIORITY_F_HIGH | RPC_DOMAIN_F_PROC |
	                 RPC_JOIN_F_ASYNC,
	                 E_INVALID_ARGUMENT_CONTEXT_RPC_SCHEDULE_MODE);
	if unlikely(max_param_count > RPC_PARAMS_MAX) {
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_RPC_SCHEDULE_TOO_MANY_PARAMS,
		      max_param_count);
	}

	/* Set the default signal number `SIGRPC' if none was specified. */
	if ((mode & RPC_SIGNO_MASK) == 0)
		mode |= RPC_SIGNO(SIGRPC);
	validate_readable(program, 1);
	validate_readablem(params, max_param_count, sizeof(USER UNCHECKED void const *));

	/* If  we intend to wait for the RPC program to complete, then we also
	 * check  for RPCs pending  within our own thread  before we'll end up
	 * doing the wait. This way, no RPC is ever scheduled on one side more
	 * than once in a  scenario where 2 threads  are sending RPCs to  each
	 * other. */
	if (!(mode & RPC_JOIN_F_ASYNC))
		task_serve();

	/* Allocate the new RPC controller. */
	rpc = (struct pending_rpc *)pending_rpc_alloc(offsetof(struct pending_rpc, pr_user.pur_argv) +
	                                              max_param_count * sizeof(USER UNCHECKED void *),
	                                              GFP_NORMAL);

	/* Copy arguments. */
	TRY {
#ifdef DEFINE_compat_sys_rpc_schedule
		size_t i;
		for (i = 0; i < max_param_count; ++i)
			rpc->pr_user.pur_argv[i] = params[i];
#else /* DEFINE_compat_sys_rpc_schedule */
		memcpy(rpc->pr_user.pur_argv, params,
		       max_param_count, sizeof(USER UNCHECKED void *));
#endif /* !DEFINE_compat_sys_rpc_schedule */
	} EXCEPT {
		pending_rpc_free(rpc);
		RETHROW();
	}

	/* Fill in RPC information. */
	rpc->pr_flags = mode & (RPC_SIGNO_MASK |
	                        RPC_SYNCMODE_F_ALLOW_ASYNC |
	                        RPC_SYNCMODE_F_REQUIRE_SC |
	                        RPC_SYNCMODE_F_REQUIRE_CP |
	                        RPC_SYSRESTART_F_AUTO |
	                        RPC_SYSRESTART_F_DONT |
	                        RPC_PRIORITY_F_HIGH);
	rpc->pr_user.pur_refcnt = 1;
	rpc->pr_user.pur_status = PENDING_USER_RPC_STATUS_PENDING;
	sig_init(&rpc->pr_user.pur_stchng);
	rpc->pr_user.pur_mman = incref(THIS_MMAN);
	rpc->pr_user.pur_prog = program;
	rpc->pr_user.pur_argc = max_param_count;
	FINALLY_DECREF(&rpc->pr_user);

	/* Lookup the target thread. */
	target = pidns_lookup_task(THIS_PIDNS, (upid_t)target_tid);

	/* Schedule the RPC */
	rpc->pr_user.pur_refcnt = 2; /* +1 for the target component's list. */
	COMPILER_WRITE_BARRIER();
	if (mode & RPC_DOMAIN_F_PROC) {
		if (!task_rpc_schedule(target, rpc)) {
			rpc->pr_user.pur_refcnt = 1;
			THROW(E_PROCESS_EXITED, (upid_t)target_tid);
		}
	} else {
		if (!proc_rpc_schedule(target, rpc)) {
			rpc->pr_user.pur_refcnt = 1;
			THROW(E_PROCESS_EXITED, (upid_t)target_tid);
		}
	}

	/* (possibly) wait for completion */
	if (!(mode & RPC_JOIN_F_ASYNC)) {
		unsigned int status;
		for (;;) {
			status = ATOMIC_READ(rpc->pr_user.pur_status);
			if (status != PENDING_USER_RPC_STATUS_PENDING)
				break;
			task_connect(&rpc->pr_user.pur_stchng);
			status = ATOMIC_READ(rpc->pr_user.pur_status);
			if (status != PENDING_USER_RPC_STATUS_PENDING) {
				task_disconnectall();
				break;
			}
			TRY {
				task_waitfor();
			} EXCEPT {
				error_code_t code;
				/* Must  cancel the RPC  if we get  here, and, if that
				 * cancel can't be performed because the RPC finished,
				 * then we must discard the exception (unless it's  an
				 * RT-level error) */
				status = ATOMIC_XCH(rpc->pr_user.pur_status, PENDING_USER_RPC_STATUS_CANCELED);
				assert(status == PENDING_USER_RPC_STATUS_PENDING ||
				       status == PENDING_USER_RPC_STATUS_COMPLETE ||
				       status == PENDING_USER_RPC_STATUS_CANCELED);
				if (status != PENDING_USER_RPC_STATUS_COMPLETE)
					RETHROW();

				/* Ooop... The RPC completed before we could cancel it.
				 * Well: now we have to get rid of the current exception,
				 *       as  user-space mustn't be told about ?something?
				 *       having gone wrong.
				 * A special case here are  RT exception which are  too
				 * important to dismiss (as they include stuff like our
				 * own thread being supposed to terminate) */
				code = error_class();
				if (ERRORCLASS_ISRTLPRIORITY(ERROR_CLASS(code)))
					RETHROW(); /* Sorry. Can't discard this one... */

				/* If it was  just an `E_INTERRUPT_USER_RPC',  then we  can
				 * discard it by redirecting our sysret path (so that async
				 * RPCs/posix signals can  be handled  that way).  However,
				 * synchronous RPCs can't be handled anymore since we can't
				 * restart the system call anymore (as it succeeded) */
				if (code == ERROR_CODEOF(E_INTERRUPT_USER_RPC)) {
					userexcept_sysret_inject_self();
				} else {
					/* Everything else is just dumped to the system log.
					 * But  note that there really shouldn't be anything
					 * that gets here... */
					error_printf("Canceling user RPC");
				}
				break;
			}
		}
		if (status != PENDING_USER_RPC_STATUS_COMPLETE) {
			assert(status == PENDING_USER_RPC_STATUS_CANCELED);
			/* The RPC was canceled, but it wasn't us. This can only mean that
			 * the  target thread/process exited and will no longer be able to
			 * service _any_ rpcs at all! */
			THROW(E_PROCESS_EXITED, (upid_t)target_tid);
		}
	}

	return 0;
}

DECL_END

#undef DEFINE_compat_sys_rpc_schedule
#undef DEFINE_sys_rpc_schedule
