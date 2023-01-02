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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_SLAB_H
#define GUARD_KERNEL_INCLUDE_KERNEL_SLAB_H 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/types.h>

#include <hybrid/sequence/list.h>
#include <hybrid/typecore.h>

#include <kos/kernel/paging.h> /* KERNEL_MHINT_SLAB */

#ifdef BUILDING_KERNEL_CORE
#include <hybrid/sched/atomic-lock.h>
#endif /* BUILDING_KERNEL_CORE */

#include "malloc-defs.h"
#include "malloc.h"

/* Slab allocators.
 * - Used by kmalloc() for very small, but efficient allocations (< HEAP_MINSIZE)
 * - Uses the same mechanism as corebase, in that memory is allocated in pages,
 *   but then handed out in very small, fixed-length segments that are  tracked
 *   via a bitset within the page.
 * - Each slab has its own chain of in-use pages (that still contain unused segments)
 * - All slabs share 2 small pools of pages that are entirely free (usually up to 3)
 *   - When a new page is required for allocation, they are taken from the pools
 *   - One pool is for locked pages, while the other is for swap-capable ones.
 * - Memory is freed  by loading  the page address  of a  pointer, where  meta-data
 *   including the size of segments within that page is stored, as well as a bitset
 *   describing  which segments have  been allocated. This  bitset is then updated.
 * - Once a slab page contains no further in-use segments, it is added to the pool
 *   of  free pages. If the pool would then exceed its limit, the oldest free page
 *   is released to the core.
 * - Slab allocators are used for all fixed-length allocations `<= CONFIG_KERNEL_SLAB_MAXSIZE'
 * - Slab sizes have a granularity of `sizeof(void *)', with all possible values
 *   that   are   `<= CONFIG_KERNEL_SLAB_MAXSIZE'  having   a   dedicated  slab.
 * - Since slab-memory  cannot be  realloc()'ed,  by default  only  kmalloc()
 *   will allocate  slab memory,  while krealloc()  will only  ever  allocate
 *   actual heap memory.  However, krealloc(SLAB_PTR) still  works, but  will
 *   never re-return SLAB_PTR (i.e. inplace_realloc doesn't work), unless the
 *   block  size didn't change (and even then:  it's not guarantied to do so) */


#ifdef CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS
#ifdef __CC__
DECL_BEGIN

struct slab {
	union {
		SLIST_ENTRY(slab) s_slink; /* [0..1] Used internally to chain fully free slabs. */
		LIST_ENTRY(slab)  s_link;  /* [0..1] Prev/next slab (either in-use, or free) */
	};
#define SLAB_FNORMAL 0x00  /* Normal slab flags. */
#define SLAB_FLOCKED 0x01  /* The slab kernel page is locked into memory. */
#define SLAB_FCALLOC 0x04  /* Slab memory (of unused slabs) is zero-initialized. */
	uintptr_quarter_t     s_flags; /* Slab flags (Set of `SLAB_F*'). */
	uintptr_quarter_t     s_size;  /* [const] Slab segment size (in bytes) */
	WEAK uintptr_half_t   s_free;  /* Amount of free segments in this slab. */
	/* A bitset of allocated segments goes here (every segment has `SLAB_SEGMENT_STATUS_BITS'
	 * consecutive  status bits in  within this bitset, that  form an integer  that is one of
	 * `SLAB_SEGMENT_STATUS_*').
	 * Note that the bitset works with whole words (uintptr_t),
	 * so-as to  ensure that  the following  segment vector  is
	 * pointer-aligned. */

	/* When  `HEAP_ALIGNMENT > __SIZEOF_POINTER__',  there  exists   some
	 * unused padding here to ensure that the vector is properly aligned. */
	/* Actual segment data goes here, following the initialization rules  of
	 * `SLAB_FCALLOC' for 0, and undefined/DEBUGHEAP_NO_MANS_LAND otherwise. */
};

#define SLAB_GET(ptr) ((struct slab *)((uintptr_t)(ptr) & ~PAGEMASK))

#define PRIVATE_SLAB_SEGMENT_COUNT(segment_size) \
	((PAGESIZE - 4 * __SIZEOF_POINTER__) / (segment_size))

