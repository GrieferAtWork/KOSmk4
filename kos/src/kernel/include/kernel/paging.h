/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_PAGING_H
#define GUARD_KERNEL_INCLUDE_KERNEL_PAGING_H 1

#include <kernel/compiler.h>

#include <kernel/arch/paging.h>
#include <kernel/types.h>

#include <hybrid/sched/__preemption.h>
#include <hybrid/typecore.h>

#include <asm/pagesize.h>
#include <kos/kernel/memory.h>
#include <kos/kernel/paging.h>

#ifndef PAGESIZE
#define PAGESIZE __ARCH_PAGESIZE
#elif PAGESIZE != __ARCH_PAGESIZE
#error "Miss-configured: `PAGESIZE != __ARCH_PAGESIZE'"
#endif /* ... */

#ifndef PAGESHIFT
#define PAGESHIFT __ARCH_PAGESHIFT
#elif PAGESHIFT != __ARCH_PAGESHIFT
#error "Miss-configured: `PAGESHIFT != __ARCH_PAGESHIFT'"
#endif /* ... */

#ifndef PAGEMASK
#define PAGEMASK __ARCH_PAGEMASK
#elif PAGEMASK != __ARCH_PAGEMASK
#error "Miss-configured: `PAGEMASK != __ARCH_PAGEMASK'"
#endif /* ... */


/* Check if a given `addr' or [startaddr, endaddr)
 * is  consider  apart of  user-  or kernel-space.
 *
 * The *_PARTIAL functions check if the range has any overlapping parts
 * with the named address space, while the non-_PARTIAL functions check
 * that the entire range is apart of the named address space.
 *
 * Note that  the range-checking  functions are  allowed to  assume  that
 * `endaddr >= startaddr'.  In  the  case  where  `endaddr == startaddr',
 * the range-checking functions behave identical to `ADDR_IS(KERN|USER)',
 * or in other words: will use `endaddr = startaddr+1' */
#ifdef KERNELSPACE_HIGHMEM
#define ADDR_ISKERN(addr)                            (__CCAST(__UINTPTR_TYPE__)(addr) >= KERNELSPACE_BASE)
#define ADDR_ISUSER(addr)                            (__CCAST(__UINTPTR_TYPE__)(addr) < KERNELSPACE_BASE)
#define ADDRRANGE_ISKERN(startaddr, endaddr)         (__CCAST(__UINTPTR_TYPE__)(startaddr) >= KERNELSPACE_BASE)
#define ADDRRANGE_ISUSER(startaddr, endaddr)         (__CCAST(__UINTPTR_TYPE__)(endaddr) <= KERNELSPACE_BASE)
#define ADDRRANGE_ISKERN_PARTIAL(startaddr, endaddr) (__CCAST(__UINTPTR_TYPE__)(endaddr) > KERNELSPACE_BASE)
#define ADDRRANGE_ISUSER_PARTIAL(startaddr, endaddr) (__CCAST(__UINTPTR_TYPE__)(startaddr) < KERNELSPACE_BASE)
#elif defined(KERNELSPACE_LOWMEM)
#define ADDR_ISKERN(addr)                            (__CCAST(__UINTPTR_TYPE__)(addr) < KERNELSPACE_END)
#define ADDR_ISUSER(addr)                            (__CCAST(__UINTPTR_TYPE__)(addr) >= KERNELSPACE_END)
#define ADDRRANGE_ISKERN(startaddr, endaddr)         (__CCAST(__UINTPTR_TYPE__)(endaddr) <= KERNELSPACE_END)
#define ADDRRANGE_ISUSER(startaddr, endaddr)         (__CCAST(__UINTPTR_TYPE__)(startaddr) >= KERNELSPACE_END)
#define ADDRRANGE_ISKERN_PARTIAL(startaddr, endaddr) (__CCAST(__UINTPTR_TYPE__)(startaddr) < KERNELSPACE_END)
#define ADDRRANGE_ISUSER_PARTIAL(startaddr, endaddr) (__CCAST(__UINTPTR_TYPE__)(endaddr) > KERNELSPACE_END)
#else /* KERNELSPACE_...MEM */
#define ADDR_ISKERN(addr)                            (__CCAST(__UINTPTR_TYPE__)(addr) >= KERNELSPACE_BASE && __CCAST(__UINTPTR_TYPE__)(addr) < KERNELSPACE_END)
#define ADDR_ISUSER(addr)                            (__CCAST(__UINTPTR_TYPE__)(addr) < KERNELSPACE_BASE && __CCAST(__UINTPTR_TYPE__)(addr) >= KERNELSPACE_END)
#define ADDRRANGE_ISKERN(startaddr, endaddr)         (__CCAST(__UINTPTR_TYPE__)(startaddr) >= KERNELSPACE_BASE && __CCAST(__UINTPTR_TYPE__)(endaddr) <= KERNELSPACE_END)
#define ADDRRANGE_ISUSER(startaddr, endaddr)         (__CCAST(__UINTPTR_TYPE__)(startaddr) >= KERNELSPACE_END || __CCAST(__UINTPTR_TYPE__)(endaddr) <= KERNELSPACE_BASE)
#define ADDRRANGE_ISKERN_PARTIAL(startaddr, endaddr) (__CCAST(__UINTPTR_TYPE__)(startaddr) < KERNELSPACE_END || __CCAST(__UINTPTR_TYPE__)(endaddr) > KERNELSPACE_BASE)
#define ADDRRANGE_ISUSER_PARTIAL(startaddr, endaddr) (__CCAST(__UINTPTR_TYPE__)(startaddr) < KERNELSPACE_BASE && __CCAST(__UINTPTR_TYPE__)(endaddr) > KERNELSPACE_END)
#endif /* !KERNELSPACE_...MEM */



