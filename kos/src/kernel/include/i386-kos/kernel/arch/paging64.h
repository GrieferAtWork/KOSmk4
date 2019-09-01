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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_PAGING64_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_PAGING64_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <kos/kernel/paging.h>

#include <stdbool.h>

#ifdef __cplusplus
#include <__stdcxx.h>
#endif /* __cplusplus */

#undef CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
#define CONFIG_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE 1

#undef CONFIG_PAGEDIR_INIT_NEED_PHYS_SELF
#define CONFIG_PAGEDIR_INIT_NEED_PHYS_SELF 1

#undef CONFIG_PAGEDIR_FINI_NEED_PHYS_SELF
#define CONFIG_PAGEDIR_FINI_NEED_PHYS_SELF 1


DECL_BEGIN

/* Implementation of 4-level paging (s.a. `Table 4-1.  Properties of Different Paging Modes')
 * The best overview of this can be found in:
 *     `Figure 4-11.  Formats of CR3 and Paging-Structure Entries with 4-Level Paging'
 */



/* To differentiate between hints and allocated, but non-present pages, we use this:
 *                                                                  X86_PAGE_FPRESENT
 *                                                                  |
 * E XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX1: Page:  4KiB-page (X86_PAGE_FADDR_4KIB)
 * 1 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX0: Hint:  DATA & X86_PAGE_FHINT
 *   0000000000000000000000000000000000000000000000000000000000000000: Unused (X86_PAGE_ABSENT)
 *    6 6 5 5 5 5 5 4 4 4 4 4 3 3 3 3 3 2 2 2 2 2 1 1 1 1 1 8 6 4 2 0
 *    2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0
 *
 *                                                           X86_PAGE_F2MIB
 *                                                           |
 *                                                           |      X86_PAGE_FPRESENT
 *                                                           |      |
 * E XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXXXX1: Page:  Large page mapping X86_PAGE_FADDR_2MIB
 * 2 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX0XXXXXX1: Owned: page_freeone(DATA & X86_PAGE_FVECTOR) (present)
 *   XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX0: Owned: page_freeone(DATA & X86_PAGE_FVECTOR) (Pre-allocated)
 *   0000000000000000000000000000000000000000000000000000000000000000: Unused (X86_PAGE_ABSENT)
 *    6 6 5 5 5 5 5 4 4 4 4 4 3 3 3 3 3 2 2 2 2 2 1 1 1 1 1 8 6 4 2 0
 *    2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0
 *
 *                                                           X86_PAGE_F1GIB
 *                                                           |
 *                                                           |      X86_PAGE_FPRESENT
 *                                                           |      |
 * E XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXXXX1: Page:  Large page mapping X86_PAGE_FADDR_1GIB
 * 3 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX0XXXXXX1: Owned: page_freeone(DATA & X86_PAGE_FVECTOR) (present)
 *   XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX0: Owned: page_freeone(DATA & X86_PAGE_FVECTOR) (Pre-allocated)
 *   0000000000000000000000000000000000000000000000000000000000000000: Unused (X86_PAGE_ABSENT)
 *    6 6 5 5 5 5 5 4 4 4 4 4 3 3 3 3 3 2 2 2 2 2 1 1 1 1 1 8 6 4 2 0
 *    2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0
 *
 *                                                                  X86_PAGE_FPRESENT
 *                                                                  |
 * E XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX1: Owned: page_freeone(DATA & X86_PAGE_FVECTOR) (present)
 * 4 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX0: Unused (X86_PAGE_ABSENT)
 *    6 6 5 5 5 5 5 4 4 4 4 4 3 3 3 3 3 2 2 2 2 2 1 1 1 1 1 8 6 4 2 0
 *    2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0
 *
 * NOTE: In the case of E4, you may assume that any address with `X86_PDIR_VEC4INDEX(addr) >= 256'
 *       always has the `X86_PAGE_FPRESENT' bit set, and that it points to a statically allocated
 *       block of `union x86_pdir_e3[512]' that are shared between all page directories.
 */

/* The minimum alignment required for pointers passed to `pagedir_maphint()' */
#define PAGEDIR_MAPHINT_ALIGNMENT  2


#define X86_PAGE_SHIFT      12 /* Shift to convert between pages and addresses. */
#define X86_PAGE_ALIGN      __UINT64_C(0x0000000000001000) /* Required page alignment. */
#define X86_PAGE_SIZE       __UINT64_C(0x0000000000001000) /* Required page size. */
#define X86_PAGE_FVECTOR    __UINT64_C(0x000ffffffffff000) /* [bit(12:51)] Mask of an inner vector. */
#define X86_PAGE_FHINT      __UINT64_C(0xfffffffffffffffe) /* Mask of page hints. */
#define X86_PAGE_FADDR_4KIB __UINT64_C(0x000ffffffffff000) /* Mask of the page address for 1KiB pages. */
#define X86_PAGE_OFFST_4KIB __UINT64_C(0x0000000000000fff) /* Offset mask for 1KiB pages. */
#define X86_PAGE_FADDR_2MIB __UINT64_C(0x000fffffffe00000) /* Mask of the page address for 2MiB pages. */
#define X86_PAGE_OFFST_2MIB __UINT64_C(0x00000000001fffff) /* Offset mask for 2MiB pages. */
#define X86_PAGE_FADDR_1GIB __UINT64_C(0x000fffffc0000000) /* Mask of the page address for 1GiB pages. */
#define X86_PAGE_OFFST_1GIB __UINT64_C(0x000000003fffffff) /* Offset mask for 1GiB pages. */
#define X86_PAGE_FMASK      __UINT64_C(0xfff0000000000fff) /* Mask of page flag bits. */
#define X86_PAGE_FPROTKEY   __UINT64_C(0x7000000000000000) /* Mask for the protection key. */
#define X86_PAGE_ABSENT     __UINT64_C(0x0000000000000000) /* Value found in any TIER _EXCEPT_ TIER#1 to indicate that a vector hasn't been allocated. */

