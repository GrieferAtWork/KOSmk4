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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_C 1
#define __WANT_MPART__mp_nodlsts
#define __WANT_MPART__mp_lopall
#define __WANT_MPART__mp_dtplop  /* Only to assert offsets */
#define __WANT_MPART__mp_anXplop /* Only to assert offsets */
#define __WANT_MPART__mp_dead    /* Only to assert offsets */
#define __WANT_MPART__mp_trmlop  /* Only to assert offsets */
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/mman.h>
#include <kernel/mman/mcoreheap.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/mpartmeta.h>
#include <kernel/swap.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include <kos/except.h>
#include <kos/lockop.h>

#include <assert.h>
#include <atomic.h>
#include <inttypes.h>
#include <stdalign.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

/* Check if 2 given ranges overlap (that is: share at least 1 common address) */
#define RANGE_OVERLAPS(a_start, a_end, b_start, b_end) \
	((a_end) > (b_start) && (a_start) < (b_end))


#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */


/* Assert `struct mpart' offsets */
static_assert(offsetof(struct mchunk, mc_start) == OFFSET_MCHUNK_START);
static_assert(offsetof(struct mchunk, mc_size) == OFFSET_MCHUNK_SIZE);
static_assert(sizeof(struct mchunk) == SIZEOF_MCHUNK);
static_assert(alignof(struct mchunk) == ALIGNOF_MCHUNK);
static_assert(offsetof(struct mchunkvec, ms_v) == OFFSET_MCHUNKVEC_V);
static_assert(offsetof(struct mchunkvec, ms_c) == OFFSET_MCHUNKVEC_C);
static_assert(sizeof(struct mchunkvec) == SIZEOF_MCHUNKVEC);
static_assert(alignof(struct mchunkvec) == ALIGNOF_MCHUNKVEC);
static_assert(offsetof(struct mpart, mp_refcnt) == OFFSET_MPART_REFCNT);
static_assert(offsetof(struct mpart, mp_flags) == OFFSET_MPART_FLAGS);
static_assert(offsetof(struct mpart, mp_xflags) == OFFSET_MPART_XFLAGS);
static_assert(offsetof(struct mpart, mp_state) == OFFSET_MPART_STATE);
static_assert(offsetof(struct mpart, _mp_joblink) == OFFSET_MPART__JOBLINK);
static_assert(offsetof(struct mpart, _mp_joblink.sle_next) == OFFSET_MPART__JOBLINK_NEXT);
static_assert(offsetof(struct mpart, mp_file) == OFFSET_MPART_FILE);
static_assert(offsetof(struct mpart, mp_copy) == OFFSET_MPART_COPY);
static_assert(offsetof(struct mpart, mp_copy.lh_first) == OFFSET_MPART_COPY_FIRST);
static_assert(offsetof(struct mpart, mp_share) == OFFSET_MPART_SHARE);
static_assert(offsetof(struct mpart, mp_share.lh_first) == OFFSET_MPART_SHARE_FIRST);
static_assert(offsetof(struct mpart, _mp_nodlsts) == OFFSET_MPART__NODLSTS);
static_assert(offsetof(struct mpart, _mp_dtplop) == OFFSET_MPART__DTPLOP);
static_assert(offsetof(struct mpart, _mp_anfplop) == OFFSET_MPART__ANFPLOP);
static_assert(offsetof(struct mpart, _mp_anpplop) == OFFSET_MPART__ANPPLOP);
static_assert(offsetof(struct mpart, mp_lockops) == OFFSET_MPART_LOCKOPS);
static_assert(offsetof(struct mpart, mp_allparts) == OFFSET_MPART_ALLPARTS);
static_assert(offsetof(struct mpart, mp_allparts.tqe_next) == OFFSET_MPART_ALLPARTS_NEXT);
static_assert(offsetof(struct mpart, mp_allparts.tqe_prev) == OFFSET_MPART_ALLPARTS_PREV);
static_assert(offsetof(struct mpart, _mp_lopall) == OFFSET_MPART__LOPALL);
static_assert(offsetof(struct mpart, _mp_plopall) == OFFSET_MPART__PLOPALL);
static_assert(offsetof(struct mpart, mp_changed) == OFFSET_MPART_CHANGED);
static_assert(offsetof(struct mpart, mp_changed.sle_next) == OFFSET_MPART_CHANGED_NEXT);
static_assert(offsetof(struct mpart, _mp_dead) == OFFSET_MPART__DEAD);
static_assert(offsetof(struct mpart, _mp_dead.sle_next) == OFFSET_MPART__DEAD_NEXT);
static_assert(offsetof(struct mpart, mp_minaddr) == OFFSET_MPART_MINADDR);
static_assert(offsetof(struct mpart, mp_maxaddr) == OFFSET_MPART_MAXADDR);
static_assert(offsetof(struct mpart, mp_filent) == OFFSET_MPART_FILENT);
static_assert(offsetof(struct mpart, mp_filent.rb_par) == OFFSET_MPART_FILENT_PAR);
static_assert(offsetof(struct mpart, mp_filent.rb_lhs) == OFFSET_MPART_FILENT_LHS);
static_assert(offsetof(struct mpart, mp_filent.rb_rhs) == OFFSET_MPART_FILENT_RHS);
static_assert(offsetof(struct mpart, __mp_trmlop_pad) == OFFSET_MPART___TRMLOP_PAD);
static_assert(offsetof(struct mpart, _mp_trmlop_mm) == OFFSET_MPART__TRMLOP_MM);
static_assert(offsetof(struct mpart, _mp_trmplop_mm) == OFFSET_MPART__TRMPLOP_MM);
static_assert(offsetof(struct mpart, _mp_trmlop_mp) == OFFSET_MPART__TRMLOP_MP);
static_assert(offsetof(struct mpart, _mp_trmplop_mp) == OFFSET_MPART__TRMPLOP_MP);
static_assert(offsetof(struct mpart, mp_blkst_ptr) == OFFSET_MPART_BLKST_PTR);
static_assert(offsetof(struct mpart, mp_blkst_inl) == OFFSET_MPART_BLKST_INL);
static_assert(offsetof(struct mpart, mp_mem) == OFFSET_MPART_MEM);
static_assert(offsetof(struct mpart, mp_mem) == OFFSET_MPART_MEM);
static_assert(offsetof(struct mpart, mp_mem_sc) == OFFSET_MPART_MEM_SC);
static_assert(offsetof(struct mpart, mp_swp) == OFFSET_MPART_SWP);
static_assert(offsetof(struct mpart, mp_swp_sc) == OFFSET_MPART_SWP_SC);
static_assert(offsetof(struct mpart, mp_meta) == OFFSET_MPART_META);
#ifdef OFFSET_MPART___PAD
static_assert(offsetof(struct mpart, __mp_pad) == OFFSET_MPART___PAD);
#endif /* OFFSET_MPART___PAD */
static_assert(sizeof(struct mpart) == SIZEOF_MPART);
static_assert(alignof(struct mpart) == ALIGNOF_MPART);



