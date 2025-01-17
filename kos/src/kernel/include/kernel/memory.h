/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
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

#include <kos/kernel/memory.h>

#include <stdbool.h>

/* Physical memory management. */

DECL_BEGIN

/* Special page index that is returned on error. */
#ifndef PHYSPAGE_INVALID
#define PHYSPAGE_INVALID (__CCAST(physpage_t)-1)
#endif /* !PHYSPAGE_INVALID */

/* A page pointer is just like a normal physical pointer, but divided by PAGESIZE */
#ifdef __CC__
typedef __physpage_t physpagecnt_t;
#endif /* __CC__ */


#define PMEMBANK_TYPE_UNDEF      0 /* Undefined memory (Handled identically to `PMEMBANK_TYPE_BADRAM') */
#define PMEMBANK_TYPE_RAM        1 /* [USE] Dynamic; aka. RAM memory (Main source of memory for `page_malloc') */
#ifdef BUILDING_KERNEL_CORE
#define PMEMBANK_TYPE_PRESERVE   2 /* [USE_LATER_0|MAP] Preserve  the  original content  of this  memory until
                                    * `mem_unpreserve()'  is  called,  at  which  point  the  memory  will  be
                                    * transformed into `PMEMBANK_TYPE_RAM', and made available to the physical
                                    * memory allocator. */
#define PMEMBANK_TYPE_ALLOCATED  3 /* [USE_LATER_1|MAP] Same as 'PMEMBANK_TYPE_RAM', but don't make memory available to `page_malloc' */
#endif /* BUILDING_KERNEL_CORE */
#define PMEMBANK_TYPE_KFREE      4 /* [USE_LATER_2|MAP] Kernel memory later turned into `PMEMBANK_TYPE_RAM' (The `.free' section...) */
#define PMEMBANK_TYPE_KERNEL     5 /* [MAP] Kernel core memory (mapped, not used) */
#define PMEMBANK_TYPE_NVS        6 /* Non-volatile memory (that is: memory that doesn't get wiped after shutdown) */
#define PMEMBANK_TYPE_DEVICE     7 /* Device memory (mapped, but not used as RAM) */
#define PMEMBANK_TYPE_BADRAM     8 /* Broken memory (Neither mapped nor used, but known to be present) */
#define PMEMBANK_TYPE_COUNT      9 /* Amount of known memory types. */

#ifdef __CC__
struct pmembank {
	union {
		uintptr_t  mb_startptr; /* Memory block starting address. */
		physaddr_t mb_start;    /* Memory block starting address. */
	};
	u16            mb_type;     /* Memory bank type. (One of `PMEMBANK_TYPE_*') */
	u16            mb_pad[(sizeof(physaddr_t) - 2) / 2]; /* ... */
};
#define PMEMBANK_INIT(startptr, type) { { startptr }, type, { } }

#define PMEMBANK_STARTADDR(x) ((x).mb_start)
#define PMEMBANK_MINADDR(x)   ((x).mb_start)
#define PMEMBANK_MAXADDR(x)   ((&(x))[1].mb_start - 1)
#define PMEMBANK_ENDADDR(x)   ((&(x))[1].mb_start)
#define PMEMBANK_SIZE(x)      (PMEMBANK_ENDADDR(x) - PMEMBANK_STARTADDR(x))
#define PMEMBANK_STARTPAGE(x) ((physpage_t)((PMEMBANK_STARTADDR(x) + PAGESIZE - 1) / PAGESIZE))
#define PMEMBANK_MINPAGE(x)   ((physpage_t)((PMEMBANK_STARTADDR(x) + PAGESIZE - 1) / PAGESIZE))
#define PMEMBANK_MAXPAGE(x)   ((physpage_t)((PMEMBANK_ENDADDR(x) / PAGESIZE) - 1))
#define PMEMBANK_ENDPAGE(x)   ((physpage_t)(PMEMBANK_ENDADDR(x) / PAGESIZE))
#define PMEMBANK_NUMPAGES(x)  ((physpagecnt_t)(PMEMBANK_ENDPAGE(x) - PMEMBANK_STARTPAGE(x)))

struct pmeminfo {
	size_t           mb_bankc; /* [const] Total number of memory banks. */
	struct pmembank *mb_banks; /* [const] Vector of memory banks. */
};

DATDEF char const pmembank_type_names[PMEMBANK_TYPE_COUNT][16];
DATDEF struct pmeminfo minfo; /* Physical memory info. */

#ifdef BUILDING_KERNEL_CORE
/* Returns the total number of usable pages of RAM */
INTDEF FREE ATTR_PURE size_t
NOTHROW(KCALL minfo_usable_ram_pages)(void);

/* Add information about a new member bank / region. */
INTDEF FREE void NOTHROW(KCALL minfo_addbank)(physaddr_t start, physaddr_t size, u16 type);

/* Construct memory zones from memory info. */
INTDEF FREE void NOTHROW(KCALL kernel_initialize_minfo_makezones)(void);

/* Relocate `minfo', as well as `mzones'  data to a more appropriate  location
 * after `kernel_initialize_minfo_makezones()' has been called, and the kernel
 * VM has been cleaned from unused memory mappings.
 * Before this function is called, all memory information still resides at a
 * location where its physical address is relative to its virtual, just like
 * any other kernel data. However, since  that can literally be anywhere  in
 * virtual memory, it  can easily (and  accidentally) interfere with  memory
 * layout expectancies of other early-boot systems.
 * Because of this, we try to relocate memory information into higher  memory
 * as soon as this becomes possible, thus keeping it from randomly showing up
 * and causing problems for other code. */
