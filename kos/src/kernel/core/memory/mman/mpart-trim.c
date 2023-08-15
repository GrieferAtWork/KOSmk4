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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_TRIM_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_TRIM_C 1
#define __WANT_MPART__mp_nodlsts
#define __WANT_MPART__mp_trmlop
#define __WANT_MFUTEX__mfu_dead
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/heap.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/cc.h>
#include <kernel/mman/mcoreheap.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/mpartmeta.h>
#include <kernel/swap.h>
#include <sched/task.h> /* _TASK_FDBGHEAPDMEM */

#include <hybrid/align.h>
#include <hybrid/sched/preemption.h>

#include <assert.h>
#include <atomic.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>


/*[[[config CONFIG_HAVE_KERNEL_MPART_TRIM = true]]]*/
#ifdef CONFIG_NO_KERNEL_MPART_TRIM
#undef CONFIG_HAVE_KERNEL_MPART_TRIM
#elif !defined(CONFIG_HAVE_KERNEL_MPART_TRIM)
#define CONFIG_HAVE_KERNEL_MPART_TRIM
#elif (-CONFIG_HAVE_KERNEL_MPART_TRIM - 1) == -1
#undef CONFIG_HAVE_KERNEL_MPART_TRIM
#define CONFIG_NO_KERNEL_MPART_TRIM
#endif /* ... */
/*[[[end]]]*/



/* Alongside mpart_merge(), there should also be a function `mpart_trim()'
 * that will look at what's actually being mapped about the part, and will
 * try to trim/split the part, such  that unmapped portions are no  longer
 * being represented.
 *
 * Without special handling, the following will actually keep backing memory allocated:
 *
 * >> mmap(0x01234000, PAGESIZE, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_ANON, -1, 0);
 * >> mmap(0x01235000, PAGESIZE, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_ANON, -1, 0); // Automatically merged
 * >> mmap(0x01236000, PAGESIZE, PROT_READ | PROT_WRITE, MAP_FIXED | MAP_ANON, -1, 0); // Automatically merged
 * >> munmap(0x01235000, PAGESIZE); // Automatically cases a split, but only within mem-nodes (mpart would be unaffected)
 *
 * The idea here is that the `munmap()' calls `mpart_trim()', which will
 * (asynchronously, and only in case the part is anonymous) look at  the
 * part's set of mapped nodes and figure out which parts of the part (if
 * any)  are actually in use. Any part that's not in use from the part's
 * edges  is then simply  trimmed, and unused holes  from the middle are
 * handled by trying to split the part, such that each consecutive chunk
 * of used memory has its own mpart, and thus doesn't require the entire
 * region to be kept in-core all at once. */

DECL_BEGIN

#ifdef CONFIG_HAVE_KERNEL_MPART_TRIM

/* Check if `self' may be trimmed.
 * This macro may only be called while holding a lock to  `self',
 * and if it returns `false', then trimming of `self' is a no-op.
 *
 * Currently, we disable trimming for parts that have the NOSPLIT
 * flag set. - You could argue that we'd merely not be allowed to
 * punch  holes into parts with the NOSPLIT flag (i.e. split them
 * for  the purpose of then truncating one of them), however even
 * the act of trimming leading/trailing data from a mem-part kind
 * of behaves like a split if you think about it. Read:  trimming
 * is like _splitting_ off a  portion that's not needed,  meaning
 * that the NOSPLIT  flag could also  be interpreted to  prohibit
 * the part's from being lowered,  whilst the NOMERGE flag  could
 * be interpreted that the part's size is prohibited from rising.
 * As such, only check NOSPLIT, because our only job is to  lower
 * the  size of a mem-part if it is found that parts if it aren't
 * actually in-use!
 *
 * NOTE: This macro should be used independently of `mpart_isanon()'! */
#define mpart_maytrim(self) \
	(!((self)->mp_flags & MPART_F_NOSPLIT))

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

static_assert(offsetof(struct mpart, _mp_trmlop_mp.olo_func) == offsetof(struct mpart, _mp_trmlop_mm.olo_func) &&
              offsetafter(struct mpart, _mp_trmlop_mp.olo_func) == offsetafter(struct mpart, _mp_trmlop_mm.olo_func) &&
              offsetof(struct mpart, _mp_trmlop_mp.olo_func) == offsetof(struct mpart, _mp_trmplop_mm.oplo_func) &&
              offsetafter(struct mpart, _mp_trmlop_mp.olo_func) == offsetafter(struct mpart, _mp_trmplop_mm.oplo_func) &&
              offsetof(struct mpart, _mp_trmlop_mp.olo_func) == offsetof(struct mpart, _mp_trmplop_mp.oplo_func) &&
              offsetafter(struct mpart, _mp_trmlop_mp.olo_func) == offsetafter(struct mpart, _mp_trmplop_mp.oplo_func) &&
              offsetof(struct mpart, _mp_trmlop_mp.olo_func) == offsetof(struct mpart, mp_filent.rb_rhs) &&
              offsetafter(struct mpart, _mp_trmlop_mp.olo_func) == offsetafter(struct mpart, mp_filent.rb_rhs),
              "This is assumed by `_mpart_init_asanon()', which fills in `rb_rhs' as NULL "
              "when called, which in turn must cause the `olo_func' of the lockops used to "
              "be initialized to `NULL' as well.\n"
              "Calls to `mpart_trim()' will then do an atomic_cmpxch on `olo_func' to start "
              "an async trim operation of the mem-part!");


/************************************************************************/
/* Cleanup helper functions                                             */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mchunk_freemem)(struct mchunk *__restrict self) {
	page_free(self->mc_start, self->mc_size);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mchunk_freeswp)(struct mchunk *__restrict self) {
	swap_free(self->mc_start, self->mc_size);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mchunkvec_freemem)(struct mchunk *__restrict vec, size_t count,
                                 struct ccinfo *info) {
	size_t i;
	if (info) {
		for (i = 0; i < count; ++i)
			ccinfo_account_physpages(info, vec[i].mc_size);
	}
	for (i = 0; i < count; ++i)
		mchunk_freemem(&vec[i]);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mchunkvec_freeswp)(struct mchunk *__restrict vec, size_t count,
                                 struct ccinfo *info) {
	size_t i;
	if (info) {
		for (i = 0; i < count; ++i)
			ccinfo_account_swappages(info, vec[i].mc_size);
	}
	for (i = 0; i < count; ++i)
		mchunk_freeswp(&vec[i]);
}
/************************************************************************/





PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mnode_list_sort_item_by_partoff)(struct mnode_list *__restrict list,
                                               struct mnode *__restrict self) {
	struct mnode *neighbor;
	if (self != LIST_FIRST(list)) {
		neighbor = LIST_PREV_UNSAFE(self, mn_link);
		if (self->mn_partoff < neighbor->mn_partoff) {
			do {
				/* Re-insert `self' before `neighbor' */
				LIST_REMOVE(self, mn_link);
				LIST_INSERT_BEFORE(neighbor, self, mn_link);
			} while (self != LIST_FIRST(list) &&
			         (neighbor = LIST_PREV_UNSAFE(self, mn_link),
			          self->mn_partoff < neighbor->mn_partoff));
			return;
		}
	}
	if ((neighbor = LIST_NEXT(self, mn_link)) != NULL &&
	    (self->mn_partoff > neighbor->mn_partoff)) {
		do {
			/* Re-insert `self' after `neighbor' */
			LIST_REMOVE(self, mn_link);
			LIST_INSERT_AFTER(neighbor, self, mn_link);
			neighbor = LIST_NEXT(self, mn_link);
		} while (neighbor != NULL &&
		         self->mn_partoff > neighbor->mn_partoff);
	}
}

/* Sort the given mem-node list by each node's `mn_partoff'.  This
 * isn't the most efficient function, mainly because it's meant to
 * sort a linked list, so it runs in O(n+(n-1)+(n-2)+...+2+1) */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mnode_list_sort_by_partoff)(struct mnode_list *__restrict self) {
	struct mnode *iter, *next;
	for (iter = LIST_FIRST(self); iter; iter = next) {
		next = LIST_NEXT(iter, mn_link);
		mnode_list_sort_item_by_partoff(self, iter);
	}
}

struct mpart_node_iterator {
	struct mnode *pni_cnext; /* [0..1] Next copy-node */
	struct mnode *pni_snext; /* [0..1] Next share-node */
};

#define mpart_node_iterator_init(self, part)           \
	((self)->pni_cnext = LIST_FIRST(&(part)->mp_copy), \
	 (self)->pni_snext = LIST_FIRST(&(part)->mp_share))

/* Enumerate the next mem-node (return `NULL' when no more nodes remain) */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) struct mnode *
NOTHROW(FCALL mpart_node_iterator_next)(struct mpart_node_iterator *__restrict self) {
	struct mnode *result;
	do {
		result = self->pni_cnext;
		if (result == NULL) {
			/* Enumerate the rest from the share-list. */
			result = self->pni_snext;
			if (result == NULL)
				break; /* Exhausted */
			self->pni_snext = LIST_NEXT(result, mn_link);
		} else if (self->pni_snext != NULL &&
		           self->pni_snext->mn_partoff < result->mn_partoff) {
			/* The next share-node comes before the next copy-node. */
			result          = self->pni_snext;
			self->pni_snext = LIST_NEXT(result, mn_link);
		} else {
			self->pni_cnext = LIST_NEXT(result, mn_link);
		}
		/* Skip nodes from dead mmans. */
	} while (unlikely(wasdestroyed(result->mn_mman)) ||
	         (result->mn_flags & MNODE_F_UNMAPPED));
	return result;
}


/* Ensure that all pages from an MNODE_F_MHINT-node have been loaded.
 * Once this  has  been  ensured,  clear  the  `MNODE_F_MHINT'  flag! */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mnode_load_mhint)(struct mnode *__restrict self) {
	assert(self->mn_mman == &mman_kernel);
	PAGEDIR_PAGEALIGNED byte_t *iter, *end;
	iter = (byte_t *)mnode_getaddr(self);
	end  = (byte_t *)mnode_getendaddr(self);
	assert(iter < end);
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
	if (self->mn_part->mp_file == &mfile_dbgheap) {
		preemption_flag_t was;
		/* Super-ugly, hacky work-around because the heap system can't
		 * be made compatible  with lockops without  a full  re-write.
		 *
		 * s.a.: `heap_unmap_kram()' */
		heap_validate_all();
		preemption_pushoff(&was);
		atomic_or(&THIS_TASK->t_flags, _TASK_FDBGHEAPDMEM);
		do {
			__asm__ __volatile__("" : : "r" (*iter));
			iter += PAGESIZE;
		} while (iter < end);
		preemption_pop(&was);
		atomic_and(&THIS_TASK->t_flags, ~_TASK_FDBGHEAPDMEM);
		heap_validate_all();
	} else
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
	{
		do {
			__asm__ __volatile__("" : : "r" (*iter));
			iter += PAGESIZE;
		} while (iter < end);
	}

	/* Make sure that any other CPU is still initializing hinted pages,
	 * which may  overlap with  the address  range we've  just  loaded. */
	mman_kernel_hintinit_inuse_waitfor();

	atomic_and(&self->mn_flags, ~MNODE_F_MHINT);
}

