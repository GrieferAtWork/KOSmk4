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
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_PAGING64_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_PAGING64_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <kos/kernel/memory.h>
#include <kos/kernel/paging.h>

#include <stdbool.h>

#ifdef __cplusplus
#include <__stdcxx.h>
#endif /* __cplusplus */

#undef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
#define ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE 1

#undef ARCH_PAGEDIR_INIT_NEED_PHYS_SELF
#define ARCH_PAGEDIR_INIT_NEED_PHYS_SELF 1

#undef ARCH_PAGEDIR_FINI_NEED_PHYS_SELF
#define ARCH_PAGEDIR_FINI_NEED_PHYS_SELF 1

DECL_BEGIN

/* Implementation of 4-level paging (s.a. `Table 4-1.  Properties of Different Paging Modes')
 * The best overview of this can be found in:
 *     `Figure 4-11.  Formats of CR3 and Paging-Structure Entries with 4-Level Paging'
 */



/* To differentiate between hints and allocated, but non-present pages, we use this:
 *
 * ```
 *                                                       P64_PAGE_FPREPARED
 *                                                       |
 *                                                       |         P64_PAGE_FISAHINT
 *                                                       |         |
 *                                                       |         |P64_PAGE_FPRESENT
 *                                                       |         ||
 * E XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX1: Page:  4KiB-page (P64_PAGE_FADDR_4KIB)
 * 1 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX10: Hint:  DATA & P64_PAGE_FHINT
 *   0000000000000000000000000000000000000000000000000000XXXXXXXXXX00: Unused with meta-data (e.g. `P64_PAGE_FPREPARED')
 *   0000000000000000000000000000000000000000000000000000000000000000: Unused (P64_PAGE_ABSENT)
 *    6 6 5 5 5 5 5 4 4 4 4 4 3 3 3 3 3 2 2 2 2 2 1 1 1 1 1 8 6 4 2 0
 *    2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0
 *
 *                                                           P64_PAGE_F2MIB
 *                                                           |
 *                                                           |      P64_PAGE_FPRESENT
 *                                                           |      |
 * E XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXXXX1: Page:  Large page mapping P64_PAGE_FADDR_2MIB
 * 2 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX0XXXXXX1: Owned: page_freeone(DATA & P64_PAGE_FVECTOR) (present)
 *   0000000000000000000000000000000000000000000000000000000000000000: Unused (P64_PAGE_ABSENT)
 *    6 6 5 5 5 5 5 4 4 4 4 4 3 3 3 3 3 2 2 2 2 2 1 1 1 1 1 8 6 4 2 0
 *    2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0
 *
 *                                                           P64_PAGE_F1GIB
 *                                                           |
 *                                                           |      P64_PAGE_FPRESENT
 *                                                           |      |
 * E XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXXXX1: Page:  Large page mapping P64_PAGE_FADDR_1GIB
 * 3 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX0XXXXXX1: Owned: page_freeone(DATA & P64_PAGE_FVECTOR) (present)
 *   0000000000000000000000000000000000000000000000000000000000000000: Unused (P64_PAGE_ABSENT)
 *    6 6 5 5 5 5 5 4 4 4 4 4 3 3 3 3 3 2 2 2 2 2 1 1 1 1 1 8 6 4 2 0
 *    2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0
 *
 *                                                                  P64_PAGE_FPRESENT
 *                                                                  |
 * E XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX1: Owned: page_freeone(DATA & P64_PAGE_FVECTOR) (present)
 * 4 0000000000000000000000000000000000000000000000000000000000000000: Unused (P64_PAGE_ABSENT)
 *    6 6 5 5 5 5 5 4 4 4 4 4 3 3 3 3 3 2 2 2 2 2 1 1 1 1 1 8 6 4 2 0
 *    2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0
 * ```
 *
 * NOTE: In the case of E4, you may assume that any address with `P64_PDIR_VEC4INDEX(addr) >= 256'
 *       always  has the `P64_PAGE_FPRESENT' bit set, and that it points to a statically allocated
 *       block of `union p64_pdir_e3[512]' that are shared between all page directories.
 */

/* The minimum alignment required for pointers passed to `pagedir_maphint()' */
#define PAGEDIR_MAPHINT_ALIGNMENT 4


