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
#include <sched/rpc.h>
#include <sched/task.h>
#include <sched/cred.h>

#include <hybrid/atomic.h>
#include <hybrid/sync/atomic-rwlock.h>
#include <hybrid/unaligned.h>

#include <asm/registers.h>
#include <kos/debugtrap.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/cpu-state32.h>
#include <kos/bits/debugtrap.h>
#include <kos/bits/debugtrap32.h>

#include <errno.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <librpc/rpc.h>

DECL_BEGIN


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



#ifdef __x86_64__
INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL
sys_debugtrap64_impl(struct icpustate *__restrict return_state,
                     USER UNCHECKED struct ucpustate64 const *state,
                     syscall_ulong_t trapno,
                     USER UNCHECKED struct debug_trap_register64 const *regs) {
	char trap_register_text[DEBUG_TRAP_REGISTER_MAXSIZE + 1];
	if (!kernel_debugtrap_enabled()) {
		/* Debug traps are disabled. */
		return_state->ics_gpregs.gp_rax = (u32)-ENOENT;
		return;
	}
	if (trapno == 0 || trapno >= NSIG)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_DEBUG_TRAPNO,
		      trapno);
	if (regs) {
		size_t reqlen = 0;
		validate_readable(regs, sizeof(*regs));
		for (;; ++regs) {
			size_t avail;
			USER UNCHECKED char const *name, *value;
			name = ATOMIC_READ(regs->dtr_name);
			if (!name)
				break; /* Sentinel */
			value = ATOMIC_READ(regs->dtr_value);
			validate_readable(name, 1);
			validate_readable(value, 1);
			avail = DEBUG_TRAP_REGISTER_MAXSIZE - reqlen;
			if (reqlen >= DEBUG_TRAP_REGISTER_MAXSIZE)
				avail = 0;
			/* Append event text. */
			/* TODO: Ensure that `name' and `value' only contain valid characters. */
			reqlen += (size_t)snprintf(trap_register_text + reqlen,
			                           avail, "%s:%s;",
			                           name, value);
		}
		/* Ensure NUL-termination (this is why we allocate `trap_register_text' with +1 items) */
		trap_register_text[DEBUG_TRAP_REGISTER_MAXSIZE] = 0;
		/* Make sure that we don't use too much */
		if unlikely(reqlen > DEBUG_TRAP_REGISTER_MAXSIZE)
			THROW(E_BUFFER_TOO_SMALL, reqlen, DEBUG_TRAP_REGISTER_MAXSIZE);
	}
	if (state) {
		u16 gs, fs, es, ds, ss, cs;
		uintptr_t rflags;
		uintptr_t rflags_mask = cred_allow_eflags_modify_mask();
		validate_readable(state, sizeof(*state));
		gs     = state->ucs_sgregs.sg_gs;
		fs     = state->ucs_sgregs.sg_fs;
		es     = state->ucs_sgregs.sg_es;
		ds     = state->ucs_sgregs.sg_ds;
		ss     = state->ucs_ss;
		cs     = state->ucs_cs;
		rflags = state->ucs_rflags;
		COMPILER_READ_BARRIER();
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
		if unlikely((irregs_rdflags(&return_state->ics_irregs) & ~rflags_mask) !=
		            (rflags & ~rflags_mask))
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_SIGRETURN_REGISTER,
			      X86_REGISTER_MISC_RFLAGS, rflags);
		__wrgs(gs);
		__wrfs(fs);
		__wres(es);
		__wrds(ds);
		irregs_wrcs(&return_state->ics_irregs, cs);
		irregs_wrss(&return_state->ics_irregs, ss);
		GPREGS_TO_GPREGSNSP(return_state->ics_gpregs, state->ucs_gpregs);
		irregs_wrflags(&return_state->ics_irregs, rflags);
		irregs_wrip(&return_state->ics_irregs, state->ucs_rip);
		irregs_wrsp(&return_state->ics_irregs, state->ucs_gpregs.gp_rsp);
		set_user_fsbase(state->ucs_sgbase.sg_fsbase);
		set_user_gsbase(state->ucs_sgbase.sg_gsbase);
	} else {
		/* Return EOK to indicate that the trap got triggered */
		return_state->ics_gpregs.gp_rax = (u32)-EOK;
	}
	/* Trigger the trap. */
	return kernel_debugtrap_r_icpustate(return_state,
	                                    trapno,
	                                    regs ? trap_register_text : NULL);
}
#endif /* __x86_64__ */

