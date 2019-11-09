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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_PAGING_H
#define GUARD_KERNEL_INCLUDE_KERNEL_PAGING_H 1

#include <kernel/compiler.h>
#include <kernel/arch/paging.h>
#include <kernel/types.h>
#include <kos/kernel/paging.h>
#ifndef PAGESIZE
#include <hybrid/limits.h>
#endif /* !PAGESIZE */

DECL_BEGIN

#ifndef VM_VPAGE_MAX
#define VM_VPAGE_MAX       __VM_VPAGE_MAX
#define VM_PPAGE_MAX       __VM_PPAGE_MAX
#endif /* !VM_VPAGE_MAX */
#ifndef VM_PPAGE2ADDR
#define VM_PPAGE2ADDR(page) __VM_PPAGE2ADDR(page)
#endif /* !VM_PPAGE2ADDR */
#ifndef VM_PAGE2ADDR
#define VM_PAGE2ADDR(page) __VM_PAGE2ADDR(page)
#define VM_ADDR2PAGE(addr) __VM_ADDR2PAGE(addr)
#endif /* !VM_PAGE2ADDR */
#ifndef PAGEALIGN
#define PAGEALIGN PAGESIZE
#endif /* !PAGEALIGN */
#ifndef PAGEDIR_ALIGN
#define PAGEDIR_ALIGN 1
#endif /* !PAGEDIR_ALIGN */
#ifndef PAGEDIR_SIZE
#error "Missing `#define PAGEDIR_SIZE'"
#endif /* !PAGEDIR_SIZE */

#ifndef __pagedir_pushval_t_defined
#define __pagedir_pushval_t_defined 1
#define PAGEDIR_PUSHVAL_INVALID (__CCAST(pagedir_pushval_t)-1)
#define SIZEOF_PAGEDIR_PUSHVAL  __SIZEOF_POINTER__
#ifdef __CC__
typedef uintptr_t pagedir_pushval_t;
#endif /* __CC__ */
#endif /* !__pagedir_pushval_t_defined */

#ifdef __CC__
/* The physical and virtual address bindings of the kernel's page directory.
 * This is the initial page directory active when KOS boots, as well as the
 * the directory later used for thread running in kernel-space only. */
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_KERNEL
DATDEF VIRT pagedir_t pagedir_kernel;
DATDEF PHYS pagedir_t pagedir_kernel_phys;
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_KERNEL */

/* Initialize the given page directory.
 * The caller is required to allocate the page directory controller itself, which
 * must be aligned and sized according to `PAGEDIR_ALIGN' and `PAGEDIR_SIZE'. */
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_INIT
#ifdef CONFIG_PAGEDIR_INIT_NEED_PHYS_SELF
#ifdef CONFIG_PAGEDIR_INIT_IS_NOEXCEPT
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pagedir_init)(VIRT pagedir_t *__restrict self,
                            PHYS vm_phys_t phys_self);
#else /* CONFIG_PAGEDIR_INIT_IS_NOEXCEPT */
FUNDEF NOBLOCK NONNULL((1)) void FCALL
pagedir_init(VIRT pagedir_t *__restrict self,
             PHYS vm_phys_t phys_self) THROWS(E_BADALLOC);
#endif /* !CONFIG_PAGEDIR_INIT_IS_NOEXCEPT */
#define pagedir_init1(self)            pagedir_init(self, pagedir_translate((vm_virt_t)(self)))
#define pagedir_init2(self, phys_self) pagedir_init(self, phys_self)
#else /* CONFIG_PAGEDIR_INIT_NEED_PHYS_SELF */
#ifdef CONFIG_PAGEDIR_INIT_IS_NOEXCEPT
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pagedir_init)(VIRT pagedir_t *__restrict self);
#else /* CONFIG_PAGEDIR_INIT_IS_NOEXCEPT */
FUNDEF NOBLOCK NONNULL((1)) void FCALL
pagedir_init(VIRT pagedir_t *__restrict self) THROWS(E_BADALLOC);
#endif /* !CONFIG_PAGEDIR_INIT_IS_NOEXCEPT */
#define pagedir_init1(self)            pagedir_init(self)
#define pagedir_init2(self, phys_self) pagedir_init(self)
#endif /* !CONFIG_PAGEDIR_INIT_NEED_PHYS_SELF */
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_INIT */

