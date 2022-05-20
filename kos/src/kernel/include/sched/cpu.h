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
#ifndef GUARD_KERNEL_INCLUDE_SCHED_CPU_H
#define GUARD_KERNEL_INCLUDE_SCHED_CPU_H 1

#include <kernel/compiler.h>

#include <kernel/paging.h> /* pagedir_phys_t */
#include <sched/pertask.h>

#include <hybrid/__bit.h>
#include <hybrid/__overflow.h>
#include <hybrid/typecore.h>

#include <kos/kernel/types.h>

#include <stdbool.h>

DECL_BEGIN

/* NOTE: When talking about a CPU having `work left to be done', what is meant one of these:
 *  - The CPU is hosting at least 1 thread (that isn't its IDLE thread)
 *    as part of the active chain of running tasks.
 *  - The CPU is hosting at least 1  thread with the KEEPCORE flag set,  regardless
 *    of which state that thread may be in (may the thread be sleeping, or running) */

#define CPU_STATE_DREAMING       0x0000 /* The CPU is fast asleep
                                         *  - Only used by secondary cores
                                         *  - Preemptive interrupts are disabled
                                         *  - Outside interrupts  are not  responded to,  except
                                         *    for when running on the boot CPU, where Preemption
                                         *    will remain enabled when `__hlt()' is called. */
#define CPU_STATE_FALLING_ASLEEP 0x0001 /* The CPU is currently falling asleep.
                                         *  - Preemption  is   disabled,  but   `cpu_deepwake()'
                                         *    should not stop the CPU before it has fully fallen
                                         *    asleep, or has woken up again after noticing  that
                                         *    there is still work left to be done.
                                         *  - This is a transitional state used to describe an
                                         *    idling CPU that is  currently checking if it  is
                                         *    allowed to fall asleep.
                                         *  - During this state, preemptive interrupts are disabled,
                                         *    alongside  other  CPU-specific machinery  being turned
                                         *    off in order to save power. */
#define CPU_STATE_RUNNING        0x0002 /* The CPU is fully up and running, hosting any number of threads. */
#define CPU_STATE_GETTING_UP     0x0003 /* An INIT IPI is being / has been send to the CPU, and the
                                         * core  is  currently  in  the  process  of  startup   up.
                                         * This state is transitioned to `CPU_STATE_RUNNING' at the end  of
                                         * the internal CPU initialization phase (the i386 variant of which
                                         * is implemented in `arch/i386/sched/smp32.S') */

#ifdef __CC__

struct task;

struct cpu {
	unsigned int        c_id;       /* The ID of this CPU. */
	WEAK u16            c_state;    /* CPU State (one of `CPU_STATE_*') */
#if ((__SIZEOF_INT__ + 2) % __SIZEOF_POINTER__) != 0
	u16                _c_pad[__SIZEOF_POINTER__ - ((__SIZEOF_INT__ + 2) % __SIZEOF_POINTER__)]; /* ... */
#endif /* ((__SIZEOF_INT__ + 2) % __SIZEOF_POINTER__) != 0 */
#ifndef CONFIG_NO_SMP
	WEAK pagedir_phys_t c_pdir; /* [1..1][lock(READ(*), WRITE(THIS_CPU))]
	                             * The currently used  page directory. When  `mman_sync()' is  called,
	                             * this field is  checked for  all configured  CPUs, and  if equal  to
	                             * the MMan that is being synced, our CPU will receive an IPI, telling
	                             * us  that we need to (possibly partially) invalidate our TLB caches.
	                             * s.a. `mman_sync()', `pagedir_sync_smp_p()', `pagedir_sync()' */
#endif /* !CONFIG_NO_SMP */
	/* Per-CPU data goes here. */
};


#ifndef __realtime_defined
#define __realtime_defined
/* Returns the current real time derived from the current CPU time.
 * WARNING: KOS only gives a best-effort guaranty for this function
 *          in terms of  consistency when it  comes to the  calling
 *          thread being moved to a different CPU.
 *          There is a chance  of minor inconsistencies in  terms
 *          of exact nano-second values returned by this function
 *          when the calling thread is moved.
 * However, it is guarantied that (so long as `settimeofday()'  isn't
 * called), calling this function repeatedly from the threads  hosted
 * by the same CPU will _always_ return values such that later values
 * are >= earlier values. */
