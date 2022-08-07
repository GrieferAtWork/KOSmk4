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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_GDT_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_GDT_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>
#include <sched/pertask.h>

#include <hybrid/__assert.h>

#include <kos/kernel/x86/gdt.h>
#include <kos/kernel/x86/segment.h>

#ifdef __x86_64__
#include <asm/cpu-flags.h>
#include <asm/cpu-msr.h>
#include <asm/intrin.h>
#else /* __x86_64__ */
#include <hybrid/sched/__preemption.h>
#endif /* !__x86_64__ */

DECL_BEGIN

#ifdef __CC__
/* The per-cpu GDT vector. */
DATDEF ATTR_PERCPU struct segment thiscpu_x86_gdt[SEGMENT_COUNT];
DATDEF ATTR_PERCPU struct segment thiscpu_x86_ldt[LDT_SEGMENT_COUNT];
DATDEF struct segment bootcpu_x86_gdt[SEGMENT_COUNT];

#ifndef CONFIG_NO_KERNEL_USERKERN_SEGMENT
#ifdef __x86_64__
FUNDEF u32 NOTHROW(KCALL x86_get_random_userkern_address32)(void);
FUNDEF uintptr_t NOTHROW(KCALL x86_get_random_userkern_address)(void);
#define x86_get_random_userkern_address64 x86_get_random_userkern_address
#else /* __x86_64__ */
FUNDEF uintptr_t NOTHROW(KCALL x86_get_random_userkern_address)(void);
#define x86_get_random_userkern_address32 x86_get_random_userkern_address
#endif /* !__x86_64__ */
#endif /* !CONFIG_NO_KERNEL_USERKERN_SEGMENT */

#ifndef ___this_x86_kernel_psp0_defined
#define ___this_x86_kernel_psp0_defined
/* [== mnode_getendaddr(THIS_KERNEL_STACK)]
 * The per-task value written to `t_psp0' during scheduler preemption. */
DATDEF ATTR_PERTASK uintptr_t const this_x86_kernel_psp0;
#endif /* !___this_x86_kernel_psp0_defined */

/* Get/Set the user-space FS/GS base for the current thread. */
#ifdef __x86_64__
#define x86_get_user_fsbase()       ((uintptr_t)__rdfsbaseq())
#define x86_set_user_fsbase(v)      __wrfsbaseq((uint64_t)(v));
#define x86_set_user_fsbase_nopr(v) __wrfsbaseq((uint64_t)(v));
/* We must  read the  KERNEL_GS_BASE MSR  here, as  it
 * currently contains the effective user-space GS-base */
#define x86_get_user_gsbase()       ((uintptr_t)__rdmsr(IA32_KERNEL_GS_BASE))
#define x86_set_user_gsbase(v)      __wrmsr(IA32_KERNEL_GS_BASE, (uint64_t)(v))
#define x86_set_user_gsbase_nopr(v) __wrmsr(IA32_KERNEL_GS_BASE, (uint64_t)(v))
#else /* __x86_64__ */

/* The  per-task values with which the `SEGMENT_USER_FSBASE' and
 * `SEGMENT_USER_GSBASE' segments are populated during scheduler
 * preemption. */
DATDEF ATTR_PERTASK uintptr_t this_x86_user_fsbase;
DATDEF ATTR_PERTASK uintptr_t this_x86_user_gsbase;

#define x86_get_user_fsbase() PERTASK_GET(this_x86_user_fsbase)
#define x86_get_user_gsbase() PERTASK_GET(this_x86_user_gsbase)
#define x86_set_user_fsbase_nopr(v)                                                       \
	do {                                                                                  \
		PERTASK_SET(this_x86_user_fsbase, v);                                             \
		segment_wrbaseX(&PERCPU(thiscpu_x86_gdt[SEGMENT_INDEX(SEGMENT_USER_FSBASE)]), v); \
		/* NOTE: No need to reload the %fs register here, since it'll                     \
		 *       be reloaded anyways once we return to user-space; at                     \
		 *       the moment's it's `SEGMENT_KERNEL_FSBASE' anyways! */                    \
	}	__WHILE0
#define x86_set_user_fsbase(v)                                                            \
	do {                                                                                  \
		__hybrid_preemption_flag_t _xsufnr_was;                                           \
		PERTASK_SET(this_x86_user_fsbase, v);                                             \
		__hybrid_preemption_pushoff(&_xsufnr_was);                                        \
		segment_wrbaseX(&PERCPU(thiscpu_x86_gdt[SEGMENT_INDEX(SEGMENT_USER_FSBASE)]), v); \
		__hybrid_preemption_pop(&_xsufnr_was);                                            \
		/* NOTE: No need to reload the %fs register here, since it'll                     \
		 *       be reloaded anyways once we return to user-space; at                     \
		 *       the moment's it's `SEGMENT_KERNEL_FSBASE' anyways! */                    \
	}	__WHILE0
#define x86_set_user_gsbase_nopr(v)                                                       \
	do {                                                                                  \
		PERTASK_SET(this_x86_user_gsbase, v);                                             \
		segment_wrbaseX(&PERCPU(thiscpu_x86_gdt[SEGMENT_INDEX(SEGMENT_USER_GSBASE)]), v); \
		/* Reload the GS register, which likely wouldn't be done without this. */         \
		__asm__ __volatile__("movw %%gs, %w0\n\t"                                         \
		                     "movw %w0, %%gs"                                             \
		                     : "=&r" (_xsugnr_temp)                                       \
		                     :                                                            \
		                     : "memory");                                                 \
	}	__WHILE0
#define x86_set_user_gsbase(v)                                                            \
	do {                                                                                  \
		__hybrid_preemption_flag_t _xsugnr_was;                                           \
		__register uintptr_t _xsugnr_temp;                                                \
		PERTASK_SET(this_x86_user_gsbase, v);                                             \
		__hybrid_preemption_pushoff(&_xsugnr_was);                                        \
		segment_wrbaseX(&PERCPU(thiscpu_x86_gdt[SEGMENT_INDEX(SEGMENT_USER_GSBASE)]), v); \
		__hybrid_preemption_pop(&_xsugnr_was);                                            \
		/* Reload the GS register, which likely wouldn't be done without this. */         \
		__asm__ __volatile__("movw %%gs, %w0\n\t"                                         \
		                     "movw %w0, %%gs"                                             \
		                     : "=&r" (_xsugnr_temp)                                       \
		                     :                                                            \
		                     : "memory");                                                 \
	}	__WHILE0
#endif /* !__x86_64__ */
#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_X86_GDT_H */
