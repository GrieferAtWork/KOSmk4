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

#include <asm/pagesize.h>
#include <kos/kernel/paging.h>

#ifndef PAGESIZE
#define PAGESIZE __ARCH_PAGESIZE
#elif PAGESIZE != __ARCH_PAGESIZE
#error "Miss-configured: `PAGESIZE != __ARCH_PAGESIZE'"
#endif

#ifndef PAGESHIFT
#define PAGESHIFT __ARCH_PAGESHIFT
#elif PAGESHIFT != __ARCH_PAGESHIFT
#error "Miss-configured: `PAGESHIFT != __ARCH_PAGESHIFT'"
#endif


DECL_BEGIN

#ifndef VM_VPAGE_MAX
#define VM_VPAGE_MAX       __VM_VPAGE_MAX /* DEPRECATED; REMOVE ME */
#define VM_PPAGE_MAX       __VM_PPAGE_MAX /* DEPRECATED; REMOVE ME */
#endif /* !VM_VPAGE_MAX */
#ifndef VM_PPAGE2ADDR
#define VM_PPAGE2ADDR(page) __VM_PPAGE2ADDR(page) /* DEPRECATED; REMOVE ME */
#endif /* !VM_PPAGE2ADDR */
#ifndef VM_PAGE2ADDR
#define VM_PAGE2ADDR(page) __VM_PAGE2ADDR(page) /* DEPRECATED; REMOVE ME */
#define VM_ADDR2PAGE(addr) __VM_ADDR2PAGE(addr) /* DEPRECATED; REMOVE ME */
#endif /* !VM_PAGE2ADDR */
#ifndef PAGEDIR_ALIGN
#define PAGEDIR_ALIGN PAGESIZE
#endif /* !PAGEDIR_ALIGN */
#ifndef PAGEDIR_SIZE
#define PAGEDIR_SIZE PAGESIZE
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
#define pagedir_init1(self)            pagedir_init(self, pagedir_translate(self))
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
#define pagedir_fini1(self)            pagedir_fini(self, pagedir_translate(self))
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
#ifdef CONFIG_USE_NEW_PAGING
FUNDEF NOBLOCK void NOTHROW(FCALL npagedir_syncone)(VIRT void *addr);
#else /* CONFIG_USE_NEW_PAGING */
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_syncone)(VIRT vm_vpage_t virt_page);
#endif /* !CONFIG_USE_NEW_PAGING */
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_SYNCONE */

/* Translate a virtual address into its physical counterpart. */
FUNDEF NOBLOCK WUNUSED PHYS vm_phys_t NOTHROW(FCALL pagedir_translate)(VIRT void *addr);
FUNDEF NOBLOCK PHYS vm_phys_t NOTHROW(KCALL pagedir_translate_p)(PAGEDIR_P_SELFTYPE self, VIRT void *addr);

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


struct vm;
/* Unmap the entirety of user-space.
 * NOTE: Unlike all other unmap() functions, this one guaranties that it
 *       can perform the task without needing to allocate more memory! */
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_UNMAP_USERSPACE
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_unmap_userspace)(struct vm *__restrict sync_vm);
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_unmap_userspace_nosync)(void);
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_UNMAP_USERSPACE */

#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_UNMAP_USERSPACE_P
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unmap_userspace_p)(PAGEDIR_P_SELFTYPE self, struct vm *__restrict sync_vm);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unmap_userspace_nosync_p)(PAGEDIR_P_SELFTYPE self);
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_UNMAP_USERSPACE_P */

/* Temporarily switch to a different page directory `self'
 * @param: self: The page directory to switch to (of type `PAGEDIR_P_SELFTYPE') */
#ifdef __INTELLISENSE__
#define PAGEDIR_P_BEGINUSE(self) do
#define PAGEDIR_P_ENDUSE(self)   __WHILE0
#else /* __INTELLISENSE__ */
#define PAGEDIR_P_BEGINUSE(self)                              \
	do {                                                      \
		PAGEDIR_P_SELFTYPE _old_pdir;                         \
		pflag_t _p_was = PREEMPTION_PUSHOFF();                \
		assert(IS_ALIGNED((uintptr_t)(self), PAGEDIR_ALIGN)); \
		_old_pdir = pagedir_get();                            \
		if (_old_pdir != (self))                              \
			pagedir_set(self);                                \
		do
#define PAGEDIR_P_ENDUSE(self)      \
		__WHILE0;                   \
		if (_old_pdir != (self))    \
			pagedir_set(_old_pdir); \
		PREEMPTION_POP(_p_was);     \
	} __WHILE0
#endif /* !__INTELLISENSE__ */




#ifdef CONFIG_USE_NEW_PAGING

#ifndef PAGEDIR_PAGEALIGNED
#define PAGEDIR_PAGEALIGNED /* Annotation for variables that need to be aligned on page boundaries. */
#endif /* !PAGEDIR_PAGEALIGNED */

/* Prepare the page directory for a future map() operation.
 * The full cycle of a single mapping then looks like this:
 * >> npagedir_prepare_map(...);
 * >> npagedir_map(...);
 * >> npagedir_unmap(...);
 * >> npagedir_unprepare_map(...);
 * NOTE: A prepared mapping is not only valid for the exact range.
 *       Wishing to map something at a sub-range of it is also allowed:
 *       >> npagedir_prepare_map(5, 6);   // Prepage 6 pages at page-index 5 for modification
 *       >> npagedir_map(5, 3);           // OK
 *       >> npagedir_map(8, 3);           // OK
 *       >> npagedir_unprepare_map(5, 6); // Indicate that the 6 pages must not longer be modified
 * NOTE: `npagedir_prepare_map_keep()' is the same as `npagedir_prepare_map()', but
 *        will not undo already successfully made preparations after a later one fails.
 *        This will include the undoing of redundant preparations of the given range that
 *        were made in prior calls.
 * WARNING: prepare() + unprepare() _DONT_ work recursively, and are also not thread-safe
 * WARNING: unprepare() should always be called with the same range as prepare()
 * @return: true:  Successfully allocated structures required for creating mappings.
 * @return: false: Insufficient physical memory to change mappings. */
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_PREPARE
FUNDEF NOBLOCK WUNUSED __BOOL
NOTHROW(FCALL npagedir_prepare_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr);
FUNDEF NOBLOCK void
NOTHROW(FCALL npagedir_unprepare_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr);
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK WUNUSED __BOOL
NOTHROW(FCALL __os_npagedir_prepare_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                         PAGEDIR_PAGEALIGNED size_t num_bytes)
		ASMNAME("npagedir_prepare_map");
