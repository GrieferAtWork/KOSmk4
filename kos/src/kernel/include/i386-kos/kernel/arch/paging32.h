/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
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
#undef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
//#define ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE 1

/* x86 implements the `pagedir_(has|unset)changed' API. */
#undef ARCH_PAGEDIR_HAVE_CHANGED
#define ARCH_PAGEDIR_HAVE_CHANGED 1

/* x86 implements the `pagedir_unwrite' API (delete low-level write permissions). */
#undef ARCH_PAGEDIR_HAVE_UNWRITE
#define ARCH_PAGEDIR_HAVE_UNWRITE 1

#if defined(CONFIG_NO_PAGING_PAE) && defined(CONFIG_NO_PAGING_P32)
#error "You can't disable PAE and P32 paging! - I need at least either to work properly!"
#elif defined(CONFIG_NO_PAGING_PAE)
/* P32-paging only */
#include "paging32-p32.h"

#undef ARCH_PAGEDIR_INIT_NEED_PHYS_SELF
#define ARCH_PAGEDIR_INIT_NEED_PHYS_SELF 1
#undef ARCH_PAGEDIR_FINI_NEED_PHYS_SELF
#undef ARCH_PAGEDIR_INIT_IS_NOEXCEPT
#define ARCH_PAGEDIR_INIT_IS_NOEXCEPT 1

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

#elif defined(CONFIG_NO_PAGING_P32)
/* PAE-paging only */
#include "paging32-pae.h"

#undef ARCH_PAGEDIR_INIT_NEED_PHYS_SELF
#undef ARCH_PAGEDIR_FINI_NEED_PHYS_SELF
#define ARCH_PAGEDIR_FINI_NEED_PHYS_SELF 1
#undef ARCH_PAGEDIR_INIT_IS_NOEXCEPT

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

#else /* CONFIG_... */

/* Configure for hybrid paging. */

/**/
#include "paging32-p32.h"
#include "paging32-pae.h"
/**/

#include <kernel/x86/cpuid.h> /* bootcpu_x86_cpuid */

#include <asm/cpu-cpuid.h> /* CPUID_1D_PAE */

#undef ARCH_PAGEDIR_INIT_NEED_PHYS_SELF
#define ARCH_PAGEDIR_INIT_NEED_PHYS_SELF 1 /* Needed by P32 (`p32_pagedir_init') */
#undef ARCH_PAGEDIR_FINI_NEED_PHYS_SELF
#define ARCH_PAGEDIR_FINI_NEED_PHYS_SELF 1 /* Needed by PAE (`pae_pagedir_fini') */
#undef ARCH_PAGEDIR_INIT_IS_NOEXCEPT /* `pae_pagedir_init()' may throw `E_BADALLOC' (but `p32_pagedir_init()' is noexcept) */


#define X86_PAGEDIR_USES_PAE() X86_HAVE_PAE
#define X86_PAGEDIR_USES_P32() (!X86_HAVE_PAE)

#if (P32_VM_KERNEL_PDIR_RESERVED_BASE == PAE_VM_KERNEL_PDIR_RESERVED_BASE && \
     P32_VM_KERNEL_PDIR_RESERVED_SIZE == PAE_VM_KERNEL_PDIR_RESERVED_SIZE)
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


#ifndef PAGEDIR_PAGEALIGNED
#define PAGEDIR_PAGEALIGNED /* Annotation for variables that need to be aligned on page boundaries. */
#endif /* !PAGEDIR_PAGEALIGNED */


/* x86 uses a 32-/64-bit pointer for `cr3', meaning that physical memory
 * which may exist outside of the address space also addressable without
 * paging enabled cannot be used as a page directory pointer. */
#undef ARCH_PAGEDIR_GETSET_USES_POINTER
#define ARCH_PAGEDIR_GETSET_USES_POINTER 1


#undef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_GETSET
#ifndef __INTELLISENSE__
#define ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_GETSET 1
#ifdef __CC__
/* Low-level Get/Set the physical address of the currently active page directory. */
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL ATTR_PURE WUNUSED PHYS pagedir_t *
NOTHROW(KCALL pagedir_get)(void) {
	pagedir_t *result;
	__asm__("movl %%cr3, %0"
	        : "=r" (result)
	        :
	        : "memory");
	return result;
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(KCALL pagedir_set)(PHYS pagedir_t *__restrict value) {
	__asm__("movl %0, %%cr3"
	        :
	        : "r" (value)
	        : "memory");
}
#endif /* __CC__ */
#endif /* !__INTELLISENSE__ */


/* When more than `ARCH_PAGEDIR_LARGESYNC_THRESHOLD' need to be synced, rather
 * than performing that number of single-page TLB invalidations, invalidate
 * everything instead. */
#ifndef ARCH_PAGEDIR_LARGESYNC_THRESHOLD
#define ARCH_PAGEDIR_LARGESYNC_THRESHOLD 0x100000 /* 256 pages */
#endif /* !ARCH_PAGEDIR_LARGESYNC_THRESHOLD */


#undef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_SYNCALL
#undef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_SYNCONE
#undef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_SYNC
#define ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_SYNCALL 1
#define ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_SYNCONE 1
#define ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_SYNC 1


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
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(FCALL pagedir_syncall_user)(void) {
	__register u32 temp;
	__asm__ __volatile__("movl %%cr3, %0\n\t"
	                     "movl %0, %%cr3"
	                     : "=&r" (temp));
}

/* Same as `pagedir_syncall_user()', but also
 * ensures that all of kernel-space is synced. */
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_syncall)(void);

/* Hybrid of `pagedir_syncall()' and `pagedir_syncall_user()': When the given range
 * overlaps with kernel-space, behave the same as `pagedir_syncall()', otherwise,
 * behave the same as `pagedir_syncall_user()' */
FUNDEF NOBLOCK void
NOTHROW(FCALL x86_pagedir_syncall_maybe_global)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                                PAGEDIR_PAGEALIGNED size_t num_bytes);

/* X86-specific implementation for invalidating every TLB over a given range. */
FUNDEF NOBLOCK void
NOTHROW(FCALL arch_pagedir_sync)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                 PAGEDIR_PAGEALIGNED size_t num_bytes)
		ASMNAME("pagedir_sync");

/* Synchronize mappings within the given address range. */
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_syncone)(VIRT void *addr);

/* Synchronize mappings within the given address range. */
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(FCALL pagedir_sync)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                            PAGEDIR_PAGEALIGNED size_t num_bytes) {
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= 4096) {
			pagedir_syncone(addr);
			return;
		}
		if (num_bytes > KERNELSPACE_BASE) {
			/* We know that the address always _has_ to
			 * fall into kernel-space in this case! */
			pagedir_syncall();
			return;
		}
		if (num_bytes >= ARCH_PAGEDIR_LARGESYNC_THRESHOLD) {
			x86_pagedir_syncall_maybe_global(addr, num_bytes);
			return;
		}
	}
#endif /* !__OMIT_PAGING_CONSTANT_P_WRAPPERS */
	arch_pagedir_sync(addr, num_bytes);
}
#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_PAGING32_H */
