/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_REGISTER_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_REGISTER_C 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_DEBUGGER
#include <debugger/hook.h>
#include <debugger/rt.h>
#include <kernel/vm.h>
#include <kernel/x86/breakpoint.h>
#include <sched/scheduler.h>

#include <hybrid/host.h>
#include <hybrid/unaligned.h>

#include <asm/cpu-flags.h>
#include <asm/registers-compat.h>
#include <asm/registers.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <assert.h>
#include <string.h>

#include <libcpustate/register.h>
#include <libunwind/arch-register.h>
#include <libunwind/cfi.h>

DECL_BEGIN

INTERN ATTR_DBGBSS struct fcpustate x86_dbg_origstate = {};
INTERN ATTR_DBGBSS struct fcpustate x86_dbg_viewstate = {};

/* [0..1] The thread who's view state is currently cached
 *        in `x86_dbg_viewstate' and `x86_dbg_origstate' */
INTERN ATTR_DBGBSS struct task *x86_dbg_viewthread = NULL;

/* Convert `x86_dbg_trapstate' into an fcpustate. */
PRIVATE ATTR_DBGTEXT void
NOTHROW(KCALL get_fcpustate_from_trapstate)(struct fcpustate *__restrict result) {
	switch (x86_dbg_trapstatekind) {

	case X86_DBG_STATEKIND_FCPU:
		memcpy(result, x86_dbg_trapstate, sizeof(struct fcpustate));
		break;

	case X86_DBG_STATEKIND_UCPU:
		memcpy(result, &x86_dbg_exitstate, sizeof(struct fcpustate));
		fcpustate_assign_ucpustate(result, (struct ucpustate const *)x86_dbg_trapstate);
		break;

	case X86_DBG_STATEKIND_LCPU:
		memcpy(result, &x86_dbg_exitstate, sizeof(struct fcpustate));
		fcpustate_assign_lcpustate(result, (struct lcpustate const *)x86_dbg_trapstate);
		break;

	case X86_DBG_STATEKIND_KCPU:
		memcpy(result, &x86_dbg_exitstate, sizeof(struct fcpustate));
		fcpustate_assign_kcpustate(result, (struct kcpustate const *)x86_dbg_trapstate);
		break;

	case X86_DBG_STATEKIND_ICPU:
		memcpy(result, &x86_dbg_exitstate, sizeof(struct fcpustate));
		fcpustate_assign_icpustate(result, (struct icpustate const *)x86_dbg_trapstate);
		break;

	case X86_DBG_STATEKIND_SCPU:
		memcpy(result, &x86_dbg_exitstate, sizeof(struct fcpustate));
		fcpustate_assign_scpustate(result, (struct scpustate const *)x86_dbg_trapstate);
		break;

	default:
		memcpy(result, &x86_dbg_exitstate, sizeof(struct fcpustate));
		break;
	}
}

/* Assign the given `struct fcpustate' to `x86_dbg_trapstate', and let
 * registers not defined inside of it ripple down to `x86_dbg_exitstate' */
PRIVATE ATTR_DBGTEXT void
NOTHROW(KCALL set_trapstate_from_fcpustate)(struct fcpustate const *__restrict state) {
	switch (x86_dbg_trapstatekind) {
	case X86_DBG_STATEKIND_FCPU:
		memcpy((struct fcpustate *)x86_dbg_trapstate, state, sizeof(struct fcpustate));
		return;

	case X86_DBG_STATEKIND_UCPU:
		fcpustate_to_ucpustate(state, (struct ucpustate *)x86_dbg_trapstate);
		break;

	case X86_DBG_STATEKIND_LCPU:
		fcpustate_to_lcpustate(state, (struct lcpustate *)x86_dbg_trapstate);
#ifdef __x86_64__
		/* Restore all registers except for `%r15', `%r14', `%r13', `%r12', ``rebp', `%rsp', `%rbx', `%rip' */
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_pdi = state->fcs_gpregs.gp_pdi;
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_psi = state->fcs_gpregs.gp_psi;
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_r11 = state->fcs_gpregs.gp_r11;
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_r10 = state->fcs_gpregs.gp_r10;
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_r9  = state->fcs_gpregs.gp_r9;
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_r8  = state->fcs_gpregs.gp_r8;
		x86_dbg_exitstate.de_state.fcs_sgbase = state->fcs_sgbase;
#else /* __x86_64__ */
		/* Restore all registers except for `%edi', `%esi', `%ebp', `%esp', `%ebx', `%eip' */
#endif /* !__x86_64__ */
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_pax = state->fcs_gpregs.gp_pax;
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_pbx = state->fcs_gpregs.gp_pbx;
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_pdx = state->fcs_gpregs.gp_pdx;
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_pcx = state->fcs_gpregs.gp_pcx;
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_pax = state->fcs_gpregs.gp_pax;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_es  = state->fcs_sgregs.sg_es;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_cs  = state->fcs_sgregs.sg_cs;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_ss  = state->fcs_sgregs.sg_ss;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_ds  = state->fcs_sgregs.sg_ds;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_fs  = state->fcs_sgregs.sg_fs;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_gs  = state->fcs_sgregs.sg_gs;
		x86_dbg_exitstate.de_state.fcs_pflags        = state->fcs_pflags;
		break;

	case X86_DBG_STATEKIND_KCPU:
		fcpustate_to_kcpustate(state, (struct kcpustate *)x86_dbg_trapstate);
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_es  = state->fcs_sgregs.sg_es;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_cs  = state->fcs_sgregs.sg_cs;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_ss  = state->fcs_sgregs.sg_ss;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_ds  = state->fcs_sgregs.sg_ds;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_fs  = state->fcs_sgregs.sg_fs;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_gs  = state->fcs_sgregs.sg_gs;
		break;

	case X86_DBG_STATEKIND_ICPU:
		x86_dbg_trapstate = fcpustate_to_icpustate_p(state, (struct icpustate *)x86_dbg_trapstate);
#ifdef __x86_64__
		x86_dbg_exitstate.de_state.fcs_sgbase       = state->fcs_sgbase;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_es = state->fcs_sgregs.sg_es;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_ds = state->fcs_sgregs.sg_ds;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_fs = state->fcs_sgregs.sg_fs;
#endif /* __x86_64__ */
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_gs = state->fcs_sgregs.sg_gs;
		break;

	case X86_DBG_STATEKIND_SCPU:
		x86_dbg_trapstate = fcpustate_to_scpustate_p(state, (struct scpustate *)x86_dbg_trapstate);
		break;

	default:
		/* Set the whole exit state. */
		memcpy(&x86_dbg_exitstate, state, sizeof(struct fcpustate));
		return;
	}
	/* These registers are never present in trap states other than `X86_DBG_STATEKIND_FCPU'.
	 * As such, changes to the values of these registers must cascade down to the debugger
	 * exit state. */
	x86_dbg_exitstate.de_state.fcs_sgregs.sg_tr  = state->fcs_sgregs.sg_tr16;
	x86_dbg_exitstate.de_state.fcs_sgregs.sg_ldt = state->fcs_sgregs.sg_ldt16;
	x86_dbg_exitstate.de_state.fcs_coregs        = state->fcs_coregs;
	x86_dbg_exitstate.de_state.fcs_drregs        = state->fcs_drregs;
	x86_dbg_exitstate.de_state.fcs_gdt           = state->fcs_gdt;
	x86_dbg_exitstate.de_state.fcs_idt           = state->fcs_idt;
	return;
}


