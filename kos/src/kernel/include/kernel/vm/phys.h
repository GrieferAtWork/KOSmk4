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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_VM_PHYS_H
#define GUARD_KERNEL_INCLUDE_KERNEL_VM_PHYS_H 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_VM
#include <kernel/mman/phys.h>

#define vm_readphysb(addr)                   peekphysb(addr)
#define vm_readphysw(addr)                   peekphysw(addr)
#define vm_readphysl(addr)                   peekphysl(addr)
#define vm_readphysw_unaligned(addr)         peekphysw_unaligned(addr)
#define vm_readphysl_unaligned(addr)         peekphysl_unaligned(addr)
#define vm_writephysb(addr, value)           pokephysb(addr, value)
#define vm_writephysw(addr, value)           pokephysw(addr, value)
#define vm_writephysl(addr, value)           pokephysl(addr, value)
#define vm_writephysw_unaligned(addr, value) pokephysw_unaligned(addr, value)
#define vm_writephysl_unaligned(addr, value) pokephysl_unaligned(addr, value)
#ifdef __UINT64_TYPE__
#define vm_readphysq(addr)                   peekphysq(addr)
#define vm_readphysq_unaligned(addr)         peekphysq_unaligned(addr)
#define vm_writephysq(addr, value)           pokephysq(addr, value)
#define vm_writephysq_unaligned(addr, value) pokephysq_unaligned(addr, value)
#endif /* __UINT64_TYPE__ */
#define vm_insb_phys(port, buf, num_bytes)                insphysb(port, buf, num_bytes)
#define vm_insw_phys(port, buf, num_words)                insphysw(port, buf, num_words)
#define vm_insl_phys(port, buf, num_dwords)               insphysl(port, buf, num_dwords)
#define vm_outsb_phys(port, buf, num_bytes)               outsphysb(port, buf, num_bytes)
#define vm_outsw_phys(port, buf, num_words)               outsphysw(port, buf, num_words)
#define vm_outsl_phys(port, buf, num_dwords)              outsphysl(port, buf, num_dwords)
#define vm_copyfromphys(dst, src, num_bytes)              copyfromphys(dst, src, num_bytes)
#define vm_copytophys(dst, src, num_bytes)                copytophys(dst, src, num_bytes)
#define vm_copyinphys(dst, src, num_bytes)                copyinphys(dst, src, num_bytes)
#define vm_memsetphys(dst, byte, num_bytes)               memsetphys(dst, byte, num_bytes)
#define vm_copyfromphys_nopf(dst, src, num_bytes)         copyfromphys_nopf(dst, src, num_bytes)
#define vm_copytophys_nopf(dst, src, num_bytes)           copytophys_nopf(dst, src, num_bytes)
#define vm_copyfromphys_onepage(dst, src, num_bytes)      copyfromphys_onepage(dst, src, num_bytes)
#define vm_copytophys_onepage(dst, src, num_bytes)        copytophys_onepage(dst, src, num_bytes)
#define vm_copyinphys_onepage(dst, src, num_bytes)        copyinphys_onepage(dst, src, num_bytes)
#define vm_memsetphys_onepage(dst, byte, num_bytes)       memsetphys_onepage(dst, byte, num_bytes)
#define vm_copyfromphys_onepage_nopf(dst, src, num_bytes) copyfromphys_onepage_nopf(dst, src, num_bytes)
#define vm_copytophys_onepage_nopf(dst, src, num_bytes)   copytophys_onepage_nopf(dst, src, num_bytes)
#define vm_copypagefromphys(dst, src)                     copypagefromphys(dst, src)
#define vm_copypagetophys(dst, src)                       copypagetophys(dst, src)
#define vm_copypageinphys(dst, src)                       copypageinphys(dst, src)
#define vm_copypagesinphys(dst, src, num_pages)           copypagesinphys(dst, src, (num_pages) * PAGESIZE)
#define vm_memsetphyspage(dst, byte)                      memsetphyspage(dst, byte)
#define vm_memsetphyspages(dst, byte, num_pages)          memsetphyspages(dst, byte, (num_pages) * PAGESIZE)
#define vm_copypagefromphys_nopf(dst, src)                copypagefromphys_nopf(dst, src)
#define vm_copypagetophys_nopf(dst, src)                  copypagetophys_nopf(dst, src)
#define vm_ptram                                          mptram
#define pt_pushval                                        mpt_pushval
#define VM_PTRAM_INIT                                     MPTRAM_INIT
#define vm_ptram_init(self)                               mptram_init(self)
#define vm_ptram_cinit(self)                              mptram_cinit(self)
#define vm_ptram_fini(self)                               mptram_fini(self)
#define vm_ptram_mappage_noidentity(self, page, ...)      mptram_mappage_noidentity(self, page)
#define vm_ptram_mappage(self, page, ...)                 mptram_mappage(self, page)
#define vm_ptram_map_noidentity(self, addr, ...)          mptram_map_noidentity(self, addr)
#define vm_ptram_map(self, addr, ...)                     mptram_map(self, addr)