FUNDEF NOBLOCK WUNUSED __BOOL
NOTHROW(FCALL __os_npagedir_prepare_map_keep)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                              PAGEDIR_PAGEALIGNED size_t num_bytes)
		ASMNAME("npagedir_prepare_map_keep");
FUNDEF NOBLOCK void
NOTHROW(FCALL __os_npagedir_unprepare_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                           PAGEDIR_PAGEALIGNED size_t num_bytes)
		ASMNAME("npagedir_unprepare_map");
FORCELOCAL NOBLOCK WUNUSED __BOOL
NOTHROW(FCALL npagedir_prepare_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                    PAGEDIR_PAGEALIGNED size_t num_bytes) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return true;
		if (num_bytes <= PAGESIZE)
			return npagedir_prepare_mapone(addr);
	}
	return __os_npagedir_prepare_map(addr, num_bytes);
}

FORCELOCAL NOBLOCK WUNUSED __BOOL
NOTHROW(FCALL npagedir_prepare_map_keep)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                         PAGEDIR_PAGEALIGNED size_t num_bytes) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return true;
		if (num_bytes <= PAGESIZE)
			return npagedir_prepare_mapone(addr);
	}
	return __os_npagedir_prepare_map_keep(addr, num_bytes);
}

FORCELOCAL NOBLOCK void
NOTHROW(FCALL npagedir_unprepare_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                      PAGEDIR_PAGEALIGNED size_t num_bytes) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			npagedir_unprepare_mapone(addr);
			return;
		}
	}
	__os_npagedir_unprepare_map(addr, num_bytes);
}
#else /* !__OMIT_PAGING_CONSTANT_P_WRAPPERS */
FUNDEF NOBLOCK WUNUSED __BOOL
NOTHROW(FCALL npagedir_prepare_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                    PAGEDIR_PAGEALIGNED size_t num_bytes);
FUNDEF NOBLOCK WUNUSED __BOOL
NOTHROW(FCALL npagedir_prepare_map_keep)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                         PAGEDIR_PAGEALIGNED size_t num_bytes);
FUNDEF NOBLOCK void
NOTHROW(FCALL npagedir_unprepare_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                      PAGEDIR_PAGEALIGNED size_t num_bytes);
#endif /* __OMIT_PAGING_CONSTANT_P_WRAPPERS */
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
 *   - Use of this function requires a prior call to `npagedir_prepare_map()'!
 *   - Memory mappings defined in `vm_kernel' to be non-blocking have their
 *     mapping hint set to the address of the associated `struct vm_node' */
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_MAPHINT
FUNDEF NOBLOCK void
NOTHROW(FCALL npagedir_maphintone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                   VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint);
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK void
NOTHROW(FCALL __os_npagedir_maphint)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                     PAGEDIR_PAGEALIGNED size_t num_bytes,
                                     VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint)
		ASMNAME("npagedir_maphint");
FORCELOCAL NOBLOCK void
NOTHROW(FCALL npagedir_maphint)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                PAGEDIR_PAGEALIGNED size_t num_bytes,
                                VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			npagedir_maphintone(addr, hint);
			return;
		}
	}
	__os_npagedir_maphint(addr, num_bytes, hint);
}
#else /* !__OMIT_PAGING_CONSTANT_P_WRAPPERS */
FUNDEF NOBLOCK void
NOTHROW(FCALL npagedir_maphint)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                PAGEDIR_PAGEALIGNED size_t num_bytes,
                                VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint);
#endif /* __OMIT_PAGING_CONSTANT_P_WRAPPERS */
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_MAPHINT */

/* Return the given of the given page, or NULL if no hint has been mapped. */
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_GETHINT
FUNDEF NOBLOCK WUNUSED void *NOTHROW(FCALL npagedir_gethint)(VIRT void *addr);
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_GETHINT */

/* Create/delete a page-directory mapping.
 * @param: perm: A set of `PAGEDIR_MAP_F*' detailing how memory should be mapped.
 * `npagedir_sync()' must be called while specifying a virtual address range containing
 * `addr...+=num_bytes' in order to ensure that changes will become visible.
 * NOTE: This function can be called regardless of which page directory is active. */
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_MAP
FUNDEF NOBLOCK void NOTHROW(FCALL npagedir_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                                   PAGEDIR_PAGEALIGNED PHYS vm_phys_t phys,
                                                   u16 perm);
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK void NOTHROW(FCALL __os_npagedir_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                                     PAGEDIR_PAGEALIGNED size_t num_bytes,
                                                     PAGEDIR_PAGEALIGNED PHYS vm_phys_t phys,
                                                     u16 perm)
		ASMNAME("npagedir_map");