INTDEF FREE void NOTHROW(KCALL kernel_initialize_minfo_relocate)(void);

/* Release all memory previously marked as `PMEMBANK_TYPE_PRESERVE' or
 * `PMEMBANK_TYPE_ALLOCATED',  and page_free() all whole pages touched
 * by mappings of type `PMEMBANK_TYPE_PRESERVE' (unless the same  page
 * also contains another  mapping of type  `PMEMBANK_TYPE_ALLOCATED').
 * Afterwards, transform memory information for either type of  memory
 * bank  into `PMEMBANK_TYPE_RAM', and  (when possible) merge adjacent
 * banks of identical typing. */
INTDEF FREE void NOTHROW(KCALL minfo_release_preservations)(void);
#endif /* BUILDING_KERNEL_CORE */




struct pmemstat {
	physpagecnt_t ps_free;  /* Amount of free pages (including z-pages). */
	physpagecnt_t ps_zfree; /* Amount of free zero-pages. */
	physpagecnt_t ps_used;  /* Amount of used pages. */
};
#endif /* __CC__ */


#define PMEMZONE_ISFREEBIT   0 /* BIT: 1 -- The page is free, 0 -- The page is being used */
#define PMEMZONE_ISUNDFBIT   1 /* BIT: 1 -- The contents of the page are undefined, 0 -- The page contains only 0-bits. */
#define PMEMZONE_BITSPERPAGE 2 /* Number of bits per page. */
#define PMEMZONE_ISFREEMASK  0x01
#define PMEMZONE_ISUNDFMASK  0x02

#ifdef __CC__
struct pmemzone {
	struct pmemzone   *mz_prev;  /* [0..1][const] Pointer to the previous zone. */
	struct pmemzone   *mz_next;  /* [0..1][const] Pointer to the next zone. */
	physpage_t         mz_start; /* [const] Start page number. */
	physpage_t         mz_max;   /* [const] Max page still apart of this zone. */
	physpage_t         mz_rmax;  /* [const][== (mz_max - mz_start)] Zone-relative index of the max page. */
	WEAK physpage_t    mz_fmax;  /* The zone-relative address of the greatest free page (used as hint to the allocator). */
	WEAK physpagecnt_t mz_cfree; /* The number of free pages within this zone. */
	WEAK physpagecnt_t mz_qfree; /* The number of free pages within this zone that aren't initialized. */
	uintptr_t          mz_zero;  /* [const] Always 0 */
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
	                                   * NOTE:  Ordered  by   ascending  starting   address. */
};

DATDEF struct pmem mzones;

LOCAL NOBLOCK ATTR_RETNONNULL WUNUSED struct pmemzone *
NOTHROW(FCALL page_getzone)(physpage_t ptr) {
	struct pmemzone *zone;
	zone = mzones.pm_last;
	while (ptr > zone->mz_max) {
		__hybrid_assert(zone->mz_prev);
		zone = zone->mz_prev;
	}
	__hybrid_assert(ptr >= zone->mz_start);
	return zone;
}


/* API Versions:
 *
 * - malloc:          Allocate and try to use `system_cc_s()' if allocation fails
 * - malloc_nocc:     Allocate, but don't try to clear caches if operation fails
 * - malloc_noblock:  Allocate and try to use `system_cc_s_noblock()' if allocation fails
 */



/* Allocate `num_pages' continuous pages of physical memory and return their page number.
 * WARNING:  Physical   memory   cannot   be  dereferenced   prior   to   being   mapped.
 * @return: * :              The starting page number of the newly allocated memory range.
 * @return: PHYSPAGE_INVALID: The allocation failed. */
FUNDEF WUNUSED physpage_t NOTHROW(FCALL page_mallocone)(void);
FUNDEF NOBLOCK WUNUSED physpage_t NOTHROW(FCALL page_mallocone_nocc)(void);
FUNDEF NOBLOCK WUNUSED physpage_t NOTHROW(FCALL page_mallocone_noblock)(void);
#ifndef __NO_PAGE_MALLOC_CONSTANT_P_WRAPPERS
FUNDEF WUNUSED physpage_t NOTHROW(FCALL __os_page_malloc)(physpagecnt_t num_pages) ASMNAME("page_malloc");
FUNDEF NOBLOCK WUNUSED physpage_t NOTHROW(FCALL __os_page_malloc_noblock)(physpagecnt_t num_pages) ASMNAME("page_malloc_noblock");
FUNDEF NOBLOCK WUNUSED physpage_t NOTHROW(FCALL __os_page_malloc_nocc)(physpagecnt_t num_pages) ASMNAME("page_malloc_nocc");
FORCELOCAL ATTR_ARTIFICIAL WUNUSED physpage_t
NOTHROW(FCALL page_malloc)(physpagecnt_t num_pages) {
	if (__builtin_constant_p(num_pages) && num_pages == 1)
		return page_mallocone();
	return __os_page_malloc(num_pages);
}
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL WUNUSED physpage_t
NOTHROW(FCALL page_malloc_noblock)(physpagecnt_t num_pages) {
	if (__builtin_constant_p(num_pages) && num_pages == 1)
		return page_mallocone_noblock();
	return __os_page_malloc_noblock(num_pages);
}
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL WUNUSED physpage_t
NOTHROW(FCALL page_malloc_nocc)(physpagecnt_t num_pages) {
	if (__builtin_constant_p(num_pages) && num_pages == 1)
		return page_mallocone_nocc();
	return __os_page_malloc_nocc(num_pages);
}
#else /* !__NO_PAGE_MALLOC_CONSTANT_P_WRAPPERS */
FUNDEF WUNUSED physpage_t NOTHROW(FCALL page_malloc)(physpagecnt_t num_pages);
FUNDEF NOBLOCK WUNUSED physpage_t NOTHROW(FCALL page_malloc_noblock)(physpagecnt_t num_pages);
FUNDEF NOBLOCK WUNUSED physpage_t NOTHROW(FCALL page_malloc_nocc)(physpagecnt_t num_pages);
#endif /* __NO_PAGE_MALLOC_CONSTANT_P_WRAPPERS */