#ifndef NDEBUG
/* Assert the integrity of the given mem-part and associated nodes.
 * The caller must be holding a lock to `self'. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_assert_integrity)(struct mpart *__restrict self) {
	size_t size;
	assert(mpart_lock_acquired(self));
	assertf((self->mp_flags & MPART_F_COREPART) || kmalloc_islocked(self),
	        "Descriptor of mem-part at %p is not locked into memory", self);
	assert(self->mp_refcnt != 0);
	assertf(self->mp_maxaddr + 1 >= self->mp_minaddr ||
	        self->mp_maxaddr == (pos_t)-1,
	        "Invalid min/max addr range:\n"
	        "self->mp_minaddr = %#" PRIxN(__SIZEOF_POS_T__) "\n"
	        "self->mp_maxaddr = %#" PRIxN(__SIZEOF_POS_T__) "\n",
	        self->mp_minaddr, self->mp_maxaddr);
	size = mpart_getsize(self);
#if __SIZEOF_SIZE_T__ < __SIZEOF_POS_T__
	assertf(self->mp_minaddr + size - 1 == self->mp_maxaddr,
	        "Size too large:\n"
	        "self->mp_minaddr = %#" PRIxN(__SIZEOF_POS_T__) "\n"
	        "self->mp_maxaddr = %#" PRIxN(__SIZEOF_POS_T__) "\n"
	        "size = %#" PRIxSIZ "\n"
	        "size = %#" PRIxN(__SIZEOF_POS_T__) " (actual)\n",
	        self->mp_minaddr, self->mp_maxaddr,
	        size, (self->mp_maxaddr - self->mp_minaddr) + 1);
#endif /* __SIZEOF_SIZE_T__ < __SIZEOF_POS_T__ */
	assertf(IS_ALIGNED(size, PAGESIZE),
	        "Part size %#" PRIxSIZ " isn't page-aligned", size);
	switch (self->mp_state) {

	case MPART_ST_SWP:
	case MPART_ST_MEM:
		assertf((size / PAGESIZE) == self->mp_mem.mc_size,
		        "Part size %#" PRIxSIZ " doesn't match mem size %#" PRIx64,
		        size, (u64)self->mp_mem.mc_size * PAGESIZE);
		break;

#ifdef LIBVIO_CONFIG_ENABLED
	case MPART_ST_VIO:
		break;
#endif /* LIBVIO_CONFIG_ENABLED */

	case MPART_ST_SWP_SC:
	case MPART_ST_MEM_SC: {
		size_t i;
		physpagecnt_t total_size = 0;
		for (i = 0; i < self->mp_mem_sc.ms_c; ++i) {
			if (OVERFLOW_UADD(total_size,
			                  self->mp_mem_sc.ms_v[i].mc_size,
			                  &total_size))
				assert_failed("Part size overflow");
		}
		assertf((size / PAGESIZE) == total_size,
		        "Part size %#" PRIxSIZ " doesn't match mem size %#" PRIx64,
		        size, (u64)total_size * PAGESIZE);
	}	break;

	default:
		assertf(self->mp_state == MPART_ST_VOID,
		        "Invalid state: %u",
		        (unsigned int)self->mp_state);
	}

	/* Assert that mem-node access ranges are all in-bounds. */
	{
		unsigned int i;
		for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
			struct mnode *node;
			LIST_FOREACH (node, &self->_mp_nodlsts[i], mn_link) {
				byte_t *minaddr, *maxaddr;
				mpart_reladdr_t part_minaddr;
				mpart_reladdr_t part_maxaddr;
				size_t node_size;
				REF struct mman *mm;
				if (atomic_read(&node->mn_flags) & MNODE_F_UNMAPPED)
					continue; /* Allow bad values for unmapped nodes. */
				mm = node->mn_mman;
				if (!tryincref(mm))
					continue; /* Allow bad values for dead mmans. */
				minaddr      = node->mn_minaddr;
				maxaddr      = node->mn_maxaddr;
				part_minaddr = node->mn_partoff;
				COMPILER_READ_BARRIER();
				assertf(node->mn_part == self,
				        "Node uses incorrect mem-part:\n"
				        "iter->mn_part = %p\n"
				        "self          = %p\n",
				        node->mn_part, self);
				assertf(maxaddr >= minaddr,
				        "Invalid min/max addr bounds:\n"
				        "minaddr = %p\n"
				        "maxaddr = %p\n",
				        minaddr, maxaddr);
				assertf(IS_ALIGNED((uintptr_t)minaddr, PAGESIZE),
				        "Unaligned minaddr %p", minaddr);
				assertf(IS_ALIGNED((uintptr_t)maxaddr + 1, PAGESIZE),
				        "Unaligned maxaddr %p", maxaddr);
				node_size = (size_t)(maxaddr - minaddr) + 1;
				if (OVERFLOW_UADD(part_minaddr, node_size - 1, &part_maxaddr)) {
					assert_failed("Mapped part range overflows\n"
					              "part_minaddr = %#" PRIxSIZ "\n"
					              "node_size    = %#" PRIxSIZ "\n",
					              part_minaddr, node_size);
				}
				assertf(part_maxaddr <= size - 1,
				        "Mem-node mapping is out-of-bounds:\n"
				        "Node address range: %p-%p\n"
				        "Node part range:    %#" PRIxSIZ "-%#" PRIxSIZ "\n"
				        "Valid part range:   0x0-%#" PRIxSIZ "\n",
				        minaddr, maxaddr, part_minaddr,
				        part_maxaddr, size - 1);
				decref_unlikely(mm);
			}
		}
	}
}
#endif /* !NDEBUG */



