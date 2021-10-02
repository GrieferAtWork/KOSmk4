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
#include <kernel/except.h>
#include <kernel/mman.h>
#include <kernel/rt/except-handler.h>
#include <kernel/rt/except-syscall.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/rpc-internal.h>
#include <sched/rpc.h>
#include <sched/signal.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/host.h>

#include <kos/rpc.h>

#include <assert.h>
#include <errno.h>

#include <libunwind/arch-register.h>

DECL_BEGIN


/* Destroy a "!RPC_CONTEXT_KERN && !RPC_CONTEXT_SIGNAL"-rpc once `self->pr_user.pur_refcnt == 0' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _pending_rpc_destroy_user)(struct pending_rpc *__restrict self) {
	sig_broadcast_for_fini(&self->pr_user.pur_stchng);
	decref(self->pr_user.pur_mman);
	pending_rpc_free(self);
}

/* Mark  the given `rpc' as canceled. This function is guarantied to
 * not be called at the same time as `task_userrpc_runprogram()', as
 * it is only used to  implement handling for `!RPC_CONTEXT_KERN  &&
 * !RPC_CONTEXT_SIGNAL' RPCs left-over during thread/process exit. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL task_userrpc_cancelprogram)(struct pending_rpc *__restrict rpc) {
	assert(!(rpc->pr_flags & RPC_CONTEXT_KERN));
	assert(!(rpc->pr_flags & RPC_CONTEXT_SIGNAL));

	/* Indicate that the program was canceled. */
	ATOMIC_WRITE(rpc->pr_user.pur_status, PENDING_USER_RPC_STATUS_CANCELED);
	sig_broadcast(&rpc->pr_user.pur_stchng);
}


/* Execute a user-space RPC program
 * @param: reason:  One of `_RPC_REASONCTX_ASYNC', `_RPC_REASONCTX_SYNC' or `_RPC_REASONCTX_SYSCALL'
 * @param: sc_info: [valid_if(reason == _RPC_REASONCTX_SYSCALL)] System call information. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) rpc_cpustate_t *FCALL
task_userrpc_runprogram(rpc_cpustate_t *__restrict state,
                        struct pending_rpc *__restrict rpc,
                        unsigned int reason,
                        struct rpc_syscall_info const *sc_info) {
	assert(reason == _RPC_REASONCTX_ASYNC ||
	       reason == _RPC_REASONCTX_SYNC ||
	       reason == _RPC_REASONCTX_SYSCALL);

	/* NOTE: When the system call isn't restarted, we're also responsible
	 *       to write -EINTR to the system call return value, or to  have
	 *       the RPC program return  to the user-space exception  handler
	 *       with an E_INTERRUPT already pushed onto the stack! */

	/* TODO: To  ensure that  RPC programs  with infinite  loops don't cause
	 *       the kernel to hang itself, a call to `task_serve_with_sigmask',
	 *       with a signal mask that is  masking all signals except for  the
	 *       mandatory `SIGKILL' and `SIGSTOP',  is made prior to  executing
	 *       any given instruction. */

	/* TODO: `RPC_JOIN_WAITFOR'  can only really  be implemented by making
	 *       the `pending_user_rpc' reference-counted,  as well as  having
	 *       some should-cancel write-back field (which can be set by  the
	 *       sending process when  the send should  be canceled). To  make
	 *       sure  that modifications  made by  RPC program  can always be
	 *       undone, all such modifications must  first be collected in  a
	 *       way similar to what is  done by modrtm, before being  applied
	 *       all at the same time.  (The point at which modifications  are
	 *       applied is _after_ a call to `rpc_schedule(2)' that was given
	 *       the `RPC_JOIN_WAITFOR' argument stops blocking)
	 *       This way, we can also guaranty that no modifications are made
	 *       in  situations where the program causes some kind of error at
	 *       some point during its execution (at which point prior changes
	 *       can simply be discarded)
	 *
	 * The best way to do this is probably to make `struct pending_user_rpc'
	 * reference-counted (and adjust  all calls  to `pending_rpc_free()'  to
	 * include checks for !RPC_CONTEXT_KERN && !RPC_CONTEXT_SIGNAL RPCs)
	 *
	 * Then, add a status word to `struct pending_user_rpc' that is attached
	 * to a `struct sig', allowing one to  cancel the invocation of the  RPC
	 * by writing some CANCELED state to the status word. If the cancel from
	 * some place other than the original sender thread, this is followed by
	 * broadcasting the  `struct sig' (which  the original  sender may  have
	 * been polling).
	 * Additionally, this status word can  be used to return  information
	 * about program execution errors to the sender (including stuff like
	 * segmentation faults during memory reads/writes)
	 */

	(void)state;
	(void)rpc;
	(void)reason;
	(void)sc_info;
	THROW(E_NOT_IMPLEMENTED_TODO);

	/* TODO */
	return state;
}








/************************************************************************/
/* RPC related system calls                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_RPC_SERVE
DEFINE_SYSCALL0(errno_t, rpc_serve) {
	task_serve();
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_RPC_SERVE */

#ifdef __ARCH_WANT_SYSCALL_RPC_SERVE_SYSRET
DEFINE_SYSCALL0(errno_t, rpc_serve_sysret) {
	userexcept_sysret_inject_self();
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_RPC_SERVE_SYSRET */

DECL_END

#ifndef __INTELLISENSE__
#ifdef __ARCH_WANT_SYSCALL_RPC_SCHEDULE
#define DEFINE_sys_rpc_schedule
#include "rpc-program-schedule.c.inl"
#endif /* __ARCH_WANT_SYSCALL_RPC_SCHEDULE */
#ifdef __ARCH_WANT_COMPAT_SYSCALL_RPC_SCHEDULE
#define DEFINE_compat_sys_rpc_schedule
#include "rpc-program-schedule.c.inl"
#endif /* __ARCH_WANT_COMPAT_SYSCALL_RPC_SCHEDULE */
#endif /* !__INTELLISENSE__ */

#endif /* CONFIG_USE_NEW_RPC */

#endif /* !GUARD_KERNEL_SRC_SCHED_RPC_PROGRAM_C */