#if (__SIZEOF_PHYSPAGE_T__ * 2) == 8
#define __page_malloc_part_return_t __UINT64_TYPE__
#define __page_malloc_part_return_pack(page, count)         \
	((__page_malloc_part_return_t)(__UINT32_TYPE__)(page) | \
	 (__page_malloc_part_return_t)(__UINT32_TYPE__)(count) << 32)
#define __page_malloc_part_return_getpage(v)  (physpage_t)(__UINT32_TYPE__)(v)
#define __page_malloc_part_return_getcount(v) (physpagecnt_t)(__UINT32_TYPE__)((v) >> 32)
#elif (__SIZEOF_PHYSPAGE_T__ * 2) == 16 && defined(__UINT128_TYPE__)
#define __page_malloc_part_return_t __UINT128_TYPE__
#define __page_malloc_part_return_pack(page, count)         \
	((__page_malloc_part_return_t)(__UINT64_TYPE__)(page) | \
	 (__page_malloc_part_return_t)(__UINT64_TYPE__)(count) << 64)
#define __page_malloc_part_return_getpage(v)  (physpage_t)(__UINT64_TYPE__)(v)
#define __page_malloc_part_return_getcount(v) (physpagecnt_t)(__UINT64_TYPE__)((v) >> 64)
#else /* ... */
typedef struct {
	physpage_t    _pmpr_page;  /* Page base */
	physpagecnt_t _pmpr_count; /* Page count */
} __page_malloc_part_return_t;
#define __page_malloc_part_return_t_IS_STRUCT
#define __page_malloc_part_return_pack(page, count) ((__page_malloc_part_return_t){ page, count })
#define __page_malloc_part_return_getpage(v)        (v)._pmpr_page
#define __page_malloc_part_return_getcount(v)       (v)._pmpr_count
#endif /* !... */


/* Allocate  at  least  `min_pages', and  at  most `max_pages',
 * writing the actual number of pages allocated to `res_pages'.
 *  - This function  will try  to serve  the request  to allocate  `max_pages',
 *    but will prefer to return the first block of free consecutive pages  with
 *    a length of at least `min_pages', thus preventing memory fragmentation by
 *    using  up small memory blocks that might otherwise continue going unused.
 * @return: * :              The starting page number of the newly allocated memory range.
 * @return: PHYSPAGE_INVALID: The allocation failed. */
FUNDEF WUNUSED __page_malloc_part_return_t
NOTHROW(FCALL _page_malloc_part)(physpagecnt_t min_pages, physpagecnt_t max_pages);
FUNDEF NOBLOCK WUNUSED __page_malloc_part_return_t
NOTHROW(FCALL _page_malloc_part_noblock)(physpagecnt_t min_pages, physpagecnt_t max_pages);
FUNDEF NOBLOCK WUNUSED __page_malloc_part_return_t
NOTHROW(FCALL _page_malloc_part_nocc)(physpagecnt_t min_pages, physpagecnt_t max_pages);
FORCELOCAL WUNUSED NONNULL((3)) physpage_t
NOTHROW(FCALL page_malloc_part)(physpagecnt_t min_pages, physpagecnt_t max_pages,
                                physpagecnt_t *__restrict res_pages) {
	__page_malloc_part_return_t temp;
	temp = _page_malloc_part(min_pages, max_pages);
	*res_pages = __page_malloc_part_return_getcount(temp);
	return __page_malloc_part_return_getpage(temp);
}
FORCELOCAL NOBLOCK WUNUSED NONNULL((3)) physpage_t
NOTHROW(FCALL page_malloc_part_noblock)(physpagecnt_t min_pages, physpagecnt_t max_pages,
                                        physpagecnt_t *__restrict res_pages) {
	__page_malloc_part_return_t temp;
	temp = _page_malloc_part_noblock(min_pages, max_pages);
	*res_pages = __page_malloc_part_return_getcount(temp);
	return __page_malloc_part_return_getpage(temp);
}
FORCELOCAL NOBLOCK WUNUSED NONNULL((3)) physpage_t
NOTHROW(FCALL page_malloc_part_nocc)(physpagecnt_t min_pages, physpagecnt_t max_pages,
                                     physpagecnt_t *__restrict res_pages) {
	__page_malloc_part_return_t temp;
	temp = _page_malloc_part_nocc(min_pages, max_pages);
	*res_pages = __page_malloc_part_return_getcount(temp);
	return __page_malloc_part_return_getpage(temp);
}

/* Try to allocate the given page.
 * @return: * : One of `PAGE_MALLOC_AT_*' */