#define X86_PAGE_FPRESENT   __UINT64_C(0x0000000000000001) /* [bit(0)] The page is present (When not set, cause a PAGEFAULT that may be used for allocate/load-on-read). */
#define X86_PAGE_FWRITE     __UINT64_C(0x0000000000000002) /* [bit(1)] The page is writable. */
#define X86_PAGE_FUSER      __UINT64_C(0x0000000000000004) /* [bit(2)] User-space may access this page (read, or write). */
#define X86_PAGE_FPWT       __UINT64_C(0x0000000000000008) /* [bit(3)] Page-level write-through. */
#define X86_PAGE_FPCD       __UINT64_C(0x0000000000000010) /* [bit(4)] Page-level cache disable. */
#define X86_PAGE_FACCESSED  __UINT64_C(0x0000000000000020) /* [bit(5)] The page has been read from, or written to. */
#define X86_PAGE_FDIRTY     __UINT64_C(0x0000000000000040) /* [bit(6)] The page has been written to. (only valid in entries that map physical memory, rather than point to other vectors) */
#define X86_PAGE_F2MIB      __UINT64_C(0x0000000000000080) /* [bit(7)] Directly map a physical address on level #2 (for use in `union x86_pdir_e2::p_word'). */
#define X86_PAGE_F1GIB      __UINT64_C(0x0000000000000080) /* [bit(7)] Directly map a physical address on level #3 (for use in `union x86_pdir_e3::p_word'). */
#define X86_PAGE_FGLOBAL    __UINT64_C(0x0000000000000100) /* [bit(8)] Set to optimize mappings that appear at the same location in all
                                                            *          directories it appears inside of (aka: Kernel-allocated stack/memory). */
#define X86_PAGE_FPAT_4KIB  __UINT64_C(0x0000000000000080) /* [bit(7)]  Indirectly determines the memory type used to access the 4-KByte page referenced by this entry. */
#define X86_PAGE_FPAT_2MIB  __UINT64_C(0x0000000000001000) /* [bit(12)] Indirectly determines the memory type used to access the 2-MByte page referenced by this entry. */
#define X86_PAGE_FPAT_1GIB  __UINT64_C(0x0000000000001000) /* [bit(12)] Indirectly determines the memory type used to access the 1-GByte page referenced by this entry. */
#define X86_PAGE_FNOEXEC    __UINT64_C(0x8000000000000000) /* [bit(63)] Memory within the page cannot be executed. */


#define X86_PDIR_VEC1INDEX(ptr)  ((__CCAST(u64)(ptr) >> 12) & 0x1ff) /* For `union x86_pdir_e2::p_e1' */
#define X86_PDIR_VEC2INDEX(ptr)  ((__CCAST(u64)(ptr) >> 21) & 0x1ff) /* For `union x86_pdir_e3::p_e2' */
#define X86_PDIR_VEC3INDEX(ptr)  ((__CCAST(u64)(ptr) >> 30) & 0x1ff) /* For `union x86_pdir_e4::p_e3' */
#define X86_PDIR_VEC4INDEX(ptr)  ((__CCAST(u64)(ptr) >> 39) & 0x1ff) /* For `struct x86_pdir::p_e4' */

#define X86_PDIR_VEC1INDEX_VPAGE(vpage)   (__CCAST(u64)(vpage) & 0x1ff)        /* For `union x86_pdir_e2::p_e1' */
#define X86_PDIR_VEC2INDEX_VPAGE(vpage)  ((__CCAST(u64)(vpage) >> 9) & 0x1ff)  /* For `union x86_pdir_e3::p_e2' */
#define X86_PDIR_VEC3INDEX_VPAGE(vpage)  ((__CCAST(u64)(vpage) >> 18) & 0x1ff) /* For `union x86_pdir_e4::p_e3' */
#define X86_PDIR_VEC4INDEX_VPAGE(vpage)  ((__CCAST(u64)(vpage) >> 27) & 0x1ff) /* For `struct x86_pdir::p_e4' */

/* Pagesizes of different page directory levels. */
#define X86_PDIR_E1_SIZE     __UINT64_C(0x0000000000001000) /* 4 KiB (Same as `PAGESIZE') */
#define X86_PDIR_E2_SIZE     __UINT64_C(0x0000000000200000) /* 2 MiB */
#define X86_PDIR_E3_SIZE     __UINT64_C(0x0000000040000000) /* 1 GiB */
#define X86_PDIR_E4_SIZE     __UINT64_C(0x0000008000000000) /* 512 GiB */

