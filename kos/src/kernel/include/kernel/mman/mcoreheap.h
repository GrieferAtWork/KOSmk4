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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MCOREHEAP_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MCOREHEAP_H 1

#include <kernel/compiler.h>

#include <kernel/malloc-defs.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/paging.h>
#include <kernel/types.h>

#include <hybrid/sequence/list.h>
#include <hybrid/typecore.h> /* __CHAR_BIT__ */

/* The memory manager core heap.
 * This is the low-level, self-sustaining heap used for allocating
 * `struct mnode' and `struct mpart'  objects for  the purpose  of
 * describing  higher-level  heap systems  which should  no longer
 * have to make use of these functions.
 *
 * The sole consumer of functions exposed by this API should be the
 * low-level  kernel  ram  alloc/free functions  found  in "kram.h" */

#ifdef __CC__
DECL_BEGIN

/* This is the type of object (or rather: this one's size is the size of
 * the  objects) that get allocated by the mcoreheap system. The obvious
 * intend  here is to  use the coreheap  system for allocating mem-parts
 * and mem-nodes for use with `mfile_zero' and `mman_kernel' in order to
 * implement a higher-level memory mapping  system that is then  capable
 * of mapping arbitrary-size memory mappings.
 * s.a.:
 *   - MPART_F_COREPART
 *   - MNODE_F_COREPART
 */
#if __SIZEOF_MPART > __SIZEOF_MNODE
#define __SIZEOF_MCOREPART __SIZEOF_MPART
#else /* __SIZEOF_MPART > __SIZEOF_MNODE */
#define __SIZEOF_MCOREPART __SIZEOF_MNODE
#endif /* __SIZEOF_MPART <= __SIZEOF_MNODE */
#if __ALIGNOF_MPART > __ALIGNOF_MNODE
#define __ALIGNOF_MCOREPART __ALIGNOF_MPART
#else /* __ALIGNOF_MPART > __ALIGNOF_MNODE */
#define __ALIGNOF_MCOREPART __ALIGNOF_MNODE
#endif /* __ALIGNOF_MPART <= __ALIGNOF_MNODE */
union mcorepart {
	struct mpart mcp_part; /* Mem-part part */
	struct mnode mcp_node; /* Node part */
};



/* Figure out how many parts we can cram into a single page, while
 * still maintaining at least  pointer-alignment for all of  them. */
#if __ALIGNOF_MCOREPART > __SIZEOF_POINTER__
/* NOTE: 3*pointer is the smallest possible header, since we always need
 *       at least 2 pointers for the  list-link, and 1 more pointer  for
 *       the smallest-sized in-use  bitset. But also  align that  offset
 *       to match the alignment requirements of core-heap-parts. */
#define _MCOREPAGE_PARTCOUNT             ((PAGESIZE - (((2 * __SIZEOF_POINTER__) + __ALIGNOF_MCOREPART - 1) & ~(__ALIGNOF_MCOREPART - 1))) / __SIZEOF_MCOREPART)
#else /* __ALIGNOF_MCOREPART > __SIZEOF_POINTER__ */
#define _MCOREPAGE_PARTCOUNT             ((PAGESIZE - (2 * __SIZEOF_POINTER__)) / __SIZEOF_MCOREPART)
#endif /* __ALIGNOF_MCOREPART <= __SIZEOF_POINTER__ */
#define _MCOREPAGE_BITSET_LENGTH         ((_MCOREPAGE_PARTCOUNT + (__SIZEOF_POINTER__ * __CHAR_BIT__) - 1) / (__SIZEOF_POINTER__ * __CHAR_BIT__))
#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
#define _MCOREPAGE_BITSET_SIZE           (_MCOREPAGE_BITSET_LENGTH * __SIZEOF_POINTER__ * 2)
#else /* CONFIG_HAVE_KERNEL_TRACE_MALLOC */
#define _MCOREPAGE_BITSET_SIZE           (_MCOREPAGE_BITSET_LENGTH * __SIZEOF_POINTER__)
#endif /* !CONFIG_HAVE_KERNEL_TRACE_MALLOC */
#define _MCOREPAGE_HEADER_SIZE_UNALIGNED ((1 * __SIZEOF_POINTER__) + _MCOREPAGE_BITSET_SIZE)
#if __ALIGNOF_MCOREPART > __SIZEOF_POINTER__
#define _MCOREPAGE_HEADER_SIZE ((_MCOREPAGE_HEADER_SIZE_UNALIGNED + __ALIGNOF_MCOREPART - 1) & ~(__ALIGNOF_MCOREPART - 1))
#else /* __ALIGNOF_MCOREPART > __SIZEOF_POINTER__ */
#define _MCOREPAGE_HEADER_SIZE _MCOREPAGE_HEADER_SIZE_UNALIGNED
#endif /* __ALIGNOF_MCOREPART <= __SIZEOF_POINTER__ */
#define _MCOREPAGE_FREESPACE    (PAGESIZE - _MCOREPAGE_HEADER_SIZE)
#define MCOREPAGE_PARTCOUNT     (_MCOREPAGE_FREESPACE / __SIZEOF_MCOREPART)
#define MCOREPAGE_BITSET_LENGTH ((MCOREPAGE_PARTCOUNT + (__SIZEOF_POINTER__ * __CHAR_BIT__) - 1) / (__SIZEOF_POINTER__ * __CHAR_BIT__))