FUNDEF NOBLOCK WUNUSED struct timespec NOTHROW(KCALL realtime)(void);
#endif /* !__realtime_defined */

/* [!0][<= CONFIG_MAX_CPU_COUNT][const] The total number of known CPUs. */
DATDEF unsigned int const cpu_count;

#ifndef CONFIG_NO_SMP
/* Number of CPUs with a state set to `CPU_STATE_RUNNING'
 * This value is incremented when a cpu changes state to `CPU_STATE_RUNNING'
 * as  the result of a call to `cpu_wake()' when an INIT IPI is used, and is
 * decremented   when   a   cpu  changes   state   to  `CPU_STATE_DREAMING'.
 * Because  the  BOOT CPU  can  never dream,  this  value is  always `>= 1'! */
DATDEF unsigned int cpu_online_count;
#else /* !CONFIG_NO_SMP */
#define cpu_online_count 1
#endif /* CONFIG_NO_SMP */


/* [1..1][cpu_count] Vector of CPU descriptors.
 * NOTE: The index in this vector is the `cpu_id' of the associated CPU.
 * NOTE: `bootcpu' always has the CPUID ZERO(0) */
DATDEF struct cpu *const cpu_vector[CONFIG_MAX_CPU_COUNT];

#if CONFIG_MAX_CPU_COUNT > BITS_PER_POINTER
DECL_END
#include <libc/string.h>
DECL_BEGIN
typedef uintptr_t *cpuset_ptr_t;
#define CPUSET_PTR(x) x
#define CPUSET_IND(x) x
typedef uintptr_t cpuset_t[(CONFIG_MAX_CPU_COUNT + (BITS_PER_POINTER-1)) / BITS_PER_POINTER];
#if __SIZEOF_POINTER__ == 8
#define CPUSET_COPY(dst, src) (void)__libc_memcpyq(dst, src, (CONFIG_MAX_CPU_COUNT + (BITS_PER_POINTER - 1)) / BITS_PER_POINTER)
#define CPUSET_CLEAR(x)       (void)__libc_memsetq(x, 0, (CONFIG_MAX_CPU_COUNT + (BITS_PER_POINTER - 1)) / BITS_PER_POINTER)
#define CPUSET_SETFULL(x)     (void)__libc_memsetq(x, (uintptr_t)-1, (CONFIG_MAX_CPU_COUNT + (BITS_PER_POINTER - 1)) / BITS_PER_POINTER)
#elif __SIZEOF_POINTER__ == 4
#define CPUSET_COPY(dst, src) (void)__libc_memcpyl(dst, src, (CONFIG_MAX_CPU_COUNT + (BITS_PER_POINTER - 1)) / BITS_PER_POINTER)
#define CPUSET_CLEAR(x)       (void)__libc_memsetl(x, 0, (CONFIG_MAX_CPU_COUNT + (BITS_PER_POINTER - 1)) / BITS_PER_POINTER)
#define CPUSET_SETFULL(x)     (void)__libc_memsetl(x, (uintptr_t)-1, (CONFIG_MAX_CPU_COUNT + (BITS_PER_POINTER - 1)) / BITS_PER_POINTER)
#else /* __SIZEOF_POINTER__ == ... */
#define CPUSET_COPY(dst, src) (void)__libc_memcpy(dst, src, sizeof(cpuset_t))
#define CPUSET_CLEAR(x)       (void)__libc_memset(x, 0, sizeof(cpuset_t))
#define CPUSET_SETFULL(x)     (void)__libc_memset(x, 0xff, sizeof(cpuset_t))
#endif /* __SIZEOF_POINTER__ != ... */
#define CPUSET_CONTAINS(x, id) ((x)[(id) / BITS_PER_POINTER] & ((uintptr_t)1 << ((id) % BITS_PER_POINTER)))
#define CPUSET_INSERT(x, id)   (void)((x)[(id) / BITS_PER_POINTER] |= ((uintptr_t)1 << ((id) % BITS_PER_POINTER)))
#define CPUSET_REMOVE(x, id)   (void)((x)[(id) / BITS_PER_POINTER] &= ~((uintptr_t)1 << ((id) % BITS_PER_POINTER)))
#define CPUSET_COUNT(x) cpuset_count_impl(x)
LOCAL size_t NOTHROW(KCALL cpuset_count_impl)(cpuset_t self) {
	size_t result = 0;
	unsigned int i;
	for (i = 0; i < cpu_count; ++i) {
		if (CPUSET_CONTAINS(self, i))
			++result;
	}
	return result;
}
#define CPUSET_ISEMPTY(x) cpuset_isempty_impl(x)
LOCAL bool NOTHROW(KCALL cpuset_isempty_impl)(cpuset_t self) {
	unsigned int i;
	for (i = 0; i < cpu_count; ++i) {
		if (CPUSET_CONTAINS(self, i))
			return false;
	}
	return true;
}
#else /* CONFIG_MAX_CPU_COUNT > BITS_PER_POINTER */
typedef uintptr_t *cpuset_ptr_t;
#define CPUSET_PTR(x) (&(x))
#define CPUSET_IND(x) (*(x))
typedef uintptr_t cpuset_t;
#define CPUSET_INIT 0
#if CONFIG_MAX_CPU_COUNT <= 1
#define __cpuset_full_mask  1
#else /* CONFIG_MAX_CPU_COUNT <= 1 */
#define __HAVE_CPUSET_FULL_MASK 1
DATDEF cpuset_t const __cpuset_full_mask; /* [== (1 << cpu_count) - 1] */
#endif /* CONFIG_MAX_CPU_COUNT > 1 */
#if CONFIG_MAX_CPU_COUNT > 32
#define CPUSET_COUNT(x)       __hybrid_popcount64((u64)((x) & __cpuset_full_mask))
#elif CONFIG_MAX_CPU_COUNT > 16
#define CPUSET_COUNT(x)       __hybrid_popcount32((u32)((x) & __cpuset_full_mask))
#elif CONFIG_MAX_CPU_COUNT > 8
#define CPUSET_COUNT(x)       __hybrid_popcount16((u16)((x) & __cpuset_full_mask))
#else /* CONFIG_MAX_CPU_COUNT > ... */
#define CPUSET_COUNT(x)       __hybrid_popcount8((u8)((x) & __cpuset_full_mask))
#endif /* CONFIG_MAX_CPU_COUNT <= ... */
#define CPUSET_COPY(dst, src)  (void)((dst) = (src))
#define CPUSET_CLEAR(x)        (void)((x) = 0)
#define CPUSET_ISEMPTY(x)      (((x)&__cpuset_full_mask) == 0)
#define CPUSET_SETFULL(x)      (void)((x) = (uintptr_t)-1)
#define CPUSET_SETONE(x, id)   (void)((x) = ((uintptr_t)1 << (id)))
#define CPUSET_CONTAINS(x, id) ((x) & ((uintptr_t)1 << (id)))
#define CPUSET_INSERT(x, id)   (void)((x) |= ((uintptr_t)1 << (id)))
#define CPUSET_REMOVE(x, id)   (void)((x) &= ~((uintptr_t)1 << (id)))
#endif /* CONFIG_MAX_CPU_COUNT <= BITS_PER_POINTER */
#ifndef CPUSET_SETONE
#define CPUSET_SETONE(x, id) (CPUSET_CLEAR(x), CPUSET_INSERT(x, id))
#endif /* !CPUSET_SETONE */



