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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MCOREHEAP_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MCOREHEAP_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/heap.h>
#include <kernel/malloc-defs.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/cc.h>
#include <kernel/mman/kram.h>
#include <kernel/mman/mcoreheap.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/phys.h>
#include <kernel/mman/sync.h>
#include <kernel/mman/unmapped.h>
#include <kernel/paging.h>
#include <kernel/printk.h>
#include <kernel/types.h>

#include <hybrid/align.h>

#include <kos/except.h>
#include <kos/kernel/paging.h>
#include <kos/lockop.h>
#include <sys/param.h>

#include <assert.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/* Assert that constants are correct. */
static_assert(alignof(struct mpart) == __ALIGNOF_MPART);
static_assert(alignof(struct mnode) == __ALIGNOF_MNODE);
static_assert(alignof(union mcorepart) == __ALIGNOF_MCOREPART);
static_assert(sizeof(struct mpart) == __SIZEOF_MPART);
static_assert(sizeof(struct mnode) == __SIZEOF_MNODE);
static_assert(sizeof(union mcorepart) == __SIZEOF_MCOREPART);
static_assert(offsetof(struct mcorepage, mcp_part) == _MCOREPAGE_HEADER_SIZE);

/* Also make sure that `struct mcorepage' really fits into a single page! */
static_assert(sizeof(struct mcorepage) <= PAGESIZE);

#ifndef SIZEOF_POINTER
#define SIZEOF_POINTER __SIZEOF_POINTER__
#endif /* !SIZEOF_POINTER */

#define INUSE_BITSET_INDEXOF(index) ((index) / (SIZEOF_POINTER * NBBY))
#define INUSE_BITSET_SHIFTOF(index) ((index) % (SIZEOF_POINTER * NBBY))
#define INUSE_BITSET_GET(page, index) \
	(((page)->mcp_used[INUSE_BITSET_INDEXOF(index)] >> INUSE_BITSET_SHIFTOF(index)) & 1)
#define INUSE_BITSET_TURNOFF(page, index) \
	((page)->mcp_used[INUSE_BITSET_INDEXOF(index)] &= ~((uintptr_t)1 << INUSE_BITSET_SHIFTOF(index)))
#define INUSE_BITSET_TURNON(page, index) \
	((page)->mcp_used[INUSE_BITSET_INDEXOF(index)] |= ((uintptr_t)1 << INUSE_BITSET_SHIFTOF(index)))


/* The memory-file to which internal self-replication parts belong.
 * This   file  must   be  (and   is  assumed   to  be)  anonymous! */
#define mcore_file mfile_zero


/* The initial mem-core page. (needed to kick-start the mem-core system) */
#ifdef CONFIG_HAVE_KERNEL_TRACE_MALLOC
ATTR_MALL_UNTRACKED
#endif /* CONFIG_HAVE_KERNEL_TRACE_MALLOC */
PRIVATE ATTR_ALIGNED(PAGESIZE) struct mcorepage _mcore_initpage = {
	.mcp_link = { NULL },
	.mcp_used = { 0, },
	/* ... */
};


/* Internal lists for mcoreheap. */
PUBLIC struct mcorepage_slist mcoreheap_lists[2] = {
	/* [0..n][lock(mman_kernel.mm_lock)]
	 * List of (fully; as in: all bits in `mcp_used' are set) mcoreheap pages. */
	[0] = LIST_HEAD_INITIALIZER(&mcoreheap_usedlist),

	/* [1..n][lock(mman_kernel.mm_lock)]
	 * List of mcoreheap pages that still contain available parts.
	 * NOTE: This list must _always_ be non-empty, and there  must
	 *       _always_ be at  least 2 additional  core parts  ready
	 *       for allocation at any time. This is required, because
	 *       in  order to allocate additional pages, the mcoreheap
	 *       allocator itself already requires 2 parts in order to
	 *       do replicate itself! */
	[1] = { &_mcore_initpage },
};


/* [>= 2][lock(mman_kernel.mm_lock)]
 * The total # of free core parts currently available through `mcoreheap_free' */
