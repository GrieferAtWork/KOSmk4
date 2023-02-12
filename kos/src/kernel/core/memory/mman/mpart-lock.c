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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_LOCK_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_LOCK_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/mpartmeta.h>
#include <kernel/mman/phys.h>
#include <kernel/mman/sync.h>
#include <kernel/paging.h>
#include <kernel/swap.h>
#include <sched/sig.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>

#include <kos/except.h>

#include <assert.h>
#include <atomic.h>
#include <inttypes.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mchunk_freemem)(struct mchunk *__restrict self) {
	page_free(self->mc_start, self->mc_size);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mchunkvec_freemem)(struct mchunk *__restrict vec, size_t count) {
	size_t i;
	for (i = 0; i < count; ++i)
		mchunk_freemem(&vec[i]);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mchunk_freeswp)(struct mchunk *__restrict self) {
	swap_free(self->mc_start, self->mc_size);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mchunkvec_freeswp)(struct mchunk *__restrict vec, size_t count) {
	size_t i;
	for (i = 0; i < count; ++i)
		mchunk_freeswp(&vec[i]);
}


#define UNLOCK(self, unlock)     \
	(_mpart_lock_release(self), \
	 unlockinfo_xunlock(unlock), \
	 mpart_lockops_reap(self))
#ifdef __OPTIMIZE_SIZE__
#define UNLOCK_OPTREAP(self, unlock) \
	(_mpart_lock_release(self),     \
	 unlockinfo_xunlock(unlock))
#else /* __OPTIMIZE_SIZE__ */
#define UNLOCK_OPTREAP(self, unlock) \
	UNLOCK(self, unlock)
#endif /* !__OPTIMIZE_SIZE__ */



/************************************************************************/
/* MPart API to lock a part, alongside doing some other operations.     */
/************************************************************************/

/* Ensure that `!mpart_hasblocksstate_init(self)' */
PUBLIC BLOCKING WUNUSED NONNULL((1)) bool FCALL
mpart_initdone_or_unlock(struct mpart *__restrict self,
                         struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, ...) {
	if unlikely(mpart_hasblocksstate_init(self)) {
		incref(self);
		FINALLY_DECREF_UNLIKELY(self);
		TRY {
			/* Wait for init-done to be signaled. */
			REF struct mfile *file;
			file = incref(self->mp_file);
			UNLOCK_OPTREAP(self, unlock);
			{
				FINALLY_DECREF_UNLIKELY(file);
				task_connect(&file->mf_initdone);
			}
			TRY {
				mpart_lock_acquire(self);
			} EXCEPT {
				task_disconnectall();
				RETHROW();
			}

			/* Check for init-parts once again. */
			if unlikely(!mpart_hasblocksstate_init(self)) {
				mpart_lock_release(self);
				task_disconnectall();
				return false;
			}
			mpart_lock_release(self);
			task_waitfor();
		} EXCEPT {
			mpart_lockops_reap(self);
			RETHROW();
		}
		return false;
	}
	return true;
}

/* Ensure that `self->mp_meta == NULL || self->mp_meta->mpm_dmalocks == 0' */
PUBLIC BLOCKING WUNUSED NONNULL((1)) bool FCALL
mpart_nodma_or_unlock(struct mpart *__restrict self,
                      struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, ...) {
	struct mpartmeta *meta = self->mp_meta;
	if (meta != NULL && atomic_read(&meta->mpm_dmalocks) != 0) {
		/* Must blocking-wait until all DMA locks have been released. */
		incref(self);
		UNLOCK(self, unlock);
		{
			FINALLY_DECREF_UNLIKELY(self);
			task_connect(&meta->mpm_dma_done);
			if unlikely(atomic_read(&meta->mpm_dmalocks) == 0) {
				task_disconnectall();
				return false;
			}
		}
		task_waitfor();
		return false;
	}
	return true;
}

/* Ensure that `self->mp_meta != NULL' */
PUBLIC WUNUSED NONNULL((1)) bool FCALL
mpart_hasmeta_or_unlock(struct mpart *__restrict self,
                        struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	if (self->mp_meta == NULL) {
		struct mpartmeta *meta;
		meta = (struct mpartmeta *)kmalloc_nx(sizeof(struct mpartmeta),
		                                      GFP_ATOMIC | GFP_CALLOC);
		if (meta == NULL) {
			/* Must allocate while blocking. */
			incref(self);
			UNLOCK(self, unlock);
			FINALLY_DECREF_UNLIKELY(self);
			meta = (struct mpartmeta *)kmalloc(sizeof(struct mpartmeta),
			                                   GFP_CALLOC);
			mpartmeta_cinit(meta);

			/* The part-meta-field can only be written while holding  a
			 * lock to the  mem-part. This is  required to prevent  the
			 * random  introduction  of additional  locks (such  as the
			 * `struct mpartmeta::mpm_ftxlock' lock) needing to be held
			 * to be able to modify  (e.g.) `mp_minaddr'. If the  meta-
			 * controller  could  be allocated  atomically,  then there
			 * would be no way to  prevent its addition and  subsequent
			 * requirement of acquiring `mpm_ftxlock' in this scenario,
			 * meaning  that  such code  would have  to unconditionally
			 * allocate the futex controller, even if it's not  needed. */
			TRY {
				mpart_lock_acquire(self);
			} EXCEPT {
				kfree(meta);
				RETHROW();
			}

			/* Remember that meta-data has been allocated. */
			if likely(self->mp_meta == NULL) {
				self->mp_meta = meta;
				mpart_lock_release(self);
			} else {
				mpart_lock_release(self);
				kfree(meta);
			}
			return false;
		}
		mpartmeta_cinit(meta);

		/* Remember that meta-data has been allocated.
		 * NOTE: We never released the lock to `self', so we're allowed
		 *       to  assume that the  meta-data controller still hasn't
		 *       been allocated. */
		assert(self->mp_meta == NULL);
		self->mp_meta = meta;
	}
	return true;
}



/* Finalize data needed for `mpart_setcore_or_unlock()' */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_setcore_data_fini)(struct mpart_setcore_data *__restrict self) {
	kfree(self->scd_bitset);
	switch (self->scd_copy_state) {

	case MPART_ST_MEM:
		mchunk_freemem(&self->scd_copy_mem);
		break;

	case MPART_ST_MEM_SC:
		mchunkvec_freemem(self->scd_copy_mem_sc.ms_v,
		                  self->scd_copy_mem_sc.ms_c);
		kfree(self->scd_copy_mem_sc.ms_v);
		break;

	default:
		assertf(self->scd_copy_state == MPART_ST_VOID,
		        "self->scd_copy_state: %u",
		        self->scd_copy_state);
		break;
	}
}



/* Allocate physical memory for exactly `data->scd_partsize' bytes of
 * memory, and store the results in:
 *   - data->scd_copy_state
 *   - data->scd_copy_mem
 *   - data->scd_copy_mem_sc
 * Throws an exception on error.
 * @return: true:  Success
 * @return: false: Success, but the lock to `self' was lost */
