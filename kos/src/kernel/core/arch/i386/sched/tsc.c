/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_SCHED_TSC_C
#define GUARD_KERNEL_CORE_ARCH_I386_SCHED_TSC_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/x86/alternatives.h>
#include <kernel/x86/apic.h>
#include <kernel/x86/cpuid.h>
#include <kernel/x86/pic.h>
#include <kernel/x86/pit.h>
#include <sched/cpu.h>
#include <sched/pertask.h>
#include <sched/tsc.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>
#include <hybrid/sched/preemption.h>

#include <sys/io.h>

#include <assert.h>
#include <atomic.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/**/
#include "tsc.h" /* CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD */

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>

#include <kos/keyboard.h>

#include <alloca.h>
#include <time.h>
#endif /* !CONFIG_HAVE_KERNEL_DEBUGGER */

#define assert_poison(expr)       assert((expr) || kernel_poisoned())
#define assertf_poison(expr, ...) assertf((expr) || kernel_poisoned(), __VA_ARGS__)


DECL_BEGIN

/* (In HZ): The lowest  distance for  which a  TSC deadline  can be  set.
 *          Attempting to set  something lower than  this will cause  the
 *          kernel to simply spin until the deadline has actually passed. */
#ifndef TSC_MIN_DISTANCE_HZ
#define TSC_MIN_DISTANCE_HZ 10000
#endif /* !TSC_MIN_DISTANCE_HZ */


#ifndef CONFIG_NO_SMP
/* Lock used to synchronize access to the PIT. */
PUBLIC struct atomic_lock x86_pit_lock = ATOMIC_LOCK_INIT;
#endif /* !CONFIG_NO_SMP */


/* The best approximation currently known in regards to the  TSC
 * frequency of this CPU. This frequency should approximately be
 * the same on all CPUs, and  shouldn't change too much as  time
 * goes  on. However minor  adjustments may be  made in order to
 * deal with drifts  and inaccuracies. Also:  the actual HZ  may
 * be a floating point number, and  this value can only ever  be
 * as good of an approximation as we can manage to calculate.
 *
 * NOTE: The value of this variable may only change when preemption
 *       is  enabled, at which  point low-level, arch-specific code
 *       may set-up a periodic  interrupt handler who's purpose  is
 *       to occasionally re-sync the  realtime() clock, as well  as
 *       make minor adjustments to the TSC_HZ.
 *
 * HINT: HZ = ticks_per_second. */
PUBLIC ATTR_PERCPU tsc_hz_t thiscpu_tsc_hz = (tsc_hz_t)PIT_HZ_DIV(X86_PIT_EARLY_HZ) * X86_PIT_EARLY_HZ;

/* Only used in APIC and PIT mode!
 * The emulated TSC deadline value */
INTERN ATTR_PERCPU u64 thiscpu_x86_apic_emutsc_deadline = (u64)-1;

/* Only used in APIC and PIT mode!
 * Alias for `thiscpu_x86_apic_emutsc_initial << thiscpu_x86_apic_emutsc_divide' */
INTERN ATTR_PERCPU u64 thiscpu_x86_apic_emutsc_initial_shifted = PIT_HZ_DIV(X86_PIT_EARLY_HZ);

/* Only used in APIC and PIT mode!
 * The base-line value for the emulated TSC counter. */
INTERN ATTR_PERCPU u64 thiscpu_x86_apic_emutsc_tscbase = 0;

/* Only used in APIC and PIT mode!
 * The last-read value of `APIC_TIMER_CURRENT' */
INTERN ATTR_PERCPU u32 thiscpu_x86_apic_emutsc_prev_current = (u32)-1;

/* Only used in APIC and PIT mode!
 * The current value of `APIC_TIMER_INITIAL' (shadow value) */
INTERN ATTR_PERCPU u32 thiscpu_x86_apic_emutsc_initial = PIT_HZ_DIV(X86_PIT_EARLY_HZ);

/* Only used in APIC and PIT mode!
 * The current shift stored in `APIC_TIMER_DIVIDE' (shadow value)
 * This  variable  contains `ilog2(n)'  of `APIC_TIMER_DIVIDE_Fn' */
INTERN ATTR_PERCPU shift_t thiscpu_x86_apic_emutsc_divide = 0;

/* The minimal  distance for  TSC. Attempts  at
 * setting a distance less than this will fail. */
INTERN ATTR_PERCPU tsc_t thiscpu_x86_apic_emutsc_mindistance = PIT_HZ_DIV(TSC_MIN_DISTANCE_HZ);

/* Only used in APIC and PIT mode!
 * Set to true if an APIC timer interrupt was caught before it was triggered */
INTERN ATTR_PERCPU bool thiscpu_x86_apic_emutsc_early_interrupt = false;



PRIVATE u32 const emutsc_shift_to_divide[8] = {
	/* [ilog2(1)]   = */ APIC_TIMER_DIVIDE_F1,
	/* [ilog2(2)]   = */ APIC_TIMER_DIVIDE_F2,
	/* [ilog2(4)]   = */ APIC_TIMER_DIVIDE_F4,
	/* [ilog2(8)]   = */ APIC_TIMER_DIVIDE_F8,
	/* [ilog2(16)]  = */ APIC_TIMER_DIVIDE_F16,
	/* [ilog2(32)]  = */ APIC_TIMER_DIVIDE_F32,
	/* [ilog2(64)]  = */ APIC_TIMER_DIVIDE_F64,
	/* [ilog2(128)] = */ APIC_TIMER_DIVIDE_F128
};

/* Low-level: read current TSC offset. */
FORCELOCAL WUNUSED u32 NOTHROW(tsc_ll_getcurrent)(void) {
	u32 result;
	COMPILER_BARRIER();
	__asm__ __volatile__(".alt_if %P1\n"
#ifdef __x86_64__
	                     "	movq   x86_lapicbase, %%rax\n"
	                     "	movl   " PP_STR(APIC_TIMER_CURRENT) "(%%rax), %%eax\n"
#else /* __x86_64__ */
	                     "	movl   x86_lapicbase, %%eax\n"
	                     "	movl   " PP_STR(APIC_TIMER_CURRENT) "(%%eax), %%eax\n"
#endif /* !__x86_64__ */
	                     ".alt_else\n"
	                     "	movb   $(" PP_STR(PIT_COMMAND_SELECT_F0)
	                      	       "|" PP_STR(PIT_COMMAND_ACCESS_FLATCH)
	                      	       "|" PP_STR(PIT_COMMAND_FBINARY) "), %%al\n"
	                     "	outb   %%al,  $%P3\n"
	                     "	inb    $%P2, %%al\n"
	                     "	movb   %%al, %%ah\n"
	                     "	inb    $%P2, %%al\n"
	                     "	xchgb  %%al, %%ah\n"
	                     "	movzwl %%ax, %%eax\n"
	                     ".alt_endif\n"
	                     : "=a" (result)
	                     : "X" (X86_FEAT_APIC)
	                     , "X" ((u16)PIT_DATA0)
	                     , "X" ((u16)PIT_COMMAND));
	COMPILER_BARRIER();
	return result;
}