PUBLIC size_t mcoreheap_freecount = lengthof(_mcore_initpage.mcp_part);



/************************************************************************/
/* Mem-Core-Heap low-level alloc/free functions.                        */
/************************************************************************/

/* The max # of still-valid bits in `mcorepage::mcp_used[MCOREPAGE_BITSET_LENGTH - 1]' */
#define LAST_BITSET_WORD_PARTS (MCOREPAGE_PARTCOUNT % (SIZEOF_POINTER * NBBY))
/* Mask for all valid bits in `mcorepage::mcp_used[MCOREPAGE_BITSET_LENGTH - 1]' */
#define LAST_BITSET_WORD_ALLUSED (((uintptr_t)1 << LAST_BITSET_WORD_PARTS) - 1)

/* Check if the given mcorepage is fully in-use. */
LOCAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL mcorepage_allused)(struct mcorepage const *__restrict self) {
#if LAST_BITSET_WORD_PARTS == 0
#if MCOREPAGE_BITSET_LENGTH == 1
	return self->mcp_used[0] == (uintptr_t)-1;
#else /* MCOREPAGE_BITSET_LENGTH == 1 */
	unsigned int i;
	for (i = 0; i < MCOREPAGE_BITSET_LENGTH; ++i) {
		if (self->mcp_used[i] != (uintptr_t)-1)
			return false; /* Still contains free slots! */
	}
	return true;
#endif /* MCOREPAGE_BITSET_LENGTH != 1 */
#else /* LAST_BITSET_WORD_PARTS == 0 */
#if MCOREPAGE_BITSET_LENGTH == 1
	return (self->mcp_used[0] & LAST_BITSET_WORD_ALLUSED) == LAST_BITSET_WORD_ALLUSED;
#else /* MCOREPAGE_BITSET_LENGTH == 1 */
	unsigned int i;
	for (i = 0; i < (MCOREPAGE_BITSET_LENGTH - 1); ++i) {
		if (self->mcp_used[i] != (uintptr_t)-1)
			return false; /* Still contains free slots! */
	}

	/* Check the incomplete last word of the bitset for fully-in-use. */
	return (self->mcp_used[MCOREPAGE_BITSET_LENGTH - 1] &
	        LAST_BITSET_WORD_ALLUSED) == LAST_BITSET_WORD_ALLUSED;
#endif /* MCOREPAGE_BITSET_LENGTH != 1 */
#endif /* LAST_BITSET_WORD_PARTS != 0 */
}

/* Check if the given mcorepage is fully free. */
LOCAL NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL mcorepage_allfree)(struct mcorepage const *__restrict self) {
#if LAST_BITSET_WORD_PARTS == 0
#if MCOREPAGE_BITSET_LENGTH == 1
	return self->mcp_used[0] == 0;
#else /* MCOREPAGE_BITSET_LENGTH == 1 */
	unsigned int i;
	for (i = 0; i < MCOREPAGE_BITSET_LENGTH; ++i) {
		if (self->mcp_used[i] != 0)
			return false; /* Still contains used slots! */
	}
	return true;
#endif /* MCOREPAGE_BITSET_LENGTH != 1 */
#else /* LAST_BITSET_WORD_PARTS == 0 */
#if MCOREPAGE_BITSET_LENGTH == 1
	return (self->mcp_used[0] & LAST_BITSET_WORD_ALLUSED) == 0;
#else /* MCOREPAGE_BITSET_LENGTH == 1 */
	unsigned int i;
	for (i = 0; i < (MCOREPAGE_BITSET_LENGTH - 1); ++i) {
		if (self->mcp_used[i] != 0)
			return false; /* Still contains used slots! */
	}

	/* Check the incomplete last word of the bitset for fully-in-use. */
	return (self->mcp_used[MCOREPAGE_BITSET_LENGTH - 1] &
	        LAST_BITSET_WORD_ALLUSED) == 0;
#endif /* MCOREPAGE_BITSET_LENGTH != 1 */
#endif /* LAST_BITSET_WORD_PARTS != 0 */
}

