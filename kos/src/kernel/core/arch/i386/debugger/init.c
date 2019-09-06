/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.remove("-O3"))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_INIT_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_INIT_C 1
#define _KOS_SOURCE 1
#define DISABLE_BRANCH_PROFILING 1

#include <kernel/compiler.h>

#include <kernel/debugger.h>

#ifndef CONFIG_NO_DEBUGGER
#include <kernel/apic.h>
#include <kernel/vm.h>
#include <kernel/except.h>
#include <kernel/gdt.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/tss.h>
#include <sched/cpu.h>
#include <sched/task.h>
#include <sched/signal.h>

#include <hybrid/atomic.h>

#include <asm/cpu-flags.h>
#include <asm/intrin.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/gdt.h>

#include <assert.h>
#include <string.h>

#include "../../../sched/rwlock.h" /* struct read_locks */

DECL_BEGIN


/* Saved backup of the original debugger exit state. */
PRIVATE ATTR_COLDBSS struct fcpustate dbg_orig_exitstate = {};

/* Impersonate the given `thread' for the purpose of debugging. */
PUBLIC ATTR_DBGTEXT NONNULL((1)) void KCALL
dbg_impersonate_thread(struct task *__restrict thread) {
	if (thread == THIS_TASK)
		return;
#ifdef __x86_64__
	__wrgsbase((uintptr_t)thread);
#else /* __x86_64__ */
	segment_wrbaseX(&x86_debug_gdt[SEGMENT_INDEX(SEGMENT_KERNEL_FSBASE)],
	                (uintptr_t)thread);
	__wrfs(SEGMENT_KERNEL_FSBASE);
#endif /* !__x86_64__ */
#if 0 /* The debugger always uses the kernel page directory...
       * FIXME: This is currently required because of the address of the VGA
       *        display buffer, but also prevents inspection of user-space
       *        memory by utilities such as the hex editor. */
	/* Also change page directories (if necessary). */
	pagedir_set(thread->t_vm->v_pdir_phys_ptr);
#endif
	if (thread == debug_original_thread) {
		memcpy(&dbg_exitstate, &dbg_orig_exitstate, sizeof(struct fcpustate));
		memcpy(&dbg_viewstate, &dbg_orig_exitstate, sizeof(struct fcpustate));
	} else {
		struct scpustate *state;
		state = thread->t_sched.s_state;
#ifdef __x86_64__
		/* TODO */
#else /* __x86_64__ */
		dbg_viewstate.fcs_gpregs        = state->scs_gpregs;
		dbg_viewstate.fcs_eip           = state->scs_irregs_k.ir_eip;
		dbg_viewstate.fcs_eflags        = state->scs_irregs_k.ir_eflags;
		dbg_viewstate.fcs_sgregs.sg_cs  = state->scs_irregs_k.ir_cs;
		dbg_viewstate.fcs_coregs.co_cr3 = (u32)thread->t_vm->v_pdir_phys_ptr;
		if (SCPUSTATE_ISVM86(*state)) {
			dbg_viewstate.fcs_gpregs.gp_esp = state->scs_irregs_v.ir_esp;
			dbg_viewstate.fcs_sgregs.sg_ss  = state->scs_irregs_v.ir_ss;
			dbg_viewstate.fcs_sgregs.sg_ds  = state->scs_irregs_v.ir_ds;
			dbg_viewstate.fcs_sgregs.sg_es  = state->scs_irregs_v.ir_es;
			dbg_viewstate.fcs_sgregs.sg_fs  = state->scs_irregs_v.ir_fs;
			dbg_viewstate.fcs_sgregs.sg_gs  = state->scs_irregs_v.ir_gs;
		} else {
			dbg_viewstate.fcs_sgregs.sg_ds = state->scs_sgregs.sg_ds;
			dbg_viewstate.fcs_sgregs.sg_es = state->scs_sgregs.sg_es;
			dbg_viewstate.fcs_sgregs.sg_fs = state->scs_sgregs.sg_fs;
			dbg_viewstate.fcs_sgregs.sg_gs = state->scs_sgregs.sg_gs;
			if (state->scs_irregs_k.ir_cs & 3) {
				dbg_viewstate.fcs_sgregs.sg_ss  = SCPUSTATE_USER_SS(*state);
				dbg_viewstate.fcs_gpregs.gp_esp = SCPUSTATE_USER_ESP(*state);
			} else {
				dbg_viewstate.fcs_sgregs.sg_ss  = SCPUSTATE_KERNEL_SS(*state);
				dbg_viewstate.fcs_gpregs.gp_esp = SCPUSTATE_KERNEL_ESP(*state);
			}
		}
#endif /* !__x86_64__ */
		memcpy(&dbg_orig_exitstate, &dbg_exitstate, sizeof(struct fcpustate));
		memcpy(&dbg_exitstate, &dbg_viewstate, sizeof(struct fcpustate));
	}
}



