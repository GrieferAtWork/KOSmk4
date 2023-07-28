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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_FPU_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_FPU_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/driver-param.h>
#include <kernel/except.h>
#include <kernel/fpu.h>
#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/x86/cpuid.h>
#include <sched/group.h>
#include <sched/task.h>

#include <hybrid/sched/preemption.h>

#include <asm/cpu-cpuid.h>
#include <asm/cpu-flags.h>
#include <asm/intrin-fpu.h>
#include <asm/intrin.h>
#include <asm/redirect.h>
#include <kos/kernel/cpu-state-compat.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/fpu-state-helpers.h>
#include <kos/kernel/fpu-state.h>
#include <kos/kernel/bits/fpu-state32.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#define FPU_GFP  (GFP_NORMAL)

#ifdef CONFIG_HAVE_FPU

/* [const] The type of FPU state used (One of `FPU_STATE_*') */
PUBLIC unsigned int _x86_fpustate_variant ASMNAME("x86_fpustate_variant") = FPU_STATE_XSTATE;

/* [0..1] The task associated with the current FPU register contents, or NULL if none.
 * NOTE: When accessing this field, preemption must be disabled, as
 *       this field affects  the behavior of  task state  switches. */
PUBLIC ATTR_PERCPU struct task *thiscpu_fputhread = NULL;

/* [0..1][owned] The per-task FPU state (lazily allocated) */
PUBLIC ATTR_PERTASK ATTR_ALIGN(struct fpustate *) this_fpustate = NULL;

DEFINE_PERTASK_FINI(pertask_finalize_fpustate);
INTERN NOBLOCK void
NOTHROW(KCALL pertask_finalize_fpustate)(struct task *__restrict self) {
	fpustate_free(FORTASK(self, this_fpustate));
}


PRIVATE ATTR_MALLOC ATTR_RETNONNULL WUNUSED struct fpustate *KCALL
fpustate_alloc_noinit(void) {
	return (struct fpustate *)kmemalign(ALIGNOF_FPUSTATE,
	                                    SIZEOF_FPUSTATE,
	                                    FPU_GFP);
}

PUBLIC ATTR_MALLOC ATTR_RETNONNULL WUNUSED struct fpustate *KCALL
fpustate_alloc(void) {
	struct fpustate *result;
	result = (struct fpustate *)kmemalign(ALIGNOF_FPUSTATE,
	                                      SIZEOF_FPUSTATE,
	                                      FPU_GFP | GFP_CALLOC);
	x86_fpustate_init(result);
	return result;
}

PUBLIC ATTR_MALLOC WUNUSED struct fpustate *
NOTHROW(KCALL fpustate_alloc_nx)(void) {
	struct fpustate *result;
	result = (struct fpustate *)kmemalign_nx(ALIGNOF_FPUSTATE,
	                                         SIZEOF_FPUSTATE,
	                                         FPU_GFP | GFP_CALLOC);
	if likely(result)
		x86_fpustate_init(result);
	return result;
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fpustate_free)(struct fpustate *__restrict self) {
	kfree(self);
}



/* Ensure that `this_fpustate' has been allocated, allocating
 * and initializing it now if that hasn't been done  already. */
PUBLIC void KCALL fpustate_init(void) THROWS(E_BADALLOC) {
	if (!PERTASK_TEST(this_fpustate))
		PERTASK_SET(this_fpustate, fpustate_alloc());
}

PUBLIC WUNUSED bool NOTHROW(KCALL fpustate_init_nx)(void) {
	struct fpustate *state;
	if (PERTASK_TEST(this_fpustate))
		return true;
	state = fpustate_alloc_nx();
	if unlikely(!state)
		return false;
	PERTASK_SET(this_fpustate, state);
	return true;
}

/* Save the FPU context of the calling thread.
 * This functions are no-ops if the calling thread wasn't the
 * last one to use the FPU, or has never used the FPU at all. */