/* Check if a timer interrupt is current pending. */
FORCELOCAL WUNUSED bool NOTHROW(tsc_interrupt_ispending)(void) {
#if 1
	bool result;
	uintptr_t temp;
	COMPILER_BARRIER();
	__asm__ __volatile__(".alt_if %P[x86_feat_apic]\n"
#ifdef __x86_64__
	                     "	movq   x86_lapicbase, %1\n"
#else /* __x86_64__ */
	                     "	movl   x86_lapicbase, %1\n"
#endif /* !__x86_64__ */
	                     "	testl  $%P[lapic_irr_mask], %P[lapic_irr_addr](%1)\n"
	                     ".alt_else\n"
	                     "	movb   $%P[x86_pic_read_irr], %%al\n"
	                     "	outb   %%al, $%P[x86_pic1_cmd]\n"
	                     "	inb    $%P[x86_pic1_cmd], %%al\n"
	                     "	testb  $%P[pic_mask], %%al\n"
	                     ".alt_endif\n"
	                     : "=@ccnz" (result)
	                     , "=&a" (temp)
	                     : [x86_feat_apic] "X" (X86_FEAT_APIC)
	                     , [lapic_irr_addr] "X" (APIC_IRR(APIC_IRR_INDEX(X86_INTNO_PIC1_PIT)))
	                     , [lapic_irr_mask] "X" (APIC_IRR_MASK(X86_INTNO_PIC1_PIT))
	                     , [x86_pic1_cmd] "X" ((u16)X86_PIC1_CMD)
	                     , [pic_mask] "X" (X86_INTNO_PIC1_PIT - X86_INTERRUPT_PIC1_BASE)
	                     , [x86_pic_read_irr] "X" (X86_PIC_READ_IRR));
	COMPILER_BARRIER();
	return result;
#else
	COMPILER_BARRIER();
	return (lapic_read(APIC_IRR(APIC_IRR_INDEX(X86_INTNO_PIC1_PIT))) &
	        /*                */ APIC_IRR_MASK(X86_INTNO_PIC1_PIT)) != 0;
#endif
}

/* Mark an already-pending TSC interrupt as ignored. */
LOCAL NONNULL((1)) void
NOTHROW(FCALL tsc_ignore_pending_interrupt)(struct cpu *__restrict me) {
	if (!FORCPU(me, thiscpu_x86_apic_emutsc_early_interrupt))
		FORCPU(me, thiscpu_x86_apic_emutsc_early_interrupt) = tsc_interrupt_ispending();
}



/* Only used in APIC and PIT mode!
 * [const] Additional delay  needed to  account for  the time  it
 *         takes to read, compare + write the APIC current  timer
 *         during execution of `tsc_ll_cmpxch_divide_and_initial'
 * This delay is valid under `APIC_TIMER_DIVIDE_F1' */
PRIVATE ATTR_PERCPU u32 thiscpu_x86_apic_emutsc_cmpxch_delay = 0;


/* Atomically (as far as as timings go), do the following:
 * >> u32 result;
 * >> result = lapic_read(APIC_TIMER_CURRENT);
 * >> if (result == old_current) {
 * >>     lapic_write(APIC_TIMER_DIVIDE, new_divide);
 * >>     lapic_write(APIC_TIMER_INITIAL, new_initial);
 * >> }
 * >> return result;
 * With the (best-effort) guaranty that the final write  to
 * `APIC_TIMER_INITIAL', when propagating its value back to
 * `APIC_TIMER_CURRENT', the value being replaced inside of
 * `APIC_TIMER_CURRENT' is  equal  to  `old_current',  thus
 * ensuring that no time is lost. */
FORCELOCAL NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) u32
NOTHROW(tsc_ll_cmpxch_divide_and_initial)(struct cpu *__restrict me,
                                          u32 old_current,
                                          u32 new_divide,
                                          u32 new_initial) {
	u32 result;
	COMPILER_BARRIER();
#if 1 /* Do this in assembly (with fixed registers), so we can better control timings!
       * Also: this way we can easily write (similar) code to calibrate the value
       *       for  `thiscpu_x86_apic_emutsc_cmpxch_delay'  during  early   boot. */
	__asm__ __volatile__("movl   " PP_STR(APIC_TIMER_CURRENT) "(%[x86_lapicbase]), %%eax\n"
	                     "subl   %%ecx, %%eax\n"
	                     "cmpl   %%ebx, %%eax\n"
	                     "jne    1f\n"
	                     "movl   %%esi, " PP_STR(APIC_TIMER_DIVIDE) "(%[x86_lapicbase])\n"
	                     "movl   %%edi, " PP_STR(APIC_TIMER_INITIAL) "(%[x86_lapicbase])\n"
	                     "1:\n"
	                     : "=a" (result)
	                     : [x86_lapicbase] "d" (x86_lapicbase)
	                     , "c" (FORCPU(me, thiscpu_x86_apic_emutsc_cmpxch_delay) >>
	                            FORCPU(me, thiscpu_x86_apic_emutsc_divide))
	                     , "b" (old_current)
	                     , "S" (new_divide)
	                     , "D" (new_initial)
	                     : "memory", "cc");
#else
	/* The   C-equivalent   of  the   above   assembly  block.
	 * Only here do aid in visualizing what our function does. */
	result = lapic_read(APIC_TIMER_CURRENT);
	result -= FORCPU(me, thiscpu_x86_apic_emutsc_cmpxch_delay) >>
	          FORCPU(me, thiscpu_x86_apic_emutsc_divide);
	if (result == old_current) {
		lapic_write(APIC_TIMER_DIVIDE, new_divide);
		lapic_write(APIC_TIMER_INITIAL, new_initial);
	}
#endif
	COMPILER_BARRIER();
	return result;
}

PRIVATE NOPREEMPT ATTR_FREETEXT u32
NOTHROW(KCALL x86_calibrate_tsc_cmpxch_delay)(void) {
	u32 r1, r2, r3;
	/* Re-initialize our APIC. (since we trashed its registers during calibration) */
	lapic_write(APIC_TIMER, X86_INTERRUPT_APIC_SPURIOUS | APIC_TIMER_MODE_FPERIODIC);
	lapic_write(APIC_TIMER_DIVIDE, APIC_TIMER_DIVIDE_F1);
	lapic_write(APIC_TIMER_INITIAL, UINT32_MAX);
	COMPILER_BARRIER();
	__asm__ __volatile__("movl   " PP_STR(APIC_TIMER_CURRENT) "(%[x86_lapicbase]), %%eax\n"
	                     "subl   %%ecx, %%eax\n"
	                     "cmpl   %%ebx, %%eax\n"
	                     "jne    1f\n" /* Hopefully this instr will take just as long, even though
	                                    * both of  its  branches  point  to  the  same  address... */
	                     "1:\n"
	                     /* Hopefully, writing to `APIC_EOI' takes just as long as  writing
	                      * to `APIC_TIMER_DIVIDE' and `APIC_TIMER_INITIAL' would. We can't
	                      * write  to the later two, since that would alter/reset the clock
	                      * that we (have to) use for measuring the timings. */
	                     "movl   %%esi, " PP_STR(APIC_EOI) "(%[x86_lapicbase])\n"
	                     "movl   %%esi, " PP_STR(APIC_EOI) "(%[x86_lapicbase])\n"
	                     /* Read  the final current-count  twice, so we can  derive the time it
	                      * takes  to do perform this final write. - After all: We need to know
	                      * the APIC time at this point right here, and not following the first
	                      * read  below. - So we read twice  and use the difference between the
	                      * two  reads to derive the time as it was before the first read (that
	                      * is: right _now_) */
	                     "movl   " PP_STR(APIC_TIMER_CURRENT) "(%[x86_lapicbase]), %%ecx\n"
	                     "movl   " PP_STR(APIC_TIMER_CURRENT) "(%[x86_lapicbase]), %%edx\n"
	                     : "=a" (r1)
	                     , "=c" (r2)
	                     , "=d" (r3)
	                     : [x86_lapicbase] "d" (x86_lapicbase)
	                     , "c" (0)
	                     , "S" (APIC_EOI_FSIGNAL)
	                     : "memory", "cc");
	COMPILER_BARRIER();
	r3 = r2 - r3; /* r3 = <ticks between 2 consecutive reads from APIC_TIMER_CURRENT;
	               *       iow: ticks that 1 such read takes> */
	r2 += r3;     /* r2 = <ticks before 2nd read from APIC_TIMER_CURRENT> */
	r1 -= r2;     /* r1 = <ticks between 1st and 2nd read from APIC_TIMER_CURRENT> */
	return r1;
}