#ifdef __x86_64__
/* Try to get/set the `%kernel_gs.base' register of `dbg_current'
 * Note that doing this is only possible for `THIS_TASK', as well as
 * the current thread of another CPU. All other threads have an implicit
 * `%kernel_gs.base' register value set to the address of their `struct task'
 * structure, which is non-relocatable. */
PRIVATE ATTR_DBGTEXT bool
NOTHROW(KCALL get_dbg_current_kernel_gs_base)(u64 *__restrict presult) {
	if (!x86_dbg_viewthread)
		return false;
	if (dbg_current == THIS_TASK) {
		/* Assign registers to the trap state, and let
		 * undefined registers ripple down to the exit state. */
		*presult = x86_dbg_exitstate.de_kernel_gsbase;
		return true;
	}
#ifndef CONFIG_NO_SMP
	else if (dbg_current->t_cpu &&
	         FORCPU(dbg_current->t_cpu, thiscpu_sched_current) == dbg_current) {
		unsigned int cpuid;
		struct x86_dbg_cpuammend *ammend;
		/* The current thread of a different CPU. */
		cpuid  = dbg_current->t_cpu->c_id;
		assert(cpuid < COMPILER_LENOF(x86_dbg_hostbackup.dhs_cpus));
		if (x86_dbg_hostbackup.dhs_cpus[cpuid].dcs_istate) {
			ammend = x86_dbg_hostbackup.dhs_cpus[cpuid].dcs_iammend;
			assert(ammend);
			assert(ammend->dca_cpu == dbg_current->t_cpu);
			assert(ammend->dca_thread == dbg_current);
			*presult = ammend->dca_kgsbase;
			return true;
		}
	}
#endif /* !CONFIG_NO_SMP */
	return false;
}
PRIVATE ATTR_DBGTEXT bool
NOTHROW(KCALL set_dbg_current_kernel_gs_base)(u64 value) {
	if (!x86_dbg_viewthread)
		return false;
	if (dbg_current == THIS_TASK) {
		/* Assign registers to the trap state, and let
		 * undefined registers ripple down to the exit state. */
		x86_dbg_exitstate.de_kernel_gsbase = value;
		return true;
	}
#ifndef CONFIG_NO_SMP
	else if (dbg_current->t_cpu &&
	         FORCPU(dbg_current->t_cpu, thiscpu_sched_current) == dbg_current) {
		unsigned int cpuid;
		struct x86_dbg_cpuammend *ammend;
		/* The current thread of a different CPU. */
		cpuid  = dbg_current->t_cpu->c_id;
		assert(cpuid < COMPILER_LENOF(x86_dbg_hostbackup.dhs_cpus));
		if (x86_dbg_hostbackup.dhs_cpus[cpuid].dcs_istate) {
			ammend = x86_dbg_hostbackup.dhs_cpus[cpuid].dcs_iammend;
			assert(ammend);
			assert(ammend->dca_cpu == dbg_current->t_cpu);
			assert(ammend->dca_thread == dbg_current);
			ammend->dca_kgsbase = value;
			return true;
		}
	}
#endif /* !CONFIG_NO_SMP */
	return false;
}
#endif /* __x86_64__ */

/* Write the contents of `x86_dbg_origstate', into the
 * state to-be loaded by `x86_dbg_viewthread' */
