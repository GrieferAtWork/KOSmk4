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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_VM_PHYS_H
#define GUARD_KERNEL_INCLUDE_KERNEL_VM_PHYS_H 1

#include <kernel/compiler.h>

#include <kernel/arch/paging.h> /* `pagedir_pushval_t' */
#include <kernel/paging.h>      /* `pagedir_push_mapone()' */
#include <kernel/types.h>
#include <sched/pertask.h> /* PERTASK_GET() */

#include <hybrid/__assert.h>
#include <hybrid/__unaligned.h>

#include <kos/kernel/paging.h> /* `PHYS_IS_IDENTITY()' */

/* Helper functions for accessing physical memory */

DECL_BEGIN

#ifndef PHYS_IS_IDENTITY
#define NO_PHYS_IDENTITY 1
#define PHYS_IS_IDENTITY(addr, num_bytes) 0
#define PHYS_TO_IDENTITY(addr) (void *)0
#endif /* !PHYS_IS_IDENTITY */

#ifndef PHYS_IS_IDENTITY_PAGE
#define PHYS_IS_IDENTITY_PAGE(pageno) \
	PHYS_IS_IDENTITY(VM_PPAGE2ADDR(pageno), PAGESIZE)
#define PHYS_TO_IDENTITY_PAGE(addr) \
	PHYS_TO_IDENTITY(VM_PPAGE2ADDR(pageno))
#endif /* !PHYS_IS_IDENTITY_PAGE */


#ifndef __pagedir_pushval_t_defined
#define __pagedir_pushval_t_defined 1
#define PAGEDIR_PUSHVAL_INVALID (__CCAST(pagedir_pushval_t)-1)
#define SIZEOF_PAGEDIR_PUSHVAL  __SIZEOF_POINTER__
#ifdef __CC__
typedef uintptr_t pagedir_pushval_t;
#endif /* __CC__ */
#endif /* !__pagedir_pushval_t_defined */


#ifdef __CC__

/* Helper functions for accessing very small segments of physical memory.
 * WARNING: DON'T SPAM THESE FUNCTIONS! If you want to access consecutive physical memory,
 *          either make use of `vm_copy(from|to)phys()' or `THIS_TRAMPOLINE_PAGE'.
 *          These functions will try to make use arch-specific physical identity mappings,
 *          like can be found on `x86_64' for the first 1Gib of physical memory.
 *          However any memory outside that region (or any memory at all if no such
 *          region is defined by the arch (as is the case for `i386'), will need to
 *          be accessed through use of `THIS_TRAMPOLINE_PAGE'!) */
FUNDEF NOBLOCK WUNUSED u8 NOTHROW(KCALL vm_readphysb)(PHYS vm_phys_t addr);
FUNDEF NOBLOCK WUNUSED u16 NOTHROW(KCALL vm_readphysw)(/*aligned(2)*/ PHYS vm_phys_t addr);
FUNDEF NOBLOCK WUNUSED u32 NOTHROW(KCALL vm_readphysl)(/*aligned(4)*/ PHYS vm_phys_t addr);
FUNDEF NOBLOCK WUNUSED u16 NOTHROW(KCALL vm_readphysw_unaligned)(PHYS vm_phys_t addr);
FUNDEF NOBLOCK WUNUSED u32 NOTHROW(KCALL vm_readphysl_unaligned)(PHYS vm_phys_t addr);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_writephysb)(PHYS vm_phys_t addr, u8 value);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_writephysw)(/*aligned(2)*/ PHYS vm_phys_t addr, u16 value);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_writephysl)(/*aligned(4)*/ PHYS vm_phys_t addr, u32 value);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_writephysw_unaligned)(PHYS vm_phys_t addr, u16 value);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_writephysl_unaligned)(PHYS vm_phys_t addr, u32 value);
#ifdef __UINT64_TYPE__
FUNDEF NOBLOCK WUNUSED u64 NOTHROW(KCALL vm_readphysq)(/*aligned(8)*/ PHYS vm_phys_t addr);
FUNDEF NOBLOCK WUNUSED u64 NOTHROW(KCALL vm_readphysq_unaligned)(PHYS vm_phys_t addr);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_writephysq)(/*aligned(8)*/ PHYS vm_phys_t addr, u64 value);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_writephysq_unaligned)(PHYS vm_phys_t addr, u64 value);
#endif /* __UINT64_TYPE__ */



