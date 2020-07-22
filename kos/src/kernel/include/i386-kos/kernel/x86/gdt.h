/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_GDT_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_GDT_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/pertask.h>

#include <hybrid/__assert.h>

#include <kos/kernel/gdt.h>
#include <kos/kernel/segment.h>

#ifdef __x86_64__
#include <asm/cpu-flags.h>
#include <asm/cpu-msr.h>
#include <asm/intrin.h>
#endif /* __x86_64__ */

DECL_BEGIN

#ifdef __CC__
/* The per-cpu GDT vector. */
DATDEF ATTR_PERCPU struct segment thiscpu_x86_gdt[SEGMENT_COUNT];
DATDEF ATTR_PERCPU struct segment thiscpu_x86_ldt[LDT_SEGMENT_COUNT];
DATDEF struct segment bootcpu_x86_gdt[SEGMENT_COUNT];

#ifndef CONFIG_NO_USERKERN_SEGMENT
#ifdef __x86_64__
FUNDEF u32 NOTHROW(KCALL x86_get_random_userkern_address32)(void);
FUNDEF uintptr_t NOTHROW(KCALL x86_get_random_userkern_address)(void);
#define x86_get_random_userkern_address64 x86_get_random_userkern_address
#else /* __x86_64__ */
FUNDEF uintptr_t NOTHROW(KCALL x86_get_random_userkern_address)(void);
#define x86_get_random_userkern_address32 x86_get_random_userkern_address
#endif /* !__x86_64__ */
#endif /* !CONFIG_NO_USERKERN_SEGMENT */

#ifndef ___this_x86_kernel_psp0_defined
#define ___this_x86_kernel_psp0_defined 1
/* [== vm_node_getend(THIS_KERNEL_STACK)]
 * The per-task value written to `t_psp0' during scheduler preemption. */
DATDEF ATTR_PERTASK uintptr_t const this_x86_kernel_psp0;
#endif /* !___this_x86_kernel_psp0_defined */

/* Get/Set the user-space FS/GS base for the current thread. */
#ifdef __x86_64__
LOCAL WUNUSED uintptr_t KCALL get_user_fsbase(void) {
	return (uintptr_t)__rdfsbase();
}

LOCAL void KCALL set_user_fsbase(uintptr_t value) {
	__wrfsbase((void *)value);
}

LOCAL WUNUSED uintptr_t KCALL get_user_gsbase(void) {
	/* We must read the KERNEL_GS_BASE MSR here, as it
	 * currently contains the effective user-space GS-base */
	return (uintptr_t)__rdmsr(IA32_KERNEL_GS_BASE);
}

LOCAL void KCALL set_user_gsbase(uintptr_t value) {
	/* We must write the KERNEL_GS_BASE MSR here, as it
	 * currently contains the effective user-space GS-base */
	__wrmsr(IA32_KERNEL_GS_BASE, (uint64_t)value);
}

LOCAL void KCALL update_user_fsbase(void) {
	/* Nothing */
}

LOCAL void KCALL update_user_gsbase(void) {
	/* Nothing */
}

#else /* __x86_64__ */

/* The per-task values with which the `SEGMENT_USER_FSBASE' and
 * `SEGMENT_USER_GSBASE' segments are populated during scheduler
 * preemption. */
DATDEF ATTR_PERTASK uintptr_t this_x86_user_fsbase;
DATDEF ATTR_PERTASK uintptr_t this_x86_user_gsbase;

/* TODO: Rename to `x86_get_user_fsbase()' */
LOCAL WUNUSED uintptr_t KCALL get_user_fsbase(void) {
	return PERTASK_GET(this_x86_user_fsbase);
}

/* TODO: Rename to `x86_set_user_fsbase_noreload()' */
LOCAL void KCALL set_user_fsbase_noreload(uintptr_t value) {
	PERTASK_SET(this_x86_user_fsbase, value);
	segment_wrbaseX(&PERCPU(thiscpu_x86_gdt[SEGMENT_INDEX(SEGMENT_USER_FSBASE)]), value);
}

/* TODO: Rename to `x86_set_user_fsbase()' */
LOCAL void KCALL set_user_fsbase(uintptr_t value) {
	set_user_fsbase_noreload(value);
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

LOCAL void KCALL update_user_fsbase(void) {
	segment_wrbaseX(&PERCPU(thiscpu_x86_gdt[SEGMENT_INDEX(SEGMENT_USER_FSBASE)]),
	                PERTASK_GET(this_x86_user_fsbase));
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

/* TODO: Rename to `x86_get_user_gsbase()' */
LOCAL WUNUSED uintptr_t KCALL get_user_gsbase(void) {
	return PERTASK_GET(this_x86_user_gsbase);
}

/* TODO: Rename to `x86_set_user_gsbase_noreload()' */
LOCAL void KCALL set_user_gsbase_noreload(uintptr_t value) {
	PERTASK_SET(this_x86_user_gsbase, value);
	segment_wrbaseX(&PERCPU(thiscpu_x86_gdt[SEGMENT_INDEX(SEGMENT_USER_GSBASE)]), value);
}

/* TODO: Rename to `x86_set_user_gsbase()' */
LOCAL void KCALL set_user_gsbase(uintptr_t value) {
	set_user_gsbase_noreload(value);
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

/* TODO: Rename to `x86_update_user_gsbase()' */
LOCAL void KCALL update_user_gsbase(void) {
	segment_wrbaseX(&PERCPU(thiscpu_x86_gdt[SEGMENT_INDEX(SEGMENT_USER_GSBASE)]),
	                PERTASK_GET(this_x86_user_gsbase));
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

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_GDT_H */