PRIVATE ATTR_DBGTEXT void
NOTHROW(KCALL saveorig)(void) {
	/* Special case: If no thread is being viewed, then we can't save anything. */
	if (!x86_dbg_viewthread)
		return;
	/* Special case: If the current thread has changed, the we mustn't write back changes.
	 *               Instead, we must discard the cache in its entirety. */
	if (x86_dbg_viewthread != dbg_current) {
		x86_dbg_viewthread = NULL;
		return;
	}
	if (dbg_current == THIS_TASK) {
		/* Assign registers to the trap state, and let
		 * undefined registers ripple down to the exit state. */
		set_trapstate_from_fcpustate(&x86_dbg_origstate);
#ifndef CONFIG_NO_SMP
	} else if (dbg_current->t_cpu &&
	           FORCPU(dbg_current->t_cpu, thiscpu_sched_current) == dbg_current) {
		unsigned int cpuid;
		struct icpustate *ist;
		struct x86_dbg_cpuammend *ammend;
		/* The current thread of a different CPU. */
		cpuid  = dbg_current->t_cpu->c_id;
		assert(cpuid < COMPILER_LENOF(x86_dbg_hostbackup.dhs_cpus));
		ist = x86_dbg_hostbackup.dhs_cpus[cpuid].dcs_istate;
		if (!ist) /* The CPU wasn't suspended, because it wasn't online */
			goto do_normal_unscheduled_thread;
		ammend = x86_dbg_hostbackup.dhs_cpus[cpuid].dcs_iammend;
		assert(ammend);
		assert(ammend->dca_cpu == dbg_current->t_cpu);
		assert(ammend->dca_thread == dbg_current);
		ammend->dca_coregs = x86_dbg_origstate.fcs_coregs;
		ammend->dca_drregs = x86_dbg_origstate.fcs_drregs;
		ammend->dca_gdt    = x86_dbg_origstate.fcs_gdt;
		ammend->dca_idt    = x86_dbg_origstate.fcs_idt;

		/* Construct a new icpustate for the thread to continue running under. */
		ist = fcpustate_to_icpustate_p(&x86_dbg_origstate,
		                               (byte_t *)ist + icpustate_sizeof(ist));

#ifdef __x86_64__
		ammend->dca_sgbase       = x86_dbg_origstate.fcs_sgbase;
		ammend->dca_sgregs.sg_es = x86_dbg_origstate.fcs_sgregs.sg_es16;
		ammend->dca_sgregs.sg_ds = x86_dbg_origstate.fcs_sgregs.sg_ds16;
		ammend->dca_sgregs.sg_fs = x86_dbg_origstate.fcs_sgregs.sg_fs16;
		ammend->dca_sgregs.sg_gs = x86_dbg_origstate.fcs_sgregs.sg_gs16;
#else /* __x86_64__ */
		if (!(x86_dbg_origstate.fcs_pflags & EFLAGS_VM)) {
			ammend->dca_gs = x86_dbg_origstate.fcs_sgregs.sg_gs;
			ammend->dca_ss = x86_dbg_origstate.fcs_sgregs.sg_ss;
		}
#endif /* !__x86_64__ */
		ammend->dca_tr  = x86_dbg_origstate.fcs_sgregs.sg_tr16;
		ammend->dca_ldt = x86_dbg_origstate.fcs_sgregs.sg_ldt16;
#endif /* !CONFIG_NO_SMP */
	} else {
		/* Some different thread that is not being scheduled at the moment. */
		struct scpustate *sst;
#ifndef CONFIG_NO_SMP
do_normal_unscheduled_thread:
#endif /* !CONFIG_NO_SMP */
		/* Re-construct the thread's scheduler CPU state. */
		sst = FORTASK(dbg_current, this_sstate);
		if (sst) {
			sst = (struct scpustate *)((byte_t *) + scpustate_sizeof(sst));
			sst = fcpustate_to_scpustate_p(&x86_dbg_origstate, sst);
			FORTASK(dbg_current, this_sstate) = sst;
		}
		/* Fill in missing registers. */
#ifndef CONFIG_NO_SMP
		if (dbg_current->t_cpu != THIS_CPU) {
			unsigned int cpuid;
			if unlikely(!dbg_current->t_cpu)
				goto nocpu;
			cpuid = dbg_current->t_cpu->c_id;
			if unlikely(cpuid >= COMPILER_LENOF(x86_dbg_hostbackup.dhs_cpus))
				goto nocpu;
			if (x86_dbg_hostbackup.dhs_cpus[cpuid].dcs_istate) {
				struct x86_dbg_cpuammend *ammend;
				ammend = x86_dbg_hostbackup.dhs_cpus[cpuid].dcs_iammend;
				assert(ammend);
				ammend->dca_tr     = x86_dbg_origstate.fcs_sgregs.sg_tr16;
				ammend->dca_ldt    = x86_dbg_origstate.fcs_sgregs.sg_ldt16;
				ammend->dca_coregs = x86_dbg_origstate.fcs_coregs;
				ammend->dca_drregs = x86_dbg_origstate.fcs_drregs;
				ammend->dca_gdt    = x86_dbg_origstate.fcs_gdt;
				ammend->dca_idt    = x86_dbg_origstate.fcs_idt;
			} else {
nocpu:
				/* The thread may not have been started, yet.
				 * In this case, discard extended register information. */
				;
			}
		} else
#endif /* !CONFIG_NO_SMP */
		{
			/* The target thread is running on our own CPU.
			 * -> Use registers from `x86_dbg_exitstate' */
			x86_dbg_exitstate.de_state.fcs_sgregs.sg_tr  = x86_dbg_origstate.fcs_sgregs.sg_tr16;
			x86_dbg_exitstate.de_state.fcs_sgregs.sg_ldt = x86_dbg_origstate.fcs_sgregs.sg_ldt16;
			x86_dbg_exitstate.de_state.fcs_coregs        = x86_dbg_origstate.fcs_coregs;
			x86_dbg_exitstate.de_state.fcs_drregs        = x86_dbg_origstate.fcs_drregs;
			x86_dbg_exitstate.de_state.fcs_gdt           = x86_dbg_origstate.fcs_gdt;
			x86_dbg_exitstate.de_state.fcs_idt           = x86_dbg_origstate.fcs_idt;
		}

	}
	/* Account for register overrides related to some thread-local components. */
	if (dbg_current->t_vm) {
		struct vm *v = dbg_current->t_vm;
		v->v_pdir_phys = (PHYS pagedir_t *)x86_dbg_origstate.fcs_coregs.co_cr3;
		FORVM(v, thisvm_x86_dr0) = x86_dbg_origstate.fcs_drregs.dr_dr0;
		FORVM(v, thisvm_x86_dr1) = x86_dbg_origstate.fcs_drregs.dr_dr1;
		FORVM(v, thisvm_x86_dr2) = x86_dbg_origstate.fcs_drregs.dr_dr2;
		FORVM(v, thisvm_x86_dr3) = x86_dbg_origstate.fcs_drregs.dr_dr3;
		FORVM(v, thisvm_x86_dr7) = x86_dbg_origstate.fcs_drregs.dr_dr7;
	}
}

