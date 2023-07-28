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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_TASK_CLONE_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_TASK_CLONE_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/syscall.h>
#include <sched/group.h>
#include <sched/rpc.h>
#include <sched/task-clone.h>
#include <sched/task.h>

#include <asm/cpu-flags.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>

#ifndef CONFIG_NO_KERNEL_USERKERN_SEGMENT
#include <kernel/rand.h>
#include <sched/userkern.h>

#include <kos/kernel/paging.h>
#include <kos/ukern.h>
#endif /* !CONFIG_NO_KERNEL_USERKERN_SEGMENT */

DECL_BEGIN

#ifndef CONFIG_NO_KERNEL_USERKERN_SEGMENT
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
#endif /* !CONFIG_NO_KERNEL_USERKERN_SEGMENT */


DATDEF ATTR_PERTASK uintptr_t this_x86_kernel_psp0_ ASMNAME("this_x86_kernel_psp0");
extern byte_t x86_kthread_exit[];


/* Arch-specific function  to construct  the initial  scpustate
 * that will execute the function descriptor encoded by `args'. */
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 2, 3)) struct scpustate *
NOTHROW(FCALL task_clone_setup_kthread)(struct task *__restrict thread, void *ksp,
                                        struct task_clone_kargs *__restrict args) {
	struct scpustate *result;
	FORTASK(thread, this_x86_kernel_psp0_) = (uintptr_t)ksp;

#ifdef __x86_64__
	/* Make space for arguments. */
	if (args->tck_argc > 6)
		ksp = (byte_t *)ksp - ((args->tck_argc - 6) * 8);

	/* Push return address. */
	ksp = (byte_t *)ksp - sizeof(u64);
	*(u64 *)ksp = (u64)(void *)x86_kthread_exit;

	result = (struct scpustate *)((byte_t *)ksp - SIZEOF_SCPUSTATE);

	/* Initialize the thread's entry state. */
	bzero(result, sizeof(*result));
	result->scs_irregs.ir_cs     = SEGMENT_KERNEL_CODE;
	result->scs_irregs.ir_ss     = SEGMENT_KERNEL_DATA0;
	result->scs_irregs.ir_rsp    = (u64)ksp;
	result->scs_irregs.ir_rflags = EFLAGS_IF;
	result->scs_irregs.ir_rip    = (u64)(void *)args->tck_main;
	result->scs_sgregs.sg_gs     = SEGMENT_USER_DATA_RPL; /* Doesn't really matter, but stick to the likely case of this being USER_GSBASE */
	result->scs_sgregs.sg_fs     = SEGMENT_USER_DATA_RPL;
	result->scs_sgregs.sg_es     = SEGMENT_USER_DATA_RPL;
	result->scs_sgregs.sg_ds     = SEGMENT_USER_DATA_RPL;
	result->scs_sgbase.sg_gsbase = (u64)thread;

	/* Fill in arguments */
	if (args->tck_argc >= 1)
		result->scs_gpregs.gp_rdi = va_arg(args->tck_args, u64);
	if (args->tck_argc >= 2)
		result->scs_gpregs.gp_rsi = va_arg(args->tck_args, u64);
	if (args->tck_argc >= 3)
		result->scs_gpregs.gp_rdx = va_arg(args->tck_args, u64);
	if (args->tck_argc >= 4)
		result->scs_gpregs.gp_rcx = va_arg(args->tck_args, u64);
	if (args->tck_argc >= 5)
		result->scs_gpregs.gp_r8 = va_arg(args->tck_args, u64);
	if (args->tck_argc >= 6)
		result->scs_gpregs.gp_r9 = va_arg(args->tck_args, u64);
	if (args->tck_argc > 6) {
		size_t i;
		for (i = 0; i < (args->tck_argc - 6); ++i)
			((u64 *)ksp)[i] = va_arg(args->tck_args, u64);
	}
#else /* __x86_64__ */
	/* Make space for arguments. */
	ksp = (byte_t *)ksp - (args->tck_argc * 4);
	ksp = memcpy(ksp, args->tck_args, args->tck_argc, 4);

	/* Push return address. */
	ksp = (byte_t *)ksp - sizeof(u32);
	*(u32 *)ksp = (u32)(void *)x86_kthread_exit;

	/* Allocate initial CPU state. */
	ksp = (byte_t *)ksp - (OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL);
	result = (struct scpustate *)ksp;
	bzero(result, OFFSET_SCPUSTATE_IRREGS + SIZEOF_IRREGS_KERNEL);

	/* Initialize the thread's entry state. */
	result->scs_irregs_k.ir_cs     = SEGMENT_KERNEL_CODE;
	result->scs_irregs_k.ir_eflags = EFLAGS_IF;
	result->scs_irregs_k.ir_eip    = (u32)(void *)args->tck_main;
	result->scs_sgregs.sg_gs       = SEGMENT_USER_GSBASE_RPL;
	result->scs_sgregs.sg_fs       = SEGMENT_KERNEL_FSBASE;
	result->scs_sgregs.sg_es       = SEGMENT_USER_DATA_RPL;
	result->scs_sgregs.sg_ds       = SEGMENT_USER_DATA_RPL;
#endif /* !__x86_64__ */
	return result;
}