#define X86_PDIR_ALIGN  4096 /* Alignment required for instances of `struct x86_pdir' */
#define X86_PDIR_SIZE   4096 /* The total size of `struct x86_pdir' in bytes. */


#ifdef __CC__
union x86_pdir_e1 {
	/* Lowest-level page-directory entry:
	 *   - 4-Level Page-Table Entry that Maps a 4-KByte Page */
	u64                      p_word;     /* Mapping data. */
	PHYS u64                 p_addr;     /* [MASK(X86_PAGE_FADDR_4KIB)]
	                                      * [valid_if(X86_PDIR_E1_IS1KIB(p_word))]
	                                      * _Physical_ page address. */
#define X86_PDIR_E1_IS1KIB(e1_word)    ((e1_word) & X86_PAGE_FPRESENT)
#define X86_PDIR_E1_ISHINT(e1_word)    (!((e1_word) & X86_PAGE_FPRESENT) && (e1_word) != X86_PAGE_ABSENT)
#define X86_PDIR_E1_ISUNUSED(e1_word)  ((e1_word) == X86_PAGE_ABSENT)
	struct {
		u64          d_present : 1;      /* X86_PAGE_FPRESENT */
		u64          d_writable : 1;     /* [valid_if(d_present)] X86_PAGE_FWRITE */
		u64          d_user : 1;         /* [valid_if(d_present)] X86_PAGE_FUSER */
		u64          d_pwt : 1;          /* [valid_if(d_present)] X86_PAGE_FPWT */
		u64          d_pcd : 1;          /* [valid_if(d_present)] X86_PAGE_FPCD */
		u64          d_accessed : 1;     /* [valid_if(d_present)] X86_PAGE_FACCESSED */
		u64          d_dirty : 1;        /* [valid_if(d_present)] X86_PAGE_FDIRTY */
		u64          d_pat : 1;          /* [valid_if(d_present)] X86_PAGE_FPAT_4KIB */
		u64          d_global : 1;       /* [valid_if(d_present)] X86_PAGE_FGLOBAL */
		u64          d_unused1_ign : 3;  /* [valid_if(d_present)] Ignored...  (0x200, 0x400, 0x800) */
		u64          d_addr : 40;        /* [valid_if(d_present)] X86_PAGE_FADDR_4KIB */
		u64          d_unused2_ign : 8;  /* [valid_if(d_present)] Ignored...  (Bits 52:58) */
		u64          d_prot_key : 3;     /* [valid_if(d_present)] X86_PAGE_FPROTKEY */
		u64          d_noexec : 1;       /* [valid_if(d_present)] X86_PAGE_FNOEXEC */
	} p_4kib;
#ifdef __cplusplus
	__CXX_CLASSMEMBER bool is1kib() const __CXX_NOEXCEPT {
		return X86_PDIR_E1_IS1KIB(p_word);
	}
	__CXX_CLASSMEMBER bool ishint() const __CXX_NOEXCEPT {
		return X86_PDIR_E1_ISHINT(p_word);
	}
	__CXX_CLASSMEMBER bool isunused() const __CXX_NOEXCEPT {
		return X86_PDIR_E1_ISUNUSED(p_word);
	}
	__CXX_CLASSMEMBER vm_phys_t getpageaddr() const __CXX_NOEXCEPT {
		return (vm_phys_t)(p_word & X86_PAGE_FADDR_4KIB);
	}
	__CXX_CLASSMEMBER vm_phys_t getpageaddr(vm_virt_t virt_addr) const __CXX_NOEXCEPT {
		return getpageaddr() + (vm_phys_t)(virt_addr & X86_PAGE_OFFST_4KIB);
	}
	__CXX_CLASSMEMBER vm_ppage_t getpage() const __CXX_NOEXCEPT {
		return VM_ADDR2PAGE(getpageaddr());
	}
#endif /* __cplusplus */
};

union x86_pdir_e2 {
	/* TIER#2 page-directory entry:
	 *   - 4-Level Page-Directory Entry that References a Page Table
	 *   - 4-Level Page-Directory Entry that Maps a 2-MByte Page */
	u64                      p_word;     /* Mapping data. */
#define X86_PDIR_E2_ISVEC1(e2_word)       (((e2_word) & (X86_PAGE_FPRESENT | X86_PAGE_F2MIB)) == X86_PAGE_FPRESENT)
#define X86_PDIR_E2_ISVEC1_OWNED(e2_word) (((e2_word) & (X86_PAGE_FPRESENT | X86_PAGE_F2MIB)) == X86_PAGE_FPRESENT || \
	                                       (!((e2_word) & X86_PAGE_FPRESENT) && (e2_word) != X86_PAGE_ABSENT))