PRIVATE WUNUSED NONNULL((1, 3)) bool FCALL
mpart_setcore_makememdat_or_unlock(struct mpart *__restrict self,
                                   struct unlockinfo *unlock,
                                   struct mpart_setcore_data *__restrict data,
                                   size_t total_pages) {
	struct mchunk chunk, *vec;
	size_t done, missing_pages;
	if unlikely(data->scd_copy_state != MPART_ST_VOID) {
		/* Re-use already-allocated buffers. */
		assert(data->scd_copy_state == MPART_ST_MEM ||
		       data->scd_copy_state == MPART_ST_MEM_SC);
		if (data->scd_copy_state == MPART_ST_MEM) {
			if (total_pages == data->scd_copy_mem.mc_size)
				return true; /* Unchanged */
			if (total_pages < data->scd_copy_mem.mc_size) {
				page_ccfree(data->scd_copy_mem.mc_start + total_pages,
				            data->scd_copy_mem.mc_size - total_pages);
				data->scd_copy_mem.mc_size = total_pages;
				return true;
			}

			/* Must allocate more memory. (try re-try from the start) */
			page_ccfree(data->scd_copy_mem.mc_start,
			            data->scd_copy_mem.mc_size);
			data->scd_copy_state = MPART_ST_VOID;
		} else {
			/* A scatter-list had already been allocated in the past. */
			size_t i, old_total = 0;
			assert(data->scd_copy_mem_sc.ms_c != 0);
			for (i = 0; i < data->scd_copy_mem_sc.ms_c; ++i)
				old_total += data->scd_copy_mem_sc.ms_v[i].mc_size;
			if (total_pages == old_total)
				return true; /* Unchanged */
			if (total_pages < old_total) {
				size_t too_many = old_total - total_pages;
				i = data->scd_copy_mem_sc.ms_c - 1;

				/* Trim tailing pages. */
				while (too_many) {
					chunk = data->scd_copy_mem_sc.ms_v[i];
					if (chunk.mc_size <= too_many) {
						page_ccfree(chunk.mc_start, chunk.mc_size);
						too_many -= chunk.mc_size;
						--i;
						continue;
					}

					/* Truncate the last mem-part. */
					page_ccfree(chunk.mc_start +
					            chunk.mc_size - too_many,
					            too_many);
					data->scd_copy_mem_sc.ms_v[i].mc_size -= too_many;
					break;
				}
				assert(i <= data->scd_copy_mem_sc.ms_c);
				if (i == 0) {
					chunk = data->scd_copy_mem_sc.ms_v[0];
					kfree(data->scd_copy_mem_sc.ms_v);

					/* Transform into a single chunk. */
					data->scd_copy_mem   = chunk;
					data->scd_copy_state = MPART_ST_MEM;
				} else if (i < data->scd_copy_mem_sc.ms_c - 1) {
					struct mchunk *newvec;
					newvec = (struct mchunk *)krealloc_nx(data->scd_copy_mem_sc.ms_v,
					                                      (i + 1) * sizeof(struct mchunk),
					                                      GFP_LOCKED | GFP_ATOMIC | GFP_PREFLT);
					if likely(newvec)
						data->scd_copy_mem_sc.ms_v = newvec;
					data->scd_copy_mem_sc.ms_c = i + 1;
				}
				return true;
			}

			/* Must increase the size. */
			done = old_total;
			goto extend_vector;
		}
	}

	/* Try to allocate everything in a single page. */
	data->scd_copy_mem.mc_start = mfile_alloc_physmem(self->mp_file,
	                                                  total_pages,
	                                                  &data->scd_copy_mem.mc_size);
	if unlikely(data->scd_copy_mem.mc_start == PHYSPAGE_INVALID)
		goto err_badalloc; /* Insufficient physical memory. */
	assert(data->scd_copy_mem.mc_size != 0);
	assert(data->scd_copy_mem.mc_size <= total_pages);
	if likely(data->scd_copy_mem.mc_size >= total_pages) {
		/* Done: We've managed to allocate everything within a single chunk. */
		data->scd_copy_state = MPART_ST_MEM;
		return true;
	}

	/* Must allocate as scattered memory. */
	chunk = data->scd_copy_mem;
	vec = (struct mchunk *)kmalloc_nx(4 * sizeof(struct mchunk),
	                                  GFP_LOCKED | GFP_ATOMIC | GFP_PREFLT);
	if unlikely(!vec) {
		vec = (struct mchunk *)kmalloc_nx(2 * sizeof(struct mchunk),
		                                  GFP_LOCKED | GFP_ATOMIC | GFP_PREFLT);
		if unlikely(!vec) {
			_mpart_lock_release(self);
			unlockinfo_xunlock(unlock);
			mpart_lockops_reap(self);

			/* Must do the allocation with blocking */
			vec = (struct mchunk *)kmalloc_nx(4 * sizeof(struct mchunk),
			                                  GFP_LOCKED | GFP_PREFLT);
			if unlikely(!vec) {
				vec = (struct mchunk *)kmalloc(2 * sizeof(struct mchunk),
				                               GFP_LOCKED | GFP_PREFLT);
			}
			data->scd_copy_mem_sc.ms_v = vec;
			data->scd_copy_mem_sc.ms_c = 1;
			data->scd_copy_state       = MPART_ST_MEM_SC;
			vec[0]                     = chunk;
			done                       = chunk.mc_size;
			for (;;) {
				size_t avail;
				assert(done < total_pages);
				missing_pages = total_pages - done;

				/* Make sure that there is sufficient space for one additional chunk. */
				avail = kmalloc_usable_size(data->scd_copy_mem_sc.ms_v) / sizeof(struct mchunk);
				assert(avail >= data->scd_copy_mem_sc.ms_c);
				if (avail <= data->scd_copy_mem_sc.ms_c) {
do_realloc_in_extend_after_unlock:
					vec = (struct mchunk *)krealloc(data->scd_copy_mem_sc.ms_v,
					                                (data->scd_copy_mem_sc.ms_c + 1) *
					                                sizeof(struct mchunk),
					                                GFP_LOCKED | GFP_PREFLT);
					data->scd_copy_mem_sc.ms_v = vec;
				}

				/* Allocate the new chunk. */
				chunk.mc_start = mfile_alloc_physmem(self->mp_file, missing_pages, &chunk.mc_size);
				if unlikely(chunk.mc_start == PHYSPAGE_INVALID)
					goto err_badalloc_after_unlock; /* Insufficient physical memory. */
				assert(chunk.mc_size <= missing_pages);
				data->scd_copy_mem_sc.ms_v[data->scd_copy_mem_sc.ms_c] = chunk;
				++data->scd_copy_mem_sc.ms_c;
				done += chunk.mc_size;
				assert(done <= total_pages);
				if (done >= total_pages)
					break;
			}

			/* Try to truncate unused memory. */
			vec = (struct mchunk *)krealloc_nx(data->scd_copy_mem_sc.ms_v,
			                                   data->scd_copy_mem_sc.ms_c *
			                                   sizeof(struct mchunk),
			                                   GFP_LOCKED | GFP_PREFLT);
			if likely(vec != NULL)
				data->scd_copy_mem_sc.ms_v = vec;
			return false;
		}
	}
	data->scd_copy_mem_sc.ms_v = vec;
	data->scd_copy_mem_sc.ms_c = 1;
	data->scd_copy_state       = MPART_ST_MEM_SC;
	vec[0]                     = chunk;
	done                       = chunk.mc_size;
extend_vector:
	assert(done < total_pages);
	for (;;) {
		size_t avail;
		missing_pages = total_pages - done;

		/* Make sure that there is sufficient space for one additional chunk. */
		avail = kmalloc_usable_size(data->scd_copy_mem_sc.ms_v) / sizeof(struct mchunk);
		assert(avail >= data->scd_copy_mem_sc.ms_c);
		if (avail <= data->scd_copy_mem_sc.ms_c) {
			/* Extend the vector. */
			vec = (struct mchunk *)krealloc_nx(data->scd_copy_mem_sc.ms_v,
			                                   (data->scd_copy_mem_sc.ms_c + 1) *
			                                   sizeof(struct mchunk),
			                                   GFP_LOCKED | GFP_ATOMIC | GFP_PREFLT);
			if unlikely(!vec) {
				/* Must do the thing with blocking. */
				UNLOCK(self, unlock);
				goto do_realloc_in_extend_after_unlock;
			}
			data->scd_copy_mem_sc.ms_v = vec;
		}

		/* Allocate the new chunk. */
		chunk.mc_start = mfile_alloc_physmem(self->mp_file, missing_pages, &chunk.mc_size);
		if unlikely(chunk.mc_start == PHYSPAGE_INVALID)
			goto err_badalloc; /* Insufficient physical memory. */
		data->scd_copy_mem_sc.ms_v[data->scd_copy_mem_sc.ms_c] = chunk;
		++data->scd_copy_mem_sc.ms_c;
		done += chunk.mc_size;
		assert(done <= total_pages);
		if (done >= total_pages)
			break;
	}

	/* Try to truncate unused memory. */
	vec = (struct mchunk *)krealloc_nx(data->scd_copy_mem_sc.ms_v,
	                                   data->scd_copy_mem_sc.ms_c *
	                                   sizeof(struct mchunk),
	                                   GFP_LOCKED | GFP_ATOMIC | GFP_PREFLT);
	if likely(vec != NULL)
		data->scd_copy_mem_sc.ms_v = vec;
	return true;
err_badalloc:
	UNLOCK(self, unlock);
err_badalloc_after_unlock:
	THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, total_pages);
}



#define bitset_getstate(base, partrel_block_index)                                    \
	(((base)[(partrel_block_index) / MPART_BLKST_BLOCKS_PER_WORD] >>                  \
	  (((partrel_block_index) % MPART_BLKST_BLOCKS_PER_WORD) * MPART_BLOCK_STBITS)) & \
	 (((mpart_blkst_word_t)1 << MPART_BLOCK_STBITS) - 1))
#define setcore_ex_bitset_getstate(self, partrel_block_index) \
	bitset_getstate((self)->scd_bitset, partrel_block_index)

PRIVATE WUNUSED NONNULL((1, 3)) bool FCALL
setcore_ex_makebitset_or_unlock(struct mpart *__restrict self,
                                struct unlockinfo *unlock,
                                struct mpart_setcore_data *__restrict data,
                                size_t num_blocks,
                                gfp_t gfp_flags) {
	size_t avl_size, req_size;
	mpart_blkst_word_t *new_bitset;

	/* Must actually allocate the block-status bitset! */
	avl_size = kmalloc_usable_size(data->scd_bitset);
	req_size = CEILDIV(num_blocks, MPART_BLKST_BLOCKS_PER_WORD) * sizeof(mpart_blkst_word_t);
	if likely(req_size > avl_size) {
		/* Must allocate a larger bitset. */
		new_bitset = (mpart_blkst_word_t *)krealloc_nx(data->scd_bitset, req_size,
		                                               GFP_LOCKED | GFP_ATOMIC |
		                                               GFP_PREFLT | gfp_flags);
		if unlikely(!new_bitset) {
			/* Must allocate the bitset while blocking. */
			UNLOCK(self, unlock);
			data->scd_bitset = (mpart_blkst_word_t *)krealloc(data->scd_bitset, req_size,
			                                                  GFP_LOCKED | GFP_PREFLT |
			                                                  gfp_flags);
			return false;
		}
		data->scd_bitset = new_bitset;
	} else if (req_size < avl_size) {
		new_bitset = (mpart_blkst_word_t *)krealloc_nx(data->scd_bitset, req_size,
		                                               GFP_LOCKED | GFP_ATOMIC |
		                                               GFP_PREFLT | gfp_flags);
		if likely(new_bitset != NULL)
			data->scd_bitset = new_bitset;
	}
	return true;
}


PRIVATE NONNULL((1, 2, 3, 4)) void FCALL
setcore_ex_load_from_swap_impl(struct mchunkvec *__restrict dst_vec,
                               struct mchunkvec *__restrict src_vec,
                               uintptr_t *__restrict pdst_offset,
                               uintptr_t *__restrict psrc_offset,
                               size_t num_bytes) {
	while (num_bytes) {
		size_t dst_bytes, src_bytes, part;
		physaddr_t dst_addr;
		swapaddr_t src_addr;

		/* Skip unused leading chunks in src and dst */
		while ((assert(dst_vec->ms_c), *pdst_offset >= (dst_vec->ms_v[0].mc_size * PAGESIZE))) {
			*pdst_offset -= dst_vec->ms_v[0].mc_size * PAGESIZE;
			--dst_vec->ms_c;
			++dst_vec->ms_v;
		}
		while ((assert(src_vec->ms_c), *psrc_offset >= (src_vec->ms_v[0].mc_size * PAGESIZE))) {
			*psrc_offset -= src_vec->ms_v[0].mc_size * PAGESIZE;
			--src_vec->ms_c;
			++src_vec->ms_v;
		}
		dst_bytes = (dst_vec->ms_v[0].mc_size * PAGESIZE) - *pdst_offset;
		src_bytes = (src_vec->ms_v[0].mc_size * PAGESIZE) - *psrc_offset;
		dst_addr  = physpage2addr(dst_vec->ms_v[0].mc_start) + *pdst_offset;
		src_addr  = physpage2addr(src_vec->ms_v[0].mc_start) + *psrc_offset;
		part      = dst_bytes;
		if (part > src_bytes)
			part = src_bytes;
		if (part > num_bytes)
			part = num_bytes;

		/* Do the actual transfer. */
		swap_read(src_addr, dst_addr, part);

		*pdst_offset += part;
		*psrc_offset += part;
		if (part >= num_bytes)
			break;
		num_bytes -= part;
	}
}

/* Load data from swap memory.
 * WARNING: This function will modify `dst_vec' and `src_vec' */
PRIVATE NONNULL((1, 2, 3)) void FCALL
setcore_ex_load_from_swap(struct mchunkvec *__restrict dst_vec,
                          struct mchunkvec *__restrict src_vec,
                          mpart_blkst_word_t const *__restrict bitset,
                          shift_t block_shift,
                          size_t num_blocks) {
#define GETSTATE(index) bitset_getstate(bitset, index)
	size_t i, block_size;
	uintptr_t dst_offset = 0;
	uintptr_t src_offset = 0;
	block_size = (size_t)1 << block_shift;
	for (i = 0; i < num_blocks;) {
		size_t end, num_bytes;
		if (GETSTATE(i) != MPART_BLOCK_ST_INIT) {
			dst_offset += block_size;
			++i;
			continue;
		}
		end = i + 1;

		/* Load continuous segments all at once! */
		while (end < num_blocks) {
			if (GETSTATE(end) != MPART_BLOCK_ST_INIT)
				break;
			++end;
		}

		/* Load swap data within i...end */
		num_bytes = (end - i) << block_shift;
		setcore_ex_load_from_swap_impl(dst_vec, src_vec,
		                               &dst_offset,
		                               &src_offset,
		                               num_bytes);
		i = end;
	}
#undef GETSTATE
}


