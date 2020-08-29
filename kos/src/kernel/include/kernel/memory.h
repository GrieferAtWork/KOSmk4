/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MEMORY_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MEMORY_H 1

#include <kernel/compiler.h>

#include <kernel/arch/memory.h>
#include <kernel/paging.h>
#include <kernel/types.h>

#include <hybrid/__assert.h>

#include <stdbool.h>

/* Physical memory management. */

DECL_BEGIN

#if defined(__INTELLISENSE__) && defined(__CC__) && defined(__cplusplus)
extern "C++" {
vm_phys_t (page2addr)(pageptr_t pageptr);
pageptr_t (addr2page)(vm_phys_t physaddr);
pageptr_t (addr2page)(uintptr_t physaddr);
u32 (page2addr32)(pageptr_t pageptr);
}
#define page2addr page2addr
#define addr2page addr2page
#define page2addr32 page2addr32
#else /* __INTELLISENSE__ && __CC__ && __cplusplus */
#define page2addr(pageptr)   (__CCAST(vm_phys_t)(pageptr) * PAGESIZE)
#define addr2page(physaddr)  (__CCAST(pageptr_t)((physaddr) / PAGESIZE))
#define page2addr32(pageptr) (__CCAST(u32)(pageptr) * PAGESIZE)
#endif /* !__INTELLISENSE__ || !__CC__ || !__cplusplus */

#ifndef PAGEPTR_INVALID
#define PAGEPTR_INVALID (__CCAST(pageptr_t)-1)
#endif /* !PAGEPTR_INVALID */

/* A page pointer is just like a normal physical pointer, but divided by PAGESIZE */
#define FORMAT_PAGECNT_T "%Iu"
#ifdef __CC__
typedef size_t pagecnt_t;
#endif /* __CC__ */


#define PMEMBANK_TYPE_UNDEF      0 /* Undefined memory (Handled identically to `PMEMBANK_TYPE_BADRAM') */
#define PMEMBANK_TYPE_RAM        1 /* [USE] Dynamic; aka. RAM memory (Main source of memory for `page_malloc') */
#ifdef CONFIG_BUILDING_KERNEL_CORE
#define PMEMBANK_TYPE_PRESERVE   2 /* [USE_LATER_0|MAP] Preserve the original content of this memory until
                                    * `mem_unpreserve()' is called, at which point the memory will be
                                    * transformed into `PMEMBANK_TYPE_RAM', and made available to the physical
                                    * memory allocator. */
#define PMEMBANK_TYPE_ALLOCATED  3 /* [USE_LATER_1|MAP] Same as 'PMEMBANK_TYPE_RAM', but don't make memory available to `page_malloc' */
#endif /* CONFIG_BUILDING_KERNEL_CORE */
#define PMEMBANK_TYPE_KFREE      4 /* [USE_LATER_2|MAP] Kernel memory later turned into `PMEMBANK_TYPE_RAM' (The `.free' section...) */
#define PMEMBANK_TYPE_KERNEL     5 /* [MAP] Kernel core memory (mapped, not used) */
#define PMEMBANK_TYPE_NVS        6 /* Non-volatile memory (that is: memory that doesn't get wiped after shutdown) */
#define PMEMBANK_TYPE_DEVICE     7 /* Device memory (mapped, but not used as RAM) */
#define PMEMBANK_TYPE_BADRAM     8 /* Broken memory (Neither mapped nor used, but known to be present) */
#define PMEMBANK_TYPE_COUNT      9 /* Amount of known memory types. */

#ifdef __CC__
struct pmembank {
	union {
		uintptr_t mb_startptr; /* Memory block starting address. */
		vm_phys_t mb_start;    /* Memory block starting address. */
	};
	u16           mb_type;     /* Memory bank type. (One of `PMEMBANK_TYPE_*') */
	u16           mb_pad[(sizeof(vm_phys_t) - 2) / 2]; /* ... */
};
#define PMEMBANK_INIT(startptr, type) { { startptr }, type, { } }

#define PMEMBANK_STARTADDR(x) ((x).mb_start)
#define PMEMBANK_MINADDR(x)   ((x).mb_start)
#define PMEMBANK_MAXADDR(x)   ((&(x))[1].mb_start - 1)
#define PMEMBANK_ENDADDR(x)   ((&(x))[1].mb_start)
#define PMEMBANK_SIZE(x)      (PMEMBANK_ENDADDR(x) - PMEMBANK_STARTADDR(x))
#define PMEMBANK_STARTPAGE(x) ((pageptr_t)((PMEMBANK_STARTADDR(x) + PAGESIZE - 1) / PAGESIZE))
#define PMEMBANK_MINPAGE(x)   ((pageptr_t)((PMEMBANK_STARTADDR(x) + PAGESIZE - 1) / PAGESIZE))
#define PMEMBANK_MAXPAGE(x)   ((pageptr_t)((PMEMBANK_ENDADDR(x) / PAGESIZE) - 1))
#define PMEMBANK_ENDPAGE(x)   ((pageptr_t)(PMEMBANK_ENDADDR(x) / PAGESIZE))
#define PMEMBANK_NUMPAGES(x)  ((size_t)(PMEMBANK_ENDPAGE(x) - PMEMBANK_STARTPAGE(x)))