#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
#define SLAB_SEGMENT_STATUS_FREE  0 /* Segment is free. */
#define SLAB_SEGMENT_STATUS_ALLOC 1 /* Segment is allocated. */
/*      SLAB_SEGMENT_STATUS_      2  * ... */
#define SLAB_SEGMENT_STATUS_REACH 3 /* Segment is reachable. */
#define SLAB_SEGMENT_STATUS_MASK  3 /* Mask of bits */
#define SLAB_SEGMENT_STATUS_BITS  2 /* # of status bits per slab. */
#else /* CONFIG_HAVE_KERNEL_TRACE_MALLOC */
#define SLAB_SEGMENT_STATUS_FREE  0 /* Segment is free. */
#define SLAB_SEGMENT_STATUS_ALLOC 1 /* Segment is allocated. */
#define SLAB_SEGMENT_STATUS_MASK  1 /* Mask of bits */
#define SLAB_SEGMENT_STATUS_BITS  1 /* # of status bits per slab. */
#endif /* !CONFIG_HAVE_KERNEL_TRACE_MALLOC */

/* Return a base-pointer to the status-bitset of `self' */
#define _SLAB_SEGMENT_STATUS_BITSET(self) ((uintptr_t *)((struct slab *)(self) + 1))

/* Return the word(index), mask, and shift for the
 * index'th  segment  within  the  status  bitset. */
#define _SLAB_SEGMENT_STATUS_MASK(index) ((uintptr_t)SLAB_SEGMENT_STATUS_MASK << _SLAB_SEGMENT_STATUS_SHFT(index))
#if SLAB_SEGMENT_STATUS_BITS == 2
#define _SLAB_SEGMENT_STATUS_WORD(index) ((index) / (__SIZEOF_POINTER__ * 4))
#define _SLAB_SEGMENT_STATUS_SHFT(index) (((index) % (__SIZEOF_POINTER__ * 4)) * 2)
#elif SLAB_SEGMENT_STATUS_BITS == 1
#define _SLAB_SEGMENT_STATUS_WORD(index) ((index) / (__SIZEOF_POINTER__ * 8))
#define _SLAB_SEGMENT_STATUS_SHFT(index) ((index) % (__SIZEOF_POINTER__ * 8))
#else /* SLAB_SEGMENT_STATUS_BITS == ... */
#define _SLAB_SEGMENT_STATUS_WORD(index) ((index) / (__SIZEOF_POINTER__ * (8 / SLAB_SEGMENT_STATUS_BITS)))
#define _SLAB_SEGMENT_STATUS_SHFT(index) (((index) % (__SIZEOF_POINTER__ * (8 / SLAB_SEGMENT_STATUS_BITS))) * SLAB_SEGMENT_STATUS_BITS)
#endif /* SLAB_SEGMENT_STATUS_BITS != ... */

#define SLAB_SEGMENT_STATUS_ALLOC_N(index) ((uintptr_t)SLAB_SEGMENT_STATUS_ALLOC << _SLAB_SEGMENT_STATUS_SHFT(index))
#define SLAB_SEGMENT_STATUS_MASK_N(index)  ((uintptr_t)SLAB_SEGMENT_STATUS_MASK << _SLAB_SEGMENT_STATUS_SHFT(index))

#if SLAB_SEGMENT_STATUS_BITS == 2
#if __SIZEOF_POINTER__ == 4
#define _SLAB_SEGMENT_STATUS_WORDMASK(status) (__UINT32_C(0x55555555) * (status))
#elif __SIZEOF_POINTER__ == 8
#define _SLAB_SEGMENT_STATUS_WORDMASK(status) (__UINT64_C(0x5555555555555555) * (status))
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported sizeof(void *)"
#endif /* __SIZEOF_POINTER__ != ... */
#elif SLAB_SEGMENT_STATUS_BITS == 1
#if __SIZEOF_POINTER__ == 4
#define _SLAB_SEGMENT_STATUS_WORDMASK(status) (__UINT32_C(0xffffffff) * (status))
#elif __SIZEOF_POINTER__ == 8
#define _SLAB_SEGMENT_STATUS_WORDMASK(status) (__UINT64_C(0xffffffffffffffff) * (status))
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported sizeof(void *)"
#endif /* __SIZEOF_POINTER__ != ... */
#else /* __SIZEOF_POINTER__ == ... */
#error "Unsupported SLAB_SEGMENT_STATUS_BITS"
#endif /* __SIZEOF_POINTER__ != ... */