/* The boot CPU. */
DATDEF struct cpu bootcpu;

/* The CPU of the calling thread */
DATDEF ATTR_PERTASK struct cpu *this_cpu;

/* [const] The ID (index in `cpu_vector') of the calling thread. */
DATDEF ATTR_PERCPU unsigned int thiscpu_id; /* ALIAS:THIS_CPU->c_id */

#ifndef CONFIG_NO_SMP
/* ALIAS:THIS_CPU->c_pdir */
DATDEF ATTR_PERCPU pagedir_phys_t thiscpu_pdir;
#endif /* !CONFIG_NO_SMP */


#ifdef CONFIG_NO_SMP
#undef THIS_CPU
#undef THIS_IDLE
#define THIS_CPU  (&bootcpu)
#define THIS_IDLE (&bootidle)
#else /* CONFIG_NO_SMP */
#ifndef THIS_CPU
#define THIS_CPU PERTASK_GET(this_cpu)
#endif /* !THIS_CPU */
#ifndef THIS_IDLE
#define THIS_IDLE (&PERCPU(thiscpu_idle))
#endif /* !THIS_IDLE */
#endif /* !CONFIG_NO_SMP */




#ifndef CONFIG_NO_SMP
/* Set the current MMan, and update the MMan pointer of `self' */
#define cpu_setmman_ex(me, current_mm)                 \
	(__hybrid_atomic_store((me)->c_pdir,               \
	                       (current_mm)->mm_pagedir_p, \
	                       __ATOMIC_RELEASE),          \
	 pagedir_set((current_mm)->mm_pagedir_p))