struct pmeminfo {
	vm_phys_t        mb_total[PMEMBANK_TYPE_COUNT]; /* [const] The total number of bytes corresponding to certain banks. */
	size_t           mb_bankc;                      /* [const] Total number of memory banks. */
	struct pmembank *mb_banks;                      /* [const] Vector of memory banks. */
};

DATDEF char const pmembank_type_names[PMEMBANK_TYPE_COUNT][16];
DATDEF struct pmeminfo minfo; /* Physical memory info. */

#ifdef CONFIG_BUILDING_KERNEL_CORE
/* Returns the total number of usable pages of RAM */
INTDEF FREE ATTR_PURE size_t
NOTHROW(KCALL minfo_usable_ram_pages)(void);

/* Add information about a new member bank / region. */
INTDEF FREE void NOTHROW(KCALL minfo_addbank)(vm_phys_t start, vm_phys_t size, u16 type);

/* Construct memory zones from memory info. */
INTDEF FREE void NOTHROW(KCALL kernel_initialize_minfo_makezones)(void);

/* Relocate `minfo', as well as `mzones' data to a more appropriate location
 * after `kernel_initialize_minfo_makezones()' has been called, and the kernel
 * VM has been cleaned from unused memory mappings.
 * Before this function is called, all memory information still resides at a
 * location where its physical address is relative to its virtual, just like
 * any other kernel data. However, since that can literally be anywhere in
 * virtual memory, it can easily (and accidentally) interfere with memory
 * layout expectancies of other early-boot systems.
 * Because of this, we try to relocate memory information into higher memory
 * as soon as this becomes possible, thus keeping it from randomly showing up
 * and causing problems for other code. */
INTDEF FREE void NOTHROW(KCALL kernel_initialize_minfo_relocate)(void);

/* Release all memory previously marked as `PMEMBANK_TYPE_PRESERVE' or
 * `PMEMBANK_TYPE_ALLOCATED', and page_free() all whole pages touched
 * by mappings of type `PMEMBANK_TYPE_PRESERVE' (unless the same page
 * also contains another mapping of type `PMEMBANK_TYPE_ALLOCATED').
 * Afterwards, transform memory information for either type of memory
 * bank into `PMEMBANK_TYPE_RAM', and (when possible) merge adjacent
 * banks of identical typing. */
INTDEF FREE void NOTHROW(KCALL minfo_release_preservations)(void);
#endif /* CONFIG_BUILDING_KERNEL_CORE */




struct pmemstat {
	pagecnt_t  ps_free;  /* Amount of free pages (including z-pages). */
	pagecnt_t  ps_zfree; /* Amount of free zero-pages. */
	pagecnt_t  ps_used;  /* Amount of used pages. */
};
#endif /* __CC__ */


#define PMEMZONE_ISFREEBIT   0 /* BIT: 1 -- The page is free, 0 -- The page is being used */
#define PMEMZONE_ISUNDFBIT   1 /* BIT: 1 -- The contents of the page are undefined, 0 -- The page contains only 0-bits. */
#define PMEMZONE_BITSPERPAGE 2 /* Number of bits per page. */
#define PMEMZONE_ISFREEMASK  0x01
#define PMEMZONE_ISUNDFMASK  0x02

#ifdef __CC__
struct pmemzone {
	struct pmemzone *mz_prev;    /* [0..1][const] Pointer to the previous zone. */
	struct pmemzone *mz_next;    /* [0..1][const] Pointer to the next zone. */
	pageptr_t        mz_start;   /* [const] Start page number. */
	pageptr_t        mz_max;     /* [const] Max page still apart of this zone. */
	pageptr_t        mz_rmax;    /* [const][== (mz_max - mz_start)] Zone-relative index of the max page. */
	WEAK pageptr_t   mz_fmax;    /* The zone-relative address of the greatest free page (used as hint to the allocator). */
	WEAK pagecnt_t   mz_cfree;   /* The number of free pages within this zone. */
	WEAK pagecnt_t   mz_qfree;   /* The number of free pages within this zone that aren't initialized. */
	uintptr_t        mz_zero;    /* [const] Always 0 */
	COMPILER_FLEXIBLE_ARRAY(uintptr_t, mz_free);
	                             /* [((mz_rmax + 1) * PMEMZONE_BITSPERPAGE) / BITS_PER_POINTER] Bitset of free pages
	                              * NOTE: Modifications are performed using atomic instructions. */
//	uintptr_t        mz_zero2;   /* [const] Always 0 */
};
#define PMEMZONE_LENGTHOF_BITSET(num_pages) \
	(((num_pages) * PMEMZONE_BITSPERPAGE) / BITS_PER_POINTER)