FORCELOCAL NOBLOCK void
NOTHROW(FCALL npagedir_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                            PAGEDIR_PAGEALIGNED size_t num_bytes,
                            PAGEDIR_PAGEALIGNED PHYS vm_phys_t phys,
                            u16 perm) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			npagedir_mapone(addr, phys, perm);
			return;
		}
	}
	__os_npagedir_map(addr, num_bytes, phys, perm);
}
#else /* !__OMIT_PAGING_CONSTANT_P_WRAPPERS */
FUNDEF NOBLOCK void
NOTHROW(FCALL npagedir_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                            PAGEDIR_PAGEALIGNED size_t num_bytes,
                            PAGEDIR_PAGEALIGNED PHYS vm_phys_t phys,
                            u16 perm);
#endif /* __OMIT_PAGING_CONSTANT_P_WRAPPERS */
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_MAP */

/* Special variants of `npagedir_mapone()' that should be used to
 * temporary override the mapping of a single, prepared page.
 * These functions are mainly intended for use with `this_trampoline_page', allowing
 * each thread to push/pop its trampoline page, with doing so actually being an atomic
 * operation in the sense that the data is entirely thread-private, while modifications
 * do not require any kind of lock.
 * NOTE: If the page had been mapped, `npagedir_pop_mapone()' will automatically sync the page. */
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_PUSH_MAPONE
FUNDEF NOBLOCK WUNUSED pagedir_pushval_t
NOTHROW(FCALL npagedir_push_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                    PAGEDIR_PAGEALIGNED PHYS vm_phys_t phys, u16 perm);
FUNDEF NOBLOCK void
NOTHROW(FCALL npagedir_pop_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                   pagedir_pushval_t backup);
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_PUSH_MAPONE */

/* Unmap pages from the given address range. (requires that the given area be prepared) */
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_UNMAP
FUNDEF NOBLOCK void
NOTHROW(FCALL npagedir_unmapone)(PAGEDIR_PAGEALIGNED VIRT void *addr);
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK void
NOTHROW(FCALL __os_npagedir_unmap)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                   PAGEDIR_PAGEALIGNED size_t num_bytes)
		ASMNAME("npagedir_unmap");
FORCELOCAL NOBLOCK void
NOTHROW(FCALL npagedir_unmap)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                              PAGEDIR_PAGEALIGNED size_t num_bytes) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			npagedir_unmapone(addr);
			return;
		}
	}
	__os_npagedir_unmap(addr, num_bytes);
}
#else /* !__OMIT_PAGING_CONSTANT_P_WRAPPERS */
FUNDEF NOBLOCK void
NOTHROW(FCALL npagedir_unmap)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                              PAGEDIR_PAGEALIGNED size_t num_bytes);
#endif /* __OMIT_PAGING_CONSTANT_P_WRAPPERS */
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_UNMAP */


/* Remove write-permissions from the given address range. (requires that the given area be prepared) */
#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_UNWRITE
FUNDEF NOBLOCK void
NOTHROW(FCALL npagedir_unwriteone)(PAGEDIR_PAGEALIGNED VIRT void *addr);
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK void
NOTHROW(FCALL __os_npagedir_unwrite)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                     PAGEDIR_PAGEALIGNED size_t num_bytes)
		ASMNAME("npagedir_unwrite");
FORCELOCAL NOBLOCK void
NOTHROW(FCALL npagedir_unwrite)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                PAGEDIR_PAGEALIGNED size_t num_bytes) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			npagedir_unwriteone(addr);
			return;
		}
	}
	__os_npagedir_unwrite(addr, num_bytes);
}
#else /* !__OMIT_PAGING_CONSTANT_P_WRAPPERS */
FUNDEF NOBLOCK void
NOTHROW(FCALL npagedir_unwrite)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                PAGEDIR_PAGEALIGNED size_t num_bytes);
#endif /* __OMIT_PAGING_CONSTANT_P_WRAPPERS */
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_UNWRITE */
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */


#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_SYNC
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK void
NOTHROW(FCALL __os_npagedir_sync)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                  PAGEDIR_PAGEALIGNED size_t num_bytes)
		ASMNAME("npagedir_sync");
FORCELOCAL NOBLOCK void
NOTHROW(FCALL npagedir_sync)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                             PAGEDIR_PAGEALIGNED size_t num_bytes) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			npagedir_syncone(addr);
			return;
		}
	}
	__os_npagedir_sync(addr, num_bytes);
}
#else
FUNDEF NOBLOCK void
NOTHROW(FCALL npagedir_sync)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                             PAGEDIR_PAGEALIGNED size_t num_bytes);
#endif
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_SYNC */

/* Check if the given page is mapped.
 * NOTE: The given `addr' */
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_ISMAPPED
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(FCALL npagedir_ismapped)(VIRT void *addr);
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(FCALL npagedir_iswritable)(VIRT void *addr);
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(FCALL npagedir_isuseraccessible)(VIRT void *addr);
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(FCALL npagedir_isuserwritable)(VIRT void *addr);
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_ISMAPPED */

#ifdef CONFIG_HAVE_PAGEDIR_CHANGED
#ifndef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_HASCHANGED
/* TODO: Figure out a better design for these functions
 *       The current system is written under the assumption that 4MiB pages don't exist... */
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(FCALL npagedir_haschanged)(VIRT void *addr);
FUNDEF NOBLOCK void NOTHROW(FCALL npagedir_unsetchanged)(VIRT void *addr);
#endif /* !CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_HASCHANGED */
#endif /* CONFIG_HAVE_PAGEDIR_CHANGED */