/* Find and return a free (unused) part index. */
LOCAL NOBLOCK WUNUSED NONNULL((1)) unsigned int
NOTHROW(FCALL mcorepage_findfree)(struct mcorepage *__restrict self) {
	unsigned int word_index;
	uintptr_t word;
#if LAST_BITSET_WORD_PARTS == 0
#if MCOREPAGE_BITSET_LENGTH == 1
	word_index = 0;
	word       = self->mcp_used[0];
#else /* MCOREPAGE_BITSET_LENGTH == 1 */
	for (word_index = 0;; ++word_index) {
		assert(word_index < MCOREPAGE_BITSET_LENGTH);
		word = self->mcp_used[word_index];
		if (word != (uintptr_t)-1)
			break;
	}
#endif /* MCOREPAGE_BITSET_LENGTH != 1 */
#else /* LAST_BITSET_WORD_PARTS == 0 */
#if MCOREPAGE_BITSET_LENGTH == 1
	word_index = 0;
	word       = self->mcp_used[0];
	assert((word & LAST_BITSET_WORD_ALLUSED) != LAST_BITSET_WORD_ALLUSED);
#else /* MCOREPAGE_BITSET_LENGTH == 1 */
	for (word_index = 0; word_index < (MCOREPAGE_BITSET_LENGTH - 1); ++word_index) {
		word = self->mcp_used[word_index];
		if (word != (uintptr_t)-1)
			goto got_word;
	}
	word = self->mcp_used[word_index];
	assert((word & LAST_BITSET_WORD_ALLUSED) != LAST_BITSET_WORD_ALLUSED);
got_word:
#endif /* MCOREPAGE_BITSET_LENGTH != 1 */
#endif /* LAST_BITSET_WORD_PARTS != 0 */
	assert(word != (uintptr_t)-1);
	word_index *= (SIZEOF_POINTER * NBBY);
	while (word & 1) {
		++word_index;
		word >>= 1;
	}
	return word_index;
}


/* Unconditionally allocate a mem-core-part from `mcoreheap_freelist'.
 * The  caller must  ensure that parts  are available, and  that the 2
 * reserved parts aren't used inappropriately. */
PRIVATE NOBLOCK ATTR_MALLOC ATTR_RETNONNULL WUNUSED union mcorepart *
NOTHROW(FCALL mcoreheap_alloc_nocc_impl)(void) {
	union mcorepart *result;
	struct mcorepage *page;
	unsigned int index;

	/* Pick the first known free-list. */
	page = SLIST_FIRST(&mcoreheap_freelist);
	assert(!mcorepage_allused(page));
	index  = mcorepage_findfree(page);
	result = &page->mcp_part[index];

	/* Mark the chosen part as in-use. */
	INUSE_BITSET_TURNON(page, index);
	--mcoreheap_freecount;

	/* Check if the page has become fully in-use. */
	if (mcorepage_allused(page)) {
		/* Remove from the free-list, and add to the fully-used list. */
		assert(page == SLIST_FIRST(&mcoreheap_freelist));
		SLIST_REMOVE_HEAD(&mcoreheap_freelist, mcp_link);
		SLIST_INSERT_HEAD(&mcoreheap_usedlist, page, mcp_link);
	}
	return result;
}

/* Initialize and register the given `page' for dynamic allocations. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mcoreheap_provide_page)(struct mcorepage *__restrict page) {
	/* Initialize the in-use bitset to all-free. */
	bzero(page->mcp_used, sizeof(page->mcp_used));

	/* Insert the page into the free-list. */
	SLIST_INSERT_HEAD(&mcoreheap_freelist, page, mcp_link);

	/* Account for all of the newly added parts. */
	mcoreheap_freecount += MCOREPAGE_PARTCOUNT;
}


