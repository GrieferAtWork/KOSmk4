/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_PHYS_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_PHYS_H 1

#include <kernel/compiler.h>

#include <kernel/arch/paging.h> /* `pagedir_pushval_t' */
#include <kernel/memory.h>      /* `physpage2addr()' */
#include <kernel/paging.h>      /* `pagedir_push_mapone()' */
#include <kernel/types.h>
#include <sched/pertask.h> /* PERTASK_GET() */

#include <hybrid/__assert.h>
#include <hybrid/__unaligned.h>
#include <hybrid/typecore.h>

#include <kos/kernel/paging.h> /* `PHYS_IS_IDENTITY()' */

#ifdef __CC__
DECL_BEGIN

struct mnode;

#ifndef PHYS_IS_IDENTITY
#define NO_PHYS_IDENTITY 1
#define PHYS_IS_IDENTITY(addr, num_bytes) 0
#define PHYS_TO_IDENTITY(addr) (byte_t *)0
#endif /* !PHYS_IS_IDENTITY */

#ifndef PHYS_IS_IDENTITY_PAGE
#define PHYS_IS_IDENTITY_PAGE(pageno) PHYS_IS_IDENTITY(physpage2addr(pageno), PAGESIZE)
#define PHYS_TO_IDENTITY_PAGE(addr)   PHYS_TO_IDENTITY(physpage2addr(pageno))
#endif /* !PHYS_IS_IDENTITY_PAGE */


#ifndef __pagedir_pushval_t_defined
#define __pagedir_pushval_t_defined
#define PAGEDIR_PUSHVAL_INVALID (__CCAST(pagedir_pushval_t)-1)
#define SIZEOF_PAGEDIR_PUSHVAL  __SIZEOF_POINTER__
#ifdef __CC__
typedef uintptr_t pagedir_pushval_t;
#endif /* __CC__ */
#endif /* !__pagedir_pushval_t_defined */





/************************************************************************/
/* Helper functions for accessing very small segments of physical memory.
 * WARNING: DON'T SPAM THESE FUNCTIONS! If you want to access consecutive physical
 *          memory, either make use of `copy(from|to)phys()' or `THIS_TRAMPOLINE'.
 * - These functions will try to make use arch-specific physical identity mappings,
 *   like can  be  found  on `x86_64'  for  the  first 64TiB  of  physical  memory.
 * - However any memory outside that region (or  any memory at all if no  such
 *   region is defined by the arch -- as is the case for `i386'), will need to
 *   be accessed through use of `THIS_TRAMPOLINE'! */
FUNDEF NOBLOCK WUNUSED u8 NOTHROW(FCALL peekphysb)(physaddr_t addr);
FUNDEF NOBLOCK WUNUSED u16 NOTHROW(FCALL peekphysw)(/*aligned(2)*/ physaddr_t addr);
FUNDEF NOBLOCK WUNUSED u32 NOTHROW(FCALL peekphysl)(/*aligned(4)*/ physaddr_t addr);
FUNDEF NOBLOCK WUNUSED u16 NOTHROW(FCALL peekphysw_unaligned)(physaddr_t addr);
FUNDEF NOBLOCK WUNUSED u32 NOTHROW(FCALL peekphysl_unaligned)(physaddr_t addr);
FUNDEF NOBLOCK void NOTHROW(FCALL pokephysb)(physaddr_t addr, u8 value);
FUNDEF NOBLOCK void NOTHROW(FCALL pokephysw)(/*aligned(2)*/ physaddr_t addr, u16 value);
FUNDEF NOBLOCK void NOTHROW(FCALL pokephysl)(/*aligned(4)*/ physaddr_t addr, u32 value);
FUNDEF NOBLOCK void NOTHROW(FCALL pokephysw_unaligned)(physaddr_t addr, u16 value);
FUNDEF NOBLOCK void NOTHROW(FCALL pokephysl_unaligned)(physaddr_t addr, u32 value);
#ifdef __UINT64_TYPE__
FUNDEF NOBLOCK WUNUSED u64 NOTHROW(FCALL peekphysq)(/*aligned(8)*/ physaddr_t addr);
FUNDEF NOBLOCK WUNUSED u64 NOTHROW(FCALL peekphysq_unaligned)(physaddr_t addr);
FUNDEF NOBLOCK void NOTHROW(FCALL pokephysq)(/*aligned(8)*/ physaddr_t addr, u64 value);
FUNDEF NOBLOCK void NOTHROW(FCALL pokephysq_unaligned)(physaddr_t addr, u64 value);
#endif /* __UINT64_TYPE__ */