/* Same as the functions above, but operate on the specified
 * page directory, rather than the one currently being used.
 * NOTE: The caller is responsible for synchronization. */
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(KCALL npagedir_prepare_mapone_p)(PAGEDIR_P_SELFTYPE self, PAGEDIR_PAGEALIGNED VIRT void *addr);
FUNDEF NOBLOCK void NOTHROW(KCALL npagedir_unprepare_mapone_p)(PAGEDIR_P_SELFTYPE self, PAGEDIR_PAGEALIGNED VIRT void *addr);
FUNDEF NOBLOCK void NOTHROW(KCALL npagedir_maphintone_p)(PAGEDIR_P_SELFTYPE self, PAGEDIR_PAGEALIGNED VIRT void *addr, VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint);
FUNDEF NOBLOCK void NOTHROW(KCALL npagedir_mapone_p)(PAGEDIR_P_SELFTYPE self, PAGEDIR_PAGEALIGNED VIRT void *addr, PAGEDIR_PAGEALIGNED PHYS vm_phys_t phys, u16 perm);
FUNDEF NOBLOCK void NOTHROW(KCALL npagedir_unmapone_p)(PAGEDIR_P_SELFTYPE self, PAGEDIR_PAGEALIGNED VIRT void *addr);
#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
FUNDEF NOBLOCK void NOTHROW(KCALL npagedir_unwriteone_p)(PAGEDIR_P_SELFTYPE self, PAGEDIR_PAGEALIGNED VIRT void *addr);
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */
FUNDEF NOBLOCK __BOOL NOTHROW(KCALL npagedir_ismapped_p)(PAGEDIR_P_SELFTYPE self, VIRT void *addr);
FUNDEF NOBLOCK __BOOL NOTHROW(KCALL npagedir_iswritable_p)(PAGEDIR_P_SELFTYPE self, VIRT void *addr);
FUNDEF NOBLOCK __BOOL NOTHROW(KCALL npagedir_isuseraccessible_p)(PAGEDIR_P_SELFTYPE self, VIRT void *addr);
FUNDEF NOBLOCK __BOOL NOTHROW(KCALL npagedir_isuserwritable_p)(PAGEDIR_P_SELFTYPE self, VIRT void *addr);
#ifdef CONFIG_HAVE_PAGEDIR_CHANGED
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(KCALL npagedir_haschanged_p)(PAGEDIR_P_SELFTYPE self, VIRT void *addr);
FUNDEF NOBLOCK void NOTHROW(KCALL npagedir_unsetchanged_p)(PAGEDIR_P_SELFTYPE self, VIRT void *addr);
#endif /* CONFIG_HAVE_PAGEDIR_CHANGED */
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK WUNUSED __BOOL
NOTHROW(KCALL __os_npagedir_prepare_map_p)(PAGEDIR_P_SELFTYPE self,
                                           PAGEDIR_PAGEALIGNED VIRT void *addr,
                                           PAGEDIR_PAGEALIGNED size_t num_bytes)
		ASMNAME("npagedir_prepare_map_p");
FUNDEF NOBLOCK WUNUSED __BOOL
NOTHROW(KCALL __os_npagedir_prepare_map_keep_p)(PAGEDIR_P_SELFTYPE self,
                                                PAGEDIR_PAGEALIGNED VIRT void *addr,
                                                PAGEDIR_PAGEALIGNED size_t num_bytes)
		ASMNAME("npagedir_prepare_map_keep_p");
FUNDEF NOBLOCK void
NOTHROW(KCALL __os_npagedir_unprepare_map_p)(PAGEDIR_P_SELFTYPE self,
                                             PAGEDIR_PAGEALIGNED VIRT void *addr,
                                             PAGEDIR_PAGEALIGNED size_t num_bytes)
		ASMNAME("npagedir_unprepare_map_p");
FUNDEF NOBLOCK void
NOTHROW(KCALL __os_npagedir_maphint_p)(PAGEDIR_P_SELFTYPE self,
                                       PAGEDIR_PAGEALIGNED VIRT void *addr,
                                       PAGEDIR_PAGEALIGNED size_t num_bytes,
                                       VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint)
		ASMNAME("npagedir_maphint_p");
FUNDEF NOBLOCK void
NOTHROW(KCALL __os_npagedir_map_p)(PAGEDIR_P_SELFTYPE self,
                                   PAGEDIR_PAGEALIGNED VIRT void *addr,
                                   PAGEDIR_PAGEALIGNED size_t num_bytes,
                                   PAGEDIR_PAGEALIGNED PHYS vm_phys_t phys,
                                   u16 perm)
		ASMNAME("npagedir_map_p");
FUNDEF NOBLOCK void
NOTHROW(KCALL __os_npagedir_unmap_p)(PAGEDIR_P_SELFTYPE self,
                                     PAGEDIR_PAGEALIGNED VIRT void *addr,
                                     PAGEDIR_PAGEALIGNED size_t num_bytes)
		ASMNAME("npagedir_unmap_p");