DECL_BEGIN

#ifndef PAGEDIR_ALIGN
#define PAGEDIR_ALIGN PAGESIZE
#endif /* !PAGEDIR_ALIGN */
#ifndef PAGEDIR_SIZE
#define PAGEDIR_SIZE PAGESIZE
#endif /* !PAGEDIR_SIZE */

#ifndef __pagedir_pushval_t_defined
#define __pagedir_pushval_t_defined
#define PAGEDIR_PUSHVAL_INVALID (__CCAST(pagedir_pushval_t)-1)
#define SIZEOF_PAGEDIR_PUSHVAL  __SIZEOF_POINTER__
#ifdef __CC__
typedef uintptr_t pagedir_pushval_t;
#endif /* __CC__ */
#endif /* !__pagedir_pushval_t_defined */

/* Helper macros to generate the most efficient code to  specifically
 * prepare/unprepare memory regions within the kernel page directory.
 *
 * But  note that you can always just use the normal prepare/unprepare
 * functions even for kernel addresses, only that these right here may
 * be more efficient in certain configurations. */
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
#define pagedir_kernelprepareone(addr)           pagedir_prepareone(addr)
#define pagedir_kernelunprepareone(addr)         pagedir_unprepareone(addr)
#define pagedir_kernelprepare(addr, num_bytes)   pagedir_prepare(addr, num_bytes)
#define pagedir_kernelunprepare(addr, num_bytes) pagedir_unprepare(addr, num_bytes)
#else /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
#define pagedir_kernelprepareone(addr)           1
#define pagedir_kernelunprepareone(addr)         (void)0
#define pagedir_kernelprepare(addr, num_bytes)   1
#define pagedir_kernelunprepare(addr, num_bytes) (void)0
#endif /* !ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */



#ifndef __pagedir_phys_t_defined
#define __pagedir_phys_t_defined
#ifdef ARCH_PAGEDIR_GETSET_USES_POINTER
#define __SIZEOF_PAGEDIR_PHYS_T__ __SIZEOF_POINTER__
#ifdef __CC__
typedef pagedir_t *pagedir_phys_t;
#endif /* __CC__ */
#else /* ARCH_PAGEDIR_GETSET_USES_POINTER */
#define __SIZEOF_PAGEDIR_PHYS_T__ __SIZEOF_PHYSADDR_T__
#ifdef __CC__
typedef physaddr_t pagedir_phys_t;
#endif /* __CC__ */
#endif /* !ARCH_PAGEDIR_GETSET_USES_POINTER */
#endif /* !__pagedir_phys_t_defined */


#ifdef __CC__
/* The physical and virtual address bindings of the kernel's page directory.
 * This  is the initial page directory active when KOS boots, as well as the
 * the directory later used for threads running in kernel-space only. */
#ifndef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_KERNEL
DATDEF pagedir_t pagedir_kernel;
#ifdef ARCH_PAGEDIR_GETSET_USES_POINTER
DATDEF pagedir_t pagedir_kernel_phys[];
#elif __SIZEOF_PHYSADDR_T__ == __SIZEOF_POINTER__
DATDEF physaddr_t pagedir_kernel_phys_0[];
#define pagedir_kernel_phys ((pagedir_phys_t)(uintptr_t)pagedir_kernel_phys_0)
#elif __SIZEOF_PHYSADDR_T__ == 8 && __SIZEOF_POINTER__ == 4
DATDEF PHYS uintptr_t pagedir_kernel_phys_0[];
DATDEF PHYS uintptr_t pagedir_kernel_phys_1[];
#define pagedir_kernel_phys                             \
	((pagedir_phys_t)(uintptr_t)pagedir_kernel_phys_0 | \
	 (pagedir_phys_t)(uintptr_t)pagedir_kernel_phys_1 << 32)
#else /* ... */
#error "Unsupported configuration"
#endif /* !... */
#endif /* !ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_KERNEL */


/* Initialize the given page directory.
 * The caller is required to allocate the page directory controller itself, which
 * must  be aligned  and sized  according to  `PAGEDIR_ALIGN' and `PAGEDIR_SIZE'. */
#ifndef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_INIT
#ifdef ARCH_PAGEDIR_INIT_NEED_PHYS_SELF
#ifdef ARCH_PAGEDIR_INIT_IS_NOEXCEPT
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pagedir_init)(pagedir_t *__restrict self,
                            pagedir_phys_t phys_self);
#else /* ARCH_PAGEDIR_INIT_IS_NOEXCEPT */
FUNDEF NOBLOCK NONNULL((1)) void FCALL
pagedir_init(pagedir_t *__restrict self,
             pagedir_phys_t phys_self) THROWS(E_BADALLOC);