typedef NOBLOCK void
NOTHROW_T(FCALL *freefun_t)(physpage_t base, physpagecnt_t num_pages, gfp_t flags);

INTERN NOBLOCK void /* from "kram-unmap.c" */
NOTHROW(FCALL mpart_freefun_noop)(physpage_t UNUSED(base), physpagecnt_t UNUSED(num_pages), gfp_t UNUSED(flags));
INTDEF ATTR_PURE ATTR_RETNONNULL WUNUSED NONNULL((1)) freefun_t /* from "kram-unmap.c" */
NOTHROW(FCALL mpart_getfreefun)(struct mpart const *__restrict self);

/* Assert that the scatter enable/disable macros work. */
static_assert(MPART_ST_WTSC(MPART_ST_MEM) == MPART_ST_MEM_SC);
static_assert(MPART_ST_WTSC(MPART_ST_SWP) == MPART_ST_SWP_SC);
static_assert(MPART_ST_NOSC(MPART_ST_MEM_SC) == MPART_ST_MEM);
static_assert(MPART_ST_NOSC(MPART_ST_SWP_SC) == MPART_ST_SWP);


PRIVATE NOBLOCK NONNULL((1, 3)) void
NOTHROW(FCALL bitmovedown)(mpart_blkst_word_t *dst_bitset, size_t dst_index,
                           mpart_blkst_word_t const *src_bitset, size_t src_index,
                           size_t num_bits) {
#define BITSET_INDEX(index) ((index) / BITSOF(mpart_blkst_word_t))
#define BITSET_SHIFT(index) ((index) % BITSOF(mpart_blkst_word_t))
#define GETBIT(index)       ((src_bitset[BITSET_INDEX(index)] >> BITSET_SHIFT(index)) & 1)
#define SETBIT_OFF(index)   ((dst_bitset[BITSET_INDEX(index)] &= ~((mpart_blkst_word_t)1 << BITSET_SHIFT(index))))
#define SETBIT_ON(index)    ((dst_bitset[BITSET_INDEX(index)] |= ((mpart_blkst_word_t)1 << BITSET_SHIFT(index))))
	while (num_bits) {
		--num_bits;
		if (GETBIT(src_index)) {
			SETBIT_ON(dst_index);
		} else {
			SETBIT_OFF(dst_index);
		}
		++dst_index;
		++src_index;
	}
#undef SETBIT_ON
#undef SETBIT_OFF
#undef GETBIT
#undef BITSET_SHIFT
#undef BITSET_INDEX
}


/* Load all mem-nodes with the `MHINT' flag. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_load_all_mhint_nodes)(struct mpart *__restrict self) {
	unsigned int i;
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		struct mnode *node;
		LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link) {
			if unlikely(wasdestroyed(node->mn_mman))
				continue;
			assert(node->mn_part == self || (node->mn_flags & MNODE_F_UNMAPPED));
			if unlikely(node->mn_flags & MNODE_F_MHINT) {
				assert(!(node->mn_flags & MNODE_F_UNMAPPED));
				mnode_load_mhint(node);
			}
		}
	}
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mfutex_tree_reinsert_or_detach_lstrip)(struct mfutex **__restrict p_tree,
                                                     struct mfutex *__restrict self,
                                                     PAGEDIR_PAGEALIGNED mpart_reladdr_t num_bytes) {
	struct mfutex *lhs, *rhs;
again:
	lhs = self->mfu_mtaent.rb_lhs;
	rhs = self->mfu_mtaent.rb_rhs;
	if (tryincref(self)) {
		if (self->mfu_addr >= num_bytes) {
			/* Re-insert into the new tree with the new offset. */
			self->mfu_addr -= num_bytes;
			mfutex_tree_insert(p_tree, self);
		} else {
			/* Get rid of this futex. */
			DBG_memset(&self->mfu_mtaent, 0xcc, sizeof(self->mfu_mtaent));
			awref_clear(&self->mfu_part);
			weakdecref_nokill(self);
		}
		decref_unlikely(self);
	} else {
		DBG_memset(&self->mfu_mtaent, 0xcc, sizeof(self->mfu_mtaent));
		awref_clear(&self->mfu_part);
		weakdecref_unlikely(self);
	}
	if (lhs) {
		if (rhs)
			mfutex_tree_reinsert_or_detach_lstrip(p_tree, rhs, num_bytes);
		self = lhs;
		goto again;
	}
	if (rhs) {
		self = rhs;
		goto again;
	}
}


/* Strip the first `num_bytes' bytes from the block-status bitset of `self'. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_lstrip_blkst)(struct mpart *__restrict self,
                                  PAGEDIR_PAGEALIGNED mpart_reladdr_t num_bytes) {
	size_t num_blkbits;
	num_blkbits = (num_bytes >> self->mp_file->mf_blockshift) * MPART_BLOCK_STBITS;
	if (self->mp_flags & MPART_F_BLKST_INL) {
		self->mp_blkst_inl >>= num_blkbits;
	} else {
		mpart_blkst_word_t *bitset;
		if ((bitset = self->mp_blkst_ptr) != NULL) {
			size_t new_size, new_blks, new_wrds;
			new_size = mpart_getsize(self) - num_bytes;
			new_blks = new_size >> self->mp_file->mf_blockshift;
			new_wrds = CEILDIV(new_blks, MPART_BLKST_BLOCKS_PER_WORD);
			/* Move down bits. */
			bitmovedown(bitset, 0,
			            bitset, num_blkbits,
			            new_blks * MPART_BLOCK_STBITS);
			/* Try to truncate the bitset vector. */
			bitset = (mpart_blkst_word_t *)krealloc_nx(bitset, new_wrds * sizeof(mpart_blkst_word_t),
			                                           GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
			if likely(bitset)
				self->mp_blkst_ptr = bitset;
		}
	}
}

/* Strip the first `pages' pages from the mem-scatter vector of `self' */
PRIVATE NOBLOCK NONNULL((1, 3)) void
NOTHROW(FCALL mpart_lstrip_memsc)(struct mpart *__restrict self,
                                  physpagecnt_t pages, freefun_t freefun) {
	struct mchunk *vec;
	/* Trim leading pages from the scatter vector. */
	vec = self->mp_mem_sc.ms_v;
	for (;;) {
		physpagecnt_t count;
		assert(self->mp_mem_sc.ms_c);
		count = vec[0].mc_size;
		if (pages >= count) {
			(*freefun)(vec[0].mc_start, count, 0);
			--self->mp_mem_sc.ms_c;
			memmovedown(&vec[0], &vec[1],
			            self->mp_mem_sc.ms_c,
			            sizeof(struct mchunk));
			pages -= count;
		} else {
			(*freefun)(vec[0].mc_start, pages, 0);
			vec[0].mc_start += pages;
			vec[0].mc_size -= pages;
			break;
		}
	}
	if (self->mp_mem_sc.ms_c == 1) {
		self->mp_mem   = vec[0];
		self->mp_state = MPART_ST_NOSC(self->mp_state);
		kfree(vec);
	} else {
		/* Try to truncate the vector. */
		vec = (struct mchunk *)krealloc_nx(vec,
		                                   self->mp_mem_sc.ms_c *
		                                   sizeof(struct mchunk),
		                                   GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
		if likely(vec)
			self->mp_mem_sc.ms_v = vec;
	}
}


/* Subtract `num_bytes' from the `mn_partoff' field of every node from `self'.
 * The caller must ensure that all nodes of `self' have offsets >= `num_bytes' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_lstrip_nodes)(struct mpart *__restrict self,
                                  PAGEDIR_PAGEALIGNED mpart_reladdr_t num_bytes) {
	unsigned int i;
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		struct mnode *node;
		LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link) {
			if unlikely(wasdestroyed(node->mn_mman))
				continue;
			if unlikely(node->mn_flags & MNODE_F_UNMAPPED)
				continue; /* Skip unmapped nodes... */
			assert(node->mn_part == self); /* Only assert this when `MNODE_F_UNMAPPED' isn't set! */
			assert(node->mn_partoff >= num_bytes);
			/* Deal with MHINT'd nodes! */
			if unlikely(node->mn_flags & MNODE_F_MHINT)
				mnode_load_mhint(node);
			node->mn_partoff -= num_bytes;
		}
	}
}

/* Strip the first `num_bytes' bytes from the given mem-part. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_lstrip)(struct mpart *__restrict self,
                            PAGEDIR_PAGEALIGNED mpart_reladdr_t num_bytes) {
	physpagecnt_t pages;
	freefun_t freefun;

	/* Detach or relocate bound objects (futexes) */
	{
		struct mpartmeta *meta;
		if ((meta = self->mp_meta) != NULL && meta->mpm_ftx) {
			struct mfutex *tree;
			tree          = meta->mpm_ftx;
			meta->mpm_ftx = NULL;
			mfutex_tree_reinsert_or_detach_lstrip(&meta->mpm_ftx, tree, num_bytes);
		}
	}

	/* Update the offsets within associated mem-nodes. */
	mpart_lstrip_nodes(self, num_bytes);

	/* Update the part's backing data. */
	pages   = num_bytes >> PAGESHIFT;
	freefun = mpart_getfreefun(self);
	switch (self->mp_state) {

	case MPART_ST_SWP:
		pages = mpart_page2swap(self, pages);
		ATTR_FALLTHROUGH
	case MPART_ST_MEM:
		/* Free leading pages. */
		assert(self->mp_mem.mc_size >= pages);
		(*freefun)(self->mp_swp.mc_start, pages, 0);
		self->mp_mem.mc_start += pages;
		self->mp_mem.mc_size -= pages;
		break;

	case MPART_ST_SWP_SC:
		pages = mpart_page2swap(self, pages);
		ATTR_FALLTHROUGH
	case MPART_ST_MEM_SC:
		mpart_lstrip_memsc(self, pages, freefun);
		break;

	default:
		break;
	}

	/* Update the block-status bitset to strip leading bytes. */
	mpart_lstrip_blkst(self, num_bytes);

	/* Update the part's actual minaddr field. */
	self->mp_minaddr += num_bytes;
}