FUNDEF WUNUSED unsigned int NOTHROW(FCALL page_malloc_at)(physpage_t ptr);
FUNDEF NOBLOCK WUNUSED unsigned int NOTHROW(FCALL page_malloc_at_noblock)(physpage_t ptr);
FUNDEF NOBLOCK WUNUSED unsigned int NOTHROW(FCALL page_malloc_at_nocc)(physpage_t ptr);
#endif /* __CC__ */
#define PAGE_MALLOC_AT_SUCCESS   0 /* Successfully allocated the page. */
#define PAGE_MALLOC_AT_NOTMAPPED 1 /* The specified page is not mapped. */
#define PAGE_MALLOC_AT_NOTFREE   2 /* The specified page has already been allocated. */

#ifdef __CC__
/* Similar to `page_malloc_part()', but only allocate memory from
 * between the two given page addresses, such that all  allocated
 * pages are located within the specified range. */
FUNDEF WUNUSED __page_malloc_part_return_t
NOTHROW(FCALL _page_malloc_part_between)(physpage_t min_page, physpage_t max_page,
                                         physpagecnt_t min_pages, physpagecnt_t max_pages);
FUNDEF NOBLOCK WUNUSED __page_malloc_part_return_t
NOTHROW(FCALL _page_malloc_part_between_noblock)(physpage_t min_page, physpage_t max_page,
                                                 physpagecnt_t min_pages, physpagecnt_t max_pages);
FUNDEF NOBLOCK WUNUSED __page_malloc_part_return_t
NOTHROW(FCALL _page_malloc_part_between_nocc)(physpage_t min_page, physpage_t max_page,
                                              physpagecnt_t min_pages, physpagecnt_t max_pages);
FORCELOCAL WUNUSED NONNULL((5)) physpage_t
NOTHROW(FCALL page_malloc_part_between)(physpage_t min_page, physpage_t max_page,
                                        physpagecnt_t min_pages, physpagecnt_t max_pages,
                                        physpagecnt_t *__restrict res_pages) {
	__page_malloc_part_return_t temp;
	temp = _page_malloc_part_between(min_page, max_page, min_pages, max_pages);
	*res_pages = __page_malloc_part_return_getcount(temp);
	return __page_malloc_part_return_getpage(temp);
}
FORCELOCAL NOBLOCK WUNUSED NONNULL((5)) physpage_t
NOTHROW(FCALL page_malloc_part_between_noblock)(physpage_t min_page, physpage_t max_page,
                                                physpagecnt_t min_pages, physpagecnt_t max_pages,
                                                physpagecnt_t *__restrict res_pages) {
	__page_malloc_part_return_t temp;
	temp = _page_malloc_part_between_noblock(min_page, max_page, min_pages, max_pages);
	*res_pages = __page_malloc_part_return_getcount(temp);
	return __page_malloc_part_return_getpage(temp);
}
FORCELOCAL NOBLOCK WUNUSED NONNULL((5)) physpage_t
NOTHROW(FCALL page_malloc_part_between_nocc)(physpage_t min_page, physpage_t max_page,
                                             physpagecnt_t min_pages, physpagecnt_t max_pages,
                                             physpagecnt_t *__restrict res_pages) {
	__page_malloc_part_return_t temp;
	temp = _page_malloc_part_between_nocc(min_page, max_page, min_pages, max_pages);
	*res_pages = __page_malloc_part_return_getcount(temp);
	return __page_malloc_part_return_getpage(temp);
}

/* Similar to  `page_malloc()'  /  `page_malloc_part()',  but  only
 * allocate memory from between the two given page addresses,  such
 * that all allocated pages are located within the specified range.
 * @assume(return == PHYSPAGE_INVALID ||
 *        (return >= min_page &&
 *         return + num_pages - 1 <= max_page)); */
#ifdef __page_malloc_part_return_t_IS_STRUCT
FORCELOCAL WUNUSED physpage_t
NOTHROW(FCALL page_malloc_between)(physpage_t min_page, physpage_t max_page,
                                   physpagecnt_t num_pages) {
	__page_malloc_part_return_t temp;
	temp = _page_malloc_part_between(min_page, max_page, num_pages, num_pages);
	return __page_malloc_part_return_getpage(temp);
}
FORCELOCAL NOBLOCK WUNUSED physpage_t
NOTHROW(FCALL page_malloc_between_noblock)(physpage_t min_page, physpage_t max_page,
                                           physpagecnt_t num_pages) {
	__page_malloc_part_return_t temp;
	temp = _page_malloc_part_between_noblock(min_page, max_page, num_pages, num_pages);
	return __page_malloc_part_return_getpage(temp);
}
FORCELOCAL NOBLOCK WUNUSED physpage_t
NOTHROW(FCALL page_malloc_between_nocc)(physpage_t min_page, physpage_t max_page,
                                        physpagecnt_t num_pages) {
	__page_malloc_part_return_t temp;
	temp = _page_malloc_part_between_nocc(min_page, max_page, num_pages, num_pages);
	return __page_malloc_part_return_getpage(temp);
}
#else /* __page_malloc_part_return_t_IS_STRUCT */
#define page_malloc_between(min_page, max_page, num_pages) \
	__page_malloc_part_return_getpage(_page_malloc_part_between(min_page, max_page, num_pages, num_pages))
#define page_malloc_between_noblock(min_page, max_page, num_pages) \
	__page_malloc_part_return_getpage(_page_malloc_part_between_noblock(min_page, max_page, num_pages, num_pages))