/* Copy memory to/from the physical address space. */
#ifdef __OMIT_PHYS_COPY_CONSTANT_P_WRAPPERS
FUNDEF void KCALL vm_copyfromphys(USER CHECKED void *dst, PHYS vm_phys_t src, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF void KCALL vm_copytophys(PHYS vm_phys_t dst, USER CHECKED void const *src, size_t num_bytes) THROWS(E_SEGFAULT);
#else /* __OMIT_PHYS_COPY_CONSTANT_P_WRAPPERS */
FUNDEF void KCALL __os_vm_copyfromphys(USER CHECKED void *dst, PHYS vm_phys_t src, size_t num_bytes) THROWS(E_SEGFAULT) ASMNAME("vm_copyfromphys");
FUNDEF void KCALL __os_vm_copytophys(PHYS vm_phys_t dst, USER CHECKED void const *src, size_t num_bytes) THROWS(E_SEGFAULT) ASMNAME("vm_copytophys");

FORCELOCAL void KCALL
vm_copyfromphys(USER CHECKED void *dst,
                PHYS vm_phys_t src,
                size_t num_bytes)
		THROWS(E_SEGFAULT) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes == 1) {
			*(u8 *)dst = vm_readphysb(src);
			return;
		}
		if (num_bytes == 2) {
			__hybrid_unaligned_set16((u16 *)dst, vm_readphysw(src));
			return;
		}
		if (num_bytes == 4) {
			__hybrid_unaligned_set32((u32 *)dst, vm_readphysl(src));
			return;
		}
#ifdef __UINT64_TYPE__
		if (num_bytes == 8) {
			__hybrid_unaligned_set64((u64 *)dst, vm_readphysq(src));
			return;
		}
#endif /* __UINT64_TYPE__ */
	}
	__os_vm_copyfromphys(dst, src, num_bytes);
}

FORCELOCAL void KCALL
vm_copytophys(PHYS vm_phys_t dst,
              USER CHECKED void const *src,
              size_t num_bytes)
		THROWS(E_SEGFAULT) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes == 1) {
			vm_writephysb(dst, *(u8 *)src);
			return;
		}
		if (num_bytes == 2) {
			vm_writephysw(dst, __hybrid_unaligned_get16((u16 *)src));
			return;
		}
		if (num_bytes == 4) {
			vm_writephysl(dst, __hybrid_unaligned_get32((u32 *)src));
			return;
		}
#ifdef __UINT64_TYPE__
		if (num_bytes == 8) {
			vm_writephysq(dst, __hybrid_unaligned_get64((u64 *)src));
			return;
		}
#endif /* __UINT64_TYPE__ */
	}
	__os_vm_copytophys(dst, src, num_bytes);
}
#endif /* !__OMIT_PHYS_COPY_CONSTANT_P_WRAPPERS */

FUNDEF NOBLOCK void NOTHROW(KCALL vm_copyinphys)(PHYS vm_phys_t dst, PHYS vm_phys_t src, size_t num_bytes);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_memsetphys)(PHYS vm_phys_t dst, int byte, size_t num_bytes);




/* no-#PF variants of `vm_copy(from|to)phys()'.
 * @return: 0 : The copy operation completed without any problems.
 * @return: * : The number of bytes that could not be transfered.
 *              The affected memory range is:
 *               - `(dst|src) + num_bytes - return ... (dst|src) + num_bytes - 1' */
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL vm_copyfromphys_nopf)(USER CHECKED void *dst, PHYS vm_phys_t src, size_t num_bytes);
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL vm_copytophys_nopf)(PHYS vm_phys_t dst, USER CHECKED void const *src, size_t num_bytes);

/* Same as the functions above, however all memory accesses are guarantied to happen within the same page.
 * In other words: `(PHYS & ~PAGEMASK) == ((PHYS + num_bytes - 1) & ~PAGEMASK)' */
FUNDEF void KCALL vm_copyfromphys_onepage(USER CHECKED void *dst, PHYS vm_phys_t src, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF void KCALL vm_copytophys_onepage(PHYS vm_phys_t dst, USER CHECKED void const *src, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_copyinphys_onepage)(PHYS vm_phys_t dst, PHYS vm_phys_t src, size_t num_bytes);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_memsetphys_onepage)(PHYS vm_phys_t dst, int byte, size_t num_bytes);
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL vm_copyfromphys_onepage_nopf)(USER CHECKED void *dst, PHYS vm_phys_t src, size_t num_bytes);
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL vm_copytophys_onepage_nopf)(PHYS vm_phys_t dst, USER CHECKED void const *src, size_t num_bytes);

/* Copy a whole page to/from physical memory. (s.a. `PAGESIZE') */
FUNDEF void KCALL vm_copypagefromphys(USER CHECKED void *dst, PHYS vm_ppage_t src) THROWS(E_SEGFAULT);
FUNDEF void KCALL vm_copypagetophys(PHYS vm_ppage_t dst, USER CHECKED void const *src) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_copypageinphys)(PHYS vm_ppage_t dst, PHYS vm_ppage_t src);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_copypagesinphys)(PHYS vm_ppage_t dst, PHYS vm_ppage_t src, size_t num_pages);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_memsetphyspage)(PHYS vm_ppage_t dst, int byte);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_memsetphyspages)(PHYS vm_ppage_t dst, int byte, size_t num_pages);
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL vm_copypagefromphys_nopf)(USER CHECKED void *dst, PHYS vm_ppage_t src);
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL vm_copypagetophys_nopf)(PHYS vm_ppage_t dst, USER CHECKED void const *src);