/* Ensure that `MPART_ST_INCORE(self->mp_state)' */
PUBLIC BLOCKING WUNUSED NONNULL((1, 3)) bool FCALL
mpart_setcore_or_unlock(struct mpart *__restrict self,
                        struct unlockinfo *unlock,
                        struct mpart_setcore_data *__restrict data)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	size_t num_bytes, num_pages, num_blocks;
	struct mfile *file;

	/* Quick check: is the part already in the expected state? */
	if (MPART_ST_INCORE(self->mp_state))
		goto done_simple; /* Already done! */

	num_bytes = mpart_getsize(self);
	assert(IS_ALIGNED(num_bytes, PAGESIZE));
	if unlikely(!num_bytes) {
		/* Special case for when a part was deleted. */
		assert((self->mp_state == MPART_ST_VOID) ||
		       (self->mp_state == MPART_ST_MEM && self->mp_mem.mc_size == 0) ||
		       (self->mp_state == MPART_ST_SWP && self->mp_swp.mc_size == 0));
		self->mp_state        = MPART_ST_MEM;
		self->mp_mem.mc_start = 0;
		self->mp_mem.mc_size  = 0;
		return true;
	}

	file       = self->mp_file;
	num_pages  = num_bytes / PAGESIZE;
	num_blocks = num_bytes >> file->mf_blockshift;

	/* Allocate physical memory. */
	if (!mpart_setcore_makememdat_or_unlock(self, unlock, data, num_pages))
		goto nope;

	/* Fill in memory information for `self'. */
	assert(!MPART_ST_INCORE(self->mp_state));
	switch (__builtin_expect(self->mp_state, MPART_ST_VOID)) {

	case MPART_ST_VOID:
		/* Make sure that we've got sufficient space for the block-state bitset. */
		if (num_blocks <= MPART_BLKST_BLOCKS_PER_WORD) {
			/* Can use the inline bitset. */
			if unlikely(data->scd_bitset != NULL) {
				kfree(data->scd_bitset);
				DBG_memset(&data->scd_bitset, 0xcc, sizeof(data->scd_bitset));
			}
			if unlikely(!(self->mp_flags & MPART_F_BLKST_INL))
				kfree(self->mp_blkst_ptr);

			/* All blocks are undefined by default! */
			self->mp_blkst_inl = MPART_BLOCK_REPEAT(MPART_BLOCK_ST_NDEF);
			atomic_or(&self->mp_flags, MPART_F_BLKST_INL);
		} else if (self->mp_blkst_ptr == NULL) {
			/* Must actually allocate the block-status bitset! */
			if (!setcore_ex_makebitset_or_unlock(self, unlock, data, num_blocks, GFP_CALLOC))
				goto nope;

			/* NOTE: Because we've used GFP_CALLOC, all blocks will have
			 *       already been initialized to  `MPART_BLOCK_ST_NDEF'! */
			self->mp_blkst_ptr = data->scd_bitset;
			atomic_and(&self->mp_flags, ~MPART_F_BLKST_INL);
			DBG_memset(&data->scd_bitset, 0xcc, sizeof(data->scd_bitset));
		}
#ifndef NDEBUG
		else {
			assertf(kmalloc_usable_size(self->mp_blkst_ptr) >=
			        CEILDIV(num_blocks, MPART_BLKST_BLOCKS_PER_WORD) *
			        sizeof(mpart_blkst_word_t),
			        "Allocated bitset at %p is too small (%" PRIuSIZ " < %" PRIuSIZ ")",
			        kmalloc_usable_size(self->mp_blkst_ptr),
			        CEILDIV(num_blocks, MPART_BLKST_BLOCKS_PER_WORD) *
			        sizeof(mpart_blkst_word_t));
		}
#endif /* !NDEBUG */
		break;

	case MPART_ST_SWP:
	case MPART_ST_SWP_SC: {
		size_t i;
		bool did_set_init_parts;
		assert(mpart_hasblockstate(self));

		/* Load data from swap.
		 * For this purpose, we must ensure that there aren't any pre-existing
		 * INIT-blocks, which might  happen if  someone else is  still in  the
		 * process of writing data _to_ swap (in which case they will make the
		 * INIT-blocks go away once they're done) */
		if (!mpart_initdone_or_unlock(self, unlock))
			goto nope;

		/* In  order to (safely) remember which parts  we've set to INIT (as opposed
		 * to someone else setting them), we have to allocate sufficient heap memory
		 * in order to store a copy of the bitset of `self' */
		if (!setcore_ex_makebitset_or_unlock(self, unlock, data, num_blocks, 0))
			goto nope;

		/* Now we must switch all  `MPART_BLOCK_ST_CHNG' parts (i.e. all parts  that
		 * have been written to swap) over to `MPART_BLOCK_ST_INIT', thus preventing
		 * anyone else from changing the contents of the part.
		 *
		 * NOTE: And while we're at it, also change all `MPART_BLOCK_ST_LOAD' parts
		 *       back to `MPART_BLOCK_ST_NDEF',  since their  contents have  gotten
		 *       lost when memory was written to swap. */
		did_set_init_parts = false;
		for (i = 0; i < num_blocks; ++i) {
			unsigned int st;
			st = mpart_getblockstate(self, i);
			if (st == MPART_BLOCK_ST_LOAD) {
				mpart_setblockstate(self, i, MPART_BLOCK_ST_NDEF);
			} else if (st == MPART_BLOCK_ST_CHNG) {
				mpart_setblockstate(self, i, MPART_BLOCK_ST_INIT);
				did_set_init_parts = true;
			}
		}

		/* Special (but _really_ unlikely) case: The swap area wasn't actually used. */
		if unlikely(!did_set_init_parts)
			goto done_swap;

		/* Set the flag to indicate that there are INIT-blocks! */
		atomic_or(&self->mp_flags, MPART_F_MAYBE_BLK_INIT);

		/* At this point, we know  that _all_ INIT-entries within the  bitset
		 * of  `self' originate from  our doing. As  such, copy the constants
		 * of  the bitset  into our local  heap-copy, so we  still know which
		 * parts we're supposed to initialize from swap once we're done here! */
		{
			mpart_blkst_word_t *src = self->mp_blkst_ptr;
			if (self->mp_flags & MPART_F_BLKST_INL)
				src = &self->mp_blkst_inl;
			memcpy(data->scd_bitset, src,
			       CEILDIV(num_blocks, MPART_BLKST_BLOCKS_PER_WORD),
			       sizeof(mpart_blkst_word_t));
		}

		/* Release our lock to `self' so we can safely invoke swap-callbacks. */
		incref(self);
		incref(file);
		UNLOCK(self, unlock);
		TRY {
			struct mchunkvec mem_data;
			struct mchunkvec swp_data;
			/* NOTE: We can still access fields of `self' that are marked as
			 *       [const_if(EXISTS(MPART_BLOCK_ST_INIT))]
			 *       because we know that ST_INIT blocks exist (since we've
			 *       created them) */
			if (self->mp_state == MPART_ST_SWP) {
				swp_data.ms_c = 1;
				swp_data.ms_v = &self->mp_swp;
			} else {
				swp_data.ms_c = self->mp_swp_sc.ms_c;
				swp_data.ms_v = self->mp_swp_sc.ms_v;
			}
			if (data->scd_copy_state == MPART_ST_MEM) {
				mem_data.ms_c = 1;
				mem_data.ms_v = &data->scd_copy_mem;
			} else {
				mem_data.ms_c = data->scd_copy_mem_sc.ms_c;
				mem_data.ms_v = data->scd_copy_mem_sc.ms_v;
			}

			/* Actually load data from swap. */
			setcore_ex_load_from_swap(&mem_data, &swp_data,
			                          data->scd_bitset,
			                          file->mf_blockshift,
			                          num_blocks);

			/* Re-acquire our lock to `self' */
			mpart_lock_acquire(self);
		} EXCEPT {
			/* Change the INIT-blocks we've set above to `CHNG' */
			for (i = 0; i < num_blocks; ++i) {
				unsigned int st;
				st = setcore_ex_bitset_getstate(data, i); /* Read from the local bitset! */
				if (st == MPART_BLOCK_ST_INIT)
					mpart_setblockstate(self, i, MPART_BLOCK_ST_CHNG);
			}
			sig_broadcast(&file->mf_initdone);
			decref_unlikely(file);
			decref_unlikely(self);
			RETHROW();
		}

		/* Assert that nothing changed about `self' that should have
		 * been  protected  by  us  having  set  INIT-blocks  above. */
		assert(self->mp_state == MPART_ST_SWP ||
		       self->mp_state == MPART_ST_SWP_SC);
		assert(self->mp_file == file);
		assert(num_bytes == mpart_getsize(self));

		/* Change the INIT-blocks we've set above to `CHNG' */
		for (i = 0; i < num_blocks; ++i) {
			unsigned int st;
			st = setcore_ex_bitset_getstate(data, i); /* Read from the local bitset! */
			if (st == MPART_BLOCK_ST_INIT)
				mpart_setblockstate(self, i, MPART_BLOCK_ST_CHNG);
		}

		/* Now that all of (our) INIT-blocks are gone, broadcast
		 * the init-done signal of our file to tell other thread
		 * that INIT blocks may possible be all gone now. */
		sig_broadcast(&file->mf_initdone);
		decref_unlikely(file);

		/* And with that, all required data has been read from swap,
		 * and  we can  safely transition  to on  of the MEM-states. */
done_swap:
		kfree(data->scd_bitset);
		DBG_memset(&data->scd_bitset, 0xcc, sizeof(data->scd_bitset));

		/* Free the swap storage area used by this part. */
		if (self->mp_state == MPART_ST_SWP) {
			mchunk_freeswp(&self->mp_swp);
		} else {
			mchunkvec_freeswp(self->mp_swp_sc.ms_v,
			                  self->mp_swp_sc.ms_c);
			kfree(self->mp_swp_sc.ms_v);
		}

		/* Fill in information on the backing storage. */
		self->mp_state = data->scd_copy_state;
		DBG_memset(&data->scd_copy_state, 0xcc, sizeof(data->scd_copy_state));
		memcpy(&self->mp_mem, &data->scd_copy_mem,
		       MAX_C(sizeof(struct mchunk),
		             sizeof(struct mchunkvec)));
		DBG_memset(&data->scd_copy_mem, 0xcc,
		           MAX_C(sizeof(struct mchunk),
		                 sizeof(struct mchunkvec)));

		/* Even though we _did_ manage to load the part from swap,
		 * we  _did_ have to release _all_ locks to do so, meaning
		 * that we can't actually indicate success to our caller.
		 *
		 * However, the  next time  around,  our part  is  probably
		 * still going to be loaded in-core, so we'll succeed then! */
		mpart_lock_release(self);
		decref_unlikely(self);

		/* Ensure a consistent state when returning `false' */
		mpart_setcore_data_init(data);
		goto nope;
	}	break;

	default: __builtin_unreachable();
	}

	/* Fill in information on the backing storage. */
	self->mp_state = data->scd_copy_state;
	DBG_memset(&data->scd_copy_state, 0xcc,
	           sizeof(data->scd_copy_state));
	memcpy(&self->mp_mem, &data->scd_copy_mem,
	       MAX_C(sizeof(struct mchunk),
	             sizeof(struct mchunkvec)));
	DBG_memset(&data->scd_copy_mem, 0xcc,
	           MAX_C(sizeof(struct mchunk),
	                 sizeof(struct mchunkvec)));
	return true;
