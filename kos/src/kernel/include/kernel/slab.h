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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_SLAB_H
#define GUARD_KERNEL_INCLUDE_KERNEL_SLAB_H 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/types.h>
#include <kernel/vm.h>

#include "malloc-defs.h"
#include "malloc.h"

DECL_BEGIN

/* Slab allocators.
 *  - Used by kmalloc() for very small, but efficient allocations (< HEAP_MINSIZE)
 *  - Uses the same mechanism as corebase, in that memory is allocated in pages,
 *    but then handed out in very small, fixed-length segments that are tracked
 *    via a bitset within the page.
 *  - Each slab has its own chain of in-use pages (that still contain unused segments)
 *  - All slabs share 2 small pools of pages that are entirely free (usually up to 3)
 *    - When a new page is required for allocation, they are taken from the pools
 *    - One pool is for locked pages, while the other is for swap-capable ones.
 *  - Memory is freed by loading the page address of a pointer, where meta-data
 *    including the size of segments within that page is stored, as well as a bitset
 *    describing which segments have been allocated.
 *  - Once a slab page contains no further in-use segments, it is added to the pool
 *    of free pages. If the pool would then exceed its limit, the oldest free page
 *    is released to the core.
 *  - Slab allocators are used for all allocations `>= HEAP_ALIGNMENT' and `<= SLAB_MAXSIZE'
 *  - Assuming 4-byte alignment, and a `SLAB_MAXSIZE' of `20'
 *    bytes, this makes 5 slab variants: 4, 8, 12, 16, 20
 *  - Since slab-memory cannot be realloc()'ed, by default only kmalloc()
 *    will allocate slab memory, while krealloc() will only ever allocate
 *    actual heap memory. */


#ifdef CONFIG_USE_SLAB_ALLOCATORS
#ifdef __CC__

struct slab {
	struct slab **s_pself; /* [1..1][0..1] Self pointer (set to NULL when the page has been fully allocated) */
	struct slab  *s_next;  /* [0..1] Next slab (either next in-use, or next free) */
#define SLAB_FNORMAL 0x00  /* Normal slab flags. */
#define SLAB_FLOCKED 0x01  /* The slab kernel page is locked into memory. */
#define SLAB_FCALLOC 0x04  /* Slab memory (of unused slabs) is zero-initialized. */
#if __SIZEOF_POINTER__ >= 8
	u16          s_flags; /* Slab flags (Set of `SLAB_F*'). */
	u16          s_size;  /* [const] Slab segment size (in bytes) */
	WEAK u32     s_free;  /* Amount of free segments in this slab. */
#else
	u8           s_flags; /* Slab flags (Set of `SLAB_F*'). */
	u8           s_size;  /* [const] Slab segment size (in bytes) */
	WEAK u16     s_free;  /* Amount of free segments in this slab. */
#endif
	/* A bitset of allocated segments goes here (1-bits indicate allocated segments)
	 * Note that the bitset works with whole words (uintptr_t),
	 * so-as to ensure that the following segment vector is
	 * pointer-aligned. */
	/* When `HEAP_ALIGNMENT > __SIZEOF_POINTER__', there exists some
	 * unused padding here to ensure that the vector is properly aligned. */
	/* Actual segment data goes here, following the initialization rules of
	 * `SLAB_FCALLOC' for 0, and undefined/DEBUGHEAP_NO_MANS_LAND otherwise. */
};

#define SLAB_GET(ptr) ((struct slab *)((uintptr_t)(ptr) & ~(PAGESIZE - 1)))


#define PRIVATE_SLAB_SEGMENT_COUNT(segment_size) \
	((PAGESIZE - 4 * __SIZEOF_POINTER__) / (segment_size))