#define cpu_setmman(current_mm) cpu_setmman_ex(THIS_CPU, current_mm)

/* Return the set of CPUs that are currently mapped to make use of `self'
 * Note that the returned set of  CPUs is only a (possibly  inconsistent)
 * snapshot, with the only guaranties being that:
 *   - If a CPU is apart of the returned cpuset, that CPU has at one point
 *     made use of the given page directory `self'.
 *   - If  a CPU is  not apart of the  returned cpuset, that  CPU may have since
 *     switched its pdir to the given one. Note however that during this switch,
 *     additional things  may have  also happened,  such as  the CPU  invaliding
 *     its TLB cache (where  is function is  meant to be  used to calculate  the
 *     bounding  set  of CPUs  that (may)  need to  have their  page directories
 *     invalidated)
 * WARNING: This function does not include special handling for when `self'
 *          is the kernel MMan. In this  case, the caller must implement  a
 *          dedicated code-path that  behaves as though  this function  had
 *          returned a completely filled cpuset. */
#if CONFIG_MAX_CPU_COUNT > BITS_PER_POINTER
FUNDEF NOBLOCK NONNULL((2)) void
NOTHROW(FCALL pagedir_getcpus)(pagedir_phys_t self,
                               cpuset_ptr_t result);
#else /* CONFIG_MAX_CPU_COUNT > BITS_PER_POINTER */
FUNDEF NOBLOCK WUNUSED cpuset_t
NOTHROW(FCALL __pagedir_getcpus)(pagedir_phys_t self)
	ASMNAME("pagedir_getcpus");
#define pagedir_getcpus(self, result) (void)(*(result) = __pagedir_getcpus(self))
#endif /* CONFIG_MAX_CPU_COUNT <= BITS_PER_POINTER */

/* Return the set of CPUs using the page directory of the given MMan. */
#define mman_getcpus(self, result) pagedir_getcpus((self)->mm_pagedir_p, result)

#else /* !CONFIG_NO_SMP */

/* Set the current MMan, and update the MMan pointer of `self' */
#define cpu_setmman_ex(me, current_mm) pagedir_set((current_mm)->mm_pagedir_p)
#define cpu_setmman(current_mm)        pagedir_set((current_mm)->mm_pagedir_p)

#endif /* CONFIG_NO_SMP */





