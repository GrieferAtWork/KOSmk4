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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_PAGING32_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_PAGING32_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <kos/kernel/paging.h>

#include <stdbool.h>



/* Since the entire kernel-space has its E1-vectors pre-allocated (so-as
 * to allow them to be share across all page-directories), page directory
 * mappings within kernel space itself do not require and sort of
 * preparations being made. */
#undef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
//#define CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE 1

/* x86 implements the `pagedir_(has|unset)changed' API. */
#undef CONFIG_HAVE_PAGEDIR_CHANGED
#define CONFIG_HAVE_PAGEDIR_CHANGED 1

/* x86 implements the `pagedir_unwrite' API (delete low-level write permissions). */
#undef CONFIG_HAVE_PAGEDIR_UNWRITE
#define CONFIG_HAVE_PAGEDIR_UNWRITE 1

#if defined(CONFIG_NO_PAGING_PAE) && defined(CONFIG_NO_PAGING_P32)
#error "You can't disable PAE and P32 paging! - I need at least either to work properly!"
#elif defined(CONFIG_NO_PAGING_PAE)
/* P32-paging only */
#include "paging32-p32.h"

DECL_BEGIN

#undef CONFIG_PAGEDIR_INIT_NEED_PHYS_SELF
#define CONFIG_PAGEDIR_INIT_NEED_PHYS_SELF 1
#undef CONFIG_PAGEDIR_FINI_NEED_PHYS_SELF
#undef CONFIG_PAGEDIR_INIT_IS_NOEXCEPT
#define CONFIG_PAGEDIR_INIT_IS_NOEXCEPT 1

#define X86_PAGEDIR_USES_PAE()  0
#define X86_PAGEDIR_USES_P32()  1

#define X86_VM_KERNEL_PDIR_RESERVED_BASE_IS_COMPILETIME_VALUE 1
/* Start of the address range reserved for page-directory self-modifications. */
#define X86_VM_KERNEL_PDIR_RESERVED_BASE P32_VM_KERNEL_PDIR_RESERVED_BASE
/* Amount of memory reserved for page-directory self-modifications. */
#define X86_VM_KERNEL_PDIR_RESERVED_SIZE P32_VM_KERNEL_PDIR_RESERVED_SIZE

/* The minimum alignment required for pointers passed to `pagedir_maphint()' */
#define PAGEDIR_MAPHINT_ALIGNMENT  P32_PAGEDIR_MAPHINT_ALIGNMENT

/* Define platform-independent symbols. */
#define PAGEDIR_ALIGN P32_PDIR_ALIGN
#define PAGEDIR_SIZE  P32_PDIR_SIZE

DECL_END

#elif defined(CONFIG_NO_PAGING_P32)
/* PAE-paging only */
#include "paging32-pae.h"

DECL_BEGIN

#undef CONFIG_PAGEDIR_INIT_NEED_PHYS_SELF
#undef CONFIG_PAGEDIR_FINI_NEED_PHYS_SELF
#define CONFIG_PAGEDIR_FINI_NEED_PHYS_SELF 1
#undef CONFIG_PAGEDIR_INIT_IS_NOEXCEPT

#define X86_PAGEDIR_USES_PAE()  1
#define X86_PAGEDIR_USES_P32()  0

#define X86_VM_KERNEL_PDIR_RESERVED_BASE_IS_COMPILETIME_VALUE 1
/* Start of the address range reserved for page-directory self-modifications. */
#define X86_VM_KERNEL_PDIR_RESERVED_BASE PAE_VM_KERNEL_PDIR_RESERVED_BASE
/* Amount of memory reserved for page-directory self-modifications. */
#define X86_VM_KERNEL_PDIR_RESERVED_SIZE PAE_VM_KERNEL_PDIR_RESERVED_SIZE

/* The minimum alignment required for pointers passed to `pagedir_maphint()' */
#define PAGEDIR_MAPHINT_ALIGNMENT  PAE_PAGEDIR_MAPHINT_ALIGNMENT

/* Define platform-independent symbols. */
#define PAGEDIR_ALIGN PAE_PDIR_ALIGN
#define PAGEDIR_SIZE  PAE_PDIR_SIZE