/* Check if  the given  `node' has  all of  the
 * required properties of a core-heap mem-node. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL is_coreheap_node)(struct mnode const *__restrict node) {
	struct mpart const *part;
	part = node->mn_part;
	if unlikely(!part)
		goto nope;

	/* Make sure that `part' isn't externally visible.
	 * This is required since we don't intend on locking the part,
	 * meaning that we have to be  certain that holding a lock  to
	 * the kernel mman  will be  enough to keep  anyone else  from
	 * seeing the part in question. */
	if (isshared(part))
		goto nope;
	if (part->mp_flags != (MPART_F_COREPART | MPART_F_MLOCK_FROZEN | MPART_F_MLOCK))
		goto nope;
	if (TAILQ_ISBOUND(part, mp_allparts))
		goto nope;
	if (part->mp_file != &mcore_file)
		goto nope;
	if (!LIST_EMPTY(&part->mp_copy))
		goto nope;
	if (LIST_FIRST(&part->mp_share) != node)
		goto nope;
	if (LIST_NEXT(node, mn_link) != NULL)
		goto nope;

	/* Now just validate the rest. */
	if (part->mp_state != MPART_ST_MEM)
		goto nope;
	if (part->mp_minaddr != 0)
		goto nope;
	if (part->mp_maxaddr != (pos_t)(mnode_getsize(node) - 1))
		goto nope;
	if (part->mp_blkst_ptr != NULL)
		goto nope;
	if (part->mp_meta != NULL)
		goto nope;
	if (node->mn_flags != (MNODE_F_PREAD | MNODE_F_PWRITE | MNODE_F_SHARED |
	                       MNODE_F_COREPART | MNODE_F_MLOCK))
		goto nope;
	if (node->mn_fspath != NULL)
		goto nope;
	if (node->mn_fsname != NULL)
		goto nope;
	if (node->mn_module != NULL)
		goto nope;
	if (node->mn_partoff != 0)
		goto nope;
	assert(node->mn_mman == &mman_kernel);
	assert(node->mn_link.le_prev == &part->mp_share.lh_first);
	assert(((size_t)part->mp_mem.mc_size * PAGESIZE) == mnode_getsize(node));
	return true;
nope:
	return false;
}