#endif /* !ARCH_PAGEDIR_INIT_IS_NOEXCEPT */
#define pagedir_init1(self)            pagedir_init(self, pagedir_translate(self))
#define pagedir_init2(self, phys_self) pagedir_init(self, phys_self)
#else /* ARCH_PAGEDIR_INIT_NEED_PHYS_SELF */
#ifdef ARCH_PAGEDIR_INIT_IS_NOEXCEPT
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pagedir_init)(pagedir_t *__restrict self);
#else /* ARCH_PAGEDIR_INIT_IS_NOEXCEPT */
FUNDEF NOBLOCK NONNULL((1)) void FCALL
pagedir_init(pagedir_t *__restrict self) THROWS(E_BADALLOC);
#endif /* !ARCH_PAGEDIR_INIT_IS_NOEXCEPT */
#define pagedir_init1(self)            pagedir_init(self)
#define pagedir_init2(self, phys_self) pagedir_init(self)
#endif /* !ARCH_PAGEDIR_INIT_NEED_PHYS_SELF */
#endif /* !ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_INIT */


/* Finalize a given page directory. */
#ifndef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_FINI
#ifdef ARCH_PAGEDIR_FINI_NEED_PHYS_SELF
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pagedir_fini)(pagedir_t *__restrict self,
                            pagedir_phys_t phys_self);
#define pagedir_fini1(self)            pagedir_fini(self, pagedir_translate(self))
#define pagedir_fini2(self, phys_self) pagedir_fini(self, phys_self)
#else /* ARCH_PAGEDIR_FINI_NEED_PHYS_SELF */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pagedir_fini)(pagedir_t *__restrict self);
#define pagedir_fini1(self)            pagedir_fini(self)
#define pagedir_fini2(self, phys_self) pagedir_fini(self)
#endif /* !ARCH_PAGEDIR_FINI_NEED_PHYS_SELF */
#endif /* !ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_FINI */
#endif /* __CC__ */


/* WARNING: If the host does not support some combination of permission
 *          bits,  more  permissions  than  specified  may  be granted.
 *          For example: On X86, write-permissions require read-permissions
 *                       to  be granted, and exec-permissions require read. */
#ifndef PAGEDIR_PROT_MASK
#define PAGEDIR_PROT_EXEC  0x0001 /* Permission bit: Allow execution within the mapping. */
#define PAGEDIR_PROT_WRITE 0x0002 /* Permission bit: Permit write-access to memory within mapping. */
#define PAGEDIR_PROT_READ  0x0004 /* Permission bit: Permit read-access to memory within mapping. */
#define PAGEDIR_PROT_MASK  0x0007 /* Mask of valid permission bits. */
#endif /* !PAGEDIR_PROT_MASK */

#ifdef __CC__
#ifndef __pagedir_prot_t_defined
#define __pagedir_prot_t_defined
typedef u16 pagedir_prot_t;
#endif /* !__pagedir_prot_t_defined */


#ifndef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_SYNCALL
/* Synchronize the entirety of the current page directory.
 * Note that this function may only sync all user-space mappings. If the
 * intent is to also sync all of kernel-space, `pagedir_syncall()'  must
 * be used instead. */
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_syncall_user)(void);
/* Same as `pagedir_syncall()', but also ensures that
 * all of kernel-space is synced. */
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_syncall)(void);
#endif /* !ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_SYNCALL */

#ifndef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_SYNCONE
/* Synchronize mappings within the given address range. */
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_syncone)(VIRT void *addr);
#endif /* !ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_SYNCONE */


/* Translate a virtual address into its physical counterpart. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED ATTR_ACCESS_NONE(1) physaddr_t
NOTHROW(FCALL pagedir_translate)(VIRT void const *addr);
FUNDEF NOBLOCK ATTR_PURE WUNUSED ATTR_ACCESS_NONE(2) physaddr_t
NOTHROW(KCALL pagedir_translate_p)(pagedir_phys_t self, VIRT void const *addr);


/* Low-level Get/Set the physical address of the currently active page directory. */
#ifndef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_GETSET
FUNDEF NOBLOCK ATTR_PURE WUNUSED pagedir_phys_t NOTHROW(KCALL pagedir_get)(void);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_set)(pagedir_phys_t value);
#endif /* !ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_GETSET */


/* Unmap the entirety of user-space.
 * NOTE: Unlike all other unmap() functions, this one guaranties that it
 *       can perform the task without  needing to allocate more  memory! */
#ifndef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_UNMAP_USERSPACE
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_unmap_userspace)(void);
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_unmap_userspace_nosync)(void);
#endif /* !ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_UNMAP_USERSPACE */

#ifndef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_UNMAP_USERSPACE_P
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unmap_userspace_p)(pagedir_phys_t self);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unmap_userspace_nosync_p)(pagedir_phys_t self);
#endif /* !ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_UNMAP_USERSPACE_P */


/* Temporarily switch to a different page directory `self'
 * @param: self: The page directory to switch to (of type `pagedir_phys_t') */
