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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_CLONE_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_CLONE_C 1

#include <kernel/compiler.h>

#include <kernel/syscall.h>
#include <sched/pid.h>
#include <sched/rpc.h>
#include <sched/task-clone.h>
#include <sched/task.h>

#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <signal.h>
#include <stddef.h>

#ifndef CONFIG_NO_USERKERN_SEGMENT
#include <kernel/rand.h>
#include <sched/userkern.h>

#include <kos/kernel/paging.h>
#include <kos/ukern.h>
#endif /* !CONFIG_NO_USERKERN_SEGMENT */

DECL_BEGIN

#ifndef CONFIG_NO_USERKERN_SEGMENT
PUBLIC NOBLOCK uintptr_t
NOTHROW(KCALL x86_get_random_userkern_address)(void) {
	uintptr_t offset;
	/* Assign a random (pointer-aligned) offset into kernel-
	 * space as the base  address for the userkern  segment. */
	offset = (uintptr_t)(krand() * USERKERN_SEGMENT_ALIGN);
	offset %= ((uintptr_t)0 - KERNELSPACE_BASE) - (USERKERN_SYSCALL_MAXVALID + 1);
	offset += KERNELSPACE_BASE;
	return offset;
}

#ifdef __x86_64__
PUBLIC NOBLOCK u32
NOTHROW(KCALL x86_get_random_userkern_address32)(void) {
	u32 offset;
	/* Assign a random (pointer-aligned) offset into (compatibility-mode)
	 * kernel-space  as  the  base  address  for  the  userkern  segment. */
	offset = (u32)(krand32() * USERKERN_SEGMENT_ALIGN);
	offset %= ((u32)0 - COMPAT_KERNELSPACE_BASE) - (USERKERN_SYSCALL_MAXVALID + 1);
	offset += COMPAT_KERNELSPACE_BASE;
	return offset;
}
#endif /* __x86_64__ */
#endif /* !CONFIG_NO_USERKERN_SEGMENT */



/************************************************************************/
/* clone()                                                              */
/************************************************************************/
#if defined(__ARCH_WANT_SYSCALL_CLONE) && defined(__x86_64__)
PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_clone64_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	pid_t child_tid;
	REF struct task *child_tsk;
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;
	child_tsk = sys_clone_impl(ctx->rc_state,
	                           ctx->rc_scinfo.rsi_regs[0],                         /* clone_flags */
	                           (USER UNCHECKED pid_t *)ctx->rc_scinfo.rsi_regs[2], /* parent_tidptr */
	                           (USER UNCHECKED pid_t *)ctx->rc_scinfo.rsi_regs[3], /* child_tidptr */
	                           (USER UNCHECKED void *)ctx->rc_scinfo.rsi_regs[1],  /* child_stack */
	                           x86_get_user_gsbase(),
	                           ctx->rc_scinfo.rsi_regs[0] & CLONE_SETTLS ? ctx->rc_scinfo.rsi_regs[4]
	                                                                     : x86_get_user_fsbase());
	child_tid = task_gettid_of(child_tsk);
	decref(child_tsk);
	icpustate_setreturn(ctx->rc_state, child_tid);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL64_5(pid_t, clone,
                   syscall_ulong_t, flags,
                   USER UNCHECKED void *, child_stack,
                   USER UNCHECKED pid_t *, ptid,
                   USER UNCHECKED pid_t *, ctid,
                   uintptr_t, newtls) {
	(void)flags;
	(void)child_stack;
	(void)ptid;
	(void)ctid;
	(void)newtls;

	/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&sys_clone64_rpc, NULL);
	__builtin_unreachable();
}
#endif /* __ARCH_WANT_SYSCALL_CLONE && __x86_64__ */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_CLONE) || \
     (defined(__ARCH_WANT_SYSCALL_CLONE) && !defined(__x86_64__)))
PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_clone32_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	pid_t child_tid;
	REF struct task *child_tsk;
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;
	child_tsk = sys_clone_impl(ctx->rc_state,
	                           ctx->rc_scinfo.rsi_regs[0],                         /* clone_flags */
	                           (USER UNCHECKED pid_t *)ctx->rc_scinfo.rsi_regs[2], /* parent_tidptr */
	                           (USER UNCHECKED pid_t *)ctx->rc_scinfo.rsi_regs[4], /* child_tidptr */
	                           (USER UNCHECKED void *)ctx->rc_scinfo.rsi_regs[1],  /* child_stack */
	                           ctx->rc_scinfo.rsi_regs[0] & CLONE_SETTLS ? ctx->rc_scinfo.rsi_regs[3]
	                                                                     : x86_get_user_gsbase(),
	                           x86_get_user_fsbase());
	child_tid = task_gettid_of(child_tsk);
	decref(child_tsk);
	icpustate_setreturn(ctx->rc_state, child_tid);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL32_5(pid_t, clone,
                   syscall_ulong_t, flags,
                   USER UNCHECKED void *, child_stack,
                   USER UNCHECKED pid_t *, ptid,
                   uintptr_t, newtls,
                   USER UNCHECKED pid_t *, ctid) {
	(void)flags;
	(void)child_stack;
	(void)ptid;
	(void)ctid;
	(void)newtls;

	/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&sys_clone32_rpc, NULL);
	__builtin_unreachable();
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_CLONE || (__ARCH_WANT_SYSCALL_CLONE && !__x86_64__) */





/************************************************************************/
/* fork()                                                               */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FORK
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL
sys_fork_impl(struct icpustate *__restrict state) {
	pid_t child_tid;
	REF struct task *child_tsk;
	child_tsk = sys_clone_impl(state, SIGCHLD, NULL, NULL,
	                           (USER UNCHECKED void *)icpustate_getusersp(state),
	                           x86_get_user_gsbase(),
	                           x86_get_user_fsbase());
	child_tid = task_gettid_of(child_tsk);
	decref(child_tsk);
	gpregs_setpax(&state->ics_gpregs, child_tid);
	return state;
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_fork_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;
	ctx->rc_state = sys_fork_impl(ctx->rc_state);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL0(pid_t, fork) {
	/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&sys_fork_rpc, NULL);
	__builtin_unreachable();
}
#endif /* __ARCH_WANT_SYSCALL_FORK */





/************************************************************************/
/* fork()                                                               */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_VFORK
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL
sys_vfork_impl(struct icpustate *__restrict state) {
	pid_t child_tid;
	REF struct task *child_tsk;
	child_tsk = sys_clone_impl(state, CLONE_VM | CLONE_VFORK | SIGCHLD, NULL, NULL,
	                           (USER UNCHECKED void *)icpustate_getusersp(state),
	                           x86_get_user_gsbase(),
	                           x86_get_user_fsbase());
	child_tid = task_gettid_of(child_tsk);
	decref(child_tsk);
	gpregs_setpax(&state->ics_gpregs, child_tid);
	return state;
}

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_vfork_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;
	ctx->rc_state = sys_vfork_impl(ctx->rc_state);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL0(pid_t, vfork) {
	/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&sys_vfork_rpc, NULL);
	__builtin_unreachable();
}
#endif /* __ARCH_WANT_SYSCALL_VFORK */

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_CLONE_C */