/* Strip the last `num_bytes' bytes from the given mem-part. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_rstrip)(struct mpart *__restrict self,
                            PAGEDIR_PAGEALIGNED mpart_reladdr_t num_bytes) {
	physpagecnt_t pages;
	freefun_t freefun;
	mpart_reladdr_t oldsize, newsize;
	oldsize = mpart_getsize(self);
	newsize = oldsize - num_bytes;

	/* Detach bound objects (futexes) */
	{
		struct mpartmeta *meta;
		if ((meta = self->mp_meta) != NULL) {
			struct mfutex *ftx;
			while ((ftx = mpartmeta_ftx_rremove(meta, newsize, oldsize - 1)) != NULL) {
				awref_clear(&ftx->mfu_part);
				weakdecref_unlikely(ftx);
			}
		}
	}

	/* Update the part's backing data. */
	pages   = num_bytes >> PAGESHIFT;
	freefun = mpart_getfreefun(self);
	switch (self->mp_state) {

	case MPART_ST_SWP:
		pages = mpart_page2swap(self, pages);
		ATTR_FALLTHROUGH
	case MPART_ST_MEM:
		/* Free leading pages. */
		assert(self->mp_mem.mc_size >= pages);
		(*freefun)(self->mp_swp.mc_start +
		           self->mp_swp.mc_size - pages,
		           pages, 0);
		self->mp_mem.mc_size -= pages;
		break;

	case MPART_ST_SWP_SC:
		pages = mpart_page2swap(self, pages);
		ATTR_FALLTHROUGH
	case MPART_ST_MEM_SC: {
		struct mchunk *vec;
		/* Trim leading pages from the scatter vector. */
		vec = self->mp_mem_sc.ms_v;
		for (;;) {
			physpage_t base;
			physpagecnt_t count;
			assert(self->mp_mem_sc.ms_c);
			base  = vec[self->mp_mem_sc.ms_c - 1].mc_start;
			count = vec[self->mp_mem_sc.ms_c - 1].mc_size;
			if (pages >= count) {
				(*freefun)(base, count, 0);
				--self->mp_mem_sc.ms_c;
				pages -= count;
			} else {
				(*freefun)(base + count - pages, pages, 0);
				vec[self->mp_mem_sc.ms_c - 1].mc_size -= pages;
				break;
			}
		}
		if (self->mp_mem_sc.ms_c == 1) {
			self->mp_mem   = vec[0];
			self->mp_state = MPART_ST_NOSC(self->mp_state);
			kfree(vec);
		} else {
			/* In order to be allowed to change the base-address  of
			 * the mem-chunk-vector, we have to make sure that there
			 * aren't any MHINT-nodes  out there, and  if there  are
			 * any, then we must first initialize them! */
			mpart_load_all_mhint_nodes(self);

			/* Try to truncate the vector. */
			vec = (struct mchunk *)krealloc_nx(vec,
			                                   self->mp_mem_sc.ms_c *
			                                   sizeof(struct mchunk),
			                                   GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
			if likely(vec)
				self->mp_mem_sc.ms_v = vec;
		}
	}	break;

	default:
		break;
	}

	/* Update the block-status bitset to strip trailing entries. */
	if (!(self->mp_flags & MPART_F_BLKST_INL) && self->mp_blkst_ptr) {
		mpart_blkst_word_t *bitset;
		size_t new_blcks, new_words;
		new_blcks = newsize >> self->mp_file->mf_blockshift;
		new_words = CEILDIV(new_blcks, MPART_BLKST_BLOCKS_PER_WORD);
		/* Like above, we can only change the base-address of the block-
		 * status-bitset after we've made sure  that there are no  MHINT
		 * nodes! */
		mpart_load_all_mhint_nodes(self);
		bitset = (mpart_blkst_word_t *)krealloc_nx(self->mp_blkst_ptr,
		                                           new_words * sizeof(mpart_blkst_word_t),
		                                           GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT);
		if likely(bitset)
			self->mp_blkst_ptr = bitset;
	}

	/* Update the part's actual maxaddr field. */
	self->mp_maxaddr -= num_bytes;
}



/* Return codes for `mpart_trim_with_all_locks()' */
#define MPART_TRIM_STATUS_SUCCESS 0 /* Success */
#define MPART_TRIM_STATUS_ASYNC   1 /* Trimming will complete asynchronously */
#define MPART_TRIM_STATUS_NOMEM   2 /* Insufficient memory (enqueue the part as a lockop into `mman_kernel') */

#define async_kmalloc(num_bytes) \
	kmalloc_nx(num_bytes, GFP_ATOMIC | GFP_LOCKED | GFP_PREFLT)

/* NOTE: This function inherits a reference to `container_of(_lop, struct mpart, _mp_trmlop_mm)' */
PRIVATE NOBLOCK NONNULL((1)) Tobpostlockop(mman) *
NOTHROW(FCALL mpart_trim_mmlop)(Toblockop(mman) *__restrict _lop,
                                struct mman *__restrict UNUSED(mm));

/* Like `mpart_mappedby_mman()', but stop checking nodes when `stop'
 * is reached. Additionally, `stop' isn't considered to be apart  of
 * the list of nodes to test for mapping `mm' */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1, 3)) bool
NOTHROW(FCALL mpart_mappedby_mman_before)(struct mpart const *__restrict self,
                                          struct mnode const *stop,
                                          struct mman const *__restrict mm);

/* Dynamically allocate a new mem-part.
 * Also: If one of the  nodes that are mapping  `self'
 *       belongs to `mman_kernel', assume that the caller is holding
 *       a lock to  `mman_kernel', and attempt  to allocate the  new
 *       mem-part via  `mcoreheap_alloc_locked_nx()'  without  first
 *       acquiring a lock to `mman_kernel' by ourselves.
 * NOTE: All fields of the returned mem-part are undefined, with the
 *       exception  of `mp_flags', which is either set to `0' if the
 *       part was allocated  via `kmalloc()', or  `MPART_F_COREPART'
 *       if `mcoreheap_alloc_locked_nx()' was used.
 * @return: * : One of `MPART_TRIM_STATUS_*' */
PRIVATE NOBLOCK ATTR_MALLOC NONNULL((1, 2)) unsigned int
NOTHROW(FCALL async_alloc_mpart)(struct mpart **__restrict p_newpart,
                                 struct mpart *__restrict self) {
	struct mpart *newpart;
	/* First attempt: directly try to kmalloc() the new part. */
	newpart = (struct mpart *)async_kmalloc(sizeof(struct mpart));
	if (newpart) {
		newpart->mp_xflags = MPART_XF_NORMAL;
		newpart->mp_flags  = MPART_F_NORMAL;
		*p_newpart         = newpart;
		return MPART_TRIM_STATUS_SUCCESS;
	}

	/* Try to get a lock to the kernel mman, and
	 * make use of `mcoreheap_alloc_locked_nx()' */
	if (mman_lock_tryacquire(&mman_kernel)) {
		union mcorepart *cp;
		cp = mcoreheap_alloc_locked_nx();
		mman_lock_release(&mman_kernel);
		if (!cp)
			return MPART_TRIM_STATUS_NOMEM;
		cp->mcp_part.mp_xflags = MPART_XF_NORMAL;
		cp->mcp_part.mp_flags  = MPART_F_COREPART;
		*p_newpart             = &cp->mcp_part;
		return MPART_TRIM_STATUS_SUCCESS;
	}

	/* Check if one of our callers is already holding a lock
	 * to the kernel mman, because  if they are, then  we're
	 * allowed to call `mcoreheap_alloc_locked_nx()' without
	 * having to acquire another lock ourselves! */
	if (mpart_mappedby_mman_before(self, NULL, &mman_kernel)) {
		union mcorepart *cp;
		cp = mcoreheap_alloc_locked_nx();
		if (!cp)
			return MPART_TRIM_STATUS_NOMEM;
		cp->mcp_part.mp_xflags = MPART_XF_NORMAL;
		cp->mcp_part.mp_flags  = MPART_F_COREPART;
		*p_newpart             = &cp->mcp_part;
		return MPART_TRIM_STATUS_SUCCESS;
	}

	/* We'd need a lock to the kernel mman to proceed. - As
	 * such, enqueue `self' to wait for said lock to become
	 * available. */
	atomic_write(&self->_mp_trmlop_mm.olo_func, &mpart_trim_mmlop);
	incref(self); /* Inherited by `mpart_trim_mmlop()' */
	SLIST_ATOMIC_INSERT(&mman_kernel_lockops, &self->_mp_trmlop_mm, olo_link);
	_mman_lockops_reap(&mman_kernel);
	return MPART_TRIM_STATUS_ASYNC;
}


PRIVATE NOBLOCK NONNULL((1, 2, 3, 4)) void
NOTHROW(FCALL mfutex_tree_reinsert_or_transfer_lstrip)(struct mfutex **__restrict p_lotree,
                                                       struct mfutex **__restrict p_hitree,
                                                       struct mfutex *__restrict self,
                                                       struct mpart *__restrict lopart,
                                                       PAGEDIR_PAGEALIGNED mpart_reladdr_t addr) {
	struct mfutex *lhs, *rhs;
again:
	lhs = self->mfu_mtaent.rb_lhs;
	rhs = self->mfu_mtaent.rb_rhs;
	if (tryincref(self)) {
		if (self->mfu_addr >= addr) {
			/* Re-insert into the new tree with the new offset. */
			self->mfu_addr -= addr;
			mfutex_tree_insert(p_hitree, self);
		} else {
			/* Insert into the low-part's tree. */
			awref_set(&self->mfu_part, lopart);
			mfutex_tree_insert(p_lotree, self);
		}
		decref_unlikely(self);
	} else {
		DBG_memset(&self->mfu_mtaent, 0xcc, sizeof(self->mfu_mtaent));
		awref_clear(&self->mfu_part);
		weakdecref_unlikely(self);
	}
	if (lhs) {
		if (rhs) {
			mfutex_tree_reinsert_or_transfer_lstrip(p_lotree, p_hitree, rhs,
			                                        lopart, addr);
		}
		self = lhs;
		goto again;
	}
	if (rhs) {
		self = rhs;
		goto again;
	}
}


/* Check if `self' contains any MLOCK-nodes. */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL mpart_has_mlock_nodes)(struct mpart const *__restrict self) {
	unsigned int i;
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		struct mnode *node;
		LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link) {
			if (node->mn_flags & MNODE_F_MLOCK)
				return true;
		}
	}
	return false;
}


/* Asynchronously split `self', such that a new part is created
 * that  then encompasses all of the data leading up to `addr'.
 * The caller must  ensure that `addr'  doesn't point into  the
 * middle  of one of  the part's mem-node  mappings, as well as
 * that `addr' is properly aligned by the part's  file-specific
 * alignment `self->mp_file->mf_part_amask'.
 * @return: * : One of `MPART_TRIM_STATUS_*' */