/* Return the length (in words) of the in-use bitset of a given slab. */
#define SLAB_LENGTHOF_BITSET(segment_size) ((PRIVATE_SLAB_SEGMENT_COUNT(segment_size) + (BITS_PER_POINTER - 1)) / BITS_PER_POINTER)
#define SLAB_SIZEOF_BITSET(segment_size)   (SLAB_LENGTHOF_BITSET(segment_size) * __SIZEOF_POINTER__)

#if HEAP_ALIGNMENT > __SIZEOF_POINTER__
#define SLAB_SEGMENT_OFFSET(segment_size) ((((3 + SLAB_LENGTHOF_BITSET(segment_size)) * __SIZEOF_POINTER__) + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1))
#else
#define SLAB_SEGMENT_OFFSET(segment_size)   ((3 + SLAB_LENGTHOF_BITSET(segment_size)) * __SIZEOF_POINTER__)
#endif

/* Return the number of segments available per page, when each has a size of `segment_size' */
#define SLAB_SEGMENT_COUNT(segment_size) \
	((PAGESIZE - SLAB_SEGMENT_OFFSET(segment_size)) / (segment_size))


#define PRIVATE_SLAB_GET_ADDR2(a,b) a
#define PRIVATE_SLAB_GET_ADDR(x) PRIVATE_SLAB_GET_ADDR2 x

#define PRIVATE_SLAB_GET_HINT2(a,b) b
#define PRIVATE_SLAB_GET_HINT(x) PRIVATE_SLAB_GET_HINT2 x
#if PRIVATE_SLAB_GET_HINT(KERNEL_VMHINT_SLAB) == VM_GETFREE_BELOW
#undef CONFIG_SLAB_GROWS_UPWARDS
#define CONFIG_SLAB_GROWS_DOWNWARDS 1
#else
#undef CONFIG_SLAB_GROWS_DOWNWARDS
#define CONFIG_SLAB_GROWS_UPWARDS 1
#endif


#define KERNEL_SLAB_INITIAL   \
	((uintptr_t)VM_PAGE2ADDR(__CCAST(vm_vpage_t)PRIVATE_SLAB_GET_ADDR(KERNEL_VMHINT_SLAB)))

/* [lock(vm_kernel)]
 * The pointer to either the lowest (CONFIG_SLAB_GROWS_DOWNWARDS), or
 * one past the greatest (CONFIG_SLAB_GROWS_UPWARDS) address that was
 * ever allocated for slab memory.
 * Since slab allocations don't carry any meta-data, they are actually
 * identified by their address, meaning that we need to keep track of
 * the max range of pointers associated with the slab allocator.
 * NOTE: This value starts out as `KERNEL_SLAB_INITIAL', and is only
 *       ever extended in one direction, based on the slab growth
 *       direction. */
DATDEF uintptr_t kernel_slab_break;


/* The starting/end address of slab allocated memory. */
#ifdef CONFIG_SLAB_GROWS_DOWNWARDS
#define KERNEL_SLAB_START    kernel_slab_break
#define KERNEL_SLAB_END      KERNEL_SLAB_INITIAL
#define KERNEL_SLAB_MIN      kernel_slab_break
#define KERNEL_SLAB_MAX     (KERNEL_SLAB_INITIAL - 1)
#else
#define KERNEL_SLAB_START    KERNEL_SLAB_INITIAL
#define KERNEL_SLAB_END      kernel_slab_break
#define KERNEL_SLAB_MIN      KERNEL_SLAB_INITIAL
#define KERNEL_SLAB_MAX     (kernel_slab_break - 1)
#endif

/* Check if a given pointer belongs to the slab allocator,
 * and can be passed to `SLAB_GET()' in order to determine
 * the associated page, as well as meta-data. */
#define KERNEL_SLAB_CHECKPTR(x) \
	((uintptr_t)(x) >= KERNEL_SLAB_START && (uintptr_t)(x) < KERNEL_SLAB_END)


#endif /* __CC__ */
#endif /* CONFIG_USE_SLAB_ALLOCATORS */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_SLAB_H */
