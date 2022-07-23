/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_PAGING32_PAE_H
#define GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_PAGING32_PAE_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <kos/kernel/memory.h>
#include <kos/kernel/paging.h>

#include <stdbool.h>

#ifndef CONFIG_NO_KERNEL_X86_PAGING_PAE

DECL_BEGIN

/* To differentiate between hints and allocated, but non-present pages, we use this:
 *
 * ```
 *                                                       PAE_PAGE_FPREPARED
 *                                                       |
 *                                                       |         PAE_PAGE_FISAHINT
 *                                                       |         |
 *                                                       |         |PAE_PAGE_FPRESENT
 *                                                       |         ||
 * E XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX1: Page:  4KiB-page (PAE_PAGE_FADDR_4KIB)
 * 1 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX10: Hint:  DATA & PAE_PAGE_FHINT
 *   0000000000000000000000000000000000000000000000000000XXXXXXXXXX00: Unused with meta-data (e.g. `PAE_PAGE_FPREPARED')
 *   0000000000000000000000000000000000000000000000000000000000000000: Unused (PAE_PAGE_ABSENT)
 *    6 6 5 5 5 5 5 4 4 4 4 4 3 3 3 3 3 2 2 2 2 2 1 1 1 1 1 8 6 4 2 0
 *    2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0
 *
 *                                                           PAE_PAGE_F2MIB
 *                                                           |
 *                                                           |      PAE_PAGE_FPRESENT
 *                                                           |      |
 * E XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXXXX1: Page:  Large page mapping PAE_PAGE_FADDR_2MIB
 * 2 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX0XXXXXX1: Owned: page_freeone(DATA & PAE_PAGE_FVECTOR) (present)
 *   0000000000000000000000000000000000000000000000000000000000000000: Unused (PAE_PAGE_ABSENT)
 *    6 6 5 5 5 5 5 4 4 4 4 4 3 3 3 3 3 2 2 2 2 2 1 1 1 1 1 8 6 4 2 0
 *    2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0
 *
 * E XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX1: Owned: page_freeone(DATA & PAE_PAGE_FVECTOR) (present)
 * 3  6 6 5 5 5 5 5 4 4 4 4 4 3 3 3 3 3 2 2 2 2 2 1 1 1 1 1 8 6 4 2 0
 *    2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0 8 6 4 2 0
 * ```
 *
 * NOTE: In the case of E3, all entries (all 4 of them) are always PRESENT,
 *       in order to support identity-mapping, as well as shared kernel-memory:
 *       >> p_e3[3].p_e2[0...507] = KERNEL_SHARE; // Kernel share:     0xc0000000 ... 0xff7fffff
 *       >> p_e3[3].p_e2[508]     = p_e3[0];      // Identity mapping: 0xff800000 ... 0xff9fffff
 *       >> p_e3[3].p_e2[509]     = p_e3[1];      // Identity mapping: 0xffa00000 ... 0xff8fffff
 *       >> p_e3[3].p_e2[510]     = p_e3[2];      // Identity mapping: 0xffc00000 ... 0xffdfffff
 *       >> p_e3[3].p_e2[511]     = p_e3[3];      // Identity mapping: 0xffe00000 ... 0xffffffff
 */

/* The minimum alignment required for pointers passed to `pagedir_maphint()' */
#define PAE_PAGEDIR_MAPHINT_ALIGNMENT  4

#define PAE_PAGE_SHIFT      12 /* Shift to convert between pages and addresses. */
#define PAE_PAGE_ALIGN      __UINT64_C(0x0000000000001000) /* Required page alignment. */
#define PAE_PAGE_SIZE       __UINT64_C(0x0000000000001000) /* Required page size. */
#define PAE_PAGE_FVECTOR    __UINT64_C(0x000ffffffffff000) /* [bit(12:51)] Mask of an inner vector. */
#define PAE_PAGE_FHINT      __UINT64_C(0xfffffffffffffffc) /* Mask of page hints. */
#define PAE_PAGE_FADDR_4KIB __UINT64_C(0x000ffffffffff000) /* Mask of the page address for 1KiB pages. */
#define PAE_PAGE_OFFST_4KIB         __UINT32_C(0x00000fff) /* Offset mask for 1KiB pages. */
#define PAE_PAGE_FADDR_2MIB __UINT64_C(0x000fffffffe00000) /* Mask of the page address for 2MiB pages. */
#define PAE_PAGE_OFFST_2MIB         __UINT32_C(0x001fffff) /* Offset mask for 2MiB pages. */
#define PAE_PAGE_FMASK      __UINT64_C(0xfff0000000000fff) /* Mask of page flag bits. */
#define PAE_PAGE_ABSENT     __UINT64_C(0x0000000000000000) /* Value found in E2 (`union pae_pdir_e2::p_word') to indicate that the E1-vector hasn't been allocated. */