/* Enter deep-sleep mode on the given CPU.
 * In deep-sleep mode, no interrupts are  fired and no code is  executed.
 * Essentially, the CPU is offline, and can only be re-enabled by another
 * core calling `cpu_deepwake()' on the core.
 * NOTES:
 *    - This function may only ever be called a the CPU's IDLE thread
 *    - When called, it is checked if there are other running tasks.
 *      If there are, simply switch to the next one.
 *      If there are none that can continue execution, `__hlt()', but
 *      don't disable preemption,  thus checking again  periodically.
 *      If there are none at  all, disable preemptive interrupts,  as
 *      well  as  other hardware-specific  machinery to  reduce power
 *      consumption, before entering deep-sleep mode.
 *    - The BOOT cpu cannot be shut down in this manner, as it is
 *      responsible for handling interrupts.
 *      When  called  by the  BOOT cpu's  IDLE  thread, the  function will
 *      instead  check if  other threads  should be  run, before disabling
 *      preemptive interrupts and waiting for the next hardware interrupt,
 *      in the mean time tracking how much time has passed before then  in
 *      order  to update the global jiffies counter (which is identical to
 *      the counter of the boot CPU)
 *      After a hardware interrupt occurred,  the process is repeated,  in
 *      that the function will check for new tasks that may have shown up.
 *    - This function returns once DEEP-SLEEP ends, and the IDLE task should
 *      execute  again  for  the  first  time  since  the  last  DEEP-SLEEP.
 *      For this purpose,  the CPU can  be woken by  a call to  `cpu_wake()'
 * Implementation-wise, this function will:
 *   #1 Disable preemption
 *   #2 Transition from `CPU_STATE_RUNNING' to `CPU_STATE_FALLING_ASLEEP'
 *#ifndef CONFIG_NO_SMP
 *   #3 Schedule all tasks found in `c_pending'
 *   #4 Serve all pending IPI callbacks (s.a. `cpu_sendipi()')
 *#endif
 *   #5 Check for other running tasks
 *      #5.1 If there are some, unschedule the IDLE thread and yield to the  first
 *           In this case, this function will return the next time the IDLE thread
 *           will get re-scheduled.
 *   #6 Check for sleeping tasks with the KEEPCORE flag
 *      #6.1 If there are any, re-enable preemption and wait for the next
 *           preemptive   interrupt   before  going   back  to   step  #1
 *   #7 Disable preemptive interrupts on secondary  cores,
 *      or the boot core if no secondary cores are online.
 *   #8 Hand over all  tasks still  hosted by  the CPU  to another  one (with  the
 *      fallback hand-over target being the boot-cpu, as it can never fall asleep)
 *   #9 Disable other per-cpu hardware components to save power
 *  --- Secondary cores:
 *   #10 Change state to `CPU_STATE_DREAMING'
 *   #11 Halt execution, now only listening for INIT-IPIs send via `cpu_wake()'
 *  --- Boot CPU:
 *   #10 Halt execution until the next interrupt.
 *   #11 Disable preemption
 *   #12 Re-enable per-cpu hardware components disabled in step #9
 *   #13 If disabled in  step #7, re-enable preemptive  interrupts
 *   #14 Got back to step #2
 */
FUNDEF void NOTHROW(KCALL cpu_deepsleep)(void);

#ifndef CONFIG_NO_SMP
/* MUST ONLY BE CALLED FROM AN IDLE TASK!
 * This  function  does  the   following:
 * >> FORCPU(me, thiscpu_idle).t_state = PUSH_CPU_STATE_FOR_RETURNING_TO_CALLER();
 * >> ATOMIC_WRITE(caller->c_state, CPU_STATE_DREAMING);
 * >> PREEMPTION_DEEPHALT();
 * NOTE: Do not call this function directly. - Use `cpu_deepsleep()' instead,
 *       and   even  then:  Only  call  that  function  from  an  IDLE  task.
 * NOTE: When this function returns, preemption will have been re-enabled
 *       as the result  of another CPU  calling `cpu_wake()' on  `caller'
 * NOTE:  This  function  must  not  be  called  by  the  BOOT CPU!
 * With this, it is the arch-dependent portion of `cpu_deepsleep()'
 * that performs  the actual  deep-sleep  on a  multi-core  system. */
FUNDEF NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL cpu_enter_deepsleep)(struct cpu *__restrict caller);

/* Check  if IPIs are  pending to be executed  by the calling CPU,
 * returning  `true'  if  this is  the  case, or  `false'  it not.
 * In order to serve any pending IPIs, preemption must be enabled. */
FUNDEF NOBLOCK WUNUSED NOPREEMPT bool
NOTHROW(FCALL arch_cpu_hwipi_pending_nopr)(void);

/* Check  if  there   are  any  non-interrupting   software-based  IPIs   pending.
 * If some are present, these must be serviced by calling `cpu_ipi_service_nopr()' */
FUNDEF NOBLOCK WUNUSED NOPREEMPT NONNULL((1)) bool
NOTHROW(FCALL arch_cpu_swipi_pending_nopr)(struct cpu *__restrict me);