/* Finalize a given page directory. */
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_FINI
#ifdef CONFIG_PAGEDIR_FINI_NEED_PHYS_SELF
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pagedir_fini)(VIRT pagedir_t *__restrict self,
                            PHYS vm_phys_t phys_self);
#define pagedir_fini1(self)            pagedir_fini(self, pagedir_translate((vm_virt_t)(self)))
#define pagedir_fini2(self, phys_self) pagedir_fini(self, phys_self)
#else /* CONFIG_PAGEDIR_FINI_NEED_PHYS_SELF */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pagedir_fini)(VIRT pagedir_t *__restrict self);
#define pagedir_fini1(self)            pagedir_fini(self)
#define pagedir_fini2(self, phys_self) pagedir_fini(self)
#endif /* !CONFIG_PAGEDIR_FINI_NEED_PHYS_SELF */
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_FINI */
#endif /* __CC__ */


/* WARNING: If the host does not support some combination of permission
 *          bits, more permissions than specified may be granted.
 *          For example: On X86, write-permissions require read-permissions
 *                       to be granted, and exec-permissions require read. */
#ifndef PAGEDIR_MAP_FMASK
#define PAGEDIR_MAP_FEXEC      0x0001 /* Permission bit: Allow execution within the mapping. */
#define PAGEDIR_MAP_FWRITE     0x0002 /* Permission bit: Permit write-access to memory within mapping. */
#define PAGEDIR_MAP_FREAD      0x0004 /* Permission bit: Permit read-access to memory within mapping. */
#define PAGEDIR_MAP_FUSER      0x0008 /* Permission bit: Permit the user access to the mapping. */
#define PAGEDIR_MAP_FMASK      0x000f /* Mask of valid permission bits. */
#endif /* !PAGEDIR_MAP_FMASK */