PRIVATE NOPREEMPT ATTR_FREETEXT u32
NOTHROW(KCALL x86_calibrate_tsc_cmpxch_delay_stable)(void) {
	u32 result, new_result;
	result = x86_calibrate_tsc_cmpxch_delay();
	for (;;) {
		/* Repeat the calibration until we get the same result twice in
		 * a row, thus preventing timing variants as the result of code
		 * not having been cached the first time around.
		 * And yes: This does make a _huuge_ difference! */
		new_result = x86_calibrate_tsc_cmpxch_delay();
		if (result == new_result)
			break;
		result = new_result;
	}
	return result;
}


#ifdef CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD
INTERN ATTR_PERCPU tsc_t thiscpu_x86_last_tsc = 0;
#endif /* CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD */


/* Read  and return the current timestamp counter of the calling CPU.
 * The base-line of  the returned  counter is the  calling CPU  being
 * booted,  or more precisely:  some point in  time during before the
 * CPU completed its low-level, arch-specific startup initialization.
 * This function may only be called with preemption disabled. */
PUBLIC NOBLOCK NOPREEMPT WUNUSED NONNULL((1)) tsc_t
NOTHROW(FCALL tsc_get)(struct cpu *__restrict me) {
	tsc_t result;
	u64 tscbase;
	u32 current;
	current = tsc_ll_getcurrent();
	assertf_poison(current <= FORCPU(me, thiscpu_x86_apic_emutsc_initial),
	               "current                                     = %#I32x\n"
	               "FORCPU(me, thiscpu_x86_apic_emutsc_initial) = %#I32x\n"
	               "APIC_TIMER_INITIAL                          = %#I32x\n",
	               current,
	               FORCPU(me, thiscpu_x86_apic_emutsc_initial),
	               lapic_read(APIC_TIMER_INITIAL));
	tscbase = FORCPU(me, thiscpu_x86_apic_emutsc_tscbase);
	if unlikely(current > FORCPU(me, thiscpu_x86_apic_emutsc_prev_current)) {
		/* Interrupt hasn't fired yet. (correct timings ourselves) */
		tscbase += FORCPU(me, thiscpu_x86_apic_emutsc_initial_shifted);
		FORCPU(me, thiscpu_x86_apic_emutsc_tscbase)         = tscbase;
		FORCPU(me, thiscpu_x86_apic_emutsc_early_interrupt) = true;
	}
	FORCPU(me, thiscpu_x86_apic_emutsc_prev_current) = current;
	current = FORCPU(me, thiscpu_x86_apic_emutsc_initial) - current;
	result = tscbase + ((u64)current << FORCPU(me, thiscpu_x86_apic_emutsc_divide));
#ifdef CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD
	assertf_poison(result >= FORCPU(me, thiscpu_x86_last_tsc),
	               "result = %#" PRIxN(__SIZEOF_TSC_HZ_T__) "\n"
	               "last   = %#" PRIxN(__SIZEOF_TSC_HZ_T__) "\n",
	               result, FORCPU(me, thiscpu_x86_last_tsc));
	FORCPU(me, thiscpu_x86_last_tsc) = result;
#endif /* CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD */
	return result;
}

/* Disable the TSC deadline, such that it will never trigger (or at the
 * very least: won't trigger until in  a couple of months or  something
 * like that...) */
PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL tsc_nodeadline)(struct cpu *__restrict me) {
	u32 current_reg;
	u32 old_current_reg;
	u32 new_current_reg;
	u32 delay;
#ifdef CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD
	COMPILER_UNUSED(tsc_get(me));
#endif /* CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD */
	/* TODO: Support for PIC-mode */
	FORCPU(me, thiscpu_x86_apic_emutsc_deadline) = (u64)-1;
	/* Check for simple case: If  initial+divide  didn't change,
	 *                        then we don't have to do anything! */
	if (FORCPU(me, thiscpu_x86_apic_emutsc_initial) == UINT32_MAX &&
	    FORCPU(me, thiscpu_x86_apic_emutsc_divide) == APIC_TIMER_DIVIDE_F128)
		return;
	/* Re-program the LAPIC timer to use the largest, possible delays. */
	delay = 1; /* Initial guess */
again:
	COMPILER_BARRIER();
	current_reg = lapic_read(APIC_TIMER_CURRENT);
	COMPILER_BARRIER();
again_with_timer:
	COMPILER_BARRIER();
	assertf_poison(current_reg <= FORCPU(me, thiscpu_x86_apic_emutsc_initial),
	               "current_reg                                 = %#I32x\n"
	               "FORCPU(me, thiscpu_x86_apic_emutsc_initial) = %#I32x\n"
	               "APIC_TIMER_INITIAL                          = %#I32x\n",
	               current_reg,
	               FORCPU(me, thiscpu_x86_apic_emutsc_initial),
	               lapic_read(APIC_TIMER_INITIAL));
	if unlikely(current_reg > FORCPU(me, thiscpu_x86_apic_emutsc_prev_current)) {
		/* Interrupt hasn't fired yet. (correct timings ourselves) */
		FORCPU(me, thiscpu_x86_apic_emutsc_tscbase) += FORCPU(me, thiscpu_x86_apic_emutsc_initial_shifted);
		FORCPU(me, thiscpu_x86_apic_emutsc_prev_current)    = current_reg;
		FORCPU(me, thiscpu_x86_apic_emutsc_early_interrupt) = true;
		goto again;
	}
	FORCPU(me, thiscpu_x86_apic_emutsc_prev_current) = current_reg;
	/* Update the current register to what it's value will be down below. */
	if (OVERFLOW_USUB(current_reg, delay, &old_current_reg)) {
		/* Special case: Roll-over will (probably) happen during our calculations. */
		preemption_tryyield_nopr();
		/* In case there was a (really long) SMM interrupt,
		 * we need  to  be  able to  deal  with  that,  too */
		delay >>= 1;
		goto again;
	}
	new_current_reg = tsc_ll_cmpxch_divide_and_initial(me,
	                                                   old_current_reg,
	                                                   APIC_TIMER_DIVIDE_F128,
	                                                   UINT32_MAX);
	if (new_current_reg != old_current_reg) {
		new_current_reg %= FORCPU(me, thiscpu_x86_apic_emutsc_initial);
		if (current_reg >= new_current_reg)
			delay = current_reg - new_current_reg;
		current_reg = new_current_reg;
		goto again_with_timer;
	}
	/* Ignore the next TSC interrupt, if it's already pending.
	 * NOTE: Technically,  we'd have to do this atomically alongside
	 *       `tsc_ll_cmpxch_divide_and_initial()', however we should
	 *       be safe to assume that the newly set APIC counter won't
	 *       have already expired at this point. */
	tsc_ignore_pending_interrupt(me);

	/* Remember the updated LAPIC configuration. */
	new_current_reg = FORCPU(me, thiscpu_x86_apic_emutsc_initial) - new_current_reg;
	FORCPU(me, thiscpu_x86_apic_emutsc_tscbase) += (tsc_t)new_current_reg << FORCPU(me, thiscpu_x86_apic_emutsc_divide);
	FORCPU(me, thiscpu_x86_apic_emutsc_prev_current)    = UINT32_MAX;
	FORCPU(me, thiscpu_x86_apic_emutsc_divide)          = 7; /* ilog2(128) */
	FORCPU(me, thiscpu_x86_apic_emutsc_initial)         = UINT32_MAX;
	FORCPU(me, thiscpu_x86_apic_emutsc_initial_shifted) = (u64)UINT32_MAX << 7;
#ifdef CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD
	COMPILER_UNUSED(tsc_get(me));
#endif /* CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD */
}

/* Set the TSC deadline, that is: the point in time when `tsc_interrupt()'
 * should be  called  by  low-level, arch-specific  code.  This  function,
 * together with `tsc_get()', form  the basis for timing-based  scheduling
 * on KOS.
 * NOTE: A previously set deadline is overwritten by later calls to this
 *       function.  If a previous deadline has expired in the mean time,
 *       then `tsc_interrupt()' may or may not be called once the caller
 *       re-enables preemption.
 * @return: * :          The timestamp at the time of the deadline being set.
 * @return: >= deadline: The given `deadline' has already expired.
 * @return: < deadline:  Successfully set the new deadline. */