#else /* CONFIG_USE_NEW_VM */

/* Forward-compatibility. */
#define peekphysb(addr)                      vm_readphysb(addr)
#define peekphysw(addr)                      vm_readphysw(addr)
#define peekphysl(addr)                      vm_readphysl(addr)
#define peekphysw_unaligned(addr)            vm_readphysw_unaligned(addr)
#define peekphysl_unaligned(addr)            vm_readphysl_unaligned(addr)
#define pokephysb(addr, value)               vm_writephysb(addr, value)
#define pokephysw(addr, value)               vm_writephysw(addr, value)
#define pokephysl(addr, value)               vm_writephysl(addr, value)
#define pokephysw_unaligned(addr, value)     vm_writephysw_unaligned(addr, value)
#define pokephysl_unaligned(addr, value)     vm_writephysl_unaligned(addr, value)
#ifdef __UINT64_TYPE__
#define peekphysq(addr)                  vm_readphysq(addr)
#define peekphysq_unaligned(addr)        vm_readphysq_unaligned(addr)
#define pokephysq(addr, value)           vm_writephysq(addr, value)
#define pokephysq_unaligned(addr, value) vm_writephysq_unaligned(addr, value)
#endif /* __UINT64_TYPE__ */
#define insphysb(port, buf, num_bytes)                 vm_insb_phys(port, buf, num_bytes)
#define insphysw(port, buf, num_words)                 vm_insw_phys(port, buf, num_words)
#define insphysl(port, buf, num_dwords)                vm_insl_phys(port, buf, num_dwords)
#define outsphysb(port, buf, num_bytes)                vm_outsb_phys(port, buf, num_bytes)
#define outsphysw(port, buf, num_words)                vm_outsw_phys(port, buf, num_words)
#define outsphysl(port, buf, num_dwords)               vm_outsl_phys(port, buf, num_dwords)
#define copyfromphys(dst, src, num_bytes)              vm_copyfromphys(dst, src, num_bytes)
#define copytophys(dst, src, num_bytes)                vm_copytophys(dst, src, num_bytes)
#define copyinphys(dst, src, num_bytes)                vm_copyinphys(dst, src, num_bytes)
#define memsetphys(dst, byte, num_bytes)               vm_memsetphys(dst, byte, num_bytes)
#define copyfromphys_nopf(dst, src, num_bytes)         vm_copyfromphys_nopf(dst, src, num_bytes)
#define copytophys_nopf(dst, src, num_bytes)           vm_copytophys_nopf(dst, src, num_bytes)
#define copyfromphys_onepage(dst, src, num_bytes)      vm_copyfromphys_onepage(dst, src, num_bytes)
#define copytophys_onepage(dst, src, num_bytes)        vm_copytophys_onepage(dst, src, num_bytes)
#define copyinphys_onepage(dst, src, num_bytes)        vm_copyinphys_onepage(dst, src, num_bytes)
#define memsetphys_onepage(dst, byte, num_bytes)       vm_memsetphys_onepage(dst, byte, num_bytes)
#define copyfromphys_onepage_nopf(dst, src, num_bytes) vm_copyfromphys_onepage_nopf(dst, src, num_bytes)
#define copytophys_onepage_nopf(dst, src, num_bytes)   vm_copytophys_onepage_nopf(dst, src, num_bytes)
#define copypagefromphys(dst, src)                     vm_copypagefromphys(dst, src)
#define copypagetophys(dst, src)                       vm_copypagetophys(dst, src)
#define copypageinphys(dst, src)                       vm_copypageinphys(dst, src)
#define copypagesinphys(dst, src, num_bytes)           vm_copypagesinphys(dst, src, (num_bytes) / PAGESIZE)
#define memsetphyspage(dst, byte)                      vm_memsetphyspage(dst, byte)
#define memsetphyspages(dst, byte, num_bytes)          vm_memsetphyspages(dst, byte, (num_bytes) / PAGESIZE)
#define copypagefromphys_nopf(dst, src)                vm_copypagefromphys_nopf(dst, src)
#define copypagetophys_nopf(dst, src)                  vm_copypagetophys_nopf(dst, src)
#define mptram                                         vm_ptram
#define mpt_pushval                                    pt_pushval
#define MPTRAM_INIT                                    VM_PTRAM_INIT
#define mptram_init(self)                              vm_ptram_init(self)
#define mptram_cinit(self)                             vm_ptram_cinit(self)
#define mptram_fini(self)                              vm_ptram_fini(self)
#define mptram_mappage_noidentity(self, page)          vm_ptram_mappage_noidentity(self, page)
#define mptram_mappage(self, page)                     vm_ptram_mappage(self, page)
#define mptram_map_noidentity(self, addr)              vm_ptram_map_noidentity(self, addr)
#define mptram_map(self, addr)                         vm_ptram_map(self, addr)