#ifndef CONFIG_NO_SMP
INTERN ATTR_DBGTEXT NOBLOCK void
NOTHROW(FCALL x86_debugger_wait_for_done)(void) {
	uintptr_t was = __rdflags();
	__cli();
	cpu_disable_preemptive_interrupts_nopr();
	__sti();
	while (dbg_active) {
		__pause();
		__hlt();
	}
	__cli();
	cpu_enable_preemptive_interrupts_nopr(); /* XXX: Don't account for lost time! */
	__wrflags(was);
}

PRIVATE ATTR_DBGTEXT NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL debugger_wait_for_done)(struct icpustate *__restrict state,
                                      void *UNUSED(args)[CPU_IPI_ARGCOUNT]) {
	x86_debugger_wait_for_done();
	return state;
}
#endif /* !CONFIG_NO_SMP */

INTDEF void KCALL x86_debug_initialize_vga_terminal(void);
INTDEF void KCALL x86_debug_finalize_vga_terminal(void);
INTDEF void KCALL x86_debug_initialize_ps2_keyboard(void);
INTDEF void KCALL x86_debug_finalize_ps2_keyboard(void);


/* Backup of the exception info. */
PRIVATE ATTR_COLDBSS struct exception_info debug_old_exception_info;

#ifndef CONFIG_NO_SMP
INTERN ATTR_COLDBSS struct cpu *debug_mycpu = NULL;
#else /* !CONFIG_NO_SMP */
#define debug_mycpu (&_bootcpu)
#endif /* CONFIG_NO_SMP */
PUBLIC ATTR_COLDBSS struct task *debug_original_thread_ ASMNAME("debug_original_thread") = NULL;

PUBLIC ATTR_COLDBSS unsigned int dbg_active = 0;
PUBLIC ATTR_COLDBSS struct fcpustate dbg_exitstate = {};
PUBLIC ATTR_COLDBSS struct fcpustate dbg_viewstate = {};

typedef void (KCALL *dbg_callback_t)(void);
INTDEF dbg_callback_t const __kernel_dbg_init_start[];
INTDEF dbg_callback_t const __kernel_dbg_init_end[];
INTDEF dbg_callback_t const __kernel_dbg_reset_start[];
INTDEF dbg_callback_t const __kernel_dbg_reset_end[];
INTDEF dbg_callback_t const __kernel_dbg_fini_start[];
INTDEF dbg_callback_t const __kernel_dbg_fini_end[];

#if 1
#define CALL_FUNCTIONS(start, end)             \
	do {                                       \
		dbg_callback_t const *iter;            \
		for (iter = start; iter < end; ++iter) \
			(**iter)();                        \
	} __WHILE0
#define CALL_FUNCTIONS_REV(start, end)    \
	do {                                  \
		dbg_callback_t const *iter = end; \
		while (iter > start) {            \
			--iter;                       \
			(**iter)();                   \
		}                                 \
	} __WHILE0
#else
#define CALL_FUNCTIONS(start, end)     do{}__WHILE0
#define CALL_FUNCTIONS_REV(start, end) do{}__WHILE0
#endif



INTDEF void NOTHROW(KCALL x86_init_this_kernel_sp)(struct task *__restrict self);
#ifndef __x86_64__
INTDEF void NOTHROW(KCALL x86_this_userkern_init)(struct task *__restrict self);
#endif /* !__x86_64__ */
INTDEF NOBLOCK void NOTHROW(KCALL pertask_readlocks_init)(struct task *__restrict thread);
INTDEF NOBLOCK void NOTHROW(KCALL pertask_init_task_connections)(struct task *__restrict self);

INTDEF ATTR_PERTASK struct task_connections _this_cons;

INTDEF void NOTHROW(KCALL x86_initialize_pic)(void);


PRIVATE ATTR_DBGTEXT NOBLOCK void
NOTHROW(KCALL dbg_ensure_initialized_pertask)(struct task *__restrict self) {
	if (!FORTASK(self, x86_this_kernel_sp0))
		x86_init_this_kernel_sp(self);
#ifndef __x86_64__
	if (!FORTASK(self, x86_this_user_gsbase))
		x86_this_userkern_init(self);
#endif /* !__x86_64__ */
	if (!FORTASK(self, _this_read_locks).rls_vec)
		pertask_readlocks_init(self);
	if (!FORTASK(self, _this_cons).tc_static_v ||
	    FORTASK(self, _this_cons).tc_signals.ts_thread != self)
		pertask_init_task_connections(self);
}