/* I/O functions with physical buffers. */
#ifdef __port_t
FUNDEF NOBLOCK void NOTHROW(KCALL insphysb)(port_t port, physaddr_t addr, size_t num_bytes);
FUNDEF NOBLOCK void NOTHROW(KCALL insphysw)(port_t port, /*aligned(2)*/ physaddr_t addr, size_t num_words);
FUNDEF NOBLOCK void NOTHROW(KCALL insphysl)(port_t port, /*aligned(4)*/ physaddr_t addr, size_t num_dwords);
FUNDEF NOBLOCK void NOTHROW(KCALL outsphysb)(port_t port, physaddr_t addr, size_t num_bytes);
FUNDEF NOBLOCK void NOTHROW(KCALL outsphysw)(port_t port, /*aligned(2)*/ physaddr_t addr, size_t num_words);
FUNDEF NOBLOCK void NOTHROW(KCALL outsphysl)(port_t port, /*aligned(4)*/ physaddr_t addr, size_t num_dwords);
#endif /* __port_t */

/* Copy memory to/from/within the physical address space. */
#ifdef __OMIT_PHYS_COPY_CONSTANT_P_WRAPPERS
FUNDEF void KCALL copyfromphys(NCX void *dst, physaddr_t src, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF void KCALL copytophys(physaddr_t dst, NCX void const *src, size_t num_bytes) THROWS(E_SEGFAULT);
#else /* __OMIT_PHYS_COPY_CONSTANT_P_WRAPPERS */
FUNDEF void KCALL __os_copyfromphys(NCX void *dst, physaddr_t src, size_t num_bytes) THROWS(E_SEGFAULT) ASMNAME("copyfromphys");
FUNDEF void KCALL __os_copytophys(physaddr_t dst, NCX void const *src, size_t num_bytes) THROWS(E_SEGFAULT) ASMNAME("copytophys");

FORCELOCAL ATTR_ARTIFICIAL void KCALL
copyfromphys(NCX void *dst,
             physaddr_t src,
             size_t num_bytes)
		THROWS(E_SEGFAULT) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes == 1) {
			__hybrid_unaligned_set8(dst, peekphysb(src));
			return;
		}
		if (num_bytes == 2) {
			__hybrid_unaligned_set16(dst, peekphysw(src));
			return;
		}
		if (num_bytes == 4) {
			__hybrid_unaligned_set32(dst, peekphysl(src));
			return;
		}
#ifdef __UINT64_TYPE__
		if (num_bytes == 8) {
			__hybrid_unaligned_set64(dst, peekphysq(src));
			return;
		}
#endif /* __UINT64_TYPE__ */
	}
	__os_copyfromphys(dst, src, num_bytes);
}

FORCELOCAL ATTR_ARTIFICIAL void KCALL
copytophys(physaddr_t dst,
           NCX void const *src,
           size_t num_bytes)
		THROWS(E_SEGFAULT) {
	if (__builtin_constant_p(num_bytes)) {
		if (num_bytes == 0)
			return;
		if (num_bytes == 1) {
			pokephysb(dst, __hybrid_unaligned_get8(src));
			return;
		}
		if (num_bytes == 2) {
			pokephysw(dst, __hybrid_unaligned_get16(src));
			return;
		}
		if (num_bytes == 4) {
			pokephysl(dst, __hybrid_unaligned_get32(src));
			return;
		}
#ifdef __UINT64_TYPE__
		if (num_bytes == 8) {
			pokephysq(dst, __hybrid_unaligned_get64(src));
			return;
		}
#endif /* __UINT64_TYPE__ */
	}
	__os_copytophys(dst, src, num_bytes);
}
#endif /* !__OMIT_PHYS_COPY_CONSTANT_P_WRAPPERS */

FUNDEF NOBLOCK void NOTHROW(KCALL copyinphys)(physaddr_t dst, physaddr_t src, size_t num_bytes);
FUNDEF NOBLOCK void NOTHROW(KCALL memsetphys)(physaddr_t dst, int byte, size_t num_bytes);
/* Same as `memsetphys(dst, 0, num_bytes)', but includes a special optimization
 * where it will skip whole  physical pages when `page_iszero()' returns  true. */