/* Wake up a CPU, regardless of which ever state it may be in, potentially
 * not  even waking it at all, but simply sending an IPI, such that sooner
 * or later it will check its chain of pending task (`FORCPU(target, thiscpu_sched_pending)'),
 * causing  it   to   load   all  threads   found   within   that  chain,   so-as   to   allow
 * those tasks to continue running on it.
 * On X86, this function is implemented as:
 * >> for (;;) {
 * >>     u16 state = ATOMIC_READ(target->c_state);
 * >>     switch (state) {
 * >>     case CPU_STATE_DREAMING:
 * >>         // Take on the responsibility of waking up the CPU.
 * >>         if (!ATOMIC_CMPXCH_WEAK(target->c_state,state,CPU_STATE_GETTING_UP))
 * >>             continue;
 * >>         SEND_IPI(INIT,target);
 * >>         ATTR_FALLTHROUGH
 * >>     case CPU_STATE_GETTING_UP:
 * >>         // The CPU has been instructed to wake up / is currently waking up
 * >>         // In this state, we can be sure that (when not considering possible
 * >>         // hardware failure), it will load pending tasks after switching to
 * >>         // `CPU_STATE_RUNNING' mode.
 * >>         return;
 * >>     case CPU_STATE_FALLING_ASLEEP:
 * >>         // The CPU is currently falling asleep. - If it already went past the
 * >>         // point of checking for pending tasks, then it will switch states to
 * >>         // `CPU_STATE_DREAMING' in just a moment.
 * >>         // If it didn't and is currently loading those tasks, the state will
 * >>         // shortly change to `CPU_STATE_RUNNING'
 * >>         // In either case, wait for something to happen, but do so in a busy
 * >>         // loop, so-as to not block, fulfilling the `NOBLOCK' requirement.
 * >>         __pause();
 * >>         continue;
 * >>     case CPU_STATE_RUNNING:
 * >>         // The CPU should still be able to receive regular IPIs, so use those
 * >>         SEND_IPI(LOAD_PENDING_TASKS,target);
 * >>         // NOTE: If the CPU changed states to one where IPIs can no longer be
 * >>         //       received (aka. from `CPU_STATE_RUNNING' to `CPU_STATE_FALLING_ASLEEP'),
 * >>         //       it would have already loaded pending tasks during that transition,
 * >>         //       so regardless of the IPI actually being delivered, we know that
 * >>         //       the CPU _has_ loaded any pending tasks!
 * >>         return;
 * >>
 * >>     default:
 * >>         __builtin_unreachable();
 * >>     }
 * >>     break;
 * >> }
 */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL cpu_wake)(struct cpu *__restrict target);

/* Service pending IPIs (must be called after a manual switch to the RUNNING state)
 * The  general   sequence  of   setting  `CPU_STATE_RUNNING'   looks  like   this:
 * >>again:
 * >>    PREEMPTION_DISABLE();
 * >>    ATOMIC_WRITE(me->c_state, CPU_STATE_FALLING_ASLEEP);
 * >>    // Check for hardware IPIs which may have been delivered after `PREEMPTION_DISABLE()'
 * >>    // was called, but bfore `CPU_STATE_FALLING_ASLEEP' got set (letting other CPUs think
 * >>    // that our CPU would be able to service IPIs)
 * >>    if (arch_cpu_hwipi_pending_nopr(me)) {
 * >>        ATOMIC_WRITE(me->c_state, CPU_STATE_RUNNING);
 * >>        cpu_ipi_service_nopr();
 * >>        PREEMPTION_ENABLE_P();
 * >>        goto again;
 * >>    }
 * >>
 * >>    // Some other code
 * >>    ...
 * >>
 * >>    ATOMIC_WRITE(me->c_state, CPU_STATE_RUNNING);
 * >>    if (arch_cpu_swipi_pending_nopr(me)) {
 * >>        cpu_ipi_service_nopr();
 * >>        PREEMPTION_ENABLE();
 * >>        goto again;
 * >>    }
 * This  sequence is required, since cpu_wake() which  is used to deliver IPI requests
 * to cpus in a state other than `CPU_STATE_RUNNING' (in order to allow for deep-sleep
 * wake-ups), will not trigger an IPI interrupt if there are any sw-based IPIs pending */
FUNDEF NOBLOCK NOPREEMPT void NOTHROW(KCALL cpu_ipi_service_nopr)(void);
#endif /* !CONFIG_NO_SMP */
#endif /* __CC__ */