#ifdef __CC__
/* Prepare the page directory for a future map() operation.
 * The full cycle of a single mapping then looks like this:
 * >> pagedir_prepare_map(...);
 * >> pagedir_map(...);
 * >> pagedir_unmap(...);
 * >> pagedir_unprepare_map(...);
 * NOTE: A prepared mapping is not only valid for the exact range.
 *       Wishing to map something at a sub-range of it is also allowed:
 *       >> pagedir_prepare_map(5,6);   // Prepage 6 pages at page-index 5 for modification
 *       >> pagedir_map(5,3);           // OK
 *       >> pagedir_map(8,3);           // OK
 *       >> pagedir_unprepare_map(5,6); // Indicate that the 6 pages must not longer be modified
 * TODO: At one point, the restrictions on this functionality became somewhat looser:
 *        - Before, preparing and then mapping some address range used to allow the
 *          page directory implementation to optionally get rid of any preparations
 *          contained within a linearly mapped address range.
 *        - This used to mean that the following code was illegal, however no longer is:
 *          >> pagedir_prepare_map(3, 4);
 *          >> pagedir_map(3, 4);
 *          >> pagedir_unmap(3, 2); // This used to be illegal, since `pagedir_map()' was allowed to undo preparations
 *          >> pagedir_unmap(5, 2);
 *        - Now however, preparations aren't as volatile as they used to be, and are
 *          actually being enforced by the page directory back-ends.
 *          However, some legacy code (most definitely) exists that used to re-prepare mappings
 *          that were already prepared because there was a chance that they no longer were.
 *          Get rid of such code.
 *        - Also: Strictly enforce use of `VM_NODE_FLAG_PREPARED' to indicate if some mapping
 *                is prepared, and don't keep mappings prepared longer than they need to be!
 * NOTE: `pagedir_prepare_map_keep()' is the same as `pagedir_prepare_map()', but
 *        will not undo already successfully made preparations after a later one fails.
 *        This will include the undoing of redundant preparations of the given range that
 *        were made in prior calls.
 * WARNING: prepare() + unprepare() _DONT_ work recursively, and are also not thread-safe
 * WARNING: unprepare() should always be called with the same range as prepare()
 * @return: true:  Successfully allocated structures required for creating mappings.
 * @return: false: Insufficient physical memory to change mappings. */
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_PREPARE
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(FCALL pagedir_prepare_mapone)(VIRT vm_vpage_t virt_page);
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_unprepare_mapone)(VIRT vm_vpage_t virt_page);
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(FCALL __os_pagedir_prepare_map)(VIRT vm_vpage_t virt_page, size_t num_pages) ASMNAME("pagedir_prepare_map");
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(FCALL __os_pagedir_prepare_map_keep)(VIRT vm_vpage_t virt_page, size_t num_pages) ASMNAME("pagedir_prepare_map_keep");
FUNDEF NOBLOCK void NOTHROW(FCALL __os_pagedir_unprepare_map)(VIRT vm_vpage_t virt_page, size_t num_pages) ASMNAME("pagedir_unprepare_map");
FORCELOCAL NOBLOCK WUNUSED __BOOL
NOTHROW(FCALL pagedir_prepare_map)(VIRT vm_vpage_t virt_page, size_t num_pages) {
	if (__builtin_constant_p(num_pages)) {
		if (num_pages == 1)
			return pagedir_prepare_mapone(virt_page);
		if (num_pages == 0)
			return true;
	}
	return __os_pagedir_prepare_map(virt_page, num_pages);
}
FORCELOCAL NOBLOCK WUNUSED __BOOL
NOTHROW(FCALL pagedir_prepare_map_keep)(VIRT vm_vpage_t virt_page, size_t num_pages) {
	if (__builtin_constant_p(num_pages)) {
		if (num_pages == 1)
			return pagedir_prepare_mapone(virt_page);
		if (num_pages == 0)
			return true;
	}
	return __os_pagedir_prepare_map_keep(virt_page, num_pages);
}
FORCELOCAL NOBLOCK void
NOTHROW(FCALL pagedir_unprepare_map)(VIRT vm_vpage_t virt_page, size_t num_pages) {
	if (__builtin_constant_p(num_pages)) {
		if (num_pages == 1) {
			pagedir_unprepare_mapone(virt_page);
			return;
		}
		if (num_pages == 0)
			return;
	}
	__os_pagedir_unprepare_map(virt_page, num_pages);
}
#else
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(FCALL pagedir_prepare_map)(VIRT vm_vpage_t virt_page, size_t num_pages);
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(FCALL pagedir_prepare_map_keep)(VIRT vm_vpage_t virt_page, size_t num_pages);
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_unprepare_map)(VIRT vm_vpage_t virt_page, size_t num_pages);
#endif
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_PREPARE */



/* Set a mapping hint for pages apart of the given virtual memory range.
 * Mapping hints are overwritten once a page has been mapped, and when
 * not specified, will default to `NULL'.
 * Their main purpose is to be accessible through atomic means, allowing
 * them to be used by the PAGE_FAULT handler, while still ensuring that
 * access remains non-blocking.
 * Note that because of platform-specific restrictions, only pointers
 * which are aligned by at least `PAGEDIR_MAPHINT_ALIGNMENT' bytes can
 * be specified as hints.
 *   - Use of this function requires a prior call to `pagedir_prepare_map()'!
 *   - Memory mappings defined in `vm_kernel' to be non-blocking have their
 *     mapping hint set to the address of the associated `struct vm_node' */
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_MAPHINT
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_maphintone)(VIRT vm_vpage_t virt_page, VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/void *hint);
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK void NOTHROW(FCALL __os_pagedir_maphint)(VIRT vm_vpage_t virt_page, size_t num_pages, VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/void *hint) ASMNAME("pagedir_maphint");
FORCELOCAL NOBLOCK void
NOTHROW(FCALL pagedir_maphint)(VIRT vm_vpage_t virt_page, size_t num_pages,
                                VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/void *hint) {
	if (__builtin_constant_p(num_pages)) {
		if (num_pages == 1) {
			pagedir_maphintone(virt_page, hint);
			return;
		}
		if (num_pages == 0)
			return;
	}
	__os_pagedir_maphint(virt_page, num_pages, hint);
}
#else
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_maphint)(VIRT vm_vpage_t virt_page, size_t num_pages, VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/void *hint);
#endif
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_MAPHINT */

/* Return the given of the given page, or NULL if no hint has been mapped. */
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_GETHINT
FUNDEF NOBLOCK WUNUSED void *NOTHROW(FCALL pagedir_gethint)(VIRT vm_vpage_t virt_page);
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_GETHINT */