DECL_END

#else /* CONFIG_... */

/* Configure for hybrid paging. */

/**/
#include "paging32-p32.h"
#include "paging32-pae.h"
/**/

#include <kernel/cpuid.h>  /* x86_bootcpu_cpuid */
#include <asm/cpu-cpuid.h> /* CPUID_1D_PAE */

DECL_BEGIN

#undef CONFIG_PAGEDIR_INIT_NEED_PHYS_SELF
#define CONFIG_PAGEDIR_INIT_NEED_PHYS_SELF 1 /* Needed by P32 (`p32_pagedir_init') */
#undef CONFIG_PAGEDIR_FINI_NEED_PHYS_SELF
#define CONFIG_PAGEDIR_FINI_NEED_PHYS_SELF 1 /* Needed by PAE (`pae_pagedir_fini') */
#undef CONFIG_PAGEDIR_INIT_IS_NOEXCEPT /* `pae_pagedir_init()' may throw `E_BADALLOC' (but `p32_pagedir_init()' is noexcept) */


#define X86_PAGEDIR_USES_PAE()    (x86_bootcpu_cpuid.ci_1d & CPUID_1D_PAE)
#define X86_PAGEDIR_USES_P32()  (!(x86_bootcpu_cpuid.ci_1d & CPUID_1D_PAE))

#if P32_VM_KERNEL_PDIR_RESERVED_BASE == PAE_VM_KERNEL_PDIR_RESERVED_BASE && \
    P32_VM_KERNEL_PDIR_RESERVED_SIZE == PAE_VM_KERNEL_PDIR_RESERVED_SIZE
#define X86_VM_KERNEL_PDIR_RESERVED_BASE_IS_COMPILETIME_VALUE 1

/* Start of the address range reserved for page-directory self-modifications. */
#define X86_VM_KERNEL_PDIR_RESERVED_BASE \
	P32_VM_KERNEL_PDIR_RESERVED_BASE
/* Amount of memory reserved for page-directory self-modifications. */
#define X86_VM_KERNEL_PDIR_RESERVED_SIZE \
	P32_VM_KERNEL_PDIR_RESERVED_SIZE
#else /* Same-reservations */
#define X86_VM_KERNEL_PDIR_RESERVED_BASE_IS_RUNTIME_VALUE 1

/* Start of the address range reserved for page-directory self-modifications. */
#define X86_VM_KERNEL_PDIR_RESERVED_BASE \
	(X86_PAGEDIR_USES_PAE() ? PAE_VM_KERNEL_PDIR_RESERVED_BASE : P32_VM_KERNEL_PDIR_RESERVED_BASE)
/* Amount of memory reserved for page-directory self-modifications. */
#define X86_VM_KERNEL_PDIR_RESERVED_SIZE \
	(X86_PAGEDIR_USES_PAE() ? PAE_VM_KERNEL_PDIR_RESERVED_SIZE : P32_VM_KERNEL_PDIR_RESERVED_SIZE)
#endif /* Diff-reservations */


/* The minimum alignment required for pointers passed to `pagedir_maphint()' */
#if P32_PAGEDIR_MAPHINT_ALIGNMENT > PAE_PAGEDIR_MAPHINT_ALIGNMENT
#define PAGEDIR_MAPHINT_ALIGNMENT  P32_PAGEDIR_MAPHINT_ALIGNMENT
#else /* P32_PAGEDIR_MAPHINT_ALIGNMENT > PAE_PAGEDIR_MAPHINT_ALIGNMENT */
#define PAGEDIR_MAPHINT_ALIGNMENT  PAE_PAGEDIR_MAPHINT_ALIGNMENT
#endif /* P32_PAGEDIR_MAPHINT_ALIGNMENT <= PAE_PAGEDIR_MAPHINT_ALIGNMENT */


/* Define platform-independent symbols. */
#if P32_PDIR_ALIGN > PAE_PDIR_ALIGN
#define PAGEDIR_ALIGN P32_PDIR_ALIGN
#else /* P32_PDIR_ALIGN > PAE_PDIR_ALIGN */
#define PAGEDIR_ALIGN PAE_PDIR_ALIGN
#endif /* P32_PDIR_ALIGN <= PAE_PDIR_ALIGN */