#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
FUNDEF NOBLOCK void
NOTHROW(KCALL __os_npagedir_unwrite_p)(PAGEDIR_P_SELFTYPE self,
                                       PAGEDIR_PAGEALIGNED VIRT void *addr,
                                       PAGEDIR_PAGEALIGNED size_t num_bytes)
		ASMNAME("npagedir_unwrite_p");
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */
FORCELOCAL NOBLOCK WUNUSED __BOOL
NOTHROW(KCALL npagedir_prepare_map_p)(PAGEDIR_P_SELFTYPE self,
                                      PAGEDIR_PAGEALIGNED VIRT void *addr,
                                      PAGEDIR_PAGEALIGNED size_t num_bytes) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return true;
		if (num_bytes <= PAGESIZE)
			return npagedir_prepare_mapone_p(self, addr);
	}
	return __os_npagedir_prepare_map_p(self, addr, num_bytes);
}
FORCELOCAL NOBLOCK WUNUSED __BOOL
NOTHROW(KCALL npagedir_prepare_map_keep_p)(PAGEDIR_P_SELFTYPE self,
                                           PAGEDIR_PAGEALIGNED VIRT void *addr,
                                           PAGEDIR_PAGEALIGNED size_t num_bytes) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return true;
		if (num_bytes <= PAGESIZE)
			return npagedir_prepare_mapone_p(self, addr);
	}
	return __os_npagedir_prepare_map_keep_p(self, addr, num_bytes);
}
FORCELOCAL NOBLOCK void
NOTHROW(KCALL npagedir_unprepare_map_p)(PAGEDIR_P_SELFTYPE self,
                                        PAGEDIR_PAGEALIGNED VIRT void *addr,
                                        PAGEDIR_PAGEALIGNED size_t num_bytes) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			npagedir_unprepare_mapone_p(self, addr);
			return;
		}
	}
	__os_npagedir_unprepare_map_p(self, addr, num_bytes);
}
FORCELOCAL NOBLOCK void
NOTHROW(KCALL npagedir_maphint_p)(PAGEDIR_P_SELFTYPE self,
                                  PAGEDIR_PAGEALIGNED VIRT void *addr,
                                  PAGEDIR_PAGEALIGNED size_t num_bytes,
                                  VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			npagedir_maphintone_p(self, addr, hint);
			return;
		}
	}
	__os_npagedir_maphint_p(self, addr, num_bytes, hint);
}
FORCELOCAL NOBLOCK void
NOTHROW(KCALL npagedir_map_p)(PAGEDIR_P_SELFTYPE self,
                              PAGEDIR_PAGEALIGNED VIRT void *addr,
                              PAGEDIR_PAGEALIGNED size_t num_bytes,
                              PAGEDIR_PAGEALIGNED PHYS vm_phys_t phys,
                              u16 perm) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			npagedir_mapone_p(self, addr, phys, perm);
			return;
		}
	}
	__os_npagedir_map_p(self, addr, num_bytes, phys, perm);
}
FORCELOCAL NOBLOCK void
NOTHROW(KCALL npagedir_unmap_p)(PAGEDIR_P_SELFTYPE self,
                                PAGEDIR_PAGEALIGNED VIRT void *addr,
                                PAGEDIR_PAGEALIGNED size_t num_bytes) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			npagedir_unmapone_p(self, addr);
			return;
		}
	}
	__os_npagedir_unmap_p(self, addr, num_bytes);
}
#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
FORCELOCAL NOBLOCK void
NOTHROW(KCALL npagedir_unwrite_p)(PAGEDIR_P_SELFTYPE self,
                                  PAGEDIR_PAGEALIGNED VIRT void *addr,
                                  PAGEDIR_PAGEALIGNED size_t num_bytes) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			npagedir_unwriteone_p(self, addr);
			return;
		}
	}
	__os_npagedir_unwrite_p(self, addr, num_bytes);
}
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */
#else /* !__OMIT_PAGING_CONSTANT_P_WRAPPERS */
FUNDEF NOBLOCK WUNUSED __BOOL
NOTHROW(KCALL npagedir_prepare_map_p)(PAGEDIR_P_SELFTYPE self,
                                      PAGEDIR_PAGEALIGNED VIRT void *addr,
                                      PAGEDIR_PAGEALIGNED size_t num_bytes);
FUNDEF NOBLOCK WUNUSED __BOOL
NOTHROW(KCALL npagedir_prepare_map_keep_p)(PAGEDIR_P_SELFTYPE self,
                                           PAGEDIR_PAGEALIGNED VIRT void *addr,
                                           PAGEDIR_PAGEALIGNED size_t num_bytes);
FUNDEF NOBLOCK void
NOTHROW(KCALL npagedir_unprepare_map_p)(PAGEDIR_P_SELFTYPE self,
                                        PAGEDIR_PAGEALIGNED VIRT void *addr,
                                        PAGEDIR_PAGEALIGNED size_t num_bytes);
FUNDEF NOBLOCK void
NOTHROW(KCALL npagedir_maphint_p)(PAGEDIR_P_SELFTYPE self,
                                  PAGEDIR_PAGEALIGNED VIRT void *addr,
                                  PAGEDIR_PAGEALIGNED size_t num_bytes,
                                  VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint);
FUNDEF NOBLOCK void
NOTHROW(KCALL npagedir_map_p)(PAGEDIR_P_SELFTYPE self,
                              PAGEDIR_PAGEALIGNED VIRT void *addr,
                              PAGEDIR_PAGEALIGNED size_t num_bytes,
                              PAGEDIR_PAGEALIGNED PHYS vm_phys_t phys,
                              u16 perm);
FUNDEF NOBLOCK void
NOTHROW(KCALL npagedir_unmap_p)(PAGEDIR_P_SELFTYPE self,
                                PAGEDIR_PAGEALIGNED VIRT void *addr,
                                PAGEDIR_PAGEALIGNED size_t num_bytes);
#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
FUNDEF NOBLOCK void
NOTHROW(KCALL npagedir_unwrite_p)(PAGEDIR_P_SELFTYPE self,
                                  PAGEDIR_PAGEALIGNED VIRT void *addr,
                                  PAGEDIR_PAGEALIGNED size_t num_bytes);
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */
#endif /* __OMIT_PAGING_CONSTANT_P_WRAPPERS */


/* Old-style paging compatibility functions.
 * NOTE: These don't have to be portable, as they will be removed eventually, so
 *       don't worry about the fact that they assume a pagesize of 4096 bytes! */