#define P64_PAGE_SHIFT      12 /* Shift to convert between pages and addresses. */
#define P64_PAGE_ALIGN      __UINT64_C(0x0000000000001000) /* Required page alignment. */
#define P64_PAGE_SIZE       __UINT64_C(0x0000000000001000) /* Required page size. */
#define P64_PAGE_FVECTOR    __UINT64_C(0x000ffffffffff000) /* [bit(12:51)] Mask of an inner vector. */
#define P64_PAGE_FHINT      __UINT64_C(0xfffffffffffffffc) /* Mask of page hints. */
#define P64_PAGE_FADDR_4KIB __UINT64_C(0x000ffffffffff000) /* Mask of the page address for 1KiB pages. */
#define P64_PAGE_OFFST_4KIB __UINT64_C(0x0000000000000fff) /* Offset mask for 1KiB pages. */
#define P64_PAGE_FADDR_2MIB __UINT64_C(0x000fffffffe00000) /* Mask of the page address for 2MiB pages. */
#define P64_PAGE_OFFST_2MIB __UINT64_C(0x00000000001fffff) /* Offset mask for 2MiB pages. */
#define P64_PAGE_FADDR_1GIB __UINT64_C(0x000fffffc0000000) /* Mask of the page address for 1GiB pages. */
#define P64_PAGE_OFFST_1GIB __UINT64_C(0x000000003fffffff) /* Offset mask for 1GiB pages. */
#define P64_PAGE_FMASK      __UINT64_C(0xfff0000000000fff) /* Mask of page flag bits. */
#define P64_PAGE_FPROTKEY   __UINT64_C(0x7000000000000000) /* Mask for the protection key. */
#define P64_PAGE_ABSENT     __UINT64_C(0x0000000000000000) /* Value found in any TIER _EXCEPT_ TIER#1 to indicate that a vector hasn't been allocated. */

#define P64_PAGE_FPRESENT   __UINT64_C(0x0000000000000001) /* [bit(0)] The page is present (When not set, cause a PAGEFAULT that may be used for allocate/load-on-read). */
#define P64_PAGE_FISAHINT   __UINT64_C(0x0000000000000002) /* [bit(1)][valid_if(!P64_PAGE_FPRESENT)] The page has been hinted. */
#define P64_PAGE_FWRITE     __UINT64_C(0x0000000000000002) /* [bit(1)] The page is writable. */
#define P64_PAGE_FUSER      __UINT64_C(0x0000000000000004) /* [bit(2)] User-space may access this page (read, or write). */
#define P64_PAGE_FPWT       __UINT64_C(0x0000000000000008) /* [bit(3)] Page-level write-through. */
#define P64_PAGE_FPCD       __UINT64_C(0x0000000000000010) /* [bit(4)] Page-level cache disable. */
#define P64_PAGE_FACCESSED  __UINT64_C(0x0000000000000020) /* [bit(5)] The page has been read from, or written to. */
#define P64_PAGE_FDIRTY     __UINT64_C(0x0000000000000040) /* [bit(6)] The page has been written to. (only valid in entries that map physical memory, rather than point to other vectors) */
#define P64_PAGE_F2MIB      __UINT64_C(0x0000000000000080) /* [bit(7)] Directly map a physical address on level #2 (for use in `union p64_pdir_e2::p_word'). */
#define P64_PAGE_F1GIB      __UINT64_C(0x0000000000000080) /* [bit(7)] Directly map a physical address on level #3 (for use in `union p64_pdir_e3::p_word'). */
#define P64_PAGE_FGLOBAL    __UINT64_C(0x0000000000000100) /* [bit(8)] Set to optimize mappings that appear at the same location in all
                                                            *          directories it appears inside of (aka: Kernel-allocated stack/memory). */
#define P64_PAGE_FPREPARED  __UINT64_C(0x0000000000000800) /* [bit(11)][KOS_SPECIFIC] Prevent the associated mapping from being flattened. (May only appear in E1-entries)
                                                            * This flag is used to indicate that the associated page is currently prepared,
                                                            * and that its containing vectors shouldn't be merged before it becomes unprepared. */
#define P64_PAGE_FPAT_4KIB  __UINT64_C(0x0000000000000080) /* [bit(7)]  Indirectly determines the memory type used to access the 4-KByte page referenced by this entry. */
#define P64_PAGE_FPAT_2MIB  __UINT64_C(0x0000000000001000) /* [bit(12)] Indirectly determines the memory type used to access the 2-MByte page referenced by this entry. */
#define P64_PAGE_FPAT_1GIB  __UINT64_C(0x0000000000001000) /* [bit(12)] Indirectly determines the memory type used to access the 1-GByte page referenced by this entry. */
#define P64_PAGE_FNOEXEC    __UINT64_C(0x8000000000000000) /* [bit(63)] Memory within the page cannot be executed. */


#define P64_PDIR_VEC1INDEX(ptr) ((__CCAST(u64)(ptr) >> 12) & 0x1ff) /* For `union p64_pdir_e2::p_e1' */
#define P64_PDIR_VEC2INDEX(ptr) ((__CCAST(u64)(ptr) >> 21) & 0x1ff) /* For `union p64_pdir_e3::p_e2' */
#define P64_PDIR_VEC3INDEX(ptr) ((__CCAST(u64)(ptr) >> 30) & 0x1ff) /* For `union p64_pdir_e4::p_e3' */
#define P64_PDIR_VEC4INDEX(ptr) ((__CCAST(u64)(ptr) >> 39) & 0x1ff) /* For `struct p64_pdir::p_e4' */
#ifdef __CC__
#define P64_PDIR_VECADDR(vec4, vec3, vec2, vec1)         \
	(void *)((u64)(((s64)(vec4) << 55) >> 16) |          \
	         ((u64)(vec3) << 30) | ((u64)(vec2) << 21) | \
	         ((u64)(vec1) << 12))