/* Reference counting control for `struct mpart' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_free)(struct mpart *__restrict self) {
	if (self->mp_flags & MPART_F_COREPART) {
		mcoreheap_free(container_of(self, union mcorepart, mcp_part));
	} else {
		kfree(self);
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mchunk_freemem)(struct mchunk *__restrict self) {
	page_free(self->mc_start, self->mc_size);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mchunk_freeswp)(struct mchunk *__restrict self) {
	swap_free(self->mc_start, self->mc_size);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mchunkvec_freemem)(struct mchunk *__restrict vec, size_t count) {
	size_t i;
	for (i = 0; i < count; ++i)
		mchunk_freemem(&vec[i]);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mchunkvec_freeswp)(struct mchunk *__restrict vec, size_t count) {
	size_t i;
	for (i = 0; i < count; ++i)
		mchunk_freeswp(&vec[i]);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_fini)(struct mpart *__restrict self) {
	/* If valid, free the block-status extension vector. */
	if (!(self->mp_flags & MPART_F_BLKST_INL))
		kfree(self->mp_blkst_ptr);

	/* Free state-specific data. */
	switch (self->mp_state) {

	case MPART_ST_SWP:
		if (!(self->mp_flags & MPART_F_NOFREE))
			mchunk_freeswp(&self->mp_swp);
		break;

	case MPART_ST_MEM:
		if (!(self->mp_flags & MPART_F_NOFREE))
			mchunk_freemem(&self->mp_mem);
		break;

	case MPART_ST_SWP_SC:
		if (!(self->mp_flags & MPART_F_NOFREE))
			mchunkvec_freeswp(self->mp_swp_sc.ms_v, self->mp_swp_sc.ms_c);
		kfree(self->mp_swp_sc.ms_v);
		break;

	case MPART_ST_MEM_SC:
		if (!(self->mp_flags & MPART_F_NOFREE))
			mchunkvec_freemem(self->mp_mem_sc.ms_v, self->mp_mem_sc.ms_c);
		kfree(self->mp_mem_sc.ms_v);
		break;

	default:
		break;
	}
	if (self->mp_meta) {
		/* Free mem-part meta-data. */
		mpartmeta_destroy(self->mp_meta);
	}
}


#define mpart_destroy_lockop_encode(prt)          ((struct lockop *)&(prt)->mp_blkst_ptr)
#define mpart_destroy_lockop_decode(lop)          container_of((uintptr_t **)(lop), struct mpart, mp_blkst_ptr)
#define mpart_destroy_postlockop_encode(prt)      ((struct postlockop *)&(prt)->mp_blkst_ptr)
#define mpart_destroy_postlockop_decode(lop)      container_of((uintptr_t **)(lop), struct mpart, mp_blkst_ptr)
#define mpart_destroy_mfilelockop_encode(prt)     ((Toblockop(mfile) *)&(prt)->mp_blkst_ptr)
#define mpart_destroy_mfilelockop_decode(lop)     container_of((uintptr_t **)(lop), struct mpart, mp_blkst_ptr)
#define mpart_destroy_mfilepostlockop_encode(prt) ((Tobpostlockop(mfile) *)&(prt)->mp_blkst_ptr)
#define mpart_destroy_mfilepostlockop_decode(lop) container_of((uintptr_t **)(lop), struct mpart, mp_blkst_ptr)

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_destroy_postlop_rmall_async)(struct postlockop *__restrict self) {
	struct mpart *me;
	me = mpart_destroy_postlockop_decode(self);
	mpart_free(me);
}

INTERN NOBLOCK NONNULL((1)) struct postlockop * /* INTERN: Used in "mnode-merge.c" */
NOTHROW(FCALL mpart_destroy_lop_rmall_async)(struct lockop *__restrict self) {
	struct postlockop *plop;
	struct mpart *me;
	me = mpart_destroy_lockop_decode(self);

	/* Remove the part from the all-parts list. */
	COMPILER_READ_BARRIER();
	if (TAILQ_ISBOUND(me, mp_allparts))
		_mpart_all_list_remove(me);

	/* Call mpart_free() once the caller has released their lock to `mpart_all_lock' */
	plop           = mpart_destroy_postlockop_encode(me);
	plop->plo_func = &mpart_destroy_postlop_rmall_async;
	return plop;
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mpart_destroy_lop_rmall)(Tobpostlockop(mfile) *__restrict self,
                                       struct mfile *__restrict UNUSED(file)) {
	struct mpart *me;
	me = mpart_destroy_mfilelockop_decode(self);
	if (TAILQ_ISBOUND(me, mp_allparts)) {
		/* Must remove from the global list of all known parts. */
		if (mpart_all_tryacquire()) {
			COMPILER_READ_BARRIER();
			if (TAILQ_ISBOUND(me, mp_allparts))
				_mpart_all_list_remove(me);
			mpart_all_release();
		} else {
			struct lockop *lop;
			lop          = mpart_destroy_lockop_encode(me);
			lop->lo_func = &mpart_destroy_lop_rmall_async;
			SLIST_ATOMIC_INSERT(&mpart_all_lops, lop, lo_link);
			_mpart_all_reap();
			return;
		}
	}

	/* Finally, free the part proper. */
	mpart_free(me);
}

PRIVATE NOBLOCK NONNULL((1, 2)) Tobpostlockop(mfile) *
NOTHROW(FCALL mpart_destroy_lop_rmfile)(Toblockop(mfile) *__restrict self,
                                        struct mfile *__restrict file) {
	Tobpostlockop(mfile) *post;
	struct mpart *me;
	me = mpart_destroy_mfilelockop_decode(self);

	/* Remove the dead part from the file's tree of parts. */
	if likely(!mpart_isanon(me)) {
		assert(!mfile_isanon(file));
		mpart_tree_removenode(&file->mf_parts, me);
	}
	DBG_memset(&me->mp_filent, 0xcc, sizeof(me->mp_filent));
	post = mpart_destroy_mfilepostlockop_encode(me);

	/* Remove from the all-parts list and free _after_ the
	 * lock  to  the backing  mem-file has  been released. */
	post->oplo_func = &mpart_destroy_lop_rmall;
	return post;
}



PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_destroy)(struct mpart *__restrict self) {
	REF struct mfile *file;
	mpart_fini(self);
	file = self->mp_file;
	assert(file);
	if (mpart_isanon(self)) {
		/* No need to unlink from the file. - The file's tree was deleted! */
remove_node_from_globals:
		if (TAILQ_ISBOUND(self, mp_allparts)) {
			/* Must remove from the global list of all known parts. */
			if (mpart_all_tryacquire()) {
				COMPILER_READ_BARRIER();
				if (TAILQ_ISBOUND(self, mp_allparts))
					_mpart_all_list_remove(self);
				mpart_all_release();
			} else {
				struct lockop *lop;
				lop          = mpart_destroy_lockop_encode(self);
				lop->lo_func = &mpart_destroy_lop_rmall_async;
				SLIST_ATOMIC_INSERT(&mpart_all_lops, lop, lo_link);
				_mpart_all_reap();
				return;
			}
		}
	} else if (mfile_lock_trywrite(file)) {
		/* Immediately remove the part from the associated file's tree. */
		if likely(!mpart_isanon(self)) {
			assert(!mfile_isanon(file));
			mpart_tree_removenode(&file->mf_parts, self);
		}
		mfile_lock_endwrite(file);
		DBG_memset(&self->mp_filent, 0xcc, sizeof(self->mp_filent));
		goto remove_node_from_globals;
	} else {
		/* Enqueue the file for later deletion. */
		Toblockop(mfile) *lop;
		lop = mpart_destroy_mfilelockop_encode(self);
		lop->olo_func = &mpart_destroy_lop_rmfile;
		SLIST_ATOMIC_INSERT(&file->mf_lockops, lop, olo_link);
		_mfile_lockops_reap(file);
		decref(file);
		return;
	}
	decref(file);
	mpart_free(self);
}

SLIST_HEAD(mpart_postlockop_slist, Tobpostlockop(mpart));

/* Reap dead nodes of `self' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _mpart_lockops_reap)(struct mpart *__restrict self) {
	Toblockop_slist(mpart) lops;
	struct mpart_postlockop_slist post;
	Toblockop(mpart) *iter;
	if (!mpart_lock_tryacquire(self))
		return;
	SLIST_INIT(&post);
again_steal_and_service_lops:
	lops.slh_first = SLIST_ATOMIC_CLEAR(&self->mp_lockops);
again_service_lops:
	iter = SLIST_FIRST(&lops);
	while (iter != NULL) {
		Toblockop(mpart) *next;
		Tobpostlockop(mpart) *later;
		next = SLIST_NEXT(iter, olo_link);

		/* Invoke the lock operation. */
		later = (*iter->olo_func)(iter, self);

		/* Enqueue operations for later execution. */
		if (later != NULL)
			SLIST_INSERT(&post, later, oplo_link);
		iter = next;
	}
	_mpart_lock_release(self);

	/* Check for more operations. */
	lops.slh_first = SLIST_ATOMIC_CLEAR(&self->mp_lockops);
	if unlikely(!SLIST_EMPTY(&lops)) {
		if likely(mpart_lock_tryacquire(self))
			goto again_service_lops;

		/* re-queue all stolen lops. */
		iter = SLIST_FIRST(&lops);
		while (SLIST_NEXT(iter, olo_link))
			iter = SLIST_NEXT(iter, olo_link);
		SLIST_ATOMIC_INSERT_R(&self->mp_lockops,
		                      SLIST_FIRST(&lops),
		                      iter, olo_link);
		if unlikely(mpart_lock_tryacquire(self))
			goto again_steal_and_service_lops;
	}

	/* Run all enqueued post-operations. */
	while (!SLIST_EMPTY(&post)) {
		Tobpostlockop(mpart) *op;
		op = SLIST_FIRST(&post);
		SLIST_REMOVE_HEAD(&post, oplo_link);
		(*op->oplo_func)(op, self);
	}
}



/* Mem-part tree API. All of these functions require that the caller
 * be holding a lock to the associated file. */
DECL_END

#undef RBTREE_LEFT_LEANING
#define RBTREE_WANT_MINMAXLOCATE
#define RBTREE_WANT_PREV_NEXT_NODE
#define RBTREE_WANT_RREMOVE
#define RBTREE_WANT_RLOCATE
#define RBTREE_WANT_TRYINSERT
#define RBTREE_MINMAX_T_DEFINED
#define mpart_tree_minmax_t    struct mpart_tree_minmax
#define RBTREE(name)           mpart_tree_##name
#define RBTREE_T               struct mpart
#define RBTREE_Tkey            pos_t
#define RBTREE_GETNODE(self)   (self)->mp_filent
#define RBTREE_GETMINKEY(self) mpart_getminaddr(self)
#define RBTREE_GETMAXKEY(self) mpart_getmaxaddr(self)
#define RBTREE_ISRED(self)     (atomic_read(&(self)->mp_flags) & MPART_F__RBRED)
#define RBTREE_SETRED(self)    atomic_or(&(self)->mp_flags, MPART_F__RBRED)
#define RBTREE_SETBLACK(self)  atomic_and(&(self)->mp_flags, ~MPART_F__RBRED)
#define RBTREE_FLIPCOLOR(self) atomic_xor(&(self)->mp_flags, MPART_F__RBRED)
#define RBTREE_CC              FCALL
#define RBTREE_NOTHROW         NOTHROW
#define RBTREE_DECL            FUNDEF
#define RBTREE_IMPL            PUBLIC
#include <hybrid/sequence/rbtree-abi.h>

DECL_BEGIN

/* Get/Set the state of the index'd block `partrel_block_index' from the part's block-state bitset.
 * NOTE: The caller is responsible to ensure that `partrel_block_index' is
 *       located in-bounds.
 * NOTE: The caller must be holding a lock to `self', unless the intend is to
 *       change the state of a  block that used to be  `MPART_BLOCK_ST_INIT',
 *       in which case `mpart_setblockstate()' may be called without  holding
 *       a lock to `self'
 *       But also note that after transitioning away from `MPART_BLOCK_ST_INIT',
 *       the caller must  broadcast the  `mf_initdone' signal of  the file  that
 *       was used to initialize the part.
 * NOTE: When  calling  `mpart_setblockstate()'  to  set  `MPART_BLOCK_ST_INIT',
 *       then the caller is also responsible to set the `MPART_F_MAYBE_BLK_INIT'
 *       flag! But  note that  that flag  should  _NOT_ be  cleared by  the  one
 *       who  originally  set  it,  since  other  (unrelated)  blocks  may exist
 *       that still make use of the `MPART_BLOCK_ST_CHNG' state!
 * @param: st:  One of `MPART_BLOCK_ST_*'
 * @return: * : *ditto* */