#define page_malloc_between_nocc(min_page, max_page, num_pages) \
	__page_malloc_part_return_getpage(_page_malloc_part_between_nocc(min_page, max_page, num_pages, num_pages))
#endif /* !__page_malloc_part_return_t_IS_STRUCT */


#if __SIZEOF_PHYSADDR_T__ > 4
#define page_malloc32(num_pages)                               \
	page_malloc_between(physaddr2page(__UINT32_C(0x00000000)), \
	                    physaddr2page(__UINT32_C(0xffffffff)), \
	                    num_pages)
#define page_malloc32_noblock(num_pages)                               \
	page_malloc_between_noblock(physaddr2page(__UINT32_C(0x00000000)), \
	                            physaddr2page(__UINT32_C(0xffffffff)), \
	                            num_pages)
#define page_malloc32_nocc(num_pages)                               \
	page_malloc_between_nocc(physaddr2page(__UINT32_C(0x00000000)), \
	                         physaddr2page(__UINT32_C(0xffffffff)), \
	                         num_pages)
#define page_mallocone32()         page_malloc32(1)
#define page_mallocone32_noblock() page_malloc32_noblock(1)
#define page_mallocone32_nocc()    page_malloc32_nocc(1)
#else /* __SIZEOF_PHYSADDR_T__ > 4 */
#define page_malloc32(num_pages)         page_malloc(num_pages)
#define page_malloc32_noblock(num_pages) page_malloc_noblock(num_pages)
#define page_malloc32_nocc(num_pages)    page_malloc_nocc(num_pages)
#define page_mallocone32()               page_mallocone()
#define page_mallocone32_noblock()       page_mallocone_noblock()
#define page_mallocone32_nocc()          page_mallocone_nocc()
#endif /* __SIZEOF_PHYSADDR_T__ <= 4 */

/* Free a given physical address range.
 * The caller is responsible to ensure that the given range has previously been allocated. */
FUNDEF NOBLOCK void NOTHROW(FCALL page_freeone)(physpage_t base);
#ifndef __NO_PAGE_MALLOC_CONSTANT_P_WRAPPERS
FUNDEF NOBLOCK void NOTHROW(FCALL __os_page_free)(physpage_t base, physpagecnt_t num_pages) ASMNAME("page_free");
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL void
NOTHROW(FCALL page_free)(physpage_t base, physpagecnt_t num_pages) {
	if (__builtin_constant_p(num_pages) && num_pages == 1) {
		page_freeone(base);
	} else {
		__os_page_free(base, num_pages);
	}
}
#else /* !__NO_PAGE_MALLOC_CONSTANT_P_WRAPPERS */
FUNDEF NOBLOCK void NOTHROW(FCALL page_free)(physpage_t base, physpagecnt_t num_pages);
#endif /* __NO_PAGE_MALLOC_CONSTANT_P_WRAPPERS */

/* Similar to `page_free()', however set the is-zero-bit for all pages. */
FUNDEF NOBLOCK void
NOTHROW(FCALL page_cfree)(physpage_t base, physpagecnt_t num_pages);

/* Similar to `page_free()', however set the is-zero-bit for pages where `page_iszero()' is true. */
FUNDEF NOBLOCK void
NOTHROW(FCALL page_ccfree)(physpage_t base, physpagecnt_t num_pages);

/* Combination of `page_free()' and `page_cfree()' */
FUNDEF NOBLOCK void
NOTHROW(FCALL page_ffree)(physpage_t base, physpagecnt_t num_pages, bool is_zero);


/* Collect volatile statistics about the usage of physical memory */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL page_stat)(struct pmemstat *__restrict result);
FUNDEF NOBLOCK NONNULL((3)) void
NOTHROW(FCALL page_stat_between)(physpage_t base, physpagecnt_t num_pages,
                                 struct pmemstat *__restrict result);

/* Check if a given `page' is current free.
 * NOTE: Returns `false' when `page_ismapped(page, 1)' is false. */
FUNDEF NOBLOCK WUNUSED bool
NOTHROW(FCALL page_isfree)(physpage_t page);

/* Following a call to one of the `page_malloc()' functions,
 * check  if  the  given  `page'  contains  only zero-bytes.
 * NOTE: This function doesn't actually  look at the contents  of
 *       page itself, but rather at what it known about the page.
 * NOTE: Returns `false' when `page_ismapped(page, 1)' is false.
 * HINT: This  function  is  mainly  used  in  order  to  optimize the
 *       mapping of zero-initialized memory, such that the initializer
 *       will do something like:
 *       >> page = page_malloc(1);
 *       >> pagedir_mapone(dest, page, PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE);
 *       >> if (!page_iszero(page))
 *       >>      memsetphys(physpage2addr(dest), 0, PAGESIZE);
 *       In other words: The information is most useful in freshly
 *       allocated pages, in order to determine if the mapped memory
 *       already contains all zeros. */
FUNDEF NOBLOCK WUNUSED bool
NOTHROW(FCALL page_iszero)(physpage_t page);

/* Reset the is-zero attribute for all pages in the given range.
 * Pages  that aren't  part of  any zones  are silently ignored. */
FUNDEF NOBLOCK void
NOTHROW(FCALL page_resetzero)(physpage_t page, physpagecnt_t num_pages);
FUNDEF NOBLOCK void
NOTHROW(FCALL page_resetzeroone)(physpage_t page);