/* Try to extend the given node by 1 page below. */
PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL mcoreheap_replicate_extend_below)(struct mnode *__restrict node) {
	struct mpart *part;
	physpage_t ppage;
	part  = node->mn_part;
	ppage = part->mp_mem.mc_start - 1;
	if (page_malloc_at_nocc(ppage) != PAGE_MALLOC_AT_SUCCESS)
		goto fail;

	/* If necessary, make sure that the new page is prepared! */
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	if (!pagedir_prepareone(node->mn_minaddr - PAGESIZE)) {
		page_ccfree(part->mp_mem.mc_start - 1, 1);
		goto fail;
	}
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

	/* Success! (Start by physically mapping the new page) */
	pagedir_mapone(node->mn_minaddr - PAGESIZE, physpage2addr(ppage),
	               PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	pagedir_unprepareone(node->mn_minaddr - PAGESIZE);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

	/* Update the node/part */
	mman_mappings_removenode(&mman_kernel, node);
	node->mn_minaddr -= PAGESIZE;
	part->mp_mem.mc_start -= 1;
	part->mp_mem.mc_size += 1;
	part->mp_maxaddr += PAGESIZE;
	mman_mappings_insert_and_verify(&mman_kernel, node);
	return true;
fail:
	return false;
}

PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL mcoreheap_replicate_extend_above)(struct mnode *__restrict node) {
	struct mpart *part;
	physpage_t ppage;
	part  = node->mn_part;
	ppage = part->mp_mem.mc_start + part->mp_mem.mc_size;
	if (page_malloc_at_nocc(ppage) != PAGE_MALLOC_AT_SUCCESS)
		goto fail;

	/* If necessary, make sure that the new page is prepared! */
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	if (!pagedir_prepareone(node->mn_maxaddr + 1)) {
		page_ccfree(part->mp_mem.mc_start - 1, 1);
		goto fail;
	}
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

	/* Success! (Start by physically mapping the new page) */
	pagedir_mapone(node->mn_maxaddr + 1, physpage2addr(ppage),
	               PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	pagedir_unprepareone(node->mn_maxaddr + 1);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

	/* Update the node/part */
	mman_mappings_removenode(&mman_kernel, node);
	part->mp_mem.mc_size += 1;
	node->mn_maxaddr += PAGESIZE;
	part->mp_maxaddr += PAGESIZE;
	mman_mappings_insert_and_verify(&mman_kernel, node);
	return true;
fail:
	return false;
}

/* Try to merge the 2 given nodes.
 * The caller has already ensured that the 2 nodes are adjacent, and  that
 * both of them fulfill the conditions checked for by `is_coreheap_node()' */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mcoreheap_try_merge_nodes)(struct mnode *__restrict lo,
                                         struct mnode *__restrict hi) {
	struct mpart *lopart, *hipart;
	lopart = lo->mn_part;
	hipart = hi->mn_part;

	/* Try to merge memory. */
	if ((lopart->mp_mem.mc_start + lopart->mp_mem.mc_size) == hipart->mp_mem.mc_start) {
		/* Simple (but rather unlikely) case: the lo- and hi-parts are physically consecutive */
		lopart->mp_mem.mc_size += hipart->mp_mem.mc_size;
	} else {
		/* Cannot merge (attempting to realloc physical memory would  be
		 * prone to race conditions, since  we'd have to make sure  that
		 * no-one is writing to the region we're trying to modify in the
		 * mean time, which we can't safely do) */
		return;
	}

	/* Fix-up mappings. */
	mman_mappings_removenode(&mman_kernel, lo);
	mman_mappings_removenode(&mman_kernel, hi);
	assert(!lo->mn_module && !hi->mn_module);
	lo->mn_maxaddr = hi->mn_maxaddr;
	lopart->mp_maxaddr += mnode_getsize(hi);
	mman_mappings_insert_and_verify(&mman_kernel, lo);

	/* `hi' isn't re-inserted, so we must ensure that it  doesn't
	 * continue to linger within the list of writable nodes. This
	 * list  is a  no-op for the  kernel mman, but  must still be
	 * kept valid and  not end up  containing dangling  pointers.
	 * Otherwise, we might end up with memory corruptions. */
	if unlikely(LIST_ISBOUND(hi, mn_writable))
		LIST_REMOVE(hi, mn_writable);

	/* Destroy the existing mapping. */
	mcoreheap_free_locked(container_of(hipart, union mcorepart, mcp_part));
	mcoreheap_free_locked(container_of(hi, union mcorepart, mcp_node));
}

/* Try to replicate the mem-core-heap by extending a previously
 * allocated extension further.
 * If this fails, return `false'. Otherwise, return `true' on success. */
PRIVATE NOBLOCK bool
NOTHROW(FCALL mcoreheap_replicate_extend)(void) {
	struct mcorepage *page;
	SLIST_FOREACH (page, &mcoreheap_usedlist, mcp_link) {
		struct mnode *node;
		if (page == &_mcore_initpage)
			continue; /* We can never extend this one... */
		node = mnode_tree_locate(mman_kernel.mm_mappings, page);
		assert(node);
		if unlikely(!is_coreheap_node(node)) /* Should always be the case, but better be sure. */
			continue;
		if (mnode_getminaddr(node) == page) {
			struct mnode *prev = mnode_tree_prevnode(node);
			if (!prev || mnode_getendaddr(prev) < mnode_getaddr(node)) {
				/* Try to extend `node' below */
				if (mcoreheap_replicate_extend_below(node)) {
					/* Try to merge nodes if possible. */
					if (prev && mnode_getendaddr(prev) == mnode_getaddr(node) && is_coreheap_node(prev)) {
						mcoreheap_try_merge_nodes(prev, node);
					}
					page = (struct mcorepage *)((byte_t *)page - PAGESIZE);
					goto ok;
				}
			}
		}
		if ((void *)((byte_t *)mnode_getendaddr(node) - PAGESIZE) == page) {
			struct mnode *next = mnode_tree_nextnode(node);
			if (!next || mnode_getendaddr(node) < mnode_getaddr(next)) {
				/* Try to extend `node' above */
				if (mcoreheap_replicate_extend_above(node)) {
					/* Try to merge nodes if possible. */
					if (next && mnode_getendaddr(node) == mnode_getaddr(next) && is_coreheap_node(next))
						mcoreheap_try_merge_nodes(node, next);
					page = (struct mcorepage *)((byte_t *)page + PAGESIZE);
					goto ok;
				}
			}
		}
	}
	return false;
ok:
	/* Provide the newly added page to the allocator. */
	mcoreheap_provide_page(page);
	return true;
}