#else /* __CC__ */
#define P64_PDIR_VECADDR(vec4, vec3, vec2, vec1)        \
	((((vec4)&0x100) * __UINT64_C(0xffff0000000000)) |  \
	 ((vec4) << 39) | ((vec3) << 30) | ((vec2) << 21) | \
	 ((vec1) << 12))
#endif /* !__CC__ */

/* Pagesizes of different page directory levels. */
#define P64_PDIR_E1_SIZE __UINT64_C(0x0000000000001000) /* 4 KiB (Same as `PAGESIZE') */
#define P64_PDIR_E2_SIZE __UINT64_C(0x0000000000200000) /* 2 MiB */
#define P64_PDIR_E3_SIZE __UINT64_C(0x0000000040000000) /* 1 GiB */
#define P64_PDIR_E4_SIZE __UINT64_C(0x0000008000000000) /* 512 GiB */

#define P64_IS_4KIB_ALIGNED(addr) (((addr) & __UINT64_C(0x0000000000000fff)) == 0)
#define P64_IS_2MIB_ALIGNED(addr) (((addr) & __UINT64_C(0x00000000001fffff)) == 0)
#define P64_IS_1GIB_ALIGNED(addr) (((addr) & __UINT64_C(0x000000003fffffff)) == 0)

/* Return the in-page offset of a regular pointer mapping,
 * or  one  that  has  been  mapped  within  a  2MiB page. */
#define P64_PDIR_PAGEINDEX_4KIB(ptr) (__CCAST(u64)(ptr) & 0xfff)
#define P64_PDIR_PAGEINDEX_2MIB(ptr) (__CCAST(u64)(ptr) & 0x1fffff)
#define P64_PDIR_PAGEINDEX_1GIB(ptr) (__CCAST(u64)(ptr) & 0x3fffffff)

#define P64_PDIR_ALIGN  4096 /* Alignment required for instances of `struct p64_pdir' */
#define P64_PDIR_SIZE   4096 /* The total size of `struct p64_pdir' in bytes. */


#ifdef __CC__
union p64_pdir_e1 {
	/* Lowest-level page-directory entry:
	 *   - 4-Level Page-Table Entry that Maps a 4-KByte Page */
	u64                      p_word;     /* Mapping data. */
#define P64_PDIR_E1_IS1KIB(e1_word)    ((e1_word) & P64_PAGE_FPRESENT)
#define P64_PDIR_E1_ISHINT(e1_word)    (((e1_word) & (P64_PAGE_FPRESENT | P64_PAGE_FISAHINT)) == P64_PAGE_FISAHINT)
#define P64_PDIR_E1_ISUNUSED(e1_word)  (((e1_word) & (P64_PAGE_FPRESENT | P64_PAGE_FISAHINT)) == 0)
	struct {
		u64          d_present : 1;      /* P64_PAGE_FPRESENT */
		u64          d_writable : 1;     /* [valid_if(d_present)] P64_PAGE_FWRITE */
		u64          d_user : 1;         /* [valid_if(d_present)] P64_PAGE_FUSER */
		u64          d_pwt : 1;          /* [valid_if(d_present)] P64_PAGE_FPWT */
		u64          d_pcd : 1;          /* [valid_if(d_present)] P64_PAGE_FPCD */
		u64          d_accessed : 1;     /* [valid_if(d_present)] P64_PAGE_FACCESSED */
		u64          d_dirty : 1;        /* [valid_if(d_present)] P64_PAGE_FDIRTY */
		u64          d_pat : 1;          /* [valid_if(d_present)] P64_PAGE_FPAT_4KIB */
		u64          d_global : 1;       /* [valid_if(d_present)] P64_PAGE_FGLOBAL */
		u64          d_unused1_ign : 3;  /* [valid_if(d_present)] Ignored...  (0x200, 0x400, 0x800) */
		u64          d_addr : 40;        /* [valid_if(d_present)] P64_PAGE_FADDR_4KIB */
		u64          d_unused2_ign : 8;  /* [valid_if(d_present)] Ignored...  (Bits 52:58) */
		u64          d_prot_key : 3;     /* [valid_if(d_present)] P64_PAGE_FPROTKEY */
		u64          d_noexec : 1;       /* [valid_if(d_present)] P64_PAGE_FNOEXEC */
	} p_4kib;
};