#include <kernel/arch/paging.h> /* `pagedir_pushval_t' */
#include <kernel/memory.h>      /* physpage2addr() */
#include <kernel/paging.h>      /* `pagedir_push_mapone()' */
#include <kernel/types.h>
#include <sched/pertask.h> /* PERTASK_GET() */

#include <hybrid/__assert.h>
#include <hybrid/__unaligned.h>
#include <hybrid/typecore.h>

#include <asm/pageid.h>        /* __ARCH_PAGEID_TYPE */
#include <kos/kernel/paging.h> /* `PHYS_IS_IDENTITY()' */

/* Helper functions for accessing physical memory */

DECL_BEGIN

#ifndef PHYS_IS_IDENTITY
#define NO_PHYS_IDENTITY 1
#define PHYS_IS_IDENTITY(addr, num_bytes) 0
#define PHYS_TO_IDENTITY(addr) (void *)0
#endif /* !PHYS_IS_IDENTITY */

#ifndef PHYS_IS_IDENTITY_PAGE
#define PHYS_IS_IDENTITY_PAGE(pageno) PHYS_IS_IDENTITY(physpage2addr(pageno), PAGESIZE)
#define PHYS_TO_IDENTITY_PAGE(addr)   PHYS_TO_IDENTITY(physpage2addr(pageno))
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
 *          either  make  use   of  `vm_copy(from|to)phys()'  or   `THIS_TRAMPOLINE_PAGE'.
 *          These functions will try to make use arch-specific physical identity mappings,
 *          like can  be  found  on  `x86_64'  for the  first  1Gib  of  physical  memory.
 *          However  any  memory outside  that region  (or any  memory at  all if  no such
 *          region is  defined by  the arch  (as is  the case  for `i386'),  will need  to
 *          be accessed through use of `THIS_TRAMPOLINE_PAGE'!) */
FUNDEF NOBLOCK WUNUSED u8 NOTHROW(KCALL vm_readphysb)(PHYS physaddr_t addr);
FUNDEF NOBLOCK WUNUSED u16 NOTHROW(KCALL vm_readphysw)(/*aligned(2)*/ PHYS physaddr_t addr);
FUNDEF NOBLOCK WUNUSED u32 NOTHROW(KCALL vm_readphysl)(/*aligned(4)*/ PHYS physaddr_t addr);
FUNDEF NOBLOCK WUNUSED u16 NOTHROW(KCALL vm_readphysw_unaligned)(PHYS physaddr_t addr);
FUNDEF NOBLOCK WUNUSED u32 NOTHROW(KCALL vm_readphysl_unaligned)(PHYS physaddr_t addr);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_writephysb)(PHYS physaddr_t addr, u8 value);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_writephysw)(/*aligned(2)*/ PHYS physaddr_t addr, u16 value);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_writephysl)(/*aligned(4)*/ PHYS physaddr_t addr, u32 value);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_writephysw_unaligned)(PHYS physaddr_t addr, u16 value);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_writephysl_unaligned)(PHYS physaddr_t addr, u32 value);
#ifdef __UINT64_TYPE__
FUNDEF NOBLOCK WUNUSED u64 NOTHROW(KCALL vm_readphysq)(/*aligned(8)*/ PHYS physaddr_t addr);
FUNDEF NOBLOCK WUNUSED u64 NOTHROW(KCALL vm_readphysq_unaligned)(PHYS physaddr_t addr);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_writephysq)(/*aligned(8)*/ PHYS physaddr_t addr, u64 value);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_writephysq_unaligned)(PHYS physaddr_t addr, u64 value);
#endif /* __UINT64_TYPE__ */

/* I/O functions with physical buffers. */
FUNDEF NOBLOCK void NOTHROW(KCALL vm_insb_phys)(port_t port, PHYS physaddr_t buf, size_t num_bytes);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_insw_phys)(port_t port, PHYS physaddr_t buf, size_t num_words);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_insl_phys)(port_t port, PHYS physaddr_t buf, size_t num_dwords);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_outsb_phys)(port_t port, PHYS physaddr_t buf, size_t num_bytes);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_outsw_phys)(port_t port, PHYS physaddr_t buf, size_t num_words);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_outsl_phys)(port_t port, PHYS physaddr_t buf, size_t num_dwords);


/* Copy memory to/from the physical address space. */
#ifdef __OMIT_PHYS_COPY_CONSTANT_P_WRAPPERS
FUNDEF void KCALL vm_copyfromphys(USER CHECKED void *dst, PHYS physaddr_t src, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF void KCALL vm_copytophys(PHYS physaddr_t dst, USER CHECKED void const *src, size_t num_bytes) THROWS(E_SEGFAULT);
#else /* __OMIT_PHYS_COPY_CONSTANT_P_WRAPPERS */
FUNDEF void KCALL __os_vm_copyfromphys(USER CHECKED void *dst, PHYS physaddr_t src, size_t num_bytes) THROWS(E_SEGFAULT) ASMNAME("vm_copyfromphys");
FUNDEF void KCALL __os_vm_copytophys(PHYS physaddr_t dst, USER CHECKED void const *src, size_t num_bytes) THROWS(E_SEGFAULT) ASMNAME("vm_copytophys");

FORCELOCAL ATTR_ARTIFICIAL void KCALL
vm_copyfromphys(USER CHECKED void *dst,
                PHYS physaddr_t src,
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

FORCELOCAL ATTR_ARTIFICIAL void KCALL
vm_copytophys(PHYS physaddr_t dst,
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

FUNDEF NOBLOCK void NOTHROW(KCALL vm_copyinphys)(PHYS physaddr_t dst, PHYS physaddr_t src, size_t num_bytes);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_memsetphys)(PHYS physaddr_t dst, int byte, size_t num_bytes);




/* no-#PF variants of `vm_copy(from|to)phys()'.
 * @return: 0 : The copy operation completed without any problems.
 * @return: * : The number of bytes that could not be transfered.
 *              The affected memory range is:
 *               - `(dst|src) + num_bytes - return ... (dst|src) + num_bytes - 1' */
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL vm_copyfromphys_nopf)(USER CHECKED void *dst, PHYS physaddr_t src, size_t num_bytes);
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL vm_copytophys_nopf)(PHYS physaddr_t dst, USER CHECKED void const *src, size_t num_bytes);

/* Same as the functions above, however all memory accesses are guarantied to happen within the same page.
 * In other words: `(PHYS & ~PAGEMASK) == ((PHYS + num_bytes - 1) & ~PAGEMASK)' */
