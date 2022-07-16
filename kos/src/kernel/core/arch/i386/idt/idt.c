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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_IDT_IDT_C
#define GUARD_KERNEL_CORE_ARCH_I386_IDT_IDT_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/rt.h>
#include <kernel/except.h>
#include <kernel/isr.h>
#include <kernel/malloc.h>
#include <kernel/printk.h>
#include <kernel/types.h>
#include <kernel/x86/idt-foreach.h>
#include <kernel/x86/idt.h>
#include <kernel/x86/pic.h>
#include <sched/cpu.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <asm/intrin.h>
#include <kos/kernel/cpu-state.h>
#include <kos/kernel/segment.h>
#include <kos/sched/shared-lock.h>

#include <assert.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#ifdef CONFIG_NO_KERNEL_DEBUGGER
#define ISR_DEFINE_HILO(id)           \
	INTDEF byte_t __x86_idtlo_##id[]; \
	INTDEF byte_t __x86_idthi_##id[];
#elif defined(CONFIG_NO_SMP)
#define ISR_DEFINE_HILO(id)              \
	INTDEF byte_t __x86_idtlo_##id[];    \
	INTDEF byte_t __x86_idthi_##id[];    \
	INTDEF byte_t __x86_dbgidtlo_##id[]; \
	INTDEF byte_t __x86_dbgidthi_##id[];
#else /* CONFIG_NO_KERNEL_DEBUGGER */
#define ISR_DEFINE_HILO(id)                     \
	INTDEF byte_t __x86_idtlo_##id[];           \
	INTDEF byte_t __x86_idthi_##id[];           \
	INTDEF byte_t __x86_dbgidtlo_##id[];        \
	INTDEF byte_t __x86_dbgidthi_##id[];        \
	INTDEF byte_t __x86_dbgaltcoreidtlo_##id[]; \
	INTDEF byte_t __x86_dbgaltcoreidthi_##id[];
#endif /* !CONFIG_NO_KERNEL_DEBUGGER */
IDT_X86_FOREACH(ISR_DEFINE_HILO)
#undef ISR_DEFINE_HILO
#ifdef __x86_64__
#define ISR_DEFINE_HILO(prefix, id)       \
	/* [0x##id] = */ {                    \
		/* .i_seg = */ { {                \
			 .s_u = (u64)prefix##lo_##id, \
		} },                              \
		/* .i_ext = */ { {                \
			 .s_u = (u64)prefix##hi_##id, \
		} }                               \
	},
#else /* __x86_64__ */
#define ISR_DEFINE_HILO(prefix, id)             \
	/* [0x##id] = */ {                          \
		/* .i_seg = */ { { {                    \
			/* .s_ul = */ (u32)prefix##lo_##id, \
			/* .s_uh = */ (u32)prefix##hi_##id  \
		} } }                                   \
	},
#endif /* !__x86_64__ */


/************************************************************************/
/* The Default InterruptDescriptorTable used by KOS                     */
/************************************************************************/
PUBLIC ATTR_HOTDATA struct idt_segment x86_idt[256] = {
#define ISR_DEFINE(id) ISR_DEFINE_HILO(__x86_idt, id)
	IDT_X86_FOREACH(ISR_DEFINE)
#undef ISR_DEFINE
};

PUBLIC_CONST ATTR_COLDRODATA struct desctab const x86_idt_ptr = {
	.dt_limit = sizeof(x86_idt) - 1,
	.dt_base  = (uintptr_t)x86_idt
};


/************************************************************************/
/* The InterruptDescriptorTable used by the builtin debugger            */
/************************************************************************/
#ifndef CONFIG_NO_KERNEL_DEBUGGER
PUBLIC ATTR_COLDDATA struct idt_segment x86_dbgidt[256] = {
#define ISR_DEFINE(id) ISR_DEFINE_HILO(__x86_dbgidt, id)
	IDT_X86_FOREACH(ISR_DEFINE)
#undef ISR_DEFINE
};

PUBLIC_CONST ATTR_COLDRODATA struct desctab const x86_dbgidt_ptr = {
	.dt_limit = sizeof(x86_dbgidt) - 1,
	.dt_base  = (uintptr_t)x86_dbgidt
};

#ifndef CONFIG_NO_SMP
PUBLIC ATTR_COLDDATA struct idt_segment x86_dbgaltcoreidt[256] = {
#define ISR_DEFINE(id) ISR_DEFINE_HILO(__x86_dbgaltcoreidt, id)
	IDT_X86_FOREACH(ISR_DEFINE)
#undef ISR_DEFINE
};