#ifndef CONFIG_NO_SMP
PRIVATE ATTR_DBGTEXT NOBLOCK NONNULL((1, 2)) cpuid_t
NOTHROW(KCALL cpu_broadcastipi_notthis_early_boot_aware)(cpu_ipi_t func,
                                                         void *args[CPU_IPI_ARGCOUNT],
                                                         unsigned int flags,
                                                         struct cpu *calling_cpu) {
	cpuid_t i, result = 0;
	pflag_t was = PREEMPTION_PUSHOFF();
	for (i = 0; i < cpu_count; ++i) {
		struct cpu *target;
		target = cpu_vector[i];
		if (target == calling_cpu)
			continue;
		/* At one point during early boot, the entires of the `cpu_vector'
		 * are used to carry a 16-bit block of information about the how
		 * the associated CPU will be addressed physically.
		 * Since we known that the kernel lives in upper memory, and that
		 * this type of address information only uses the lower-most 16
		 * bits, we can infer that anything that isn't >= 0xc000000 in i386,
		 * or `0xffff800000000000' on x86_64 isn't an initialized CPU pointer. */
		if ((uintptr_t)target < KERNEL_BASE)
			continue;
		if (cpu_sendipi(target, func, args, flags))
			++result;
	}
	PREEMPTION_POP(was);
	return result;
}
#endif /* !CONFIG_NO_SMP */


INTERN ATTR_DBGTEXT void KCALL dbg_fix_segments(void) {

	/* Setup kernel segment bases. */
	segment_wrbaseX(&x86_debug_gdt[SEGMENT_INDEX(SEGMENT_CPU_TSS)], (uintptr_t)&FORCPU(debug_mycpu, x86_cputss));
	segment_wrbaseX(&x86_debug_gdt[SEGMENT_INDEX(SEGMENT_CPU_LDT)], (uintptr_t)&FORCPU(debug_mycpu, x86_cpuldt));
#ifndef __x86_64__
	segment_wrbaseX(&x86_debug_gdt[SEGMENT_INDEX(SEGMENT_CPU_TSS_DF)], (uintptr_t)&FORCPU(debug_mycpu, x86_cputss_df));
	segment_wrbaseX(&x86_debug_gdt[SEGMENT_INDEX(SEGMENT_KERNEL_FSBASE)], (uintptr_t)debug_original_thread_);
	segment_wrbaseX(&x86_debug_gdt[SEGMENT_INDEX(SEGMENT_USER_FSBASE)], (uintptr_t)FORTASK(debug_original_thread_, x86_this_user_fsbase));
	segment_wrbaseX(&x86_debug_gdt[SEGMENT_INDEX(SEGMENT_USER_GSBASE)], (uintptr_t)FORTASK(debug_original_thread_, x86_this_user_gsbase));
#endif /* !__x86_64__ */
	x86_debug_gdt[SEGMENT_INDEX(SEGMENT_CPU_TSS)].s_tss.t_type_bits.ttb_busy = 0; /* BUSY=0 */
	__ltr(SEGMENT_CPU_TSS);
	__lldt(SEGMENT_CPU_LDT);
#ifdef __x86_64__
	__wrgsbase(debug_original_thread_);
#else /* __x86_64__ */
	__wrfs(SEGMENT_KERNEL_FSBASE);
	__wrgs(SEGMENT_USER_GSBASE_RPL);
#endif /* !__x86_64__ */
}