/* Update the current thread orig/view CPU state. */
PRIVATE ATTR_DBGTEXT void
NOTHROW(KCALL loadview)(void) {
	if (x86_dbg_viewthread != dbg_current) {
		if (!dbg_current) {
			/* Special case: no thread loaded. */
			memset(&x86_dbg_origstate, 0, sizeof(x86_dbg_origstate));
		} else if (dbg_current == THIS_TASK) {
			/* DBG_REGLEVEL_ORIG = DBG_REGLEVEL_TRAP */
			get_fcpustate_from_trapstate(&x86_dbg_origstate);
#ifndef CONFIG_NO_SMP
		} else if (dbg_current->t_cpu &&
		           FORCPU(dbg_current->t_cpu, thiscpu_sched_current) == dbg_current) {
			unsigned int cpuid;
			struct icpustate *ist;
			struct x86_dbg_cpuammend *ammend;
			uintptr_t psp;
			/* The current thread of a different CPU. */
			cpuid  = dbg_current->t_cpu->c_id;
			assert(cpuid < COMPILER_LENOF(x86_dbg_hostbackup.dhs_cpus));
			ist = x86_dbg_hostbackup.dhs_cpus[cpuid].dcs_istate;
			if (!ist) /* The CPU wasn't suspended, because it wasn't online */
				goto do_normal_unscheduled_thread;
			ammend = x86_dbg_hostbackup.dhs_cpus[cpuid].dcs_iammend;
			assert(ammend);
			assert(ammend->dca_cpu == dbg_current->t_cpu);
			assert(ammend->dca_thread == dbg_current);
			x86_dbg_origstate.fcs_coregs       = ammend->dca_coregs;
			x86_dbg_origstate.fcs_drregs       = ammend->dca_drregs;
			x86_dbg_origstate.fcs_gdt          = ammend->dca_gdt;
			x86_dbg_origstate.fcs_idt          = ammend->dca_idt;
			x86_dbg_origstate.fcs_pip          = ist->ics_irregs.ir_pip;
			x86_dbg_origstate.fcs_pflags       = ist->ics_irregs.ir_pflags;
			x86_dbg_origstate.fcs_sgregs.sg_cs = ist->ics_irregs.ir_cs16;
#ifdef __x86_64__
			psp                                = ist->ics_irregs.ir_psp;
			x86_dbg_origstate.fcs_sgregs.sg_ss = ist->ics_irregs.ir_ss16;
#endif /* __x86_64__ */
#if 0 /* Don't bend the truth when it comes to IRET tails. */
			if (x86_dbg_origstate.fcs_pip == (uintptr_t)&x86_rpc_user_redirection) {
				struct irregs_kernel *iret;
				iret = &FORTASK(ammend->dca_thread, this_x86_rpc_redirection_iret);
				x86_dbg_origstate.fcs_pip          = iret->ir_pip;
				x86_dbg_origstate.fcs_pflags       = iret->ir_pflags;
				x86_dbg_origstate.fcs_sgregs.sg_cs = iret->ir_cs16;
#ifdef __x86_64__
				psp                                = iret->ir_psp;
				x86_dbg_origstate.fcs_sgregs.sg_ss = iret->ir_ss16;
#endif /* __x86_64__ */
			}
#endif
#ifdef __x86_64__
			x86_dbg_origstate.fcs_sgbase       = ammend->dca_sgbase;
			x86_dbg_origstate.fcs_sgregs.sg_es = ammend->dca_sgregs.sg_es16;
			x86_dbg_origstate.fcs_sgregs.sg_ds = ammend->dca_sgregs.sg_ds16;
			x86_dbg_origstate.fcs_sgregs.sg_fs = ammend->dca_sgregs.sg_fs16;
			x86_dbg_origstate.fcs_sgregs.sg_gs = ammend->dca_sgregs.sg_gs16;
#else /* __x86_64__ */
			if (x86_dbg_origstate.fcs_pflags & EFLAGS_VM) {
				/* Vm86 IRET tail */
				x86_dbg_origstate.fcs_sgregs.sg_es = ist->ics_irregs_v.ir_es16;
				x86_dbg_origstate.fcs_sgregs.sg_ds = ist->ics_irregs_v.ir_ds16;
				x86_dbg_origstate.fcs_sgregs.sg_fs = ist->ics_irregs_v.ir_fs16;
				x86_dbg_origstate.fcs_sgregs.sg_gs = ist->ics_irregs_v.ir_gs16;
				x86_dbg_origstate.fcs_sgregs.sg_ss = ist->ics_irregs_v.ir_ss16;
				psp                                = ist->ics_irregs_v.ir_psp;
			} else {
				x86_dbg_origstate.fcs_sgregs.sg_es = ist->ics_es16;
				x86_dbg_origstate.fcs_sgregs.sg_ds = ist->ics_ds16;
				x86_dbg_origstate.fcs_sgregs.sg_fs = ist->ics_fs16;
				x86_dbg_origstate.fcs_sgregs.sg_gs = ammend->dca_gs;
				x86_dbg_origstate.fcs_sgregs.sg_ss = ammend->dca_ss;
				if (x86_dbg_origstate.fcs_sgregs.sg_cs16 & 3) {
					/* User-space IRET tail */
					psp = ist->ics_irregs_u.ir_psp;
				} else {
					/* Kernel-space IRET tail */
					psp = irregs_getkernelpsp(&ist->ics_irregs);
				}
			}
#endif /* !__x86_64__ */
			x86_dbg_origstate.fcs_sgregs.sg_tr  = ammend->dca_tr;
			x86_dbg_origstate.fcs_sgregs.sg_ldt = ammend->dca_ldt;
#ifdef __x86_64__
			gpregsnsp_to_gpregs(&ist->ics_gpregs, &x86_dbg_origstate.fcs_gpregs, psp);
#else /* __x86_64__ */
			memcpy(&x86_dbg_origstate.fcs_gpregs, &ist->ics_gpregs, sizeof(struct gpregs));
			x86_dbg_origstate.fcs_gpregs.gp_psp = psp;
#endif /* !__x86_64__ */
#endif /* !CONFIG_NO_SMP */
		} else {
#ifndef CONFIG_NO_SMP
do_normal_unscheduled_thread:
#endif /* !CONFIG_NO_SMP */
			/* Some different thread that is not being scheduled at the moment. */
			if (FORTASK(dbg_current, this_sstate)) {
				fcpustate_assign_scpustate(&x86_dbg_origstate,
				                           FORTASK(dbg_current, this_sstate));
			} else {
				memset(&x86_dbg_origstate, 0, sizeof(x86_dbg_origstate));
			}
			/* OK: [x86_dbg_origstate.fcs_sgbase]
			 * OK: x86_dbg_origstate.fcs_gpregs
			 * OK: x86_dbg_origstate.fcs_eip
			 * OK: x86_dbg_origstate.fcs_eflags
			 * OK: x86_dbg_origstate.fcs_sgregs.sg_cs
			 * OK: x86_dbg_origstate.fcs_sgregs.sg_ss
			 * OK: x86_dbg_origstate.fcs_sgregs.sg_ds
			 * OK: x86_dbg_origstate.fcs_sgregs.sg_es
			 * OK: x86_dbg_origstate.fcs_sgregs.sg_fs
			 * OK: x86_dbg_origstate.fcs_sgregs.sg_gs */
			/* Fill in missing registers. */
#ifndef CONFIG_NO_SMP
			if (dbg_current->t_cpu != THIS_CPU) {
				unsigned int cpuid;
				if unlikely(!dbg_current->t_cpu)
					goto nocpu;
				cpuid = dbg_current->t_cpu->c_id;
				if unlikely(cpuid >= COMPILER_LENOF(x86_dbg_hostbackup.dhs_cpus))
					goto nocpu;
				if (x86_dbg_hostbackup.dhs_cpus[cpuid].dcs_istate) {
					struct x86_dbg_cpuammend *ammend;
					ammend = x86_dbg_hostbackup.dhs_cpus[cpuid].dcs_iammend;
					assert(ammend);
					x86_dbg_origstate.fcs_sgregs.sg_tr  = ammend->dca_tr;
					x86_dbg_origstate.fcs_sgregs.sg_ldt = ammend->dca_ldt;
					x86_dbg_origstate.fcs_coregs        = ammend->dca_coregs;
					x86_dbg_origstate.fcs_drregs        = ammend->dca_drregs;
					x86_dbg_origstate.fcs_gdt           = ammend->dca_gdt;
					x86_dbg_origstate.fcs_idt           = ammend->dca_idt;
				} else {
nocpu:
					/* The thread may not have been started, yet.
					 * Fill in generic register information. */
					x86_dbg_origstate.fcs_sgregs.sg_tr  = SEGMENT_CPU_TSS;
					x86_dbg_origstate.fcs_sgregs.sg_ldt = SEGMENT_CPU_LDT;
					x86_dbg_origstate.fcs_coregs        = x86_dbg_exitstate.de_state.fcs_coregs;
					x86_dbg_origstate.fcs_drregs        = x86_dbg_exitstate.de_state.fcs_drregs;
					x86_dbg_origstate.fcs_gdt           = x86_dbg_exitstate.de_state.fcs_gdt;
					x86_dbg_origstate.fcs_idt           = x86_dbg_exitstate.de_state.fcs_idt;
				}
			} else
#endif /* !CONFIG_NO_SMP */
			{
				/* The target thread is running on our own CPU.
				 * -> Use registers from `x86_dbg_exitstate' */
				x86_dbg_origstate.fcs_sgregs.sg_tr  = x86_dbg_exitstate.de_state.fcs_sgregs.sg_tr16;
				x86_dbg_origstate.fcs_sgregs.sg_ldt = x86_dbg_exitstate.de_state.fcs_sgregs.sg_ldt16;
				x86_dbg_origstate.fcs_coregs        = x86_dbg_exitstate.de_state.fcs_coregs;
				x86_dbg_origstate.fcs_drregs        = x86_dbg_exitstate.de_state.fcs_drregs;
				x86_dbg_origstate.fcs_gdt           = x86_dbg_exitstate.de_state.fcs_gdt;
				x86_dbg_origstate.fcs_idt           = x86_dbg_exitstate.de_state.fcs_idt;
			}
			/* Account for register overrides related to some thread-local components. */
			if (dbg_current->t_vm) {
				struct vm *v = dbg_current->t_vm;
				x86_dbg_origstate.fcs_coregs.co_cr3 = (uintptr_t)v->v_pdir_phys;
				x86_dbg_origstate.fcs_drregs.dr_dr0 = FORVM(v, thisvm_x86_dr0);
				x86_dbg_origstate.fcs_drregs.dr_dr1 = FORVM(v, thisvm_x86_dr1);
				x86_dbg_origstate.fcs_drregs.dr_dr2 = FORVM(v, thisvm_x86_dr2);
				x86_dbg_origstate.fcs_drregs.dr_dr3 = FORVM(v, thisvm_x86_dr3);
				x86_dbg_origstate.fcs_drregs.dr_dr7 = FORVM(v, thisvm_x86_dr7);
			}
		}
		memcpy(&x86_dbg_viewstate, &x86_dbg_origstate, sizeof(struct fcpustate));
		x86_dbg_viewthread = dbg_current;
	}
}