FUNDEF void KCALL vm_copyfromphys_onepage(USER CHECKED void *dst, PHYS physaddr_t src, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF void KCALL vm_copytophys_onepage(PHYS physaddr_t dst, USER CHECKED void const *src, size_t num_bytes) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_copyinphys_onepage)(PHYS physaddr_t dst, PHYS physaddr_t src, size_t num_bytes);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_memsetphys_onepage)(PHYS physaddr_t dst, int byte, size_t num_bytes);
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL vm_copyfromphys_onepage_nopf)(USER CHECKED void *dst, PHYS physaddr_t src, size_t num_bytes);
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL vm_copytophys_onepage_nopf)(PHYS physaddr_t dst, USER CHECKED void const *src, size_t num_bytes);

/* Copy a whole page to/from physical memory. (s.a. `PAGESIZE') */
FUNDEF void KCALL vm_copypagefromphys(USER CHECKED void *dst, PAGEDIR_PAGEALIGNED PHYS physaddr_t src) THROWS(E_SEGFAULT);
FUNDEF void KCALL vm_copypagetophys(PAGEDIR_PAGEALIGNED PHYS physaddr_t dst, USER CHECKED void const *src) THROWS(E_SEGFAULT);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_copypageinphys)(PAGEDIR_PAGEALIGNED PHYS physaddr_t dst, PAGEDIR_PAGEALIGNED PHYS physaddr_t src);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_copypagesinphys)(PAGEDIR_PAGEALIGNED PHYS physaddr_t dst, PAGEDIR_PAGEALIGNED PHYS physaddr_t src, size_t num_pages);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_memsetphyspage)(PAGEDIR_PAGEALIGNED PHYS physaddr_t dst, int byte);
FUNDEF NOBLOCK void NOTHROW(KCALL vm_memsetphyspages)(PAGEDIR_PAGEALIGNED PHYS physaddr_t dst, int byte, size_t num_pages);
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL vm_copypagefromphys_nopf)(USER CHECKED void *dst, PAGEDIR_PAGEALIGNED PHYS physaddr_t src);
FUNDEF NOBLOCK WUNUSED size_t NOTHROW(KCALL vm_copypagetophys_nopf)(PAGEDIR_PAGEALIGNED PHYS physaddr_t dst, USER CHECKED void const *src);