#ifdef __INTELLISENSE__
#define PAGEDIR_P_BEGINUSE(self)         do
#define PAGEDIR_P_ENDUSE(self)           __WHILE0
#define PAGEDIR_P_BEGINUSE_KEEP_PR(self) do
#define PAGEDIR_P_ENDUSE_KEEP_PR(self)   __WHILE0
#else /* __INTELLISENSE__ */
#define PAGEDIR_P_BEGINUSE(self)                              \
	do {                                                      \
		pagedir_phys_t _old_pdir;                             \
		__hybrid_preemption_flag_t _p_was;                    \
		__hybrid_preemption_pushoff(&_p_was);                 \
		assert(IS_ALIGNED((uintptr_t)(self), PAGEDIR_ALIGN)); \
		_old_pdir = pagedir_get();                            \
		if (_old_pdir != (self))                              \
			pagedir_set(self);                                \
		do
#define PAGEDIR_P_ENDUSE(self)            \
		__WHILE0;                         \
		if (_old_pdir != (self))          \
			pagedir_set(_old_pdir);       \
		__hybrid_preemption_pop(&_p_was); \
	}	__WHILE0
#define PAGEDIR_P_BEGINUSE_KEEP_PR(self)                      \
	do {                                                      \
		pagedir_phys_t _old_pdir;                             \
		assert(IS_ALIGNED((uintptr_t)(self), PAGEDIR_ALIGN)); \
		_old_pdir = pagedir_get();                            \
		if (_old_pdir != (self))                              \
			pagedir_set(self);                                \
		do
#define PAGEDIR_P_ENDUSE_KEEP_PR(self) \
		__WHILE0;                      \
		if (_old_pdir != (self))       \
			pagedir_set(_old_pdir);    \
	}	__WHILE0
#endif /* !__INTELLISENSE__ */




#ifndef PAGEDIR_PAGEALIGNED
#define PAGEDIR_PAGEALIGNED /* Annotation for variables that need to be aligned on page boundaries. */
#endif /* !PAGEDIR_PAGEALIGNED */


/* Prepare the page directory for a future map() operation.
 * The full cycle of a single mapping then looks like this:
 * >> pagedir_prepare(...);
 * >> pagedir_map(...);
 * >> pagedir_unmap(...);
 * >> pagedir_unprepare(...);
 * NOTE: A prepared  mapping is  not only  valid for  the exact  range.
 *       Wishing to map something at a sub-range of it is also allowed:
 *       >> pagedir_prepare(5, 6);   // Prepage 6 bytes at address 5 for modification
 *       >> pagedir_map(5, 3);       // OK
 *       >> pagedir_map(8, 3);       // OK
 *       >> pagedir_unprepare(5, 6); // Indicate that the 6 bytes must not longer be modified
 *       *: Addresses in this example would only be correct for PAGESIZE=1
 * WARNING: prepare() + unprepare() _DONT_  work recursively, and are  also
 *          not thread-safe when called for overlapping ranges in parallel!
 * WARNING: unprepare() should always be called with the same range-, or a
 *          larger (fully overlapping) range as during the prior prepare()
 * @return: true:  Successfully allocated structures required for creating mappings.
 * @return: false: Insufficient physical memory to prepare mappings. */
#ifndef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_PREPARE
FUNDEF NOBLOCK WUNUSED __BOOL
NOTHROW(FCALL pagedir_prepareone)(PAGEDIR_PAGEALIGNED VIRT void *addr);
FUNDEF NOBLOCK void
NOTHROW(FCALL pagedir_unprepareone)(PAGEDIR_PAGEALIGNED VIRT void *addr);
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK WUNUSED __BOOL
NOTHROW(FCALL __private_pagedir_prepare)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                         PAGEDIR_PAGEALIGNED size_t num_bytes)
		ASMNAME("pagedir_prepare");
FUNDEF NOBLOCK void
NOTHROW(FCALL __private_pagedir_unprepare)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                           PAGEDIR_PAGEALIGNED size_t num_bytes)
		ASMNAME("pagedir_unprepare");
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL WUNUSED __BOOL
NOTHROW(FCALL pagedir_prepare)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                               PAGEDIR_PAGEALIGNED size_t num_bytes) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return 1;
		if (num_bytes <= PAGESIZE)
			return pagedir_prepareone(addr);
	}
	return __private_pagedir_prepare(addr, num_bytes);
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(FCALL pagedir_unprepare)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                 PAGEDIR_PAGEALIGNED size_t num_bytes) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			pagedir_unprepareone(addr);
			return;
		}
	}
	__private_pagedir_unprepare(addr, num_bytes);
}
#else /* !__OMIT_PAGING_CONSTANT_P_WRAPPERS */
FUNDEF NOBLOCK WUNUSED __BOOL
NOTHROW(FCALL pagedir_prepare)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                               PAGEDIR_PAGEALIGNED size_t num_bytes);
FUNDEF NOBLOCK void
NOTHROW(FCALL pagedir_unprepare)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                 PAGEDIR_PAGEALIGNED size_t num_bytes);
#endif /* __OMIT_PAGING_CONSTANT_P_WRAPPERS */
#endif /* !ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_PREPARE */