/************************************************************************/
/* clone()                                                              */
/************************************************************************/
#if defined(__ARCH_WANT_SYSCALL_CLONE) && defined(__x86_64__)
PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_clone64_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	pid_t child_tid;
	struct task_clone_args cargs;
	REF struct task *child_tsk;
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;
	bzero(&cargs, sizeof(cargs));
	cargs.tca_flags       = ctx->rc_scinfo.rsi_regs[0] & ~CSIGNAL;              /* clone_flags */
	cargs.tca_exit_signal = ctx->rc_scinfo.rsi_regs[0] & CSIGNAL;               /* clone_flags */
	cargs.tca_pidfd       = (NCX UNCHECKED fd_t *)ctx->rc_scinfo.rsi_regs[2];  /* parent_tidptr */
	cargs.tca_parent_tid  = (NCX UNCHECKED pid_t *)ctx->rc_scinfo.rsi_regs[2]; /* parent_tidptr */
	cargs.tca_child_tid   = (NCX UNCHECKED pid_t *)ctx->rc_scinfo.rsi_regs[3]; /* child_tidptr */
	cargs.tca_stack       = (NCX UNCHECKED void *)ctx->rc_scinfo.rsi_regs[1];  /* child_stack */
	cargs.tca_arch.atca_x86_gsbase = x86_get_user_gsbase();
	cargs.tca_arch.atca_x86_fsbase = ctx->rc_scinfo.rsi_regs[4];
	if (!(ctx->rc_scinfo.rsi_regs[0] & CLONE_SETTLS))
		cargs.tca_arch.atca_x86_fsbase = x86_get_user_fsbase();
	child_tsk = task_clone(ctx->rc_state, &cargs);
	child_tid = task_gettid_of(child_tsk);
	decref(child_tsk);
	icpustate_setreturn(ctx->rc_state, child_tid);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL64_5(pid_t, clone,
                   syscall_ulong_t, flags,
                   NCX UNCHECKED void *, child_stack,
                   NCX UNCHECKED pid_t *, ptid,
                   NCX UNCHECKED pid_t *, ctid,
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
	struct task_clone_args cargs;
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;
	bzero(&cargs, sizeof(cargs));
	cargs.tca_flags       = ctx->rc_scinfo.rsi_regs[0] & ~CSIGNAL;              /* clone_flags */
	cargs.tca_exit_signal = ctx->rc_scinfo.rsi_regs[0] & CSIGNAL;               /* clone_flags */
	cargs.tca_pidfd       = (NCX UNCHECKED fd_t *)ctx->rc_scinfo.rsi_regs[2];  /* parent_tidptr */
	cargs.tca_parent_tid  = (NCX UNCHECKED pid_t *)ctx->rc_scinfo.rsi_regs[2]; /* parent_tidptr */
	cargs.tca_child_tid   = (NCX UNCHECKED pid_t *)ctx->rc_scinfo.rsi_regs[4]; /* child_tidptr */
	cargs.tca_stack       = (NCX UNCHECKED void *)ctx->rc_scinfo.rsi_regs[1];  /* child_stack */
	cargs.tca_arch.atca_x86_fsbase = x86_get_user_fsbase();
	cargs.tca_arch.atca_x86_gsbase = ctx->rc_scinfo.rsi_regs[3];
	if (!(ctx->rc_scinfo.rsi_regs[0] & CLONE_SETTLS))
		cargs.tca_arch.atca_x86_gsbase = x86_get_user_gsbase();
	child_tsk = task_clone(ctx->rc_state, &cargs);
	child_tid = task_gettid_of(child_tsk);
	decref(child_tsk);
	icpustate_setreturn(ctx->rc_state, child_tid);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL32_5(pid_t, clone,
                   syscall_ulong_t, flags,
                   NCX UNCHECKED void *, child_stack,
                   NCX UNCHECKED pid_t *, ptid,
                   uintptr_t, newtls,
                   NCX UNCHECKED pid_t *, ctid) {
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

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_TASK_CLONE_C */