done_simple:
	mpart_setcore_data_fini(data);
	return true;
nope:
	return false;
}



/* Ensure that all blocks (within the given range of blocks)
 * are either `MPART_BLOCK_ST_LOAD' or `MPART_BLOCK_ST_CHNG'
 * The caller must ensure that...
 *   - ... the given address range is in-bounds!
 *   - ... MPART_ST_INCORE(self->mp_state)
 * If they don't, then this function will cause an assertion failure! */
PUBLIC BLOCKING WUNUSED NONNULL((1)) bool FCALL
mpart_load_or_unlock(struct mpart *__restrict self,
                     struct unlockinfo *unlock,
                     mpart_reladdr_t partrel_offset,
                     size_t num_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	size_t i;
	struct mfile *file = self->mp_file;
	bool has_init = false;
	shift_t shift;
	size_t blocks_start, blocks_end;
	assert(MPART_ST_INCORE(self->mp_state));
	shift        = self->mp_file->mf_blockshift;
	blocks_start = partrel_offset >> shift;
	blocks_end   = ((partrel_offset + num_bytes - 1) >> shift) + 1;
	assert(blocks_start <= blocks_end);
	assert(blocks_end <= (mpart_getsize(self) >> shift));

	/* Check for simple case: Without a proper block-state,
	 * everything  is  implicitly marked  as  CHNG, meaning
	 * everything has already been loaded! */
	if unlikely(!mpart_hasblockstate(self))
		return true;

	/* Check for parts that have yet to be loaded. */
	for (i = blocks_start; i < blocks_end; ++i) {
		unsigned int st;
		size_t start, end, blocks_maxend;
		struct mpart_physloc loc;
		st = mpart_getblockstate(self, i);
		if (st == MPART_BLOCK_ST_CHNG ||
		    st == MPART_BLOCK_ST_LOAD)
			continue;
		if (st == MPART_BLOCK_ST_INIT) {
			has_init = true;
			continue;
		}
		assert(st == MPART_BLOCK_ST_NDEF);

		/* Figure out backing physical memory. */
		start = i;
		mpart_memaddr_direct(self, start << file->mf_blockshift, &loc);
		blocks_maxend = start + (loc.mppl_size >> file->mf_blockshift);
		assert(blocks_maxend <= mpart_getblockcount(self, file));
		if (blocks_end > blocks_maxend)
			blocks_end = blocks_maxend;

		/* Alter the state of UNDEF parts to INIT, thus essentially
		 * locking them in-memory  until we're  down loading  them. */
		for (end = start + 1;;) {
			mpart_setblockstate(self, end - 1, MPART_BLOCK_ST_INIT);
			if (end >= blocks_end)
				break; /* The next block would no longer be apart of the containing chunk. */
			st = mpart_getblockstate(self, end);
			if (st != MPART_BLOCK_ST_NDEF)
				break; /* The next block is no longer marked as UNDEF. */
			++end;
		}
		atomic_or(&self->mp_flags, MPART_F_MAYBE_BLK_INIT);
		incref(self);
		incref(file);
		mfile_trunclock_inc(file);

		/* Release the lock from the part, so we can load
		 * blocks without holding that non-recursive, and
		 * non-preemptive lock! */
		UNLOCK(self, unlock);
		TRY {
			/* Actually do the load. */
			pos_t addr;
			size_t num_bytes;
			auto mo_loadblocks = file->mf_ops->mo_loadblocks;

			addr      = self->mp_minaddr + (start << file->mf_blockshift);
			num_bytes = (end - start) << file->mf_blockshift;

			if (!mfile_isanon(file)) {
				pos_t filesize = mfile_getsize(file);
				if (!OVERFLOW_UADD(filesize, file->mf_part_amask, &filesize)) {
					filesize = mfile_partaddr_flooralign(file, filesize);

					/* NOTE: The file size may increase in the mean time, but that's actually
					 *       ok: We're currently holding exclusive locks to all of the blocks
					 *       that  we're going to initialize next (s.a. MPART_BLOCK_ST_INIT).
					 *       As  such, if  the file's size  increases, _has_ to  include to a
					 *       point above the  region which we're  trying to initialize  here.
					 * e.g.: Someone else is allowed to  write data, say, +0x12000 bytes  further
					 *       into the file, and that would never affect us here. If this happens,
					 *       there are 2 race conditions that can happen:
					 *   - We've read the file's old size, and it has since increased.
					 *     -> In  this case, we'll be zero-initializing some data that has already
					 *        come to be considered as part of the live file, but that's OK, since
					 *        that data has never been accessed before, and would have been  zero-
					 *        filled in either case.
					 *     -> Even if the  `mo_loadblocks' calls  fails, we'll just  set those  blocks
					 *        back to ST_NDEF, which will effectively look like we didn't do anything.
					 *   - We've read  the file's  new size.  - that's  even simpler,  since then  we
					 *     won't do any  that `bzerophyscc' call  at all.  - In this  case, the  call
					 *     to `mo_loadblocks' will load in data from disk that (may have been) loaded
					 *     when the write  that increased the  file's size was  done. And since  this
					 *     writing  somewhere  further into  a  file automatically  implies  that all
					 *     uninitialized  data  up until  that point  should  be considered  as ZERO,
					 *     we'll  end  with the  same  result, where  the  fs-driver will  just write
					 *     zeroes to the buffer, the same way we would have! */
					if unlikely(addr + num_bytes > filesize) {
						if (addr >= filesize) {
							bzerophyscc(loc.mppl_addr, num_bytes);
						} else {
							size_t load_bytes;
							load_bytes = (size_t)(filesize - addr);
							assert(load_bytes < num_bytes);
							if likely(mo_loadblocks != NULL)
								mfile_dosyncio(file, mo_loadblocks, addr, loc.mppl_addr, load_bytes);
							bzerophyscc(loc.mppl_addr + load_bytes,
							            num_bytes - load_bytes);
						}
						goto initdone;
					}
				}
			}
			if likely(mo_loadblocks != NULL)
				mfile_dosyncio(file, mo_loadblocks, addr, loc.mppl_addr, num_bytes);
		} EXCEPT {
			/* Set block states back to NDEF */
			for (i = start; i < end; ++i)
				mpart_setblockstate(self, i, MPART_BLOCK_ST_NDEF);
			mfile_trunclock_dec_nosignal(file);
			sig_broadcast(&file->mf_initdone);
			decref_unlikely(file);
			decref_unlikely(self);
			RETHROW();
		}
initdone:

		/* Set loaded states back to LOAD */
		for (i = start; i < end; ++i)
			mpart_setblockstate(self, i, MPART_BLOCK_ST_LOAD);
		mfile_trunclock_dec_nosignal(file);
		sig_broadcast(&file->mf_initdone);
		decref_unlikely(file);
		decref_unlikely(self);
		return false;
	}

	/* Wait for init-parts to go away! */
	if (has_init) {
		incref(self);
		FINALLY_DECREF_UNLIKELY(self);
		TRY {
			incref(file);
			UNLOCK_OPTREAP(self, unlock);
			{
				FINALLY_DECREF_UNLIKELY(file);
				task_connect(&file->mf_initdone);
			}
			TRY {
				mpart_lock_acquire(self);
			} EXCEPT {
				task_disconnectall();
				RETHROW();
			}

			/* Check for init-parts once again. */
			if unlikely(!mpart_hasblocksstate_init(self)) {
				mpart_lock_release(self);
				task_disconnectall();
				return false;
			}
			mpart_lock_release(self);
			task_waitfor();
		} EXCEPT {
			mpart_lockops_reap(self);
			RETHROW();
		}
		return false;
	}
	return true;
}





/* Given 2 mem-parts that are both `MPART_ST_MEM' or `MPART_ST_MEM_SC',
 * and are both at least `num_pages' large, copy the contents of  those
 * many pages of physical memory from `src' to `dst' */
INTERN NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mpart_copyram)(struct mpart *__restrict dst,
                             struct mpart *__restrict src,
                             PAGEDIR_PAGEALIGNED mpart_reladdr_t src_offset,
                             size_t num_pages) {
	assert(MPART_ST_INMEM(dst->mp_state));
	assert(MPART_ST_INMEM(src->mp_state));
	if (src->mp_state == MPART_ST_MEM) {
		if (dst->mp_state == MPART_ST_MEM) {
			/* SINGLE --> SINGLE */
			copypagesinphys(physpage2addr(dst->mp_mem.mc_start),
			                physpage2addr(src->mp_mem.mc_start) + src_offset,
			                num_pages);
		} else {
			/* SINGLE --> MULTIPLE */
			size_t i;
			physpage_t src_page;
			struct mchunk *dst_chunks;
			src_page   = src->mp_mem.mc_start;
			dst_chunks = dst->mp_mem_sc.ms_v;
			for (i = 0;; ++i) {
				size_t count;
				assert(i < dst->mp_mem_sc.ms_c);
				count = dst_chunks[i].mc_size;
				if (count > num_pages)
					count = num_pages;
				copypagesinphys(physpage2addr(dst_chunks[i].mc_start),
				                physpage2addr(src_page) + src_offset,
				                count);
				if (count >= num_pages)
					break;
				num_pages -= count;
				src_page += count;
			}
		}
	} else if (dst->mp_state == MPART_ST_MEM) {
		/* MULTIPLE --> SINGLE */
		size_t i;
		physpage_t dst_page;
		struct mchunk *src_chunks;
		dst_page   = dst->mp_mem.mc_start;
		src_chunks = src->mp_mem_sc.ms_v;
		for (i = 0;; ++i) {
			size_t count;
			assert(i < src->mp_mem_sc.ms_c);
			count = src_chunks[i].mc_size;
			if (src_offset != 0) {
				if (src_offset >= (count * PAGESIZE)) {
					src_offset -= (count * PAGESIZE);
					continue;
				}
				count -= src_offset / PAGESIZE;
			}
			if (count > num_pages)
				count = num_pages;
			copypagesinphys(physpage2addr(dst_page),
			                physpage2addr(src_chunks[i].mc_start) + src_offset,
			                count);
			if (count >= num_pages)
				break;
			src_offset = 0;
			num_pages -= count;
			dst_page += count;
		}
	} else {
		/* MULTIPLE --> MULTIPLE */
		size_t dst_i, src_i, dst_count;
		struct mchunk *dst_chunks;
		struct mchunk *src_chunks;
		struct mchunk src_chunk;
		dst_count  = dst->mp_mem_sc.ms_c;
		dst_chunks = dst->mp_mem_sc.ms_v;
		src_chunks = src->mp_mem_sc.ms_v;
		src_i = 1, src_chunk = src_chunks[0];
		for (dst_i = 0;; ++dst_i) {
			struct mchunk b;
			assert(dst_i < dst_count);
			b = dst_chunks[dst_i];
			while (b.mc_size) {
				size_t count;
				if (!src_chunk.mc_size) {
next_src_chunk:
					assert(src_i < src->mp_mem_sc.ms_c);
					src_chunk = src_chunks[src_i++];
				}
				if (src_offset != 0) {
					if (src_offset >= (src_chunk.mc_size * PAGESIZE)) {
						src_offset -= (src_chunk.mc_size * PAGESIZE);
						goto next_src_chunk;
					}
					src_chunk.mc_start += src_offset / PAGESIZE;
					src_chunk.mc_size -= src_offset / PAGESIZE;
					src_offset = 0;
				}
				assert(src_chunk.mc_size != 0);
				count = b.mc_size;
				if (count > src_chunk.mc_size)
					count = src_chunk.mc_size;
				if (count > num_pages)
					count = num_pages;
				copypagesinphys(physpage2addr(b.mc_start),
				                physpage2addr(src_chunk.mc_start),
				                count);
				if (count >= num_pages)
					return;
				num_pages -= count;
				src_chunk.mc_start += count;
				src_chunk.mc_size -= count;
				b.mc_start += count;
				b.mc_size -= count;
			}
		}
	}
}