#define X86_PDIR_E2_IS2MIB(e2_word)       (((e2_word) & (X86_PAGE_FPRESENT | X86_PAGE_F2MIB)) == (X86_PAGE_FPRESENT | X86_PAGE_F2MIB))
#define X86_PDIR_E2_ISUNUSED(e2_word)     ((e2_word) == X86_PAGE_ABSENT)


	PHYS u64                 p_addr;     /* [MASK(X86_PAGE_FADDR_2MIB)]
	                                      * [valid_if(X86_PAGE_FPRESENT && X86_PAGE_F2MIB)]
	                                      * _Physical_ page address. */
	PHYS union x86_pdir_e1 (*p_e1)[512]; /* [MASK(X86_PAGE_FVECTOR)]
	                                      * [owned_if(X86_PDIR_E2_ISVEC1_OWNED(p_word))]
	                                      * [valid_if(X86_PDIR_E2_ISVEC1(p_word))]
	                                      * _Physical_ pointer to a level #1 paging vector. */
	struct {
		u64          v_present : 1;      /* X86_PAGE_FPRESENT */
		u64          v_writable : 1;     /* [valid_if(v_present)] X86_PAGE_FWRITE */
		u64          v_user : 1;         /* [valid_if(v_present)] X86_PAGE_FUSER */
		u64          v_pwt : 1;          /* [valid_if(v_present)] X86_PAGE_FPWT */
		u64          v_pcd : 1;          /* [valid_if(v_present)] X86_PAGE_FPCD */
		u64          v_accessed : 1;     /* [valid_if(v_present)] X86_PAGE_FACCESSED */
		u64          v_dirty_ign : 1;    /* [valid_if(v_present)] Ignored...  (X86_PAGE_FDIRTY) */
		u64          v_2mib_0 : 1;       /* [valid_if(v_present)] Must be 0  (X86_PAGE_F2MIB) */
		u64          v_global_ign : 1;   /* [valid_if(v_present)] Ignored...  (X86_PAGE_FGLOBAL) */
		u64          v_unused1_ign : 3;  /* [valid_if(v_present)] Ignored...  (0x200, 0x400, 0x800) */
		u64          v_e1 : 40;          /* [valid_if(v_present)][TYPE(union x86_pdir_e2(*)[512])][owned] X86_PAGE_FVECTOR */
		u64          v_unused2_ign : 11; /* [valid_if(v_present)] Ignored...  (Bits 52:62) */
		u64          v_noexec : 1;       /* [valid_if(v_present)] X86_PAGE_FNOEXEC */
	} p_vec1; /* [valid_if(p_vec1.v_2mib_0 == 0)] */
	struct {
		u64          d_present : 1;      /* X86_PAGE_FPRESENT */
		u64          d_writable : 1;     /* [valid_if(d_present)] X86_PAGE_FWRITE */
		u64          d_user : 1;         /* [valid_if(d_present)] X86_PAGE_FUSER */
		u64          d_pwt : 1;          /* [valid_if(d_present)] X86_PAGE_FPWT */
		u64          d_pcd : 1;          /* [valid_if(d_present)] X86_PAGE_FPCD */
		u64          d_accessed : 1;     /* [valid_if(d_present)] X86_PAGE_FACCESSED */
		u64          d_dirty : 1;        /* [valid_if(d_present)] X86_PAGE_FDIRTY */
		u64          d_2mib_1 : 1;       /* [valid_if(d_present)] Must be 1  (X86_PAGE_F2MIB) */
		u64          d_global : 1;       /* [valid_if(d_present)] X86_PAGE_FGLOBAL */
		u64          d_unused1_ign : 3;  /* [valid_if(d_present)] Ignored...  (0x200, 0x400, 0x800) */
		u64          d_pat : 1;          /* [valid_if(d_present)] X86_PAGE_FPAT_2MIB */
		u64          d_reserved_0 : 8;   /* [valid_if(d_present)] Must be 0  (Reserved...) */
		u64          d_addr : 31;        /* [valid_if(d_present)] X86_PAGE_FADDR_2MIB */
		u64          d_unused2_ign : 8;  /* [valid_if(d_present)] Ignored...  (Bits 52:58) */
		u64          d_prot_key : 3;     /* [valid_if(d_present)] X86_PAGE_FPROTKEY */
		u64          d_noexec : 1;       /* [valid_if(d_present)] X86_PAGE_FNOEXEC */
	} p_2mib; /* [valid_if(p_2mib.d_2mib_1 == 0)] */
#ifdef __cplusplus
	__CXX_CLASSMEMBER bool isvec1() const __CXX_NOEXCEPT {
		return X86_PDIR_E2_ISVEC1(p_word);
	}
	__CXX_CLASSMEMBER bool is2mib() const __CXX_NOEXCEPT {
		return X86_PDIR_E2_IS2MIB(p_word);
	}
	__CXX_CLASSMEMBER bool isunused() const __CXX_NOEXCEPT {
		return X86_PDIR_E2_ISUNUSED(p_word);
	}
	__CXX_CLASSMEMBER vm_phys_t getpageaddr() const __CXX_NOEXCEPT {
		return (vm_phys_t)(p_word & X86_PAGE_FADDR_2MIB);
	}
	__CXX_CLASSMEMBER vm_phys_t getpageaddr(vm_virt_t virt_addr) const __CXX_NOEXCEPT {
		return getpageaddr() + (vm_phys_t)(virt_addr & X86_PAGE_OFFST_2MIB);
	}
	__CXX_CLASSMEMBER vm_ppage_t getpage() const __CXX_NOEXCEPT {
		return VM_ADDR2PAGE(getpageaddr());
	}