PRIVATE NOBLOCK NONNULL((1)) unsigned int
NOTHROW(FCALL mpart_async_split_before)(struct mpart *__restrict self,
                                        PAGEDIR_PAGEALIGNED mpart_reladdr_t addr) {
	unsigned int status;
	struct mpart *lopart, *hipart;
	physpagecnt_t pages;
	assert(!(addr & self->mp_file->mf_part_amask));

	hipart = self;
	status = async_alloc_mpart(&lopart, self);
	if unlikely(status != MPART_TRIM_STATUS_SUCCESS)
		return status;

	/* Allocate / set-up the block-status bitset of `lopart' */
	if (hipart->mp_flags & MPART_F_BLKST_INL) {
		lopart->mp_flags |= MPART_F_BLKST_INL;
		lopart->mp_blkst_inl = hipart->mp_blkst_inl;
	} else if (hipart->mp_blkst_ptr == NULL) {
		lopart->mp_blkst_ptr = NULL;
	} else {
		size_t loblocks;
		mpart_blkst_word_t *hipart_bitset;
		loblocks      = addr >> hipart->mp_file->mf_blockshift;
		hipart_bitset = hipart->mp_blkst_ptr;
		if (loblocks <= MPART_BLKST_BLOCKS_PER_WORD) {
			lopart->mp_flags |= MPART_F_BLKST_INL;
			lopart->mp_blkst_inl = hipart_bitset[0];
		} else {
			mpart_blkst_word_t *lopart_bitset;
			size_t lowords;
			lowords       = CEILDIV(loblocks, MPART_BLKST_BLOCKS_PER_WORD);
			lopart_bitset = (mpart_blkst_word_t *)async_kmalloc(lowords * sizeof(mpart_blkst_word_t));
			if (!lopart_bitset)
				goto err_nomem_lopart;
			memcpy(lopart_bitset, hipart_bitset,
			       lowords, sizeof(mpart_blkst_word_t));
			lopart->mp_blkst_ptr = lopart_bitset; /* Inherit! */
		}
	}

	/* Initialize state-specific data for `lopart' */
	lopart->mp_state = hipart->mp_state;
	pages            = addr >> PAGESHIFT;
	switch (lopart->mp_state) {

	case MPART_ST_SWP:
		pages = mpart_page2swap(hipart, pages);
		ATTR_FALLTHROUGH
	case MPART_ST_MEM:
		lopart->mp_mem.mc_start = hipart->mp_mem.mc_start;
		lopart->mp_mem.mc_size  = pages;
		break;

	case MPART_ST_SWP_SC:
		pages = mpart_page2swap(hipart, pages);
		ATTR_FALLTHROUGH
	case MPART_ST_MEM_SC: {
		/* Figure out how to split the scatter-vector. */
		physpagecnt_t missing;
		size_t index;
		missing = pages;
		index   = 0;
		for (;;) {
			physpagecnt_t count;
			assert(index < hipart->mp_mem_sc.ms_c);
			count = hipart->mp_mem_sc.ms_v[index].mc_size;
			if (count >= missing)
				break; /* Split at `index+missing' */
			missing -= count;
			++index;
		}
		if (index == 0) {
			/* Simple case: don't need a scatter-list for `lopart'! */
			assert(missing == pages);
			lopart->mp_state        = MPART_ST_NOSC(hipart->mp_state);
			lopart->mp_mem.mc_start = hipart->mp_mem_sc.ms_v[0].mc_start;
			lopart->mp_mem.mc_size  = pages;
		} else {
			/* Complicated case: Must allocate a `index+1'-long vector. */
			struct mchunk *lovec;
			lovec = (struct mchunk *)async_kmalloc((index + 1) * sizeof(struct mchunk));
			if unlikely(!lovec)
				goto err_nomem_lopart_bitset;

			/* Fill in the mem-chunk-vector of `lopart'. */
			memcpy(lovec, hipart->mp_mem_sc.ms_v, index, sizeof(struct mchunk));
			lovec[index].mc_start = hipart->mp_mem_sc.ms_v[index].mc_start;
			lovec[index].mc_size  = missing;

			/* Write-back the newly allocated vector into `lopart' */
			lopart->mp_mem_sc.ms_c = index + 1;
			lopart->mp_mem_sc.ms_v = lovec;
		}
	}	break;

	default:
		break;
	}

	/* If necessary, allocate a meta-data controller for `lopart' */
	lopart->mp_meta = NULL;
	if (hipart->mp_meta &&
	    (mpartmeta_ftx_rlocate(hipart->mp_meta, 0, addr - 1) != NULL
#ifdef ARCH_HAVE_RTM
	     || hipart->mp_meta->mpm_rtm_vers != 0
#endif /* ARCH_HAVE_RTM */
	     )) {
		/* Allocate a meta-controller for `lopart' */
		struct mpartmeta *meta;
		meta = (struct mpartmeta *)async_kmalloc(sizeof(struct mpartmeta));
		if unlikely(!meta)
			goto err_nomem_lopart_bitset_scvec;
		lopart->mp_meta = meta;
	}

	/* ===== Point of no return */

	/* Fill in the misc. remaining fields of `lopart' */
	lopart->mp_flags |= MPART_F_LOCKBIT;
	lopart->mp_flags |= (hipart->mp_flags & (MPART_F_MAYBE_BLK_INIT |
	                                         MPART_F_GLOBAL_REF |
	                                         MPART_F_NOFREE |
	                                         /*MPART_F_NOSPLIT |*/ /* Mustn't be set! */
	                                         MPART_F_NOMERGE |
	                                         MPART_F_MLOCK_FROZEN |
	                                         MPART_F_MLOCK));
	lopart->mp_file = incref(hipart->mp_file);
	SLIST_INIT(&lopart->mp_lockops);
	lopart->mp_minaddr = hipart->mp_minaddr;
	lopart->mp_maxaddr = hipart->mp_minaddr + addr - 1;
	DBG_memset(&lopart->mp_changed, 0xcc, sizeof(lopart->mp_changed));
	LIST_ENTRY_UNBOUND_INIT(&lopart->mp_allparts); /* Overwritten below if necessary... */
	_mpart_init_asanon(lopart);

	/* Transfer mem-nodes from `hipart' to `lopart'. */
	{
		unsigned int i;
		lopart->mp_refcnt = 0;
		for (i = 0; i < lengthof(hipart->_mp_nodlsts); ++i) {
			struct mnode *node;
			LIST_INIT(&lopart->_mp_nodlsts[i]);
again_enum_hipart_nodlst:
			LIST_FOREACH (node, &hipart->_mp_nodlsts[i], mn_link) {
				if unlikely(wasdestroyed(node->mn_mman))
					continue; /* Skip nodes of dead mmans... */
				if unlikely(node->mn_flags & MNODE_F_UNMAPPED)
					continue; /* Skip unmapped nodes... */
				assert(node->mn_part == hipart); /* Only assert this when `MNODE_F_UNMAPPED' isn't set! */
				if (node->mn_partoff >= addr)
					break; /* Keep all nodes starting w/ this one! */

				assertf(!(addr >= mnode_getpartminaddr(node) &&
				          addr <= mnode_getpartmaxaddr(node)),
				        "Node is mapped directly in the middle of the split.\n"
				        "This shouldn't be possible since our caller only ever "
				        "creates splits such that they appear within entirely "
				        "unmapped gaps!\n"
				        "Node address range: %p-%p\n"
				        "Node part range:    %#" PRIxSIZ "-%#" PRIxSIZ "\n"
				        "addr:               %#" PRIxSIZ "\n",
				        mnode_getminaddr(node), mnode_getmaxaddr(node),
				        mnode_getpartminaddr(node), mnode_getpartmaxaddr(node),
				        addr);

				if unlikely(node->mn_flags & MNODE_F_MHINT)
					mnode_load_mhint(node);

				/* Update the part-pointer of this node to reference `lopart' */
				decref_nokill(hipart);
				node->mn_part = lopart;
				++lopart->mp_refcnt;

				/* Re-insert this node into `lopart'
				 * NOTE: It doesn't  matter  that  this  cases  the
				 *       node order to be inverted within `lopart'. */
				LIST_REMOVE(node, mn_link);
				LIST_INSERT_HEAD(&lopart->_mp_nodlsts[i], node, mn_link);
				goto again_enum_hipart_nodlst;
			}
		}
		assertf(lopart->mp_refcnt > 0,
		        "If this was the case, then our caller shouldn't "
		        "have tried to split the part, but rather lstrip it");
	}

	/* Add another reference that will be dropped once we've
	 * release all of our locks to `lopart' (it must be kept
	 * up  until that point in order to ensure that the part
	 * isn't destroyed before then due to other threads) */
	++lopart->mp_refcnt;

	/* Add yet another reference to `lopart' if necessary. */
	if (lopart->mp_flags & MPART_F_GLOBAL_REF)
		++lopart->mp_refcnt;

	/* Check  which of the  2 parts still  contains MLOCK-nodes, and clear
	 * the MLOCK flag for exactly that part (if any) which doesn't contain
	 * any MLOCK-nodes. */
	if ((lopart->mp_flags & (MPART_F_MLOCK | MPART_F_MLOCK_FROZEN)) == MPART_F_MLOCK) {
		assert((hipart->mp_flags & (MPART_F_MLOCK | MPART_F_MLOCK_FROZEN)) == MPART_F_MLOCK);
		if (!mpart_has_mlock_nodes(lopart)) {
			lopart->mp_flags &= ~MPART_F_MLOCK;
		} else if (!mpart_has_mlock_nodes(hipart)) {
			atomic_and(&hipart->mp_flags, ~MPART_F_MLOCK);
		}
	}

	if (lopart->mp_meta) {
		struct mpartmeta *lometa, *himeta;
		lometa = lopart->mp_meta;
		himeta = hipart->mp_meta;
		assert(himeta);
		/* Initialize the lometa futex lock in write-mode! */
		atomic_rwlock_init_write(&lometa->mpm_ftxlock);
		_mpartmeta_init_noftxlock(lometa);
#ifdef ARCH_HAVE_RTM
		++himeta->mpm_rtm_vers; /* Indicate that something has changed. */
		lometa->mpm_rtm_vers = himeta->mpm_rtm_vers;
#endif /* ARCH_HAVE_RTM */

		/* Transfer futex objects */
		if (himeta->mpm_ftx) {
			struct mfutex *tree = himeta->mpm_ftx;
			himeta->mpm_ftx     = NULL;
			mfutex_tree_reinsert_or_transfer_lstrip(&lometa->mpm_ftx,
			                                        &himeta->mpm_ftx,
			                                        tree, lopart, addr);
		}
		mpartmeta_ftxlock_endwrite(lometa, lopart);
	}


	/* Mirror the is-part-of-all-list attribute of `hipart' within `lopart'.
	 * NOTE: Once we do this, `lopart' becomes visible to the outside world! */
	COMPILER_BARRIER();
	if (LIST_ISBOUND(hipart, mp_allparts))
		mpart_all_list_insert(lopart);

	/* remove locks to mmans in `lopart', and no longer present in `hipart',
	 * in addition  to dropping  references  from _all_  transferred  mmans. */
	{
		unsigned int i;
		for (i = 0; i < lengthof(lopart->_mp_nodlsts); ++i) {
			struct mnode *node;
			LIST_FOREACH (node, &lopart->_mp_nodlsts[i], mn_link) {
				struct mman *mm = node->mn_mman;
				assertf(!wasdestroyed(mm),
				        "Only non-destroyed mmans should have been transferred!");
				assertf(!(node->mn_flags & MNODE_F_UNMAPPED),
				        "Only non-UNMAPPED nodes should have been transferred!");
				if (!mpart_mappedby_mman_before(lopart, node, mm) &&
				    !mpart_mappedby_mman_before(hipart, NULL, mm))
					mman_lock_release(mm);
				decref_unlikely(mm);
			}
		}
	}

	/* Release the lock with which we've created `lopart' */
	mpart_assert_integrity(lopart);
	mpart_lock_release(lopart);

	/* Drop our own personal reference from `lopart' (created above)
	 * We had to keep it up until _after_ all locks were released in
	 * order to guaranty that no other  thread would try to jump  in
	 * and destroy the part before we could release all locks. */
	decref_unlikely(lopart);

	/************************************************************************/
	/* === SPLIT: With `lopart' done, lstrip inherited data in `hipart'     */
	/************************************************************************/

	/* Update the block-status bitset to strip leading bytes. */
	mpart_lstrip_blkst(hipart, addr);

	/* Update the offsets within associated mem-nodes. */
	mpart_lstrip_nodes(hipart, addr);

	/* Trim leading pages from `hipart'. Note that `lopart' has
	 * inherited ownership of these pages, so `hipart' must act
	 * as though it didn't know anything about them! */
	switch (hipart->mp_state) {

	case MPART_ST_SWP:
	case MPART_ST_MEM:
		assert(hipart->mp_mem.mc_size > pages);
		hipart->mp_mem.mc_start += pages;
		hipart->mp_mem.mc_size -= pages;
		break;

	case MPART_ST_SWP_SC:
	case MPART_ST_MEM_SC:
		/* NOTE: Use the no-op free function since the actual
		 *       data has already been inherited by `lopart'! */
		mpart_lstrip_memsc(hipart, pages, &mpart_freefun_noop);
		break;

	default:
		break;
	}

	/* Update the part's actual maxaddr field. */
	hipart->mp_minaddr += addr;
	assert(hipart->mp_minaddr <= hipart->mp_maxaddr);

	/* And with that: we're done! */
	return MPART_TRIM_STATUS_SUCCESS;
err_nomem_lopart_bitset_scvec:
	if (lopart->mp_state == MPART_ST_SWP_SC ||
	    lopart->mp_state == MPART_ST_MEM_SC)
		kfree(lopart->mp_mem_sc.ms_v);
err_nomem_lopart_bitset:
	if (!(lopart->mp_flags & MPART_F_BLKST_INL))
		kfree(lopart->mp_blkst_ptr);
err_nomem_lopart:
	mpart_free(lopart);
	return MPART_TRIM_STATUS_NOMEM;
}



