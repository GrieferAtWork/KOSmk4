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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_COM_H
#define GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_COM_H 1

#include <kernel/compiler.h>

#include <kernel/arch/paging32.h>
#include <kernel/types.h>
#include <kernel/x86/cpuid.h>

#include <hybrid/atomic.h>
#include <hybrid/sched/preemption.h>
#include <hybrid/sync/atomic-rwlock.h>

#include <asm/cpu-cpuid.h>

#if 1 /* Not used often enough to excuse taking up precious cache space */
#define ATTR_PAGING_READMOSTLY /* nothing */
#else
#define ATTR_PAGING_READMOSTLY ATTR_READMOSTLY
#endif


DECL_BEGIN

/* Paging feature selectors. */
#define HAVE_PAGE_GLOBAL_BIT       X86_HAVE_PAGE_GLOBAL_BIT
#define HAVE_PAGE_ATTRIBUTE_TABLE  X86_HAVE_PAGE_ATTRIBUTE_TABLE
#define HAVE_INSTR_INVLPG          X86_HAVE_INSTR_INVLPG
#define HAVE_INSTR_INVPCID         X86_HAVE_INSTR_INVPCID

#if !defined(CONFIG_NO_PAGING_P32) && !defined(CONFIG_NO_PAGING_PAE)
STATIC_ASSERT((u64)P32_PAGE_FGLOBAL == (u64)PAE_PAGE_FGLOBAL);
#if PAE_PAGE_FGLOBAL <= 0xffffffff /* This is faster because GCC can assume that the upper 32 bits are 0 */
INTERN ATTR_PAGING_READMOSTLY u32 used_pxx_page_fglobal = (u32)PAE_PAGE_FGLOBAL;
#define USED_P32_PAGE_FGLOBAL     used_pxx_page_fglobal
#define USED_PAE_PAGE_FGLOBAL     used_pxx_page_fglobal
#else /* PAE_PAGE_FGLOBAL <= 0xffffffff */
INTERN ATTR_PAGING_READMOSTLY union {
	u64 pae;
	u32 p32;
} used_pxx_page_fglobal = { PAE_PAGE_FGLOBAL }; /* Cleared during init if unsupported */
#define USED_P32_PAGE_FGLOBAL     used_pxx_page_fglobal.p32
#define USED_PAE_PAGE_FGLOBAL     used_pxx_page_fglobal.pae
#endif /* PAE_PAGE_FGLOBAL > 0xffffffff */
#elif !defined(CONFIG_NO_PAGING_P32)
INTERN ATTR_PAGING_READMOSTLY u32 used_pxx_page_fglobal = P32_PAGE_FGLOBAL; /* Cleared during init if unsupported */
#define USED_P32_PAGE_FGLOBAL     used_pxx_page_fglobal
#elif !defined(CONFIG_NO_PAGING_PAE)
#if PAE_PAGE_FGLOBAL <= 0xffffffff /* This is faster because GCC can assume that the upper 32 bits are 0 */
INTERN ATTR_PAGING_READMOSTLY u32 used_pxx_page_fglobal = (u32)PAE_PAGE_FGLOBAL; /* Cleared during init if unsupported */
#else /* PAE_PAGE_FGLOBAL <= 0xffffffff */
INTERN ATTR_PAGING_READMOSTLY u64 used_pxx_page_fglobal = PAE_PAGE_FGLOBAL; /* Cleared during init if unsupported */
#endif /* PAE_PAGE_FGLOBAL > 0xffffffff */
#define USED_PAE_PAGE_FGLOBAL     used_pxx_page_fglobal
#endif /* ... */


#ifndef CONFIG_NO_PAGING_P32
#define HAVE_4MIB_PAGES           X86_HAVE_4MIB_PAGES
#endif /* !CONFIG_NO_PAGING_P32 */

#ifndef CONFIG_NO_PAGING_PAE
#define HAVE_2MIB_PAGES           1 /* Always supported */
/* TODO: Take this into account:  When you set  bit 34 of  the 0x01A0 MSR  on an Intel  processor
 *                                you clear the bit 20 of EDX for CPUID/EAX=800000001h, disabling
 *                                your ability to enable the execute disable bit
 * From: https://forum.osdev.org/viewtopic.php?f=1&t=18945 */
#define HAVE_EXECUTE_DISABLE      X86_HAVE_EXECUTE_DISABLE
#endif /* !CONFIG_NO_PAGING_PAE */


/* Lock counter to indicate that some thread somewhere is setting the
 * initial PREPARED bit for of some E1-vector in some page directory. */
PRIVATE struct atomic_rwlock x86_pagedir_prepare_lock = ATOMIC_RWLOCK_INIT;

/* Version counter for `x86_pagedir_prepare_lock' (incremented each read/write) */
PRIVATE ATTR_WRITEMOSTLY WEAK uintptr_t x86_pagedir_prepare_version = 0;

#define X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_READ(was)                    \
	do {                                                              \
		preemption_pushoff(&(was));                                   \
		if likely(atomic_rwlock_tryread(&x86_pagedir_prepare_lock)) { \
			ATOMIC_INC(x86_pagedir_prepare_version);                  \
			break;                                                    \
		}                                                             \
		preemption_pop(&(was));                                       \
		preemption_tryyield();                                        \
	}	__WHILE1
#define X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_READ_NOVER(was)            \
	do {                                                            \
		preemption_pushoff(&(was));                                 \
		if likely(atomic_rwlock_tryread(&x86_pagedir_prepare_lock)) \
			break;                                                  \
		preemption_pop(&(was));                                     \
		preemption_tryyield();                                      \
	}	__WHILE1
#define X86_PAGEDIR_PREPARE_LOCK_ACQUIRE_WRITE(was)                  \
	do {                                                             \
		preemption_pushoff(&(was));                                  \
		if likely(atomic_rwlock_trywrite(&x86_pagedir_prepare_lock)) \
			break;                                                   \
		preemption_pop(&(was));                                      \
		preemption_tryyield();                                       \
	}	__WHILE1
#define X86_PAGEDIR_PREPARE_LOCK_RELEASE_READ(was)        \
	do {                                                  \
		atomic_rwlock_endread(&x86_pagedir_prepare_lock); \
		preemption_pop(&(was));                           \
	}	__WHILE0
#define X86_PAGEDIR_PREPARE_LOCK_RELEASE_WRITE(was)        \
	do {                                                   \
		atomic_rwlock_endwrite(&x86_pagedir_prepare_lock); \
		preemption_pop(&(was));                            \
	}	__WHILE0


DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_MEMORY_PAGING32_COM_H */