#if 1
#ifndef __PAGEDIR_COMPAT_VIRTPAGE2ADDR
#define __PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page)     (void *)((uintptr_t)(virt_page) * 4096)
#define __PAGEDIR_COMPAT_PHYSPAGE2PHYS(phys_page)     (vm_phys_t)((uintptr_t)(phys_page) * 4096)
#define __PAGEDIR_COMPAT_NUMPAGES2NUMBYTES(num_pages) ((size_t)(num_pages) * 4096)
#endif /* !__PAGEDIR_COMPAT_VIRTPAGE2ADDR */
#define pagedir_prepare_mapone(virt_page)                          npagedir_prepare_mapone(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page))
#define pagedir_unprepare_mapone(virt_page)                        npagedir_unprepare_mapone(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page))
#define pagedir_prepare_map(virt_page, num_pages)                  npagedir_prepare_map(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page), __PAGEDIR_COMPAT_NUMPAGES2NUMBYTES(num_pages))
#define pagedir_prepare_map_keep(virt_page, num_pages)             npagedir_prepare_map_keep(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page), __PAGEDIR_COMPAT_NUMPAGES2NUMBYTES(num_pages))
#define pagedir_unprepare_map(virt_page, num_pages)                npagedir_unprepare_map(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page), __PAGEDIR_COMPAT_NUMPAGES2NUMBYTES(num_pages))
#define pagedir_maphintone(virt_page, hint)                        npagedir_maphintone(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page), hint)
#define pagedir_maphint(virt_page, num_pages, hint)                npagedir_maphint(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page), __PAGEDIR_COMPAT_NUMPAGES2NUMBYTES(num_pages), hint)
#define pagedir_gethint(virt_page)                                 npagedir_gethint(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page))
#define pagedir_mapone(virt_page, phys_page, perm)                 npagedir_mapone(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page), __PAGEDIR_COMPAT_PHYSPAGE2PHYS(phys_page), perm)
#define pagedir_map(virt_page, num_pages, phys_page, perm)         npagedir_map(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page), __PAGEDIR_COMPAT_NUMPAGES2NUMBYTES(num_pages), __PAGEDIR_COMPAT_PHYSPAGE2PHYS(phys_page), perm)
#define pagedir_push_mapone(virt_page, phys_page, perm)            npagedir_push_mapone(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page), __PAGEDIR_COMPAT_PHYSPAGE2PHYS(phys_page), perm)
#define pagedir_pop_mapone(virt_page, backup)                      npagedir_pop_mapone(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page), backup)
#define pagedir_unmapone(virt_page)                                npagedir_unmapone(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page))
#define pagedir_unmap(virt_page, num_pages)                        npagedir_unmap(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page), __PAGEDIR_COMPAT_NUMPAGES2NUMBYTES(num_pages))
#define pagedir_syncone(virt_page)                                 npagedir_syncone(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page))
#define pagedir_sync(virt_page, num_pages)                         npagedir_sync(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page), __PAGEDIR_COMPAT_NUMPAGES2NUMBYTES(num_pages))
#define pagedir_ismapped(vpage)                                    npagedir_ismapped(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(vpage))
#define pagedir_iswritable(vpage)                                  npagedir_iswritable(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(vpage))
#define pagedir_isuseraccessible(vpage)                            npagedir_isuseraccessible(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(vpage))
#define pagedir_isuserwritable(vpage)                              npagedir_isuserwritable(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(vpage))
#define pagedir_prepare_mapone_p(self, virt_page)                  npagedir_prepare_mapone_p(self, __PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page))
#define pagedir_unprepare_mapone_p(self, virt_page)                npagedir_unprepare_mapone_p(self, __PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page))
#define pagedir_maphintone_p(self, virt_page, hint)                npagedir_maphintone_p(self, __PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page), hint)
#define pagedir_mapone_p(self, virt_page, phys_page, perm)         npagedir_mapone_p(self, __PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page), __PAGEDIR_COMPAT_PHYSPAGE2PHYS(phys_page), perm)
#define pagedir_unmapone_p(self, virt_page)                        npagedir_unmapone_p(self, __PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page))
#define pagedir_ismapped_p(self, vpage)                            npagedir_ismapped_p(self, __PAGEDIR_COMPAT_VIRTPAGE2ADDR(vpage))
#define pagedir_iswritable_p(self, vpage)                          npagedir_iswritable_p(self, __PAGEDIR_COMPAT_VIRTPAGE2ADDR(vpage))
#define pagedir_isuseraccessible_p(self, vpage)                    npagedir_isuseraccessible_p(self, __PAGEDIR_COMPAT_VIRTPAGE2ADDR(vpage))
#define pagedir_isuserwritable_p(self, vpage)                      npagedir_isuserwritable_p(self, __PAGEDIR_COMPAT_VIRTPAGE2ADDR(vpage))
#define pagedir_prepare_map_p(self, virt_page, num_pages)          npagedir_prepare_map_p(self, __PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page), __PAGEDIR_COMPAT_NUMPAGES2NUMBYTES(num_pages))
#define pagedir_prepare_map_keep_p(self, virt_page, num_pages)     npagedir_prepare_map_keep_p(self, __PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page), __PAGEDIR_COMPAT_NUMPAGES2NUMBYTES(num_pages))
#define pagedir_unprepare_map_p(self, virt_page, num_pages)        npagedir_unprepare_map_p(self, __PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page), __PAGEDIR_COMPAT_NUMPAGES2NUMBYTES(num_pages))
#define pagedir_maphint_p(self, virt_page, num_pages, hint)        npagedir_maphint_p(self, __PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page), __PAGEDIR_COMPAT_NUMPAGES2NUMBYTES(num_pages), hint)
#define pagedir_map_p(self, virt_page, num_pages, phys_page, perm) npagedir_map_p(self, __PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page), __PAGEDIR_COMPAT_NUMPAGES2NUMBYTES(num_pages), __PAGEDIR_COMPAT_PHYSPAGE2PHYS(phys_page), perm)
#define pagedir_unmap_p(self, virt_page, num_pages)                npagedir_unmap_p(self, __PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page), __PAGEDIR_COMPAT_NUMPAGES2NUMBYTES(num_pages))
#ifdef CONFIG_HAVE_PAGEDIR_CHANGED
#define pagedir_haschanged(vpage)           npagedir_haschanged(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(vpage))
#define pagedir_unsetchanged(vpage)         npagedir_unsetchanged(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(vpage))
#define pagedir_haschanged_p(self, vpage)   npagedir_haschanged_p(self, __PAGEDIR_COMPAT_VIRTPAGE2ADDR(vpage))
#define pagedir_unsetchanged_p(self, vpage) npagedir_unsetchanged_p(self, __PAGEDIR_COMPAT_VIRTPAGE2ADDR(vpage))
#endif /* CONFIG_HAVE_PAGEDIR_CHANGED */
#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
#define pagedir_unwriteone(virt_page)                 npagedir_unwriteone(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page))
#define pagedir_unwrite(virt_page, num_pages)         npagedir_unwrite(__PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page), __PAGEDIR_COMPAT_NUMPAGES2NUMBYTES(num_pages))
#define pagedir_unwriteone_p(self, virt_page)         npagedir_unwriteone_p(self, __PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page))
#define pagedir_unwrite_p(self, virt_page, num_pages) npagedir_unwrite_p(self, __PAGEDIR_COMPAT_VIRTPAGE2ADDR(virt_page), __PAGEDIR_COMPAT_NUMPAGES2NUMBYTES(num_pages))
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */
#endif