/* Detach all futex objects reachable from `self' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfutex_tree_detachall)(struct mfutex *__restrict self,
                                     struct ccinfo *info) {
	struct mfutex *lhs, *rhs;
again:
	lhs = self->mfu_mtaent.rb_lhs;
	rhs = self->mfu_mtaent.rb_rhs;
	DBG_memset(&self->mfu_mtaent, 0xcc, sizeof(self->mfu_mtaent));
	awref_clear(&self->mfu_part);
	assert(atomic_read(&self->mfu_weakrefcnt) != 0);
	if (atomic_decfetch(&self->mfu_weakrefcnt) == 0) {
		if (info)
			ccinfo_account(info, kmalloc_usable_size(self));
		mfutex_free(self);
	}
	if (lhs) {
		if (rhs)
			mfutex_tree_detachall(rhs, info);
		self = lhs;
		goto again;
	}
	if (rhs) {
		self = rhs;
		goto again;
	}
}

/* Set the effective size of `self' to `0', and free all backing storage. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_clear)(struct mpart *__restrict self,
                           struct ccinfo *info) {
	struct mpartmeta *meta;
	if ((meta = self->mp_meta) != NULL) {
		/* Detach all futex objects by clearing their `mfu_part' pointers. */
		if (meta->mpm_ftx) {
			struct mfutex *tree;
			tree          = meta->mpm_ftx;
			meta->mpm_ftx = NULL;
			mfutex_tree_detachall(tree, info); /* TODO: Track ccinfo */
		}
	}

	/* Free backing memory/swap. */
	switch (self->mp_state) {

	case MPART_ST_SWP:
		if (!(self->mp_flags & MPART_F_NOFREE)) {
			if (info != NULL)
				ccinfo_account_swappages(info, self->mp_swp.mc_size);
			mchunk_freeswp(&self->mp_swp);
		}
		break;

	case MPART_ST_MEM:
		if (!(self->mp_flags & MPART_F_NOFREE)) {
			if (info != NULL)
				ccinfo_account_physpages(info, self->mp_mem.mc_size);
			mchunk_freemem(&self->mp_mem);
		}
		break;

	case MPART_ST_SWP_SC:
		if (!(self->mp_flags & MPART_F_NOFREE))
			mchunkvec_freeswp(self->mp_swp_sc.ms_v, self->mp_swp_sc.ms_c, info);
		if (info)
			ccinfo_account(info, kmalloc_usable_size(self->mp_swp_sc.ms_v));
		kfree(self->mp_swp_sc.ms_v);
		break;

	case MPART_ST_MEM_SC:
		if (!(self->mp_flags & MPART_F_NOFREE))
			mchunkvec_freemem(self->mp_mem_sc.ms_v, self->mp_mem_sc.ms_c, info);
		if (info)
			ccinfo_account(info, kmalloc_usable_size(self->mp_mem_sc.ms_v));
		kfree(self->mp_mem_sc.ms_v);
		break;

	default:
		break;
	}

	/* Deallocate a dynamically allocated block-status-bitset. */
	if (self->mp_blkst_ptr != NULL && !(self->mp_flags & MPART_F_BLKST_INL)) {
		if (info)
			ccinfo_account(info, kmalloc_usable_size(self->mp_blkst_ptr));
		kfree(self->mp_blkst_ptr);
		self->mp_blkst_ptr = NULL;
	}

	/* Change the part into a void-state. */
	self->mp_state = MPART_ST_VOID;

	/* NOTE: The part is always anonymous, unless we got here from `mpart_trim_or_unlock_nx()' */
	if (mpart_isanon(self)) {
		/* Set mp_minaddr/mp_maxaddr to indicate an empty part. */
		self->mp_minaddr = (pos_t)PAGESIZE;
		self->mp_maxaddr = (pos_t)PAGESIZE - 1;

		/* If not already referencing one of the generic anon-files,
		 * change  the part's  associated file  to one  of them now! */
		if (!(self->mp_file >= mfile_anon &&
		      self->mp_file < COMPILER_ENDOF(mfile_anon))) {
			REF struct mfile *newfile, *oldfile;
			oldfile       = self->mp_file;
			newfile       = incref(&mfile_anon[oldfile->mf_blockshift]);
			self->mp_file = newfile;
			decref_unlikely(oldfile);
		}

		/* Clear the `MPART_F_GLOBAL_REF' bit. */
		if (atomic_fetchand(&self->mp_flags, ~MPART_F_GLOBAL_REF) & MPART_F_GLOBAL_REF)
			decref_nokill(self);
	}
}



/* Trim `self' whilst holding all relevant locks:
 *   - mpart_lock_acquired(self);
 *   - !self->mp_meta || mpartmeta_ftxlock_writing(self->mp_meta);
 *   - mman_lock_acquired(self->mp_copy.each->mn_mman.filter(!wasdestroyed($)));
 *   - mman_lock_acquired(self->mp_share.each->mn_mman.filter(!wasdestroyed($)));
 * @return: * : One of `MPART_TRIM_STATUS_*' */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) unsigned int