struct unsharecow_bounds {
	/*PAGEDIR_PAGEALIGNED*/ mpart_reladdr_t ucb_mapmin;  /* The lowest (part-relative) address mapped by copy-on-write nodes. */
	mpart_reladdr_t                         ucb_mapmax;  /* The greatest (part-relative) address mapped by copy-on-write nodes. */
	/*PAGEDIR_PAGEALIGNED*/ size_t          ucb_mapsize; /* == (ucb_mapmax - ucb_mapmin) + 1. */
};


/* Calculate the max-size needed to represent `part'. */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL unsharecow_calculate_mapbounds)(struct unsharecow_bounds *__restrict self,
                                              struct mpart *__restrict part,
                                              mpart_reladdr_t minaddr,
                                              mpart_reladdr_t maxaddr) {
	struct mnode *node;
	self->ucb_mapmin = (mpart_reladdr_t)-1;
	self->ucb_mapmax = 0;
	LIST_FOREACH (node, &part->mp_copy, mn_link) {
		mpart_reladdr_t min, max;
		if (!mnode_ismapping(node, minaddr, maxaddr))
			continue;
		if (wasdestroyed(node->mn_mman))
			continue;
		min = mnode_getpartminaddr(node);
		max = mnode_getpartmaxaddr(node);
		if (self->ucb_mapmin > min)
			self->ucb_mapmin = min;
		if (self->ucb_mapmax < max)
			self->ucb_mapmax = max;
	}
	assert(self->ucb_mapmin < self->ucb_mapmax);
	assert(IS_ALIGNED(self->ucb_mapmin, PAGESIZE));
	assert(IS_ALIGNED(self->ucb_mapmax + 1, PAGESIZE));
	self->ucb_mapsize = 1 + (self->ucb_mapmax - self->ucb_mapmin);
}


/* Ensure that `data->ucd_copy' has been allocated.
 * If it hasn't been allocated yet,  and doing so cannot be  done
 * without blocking, then the lock to `self' is released, and the
 * allocation is performed with blocking. Stores the results  in:
 *   - data->ucd_copy
 * Throws an exception on error.
 * @return: true:  Success
 * @return: false: Success, but the lock to `self' was lost */
INTERN WUNUSED NONNULL((1, 3)) bool FCALL
unsharecow_makecopy_or_unlock(struct mpart *__restrict self,
                              struct unlockinfo *unlock,
                              struct mpart_unsharecow_data *__restrict data) {
	struct mpart *copy;
	if unlikely(data->ucd_copy != NULL)
		goto done;

	/* Try to allocate the copy. */
	copy = (struct mpart *)kmalloc_nx(sizeof(struct mpart),
	                                  GFP_LOCKED | GFP_ATOMIC |
	                                  GFP_PREFLT);
	if unlikely(!copy) {
		/* Must allocate while blocking. */
		UNLOCK(self, unlock);
		copy = (struct mpart *)kmalloc(sizeof(struct mpart),
		                               GFP_LOCKED | GFP_PREFLT);
		data->ucd_copy = copy;
		return false;
	}
	data->ucd_copy = copy;
done:
	return true;
}

/* If necessary, allocate an extended block-status bitset needed to hold
 * the data for a copy of `self'. If such a bitset isn't necessary, then
 * don't do anything. Stores the results in:
 *   - data->ucd_ucmem.scd_bitset
 * Throws an exception on error.
 * @return: true:  Success
 * @return: false: Success, but the lock to `self' was lost */
INTERN WUNUSED NONNULL((1, 3)) bool FCALL
unsharecow_makeblkext_or_unlock(struct mpart *__restrict self,
                                struct unlockinfo *unlock,
                                struct mpart_unsharecow_data *__restrict data,
                                PAGEDIR_PAGEALIGNED size_t num_bytes) {
	size_t block_count, reqsize;
	mpart_blkst_word_t *bitset;

	/* We need to copy the block-status bitset. */
	block_count = num_bytes >> self->mp_file->mf_blockshift;
	if (block_count <= MPART_BLKST_BLOCKS_PER_WORD)
		return true; /* A single word is enough! */
	if (self->mp_blkst_ptr == NULL)
		return true; /* We can just mirror the NULL-bitset. */

	/* This is the case where we need the dynamically allocated block-status bitset. */
	reqsize = CEILDIV(block_count, MPART_BLKST_BLOCKS_PER_WORD) * sizeof(mpart_blkst_word_t);
	bitset  = (mpart_blkst_word_t *)krealloc_nx(data->ucd_ucmem.scd_bitset, reqsize,
	                                            GFP_LOCKED | GFP_ATOMIC | GFP_PREFLT);
	if unlikely(!bitset) {
		/* Must allocate while blocking. */
		UNLOCK(self, unlock);
		bitset = (mpart_blkst_word_t *)krealloc(data->ucd_ucmem.scd_bitset, reqsize,
		                                        GFP_LOCKED | GFP_PREFLT);
		data->ucd_ucmem.scd_bitset = bitset;
		return false;
	}
	data->ucd_ucmem.scd_bitset = bitset;
	return true;
}


/* Allocate physical memory for exactly `data->ucd_partsize' bytes of
 * memory, and store the results in:
 *   - data->ucd_copy_state
 *   - data->ucd_copy_mem
 *   - data->ucd_copy_mem_sc
 * Throws an exception on error.
 * @return: true:  Success
 * @return: false: Success, but the lock to `self' was lost */
INTERN WUNUSED NONNULL((1, 3)) bool FCALL
unsharecow_makememdat_or_unlock(struct mpart *__restrict self,
                                struct unlockinfo *unlock,
                                struct mpart_unsharecow_data *__restrict data,
                                PAGEDIR_PAGEALIGNED size_t num_bytes) {
	bool result;
	size_t total_pages;
	assert(IS_ALIGNED(num_bytes, PAGESIZE));
	total_pages = num_bytes / PAGESIZE;
	result = mpart_setcore_makememdat_or_unlock(self, unlock,
	                                            &data->ucd_ucmem,
	                                            total_pages);
	return result;
}


PRIVATE NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL unsharecow_has_mapping_nodes)(struct mpart *__restrict part,
                                            mpart_reladdr_t minaddr,
                                            mpart_reladdr_t maxaddr) {
	struct mnode *node;
	LIST_FOREACH (node, &part->mp_copy, mn_link) {
		if (mnode_ismapping(node, minaddr, maxaddr)) {
			if (!wasdestroyed(node->mn_mman))
				return true;
		}
	}
	return false;
}


/* Incref all of the mmans of copy-on-write nodes.
 * Dead mmans are silently ignored (returns `false' if all mmans are dead) */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) bool
NOTHROW(FCALL unsharecow_incref_mmans)(struct mpart *__restrict part,
                                       mpart_reladdr_t minaddr,
                                       mpart_reladdr_t maxaddr) {
	bool result = false;
	struct mnode *node;
	LIST_FOREACH (node, &part->mp_copy, mn_link) {
		if (mnode_ismapping(node, minaddr, maxaddr)) {
			if (tryincref(node->mn_mman))
				result = true;
		}
	}
	return result;
}

/* Decref all of  the mmans  of copy-on-write  nodes.
 * mmans that were already dead are silently ignored. */
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL unsharecow_decref_mmans)(struct mpart *__restrict part,
                                       mpart_reladdr_t minaddr,
                                       mpart_reladdr_t maxaddr) {
	struct mnode *node;
	LIST_FOREACH (node, &part->mp_copy, mn_link) {
		if (mnode_ismapping(node, minaddr, maxaddr)) {
			if (!wasdestroyed(node->mn_mman))
				decref_unlikely(node->mn_mman);
		}
	}
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL unsharecow_decref_mmans_fast)(struct mpart *__restrict part) {
	struct mnode *node;
	LIST_FOREACH (node, &part->mp_copy, mn_link) {
		decref_unlikely(node->mn_mman);
	}
}

PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1, 2, 3)) bool
NOTHROW(FCALL mnode_list_contains_mman_until)(struct mnode const *start_node,
                                              struct mnode const *stop_node,
                                              struct mman const *__restrict mm,
                                              mpart_reladdr_t minaddr,
                                              mpart_reladdr_t maxaddr) {
	while (start_node != stop_node) {
		if (mnode_ismapping(start_node, minaddr, maxaddr)) {
			if (start_node->mn_mman == mm)
				return true;
		}
		start_node = LIST_NEXT(start_node, mn_link);
	}
	return false;
}

PRIVATE NOBLOCK ATTR_PURE WUNUSED NONNULL((1, 2, 3)) bool
NOTHROW(FCALL mnode_list_contains_mman_until_fast)(struct mnode const *start_node,
                                                   struct mnode const *stop_node,
                                                   struct mman const *__restrict mm) {
	while (start_node != stop_node) {
		if (start_node->mn_mman == mm)
			return true;
		start_node = LIST_NEXT(start_node, mn_link);
	}
	return false;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL unsharecow_unlock_unique_mmans_until)(struct mpart *__restrict part,
                                                    struct mnode *stop_node,
                                                    mpart_reladdr_t minaddr,
                                                    mpart_reladdr_t maxaddr) {
	struct mnode *node;
	for (node = LIST_FIRST(&part->mp_copy); node != stop_node;
	     node = LIST_NEXT(node, mn_link)) {
		struct mman *mm;
		if (!mnode_ismapping(node, minaddr, maxaddr))
			continue;
		mm = node->mn_mman;
		if (wasdestroyed(mm))
			continue;

		/* Check if we've already seen this mman */
		if (mnode_list_contains_mman_until(LIST_FIRST(&part->mp_copy),
		                                   node, mm, minaddr, maxaddr))
			continue;
		mman_lock_release(mm);
	}
}