PUBLIC_CONST ATTR_COLDRODATA struct desctab const x86_dbgaltcoreidt_ptr = {
	.dt_limit = sizeof(x86_dbgaltcoreidt) - 1,
	.dt_base  = (uintptr_t)x86_dbgaltcoreidt
};
#endif /* !CONFIG_NO_SMP */
#endif /* !CONFIG_NO_KERNEL_DEBUGGER */

/* Lock used to guard against multiple threads modifying the IDT */
PRIVATE ATTR_COLDBSS struct shared_lock x86_idt_modify_lock = SHARED_LOCK_INIT;

/* [0..1][lock(x86_idt_modify_lock)]
 * The temporary IDT copy that is in-use while the original IDT is getting modified. */
PRIVATE ATTR_COLDBSS struct idt_segment *x86_idt_modify_copy = NULL;


#ifndef CONFIG_NO_SMP
PRIVATE ATTR_COLDBSS unsigned int x86_idt_setcurrent_ack = 0;
PRIVATE NOBLOCK ATTR_COLDTEXT NONNULL((1, 2)) struct icpustate *
NOTHROW(FCALL x86_idt_setcurrent_ipi)(struct icpustate *__restrict state,
                                      void *args[CPU_IPI_ARGCOUNT]) {
	__lidt_p(args[0]);
	ATOMIC_INC(x86_idt_setcurrent_ack);
	printk(KERN_DEBUG "[idt#%u] Acknowledge new IDT\n",
	       THIS_CPU->c_id);
	return state;
}
#endif /* !CONFIG_NO_SMP */

/* Set   the  IDT  base  pointer  currently  in  use  on  all  CPUs.
 * This function only returns once all CPUs have updated their IDTs. */
PRIVATE NOBLOCK ATTR_COLDTEXT void
NOTHROW(FCALL x86_idt_setcurrent)(struct desctab const *__restrict ptr) {
	/* TODO: When a CPU goes into deep-sleep, we must save,  and
	 *       during the next wake-up, restore, the current IDTR!
	 * NOTE: The same also goes for the GDTR, LDTR and TR, all  of
	 *       which should really be saved in some PERCPU variables
	 *       whenever a CPU goes into deep sleep, and be  restored
	 *       whenever the CPU comes back to live!
	 * NOTE: Possibly, we could even go so far as-to save CRn registers.
	 * Also: Check if we're actually restoring DRn registers, as already
	 *       defined on a per-mman basis! */
	printk(KERN_DEBUG "[idt] Set new IDT {%p, %#" PRIx16 "}\n",
	       ptr->dt_base, ptr->dt_limit);

	COMPILER_BARRIER();
#ifndef CONFIG_NO_SMP
	{
		unsigned int count;
		void *args[CPU_IPI_ARGCOUNT];
		ATOMIC_WRITE(x86_idt_setcurrent_ack, 0);
		args[0] = (void *)ptr;
		/* NOTE: We always set the `CPU_IPI_FWAKEUP' flag, even though  doing
		 *       so is kind-of excessive, simply because we don't want to run
		 *       any risk of not being able  to reach some specific CPU  when
		 *       that CPU is currently waking up, or has gone to sleep  after
		 *       having received a  previous IDT override  request, with  the
		 *       current invocation of `x86_idt_setcurrent()' relating to the
		 *       old (original) IDT base address being restored. */
		count = cpu_broadcastipi_notthis(&x86_idt_setcurrent_ipi, args,
		                                 CPU_IPI_FWAKEUP | CPU_IPI_FWAITFOR);
		while (ATOMIC_READ(x86_idt_setcurrent_ack) < count)
			task_pause();
	}
#endif /* !CONFIG_NO_SMP */
	if (!dbg_active) {
		/* Finally, apply the new IDT within the calling CPU. */
		__lidt_p(ptr);
	}
	COMPILER_BARRIER();
}