PUBLIC NOBLOCK void NOTHROW(KCALL fpustate_save)(void) {
	preemption_flag_t was;
	if (PERCPU(thiscpu_fputhread) != THIS_TASK)
		return;
	preemption_pushoff(&was);
	COMPILER_READ_BARRIER();
	if (PERCPU(thiscpu_fputhread) == THIS_TASK) {
		__clts();
		/* The FPU state was changed. */
		assert(PERTASK_TEST(this_fpustate));
		x86_fpustate_save(PERTASK_GET(this_fpustate));
		__wrcr0(__rdcr0() | CR0_TS);
		PERCPU(thiscpu_fputhread) = NULL;
	}
	preemption_pop(&was);
}

/* Similar to `fpustate_save()', but save the state of whichever thread is
 * currently  holding the active FPU context. - When called, this function
 * will  ensure that the most-up-to-date FPU context is written to memory,
 * and will be read back  from memory the next  time that thread (if  any)
 * performs another FPU operation.
 * The main purpose  of this function  is to aid  in implementing FPU  support
 * in  debuggers, where this  function is called  when suspending execution of
 * the associated CPU, after which the debugger can read/write FPU information
 * for any thread by simply looking at `FORTASK(thread, this_fpustate)' */
PUBLIC NOBLOCK void NOTHROW(KCALL fpustate_savecpu)(void) {
	preemption_flag_t was;
	struct task *holder;
	preemption_pushoff(&was);
	holder = PERCPU(thiscpu_fputhread);
	if (holder) {
		assert(!wasdestroyed(holder));
		__clts();

		/* The FPU state was changed. */
		assertf(FORTASK(holder, this_fpustate),
		        "This should have been allocated the first time thread %p used the FPU",
		        holder);

		/* Save the context */
		x86_fpustate_save(FORTASK(holder, this_fpustate));

		/* Disable FPU access (so-as to lazily re-load it
		 * the next time an  access is made by  `holder') */
		__wrcr0(__rdcr0() | CR0_TS);
		PERCPU(thiscpu_fputhread) = NULL;
	}
	preemption_pop(&was);
}


PRIVATE NOBLOCK ATTR_NOINLINE void
NOTHROW(FCALL inplace_swap_fpustate_variant)(struct fpustate *__restrict state) {
	struct fpustate newstate;
	if (fpustate_isssave(state)) {
		sfpustate_to_xfpustate(&state->f_ssave, &newstate.f_xsave);
	} else {
		bzero((byte_t *)&newstate.f_ssave + offsetafter(struct fpustate, f_ssave),
		      sizeof(newstate) - offsetafter(struct fpustate, f_ssave));
		xfpustate_to_sfpustate(&state->f_xsave, &newstate.f_ssave);
	}
	memcpy(state, &newstate, sizeof(struct fpustate));
}


/* Load / Save the FPU context of  the calling thread to/from the given  `state'
 * If no FPU state had yet to be allocated when `fpustate_loadfrom()' is called,
 * a new state will be allocated before returning. */
PUBLIC NOBLOCK void KCALL
fpustate_loadfrom(NCX struct fpustate const *state)
		THROWS(E_SEGFAULT, E_BADALLOC) {
	struct fpustate *mystate;
	mystate = PERTASK_GET(this_fpustate);
	if (mystate) {
		preemption_flag_t was;
		preemption_pushoff(&was);
		/* Make sure that the calling thread isn't the current FPU user. */
		if (PERCPU(thiscpu_fputhread) == THIS_TASK) {
			PERCPU(thiscpu_fputhread) = NULL;
			__wrcr0(__rdcr0() | CR0_TS);
		}
		preemption_pop(&was);
		/* Copy the given state to set it as the new FPU state. */
		memcpy(mystate, state, SIZEOF_FPUSTATE);
	} else {
		mystate = fpustate_alloc_noinit();
		TRY {
			memcpy(mystate, state, SIZEOF_FPUSTATE);
		} EXCEPT {
			fpustate_free(mystate);
			RETHROW();
		}
		/* Save the newly allocated FPU state. */
		PERTASK_SET(this_fpustate, mystate);
	}
	/* XXX: Should we be doing  some kind of verification  here?
	 *      Are there register states that are illegal and would
	 *      result in in exceptions later down the line? */
	if (!!fpustate_isssave(mystate) != (x86_fpustate_variant == FPU_STATE_SSTATE)) {
		/* Inplace-convert the state. */
		inplace_swap_fpustate_variant(mystate);
	}
}