/* Set a mapping hint for pages apart of the given virtual memory range.
 * Mapping hints are overwritten once a  page has been mapped, and  when
 * not specified, will default to `NULL'.
 * Their main purpose is to be accessible through atomic means, allowing
 * them to be used by the PAGE_FAULT handler, while still ensuring  that
 * access remains non-blocking.
 * Note  that because of platform-specific restrictions, only pointers
 * which are aligned by at least `PAGEDIR_MAPHINT_ALIGNMENT' bytes can
 * be specified as hints.
 *  - Use of this function requires a prior call to `pagedir_prepare()'!
 *  - Memory  mappings  defined  in  `mman_kernel'  as  `MNODE_F_MHINT' have
 *    their mapping hint set to the address of the associated `struct mnode' */
#ifndef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_MAPHINT
FUNDEF NOBLOCK void
NOTHROW(FCALL pagedir_maphintone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                  VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint);
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK void
NOTHROW(FCALL __private_pagedir_maphint)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                         PAGEDIR_PAGEALIGNED size_t num_bytes,
                                         VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint)
		ASMNAME("pagedir_maphint");
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(FCALL pagedir_maphint)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                               PAGEDIR_PAGEALIGNED size_t num_bytes,
                               VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			pagedir_maphintone(addr, hint);
			return;
		}
	}
	__private_pagedir_maphint(addr, num_bytes, hint);
}
#else /* !__OMIT_PAGING_CONSTANT_P_WRAPPERS */
FUNDEF NOBLOCK void
NOTHROW(FCALL pagedir_maphint)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                               PAGEDIR_PAGEALIGNED size_t num_bytes,
                               VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint);
#endif /* __OMIT_PAGING_CONSTANT_P_WRAPPERS */
#endif /* !ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_MAPHINT */


/* Return the hint of the given page, or NULL if no hint has been mapped. */
#ifndef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_GETHINT
FUNDEF NOBLOCK WUNUSED void *NOTHROW(FCALL pagedir_gethint)(VIRT void *addr);
#endif /* !ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_GETHINT */


/* Create/delete a page-directory mapping.
 * @param: prot: A set  of `PAGEDIR_PROT_*'  detailing how  memory should  be  mapped.
 * `pagedir_sync()' must be called while specifying a virtual address range containing
 * `addr...+=num_bytes' in order to ensure that changes will become visible.
 * NOTE: This function  can be called  regardless of which  page directory is  active. */
#ifndef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_MAP
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                                  PAGEDIR_PAGEALIGNED physaddr_t phys,
                                                  pagedir_prot_t prot);
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK void
NOTHROW(FCALL __private_pagedir_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                     PAGEDIR_PAGEALIGNED size_t num_bytes,
                                     PAGEDIR_PAGEALIGNED physaddr_t phys,
                                     pagedir_prot_t prot)
		ASMNAME("pagedir_map");
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(FCALL pagedir_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                           PAGEDIR_PAGEALIGNED size_t num_bytes,
                           PAGEDIR_PAGEALIGNED physaddr_t phys,
                           pagedir_prot_t prot) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			pagedir_mapone(addr, phys, prot);
			return;
		}
	}
	__private_pagedir_map(addr, num_bytes, phys, prot);
}
#else /* !__OMIT_PAGING_CONSTANT_P_WRAPPERS */
FUNDEF NOBLOCK void
NOTHROW(FCALL pagedir_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                           PAGEDIR_PAGEALIGNED size_t num_bytes,
                           PAGEDIR_PAGEALIGNED physaddr_t phys,
                           pagedir_prot_t prot);
#endif /* __OMIT_PAGING_CONSTANT_P_WRAPPERS */
#endif /* !ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_MAP */


/* Special variants of `pagedir_mapone()' that should be used to
 * temporary override the  mapping of a  single, prepared  page.
 * These functions are  mainly intended for  use with `this_trampoline_page',  allowing
 * each  thread to push/pop its trampoline page, with doing so actually being an atomic
 * operation in the sense that the data is entirely thread-private, while modifications
 * do not require any kind of lock.
 * NOTE: If the page had been mapped, `pagedir_pop_mapone()' will automatically sync the page. */
#ifndef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_PUSH_MAPONE
FUNDEF NOBLOCK WUNUSED pagedir_pushval_t
NOTHROW(FCALL pagedir_push_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                   PAGEDIR_PAGEALIGNED physaddr_t phys,
                                   pagedir_prot_t prot);
FUNDEF NOBLOCK void
NOTHROW(FCALL pagedir_pop_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                  pagedir_pushval_t backup);
#endif /* !ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_PUSH_MAPONE */


/* Unmap pages from the given address range. (requires that the given area be prepared) */
#ifndef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_UNMAP
FUNDEF NOBLOCK void
NOTHROW(FCALL pagedir_unmapone)(PAGEDIR_PAGEALIGNED VIRT void *addr);
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK void
NOTHROW(FCALL __private_pagedir_unmap)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                       PAGEDIR_PAGEALIGNED size_t num_bytes)
		ASMNAME("pagedir_unmap");
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(FCALL pagedir_unmap)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                             PAGEDIR_PAGEALIGNED size_t num_bytes) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			pagedir_unmapone(addr);
			return;
		}
	}
	__private_pagedir_unmap(addr, num_bytes);
}
#else /* !__OMIT_PAGING_CONSTANT_P_WRAPPERS */
FUNDEF NOBLOCK void
NOTHROW(FCALL pagedir_unmap)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                             PAGEDIR_PAGEALIGNED size_t num_bytes);
#endif /* __OMIT_PAGING_CONSTANT_P_WRAPPERS */
#endif /* !ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_UNMAP */