NOTHROW(FCALL mpart_trim_with_all_locks)(struct mpart *__restrict self) {
	struct mnode *node;
	struct mpart_node_iterator iter;

	/* Check  if `self' might possibly contain gaps that
	 * aren't being referenced by any of the part's mem-
	 * nodes.
	 *
	 * In order to find gaps, we can do this:
	 *  - Sort  the mem-node lists  by their `mn_partoff', and
	 *    use an iterator abstraction with 2 mem-node pointers
	 *    into each of the  lists that offsets a  next_after()
	 *    function to enumerate them in order.
	 *  - Then, enumerate all mem-nodes in order and look for
	 *    adjacent nodes with gaps in-between.
	 *
	 * For  leading/trailing  gaps, directly  trim  `self'. For
	 * leading gaps, also update the `mn_partoff' of all nodes.
	 *
	 * For gaps found elsewhere, punch a hole into the part,
	 * similar to  `mpart_split()'. -  However, since  we're
	 * already holding all of  the relevant locks, our  impl
	 * of that function's behavior would only require us  to
	 * alloc 1 additional mem-part  for every hole we  find.
	 *
	 * For every hole found like this, set-up a new mpart to  fill
	 * in the hole, and have it take the place of the range  below
	 * the  gap. - Then release locks to all mmans associated with
	 * the lopart, that aren't also  present in `self'; this  way,
	 * we, and our caller will still be holding locks to all mmans
	 * associated with nodes from `self' */

	/* Step #1: Since this isn't normally a  requirement,
	 *          make sure that mem-node lists are sorted. */
	mnode_list_sort_by_partoff(&self->mp_share);
	mnode_list_sort_by_partoff(&self->mp_copy);

	/* Step #2: Enumerate nodes. */
again_enum_nodes:
	mpart_node_iterator_init(&iter, self);
	node = mpart_node_iterator_next(&iter);

	if unlikely(!node) {
		/* This can happen if _all_ nodes have the UNMAPPED flag set! */
		mpart_clear(self, NULL);
		return MPART_TRIM_STATUS_SUCCESS;
	}

	/* Step #3: Check for an unused portion preceding the first node. */
	if (node->mn_partoff != 0 &&
	    node->mn_partoff > self->mp_file->mf_part_amask) {
		PAGEDIR_PAGEALIGNED mpart_reladdr_t lstrip;
		lstrip = node->mn_partoff & ~(mpart_reladdr_t)self->mp_file->mf_part_amask;
		assert(lstrip);
		mpart_lstrip(self, lstrip);
		assert(node->mn_partoff <= self->mp_file->mf_part_amask);
	}

	/* Step #4: Go over all nodes and find mapping gaps. */
	for (;;) {
		struct mnode *next;
		mpart_reladdr_t node_endaddr;
		mpart_reladdr_t next_basaddr;
		next = mpart_node_iterator_next(&iter);
		if (!next)
			break; /* Last node reached. */
		/* Figure out of there's some part that's not mapped. */
		node_endaddr = mnode_getpartendaddr(node);

again_check_next_same_base:
		if (next->mn_partoff == node->mn_partoff) {
			/* Special case: because the list of nodes is only sorted by `mn_partoff',
			 *               it can happen that more  than one node mapping starts  at
			 *               the same base address.
			 * When this is the case, we have to scan all adjacent  same-base-address
			 * nodes for the one that is the largest (iow: has the greatest mpart end
			 * address; i.e. `mnode_getpartendaddr()').
			 * Otherwise, we'd only use the last node from a set of same-base-address
			 * nodes, which may not necessarily be the largest! */
			mpart_reladdr_t next_endaddr;
			next_endaddr = mnode_getpartendaddr(next);
			if (node_endaddr < next_endaddr) {
				node_endaddr = next_endaddr; /* Use the end-address of the largest node! */
				node         = next;         /* Node needs to stay the one which extends the greatest amount. */
			}

			/* Look  at the next node and check if it too has the same base address.
			 * Note that since the  list of nodes is  sorted by base address,  we're
			 * allowed to assume any follow-up node's base address is >= the current
			 * node's. */
			next = mpart_node_iterator_next(&iter);
			if (!next)
				break; /* Last node reached. */
			goto again_check_next_same_base;
		}

		/* Special case:
		 *    NODE[0]: { 0FFFC000-10001FFF, mn_partoff: 0x0000 }  // size == 0x6000  (mapendaddr: 0x6000)
		 *    NODE[1]: { 0FFFF000-0FFFFFFF, mn_partoff: 0x3000 }  // size == 0x1000  (mapendaddr: 0x4000)
		 *    NODE[2]: { 10000000-10003FFF, mn_partoff: 0x6000 }  // size == 0x4000  (mapendaddr: 0xA000)
		 *
		 * When the  next node  is entirely  contained within  the
		 * current node, then we mustn't allow ourselves to switch
		 * to a node with a  lower node_endaddr that the  current.
		 *
		 * See the  above example  data  for one  such  scenario.
		 * Without this special  handling, the  below code  would
		 * try to trim  part region [0x4000-0x5FFF]  as a  result
		 * of  the  (apparent) gap  between NODE[1]  and NODE[2].
		 * However, NODE[1] is entirely contained within NODE[0],
		 * which  ends  at  0x6000, meaning  that  there actually
		 * isn't any gap at all.
		 *
		 * Fix this problem by simply skipping nodes that are
		 * entirely   contained   within   preceding   nodes. */
again_check_next_inside_current:
		if (mnode_getpartendaddr(next) <= node_endaddr) {
			next = mpart_node_iterator_next(&iter);
			if (!next)
				break; /* Last node reached. */
			goto again_check_next_inside_current;
		}

		next_basaddr = mnode_getpartaddr(next);
		if (node_endaddr < next_basaddr) {
			/* Align addresses by the mandatory file alignment. */
			node_endaddr += self->mp_file->mf_part_amask;
			node_endaddr &= ~(mpart_reladdr_t)self->mp_file->mf_part_amask;
			next_basaddr &= ~(mpart_reladdr_t)self->mp_file->mf_part_amask;
			if (node_endaddr < next_basaddr) {
				/* Split the mem-part at the start of the  hole.
				 * Once this succeeds, we'll loop back around to
				 * re-start enumeration, which will then  notice
				 * that the first  `next_basaddr - node_endaddr'
				 * bytes can be split. */
				unsigned int status;
				status = mpart_async_split_before(self, node_endaddr);
				if (status != MPART_TRIM_STATUS_SUCCESS)
					return status;
				goto again_enum_nodes;
			}
		}
		node = next;
	}

	/* Step #5: Check if the last `node' maps the remainder of `self'.
	 *          If it doesn't, then rstrip the unused tail to free it. */
	{
		mpart_reladdr_t node_endaddr;
		mpart_reladdr_t part_endaddr;
		node_endaddr = mnode_getpartendaddr(node);
		part_endaddr = mpart_getsize(self);
		assert(node_endaddr <= part_endaddr);
		assert((part_endaddr & self->mp_file->mf_part_amask) == 0);
		if (node_endaddr < part_endaddr) {
			node_endaddr += (mpart_reladdr_t)self->mp_file->mf_part_amask;
			node_endaddr &= ~(mpart_reladdr_t)self->mp_file->mf_part_amask;
			assert(node_endaddr <= part_endaddr);
			if (node_endaddr < part_endaddr) {
				/* rstrip() the last `part_endaddr - node_endaddr' bytes of `self' */
				mpart_rstrip(self, part_endaddr - node_endaddr);
			}
		}
	}

	return MPART_TRIM_STATUS_SUCCESS;
}







/* Increment the reference counter of every (not already-destroyed)
 * mman that can be reached via the `mp_copy' and `mp_share' chains
 * of `self'.
 * @return: true:  At least 1 mman was incref'd.
 * @return: false: No, or only dead mmans referenced. */
PRIVATE NOBLOCK NONNULL((1)) bool
NOTHROW(FCALL mpart_foreach_mmans_incref)(struct mpart *__restrict self) {
	bool result = false;
	unsigned int i;
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		struct mnode *node;
		LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link)
			result |= tryincref(node->mn_mman);
	}
	return result;
}

/* Decref all mmans of `self' (skipping those that were already destroyed) */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) void
NOTHROW(FCALL mpart_decref_all_mmans)(struct mpart const *__restrict self) {
	unsigned int i;
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		struct mnode *node;
		LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link) {
			if likely(!wasdestroyed(node->mn_mman))
				decref_unlikely(node->mn_mman);
		}
	}
}


/* Like `mpart_mappedby_mman()', but stop checking nodes when `stop'
 * is reached. Additionally, `stop' isn't considered to be apart  of
 * the list of nodes to test for mapping `mm' */
PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1, 3)) bool
NOTHROW(FCALL mpart_mappedby_mman_before)(struct mpart const *__restrict self,
                                          struct mnode const *stop,
                                          struct mman const *__restrict mm) {
	unsigned int i;
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		struct mnode *node;
		LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link) {
			if (node == stop)
				return false;
			if (node->mn_mman == mm)
				return true;
		}
	}
	return false;
}


/* Release locks to every unique mman with nodes that map `self'.
 * For every mman, only a single lock is released, and only locks
 * to mmans to nodes before `stop' are released (unless `stop' is
 * given as `NULL', in which case _all_ locks are released) */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) void
NOTHROW(FCALL mpart_unlock_all_mmans)(struct mpart const *__restrict self,
                                      struct mnode const *stop DFL(NULL)) {
	struct mnode *node;
	unsigned int i;
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link) {
			if (node == stop)
				return; /* Stop on this node! */
			if unlikely(wasdestroyed(node->mn_mman))
				continue; /* Skip destroyed mmans */
			if (mpart_mappedby_mman_before(self, node, node->mn_mman))
				continue; /* Already unlocked before... */
			mman_lock_release(node->mn_mman);
		}
	}
}


/* Try to acquire locks to all of the mmans of `self'. (skipping dead mmans)
 * If doing so would block for one  of the mmans, release all locks  already
 * acquired, and return a pointer to the blocking mman. */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) struct mman *
NOTHROW(FCALL mpart_lock_all_mmans)(struct mpart const *__restrict self) {
	struct mnode *node;
	unsigned int i;
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link) {
			if unlikely(wasdestroyed(node->mn_mman))
				continue; /* Skip destroyed mmans */
			if (mman_lock_tryacquire(node->mn_mman))
				continue; /* Successfully locked the mman */
			if (mpart_mappedby_mman_before(self, node, node->mn_mman))
				continue; /* We've already acquired a lock to this mman in the part. */
			/* Oops... We've got a blocking one here! */
			mpart_unlock_all_mmans(self, node);
			return node->mn_mman;
		}
	}
	return NULL;
}



/* NOTE: This function inherits a reference to `container_of(_lop, struct mpart, _mp_trmplop_mm)' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_trim_mmplop)(Tobpostlockop(mman) *__restrict _lop,
                                 struct mman *__restrict UNUSED(mm));

/* NOTE: This function inherits a reference to `container_of(_lop, struct mpart, _mp_trmlop_mm)' */
PRIVATE NOBLOCK NONNULL((1)) Tobpostlockop(mman) *
NOTHROW(FCALL mpart_trim_mmlop)(Toblockop(mman) *__restrict _lop,
                                struct mman *__restrict UNUSED(mm)) {
	REF struct mpart *self;
	self = container_of(_lop, struct mpart, _mp_trmlop_mm);
	atomic_write(&self->_mp_trmplop_mm.oplo_func, &mpart_trim_mmplop);
	return &self->_mp_trmplop_mm;
}


/* Same  as  `mpart_trim_locked()', but  the caller
 * is also holding a lock to the part's futex-tree. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_trim_locked_ftx)(struct mpart *__restrict self) {
	unsigned int status;

	/* Try to incref() all alive mmans, thus keeping them alive and allowing
	 * us  to try to acquire locks to each of them, without some (or all) of
	 * them suddenly being destroyed while we're still busy.
	 *
	 * If we don't find any alive mmans, then we know that the effective area
	 * mapped by mem-nodes of `self' is empty, meaning that we can clear  the
	 * mem-part in its entirety! */
	if unlikely(!mpart_foreach_mmans_incref(self)) {
		mpart_clear(self, NULL);
		goto trim_completed;
	}

	/* Try to acquire locks to  all of the mmans  that are mapping this  part.
	 * This is needed so we can get piece together a consistent (non-volatile)
	 * view of all of the regions of `self' that are actually used. */
	{
		struct mman *blocking_mm;
		blocking_mm = mpart_lock_all_mmans(self);
		if unlikely(blocking_mm) {
			incref(blocking_mm);
			mpart_decref_all_mmans(self);

			/* asynchronously wait for the lock of this mman to become available. */
			atomic_write(&self->_mp_trmlop_mm.olo_func, &mpart_trim_mmlop);
			incref(self); /* Inherited by `mpart_trim_mmlop()' */
			SLIST_ATOMIC_INSERT(&FORMMAN(blocking_mm, thismman_lockops),
			                    &self->_mp_trmlop_mm, olo_link);
			_mman_lockops_reap(blocking_mm);
			decref_unlikely(blocking_mm);
			return;
		}
	}

	/* Continue the trim operation now that we're holding  locks
	 * to the part itself, as well as all of the relevant mmans. */
	status = mpart_trim_with_all_locks(self);

	/* Release locks & references acquired above. */
	mpart_unlock_all_mmans(self);
	mpart_decref_all_mmans(self);

	/* If necessary, enqueue the part for async trim operation within the kernel mman. */
	if likely(status == MPART_TRIM_STATUS_SUCCESS) {
trim_completed:
		/* Indicate that the async mpart-trim operation has completed.
		 * Once  this has been done, other threads can once again call
		 * `mpart_trim()' in order to initiate yet another async  trim
		 * operation! */
		atomic_write(&self->_mp_trmlop_mp.olo_func, NULL);
	} else if (status == MPART_TRIM_STATUS_NOMEM) {
		/* Must do the trim operation via the mpart async-job system. */
		atomic_write(&self->_mp_trmlop_mp.olo_func, NULL);
		mpart_start_asyncjob(incref(self), MPART_XF_WILLTRIM);
	}
}