PUBLIC NOBLOCK ATTR_PURE NONNULL((1)) unsigned int
NOTHROW(FCALL mpart_getblockstate)(struct mpart const *__restrict self,
                                   size_t partrel_block_index) {
	mpart_blkst_word_t word;
	shift_t shift;

	/* We're called from `mpart_hinted_mmap()', so we can't assert the lock! */
	/*assert(mpart_lock_acquired(self));*/
	assertf(partrel_block_index < mpart_getblockcount(self, self->mp_file),
	        "Block index %" PRIuSIZ " is out-of-bounds of 0-%" PRIuSIZ,
	        partrel_block_index, mpart_getblockcount(self, self->mp_file) - 1);
	if (self->mp_flags & MPART_F_BLKST_INL) {
		word = atomic_read(&self->mp_blkst_inl);
	} else {
		size_t index;
		assertf(self->mp_blkst_ptr, "Caller did not verify that `mpart_hasblockstate(self)'");
		index = partrel_block_index / MPART_BLKST_BLOCKS_PER_WORD;
		word  = atomic_read(&self->mp_blkst_ptr[index]);
	}
	shift = (shift_t)((partrel_block_index % MPART_BLKST_BLOCKS_PER_WORD) * MPART_BLOCK_STBITS);
	return (unsigned int)(word >> shift) & (((unsigned int)1 << MPART_BLOCK_STBITS) - 1);
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_setblockstate)(struct mpart *__restrict self,
                                   size_t partrel_block_index,
                                   unsigned int st) {
	mpart_blkst_word_t *pword, mask, val, oldval, newval;
	shift_t shift;
	assertf(partrel_block_index < mpart_getblockcount(self, self->mp_file),
	        "Block index %" PRIuSIZ " is out-of-bounds of 0-%" PRIuSIZ,
	        partrel_block_index, mpart_getblockcount(self, self->mp_file) - 1);
	assert(st < ((unsigned int)1 << MPART_BLOCK_STBITS));
	shift = (shift_t)((partrel_block_index % MPART_BLKST_BLOCKS_PER_WORD) * MPART_BLOCK_STBITS);
	mask  = (mpart_blkst_word_t)((1 << MPART_BLOCK_STBITS) - 1) << shift;
	val   = (mpart_blkst_word_t)st << shift;
	if (self->mp_flags & MPART_F_BLKST_INL) {
		pword = &self->mp_blkst_inl;
	} else {
		size_t index;
		assertf(self->mp_blkst_ptr, "Caller did not verify that `mpart_hasblockstate(self)'");
		index = partrel_block_index / MPART_BLKST_BLOCKS_PER_WORD;
		pword = &self->mp_blkst_ptr[index];
	}
	do {
		oldval = atomic_read(pword);
		newval = (oldval & ~mask) | val;
	} while (!atomic_cmpxch_weak(pword, oldval, newval));
}

PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_setblockstate_r)(struct mpart *__restrict self,
                                     size_t partrel_block_index_start,
                                     size_t partrel_block_index_end,
                                     unsigned int st) {
	size_t i;
	assert(partrel_block_index_start <= partrel_block_index_end);
	/* TODO: This can probably be done more efficiently. */
	for (i = partrel_block_index_start; i < partrel_block_index_end; ++i)
		mpart_setblockstate(self, i, st);
}


FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_setblockstate_r_from_dbg)(struct mpart *__restrict self,
                                              size_t partrel_block_index_start,
                                              size_t partrel_block_index_end,
                                              unsigned int old_st,
                                              unsigned int st);
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_setblockstate_r_from_dbg)(struct mpart *__restrict self,
                                              size_t partrel_block_index_start,
                                              size_t partrel_block_index_end,
                                              unsigned int old_st,
                                              unsigned int st) {
#ifndef NDEBUG
	size_t i;
	for (i = partrel_block_index_start; i < partrel_block_index_end; ++i) {
		unsigned int real_old_st;
		real_old_st = mpart_getblockstate(self, i);
		assertf(real_old_st == old_st,
		        "Wrong old status from block %" PRIuSIZ " of range "
		        "%" PRIuSIZ "-%" PRIuSIZ " (expected: %u, actual: %u)",
		        i, partrel_block_index_start, partrel_block_index_end - 1,
		        old_st, real_old_st);
	}
#endif /* !NDEBUG */
	(void)old_st;
	mpart_setblockstate_r(self, partrel_block_index_start, partrel_block_index_end, st);
}


PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _mpart_setblockstate_initdone_extrahooks)(REF struct mpart *__restrict self)
		ASMNAME("mpart_setblockstate_initdone_extrahooks");
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL _mpart_setblockstate_initdone_extrahooks)(REF struct mpart *__restrict self) {
	uintptr_quarter_t actions;
	actions = atomic_fetchadd(&self->mp_xflags, ~(MPART_XF_MERGE_AFTER_INIT |
	                                              MPART_XF_TRIM_AFTER_INIT));
	actions &= (MPART_XF_MERGE_AFTER_INIT | MPART_XF_TRIM_AFTER_INIT);
	switch (actions) {

	case MPART_XF_MERGE_AFTER_INIT | MPART_XF_TRIM_AFTER_INIT:
		mpart_trim(incref(self));
		decref(mpart_merge(self));
		break;

	case MPART_XF_MERGE_AFTER_INIT:
		decref(mpart_merge(self));
		break;

	case MPART_XF_TRIM_AFTER_INIT:
		mpart_trim(self);
		break;

	case 0:
		decref(self);
		break;

	default: __builtin_unreachable();
	}
}


/* Check if the given mem-part contains blocks with `MPART_BLOCK_ST_INIT'.
 * For this purpose, if the `MPART_F_MAYBE_BLK_INIT' flag isn't set,  then
 * this function immediately returns `false'.
 * Otherwise, all blocks of the part are searched, and if one is found that
 * uses the `MPART_BLOCK_ST_INIT'  state, return  `true'. Otherwise,  clear
 * the `MPART_F_MAYBE_BLK_INIT' flag and return `false'.
 * NOTE: The caller must be holding a lock to `self' */