/* The max number of pointers that can be passed to an IPI function. */
#define CPU_IPI_ARGCOUNT  4

#ifdef __CC__
#ifndef CONFIG_NO_SMP
struct icpustate;
/* Callback for an asynchronous IPI executed by some target CPU.
 * IPIs can be  handled (and thus  executed) any time  execution
 * in a target CPU has preemption enabled.
 * Note however that  IPIs are  very restricted  in what  they can  actually
 * do  when it comes  to write-access. The poster-child  example for the use
 * of an IPI is the TLB shoot down used by paging to invalidate old mappings
 * on other cores before associated paging data can safely be freed.
 * NOTE: IPIs are always executed with preemption disabled. - And even though
 *       IPIs  are allowed to re-enable preemption, please note that doing so
 *       may  lead  to  one  IPI  callback  being  interrupted  by   another.
 *       Also note that preemption is always enabled where `state' points to,
 *       unless the `CPU_IPI_FNOINTR' flag was set then the request was made.
 * @param: args: The arguments alongside which the IPI was scheduled.
 * @return: * :  The cpu state to restore, or one of `CPU_IPI_MODE_*'
 */
typedef NOBLOCK NOPREEMPT NONNULL_T((1, 2)) struct icpustate *
NOTHROW_T(FCALL *cpu_ipi_t)(struct icpustate *__restrict state,
                            void *args[CPU_IPI_ARGCOUNT]);
#endif /* !CONFIG_NO_SMP */
#endif /* __CC__ */

/* Special return values for `cpu_ipi_t' callbacks. */
#define CPU_IPI_MODE_SPECIAL_MIN      (__CCAST(uintptr_t)(-1))
#define CPU_IPI_MODE_ISSPECIAL(x)     (__CCAST(uintptr_t)(x) >= CPU_IPI_MODE_SPECIAL_MIN)

/* Directly yield execution to `PERCPU(thiscpu_sched_current)'. The caller is responsible
 * to deal  with  time  accounting,  preferably via  use  of  the  `sched_intern_*'  API.
 * This   is   mainly  used   to   quickly  cause   a   thread  woken   by  `task_wake()'
 * to  resume  execution   when  it  was   hosted  by  a   different  CPU  before   then. */
#define CPU_IPI_MODE_SWITCH_TASKS     (__CCAST(struct icpustate *)(-1))



#define CPU_IPI_FNORMAL   0x0000 /* Normal IPI delivery flags. */
#define CPU_IPI_FWAKEUP   0x0001 /* FLAG: Wake  up the  target CPU if  it is currently  in deep-sleep mode.
                                  * When this flag  isn't given,  broadcasting IPIs  to some  set to  CPUs,
                                  * as  can  be  done  with  `cpu_sendipi_cpuset()',  `cpu_broadcastipi()',
                                  * as well  as `cpu_broadcastipi_notthis()'  is guarantied  to be  atomic,
                                  * in the sense that any CPU that isn't in deep by the time the associated
                                  * function returns will have received the IPI.
                                  * This in  turns  allows  you to  restrict  execution  of IPIs  to  only  the
                                  * set of CPUs considered to be on-line, allowing the efficient implementation
                                  * of single-core sub-systems  that only  need to interrupt  CPUs that  aren't
                                  * already off-line.
                                  * s.a. `cpu_isrunning()' */
#define CPU_IPI_FNOINTR   0x0002 /* FLAG: The IPI may be executed when preemption is disabled.
                                  *       When this flag is set, sending a non-blocking IPI to
                                  *       one self is allowed. */
#define CPU_IPI_FWAITFOR  0x1000 /* Wait for the target CPU to acknowledge having received the IPI,
                                  * rather than allowing  the IPI to  be delivered  asynchronously. */

/* Check if  `self' is  running, and  sending  an IPI  without `CPU_IPI_FWAKEUP'  should  succeed.
 * Note however the race condition where a CPU might stop running before/after this check is made. */
#define cpu_isrunning(self) (__hybrid_atomic_load((self)->c_state, __ATOMIC_ACQUIRE) == CPU_STATE_RUNNING)