#if P32_PDIR_SIZE > PAE_PDIR_SIZE
#define PAGEDIR_SIZE  P32_PDIR_SIZE
#else /* P32_PDIR_SIZE > PAE_PDIR_SIZE */
#define PAGEDIR_SIZE  PAE_PDIR_SIZE
#endif /* P32_PDIR_SIZE <= PAE_PDIR_SIZE */

DECL_END
#endif /* !CONFIG_... */


DECL_BEGIN

#ifdef __CC__
typedef union {
#ifndef CONFIG_NO_PAGING_P32
	struct p32_pdir pd_p32; /* P32 page directory */
#endif /* !CONFIG_NO_PAGING_P32 */
#ifndef CONFIG_NO_PAGING_PAE
	struct pae_pdir pd_pae; /* PAE page directory */
#endif /* !CONFIG_NO_PAGING_PAE */
} pagedir_t;
#endif /* __CC__ */



/* x86 uses a 32-/64-bit pointer for `cr3', meaning that physical memory
 * which may exist outside of the address space also addressable without
 * paging enabled cannot be used as a page directory pointer. */
#undef CONFIG_PAGEDIR_GETSET_USES_POINTER
#define CONFIG_PAGEDIR_GETSET_USES_POINTER 1


#undef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_GETSET
#define CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_GETSET 1
#ifdef __CC__
/* Low-level Get/Set the physical address of the currently active page directory. */
FORCELOCAL NOBLOCK PHYS pagedir_t *
NOTHROW(KCALL pagedir_get)(void) {
	pagedir_t *result;
	__asm__("movl %%cr3, %0"
	        : "=r" (result)
	        :
	        : "memory");
	return result;
}

FORCELOCAL NOBLOCK void
NOTHROW(KCALL pagedir_set)(PHYS pagedir_t *__restrict value) {
	__asm__("movl %0, %%cr3"
	        :
	        : "r" (value)
	        : "memory");
}
#endif /* __CC__ */


/* When more than `CONFIG_PAGEDIR_LARGESYNC_THRESHOLD' need to be synced, rather
 * than performing that number of single-page TLB invalidations, invalidate
 * everything instead. */
#ifndef CONFIG_PAGEDIR_LARGESYNC_THRESHOLD
#define CONFIG_PAGEDIR_LARGESYNC_THRESHOLD 256
#endif /* !CONFIG_PAGEDIR_LARGESYNC_THRESHOLD */


#undef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_SYNCALL
#undef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_SYNCONE
#undef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_SYNC
#define CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_SYNCALL 1
#define CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_SYNCONE 1
#define CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_SYNC 1


#ifndef __pagedir_pushval_t_defined
#define __pagedir_pushval_t_defined 1
#ifdef CONFIG_NO_PAGING_PAE
#define PAGEDIR_PUSHVAL_INVALID PAE_PAGEDIR_PUSHVAL_INVALID
#define SIZEOF_PAGEDIR_PUSHVAL  SIZEOF_PAE_PAGEDIR_PUSHVAL
#ifdef __CC__
typedef p32_pagedir_pushval_t pagedir_pushval_t;
#endif /* __CC__ */
#elif defined(CONFIG_NO_PAGING_P32)
#define PAGEDIR_PUSHVAL_INVALID P32_PAGEDIR_PUSHVAL_INVALID
#define SIZEOF_PAGEDIR_PUSHVAL  SIZEOF_P32_PAGEDIR_PUSHVAL
#ifdef __CC__
typedef pae_pagedir_pushval_t pagedir_pushval_t;
#endif /* __CC__ */
#elif SIZEOF_PAE_PAGEDIR_PUSHVAL == SIZEOF_P32_PAGEDIR_PUSHVAL
#define PAGEDIR_PUSHVAL_INVALID PAE_PAGEDIR_PUSHVAL_INVALID
#define SIZEOF_PAGEDIR_PUSHVAL  SIZEOF_PAE_PAGEDIR_PUSHVAL
#ifdef __CC__
typedef pae_pagedir_pushval_t pagedir_pushval_t;
#endif /* __CC__ */
#else
#error "The types `pae_pagedir_pushval_t' and `p32_pagedir_pushval_t' are not compatible"
#endif
#endif /* !__pagedir_pushval_t_defined */