#endif /* __cplusplus */
};

union x86_pdir_e3 {
	/* TIER#3 page-directory entry:
	 *   - 4-Level Page-Directory-Pointer-Table Entry (PDPTE) that References a Page Directory
	 *   - 4-Level Page-Directory-Pointer-Table Entry (PDPTE) that Maps a 1-GByte Page */
	u64                      p_word;     /* Mapping data. */
#define X86_PDIR_E3_ISVEC2(e3_word)       (((e3_word) & (X86_PAGE_FPRESENT | X86_PAGE_F1GIB)) == X86_PAGE_FPRESENT)
#define X86_PDIR_E3_ISVEC2_OWNED(e3_word) (((e3_word) & (X86_PAGE_FPRESENT | X86_PAGE_F1GIB)) == X86_PAGE_FPRESENT || \
	                                       (!((e3_word) & X86_PAGE_FPRESENT) && (e3_word) != X86_PAGE_ABSENT))
#define X86_PDIR_E3_IS1GIB(e3_word)       (((e3_word) & (X86_PAGE_FPRESENT | X86_PAGE_F1GIB)) == (X86_PAGE_FPRESENT | X86_PAGE_F1GIB))
#define X86_PDIR_E3_ISUNUSED(e3_word)     ((e3_word) == X86_PAGE_ABSENT)
	PHYS u64                 p_addr;     /* [MASK(X86_PAGE_FADDR_1GIB)]
	                                      * [valid_if(X86_PAGE_FPRESENT && X86_PAGE_F1GIB)]
	                                      * _Physical_ page address. */
	PHYS union x86_pdir_e2 (*p_e2)[512]; /* [MASK(X86_PAGE_FVECTOR)]
	                                      * [owned_if(X86_PDIR_E3_ISVEC2_OWNED(p_word))]
	                                      * [valid_if(X86_PDIR_E3_ISVEC2(p_word))]
	                                      * _Physical_ pointer to a level #1 paging vector. */
	struct ATTR_PACKED {
		u64          v_present : 1;      /* X86_PAGE_FPRESENT */
		u64          v_writable : 1;     /* [valid_if(v_present)] X86_PAGE_FWRITE */
		u64          v_user : 1;         /* [valid_if(v_present)] X86_PAGE_FUSER */
		u64          v_pwt : 1;          /* [valid_if(v_present)] X86_PAGE_FPWT */
		u64          v_pcd : 1;          /* [valid_if(v_present)] X86_PAGE_FPCD */
		u64          v_accessed : 1;     /* [valid_if(v_present)] X86_PAGE_FACCESSED */
		u64          v_dirty_ign : 1;    /* [valid_if(v_present)] Ignored...  (X86_PAGE_FDIRTY) */
		u64          v_1gib_0 : 1;       /* [valid_if(v_present)] Must be 0  (X86_PAGE_F1GIB) */
		u64          v_global_ign : 1;   /* [valid_if(v_present)] Ignored...  (X86_PAGE_FGLOBAL) */
		u64          v_unused1_ign : 3;  /* [valid_if(v_present)] Ignored...  (0x200, 0x400, 0x800) */
		u64          v_e2 : 40;          /* [valid_if(v_present)][TYPE(union x86_pdir_e2(*)[512])][owned] X86_PAGE_FVECTOR */
		u64          v_unused2_ign : 11; /* [valid_if(v_present)] Ignored...  (Bits 52:62) */
		u64          v_noexec : 1;       /* [valid_if(v_present)] X86_PAGE_FNOEXEC */
	} p_vec2; /* [valid_if(p_vec2.v_1gib_0 == 0)] */
	struct ATTR_PACKED {
		u64          d_present : 1;      /* X86_PAGE_FPRESENT */
		u64          d_writable : 1;     /* [valid_if(d_present)] X86_PAGE_FWRITE */
		u64          d_user : 1;         /* [valid_if(d_present)] X86_PAGE_FUSER */
		u64          d_pwt : 1;          /* [valid_if(d_present)] X86_PAGE_FPWT */
		u64          d_pcd : 1;          /* [valid_if(d_present)] X86_PAGE_FPCD */
		u64          d_accessed : 1;     /* [valid_if(d_present)] X86_PAGE_FACCESSED */
		u64          d_dirty : 1;        /* [valid_if(d_present)] X86_PAGE_FDIRTY */
		u64          d_1gib_1 : 1;       /* [valid_if(d_present)] Must be 1  (X86_PAGE_F1GIB) */
		u64          d_global : 1;       /* [valid_if(d_present)] X86_PAGE_FGLOBAL */
		u64          d_unused1_ign : 3;  /* [valid_if(d_present)] Ignored...  (0x200, 0x400, 0x800) */
		u64          d_pat : 1;          /* [valid_if(d_present)] X86_PAGE_FPAT_1GIB */
		u64          d_reserved_0 : 17;  /* [valid_if(d_present)] Must be 0  (Reserved...) */
		u64          d_addr : 22;        /* [valid_if(d_present)] X86_PAGE_FADDR_1GIB */
		u64          d_unused2_ign : 8;  /* [valid_if(d_present)] Ignored...  (Bits 52:58) */
		u64          d_prot_key : 3;     /* [valid_if(d_present)] X86_PAGE_FPROTKEY */
		u64          d_noexec : 1;       /* [valid_if(d_present)] X86_PAGE_FNOEXEC */
	} p_1gib; /* [valid_if(p_1gib.d_1gib_1 == 1)] */