/* Remove write-permissions from the given address range. (requires that the given area be prepared) */
#ifdef ARCH_PAGEDIR_HAVE_DENYWRITE
#ifndef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_UNWRITE
FUNDEF NOBLOCK void
NOTHROW(FCALL pagedir_denywriteone)(PAGEDIR_PAGEALIGNED VIRT void *addr);
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK void
NOTHROW(FCALL __private_pagedir_denywrite)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                           PAGEDIR_PAGEALIGNED size_t num_bytes)
		ASMNAME("pagedir_denywrite");
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(FCALL pagedir_denywrite)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                 PAGEDIR_PAGEALIGNED size_t num_bytes) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			pagedir_denywriteone(addr);
			return;
		}
	}
	__private_pagedir_denywrite(addr, num_bytes);
}
#else /* !__OMIT_PAGING_CONSTANT_P_WRAPPERS */
FUNDEF NOBLOCK void
NOTHROW(FCALL pagedir_denywrite)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                 PAGEDIR_PAGEALIGNED size_t num_bytes);
#endif /* __OMIT_PAGING_CONSTANT_P_WRAPPERS */
#endif /* !ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_UNWRITE */
#endif /* ARCH_PAGEDIR_HAVE_DENYWRITE */


#ifndef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_SYNC
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK void
NOTHROW(FCALL __private_pagedir_sync)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                      PAGEDIR_PAGEALIGNED size_t num_bytes)
		ASMNAME("pagedir_sync");
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(FCALL pagedir_sync)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                            PAGEDIR_PAGEALIGNED size_t num_bytes) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			pagedir_syncone(addr);
			return;
		}
	}
	__private_pagedir_sync(addr, num_bytes);
}
#else /* !__OMIT_PAGING_CONSTANT_P_WRAPPERS */
FUNDEF NOBLOCK void
NOTHROW(FCALL pagedir_sync)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                            PAGEDIR_PAGEALIGNED size_t num_bytes);
#endif /* __OMIT_PAGING_CONSTANT_P_WRAPPERS */
#endif /* !ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_SYNC */


#ifndef CONFIG_NO_SMP
/* Sync memory on every CPU with `CPU->c_pdir == pagedir' */
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_sync_smp_p)(pagedir_phys_t pagedir, PAGEDIR_PAGEALIGNED VIRT void *addr, PAGEDIR_PAGEALIGNED size_t num_bytes);
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_syncone_smp_p)(pagedir_phys_t pagedir, PAGEDIR_PAGEALIGNED VIRT void *addr);
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_syncall_smp_p)(pagedir_phys_t pagedir);

/* Sync memory on every CPU with `CPU->c_pdir == pagedir_get()' */
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_sync_smp)(PAGEDIR_PAGEALIGNED VIRT void *addr, PAGEDIR_PAGEALIGNED size_t num_bytes);
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_syncone_smp)(PAGEDIR_PAGEALIGNED VIRT void *addr);
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_syncall_smp)(void);
#else /* !CONFIG_NO_SMP */
#if 1 /* No point in comparing against the current pagedir. - If they don't match,
       * syncing  is  a  semantic  no-op,  and  usually  they're  going  to match! */
#define pagedir_sync_smp_p(pagedir, addr, num_bytes) pagedir_sync(addr, num_bytes)
#define pagedir_syncone_smp_p(pagedir, addr)         pagedir_syncone(addr)
#define pagedir_syncall_smp_p(pagedir)               pagedir_syncall()
#else
#define pagedir_sync_smp_p(pagedir, addr, num_bytes) ((pagedir) == pagedir_get() ? pagedir_sync(addr, num_bytes) : (void)0)
#define pagedir_syncone_smp_p(pagedir, addr)         ((pagedir) == pagedir_get() ? pagedir_syncone(addr) : (void)0)
#define pagedir_syncall_smp_p(pagedir)               ((pagedir) == pagedir_get() ? pagedir_syncall() : (void)0)
#endif
#define pagedir_sync_smp(addr, num_bytes) pagedir_sync(addr, num_bytes)
#define pagedir_syncone_smp(addr)         pagedir_syncone(addr)
#define pagedir_syncall_smp()             pagedir_syncall()
#endif /* CONFIG_NO_SMP */



/* Check if the given page is mapped.
 * NOTE: The given `addr' */
#ifndef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_ISMAPPED
FUNDEF NOBLOCK ATTR_PURE WUNUSED ATTR_ACCESS_NONE(1) __BOOL NOTHROW(FCALL pagedir_ismapped)(VIRT void const *addr);
FUNDEF NOBLOCK ATTR_PURE WUNUSED __BOOL NOTHROW(FCALL pagedir_iswritable)(VIRT void *addr);
FUNDEF NOBLOCK ATTR_PURE WUNUSED ATTR_ACCESS_NONE(1) __BOOL NOTHROW(FCALL pagedir_isuseraccessible)(VIRT void const *addr);
FUNDEF NOBLOCK ATTR_PURE WUNUSED __BOOL NOTHROW(FCALL pagedir_isuserwritable)(VIRT void *addr);
#endif /* !ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_ISMAPPED */


