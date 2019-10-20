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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_GDT_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_GDT_H 1

#include <kernel/compiler.h>
#include <kernel/types.h>
#include <hybrid/__assert.h>
#include <kos/kernel/gdt.h>
#include <kos/kernel/segment.h>
#include <sched/pertask.h>

#ifdef __x86_64__
#include <asm/cpu-flags.h>
#include <asm/cpu-msr.h>
#include <asm/intrin.h>
#endif /* __x86_64__ */

DECL_BEGIN

#ifdef __CC__
/* The per-cpu GDT vector. */
DATDEF ATTR_PERCPU struct segment x86_cpugdt[SEGMENT_COUNT];
DATDEF ATTR_PERCPU struct segment x86_cpuldt[LDT_SEGMENT_COUNT];

/* [== VM_NODE_ENDADDR(THIS_KERNEL_STACK)]
 * The per-task value written to `t_esp0' / `t_rsp0' during scheduler preemption. */
DATDEF ATTR_PERTASK uintptr_t const x86_this_kernel_sp0;

/* Get/Set the user-space FS/GS base for the current thread. */
#ifdef __x86_64__
FORCELOCAL WUNUSED uintptr_t KCALL get_user_fsbase(void) {
	return (uintptr_t)__rdfsbase();
}

FORCELOCAL void KCALL set_user_fsbase(uintptr_t value) {
	__wrfsbase((void *)value);
}

FORCELOCAL WUNUSED uintptr_t KCALL get_user_gsbase(void) {
	/* We must read the KERNEL_GS_BASE MSR here, as it
	 * currently contains the effective user-space GS-base */
	return (uintptr_t)__rdmsr(IA32_KERNEL_GS_BASE);
}

FORCELOCAL void KCALL set_user_gsbase(uintptr_t value) {
	/* We must write the KERNEL_GS_BASE MSR here, as it
	 * currently contains the effective user-space GS-base */
	__wrmsr(IA32_KERNEL_GS_BASE, (__UINT64_TYPE__)value);
}

FORCELOCAL void KCALL update_user_fsbase(void) {
	/* Nothing */
}

FORCELOCAL void KCALL update_user_gsbase(void) {
	/* Nothing */
}

#else /* __x86_64__ */

/* The per-task values with which the `SEGMENT_USER_FSBASE' and
 * `SEGMENT_USER_GSBASE' segments are populated during scheduler
 * preemption. */
DATDEF ATTR_PERTASK uintptr_t x86_this_user_fsbase;
DATDEF ATTR_PERTASK uintptr_t x86_this_user_gsbase;

FORCELOCAL WUNUSED uintptr_t KCALL get_user_fsbase(void) {
	return PERTASK_GET(x86_this_user_fsbase);
}

FORCELOCAL void KCALL set_user_fsbase(uintptr_t value) {
	PERTASK_SET(x86_this_user_fsbase, value);
	segment_wrbaseX(&PERCPU(x86_cpugdt[SEGMENT_INDEX(SEGMENT_USER_FSBASE)]), value);
#ifndef SEGMENT_KERNEL_FSBASE
	{
		__register uintptr_t temp;
		/* Reload the FS register, which likely wouldn't be done without this. */
		__asm__ __volatile__("movw %%fs, %w0\n\t"
		                     "movw %w0, %%fs"
		                     : "=&r" (temp)
		                     :
		                     : "memory");
	}
#endif /* !SEGMENT_KERNEL_FSBASE */
}

FORCELOCAL void KCALL update_user_fsbase(void) {
	segment_wrbaseX(&PERCPU(x86_cpugdt[SEGMENT_INDEX(SEGMENT_USER_FSBASE)]),
	                PERTASK_GET(x86_this_user_fsbase));
#ifndef SEGMENT_KERNEL_FSBASE
	{
		__register uintptr_t temp;
		/* Reload the FS register, which likely wouldn't be done without this. */
		__asm__ __volatile__("movw %%fs, %w0\n\t"
		                     "movw %w0, %%fs"
		                     : "=&r" (temp)
		                     :
		                     : "memory");
	}
#endif /* !SEGMENT_KERNEL_FSBASE */
}

FORCELOCAL WUNUSED uintptr_t KCALL get_user_gsbase(void) {
	return PERTASK_GET(x86_this_user_gsbase);
}

FORCELOCAL void KCALL set_user_gsbase(uintptr_t value) {
	PERTASK_SET(x86_this_user_gsbase, value);
	segment_wrbaseX(&PERCPU(x86_cpugdt[SEGMENT_INDEX(SEGMENT_USER_GSBASE)]), value);
#ifndef SEGMENT_KERNEL_GSBASE
	{
		/* Reload the GS register, which likely wouldn't be done without this. */
		__register uintptr_t temp;
		__asm__ __volatile__("movw %%gs, %w0\n\t"
		                     "movw %w0, %%gs"
		                     : "=&r" (temp)
		                     :
		                     : "memory");
	}
#endif /* !SEGMENT_KERNEL_GSBASE */
}

FORCELOCAL void KCALL update_user_gsbase(void) {
	segment_wrbaseX(&PERCPU(x86_cpugdt[SEGMENT_INDEX(SEGMENT_USER_GSBASE)]),
	                PERTASK_GET(x86_this_user_gsbase));
#ifndef SEGMENT_KERNEL_GSBASE
	{
		/* Reload the GS register, which likely wouldn't be done without this. */
		__register uintptr_t temp;
		__asm__ __volatile__("movw %%gs, %w0\n\t"
		                     "movw %w0, %%gs"
		                     : "=&r" (temp)
		                     :
		                     : "memory");
	}
#endif /* !SEGMENT_KERNEL_GSBASE */
}
#endif /* !__x86_64__ */

#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_GDT_H */