/* Self-replicate the mem-core-heap to expand into yet another page.
 * For this purpose, _always_ inherit  the given `node' and  `part',
 * even  if they don't end up being  used for the replication (as is
 * the case when this function is able to extend an older  mem-core-
 * heap page)
 * NOTE: The given `node' and `part' are assumed to be allocated by `mcoreheap_alloc_nocc_impl()'!
 * @return: true:  Successfully replicated the  core heap. In  this case,  the
 *                 caller  may  assume  that  at  least  `MCOREPAGE_PARTCOUNT'
 *                 additional core parts have become available for allocation.
 * @return: false: Insufficient physical memory (`page_malloc()' failed, or
 *                 failed to find a free spot within the kernel-space mman) */
PRIVATE NOBLOCK NONNULL((1, 2)) bool
NOTHROW(FCALL mcoreheap_replicate_nocc)(/*inherit(always)*/ struct mpart *__restrict part,
                                        /*inherit(always)*/ struct mnode *__restrict node) {
	/* Check if we might be able to extend a pre-existing mcoreheap node/part pair. */
	if (mcoreheap_replicate_extend()) {
		/* Noice :) */
		mcoreheap_free_locked(container_of(part, union mcorepart, mcp_part));
		mcoreheap_free_locked(container_of(node, union mcorepart, mcp_node));
		return true;
	}

	/* Must actually create a new node/part pair! */
	node->mn_minaddr = (byte_t *)mman_findunmapped(&mman_kernel,
	                                               MHINT_GETADDR(KERNEL_MHINT_COREPAGE), PAGESIZE,
	                                               MHINT_GETMODE(KERNEL_MHINT_COREPAGE));
	if unlikely(node->mn_minaddr == MAP_FAILED) {
		printk(KERN_CRIT "[mcore] low-level OOM: Unable to find spot to place a new core-page\n");
		return false;
	}

	/* Allocate the physical page that'll be holding the core-page */
	part->mp_mem.mc_start = page_mallocone_nocc();
	if unlikely(part->mp_mem.mc_start == PHYSPAGE_INVALID) {
		printk(KERN_CRIT "[mcore] low-level OOM: Unable to allocate physical memory\n");
		return false;
	}

	/* Make sure that the backing page directory is prepared. */
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	if (!pagedir_prepare(node->mn_minaddr, PAGESIZE)) {
		page_ccfree(part->mp_mem.mc_start, 1);
		printk(KERN_CRIT "[mcore] low-level OOM: Unable to prepare page directory\n");
		return false;
	}
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

	/* Initialize the (remainder of the) mem-part */
	part->mp_refcnt = 1;
	part->mp_flags  = MPART_F_COREPART | MPART_F_MLOCK_FROZEN | MPART_F_MLOCK;
	part->mp_xflags = MPART_XF_NORMAL;
	part->mp_state  = MPART_ST_MEM;
	part->mp_file   = incref(&mcore_file);
	LIST_INIT(&part->mp_copy);
	SLIST_INIT(&part->mp_lockops);
	TAILQ_ENTRY_UNBOUND_INIT(&part->mp_allparts);
	DBG_memset(&part->mp_changed, 0xcc, sizeof(part->mp_changed));
	part->mp_minaddr = (pos_t)(0);
	part->mp_maxaddr = (pos_t)(PAGESIZE - 1);
	_mpart_init_asanon(part);
	part->mp_blkst_ptr   = NULL;
	part->mp_mem.mc_size = 1;
	part->mp_meta        = NULL;

	/* Initialize the (remainder of the) mem-node */
	node->mn_maxaddr      = node->mn_minaddr + PAGESIZE - 1;
	node->mn_flags        = MNODE_F_PREAD | MNODE_F_PWRITE | MNODE_F_SHARED |
	                        MNODE_F_COREPART | MNODE_F_MLOCK;
	node->mn_part         = part;
	node->mn_fspath       = NULL;
	node->mn_fsname       = NULL;
	node->mn_mman         = &mman_kernel;
	node->mn_partoff      = 0;
	node->mn_module       = NULL;
	part->mp_share.lh_first = node;
	node->mn_link.le_next   = NULL;
	node->mn_link.le_prev   = &part->mp_share.lh_first;

	/* Load the mem-node into the kernel mman. */
	LIST_INSERT_HEAD(&mman_kernel.mm_writable, node, mn_writable);
	mman_mappings_insert_and_verify(&mman_kernel, node);

	/* And finally: immediately map the new core-page into the kernel mman. */
	pagedir_mapone(node->mn_minaddr,
	               physpage2addr(part->mp_mem.mc_start),
	               PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	pagedir_unprepare(node->mn_minaddr, PAGESIZE);
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */

	/* With everything mapped, register the new page for use. */
	mcoreheap_provide_page((struct mcorepage *)node->mn_minaddr);

	/* And we're done! */
	return true;
}

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
PUBLIC NOBLOCK ATTR_MALLOC WUNUSED union mcorepart *
NOTHROW(FCALL mcoreheap_alloc_locked_nx_nocc)(void) {
	union mcorepart *result;
	union mcorepart *replica;
	assert(mcoreheap_freecount >= 2);

	/* Allocate the part. */
	result = mcoreheap_alloc_nocc_impl();

	/* Check if there are still enough parts left for self-replication. */
	if (mcoreheap_freecount >= 2)
		goto done;

	/* We're down to the last couple of (for this purpose reserved) nodes.
	 * As such,  use  the last  2  of  them to  replicate  the  core-heap. */
	replica = mcoreheap_alloc_nocc_impl();
	if unlikely(!mcoreheap_replicate_nocc(&result->mcp_part,
	                                      &replica->mcp_node)) {
		/* Free the already-allocated part. */
		assert(mcoreheap_freecount < 2);
		mcoreheap_free_locked(replica);
		mcoreheap_free_locked(result);
		assert(mcoreheap_freecount >= 2);
		return NULL;
	}

	/* At this point, there should be at least 3 parts, since we statically
	 * assert that a mem-core-page is capable of holding at least that many
	 * core-parts. */
	assert(mcoreheap_freecount >= 3);
	result = mcoreheap_alloc_nocc_impl();
done:
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
	mempatl(result, DEBUGHEAP_FRESH_MEMORY, sizeof(*result));
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
	return result;
}

PUBLIC NOBLOCK ATTR_MALLOC WUNUSED union mcorepart *
NOTHROW(FCALL mcoreheap_alloc_locked_nx)(void) {
	union mcorepart *result;
	result = mcoreheap_alloc_locked_nx_nocc();
	if unlikely(!result) {
		ccstate_t ccstate = CCSTATE_INIT;
		do {
			if (!system_cc_s_noblock(&ccstate))
				THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, sizeof(*result));
			result = mcoreheap_alloc_locked_nx_nocc();
		} while (!result);
	}
	return result;
}