/* Create/delete a page-directory mapping.
 * @param: perm: A set of `PAGEDIR_MAP_F*' detailing how memory should be mapped.
 * `pagedir_sync()' must be called while specifying a virtual address range containing
 * `virt_page...+=num_pages' in order to ensure that changes will become visible.
 * NOTE: This function can be called regardless of which page directory is active. */
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_MAP
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_mapone)(VIRT vm_vpage_t virt_page, PHYS vm_ppage_t phys_page, u16 perm);
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK void NOTHROW(FCALL __os_pagedir_map)(VIRT vm_vpage_t virt_page, size_t num_pages, PHYS vm_ppage_t phys_page, u16 perm) ASMNAME("pagedir_map");
FORCELOCAL NOBLOCK void
NOTHROW(FCALL pagedir_map)(VIRT vm_vpage_t virt_page, size_t num_pages,
                           PHYS vm_ppage_t phys_page, u16 perm) {
	if (__builtin_constant_p(num_pages)) {
		if (num_pages == 1) {
			pagedir_mapone(virt_page, phys_page, perm);
			return;
		}
		if (num_pages == 0)
			return;
	}
	__os_pagedir_map(virt_page, num_pages, phys_page, perm);
}
#else
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_map)(VIRT vm_vpage_t virt_page, size_t num_pages, PHYS vm_ppage_t phys_page, u16 perm);
#endif
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_MAP */

/* Special variants of `pagedir_mapone()' that should be used to
 * temporary override the mapping of a single, prepared page.
 * These functions are mainly intended for use with `_this_trampoline_page', allowing
 * each thread to push/pop its trampoline page, with doing so actually being an atomic
 * operation in the sense that the data is entirely thread-private, while modifications
 * do not require any kind of lock.
 * NOTE: If the page had been mapped, `pagedir_pop_mapone()' will automatically sync the page. */
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_PUSH_MAPONE
FUNDEF NOBLOCK WUNUSED pagedir_pushval_t
NOTHROW(FCALL pagedir_push_mapone)(VIRT vm_vpage_t virt_page, PHYS vm_ppage_t phys_page, u16 perm);
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_pop_mapone)(VIRT vm_vpage_t virt_page, pagedir_pushval_t backup);
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_PUSH_MAPONE */

/* Unmap pages from the given address range. (requires that the given area be prepared) */
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_UNMAP
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_unmapone)(VIRT vm_vpage_t virt_page);
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK void NOTHROW(FCALL __os_pagedir_unmap)(VIRT vm_vpage_t virt_page, size_t num_pages) ASMNAME("pagedir_unmap");
FORCELOCAL NOBLOCK void
NOTHROW(FCALL pagedir_unmap)(VIRT vm_vpage_t virt_page, size_t num_pages) {
	if (__builtin_constant_p(num_pages)) {
		if (num_pages == 1) {
			pagedir_unmapone(virt_page);
			return;
		}
		if (num_pages == 0)
			return;
	}
	__os_pagedir_unmap(virt_page, num_pages);
}
#else
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_unmap)(VIRT vm_vpage_t virt_page, size_t num_pages);
#endif
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_UNMAP */


/* Remove write-permissions from the given address range. (requires that the given area be prepared) */
#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_UNWRITE
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_unwriteone)(VIRT vm_vpage_t virt_page);
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK void NOTHROW(FCALL __os_pagedir_unwrite)(VIRT vm_vpage_t virt_page, size_t num_pages) ASMNAME("pagedir_unwrite");
FORCELOCAL NOBLOCK void
NOTHROW(FCALL pagedir_unwrite)(VIRT vm_vpage_t virt_page, size_t num_pages) {
	if (__builtin_constant_p(num_pages)) {
		if (num_pages == 1) {
			pagedir_unwriteone(virt_page);
			return;
		}
		if (num_pages == 0)
			return;
	}
	__os_pagedir_unwrite(virt_page, num_pages);
}
#else
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_unwrite)(VIRT vm_vpage_t virt_page, size_t num_pages);
#endif
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_UNWRITE */
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */


struct vm;
/* Unmap the entirety of user-space.
 * NOTE: Unlike all other unmap() functions, this one guaranties that it
 *       can perform the task without needing to allocate more memory! */
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_UNMAP_USERSPACE
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_unmap_userspace)(struct vm *__restrict sync_vm);
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_unmap_userspace_nosync)(void);
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_UNMAP_USERSPACE */


#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_SYNCALL
/* Synchronize the entirety of the current page directory.
 * Note that this function may only sync all user-space mappings. If the
 * intent is to also sync all of kernel-space, `pagedir_syncall()'
 * must be used instead. */
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_syncall_user)(void);
/* Same as `pagedir_syncall()', but also ensures that
 * all of kernel-space is synced. */
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_syncall)(void);
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_SYNCALL */

#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_SYNCONE
/* Synchronize mappings within the given address range. */
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_syncone)(VIRT vm_vpage_t virt_page);
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_SYNCONE */

#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_SYNC
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK void NOTHROW(FCALL __os_pagedir_sync)(VIRT vm_vpage_t virt_page, size_t num_pages) ASMNAME("pagedir_sync");
FORCELOCAL NOBLOCK void
NOTHROW(FCALL pagedir_sync)(VIRT vm_vpage_t virt_page, size_t num_pages) {
	if (__builtin_constant_p(num_pages)) {
		if (num_pages == 1) {
			pagedir_syncone(virt_page);
			return;
		}
		if (num_pages == 0)
			return;
	}
	__os_pagedir_sync(virt_page, num_pages);
}
#else
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_sync)(VIRT vm_vpage_t virt_page, size_t num_pages);
#endif
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_SYNC */

/* Translate a virtual address into its physical counterpart. */
FUNDEF NOBLOCK WUNUSED PHYS vm_phys_t NOTHROW(FCALL pagedir_translate)(VIRT vm_virt_t virt_addr);

/* Check if the given page is mapped. */
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_ISMAPPED
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(FCALL pagedir_ismapped)(VIRT vm_vpage_t vpage);
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(FCALL pagedir_iswritable)(VIRT vm_vpage_t vpage);
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(FCALL pagedir_isuseraccessible)(VIRT vm_vpage_t vpage);
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(FCALL pagedir_isuserwritable)(VIRT vm_vpage_t vpage);
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_ISMAPPED */

#ifdef CONFIG_HAVE_PAGEDIR_CHANGED
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_HASCHANGED
/* TODO: Figure out a better design for these functions
 *       The current system is written under the assumption that 4MiB pages don't exist... */
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(FCALL pagedir_haschanged)(VIRT vm_vpage_t vpage);
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_unsetchanged)(VIRT vm_vpage_t vpage);
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_HASCHANGED */
#endif /* CONFIG_HAVE_PAGEDIR_CHANGED */


/* Low-level Get/Set the physical address of the currently active page directory. */
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_GETSET
#ifdef CONFIG_PAGEDIR_GETSET_USES_POINTER
FUNDEF NOBLOCK PHYS pagedir_t *NOTHROW(KCALL pagedir_get)(void);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_set)(PHYS pagedir_t *__restrict value);
#else /* CONFIG_PAGEDIR_GETSET_USES_POINTER */
FUNDEF NOBLOCK PHYS vm_phys_t NOTHROW(KCALL pagedir_get)(void);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_set)(PHYS vm_phys_t value);
#endif /* !CONFIG_PAGEDIR_GETSET_USES_POINTER */
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_GETSET */


/* Return the smallest active page size/alignment/number-of-bytes-per-page
 * possible with the current page directory.
 * Note that this value is always:
 *    - `>= PAGEDIR_MIN_PAGESIZE'
 *    - `<= PAGEDIR_MAX_PAGESIZE'
 *    - A power-of-2 value */
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_PAGESIZE
#if (PAGEDIR_MIN_PAGESIZE == PAGEDIR_MAX_PAGESIZE) && !defined(__INTELLISENSE__)
#define pagedir_pagesize()  PAGEDIR_MIN_PAGESIZE
#else /* PAGEDIR_MIN_PAGESIZE == PAGEDIR_MAX_PAGESIZE */
FUNDEF NOBLOCK ATTR_CONST WUNUSED size_t NOTHROW(KCALL pagedir_pagesize)(void);
#endif /* PAGEDIR_MIN_PAGESIZE != PAGEDIR_MAX_PAGESIZE */
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_PAGESIZE */