#define VIEWSTATE(level)                                   \
	((unsigned int)(uintptr_t)(level) == DBG_REGLEVEL_ORIG \
	 ? &x86_dbg_origstate                                  \
	 : &x86_dbg_viewstate)

/* Get/Set debugger register for some given level.
 * NOTE: These functions are written to be compatible with `unwind_getreg_t' / `unwind_setreg_t'
 * @param: arg: One of `DBG_REGLEVEL_*', cast as `(void *)(uintptr_t)DBG_REGLEVEL_*' */
PUBLIC ATTR_DBGTEXT unsigned int
NOTHROW(LIBUNWIND_CC dbg_getreg)(/*uintptr_t level*/ void const *arg,
                                 uintptr_half_t cfi_regno,
                                 void *__restrict buf) {
	unsigned int error;
	switch ((unsigned int)(uintptr_t)arg) {

	case DBG_REGLEVEL_EXIT:
	case DBG_REGLEVEL_TRAP:
		if (dbg_current == THIS_TASK) {
			if ((unsigned int)(uintptr_t)arg == DBG_REGLEVEL_TRAP) {
				/* NOTE: Use exclusive register access so that the exit state is used as
				 *       fall-back, rather than the current register state being used! */
				switch (x86_dbg_trapstatekind) {

				case X86_DBG_STATEKIND_FCPU:
					error = unwind_getreg_fcpustate_exclusive(x86_dbg_trapstate, cfi_regno, buf);
					break;

				case X86_DBG_STATEKIND_UCPU:
					error = unwind_getreg_ucpustate_exclusive(x86_dbg_trapstate, cfi_regno, buf);
					break;

				case X86_DBG_STATEKIND_LCPU:
					error = unwind_getreg_lcpustate_exclusive(x86_dbg_trapstate, cfi_regno, buf);
					break;

				case X86_DBG_STATEKIND_KCPU:
					error = unwind_getreg_kcpustate_exclusive(x86_dbg_trapstate, cfi_regno, buf);
					break;

				case X86_DBG_STATEKIND_ICPU:
					error = unwind_getreg_icpustate_exclusive(x86_dbg_trapstate, cfi_regno, buf);
					break;

				case X86_DBG_STATEKIND_SCPU:
					error = unwind_getreg_scpustate_exclusive(x86_dbg_trapstate, cfi_regno, buf);
					break;

				default:
					error = UNWIND_INVALID_REGISTER;
					break;
				}
				if (error == UNWIND_SUCCESS)
					goto done;
			}
			/* Access the exit CPU state. */
			return unwind_getreg_fcpustate(&x86_dbg_exitstate, cfi_regno, buf);
		}
		ATTR_FALLTHROUGH
	case DBG_REGLEVEL_ORIG:
	case DBG_REGLEVEL_VIEW:
		loadview();
		return unwind_getreg_fcpustate(VIEWSTATE(arg), cfi_regno, buf);

	default:
		break;
	}
	return UNWIND_INVALID_REGISTER;
done:
	return error;
}