#ifdef __CC__

/* Synchronize the entirety of the current page directory.
 * Note that this function may only sync all user-space mappings. If the
 * intent is to also sync all of kernel-space, `pagedir_syncall()'
 * must be used instead. */
FORCELOCAL NOBLOCK void NOTHROW(FCALL pagedir_syncall_user)(void) {
	__register u32 temp;
	__asm__("movl %%cr3, %0\n\t"
	        "movl %0, %%cr3"
	        : "=&r" (temp));
}

/* Same as `pagedir_syncall()', but also ensures that
 * all of kernel-space is synced. */
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_syncall)(void);

/* Hybrid of `pagedir_syncall()' and `pagedir_syncall_user()': When the given range
 * overlaps with kernel-space, behave the same as `pagedir_syncall()', otherwise,
 * behave the same as `pagedir_syncall_user()' */
FUNDEF NOBLOCK void NOTHROW(FCALL x86_pagedir_syncall_maybe_global)(VIRT vm_virt_t virt_addr, size_t num_pages);

/* X86-specific implementation for invalidating the TLB of a single page. */
FUNDEF NOBLOCK void NOTHROW(FCALL x86_pagedir_syncone)(VIRT vm_virt_t virt_addr);

/* X86-specific implementation for invalidating every TLB over a given range. */
FUNDEF NOBLOCK void NOTHROW(FCALL x86_pagedir_sync)(VIRT vm_virt_t virt_addr, size_t num_pages);

/* Synchronize mappings within the given address range. */
FORCELOCAL NOBLOCK void
NOTHROW(FCALL pagedir_syncone)(VIRT vm_vpage_t virt_page) {
	x86_pagedir_syncone(VM_PAGE2ADDR(virt_page));
}

/* Synchronize mappings within the given address range. */
FORCELOCAL NOBLOCK void
NOTHROW(FCALL pagedir_sync)(VIRT vm_vpage_t virt_page, size_t num_pages) {
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
	if (__builtin_constant_p(num_pages)) {
		if (num_pages == 0)
			return;
		if (num_pages == 1) {
			pagedir_syncone(virt_page);
			return;
		}
		if (num_pages > KERNEL_BASE_PAGE) {
			/* We know that the address always _has_ to
			 * fall into kernel-space in this case! */
			pagedir_syncall();
			return;
		}
		if (num_pages > CONFIG_PAGEDIR_LARGESYNC_THRESHOLD) {
			x86_pagedir_syncall_maybe_global(VM_PAGE2ADDR(virt_page), num_pages);
			return;
		}
	}
#endif /* !__OMIT_PAGING_CONSTANT_P_WRAPPERS */
	x86_pagedir_sync(VM_PAGE2ADDR(virt_page), num_pages);
}
#endif /* __CC__ */


#undef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_PAGESIZE
#define CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_PAGESIZE 1


/* Return the smallest active page size/alignment/number-of-bytes-per-page
 * possible with the current page directory.
 * Note that this value is always:
 *    - `>= PAGEDIR_MIN_PAGESIZE'
 *    - `<= PAGEDIR_MAX_PAGESIZE'
 *    - A power-of-2 value */
#ifdef __INTELLISENSE__
FUNDEF NOBLOCK ATTR_CONST WUNUSED size_t NOTHROW(KCALL pagedir_pagesize)(void);
#else /* __INTELLISENSE__ */
#undef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_PAGESIZE_P
#define CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_PAGESIZE_P 1
#define pagedir_pagesize()          __CCAST(size_t)4096
#define pagedir_pagesize_p(pagedir) __CCAST(size_t)4096
#endif /* !__INTELLISENSE__ */

#define PAGEDIR_MIN_PAGESIZE 4096
#define PAGEDIR_MAX_PAGESIZE 4096



DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_PAGING32_H */