#ifdef __cplusplus
	__CXX_CLASSMEMBER bool isvec2() const __CXX_NOEXCEPT {
		return X86_PDIR_E3_ISVEC2(p_word);
	}
	__CXX_CLASSMEMBER bool is1gib() const __CXX_NOEXCEPT {
		return X86_PDIR_E3_IS1GIB(p_word);
	}
	__CXX_CLASSMEMBER bool isunused() const __CXX_NOEXCEPT {
		return X86_PDIR_E3_ISUNUSED(p_word);
	}
	__CXX_CLASSMEMBER vm_phys_t getpageaddr() const __CXX_NOEXCEPT {
		return (vm_phys_t)(p_word & X86_PAGE_FADDR_1GIB);
	}
	__CXX_CLASSMEMBER vm_phys_t getpageaddr(vm_virt_t virt_addr) const __CXX_NOEXCEPT {
		return getpageaddr() + (vm_phys_t)(virt_addr & X86_PAGE_OFFST_1GIB);
	}
	__CXX_CLASSMEMBER vm_ppage_t getpage() const __CXX_NOEXCEPT {
		return VM_ADDR2PAGE(getpageaddr());
	}
#endif /* __cplusplus */
};

union x86_pdir_e4 {
	/* TIER#4 page-directory entry:
	 *   - 4-Level PML4 Entry (PML4E) that References a Page-Directory-Pointer Table
	 * NOTE: These is no 512GiB page extension! */
	u64                      p_word;     /* Mapping data. */
#define X86_PDIR_E4_ISVEC3(e4_word)      ((e4_word) & X86_PAGE_FPRESENT)
#define X86_PDIR_E4_ISUNUSED(e4_word)    (!((e4_word) & X86_PAGE_FPRESENT))
	PHYS union x86_pdir_e3 (*p_e3)[512]; /* [MASK(X86_PAGE_FVECTOR)]
	                                      * [owned_if(p_vec2.v_present &&
	                                      *         ((self - :p_e4) < X86_PDIR_VEC4INDEX(KERNEL_BASE)))]
	                                      * [const_if((self - :p_e4) >= X86_PDIR_VEC4INDEX(KERNEL_BASE))]
	                                      * [valid_if(X86_PAGE_FPRESENT)]
	                                      * _Physical_ pointer to a level #3 paging vector.
	                                      * NOTE: If `(self - :p_e4) >= X86_PDIR_E4_INDEX(KERNEL_BASE_PAGE)',
	                                      *       then the caller can assume that the `X86_PAGE_FPRESENT' flag
	                                      *       has been set, and that a vector is assigned. */
	struct ATTR_PACKED {
		u64         v_present : 1;       /* X86_PAGE_FPRESENT */
		u64         v_writable : 1;      /* [valid_if(v_present)] X86_PAGE_FWRITE */
		u64         v_user : 1;          /* [valid_if(v_present)] X86_PAGE_FUSER */
		u64         v_pwt : 1;           /* [valid_if(v_present)] X86_PAGE_FPWT */
		u64         v_pcd : 1;           /* [valid_if(v_present)] X86_PAGE_FPCD */
		u64         v_accessed : 1;      /* [valid_if(v_present)] X86_PAGE_FACCESSED */
		u64         v_dirty_ign : 1;     /* [valid_if(v_present)] Ignored...  (X86_PAGE_FDIRTY) */
		u64         v_bigpage_0 : 1;     /* [valid_if(v_present)] Must be zero  (X86_PAGE_F2MIB / X86_PAGE_F1GIB) */
		u64         v_ignore_global : 1; /* [valid_if(v_present)] Ignored...  (X86_PAGE_FGLOBAL) */
		u64         v_unused1_ign : 3;   /* [valid_if(v_present)] Ignored...  (0x200, 0x400, 0x800) */
		u64         v_e3 : 40;           /* [valid_if(v_present)][TYPE(union x86_pdir_e3(*)[512])]
		                                  * [owned_if((self - :p_e4) < X86_PDIR_VEC4INDEX(KERNEL_BASE))] X86_PAGE_FVECTOR */
		u64         v_unused2_ign : 11;  /* [valid_if(v_present)] Ignored...  (Bits 52:62) */
		u64         v_noexec : 1;        /* [valid_if(v_present)] X86_PAGE_FNOEXEC */
	} p_vec3;
#ifdef __cplusplus
	__CXX_CLASSMEMBER bool isvec3() const __CXX_NOEXCEPT {
		return X86_PDIR_E4_ISVEC3(p_word);
	}
	__CXX_CLASSMEMBER bool isunused() const __CXX_NOEXCEPT {
		return X86_PDIR_E4_ISUNUSED(p_word);
	}
#endif /* __cplusplus */
};
#endif /* __CC__ */