union p64_pdir_e2 {
	/* TIER#2 page-directory entry:
	 *   - 4-Level Page-Directory Entry that References a Page Table
	 *   - 4-Level Page-Directory Entry that Maps a 2-MByte Page */
	u64                      p_word;     /* Mapping data. */
#define P64_PDIR_E2_ISVEC1(e2_word)       (((e2_word) & (P64_PAGE_FPRESENT | P64_PAGE_F2MIB)) == P64_PAGE_FPRESENT)
#define P64_PDIR_E2_IS2MIB(e2_word)       (((e2_word) & (P64_PAGE_FPRESENT | P64_PAGE_F2MIB)) == (P64_PAGE_FPRESENT | P64_PAGE_F2MIB))
#define P64_PDIR_E2_ISUNUSED(e2_word)     ((e2_word) == P64_PAGE_ABSENT)
	PHYS union p64_pdir_e1 (*p_e1)[512]; /* [MASK(P64_PAGE_FVECTOR)]
	                                      * [owned][valid_if(P64_PDIR_E2_ISVEC1(p_word))]
	                                      * _Physical_ pointer to a level #1 paging vector. */
	struct {
		u64          v_present : 1;      /* P64_PAGE_FPRESENT */
		u64          v_writable : 1;     /* [valid_if(v_present)] P64_PAGE_FWRITE */
		u64          v_user : 1;         /* [valid_if(v_present)] P64_PAGE_FUSER */
		u64          v_pwt : 1;          /* [valid_if(v_present)] P64_PAGE_FPWT */
		u64          v_pcd : 1;          /* [valid_if(v_present)] P64_PAGE_FPCD */
		u64          v_accessed : 1;     /* [valid_if(v_present)] P64_PAGE_FACCESSED */
		u64          v_dirty_ign : 1;    /* [valid_if(v_present)] Ignored...  (P64_PAGE_FDIRTY) */
		u64          v_2mib_0 : 1;       /* [valid_if(v_present)] Must be 0  (P64_PAGE_F2MIB) */
		u64          v_global_ign : 1;   /* [valid_if(v_present)] Ignored...  (P64_PAGE_FGLOBAL) */
		u64          v_unused1_ign : 3;  /* [valid_if(v_present)] Ignored...  (0x200, 0x400, 0x800) */
		u64          v_e1 : 40;          /* [valid_if(v_present)][TYPE(union p64_pdir_e2(*)[512])][owned] P64_PAGE_FVECTOR */
		u64          v_unused2_ign : 11; /* [valid_if(v_present)] Ignored...  (Bits 52:62) */
		u64          v_noexec : 1;       /* [valid_if(v_present)] P64_PAGE_FNOEXEC */
	} p_vec1; /* [valid_if(p_vec1.v_2mib_0 == 0)] */
	struct {
		u64          d_present : 1;      /* P64_PAGE_FPRESENT */
		u64          d_writable : 1;     /* [valid_if(d_present)] P64_PAGE_FWRITE */
		u64          d_user : 1;         /* [valid_if(d_present)] P64_PAGE_FUSER */
		u64          d_pwt : 1;          /* [valid_if(d_present)] P64_PAGE_FPWT */
		u64          d_pcd : 1;          /* [valid_if(d_present)] P64_PAGE_FPCD */
		u64          d_accessed : 1;     /* [valid_if(d_present)] P64_PAGE_FACCESSED */
		u64          d_dirty : 1;        /* [valid_if(d_present)] P64_PAGE_FDIRTY */
		u64          d_2mib_1 : 1;       /* [valid_if(d_present)] Must be 1  (P64_PAGE_F2MIB) */
		u64          d_global : 1;       /* [valid_if(d_present)] P64_PAGE_FGLOBAL */
		u64          d_unused1_ign : 3;  /* [valid_if(d_present)] Ignored...  (0x200, 0x400, 0x800) */
		u64          d_pat : 1;          /* [valid_if(d_present)] P64_PAGE_FPAT_2MIB */
		u64          d_reserved_0 : 8;   /* [valid_if(d_present)] Must be 0  (Reserved...) */
		u64          d_addr : 31;        /* [valid_if(d_present)] P64_PAGE_FADDR_2MIB */
		u64          d_unused2_ign : 8;  /* [valid_if(d_present)] Ignored...  (Bits 52:58) */
		u64          d_prot_key : 3;     /* [valid_if(d_present)] P64_PAGE_FPROTKEY */
		u64          d_noexec : 1;       /* [valid_if(d_present)] P64_PAGE_FNOEXEC */
	} p_2mib; /* [valid_if(p_2mib.d_2mib_1 == 1)] */
};