#define unsharecow_unlock_unique_mmans(part, minaddr, maxaddr) \
	unsharecow_unlock_unique_mmans_until(part, NULL, minaddr, maxaddr)

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL unsharecow_unlock_unique_mmans_fast)(struct mpart *__restrict part) {
	struct mnode *node;
	LIST_FOREACH (node, &part->mp_copy, mn_link) {
		struct mman *mm = node->mn_mman;
		assert(!wasdestroyed(mm));

		/* Check if we've already seen this mman */
		if (mnode_list_contains_mman_until_fast(LIST_FIRST(&part->mp_copy),
		                                        node, mm))
			continue;
		mman_lock_release(mm);
	}
}

/* Acquire locks to all of the memory-managers in use by copy-on-write nodes of `part' */
PRIVATE WUNUSED NONNULL((1)) bool FCALL
unsharecow_lock_unique_mmans_or_unlock(struct mpart *__restrict part,
                                       struct unlockinfo *unlock,
                                       mpart_reladdr_t minaddr,
                                       mpart_reladdr_t maxaddr) {
	struct mnode *node;
	LIST_FOREACH (node, &part->mp_copy, mn_link) {
		struct mman *mm;
		if (!mnode_ismapping(node, minaddr, maxaddr))
			continue;
		mm = node->mn_mman;
		if (wasdestroyed(mm))
			continue;

		/* Check if we've already seen this mman */
		if (mnode_list_contains_mman_until(LIST_FIRST(&part->mp_copy),
		                                   node, mm, minaddr, maxaddr))
			continue;

		if (!mman_lock_tryacquire(mm)) {
			/* Found one that can't be locked immediately.
			 * -> Unlock all others and drop already-gathered references. */
			unsharecow_unlock_unique_mmans_until(part, node, minaddr, maxaddr);

			/* Drop our lock to the original part. */
			UNLOCK(part, unlock);

			/* Wait until the lock of this mman becomes available. */
			mman_lock_waitfor(mm);
			return false;
		}
	}
	return true;
}

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL unprepare_mmans_until)(struct mnode *start_node,
                                     struct mnode *stop_node,
                                     mpart_reladdr_t minaddr,
                                     mpart_reladdr_t maxaddr) {
	for (; start_node != stop_node; start_node = LIST_NEXT(start_node, mn_link)) {
		if (!mnode_ismapping(start_node, minaddr, maxaddr))
			continue;
		if unlikely(wasdestroyed(start_node->mn_mman))
			continue; /* Skip dead nodes. */
		if (start_node->mn_flags & (MNODE_F_MPREPARED | MNODE_F_UNMAPPED))
			continue; /* Skip nodes always prepared, or ones that were unmapped. */
		pagedir_unprepare_p(start_node->mn_mman->mm_pagedir_p,
		                    mnode_getaddr(start_node),
		                    mnode_getsize(start_node));
	}
}

/* Prepare the backing memory of all page directories with copy-on-write mappings,
 * such that those  regions may  atomically be replaced  with different  bindings.
 * If this cannot be done, release all locks and throw an exception. */
PRIVATE WUNUSED NONNULL((1)) bool FCALL
try_prepare_mmans_or_throw(struct mpart *__restrict self,
                           struct unlockinfo *unlock,
                           mpart_reladdr_t minaddr,
                           mpart_reladdr_t maxaddr) {
	struct mnode *node;
	bool result = false;
	LIST_FOREACH (node, &self->mp_copy, mn_link) {
		if (!mnode_ismapping(node, minaddr, maxaddr))
			continue;
		if unlikely(wasdestroyed(node->mn_mman))
			continue; /* Skip dead nodes. */
		if unlikely(node->mn_flags & MNODE_F_UNMAPPED)
			continue; /* Skip nodes that were unmapped. */
		if (!(node->mn_flags & MNODE_F_MPREPARED)) {
			/* Prepare the page directory. */
			if unlikely(!pagedir_prepare_p(node->mn_mman->mm_pagedir_p,
			                               mnode_getaddr(node),
			                               mnode_getsize(node)))
				goto err_badalloc;
		}
		result = true;
	}
	return result;

err_badalloc:
	/* Insufficient physical memory...
	 * -> Unprepare everything we've already prepared thus far,
	 *    then proceed by throwing an exception! */
	unprepare_mmans_until(LIST_FIRST(&self->mp_copy), node, minaddr, maxaddr);
	unsharecow_unlock_unique_mmans(self, minaddr, maxaddr);
	_mpart_lock_release(self);
	unlockinfo_xunlock(unlock);
	mpart_lockops_reap(self);
	THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
}




/* Ensure that `LIST_EMPTY(&self->mp_copy)' (while only considering nodes
 * which   may   be   overlapping   with   the   given   address   range)
 * NOTE: The  caller must first ensure that `MPART_ST_INCORE(self->mp_state)',
 *       otherwise this function will result in an internal assertion failure.
 * NOTE: The `LIST_EMPTY(&self->mp_copy)' mustn't be seen ~too~ strictly, as
 *       the list is still allowed to contain dead nodes that are about  to,
 *       or have already been added as lock-ops to `mp_lockops'.
 *       However, the mmans of all nodes still apart of the mp_copy list have
 *       already been destroyed, such that  no alive copy-nodes still  exist! */
