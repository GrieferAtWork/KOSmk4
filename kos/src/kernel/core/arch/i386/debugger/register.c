/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif(x -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_REGISTER_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_REGISTER_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/hook.h>
#include <debugger/rt.h>
#include <kernel/mman.h>
#include <kernel/x86/breakpoint.h>
#include <sched/scheduler.h>
#include <sched/task.h>

#include <hybrid/host.h>
#include <hybrid/unaligned.h>

#include <asm/cpu-flags.h>
#include <asm/registers-compat.h>
#include <asm/registers.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state-helpers.h>
#include <kos/kernel/cpu-state.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include <libcpustate/register.h>
#include <libunwind/cfi.h>
#include <libunwind/errno.h>
#include <libunwind/register.h>

DECL_BEGIN

INTERN ATTR_DBGBSS struct fcpustate x86_dbg_origstate = {};
INTERN ATTR_DBGBSS struct fcpustate x86_dbg_viewstate = {};

/* [0..1] The thread who's view state is currently cached
 *        in `x86_dbg_viewstate' and `x86_dbg_origstate' */
INTERN ATTR_DBGBSS struct task *x86_dbg_viewthread = NULL;

/* Convert `dbg_rt_trapstate' into an fcpustate. */
PRIVATE ATTR_DBGTEXT void
NOTHROW(KCALL get_fcpustate_from_trapstate)(struct fcpustate *__restrict result) {
	switch (dbg_rt_trapstatekind) {

	case DBG_RT_STATEKIND_FCPU:
		memcpy(result, dbg_rt_trapstate, sizeof(struct fcpustate));
		break;

	case DBG_RT_STATEKIND_UCPU:
		memcpy(result, &x86_dbg_exitstate, sizeof(struct fcpustate));
		fcpustate_assign_ucpustate(result, (struct ucpustate const *)dbg_rt_trapstate);
		break;

	case DBG_RT_STATEKIND_LCPU:
		memcpy(result, &x86_dbg_exitstate, sizeof(struct fcpustate));
		fcpustate_assign_lcpustate(result, (struct lcpustate const *)dbg_rt_trapstate);
		break;

	case DBG_RT_STATEKIND_KCPU:
		memcpy(result, &x86_dbg_exitstate, sizeof(struct fcpustate));
		fcpustate_assign_kcpustate(result, (struct kcpustate const *)dbg_rt_trapstate);
		break;

	case DBG_RT_STATEKIND_ICPU:
		memcpy(result, &x86_dbg_exitstate, sizeof(struct fcpustate));
		fcpustate_assign_icpustate(result, (struct icpustate const *)dbg_rt_trapstate);
		break;

	case DBG_RT_STATEKIND_SCPU:
		memcpy(result, &x86_dbg_exitstate, sizeof(struct fcpustate));
		fcpustate_assign_scpustate(result, (struct scpustate const *)dbg_rt_trapstate);
		break;

	default:
		memcpy(result, &x86_dbg_exitstate, sizeof(struct fcpustate));
		break;
	}
}

/* Assign the given  `struct fcpustate' to  `dbg_rt_trapstate', and  let
 * registers not defined inside of it ripple down to `x86_dbg_exitstate' */
PRIVATE ATTR_DBGTEXT void
NOTHROW(KCALL set_trapstate_from_fcpustate)(struct fcpustate const *__restrict state) {
	switch (dbg_rt_trapstatekind) {
	case DBG_RT_STATEKIND_FCPU:
		memcpy((struct fcpustate *)dbg_rt_trapstate, state, sizeof(struct fcpustate));
		return;

	case DBG_RT_STATEKIND_UCPU:
		fcpustate_to_ucpustate(state, (struct ucpustate *)dbg_rt_trapstate);
		break;

	case DBG_RT_STATEKIND_LCPU:
		fcpustate_to_lcpustate(state, (struct lcpustate *)dbg_rt_trapstate);
#ifdef __x86_64__
		/* Restore all registers except for `%r15', `%r14', `%r13', `%r12', ``rebp', `%rsp', `%rbx', `%rip' */
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_Pdi = state->fcs_gpregs.gp_Pdi;
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_Psi = state->fcs_gpregs.gp_Psi;
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_r11 = state->fcs_gpregs.gp_r11;
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_r10 = state->fcs_gpregs.gp_r10;
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_r9  = state->fcs_gpregs.gp_r9;
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_r8  = state->fcs_gpregs.gp_r8;
		x86_dbg_exitstate.de_state.fcs_sgbase = state->fcs_sgbase;
#else /* __x86_64__ */
		/* Restore all registers except for `%edi', `%esi', `%ebp', `%esp', `%ebx', `%eip' */
#endif /* !__x86_64__ */
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_Pax = state->fcs_gpregs.gp_Pax;
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_Pbx = state->fcs_gpregs.gp_Pbx;
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_Pdx = state->fcs_gpregs.gp_Pdx;
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_Pcx = state->fcs_gpregs.gp_Pcx;
		x86_dbg_exitstate.de_state.fcs_gpregs.gp_Pax = state->fcs_gpregs.gp_Pax;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_es  = state->fcs_sgregs.sg_es;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_cs  = state->fcs_sgregs.sg_cs;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_ss  = state->fcs_sgregs.sg_ss;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_ds  = state->fcs_sgregs.sg_ds;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_fs  = state->fcs_sgregs.sg_fs;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_gs  = state->fcs_sgregs.sg_gs;
		x86_dbg_exitstate.de_state.fcs_Pflags        = state->fcs_Pflags;
		break;

	case DBG_RT_STATEKIND_KCPU:
		fcpustate_to_kcpustate(state, (struct kcpustate *)dbg_rt_trapstate);
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_es  = state->fcs_sgregs.sg_es;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_cs  = state->fcs_sgregs.sg_cs;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_ss  = state->fcs_sgregs.sg_ss;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_ds  = state->fcs_sgregs.sg_ds;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_fs  = state->fcs_sgregs.sg_fs;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_gs  = state->fcs_sgregs.sg_gs;
		break;

	case DBG_RT_STATEKIND_ICPU:
		dbg_rt_trapstate = fcpustate_to_icpustate_p(state, (struct icpustate *)dbg_rt_trapstate);
#ifdef __x86_64__
		x86_dbg_exitstate.de_state.fcs_sgbase       = state->fcs_sgbase;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_es = state->fcs_sgregs.sg_es;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_ds = state->fcs_sgregs.sg_ds;
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_fs = state->fcs_sgregs.sg_fs;
#endif /* __x86_64__ */
		x86_dbg_exitstate.de_state.fcs_sgregs.sg_gs = state->fcs_sgregs.sg_gs;
		break;

	case DBG_RT_STATEKIND_SCPU:
		dbg_rt_trapstate = fcpustate_to_scpustate_p(state, (struct scpustate *)dbg_rt_trapstate);
		break;

	default:
		/* Set the whole exit state. */
		memcpy(&x86_dbg_exitstate, state, sizeof(struct fcpustate));
		return;
	}
	/* These registers are never present in trap states other than `DBG_RT_STATEKIND_FCPU'.
	 * As  such, changes to the values of these registers must cascade down to the debugger
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
/* Try   to   get/set   the  `%kernel_gs.base'   register   of  `dbg_current'
 * Note that  doing  this  is  only possible  for  `THIS_TASK',  as  well  as
 * the current thread  of another  CPU. All  other threads  have an  implicit
 * `%kernel_gs.base' register value set to the address of their `struct task'
 * structure, which is non-relocatable. */
PRIVATE ATTR_DBGTEXT bool
NOTHROW(KCALL get_dbg_current_kernel_gs_base)(u64 *__restrict presult) {
	if (!x86_dbg_viewthread)
		return false;
	if (dbg_current == THIS_TASK) {
		/* Assign  registers  to  the  trap  state,  and  let
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
		assert(cpuid < lengthof(x86_dbg_hostbackup.dhs_cpus));
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
		/* Assign  registers  to  the  trap  state,  and  let
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
		assert(cpuid < lengthof(x86_dbg_hostbackup.dhs_cpus));
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
 * state   to-be   loaded   by    `x86_dbg_viewthread' */
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
		/* Assign  registers  to  the  trap  state,  and  let
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
		assert(cpuid < lengthof(x86_dbg_hostbackup.dhs_cpus));
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
#ifndef __I386_NO_VM86
		if (!(x86_dbg_origstate.fcs_Pflags & EFLAGS_VM))
#endif /* !__I386_NO_VM86 */
		{
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
			if unlikely(cpuid >= lengthof(x86_dbg_hostbackup.dhs_cpus))
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
	if (dbg_current->t_mman) {
		struct mman *mm = dbg_current->t_mman;
		mm->mm_pagedir_p = (PHYS pagedir_t *)x86_dbg_origstate.fcs_coregs.co_cr3;
		FORMMAN(mm, thismman_x86_dr0) = x86_dbg_origstate.fcs_drregs.dr_dr0;
		FORMMAN(mm, thismman_x86_dr1) = x86_dbg_origstate.fcs_drregs.dr_dr1;
		FORMMAN(mm, thismman_x86_dr2) = x86_dbg_origstate.fcs_drregs.dr_dr2;
		FORMMAN(mm, thismman_x86_dr3) = x86_dbg_origstate.fcs_drregs.dr_dr3;
		FORMMAN(mm, thismman_x86_dr7) = x86_dbg_origstate.fcs_drregs.dr_dr7;
	}
}

/* Update the current thread orig/view CPU state. */
PRIVATE ATTR_DBGTEXT void
NOTHROW(KCALL loadview)(void) {
	if (x86_dbg_viewthread != dbg_current) {
		if (!dbg_current) {
			/* Special case: no thread loaded. */
			bzero(&x86_dbg_origstate, sizeof(x86_dbg_origstate));
		} else if (dbg_current == THIS_TASK) {
			/* DBG_RT_REGLEVEL_ORIG = DBG_RT_REGLEVEL_TRAP */
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
			assert(cpuid < lengthof(x86_dbg_hostbackup.dhs_cpus));
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
			x86_dbg_origstate.fcs_Pip          = ist->ics_irregs.ir_Pip;
			x86_dbg_origstate.fcs_Pflags       = ist->ics_irregs.ir_Pflags;
			x86_dbg_origstate.fcs_sgregs.sg_cs = ist->ics_irregs.ir_cs16;
#ifdef __x86_64__
			psp                                = ist->ics_irregs.ir_Psp;
			x86_dbg_origstate.fcs_sgregs.sg_ss = ist->ics_irregs.ir_ss16;
#endif /* __x86_64__ */
#if 0 /* Don't bend the truth when it comes to IRET tails. */
			if (x86_dbg_origstate.fcs_Pip == (uintptr_t)&x86_userexcept_sysret) {
				struct irregs_kernel *iret;
				iret = &FORTASK(ammend->dca_thread, this_x86_sysret_iret);
				x86_dbg_origstate.fcs_Pip          = iret->ir_Pip;
				x86_dbg_origstate.fcs_Pflags       = iret->ir_Pflags;
				x86_dbg_origstate.fcs_sgregs.sg_cs = iret->ir_cs16;
#ifdef __x86_64__
				psp                                = iret->ir_Psp;
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
#ifndef __I386_NO_VM86
			if (x86_dbg_origstate.fcs_Pflags & EFLAGS_VM) {
				/* Vm86 IRET tail */
				x86_dbg_origstate.fcs_sgregs.sg_es = ist->ics_irregs_v.ir_es16;
				x86_dbg_origstate.fcs_sgregs.sg_ds = ist->ics_irregs_v.ir_ds16;
				x86_dbg_origstate.fcs_sgregs.sg_fs = ist->ics_irregs_v.ir_fs16;
				x86_dbg_origstate.fcs_sgregs.sg_gs = ist->ics_irregs_v.ir_gs16;
				x86_dbg_origstate.fcs_sgregs.sg_ss = ist->ics_irregs_v.ir_ss16;
				psp                                = ist->ics_irregs_v.ir_Psp;
			} else
#endif /* !__I386_NO_VM86 */
			{
				x86_dbg_origstate.fcs_sgregs.sg_es = ist->ics_es16;
				x86_dbg_origstate.fcs_sgregs.sg_ds = ist->ics_ds16;
				x86_dbg_origstate.fcs_sgregs.sg_fs = ist->ics_fs16;
				x86_dbg_origstate.fcs_sgregs.sg_gs = ammend->dca_gs;
				x86_dbg_origstate.fcs_sgregs.sg_ss = ammend->dca_ss;
				if (x86_dbg_origstate.fcs_sgregs.sg_cs16 & 3) {
					/* User-space IRET tail */
					psp = ist->ics_irregs_u.ir_Psp;
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
			x86_dbg_origstate.fcs_gpregs.gp_Psp = psp;
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
				bzero(&x86_dbg_origstate, sizeof(x86_dbg_origstate));
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
				if unlikely(cpuid >= lengthof(x86_dbg_hostbackup.dhs_cpus))
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
					 * Fill  in  generic  register   information. */
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
			if (dbg_current->t_mman) {
				struct mman *mm = dbg_current->t_mman;
				x86_dbg_origstate.fcs_coregs.co_cr3 = (uintptr_t)mm->mm_pagedir_p;
				x86_dbg_origstate.fcs_drregs.dr_dr0 = FORMMAN(mm, thismman_x86_dr0);
				x86_dbg_origstate.fcs_drregs.dr_dr1 = FORMMAN(mm, thismman_x86_dr1);
				x86_dbg_origstate.fcs_drregs.dr_dr2 = FORMMAN(mm, thismman_x86_dr2);
				x86_dbg_origstate.fcs_drregs.dr_dr3 = FORMMAN(mm, thismman_x86_dr3);
				x86_dbg_origstate.fcs_drregs.dr_dr7 = FORMMAN(mm, thismman_x86_dr7);
			}
		}
		memcpy(&x86_dbg_viewstate, &x86_dbg_origstate, sizeof(struct fcpustate));
		x86_dbg_viewthread = dbg_current;
	}
}

#define VIEWSTATE(level)                                   \
	((unsigned int)(uintptr_t)(level) == DBG_RT_REGLEVEL_ORIG \
	 ? &x86_dbg_origstate                                  \
	 : &x86_dbg_viewstate)

/* Get/Set debugger register for some given level.
 * NOTE: These functions are written to be compatible with `unwind_getreg_t' / `unwind_setreg_t'
 * @param: arg: One of `DBG_RT_REGLEVEL_*', cast as `(void *)(uintptr_t)DBG_RT_REGLEVEL_*' */
PUBLIC ATTR_DBGTEXT unwind_errno_t
NOTHROW(LIBUNWIND_CC dbg_getreg)(/*uintptr_t level*/ void const *arg,
                                 uintptr_half_t cfi_regno,
                                 void *__restrict buf) {
	unwind_errno_t error;
	switch ((unsigned int)(uintptr_t)arg) {

	case DBG_RT_REGLEVEL_EXIT:
	case DBG_RT_REGLEVEL_TRAP:
		if (dbg_current == THIS_TASK) {
			if ((unsigned int)(uintptr_t)arg == DBG_RT_REGLEVEL_TRAP) {
				/* NOTE: Use exclusive register access so that the exit state is used as
				 *       fall-back, rather than the  current register state being  used! */
				switch (dbg_rt_trapstatekind) {

				case DBG_RT_STATEKIND_FCPU:
					error = unwind_getreg_fcpustate_exclusive(dbg_rt_trapstate, cfi_regno, buf);
					break;

				case DBG_RT_STATEKIND_UCPU:
					error = unwind_getreg_ucpustate_exclusive(dbg_rt_trapstate, cfi_regno, buf);
					break;

				case DBG_RT_STATEKIND_LCPU:
					error = unwind_getreg_lcpustate_exclusive(dbg_rt_trapstate, cfi_regno, buf);
					break;

				case DBG_RT_STATEKIND_KCPU:
					error = unwind_getreg_kcpustate_exclusive(dbg_rt_trapstate, cfi_regno, buf);
					break;

				case DBG_RT_STATEKIND_ICPU:
					error = unwind_getreg_icpustate_exclusive(dbg_rt_trapstate, cfi_regno, buf);
					break;

				case DBG_RT_STATEKIND_SCPU:
					error = unwind_getreg_scpustate_exclusive(dbg_rt_trapstate, cfi_regno, buf);
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
	case DBG_RT_REGLEVEL_ORIG:
	case DBG_RT_REGLEVEL_VIEW:
		loadview();
		return unwind_getreg_fcpustate(VIEWSTATE(arg), cfi_regno, buf);

	default:
		break;
	}
	return UNWIND_INVALID_REGISTER;
done:
	return error;
}

PUBLIC ATTR_DBGTEXT unwind_errno_t
NOTHROW(LIBUNWIND_CC dbg_setreg)(/*uintptr_t level*/ void *arg,
                                 uintptr_half_t cfi_regno,
                                 void const *__restrict buf) {
	unwind_errno_t error;
	switch ((unsigned int)(uintptr_t)arg) {

	case DBG_RT_REGLEVEL_EXIT:
	case DBG_RT_REGLEVEL_TRAP:
		if (dbg_current == THIS_TASK) {
			if ((unsigned int)(uintptr_t)arg == DBG_RT_REGLEVEL_TRAP) {
				/* NOTE: Use exclusive register access so that the exit state is used as
				 *       fall-back, rather than the  current register state being  used! */
				switch (dbg_rt_trapstatekind) {

				case DBG_RT_STATEKIND_FCPU:
					error = unwind_setreg_fcpustate_exclusive(dbg_rt_trapstate, cfi_regno, buf);
					break;

				case DBG_RT_STATEKIND_UCPU:
					error = unwind_setreg_ucpustate_exclusive(dbg_rt_trapstate, cfi_regno, buf);
					break;

				case DBG_RT_STATEKIND_LCPU:
					error = unwind_setreg_lcpustate_exclusive(dbg_rt_trapstate, cfi_regno, buf);
					break;

				case DBG_RT_STATEKIND_KCPU:
					error = unwind_setreg_kcpustate_exclusive(dbg_rt_trapstate, cfi_regno, buf);
					break;

#ifdef __x86_64__
				case DBG_RT_STATEKIND_ICPU:
					error = unwind_setreg_icpustate_exclusive(dbg_rt_trapstate, cfi_regno, buf);
					break;

				case DBG_RT_STATEKIND_SCPU:
					error = unwind_setreg_scpustate_exclusive(dbg_rt_trapstate, cfi_regno, buf);
					break;
#else /* __x86_64__ */
				case DBG_RT_STATEKIND_ICPU:
					error = unwind_setreg_icpustate_exclusive_p(&dbg_rt_trapstate, cfi_regno, buf);
					break;

				case DBG_RT_STATEKIND_SCPU:
					error = unwind_setreg_scpustate_exclusive_p(&dbg_rt_trapstate, cfi_regno, buf);
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
	case DBG_RT_REGLEVEL_ORIG:
	case DBG_RT_REGLEVEL_VIEW:
		loadview();
		error = unwind_setreg_fcpustate(VIEWSTATE(arg), cfi_regno, buf);
		if (error == UNWIND_SUCCESS) {
			if ((unsigned int)(uintptr_t)arg == DBG_RT_REGLEVEL_ORIG)
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

PRIVATE size_t
NOTHROW(KCALL raw_dbg_getregbyid)(unsigned int level, cpu_regno_t regno,
                                  void *__restrict buf, size_t buflen) {
	size_t result;
	switch (level) {

	case DBG_RT_REGLEVEL_EXIT:
	case DBG_RT_REGLEVEL_TRAP:
		if (dbg_current == THIS_TASK) {
			if (level == DBG_RT_REGLEVEL_TRAP) {
				/* NOTE: Use exclusive register access so that the exit state is used as
				 *       fall-back, rather than the  current register state being  used! */
				switch (dbg_rt_trapstatekind) {

				case DBG_RT_STATEKIND_FCPU:
					result = register_get((struct fcpustate *)dbg_rt_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				case DBG_RT_STATEKIND_UCPU:
					result = register_get((struct ucpustate *)dbg_rt_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				case DBG_RT_STATEKIND_LCPU:
					result = register_get((struct lcpustate *)dbg_rt_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				case DBG_RT_STATEKIND_KCPU:
					result = register_get((struct kcpustate *)dbg_rt_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				case DBG_RT_STATEKIND_ICPU:
					result = register_get((struct icpustate *)dbg_rt_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				case DBG_RT_STATEKIND_SCPU:
					result = register_get((struct scpustate *)dbg_rt_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				default: break;
				}
			}
#ifdef __x86_64__
			if (regno == X86_REGISTER_MISC_KGSBASEL) {
				if (buflen >= 4)
					UNALIGNED_SET32(buf, (u32)x86_dbg_exitstate.de_kernel_gsbase);
				return 4;
			}
			if (regno == X86_REGISTER_MISC_KGSBASEQ) {
				if (buflen >= 8)
					UNALIGNED_SET64(buf, (u64)x86_dbg_exitstate.de_kernel_gsbase);
				return 8;
			}
#endif /* __x86_64__ */
			/* Access the exit CPU state. */
			return register_get(&x86_dbg_exitstate.de_state, regno, buf, buflen);
		}
		ATTR_FALLTHROUGH
	case DBG_RT_REGLEVEL_ORIG:
	case DBG_RT_REGLEVEL_VIEW:
		loadview();
		result = register_get(VIEWSTATE(level), regno, buf, buflen);
#ifdef __x86_64__
		if (/*level == DBG_RT_REGLEVEL_ORIG &&*/ result == 0) {
			if (regno == X86_REGISTER_MISC_KGSBASEL) {
				u64 temp;
				result = 0;
				if (get_dbg_current_kernel_gs_base(&temp)) {
					result = 4;
					if (buflen >= 4)
						UNALIGNED_SET32(buf, temp);
				}
				goto ok;
			}
			if (regno == X86_REGISTER_MISC_KGSBASEQ) {
				u64 temp;
				result = 0;
				if (get_dbg_current_kernel_gs_base(&temp)) {
					result = 8;
					if (buflen >= 8)
						UNALIGNED_SET64(buf, temp);
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

#ifdef __x86_64__
PRIVATE WUNUSED cpu_regno_t
NOTHROW(KCALL transform_gsbase_register_indices)(unsigned int level, cpu_regno_t regno) {
	/* Special handling: when we're currently returning to  kernel-space,
	 *                   then we must switch %kernel_gs.base and %gs.base
	 * This is required to maintain proper segment logic. */
	switch (regno) {

	case X86_REGISTER_MISC_GSBASEL:
	case X86_REGISTER_MISC_GSBASEQ:
	case X86_REGISTER_MISC_KGSBASEL:
	case X86_REGISTER_MISC_KGSBASEQ: {
		u16 cs;
		if (raw_dbg_getregbyid(level, X86_REGISTER_SEGMENT_CS, &cs, 2) != 2)
			return 0;
		if (!(cs & 3)) {
			switch (regno) {
			case X86_REGISTER_MISC_GSBASEL: regno = X86_REGISTER_MISC_KGSBASEL; break;
			case X86_REGISTER_MISC_GSBASEQ: regno = X86_REGISTER_MISC_KGSBASEQ; break;
			case X86_REGISTER_MISC_KGSBASEL: regno = X86_REGISTER_MISC_GSBASEL; break;
			case X86_REGISTER_MISC_KGSBASEQ: regno = X86_REGISTER_MISC_GSBASEQ; break;
			default: __builtin_unreachable();
			}
		}
	}	break;

	default:
		break;
	}
	return regno;
}
#endif /* __x86_64__ */

/* Get/set a register, given its ID
 * NOTE: When `return > buflen', then
 *       dbg_rt_getregbyname: The contents of `buf' are undefined.
 *       dbg_rt_setregbyname: The register was not written.
 * NOTE: Accepted register names are those found in comments in `<asm/registers.h>'
 * @param: regno: One of `X86_REGISTER_*' (from <asm/registers.h>) or one of `X86_DBGREGISTER_*'
 * @return: * :   The required buffer size, or 0 when `regno' isn't recognized. */
PUBLIC size_t
NOTHROW(KCALL dbg_rt_getregbyid)(unsigned int level, cpu_regno_t regno,
                              void *__restrict buf, size_t buflen) {
#ifdef __x86_64__
	/* Special handling: when we're currently returning to  kernel-space,
	 *                   then we must switch %kernel_gs.base and %gs.base
	 * This is required to maintain proper segment logic. */
	regno = transform_gsbase_register_indices(level, regno);
#endif /* __x86_64__ */
	return raw_dbg_getregbyid(level, regno, buf, buflen);
}

PUBLIC size_t
NOTHROW(KCALL dbg_rt_setregbyid)(unsigned int level, cpu_regno_t regno,
                              void const *__restrict buf, size_t buflen) {
	size_t result;

#ifdef __x86_64__
	/* Special handling: when we're currently returning to  kernel-space,
	 *                   then we must switch %kernel_gs.base and %gs.base
	 * This is required to maintain proper segment logic. */
	regno = transform_gsbase_register_indices(level, regno);
#endif /* __x86_64__ */

	switch (level) {

	case DBG_RT_REGLEVEL_EXIT:
	case DBG_RT_REGLEVEL_TRAP:
		if (dbg_current == THIS_TASK) {
			if (level == DBG_RT_REGLEVEL_TRAP) {
				/* NOTE: Use exclusive register access so that the exit state is used as
				 *       fall-back, rather than the  current register state being  used! */
				switch (dbg_rt_trapstatekind) {

				case DBG_RT_STATEKIND_FCPU:
					result = register_set_fcpustate_p((struct fcpustate **)&dbg_rt_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				case DBG_RT_STATEKIND_UCPU:
					result = register_set_ucpustate_p((struct ucpustate **)&dbg_rt_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				case DBG_RT_STATEKIND_LCPU:
					result = register_set_lcpustate_p((struct lcpustate **)&dbg_rt_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				case DBG_RT_STATEKIND_KCPU:
					result = register_set_kcpustate_p((struct kcpustate **)&dbg_rt_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				case DBG_RT_STATEKIND_ICPU:
					result = register_set_icpustate_p((struct icpustate **)&dbg_rt_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				case DBG_RT_STATEKIND_SCPU:
					result = register_set_scpustate_p((struct scpustate **)&dbg_rt_trapstate, regno, buf, buflen);
					if (result != 0)
						goto ok;
					break;

				default: break;
				}
			}
#ifdef __x86_64__
			if (regno == X86_REGISTER_MISC_KGSBASEL) {
				if (buflen >= 4)
					x86_dbg_exitstate.de_kernel_gsbase = UNALIGNED_GET32(buf);
				return 4;
			}
			if (regno == X86_REGISTER_MISC_KGSBASEQ) {
				if (buflen >= 8)
					x86_dbg_exitstate.de_kernel_gsbase = UNALIGNED_GET64(buf);
				return 8;
			}
#endif /* __x86_64__ */
			/* Access the exit CPU state. */
			return register_set_fcpustate(&x86_dbg_exitstate.de_state, regno, buf, buflen);
		}
		ATTR_FALLTHROUGH
	case DBG_RT_REGLEVEL_ORIG:
	case DBG_RT_REGLEVEL_VIEW:
		loadview();
		result = register_set_fcpustate(VIEWSTATE(level), regno, buf, buflen);
		if (level == DBG_RT_REGLEVEL_ORIG && result != 0) {
			saveorig();
		}
#ifdef __x86_64__
		else if (level == DBG_RT_REGLEVEL_ORIG && result == 0) {
			if (regno == X86_REGISTER_MISC_KGSBASEL) {
				result = 4;
				if (buflen >= 4) {
					if (!set_dbg_current_kernel_gs_base(UNALIGNED_GET32(buf)))
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
					if (!set_dbg_current_kernel_gs_base(UNALIGNED_GET64(buf)))
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
NOTHROW(KCALL dbg_rt_getallregs)(unsigned int level,
                              struct fcpustate *__restrict state) {
	switch (level) {

	case DBG_RT_REGLEVEL_EXIT:
	case DBG_RT_REGLEVEL_TRAP:
		if (dbg_current == THIS_TASK) {
			/* Access the exit CPU state. */
			memcpy(state, &x86_dbg_exitstate, sizeof(struct fcpustate));
			if (level == DBG_RT_REGLEVEL_TRAP) {
				/* NOTE: Use exclusive register access so that the exit state is used as
				 *       fall-back, rather than the  current register state being  used! */
				switch (dbg_rt_trapstatekind) {

				case DBG_RT_STATEKIND_FCPU:
					memcpy(state, (struct fcpustate *)dbg_rt_trapstate, sizeof(struct fcpustate));
					break;

				case DBG_RT_STATEKIND_UCPU:
					fcpustate_assign_ucpustate(state, (struct ucpustate *)dbg_rt_trapstate);
					break;

				case DBG_RT_STATEKIND_LCPU:
					fcpustate_assign_lcpustate(state, (struct lcpustate *)dbg_rt_trapstate);
					break;

				case DBG_RT_STATEKIND_KCPU:
					fcpustate_assign_kcpustate(state, (struct kcpustate *)dbg_rt_trapstate);
					break;

				case DBG_RT_STATEKIND_ICPU:
					fcpustate_assign_icpustate(state, (struct icpustate *)dbg_rt_trapstate);
					break;

				case DBG_RT_STATEKIND_SCPU:
					fcpustate_assign_scpustate(state, (struct scpustate *)dbg_rt_trapstate);
					break;

				default: break;
				}
			}
			goto done;
		}
		break;
	default:
		break;
	}
	loadview();
	memcpy(state, VIEWSTATE(level),
	       sizeof(struct fcpustate));
done:
#ifdef __x86_64__
	/* Special handling: when we're currently returning to  kernel-space,
	 *                   then we must switch %kernel_gs.base and %gs.base
	 * This is required to maintain proper segment logic. */
	if (!(state->fcs_sgregs.sg_cs16 & 3)) {
		raw_dbg_getregbyid(level, X86_REGISTER_MISC_KGSBASEQ,
		                   &state->fcs_sgbase.sg_gsbase, 8);
	}
#endif /* __x86_64__ */
	;
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(KCALL dbg_rt_setallregs)(unsigned int level,
                              struct fcpustate const *__restrict state) {
#ifdef __x86_64__
	struct fcpustate real_state;
	/* Special handling: when we're currently returning to  kernel-space,
	 *                   then we must switch %kernel_gs.base and %gs.base
	 * This is required to maintain proper segment logic. */
	if (!(state->fcs_sgregs.sg_cs16 & 3)) {
		memcpy(&real_state, state, sizeof(struct fcpustate));
		set_dbg_current_kernel_gs_base(real_state.fcs_sgbase.sg_gsbase);
		raw_dbg_getregbyid(level, X86_REGISTER_MISC_KGSBASEQ,
		                   &real_state.fcs_sgbase.sg_gsbase, 8);
		state = &real_state;
	}
#endif /* __x86_64__ */
	switch (level) {

	case DBG_RT_REGLEVEL_EXIT:
	case DBG_RT_REGLEVEL_TRAP:
		if (dbg_current == THIS_TASK) {
			/* Access the exit CPU state. */
			if (level == DBG_RT_REGLEVEL_TRAP) {
				/* NOTE: Use exclusive register access so that the exit state is used as
				 *       fall-back, rather than the  current register state being  used! */
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
	if (level == DBG_RT_REGLEVEL_ORIG)
		saveorig();
}

/* Return the ISA code for use with libinstrlen */
PUBLIC ATTR_PURE WUNUSED isa_t
NOTHROW(KCALL dbg_rt_getisa)(unsigned int level) {
	isa_t result;
#ifdef __x86_64__
	uintptr_t cs;
	dbg_getreg((void *)(uintptr_t)level, CFI_X86_64_UNWIND_REGISTER_CS, &cs);
	if (__KOS64_IS_CS64BIT(cs)) {
		result = ISA_X86_64;
	} else {
		result = ISA_I386;
	}
#else /* __x86_64__ */
	uintptr_t eflags;
	dbg_getreg((void *)(uintptr_t)level, CFI_386_UNWIND_REGISTER_EFLAGS, &eflags);
	if (eflags & EFLAGS_VM) {
		result = ISA_8086;
	} else {
		result = ISA_I386;
	}
#endif /* !__x86_64__ */
	return result;
}

/* Return the page directory of `dbg_current' */
PUBLIC ATTR_PURE WUNUSED pagedir_phys_t
NOTHROW(KCALL dbg_rt_getpagedir)(void) {
	uintptr_t result;
	result = dbg_rt_getregbyidp(DBG_RT_REGLEVEL_VIEW,
	                         X86_REGISTER_CONTROL_CR3);
	return (pagedir_phys_t)result;
}


/* Check if the register view has been changed. */
PUBLIC ATTR_DBGTEXT ATTR_PURE WUNUSED bool
NOTHROW(FCALL dbg_rt_changedview)(void) {
	loadview();
	return bcmp(&x86_dbg_origstate,
	            &x86_dbg_viewstate,
	            sizeof(struct fcpustate)) != 0;
}


DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_REGISTER_C */