PUBLIC NOBLOCK NOPREEMPT NONNULL((1)) tsc_t
NOTHROW(FCALL tsc_deadline)(struct cpu *__restrict me,
                            tsc_t deadline) {
	u32 current;
	u32 current_reg;
	u32 old_current_reg;
	u32 new_current_reg;
	u32 initial;
	u32 delay; /* Unshifted TSC delay needed to account for TSC calculations. */
	u8 i, divide;
	tsc_t tsc_current;
	tsc_t tsc_distance;
#ifdef CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD
	COMPILER_UNUSED(tsc_get(me));
#endif /* CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD */
	/* TODO: Support for PIC-mode */
	delay = 1; /* Initial guess */
again:
	COMPILER_BARRIER();

	/* NOTE: All  control  paths between  here  and the
	 *       `tsc_ll_cmpxch_divide_and_initial()' below
	 *       must be timing-safe! */
	current_reg = lapic_read(APIC_TIMER_CURRENT);
	COMPILER_BARRIER();
again_with_timer:
	COMPILER_BARRIER();
	assertf_poison(current_reg <= FORCPU(me, thiscpu_x86_apic_emutsc_initial),
	               "current_reg                                 = %#I32x\n"
	               "FORCPU(me, thiscpu_x86_apic_emutsc_initial) = %#I32x\n"
	               "APIC_TIMER_INITIAL                          = %#I32x\n",
	               current_reg,
	               FORCPU(me, thiscpu_x86_apic_emutsc_initial),
	               lapic_read(APIC_TIMER_INITIAL));
	if unlikely(current_reg > FORCPU(me, thiscpu_x86_apic_emutsc_prev_current)) {
		/* Interrupt hasn't fired yet. (correct timings ourselves) */
		FORCPU(me, thiscpu_x86_apic_emutsc_tscbase) += FORCPU(me, thiscpu_x86_apic_emutsc_initial_shifted);
		FORCPU(me, thiscpu_x86_apic_emutsc_prev_current)    = current_reg;
		FORCPU(me, thiscpu_x86_apic_emutsc_early_interrupt) = true;
		goto again;
	}
	FORCPU(me, thiscpu_x86_apic_emutsc_prev_current) = current_reg;
	current = FORCPU(me, thiscpu_x86_apic_emutsc_initial) - current_reg;

	/* Update the current register to what it's value will be down below. */
	if (OVERFLOW_USUB(current_reg, delay, &old_current_reg)) {
		/* Special case: Roll-over will (probably) happen during our calculations. */
		preemption_tryyield_nopr();

		/* In case there was a (really long) SMM interrupt,
		 * we  need  to be  able  to deal  with  that, too. */
		delay >>= 1;
		goto again;
	}

	/* Figure out the current TSC at the time of the read above. */
	tsc_current = (tsc_t)current << FORCPU(me, thiscpu_x86_apic_emutsc_divide);
	tsc_current += FORCPU(me, thiscpu_x86_apic_emutsc_tscbase);

	/* Check if the deadline has already expired */
	if unlikely(tsc_current >= deadline) {
#if 0 /* Not required */
		tsc_nodeadline(me);
#endif
#ifdef CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD
		COMPILER_UNUSED(tsc_get(me));
#endif /* CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD */
		return tsc_current;
	}

	/* Calculate the TSC once after the clock got reconfigured. */
	tsc_current += delay << FORCPU(me, thiscpu_x86_apic_emutsc_divide);

	/* Check if the deadline will end up being passed when accounting for delay. */
	if unlikely(tsc_current >= deadline) {
		preemption_tryyield_nopr();
		goto again;
	}

	/* Figure out the distance for which we need to calibrate the clock. */
	tsc_distance = deadline - tsc_current;
	if unlikely(tsc_distance <= FORCPU(me, thiscpu_x86_apic_emutsc_mindistance)) {
		/* idle-spin until the deadline has expired.
		 * This must be done because our distance to the deadline is too small
		 * to allow us to safely set-up the APIC/PIT timer interval, and still
		 * be able to safely trace timings.
		 * Imagine setting the initial counter to something like `10'. In that
		 * case  the entire  machine will lock  up because it'll  just keep on
		 * triggering  interrupt  after interrupt,  without leaving  us enough
		 * time to actually handle everything! */
		preemption_tryyield_nopr();
		goto again;
	}

	initial = (u32)-1;
	divide  = 7;

	/* Try  to use small divisions to maximize precision.
	 * As such, have this loop run backwards so we'll end
	 * up with the most precise division in the end.
	 *
	 * I'd normally write this loop like this:
	 * >> initial = (u32)-1;
	 * >> for (divide = 0; divide < 8; ++divide) {
	 * >>     u64 temp = tsc_distance >> i;
	 * >>     if (temp <= (u64)UINT32_MAX) {
	 * >>         initial = temp;
	 * >>         break;
	 * >>     }
	 * >> }
	 * However  that version wouldn't be timing-safe, as it's
	 * runtime depends on the value of `tsc_distance' (making
	 * it O(N)), however  we need  all code here  to be  O(1)
	 * (even if that 1 ends up being > N) */
	i = 8;
	while (i) {
		u64 temp;
		--i;
		temp = tsc_distance >> i;
		/* FIXME: This "if" right here isn't timing-safe! */
		if (temp <= (u64)UINT32_MAX) {
			initial = temp;
			divide  = i;
		}
	}

	/* Check for simple case: If  initial+divide  didn't change,
	 *                        then we don't have to do anything! */
	if (FORCPU(me, thiscpu_x86_apic_emutsc_initial) == initial &&
	    FORCPU(me, thiscpu_x86_apic_emutsc_divide) == divide)
		goto done;

	/* Now that we've figured out everything that we need, atomically
	 * re-configure  the   clock.   in   such  a   manner   that   we */
	new_current_reg = tsc_ll_cmpxch_divide_and_initial(me,
	                                                   old_current_reg,
	                                                   emutsc_shift_to_divide[divide],
	                                                   initial);
	if (new_current_reg != old_current_reg) {
		new_current_reg %= FORCPU(me, thiscpu_x86_apic_emutsc_initial);
		if (current_reg >= new_current_reg)
			delay = current_reg - new_current_reg;
		current_reg = new_current_reg;
		goto again_with_timer;
	}

	/* Ignore the next TSC interrupt, if it's already pending.
	 * NOTE: Technically,  we'd have to do this atomically alongside
	 *       `tsc_ll_cmpxch_divide_and_initial()', however we should
	 *       be safe to assume that the newly set APIC counter won't
	 *       have already expired at this point. */
	tsc_ignore_pending_interrupt(me);

	/* Remember the updated LAPIC configuration. */
	FORCPU(me, thiscpu_x86_apic_emutsc_tscbase)         = tsc_current; /* Absolute TSC time during re-configure. */
	FORCPU(me, thiscpu_x86_apic_emutsc_prev_current)    = initial;     /* Timer was reset, so this becomes `initial' */
	FORCPU(me, thiscpu_x86_apic_emutsc_divide)          = divide;      /* The new division shift */
	FORCPU(me, thiscpu_x86_apic_emutsc_initial)         = initial;     /* The new initial value */
	FORCPU(me, thiscpu_x86_apic_emutsc_initial_shifted) = (u64)initial << divide;
done:
	FORCPU(me, thiscpu_x86_apic_emutsc_deadline) = deadline;
#ifdef CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD
	COMPILER_UNUSED(tsc_get(me));
#endif /* CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD */
	return tsc_current;
}




/* The time that TSC calibration should take, specified as in HZ,  such
 * that calibration  will  take  1/X86_TSC_CALIBRATE_DELAY_HZ  seconds.
 * Note that this value must be `>= 19', since smaller values cannot be
 * properly represented as PIT delays.
 * NOTE: Larger values mean less precise HZ calibrations, but faster init,
 *       while  smaller values  mean more  HZ precision,  but slower init.
 *       100  (iow. 1/100'th of  a second) is a  decent delay that results
 *       in a  total  HZ-error  of  around 0.1%  in  practice.  For  QEMU:
 *       >> [tsc] Boot CPU uses tsc_hz=1001300000
 *       The correct value would be:   1000000000
 * Also note that this constant should not be greater than 100, since APIC
 * initialization  uses the time  it takes to calibrate  the boot CPU's HZ
 * counter for performing  the initial initialization  of secondary  CPUs,
 * which includes one  part where  the kernel must  wait for  at least  10
 * milliseconds  (which ends up  being exactly 1/100'th  of a second), and
 * is therefor spent doing HZ calibration. */
#ifndef X86_TSC_CALIBRATE_DELAY_HZ
#define X86_TSC_CALIBRATE_DELAY_HZ 100
#endif /* !X86_TSC_CALIBRATE_DELAY_HZ */


/* Make sure that the PIT HZ value that we're to use for calibration can
 * even be represented as a constant to be passed to the PIT  circuitry. */
static_assert(PIT_HZ_DIV(X86_TSC_CALIBRATE_DELAY_HZ) <= UINT16_MAX,
              "X86_TSC_CALIBRATE_DELAY_HZ is too low");

/* (Re-)calibrate `thiscpu_tsc_hz' for the calling CPU.
 * This function is arch-specific and called once for each CPU during bootup.
 * NOTE: This function is only called when `X86_HAVE_LAPIC == true' */