/* Check if all pages of a given physical memory range are mapped as available RAM. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED bool
NOTHROW(FCALL page_ismapped)(physpage_t page, physpagecnt_t num_pages);



#ifndef CONFIG_NO_PAGE_USAGE
/* Memory usage information.
 * Keeps track of why certain  physical memory allocation were  made.
 * Any physical memory allocated that doesn't appear here is  assumed
 * to be allocated for general-purpose RAM, or some undefined reason. */
struct page_usage_struct {
	size_t pu_static;   /* [lock(ATOMIC)] # of pages allocated for static reasons. */
	size_t pu_paging;   /* [lock(ATOMIC)] # of pages allocated for page directory tables. */
#if defined(__x86_64__) || defined(__i386__)
	size_t pu_x86_iobm; /* [lock(ATOMIC)] # of pages allocated for `struct ioperm_bitmap'. */
#endif /* __x86_64__ || __i386__ */
};

/* Usage information. */
DATDEF struct page_usage_struct page_usage;

#define page_usage_inc(field)    __hybrid_atomic_inc(&(field), __ATOMIC_SEQ_CST)
#define page_usage_dec(field)    __hybrid_atomic_dec(&(field), __ATOMIC_SEQ_CST)
#define page_usage_add(field, v) __hybrid_atomic_add(&(field), v, __ATOMIC_SEQ_CST)
#define page_usage_sub(field, v) __hybrid_atomic_sub(&(field), v, __ATOMIC_SEQ_CST)
#define page_mallocone_for(usage_field)           \
	__XBLOCK({                                    \
		physpage_t _pmof_page = page_mallocone(); \
		if likely(_pmof_page != PHYSPAGE_INVALID) \
			page_usage_inc(usage_field);          \
		__XRETURN _pmof_page;                     \
	})
#define page_mallocone_noblock_for(usage_field)           \
	__XBLOCK({                                            \
		physpage_t _pmof_page = page_mallocone_noblock(); \
		if likely(_pmof_page != PHYSPAGE_INVALID)         \
			page_usage_inc(usage_field);                  \
		__XRETURN _pmof_page;                             \
	})
#define page_mallocone_nocc_for(usage_field)           \
	__XBLOCK({                                         \
		physpage_t _pmof_page = page_mallocone_nocc(); \
		if likely(_pmof_page != PHYSPAGE_INVALID)      \
			page_usage_inc(usage_field);               \
		__XRETURN _pmof_page;                          \
	})
#define page_malloc_for(usage_field, num_pages)        \
	__XBLOCK({                                         \
		physpage_t _pmf_page = page_malloc(num_pages); \
		if likely(_pmf_page != PHYSPAGE_INVALID)       \
			page_usage_add(usage_field, num_pages);    \
		__XRETURN _pmf_page;                           \
	})
#define page_malloc_noblock_for(usage_field, num_pages)        \
	__XBLOCK({                                                 \
		physpage_t _pmf_page = page_malloc_noblock(num_pages); \
		if likely(_pmf_page != PHYSPAGE_INVALID)               \
			page_usage_add(usage_field, num_pages);            \
		__XRETURN _pmf_page;                                   \
	})
#define page_malloc_nocc_for(usage_field, num_pages)        \
	__XBLOCK({                                              \
		physpage_t _pmf_page = page_malloc_nocc(num_pages); \
		if likely(_pmf_page != PHYSPAGE_INVALID)            \
			page_usage_add(usage_field, num_pages);         \
		__XRETURN _pmf_page;                                \
	})
#define page_malloc_part_for(usage_field, min_pages, max_pages, res_pages)         \
	__XBLOCK({                                                                     \
		physpage_t _pmpf_page = page_malloc_part(min_pages, max_pages, res_pages); \
		if likely(_pmpf_page != PHYSPAGE_INVALID)                                  \
			page_usage_add(usage_field, *(res_pages));                             \
		__XRETURN _pmpf_page;                                                      \
	})
#define page_malloc_part_noblock_for(usage_field, min_pages, max_pages, res_pages)         \
	__XBLOCK({                                                                             \
		physpage_t _pmpf_page = page_malloc_part_noblock(min_pages, max_pages, res_pages); \
		if likely(_pmpf_page != PHYSPAGE_INVALID)                                          \
			page_usage_add(usage_field, *(res_pages));                                     \
		__XRETURN _pmpf_page;                                                              \
	})
#define page_malloc_part_nocc_for(usage_field, min_pages, max_pages, res_pages)         \
	__XBLOCK({                                                                          \
		physpage_t _pmpf_page = page_malloc_part_nocc(min_pages, max_pages, res_pages); \
		if likely(_pmpf_page != PHYSPAGE_INVALID)                                       \
			page_usage_add(usage_field, *(res_pages));                                  \
		__XRETURN _pmpf_page;                                                           \
	})
#define page_malloc_at_for(usage_field, ptr)           \
	__XBLOCK({                                         \
		unsigned int _pmaf_res = page_malloc_at(ptr);  \
		if likely(_pmaf_res == PAGE_MALLOC_AT_SUCCESS) \
			page_usage_inc(usage_field);               \
		__XRETURN _pmaf_res;                           \
	})
#define page_malloc_at_noblock_for(usage_field, ptr)          \
	__XBLOCK({                                                \
		unsigned int _pmaf_res = page_malloc_at_noblock(ptr); \
		if likely(_pmaf_res == PAGE_MALLOC_AT_SUCCESS)        \
			page_usage_inc(usage_field);                      \
		__XRETURN _pmaf_res;                                  \
	})