PUBLIC NOBLOCK void KCALL
fpustate_saveinto(NCX struct fpustate *state)
		THROWS(E_SEGFAULT) {
	struct fpustate *mystate;
	if (!PERTASK_TEST(this_fpustate)) {
		bzero(state, SIZEOF_FPUSTATE);
		x86_fpustate_init(state);
		return;
	}

	/* Make sure that the calling thread's FPU state has been saved. */
	fpustate_save();
	mystate = PERTASK_GET(this_fpustate);

	/* This is the only place where we really need to set the FPU state markers. */
	if unlikely(x86_fpustate_variant == FPU_STATE_SSTATE) {
		mystate->f_ssave.__fs_pad2 = 0xffff; /* SSTATE marker */
	} else {
		mystate->f_xsave.fx_fop &= 0x07ff; /* XSTATE marker. */
	}
	memcpy(state, mystate, SIZEOF_FPUSTATE);
}

#ifdef __x86_64__
PUBLIC NOBLOCK void KCALL
fpustate32_loadfrom(NCX struct fpustate32 const *state)
		THROWS(E_SEGFAULT, E_BADALLOC) {
	struct fpustate fst;
	if (fpustate32_isssave(state)) {
		memcpy(&fst.f_ssave, &state->f_ssave, sizeof(struct sfpustate));
	} else {
		fpustate_saveinto(&fst);
		xfpustate_assign_xfpustate32(&fst.f_xsave,
		                             &state->f_xsave);
	}
	fpustate_loadfrom(&fst);
}

PUBLIC NOBLOCK void KCALL
fpustate32_saveinto(NCX struct fpustate32 *state)
		THROWS(E_SEGFAULT) {
	struct fpustate fst;
	fpustate_saveinto(&fst);
	if (x86_fpustate_variant == FPU_STATE_SSTATE) {
		memcpy(&state->f_ssave, &fst.f_ssave, sizeof(struct sfpustate));
	} else {
		xfpustate_to_xfpustate32(&fst.f_xsave, &state->f_xsave);
	}
}
#endif /* __x86_64__ */


INTERN struct icpustate *FCALL /* #NM */
x86_handle_device_not_available(struct icpustate *__restrict state) {
	struct task *old_task, *new_task;
	old_task = PERCPU(thiscpu_fputhread);
	new_task = THIS_TASK;
	COMPILER_BARRIER();
	if (new_task == old_task) {
		/* No other thread used the FPU in the mean time.
		 * We  get here when  preemption disabled the FPU,  only for the original
		 * thread to be the only one to access the FPU once it loops back around. */
		__clts();
	} else {
		struct fpustate *mystate;
		printk(KERN_TRACE "Switch FPU context from task "
		                  "%p[pid=%" PRIuN(__SIZEOF_PID_T__) "] to "
		                  "%p[pid=%" PRIuN(__SIZEOF_PID_T__) "] "
		                  "[pc=%p]\n",
		       old_task, old_task ? task_getroottid_of(old_task) : 0,
		       new_task, task_getroottid_of(new_task),
		       state->ics_irregs.ir_Pip);
		mystate = PERTASK_GET(this_fpustate);
		if (!mystate) {
			/* Try to have interrupts enabled when allocating memory.
			 * By doing this, we prevent the allocation failing with `E_WOULDBLOCK'
			 * if  at  some  point  it  needs  to  do  something  that  may  block. */
			if (state->ics_irregs.ir_Pflags & EFLAGS_IF)
				__sti();

			/* Lazily allocate a new state upon first access.
			 * NOTE: If this causes an exception, that exception
			 *       will   be    propagated   to    user-space. */
			mystate = fpustate_alloc();
			__cli();
			PERTASK_SET(this_fpustate, mystate);

			/* Because we (may) had interrupts enabled again, we must re-read
			 * the currently active FPU task again, as it may have changed in
			 * the mean time. */
			COMPILER_READ_BARRIER();
			old_task = PERCPU(thiscpu_fputhread);
		}

		__clts();
		if (old_task) {
			/* Save the current state within the old context holder. */
			assert(FORTASK(old_task, this_fpustate));
			x86_fpustate_save(FORTASK(old_task, this_fpustate));
		}

		/* Load the new FPU state */
		TRY {
			x86_fpustate_load(mystate);
		} EXCEPT {
			/* Because  we've saved the  old task's state, a  failure to load the
			 * new task's state will may have left the FPU in an undefined state.
			 * -> Because of this, we must indicate that no one is holding the
			 *    active FPU context at this point. */
			PERCPU(thiscpu_fputhread) = NULL;
			RETHROW();
		}
		PERCPU(thiscpu_fputhread) = THIS_TASK;
	}
	return state;
}