INTERN ATTR_RETNONNULL WUNUSED NONNULL((1)) struct icpustate *FCALL
sys_debugtrap32_impl(struct icpustate *__restrict return_state,
                     USER UNCHECKED struct ucpustate32 const *state,
                     syscall_ulong_t trapno,
                     USER UNCHECKED struct debug_trap_register32 const *regs) {
	char trap_register_text[DEBUG_TRAP_REGISTER_MAXSIZE + 1];
	if (!kernel_debugtrap_enabled()) {
		/* Debug traps are disabled. */
#ifdef __x86_64__
		return_state->ics_gpregs.gp_rax = (u32)-ENOENT;
#else /* __x86_64__ */
		return_state->ics_gpregs.gp_eax = (u32)-ENOENT;
#endif /* !__x86_64__ */
		return return_state;
	}
	if (trapno == 0 || trapno >= NSIG)
		THROW(E_INVALID_ARGUMENT_BAD_VALUE,
		      E_INVALID_ARGUMENT_CONTEXT_DEBUG_TRAPNO,
		      trapno);
	if (regs) {
		size_t reqlen = 0;
		validate_readable(regs, sizeof(*regs));
		for (;; ++regs) {
			size_t avail;
			USER UNCHECKED char const *name, *value;
			name = (char const *)ATOMIC_READ(*(u32 *)&regs->dtr_name);
			if (!name)
				break; /* Sentinel */
			value = (char const *)ATOMIC_READ(*(u32 *)&regs->dtr_value);
			validate_readable(name, 1);
			validate_readable(value, 1);
			avail = DEBUG_TRAP_REGISTER_MAXSIZE - reqlen;
			if (reqlen >= DEBUG_TRAP_REGISTER_MAXSIZE)
				avail = 0;
			/* Append event text. */
			/* TODO: Ensure that `name' and `value' only contain valid characters. */
			reqlen += (size_t)snprintf(trap_register_text + reqlen,
			                           avail, "%s:%s;",
			                           name, value);
		}
		/* Ensure NUL-termination (this is why we allocate `trap_register_text' with +1 items) */
		trap_register_text[DEBUG_TRAP_REGISTER_MAXSIZE] = 0;
		/* Make sure that we don't use too much */
		if unlikely(reqlen > DEBUG_TRAP_REGISTER_MAXSIZE)
			THROW(E_BUFFER_TOO_SMALL, reqlen, DEBUG_TRAP_REGISTER_MAXSIZE);
	}
	if (state) {
		u16 gs, fs, es, ds, ss, cs;
		u32 eflags, eflags_mask = (u32)cred_allow_eflags_modify_mask();
		validate_readable(state, sizeof(*state));
		gs     = state->ucs_sgregs.sg_gs;
		fs     = state->ucs_sgregs.sg_fs;
		es     = state->ucs_sgregs.sg_es;
		ds     = state->ucs_sgregs.sg_ds;
		ss     = state->ucs_ss;
		cs     = state->ucs_cs;
		eflags = state->ucs_eflags;
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
		return_state->ics_gpregs.gp_rdi = state->ucs_gpregs.gp_edi;
		return_state->ics_gpregs.gp_rsi = state->ucs_gpregs.gp_esi;
		return_state->ics_gpregs.gp_rbp = state->ucs_gpregs.gp_ebp;
		return_state->ics_gpregs.gp_rbx = state->ucs_gpregs.gp_ebx;
		return_state->ics_gpregs.gp_rdx = state->ucs_gpregs.gp_edx;
		return_state->ics_gpregs.gp_rcx = state->ucs_gpregs.gp_ecx;
		return_state->ics_gpregs.gp_rax = state->ucs_gpregs.gp_eax;
		irregs_wrflags(&return_state->ics_irregs, eflags);
		irregs_wrip(&return_state->ics_irregs, state->ucs_eip);
		irregs_wrsp(&return_state->ics_irregs, state->ucs_gpregs.gp_esp);
#else /* __x86_64__ */
		return_state->ics_gpregs.gp_edi = state->ucs_gpregs.gp_edi;
		return_state->ics_gpregs.gp_esi = state->ucs_gpregs.gp_esi;
		return_state->ics_gpregs.gp_ebp = state->ucs_gpregs.gp_ebp;
		return_state->ics_gpregs.gp_ebx = state->ucs_gpregs.gp_ebx;
		return_state->ics_gpregs.gp_edx = state->ucs_gpregs.gp_edx;
		return_state->ics_gpregs.gp_ecx = state->ucs_gpregs.gp_ecx;
		return_state->ics_gpregs.gp_eax = state->ucs_gpregs.gp_eax;
		irregs_wrflags(&return_state->ics_irregs_k, eflags);
		irregs_wrip(&return_state->ics_irregs_k, state->ucs_eip);
		return_state->ics_irregs_u.ir_esp = state->ucs_gpregs.gp_esp;
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
	return kernel_debugtrap_r_icpustate(return_state,
	                                    trapno,
	                                    regs ? trap_register_text
	                                         : NULL);
}


#ifdef __x86_64__
PRIVATE struct icpustate *FCALL
sys_debugtrap_rpc64(void *UNUSED(arg), struct icpustate *__restrict state,
                    unsigned int reason, struct rpc_syscall_info const *sc_info) {
	if (reason == TASK_RPC_REASON_SYSCALL) {
		state = sys_debugtrap64_impl(state,
		                             (USER UNCHECKED struct ucpustate64 const *)sc_info->rsi_args[2],
		                             (syscall_ulong_t)sc_info->rsi_args[0],
		                             (USER UNCHECKED struct debug_trap_register64 const *)sc_info->rsi_args[1]);
	}
	return state;
}
#endif /* __x86_64__ */

PRIVATE struct icpustate *FCALL
sys_debugtrap_rpc32(void *UNUSED(arg), struct icpustate *__restrict state,
                    unsigned int reason, struct rpc_syscall_info const *sc_info) {
	if (reason == TASK_RPC_REASON_SYSCALL) {
		state = sys_debugtrap32_impl(state,
		                             (USER UNCHECKED struct ucpustate32 const *)sc_info->rsi_args[2],
		                             (syscall_ulong_t)sc_info->rsi_args[0],
		                             (USER UNCHECKED struct debug_trap_register32 const *)sc_info->rsi_args[1]);
	}
	return state;
}


DEFINE_SYSCALL3(errno_t, debugtrap,
                USER UNCHECKED struct ucpustate const *, state,
                syscall_ulong_t, trapno,
                USER UNCHECKED struct debug_trap_register const *, regs) {
	(void)state;
	(void)trapno;
	(void)regs;
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


#ifdef __x86_64__
DEFINE_SYSCALL32_3(errno_t, debugtrap,
                   USER UNCHECKED struct ucpustate const *, state,
                   syscall_ulong_t, trapno,
                   USER UNCHECKED struct debug_trap_register const *, regs) {
	(void)state;
	(void)trapno;
	(void)regs;
	if (kernel_debugtrap_enabled()) {
		task_schedule_user_rpc(THIS_TASK,
		                       &sys_debugtrap_rpc32,
		                       NULL,
		                       TASK_RPC_FHIGHPRIO |
		                       TASK_USER_RPC_FINTR,
		                       NULL,
		                       GFP_NORMAL);
	}
	return -ENOENT;
}
#endif /* __x86_64__ */


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGTRAP_C */