#define PMEMZONE_SIZEOF_BITSET(num_pages) \
	((PMEMZONE_LENGTHOF_BITSET(num_pages) + 1) * sizeof(uintptr_t))
#define PMEMZONE_SIZEOF(num_pages) \
	(COMPILER_OFFSETOF(struct pmemzone, mz_free) + PMEMZONE_SIZEOF_BITSET(num_pages))



struct pmem {
	size_t                  pm_zonec; /* [!0] Amount of memory regions. */
	struct pmemzone        *pm_last;  /* [1..1][const][== pm_zones[pm_zonec - 1]] A pointer to the last memory zone. */
	struct pmemzone *const *pm_zones; /* [1..1][const][1..1pm_zonec] Vector of memory zones.
	                                   * NOTE: Ordered by ascending starting address. */
};

DATDEF struct pmem mzones;

LOCAL NOBLOCK ATTR_RETNONNULL WUNUSED struct pmemzone *
NOTHROW(KCALL page_getzone)(pageptr_t ptr) {
	struct pmemzone *zone;
	zone = mzones.pm_last;
	while (ptr > zone->mz_max) {
		__hybrid_assert(zone->mz_prev);
		zone = zone->mz_prev;
	}
	__hybrid_assert(ptr >= zone->mz_start);
	return zone;
}



/* Allocate `num_pages' continuous pages of physical memory and return their page number.
 * WARNING: Physical memory cannot be dereferenced prior to being mapped.
 * @return: * :              The starting page number of the newly allocated memory range.
 * @return: PAGEPTR_INVALID: The allocation failed. */
FUNDEF NOBLOCK WUNUSED pageptr_t NOTHROW(KCALL page_mallocone)(void);
#ifndef __NO_PAGE_MALLOC_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK WUNUSED pageptr_t NOTHROW(KCALL __os_page_malloc)(pagecnt_t num_pages) ASMNAME("page_malloc");
FORCELOCAL ATTR_ARTIFICIAL NOBLOCK WUNUSED pageptr_t
NOTHROW(KCALL page_malloc)(pagecnt_t num_pages) {
	if (__builtin_constant_p(num_pages) && num_pages == 1)
		return page_mallocone();
	return __os_page_malloc(num_pages);
}
#else /* !__NO_PAGE_MALLOC_CONSTANT_P_WRAPPERS */
FUNDEF NOBLOCK WUNUSED pageptr_t NOTHROW(KCALL page_malloc)(pagecnt_t num_pages);
#endif /* __NO_PAGE_MALLOC_CONSTANT_P_WRAPPERS */


/* Allocate at least `min_pages', and at most `max_pages',
 * writing the actual number of pages allocated to `res_pages'.
 *  - This function will try to serve the request to allocate `max_pages',
 *    but will prefer to return the first block of free consecutive pages with
 *    a length of at least `min_pages', thus preventing memory fragmentation by
 *    using up small memory blocks that might otherwise continue going unused.
 * @return: * :              The starting page number of the newly allocated memory range.
 * @return: PAGEPTR_INVALID: The allocation failed. */
FUNDEF NOBLOCK WUNUSED NONNULL((3)) pageptr_t
NOTHROW(KCALL page_malloc_part)(pagecnt_t min_pages, pagecnt_t max_pages,
                                pagecnt_t *__restrict res_pages);

/* Try to allocate the given page.
 * @return: * : One of `PAGE_MALLOC_AT_*' */
FUNDEF NOBLOCK WUNUSED unsigned int
NOTHROW(KCALL page_malloc_at)(pageptr_t ptr);
#endif /* __CC__ */
#define PAGE_MALLOC_AT_SUCCESS   0 /* Successfully allocated the page. */
#define PAGE_MALLOC_AT_NOTMAPPED 1 /* The specified page is not mapped. */
#define PAGE_MALLOC_AT_NOTFREE   2 /* The specified page has already been allocated. */