#if !defined(PAGEDIR_MIN_PAGESIZE) || !defined(PAGEDIR_MAX_PAGESIZE)
#error "Arch forgot to define PAGEDIR_MIN_PAGESIZE/PAGEDIR_MAX_PAGESIZE"
#endif /* !PAGEDIR_MIN_PAGESIZE || !PAGEDIR_MAX_PAGESIZE */

#ifndef PAGEDIR_API_P_SELFARG
#ifdef CONFIG_PAGEDIR_GETSET_USES_POINTER
#define PAGEDIR_P_SELFTYPE      PHYS pagedir_t *
#define PAGEDIR_P_SELFOFVM(vm) (vm)->v_pdir_phys_ptr
#else /* CONFIG_PAGEDIR_GETSET_USES_POINTER */
#define PAGEDIR_P_SELFTYPE      PHYS vm_phys_t
#define PAGEDIR_P_SELFOFVM(vm) (vm)->v_pdir_phys
#endif /* !CONFIG_PAGEDIR_GETSET_USES_POINTER */
#endif /* !PAGEDIR_API_P_SELFARG */

#if defined(__INTELLISENSE__)
typedef struct { PAGEDIR_P_SELFTYPE _m_self; } __pagedir_p_selftype;
__FORCELOCAL ATTR_CONST __pagedir_p_selftype KCALL __pagedir_p_selfofvm(struct vm *__restrict v);
#undef PAGEDIR_P_SELFTYPE
#undef PAGEDIR_P_SELFOFVM
#define PAGEDIR_P_SELFTYPE __pagedir_p_selftype
#define PAGEDIR_P_SELFOFVM __pagedir_p_selfofvm
#endif /* __INTELLISENSE__ */