/* We can re-use  the mman-post-lock function  for the  async-futex-lock-
 * acquired code-path. Technically, we could also write a more  optimized
 * version  that could  then make assumptions  based on the  fact that it
 * knows  that the  mem-part being  trimmed can't  possibly get destroyed
 * while it's working (since the reap-caller will be holding a reference,
 * but  given that  the async-futex-lock  code-path is  quite rare as-is,
 * that's  not  really necessary,  given  that the  more  general version
 * already quired for mman-locks works just as well!) */
#define mpart_trim_ftxplop (*(Tobpostlockop_callback_t(mpart))&mpart_trim_mmplop)

PRIVATE NOBLOCK NONNULL((1)) Tobpostlockop(mpart) *
NOTHROW(FCALL mpart_trim_ftxlop)(Toblockop(mpart) *__restrict _lop,
                                 REF struct mpart *__restrict self) {
	assert(_lop == &self->_mp_trmlop_mp);
	atomic_write(&self->_mp_trmplop_mp.oplo_func, &mpart_trim_ftxplop);
	return &self->_mp_trmplop_mp;
}


/* Same as `mpart_trim()', but  don't inherit a reference,  and
 * assume that the caller is currently holding a lock to `self'
 * NOTE: This function also assumes that `_mp_trmlop*.olo_func'
 *       is non-NULL upon entry! */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_trim_locked)(struct mpart *__restrict self) {
	struct mpartmeta *meta;
	assertf(mpart_isanon(self),
	        "We've already checked this earlier, and once a part "
	        "has become anon, it must never become non-anon!");

	/* Quick check: are we allowed to trim this part? */
	if unlikely(!mpart_maytrim(self))
		return;

	/* If some blocks are currently being initialized, then the
	 * trim must happen  *after* that  operation has  finished. */
	if unlikely(mpart_hasblocksstate_init(self)) {
		/* Wait for INIT-blocks to go away, and _then_ re-attempt the trim! */
		atomic_or(&self->mp_xflags, MPART_XF_TRIM_AFTER_INIT);
		if likely(mpart_hasblocksstate_init(self))
			return;
		atomic_and(&self->mp_xflags, ~MPART_XF_TRIM_AFTER_INIT);
	}

	/* If necessary, acquire yet another lock to the meta-data controller of `self' */
	if likely((meta = self->mp_meta) == NULL) {
		mpart_trim_locked_ftx(self);
	} else {
		if (atomic_read(&meta->mpm_dmalocks) != 0) {
			/* Wait for DMA-locks to go away, and _then_ re-attempt the trim! */
			atomic_or(&self->mp_xflags, MPART_XF_TRIM_AFTER_DMA);
			COMPILER_READ_BARRIER();
			if (atomic_read(&meta->mpm_dmalocks) != 0)
				return;
			atomic_and(&self->mp_xflags, ~MPART_XF_TRIM_AFTER_DMA);
		}
		if (mpartmeta_ftxlock_trywrite(meta)) {
			mpart_trim_locked_ftx(self);
			mpartmeta_ftxlock_endwrite(meta, self);
		} else {
			/* Must acquire the futex-lock asynchronously. */
			atomic_write(&self->_mp_trmlop_mp.olo_func, &mpart_trim_ftxlop);
			incref(self); /* The reference inherited by `mpart_trim_ftxlop' */
			/* NOTE: No need for a 2nd incref(self) to prevent `self' from being
			 *       destroyed before we get to  reap it! Our caller is  already
			 *       holding that reference! */
			SLIST_ATOMIC_INSERT(&meta->mpm_ftxlops, &self->_mp_trmlop_mp, olo_link);
			_mpartmeta_ftxlock_reap(meta, self);
		}
	}
}


PRIVATE NOBLOCK NONNULL((1)) Tobpostlockop(mpart) *
NOTHROW(FCALL mpart_trim_mplop)(Toblockop(mpart) *__restrict _lop,
                                REF struct mpart *__restrict self) {
	assert_assume(_lop == &self->_mp_trmlop_mp);
	(void)_lop;
	mpart_trim_locked(self);
	/* *_nokill, because the caller must also be holding a reference to `self'! */
	decref_nokill(self);
	return NULL;
}


/* NOTE: This function inherits a reference to `container_of(_lop, struct mpart, _mp_trmplop_mm)' */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_trim_mmplop)(Tobpostlockop(mman) *__restrict _lop,
                                 struct mman *__restrict UNUSED(mm)) {
	REF struct mpart *self;
	self = container_of(_lop, struct mpart, _mp_trmplop_mm);
	if (atomic_cmpxch(&self->mp_refcnt, 1, 0))
		goto do_destroy;

	/* The lock to  `mm' did become  available at one  point.
	 * As such, re-attempt the async `mpart_trim()' operation
	 * by trying to get a new lock for `self' again. If  this
	 * fails, then simply enqueue `mpart_trim_mplop()'! */
	if (mpart_lock_tryacquire(self)) {
		/* Do the actual trimming! */
		mpart_trim_locked(self);
		mpart_assert_integrity(self);
		mpart_lock_release(self);
	} else {
		/* The part lock isn't available.
		 * As such, we muss use `mpart_trim_mplop()' in order
		 * to asynchronously  wait for  a lock  to the  part! */
		atomic_write(&self->_mp_trmlop_mp.olo_func, &mpart_trim_mplop);

		/* Prevent the part from dying while in `_mpart_lockops_reap()'
		 * This reference is dropped further down below. */
		incref(self);
		SLIST_ATOMIC_INSERT(&self->mp_lockops, &self->_mp_trmlop_mp, olo_link);
		_mpart_lockops_reap(self);
	}

	/* Drop the reference to the part.
	 * Note that this may result in the part dying, since
	 * we get here via an mman-lock, as opposed to a lock
	 * to the part itself (meaning our caller may not  be
	 * holding a reference to `self' at this point!)
	 *
	 * Note that this  decref() is  unlikely to  actually
	 * destroy  the part, because we've already attempted
	 * to atomic_cmpxch() the reference counter to 0, and
	 * it didn't work back then. */
	decref_unlikely(self);
	return;
do_destroy:
	mpart_destroy(self);
}




/* If `self' is an anonymous mem-part, asynchronously acquire a
 * lock to `self' and compare the min/max-addr bounds of `self'
 * against the portions that are actually mapped by  mem-nodes.
 * If it is found that leading/trailing portions of `self'  are
 * not mapped by  any mem-node, trim  those parts from  `self'.
 * If there are holes within `self' of pages not mapped by  any
 * mem-nodes,  asynchronously split `self', and update nodes in
 * order to get rid of the relevant ranges.
 * This function should  be called  whenever mem-node  mappings
 * of `self' have been removed, in order to drop the references
 * that were originally held by those nodes.
 * NOTE: When `self' isn't anonymous, simply `decref(self)'!
 * NOTE: This function usually doesn't need to be called directly.
 *       Instead, it is  called from  `mnode_destroy()' to  decref
 *       the associated part after the node has been removed  from
 *       the list of node-mappings of `self' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_trim)(/*inherit(always)*/ REF struct mpart *__restrict self) {

	/* Check for special case: can we destroy the part immediately? */
	if (atomic_cmpxch(&self->mp_refcnt, 1, 0))
		goto do_destroy;

	/* Check for special case: the part isn't anonymous.
	 *
	 * The reason why we can only do this for non-anonymous parts is three-fold:
	 * 1: The `_mp_trmlop_mp' field overlaps with `mp_filent' (which is needed for non-anonymous parts)
	 * 2: Unloading file caches because they're not mmap'd is inefficient so-long as we still have enough
	 *    available  physical memory (so it's better to use that memory to cache data that's already been
	 *    loaded from disk, than to free such memory as soon as possible).
	 * 3: `system_cc()' (which gets called when we're low on memory) uses `mpart_trim_or_unlock()', which
	 *    *is* able to trim non-anonymous parts (using `mpart_trim_or_unlock_nx()'), so it isn't affected
	 *    by this restriction.
	 *
	 * Also: This prevents parts of `MFILE_F_PERSISTENT' files from being deleted (since
	 *       those kinds  of files  (i.e. ramfs)  aren't anonymous  until  `unlink(2)'d) */
	if (!mpart_isanon_atomic(self))
		goto do_normal_decref;

	/* Try to get a lock to the part. */
	if (mpart_lock_tryacquire(self)) {
		/* Deal with the (very unlikely) race condition of another thread enqueuing
		 * yet another async `mpart_trim()' operation after we've acquired our lock
		 * to `self'. - It can happen, and if it does, then  `mpart_lock_release()'
		 * will reaping once we  release the lock ~should~  cause the lockop to  be
		 * serviced. */
		if unlikely(!atomic_cmpxch(&self->_mp_trmlop_mp.olo_func,
		                           NULL, &mpart_trim_mplop)) {
			_mpart_lock_release(self);
			goto reap_and_normal_decref;
		}

		/* Do the actual trimming! */
		mpart_trim_locked(self);
		mpart_assert_integrity(self);
		mpart_lock_release(self);
	} else {
		/* Schedule an async lock-op.
		 * If such an operation is already in-progress, then don't do anything,
		 * since someone else will already end up doing what our caller  wanted
		 * us to kick-start! */
		if (!atomic_cmpxch(&self->_mp_trmlop_mp.olo_func, NULL, &mpart_trim_mplop))
			goto do_normal_decref;

		/* Get another reference so `self' is kept alive, even
		 * if reaping the part  below ends up succeeding,  and
		 * would otherwise cause the part to be destroyed. */
		incref(self);

		/* We've just kick-started the async-trim process. - Now we need to
		 * commit and enqueue the part into its own lock-op list. Also note
		 * that  by doing this, `mpart_trim_mplop' essentially inherits our
		 * caller-given reference to the mem-part! */
		SLIST_ATOMIC_INSERT(&self->mp_lockops, &self->_mp_trmlop_mp, olo_link);

		/* With the new lockop added, reap in case the lock became available. */
reap_and_normal_decref:
		_mpart_lockops_reap(self);
	}
do_normal_decref:
	/* Finally, drop the reference given by our caller. */
	decref_unlikely(self);
	return;
do_destroy:
	mpart_destroy(self);
}


#include <kernel/printk.h>


/* Same as `mpart_trim_or_unlock()', but all relevant locks are held by the caller. */
PRIVATE NOBLOCK_IF(ccinfo_noblock(data->mtd_ccinfo)) WUNUSED NONNULL((1, 2)) unsigned int
NOTHROW(FCALL mpart_trim_locked_with_all_locks_or_unlock)(struct mpart *__restrict self,
                                                          struct mpart_trim_data *__restrict data,
                                                          struct unlockinfo *unlock) {
#define LOCAL_unlock_all()                                                   \
	(!self->mp_meta || (mpartmeta_ftxlock_endwrite(self->mp_meta, self), 1), \
	 mpart_isanon(self) || (mfile_lock_endwrite(self->mp_file), 1),          \
	 mpart_unlock_all_mmans(self),                                           \
	 _mpart_lock_release(self),                                              \
	 unlockinfo_xunlock(unlock),                                             \
	 mpart_lockops_reap(self))
	unsigned int result = MPART_NXOP_ST_SUCCESS;

	/* Since this isn't normally a  requirement,
	 * make sure that mem-node lists are sorted. */
	mnode_list_sort_by_partoff(&self->mp_share);
	mnode_list_sort_by_partoff(&self->mp_copy);

	printk(KERN_DEBUG "TODO: mpart_trim_locked_with_all_locks_or_unlock(%p: %#I64x - %#I64x)\n",
	       self->mp_file, self->mp_minaddr, self->mp_maxaddr);
	/* TODO: enumerate ranges that should be trimmed based on `data->mtd_mode' */
	(void)self;
	(void)data;
	(void)unlock;

#undef LOCAL_unlock_all
	return result;
}