PUBLIC NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL mpart_hasblocksstate_init)(struct mpart *__restrict self) {
	size_t i, count;
	assert(mpart_lock_acquired(self));
	if (!(self->mp_flags & MPART_F_MAYBE_BLK_INIT))
		return false;

	/* Manually check all of the blocks. */
	count = mpart_getblockcount(self, self->mp_file);
	for (i = 0; i < count; ++i) {
		unsigned int st;
		st = mpart_getblockstate(self, i);
		if (st == MPART_BLOCK_ST_INIT)
			return true; /* Yup! There are INIT-parts... */
	}

	/* No INIT-part found (just clear the MAYBE_BLK_INIT flag) */
	atomic_and(&self->mp_flags, ~MPART_F_MAYBE_BLK_INIT);
	return false;
}


/* Sync changes made to the given mem-part.
 * @return: * : The total # of bytes that were synced.
 * NOTE: The caller is responsible for adding/removing the part to/from
 *       the associated file's list of changed parts! */
PRIVATE BLOCKING NONNULL((1)) size_t FCALL
mpart_sync_impl(struct mpart *__restrict self, bool keep_lock)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	size_t result = 0;
	struct mfile *file;
	size_t start, block_count;
	bool has_initializing_parts;
	assert(!task_wasconnected());

	/* Deal with the special case where our part is a VIO-part. */
#ifdef LIBVIO_CONFIG_ENABLED
	if unlikely(self->mp_state == MPART_ST_VIO)
		goto done_noop_nolock;
#endif /* LIBVIO_CONFIG_ENABLED */