PUBLIC ATTR_DBGTEXT unsigned int
NOTHROW(LIBUNWIND_CC dbg_setreg)(/*uintptr_t level*/ void *arg,
                                 uintptr_half_t cfi_regno,
                                 void const *__restrict buf) {
	unsigned int error;
	switch ((unsigned int)(uintptr_t)arg) {

	case DBG_REGLEVEL_EXIT:
	case DBG_REGLEVEL_TRAP:
		if (dbg_current == THIS_TASK) {
			if ((unsigned int)(uintptr_t)arg == DBG_REGLEVEL_TRAP) {
				/* NOTE: Use exclusive register access so that the exit state is used as
				 *       fall-back, rather than the current register state being used! */
				switch (x86_dbg_trapstatekind) {

				case X86_DBG_STATEKIND_FCPU:
					error = unwind_setreg_fcpustate_exclusive(x86_dbg_trapstate, cfi_regno, buf);
					break;

				case X86_DBG_STATEKIND_UCPU:
					error = unwind_setreg_ucpustate_exclusive(x86_dbg_trapstate, cfi_regno, buf);
					break;

				case X86_DBG_STATEKIND_LCPU:
					error = unwind_setreg_lcpustate_exclusive(x86_dbg_trapstate, cfi_regno, buf);
					break;

				case X86_DBG_STATEKIND_KCPU:
					error = unwind_setreg_kcpustate_exclusive(x86_dbg_trapstate, cfi_regno, buf);
					break;

#ifdef __x86_64__
				case X86_DBG_STATEKIND_ICPU:
					error = unwind_setreg_icpustate_exclusive(x86_dbg_trapstate, cfi_regno, buf);
					break;

				case X86_DBG_STATEKIND_SCPU:
					error = unwind_setreg_scpustate_exclusive(x86_dbg_trapstate, cfi_regno, buf);
					break;
#else /* __x86_64__ */
				case X86_DBG_STATEKIND_ICPU:
					error = unwind_setreg_icpustate_exclusive_p(&x86_dbg_trapstate, cfi_regno, buf);
					break;

				case X86_DBG_STATEKIND_SCPU:
					error = unwind_setreg_scpustate_exclusive_p(&x86_dbg_trapstate, cfi_regno, buf);
					break;
#endif /* !__x86_64__ */

				default:
					error = UNWIND_INVALID_REGISTER;
					break;
				}
				if (error == UNWIND_SUCCESS)
					goto done;
			}
			/* Access the exit CPU state. */
			return unwind_setreg_fcpustate(&x86_dbg_exitstate, cfi_regno, buf);
		}
		ATTR_FALLTHROUGH
	case DBG_REGLEVEL_ORIG:
	case DBG_REGLEVEL_VIEW:
		loadview();
		error = unwind_setreg_fcpustate(VIEWSTATE(arg), cfi_regno, buf);
		if (error == UNWIND_SUCCESS) {
			if ((unsigned int)(uintptr_t)arg == DBG_REGLEVEL_ORIG)
				saveorig();
		}
		goto done;

	default:
		break;
	}
	return UNWIND_INVALID_REGISTER;
done:
	return error;
}

/* Get/set a register, given its ID
 * NOTE: When `return > buflen', then
 *       dbg_getregbyname: The contents of `buf' are undefined.
 *       dbg_setregbyname: The register was not written.
 * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'
 * @param: regno: One of `X86_REGISTER_*' (from <asm/registers.h>) or one of `X86_DBGREGISTER_*'
 * @return: * :   The required buffer size, or 0 when `name' isn't recognized. */