/* Same as `mpart_trim_or_unlock()', but the caller is holding a lock
 * to `self->mp_meta' (if non-NULL) and `self->mp_file' (if not anon) */
PRIVATE NOBLOCK_IF(ccinfo_noblock(data->mtd_ccinfo)) WUNUSED NONNULL((1, 2)) unsigned int
NOTHROW(FCALL mpart_trim_locked_ftx_file_or_unlock)(struct mpart *__restrict self,
                                                    struct mpart_trim_data *__restrict data,
                                                    struct unlockinfo *unlock) {
#define LOCAL_unlock_all()                                                   \
	(!self->mp_meta || (mpartmeta_ftxlock_endwrite(self->mp_meta, self), 1), \
	 mpart_isanon(self) || (mfile_lock_endwrite(self->mp_file), 1),          \
	 _mpart_lock_release(self),                                              \
	 unlockinfo_xunlock(unlock),                                             \
	 mpart_lockops_reap(self))
	unsigned int result = MPART_NXOP_ST_SUCCESS;

	/* Try to incref() all alive mmans, thus keeping them alive and allowing
	 * us  to try to acquire locks to each of them, without some (or all) of
	 * them suddenly being destroyed while we're still busy.
	 *
	 * If we don't find any alive mmans, then we know that the effective area
	 * mapped by mem-nodes of `self' is empty, meaning that we can clear  the
	 * mem-part in its entirety! */
	if unlikely(!mpart_foreach_mmans_incref(self)) {
		mpart_clear(self, data->mtd_ccinfo);
		goto done;
	}

	/* Try to acquire locks to  all of the mmans  that are mapping this  part.
	 * This is needed so we can get piece together a consistent (non-volatile)
	 * view of all of the regions of `self' that are actually used. */
	{
		struct mman *blocking_mm;
		blocking_mm = mpart_lock_all_mmans(self);
		if unlikely(blocking_mm) {
			incref(blocking_mm);
			mpart_decref_all_mmans(self);
			if (ccinfo_noblock(data->mtd_ccinfo)) {
				decref_unlikely(blocking_mm);
				goto done;
			}
			LOCAL_unlock_all();

			/* Wait for `blocking_mm' to become available. */
			result = MPART_NXOP_ST_RETRY;
			if (!mman_lock_waitfor_nx(blocking_mm))
				result = MPART_NXOP_ST_ERROR;
			decref_unlikely(blocking_mm);
			goto done;
		}
	}

	/* Continue the trim operation now that we're holding  locks
	 * to the part itself, as well as all of the relevant mmans. */
	result = mpart_trim_locked_with_all_locks_or_unlock(self, data, unlock);

	/* Release locks & references acquired above. */
	if (result == MPART_NXOP_ST_SUCCESS)
		mpart_unlock_all_mmans(self);
	mpart_decref_all_mmans(self);
#undef LOCAL_unlock_all
done:
	return result;
}

/* Same as `mpart_trim_or_unlock()', but the caller is holding a lock to `self->mp_meta' (if non-NULL) */
PRIVATE NOBLOCK_IF(ccinfo_noblock(data->mtd_ccinfo)) WUNUSED NONNULL((1, 2)) unsigned int
NOTHROW(FCALL mpart_trim_locked_ftx_or_unlock)(struct mpart *__restrict self,
                                               struct mpart_trim_data *__restrict data,
                                               struct unlockinfo *unlock) {
#define LOCAL_unlock_all()                                                   \
	(!self->mp_meta || (mpartmeta_ftxlock_endwrite(self->mp_meta, self), 1), \
	 _mpart_lock_release(self),                                              \
	 unlockinfo_xunlock(unlock),                                             \
	 mpart_lockops_reap(self))
	unsigned int result = MPART_NXOP_ST_SUCCESS;

	/* Lock the part's file (if needed) */
	if (mpart_isanon(self)) {
		result = mpart_trim_locked_ftx_file_or_unlock(self, data, unlock);
	} else {
		struct mfile *file = self->mp_file;
		if (!mfile_lock_trywrite(file)) {
			if (ccinfo_noblock(data->mtd_ccinfo))
				goto done;
			incref(file);
			LOCAL_unlock_all();
			result = MPART_NXOP_ST_RETRY;
			if (!mfile_lock_waitwrite_nx(file))
				result = MPART_NXOP_ST_ERROR;
			decref(file);
			return result;
		}
		result = mpart_trim_locked_ftx_file_or_unlock(self, data, unlock);
		if (result == MPART_NXOP_ST_SUCCESS)
			mfile_lock_endwrite(file);
	}
#undef LOCAL_unlock_all
done:
	return result;
}

/* Synchronous version of `mpart_trim()' (that is also able to trim non-anonymous parts)
 * This function is specifically designed to-be used by `system_cc()' (in case you  were
 * wondering about the meaning of `data->mtd_ccinfo')
 * NOTE: The caller must be holding a lock to `self' when calling this function.
 * NOTE: This  function operates with respect to `ccinfo_noblock(data->mtd_ccinfo)',
 *       in that it will operate as a  no-op whenever something comes up that  would
 *       need to block, in which case `MPART_NXOP_ST_SUCCESS' is returned (emulating
 *       the behavior when  `self' was  trimmed, or  nothing about  `self' could  be
 *       trimmed)
 * @param: data: [in|out] Storage  area for dynamically allocated memory. Note that
 *                        unlike usually, this  data-area does  NOT become  invalid
 *                        when this function succeeds. Even  more so, it may  still
 *                        contain dynamically allocated memory that can be used for
 *                        further trim operations!
 * @return: MPART_NXOP_ST_SUCCESS: Success (all locks were kept)
 * @return: MPART_NXOP_ST_RETRY:   Failed (`unlock' and `mpart_lock_release(self)' was released)
 * @return: MPART_NXOP_ST_ERROR:   Non-recoverable error (OOM or yield-failure). Don't try again. */
PUBLIC NOBLOCK_IF(ccinfo_noblock(data->mtd_ccinfo)) WUNUSED NONNULL((1, 2, 3)) unsigned int
NOTHROW(FCALL mpart_trim_or_unlock_nx)(struct mpart *__restrict self,
                                       struct mpart_trim_data *__restrict data,
                                       struct unlockinfo *unlock) {
	unsigned int result = MPART_NXOP_ST_SUCCESS;
	struct mpartmeta *meta;
	assert(mpart_lock_acquired(self));

	/* Quick check: are we allowed to trim this part? */
	if unlikely(!mpart_maytrim(self))
		goto done;

	/* Make sure that no blocks of `self' is currently being initialized. */
	if unlikely(mpart_hasblocksstate_init(self)) {
		if (ccinfo_noblock(data->mtd_ccinfo))
			goto done;
		result = mpart_initdone_or_unlock_nx(self, unlock);
		if (result != MPART_NXOP_ST_SUCCESS)
			goto done;
	}

	/* Make sure that no DMA operations are in progress for `self' */
	if unlikely(!mpart_is_nodma(self)) {
		if (ccinfo_noblock(data->mtd_ccinfo))
			goto done;
		result = mpart_nodma_or_unlock_nx(self, unlock);
		if (result != MPART_NXOP_ST_SUCCESS)
			goto done;
	}

	/* Lock the meta-controller (if present) */
	if ((meta = self->mp_meta) == NULL) {
		result = mpart_trim_locked_ftx_or_unlock(self, data, unlock);
	} else {
		if (!mpartmeta_ftxlock_trywrite(meta)) {
			if (ccinfo_noblock(data->mtd_ccinfo))
				goto done;
			_mpart_lock_release(self);
			unlockinfo_xunlock(unlock);
			mpart_lockops_reap(self);
			result = MPART_NXOP_ST_RETRY;
			if unlikely(!mpartmeta_ftxlock_waitwrite_nx(meta))
				result = MPART_NXOP_ST_ERROR;
			goto done;
		}
		result = mpart_trim_locked_ftx_or_unlock(self, data, unlock);
		if (result == MPART_NXOP_ST_SUCCESS)
			mpartmeta_ftxlock_endwrite(meta, self);
	}
done:
	mpart_assert_integrity(self);
	return result;
}


#else /* CONFIG_HAVE_KERNEL_MPART_TRIM */

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_trim)(/*inherit(always)*/ REF struct mpart *__restrict self) {
	/* Trimming is disabled. */
	decref(self);
}

/* Synchronous version of `mpart_trim()' (that is also able to trim non-anonymous parts)
 * This function is specifically designed to-be used by `system_cc()' (in case you  were
 * wondering about the meaning of `data->mtd_ccinfo')
 * NOTE: The caller must be holding a lock to `self' when calling this function.
 * NOTE: This  function operates with respect to `ccinfo_noblock(data->mtd_ccinfo)',
 *       in that it will operate as a  no-op whenever something comes up that  would
 *       need to block, in which case `MPART_NXOP_ST_SUCCESS' is returned (emulating
 *       the behavior when  `self' was  trimmed, or  nothing about  `self' could  be
 *       trimmed)
 * @param: data: [in|out] Storage  area for dynamically allocated memory. Note that
 *                        unlike usually, this  data-area does  NOT become  invalid
 *                        when this function succeeds. Even  more so, it may  still
 *                        contain dynamically allocated memory that can be used for
 *                        further trim operations!
 * @return: MPART_NXOP_ST_SUCCESS: Success (all locks were kept)
 * @return: MPART_NXOP_ST_RETRY:   Failed (`unlock' and `mpart_lock_release(self)' was released)
 * @return: MPART_NXOP_ST_ERROR:   Non-recoverable error (OOM or yield-failure). Don't try again. */
PUBLIC NOBLOCK_IF(ccinfo_noblock(data->mtd_ccinfo)) WUNUSED NONNULL((1, 2, 3)) unsigned int
NOTHROW(FCALL mpart_trim_or_unlock_nx)(struct mpart *__restrict self,
                                       struct mpart_trim_data *__restrict data,
                                       struct unlockinfo *unlock) {
	/* Trimming is disabled. */
	COMPILER_IMPURE();
	(void)self;
	(void)data;
	(void)unlock;
	return MPART_TRIM_OR_UNLOCK_ST_SUCCESS;
}

#endif /* !CONFIG_HAVE_KERNEL_MPART_TRIM */

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_TRIM_C */