union p64_pdir_e3 {
	/* TIER#3 page-directory entry:
	 *   - 4-Level Page-Directory-Pointer-Table Entry (PDPTE) that References a Page Directory
	 *   - 4-Level Page-Directory-Pointer-Table Entry (PDPTE) that Maps a 1-GByte Page */
	u64                      p_word;     /* Mapping data. */
#define P64_PDIR_E3_ISVEC2(e3_word)       (((e3_word) & (P64_PAGE_FPRESENT | P64_PAGE_F1GIB)) == P64_PAGE_FPRESENT)
#define P64_PDIR_E3_IS1GIB(e3_word)       (((e3_word) & (P64_PAGE_FPRESENT | P64_PAGE_F1GIB)) == (P64_PAGE_FPRESENT | P64_PAGE_F1GIB))
#define P64_PDIR_E3_ISUNUSED(e3_word)     ((e3_word) == P64_PAGE_ABSENT)
	PHYS union p64_pdir_e2 (*p_e2)[512]; /* [MASK(P64_PAGE_FVECTOR)]
	                                      * [owned][valid_if(P64_PDIR_E3_ISVEC2(p_word))]
	                                      * _Physical_ pointer to a level #2 paging vector. */
	struct ATTR_PACKED {
		u64          v_present : 1;      /* P64_PAGE_FPRESENT */
		u64          v_writable : 1;     /* [valid_if(v_present)] P64_PAGE_FWRITE */
		u64          v_user : 1;         /* [valid_if(v_present)] P64_PAGE_FUSER */
		u64          v_pwt : 1;          /* [valid_if(v_present)] P64_PAGE_FPWT */
		u64          v_pcd : 1;          /* [valid_if(v_present)] P64_PAGE_FPCD */
		u64          v_accessed : 1;     /* [valid_if(v_present)] P64_PAGE_FACCESSED */
		u64          v_dirty_ign : 1;    /* [valid_if(v_present)] Ignored...  (P64_PAGE_FDIRTY) */
		u64          v_1gib_0 : 1;       /* [valid_if(v_present)] Must be 0  (P64_PAGE_F1GIB) */
		u64          v_global_ign : 1;   /* [valid_if(v_present)] Ignored...  (P64_PAGE_FGLOBAL) */
		u64          v_unused1_ign : 3;  /* [valid_if(v_present)] Ignored...  (0x200, 0x400, 0x800) */
		u64          v_e2 : 40;          /* [valid_if(v_present)][TYPE(union p64_pdir_e2(*)[512])][owned] P64_PAGE_FVECTOR */
		u64          v_unused2_ign : 11; /* [valid_if(v_present)] Ignored...  (Bits 52:62) */
		u64          v_noexec : 1;       /* [valid_if(v_present)] P64_PAGE_FNOEXEC */
	} p_vec2; /* [valid_if(p_vec2.v_1gib_0 == 0)] */
	struct ATTR_PACKED {
		u64          d_present : 1;      /* P64_PAGE_FPRESENT */
		u64          d_writable : 1;     /* [valid_if(d_present)] P64_PAGE_FWRITE */
		u64          d_user : 1;         /* [valid_if(d_present)] P64_PAGE_FUSER */
		u64          d_pwt : 1;          /* [valid_if(d_present)] P64_PAGE_FPWT */
		u64          d_pcd : 1;          /* [valid_if(d_present)] P64_PAGE_FPCD */
		u64          d_accessed : 1;     /* [valid_if(d_present)] P64_PAGE_FACCESSED */
		u64          d_dirty : 1;        /* [valid_if(d_present)] P64_PAGE_FDIRTY */
		u64          d_1gib_1 : 1;       /* [valid_if(d_present)] Must be 1  (P64_PAGE_F1GIB) */
		u64          d_global : 1;       /* [valid_if(d_present)] P64_PAGE_FGLOBAL */
		u64          d_unused1_ign : 3;  /* [valid_if(d_present)] Ignored...  (0x200, 0x400, 0x800) */
		u64          d_pat : 1;          /* [valid_if(d_present)] P64_PAGE_FPAT_1GIB */
		u64          d_reserved_0 : 17;  /* [valid_if(d_present)] Must be 0  (Reserved...) */
		u64          d_addr : 22;        /* [valid_if(d_present)] P64_PAGE_FADDR_1GIB */
		u64          d_unused2_ign : 8;  /* [valid_if(d_present)] Ignored...  (Bits 52:58) */
		u64          d_prot_key : 3;     /* [valid_if(d_present)] P64_PAGE_FPROTKEY */
		u64          d_noexec : 1;       /* [valid_if(d_present)] P64_PAGE_FNOEXEC */
	} p_1gib; /* [valid_if(p_1gib.d_1gib_1 == 1)] */
};