#define PAE_PAGE_FPRESENT   __UINT64_C(0x0000000000000001) /* [bit(0)] The page is present (When not set, cause a PAGEFAULT that may be used for allocate/load-on-read). */
#define PAE_PAGE_FISAHINT   __UINT64_C(0x0000000000000002) /* [bit(1)][valid_if(!PAE_PAGE_FPRESENT)] The page has been hinted. */
#define PAE_PAGE_FWRITE     __UINT64_C(0x0000000000000002) /* [bit(1)] The page is writable. */
#define PAE_PAGE_FUSER      __UINT64_C(0x0000000000000004) /* [bit(2)] User-space may access this page (read, or write). */
#define PAE_PAGE_FPWT       __UINT64_C(0x0000000000000008) /* [bit(3)] Page-level write-through. */
#define PAE_PAGE_FPCD       __UINT64_C(0x0000000000000010) /* [bit(4)] Page-level cache disable. */
#define PAE_PAGE_FACCESSED  __UINT64_C(0x0000000000000020) /* [bit(5)] The page has been read from, or written to. */
#define PAE_PAGE_FDIRTY     __UINT64_C(0x0000000000000040) /* [bit(6)] The page has been written to. (only valid in entries that map physical memory, rather than point to other vectors) */
#define PAE_PAGE_F2MIB      __UINT64_C(0x0000000000000080) /* [bit(7)] Directly map a physical address on level #2 (for use in `union pae_pdir_e2::p_word'). */
#define PAE_PAGE_FGLOBAL    __UINT64_C(0x0000000000000100) /* [bit(8)] Set to optimize mappings that appear at the same location in all
                                                            *          directories it appears inside of (aka: Kernel-allocated stack/memory). */
#define PAE_PAGE_FPREPARED  __UINT64_C(0x0000000000000800) /* [bit(11)][KOS_SPECIFIC] Prevent the associated mapping from being flattened. (May only appear in E1-entries)
                                                            * This flag is used to indicate that the associated page is currently prepared,
                                                            * and that its containing vectors shouldn't be merged before it becomes unprepared. */
#define PAE_PAGE_FPAT_4KIB  __UINT64_C(0x0000000000000080) /* [bit(7)]  Indirectly determines the memory type used to access the 4-KByte page referenced by this entry. */
#define PAE_PAGE_FPAT_2MIB  __UINT64_C(0x0000000000001000) /* [bit(12)] Indirectly determines the memory type used to access the 2-MByte page referenced by this entry. */
#define PAE_PAGE_FNOEXEC    __UINT64_C(0x8000000000000000) /* [bit(63)] Memory within the page cannot be executed. */


#define PAE_PDIR_VEC1INDEX(ptr)  ((__CCAST(u32)(ptr) >> 12) & 0x1ff) /* For `union pae_pdir_e2::p_e1' */
#define PAE_PDIR_VEC2INDEX(ptr)  ((__CCAST(u32)(ptr) >> 21) & 0x1ff) /* For `union pae_pdir_e3::p_e2' */
#define PAE_PDIR_VEC3INDEX(ptr)  ((__CCAST(u32)(ptr) >> 30) & 0x3)   /* For `union pae_pdir::p_e3' */
#define PAE_PDIR_VECADDR(vec3, vec2, vec1) \
	(__CCAST(void *)((__CCAST(u32)(vec3) << 30) | (__CCAST(u32)(vec2) << 21) | (__CCAST(u32)(vec1) << 12)))

/* Pagesizes of different page directory levels. */
#define PAE_PDIR_E1_SIZE     __UINT32_C(0x00001000) /* 4 KiB (Same as `PAGESIZE') */
#define PAE_PDIR_E2_SIZE     __UINT32_C(0x00200000) /* 2 MiB */
#define PAE_PDIR_E3_SIZE     __UINT32_C(0x40000000) /* 1 GiB */

