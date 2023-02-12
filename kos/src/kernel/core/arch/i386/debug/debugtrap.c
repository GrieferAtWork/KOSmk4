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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUG_DEBUGTRAP_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUG_DEBUGTRAP_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/rt/except-personality.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/group.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <hybrid/sched/atomic-lock.h>
#include <hybrid/unaligned.h>

#include <asm/cpu-flags.h>
#include <asm/registers.h>
#include <kos/bits/debugtrap32.h>
#include <kos/debugtrap.h>
#include <kos/except/reason/inval.h>
#include <kos/kernel/bits/cpu-state32.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state-verify.h>
#include <kos/kernel/cpu-state.h>

#include <assert.h>
#include <atomic.h>
#include <errno.h>
#include <malloca.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

DECL_BEGIN

/* Exception handler for unhandled exceptions thrown by  */
INTERN WUNUSED NONNULL((1, 2)) unsigned int
NOTHROW(EXCEPT_PERSONALITY_CC driver_initializer_personality)(struct unwind_fde_struct *__restrict UNUSED(fde),
                                                              struct kcpustate *__restrict UNUSED(state)) {
	if (kernel_debugtrap_shouldtrap(KERNEL_DEBUGTRAP_ON_DRIVER_INIT_FAILURE)) {
		siginfo_t si;
		struct kcpustate *st;
		struct exception_info *info = except_info();
		if (!except_as_signal(&info->ei_data, &si))
			si.si_signo = SIGILL;
		st = kernel_debugtrap_r(&info->ei_state, si.si_signo);
		(void)st;
	}
	return EXCEPT_PERSONALITY_CONTINUE_UNWIND;
}




/* Set of `KERNEL_DEBUGTRAP_ON_*', specifying events for which to trigger traps. */
PUBLIC uintptr_t volatile kernel_debugtrap_on = KERNEL_DEBUGTRAP_ON_DEFAULT;

#define FOREACH_CPUSTATE(callback) \
	callback(icpustate)            \
	callback(scpustate)            \
	callback(ucpustate)            \
	callback(kcpustate)            \
	callback(lcpustate)            \
	callback(fcpustate)


PRIVATE struct atomic_lock kernel_debugtrap_lock = ATOMIC_LOCK_INIT;
DATDEF byte_t kernel_debugtrap_data[] ASMNAME("kernel_debugtrap");
#define DEFINE_CPUSTATE_VARS(cpustate)                                                           \
	INTDEF byte_t trigger_debugtrap_##cpustate##_data[] ASMNAME("trigger_debugtrap_" #cpustate); \
	INTDEF byte_t kernel_debugtrap_##cpustate##_data[] ASMNAME("kernel_debugtrap_" #cpustate);   \
	INTDEF s32 __x86_kernel_debugtrap_r_##cpustate##_jmp_offset;                                 \
	INTDEF s32 __x86_trigger_debugtrap_##cpustate##_call_offset;
FOREACH_CPUSTATE(DEFINE_CPUSTATE_VARS)
#undef DEFINE_CPUSTATE_VARS

/* Helper macros for `kernel_debugtrap_lock' */
#define _kernel_debugtrap_reap()      (void)0
#define kernel_debugtrap_reap()       (void)0
#define kernel_debugtrap_mustreap()   0
#define kernel_debugtrap_tryacquire() atomic_lock_tryacquire(&kernel_debugtrap_lock)
#define kernel_debugtrap_acquire()    atomic_lock_acquire(&kernel_debugtrap_lock)
#define kernel_debugtrap_acquire_nx() atomic_lock_acquire_nx(&kernel_debugtrap_lock)
#define _kernel_debugtrap_release()   atomic_lock_release(&kernel_debugtrap_lock)
#define kernel_debugtrap_release()    (atomic_lock_release(&kernel_debugtrap_lock), kernel_debugtrap_reap())
#define kernel_debugtrap_acquired()   atomic_lock_acquired(&kernel_debugtrap_lock)
#define kernel_debugtrap_available()  atomic_lock_available(&kernel_debugtrap_lock)
#define kernel_debugtrap_waitfor()    atomic_lock_waitfor(&kernel_debugtrap_lock)
#define kernel_debugtrap_waitfor_nx() atomic_lock_waitfor_nx(&kernel_debugtrap_lock)



LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL setpcrel)(s32 *__restrict offset, void *target) {
	s32 disp;
	disp = (s32)((intptr_t)(uintptr_t)target -
	             (intptr_t)(uintptr_t)(offset + 1));
	atomic_write(offset, disp);
}
LOCAL NOBLOCK WUNUSED NONNULL((1)) void *
NOTHROW(FCALL getpcrel)(s32 *__restrict offset) {
	s32 disp;
	disp = atomic_read(offset);
	return (void *)(uintptr_t)((intptr_t)(offset + 1) + (intptr_t)disp);
}


/* Simply check if the `kernel_debugtrap()' does more than return immediately. */
#define TRAPS_ENABLED() (atomic_read(&kernel_debugtrap_data[0]) != 0xc3)

/* Check if debug traps are enabled. */
PUBLIC NOBLOCK WUNUSED bool
NOTHROW(FCALL kernel_debugtrap_enabled)(void) {
	return TRAPS_ENABLED();
}



PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL do_get_traps)(struct kernel_debugtraps *__restrict handlers) {
	if (!TRAPS_ENABLED())
		return false;
	assert(kernel_debugtrap_data[0] == 0x90);
#define LOAD_OFFSET(cpustate)                                                                                 \
	assert(getpcrel((s32 *)(kernel_debugtrap_##cpustate##_data + 1)) == trigger_debugtrap_##cpustate##_data); \
	assert(getpcrel(&__x86_kernel_debugtrap_r_##cpustate##_jmp_offset) ==                                     \
	       getpcrel(&__x86_trigger_debugtrap_##cpustate##_call_offset));                                      \
	*(void **)&handlers->dt_trap_##cpustate = getpcrel(&__x86_kernel_debugtrap_r_##cpustate##_jmp_offset);
	FOREACH_CPUSTATE(LOAD_OFFSET)
#undef LOAD_OFFSET
	return true;
}


/* Install/uninstall the given set of trap handlers. */
PUBLIC NONNULL((1)) bool FCALL
kernel_debugtraps_install(struct kernel_debugtraps const *__restrict handlers)
		THROWS(E_WOULDBLOCK) {
	kernel_debugtrap_acquire();
	if unlikely(TRAPS_ENABLED()) {
		/* There are already some traps installed. */
		kernel_debugtrap_release();
		return false;
	}
	/* Install our new traps handlers. */
#define ENABLE_TRAP(cpustate)                                                                          \
	setpcrel((s32 *)(kernel_debugtrap_##cpustate##_data + 1), trigger_debugtrap_##cpustate##_data);    \
	setpcrel(&__x86_trigger_debugtrap_##cpustate##_call_offset, (void *)handlers->dt_trap_##cpustate); \
	setpcrel(&__x86_kernel_debugtrap_r_##cpustate##_jmp_offset, (void *)handlers->dt_trap_##cpustate);
	FOREACH_CPUSTATE(ENABLE_TRAP)
#undef ENABLE_TRAP
	atomic_write(&kernel_debugtrap_data[0], 0x90); /* nop */
	kernel_debugtrap_release();
	return true;
}


PUBLIC NONNULL((1)) bool FCALL
kernel_debugtraps_uninstall(struct kernel_debugtraps const *__restrict handlers)
		THROWS(E_WOULDBLOCK) {
	struct kernel_debugtraps old_traps;
	kernel_debugtrap_acquire();
	if (!do_get_traps(&old_traps))
		goto nope; /* No traps installed. */
	if (bcmp(&old_traps, handlers, sizeof(struct kernel_debugtraps)) != 0)
		goto nope; /* Different traps were installed. */
	/* Uninstall traps. */
#define DISABLE_TRAP(cpustate)                                                                           \
	setpcrel(&__x86_trigger_debugtrap_##cpustate##_call_offset, (void *)&kernel_debugtrap_r_##cpustate); \
	atomic_write(&__x86_kernel_debugtrap_r_##cpustate##_jmp_offset, 0);                                  \
	atomic_write((s32 *)(kernel_debugtrap_##cpustate##_data + 1), 0);
	FOREACH_CPUSTATE(DISABLE_TRAP)
#undef DISABLE_TRAP
	atomic_write(&kernel_debugtrap_data[0], 0xc3); /* ret */
	kernel_debugtrap_release();
	return true;
nope:
	kernel_debugtrap_release();
	return false;
}

/* Get the currently installed debug traps (or return `false' if none are installed) */
PUBLIC NONNULL((1)) bool FCALL
kernel_debugtraps_get(struct kernel_debugtraps *__restrict handlers)
		THROWS(E_WOULDBLOCK) {
	bool result;
	kernel_debugtrap_acquire();
	result = do_get_traps(handlers);
	kernel_debugtrap_release();
	return result;
}


INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 3)) struct icpustate *FCALL
sys_do_debugtrap32_impl(struct icpustate *__restrict return_state,
                        USER UNCHECKED struct ucpustate32 const *ustate,
                        struct debugtrap_reason const *__restrict reason) {
	if (ustate) {
		u16 gs, fs, es, ds, ss, cs;
		u32 eflags, eflags_mask = (u32)cred_allow_eflags_modify_mask();
		validate_readable(ustate, sizeof(*ustate));
		gs     = ustate->ucs_sgregs.sg_gs16;
		fs     = ustate->ucs_sgregs.sg_fs16;
		es     = ustate->ucs_sgregs.sg_es16;
		ds     = ustate->ucs_sgregs.sg_ds16;
		ss     = ustate->ucs_ss16;
		cs     = ustate->ucs_cs16;
		eflags = ustate->ucs_eflags;
		COMPILER_READ_BARRIER();
		cpustate_verify_usereflags((u32)icpustate_getpflags(return_state),
		                           /* Accept `EFLAGS_RF' (needed for debug trap on exception) */
		                           EFLAGS_RF | eflags, eflags_mask);
#ifndef __x86_64__
#ifndef __I386_NO_VM86
		if (icpustate_isvm86(return_state))
#endif /* !__I386_NO_VM86 */
		{
			return_state->ics_irregs_v.ir_es = es;
			return_state->ics_irregs_v.ir_ds = ds;
			return_state->ics_irregs_v.ir_fs = fs;
			return_state->ics_irregs_v.ir_gs = gs;
		} else
#endif /* !__x86_64__ */
		{
			/* Validate segment register indices before actually restoring them. */
			cpustate_verify_usercs(cs);
			cpustate_verify_usergs(gs);
			cpustate_verify_userfs(fs);
			cpustate_verify_useres(es);
			cpustate_verify_userds(ds);
			cpustate_verify_userss(ss);
#ifdef __x86_64__
			__wrgs_keepbase(gs);
			__wrfs_keepbase(fs);
			__wres(es);
			__wrds(ds);
#else /* __x86_64__ */
			__wrgs(gs);
			return_state->ics_fs = fs;
			return_state->ics_es = es;
			return_state->ics_ds = ds;
#endif /* !__x86_64__ */
		}
		icpustate_setcs(return_state, cs);
		icpustate_setuserss(return_state, ss);
		gpregs_setpdi(&return_state->ics_gpregs, ustate->ucs_gpregs.gp_edi);
		gpregs_setpsi(&return_state->ics_gpregs, ustate->ucs_gpregs.gp_esi);
		gpregs_setpbp(&return_state->ics_gpregs, ustate->ucs_gpregs.gp_ebp);
		gpregs_setpbx(&return_state->ics_gpregs, ustate->ucs_gpregs.gp_ebx);
		gpregs_setpdx(&return_state->ics_gpregs, ustate->ucs_gpregs.gp_edx);
		gpregs_setpcx(&return_state->ics_gpregs, ustate->ucs_gpregs.gp_ecx);
		gpregs_setpax(&return_state->ics_gpregs, ustate->ucs_gpregs.gp_eax);
		icpustate_setpflags(return_state, eflags);
		icpustate_setpip(return_state, ustate->ucs_eip);
		icpustate_setuserpsp(return_state, ustate->ucs_gpregs.gp_esp);
	} else {
		/* Return EOK to indicate that the trap got triggered */
		gpregs_setpax(&return_state->ics_gpregs, (uintptr_t)-EOK);
	}
	/* Trigger the trap. */
	return kernel_debugtrap_r_icpustate(return_state, reason);
}

#ifdef __x86_64__
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1, 3)) struct icpustate *FCALL
sys_do_debugtrap64_impl(struct icpustate *__restrict return_state,
                        USER UNCHECKED struct ucpustate64 const *ustate,
                        struct debugtrap_reason const *__restrict reason) {
	if (ustate) {
		u16 gs, fs, es, ds, ss, cs;
		u64 rflags, rflags_mask = (u32)cred_allow_eflags_modify_mask();
		validate_readable(ustate, sizeof(*ustate));
		gs     = ustate->ucs_sgregs.sg_gs16;
		fs     = ustate->ucs_sgregs.sg_fs16;
		es     = ustate->ucs_sgregs.sg_es16;
		ds     = ustate->ucs_sgregs.sg_ds16;
		ss     = ustate->ucs_ss16;
		cs     = ustate->ucs_cs16;
		rflags = ustate->ucs_rflags;
		COMPILER_READ_BARRIER();
		cpustate_verify_userrflags(icpustate_getpflags(return_state),
		                           /* Accept `EFLAGS_RF' (needed for debug trap on exception) */
		                           EFLAGS_RF | rflags, rflags_mask);
		/* Validate segment register indices before actually restoring them. */
		cpustate_verify_usercs(cs);
		cpustate_verify_usergs(gs);
		cpustate_verify_userfs(fs);
		cpustate_verify_useres(es);
		cpustate_verify_userds(ds);
		cpustate_verify_userss(ss);
		__wrgs_keepbase(gs);
		__wrfs_keepbase(fs);
		__wres(es);
		__wrds(ds);
		icpustate_setcs(return_state, cs);
		icpustate_setuserss(return_state, ss);
		gpregs64_to_gpregsnsp64(&ustate->ucs_gpregs, &return_state->ics_gpregs);
		icpustate_setpflags(return_state, rflags);
		icpustate_setpip(return_state, ustate->ucs_rip);
		icpustate_setuserpsp(return_state, ustate->ucs_gpregs.gp_rsp);
		x86_set_user_fsbase(ustate->ucs_sgbase.sg_fsbase);
		x86_set_user_gsbase(ustate->ucs_sgbase.sg_gsbase);
	} else {
		/* Return EOK to indicate that the trap got triggered */
		gpregs_setpax(&return_state->ics_gpregs, (uintptr_t)-EOK);
	}
	/* Trigger the trap. */
	return kernel_debugtrap_r_icpustate(return_state, reason);
}
#endif /* __x86_64__ */

INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL
sys_debugtrap32_impl(struct icpustate *__restrict return_state,
                     USER UNCHECKED struct ucpustate32 const *ustate,
                     USER UNCHECKED struct debugtrap_reason32 const *ureason);
#ifdef __x86_64__
INTDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL
sys_debugtrap64_impl(struct icpustate *__restrict return_state,
                     USER UNCHECKED struct ucpustate64 const *ustate,
                     USER UNCHECKED struct debugtrap_reason64 const *ureason);
#endif /* __x86_64__ */


#ifndef __INTELLISENSE__
DECL_END

#include "debugtrap-impl.c.inl"
#ifdef __x86_64__
#define DEFINE_DEBUGTRAP_WIDTH 4
#include "debugtrap-impl.c.inl"
#endif /* __x86_64__ */

DECL_BEGIN
#endif /* !__INTELLISENSE__ */


PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_debugtrap_rpc32(struct rpc_context *__restrict ctx,
                    void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the system call. */
	ctx->rc_state = sys_debugtrap32_impl(ctx->rc_state,
	                                     (USER UNCHECKED struct ucpustate32 const *)ctx->rc_scinfo.rsi_regs[0],
	                                     (USER UNCHECKED struct debugtrap_reason32 const *)ctx->rc_scinfo.rsi_regs[1]);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

#ifdef __x86_64__
PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_debugtrap_rpc64(struct rpc_context *__restrict ctx,
                    void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Do the system call. */
	ctx->rc_state = sys_debugtrap64_impl(ctx->rc_state,
	                                     (USER UNCHECKED struct ucpustate64 const *)ctx->rc_scinfo.rsi_regs[0],
	                                     (USER UNCHECKED struct debugtrap_reason64 const *)ctx->rc_scinfo.rsi_regs[1]);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}
#endif /* __x86_64__ */

DEFINE_SYSCALL2(errno_t, debugtrap,
                USER UNCHECKED struct ucpustate const *, state,
                USER UNCHECKED struct debugtrap_reason const *, reason) {
	(void)state;
	(void)reason;
	if (kernel_debugtrap_enabled()) {
		/* Send an RPC to ourself, so we can gain access to the user-space register state. */
#ifdef __x86_64__
		task_rpc_userunwind(&sys_debugtrap_rpc64, NULL);
#else /* __x86_64__ */
		task_rpc_userunwind(&sys_debugtrap_rpc32, NULL);
#endif /* !__x86_64__ */
	}
	return -ENOENT;
}


#ifdef __x86_64__
DEFINE_SYSCALL32_2(errno_t, debugtrap,
                   USER UNCHECKED struct ucpustate32 const *, state,
                   USER UNCHECKED struct debugtrap_reason32 const *, reason) {
	(void)state;
	(void)reason;
	if (kernel_debugtrap_enabled()) {
		/* Send an RPC to ourself, so we can gain access to the user-space register state. */
		task_rpc_userunwind(&sys_debugtrap_rpc32, NULL);
	}
	return -ENOENT;
}
#endif /* __x86_64__ */

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUG_DEBUGTRAP_C */