/* Do  all  of  the necessary  locking  and throw  an  exception if  the  allocation failed.
 * Essentially, this is just a convenience wrapper around `mcoreheap_alloc_locked_nx_nocc()'
 * NOTE: This function also does `system_cc()' */
PUBLIC ATTR_MALLOC ATTR_RETNONNULL WUNUSED union mcorepart *FCALL
mcoreheap_alloc(void) THROWS(E_BADALLOC, E_WOULDBLOCK) {
	union mcorepart *result;
	mman_lock_acquire(&mman_kernel);
	result = mcoreheap_alloc_locked_nx_nocc();
	mman_lock_release(&mman_kernel);
	if unlikely(!result) {
		ccstate_t ccstate = CCSTATE_INIT;
		do {
			if (!system_cc_s(&ccstate))
				THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, sizeof(*result));
			mman_lock_acquire(&mman_kernel);
			result = mcoreheap_alloc_locked_nx_nocc();
			mman_lock_release(&mman_kernel);
		} while (!result);
	}
	return result;
}


PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(mman) *
NOTHROW(FCALL lockop_coreheap_free_callback)(Toblockop(mman) *__restrict self,
                                             struct mman *__restrict UNUSED(mm)) {
	union mcorepart *me;
	me = (union mcorepart *)self;
	mcoreheap_free_locked(me);
	return NULL;
}