/* Same as the functions above, but operate on the specified
 * page directory, rather than the one currently being used.
 * NOTE: The caller is responsible for synchronization. */
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(KCALL pagedir_prepare_mapone_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unprepare_mapone_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_maphintone_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/void *hint);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_mapone_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, PHYS vm_ppage_t phys_page, u16 perm);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unmapone_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page);
#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unwriteone_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page);
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */
FUNDEF NOBLOCK PHYS vm_phys_t NOTHROW(KCALL pagedir_translate_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_virt_t virt_addr);
FUNDEF NOBLOCK __BOOL NOTHROW(KCALL pagedir_ismapped_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t vpage);
FUNDEF NOBLOCK __BOOL NOTHROW(KCALL pagedir_iswritable_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t vpage);
FUNDEF NOBLOCK __BOOL NOTHROW(KCALL pagedir_isuseraccessible_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t vpage);
FUNDEF NOBLOCK __BOOL NOTHROW(KCALL pagedir_isuserwritable_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t vpage);
#ifdef CONFIG_HAVE_PAGEDIR_CHANGED
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(KCALL pagedir_haschanged_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t vpage);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unsetchanged_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t vpage);
#endif /* CONFIG_HAVE_PAGEDIR_CHANGED */
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(KCALL __os_pagedir_prepare_map_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages) ASMNAME("pagedir_prepare_map_p");
FUNDEF NOBLOCK void NOTHROW(KCALL __os_pagedir_unprepare_map_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages) ASMNAME("pagedir_unprepare_map_p");
FUNDEF NOBLOCK void NOTHROW(KCALL __os_pagedir_maphint_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages, VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/void *hint) ASMNAME("pagedir_maphint_p");
FUNDEF NOBLOCK void NOTHROW(KCALL __os_pagedir_map_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages, PHYS vm_ppage_t phys_page, u16 perm) ASMNAME("pagedir_map_p");
FUNDEF NOBLOCK void NOTHROW(KCALL __os_pagedir_unmap_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages) ASMNAME("pagedir_unmap_p");
#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
FUNDEF NOBLOCK void NOTHROW(KCALL __os_pagedir_unwrite_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages) ASMNAME("pagedir_unwrite_p");
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */
FORCELOCAL NOBLOCK WUNUSED __BOOL
NOTHROW(KCALL pagedir_prepare_map_p)(PAGEDIR_P_SELFTYPE self,
                                     VIRT vm_vpage_t virt_page, size_t num_pages) {
	if (__builtin_constant_p(num_pages)) {
		if (num_pages == 1)
			return pagedir_prepare_mapone_p(self, virt_page);
		if (num_pages == 0)
			return true;
	}
	return __os_pagedir_prepare_map_p(self, virt_page, num_pages);
}
FORCELOCAL NOBLOCK void
NOTHROW(KCALL pagedir_unprepare_map_p)(PAGEDIR_P_SELFTYPE self,
                                       VIRT vm_vpage_t virt_page, size_t num_pages) {
	if (__builtin_constant_p(num_pages)) {
		if (num_pages == 1) {
			pagedir_unprepare_mapone_p(self, virt_page);
			return;
		}
		if (num_pages == 0)
			return;
	}
	__os_pagedir_unprepare_map_p(self, virt_page, num_pages);
}
FORCELOCAL NOBLOCK void
NOTHROW(KCALL pagedir_maphint_p)(PAGEDIR_P_SELFTYPE self,
                                 VIRT vm_vpage_t virt_page, size_t num_pages,
                                 VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/void *hint) {
	if (__builtin_constant_p(num_pages)) {
		if (num_pages == 1) {
			pagedir_maphintone_p(self, virt_page, hint);
			return;
		}
		if (num_pages == 0)
			return;
	}
	__os_pagedir_maphint_p(self, virt_page, num_pages, hint);
}
FORCELOCAL NOBLOCK void
NOTHROW(KCALL pagedir_map_p)(PAGEDIR_P_SELFTYPE self,
                             VIRT vm_vpage_t virt_page, size_t num_pages,
                             PHYS vm_ppage_t phys_page, u16 perm) {
	if (__builtin_constant_p(num_pages)) {
		if (num_pages == 1) {
			pagedir_mapone_p(self, virt_page, phys_page, perm);
			return;
		}
		if (num_pages == 0)
			return;
	}
	__os_pagedir_map_p(self, virt_page, num_pages, phys_page, perm);
}
FORCELOCAL NOBLOCK void
NOTHROW(KCALL pagedir_unmap_p)(PAGEDIR_P_SELFTYPE self,
                               VIRT vm_vpage_t virt_page, size_t num_pages) {
	if (__builtin_constant_p(num_pages)) {
		if (num_pages == 1) {
			pagedir_unmapone_p(self, virt_page);
			return;
		}
		if (num_pages == 0)
			return;
	}
	__os_pagedir_unmap_p(self, virt_page, num_pages);
}
#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
FORCELOCAL NOBLOCK void
NOTHROW(KCALL pagedir_unwrite_p)(PAGEDIR_P_SELFTYPE self,
                                 VIRT vm_vpage_t virt_page, size_t num_pages) {
	if (__builtin_constant_p(num_pages)) {
		if (num_pages == 1) {
			pagedir_unwriteone_p(self, virt_page);
			return;
		}
		if (num_pages == 0)
			return;
	}
	__os_pagedir_unwrite_p(self, virt_page, num_pages);
}
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */
#else
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(KCALL pagedir_prepare_map_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unprepare_map_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_maphint_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages, VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/void *hint);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_map_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages, PHYS vm_ppage_t phys_page, u16 perm);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unmap_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages);
#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unwrite_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages);
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */
#endif
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unmap_userspace_p)(PAGEDIR_P_SELFTYPE self, struct vm *__restrict sync_vm);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unmap_userspace_nosync_p)(PAGEDIR_P_SELFTYPE self);


#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_PAGESIZE_P
#if (PAGEDIR_MIN_PAGESIZE == PAGEDIR_MAX_PAGESIZE) && !defined(__INTELLISENSE__)
#define pagedir_pagesize_p(self)  PAGEDIR_MIN_PAGESIZE
#else /* PAGEDIR_MIN_PAGESIZE == PAGEDIR_MAX_PAGESIZE */
FUNDEF NOBLOCK ATTR_CONST WUNUSED size_t NOTHROW(KCALL pagedir_pagesize_p)(PAGEDIR_P_SELFTYPE self);
#endif /* PAGEDIR_MIN_PAGESIZE != PAGEDIR_MAX_PAGESIZE */
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_PAGESIZE_P */


#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_PAGING_H */