/* The size of the buffer used to contain pending IPIs. */
#ifndef CPU_IPI_BUFFER_SIZE
#define CPU_IPI_BUFFER_SIZE  256
#endif /* !CPU_IPI_BUFFER_SIZE */


/* WARNING: Sending IPIs with preemption disabled is possible, but when sending
 *          more  than `CPU_IPI_BUFFER_SIZE / cpu_count' IPIs in a row, without
 *          re-enabling  preemption between any of them may lead to a situation
 *          where no further IPIs can be sent to some target CPU.
 */


#ifdef __CC__
#ifndef CONFIG_NO_SMP
/* Send an IPI to a specific target CPU.
 * The  sync-variant will wait for the IPI to be acknowledged and completed before continuing,
 * which is quite the expensive operation, as it requires a second follow-up IPI by the target
 * cpu, which is used for confirming the completion of an IPI.
 * @return: true:  IPI delivery successful.
 * @return: false: The IPI could not be scheduled because the  target
 *                 CPU is offline, and `CPU_IPI_FWAKEUP' was not set.
 * @return: false: The target CPU's IPI buffer is full.
 *                 This can happen if the target cpu has disabled preemption,
 *                 following  which at least `CPU_IPI_BUFFER_SIZE' other IPIs
 *                 had been sent to it.
 * @return: false: The target CPU's is the caller's and `CPU_IPI_FNOINTR' isn't set. */
FUNDEF NOBLOCK NONNULL((1, 2, 3)) bool
NOTHROW(KCALL cpu_sendipi)(struct cpu *__restrict target, cpu_ipi_t func,
                           void *args[CPU_IPI_ARGCOUNT], unsigned int flags);

/* Send an IPI to all CPUs apart of the given set of `targets'.
 * @return: * : The number of successfully delivered IPIs. */
FUNDEF NOBLOCK NONNULL((2, 3)) unsigned int
NOTHROW(KCALL cpu_sendipi_cpuset)(cpuset_t targets, cpu_ipi_t func,
                                  void *args[CPU_IPI_ARGCOUNT], unsigned int flags);

/* Same as the regular IPI functions, however the IPI is broadcast to all CPUs.
 * @return: * : The number of successfully delivered IPIs. */
FUNDEF NOBLOCK NONNULL((1, 2)) unsigned int
NOTHROW(KCALL cpu_broadcastipi)(cpu_ipi_t func, void *args[CPU_IPI_ARGCOUNT], unsigned int flags);

/* Same as `cpu_broadcastipi()', but don't send the IPI to the calling CPU. */
FUNDEF NOBLOCK NONNULL((1, 2)) unsigned int
NOTHROW(KCALL cpu_broadcastipi_notthis)(cpu_ipi_t func, void *args[CPU_IPI_ARGCOUNT], unsigned int flags);

#endif /* !CONFIG_NO_SMP */

/* The main loop that is executed by IDLE threads. */
FUNDEF ATTR_NORETURN void NOTHROW(FCALL cpu_idlemain)(void);

/* >> void NOTHROW(KCALL func(void));
 * A function that  is invoked in  order to allow  the kernel to  self-optimize
 * whenever there is nothing else to do, before falling asleep (these functions
 * are invoked by the IDLE thread). */
#define DEFINE_IDLE_JOB(func) \
	DEFINE_CALLBACK(".rodata.callback.idle_job", func)


/* Save the current CPU context and store it in `caller->s_state'.
 * Then, switch context to `PERCPU(thiscpu_sched_current)' and continue by executing it.
 * NOTE:   Preemption   must  be   disabled  before   this   function  may   be  called!
 * NOTE: Upon return, preemption will have been re-enabled! */
FUNDEF NOPREEMPT NONNULL((1)) void
NOTHROW(FCALL cpu_run_current_and_remember_nopr)(struct task *__restrict caller);

/* Similar to `cpu_run_current_and_remember_nopr()',
 * but  don't   remember   the   caller's   context.
 * This  function is used to implement `task_exit()'
 * NOTE: Preemption must be disabled before this function may be called! */
FUNDEF ABNORMAL_RETURN NOPREEMPT ATTR_NORETURN void
NOTHROW(FCALL cpu_run_current_nopr)(void);

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_SCHED_CPU_H */