PRIVATE NOBLOCK NOPREEMPT ATTR_FREETEXT ATTR_NOINLINE WUNUSED tsc_hz_t
NOTHROW(FCALL x86_tsc_calibrate_hz_cali)(void) {
	u32 remaining;
	tsc_hz_t result;
	unsigned int divide;
	x86_pit_lock_acquire_nopr();
	outb(PIT_COMMAND,
	     PIT_COMMAND_SELECT_F1 |
	     PIT_COMMAND_ACCESS_FLOHI |
	     PIT_COMMAND_MODE_FONESHOT |
	     PIT_COMMAND_FBINARY);

	/* Configure the PIT to trigger after 1/100th of a second (10ms). */
	outb_p(PIT_DATA1, PIT_HZ_DIV(X86_TSC_CALIBRATE_DELAY_HZ) & 0xff);

	/* The PIC timer is now running. -> Start the APIC timer */
	if (X86_HAVE_TSC_DEADLINE) {
		u64 start, end;
		COMPILER_BARRIER();
		outb(PIT_DATA1, (PIT_HZ_DIV(X86_TSC_CALIBRATE_DELAY_HZ) >> 8) & 0xff);
		COMPILER_BARRIER();
		start = __rdtsc();
		COMPILER_BARRIER();

		/* Wait for our one-shot timer to expire. */
		outb(PIT_COMMAND, PIT_COMMAND_SELECT_F1 | PIT_COMMAND_ACCESS_FHI |
		                  PIT_COMMAND_MODE_FONESHOT | PIT_COMMAND_FBINARY);
		while (inb(PIT_DATA1))
			/*preemption_tryyield_nopr()*/;
		outb(PIT_COMMAND, PIT_COMMAND_SELECT_F1 | PIT_COMMAND_ACCESS_FLO |
		                  PIT_COMMAND_MODE_FONESHOT | PIT_COMMAND_FBINARY);
		while (inb(PIT_DATA1))
			/*preemption_tryyield_nopr()*/;
		COMPILER_BARRIER();
		end = __rdtsc();
		COMPILER_BARRIER();
		x86_pit_lock_release_nopr();
		result = end - start;
		return result;
	}
	divide = 0;
again_calibrate:

	/* Make the timer run as slow as possible (to prevent overruns) */
	lapic_write(APIC_TIMER_DIVIDE, emutsc_shift_to_divide[divide]);
	lapic_write(APIC_TIMER,
	            X86_INTERRUPT_APIC_SPURIOUS |
	            APIC_TIMER_MODE_FONESHOT);
	COMPILER_BARRIER();
	outb(PIT_DATA1, (PIT_HZ_DIV(X86_TSC_CALIBRATE_DELAY_HZ) >> 8) & 0xff);
	COMPILER_BARRIER();
	lapic_write(APIC_TIMER_INITIAL, UINT32_MAX); /* Have the timer start at its max value. */
	COMPILER_BARRIER();

	/* Wait for our one-shot timer to expire. */
	outb(PIT_COMMAND, PIT_COMMAND_SELECT_F1 | PIT_COMMAND_ACCESS_FHI |
	                  PIT_COMMAND_MODE_FONESHOT | PIT_COMMAND_FBINARY);
	while (inb(PIT_DATA1))
		/*preemption_tryyield_nopr()*/;
	outb(PIT_COMMAND, PIT_COMMAND_SELECT_F1 | PIT_COMMAND_ACCESS_FLO |
	                  PIT_COMMAND_MODE_FONESHOT | PIT_COMMAND_FBINARY);
	while (inb(PIT_DATA1))
		/*preemption_tryyield_nopr()*/;

	COMPILER_BARRIER();
	remaining = lapic_read(APIC_TIMER_CURRENT); /* Check where we're at now. */
	COMPILER_BARRIER();
	if unlikely(remaining == 0 && divide < 7) {
		/* The APIC timer expired before we were finished...
		 * Increase   the   division   and   try    again... */
		++divide;
		outb(PIT_COMMAND,
		     PIT_COMMAND_SELECT_F1 |
		     PIT_COMMAND_ACCESS_FLOHI |
		     PIT_COMMAND_MODE_FONESHOT |
		     PIT_COMMAND_FBINARY);
		/* Configure the PIT to trigger after 1/100th of a second (10ms). */
		outb_p(PIT_DATA1, PIT_HZ_DIV(X86_TSC_CALIBRATE_DELAY_HZ) & 0xff);
		goto again_calibrate;
	}
	x86_pit_lock_release_nopr();
	result = (tsc_hz_t)(UINT32_MAX - remaining)
	         << divide; /* Account for the timer division */
	return result;
}

PRIVATE NOBLOCK NOPREEMPT ATTR_FREETEXT ATTR_NOINLINE WUNUSED tsc_hz_t
NOTHROW(FCALL x86_tsc_calibrate_hz_offs)(void) {
	u32 remaining;
	tsc_hz_t result;

	/* The PIC timer is now running. -> Start the APIC timer */
	if (X86_HAVE_TSC_DEADLINE) {
		u64 start, end;
		COMPILER_BARRIER();
		start = __rdtsc();
		COMPILER_BARRIER();
		outb(PIT_COMMAND, PIT_COMMAND_SELECT_F1 | PIT_COMMAND_ACCESS_FHI |
		                  PIT_COMMAND_MODE_FONESHOT | PIT_COMMAND_FBINARY);
		inb(PIT_DATA1);
		outb(PIT_COMMAND, PIT_COMMAND_SELECT_F1 | PIT_COMMAND_ACCESS_FLO |
		                  PIT_COMMAND_MODE_FONESHOT | PIT_COMMAND_FBINARY);
		inb(PIT_DATA1);
		COMPILER_BARRIER();
		end = __rdtsc();
		COMPILER_BARRIER();
		return end - start;
	}

	/* Make the timer run as slow as possible (to prevent overruns) */
	lapic_write(APIC_TIMER_DIVIDE, APIC_TIMER_DIVIDE_F1);
	lapic_write(APIC_TIMER,
	            X86_INTERRUPT_APIC_SPURIOUS |
	            APIC_TIMER_MODE_FONESHOT);
	COMPILER_BARRIER();
	lapic_write(APIC_TIMER_INITIAL, UINT32_MAX); /* Have the timer start at its max value. */
	COMPILER_BARRIER();
	outb(PIT_COMMAND, PIT_COMMAND_SELECT_F1 | PIT_COMMAND_ACCESS_FHI |
	                  PIT_COMMAND_MODE_FONESHOT | PIT_COMMAND_FBINARY);
	inb(PIT_DATA1);
	outb(PIT_COMMAND, PIT_COMMAND_SELECT_F1 | PIT_COMMAND_ACCESS_FLO |
	                  PIT_COMMAND_MODE_FONESHOT | PIT_COMMAND_FBINARY);
	inb(PIT_DATA1);
	COMPILER_BARRIER();
	remaining = lapic_read(APIC_TIMER_CURRENT); /* Check where we're at now. */
	COMPILER_BARRIER();
	result = (tsc_hz_t)(UINT32_MAX - remaining);
	return result;
}

PRIVATE NOBLOCK NOPREEMPT ATTR_FREETEXT ATTR_NOINLINE WUNUSED tsc_hz_t
NOTHROW(FCALL x86_tsc_calibrate_hz)(void) {
	tsc_hz_t result;

	/* Do the initial calibration. */
	result = x86_tsc_calibrate_hz_cali();

	/* Don't account for the raw delay caused by performing I/O.
	 * For this purpose, profile the time  it takes to do the  4
	 * unconditional I/O instructions  that had to  be apart  of
	 * the TSC calibration. */
	result -= x86_tsc_calibrate_hz_offs();

	/* Multiply with the delay HZ, because we were running the
	 * test for 1/X86_TSC_CALIBRATE_DELAY_HZ'th  of a  second. */
	result *= X86_TSC_CALIBRATE_DELAY_HZ;
	return result;
}




#ifndef CONFIG_NO_SMP
INTDEF FREE volatile u8 cpu_offline_mask[CEILDIV(CONFIG_MAX_CPU_COUNT, 8)];