union p64_pdir_e4 {
	/* TIER#4 page-directory entry:
	 *   - 4-Level PML4 Entry (PML4E) that References a Page-Directory-Pointer Table
	 * NOTE: There is no 512GiB page extension! */
	u64                      p_word;     /* Mapping data. */
#define P64_PDIR_E4_ISVEC3(e3_word)       ((e3_word) & P64_PAGE_FPRESENT)
#define P64_PDIR_E4_ISUNUSED(e3_word)     ((e3_word) == P64_PAGE_ABSENT)
	PHYS union p64_pdir_e3 (*p_e3)[512]; /* [MASK(P64_PAGE_FVECTOR)]
	                                      * [owned_if(P64_PDIR_E4_ISVEC3(p_word) &&
	                                      *           ((self - :p_e4) < P64_PDIR_VEC4INDEX(KERNELSPACE_BASE)))]
	                                      * [const_if((self - :p_e4) >= P64_PDIR_VEC4INDEX(KERNELSPACE_BASE))]
	                                      * [valid_if(P64_PAGE_FPRESENT)]
	                                      * _Physical_ pointer to a level #3 paging vector.
	                                      * NOTE: If `(self - :p_e4) >= P64_PDIR_VEC4INDEX(KERNELSPACE_BASE)',
	                                      *       then the caller can assume that the `P64_PAGE_FPRESENT' flag
	                                      *       has been set, and that a vector is assigned. */
	struct ATTR_PACKED {
		u64          v_present : 1;       /* P64_PAGE_FPRESENT */
		u64          v_writable : 1;      /* [valid_if(v_present)] P64_PAGE_FWRITE */
		u64          v_user : 1;          /* [valid_if(v_present)] P64_PAGE_FUSER */
		u64          v_pwt : 1;           /* [valid_if(v_present)] P64_PAGE_FPWT */
		u64          v_pcd : 1;           /* [valid_if(v_present)] P64_PAGE_FPCD */
		u64          v_accessed : 1;      /* [valid_if(v_present)] P64_PAGE_FACCESSED */
		u64          v_dirty_ign : 1;     /* [valid_if(v_present)] Ignored...  (P64_PAGE_FDIRTY) */
		u64          v_bigpage_0 : 1;     /* [valid_if(v_present)] Must be zero  (P64_PAGE_F2MIB / P64_PAGE_F1GIB) */
		u64          v_ignore_global : 1; /* [valid_if(v_present)] Ignored...  (P64_PAGE_FGLOBAL) */
		u64          v_unused1_ign : 3;   /* [valid_if(v_present)] Ignored...  (0x200, 0x400, 0x800) */
		u64          v_e3 : 40;           /* [valid_if(v_present)][TYPE(union p64_pdir_e3(*)[512])]
		                                   * [owned_if((self - :p_e4) < P64_PDIR_VEC4INDEX(KERNELSPACE_BASE))] P64_PAGE_FVECTOR */
		u64          v_unused2_ign : 11;  /* [valid_if(v_present)] Ignored...  (Bits 52:62) */
		u64          v_noexec : 1;        /* [valid_if(v_present)] P64_PAGE_FNOEXEC */
	} p_vec3;
};
#endif /* __CC__ */

#ifdef __CC__
struct ATTR_ALIGNED(P64_PDIR_ALIGN) p64_pdir {
	/* Page-directory (512-entry/4096-byte vector of `union p64_pdir_e4') */
	union p64_pdir_e4 p_e4[512];
};
#endif /* __CC__ */


#define P64_MMAN_KERNEL_PDIR_IDENTITY_BASE  __UINT64_C(0xffff808000000000) /* KERNELSPACE_BASE + 512GiB */
#define P64_MMAN_KERNEL_PDIR_IDENTITY_SIZE  __UINT64_C(0x0000008000000000) /* 512GiB */
#define P64_MMAN_KERNEL_PDIR_RESERVED_BASE  __UINT64_C(0xffff808000000000) /* Start of the address range reserved for page-directory self-modifications. */
#define P64_MMAN_KERNEL_PDIR_RESERVED_SIZE  __UINT64_C(0x0000008000000000) /* Amount of memory reserved for page-directory self-modifications. */

#define X86_MMAN_KERNEL_PDIR_RESERVED_BASE P64_MMAN_KERNEL_PDIR_RESERVED_BASE
#define X86_MMAN_KERNEL_PDIR_RESERVED_SIZE P64_MMAN_KERNEL_PDIR_RESERVED_SIZE


/* Page directory self-mapping addresses.
 * NOTE: We put the self-mapping 512 GIB after `KERNELSPACE_BASE', just
 *       so  we  can  ensure  that  the  first  kernel-page  can remain
 *       unmapped,   meaning  that  the  kernel  can  allow  user-space
 *       pointers   to  overflow  into  kernel-space,  at  which  point
 *       any read/write  operation  will  fault long  before  it  would
 *       ever reach any real kernel data.
 *       The  reason why we  can't place it  closer to the beginning,
 *       is that since the self-mapping takes  up a total of 512  GIB
 *       of memory (at most), we can only place it with a granularity
 *       of that same size. */