INTERN ATTR_DBGTEXT void KCALL dbg_init(void) {
	void *args[CPU_IPI_ARGCOUNT];
	/* Disable preemption */
	cpu_disable_preemptive_interrupts();

#ifndef CONFIG_NO_SMP
	/* Try to figure out which task we are (but
	 * don't do anything that could break stuff...) */
	if (cpu_count <= 1) {
		/* Simple case: There's only 1 CPU, so that has to be us! */
		debug_mycpu = &_bootcpu;
	} else if (X86_HAVE_LAPIC) {
		/* Use the LAPIC id to determine the current CPU. */
		cpuid_t i;
		u8 id = (u8)(lapic_read(APIC_ID) >> APIC_ID_FSHIFT);
		debug_mycpu = &_bootcpu;
		for (i = 0; i < cpu_count; ++i) {
			if (FORCPU(cpu_vector[i], x86_lapic_id) == id) {
				debug_mycpu = cpu_vector[i];
				break;
			}
		}
	} else {
		/* TODO: Use pointers from `dbg_exitstate' to determine the calling CPU */
		debug_mycpu = &_bootcpu;
	}
#endif /* !CONFIG_NO_SMP */

	debug_original_thread_ = debug_mycpu->c_current;

	/* Fix kernel segment bases. */
	dbg_fix_segments();

#ifndef CONFIG_NO_SMP
	/* Suspend execution on all other CPUs. */
	cpu_broadcastipi_notthis_early_boot_aware(&debugger_wait_for_done,
	                                          args,
	                                          CPU_IPI_FNORMAL,
	                                          debug_mycpu);
#endif /* !CONFIG_NO_SMP */

	/* Preserve active exception information. */
	memcpy(&debug_old_exception_info,
	       &FORTASK(debug_original_thread_, _this_exception_info),
	       sizeof(debug_old_exception_info));

	/* Ensure that pertask scheduler variables are initialized
	 * for some of the more special thread.
	 * If we got here very early on during bootup, this may not
	 * be the case, however other parts of the debugger rely on
	 * components that require these variables to be initialized. */
	dbg_ensure_initialized_pertask(debug_original_thread_);
	dbg_ensure_initialized_pertask(&FORCPU(debug_mycpu, _this_idle));
	dbg_ensure_initialized_pertask(&_boottask);
	dbg_ensure_initialized_pertask(&_bootidle);

	/* Set the currently viewed state to be the exit state. */
	memcpy(&dbg_viewstate,
	       &dbg_exitstate,
	       sizeof(dbg_exitstate));

	/* Make sure that the PIC is initialized properly, as the debugger's
	 * PS/2 keyboard driver requires interrupts to be mapped properly. */
	x86_initialize_pic();

	/* Configure VGA + PS/2 keyboard. */
	x86_debug_initialize_vga_terminal();
	x86_debug_initialize_ps2_keyboard();

	/* Invoke global callbacks. */
	CALL_FUNCTIONS(__kernel_dbg_init_start,
	               __kernel_dbg_init_end);
}

INTERN ATTR_DBGTEXT void KCALL dbg_reset(void) {
	/* Fix kernel segment bases. */
	dbg_fix_segments();
	/* Invoke global callbacks. */
	CALL_FUNCTIONS(__kernel_dbg_reset_start,
	               __kernel_dbg_reset_end);
}

INTERN ATTR_DBGTEXT void KCALL dbg_fini(void) {
	/* If we're still impersonating a thread, we must fix-up our exit CPU state,
	 * such that we'll be returning to our original interrupt location.
	 * This does the same as `dbg_impersonate_thread(debug_original_thread)' */
	if (THIS_TASK != debug_original_thread)
		memcpy(&dbg_exitstate, &dbg_orig_exitstate, sizeof(struct fcpustate));
	/* Fix kernel segment bases. */
	dbg_fix_segments();

	/* Invoke global callbacks. */
	CALL_FUNCTIONS_REV(__kernel_dbg_fini_start,
	                   __kernel_dbg_fini_end);

	x86_debug_finalize_ps2_keyboard();
	x86_debug_finalize_vga_terminal();

	/* Restore active exception information. */
	memcpy(&FORTASK(debug_original_thread_, _this_exception_info),
	       &debug_old_exception_info,
	       sizeof(debug_old_exception_info));
	assert(debug_original_thread_ == debug_mycpu->c_current);
	cpu_enable_preemptive_interrupts(); /* XXX: Don't account for lost time! */
}


#ifndef CONFIG_NO_SMP
PRIVATE ATTR_DBGTEXT NOBLOCK NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL debugger_wake_after_done)(struct icpustate *__restrict state,
                                        void *args[CPU_IPI_ARGCOUNT]) {
	(void)args;
	return state;
}

INTERN ATTR_DBGTEXT void KCALL dbg_wake_other_cpus(void) {
	void *args[CPU_IPI_ARGCOUNT];
	/* Send a sporadic IPI to all CPUs other than the caller. */
	cpu_broadcastipi_notthis_early_boot_aware(&debugger_wake_after_done,
	                                          args,
	                                          CPU_IPI_FNORMAL,
	                                          debug_mycpu);
}
#endif /* !CONFIG_NO_SMP */


DECL_END
#endif /* !CONFIG_NO_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_INIT_C */