#ifdef __CC__
/* Similar to `page_malloc()' / `page_malloc_part()', but only
 * allocate memory from between the two given page addresses, such
 * that all allocated pages are located within the specified range.
 * @assume(return == PAGEPTR_INVALID ||
 *        (return >= min_page &&
 *         return + num_pages - 1 <= max_page)); */
FUNDEF NOBLOCK WUNUSED pageptr_t
NOTHROW(KCALL page_malloc_between)(pageptr_t min_page, pageptr_t max_page,
                                   pagecnt_t num_pages);
FUNDEF NOBLOCK WUNUSED NONNULL((5)) pageptr_t
NOTHROW(KCALL page_malloc_part_between)(pageptr_t min_page, pageptr_t max_page,
                                        pagecnt_t min_pages, pagecnt_t max_pages,
                                        pagecnt_t *__restrict res_pages);

#if __SIZEOF_VM_PHYS_T__ > 4
#define page_malloc32(num_pages)                           \
	page_malloc_between(addr2page(__UINT32_C(0x00000000)), \
	                    addr2page(__UINT32_C(0xffffffff)), \
	                    num_pages)
#define page_mallocone32() page_malloc32(1)
#else /* __SIZEOF_VM_PHYS_T__ > 4 */
#define page_malloc32(num_pages) page_malloc(num_pages)
#define page_mallocone32()       page_mallocone()
#endif /* __SIZEOF_VM_PHYS_T__ <= 4 */

/* Free a given physical address range.
 * The caller is responsible to ensure that the given range has previously been allocated. */
FUNDEF NOBLOCK void NOTHROW(KCALL page_freeone)(pageptr_t base);
#ifndef __NO_PAGE_MALLOC_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK void NOTHROW(KCALL __os_page_free)(pageptr_t base, pagecnt_t num_pages) ASMNAME("page_free");
FORCELOCAL ATTR_ARTIFICIAL NOBLOCK void
NOTHROW(KCALL page_free)(pageptr_t base, pagecnt_t num_pages) {
	if (__builtin_constant_p(num_pages) && num_pages == 1) {
		page_freeone(base);
	} else {
		__os_page_free(base, num_pages);
	}
}
#else /* !__NO_PAGE_MALLOC_CONSTANT_P_WRAPPERS */
FUNDEF NOBLOCK void NOTHROW(KCALL page_free)(pageptr_t base, pagecnt_t num_pages);
#endif /* __NO_PAGE_MALLOC_CONSTANT_P_WRAPPERS */

/* Similar to `page_free()', however set the is-zero-bit for all pages. */
FUNDEF NOBLOCK void
NOTHROW(KCALL page_cfree)(pageptr_t base, pagecnt_t num_pages);

/* Similar to `page_free()', however set the is-zero-bit for pages where `page_iszero()' is true. */
FUNDEF NOBLOCK void
NOTHROW(KCALL page_ccfree)(pageptr_t base, pagecnt_t num_pages);

/* Combination of `page_free()' and `page_cfree()' */
FUNDEF NOBLOCK void
NOTHROW(KCALL page_ffree)(pageptr_t base, pagecnt_t num_pages, bool is_zero);


/* Collect volatile statistics about the usage of physical memory */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL page_stat)(struct pmemstat *__restrict result);
FUNDEF NOBLOCK NONNULL((3)) void
NOTHROW(KCALL page_stat_between)(pageptr_t base, pagecnt_t num_pages,
                                 struct pmemstat *__restrict result);

/* Check if a given `page' is current free.
 * NOTE: Returns `false' when `page_ismapped(page, 1)' is false. */
FUNDEF NOBLOCK WUNUSED bool
NOTHROW(KCALL page_isfree)(pageptr_t page);

/* Following a call to one of the `page_malloc()' functions,
 * check if the given `page' contains only zero-bytes.
 * NOTE: This function doesn't actually look at the contents of
 *       page itself, but rather at what it known about the page.
 * NOTE: Returns `false' when `page_ismapped(page, 1)' is false.
 * HINT: This function is mainly used in order to optimize the
 *       mapping of zero-initialized memory, such that the initializer
 *       will do something like:
 *       >> page = page_malloc(1);
 *       >> pagedir_mapone(dest, page, PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);
 *       >> if (!page_iszero(page))
 *       >>      vm_memsetphys(page2addr(dest), 0, PAGESIZE);
 *       In other words: The information is most useful in freshly
 *       allocated pages, in order to determine if the mapped memory
 *       already contains all zeros. */
FUNDEF NOBLOCK WUNUSED bool
NOTHROW(KCALL page_iszero)(pageptr_t page);

/* Check if all pages of a given physical memory range are mapped as available RAM. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(KCALL page_ismapped)(pageptr_t page, pagecnt_t num_pages);
#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MEMORY_H */