/* Return the length (in words) of the status bitset of a given slab. */
#define SLAB_LENGTHOF_BITSET(segment_size)                                    \
	(((PRIVATE_SLAB_SEGMENT_COUNT(segment_size) * SLAB_SEGMENT_STATUS_BITS) + \
	  (BITS_PER_POINTER - 1)) /                                               \
	 BITS_PER_POINTER)
#define SLAB_SIZEOF_BITSET(segment_size) \
	(SLAB_LENGTHOF_BITSET(segment_size) * __SIZEOF_POINTER__)

#if HEAP_ALIGNMENT > __SIZEOF_POINTER__
#define SLAB_SEGMENT_OFFSET(segment_size) ((((3 + SLAB_LENGTHOF_BITSET(segment_size)) * __SIZEOF_POINTER__) + (HEAP_ALIGNMENT - 1)) & ~(HEAP_ALIGNMENT - 1))
#else /* HEAP_ALIGNMENT > __SIZEOF_POINTER__ */
#define SLAB_SEGMENT_OFFSET(segment_size) ((3 + SLAB_LENGTHOF_BITSET(segment_size)) * __SIZEOF_POINTER__)
#endif /* HEAP_ALIGNMENT <= __SIZEOF_POINTER__ */

/* Return the number of segments available per page, when each has a size of `segment_size' */
#define SLAB_SEGMENT_COUNT(segment_size) \
	((PAGESIZE - SLAB_SEGMENT_OFFSET(segment_size)) / (segment_size))


#define PRIVATE_SLAB_GET_ADDR2(a, b) a
#define PRIVATE_SLAB_GET_ADDR(x)     PRIVATE_SLAB_GET_ADDR2 x
#define PRIVATE_SLAB_GET_HINT2(a, b) b
#define PRIVATE_SLAB_GET_HINT(x)     PRIVATE_SLAB_GET_HINT2 x

#undef SLAB_CONFIG_GROWS_UPWARDS
#undef SLAB_CONFIG_GROWS_DOWNWARDS
#if (PRIVATE_SLAB_GET_HINT(KERNEL_MHINT_SLAB) & (__MAP_GROWSUP | __MAP_GROWSDOWN)) == __MAP_GROWSDOWN
#define SLAB_CONFIG_GROWS_DOWNWARDS 1
#else /* (PRIVATE_SLAB_GET_HINT(KERNEL_MHINT_SLAB) & (__MAP_GROWSUP | __MAP_GROWSDOWN)) == __MAP_GROWSDOWN */
#define SLAB_CONFIG_GROWS_UPWARDS 1
#endif /* (PRIVATE_SLAB_GET_HINT(KERNEL_MHINT_SLAB) & (__MAP_GROWSUP | __MAP_GROWSDOWN)) != __MAP_GROWSDOWN */

#define SLAB_CONFIG_INITIAL_BREAK \
	PRIVATE_SLAB_GET_ADDR(KERNEL_MHINT_SLAB)

/* [lock(mman_kernel.mm_lock)]
 * The pointer to either the lowest (SLAB_CONFIG_GROWS_DOWNWARDS), or
 * one past the greatest (SLAB_CONFIG_GROWS_UPWARDS) address that was
 * ever allocated for slab memory.
 * Since slab allocations don't carry any meta-data, they are actually
 * identified by their address, meaning that we need to keep track  of
 * the max range of pointers associated with the slab allocator.
 * NOTE: This  value starts out as `SLAB_CONFIG_INITIAL_BREAK', and is
 *       only ever extended in one direction, based on the slab growth
 *       direction. */
DATDEF void *kernel_slab_break;


/* The starting/end address of slab allocated memory. */
#ifdef SLAB_CONFIG_GROWS_DOWNWARDS
#define KERNEL_SLAB_START kernel_slab_break
#define KERNEL_SLAB_END   SLAB_CONFIG_INITIAL_BREAK
#define KERNEL_SLAB_MIN   kernel_slab_break
#define KERNEL_SLAB_MAX   __CCAST(void *)(__CCAST(byte_t *)SLAB_CONFIG_INITIAL_BREAK - PAGESIZE)
#else /* SLAB_CONFIG_GROWS_DOWNWARDS */
#define KERNEL_SLAB_START SLAB_CONFIG_INITIAL_BREAK
#define KERNEL_SLAB_END   kernel_slab_break
#define KERNEL_SLAB_MIN   SLAB_CONFIG_INITIAL_BREAK
#define KERNEL_SLAB_MAX   __CCAST(void *)(__CCAST(byte_t *)kernel_slab_break - PAGESIZE)
#endif /* !SLAB_CONFIG_GROWS_DOWNWARDS */