#define page_malloc_at_nocc_for(usage_field, ptr)          \
	__XBLOCK({                                             \
		unsigned int _pmaf_res = page_malloc_at_nocc(ptr); \
		if likely(_pmaf_res == PAGE_MALLOC_AT_SUCCESS)     \
			page_usage_inc(usage_field);                   \
		__XRETURN _pmaf_res;                               \
	})
#define page_malloc_between_for(usage_field, min_page, max_page, num_pages)         \
	__XBLOCK({                                                                      \
		physpage_t _pmbf_page = page_malloc_between(min_page, max_page, num_pages); \
		if likely(_pmbf_page != PHYSPAGE_INVALID)                                   \
			page_usage_add(usage_field, num_pages);                                 \
		__XRETURN _pmbf_page;                                                       \
	})
#define page_malloc_between_noblock_for(usage_field, min_page, max_page, num_pages)         \
	__XBLOCK({                                                                              \
		physpage_t _pmbf_page = page_malloc_between_noblock(min_page, max_page, num_pages); \
		if likely(_pmbf_page != PHYSPAGE_INVALID)                                           \
			page_usage_add(usage_field, num_pages);                                         \
		__XRETURN _pmbf_page;                                                               \
	})
#define page_malloc_between_nocc_for(usage_field, min_page, max_page, num_pages)         \
	__XBLOCK({                                                                           \
		physpage_t _pmbf_page = page_malloc_between_nocc(min_page, max_page, num_pages); \
		if likely(_pmbf_page != PHYSPAGE_INVALID)                                        \
			page_usage_add(usage_field, num_pages);                                      \
		__XRETURN _pmbf_page;                                                            \
	})
#define page_malloc_part_between_for(usage_field, min_page, max_page,          \
                                     min_pages, max_pages, res_pages)          \
	__XBLOCK({                                                                 \
		physpage_t _pmbf_page = page_malloc_part_between(min_page, max_page,   \
		                                                 min_pages, max_pages, \
		                                                 res_pages);           \
		if likely(_pmbf_page != PHYSPAGE_INVALID)                              \
			page_usage_add(usage_field, (*res_pages));                         \
		__XRETURN _pmbf_page;                                                  \
	})
#define page_malloc_part_between_noblock_for(usage_field, min_page, max_page,          \
                                            min_pages, max_pages, res_pages)           \
	__XBLOCK({                                                                         \
		physpage_t _pmbf_page = page_malloc_part_between_noblock(min_page, max_page,   \
		                                                         min_pages, max_pages, \
		                                                         res_pages);           \
		if likely(_pmbf_page != PHYSPAGE_INVALID)                                      \
			page_usage_add(usage_field, (*res_pages));                                 \
		__XRETURN _pmbf_page;                                                          \
	})
#define page_malloc_part_between_nocc_for(usage_field, min_page, max_page,          \
                                          min_pages, max_pages, res_pages)          \
	__XBLOCK({                                                                      \
		physpage_t _pmbf_page = page_malloc_part_between_nocc(min_page, max_page,   \
		                                                      min_pages, max_pages, \
		                                                      res_pages);           \
		if likely(_pmbf_page != PHYSPAGE_INVALID)                                   \
			page_usage_add(usage_field, (*res_pages));                              \
		__XRETURN _pmbf_page;                                                       \
	})
#define page_freeone_for(usage_field, base)                   (page_usage_dec(usage_field), page_freeone(base))
#define page_free_for(usage_field, base, num_pages)           (page_usage_sub(usage_field, num_pages), page_free(base, num_pages))
#define page_cfree_for(usage_field, base, num_pages)          (page_usage_sub(usage_field, num_pages), page_cfree(base, num_pages))
#define page_ccfree_for(usage_field, base, num_pages)         (page_usage_sub(usage_field, num_pages), page_ccfree(base, num_pages))
#define page_ffree_for(usage_field, base, num_pages, is_zero) (page_usage_sub(usage_field, num_pages), page_ffree(base, num_pages, is_zero))
#else /* !CONFIG_NO_PAGE_USAGE */
#define page_usage_inc(field)                                  (void)0
#define page_usage_dec(field)                                  (void)0
#define page_usage_add(field, v)                               (void)0
#define page_usage_sub(field, v)                               (void)0
#define page_mallocone_for(usage_field)                        page_mallocone()
#define page_mallocone_noblock_for(usage_field)                page_mallocone_noblock()
#define page_mallocone_nocc_for(usage_field)                   page_mallocone_nocc()
#define page_malloc_for(usage_field, ...)                      page_malloc(__VA_ARGS__)
#define page_malloc_noblock_for(usage_field, ...)              page_malloc_noblock(__VA_ARGS__)
#define page_malloc_nocc_for(usage_field, ...)                 page_malloc_nocc(__VA_ARGS__)
#define page_malloc_part_for(usage_field, ...)                 page_malloc_part(__VA_ARGS__)
#define page_malloc_part_noblock_for(usage_field, ...)         page_malloc_part_noblock(__VA_ARGS__)
#define page_malloc_part_nocc_for(usage_field, ...)            page_malloc_part_nocc(__VA_ARGS__)
#define page_malloc_at_for(usage_field, ...)                   page_malloc_at(__VA_ARGS__)
#define page_malloc_at_noblock_for(usage_field, ...)           page_malloc_at_noblock(__VA_ARGS__)
#define page_malloc_at_nocc_for(usage_field, ...)              page_malloc_at_nocc(__VA_ARGS__)
#define page_malloc_between_for(usage_field, ...)              page_malloc_between(__VA_ARGS__)
#define page_malloc_part_between_for(usage_field, ...)         page_malloc_part_between(__VA_ARGS__)
#define page_malloc_part_between_noblock_for(usage_field, ...) page_malloc_part_between_noblock(__VA_ARGS__)
#define page_malloc_part_between_nocc_for(usage_field, ...)    page_malloc_part_between_nocc(__VA_ARGS__)
#define page_freeone_for(usage_field, ...)                     page_freeone(__VA_ARGS__)
#define page_free_for(usage_field, ...)                        page_free(__VA_ARGS__)
#define page_cfree_for(usage_field, ...)                       page_cfree(__VA_ARGS__)
#define page_ccfree_for(usage_field, ...)                      page_ccfree(__VA_ARGS__)
#define page_ffree_for(usage_field, ...)                       page_ffree(__VA_ARGS__)
#endif /* CONFIG_NO_PAGE_USAGE */
#if __SIZEOF_PHYSADDR_T__ > 4
#define page_malloc32_for(usage_field, num_pages)                  \
	page_malloc_between_for(usage_field,                           \
	                        physaddr2page(__UINT32_C(0x00000000)), \
	                        physaddr2page(__UINT32_C(0xffffffff)), \
	                        num_pages)