PUBLIC BLOCKING WUNUSED NONNULL((1, 3)) bool FCALL
mpart_unsharecow_or_unlock(struct mpart *__restrict self,
                           struct unlockinfo *unlock,
                           struct mpart_unsharecow_data *__restrict data,
                           mpart_reladdr_t partrel_offset, size_t num_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	/* Instead of unsharing _all_ copy-on-write mappings, extend this function to
	 * only  unshare those that  are mapping pages from  a specific sub-region of
	 * the given mem-part (where  copy-on-write mem-nodes overlap partially  with
	 * the sub-region being unshared, those mem-nodes should be split) */
	struct mpart *copy;
	struct mnode *node;
	size_t block_count;
	struct unsharecow_bounds bounds;
	mpart_reladdr_t partrel_minaddr;
	mpart_reladdr_t partrel_maxaddr;

	assert(MPART_ST_INCORE(self->mp_state));

	/* Quick check: If there aren't any copy-on-write mappings, then
	 *              we  don't  actually  need to  do  anything else! */
	if (LIST_EMPTY(&self->mp_copy))
		goto done_simple;

	/* Slightly slower check: Are there any copy-on-write nodes
	 * that map at least 1  byte from the given address  range? */
	partrel_minaddr = partrel_offset;
	partrel_maxaddr = partrel_offset + num_bytes - 1;
	if (!unsharecow_has_mapping_nodes(self, partrel_minaddr, partrel_maxaddr))
		goto done_simple; /* Nothing is mapping the range that should be unshared, so nothing to do! */


	/* Make sure to load all blocks (if necessary), and also make sure
	 * that there aren't any INIT-blocks left */
	if (!mpart_load_or_unlock(self, unlock, partrel_offset, num_bytes))
		goto nope;
	assert(!LIST_EMPTY(&self->mp_copy));

	/* Try to acquire references to all of the mmans from the copy-on-write  list.
	 * If we fail to do this for all of them, then we're already done, since there
	 * are no (alive) copy-on-write mappings present! */
	if (!unsharecow_incref_mmans(self, partrel_minaddr, partrel_maxaddr))
		goto done_simple;

	/* Calculate the max-address needed to represent `self' */
	unsharecow_calculate_mapbounds(&bounds, self, partrel_minaddr, partrel_maxaddr);
	TRY {

		if (!unsharecow_makecopy_or_unlock(self, unlock, data))
			goto nope_decref_mmans;

		/* Allocate the block-extension bitset. */
		if (!unsharecow_makeblkext_or_unlock(self, unlock, data, bounds.ucb_mapsize))
			goto nope_decref_mmans;

		/* Allocate low-level ram data. */
		if (!unsharecow_makememdat_or_unlock(self, unlock, data, bounds.ucb_mapsize))
			goto nope_decref_mmans;

		/* (almost) lastly, acquire references & locks to all of the memory-managers
		 * associated   with   nodes   from   the   copy-on-write   mappings   list. */
		if (!unsharecow_lock_unique_mmans_or_unlock(self, unlock, partrel_minaddr, partrel_maxaddr))
			goto nope_decref_mmans;

		/* And finally, make sure that we'll be able to re-map the  backing
		 * page directory mappings of all of the copy-on-write nodes. After
		 * all: we _do_ intend to replace them with our new copy. */
		if (!try_prepare_mmans_or_throw(self, unlock, partrel_minaddr, partrel_maxaddr)) {
			/* Special case: All nodes had been destroyed! */
			unsharecow_unlock_unique_mmans(self, partrel_minaddr, partrel_maxaddr);
			_mpart_lock_release(self);
			unlockinfo_xunlock(unlock);
			mpart_lockops_reap(self);
			goto nope_decref_mmans;
		}
	} EXCEPT {
		unsharecow_decref_mmans(self, partrel_minaddr, partrel_maxaddr);
		RETHROW();
	}

	/* Point of no return: We've allocated and verified everything that we
	 * could possibly need. - Now we just have to put everything together.
	 *
	 * Also note that at this point, we're holding a whole bunch of locks:
	 *   - A lock to `self'
	 *   - A lock to every (unique) mman from `self->mp_copy'
	 */

	/* Step #1: Gather up all of the copy-on-write nodes. (and skip nodes
	 *          that belong to dead mmans) */
	assert(!LIST_EMPTY(&self->mp_copy));
	copy = data->ucd_copy;
	DBG_memset(&data->ucd_copy, 0xcc, sizeof(data->ucd_copy));
	copy->mp_refcnt = 0;
	LIST_INIT(&copy->mp_copy);
	for (node = LIST_FIRST(&self->mp_copy); node;) {
		struct mnode *next_node;
		next_node = LIST_NEXT(node, mn_link);
		if (mnode_ismapping(node, partrel_minaddr, partrel_maxaddr)) {
			if likely(!wasdestroyed(node->mn_mman)) {
				/* Transfer this node to the new mem-part. */
				assert(node->mn_part == self);
				LIST_INSERT_HEAD(&copy->mp_copy, node, mn_link);
				++copy->mp_refcnt;   /* New reference (to-be) held by `node->mn_part' */
				decref_nokill(self); /* Old reference held by `node->mn_part' */
			}
		}
		node = next_node;
	}
	assert(!LIST_EMPTY(&copy->mp_copy));
	assert(copy->mp_refcnt != 0);
	assert(bounds.ucb_mapsize != 0);

	/* Initialize misc. fields of the mem-part copy. */
	copy->mp_xflags = MPART_XF_NORMAL;
	copy->mp_flags  = (self->mp_flags & MPART_F_MLOCK) | MPART_F_LOCKBIT;
	copy->mp_file   = incref(&mfile_anon[self->mp_file->mf_blockshift]);
	LIST_INIT(&copy->mp_share);
	SLIST_INIT(&copy->mp_lockops);
	DBG_memset(&copy->mp_changed, 0xcc, sizeof(copy->mp_changed));
	copy->mp_minaddr = self->mp_minaddr + bounds.ucb_mapmin;
	copy->mp_maxaddr = self->mp_minaddr + bounds.ucb_mapmax;
	assert(copy->mp_maxaddr <= self->mp_maxaddr);
	_mpart_init_asanon(copy);

	/* We need to copy the block-status bitset. */
	block_count = bounds.ucb_mapsize >> copy->mp_file->mf_blockshift;
	if (block_count <= MPART_BLKST_BLOCKS_PER_WORD) {
		/* A single word is enough! */
		mpart_blkst_word_t word;
		word = self->mp_blkst_inl;
		if (!(self->mp_flags & MPART_F_BLKST_INL)) {
			word = MPART_BLOCK_REPEAT(MPART_BLOCK_ST_CHNG);
			if (self->mp_blkst_ptr != NULL)
				word = self->mp_blkst_ptr[0];
		}
		copy->mp_blkst_inl = word;
		copy->mp_flags |= MPART_F_BLKST_INL;
free_unused_block_status:
		if unlikely(data->ucd_ucmem.scd_bitset)
			kfree(data->ucd_ucmem.scd_bitset);
		DBG_memset(&data->ucd_ucmem.scd_bitset, 0xcc,
		           sizeof(data->ucd_ucmem.scd_bitset));
	} else if (self->mp_blkst_ptr == NULL) {
		copy->mp_blkst_ptr = NULL;
		goto free_unused_block_status;
	} else {
		/* This is the case where we need the dynamically allocated block-status bitset. */
		assert(data->ucd_ucmem.scd_bitset != NULL);
		assert((kmalloc_usable_size(data->ucd_ucmem.scd_bitset) *
		        MPART_BLKST_BLOCKS_PER_WORD) >= block_count);
		assert(block_count <= mpart_getblockcount(self, self->mp_file));

		/* Copy over block-status bitset data. */
		copy->mp_blkst_ptr = (mpart_blkst_word_t *)memcpy(data->ucd_ucmem.scd_bitset,
		                                                  self->mp_blkst_ptr,
		                                                  block_count / MPART_BLKST_BLOCKS_PER_WORD,
		                                                  sizeof(mpart_blkst_word_t));
		DBG_memset(&data->ucd_ucmem.scd_bitset, 0xcc,
		           sizeof(data->ucd_ucmem.scd_bitset));
	}

	/* Fill in information on the backing storage. */
	copy->mp_state = data->ucd_ucmem.scd_copy_state;
	DBG_memset(&data->ucd_ucmem.scd_bitset, 0xcc,
	           sizeof(data->ucd_ucmem.scd_bitset));
	memcpy(&copy->mp_mem,
	       &data->ucd_ucmem.scd_copy_mem,
	       MAX_C(sizeof(struct mchunk),
	             sizeof(struct mchunkvec)));
	DBG_memset(&data->ucd_ucmem.scd_copy_mem, 0xcc,
	           MAX_C(sizeof(struct mchunk),
	                 sizeof(struct mchunkvec)));

	/* For now, we don't copy mem-part meta-data. */
	copy->mp_meta = NULL;

	/* With that, the new mem-part has been initialized, however we must
	 * still copy over the  contents of the old  part into the new  one! */
	mpart_copyram(copy, self,
	              bounds.ucb_mapmin,
	              bounds.ucb_mapsize / PAGESIZE);

	/* Tell  all of the pre-existing nodes about the new backing part!
	 * We do this only now, so-as to ensure that we directly jump from
	 * one completely valid mem-part to another. */
	LIST_FOREACH (node, &copy->mp_copy, mn_link) {
		node->mn_partoff -= bounds.ucb_mapmin;
		node->mn_part = copy;
	}

	/* With all of the software-structures updated to describe the new,
	 * valid state, time to have the hardware match us by updating  the
	 * underlying page directories. */
	{
		pagedir_prot_t prot_mask = PAGEDIR_PROT_EXEC | PAGEDIR_PROT_WRITE | PAGEDIR_PROT_READ;
		assert(!LIST_EMPTY(&copy->mp_copy));

		/* We can map as writable if only a single copy-on-write node exists! */
		if (LIST_NEXT(LIST_FIRST(&copy->mp_copy), mn_link) != NULL)
			prot_mask &= ~PAGEDIR_PROT_WRITE;
		LIST_FOREACH (node, &copy->mp_copy, mn_link) {
			struct mman *mm;
			void *addr;
			size_t size;
			pagedir_prot_t prot;
			static_assert(PAGEDIR_PROT_EXEC == MNODE_F_PEXEC);
			static_assert(PAGEDIR_PROT_WRITE == MNODE_F_PWRITE);
			static_assert(PAGEDIR_PROT_READ == MNODE_F_PREAD);
			assert(mnode_ismapping(node, partrel_minaddr, partrel_maxaddr));
			mm = node->mn_mman;
			assert(!wasdestroyed(mm));

			/* Updated virtual memory mappings to point to the copied area. */
			addr = mnode_getaddr(node);
			size = mnode_getsize(node);
			prot = node->mn_flags & prot_mask;
			prot = mpart_mmap_p(copy, mm->mm_pagedir_p, addr,
			                    size, node->mn_partoff, prot);

			/* Make sure that the node's writable-bound-state is correct. */
			if unlikely(prot & PAGEDIR_PROT_WRITE) {
				if (!LIST_ISBOUND(node, mn_writable))
					LIST_INSERT_HEAD(&mm->mm_writable, node, mn_writable);
			} else {
				if (LIST_ISBOUND(node, mn_writable))
					LIST_UNBIND(node, mn_writable);
			}

			if (!(node->mn_flags & MNODE_F_MPREPARED)) {
				/* With the new mapping in place, unprepare the page directory. */
				pagedir_unprepare_p(mm->mm_pagedir_p, addr, size);
			}

			/* Sync memory within the affected area. After all: The backing
			 * physical memory location just changed, so we must flush  tlb
			 * caches! */
			mman_sync_p(mm, addr, size);
		}
		if (prot_mask & PAGEDIR_PROT_WRITE) {
			/* Insert the (only) writable node into it's mman's writable chain. */
			node = LIST_FIRST(&copy->mp_copy);
			if (node->mn_flags & MNODE_F_PWRITE)
				LIST_INSERT_HEAD(&node->mn_mman->mm_writable, node, mn_writable);
		}
	}

	/* Add the new part to the global list of parts. Once this has been done,
	 * some  other thread may  immediately attempt to  off-load the part into
	 * swap, or do some other unspeakable things to it...
	 *
	 * In other words: We need to be damn sure we've finished initializing it! */
	COMPILER_WRITE_BARRIER();
	mpart_all_list_insert(copy);

	/* Drop  locks  to all  of  the new  part's  copy-on-write nodes.
	 * Note that we still have to be careful here to only unlock each
	 * unique mman once, since a single mman may have mapped our part
	 * multiple times. */
	unsharecow_unlock_unique_mmans_fast(copy);

	/* Drop all of the mman-references that we were still holding on to. */
	unsharecow_decref_mmans_fast(copy);

	/* Finally, release  one last  lock  from the  new  mem-part
	 * (but keep on holding onto our lock to the original part!) */
	mpart_lock_release(copy);

	return true;
done_simple:
	mpart_unsharecow_data_fini(data);
	return true;
nope_decref_mmans:
	unsharecow_decref_mmans(self, partrel_minaddr, partrel_maxaddr);
nope:
	return false;
}

/* Ensure that:
 * >> LIST_FOREACH (node, &self->mp_share, mn_link)
 * >>     mnode_clear_write(node) == MNODE_CLEAR_WRITE_SUCCESS
 * Note that when `!mpart_isanon(self)', any nodes apart of `mp_copy' wouldn't
 * have gotten write-access to begin with (since this requires such a node  to
 * create its own private copy  of `self'), so it  is sufficient to only  deny
 * write access  to MNODE_F_SHARED-nodes  in order  to ensure  that no  memory
 * mappings exist that may still have write-access! */
PUBLIC WUNUSED NONNULL((1)) bool FCALL
mpart_denywrite_or_unlock(struct mpart *__restrict self,
                          struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY) {
	struct mnode *node;

	/* Enumerate all shared nodes in order to delete write-access from them. */
	LIST_FOREACH (node, &self->mp_share, mn_link) {
		unsigned int error;
again_try_clear_write:
		error = mnode_clear_write(node);
		if likely(error == MNODE_CLEAR_WRITE_SUCCESS)
			continue;
		if (error == MNODE_CLEAR_WRITE_WOULDBLOCK) {
			REF struct mman *mm;

			/* Must wait for the node's mman to become available */
			mm = node->mn_mman;
			if unlikely(!tryincref(mm))
				goto again_try_clear_write;
			_mpart_lock_release(self);
			unlockinfo_xunlock(unlock);
			mpart_lockops_reap(self);
			FINALLY_DECREF_UNLIKELY(mm);
			mman_lock_waitfor(mm);
			return false;
		}

		/* Hard error: bad allocation :( */
		assert(error == MNODE_CLEAR_WRITE_BADALLOC);
		_mpart_lock_release(self);
		unlockinfo_xunlock(unlock);
		mpart_lockops_reap(self);
		THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
	}
	return true;
}








/************************************************************************/
/* Lock acquisition functions                                           */
/************************************************************************/

/* Acquire a lock until:
 *  - mpart_initdone_or_unlock(self, ...) */
PUBLIC BLOCKING NONNULL((1)) void FCALL
mpart_lock_acquire_and_initdone(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	do {
		mpart_lock_acquire(self);
	} while (!mpart_initdone_or_unlock(self, NULL));
}

/* Acquire a lock until:
 *  - mpart_initdone_or_unlock(self, ...)
 *  - mpart_nodma_or_unlock(self, ...) */
PUBLIC BLOCKING NONNULL((1)) void FCALL
mpart_lock_acquire_and_initdone_nodma(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	do {
		mpart_lock_acquire(self);
	} while (!mpart_initdone_or_unlock(self, NULL) ||
	         !mpart_nodma_or_unlock(self, NULL));
}



/* Acquire a lock until:
 *  - mpart_setcore_or_unlock(self, ...) */
