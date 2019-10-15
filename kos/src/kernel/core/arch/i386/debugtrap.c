/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGTRAP_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGTRAP_C 1
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

#include <asm/registers.h>
#include <kos/debugtrap.h>
#include <kos/except-inval.h>
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
NOTHROW(KCALL driver_initializer_personality)(struct unwind_fde_struct *__restrict fde,
                                              struct kcpustate *__restrict state,
                                              void *lsda) {
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
		if unlikely((irregs_rdflags(&return_state->ics_irregs) & ~eflags_mask) !=
		            (eflags & ~eflags_mask))
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
			      X86_REGISTER_MISC_EFLAGS, eflags);
#ifndef __x86_64__
		if (irregs_isvm86(&return_state->ics_irregs)) {
			irregs_wrcs(&return_state->ics_irregs, cs);
			return_state->ics_irregs_v.ir_ss = ss;
			return_state->ics_irregs_v.ir_es = es;
			return_state->ics_irregs_v.ir_ds = ds;
			return_state->ics_irregs_v.ir_fs = fs;
			return_state->ics_irregs_v.ir_gs = gs;
		} else
#endif /* !__x86_64__ */
		{
			/* Validate segment register indices before actually restoring them. */
			if unlikely(!SEGMENT_IS_VALID_USERCODE(cs))
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_SEGMENT_CS, cs);
			if unlikely(!SEGMENT_IS_VALID_USERDATA(gs))
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_SEGMENT_GS, gs);
			if unlikely(!SEGMENT_IS_VALID_USERDATA(fs))
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_SEGMENT_FS, fs);
			if unlikely(!SEGMENT_IS_VALID_USERDATA(es))
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_SEGMENT_ES, es);
			if unlikely(!SEGMENT_IS_VALID_USERDATA(ds))
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_SEGMENT_DS, ds);
			if unlikely(!SEGMENT_IS_VALID_USERDATA(ss))
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
				      X86_REGISTER_SEGMENT_SS, ss);
			__wrgs(gs);
#ifdef __x86_64__
			__wrfs(fs);
			__wres(es);
			__wrds(ds);
			irregs_wrcs(&return_state->ics_irregs, cs);
			irregs_wrss(&return_state->ics_irregs, ss);
#else /* __x86_64__ */
			return_state->ics_fs = fs;
			return_state->ics_es = es;
			return_state->ics_ds = ds;
			irregs_wrcs(&return_state->ics_irregs, cs);
			return_state->ics_irregs_u.ir_ss = ss;
#endif /* !__x86_64__ */
		}
#ifdef __x86_64__
		return_state->ics_gpregs.gp_rdi = ustate->ucs_gpregs.gp_edi;
		return_state->ics_gpregs.gp_rsi = ustate->ucs_gpregs.gp_esi;
		return_state->ics_gpregs.gp_rbp = ustate->ucs_gpregs.gp_ebp;
		return_state->ics_gpregs.gp_rbx = ustate->ucs_gpregs.gp_ebx;
		return_state->ics_gpregs.gp_rdx = ustate->ucs_gpregs.gp_edx;
		return_state->ics_gpregs.gp_rcx = ustate->ucs_gpregs.gp_ecx;
		return_state->ics_gpregs.gp_rax = ustate->ucs_gpregs.gp_eax;
		irregs_wrflags(&return_state->ics_irregs, eflags);
		irregs_wrip(&return_state->ics_irregs, ustate->ucs_eip);
		irregs_wrsp(&return_state->ics_irregs, ustate->ucs_gpregs.gp_esp);
#else /* __x86_64__ */
		return_state->ics_gpregs.gp_edi = ustate->ucs_gpregs.gp_edi;
		return_state->ics_gpregs.gp_esi = ustate->ucs_gpregs.gp_esi;
		return_state->ics_gpregs.gp_ebp = ustate->ucs_gpregs.gp_ebp;
		return_state->ics_gpregs.gp_ebx = ustate->ucs_gpregs.gp_ebx;
		return_state->ics_gpregs.gp_edx = ustate->ucs_gpregs.gp_edx;
		return_state->ics_gpregs.gp_ecx = ustate->ucs_gpregs.gp_ecx;
		return_state->ics_gpregs.gp_eax = ustate->ucs_gpregs.gp_eax;
		irregs_wrflags(&return_state->ics_irregs_k, eflags);
		irregs_wrip(&return_state->ics_irregs_k, ustate->ucs_eip);
		return_state->ics_irregs_u.ir_esp = ustate->ucs_gpregs.gp_esp;
#endif /* !__x86_64__ */
	} else {
		/* Return EOK to indicate that the trap got triggered */
#ifdef __x86_64__
		return_state->ics_gpregs.gp_rax = (u32)-EOK;
#else /* __x86_64__ */
		return_state->ics_gpregs.gp_eax = (u32)-EOK;
#endif /* !__x86_64__ */
	}
	/* Trigger the trap. */
	return kernel_debugtrap_r_icpustate(return_state, reason);
}

INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL
sys_debugtrap32_impl(struct icpustate *__restrict return_state,
                     USER UNCHECKED struct ucpustate32 const *ustate,
                     USER UNCHECKED struct debugtrap_reason32 const *ureason) {
	struct debugtrap_reason reason;
	if (!kernel_debugtrap_enabled()) {
		/* Debug traps are disabled. */
#ifdef __x86_64__
		return_state->ics_gpregs.gp_rax = (u32)-ENOENT;
#else /* __x86_64__ */
		return_state->ics_gpregs.gp_eax = (u32)-ENOENT;
#endif /* !__x86_64__ */
		return return_state;
	}
	if (ureason) {
		validate_readable(ureason, sizeof(*ureason));
		COMPILER_READ_BARRIER();
		reason.dtr_signo  = ureason->dtr_signo;
		reason.dtr_reason = ureason->dtr_reason;
		reason.dtr_intarg = ureason->dtr_intarg;
		COMPILER_READ_BARRIER();
		if (reason.dtr_reason > DEBUGTRAP_REASON_MAX)
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_DEBUG_REASON,
			      reason.dtr_reason);
		switch (reason.dtr_reason) {

		case DEBUGTRAP_REASON_MESSAGE:
			/* Debug message event. */
			validate_readable(reason.dtr_strarg, reason.dtr_signo);
			return_state = sys_do_debugtrap32_impl(return_state, ustate, &reason);
			((struct debugtrap_reason32 *)ureason)->dtr_signo = reason.dtr_signo;
			goto done;

		case DEBUGTRAP_REASON_FORK:
		case DEBUGTRAP_REASON_VFORK:
		case DEBUGTRAP_REASON_TEXITED:
		case DEBUGTRAP_REASON_PEXITED: {
			REF struct task *thread;
			cred_require_debugtrap();
			thread = pidns_lookup_task(THIS_PIDNS, (upid_t)reason.dtr_intarg);
			FINALLY_DECREF_UNLIKELY(thread);
			reason.dtr_ptrarg = thread;
			return_state = sys_do_debugtrap32_impl(return_state, ustate, &reason);
			goto done;
		}	break;

		case DEBUGTRAP_REASON_EXEC: {
			char *namebuf;
			size_t namelen;
			enum { MAXLEN = 4096 };
			validate_readable(reason.dtr_strarg, 1);
			namelen = strlen(reason.dtr_strarg);
			if (namelen > MAXLEN)
				THROW(E_BUFFER_TOO_SMALL, MAXLEN, namelen);
			namebuf = (char *)malloca((namelen + 1) * sizeof(char));
			TRY {
				memcpy(namebuf, reason.dtr_strarg, namelen * sizeof(char));
				namebuf[namelen]  = '\0';
				reason.dtr_strarg = namebuf;
				return_state = sys_do_debugtrap32_impl(return_state, ustate, &reason);
			} EXCEPT {
				freea(namebuf);
				RETHROW();
			}
			freea(namebuf);
			goto done;
		}	break;

		case DEBUGTRAP_REASON_VFORKDONE:
		case DEBUGTRAP_REASON_SC_ENTRY:
		case DEBUGTRAP_REASON_SC_EXIT:
		case DEBUGTRAP_REASON_CLONE:
		case DEBUGTRAP_REASON_SWBREAK:
		case DEBUGTRAP_REASON_HWBREAK:
			cred_require_debugtrap();
			reason.dtr_intarg = 0;
			break;

		default:
			reason.dtr_intarg = 0;
			break;
		}
		if (reason.dtr_reason != DEBUGTRAP_REASON_TEXITED &&
		    reason.dtr_reason != DEBUGTRAP_REASON_PEXITED) {
			/* Verify a valid signal number.
			 * NOTE: The (T|P)EXITED reason use the SIGNO field as the exit status. */
			if (reason.dtr_signo == 0 || reason.dtr_signo >= NSIG)
				THROW(E_INVALID_ARGUMENT_BAD_VALUE,
				      E_INVALID_ARGUMENT_CONTEXT_DEBUG_TRAPNO,
				      reason.dtr_signo);
		}
	} else {
		reason.dtr_signo  = SIGTRAP;
		reason.dtr_reason = DEBUGTRAP_REASON_NONE;
		reason.dtr_intarg = 0;
	}
	return_state = sys_do_debugtrap32_impl(return_state, ustate, &reason);
done:
	return return_state;
}


PRIVATE struct icpustate *FCALL
sys_debugtrap_rpc32(void *UNUSED(arg), struct icpustate *__restrict state,
                    unsigned int reason, struct rpc_syscall_info const *sc_info) {
	if (reason == TASK_RPC_REASON_SYSCALL) {
		state = sys_debugtrap32_impl(state,
		                             (USER UNCHECKED struct ucpustate32 const *)sc_info->rsi_args[0],
		                             (USER UNCHECKED struct debugtrap_reason32 const *)sc_info->rsi_args[1]);
	}
	return state;
}


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
		                       NULL,
		                       GFP_NORMAL);
	}
	return -ENOENT;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGTRAP_C */