again:
	if (!(self->mp_flags & MPART_F_CHANGED) && !keep_lock)
		goto done_noop_nolock;

	/* Lock the part, load it into the core, make sure that  anyone
	 * that might have write-access  right now has this  permission
	 * revoked, and that there aren't any DMA operation in-process. */
	/* XXX: It would be nice if we could differentiate between read-
	 *      and write- DMA operations, and  only wait for write  DMA
	 *      operations here. - In practice,  we don't have to  worry
	 *      about anyone reading memory in the mean time... */
	mpart_lock_acquire_and_setcore_denywrite_nodma(self);

	if (!(self->mp_flags & MPART_F_CHANGED))
		goto done_noop;

	/* Note: For our purposes, we can assume that no-one else  will
	 *       be able to make modifications to our mem-part, or  set
	 *       the CHANGED flag once again until we release our lock!
	 * The case of the 1 remaining copy-on-write mapping with write
	 * access may be ignored for our purpose! */
	file = self->mp_file;

	/* Make sure that the underlying file actually provides us with
	 * the means of writing back changes */
	if unlikely(file->mf_ops->mo_saveblocks == NULL)
		goto done_noop;

	/* Verify that the file hasn't been/is-being deleted.
	 * NOTE: The DELETING-flag won't change status since we're holding the lock to a pre-existing part. */
	{
		uintptr_t file_flags = atomic_read(&file->mf_flags);
		if unlikely(file_flags & (MFILE_F_DELETING | MFILE_F_DELETED)) {
			if (file_flags & MFILE_F_DELETING) {
				incref(file);
				mpart_lock_release(self);
				FINALLY_DECREF_UNLIKELY(file);
				mfile_deleting_waitfor(file);
				goto again;
			}
			/* If the file was deleted, we have no way of writing changes to disk. */
			goto done_noop;
		}
	}

	/* Figure out how many individual blocks are contained by this part. */
	block_count = mpart_getblockcount(self, file);

	/* Make sure that the block-state-bitset is writable. */
	if unlikely(!mpart_hasblockstate(self)) {
		/* Not writable means that the mem-part uses HEAP-based+NULL-alloc, which
		 * means  that currently all  blocks are considered `MPART_BLOCK_ST_CHNG'
		 *
		 * This is unlikely to happen, but is a well-defined scenario. */
		if (block_count <= MPART_BLKST_BLOCKS_PER_WORD) {
			/* Just use the in-line bitset. */
			self->mp_blkst_inl = MPART_BLOCK_REPEAT(MPART_BLOCK_ST_CHNG);
			atomic_or(&self->mp_flags, MPART_F_BLKST_INL);
		} else {
			size_t bitset_words;
			size_t bitset_size;
			mpart_blkst_word_t *bitset;

			/* Must allocate the bitset on the heap! */
			bitset_words = CEILDIV(block_count, MPART_BLKST_BLOCKS_PER_WORD);
			bitset_size  = bitset_words * sizeof(mpart_blkst_word_t);
			bitset = (mpart_blkst_word_t *)kmalloc_nx(bitset_size,
			                                          GFP_ATOMIC | GFP_LOCKED |
			                                          GFP_PREFLT);
			if unlikely(!bitset) {
				/* Must allocate the new bitset while blocking! */
				mpart_lock_release(self);
				bitset = (mpart_blkst_word_t *)kmalloc(bitset_size, GFP_LOCKED | GFP_PREFLT);
				TRY {
					mpart_lock_acquire_and_setcore_denywrite_nodma(self);
				} EXCEPT {
					kfree(bitset);
					RETHROW();
				}

				/* Check if anything's changed. */
				if unlikely(!(self->mp_flags & MPART_F_CHANGED) ||
				            file != self->mp_file ||
				            block_count != mpart_getblockcount(self, file) ||
				            mpart_hasblockstate(self)) {
					_mpart_lock_release(self);
					kfree(bitset);
#ifndef __OPTIMIZE_SIZE__
					mpart_lockops_reap(self);
#endif /* !__OPTIMIZE_SIZE__ */
					goto again;
				}

				/* Nothing's changed, so we can just write-back the new bitset. */
			}

			/* Initialize the bitset. */
			memsetc(bitset, MPART_BLOCK_REPEAT(MPART_BLOCK_ST_CHNG),
			        bitset_words, sizeof(mpart_blkst_word_t));

			/* Write-back the bitset. */
			self->mp_blkst_ptr = bitset;
		}
	}

	/* At this point, we know that there are changes, and we've made sure that
	 * the  block-state bitset is writable (in case it wasn't writable before) */
	assert(self->mp_state == MPART_ST_MEM ||
	       self->mp_state == MPART_ST_MEM_SC);

	/* Scan for continuous segments of changed blocks. */
	has_initializing_parts = false;
	for (start = 0; start < block_count; ++start) {
		unsigned int st;
		size_t end;
		struct mpart_physloc loc;
		st = mpart_getblockstate(self, start);
		if (st != MPART_BLOCK_ST_CHNG) {
			/* Part hasn't been changed. */
			if (st == MPART_BLOCK_ST_INIT)
				has_initializing_parts = true;
			continue;
		}

		/* Figure out the  max continuous physical  memory range  that
		 * can be used to describe memory starting at the lo'th block. */
		mpart_memaddr_direct(self, start << file->mf_blockshift, &loc);
		assert(loc.mppl_size >= mfile_getblocksize(file));

		/* Figure out the max hi-block that is still contained with
		 * the   physical   memory   range   described   by   `loc' */
		block_count = start + (loc.mppl_size >> file->mf_blockshift);
		assert(block_count >= start);
		assert(block_count <= mpart_getblockcount(self, file));

		/* Alter the state of changed parts to INIT, thus essentially
		 * locking them in-memory until we're down writing them  back
		 * to disk, or wherever else they should go. */
		for (end = start + 1;;) {
			mpart_setblockstate(self, end - 1, MPART_BLOCK_ST_INIT);
			if (end >= block_count)
				break; /* The next block would no longer be apart of the containing chunk. */
			st = mpart_getblockstate(self, end);
			if (st != MPART_BLOCK_ST_CHNG)
				break; /* The next block is no longer marked as changed. */
			++end;
		}

		/* Now to do the actual work: */
		incref(file);
		mfile_trunclock_inc_locked(file);
		atomic_or(&self->mp_flags, MPART_F_MAYBE_BLK_INIT);
		_mpart_lock_release(self);
		TRY {
			pos_t addr, filesize;
			size_t num_bytes;

			/* Account for synced pages. */
			addr      = self->mp_minaddr + (start << file->mf_blockshift);
			num_bytes = (end - start) << file->mf_blockshift;

			filesize = mfile_getsize(file);
			if (!OVERFLOW_UADD(filesize, file->mf_part_amask, &filesize)) {
				filesize = mfile_partaddr_flooralign(file, filesize);
				/* Limit the write-back address range by the size of the file,
				 * or do nothing if the entirety of said range lies outside of
				 * the file's effective bounds. */
				if unlikely(addr + num_bytes > filesize) {
					if (addr >= filesize)
						goto done_writeback;
					num_bytes = (size_t)(filesize - addr);
				}
			}

			/* Actually do the save. */
			result += num_bytes;
			mfile_dosyncio(file, file->mf_ops->mo_saveblocks,
			               addr, loc.mppl_addr, num_bytes);
		} EXCEPT {
			/* The write-back failed. - As such we must restore the ST_CHNG status
			 * of all of the pages we've altered to INIT, as well as broadcast the
			 * init-done signal of the associated file. */
			mpart_setblockstate_r(self, start, end, MPART_BLOCK_ST_CHNG);
			mfile_trunclock_dec_nosignal(file);
			sig_broadcast(&file->mf_initdone);
			mpart_setblockstate_initdone_extrahooks(self);
			decref_unlikely(file);
			mpart_lockops_reap(self);
			RETHROW();
		}
done_writeback:

		/* Change the states of all saved pages back to ST_LOAD */
		mpart_setblockstate_r(self, start, end, MPART_BLOCK_ST_LOAD);
		mfile_trunclock_dec_nosignal(file);
		sig_broadcast(&file->mf_initdone);
		mpart_setblockstate_initdone_extrahooks(self);
		decref_unlikely(file);

		/* Scan for more changes. */
		goto again;
	}
	if unlikely(has_initializing_parts) {
		incref(file);
		_mpart_lock_release(self);
#ifndef __OPTIMIZE_SIZE__
		mpart_lockops_reap(self);
#endif /* !__OPTIMIZE_SIZE__ */

		/* Wait until parts that are being initialized finish doing that. */
		TRY {
			{
				FINALLY_DECREF_UNLIKELY(file);
				task_connect(&file->mf_initdone);
				TRY {
					mpart_lock_acquire(self);
				} EXCEPT {
					task_disconnectall();
					RETHROW();
				}

				/* Check for init-parts once again. */
				if unlikely(!mpart_hasblocksstate_init(self)) {
					_mpart_lock_release(self);
					task_disconnectall();
#ifndef __OPTIMIZE_SIZE__
					mpart_lockops_reap(self);
#endif /* !__OPTIMIZE_SIZE__ */
					goto again;
				}
				mpart_lock_release(self);
			}

			/* Wait for initialization to complete. */
			task_waitfor();
		} EXCEPT {
			mpart_lockops_reap(self);
			RETHROW();
		}

		/* Try again. (hopefully now, all INIT-blocks are gone) */
		goto again;
	}

	/* Clear the LOCK-bit and CHANGED-flag at the same time! :)
	 * Also  clear the the `MPART_F_MAYBE_BLK_INIT' flag, since
	 * we're handling that case as well (see above) */
	if (keep_lock) {
		atomic_and(&self->mp_flags, ~(MPART_F_CHANGED | MPART_F_MAYBE_BLK_INIT));
		return result;
	}
	atomic_and(&self->mp_flags, ~(MPART_F_LOCKBIT | MPART_F_CHANGED |
	                             MPART_F_MAYBE_BLK_INIT));
	mpart_lockops_reap(self);
	return result;
done_noop:
	if (keep_lock)
		return result;
	mpart_lock_release(self);
	return result;
done_noop_nolock:
	if (keep_lock)
		mpart_lock_acquire_and_setcore_denywrite_nodma(self);
	return result;
}

/* Sync changes made to the given mem-part.
 * @return: * : The total # of bytes that were synced.
 * NOTE: The caller is responsible for adding/removing the part to/from
 *       the associated file's list of changed parts! */
PUBLIC BLOCKING NONNULL((1)) size_t FCALL
mpart_sync(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	return mpart_sync_impl(self, false);
}

/* Same as `mpart_sync()', but keep on holding onto the lock to `self' */
PUBLIC BLOCKING NONNULL((1)) size_t FCALL
mpart_lock_acquire_and_setcore_denywrite_sync(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	return mpart_sync_impl(self, true);
}