/* TODO: FPU Exception handlers. */
//INTDEF struct icpustate *FCALL x86_handle_coprocessor_fault(struct icpustate *__restrict state);
//INTDEF  struct  icpustate   *FCALL  x86_handle_fpu_x87(struct   icpustate  *__restrict   state);
//INTDEF   struct  icpustate  *FCALL   x86_handle_fpu_simd(struct  icpustate  *__restrict  state);



#define CPUID_FEATURES_WRITABLE bootcpu_x86_cpuid_
DATDEF struct cpuinfo bootcpu_x86_cpuid_ ASMNAME("bootcpu_x86_cpuid");


DATDEF u32 x86_fxsave_mxcsr_mask_ ASMNAME("x86_fxsave_mxcsr_mask");

INTDEF byte_t x86_fxsave_section_stmxcsr[];
INTDEF byte_t x86_fxsave_section_savexmm[];
INTDEF byte_t x86_fxrstor_section_ldmxcsr[];
INTDEF byte_t x86_fxrstor_section_loadxmm[];
INTDEF byte_t x86_fpustate_init_mxcsr[];
INTDEF byte_t x86_fpustate_init_ftw_offset_byte;
INTDEF u32 x86_fpustate_init_mxcsr_value;
INTDEF u16 x86_fpustate_init_ftw_value;


#define ENCODE32(x) (x) & 0xff, ((x) & 0xff00) >> 8, ((x) & 0xff0000) >> 16, ((x) & 0xff000000) >> 24
PRIVATE ATTR_FREERODATA byte_t const savexmm_nosse[] = {
#ifdef __x86_64__
	0x48, 0x8d, 0xbf, ENCODE32(OFFSET_XFPUSTATE_XMM(0)), /* leaq   OFFSET_XFPUSTATE_XMM(0)(%rdi), %rdi */
	0x48, 0xc7, 0xc1, ENCODE32(8 * (16 / 4)),            /* movq   $(8 * (16 / 8)), %rcx               */
	0xf3, 0x48, 0xab,                                    /* rep    stosq                               */
#else /* __x86_64__ */
	0x8d, 0xb9, ENCODE32(OFFSET_XFPUSTATE_XMM(0)), /* leal   OFFSET_XFPUSTATE_XMM(0)(%ecx), %edi */
	0xb9,       ENCODE32(8 * (16 / 4)),            /* movl   $(8 * (16 / 4)), %ecx               */
	0xf3, 0xab,                                    /* rep    stosl                               */
	0x5e,                                          /* pop    %esi                                */
	0x5f,                                          /* pop    %edi                                */
#endif /* !__x86_64__ */
	0xc3                                           /* ret                                        */
};

INTERN ATTR_FREEBSS bool x86_config_nofpu = false;
DEFINE_VERY_EARLY_KERNEL_COMMANDLINE_OPTION(x86_config_nofpu,
                                            KERNEL_COMMANDLINE_OPTION_TYPE_BOOL,
                                            "nofpu");

/* Convert sfpustate's FTW to xfpustate's */
INTERN NOBLOCK ATTR_PURE u8
NOTHROW(FCALL x86_fxsave_compress_ftw)(struct sfpustate const *__restrict self) {
	return fpustate_ftw2ftwx(self->fs_ftw);
}

