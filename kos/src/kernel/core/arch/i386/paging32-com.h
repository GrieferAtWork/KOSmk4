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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_PAGING32_COM_H
#define GUARD_KERNEL_CORE_ARCH_I386_PAGING32_COM_H 1

#include <kernel/compiler.h>

#include <kernel/cpuid.h>
#include <kernel/types.h>
#include <sched/task.h>

#include <hybrid/atomic.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <asm/cpu-cpuid.h>


/* TODO: Re-add support for `TRACE_PAGING()' */
#if !defined(NDEBUG) && 0
#include <kernel/printk.h>
#define TRACE_PAGING(...) printk(KERN_DEBUG __VA_ARGS__)
#else
#define NO_TRACE_PAGING 1
#define TRACE_PAGING(...) (void)0
#endif

#if 1 /* Not used often enough to excuse taking up precious cache space */
#define ATTR_PAGING_READMOSTLY /* nothing */
#else
#define ATTR_PAGING_READMOSTLY ATTR_READMOSTLY
#endif


DECL_BEGIN

/* Paging feature selectors. */
#define HAVE_PAGE_GLOBAL_BIT       (__x86_bootcpu_idfeatures.ci_1d & CPUID_1D_PGE)
#define HAVE_PAGE_ATTRIBUTE_TABLE  (__x86_bootcpu_idfeatures.ci_1d & CPUID_1D_PAT)
#define HAVE_INSTR_INVLPG          (__x86_bootcpu_features & CPU_FEATURE_FI486) /* ... INVLPG is an instruction available since the i486 ... */
#define HAVE_INSTR_INVPCID         (__x86_bootcpu_idfeatures.ci_7b & CPUID_7B_INVPCID)

#if !defined(CONFIG_NO_PAGING_P32) && !defined(CONFIG_NO_PAGING_PAE)
STATIC_ASSERT((u64)P32_PAGE_FGLOBAL == (u64)PAE_PAGE_FGLOBAL);
#if PAE_PAGE_FGLOBAL <= 0xffffffff /* This is faster because GCC can assume that the upper 32 bits are 0 */
INTERN ATTR_PAGING_READMOSTLY u32 used_pxx_page_fglobal = (u32)PAE_PAGE_FGLOBAL;
#define USED_P32_PAGE_FGLOBAL     used_pxx_page_fglobal
#define USED_PAE_PAGE_FGLOBAL     used_pxx_page_fglobal
#else
INTERN ATTR_PAGING_READMOSTLY union {
	u64 pae;
	u32 p32;
} used_pxx_page_fglobal = { PAE_PAGE_FGLOBAL }; /* Cleared during init if unsupported */
#define USED_P32_PAGE_FGLOBAL     used_pxx_page_fglobal.p32
#define USED_PAE_PAGE_FGLOBAL     used_pxx_page_fglobal.pae
#endif
#elif !defined(CONFIG_NO_PAGING_P32)
INTERN ATTR_PAGING_READMOSTLY u32 used_pxx_page_fglobal = P32_PAGE_FGLOBAL; /* Cleared during init if unsupported */
#define USED_P32_PAGE_FGLOBAL     used_pxx_page_fglobal
#elif !defined(CONFIG_NO_PAGING_PAE)
#if PAE_PAGE_FGLOBAL <= 0xffffffff /* This is faster because GCC can assume that the upper 32 bits are 0 */
INTERN ATTR_PAGING_READMOSTLY u32 used_pxx_page_fglobal = (u32)PAE_PAGE_FGLOBAL; /* Cleared during init if unsupported */
#else
INTERN ATTR_PAGING_READMOSTLY u64 used_pxx_page_fglobal = PAE_PAGE_FGLOBAL; /* Cleared during init if unsupported */
#endif
#define USED_PAE_PAGE_FGLOBAL     used_pxx_page_fglobal
#endif


#ifndef CONFIG_NO_PAGING_P32
#define HAVE_4MIB_PAGES            (__x86_bootcpu_idfeatures.ci_1d & CPUID_1D_PSE)
#endif /* !CONFIG_NO_PAGING_P32 */

#ifndef CONFIG_NO_PAGING_PAE
#define HAVE_2MIB_PAGES             1 /* Always supported */
/* TODO: Take this into account:  When you set bit 34 of the 0x01A0 MSR on an Intel processor
 *                                you clear the bit 20 of EDX for CPUID/EAX=800000001h, disabling
 *                                your ability to enable the execute disable bit
 * From: https://forum.osdev.org/viewtopic.php?f=1&t=18945 */
#define HAVE_EXECUTE_DISABLE       (__x86_bootcpu_idfeatures.ci_80000001d & CPUID_80000001D_NX)
#endif /* !CONFIG_NO_PAGING_PAE */


/* Lock counter to indicate that some thread somewhere is setting the
 * initial PREPARED bit for of some E1-vector in some page directory. */
PRIVATE struct atomic_rwlock x86_pagedir_prepare_lock = ATOMIC_RWLOCK_INIT;

/* Version counter for `x86_pagedir_prepare_lock' (incremented each read/write) */
PRIVATE ATTR_WRITEMOSTLY WEAK size_t x86_pagedir_prepare_version = 0;

#define X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_READ(was)                    \
	do {                                                              \
		was = PREEMPTION_PUSHOFF();                                   \
		if likely(atomic_rwlock_tryread(&x86_pagedir_prepare_lock)) { \
			ATOMIC_FETCHINC(x86_pagedir_prepare_version);             \
			break;                                                    \
		}                                                             \
		PREEMPTION_POP(was);                                          \
		task_tryyield_or_pause();                                     \
	} __WHILE1
#define X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_READ_NOVER(was)            \
	do {                                                            \
		was = PREEMPTION_PUSHOFF();                                 \
		if likely(atomic_rwlock_tryread(&x86_pagedir_prepare_lock)) \
			break;                                                  \
		PREEMPTION_POP(was);                                        \
		task_tryyield_or_pause();                                   \
	} __WHILE1
#define X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_WRITE(was)                  \
	do {                                                             \
		was = PREEMPTION_PUSHOFF();                                  \
		if likely(atomic_rwlock_trywrite(&x86_pagedir_prepare_lock)) \
			break;                                                   \
		PREEMPTION_POP(was);                                         \
		task_tryyield_or_pause();                                    \
	} __WHILE1
#define X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was)        \
	do {                                                  \
		atomic_rwlock_endread(&x86_pagedir_prepare_lock); \
		PREEMPTION_POP(was);                              \
	} __WHILE0
#define X86_PAGEDIR_PREPARE_LOCK_RELEASE_WRITE(was)        \
	do {                                                   \
		atomic_rwlock_endwrite(&x86_pagedir_prepare_lock); \
		PREEMPTION_POP(was);                               \
	} __WHILE0


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_PAGING32_COM_H */