FUNDEF NOBLOCK void NOTHROW(KCALL bzerophyscc)(physaddr_t dst, size_t num_bytes);

/* no-#PF variants of `copy(from|to)phys()'.
 * @return: 0 : The copy operation completed without any problems.
 * @return: * : The number of bytes that could not be transferred.
 *              The affected memory range is:
 *               - `(dst|src) + num_bytes - return ... (dst|src) + num_bytes - 1' */
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL copyfromphys_nopf)(NCX void *dst, physaddr_t src, size_t num_bytes);
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL copytophys_nopf)(physaddr_t dst, NCX void const *src, size_t num_bytes);

/* Same as the functions above, however all memory accesses are guarantied to happen within the same page.
 * In other words: `(PHYS & ~PAGEMASK) == ((PHYS + num_bytes - 1) & ~PAGEMASK)' */
FUNDEF void KCALL copyfromphys_onepage(NCX void *dst, physaddr_t src, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF void KCALL copytophys_onepage(physaddr_t dst, NCX void const *src, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK void NOTHROW(KCALL copyinphys_onepage)(physaddr_t dst, physaddr_t src, size_t num_bytes);
FUNDEF NOBLOCK void NOTHROW(KCALL memsetphys_onepage)(physaddr_t dst, int byte, size_t num_bytes);
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL copyfromphys_onepage_nopf)(NCX void *dst, physaddr_t src, size_t num_bytes);
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL copytophys_onepage_nopf)(physaddr_t dst, NCX void const *src, size_t num_bytes);

/* Copy a whole page to/from physical memory. (s.a. `PAGESIZE') */
FUNDEF void KCALL copypagefromphys(NCX void *dst, PAGEDIR_PAGEALIGNED physaddr_t src) THROWS(E_SEGFAULT);
FUNDEF void KCALL copypagesfromphys(NCX void *dst, PAGEDIR_PAGEALIGNED physaddr_t src, PAGEDIR_PAGEALIGNED size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF void KCALL copypagetophys(PAGEDIR_PAGEALIGNED physaddr_t dst, NCX void const *src) THROWS(E_SEGFAULT);
FUNDEF void KCALL copypagestophys(PAGEDIR_PAGEALIGNED physaddr_t dst, NCX void const *src, PAGEDIR_PAGEALIGNED size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK void NOTHROW(KCALL copypageinphys)(PAGEDIR_PAGEALIGNED physaddr_t dst, PAGEDIR_PAGEALIGNED physaddr_t src);
FUNDEF NOBLOCK void NOTHROW(KCALL copypagesinphys)(PAGEDIR_PAGEALIGNED physaddr_t dst, PAGEDIR_PAGEALIGNED physaddr_t src, PAGEDIR_PAGEALIGNED size_t num_bytes);
FUNDEF NOBLOCK void NOTHROW(KCALL memsetphyspage)(PAGEDIR_PAGEALIGNED physaddr_t dst, int byte);
FUNDEF NOBLOCK void NOTHROW(KCALL memsetphyspages)(PAGEDIR_PAGEALIGNED physaddr_t dst, int byte, PAGEDIR_PAGEALIGNED size_t num_bytes);
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL copypagefromphys_nopf)(NCX void *dst, PAGEDIR_PAGEALIGNED physaddr_t src);
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL copypagesfromphys_nopf)(NCX void *dst, PAGEDIR_PAGEALIGNED physaddr_t src, PAGEDIR_PAGEALIGNED size_t num_bytes);
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL copypagetophys_nopf)(PAGEDIR_PAGEALIGNED physaddr_t dst, NCX void const *src);
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL copypagestophys_nopf)(PAGEDIR_PAGEALIGNED physaddr_t dst, NCX void const *src, PAGEDIR_PAGEALIGNED size_t num_bytes);
/************************************************************************/







/************************************************************************/
/* A single page of virtual memory in the kernel mman, that is  always
 * prepared for being used for whatever purposes a thread has in mind.
 * NOTE: This page is also used  by PAGEFAULTS, though it  will
 *       restore a previous mapping, if such a mapping existed.
 * NOTE: Because this page is unique for each thread, the user is  not
 *       required to acquire a lock to the kernel mman when wishing to
 *       map something at this location! */