PUBLIC size_t
NOTHROW(KCALL x86_dbg_getregbyid)(unsigned int level, unsigned int regno,
                                  void *__restrict buf, size_t buflen) {
	size_t result;
	switch (level) {

	case DBG_REGLEVEL_EXIT:
	case DBG_REGLEVEL_TRAP:
		if (dbg_current == THIS_TASK) {
			if (level == DBG_REGLEVEL_TRAP) {
				/* NOTE: Use exclusive register access so that the exit state is used as
				 *       fall-back, rather than the current register state being used! */
				switch (x86_dbg_trapstatekind) {

				case X86_DBG_STATEKIND_FCPU:
					result = getreg((struct fcpustate *)x86_dbg_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				case X86_DBG_STATEKIND_UCPU:
					result = getreg((struct ucpustate *)x86_dbg_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				case X86_DBG_STATEKIND_LCPU:
					result = getreg((struct lcpustate *)x86_dbg_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				case X86_DBG_STATEKIND_KCPU:
					result = getreg((struct kcpustate *)x86_dbg_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				case X86_DBG_STATEKIND_ICPU:
					result = getreg((struct icpustate *)x86_dbg_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				case X86_DBG_STATEKIND_SCPU:
					result = getreg((struct scpustate *)x86_dbg_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				default: break;
				}
			}
#ifdef __x86_64__
			if (regno == X86_REGISTER_MISC_KGSBASEL) {
				if (buflen >= 4)
					UNALIGNED_SET32((u32 *)buf, (u32)x86_dbg_exitstate.de_kernel_gsbase);
				return 4;
			}
			if (regno == X86_REGISTER_MISC_KGSBASEQ) {
				if (buflen >= 8)
					UNALIGNED_SET64((u64 *)buf, (u64)x86_dbg_exitstate.de_kernel_gsbase);
				return 8;
			}
#endif /* __x86_64__ */
			/* Access the exit CPU state. */
			return getreg(&x86_dbg_exitstate.de_state, regno, buf, buflen);
		}
		ATTR_FALLTHROUGH
	case DBG_REGLEVEL_ORIG:
	case DBG_REGLEVEL_VIEW:
		loadview();
		result = getreg(VIEWSTATE(level), regno, buf, buflen);
#ifdef __x86_64__
		if (/*level == DBG_REGLEVEL_ORIG &&*/ result == 0) {
			if (regno == X86_REGISTER_MISC_KGSBASEL) {
				u64 temp;
				result = 0;
				if (get_dbg_current_kernel_gs_base(&temp)) {
					result = 4;
					if (buflen >= 4)
						UNALIGNED_SET32((u32 *)buf, temp);
				}
				goto ok;
			}
			if (regno == X86_REGISTER_MISC_KGSBASEQ) {
				u64 temp;
				result = 0;
				if (get_dbg_current_kernel_gs_base(&temp)) {
					result = 8;
					if (buflen >= 8)
						UNALIGNED_SET64((u64 *)buf, temp);
				}
				goto ok;
			}
		}
#endif /* __x86_64__ */
		goto ok;

	default:
		break;
	}
	return 0;
ok:
	return result;
}

PUBLIC size_t
NOTHROW(KCALL x86_dbg_setregbyid)(unsigned int level, unsigned int regno,
                                  void const *__restrict buf, size_t buflen) {
	size_t result;
	switch (level) {

	case DBG_REGLEVEL_EXIT:
	case DBG_REGLEVEL_TRAP:
		if (dbg_current == THIS_TASK) {
			if (level == DBG_REGLEVEL_TRAP) {
				/* NOTE: Use exclusive register access so that the exit state is used as
				 *       fall-back, rather than the current register state being used! */
				switch (x86_dbg_trapstatekind) {

				case X86_DBG_STATEKIND_FCPU:
					result = setreg((struct fcpustate *)x86_dbg_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				case X86_DBG_STATEKIND_UCPU:
					result = setreg((struct ucpustate *)x86_dbg_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				case X86_DBG_STATEKIND_LCPU:
					result = setreg((struct lcpustate *)x86_dbg_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				case X86_DBG_STATEKIND_KCPU:
					result = setreg((struct kcpustate *)x86_dbg_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				case X86_DBG_STATEKIND_ICPU:
#ifdef __x86_64__
					result = setreg((struct icpustate *)x86_dbg_trapstate, regno, buf, buflen);
#else /* __x86_64__ */
					result = setreg((struct icpustate **)&x86_dbg_trapstate, regno, buf, buflen);
#endif /* !__x86_64__ */
					if (result != 0)
						goto ok;
					break;

				case X86_DBG_STATEKIND_SCPU:
#ifdef __x86_64__
					result = setreg((struct scpustate *)x86_dbg_trapstate, regno, buf, buflen);
#else /* __x86_64__ */
					result = setreg((struct scpustate **)&x86_dbg_trapstate, regno, buf, buflen);
#endif /* !__x86_64__ */
					if (result != 0)
						goto ok;
					break;

				default: break;
				}
			}
#ifdef __x86_64__
			if (regno == X86_REGISTER_MISC_KGSBASEL) {
				if (buflen >= 4)
					x86_dbg_exitstate.de_kernel_gsbase = UNALIGNED_GET32((u32 *)buf);
				return 4;
			}
			if (regno == X86_REGISTER_MISC_KGSBASEQ) {
				if (buflen >= 8)
					x86_dbg_exitstate.de_kernel_gsbase = UNALIGNED_GET64((u64 *)buf);
				return 8;
			}
#endif /* __x86_64__ */
			/* Access the exit CPU state. */
			return setreg(&x86_dbg_exitstate.de_state, regno, buf, buflen);
		}
		ATTR_FALLTHROUGH
	case DBG_REGLEVEL_ORIG:
	case DBG_REGLEVEL_VIEW:
		loadview();
		result = setreg(VIEWSTATE(level), regno, buf, buflen);
		if (level == DBG_REGLEVEL_ORIG && result != 0)
			saveorig();
#ifdef __x86_64__
		else if (level == DBG_REGLEVEL_ORIG && result == 0) {
			if (regno == X86_REGISTER_MISC_KGSBASEL) {
				result = 4;
				if (buflen >= 4) {
					if (!set_dbg_current_kernel_gs_base(UNALIGNED_GET32((u32 *)buf)))
						result = 0;
				} else {
					u64 temp;
					if (!get_dbg_current_kernel_gs_base(&temp))
						result = 0;
				}
				goto ok;
			}
			if (regno == X86_REGISTER_MISC_KGSBASEQ) {
				result = 8;
				if (buflen >= 8) {
					if (!set_dbg_current_kernel_gs_base(UNALIGNED_GET64((u64 *)buf)))
						result = 0;
				} else {
					u64 temp;
					if (!get_dbg_current_kernel_gs_base(&temp))
						result = 0;
				}
				goto ok;
			}
		}
#endif /* __x86_64__ */
		goto ok;

	default:
		break;
	}
	return 0;
ok:
	return result;
}

/* Get/set all registers. */
PUBLIC ATTR_DBGTEXT void
NOTHROW(KCALL dbg_getallregs)(unsigned int level,
                              struct fcpustate *__restrict state) {
	switch (level) {

	case DBG_REGLEVEL_EXIT:
	case DBG_REGLEVEL_TRAP:
		if (dbg_current == THIS_TASK) {
			/* Access the exit CPU state. */
			memcpy(state, &x86_dbg_exitstate, sizeof(struct fcpustate));
			if (level == DBG_REGLEVEL_TRAP) {
				/* NOTE: Use exclusive register access so that the exit state is used as
				 *       fall-back, rather than the current register state being used! */
				switch (x86_dbg_trapstatekind) {

				case X86_DBG_STATEKIND_FCPU:
					memcpy(state, (struct fcpustate *)x86_dbg_trapstate, sizeof(struct fcpustate));
					break;

				case X86_DBG_STATEKIND_UCPU:
					fcpustate_assign_ucpustate(state, (struct ucpustate *)x86_dbg_trapstate);
					break;

				case X86_DBG_STATEKIND_LCPU:
					fcpustate_assign_lcpustate(state, (struct lcpustate *)x86_dbg_trapstate);
					break;

				case X86_DBG_STATEKIND_KCPU:
					fcpustate_assign_kcpustate(state, (struct kcpustate *)x86_dbg_trapstate);
					break;

				case X86_DBG_STATEKIND_ICPU:
					fcpustate_assign_icpustate(state, (struct icpustate *)x86_dbg_trapstate);
					break;

				case X86_DBG_STATEKIND_SCPU:
					fcpustate_assign_scpustate(state, (struct scpustate *)x86_dbg_trapstate);
					break;

				default: break;
				}
			}
			return;
		}
		break;
	default:
		break;
	}
	loadview();
	memcpy(state, VIEWSTATE(level),
	       sizeof(struct fcpustate));
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(KCALL dbg_setallregs)(unsigned int level,
                              struct fcpustate const *__restrict state) {
	switch (level) {

	case DBG_REGLEVEL_EXIT:
	case DBG_REGLEVEL_TRAP:
		if (dbg_current == THIS_TASK) {
			/* Access the exit CPU state. */
			if (level == DBG_REGLEVEL_TRAP) {
				/* NOTE: Use exclusive register access so that the exit state is used as
				 *       fall-back, rather than the current register state being used! */
				set_trapstate_from_fcpustate(state);
				return;
			}
			memcpy(&x86_dbg_exitstate, state, sizeof(struct fcpustate));
			return;
		}
		break;
	default:
		break;
	}
	loadview();
	memcpy(VIEWSTATE(level), state,
	       sizeof(struct fcpustate));
	if (level == DBG_REGLEVEL_ORIG)
		saveorig();
}

/* Return the page directory of `dbg_current' */
PUBLIC ATTR_PURE WUNUSED pagedir_phys_t
NOTHROW(KCALL dbg_getpagedir)(void) {
	uintptr_t result;
	result = x86_dbg_getregbyidp(DBG_REGLEVEL_VIEW,
	                             X86_REGISTER_CONTROL_CR3);
	return (pagedir_phys_t)result;
}


/* Get/set a register, given its (arch-specific) name
 * NOTE: When `return > buflen', then
 *       dbg_getregbyname: The contents of `buf' are undefined.
 *       dbg_setregbyname: The register was not written.
 * @return: * : The required buffer size, or 0 when `name' isn't recognized. */
PUBLIC ATTR_DBGTEXT size_t
NOTHROW(KCALL dbg_getregbyname)(unsigned int level, char const *__restrict name,
                                size_t namelen, void *__restrict buf, size_t buflen) {
	size_t result;
	unsigned int nameid;
	nameid = x86_dbg_regfromname(name, namelen);
	result = x86_dbg_getregbyid(level, nameid, buf, buflen);
	return result;
}

PUBLIC ATTR_DBGTEXT size_t
NOTHROW(KCALL dbg_setregbyname)(unsigned int level, char const *__restrict name,
                                size_t namelen, void const *__restrict buf, size_t buflen) {
	size_t result;
	unsigned int nameid;
	nameid = x86_dbg_regfromname(name, namelen);
	result = x86_dbg_setregbyid(level, nameid, buf, buflen);
	return result;
}


/* Get/Set a pointer-sized register, given its ID */
PUBLIC ATTR_PURE WUNUSED uintptr_t
NOTHROW(KCALL x86_dbg_getregbyidp)(unsigned int level,
                                   unsigned int regno) {
	size_t reqlen;
	uintptr_t result;
	reqlen = x86_dbg_getregbyid(level, regno, &result, sizeof(result));
	if (!reqlen || reqlen > sizeof(result))
		return 0; /* Shouldn't happen... */
	if (reqlen < sizeof(result))
		memset((byte_t *)&result + reqlen, 0, sizeof(result) - reqlen);
	return result;
}

PUBLIC bool
NOTHROW(KCALL x86_dbg_setregbyidp)(unsigned int level,
                                   unsigned int regno,
                                   uintptr_t value) {
	size_t reqlen;
	reqlen = x86_dbg_setregbyid(level, regno, &value, sizeof(value));
	if (!reqlen || reqlen > sizeof(value))
		return false;
	return true;
}


/* Check if the register view has been changed. */
PUBLIC ATTR_DBGTEXT ATTR_PURE WUNUSED bool
NOTHROW(FCALL dbg_changedview)(void) {
	loadview();
	return memcmp(&x86_dbg_origstate,
	              &x86_dbg_viewstate,
	              sizeof(struct fcpustate)) != 0;
}


DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_REGISTER_C */