#define PAE_IS_4KIB_ALIGNED(addr) (((addr) & __UINT32_C(0x00000fff)) == 0)
#define PAE_IS_2MIB_ALIGNED(addr) (((addr) & __UINT32_C(0x001fffff)) == 0)

/* Return the in-page offset of a regular pointer mapping,
 * or  one  that  has  been  mapped  within  a  2MiB page. */
#define PAE_PDIR_PAGEINDEX_4KIB(ptr) (__CCAST(u64)(__CCAST(uintptr_t)(ptr) & 0xfff))
#define PAE_PDIR_PAGEINDEX_2MIB(ptr) (__CCAST(u64)(__CCAST(uintptr_t)(ptr) & 0x1fffff))

#define PAE_PDIR_ALIGN  4096 /* Alignment required for instances of `struct pae_pdir' */
#define PAE_PDIR_SIZE   32   /* The total size of `struct pae_pdir' in bytes. */



#ifdef __CC__
union pae_pdir_e1 {
	/* TIER#1 page-directory entry:
	 *   - PAE Page-Table Entry that Maps a 4-KByte Page */
	u64                      p_word;     /* Mapping data. */
#define PAE_PDIR_E1_IS1KIB(e1_word)    ((e1_word) & PAE_PAGE_FPRESENT)
#define PAE_PDIR_E1_ISHINT(e1_word)    (((e1_word) & (PAE_PAGE_FPRESENT | PAE_PAGE_FISAHINT)) == PAE_PAGE_FISAHINT)
#define PAE_PDIR_E1_ISUNUSED(e1_word)  (((e1_word) & (PAE_PAGE_FPRESENT | PAE_PAGE_FISAHINT)) == 0)
	struct {
		u64          d_present : 1;      /* PAE_PAGE_FPRESENT */
		u64          d_writable : 1;     /* [valid_if(d_present)] PAE_PAGE_FWRITE */
		u64          d_user : 1;         /* [valid_if(d_present)] PAE_PAGE_FUSER */
		u64          d_pwt : 1;          /* [valid_if(d_present)] PAE_PAGE_FPWT */
		u64          d_pcd : 1;          /* [valid_if(d_present)] PAE_PAGE_FPCD */
		u64          d_accessed : 1;     /* [valid_if(d_present)] PAE_PAGE_FACCESSED */
		u64          d_dirty : 1;        /* [valid_if(d_present)] PAE_PAGE_FDIRTY */
		u64          d_pat : 1;          /* [valid_if(d_present)] PAE_PAGE_FPAT_4KIB */
		u64          d_global : 1;       /* [valid_if(d_present)] PAE_PAGE_FGLOBAL */
		u64          d_unused1_ign : 3;  /* [valid_if(d_present)] Ignored...  (0x200, 0x400, 0x800) */
		u64          d_addr : 40;        /* [valid_if(d_present)] PAE_PAGE_FADDR_4KIB */
		u64          d_reserved : 11;    /* [valid_if(d_present)] Reserved...  (Bits 52:62) */
		u64          d_noexec : 1;       /* [valid_if(d_present)] PAE_PAGE_FNOEXEC */
	} p_4kib;
};