#define page_malloc32_noblock_for(usage_field, num_pages)                  \
	page_malloc_between_noblock_for(usage_field,                           \
	                                physaddr2page(__UINT32_C(0x00000000)), \
	                                physaddr2page(__UINT32_C(0xffffffff)), \
	                                num_pages)
#define page_malloc32_nocc_for(usage_field, num_pages)                  \
	page_malloc_between_nocc_for(usage_field,                           \
	                             physaddr2page(__UINT32_C(0x00000000)), \
	                             physaddr2page(__UINT32_C(0xffffffff)), \
	                             num_pages)
#define page_mallocone32_for(usage_field)         page_malloc32_for(usage_field, 1)
#define page_mallocone32_noblock_for(usage_field) page_malloc32_noblock_for(usage_field, 1)
#define page_mallocone32_nocc_for(usage_field)    page_malloc32_nocc_for(usage_field, 1)
#else /* __SIZEOF_PHYSADDR_T__ > 4 */
#define page_malloc32_for(usage_field, num_pages)         page_malloc_for(usage_field, num_pages)
#define page_malloc32_noblock_for(usage_field, num_pages) page_malloc_noblock_for(usage_field, num_pages)
#define page_malloc32_nocc_for(usage_field, num_pages)    page_malloc_nocc_for(usage_field, num_pages)
#define page_mallocone32_for(usage_field)                 page_mallocone_for(usage_field)
#define page_mallocone32_noblock_for(usage_field)         page_mallocone_noblock_for(usage_field)
#define page_mallocone32_nocc_for(usage_field)            page_mallocone_nocc_for(usage_field)
#endif /* __SIZEOF_PHYSADDR_T__ <= 4 */

/* --- For copy+paste+replace: creating a new reason ---
#define page_mallocone_for_myreason(...)                   page_mallocone_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_mallocone_noblock_for_myreason(...)           page_mallocone_noblock_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_mallocone_nocc_for_myreason(...)              page_mallocone_nocc_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_malloc_for_myreason(...)                      page_malloc_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_malloc_noblock_for_myreason(...)              page_malloc_noblock_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_malloc_nocc_for_myreason(...)                 page_malloc_nocc_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_malloc_part_for_myreason(...)                 page_malloc_part_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_malloc_part_noblock_for_myreason(...)         page_malloc_part_noblock_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_malloc_part_nocc_for_myreason(...)            page_malloc_part_nocc_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_malloc_at_for_myreason(...)                   page_malloc_at_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_malloc_at_noblock_for_myreason(...)           page_malloc_at_noblock_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_malloc_at_nocc_for_myreason(...)              page_malloc_at_nocc_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_malloc_between_for_myreason(...)              page_malloc_between_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_malloc_between_noblock_for_myreason(...)      page_malloc_between_noblock_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_malloc_between_nocc_for_myreason(...)         page_malloc_between_nocc_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_malloc_part_between_for_myreason(...)         page_malloc_part_between_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_malloc_part_between_noblock_for_myreason(...) page_malloc_part_between_noblock_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_malloc_part_between_nocc_for_myreason(...)    page_malloc_part_between_nocc_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_freeone_for_myreason(...)                     page_freeone_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_free_for_myreason(...)                        page_free_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_cfree_for_myreason(...)                       page_cfree_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_ccfree_for_myreason(...)                      page_ccfree_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_ffree_for_myreason(...)                       page_ffree_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_malloc32_for_myreason(...)                    page_malloc32_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_malloc32_noblock_for_myreason(...)            page_malloc32_noblock_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_malloc32_nocc_for_myreason(...)               page_malloc32_nocc_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_mallocone32_for_myreason(...)                 page_mallocone32_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_mallocone32_noblock_for_myreason(...)         page_mallocone32_noblock_for(page_usage.pu_myreason, ##__VA_ARGS__)
#define page_mallocone32_nocc_for_myreason(...)            page_mallocone32_nocc_for(page_usage.pu_myreason, ##__VA_ARGS__)
*/

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MEMORY_H */