#define P64_PDIR_E1_IDENTITY_BASE  __UINT64_C(0xffff808000000000) /* KERNELSPACE_BASE + 512GiB */
#define P64_PDIR_E2_IDENTITY_BASE  __UINT64_C(0xffff80c040000000)
#define P64_PDIR_E3_IDENTITY_BASE  __UINT64_C(0xffff80c060200000)
#define P64_PDIR_E4_IDENTITY_BASE  __UINT64_C(0xffff80c060301000)
#if 0
/* These are the actual addresses, as well as how they are calculated.
 * However, for clarity  and compilation  speed, we use  the pre-computed  versions above  instead.
 * Still though, these versions are statically asserted to be equal to the pre-computed ones above! */
#define P64_PDIR_E2_IDENTITY_BASE (P64_PDIR_E1_IDENTITY_BASE + (P64_PDIR_VEC4INDEX(P64_PDIR_E1_IDENTITY_BASE) * P64_PDIR_E3_SIZE))
#define P64_PDIR_E3_IDENTITY_BASE (P64_PDIR_E2_IDENTITY_BASE + (P64_PDIR_VEC3INDEX(P64_PDIR_E2_IDENTITY_BASE) * P64_PDIR_E2_SIZE))
#define P64_PDIR_E4_IDENTITY_BASE (P64_PDIR_E3_IDENTITY_BASE + (P64_PDIR_VEC2INDEX(P64_PDIR_E3_IDENTITY_BASE) * P64_PDIR_E1_SIZE))
#endif


#ifdef __CC__
typedef union p64_pdir_e1
p64_pdir_e1_identity_t[512 /*P64_PDIR_VEC4INDEX(pointer)*/]
                      [512 /*P64_PDIR_VEC3INDEX(pointer)*/]
                      [512 /*P64_PDIR_VEC2INDEX(pointer)*/]
                      [512 /*P64_PDIR_VEC1INDEX(pointer)*/];
typedef union p64_pdir_e2
p64_pdir_e2_identity_t[512 /*P64_PDIR_VEC4INDEX(pointer)*/]
                      [512 /*P64_PDIR_VEC3INDEX(pointer)*/]
                      [512 /*P64_PDIR_VEC2INDEX(pointer)*/];
typedef union p64_pdir_e3
p64_pdir_e3_identity_t[512 /*P64_PDIR_VEC4INDEX(pointer)*/]
                      [512 /*P64_PDIR_VEC3INDEX(pointer)*/];
typedef union p64_pdir_e4
p64_pdir_e4_identity_t[512 /*P64_PDIR_VEC4INDEX(pointer)*/];

/* E1 identity   mapping   access   for   the   current   page   directory.
 *    Index #0: VEC4 -- The  same index as used in  `struct p64_pdir::p_e4'
 *    Index #1: VEC3 -- The same index as used in `union p64_pdir_e4::p_e3'
 *    Index #2: VEC2 -- The same index as used in `union p64_pdir_e3::p_e2'
 *    Index #3: VEC1 -- The same index as used in `union p64_pdir_e2::p_e1'
 * Example:
 * >> VIRT void *pointer = get_pointer();
 * >> union p64_pdir_e1 *desc;
 * >> unsigned int vec4 = P64_PDIR_VEC4INDEX(pointer);
 * >> unsigned int vec3 = P64_PDIR_VEC3INDEX(pointer);
 * >> unsigned int vec2 = P64_PDIR_VEC2INDEX(pointer);
 * >> unsigned int vec1 = P64_PDIR_VEC1INDEX(pointer);
 * >> if (!P64_PDIR_E4_IDENTITY[vec4].p_vec3.v_present) {
 * >>     ...; // Pointer isn't mapped.
 * >> } else if (!P64_PDIR_E3_IDENTITY[vec4][vec3].p_vec2.v_present) {
 * >>     ...; // Pointer isn't mapped.
 * >> } else if (P64_PDIR_E3_IDENTITY[vec4][vec3].p_1gib.d_1gib_1) {
 * >>     ...; // Pointer is mapped as a 1GiB mapping
 * >> } else if (!P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_vec1.v_present) {
 * >>     ...; // Pointer isn't mapped.
 * >> } else if (P64_PDIR_E2_IDENTITY[vec4][vec3][vec2].p_2mib.d_2mib_1) {
 * >>     ...; // Pointer is mapped as a 2MiB mapping
 * >> } else {
 * >>     // Load the descriptor
 * >>     desc = &P64_PDIR_E1_IDENTITY[vec4][vec3][vec2][vec1];
 * >>     if (!desc->p_4kib.d_present) {
 * >>         ...; // Pointer isn't mapped.
 * >>     } else {
 * >>         ...; // `desc' now points to the descriptor for the `pointer'
 * >>     }
 * >> }
 */