union pae_pdir_e2 {
	/* TIER#2 page-directory entry:
	 *   - PAE Page-Directory Entry that Maps a 2-MByte Page
	 *   - PAE Page-Directory Entry that References a Page Table */
	u64                      p_word;     /* Mapping data. */
#define PAE_PDIR_E2_ISVEC1(e2_word)       (((e2_word) & (PAE_PAGE_FPRESENT | PAE_PAGE_F2MIB)) == PAE_PAGE_FPRESENT)
#define PAE_PDIR_E2_IS2MIB(e2_word)       (((e2_word) & (PAE_PAGE_FPRESENT | PAE_PAGE_F2MIB)) == (PAE_PAGE_FPRESENT | PAE_PAGE_F2MIB))
#define PAE_PDIR_E2_ISUNUSED(e2_word)     ((e2_word) == PAE_PAGE_ABSENT)
	PHYS union pae_pdir_e1 (*p_e1)[512]; /* [MASK(PAE_PAGE_FVECTOR)]
	                                      * [owned][valid_if(PAE_PDIR_E2_ISVEC1(p_word))]
	                                      * _Physical_ pointer to a level #1 paging vector. */
	struct ATTR_PACKED {
		u64          v_present : 1;      /* PAE_PAGE_FPRESENT */
		u64          v_writable : 1;     /* [valid_if(v_present)] PAE_PAGE_FWRITE */
		u64          v_user : 1;         /* [valid_if(v_present)] PAE_PAGE_FUSER */
		u64          v_pwt : 1;          /* [valid_if(v_present)] PAE_PAGE_FPWT */
		u64          v_pcd : 1;          /* [valid_if(v_present)] PAE_PAGE_FPCD */
		u64          v_accessed : 1;     /* [valid_if(v_present)] PAE_PAGE_FACCESSED */
		u64          v_dirty_ign : 1;    /* [valid_if(v_present)] Ignored...  (PAE_PAGE_FDIRTY) */
		u64          v_2mib_0 : 1;       /* [valid_if(v_present)] Must be 0  (PAE_PAGE_F2MIB) */
		u64          v_global_ign : 1;   /* [valid_if(v_present)] Ignored...  (PAE_PAGE_FGLOBAL) */
		u64          v_unused1_ign : 3;  /* [valid_if(v_present)] Ignored...  (0x200, 0x400, 0x800) */
		u64          v_e1 : 40;          /* [valid_if(v_present)][TYPE(union pae_pdir_e1(*)[512])][owned] PAE_PAGE_FVECTOR */
		u64          d_reserved2_0 : 11; /* [valid_if(v_present)] Must be 0  (Reserved...) */
		u64          v_noexec : 1;       /* [valid_if(v_present)] PAE_PAGE_FNOEXEC */
	} p_vec1;
	struct {
		u64          d_present : 1;      /* PAE_PAGE_FPRESENT */
		u64          d_writable : 1;     /* [valid_if(d_present)] PAE_PAGE_FWRITE */
		u64          d_user : 1;         /* [valid_if(d_present)] PAE_PAGE_FUSER */
		u64          d_pwt : 1;          /* [valid_if(d_present)] PAE_PAGE_FPWT */
		u64          d_pcd : 1;          /* [valid_if(d_present)] PAE_PAGE_FPCD */
		u64          d_accessed : 1;     /* [valid_if(d_present)] PAE_PAGE_FACCESSED */
		u64          d_dirty : 1;        /* [valid_if(d_present)] PAE_PAGE_FDIRTY */
		u64          d_2mib_1 : 1;       /* [valid_if(d_present)] Must be 1  (PAE_PAGE_F2MIB) */
		u64          d_global : 1;       /* [valid_if(d_present)] PAE_PAGE_FGLOBAL */
		u64          d_unused1_ign : 3;  /* [valid_if(d_present)] Ignored...  (0x200, 0x400, 0x800) */
		u64          d_pat : 1;          /* [valid_if(d_present)] PAE_PAGE_FPAT_2MIB */
		u64          d_reserved1_0 : 8;  /* [valid_if(d_present)] Must be 0  (Reserved...) */
		u64          d_addr : 31;        /* [valid_if(d_present)] PAE_PAGE_FADDR_2MIB */
		u64          d_reserved2_0 : 11; /* [valid_if(v_present)] Must be 0  (Reserved...) */
		u64          d_noexec : 1;       /* [valid_if(d_present)] PAE_PAGE_FNOEXEC */
	} p_2mib; /* [valid_if(p_2mib.d_2mib_1 == 1)] */
};

union pae_pdir_e3 {
	/* TIER#3 page-directory entry:
	 *   - PAE Page-Directory-Pointer-Table Entry (PDPTE) */
	u64                      p_word;     /* Mapping data. */
	PHYS union pae_pdir_e2 (*p_e2)[512]; /* [MASK(PAE_PAGE_FVECTOR)][owned][const]
	                                      * [valid_if(PAE_PAGE_FPRESENT)]
	                                      * _Physical_ pointer to a level #2 paging vector.
	                                      * NOTE: Even  though `PAE_PAGE_FPRESENT' is needed for validity,
	                                      *       it may be assumed that that flag is _always_ set for all
	                                      *       E3 entries existing in any given PAE-page-directory */
	struct ATTR_PACKED {
		u64         v_present : 1;       /* PAE_PAGE_FPRESENT */
		u64         v_reserved1_0 : 2;   /* [valid_if(v_present)][bit(1:2)]   Reserved (must be 0) */
		u64         v_pwt : 1;           /* [valid_if(v_present)][bit(3)]     PAE_PAGE_FPWT */
		u64         v_pcd : 1;           /* [valid_if(v_present)][bit(4)]     PAE_PAGE_FPCD */
		u64         v_reserved2_0 : 4;   /* [valid_if(v_present)][bit(5:8)]   Reserved (must be 0) */
		u64         v_ignored : 3;       /* [valid_if(v_present)][bit(9:11)]  Ignored */
		u64         v_e2 : 40;           /* [valid_if(v_present)][bit(12:51)] PAE_PAGE_FVECTOR */
		u64         v_reserved3_0 : 12;  /* [valid_if(v_present)][bit(52:63)] Reserved (must be 0) */
	} p_vec2;
};