#ifdef __CC__
struct x86_pdir {
	/* Page-directory (512-entry/4096-byte vector of `union x86_pdir_e4') */
	union x86_pdir_e4 p_e4[512];
};
#endif /* __CC__ */


#define X86_VM_KERNEL_PDIR_IDENTITY_BASE  __UINT64_C(0xffff808000000000) /* KERNEL_BASE + 512GiB */
#define X86_VM_KERNEL_PDIR_IDENTITY_SIZE  __UINT64_C(0x0000008000000000) /* 512GiB */
#define X86_VM_KERNEL_PDIR_RESERVED_BASE  __UINT64_C(0xffff808000000000) /* Start of the address range reserved for page-directory self-modifications. */
#define X86_VM_KERNEL_PDIR_RESERVED_SIZE  __UINT64_C(0x0000008000000000) /* Amount of memory reserved for page-directory self-modifications. */

/* Page directory self-mapping addresses.
 * NOTE: We put the self-mapping 512 GIB after `KERNEL_BASE', just
 *       so we can ensure that the first kernel-page can remain
 *       unmapped, meaning that the kernel can allow user-space
 *       pointers to overflow into kernel-space, at which point
 *       any read/write operation will fault long before it would
 *       ever reach any real kernel data.
 *       The reason why we can't place it closer to the beginning,
 *       is that since the self-mapping takes up a total of 512 GIB
 *       of memory (at most), we can only place it with a granularity
 *       of that same size. */
#define X86_PDIR_E1_IDENTITY_BASE  __UINT64_C(0xffff808000000000) /* KERNEL_BASE + 512GiB */
#define X86_PDIR_E2_IDENTITY_BASE  __UINT64_C(0xffff80c040000000)
#define X86_PDIR_E3_IDENTITY_BASE  __UINT64_C(0xffff80c060200000)
#define X86_PDIR_E4_IDENTITY_BASE  __UINT64_C(0xffff80c060301000)
#if 0
/* These are the actual addresses, as well as how they are calculated.
 * However, for clarity and compilation speed, we use the pre-computed versions above instead.
 * Still though, these versions are statically asserted to be equal to the pre-computed ones above! */
#define X86_PDIR_E2_IDENTITY_BASE (X86_PDIR_E1_IDENTITY_BASE + (X86_PDIR_VEC4INDEX(X86_PDIR_E1_IDENTITY_BASE) * X86_PDIR_E3_SIZE))
#define X86_PDIR_E3_IDENTITY_BASE (X86_PDIR_E2_IDENTITY_BASE + (X86_PDIR_VEC3INDEX(X86_PDIR_E2_IDENTITY_BASE) * X86_PDIR_E2_SIZE))
#define X86_PDIR_E4_IDENTITY_BASE (X86_PDIR_E3_IDENTITY_BASE + (X86_PDIR_VEC2INDEX(X86_PDIR_E3_IDENTITY_BASE) * X86_PDIR_E1_SIZE))
#endif


#ifdef __CC__
typedef union x86_pdir_e1
x86_pdir_e1_identity_t[512 /*X86_PDIR_VEC4INDEX(pointer)*/]
                      [512 /*X86_PDIR_VEC3INDEX(pointer)*/]
                      [512 /*X86_PDIR_VEC2INDEX(pointer)*/]
                      [512 /*X86_PDIR_VEC1INDEX(pointer)*/];
typedef union x86_pdir_e2
x86_pdir_e2_identity_t[512 /*X86_PDIR_VEC4INDEX(pointer)*/]
                      [512 /*X86_PDIR_VEC3INDEX(pointer)*/]
                      [512 /*X86_PDIR_VEC2INDEX(pointer)*/];
typedef union x86_pdir_e3
x86_pdir_e3_identity_t[512 /*X86_PDIR_VEC4INDEX(pointer)*/]
                      [512 /*X86_PDIR_VEC3INDEX(pointer)*/];
typedef union x86_pdir_e4
x86_pdir_e4_identity_t[512 /*X86_PDIR_VEC4INDEX(pointer)*/];

/* E1 identity mapping access for the current page directory.
 *    Index #0: VEC4 -- The same index as used in `struct x86_pdir::p_e4'
 *    Index #1: VEC3 -- The same index as used in `union x86_pdir_e4::p_e3'
 *    Index #2: VEC2 -- The same index as used in `union x86_pdir_e3::p_e2'
 *    Index #3: VEC1 -- The same index as used in `union x86_pdir_e2::p_e1'
 * Example:
 * >> VIRT void *pointer = get_pointer();
 * >> union x86_pdir_e1 *desc;
 * >> unsigned int vec4 = X86_PDIR_VEC4INDEX(pointer);
 * >> unsigned int vec3 = X86_PDIR_VEC3INDEX(pointer);
 * >> unsigned int vec2 = X86_PDIR_VEC2INDEX(pointer);
 * >> unsigned int vec1 = X86_PDIR_VEC1INDEX(pointer);
 * >> if (!X86_PDIR_E4_IDENTITY[vec4].p_vec3.v_present) {
 * >>     ...; // Pointer isn't mapped.
 * >> } else if (!X86_PDIR_E3_IDENTITY[vec4][vec3].p_vec2.v_present) {
 * >>     ...; // Pointer isn't mapped.
 * >> } else if (X86_PDIR_E3_IDENTITY[vec4][vec3].p_1gib.d_1gib_1) {
 * >>     ...; // Pointer is mapped as a 1GiB mapping
 * >> } else if (!X86_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_vec1.v_present) {
 * >>     ...; // Pointer isn't mapped.
 * >> } else if (X86_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_2mib.d_2mib_1) {
 * >>     ...; // Pointer is mapped as a 2MiB mapping
 * >> } else {
 * >>     // Load the descriptor
 * >>     desc = &X86_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1];
 * >>     if (!desc->p_4kib.d_present) {
 * >>         ...; // Pointer isn't mapped.
 * >>     } else {
 * >>         ...; // `desc' now points to the descriptor for the `pointer'
 * >>     }
 * >> }
 */