#define P64_PDIR_E1_IDENTITY  (*(p64_pdir_e1_identity_t *)P64_PDIR_E1_IDENTITY_BASE) /* `union p64_pdir_e2::p_e1' */
#define P64_PDIR_E2_IDENTITY  (*(p64_pdir_e2_identity_t *)P64_PDIR_E2_IDENTITY_BASE) /* `union p64_pdir_e3::p_e2' */
#define P64_PDIR_E3_IDENTITY  (*(p64_pdir_e3_identity_t *)P64_PDIR_E3_IDENTITY_BASE) /* `union p64_pdir_e4::p_e3' */
#define P64_PDIR_E4_IDENTITY  (*(p64_pdir_e4_identity_t *)P64_PDIR_E4_IDENTITY_BASE) /* `struct p64_pdir::p_e4' */

#else /* __CC__ */

#define P64_PDIR_E1_IDENTITY  P64_PDIR_E1_IDENTITY_BASE
#define P64_PDIR_E2_IDENTITY  P64_PDIR_E2_IDENTITY_BASE
#define P64_PDIR_E3_IDENTITY  P64_PDIR_E3_IDENTITY_BASE
#define P64_PDIR_E4_IDENTITY  P64_PDIR_E4_IDENTITY_BASE

#endif /* !__CC__ */




/* Define platform-independent symbols. */
#define PAGEDIR_ALIGN P64_PDIR_ALIGN
#define PAGEDIR_SIZE  P64_PDIR_SIZE
#ifdef __CC__
typedef struct p64_pdir pagedir_t;
#endif /* __CC__ */



/* Page protection flags. */
#ifndef PAGEDIR_PROT_MASK
#define PAGEDIR_PROT_EXEC    0x0001 /* Permission bit: Allow execution within the mapping. */
#define PAGEDIR_PROT_WRITE   0x0002 /* Permission bit: Permit write-access to memory within mapping. */
#define PAGEDIR_PROT_READ    0x0004 /* Permission bit: Permit read-access to memory within mapping. */
#define PAGEDIR_PROT_X86_PWT 0x0008 /* P64_PAGE_FPWT */
#define PAGEDIR_PROT_X86_PCD 0x0010 /* P64_PAGE_FPCD */
#define PAGEDIR_PROT_X86_PAT 0x0020 /* P64_PAGE_FPAT_4KIB / P64_PAGE_FPAT_2MIB / P64_PAGE_FPAT_1GIB */
#define PAGEDIR_PROT_MASK    0x003f /* Mask of valid permission bits. */
#endif /* !PAGEDIR_PROT_MASK */


#ifndef PAGEDIR_PAGEALIGNED
#define PAGEDIR_PAGEALIGNED /* Annotation for variables that need to be aligned on page boundaries. */
#endif /* !PAGEDIR_PAGEALIGNED */


/* On x86, the `pagedir_init' function never throws an error. */
#undef ARCH_PAGEDIR_INIT_IS_NOEXCEPT
#define ARCH_PAGEDIR_INIT_IS_NOEXCEPT 1

/* x86 implements the `pagedir_(has|unset)changed' API. */
#undef ARCH_PAGEDIR_HAVE_CHANGED
#define ARCH_PAGEDIR_HAVE_CHANGED 1

/* x86 implements the `pagedir_denywrite' API (delete low-level write permissions). */
#undef ARCH_PAGEDIR_HAVE_DENYWRITE
#define ARCH_PAGEDIR_HAVE_DENYWRITE 1

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
	__asm__ __volatile__("movq %%cr3, %0"
	                     : "=r" (result)
	                     :
	                     : "memory");
	return result;
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(KCALL pagedir_set)(PHYS pagedir_t *__restrict value) {
	__asm__ __volatile__("movq %0, %%cr3"
	                     :
	                     : "r" (value)
	                     : "memory");
}
#endif /* __CC__ */
#endif /* !__INTELLISENSE__ */


/* When more than `ARCH_PAGEDIR_LARGESYNC_THRESHOLD' need to be synced, rather
 * than performing that  number of single-page  TLB invalidations,  invalidate
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

#ifdef __CC__
/* Synchronize the entirety of the current page directory.
 * Note that this function may only sync all user-space mappings. If the
 * intent is to also sync all of kernel-space, `pagedir_syncall()'  must
 * be used instead. */
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(FCALL pagedir_syncall_user)(void) {
	__register u64 temp;
	__asm__ __volatile__("movq %%cr3, %0\n\t"
	                     "movq %0, %%cr3"
	                     : "=&r" (temp));
}

/* Same as `pagedir_syncall_user()', but  also
 * ensures that all of kernel-space is synced. */
FUNDEF NOBLOCK void NOTHROW(FCALL pagedir_syncall)(void);

/* Hybrid of `pagedir_syncall()' and `pagedir_syncall_user()': When the given range
 * overlaps with kernel-space, behave  the same as `pagedir_syncall()',  otherwise,
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
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(FCALL pagedir_syncone)(VIRT void *addr) {
	COMPILER_BARRIER();
	__asm__("invlpg %0" : : "m" (*(u8 *)addr));
	COMPILER_BARRIER();
}

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
			 * fall into  kernel-space  in  this  case! */
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

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_PAGING64_H */