/* Free the given mem-core-heap part. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mcoreheap_free)(union mcorepart *__restrict part) {
	if (mman_lock_tryacquire(&mman_kernel)) {
		mcoreheap_free_locked(part);
		mman_lock_release(&mman_kernel);
	} else {
		/* Must enqueue a lock operation for the kernel mman. */
		Toblockop(mman) *lop;
		lop = (Toblockop(mman) *)part;
		lop->olo_func = &lockop_coreheap_free_callback;
		SLIST_ATOMIC_INSERT(&mman_kernel_lockops, lop, olo_link);
		_mman_lockops_reap(&mman_kernel);
	}
}


/* Same as `mcoreheap_free()', but no need to jump through all of the hoops
 * of enqueuing the free of `part' as a lockop when no lock can be acquired
 * to the kernel mman,  since the caller allows  us to assume that  they've
 * already acquired a lock to the kernel mman. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mcoreheap_free_locked)(union mcorepart *__restrict part) {
	unsigned int index;
	struct mcorepage *page;
	bool was_all_used;

	/* Extract the associated page from `part' */
	page  = (struct mcorepage *)FLOOR_ALIGN((uintptr_t)part, PAGESIZE);
	index = (unsigned int)(part - page->mcp_part);

	/* Assert that `page' exists. */
#ifndef NDEBUG
	do {
		SLIST_CONTAINS(&mcoreheap_usedlist, page, mcp_link, goto found_page);
		SLIST_CONTAINS(&mcoreheap_freelist, page, mcp_link, goto found_page);
	} while (__assertion_checkf(NULL,
	                            "Part %p in page %p not found in coreheap\n"
	                            "%[gen:c]", /* Try to include a traceback if allocated by kmalloc() */
	                            part, page, &kmalloc_printtrace, part));
found_page:
#endif /* !NDEBUG */

	assertf(part == &page->mcp_part[index],
	        "Bad part pointer %p doesn't equal part %p at index %u of page %p",
	        part, &page->mcp_part[index], index, page);
	assertf(INUSE_BITSET_GET(page, index),
	        "Part at %p (index %u in page at %p) not marked as allocated",
	        part, index, page);

#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
	mempatl(part, DEBUGHEAP_NO_MANS_LAND, sizeof(*part));
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */

	was_all_used = mcorepage_allused(page);

	/* Clear the in-use bit of the part. */
	INUSE_BITSET_TURNOFF(page, index);
	++mcoreheap_freecount;

	if (was_all_used) {
		/* Move the page from the `mcoreheap_usedlist'
		 * list  into  the  `mcoreheap_freelist'  list */
		SLIST_REMOVE(&mcoreheap_usedlist, page, mcp_link);
		SLIST_INSERT_HEAD(&mcoreheap_freelist, page, mcp_link);
	} else if (mcoreheap_freecount > (MCOREPAGE_PARTCOUNT + 2)) {
		/* If the page was fully free'd, then unmap the backing memory
		 * from the kernel mman.
		 *
		 * Note that (with the exception of `_mcore_initpage'), we can
		 * just  use  `mman_unmap_kram_locked()'  to  free  the  page! */
		if (page != &_mcore_initpage && mcorepage_allfree(page)) {
			SLIST_REMOVE(&mcoreheap_freelist, page, mcp_link);
			mcoreheap_freecount -= MCOREPAGE_PARTCOUNT;
			mman_unmap_kram_locked(page, PAGESIZE);
		}
	}
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MCOREHEAP_C */