#define X86_PDIR_E1_IDENTITY  (*(x86_pdir_e1_identity_t *)X86_PDIR_E1_IDENTITY_BASE)
#define X86_PDIR_E2_IDENTITY  (*(x86_pdir_e2_identity_t *)X86_PDIR_E2_IDENTITY_BASE)
#define X86_PDIR_E3_IDENTITY  (*(x86_pdir_e3_identity_t *)X86_PDIR_E3_IDENTITY_BASE)
#define X86_PDIR_E4_IDENTITY  (*(x86_pdir_e4_identity_t *)X86_PDIR_E4_IDENTITY_BASE)

/* Return the in-page offset of a regular pointer mapping,
 * or one that has been mapped within a 4MiB page. */
#define X86_PDIR_PAGEINDEX_4KIB(ptr) ((unsigned int)((vm_virt_t)(ptr) & 0xfff))
#define X86_PDIR_PAGEINDEX_2MIB(ptr) ((unsigned int)((vm_virt_t)(ptr) & 0x1fffff))
#define X86_PDIR_PAGEINDEX_1GIB(ptr) ((unsigned int)((vm_virt_t)(ptr) & 0x3fffffff))

#else /* __CC__ */

#define X86_PDIR_E1_IDENTITY  X86_PDIR_E1_IDENTITY_BASE
#define X86_PDIR_E2_IDENTITY  X86_PDIR_E2_IDENTITY_BASE
#define X86_PDIR_E3_IDENTITY  X86_PDIR_E3_IDENTITY_BASE
#define X86_PDIR_E4_IDENTITY  X86_PDIR_E4_IDENTITY_BASE

#define X86_PDIR_PAGEINDEX_4KIB(ptr) ((ptr) & 0xfff)
#define X86_PDIR_PAGEINDEX_2MIB(ptr) ((ptr) & 0x1fffff)
#define X86_PDIR_PAGEINDEX_1GIB(ptr) ((ptr) & 0x3fffffff)

#endif /* !__CC__ */




/* Define platform-independent symbols. */
#define PAGEDIR_ALIGN X86_PDIR_ALIGN
#define PAGEDIR_SIZE  X86_PDIR_SIZE
#ifdef __CC__
typedef struct x86_pdir pagedir_t;
#endif /* __CC__ */

/* On x86, the `pagedir_init' function never throws an error. */
#undef CONFIG_PAGEDIR_INIT_IS_NOEXCEPT
#define CONFIG_PAGEDIR_INIT_IS_NOEXCEPT 1

/* x86 implements the `pagedir_(has|unset)changed' API. */
#undef CONFIG_HAVE_PAGEDIR_CHANGED
#define CONFIG_HAVE_PAGEDIR_CHANGED 1

/* x86 implements the `pagedir_unwrite' API (delete low-level write permissions). */
#undef CONFIG_HAVE_PAGEDIR_UNWRITE
#define CONFIG_HAVE_PAGEDIR_UNWRITE 1

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
	__asm__("movq %%cr3, %0"
	        : "=r" (result)
	        :
	        : "memory");
	return result;
}

FORCELOCAL NOBLOCK void
NOTHROW(KCALL pagedir_set)(PHYS pagedir_t *__restrict value) {
	__asm__("movq %0, %%cr3"
	        :
	        : "r" (value)
	        : "memory");
}
#endif /* __CC__ */


#undef CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_SYNCALL
#define CONFIG_PAGEDIR_ARCH_HEADER_DEFINES_PAGEDIR_SYNCALL 1
#ifdef __CC__
/* Synchronize the entirety of the current page directory. */
FORCELOCAL NOBLOCK void
NOTHROW(FCALL pagedir_syncall)(void) {
	__register uintptr_t temp;
	__asm__("movq %%cr3, %0\n\t"
	        "movq %0, %%cr3"
	        : "=&r" (temp));
}

#endif /* __CC__ */


#undef PAGEALIGN
#undef PAGESIZE
#undef PAGESHIFT
#define PAGEALIGN  X86_PAGE_ALIGN /* Required page alignment. */
#define PAGESIZE   X86_PAGE_SIZE  /* Required page size. */
#define PAGESHIFT  X86_PAGE_SHIFT /* Shift used to convert between page indices and addresses. */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_PAGING64_H */
