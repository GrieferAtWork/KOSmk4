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
#ifndef GUARD_KERNEL_SRC_SCHED_CPU_C
#define GUARD_KERNEL_SRC_SCHED_CPU_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h> /* CONFIG_HAVE_KERNEL_DEBUGGER */
#include <sched/cpu.h>

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/rt.h> /* dbg_active */
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

DECL_BEGIN

#ifdef __HAVE_CPUSET_FULL_MASK
PUBLIC cpuset_t ___cpuset_full_mask ASMNAME("__cpuset_full_mask") = 1;
#endif /* __HAVE_CPUSET_FULL_MASK */


/* [!0][<= CONFIG_MAX_CPU_COUNT][const] The total number of known CPUs. */
PUBLIC unsigned int cpu_count_ ASMNAME("cpu_count") = 1;
#ifndef CONFIG_NO_SMP
PUBLIC unsigned int cpu_online_count = 1;
#endif /* !CONFIG_NO_SMP */

/* [1..1][cpu_count] Vector of CPU descriptors.
 * NOTE: The index in this vector is the `cpu_id' of the associated CPU.
 * NOTE: `bootcpu' always has the CPUID ZERO(0) */
PUBLIC struct cpu *_cpu_vector[CONFIG_MAX_CPU_COUNT] ASMNAME("cpu_vector") = { &bootcpu };


PRIVATE ATTR_USED ATTR_SECTION(".data.percpu.head")
struct cpu cpu_header = {
	.c_id    = 0,
	.c_state = CPU_STATE_RUNNING,
#ifndef CONFIG_NO_SMP
	.c_pdir  = pagedir_kernel_phys
#endif /* !CONFIG_NO_SMP */
};




PUBLIC ATTR_NORETURN void
NOTHROW(FCALL cpu_idlemain)(void) {
	for (;;) {
		/* TODO: sync() (`fsuper_syncall()') superblocks.
		 * NOTE: Should only happen after some delay (e.g. 2 seconds)
		 *       since the last write operation, or since IDLE began. */

		/* TODO: Do IDLE jobs, such as cleaning up memory. */
		/* TODO: Based on the current power profile, wait for different length's
		 *       of periods before entering deep sleep mode (in high performance
		 *       mode, never enter deep sleep mode. - Only `hlt' normally). */

		cpu_deepsleep();
	}
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_SCHED_CPU_C */