PUBLIC BLOCKING NONNULL((1)) void FCALL
mpart_lock_acquire_and_setcore(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	struct mpart_setcore_data data;
	mpart_lock_acquire(self);

	/* Quick check: is the part already in the expected state? */
	if (MPART_ST_INCORE(self->mp_state))
		return; /* Already done! */
	mpart_setcore_data_init(&data);
	TRY {
		while (!mpart_setcore_or_unlock(self, NULL, &data))
			mpart_lock_acquire(self);
	} EXCEPT {
		mpart_setcore_data_fini(&data);
		mpart_lockops_reap(self);
		RETHROW();
	}
}



/* Acquire a lock until:
 *  - mpart_setcore_or_unlock(self, ...)
 *  - mpart_load_or_unlock(self, ...)    // Based on the given address range
 *
 * If  the given `filepos' isn't contained by  `self', then no lock is acquired,
 * and `false' is returned. (`max_load_bytes' is only used as a hint for the max
 * # of bytes that may need to be loaded)
 *
 * HINT: This function is used to implement `mpart_read()' */
PUBLIC BLOCKING WUNUSED NONNULL((1)) bool FCALL
mpart_lock_acquire_and_setcore_load(struct mpart *__restrict self,
                                    pos_t filepos, size_t max_load_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	mpart_reladdr_t reladdr;
	struct mpart_setcore_data data;
	size_t loadbytes;
again:
	mpart_lock_acquire(self);

	/* Check if the given address range is in-bounds. */
	if (OVERFLOW_USUB(filepos, mpart_getminaddr(self), &reladdr))
		goto unlock_and_err;
	if (OVERFLOW_USUB(mpart_getmaxaddr(self), filepos, &loadbytes))
		goto unlock_and_err;

	/* Check: is the part already in the expected state? */
	if (!MPART_ST_INCORE(self->mp_state)) {
		mpart_setcore_data_init(&data);
		TRY {
			while (!mpart_setcore_or_unlock(self, NULL, &data)) {
				mpart_lock_acquire(self);

				/* Check if the given address range is in-bounds. */
				if (OVERFLOW_USUB(filepos, mpart_getminaddr(self), &reladdr))
					goto unlock_and_fini_data_err;
				if (OVERFLOW_USUB(mpart_getmaxaddr(self), filepos, &loadbytes))
					goto unlock_and_fini_data_err;
			}
		} EXCEPT {
			mpart_setcore_data_fini(&data);
			mpart_lockops_reap(self);
			RETHROW();
		}
	}
	++loadbytes;
	if (loadbytes > max_load_bytes)
		loadbytes = max_load_bytes;

	/* As requested, ensure that the accessed address range is loaded. */
	if (!mpart_load_or_unlock(self, NULL, reladdr, loadbytes))
		goto again;
	return true;
unlock_and_fini_data_err:
	mpart_lock_release(self);
	mpart_setcore_data_fini(&data);
	goto err;
unlock_and_err:
	mpart_lock_release(self);
err:
	return false;
}





/* Acquire a lock until:
 *  - mpart_setcore_or_unlock(self, ...)
 *  - mpart_load_or_unlock(self, ...)        // Based on the given address range
 *  - mpart_unsharecow_or_unlock(self, ...)  // Based on the given address range
 *
 * If  the given `filepos' isn't contained by  `self', then no lock is acquired,
 * and `false' is returned. (`max_load_bytes' is only used as a hint for the max
 * # of bytes that may need to be unshared/loaded)
 *
 * HINT: This function is used to implement `mman_startdma()' */
PUBLIC BLOCKING WUNUSED NONNULL((1)) bool FCALL
mpart_lock_acquire_and_setcore_unsharecow_load(struct mpart *__restrict self,
                                               pos_t filepos, size_t max_load_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	bool result;
again:
	result = mpart_lock_acquire_and_setcore_unsharecow(self, filepos, max_load_bytes);
	if likely(result) {
		mpart_reladdr_t reladdr, loadbytes;
		reladdr   = (mpart_reladdr_t)(filepos - mpart_getminaddr(self));
		loadbytes = (mpart_reladdr_t)(mpart_getendaddr(self) - reladdr);
		if (loadbytes > max_load_bytes)
			loadbytes = max_load_bytes;
		if (!mpart_load_or_unlock(self, NULL, reladdr, loadbytes))
			goto again;
	}
	return result;
}



/* Acquire a lock until:
 *  - mpart_setcore_or_unlock(self, ...)
 *  - mpart_unsharecow_or_unlock(self, ...)  // Based on the given address range
 *
 * If  the given `filepos' isn't contained by  `self', then no lock is acquired,
 * and `false' is returned. (`max_load_bytes' is only used as a hint for the max
 * # of bytes that may need to be unshared/loaded)
 *
 * HINT: This function is used to implement `mman_startdma()' */
PUBLIC BLOCKING WUNUSED NONNULL((1)) bool FCALL
mpart_lock_acquire_and_setcore_unsharecow(struct mpart *__restrict self,
                                          pos_t filepos, size_t max_load_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	mpart_reladdr_t part_offs, part_size;
	mpart_lock_acquire(self);

	/* Check if the given `filepos' is in-bounds of `self' */
	if unlikely(OVERFLOW_USUB(filepos, mpart_getminaddr(self), &part_offs))
		goto unlock_and_err;
	if unlikely(OVERFLOW_USUB(mpart_getmaxaddr(self), filepos, &part_size))
		goto unlock_and_err;
	++part_size;
	if (part_size > max_load_bytes)
		part_size = max_load_bytes;

	/* Check for special case: Must also unshare copy-on-write mappings. */
	if (!LIST_EMPTY(&self->mp_copy)) {
		struct mpart_unsharecow_data uc_data;
ensure_setcore_with_unshare:
		/* Now load the part into the core, and ensure that
		 * copy-on-write  mappings   have  been   unshared. */
		mpart_unsharecow_data_init(&uc_data);
		TRY {
again_ensure_incore_for_write:
			if (!MPART_ST_INCORE(self->mp_state)) {
				struct mpart_setcore_data data;
				mpart_setcore_data_init(&data);
				TRY {
					while (!mpart_setcore_or_unlock(self, NULL, &data)) {
						mpart_lock_acquire(self);
						if unlikely(OVERFLOW_USUB(filepos, mpart_getminaddr(self), &part_offs) ||
						            OVERFLOW_USUB(mpart_getmaxaddr(self), filepos, &part_size)) {
							mpart_lock_release(self);
							mpart_setcore_data_fini(&data);
							goto fini_uc_data_and_done;
						}
						++part_size;
						if (part_size > max_load_bytes)
							part_size = max_load_bytes;
						if unlikely(LIST_EMPTY(&self->mp_copy))
							goto ensure_setcore_without_unshare;
					}
				} EXCEPT {
					mpart_setcore_data_fini(&data);
					mpart_lockops_reap(self);
					RETHROW();
				}
			}
			if (!mpart_unsharecow_or_unlock(self, NULL, &uc_data, part_offs, part_size)) {
				mpart_lock_acquire(self);
				if unlikely(OVERFLOW_USUB(filepos, mpart_getminaddr(self), &part_offs) ||
				            OVERFLOW_USUB(mpart_getmaxaddr(self), filepos, &part_size)) {
					mpart_lock_release(self);
fini_uc_data_and_done:
					mpart_unsharecow_data_fini(&uc_data);
					goto err;
				}
				++part_size;
				if (part_size > max_load_bytes)
					part_size = max_load_bytes;
				if unlikely(LIST_EMPTY(&self->mp_copy)) {
					mpart_unsharecow_data_fini(&uc_data);
					goto ensure_setcore_without_unshare;
				}
				goto again_ensure_incore_for_write;
			}
		} EXCEPT {
			mpart_unsharecow_data_fini(&uc_data);
			mpart_lockops_reap(self);
			RETHROW();
		}
	} else {
ensure_setcore_without_unshare:
		/* Make sure that in-core data is available. */
		if (!MPART_ST_INCORE(self->mp_state)) {
			struct mpart_setcore_data data;
			mpart_setcore_data_init(&data);
			TRY {
				while (!mpart_setcore_or_unlock(self, NULL, &data)) {
					mpart_lock_acquire(self);
					if unlikely(OVERFLOW_USUB(filepos, mpart_getminaddr(self), &part_offs) ||
					            OVERFLOW_USUB(mpart_getmaxaddr(self), filepos, &part_size)) {
						mpart_lock_release(self);
						mpart_setcore_data_fini(&data);
						goto err;
					}
					++part_size;
					if (part_size > max_load_bytes)
						part_size = max_load_bytes;
					/* Special case: Must also unshare copy-on-write mappings. */
					if unlikely(!LIST_EMPTY(&self->mp_copy))
						goto ensure_setcore_with_unshare;
				}
			} EXCEPT {
				mpart_setcore_data_fini(&data);
				mpart_lockops_reap(self);
				RETHROW();
			}
		}
	}

	return true;
unlock_and_err:
	mpart_lock_release(self);
err:
	return false;
}




/* Same as `mpart_lock_acquire_and_setcore()', but also ensure that no DMA locks
 * are  still being held, and that all shared mappings of the given mem-part are
 * no longer mapped with write permissions:
 * >> LIST_FOREACH (node, &self->mp_share, mn_link) {
 * >>     mnode_clear_write(node);
 * >> }
 * Note that copy-on-write (i.e. `&self->mp_copy')  nodes don't need to be  updated.
 * But also note that copy-on-write mappings usually prevent each other from gaining
 * write access, simply  by co-existing. Furthermore,  copy-on-write mappings  can't
 * gain write-access to underlying mem-parts if  those parts might be accessed  from
 * the outside world (which is the case when `!mpart_isanon(self)').
 *
 * In other words: The only case where there may still be a node associated with
 * `self' that has write-access, applies when:
 *   >> mpart_isanon(self) &&                        // Mem-part is anonymous
 *   >> LIST_EMPTY(&self->mp_share) &&               // No secondary shared mappings
 *   >> !LIST_EMPTY(&self->mp_copy) &&               // There is a copy-on-write mapping
 *   >> (LIST_NEXT(LIST_FIRST(&self->mp_copy), mn_link) == NULL) // There is exactly 1 copy-on-write mapping
 * In this case, the node described by `LIST_FIRST(&self->mp_copy)' may still have
 * write-access,  and continue to  modify the backing memory  of `self' after this
 * function was called.
 *
 * However, the purpose of  this function is to  be used by `mpart_sync()',  where
 * syncing an anonymous file wouldn't really make much sense (where the file being
 * anonymous is one  of the  conditions for  a writable  copy-on-write mapping  to
 * continue to exist) */
PUBLIC BLOCKING NONNULL((1)) void FCALL
mpart_lock_acquire_and_setcore_denywrite_nodma(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	do {
		mpart_lock_acquire_and_setcore(self);
	} while (!mpart_nodma_or_unlock(self, NULL) ||
	         !mpart_denywrite_or_unlock(self, NULL));
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_LOCK_C */