#ifdef ARCH_PAGEDIR_HAVE_CHANGED
#ifndef ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_HASCHANGED
/* TODO: Figure out a better design for these functions
 *       The current system is written under the assumption that 4MiB pages don't exist... */
FUNDEF NOBLOCK ATTR_PURE WUNUSED __BOOL NOTHROW(FCALL pagedir_haschanged)(VIRT void *addr);
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_unsetchanged)(VIRT void *addr);
#endif /* !ARCH_PAGEDIR_ARCHHEADER_DEFINES_PAGEDIR_HASCHANGED */
#endif /* ARCH_PAGEDIR_HAVE_CHANGED */


/* Same as the functions above, but operate on the specified
 * page directory, rather than the one currently being used.
 * NOTE: The caller is responsible for synchronization. */
FUNDEF NOBLOCK WUNUSED __BOOL NOTHROW(KCALL pagedir_prepareone_p)(pagedir_phys_t self, PAGEDIR_PAGEALIGNED VIRT void *addr);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unprepareone_p)(pagedir_phys_t self, PAGEDIR_PAGEALIGNED VIRT void *addr);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_maphintone_p)(pagedir_phys_t self, PAGEDIR_PAGEALIGNED VIRT void *addr, VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_mapone_p)(pagedir_phys_t self, PAGEDIR_PAGEALIGNED VIRT void *addr, PAGEDIR_PAGEALIGNED physaddr_t phys, pagedir_prot_t prot);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unmapone_p)(pagedir_phys_t self, PAGEDIR_PAGEALIGNED VIRT void *addr);
#ifdef ARCH_PAGEDIR_HAVE_DENYWRITE
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_denywriteone_p)(pagedir_phys_t self, PAGEDIR_PAGEALIGNED VIRT void *addr);
#endif /* ARCH_PAGEDIR_HAVE_DENYWRITE */
FUNDEF NOBLOCK ATTR_PURE WUNUSED ATTR_ACCESS_NONE(2) __BOOL NOTHROW(KCALL pagedir_ismapped_p)(pagedir_phys_t self, VIRT void const *addr);
FUNDEF NOBLOCK ATTR_PURE WUNUSED __BOOL NOTHROW(KCALL pagedir_iswritable_p)(pagedir_phys_t self, VIRT void *addr);
FUNDEF NOBLOCK ATTR_PURE WUNUSED ATTR_ACCESS_NONE(2) __BOOL NOTHROW(KCALL pagedir_isuseraccessible_p)(pagedir_phys_t self, VIRT void const *addr);
FUNDEF NOBLOCK ATTR_PURE WUNUSED __BOOL NOTHROW(KCALL pagedir_isuserwritable_p)(pagedir_phys_t self, VIRT void *addr);
#ifdef ARCH_PAGEDIR_HAVE_CHANGED
FUNDEF NOBLOCK ATTR_PURE WUNUSED __BOOL NOTHROW(KCALL pagedir_haschanged_p)(pagedir_phys_t self, VIRT void *addr);
FUNDEF NOBLOCK void NOTHROW(KCALL pagedir_unsetchanged_p)(pagedir_phys_t self, VIRT void *addr);
#endif /* ARCH_PAGEDIR_HAVE_CHANGED */
#ifndef __OMIT_PAGING_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK WUNUSED __BOOL
NOTHROW(KCALL __private_pagedir_prepare_p)(pagedir_phys_t self,
                                           PAGEDIR_PAGEALIGNED VIRT void *addr,
                                           PAGEDIR_PAGEALIGNED size_t num_bytes)
		ASMNAME("pagedir_prepare_p");
FUNDEF NOBLOCK void
NOTHROW(KCALL __private_pagedir_unprepare_p)(pagedir_phys_t self,
                                             PAGEDIR_PAGEALIGNED VIRT void *addr,
                                             PAGEDIR_PAGEALIGNED size_t num_bytes)
		ASMNAME("pagedir_unprepare_p");
FUNDEF NOBLOCK void
NOTHROW(KCALL __private_pagedir_maphint_p)(pagedir_phys_t self,
                                           PAGEDIR_PAGEALIGNED VIRT void *addr,
                                           PAGEDIR_PAGEALIGNED size_t num_bytes,
                                           VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint)
		ASMNAME("pagedir_maphint_p");
FUNDEF NOBLOCK void
NOTHROW(KCALL __private_pagedir_map_p)(pagedir_phys_t self,
                                       PAGEDIR_PAGEALIGNED VIRT void *addr,
                                       PAGEDIR_PAGEALIGNED size_t num_bytes,
                                       PAGEDIR_PAGEALIGNED physaddr_t phys,
                                       pagedir_prot_t prot)
		ASMNAME("pagedir_map_p");
FUNDEF NOBLOCK void
NOTHROW(KCALL __private_pagedir_unmap_p)(pagedir_phys_t self,
                                         PAGEDIR_PAGEALIGNED VIRT void *addr,
                                         PAGEDIR_PAGEALIGNED size_t num_bytes)
		ASMNAME("pagedir_unmap_p");