/* Start modifying `x86_idt'
 * This function must be called prior to making modifications to `x86_idt'.
 * Doing this  is required  to prevent  other CPUs/threads  from  servicing
 * interrupts   with   IDT   segments   that   aren't   fully  initialized.
 * As  such,  any  modifications  made  to  `x86_idt'  after  this function
 * is called  will only  come into  effect once  `x86_idt_modify_end()'  is
 * called. These functions are implemented as:
 *   x86_idt_modify_begin():
 *     - Acquire an internal mutex
 *     - Allocate an internal copy of the IDT
 *     - Copy `x86_idt' into the internal copy
 *     - Broadcast an IPI, telling all CPUs to lidt() the internal copy
 *   x86_idt_modify_end():
 *     - if (discard_changes) x86_idt = <INTERNAL_COPY>;
 *     - Broadcast an IPI, telling all CPUs to `lidt(&x86_idt_ptr)'
 *     - Free the internal copy previously allocated by `x86_idt_modify_begin()'
 *     - Release the internal mutex
 * Using this method, changes can be staged for eventual use in  `x86_idt',
 * without running the risk of any CPU/thread ever accessing an incomplete/
 * corrupt IDT entry.
 * When calling  `x86_idt_modify_end()', the  caller is  responsible to  ensure
 * that the call was preceded by `x86_idt_modify_begin()', as well as to ensure
 * that any call to `x86_idt_modify_begin()' is eventually followed by  another
 * call to `x86_idt_modify_end()'
 * Also note that these  functions must not be  called recursively from the  same
 * thread. - A call to `x86_idt_modify_begin()' must _NOT_ be followed by another
 * call to `x86_idt_modify_begin()' from the same thread!
 * @param: nx:     When true, don't do anything that could throw an exception, or block.
 * @return: true:  Success (always returned when `nx == false')
 * @return: false: Failure (only ever returned when `nx == true') */
PUBLIC ATTR_COLDTEXT bool FCALL x86_idt_modify_begin(bool nx)
		THROWS(E_BADALLOC, E_WOULDBLOCK, E_INTERRUPT) {
	struct idt_segment *copy;
	struct desctab dt;
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	if unlikely(dbg_active)
		return true; /* no-op */
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */
	if (nx) {
		copy = (struct idt_segment *)kmalloc_nx(256 * sizeof(struct idt_segment),
		                                        GFP_LOCKED | GFP_PREFLT | GFP_ATOMIC);
		if unlikely(!copy)
			return false;
	} else {
		copy = (struct idt_segment *)kmalloc(256 * sizeof(struct idt_segment),
		                                     GFP_LOCKED | GFP_PREFLT);
	}
	if (!shared_lock_tryacquire(&x86_idt_modify_lock)) {
		if (nx) {
			kfree(copy);
			return false;
		}
		TRY {
			shared_lock_acquire(&x86_idt_modify_lock);
		} EXCEPT {
			kfree(copy);
			RETHROW();
		}
	}
	assert(!x86_idt_modify_copy);
	/* Fill in the IDT copy. */
	memcpy(copy, x86_idt, 256, sizeof(struct idt_segment));
	x86_idt_modify_copy = copy;
	/* Set the IDT copy as the IDT exclusively used everywhere */
	dt.dt_base  = (uintptr_t)copy;
	dt.dt_limit = (256 * sizeof(struct idt_segment)) - 1;
	x86_idt_setcurrent(&dt);
	return true;
}

PUBLIC NOBLOCK ATTR_COLDTEXT void
NOTHROW(FCALL x86_idt_modify_end)(bool discard_changes) {
	struct idt_segment *copy;
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
	if unlikely(dbg_active) {
		assert(!discard_changes);
		/* Simply force an IDT re-load */
		x86_idt_setcurrent(&x86_idt_ptr);
		return;
	}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */
	assert(shared_lock_acquired(&x86_idt_modify_lock));
	assert(x86_idt_modify_copy);
	copy = x86_idt_modify_copy;
	x86_idt_modify_copy = NULL;

	/* Check if we're supposed to discard any changes made. */
	if (discard_changes)
		memcpy(x86_idt, copy, 256, sizeof(struct idt_segment));

	/* Restore the used IDT within all CPUs */
	x86_idt_setcurrent(&x86_idt_ptr);

	/* Release the IDT modifications lock. */
	shared_lock_release(&x86_idt_modify_lock);

	/* Free the temporary IDT copy */
	kfree(copy);
}


PUBLIC ATTR_PERCPU struct x86_spurious_interrupts
thiscpu_x86_spurious_interrupts = { 0, 0, 0 };

INTERN void KCALL x86_pic1_spur(void) {
	struct x86_spurious_interrupts *spi;
	spi = &PERCPU(thiscpu_x86_spurious_interrupts);
	++spi->sp_pic1;
}

INTERN void KCALL x86_pic2_spur(void) {
	struct x86_spurious_interrupts *spi;
	spi = &PERCPU(thiscpu_x86_spurious_interrupts);
	++spi->sp_pic2;
}

INTERN void KCALL x86_apic_spur(void) {
	struct x86_spurious_interrupts *spi;
	spi = &PERCPU(thiscpu_x86_spurious_interrupts);
	++spi->sp_apic;
}


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_IDT_IDT_C */