struct pae_pdir {
	/* Page-directory (4-entry/32-byte vector of `union pae_pdir_e3') */
	union pae_pdir_e3 p_e3[4]; /* NOTE: All entries are always pre-allocated! */
};

#endif /* __CC__ */




#define PAE_MMAN_KERNEL_PDIR_IDENTITY_BASE __UINT32_C(0xff800000) /* E1 vectors are mapped here. */
#define PAE_MMAN_KERNEL_PDIR_IDENTITY_SIZE __UINT32_C(0x00800000) /* 8MiB */
#define PAE_MMAN_KERNEL_PDIR_RESERVED_BASE __UINT32_C(0xff800000) /* Start of the address range reserved for page-directory self-modifications. */
#define PAE_MMAN_KERNEL_PDIR_RESERVED_SIZE __UINT32_C(0x00800000) /* 8MiB */

#define PAE_PDIR_E1_IDENTITY_BASE __UINT32_C(0xff800000) /* E1 vectors are mapped here. */
#define PAE_PDIR_E2_IDENTITY_BASE __UINT32_C(0xffffc000) /* E2 vectors are mapped here. */
#define PAE_PDIR_E3_IDENTITY_BASE __UINT32_C(0xffffffe0) /* E3 vectors are mapped here. */


#ifdef __CC__
typedef union pae_pdir_e1
pae_pdir_e1_identity_t[4   /* PAE_PDIR_VEC3INDEX(pointer) */]
                      [512 /* PAE_PDIR_VEC2INDEX(pointer) */]
                      [512 /* PAE_PDIR_VEC1INDEX(pointer) */];
typedef union pae_pdir_e2
pae_pdir_e2_identity_t[4   /* PAE_PDIR_VEC3INDEX(pointer) */]
                      [512 /* PAE_PDIR_VEC2INDEX(pointer) */];
typedef union pae_pdir_e3
pae_pdir_e3_identity_t[4   /* PAE_PDIR_VEC3INDEX(pointer) */];

/* E1 identity   mapping   access   for   the   current   page   directory.
 *    Index #0: VEC3 -- The  same index as used in  `struct pae_pdir::p_e3'
 *    Index #1: VEC2 -- The same index as used in `union pae_pdir_e3::p_e2'
 *    Index #2: VEC1 -- The same index as used in `union pae_pdir_e2::p_e1'
 * Example:
 * >> VIRT void *pointer = get_pointer();
 * >> union pae_pdir_e1 *desc;
 * >> unsigned int vec3 = PAE_PDIR_VEC3INDEX(pointer);
 * >> unsigned int vec2 = PAE_PDIR_VEC2INDEX(pointer);
 * >> unsigned int vec1 = PAE_PDIR_VEC1INDEX(pointer);
 * >> assert(PAE_PDIR_E3_IDENTITY[vec3].p_vec2.v_present);
 * >> if (!PAE_PDIR_E2_IDENTITY[vec3][vec2].p_vec1.v_present) {
 * >>     ...; // Pointer isn't mapped.
 * >> } else if (PAE_PDIR_E2_IDENTITY[vec3][vec2].p_2mib.d_2mib_1) {
 * >>     ...; // Pointer is mapped as a 2MiB mapping
 * >> } else {
 * >>     // Load the descriptor
 * >>     desc = &PAE_PDIR_E1_IDENTITY[vec3][vec2][vec1];
 * >>     if (!desc->p_4kib.d_present) {
 * >>         ...; // Pointer isn't mapped.
 * >>     } else {
 * >>         ...; // `desc' now points to the descriptor for the `pointer'
 * >>     }
 * >> }
 */
