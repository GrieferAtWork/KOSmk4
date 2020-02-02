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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUG_DEBUGTRAP_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUG_DEBUGTRAP_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/syscall.h>
#include <kernel/types.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/pid.h>
#include <sched/rpc.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/sync/atomic-rwlock.h>
#include <hybrid/unaligned.h>

#include <asm/cpu-flags.h>
#include <asm/registers.h>
#include <kos/bits/debugtrap32.h>
#include <kos/debugtrap.h>
#include <kos/except/inval.h>
#include <kos/kernel/cpu-state-verify.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/cpu-state32.h>

#include <assert.h>
#include <errno.h>
#include <malloca.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <librpc/rpc.h>

DECL_BEGIN

/* Exception handler for unhandled exceptions thrown by  */
INTERN ATTR_USED NONNULL((1, 2)) unsigned int
NOTHROW(KCALL driver_initializer_personality)(struct unwind_fde_struct *__restrict UNUSED(fde),
                                              struct kcpustate *__restrict UNUSED(state),
                                              void *UNUSED(lsda)) {
	if (kernel_debugtrap_enabled() &&
	    (kernel_debugtrap_on & KERNEL_DEBUGTRAP_ON_DRIVER_INIT_FAILURE)) {
		siginfo_t si;
		struct kcpustate *st;
		struct exception_info *info = error_info();
		if (!error_as_signal(&info->ei_data, &si))
			si.si_signo = SIGILL;
		st = kernel_debugtrap_r(&info->ei_state, si.si_signo);
		(void)st;
	}
	return DWARF_PERSO_CONTINUE_UNWIND;
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


PRIVATE DEFINE_ATOMIC_RWLOCK(kernel_debugtrap_lock);
DATDEF byte_t kernel_debugtrap_data[] ASMNAME("kernel_debugtrap");
#define DEFINE_CPUSTATE_VARS(cpustate)                                                           \
	INTDEF byte_t trigger_debugtrap_##cpustate##_data[] ASMNAME("trigger_debugtrap_" #cpustate); \
	INTDEF byte_t kernel_debugtrap_##cpustate##_data[] ASMNAME("kernel_debugtrap_" #cpustate);   \
	INTDEF s32 __x86_kernel_debugtrap_r_##cpustate##_jmp_offset;                                 \
	INTDEF s32 __x86_trigger_debugtrap_##cpustate##_call_offset;
FOREACH_CPUSTATE(DEFINE_CPUSTATE_VARS)
#undef DEFINE_CPUSTATE_VARS


LOCAL NOBLOCK NONNULL((1)) void
NOTHROW(FCALL setpcrel)(s32 *__restrict offset, void *target) {
	s32 disp;
	disp = (s32)((intptr_t)(uintptr_t)target -
	             (intptr_t)(uintptr_t)(offset + 1));
	ATOMIC_WRITE(*offset, disp);
}
LOCAL NOBLOCK WUNUSED NONNULL((1)) void *
NOTHROW(FCALL getpcrel)(s32 *__restrict offset) {
	s32 disp;
	disp = ATOMIC_READ(*offset);
	return (void *)(uintptr_t)((intptr_t)(offset + 1) + (intptr_t)disp);
}


/* Simply check if the `kernel_debugtrap()' would immediately return. */
#define TRAPS_ENABLED() (ATOMIC_READ(kernel_debugtrap_data[0]) != 0xc3)

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
	sync_write(&kernel_debugtrap_lock);
	if unlikely(TRAPS_ENABLED()) {
		/* There are already some traps installed. */
		sync_endwrite(&kernel_debugtrap_lock);
		return false;
	}
	/* Install our new traps handlers. */
#define ENABLE_TRAP(cpustate)                                                                          \
	setpcrel((s32 *)(kernel_debugtrap_##cpustate##_data + 1), trigger_debugtrap_##cpustate##_data);    \
	setpcrel(&__x86_trigger_debugtrap_##cpustate##_call_offset, (void *)handlers->dt_trap_##cpustate); \
	setpcrel(&__x86_kernel_debugtrap_r_##cpustate##_jmp_offset, (void *)handlers->dt_trap_##cpustate);
	FOREACH_CPUSTATE(ENABLE_TRAP)
#undef ENABLE_TRAP
	ATOMIC_WRITE(kernel_debugtrap_data[0], 0x90); /* nop */
	sync_endwrite(&kernel_debugtrap_lock);
	return true;
}


PUBLIC NONNULL((1)) bool FCALL
kernel_debugtraps_uninstall(struct kernel_debugtraps const *__restrict handlers)
		THROWS(E_WOULDBLOCK) {
	struct kernel_debugtraps old_traps;
	sync_write(&kernel_debugtrap_lock);
	if (!do_get_traps(&old_traps))
		goto nope; /* No traps installed. */
	if (memcmp(&old_traps, handlers, sizeof(struct kernel_debugtraps)) != 0)
		goto nope; /* Different traps were installed. */
	/* Uninstall traps. */
#define DISABLE_TRAP(cpustate)                                                                           \
	setpcrel(&__x86_trigger_debugtrap_##cpustate##_call_offset, (void *)&kernel_debugtrap_r_##cpustate); \
	ATOMIC_WRITE(__x86_kernel_debugtrap_r_##cpustate##_jmp_offset, 0);                                   \
	ATOMIC_WRITE(*(s32 *)(kernel_debugtrap_##cpustate##_data + 1), 0);
	FOREACH_CPUSTATE(DISABLE_TRAP)
#undef DISABLE_TRAP
	ATOMIC_WRITE(kernel_debugtrap_data[0], 0xc3); /* ret */
	sync_endwrite(&kernel_debugtrap_lock);
	return true;
nope:
	sync_endwrite(&kernel_debugtrap_lock);
	return false;
}

/* Get the currently installed debug traps (or return `false' if none are installed) */
PUBLIC NONNULL((1)) bool FCALL
kernel_debugtraps_get(struct kernel_debugtraps *__restrict handlers)
		THROWS(E_WOULDBLOCK) {
	bool result;
	sync_read(&kernel_debugtrap_lock);
	result = do_get_traps(handlers);
	sync_endread(&kernel_debugtrap_lock);
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
		cpustate_verify_userpflags(icpustate_getpflags(return_state),
		                           eflags, eflags_mask);
#ifndef __x86_64__
		if (icpustate_isvm86(return_state)) {
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
		icpustate_setpc(return_state, ustate->ucs_eip);
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
		cpustate_verify_userpflags(icpustate_getpflags(return_state),
		                           rflags, rflags_mask);
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
		icpustate_setpc(return_state, ustate->ucs_rip);
		icpustate_setuserpsp(return_state, ustate->ucs_gpregs.gp_rsp);
		set_user_fsbase(ustate->ucs_sgbase.sg_fsbase);
		set_user_gsbase(ustate->ucs_sgbase.sg_gsbase);
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


PRIVATE struct icpustate *FCALL
sys_debugtrap_rpc32(void *UNUSED(arg), struct icpustate *__restrict state,
                    unsigned int reason, struct rpc_syscall_info const *sc_info) {
	if (reason == TASK_RPC_REASON_SYSCALL) {
		state = sys_debugtrap32_impl(state,
		                             (USER UNCHECKED struct ucpustate32 const *)sc_info->rsi_regs[0],
		                             (USER UNCHECKED struct debugtrap_reason32 const *)sc_info->rsi_regs[1]);
	}
	return state;
}

#ifdef __x86_64__
PRIVATE struct icpustate *FCALL
sys_debugtrap_rpc64(void *UNUSED(arg), struct icpustate *__restrict state,
                    unsigned int reason, struct rpc_syscall_info const *sc_info) {
	if (reason == TASK_RPC_REASON_SYSCALL) {
		state = sys_debugtrap64_impl(state,
		                             (USER UNCHECKED struct ucpustate64 const *)sc_info->rsi_regs[0],
		                             (USER UNCHECKED struct debugtrap_reason64 const *)sc_info->rsi_regs[1]);
	}
	return state;
}
#endif /* __x86_64__ */

DEFINE_SYSCALL2(errno_t, debugtrap,
                USER UNCHECKED struct ucpustate const *, state,
                USER UNCHECKED struct debugtrap_reason const *, reason) {
	(void)state;
	(void)reason;
	if (kernel_debugtrap_enabled()) {
		task_schedule_user_rpc(THIS_TASK,
#ifdef __x86_64__
		                       &sys_debugtrap_rpc64,
#else /* __x86_64__ */
		                       &sys_debugtrap_rpc32,
#endif /* !__x86_64__ */
		                       NULL,
		                       TASK_RPC_FHIGHPRIO |
		                       TASK_USER_RPC_FINTR,
		                       GFP_NORMAL);
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
		task_schedule_user_rpc(THIS_TASK,
		                       &sys_debugtrap_rpc32,
		                       NULL,
		                       TASK_RPC_FHIGHPRIO |
		                       TASK_USER_RPC_FINTR,
		                       GFP_NORMAL);
	}
	return -ENOENT;
}
#endif /* __x86_64__ */


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUG_DEBUGTRAP_C */