#else /* CONFIG_USE_NEW_PAGING */


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
#else /* !__OMIT_PAGING_CONSTANT_P_WRAPPERS */
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(FCALL pagedir_prepare_map)(VIRT vm_vpage_t virt_page, size_t num_pages);
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(FCALL pagedir_prepare_map_keep)(VIRT vm_vpage_t virt_page, size_t num_pages);
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_unprepare_map)(VIRT vm_vpage_t virt_page, size_t num_pages);
#endif /* __OMIT_PAGING_CONSTANT_P_WRAPPERS */
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
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_maphintone)(VIRT vm_vpage_t virt_page, VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint);
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK void NOTHROW(FCALL __os_pagedir_maphint)(VIRT vm_vpage_t virt_page, size_t num_pages, VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) ASMNAME("pagedir_maphint");
FORCELOCAL NOBLOCK void
NOTHROW(FCALL pagedir_maphint)(VIRT vm_vpage_t virt_page, size_t num_pages,
                                VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
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
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_maphint)(VIRT vm_vpage_t virt_page, size_t num_pages, VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint);
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
 * These functions are mainly intended for use with `this_trampoline_page', allowing
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


/* Same as the functions above, but operate on the specified
 * page directory, rather than the one currently being used.
 * NOTE: The caller is responsible for synchronization. */
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(KCALL pagedir_prepare_mapone_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unprepare_mapone_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_maphintone_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_mapone_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, PHYS vm_ppage_t phys_page, u16 perm);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unmapone_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page);
#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unwriteone_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page);
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */
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
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(KCALL __os_pagedir_prepare_map_keep_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages) ASMNAME("pagedir_prepare_map_keep_p");
FUNDEF NOBLOCK void NOTHROW(KCALL __os_pagedir_unprepare_map_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages) ASMNAME("pagedir_unprepare_map_p");
FUNDEF NOBLOCK void NOTHROW(KCALL __os_pagedir_maphint_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages, VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) ASMNAME("pagedir_maphint_p");
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
FORCELOCAL NOBLOCK WUNUSED __BOOL
NOTHROW(KCALL pagedir_prepare_map_keep_p)(PAGEDIR_P_SELFTYPE self,
                                          VIRT vm_vpage_t virt_page, size_t num_pages) {
	if (__builtin_constant_p(num_pages)) {
		if (num_pages == 1)
			return pagedir_prepare_mapone_p(self, virt_page);
		if (num_pages == 0)
			return true;
	}
	return __os_pagedir_prepare_map_keep_p(self, virt_page, num_pages);
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
                                 VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
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
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(KCALL pagedir_prepare_map_keep_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unprepare_map_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_maphint_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages, VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_map_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages, PHYS vm_ppage_t phys_page, u16 perm);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unmap_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages);
#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unwrite_p)(PAGEDIR_P_SELFTYPE self, VIRT vm_vpage_t virt_page, size_t num_pages);
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */
#endif

#endif /* !CONFIG_USE_NEW_PAGING */



#ifndef CONFIG_USE_NEW_PAGING
/* Forward-compatibility for the new paging system.
 * NOTE: These don't have to be portable, as they will be removed eventually, so
 *       don't worry about the fact that they assume a pagesize of 4096 bytes! */
#ifndef __PAGEDIR_FORWARD_ADDR2VIRTPAGE
#define __PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr)          (vm_vpage_t)((uintptr_t)(addr) / 4096)
#define __PAGEDIR_FORWARD_PHYS2PHYSPAGE(phys)          (vm_ppage_t)((phys) / 4096)
#define __PAGEDIR_FORWARD_NUMBYTES2NUMPAGES(num_bytes) ((size_t)(num_bytes) / 4096)
#endif /* !__PAGEDIR_FORWARD_ADDR2VIRTPAGE */
#define npagedir_prepare_mapone(addr)                      pagedir_prepare_mapone(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr))
#define npagedir_prepare_map(addr, num_bytes)              pagedir_prepare_map(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr), __PAGEDIR_FORWARD_NUMBYTES2NUMPAGES(num_bytes))
#define npagedir_prepare_map_keep(addr, num_bytes)         pagedir_prepare_map_keep(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr), __PAGEDIR_FORWARD_NUMBYTES2NUMPAGES(num_bytes))
#define npagedir_unprepare_mapone(addr)                    pagedir_unprepare_mapone(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr))
#define npagedir_unprepare_map(addr, num_bytes)            pagedir_unprepare_map(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr), __PAGEDIR_FORWARD_NUMBYTES2NUMPAGES(num_bytes))
#define npagedir_maphintone(addr, hint)                    pagedir_maphintone(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr), hint)
#define npagedir_maphint(addr, num_bytes, hint)            pagedir_maphint(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr), __PAGEDIR_FORWARD_NUMBYTES2NUMPAGES(num_bytes), hint)
#define npagedir_gethint(addr)                             pagedir_gethint(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr))
#define npagedir_mapone(addr, phys, perm)                  pagedir_mapone(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr), __PAGEDIR_FORWARD_PHYS2PHYSPAGE(phys), perm)
#define npagedir_map(addr, num_bytes, phys, perm)          pagedir_map(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr), __PAGEDIR_FORWARD_NUMBYTES2NUMPAGES(num_bytes), __PAGEDIR_FORWARD_PHYS2PHYSPAGE(phys), perm)
#define npagedir_push_mapone(addr, phys, perm)             pagedir_push_mapone(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr), __PAGEDIR_FORWARD_PHYS2PHYSPAGE(phys), perm)
#define npagedir_pop_mapone(addr, backup)                  pagedir_pop_mapone(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr), backup)
#define npagedir_unmapone(addr)                            pagedir_unmapone(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr))
#define npagedir_unmap(addr, num_bytes)                    pagedir_unmap(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr), __PAGEDIR_FORWARD_NUMBYTES2NUMPAGES(num_bytes))
#define npagedir_syncone(addr)                             pagedir_syncone(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr))
#define npagedir_sync(addr, num_bytes)                     pagedir_sync(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr), __PAGEDIR_FORWARD_NUMBYTES2NUMPAGES(num_bytes))
#define npagedir_ismapped(addr)                            pagedir_ismapped(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr))
#define npagedir_iswritable(addr)                          pagedir_iswritable(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr))
#define npagedir_isuseraccessible(addr)                    pagedir_isuseraccessible(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr))
#define npagedir_isuserwritable(addr)                      pagedir_isuserwritable(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr))
#define npagedir_prepare_map_p(self, addr, num_bytes)      pagedir_prepare_map_p(self, __PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr), __PAGEDIR_FORWARD_NUMBYTES2NUMPAGES(num_bytes))
#define npagedir_prepare_map_keep_p(self, addr, num_bytes) pagedir_prepare_map_keep_p(self, __PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr), __PAGEDIR_FORWARD_NUMBYTES2NUMPAGES(num_bytes))
#define npagedir_unprepare_mapone_p(self, addr)            pagedir_unprepare_mapone_p(self, __PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr))
#define npagedir_unprepare_map_p(self, addr, num_bytes)    pagedir_unprepare_map_p(self, __PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr), __PAGEDIR_FORWARD_NUMBYTES2NUMPAGES(num_bytes))
#define npagedir_maphintone_p(self, addr, hint)            pagedir_maphintone_p(self, __PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr), hint)
#define npagedir_maphint_p(self, addr, num_bytes, hint)    pagedir_maphint_p(self, __PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr), __PAGEDIR_FORWARD_NUMBYTES2NUMPAGES(num_bytes), hint)
#define npagedir_mapone_p(self, addr, phys, perm)          pagedir_mapone_p(self, __PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr), __PAGEDIR_FORWARD_PHYS2PHYSPAGE(phys), perm)
#define npagedir_map_p(self, addr, num_bytes, phys, perm)  pagedir_map_p(self, __PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr), __PAGEDIR_FORWARD_NUMBYTES2NUMPAGES(num_bytes), __PAGEDIR_FORWARD_PHYS2PHYSPAGE(phys), perm)
#define npagedir_unmapone_p(self, addr)                    pagedir_unmapone_p(self, __PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr))
#define npagedir_unmap_p(self, addr, num_bytes)            pagedir_unmap_p(self, __PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr), __PAGEDIR_FORWARD_NUMBYTES2NUMPAGES(num_bytes))
#define npagedir_ismapped_p(self, addr)                    pagedir_ismapped_p(self, __PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr))
#define npagedir_iswritable_p(self, addr)                  pagedir_iswritable_p(self, __PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr))
#define npagedir_isuseraccessible_p(self, addr)            pagedir_isuseraccessible_p(self, __PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr))
#define npagedir_isuserwritable_p(self, addr)              pagedir_isuserwritable_p(self, __PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr))
#ifdef CONFIG_HAVE_PAGEDIR_CHANGED
#define npagedir_haschanged(addr)                          pagedir_haschanged(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr))
#define npagedir_unsetchanged(addr)                        pagedir_unsetchanged(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr))
#define npagedir_haschanged_p(self, addr)                  pagedir_haschanged_p(self, __PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr))
#define npagedir_unsetchanged_p(self, addr)                pagedir_unsetchanged_p(self, __PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr))
#endif /* CONFIG_HAVE_PAGEDIR_CHANGED */
#ifdef CONFIG_HAVE_PAGEDIR_UNWRITE
#define npagedir_unwriteone(addr)                          pagedir_unwriteone(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr))
#define npagedir_unwrite(addr, num_bytes)                  pagedir_unwrite(__PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr), __PAGEDIR_FORWARD_NUMBYTES2NUMPAGES(num_bytes))
#define npagedir_unwriteone_p(self, addr)                  pagedir_unwriteone_p(self, __PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr))
#define npagedir_unwrite_p(self, addr, num_bytes)          pagedir_unwrite_p(self, __PAGEDIR_FORWARD_ADDR2VIRTPAGE(addr), __PAGEDIR_FORWARD_NUMBYTES2NUMPAGES(num_bytes))
#endif /* CONFIG_HAVE_PAGEDIR_UNWRITE */
#endif /* !CONFIG_USE_NEW_PAGING */




#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_PAGING_H */