#define PAE_PDIR_E1_IDENTITY  (*(pae_pdir_e1_identity_t *)PAE_PDIR_E1_IDENTITY_BASE) /* `union pae_pdir_e2::p_e1' */
#define PAE_PDIR_E2_IDENTITY  (*(pae_pdir_e2_identity_t *)PAE_PDIR_E2_IDENTITY_BASE) /* `union pae_pdir_e3::p_e2' */
#define PAE_PDIR_E3_IDENTITY  (*(pae_pdir_e3_identity_t *)PAE_PDIR_E3_IDENTITY_BASE) /* `struct pae_pdir::p_e3' */

#else /* __CC__ */

#define PAE_PDIR_E1_IDENTITY  PAE_PDIR_E1_IDENTITY_BASE
#define PAE_PDIR_E2_IDENTITY  PAE_PDIR_E2_IDENTITY_BASE
#define PAE_PDIR_E3_IDENTITY  PAE_PDIR_E3_IDENTITY_BASE

#endif /* !__CC__ */



/* A special value that is never returned by `pae_pagedir_push_mapone()' */
#define SIZEOF_PAE_PAGEDIR_PUSHVAL  8
#define PAE_PAGEDIR_PUSHVAL_INVALID (__CCAST(pae_pagedir_pushval_t)-1)
#ifdef __CC__
typedef u64 pae_pagedir_pushval_t;
#endif /* __CC__ */


#if defined(__CC__) && defined(BUILDING_KERNEL_CORE)

#ifndef PAGEDIR_PAGEALIGNED
#define PAGEDIR_PAGEALIGNED /* Annotation for variables that need to be aligned on page boundaries. */
#endif /* !PAGEDIR_PAGEALIGNED */

#ifndef __pagedir_prot_t_defined
#define __pagedir_prot_t_defined
typedef u16 pagedir_prot_t;
#endif /* !__pagedir_prot_t_defined */

/* Initialize the given page directory.
 * The caller is required to allocate the page directory
 * controller itself, which  must be  aligned and  sized
 * according to `PAGEDIR_ALIGN' and `PAGEDIR_SIZE'. */
INTDEF NONNULL((1)) void FCALL
pae_pagedir_init(VIRT struct pae_pdir *__restrict self)
		THROWS(E_BADALLOC);

/* Finalize a given page directory. */
INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL pae_pagedir_fini)(VIRT struct pae_pdir *__restrict self,
                                PHYS struct pae_pdir *phys_self);

/* Prepare the page directory for a future map() operation.
 * The full cycle of a single mapping then looks like this:
 * >> pae_pagedir_prepare(...);
 * >> pae_pagedir_map(...);
 * >> pae_pagedir_unmap(...);
 * >> pae_pagedir_unprepare(...);
 * @return: true:  Successfully allocated structures required for creating mappings.
 * @return: false: Insufficient physical memory to prepare mappings. */
INTDEF NOBLOCK WUNUSED bool
NOTHROW(FCALL pae_pagedir_prepareone)(PAGEDIR_PAGEALIGNED VIRT void *addr);
INTDEF NOBLOCK WUNUSED bool
NOTHROW(FCALL pae_pagedir_prepare)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                   PAGEDIR_PAGEALIGNED size_t num_bytes);
INTDEF NOBLOCK void
NOTHROW(FCALL pae_pagedir_unprepareone)(PAGEDIR_PAGEALIGNED VIRT void *addr);
INTDEF NOBLOCK void
NOTHROW(FCALL pae_pagedir_unprepare)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                     PAGEDIR_PAGEALIGNED size_t num_bytes);


/* Set a mapping hint for pages apart of the given virtual memory range.
 * Mapping hints are overwritten once a  page has been mapped, and  when
 * not specified, will default to `NULL'.
 * Their main purpose is to be accessible through atomic means, allowing
 * them to be used by the PAGE_FAULT handler, while still ensuring  that
 * access remains non-blocking. */
INTDEF NOBLOCK void
NOTHROW(FCALL pae_pagedir_maphintone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                      VIRT /*ALIGNED(P32_PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint);
INTDEF NOBLOCK void
NOTHROW(FCALL pae_pagedir_maphint)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                   PAGEDIR_PAGEALIGNED size_t num_bytes,
                                   VIRT /*ALIGNED(P32_PAGEDIR_MAPHINT_ALIGNMENT)*/ void *hint);

/* Return the hint of the given page, or NULL if no hint has been mapped. */
INTDEF NOBLOCK WUNUSED void *
NOTHROW(FCALL pae_pagedir_gethint)(PAGEDIR_PAGEALIGNED VIRT void *addr);