/* A single page of  virtual memory in the  kernel VM, that is  always
 * prepared for being used for whatever purposes a thread has in mind.
 * NOTE: This page is also used  by PAGEFAULTS, though it  will
 *       restore a previous mapping, if such a mapping existed.
 * NOTE: Because this page is unique for each thread, the user is not
 *       required to acquire a lock to the kernel VM when wishing  to
 *       map something at this location! */
DATDEF ATTR_PERTASK __ARCH_PAGEID_TYPE this_trampoline_page;

/* TODO: Go through all uses of `THIS_TRAMPOLINE_PAGE' and add
 *       optimizations  for  supporting   `PHYS_IS_IDENTITY()' */
#define THIS_TRAMPOLINE_PAGE PERTASK_GET(this_trampoline_page)
#ifdef __ARCH_PAGEID_DECODE_KERNEL
#define THIS_TRAMPOLINE ((byte_t *)__ARCH_PAGEID_DECODE_KERNEL(THIS_TRAMPOLINE_PAGE))
#else /* __ARCH_PAGEID_DECODE_KERNEL */
#define THIS_TRAMPOLINE ((byte_t *)__ARCH_PAGEID_DECODE(THIS_TRAMPOLINE_PAGE))
#endif /* !__ARCH_PAGEID_DECODE_KERNEL */

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
#define vm_ptram_fini(self)                        \
	((self)->pt_pushval == PAGEDIR_PUSHVAL_INVALID \
	 ? (void)0                                     \
	 : pagedir_pop_mapone(THIS_TRAMPOLINE, (self)->pt_pushval))