#ifdef ARCH_PAGEDIR_HAVE_DENYWRITE
FUNDEF NOBLOCK void
NOTHROW(KCALL __private_pagedir_denywrite_p)(pagedir_phys_t self,
                                             PAGEDIR_PAGEALIGNED VIRT void *addr,
                                             PAGEDIR_PAGEALIGNED size_t num_bytes)
		ASMNAME("pagedir_denywrite_p");
#endif /* ARCH_PAGEDIR_HAVE_DENYWRITE */

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL WUNUSED __BOOL
NOTHROW(KCALL pagedir_prepare_p)(pagedir_phys_t self,
                                 PAGEDIR_PAGEALIGNED VIRT void *addr,
                                 PAGEDIR_PAGEALIGNED size_t num_bytes) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return 1;
		if (num_bytes <= PAGESIZE)
			return pagedir_prepareone_p(self, addr);
	}
	return __private_pagedir_prepare_p(self, addr, num_bytes);
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(KCALL pagedir_unprepare_p)(pagedir_phys_t self,
                                   PAGEDIR_PAGEALIGNED VIRT void *addr,
                                   PAGEDIR_PAGEALIGNED size_t num_bytes) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			pagedir_unprepareone_p(self, addr);
			return;
		}
	}
	__private_pagedir_unprepare_p(self, addr, num_bytes);
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(KCALL pagedir_maphint_p)(pagedir_phys_t self,
                                 PAGEDIR_PAGEALIGNED VIRT void *addr,
                                 PAGEDIR_PAGEALIGNED size_t num_bytes,
                                 VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			pagedir_maphintone_p(self, addr, hint);
			return;
		}
	}
	__private_pagedir_maphint_p(self, addr, num_bytes, hint);
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(KCALL pagedir_map_p)(pagedir_phys_t self,
                             PAGEDIR_PAGEALIGNED VIRT void *addr,
                             PAGEDIR_PAGEALIGNED size_t num_bytes,
                             PAGEDIR_PAGEALIGNED physaddr_t phys,
                             pagedir_prot_t prot) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			pagedir_mapone_p(self, addr, phys, prot);
			return;
		}
	}
	__private_pagedir_map_p(self, addr, num_bytes, phys, prot);
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(KCALL pagedir_unmap_p)(pagedir_phys_t self,
                               PAGEDIR_PAGEALIGNED VIRT void *addr,
                               PAGEDIR_PAGEALIGNED size_t num_bytes) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			pagedir_unmapone_p(self, addr);
			return;
		}
	}
	__private_pagedir_unmap_p(self, addr, num_bytes);
}

#ifdef ARCH_PAGEDIR_HAVE_DENYWRITE
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(KCALL pagedir_denywrite_p)(pagedir_phys_t self,
                                   PAGEDIR_PAGEALIGNED VIRT void *addr,
                                   PAGEDIR_PAGEALIGNED size_t num_bytes) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes <= PAGESIZE) {
			pagedir_denywriteone_p(self, addr);
			return;
		}
	}
	__private_pagedir_denywrite_p(self, addr, num_bytes);
}
#endif /* ARCH_PAGEDIR_HAVE_DENYWRITE */
#else /* !__OMIT_PAGING_CONSTANT_P_WRAPPERS */
FUNDEF NOBLOCK WUNUSED __BOOL
NOTHROW(KCALL pagedir_prepare_p)(pagedir_phys_t self,
                                 PAGEDIR_PAGEALIGNED VIRT void *addr,
                                 PAGEDIR_PAGEALIGNED size_t num_bytes);
FUNDEF NOBLOCK void
NOTHROW(KCALL pagedir_unprepare_p)(pagedir_phys_t self,
                                   PAGEDIR_PAGEALIGNED VIRT void *addr,
                                   PAGEDIR_PAGEALIGNED size_t num_bytes);
FUNDEF NOBLOCK void
NOTHROW(KCALL pagedir_maphint_p)(pagedir_phys_t self,
                                 PAGEDIR_PAGEALIGNED VIRT void *addr,
                                 PAGEDIR_PAGEALIGNED size_t num_bytes,
                                 VIRT /*ALIGNED(PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint);
FUNDEF NOBLOCK void
NOTHROW(KCALL pagedir_map_p)(pagedir_phys_t self,
                             PAGEDIR_PAGEALIGNED VIRT void *addr,
                             PAGEDIR_PAGEALIGNED size_t num_bytes,
                             PAGEDIR_PAGEALIGNED physaddr_t phys,
                             pagedir_prot_t prot);
FUNDEF NOBLOCK void
NOTHROW(KCALL pagedir_unmap_p)(pagedir_phys_t self,
                               PAGEDIR_PAGEALIGNED VIRT void *addr,
                               PAGEDIR_PAGEALIGNED size_t num_bytes);
#ifdef ARCH_PAGEDIR_HAVE_DENYWRITE
FUNDEF NOBLOCK void
NOTHROW(KCALL pagedir_denywrite_p)(pagedir_phys_t self,
                                   PAGEDIR_PAGEALIGNED VIRT void *addr,
                                   PAGEDIR_PAGEALIGNED size_t num_bytes);
#endif /* ARCH_PAGEDIR_HAVE_DENYWRITE */
#endif /* __OMIT_PAGING_CONSTANT_P_WRAPPERS */

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_PAGING_H */