/* Create/delete a page-directory mapping.
 * @param: prot: A set of `PAGEDIR_PROT_*' detailing how memory should be mapped. */
INTDEF NOBLOCK void
NOTHROW(FCALL pae_pagedir_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                  PAGEDIR_PAGEALIGNED PHYS physaddr_t phys,
                                  pagedir_prot_t prot);
INTDEF NOBLOCK void
NOTHROW(FCALL pae_pagedir_map)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                               PAGEDIR_PAGEALIGNED size_t num_bytes,
                               PAGEDIR_PAGEALIGNED PHYS physaddr_t phys,
                               pagedir_prot_t prot);

/* Special variants of `pagedir_mapone()' that should be used to
 * temporary override the  mapping of a  single, prepared  page.
 * These functions are  mainly intended for  use with `this_trampoline_page',  allowing
 * each  thread to push/pop its trampoline page, with doing so actually being an atomic
 * operation in the sense that the data is entirely thread-private, while modifications
 * do not require any kind of lock.
 * NOTE: If the page had been mapped, `pagedir_pop_mapone()' will automatically sync the page. */
INTDEF NOBLOCK WUNUSED pae_pagedir_pushval_t
NOTHROW(FCALL pae_pagedir_push_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                       PAGEDIR_PAGEALIGNED PHYS physaddr_t phys,
                                       pagedir_prot_t prot);
INTDEF NOBLOCK void
NOTHROW(FCALL pae_pagedir_pop_mapone)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                      pae_pagedir_pushval_t backup);

/* Unmap pages from the given address range. (requires that the given area be prepared) */
INTDEF NOBLOCK void
NOTHROW(FCALL pae_pagedir_unmapone)(PAGEDIR_PAGEALIGNED VIRT void *addr);
INTDEF NOBLOCK void
NOTHROW(FCALL pae_pagedir_unmap)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                 PAGEDIR_PAGEALIGNED size_t num_bytes);

/* Remove write-permissions from the given address range. (requires that the given area be prepared) */
INTDEF NOBLOCK void
NOTHROW(FCALL pae_pagedir_denywriteone)(PAGEDIR_PAGEALIGNED VIRT void *addr);
INTDEF NOBLOCK void
NOTHROW(FCALL pae_pagedir_denywrite)(PAGEDIR_PAGEALIGNED VIRT void *addr,
                                     PAGEDIR_PAGEALIGNED size_t num_bytes);

/* Unmap the entirety of user-space.
 * NOTE: Unlike all other unmap() functions, this one guaranties that it
 *       can perform the task without  needing to allocate more  memory! */
INTDEF NOBLOCK void NOTHROW(FCALL pae_pagedir_unmap_userspace)(void);
INTDEF NOBLOCK void NOTHROW(FCALL pae_pagedir_unmap_userspace_nosync)(void);

/* Translate a virtual address into its physical counterpart. */
INTDEF NOBLOCK WUNUSED PHYS physaddr_t NOTHROW(FCALL pae_pagedir_translate)(VIRT void const *addr);

/* Check if the given page is mapped. */
INTDEF NOBLOCK WUNUSED bool NOTHROW(FCALL pae_pagedir_ismapped)(VIRT void const *addr);
INTDEF NOBLOCK WUNUSED bool NOTHROW(FCALL pae_pagedir_iswritable)(VIRT void *addr);
INTDEF NOBLOCK WUNUSED bool NOTHROW(FCALL pae_pagedir_isuseraccessible)(VIRT void const *addr);
INTDEF NOBLOCK WUNUSED bool NOTHROW(FCALL pae_pagedir_isuserwritable)(VIRT void *addr);

/* TODO: Figure out a better design for these functions
 *       The current system is written under the assumption that 2MiB pages don't exist... */
INTDEF NOBLOCK WUNUSED bool NOTHROW(FCALL pae_pagedir_haschanged)(VIRT void *addr);
INTDEF NOBLOCK void NOTHROW(FCALL pae_pagedir_unsetchanged)(VIRT void *addrvpage);

#endif /* __CC__ && BUILDING_KERNEL_CORE */



DECL_END

#endif /* !CONFIG_NO_KERNEL_X86_PAGING_PAE */

#endif /* !GUARD_KERNEL_INCLUDE_I386_KOS_KERNEL_ARCH_PAGING32_PAE_H */