/* TODO: This function being  apart of the  .free section is  unsafe!
 *       The boot core may move on  to unmap the .free section  while
 *       a secondary core is still performing initialization in here!
 *       Solution: The boot CPU must wait for secondary CPUs to finish
 *       their inits before unmapping .free!
 * NOTE: This function is only called when `X86_HAVE_LAPIC == true' */
INTERN ATTR_FREETEXT void NOTHROW(KCALL x86_altcore_entry)(void) {
	/* C-level entry point for secondary SMP cores. */
	struct cpu *me  = THIS_CPU;
	unsigned int id = me->c_id;
	tsc_hz_t hz;

	/* Tell the boot-cpu that we're now online. */
	atomic_and(&cpu_offline_mask[id / 8], ~(1 << (id % 8)));

	/* Calculate our TSC frequency. */
	hz = x86_tsc_calibrate_hz();

	/* Store the initial TSC-hz result. */
	FORCPU(me, thiscpu_tsc_hz)                      = hz;
	FORCPU(me, thiscpu_x86_apic_emutsc_mindistance) = hz / TSC_MIN_DISTANCE_HZ;
#ifdef CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD
	FORCPU(me, thiscpu_x86_last_tsc) = 0;
#endif /* CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD */

	if (!X86_HAVE_TSC_DEADLINE) {
		/* Calibrate the TSC-cmpxch delay. */
		FORCPU(me, thiscpu_x86_apic_emutsc_cmpxch_delay) = x86_calibrate_tsc_cmpxch_delay_stable();
	}

	/* Re-initialize our APIC's timer. (since we trashed its registers during calibration) */
	lapic_write(APIC_TIMER, X86_INTNO_PIC1_PIT | APIC_TIMER_MODE_FPERIODIC);
	lapic_write(APIC_TIMER_DIVIDE, APIC_TIMER_DIVIDE_F128);
	lapic_write(APIC_TIMER_INITIAL, UINT32_MAX);
	tsc_ignore_pending_interrupt(me);

	/* Since we've screwed with our APIC, we must
	 * once  again  re-initialize  our  RTC-sync. */
	tsc_resync_init(me);

	printk(FREESTR(KERN_INFO "[tsc] CPU #%u uses tsc_hz=%" PRIuN(__SIZEOF_TSC_HZ_T__) "\n"),
	       me->c_id, hz);
	if (!X86_HAVE_TSC_DEADLINE) {
		printk(FREESTR(KERN_INFO "[tsc] CPU #%u uses tsc_cmpxch_delay=%" PRIu32 "\n"),
		       me->c_id, FORCPU(me, thiscpu_x86_apic_emutsc_cmpxch_delay));
	}
}
#endif /* !CONFIG_NO_SMP */


/* Called from APIC initialization to calibrate the initial HZ of the boot cpu.
 * NOTE: This function is only called when `X86_HAVE_LAPIC == true' */
INTERN ATTR_FREETEXT void NOTHROW(KCALL x86_calibrate_boottsc)(void) {
	tsc_hz_t hz;

	/* Calibrate the APIC */
	hz = x86_tsc_calibrate_hz();
	FORCPU(&bootcpu, thiscpu_tsc_hz)                          = hz;
	FORCPU(&bootcpu, thiscpu_x86_apic_emutsc_tscbase)         = 0;
	FORCPU(&bootcpu, thiscpu_x86_apic_emutsc_prev_current)    = UINT32_MAX;
	FORCPU(&bootcpu, thiscpu_x86_apic_emutsc_divide)          = 7;
	FORCPU(&bootcpu, thiscpu_x86_apic_emutsc_deadline)        = (u64)-1;
	FORCPU(&bootcpu, thiscpu_x86_apic_emutsc_initial)         = UINT32_MAX;
	FORCPU(&bootcpu, thiscpu_x86_apic_emutsc_initial_shifted) = (u64)UINT32_MAX << 7;
	FORCPU(&bootcpu, thiscpu_x86_apic_emutsc_early_interrupt) = false;
	FORCPU(&bootcpu, thiscpu_x86_apic_emutsc_mindistance)     = hz / TSC_MIN_DISTANCE_HZ;
#ifdef CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD
	FORCPU(&bootcpu, thiscpu_x86_last_tsc) = 0;
#endif /* CONFIG_HAVE_KERNEL_X86_TSC_ASSERT_FORWARD */
	if (!X86_HAVE_TSC_DEADLINE) {
		/* Calibrate the TSC-cmpxch delay.
		 * On QEMU, this ends up being either 200 or 300 (the actual result appears
		 * inconsistent, and it seems like QEMU only increments the APIC counter in
		 * multiples of 100, so that kind-of sucks...)
		 *
		 * Since  we do already know our HZ at this point, we could in theory once
		 * again  use the PIT to determine the timings of for this, however I feel
		 * like doing it that way would only introduce further inaccuracies due to
		 * having to convert timings back-and-forth... */
		FORCPU(&bootcpu, thiscpu_x86_apic_emutsc_cmpxch_delay) = x86_calibrate_tsc_cmpxch_delay_stable();
	}

	/* Re-initialize our APIC's timer. (since we trashed its registers during calibration) */
	lapic_write(APIC_TIMER, X86_INTNO_PIC1_PIT | APIC_TIMER_MODE_FPERIODIC);
	lapic_write(APIC_TIMER_DIVIDE, APIC_TIMER_DIVIDE_F128);
	lapic_write(APIC_TIMER_INITIAL, UINT32_MAX);
	tsc_ignore_pending_interrupt(&bootcpu);

	/* Initialize the RTC proper. */
	tsc_resync_init(&bootcpu);
	printk(FREESTR(KERN_INFO "[tsc] Boot CPU uses tsc_hz=%" PRIuN(__SIZEOF_TSC_HZ_T__) "\n"), hz);
	if (!X86_HAVE_TSC_DEADLINE) {
		printk(FREESTR(KERN_INFO "[tsc] Boot CPU uses tsc_cmpxch_delay=%" PRIu32 "\n"),
		       FORCPU(&bootcpu, thiscpu_x86_apic_emutsc_cmpxch_delay));
	}
}



extern FREE byte_t x86_native_tsc_get[];
extern byte_t x86_native_tsc_get_size[];
#define x86_native_tsc_get_size ((size_t)x86_native_tsc_get_size)

extern FREE byte_t x86_native_tsc_nodeadline[];
extern byte_t x86_native_tsc_nodeadline_size[];
#define x86_native_tsc_nodeadline_size ((size_t)x86_native_tsc_nodeadline_size)

extern FREE byte_t x86_native_tsc_deadline[];
extern byte_t x86_native_tsc_deadline_size[];
#define x86_native_tsc_deadline_size ((size_t)x86_native_tsc_deadline_size)

extern FREE byte_t x86_native_tsc_getdeadline[];
extern byte_t x86_native_tsc_getdeadline_size[];
#define x86_native_tsc_getdeadline_size ((size_t)x86_native_tsc_getdeadline_size)