/* Convert xfpustate's FTW to sfpustate's
 * NOTE: Return value is actually a `u16', but use `u32'
 *       so  assembly doesn't have  to movzwl the value! */
INTERN NOBLOCK ATTR_PURE u32
NOTHROW(FCALL x86_fxsave_decompress_ftw)(struct xfpustate const *__restrict self) {
	return fpustate_ftwx2ftw(self->fx_ftw, self->fx_regs);
}


INTERN ATTR_FREETEXT void NOTHROW(KCALL x86_initialize_fpu)(void) {
	u32 cr0;
	if (x86_config_nofpu) {
		printk(FREESTR(KERN_INFO "[fpu] Disable fpu support\n"));
		__wrcr0((__rdcr0() & ~(CR0_MP)) | (CR0_EM | CR0_TS));
setup_fpu_emulation:
		/* TODO: Add an FPU emulation library
		 *       Currently, enabling `nofpu' will cause a DOUBLE_FAULT the first
		 *       time we get  into the  #NM interrupt handler,  because it  will
		 *       recurse into itself... */
		return;
	}

	/* Check for the existence of an FPU. */
	cr0 = __rdcr0() & ~(CR0_EM | CR0_TS);
	if (!X86_HAVE_FPU) {
		u16 testword = 0x55aa;
		__wrcr0(cr0);
		__fninit();
		__asm__ __volatile__("fnstsw %0" : "+m" (testword));
		if (testword != 0) {
			printk(FREESTR(KERN_INFO "[fpu] No co-processor detected\n"));
			cr0 &= ~CR0_MP; /* Disable for emulated FPU */
			cr0 |= CR0_EM | CR0_TS;
			__wrcr0(cr0);
			goto setup_fpu_emulation;
		}
		CPUID_FEATURES_WRITABLE.ci_1d |= CPUID_1D_FPU;
		CPUID_FEATURES_WRITABLE.ci_80000001d |= CPUID_80000001D_FPU;
	}
	printk(FREESTR(KERN_INFO "[fpu] Initializing co-processor\n"));
	if (!(cr0 & CR0_ET)) {
		/* TODO: Only set `CR0_ET' if we're connected to a 387 (as opposed to a 287) */
		cr0 |= CR0_ET;
	}
	if (X86_HAVE_I486)
		cr0 |= CR0_NE; /* Native exceptions enable */
	cr0 |= CR0_MP; /* Enable for native FPU */
	__wrcr0(cr0);

	/* Re-write `x86_fxsave()' and `x86_fxrstor()' based on processor capabilities. */
	if (X86_HAVE_FXSR) {
		if (X86_HAVE_SSE) {
			u32 cr4;
			cr4 = __rdcr4();
			printk(FREESTR(KERN_INFO "[fpu] Enable SSE & #XF exception support\n"));
			cr4 |= (CR4_OSFXSR/* | CR4_OSXMMEXCPT*/); /* TODO: CR4_OSXMMEXCPT */
			__wrcr4(cr4);
		}
		if (!X86_HAVE_SSE) {
			/* No SSE support */
			x86_fxsave_mxcsr_mask_ = 0;
		} else {
			struct xfpustate32 fst;
			fst.fx_mxcsr_mask = 0;
			__fninit();
			__fxsave(&fst);
			if (!fst.fx_mxcsr_mask) /* Intel says that zero should equate `0xffbf' */
				fst.fx_mxcsr_mask = 0x0000ffbf;
			x86_fxsave_mxcsr_mask_ = fst.fx_mxcsr_mask;
		}

		/* Mask the default MXCSR value with what is actually available */
		x86_fpustate_init_mxcsr_value &= x86_fxsave_mxcsr_mask_;
		printk(FREESTR(KERN_INFO "[fpu] Enable native fxsave/fxrstor support [mxcsr_mask=%#I32x]\n"),
		       x86_fxsave_mxcsr_mask_);

		/* The FXSAVE variants version of FTW works differently: a 0-bit means an empty register,
		 * and  a 1-bit means a used register, whereas  FSAVE assigns 2 bits per register, with 3
		 * meaning empty, and 0-2 meaning used, potentially with special values. */
		x86_fpustate_init_ftw_value = 0;

		((byte_t *)&x86_fxsave)[0] = 0x0f; /* fxsave (%ecx) */
		((byte_t *)&x86_fxsave)[1] = 0xae;
		((byte_t *)&x86_fxsave)[2] = 0x01;
		((byte_t *)&x86_fxsave)[3] = 0xc3; /* ret */

		((byte_t *)&x86_fxrstor)[0] = 0x0f; /* fxrstor (%ecx) */
		((byte_t *)&x86_fxrstor)[1] = 0xae;
		((byte_t *)&x86_fxrstor)[2] = 0x09;
		((byte_t *)&x86_fxrstor)[3] = 0xc3; /* ret */
	} else {
		if (X86_HAVE_SSE) {
			/* x86_fxsave_mxcsr_mask_ = 0x0000ffbf; // Already the default */
			__arch_redirect((void *)&x86_fpustate_load, (void const *)&x86_fxrstor);
			__arch_redirect((void *)&x86_fpustate_save, (void const *)&x86_fxsave);
			__arch_redirect((void *)&x86_fpustate_save_noreset, (void const *)&x86_fxsave);
			printk(FREESTR(KERN_INFO "[fpu] Enable #XF exception support\n"));
			__wrcr4(__rdcr4() | CR4_OSXMMEXCPT);
		} else {
			/* None of the MXCSR features are available. */
			x86_fxsave_mxcsr_mask_ = 0;

			/* Disable SSE support in `x86_fxsave()' and `x86_fxrstor()' */
			/* >> movl    %eax, OFFSET_XFPUSTATE_MXCSR(%ecx) */
			x86_fxsave_section_stmxcsr[0] = 0x89;
			x86_fxsave_section_stmxcsr[1] = 0x41;
			x86_fxsave_section_stmxcsr[2] = OFFSET_XFPUSTATE_MXCSR;
			x86_fxsave_section_stmxcsr[3] = 0x90; /* nop */
			/* >> leal   OFFSET_XFPUSTATE_XMM(0)(%ecx), %edi
			 * >> movl   $(8 * (16 / 4)), %ecx
			 * >> rep    stosl */
			memcpy(x86_fxsave_section_savexmm, savexmm_nosse, sizeof(savexmm_nosse));
			x86_fxrstor_section_ldmxcsr[0] = 0xc3; /* ret */
			x86_fxrstor_section_loadxmm[0] = 0xc3; /* ret */

			_x86_fpustate_variant = FPU_STATE_SSTATE;

			((byte_t *)&x86_fpustate_load)[0] = 0xdd; /* frstor (%ecx) */
			((byte_t *)&x86_fpustate_load)[1] = 0x21;
			((byte_t *)&x86_fpustate_load)[2] = 0xc3; /* ret */

			((byte_t *)&x86_fpustate_save)[0] = 0xdd; /* fnsave (%ecx) */
			((byte_t *)&x86_fpustate_save)[1] = 0x31;
			((byte_t *)&x86_fpustate_save)[2] = 0xc3; /* ret */

			((byte_t *)&x86_fpustate_save_noreset)[0] = 0xdd; /* fnsave (%ecx) */
			((byte_t *)&x86_fpustate_save_noreset)[1] = 0x31;
			((byte_t *)&x86_fpustate_save_noreset)[2] = 0xdd; /* frstor (%ecx) */
			((byte_t *)&x86_fpustate_save_noreset)[3] = 0x21;
			((byte_t *)&x86_fpustate_save_noreset)[4] = 0xc3; /* ret */

			x86_fpustate_init_ftw_offset_byte = OFFSET_SFPUSTATE_FTW;
			/* Don't initialize the MXCSR dword, which doesn't exist without SSE */
			x86_fpustate_init_mxcsr[0] = 0xc3; /* ret */
		}
	}

	/* Set the TS bit because while the FPU is now initialized, `thiscpu_fputhread'
	 * isn't   actually   set  to   anything,   much  less   the   calling  thread. */
	__wrcr0(cr0 | CR0_TS);
}

#endif /* CONFIG_HAVE_FPU */

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_FPU_C */