/* Check if the given `addr...+=num_bytes' sub-range (which _must_ be
 * entirely  contained within the portion of `self' that is mapped by
 * the given `node')  can be given  write-access by `node',  assuming
 * that `node' is a copy-on-write mapping of `self'.
 *
 * For this purpose, direct write-access is only granted when the given
 * sub-range is not visible anywhere else (iow: when `node' effectively
 * has exclusive ownership over that range):
 *   - mpart_isanon(self)                                     // The part must be anon (else: changes would
 *                                                            // be visible when read(2)-ing from its file)
 *   - self->mp_share.filter(MAPS(addr, num_bytes)) == []     // No shared memory mappings
 *   - self->mp_copy .filter(MAPS(addr, num_bytes)) == [node] // Exactly 1 copy-on-write mapping, that is `node' */
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1, 4)) bool
NOTHROW(FCALL _mpart_iscopywritable)(struct mpart const *__restrict self,
                                     mpart_reladdr_t addr, size_t num_bytes,
                                     struct mnode const *__restrict node) {
	unsigned int i;
	/* Check  for _any_ nodes that overlap with the
	 * given address range, that aren't just `node' */
	for (i = 0; i < lengthof(self->_mp_nodlsts); ++i) {
		struct mnode *iter;
		LIST_FOREACH (iter, &self->_mp_nodlsts[i], mn_link) {
			if (!RANGE_OVERLAPS(addr, addr + num_bytes,
			                    mnode_getpartaddr(iter),
			                    mnode_getpartendaddr(iter)))
				continue; /* No overlap here! */
			if (iter == node)
				continue; /* This one's allowed! */
			return false; /* oops: overlap! */
		}
	}
	return true; /* Everything OK! */
}

/* Check if there are no copy-on-write nodes for the given address range
 * This must be ensured before shared write-access can be granted to the
 * specified  range, and if this isn't the case, the copy-on-write nodes
 * for said range must be unshared via `mpart_unsharecow_or_unlock()' */
FUNDEF NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL _mpart_issharewritable)(struct mpart const *__restrict self,
                                      mpart_reladdr_t addr, size_t num_bytes)
		ASMNAME("mpart_issharewritable");
PUBLIC NOBLOCK ATTR_PURE WUNUSED NONNULL((1)) bool
NOTHROW(FCALL _mpart_issharewritable)(struct mpart const *__restrict self,
                                      mpart_reladdr_t addr, size_t num_bytes) {
	struct mnode *iter;
	LIST_FOREACH (iter, &self->mp_copy, mn_link) {
		if (RANGE_OVERLAPS(addr, addr + num_bytes,
		                   mnode_getpartaddr(iter),
		                   mnode_getpartendaddr(iter)))
			return false; /* oops: overlap! */
	}
	return true; /* Everything OK! */
}





/* Lock for `mpart_all_list' */
PUBLIC struct atomic_lock mpart_all_lock = ATOMIC_LOCK_INIT;

/* [0..n][CHAIN(mp_allparts)][lock(mpart_all_lock)]
 * List of all memory parts currently in use. List head indices are `MPART_ALL_LIST_*'
 * NOTE: This list holds a reference to every contain part that wasn't
 *       already destroyed. Statically allocated parts aren't in here. */
PUBLIC struct mpart_tailq mpart_all_list = TAILQ_HEAD_INITIALIZER(mpart_all_list);
/* NOTE: The `mpart_all_list' list gets skewed during `kmalloc_leaks()',
 *       so there's no reason to annotate it with `ATTR_MALL_UNTRACKED'! */


/* [0..n][lock(ATOMIC)] List of lock-ops for `mpart_all_list' */
PUBLIC struct lockop_slist mpart_all_lops = SLIST_HEAD_INITIALIZER(mpart_all_lops);

#ifndef CONFIG_NO_MPART_ALL_SIZE
/* [lock(mpart_all_lock)] The # of parts stored in `mpart_all_list' */
PUBLIC size_t mpart_all_size = 0;
#endif /* !CONFIG_NO_MPART_ALL_SIZE */


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL async_add2all_mpart_destroy_postlop_cb)(struct postlockop *__restrict self) {
	struct mpart *me;
	me = container_of(self, struct mpart, _mp_plopall);
	TAILQ_ENTRY_UNBOUND_INIT(&me->mp_allparts);
	mpart_destroy(me);
}

PRIVATE NOBLOCK NONNULL((1)) struct postlockop *
NOTHROW(FCALL async_add2all_mpart_lop_cb)(struct lockop *__restrict self) {
	REF struct mpart *me;
	me = container_of(self, struct mpart, _mp_lopall);
	if unlikely(atomic_decfetch(&me->mp_refcnt) == 0) {
		/* Destroy the part in a post-lockop to improve throughput! */
		me->_mp_plopall.plo_func = &async_add2all_mpart_destroy_postlop_cb;
		return &me->_mp_plopall;
	}
	_mpart_all_list_insert(me);
	return NULL;
}


/* Add  the given mpart  `self' to the  global list of parts.
 * This function will initialize `self->mp_allparts',  though
 * may do so  asynchronously (meaning that  the part may  not
 * have been added  to the  all-parts list yet,  even if  you
 * acquire a lock to said list immediately after calling this
 * function) */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_all_list_insert)(struct mpart *__restrict self) {
	if (mpart_all_tryacquire()) {
		/* Directly insert into the global part list. */
		_mpart_all_list_insert(self);
		mpart_all_release();
	} else {
		static_assert(offsetof(struct mpart, mp_allparts.tqe_prev) ==
		              offsetof(struct mpart, _mp_lopall.lo_func),
		              "This is an implementation detail that is required, such that "
		              /**/ "a mem-part that's still being added to the all-parts list via "
		              /**/ "async means can still be tested via `TAILQ_ISBOUND()' for being "
		              /**/ "apart of the all-parts list:\n"
		              "While the async `async_add2all_mpart_lop_cb()' is pending, the "
		              /**/ "lo_func field of the lop will be non-NULL, and `TAILQ_ISBOUND()' "
		              /**/ "is implemented to check if `tqe_prev' is non-NULL.\n"
		              "So we put the 2 together such that `tqe_prev' will also appear as "
		              /**/ "non-NULL for as long as the async add2all hasn't been serviced "
		              /**/ "yet, thus keeping everything consistent.");

		/* Enqueue `self' as a pending globally visible part. */
		incref(self); /* This reference is inherited by `mpart_all_pending' */

		/* Enqueue a lockop to asynchronously add `self' to the all-parts list. */
		self->_mp_lopall.lo_func = &async_add2all_mpart_lop_cb;
		SLIST_ATOMIC_INSERT(&mpart_all_lops, &self->_mp_lopall, lo_link);
		_mpart_all_reap();
	}
}




DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_C */