#if MCOREPAGE_PARTCOUNT < 3
#error "We need to be able to fit at least 3 parts into a single core page"
#endif /* MCOREPAGE_PARTCOUNT < 3 */




/* On a level as low as the mcoreheap is implemented at, all allocations
 * have  to be done in multiples of  whole pages. As such, the mcoreheap
 * allocator is implemented as a slab-style allocator. */
struct mcorepage;
SLIST_HEAD(mcorepage_slist, mcorepage);
struct mcorepage {
	SLIST_ENTRY(mcorepage) mcp_link;                            /* [lock(mman_kernel.mm_lock)] Chain of allocated/free core pages. */
	uintptr_t              mcp_used[_MCOREPAGE_BITSET_LENGTH];  /* [lock(mman_kernel.mm_lock)] Bitset of currently allocated parts. */
#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
	uintptr_t             _mcp_reach[_MCOREPAGE_BITSET_LENGTH]; /* Used internally to mark reachable parts. */
#endif /* CONFIG_HAVE_KERNEL_TRACE_MALLOC */
#if _MCOREPAGE_HEADER_SIZE > _MCOREPAGE_HEADER_SIZE_UNALIGNED
	byte_t               __mcp_pad[_MCOREPAGE_HEADER_SIZE - _MCOREPAGE_HEADER_SIZE_UNALIGNED]; /* ... */
#endif /* _MCOREPAGE_HEADER_SIZE > _MCOREPAGE_HEADER_SIZE_UNALIGNED */
	union mcorepart        mcp_part[MCOREPAGE_PARTCOUNT];      /* Vector of parts provided by this page. */
};


/* Internal lists for mcoreheap. */
DATDEF struct mcorepage_slist mcoreheap_lists[2];

/* [0..n][lock(mman_kernel.mm_lock)]
 * List of (fully; as in: all bits in `mcp_used' are set) mcoreheap pages. */
#define mcoreheap_usedlist mcoreheap_lists[0]

/* [1..n][lock(mman_kernel.mm_lock)]
 * List of mcoreheap pages that still contain available parts.
 * NOTE: This list must _always_ be non-empty, and there  must
 *       _always_ be at  least 2 additional  core parts  ready
 *       for allocation at any time. This is required, because
 *       in  order to allocate additional pages, the mcoreheap
 *       allocator itself already requires 2 parts in order to
 *       do replicate itself! */
#define mcoreheap_freelist mcoreheap_lists[1]

/* [>= 2][lock(mman_kernel.mm_lock)]
 * The total # of free core parts currently available through `mcoreheap_free' */
DATDEF size_t mcoreheap_freecount;



/************************************************************************/
/* Mem-Core-Heap low-level alloc/free functions.                        */
/************************************************************************/


/* Allocate an additional core part from the core heap.
 * The  caller must be holding a lock to the kernel mman, but should also
 * be  aware that a call to this  function may result in additional nodes
 * to be mapped  into the kernel  mman (meaning that  the caller must  be
 * able to deal with the kernel mman's mappings-tree changing as a result
 * of a call to this function)
 * @return: * :   The base-address of the newly allocated mem-core-part.
 * @return: NULL: Insufficient physical/virtual memory. This is only ever
 *                returned when memory has  actually run out, since  this
 *                function  doesn't  actually  need  to  do  any locking.
 *                As such, a NULL-return-value here means that the system
 *                has run out  of memory on  the lowest, possible  level.
 *                That is: `page_malloc_nocc()' failed. */
FUNDEF NOBLOCK ATTR_MALLOC WUNUSED union mcorepart *
NOTHROW(FCALL mcoreheap_alloc_locked_nx_nocc)(void);
FUNDEF NOBLOCK ATTR_MALLOC WUNUSED union mcorepart *
NOTHROW(FCALL mcoreheap_alloc_locked_nx)(void);

/* Do  all  of  the necessary  locking  and throw  an  exception if  the  allocation failed.
 * Essentially, this is just a convenience wrapper around `mcoreheap_alloc_locked_nx_nocc()'
 * NOTE: This function also does `system_cc()' */
FUNDEF ATTR_MALLOC ATTR_RETNONNULL WUNUSED union mcorepart *FCALL
mcoreheap_alloc(void) THROWS(E_BADALLOC, E_WOULDBLOCK);

/* Free the given mem-core-heap part. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mcoreheap_free)(union mcorepart *__restrict part);

/* Same as `mcoreheap_free()', but no need to jump through all of the hoops
 * of enqueuing the free of `part' as a lockop when no lock can be acquired
 * to the kernel mman,  since the caller allows  us to assume that  they've
 * already acquired a lock to the kernel mman. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mcoreheap_free_locked)(union mcorepart *__restrict part);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MCOREHEAP_H */