LOCAL NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) byte_t *
NOTHROW(KCALL vm_ptram_mappage_noidentity)(struct vm_ptram *__restrict self,
                                           physpage_t page, __BOOL writable DFL(true)) {
	byte_t *tramp;
	tramp = THIS_TRAMPOLINE;
	if (self->pt_pushval == PAGEDIR_PUSHVAL_INVALID) {
		self->pt_pushval = pagedir_push_mapone(tramp, physpage2addr(page),
		                                       writable ? PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE
		                                                : PAGEDIR_MAP_FREAD);
	} else {
		pagedir_mapone(tramp, physpage2addr(page),
		               writable ? PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE
		                        : PAGEDIR_MAP_FREAD);
	}
	pagedir_syncone(tramp);
	return tramp;
}

/* Return a (possibly temporary) virtual memory mapping of `page' */
#ifndef NO_PHYS_IDENTITY
LOCAL NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) byte_t *
NOTHROW(KCALL vm_ptram_mappage)(struct vm_ptram *__restrict self,
                                physpage_t page, __BOOL writable DFL(true)) {
	if (PHYS_IS_IDENTITY_PAGE(page))
		return (byte_t *)PHYS_TO_IDENTITY_PAGE(page);
	return vm_ptram_mappage_noidentity(self, page, writable);
}
#else /* !NO_PHYS_IDENTITY */
#define vm_ptram_mappage vm_ptram_mappage_noidentity
#endif /* NO_PHYS_IDENTITY */

LOCAL NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) byte_t *
NOTHROW(KCALL vm_ptram_map)(struct vm_ptram *__restrict self,
                            physaddr_t addr, __BOOL writable DFL(true)) {
	byte_t *result;
#ifndef NO_PHYS_IDENTITY
	if (PHYS_IS_IDENTITY(addr, 1))
		return (byte_t *)PHYS_TO_IDENTITY(addr);
#endif /* !NO_PHYS_IDENTITY */
	result = vm_ptram_mappage_noidentity(self, physaddr2page(addr), writable);
	result += (uintptr_t)(addr & PAGEMASK);
	return result;
}

#ifndef NO_PHYS_IDENTITY
LOCAL NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) byte_t *
NOTHROW(KCALL vm_ptram_map_noidentity)(struct vm_ptram *__restrict self,
                                       physaddr_t addr, __BOOL writable DFL(true)) {
	byte_t *result;
	result = vm_ptram_mappage_noidentity(self, physaddr2page(addr), writable);
	result += (uintptr_t)(addr & PAGEMASK);
	return result;
}
#else /* !NO_PHYS_IDENTITY */
#define vm_ptram_map_noidentity(...) vm_ptram_map(__VA_ARGS__)
#endif /* NO_PHYS_IDENTITY */

#endif /* __CC__ */

DECL_END
#endif /* !CONFIG_USE_NEW_VM */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_VM_PHYS_H */