DATDEF ATTR_PERTASK PAGEDIR_PAGEALIGNED byte_t *this_trampoline;
#define THIS_TRAMPOLINE PERTASK_GET(this_trampoline)

/* A mem-node used to describe a single, reserved page. */
DATDEF ATTR_PERTASK struct mnode const this_trampoline_node;
/************************************************************************/








/************************************************************************/
/* Helper for unifying `PHYS_IS_IDENTITY()' and `pagedir_push_mapone(THIS_TRAMPOLINE)' */
struct mptram {
	/* MemPhysTRAMpoline */
	pagedir_pushval_t mpt_pushval; /* The pushed value (or `PAGEDIR_PUSHVAL_INVALID' if nothing was pushed) */
};

#define MPTRAM_INIT       { PAGEDIR_PUSHVAL_INVALID }
#define mptram_init(self) ((self)->mpt_pushval = PAGEDIR_PUSHVAL_INVALID)
#ifdef __PAGEDIR_PUSHVAL_INVALID_IS_ZERO
#define mptram_cinit(self) __hybrid_assert((self)->mpt_pushval == 0)
#else /* __PAGEDIR_PUSHVAL_INVALID_IS_ZERO */
#define mptram_cinit(self) (__hybrid_assert((self)->mpt_pushval == 0), (self)->mpt_pushval = PAGEDIR_PUSHVAL_INVALID)
#endif /* !__PAGEDIR_PUSHVAL_INVALID_IS_ZERO */
#define mptram_fini(self)                           \
	((self)->mpt_pushval == PAGEDIR_PUSHVAL_INVALID \
	 ? (void)0                                      \
	 : pagedir_pop_mapone(THIS_TRAMPOLINE, (self)->mpt_pushval))


LOCAL NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) byte_t *
NOTHROW(FCALL mptram_mappage_noidentity)(struct mptram *__restrict self,
                                         physpage_t page) {
	byte_t *tramp = THIS_TRAMPOLINE;
	if (self->mpt_pushval == PAGEDIR_PUSHVAL_INVALID) {
		self->mpt_pushval = pagedir_push_mapone(tramp, physpage2addr(page),
		                                        PAGEDIR_PROT_READ |
		                                        PAGEDIR_PROT_WRITE);
	} else {
		pagedir_mapone(tramp, physpage2addr(page),
		               PAGEDIR_PROT_READ |
		               PAGEDIR_PROT_WRITE);
	}
	pagedir_syncone(tramp);
	return tramp;
}

/* Return a (possibly temporary) virtual memory mapping of `page' */
#ifndef NO_PHYS_IDENTITY
LOCAL NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) byte_t *
NOTHROW(KCALL mptram_mappage)(struct mptram *__restrict self,
                              physpage_t page) {
	if (PHYS_IS_IDENTITY_PAGE(page))
		return PHYS_TO_IDENTITY_PAGE(page);
	return mptram_mappage_noidentity(self, page);
}
#else /* !NO_PHYS_IDENTITY */
#define mptram_mappage mptram_mappage_noidentity
#endif /* NO_PHYS_IDENTITY */

LOCAL NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) byte_t *
NOTHROW(KCALL mptram_map)(struct mptram *__restrict self, physaddr_t addr) {
	byte_t *result;
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(addr, 1))
		return PHYS_TO_IDENTITY(addr);
#endif /* !NO_PHYS_IDENTITY */
	result = mptram_mappage_noidentity(self, physaddr2page(addr));
	result += (uintptr_t)(addr & PAGEMASK);
	return result;
}

#ifndef NO_PHYS_IDENTITY
LOCAL NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) byte_t *
NOTHROW(KCALL mptram_map_noidentity)(struct mptram *__restrict self,
                                     physaddr_t addr) {
	byte_t *result;
	result = mptram_mappage_noidentity(self, physaddr2page(addr));
	result += (uintptr_t)(addr & PAGEMASK);
	return result;
}
#else /* !NO_PHYS_IDENTITY */
#define mptram_map_noidentity(...) mptram_map(__VA_ARGS__)
#endif /* NO_PHYS_IDENTITY */
/************************************************************************/

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_PHYS_H */