/* A single page of virtual memory in the kernel VM, that is always
 * prepared for being used for whatever purposes a thread has in mind.
 * NOTE: This page is also used by PAGEFAULTS, though it will
 *       restore a previous mapping, if such a mapping existed.
 * NOTE: Because this page is unique for each thread, the user is not
 *       required to acquire a lock to the kernel VM when wishing to
 *       map something at this location! */
DATDEF ATTR_PERTASK vm_vpage_t this_trampoline_page;

/* TODO: Go through all uses of `THIS_TRAMPOLINE_PAGE' and add
 *       optimizations for supporting `PHYS_IS_IDENTITY()' */
#define THIS_TRAMPOLINE_PAGE PERTASK_GET(this_trampoline_page)
#define THIS_TRAMPOLINE_BASE ((void *)VM_PAGE2ADDR(THIS_TRAMPOLINE_PAGE))

/* A VM node used to describe a single, reserved page. */
DATDEF ATTR_PERTASK struct vm_node this_trampoline_node;


/* Helper for unifying `PHYS_IS_IDENTITY()' and `pagedir_push_mapone(THIS_TRAMPOLINE)' */
struct vm_ptram {
	/* VM_PhysTRAMpoline */
	pagedir_pushval_t pt_pushval; /* The pushed value (or `PAGEDIR_PUSHVAL_INVALID' if nothing was pushed) */
};
#define VM_PTRAM_INIT        { PAGEDIR_PUSHVAL_INVALID }
#define vm_ptram_init(self)  ((self)->pt_pushval = PAGEDIR_PUSHVAL_INVALID)
#ifdef __PAGEDIR_PUSHVAL_INVALID_IS_ZERO
#define vm_ptram_cinit(self) __hybrid_assert((self)->pt_pushval == 0)
#else /* __PAGEDIR_PUSHVAL_INVALID_IS_ZERO */
#define vm_ptram_cinit(self) (__hybrid_assert((self)->pt_pushval == 0), (self)->pt_pushval = PAGEDIR_PUSHVAL_INVALID)
#endif /* !__PAGEDIR_PUSHVAL_INVALID_IS_ZERO */
#define vm_ptram_fini(self) \
	((self)->pt_pushval == PAGEDIR_PUSHVAL_INVALID \
	 ? (void)0                                     \
	 : pagedir_pop_mapone(THIS_TRAMPOLINE_PAGE, (self)->pt_pushval))

LOCAL NOBLOCK WUNUSED ATTR_RETNONNULL NONNULL((1)) byte_t *
NOTHROW(KCALL vm_ptram_mappage_noidentity)(struct vm_ptram *__restrict self,
                                           vm_ppage_t page, __BOOL writable DFL(true)) {
	vm_vpage_t trampoline;
	trampoline = THIS_TRAMPOLINE_PAGE;
	if (self->pt_pushval == PAGEDIR_PUSHVAL_INVALID) {
		self->pt_pushval = pagedir_push_mapone(trampoline, page,
		                                       writable ? PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE
		                                                : PAGEDIR_MAP_FREAD);
	} else {
		pagedir_mapone(trampoline, page,
		               writable ? PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE
		                        : PAGEDIR_MAP_FREAD);
	}
	return (byte_t *)VM_PAGE2ADDR(trampoline);
}

/* Return a (possibly temporary) virtual memory mapping of `page' */
#ifndef NO_PHYS_IDENTITY
LOCAL NOBLOCK WUNUSED ATTR_RETNONNULL NONNULL((1)) byte_t *
NOTHROW(KCALL vm_ptram_mappage)(struct vm_ptram *__restrict self,
                                vm_ppage_t page, __BOOL writable DFL(true)) {
	if (PHYS_IS_IDENTITY_PAGE(page))
		return (byte_t *)PHYS_TO_IDENTITY_PAGE(page);
	return vm_ptram_mappage_noidentity(self, page, writable);
}
#else /* !NO_PHYS_IDENTITY */
#define vm_ptram_mappage vm_ptram_mappage_noidentity
#endif /* NO_PHYS_IDENTITY */

LOCAL NOBLOCK WUNUSED ATTR_RETNONNULL NONNULL((1)) byte_t *
NOTHROW(KCALL vm_ptram_map)(struct vm_ptram *__restrict self,
                            vm_phys_t addr, __BOOL writable DFL(true)) {
	byte_t *result;
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(addr, 1))
		return (byte_t *)PHYS_TO_IDENTITY(addr);
#endif /* !NO_PHYS_IDENTITY */
	result = vm_ptram_mappage_noidentity(self, VM_ADDR2PAGE(addr), writable);
	result += (uintptr_t)(addr & PAGEMASK);
	return result;
}



#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_VM_PHYS_H */