/* Check if a given pointer belongs to the slab allocator,
 * and can be passed to `SLAB_GET()' in order to determine
 * the associated page, as well as meta-data. */
#define KERNEL_SLAB_CHECKPTR(x) \
	((x) >= KERNEL_SLAB_START && (x) < KERNEL_SLAB_END)


#ifdef BUILDING_KERNEL_CORE
struct slab_pending_free {
	/* Using an SLIST of pending-free objects here instead of a proper
	 * lockop system might seem like bad  design, and on some level  I
	 * have to admit that you're probably right. But:
	 *  - If you take a look at `SLAB_FOREACH_SIZE()', you'll see that
	 *    the smallest possible slab has a sizeof() == sizeof(void *).
	 *  - As  such, if we want to async/non-blocking free of slabs, we
	 *    have to ensure that a pending-free descriptor is able to fit
	 *    into the smallest possible slab element.
	 *  - Because a lockop descriptor consists of 2 pointers  (being
	 *    the SLIST-next link, and the function invoked), we  aren't
	 *    actually able to fit all of that in here, meaning that  we
	 *    are  forced  to implement  async/non-blocking free  with a
	 *    special-purpose linked list  of pending-free chunks.  That
	 *    way, we don't need the pointer-to-function-to-execute, and
	 *    everything fits into a single pointer! */
	SLIST_ENTRY(slab_pending_free) spf_link; /* [0..1] Next pending free. */
};

SLIST_HEAD(slab_pending_free_slist, slab_pending_free);

LIST_HEAD(slab_list, slab);
struct slab_descriptor {
	/* Data descriptor for some fixed-length-segment slab. */
	struct atomic_lock                  sd_lock; /* Lock for this slab descriptor. */
	struct slab_list                    sd_free; /* [0..n][lock(sd_lock)] Chain of partially free slab pages. */
#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
	struct slab_list                    sd_used; /* [0..n][lock(sd_lock)] Chain of fully allocated slab pages. */
#endif /* CONFIG_HAVE_KERNEL_TRACE_MALLOC */
	WEAK struct slab_pending_free_slist sd_pend; /* [0..1] Chain of pending free segments. (pseudo-lockop list) */
};

/* Helper macros for `struct slab_descriptor::sd_lock' */
#define _slab_descriptor_reap(self)      LOCAL_slab_descriptor_service_pending() /* Define locally to clear our `sd_pend' */
#define slab_descriptor_reap(self)       (!slab_descriptor_mustreap(self) || (_slab_descriptor_reap(self), 0))
#define slab_descriptor_mustreap(self)   (__hybrid_atomic_load((self)->sd_pend.slh_first, __ATOMIC_ACQUIRE) != __NULLPTR)
#define slab_descriptor_tryacquire(self) atomic_lock_tryacquire(&(self)->sd_lock)
#define slab_descriptor_acquire(self)    atomic_lock_acquire(&(self)->sd_lock)
#define slab_descriptor_acquire_nx(self) atomic_lock_acquire_nx(&(self)->sd_lock)
#define _slab_descriptor_release(self)   atomic_lock_release(&(self)->sd_lock)
#define slab_descriptor_release(self)    (atomic_lock_release(&(self)->sd_lock), slab_descriptor_reap(self))
#define slab_descriptor_acquired(self)   atomic_lock_acquired(&(self)->sd_lock)
#define slab_descriptor_available(self)  atomic_lock_available(&(self)->sd_lock)
#define slab_descriptor_waitfor(self)    atomic_lock_waitfor(&(self)->sd_lock)
#define slab_descriptor_waitfor_nx(self) atomic_lock_waitfor_nx(&(self)->sd_lock)

#endif /* BUILDING_KERNEL_CORE */

DECL_END
#endif /* __CC__ */
#endif /* CONFIG_HAVE_KERNEL_SLAB_ALLOCATORS */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_SLAB_H */