INTERN ATTR_FREETEXT void NOTHROW(KCALL x86_initialize_tsc)(void) {
	if (X86_HAVE_TSC_DEADLINE) {
		/* Use APIC+TSC  (in `APIC_TIMER_MODE_FTSCDEADLINE'-mode) */
		printk(FREESTR(KERN_INFO "[tsc] Use APIC+TSC for timings\n"));
		memcpy((byte_t *)&tsc_get,
		       x86_native_tsc_get,
		       x86_native_tsc_get_size);
		memcpy((byte_t *)&tsc_nodeadline,
		       x86_native_tsc_nodeadline,
		       x86_native_tsc_nodeadline_size);
		memcpy((byte_t *)&tsc_deadline,
		       x86_native_tsc_deadline,
		       x86_native_tsc_deadline_size);
		memcpy((byte_t *)&tsc_getdeadline,
		       x86_native_tsc_getdeadline,
		       x86_native_tsc_getdeadline_size);
	} else if (X86_HAVE_LAPIC) {
		/* Use APIC */
		printk(FREESTR(KERN_INFO "[tsc] Use APIC for timings\n"));
		/* TODO: ```
		 *    If CPUID.06H:EAX.ARAT[bit 2] = 1, the processor's APIC timer runs at a constant rate [...].
		 *    If CPUID.06H:EAX.ARAT[bit 2] = 0 or if CPUID 06H is not supported, the APIC timer may temporarily stop [...].
		 * ```
		 */

	} else {
		/* Use PIT */
		printk(FREESTR(KERN_INFO "[tsc] Use PIT for timings\n"));
	}
}


#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
DBG_COMMAND(clockinfo,
            "clockinfo\n"
            "\tDisplay information about hardware timings") {
	void *buf;
	bool was_cursor_visible;
	u32 oldcur;
	struct cpu *me = dbg_cpu;

	/* Save terminal settings and display contents. */
	was_cursor_visible = dbg_setcur_visible(false);
	buf      = alloca(dbg_screen_width * dbg_screen_height * dbg_screen_cellsize);
	oldcur   = dbg_getcur();
	dbg_logecho_pushoff();
	dbg_savecolor();
	dbg_getscreendata(0, 0, dbg_screen_width, dbg_screen_height, buf);
	dbg_setcolor(ANSITTY_CL_BLACK, ANSITTY_CL_LIGHT_GRAY);
	dbg_hline(0, dbg_screen_height - 1, dbg_screen_width, ' ');
	dbg_pprint(0, dbg_screen_height - 1, DBGSTR("Press ESC to exit"));
	dbg_setcolor(ANSITTY_CL_LIGHT_GRAY, ANSITTY_CL_BLACK);
	for (;;) {
		preemption_flag_t was;
		tsc_t now_tsc;
		ktime_t now_ktime;
		struct timespec now_timespec;
		struct tm now_tm;
		preemption_pushoff(&was);
		now_tsc   = tsc_get(me);
		now_ktime = tsc_now_to_ktime(me, now_tsc);
		preemption_pop(&was);
		now_timespec = ktime_to_timespec(now_ktime);
		localtime_r(&now_timespec.tv_sec, &now_tm);
		dbg_beginupdate();
		dbg_fillbox(0, 0, dbg_screen_width, dbg_screen_height - 1, ' ');
		dbg_pprintf(0, dbg_screen_height > 14 ? (dbg_screen_height - 14) / 2 : 0,
		            DBGSTR("tsc:      " AC_WHITE("%" PRIuN(__SIZEOF_TSC_T__)) "\n"
		                   "ktime:    " AC_WHITE("%" PRIuN(__SIZEOF_KTIME_T__)) "\n"
		                   "timespec: " AC_WHITE("%" PRIuN(__SIZEOF_TIME_T__) ".%.9" PRIuN(__SIZEOF_SYSCALL_LONG_T__)) "\n"
		                   "realtime: " AC_WHITE("%.4u-%.2u-%.2uT%.2u:%.2u:%.2u.%.9" PRIuN(__SIZEOF_SYSCALL_LONG_T__)) "\n"
		                   "tsc.hz:   " AC_WHITE("%" PRIuN(__SIZEOF_TSC_HZ_T__)) "\n"
		                   "x86.apic.emutsc.deadline:        " AC_WHITE("%" PRIu64) "\n"
		                   "x86.apic.emutsc.initial_shifted: " AC_WHITE("%" PRIu64) "\n"
		                   "x86.apic.emutsc.tscbase:         " AC_WHITE("%" PRIu64) "\n"
		                   "x86.apic.emutsc.prev_current:    " AC_WHITE("%" PRIu32) "\n"
		                   "x86.apic.emutsc.initial:         " AC_WHITE("%" PRIu32) "\n"
		                   "x86.apic.emutsc.divide:          " AC_WHITE("%" PRIu8) "\n"
		                   "x86.apic.emutsc.mindistance:     " AC_WHITE("%" PRIuN(__SIZEOF_TSC_T__)) "\n"
		                   "x86.apic.emutsc.early_interrupt: " AC_WHITE("%s") "\n"
		                   "x86.apic.emutsc.cmpxch_delay:    " AC_WHITE("%" PRIu32) "\n"),
		            now_tsc, now_ktime, now_timespec.tv_sec, now_timespec.tv_nsec,
		            now_tm.tm_year + 1900, now_tm.tm_mon + 1, now_tm.tm_mday,
		            now_tm.tm_hour, now_tm.tm_min, now_tm.tm_sec, now_timespec.tv_nsec,
		            FORCPU(me, thiscpu_tsc_hz),
		            FORCPU(me, thiscpu_x86_apic_emutsc_deadline),
		            FORCPU(me, thiscpu_x86_apic_emutsc_initial_shifted),
		            FORCPU(me, thiscpu_x86_apic_emutsc_tscbase),
		            FORCPU(me, thiscpu_x86_apic_emutsc_prev_current),
		            FORCPU(me, thiscpu_x86_apic_emutsc_initial),
		            FORCPU(me, thiscpu_x86_apic_emutsc_divide),
		            FORCPU(me, thiscpu_x86_apic_emutsc_mindistance),
		            FORCPU(me, thiscpu_x86_apic_emutsc_early_interrupt) ? DBGSTR("true") : DBGSTR("false"),
		            FORCPU(me, thiscpu_x86_apic_emutsc_cmpxch_delay));
		dbg_endupdate(true);
		if (dbg_trygetkey() == KEY_ESC)
			break;
	}

	/* Restore display contents and terminal settings. */
	dbg_setscreendata(0, 0, dbg_screen_width, dbg_screen_height, buf);
	dbg_loadcolor();
	dbg_logecho_pop();
	dbg_setcur(DBG_GETCUR_X(oldcur), DBG_GETCUR_Y(oldcur));
	dbg_setcur_visible(was_cursor_visible);
	return 0;
}
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_SCHED_TSC_C */
