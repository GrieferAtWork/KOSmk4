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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_LOCK_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_LOCK_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/mman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart.h>
#include <kernel/paging.h>
#include <kernel/swap.h>
#include <kernel/vm/phys.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/minmax.h>

#include <kos/except.h>

#include <assert.h>
#include <string.h>

DECL_BEGIN

#if __SIZEOF_POINTER__ == 4 && MPART_BLOCK_STBITS == 2
#define MPART_BLOCK_REPEAT(st) (__UINT32_C(0x55555555) * (st))
#elif __SIZEOF_POINTER__ == 8 && MPART_BLOCK_STBITS == 2
#define MPART_BLOCK_REPEAT(st) (__UINT64_C(0x5555555555555555) * (st))
#elif __SIZEOF_POINTER__ == 2 && MPART_BLOCK_STBITS == 2
#define MPART_BLOCK_REPEAT(st) (__UINT16_C(0x5555) * (st))
#elif __SIZEOF_POINTER__ == 1 && MPART_BLOCK_STBITS == 2
#define MPART_BLOCK_REPEAT(st) (__UINT8_C(0x55) * (st))
#elif __SIZEOF_POINTER__ == 4 && MPART_BLOCK_STBITS == 1
#define MPART_BLOCK_REPEAT(st) (__UINT32_C(0xffffffff) * (st))
#elif __SIZEOF_POINTER__ == 8 && MPART_BLOCK_STBITS == 1
#define MPART_BLOCK_REPEAT(st) (__UINT64_C(0xffffffffffffffff) * (st))
#elif __SIZEOF_POINTER__ == 2 && MPART_BLOCK_STBITS == 1
#define MPART_BLOCK_REPEAT(st) (__UINT16_C(0xffff) * (st))
#elif __SIZEOF_POINTER__ == 1 && MPART_BLOCK_STBITS == 1
#define MPART_BLOCK_REPEAT(st) (__UINT8_C(0xff) * (st))
#else
#error "Unsupported __SIZEOF_POINTER__ and/or MPART_BLOCK_STBITS"
#endif

#ifdef NDEBUG
#define DBG_memset(ptr, byte, num_bytes) (void)0
#else /* NDEBUG */
#define DBG_memset(ptr, byte, num_bytes) memset(ptr, byte, num_bytes)
#endif /* !NDEBUG */

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


#ifdef __INTELLISENSE__
typedef typeof(((struct mpart *)0)->mp_blkst_inl) bitset_word_t;
#else /* __INTELLISENSE__ */
#define bitset_word_t typeof(((struct mpart *)0)->mp_blkst_inl)
#endif /* !__INTELLISENSE__ */
#define BITSET_ITEMS_PER_WORD (BITSOF(bitset_word_t) / MPART_BLOCK_STBITS)


/************************************************************************/
/* MPart API to lock a part, alongside doing some other operations.     */
/************************************************************************/

struct setcore_data {
	unsigned int         scd_copy_state;  /* One of `MPART_ST_VOID', `MPART_ST_MEM' or `MPART_ST_MEM_SC' */
	union {
		struct mchunk    scd_copy_mem;    /* [valid_if(scd_copy_state == MPART_ST_MEM)] */
		struct mchunkvec scd_copy_mem_sc; /* [valid_if(scd_copy_state == MPART_ST_MEM_SC)] */
	};
};

#define setcore_data_init(self) \
	memset(self, 0, sizeof(struct setcore_data))
STATIC_ASSERT(MPART_ST_VOID == 0);

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL setcore_data_fini)(struct setcore_data *__restrict self) {
	switch (self->scd_copy_state) {

	case MPART_ST_MEM:
		mchunk_freemem(&self->scd_copy_mem);
		break;

	case MPART_ST_SWP_SC:
		mchunkvec_freemem(self->scd_copy_mem_sc.ms_v,
		                  self->scd_copy_mem_sc.ms_c);
		kfree(self->scd_copy_mem_sc.ms_v);
		break;

	default:
		break;
	}
}



/* Allocate physical memory for exactly `self->scd_partsize' bytes of
 * memory, and store the results in:
 *   - self->scd_copy_state
 *   - self->scd_copy_mem
 *   - self->scd_copy_mem_sc
 * Throws an exception on error.
 * @return: true:  Success
 * @return: false: Success, but the lock to `part' was lost */
PRIVATE NONNULL((1, 2)) bool FCALL
setcore_makememdat_or_unlock(struct setcore_data *__restrict self,
                             struct mpart *__restrict part,
                             size_t total_pages) {
	struct mchunk chunk, *vec;
	size_t done;
	if unlikely(self->scd_copy_state != MPART_ST_VOID) {
		/* Re-use already-allocated buffers. */
		assert(self->scd_copy_state == MPART_ST_MEM ||
		       self->scd_copy_state == MPART_ST_MEM_SC);
		if (self->scd_copy_state == MPART_ST_MEM) {
			if (total_pages == self->scd_copy_mem.mc_size)
				return true; /* Unchanged */
			if (total_pages < self->scd_copy_mem.mc_size) {
				page_ccfree(self->scd_copy_mem.mc_start + total_pages,
				            self->scd_copy_mem.mc_size - total_pages);
				self->scd_copy_mem.mc_size = total_pages;
				return true;
			}
			/* Must allocate more memory. (try re-try from the start) */
			page_ccfree(self->scd_copy_mem.mc_start,
			            self->scd_copy_mem.mc_size);
			self->scd_copy_state = MPART_ST_VOID;
		} else {
			/* A scatter-list had already been allocated in the past. */
			size_t i, old_total = 0;
			assert(self->scd_copy_mem_sc.ms_c != 0);
			for (i = 0; i < self->scd_copy_mem_sc.ms_c; ++i)
				old_total += self->scd_copy_mem_sc.ms_v[i].mc_size;
			if (total_pages == old_total)
				return true; /* Unchanged */
			if (total_pages < old_total) {
				size_t too_many = old_total - total_pages;
				i = self->scd_copy_mem_sc.ms_c - 1;
				/* Trim tailing pages. */
				while (too_many) {
				}
				assert(i <= self->scd_copy_mem_sc.ms_c);
				if (i == 0) {
					chunk = self->scd_copy_mem_sc.ms_v[0];
					kfree(self->scd_copy_mem_sc.ms_v);
					/* Transform into a single chunk. */
					self->scd_copy_mem   = chunk;
					self->scd_copy_state = MPART_ST_MEM;
				} else if (i < self->scd_copy_mem_sc.ms_c - 1) {
					struct mchunk *newvec;
					newvec = (struct mchunk *)krealloc_nx(self->scd_copy_mem_sc.ms_v,
					                                      (i + 1) * sizeof(struct mchunk),
					                                      GFP_LOCKED | GFP_ATOMIC | GFP_PREFLT);
					if likely(newvec)
						self->scd_copy_mem_sc.ms_v = newvec;
					self->scd_copy_mem_sc.ms_c = i + 1;
				}
				return true;
			}
			/* Must increase the size. */
			done = old_total;
			goto extend_vector;
		}
	}
	/* Try to allocate everything in a single page. */
	self->scd_copy_mem.mc_start = mfile_alloc_physmem(part->mp_file,
	                                                  total_pages,
	                                                  &self->scd_copy_mem.mc_size);
	if unlikely(self->scd_copy_mem.mc_start == PHYSPAGE_INVALID)
		goto err_badalloc; /* Insufficient physical memory. */
	assert(self->scd_copy_mem.mc_size != 0);
	assert(self->scd_copy_mem.mc_size <= total_pages);
	if likely(self->scd_copy_mem.mc_size >= total_pages) {
		/* Done: We've managed to allocate everything within a single chunk. */
		self->scd_copy_state = MPART_ST_MEM;
		return true;
	}
	/* Must allocate as scattered memory. */
	chunk = self->scd_copy_mem;
	vec = (struct mchunk *)kmalloc_nx(4 * sizeof(struct mchunk),
	                                  GFP_LOCKED | GFP_ATOMIC | GFP_PREFLT);
	if unlikely(!vec) {
		vec = (struct mchunk *)kmalloc_nx(2 * sizeof(struct mchunk),
		                                  GFP_LOCKED | GFP_ATOMIC | GFP_PREFLT);
		if unlikely(!vec) {
			mpart_lock_release_f(part);
			/* Must do the allocation with blocking */
			vec = (struct mchunk *)kmalloc_nx(4 * sizeof(struct mchunk),
			                                  GFP_LOCKED | GFP_PREFLT);
			if unlikely(!vec) {
				vec = (struct mchunk *)kmalloc(2 * sizeof(struct mchunk),
				                               GFP_LOCKED | GFP_PREFLT);
			}
			vec;
			self->scd_copy_mem_sc.ms_v = vec;
			self->scd_copy_mem_sc.ms_c = 1;
			self->scd_copy_state       = MPART_ST_MEM_SC;
			vec[0]                     = chunk;
			done                       = chunk.mc_size;
			for (;;) {
				size_t missing_pages, avail;
				assert(done < total_pages);
				missing_pages = total_pages - done;
				/* Make sure that there is sufficient space for one additional chunk. */
				avail = kmalloc_usable_size(self->scd_copy_mem_sc.ms_v) / sizeof(struct mchunk);
				assert(avail >= self->scd_copy_mem_sc.ms_c);
				if (avail <= self->scd_copy_mem_sc.ms_c) {
do_realloc_in_extend_after_unlock:
					vec = (struct mchunk *)krealloc(self->scd_copy_mem_sc.ms_v,
					                                (self->scd_copy_mem_sc.ms_c + 1) *
					                                sizeof(struct mchunk),
					                                GFP_LOCKED | GFP_PREFLT);
					self->scd_copy_mem_sc.ms_v = vec;
				}
				/* Allocate the new chunk. */
				chunk.mc_start = mfile_alloc_physmem(part->mp_file, total_pages, &chunk.mc_size);
				if unlikely(self->scd_copy_mem.mc_start == PHYSPAGE_INVALID)
					goto err_badalloc_after_unlock; /* Insufficient physical memory. */
				self->scd_copy_mem_sc.ms_v[self->scd_copy_mem_sc.ms_c] = chunk;
				++self->scd_copy_mem_sc.ms_c;
			}
		
			/* Try to truncate unused memory. */
			vec = (struct mchunk *)krealloc_nx(self->scd_copy_mem_sc.ms_v,
			                                   self->scd_copy_mem_sc.ms_c *
			                                   sizeof(struct mchunk),
			                                   GFP_LOCKED | GFP_PREFLT);
			if likely(vec != NULL)
				self->scd_copy_mem_sc.ms_v = vec;
			return false;
		}
	}
	self->scd_copy_mem_sc.ms_v = vec;
	self->scd_copy_mem_sc.ms_c = 1;
	self->scd_copy_state       = MPART_ST_MEM_SC;
	vec[0]                     = chunk;
	done                       = chunk.mc_size;
extend_vector:
	for (;;) {
		size_t missing_pages, avail;
		assert(done < total_pages);
		missing_pages = total_pages - done;
		/* Make sure that there is sufficient space for one additional chunk. */
		avail = kmalloc_usable_size(self->scd_copy_mem_sc.ms_v) / sizeof(struct mchunk);
		assert(avail >= self->scd_copy_mem_sc.ms_c);
		if (avail <= self->scd_copy_mem_sc.ms_c) {
			/* Extend the vector. */
			vec = (struct mchunk *)krealloc_nx(self->scd_copy_mem_sc.ms_v,
			                                   (self->scd_copy_mem_sc.ms_c + 1) *
			                                   sizeof(struct mchunk),
			                                   GFP_LOCKED | GFP_ATOMIC | GFP_PREFLT);
			if unlikely(!vec) {
				/* Must do the thing with blocking. */
				mpart_lock_release_f(part);
				goto do_realloc_in_extend_after_unlock;
			}
			self->scd_copy_mem_sc.ms_v = vec;
		}
		/* Allocate the new chunk. */
		chunk.mc_start = mfile_alloc_physmem(part->mp_file, total_pages, &chunk.mc_size);
		if unlikely(self->scd_copy_mem.mc_start == PHYSPAGE_INVALID)
			goto err_badalloc; /* Insufficient physical memory. */
		self->scd_copy_mem_sc.ms_v[self->scd_copy_mem_sc.ms_c] = chunk;
		++self->scd_copy_mem_sc.ms_c;
	}

	/* Try to truncate unused memory. */
	vec = (struct mchunk *)krealloc_nx(self->scd_copy_mem_sc.ms_v,
	                                   self->scd_copy_mem_sc.ms_c *
	                                   sizeof(struct mchunk),
	                                   GFP_LOCKED | GFP_ATOMIC | GFP_PREFLT);
	if likely(vec != NULL)
		self->scd_copy_mem_sc.ms_v = vec;
	return true;
err_badalloc:
	mpart_lock_release_f(part);
err_badalloc_after_unlock:
	THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, total_pages);
}



/* Ensure that none of the blocks of `self' are set to `MPART_BLOCK_ST_INIT'.
 * If such blocks exist, then unlock `self', wait for them to go away, and
 * return `false'. Otherwise, keep the lock to `self' and return `true' */
PRIVATE NONNULL((1)) bool FCALL
mpart_ensure_no_init_blocks_or_unlock_and_wait(struct mpart *__restrict self) {
	if unlikely(mpart_hasblocksstate_init(self)) {
		/* Wait for init-done to be signaled. */
		REF struct mfile *file;
		file = incref(self->mp_file);
		mpart_lock_release_f(self);
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
			mpart_lock_release_f(self);
			task_disconnectall();
			return false;
		}
		mpart_lock_release_f(self);
		task_waitfor();
		return false;
	}
	return true;
}


struct setcore_ex_data {
	struct setcore_data scxd_mem;    /* Memory information. */
	bitset_word_t      *scxd_bitset; /* [0..1] Block-status bitset. */
};

#define bitset_getstate(base, partrel_block_index)                              \
	(((base)[(partrel_block_index) / BITSET_ITEMS_PER_WORD] >>                  \
	  (((partrel_block_index) % BITSET_ITEMS_PER_WORD) * MPART_BLOCK_STBITS)) & \
	 (((bitset_word_t)1 << MPART_BLOCK_STBITS) - 1))
#define setcore_ex_bitset_getstate(self, partrel_block_index) \
	bitset_getstate((self)->scxd_bitset, partrel_block_index)

#define setcore_ex_data_init(self) \
	memset(self, 0, sizeof(struct setcore_ex_data))
STATIC_ASSERT(MPART_ST_VOID == 0);
#define setcore_ex_data_fini(self)         \
	(setcore_data_fini(&(self)->scxd_mem), \
	 kfree((self)->scxd_bitset))


PRIVATE NONNULL((1, 2)) bool FCALL
setcore_ex_makebitset_or_unlock(struct setcore_ex_data *__restrict self,
                                struct mpart *__restrict part,
                                size_t num_blocks,
                                gfp_t gfp_flags) {
	size_t avl_size, req_size;
	bitset_word_t *new_bitset;
	/* Must actually allocate the block-status bitset! */
	avl_size = kmalloc_usable_size(self->scxd_bitset);
	req_size = CEILDIV(num_blocks, BITSET_ITEMS_PER_WORD);
	if likely(req_size > avl_size) {
		/* Must allocate a larger bitset. */
		new_bitset = (bitset_word_t *)krealloc_nx(self->scxd_bitset, req_size,
		                                          GFP_LOCKED | GFP_ATOMIC |
		                                          GFP_PREFLT | gfp_flags);
		if unlikely(!new_bitset) {
			/* Must allocate the bitset while blocking. */
			mpart_lock_release_f(part);
			self->scxd_bitset = (bitset_word_t *)krealloc(self->scxd_bitset, req_size,
			                                              GFP_LOCKED | GFP_PREFLT | gfp_flags);
			return false;
		}
		self->scxd_bitset = new_bitset;
	} else if (req_size < avl_size) {
		new_bitset = (bitset_word_t *)krealloc_nx(self->scxd_bitset, req_size,
		                                          GFP_LOCKED | GFP_ATOMIC |
		                                          GFP_PREFLT | gfp_flags);
		if likely(new_bitset != NULL)
			self->scxd_bitset = new_bitset;
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
                          bitset_word_t const *__restrict bitset,
                          unsigned int block_shift,
                          size_t num_blocks) {
#define GETSTATE(index) bitset_getstate(bitset, index)
	size_t i, block_size;
	uintptr_t dst_offset = 0;
	uintptr_t src_offset = 0;
	block_size = (size_t)1 << block_size;
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


/* Acquire a lock to `self', and ensure that `MPART_ST_INCORE(self->mp_state)' */
PUBLIC NONNULL((1)) void FCALL
mpart_lock_acquire_and_setcore(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	size_t num_bytes, num_pages, num_blocks;
	struct mfile *file;
	struct setcore_ex_data data;
	mpart_lock_acquire(self);
	/* Quick check: is the part already in the expected state? */
	if (MPART_ST_INCORE(self->mp_state))
		return; /* Already done! */
	num_bytes = mpart_getsize(self);
	assert(IS_ALIGNED(num_bytes, PAGESIZE));
	file       = self->mp_file;
	num_pages  = num_bytes / PAGESIZE;
	num_blocks = num_bytes >> file->mf_blockshift;
	setcore_data_init(&data);
	TRY {
again_init_data:
		/* Allocate physical memory. */
		if (!setcore_makememdat_or_unlock(&data.scxd_mem, self, num_pages)) {
			/* Lock was lost... */
reacquire_lock:
			mpart_lock_acquire(self);
			if unlikely(MPART_ST_INCORE(self->mp_state)) {
				setcore_ex_data_fini(&data);
				return; /* Already done! */
			}
			num_bytes = mpart_getsize(self);
			assert(IS_ALIGNED(num_bytes, PAGESIZE));
			file       = self->mp_file;
			num_pages  = num_bytes / PAGESIZE;
			num_blocks = num_bytes >> file->mf_blockshift;
			goto again_init_data;
		}

		/* Fill in memory information for `self'. */
		assert(!MPART_ST_INCORE(self->mp_state));
		switch (__builtin_expect(self->mp_state, MPART_ST_VOID)) {

		case MPART_ST_VOID:
			/* Make sure that we've got sufficient space for the block-state bitset. */
			if (num_blocks <= BITSET_ITEMS_PER_WORD) {
				/* Can use the inline bitset. */
				if unlikely(data.scxd_bitset != NULL) {
					kfree(data.scxd_bitset);
					DBG_memset(&data.scxd_bitset, 0xcc, sizeof(data.scxd_bitset));
				}
				/* All blocks are undefined by default! */
				self->mp_blkst_inl = MPART_BLOCK_REPEAT(MPART_BLOCK_ST_NDEF);
				ATOMIC_OR(self->mp_flags, MPART_F_BLKST_INL);
			} else {
				/* Must actually allocate the block-status bitset! */
				if (!setcore_ex_makebitset_or_unlock(&data, self, num_blocks, GFP_CALLOC))
					goto reacquire_lock;
				/* NOTE: Because we've used GFP_CALLOC, all blocks will have
				 *       already been initialized to `MPART_BLOCK_ST_NDEF'! */
				self->mp_blkst_ptr = data.scxd_bitset;
				ATOMIC_AND(self->mp_flags, ~MPART_F_BLKST_INL);
				DBG_memset(&data.scxd_bitset, 0xcc, sizeof(data.scxd_bitset));
			}
			break;

		case MPART_ST_SWP:
		case MPART_ST_SWP_SC: {
			size_t i;
			bool did_set_init_parts;
			assert(mpart_hasblockstate(self));
			/* Load data from swap.
			 * For this purpose, we must ensure that there aren't any pre-existing
			 * INIT-blocks, which might happen if someone else is still in the
			 * process of writing data _to_ swap (in which case they will make the
			 * INIT-blocks go away once they're done) */
			if (!mpart_ensure_no_init_blocks_or_unlock_and_wait(self))
				goto reacquire_lock;

			/* In order to (safely) remember which parts we've set to INIT (as opposed
			 * to someone else setting them), we have to allocate sufficient heap memory
			 * in order to store a copy of the bitset of `self' */
			if (!setcore_ex_makebitset_or_unlock(&data, self, num_blocks, 0))
				goto reacquire_lock;

			/* Now we must switch all `MPART_BLOCK_ST_CHNG' parts (i.e. all parts that
			 * have been written to swap) over to `MPART_BLOCK_ST_INIT', thus preventing
			 * anyone else from changing the contents of the part.
			 *
			 * NOTE: And while we're at it, also change all `MPART_BLOCK_ST_LOAD' parts
			 *       back to `MPART_BLOCK_ST_NDEF', since their contents have gotten
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
			ATOMIC_OR(self->mp_flags, MPART_F_MAYBE_BLK_INIT);

			/* At this point, we know that _all_ INIT-entries within the bitset
			 * of `self' originate from our doing. As such, copy the constants
			 * of the bitset into our local heap-copy, so we still know which
			 * parts we're supposed to initialize from swap once we're done here! */
			{
				bitset_word_t *src = self->mp_blkst_ptr;
				if (self->mp_flags & MPART_F_BLKST_INL)
					src = &self->mp_blkst_inl;
				memcpy(data.scxd_bitset, src,
				       CEILDIV(num_blocks, BITSET_ITEMS_PER_WORD),
				       sizeof(bitset_word_t));
			}
			/* Release our lock to `self' so we can safely invoke swap-callbacks. */
			incref(file);
			mpart_lock_release_f(self);
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
				if (data.scxd_mem.scd_copy_state == MPART_ST_MEM) {
					mem_data.ms_c = 1;
					mem_data.ms_v = &data.scxd_mem.scd_copy_mem;
				} else {
					mem_data.ms_c = data.scxd_mem.scd_copy_mem_sc.ms_c;
					mem_data.ms_v = data.scxd_mem.scd_copy_mem_sc.ms_v;
				}

				/* Actually load data from swap. */
				setcore_ex_load_from_swap(&mem_data, &swp_data,
				                          data.scxd_bitset,
				                          file->mf_blockshift,
				                          num_blocks);

				/* Re-acquire our lock to `self' */
				mpart_lock_acquire(self);
			} EXCEPT {
				/* Change the INIT-blocks we've set above to `CHNG' */
				for (i = 0; i < num_blocks; ++i) {
					unsigned int st;
					st = setcore_ex_bitset_getstate(&data, i); /* Read from the local bitset! */
					if (st == MPART_BLOCK_ST_INIT)
						mpart_setblockstate(self, i, MPART_BLOCK_ST_CHNG);
				}
				sig_broadcast(&file->mf_initdone);
				decref_unlikely(file);
				RETHROW();
			}

			/* Assert that nothing changed about `self' that should have
			 * been protected by us having set INIT-blocks above. */
			assert(self->mp_state == MPART_ST_SWP ||
			       self->mp_state == MPART_ST_SWP_SC);
			assert(self->mp_file == file);
			assert(num_bytes == mpart_getsize(self));

			/* Change the INIT-blocks we've set above to `CHNG' */
			for (i = 0; i < num_blocks; ++i) {
				unsigned int st;
				st = setcore_ex_bitset_getstate(&data, i); /* Read from the local bitset! */
				if (st == MPART_BLOCK_ST_INIT)
					mpart_setblockstate(self, i, MPART_BLOCK_ST_CHNG);
			}

			/* Now that all of (our) INIT-blocks are gone, broadcast
			 * the init-done signal of our file to tell other thread
			 * that INIT blocks may possible be all gone now. */
			sig_broadcast(&file->mf_initdone);
			decref_unlikely(file);

			/* And with that, all required data has been read from swap,
			 * and we can safely transition to on of the MEM-states. */
done_swap:
			kfree(data.scxd_bitset);
			DBG_memset(&data.scxd_bitset, 0xcc, sizeof(data.scxd_bitset));

			/* Free the swap storage area used by this part. */
			if (self->mp_state == MPART_ST_SWP) {
				mchunk_freeswp(&self->mp_swp);
			} else {
				mchunkvec_freeswp(self->mp_swp_sc.ms_v,
				                  self->mp_swp_sc.ms_c);
				kfree(self->mp_swp_sc.ms_v);
			}
		}	break;

		default: __builtin_unreachable();
		}
	} EXCEPT {
		setcore_ex_data_fini(&data);
		mpart_deadnodes_reap(self);
		RETHROW();
	}

	/* Fill in information on the backing storage. */
	self->mp_state = data.scxd_mem.scd_copy_state;
	memcpy(&self->mp_mem, &data.scxd_mem.scd_copy_mem,
	       MAX_C(sizeof(struct mchunk),
	             sizeof(struct mchunkvec)));
}

/* Acquire a lock to `self', and ensure that `MPART_F_MAYBE_BLK_INIT' isn't set. */
PUBLIC NONNULL((1)) void FCALL
mpart_lock_acquire_and_noinitblocks(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
again:
	mpart_lock_acquire(self);
	if unlikely(mpart_hasblocksstate_init(self)) {
		REF struct mfile *file;
		file = incref(self->mp_file);
		mpart_lock_release(self);
		/* Connect the the INIT-done signal. */
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
		/* Check for race condition: INIT-parts went away in the mean time. */
		if unlikely(!mpart_hasblocksstate_init(self)) {
			task_disconnectall();
			return;
		}
		mpart_lock_release(self);
		task_waitfor();
		goto again;
	}
}


/* Ensure that there aren't any blocks with `MPART_BLOCK_ST_NDEF'
 * or `MPART_BLOCK_ST_INIT' as state, by manually loading undefined
 * blocks into memory, and waiting until INIT-parts go away to get
 * rid of INIT.
 *  - If it could be asserted that no such parts exist without needing
 *    to release the lock of `self', return `true'.
 *  - If something was done to get closer to the goal of loading all
 *    blocks of the part, then unlock `self' (to get closer to said
 *    goal), and eventually return `false' (such that the caller may
 *    re-acquire the lock to `self')
 *  - If something else goes wrong, an exception is thrown, and the
 *    lock to `self' will have already been released.
 */
PRIVATE NONNULL((1)) bool FCALL
mpart_loadall_or_unlock(struct mpart *__restrict self) {
	size_t i, block_count;
	struct mfile *file = self->mp_file;
	bool has_init = false;

	/* Check for parts that have yet to be loaded. */
	block_count = mpart_getblockcount(self, file);
	for (i = 0; i < block_count; ++i) {
		unsigned int st;
		size_t start, end;
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
		block_count = start + (loc.mppl_size >> file->mf_blockshift);
		assert(block_count <= mpart_getblockcount(self, file));

		/* Alter the state of UNDEF parts to INIT, thus essentially
		 * locking them in-memory until we're down loading them. */
		for (end = start + 1;;) {
			mpart_setblockstate(self, end - 1, MPART_BLOCK_ST_INIT);
			if (end >= block_count)
				break; /* The next block would no longer be apart of the containing chunk. */
			st = mpart_getblockstate(self, end);
			if (st != MPART_BLOCK_ST_NDEF)
				break; /* The next block is no longer marked as UNDEF. */
			++end;
		}
		ATOMIC_OR(self->mp_flags, MPART_F_MAYBE_BLK_INIT);
		incref(file);
		/* Release the lock from the part, so we can load
		 * blocks without holding that non-recursive, and
		 * non-preemptive lock! */
		mpart_lock_release_f(self);
		TRY {
			/* Actually do the load. */
			if likely(file->mf_ops->mo_loadblocks) {
				(*file->mf_ops->mo_loadblocks)(file,
				                               (self->mp_minaddr >> file->mf_blockshift) + start,
				                               loc.mppl_addr, end - start);
			}
		} EXCEPT {
			/* Set block states back to NDEF */
			for (i = start; i < end; ++i)
				mpart_setblockstate(self, end, MPART_BLOCK_ST_NDEF);
			sig_broadcast(&file->mf_initdone);
			decref_unlikely(file);
			RETHROW();
		}
		/* Set loaded states back to LOAD */
		for (i = start; i < end; ++i)
			mpart_setblockstate(self, end, MPART_BLOCK_ST_LOAD);
		sig_broadcast(&file->mf_initdone);
		decref_unlikely(file);
		return false;
	}
	if (has_init) {
		/* Wait for init-parts to go away! */
		incref(file);
		mpart_lock_release_f(self);
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
			mpart_lock_release_f(self);
			task_disconnectall();
			return false;
		}
		mpart_lock_release_f(self);
		task_waitfor();
		return false;
	}
	return true;
}


/* Same as `mpart_lock_acquire_and_setcore()', but also ensure that _all_ blocks
 * of `self' are fully loaded (that is: no block exists with its state set to
 * either `MPART_BLOCK_ST_NDEF' or `MPART_BLOCK_ST_INIT'). */
PUBLIC NONNULL((1)) void FCALL
mpart_lock_acquire_and_setcore_loadall(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
again:
	mpart_lock_acquire_and_setcore(self);
	if unlikely(!mpart_hasblockstate(self))
		return;
	TRY {
		if (!mpart_loadall_or_unlock(self))
			goto again;
	} EXCEPT {
		mpart_deadnodes_reap(self);
		RETHROW();
	}
}



/* Same as `mpart_loadall_or_unlock()', but only ensure no INIT-blocks when
 * the file used by `self' describes zero-initialized, anonymous memory. */
PRIVATE NONNULL((1)) bool FCALL
mpart_maybe_loadall_or_unlock(struct mpart *__restrict self) {
	/* Check for special case: Without a block-state-bitset,
	 * there can't be any INIT or LOAD-parts. */
	if unlikely(!mpart_hasblockstate(self))
		return true;
	/* This is where it gets complicated, since we need to create a new,
	 * anonymous, and fully initialized (i.e. no `MPART_BLOCK_ST_NDEF'
	 * blocks) version of our mem-part.
	 *
	 * As the first step, make sure that all blocks of `self' have been
	 * loaded, as all of the unshared copies of `self' would no longer
	 * be able to access the state of `self', as it was before.
	 *
	 * Note though that we make a special case out of anon files, since
	 * those would still get the same initialization in the unshared
	 * copies when compared to now! */
	if (self->mp_file >= mfile_anon &&
	    self->mp_file < COMPILER_ENDOF(mfile_anon)) {
		/* No need to prevent `MPART_BLOCK_ST_NDEF' parts.
		 * We only need to get rid of `MPART_BLOCK_ST_INIT' parts! */
		return mpart_ensure_no_init_blocks_or_unlock_and_wait(self);
	} else {
		if (!mpart_loadall_or_unlock(self))
			return false;
	}
	return true;
}



/* Given 2 mem-parts that are both `MPART_ST_MEM' or `MPART_ST_MEM_SC',
 * and are both at least `num_pages' large, copy the contents of those
 * many pages of physical memory from `src' to `dst' */
PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mpart_copyram)(struct mpart *__restrict dst,
                             struct mpart *__restrict src,
                             PAGEDIR_PAGEALIGNED mpart_reladdr_t src_offset,
                             size_t num_pages) {
	assert(MPART_ST_INMEM(dst->mp_state));
	assert(MPART_ST_INMEM(src->mp_state));
	if (src->mp_state == MPART_ST_MEM) {
		if (dst->mp_state == MPART_ST_MEM) {
			/* SINGLE --> SINGLE */
			vm_copypagesinphys(physpage2addr(dst->mp_mem.mc_start),
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
				vm_copypagesinphys(physpage2addr(dst_chunks[i].mc_start),
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
			}
			if (count > num_pages)
				count = num_pages;
			vm_copypagesinphys(physpage2addr(dst_page),
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
				vm_copypagesinphys(physpage2addr(b.mc_start),
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






struct unsharecow_data {
	struct mpart                           *ucd_copy;    /* [0..1] The duplicate of the original mem-part. */
	bitset_word_t                          *ucd_blk_ext; /* [0..1] Dynamically allocated block-extension bitset. (if needed) */
	/*PAGEDIR_PAGEALIGNED*/ mpart_reladdr_t ucd_mapmin;  /* The lowest (part-relative) address mapped by copy-on-write nodes. */
	mpart_reladdr_t                         ucd_mapmax;  /* The greatest (part-relative) address mapped by copy-on-write nodes. */
	/*PAGEDIR_PAGEALIGNED*/ size_t          ucd_mapsize; /* == (ucd_mapmax - ucd_mapmin) + 1. */
	struct setcore_data                     ucs_mem;     /* Memory data. */
};

#define unsharecow_data_init(self) \
	memset(self, 0, sizeof(struct unsharecow_data))
STATIC_ASSERT(MPART_ST_VOID == 0);


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL unsharecow_data_fini)(struct unsharecow_data *__restrict self) {
	kfree(self->ucd_copy);
	kfree(self->ucd_blk_ext);
	setcore_data_fini(&self->ucs_mem);
}

/* Calculate the max-size needed to represent `self'. Stores the results in:
 *   - self->ucd_mapmin
 *   - self->ucd_mapmax
 *   - self->ucd_mapsize */
PRIVATE NONNULL((1, 2)) void
NOTHROW(FCALL unsharecow_calculate_mapbounds)(struct unsharecow_data *__restrict self,
                                              struct mpart *__restrict part) {
	struct mnode *node;
	self->ucd_mapmin = (mpart_reladdr_t)-1;
	self->ucd_mapmax = 0;
	LIST_FOREACH (node, &part->mp_copy, mn_link) {
		mpart_reladdr_t min, max;
		if (mnode_wasdestroyed(node))
			continue;
		min = mnode_getmapminaddr(node);
		max = mnode_getmapmaxaddr(node);
		if (self->ucd_mapmin > min)
			self->ucd_mapmin = min;
		if (self->ucd_mapmax < max)
			self->ucd_mapmax = max;
	}
	assert(self->ucd_mapmin < self->ucd_mapmax);
	assert(IS_ALIGNED(self->ucd_mapmin, PAGESIZE));
	assert(IS_ALIGNED(self->ucd_mapmax + 1, PAGESIZE));
	self->ucd_mapsize = 1 + (self->ucd_mapmax - self->ucd_mapmin);
}


/* Ensure that `self->ucd_copy' has been allocated.
 * If it hasn't been allocated yet, and doing so cannot be done
 * without blocking, then the lock to `part' is released, and the
 * allocation is performed with blocking. Stores the results in:
 *   - self->ucd_copy
 * Throws an exception on error.
 * @return: true:  Success
 * @return: false: Success, but the lock to `part' was lost */
PRIVATE NONNULL((1, 2)) bool FCALL
unsharecow_makecopy_or_unlock(struct unsharecow_data *__restrict self,
                              struct mpart *__restrict part) {
	struct mpart *copy;
	if unlikely(self->ucd_copy != NULL)
		goto done;
	/* Try to allocate the copy. */
	copy = (struct mpart *)kmalloc_nx(sizeof(struct mpart),
	                                  GFP_LOCKED | GFP_ATOMIC |
	                                  GFP_PREFLT);
	if unlikely(!copy) {
		/* Must allocate while blocking. */
		mpart_lock_release_f(part);
		copy = (struct mpart *)kmalloc(sizeof(struct mpart),
		                               GFP_LOCKED | GFP_PREFLT);
		self->ucd_copy = copy;
		return false;
	}
	self->ucd_copy = copy;
done:
	return true;
}

/* If necessary, allocate an extended block-status bitset needed to hold
 * the data for a copy of `part'. If such a bitset isn't necessary, then
 * don't do anything. Stores the results in:
 *   - self->ucd_blk_ext
 * Throws an exception on error.
 * @return: true:  Success
 * @return: false: Success, but the lock to `part' was lost */
PRIVATE NONNULL((1, 2)) bool FCALL
unsharecow_makeblkext_or_unlock(struct unsharecow_data *__restrict self,
                                struct mpart *__restrict part) {
	size_t block_count, reqsize;
	bitset_word_t *bitset;
	/* We need to copy the block-status bitset. */
	block_count = self->ucd_mapsize >> part->mp_file->mf_blockshift;
	if (block_count <= BITSET_ITEMS_PER_WORD)
		return true; /* A single word is enough! */
	if (part->mp_blkst_ptr == NULL)
		return true; /* We can just mirror the NULL-bitset. */
	/* This is the case where we need the dynamically allocated block-status bitset. */
	reqsize = CEILDIV(block_count, BITSET_ITEMS_PER_WORD) * sizeof(bitset_word_t);
	bitset  = (bitset_word_t *)krealloc_nx(self->ucd_blk_ext, reqsize,
	                                       GFP_LOCKED | GFP_ATOMIC | GFP_PREFLT);
	if unlikely(!bitset) {
		/* Must allocate while blocking. */
		mpart_lock_release_f(part);
		bitset = (bitset_word_t *)krealloc(self->ucd_blk_ext, reqsize,
		                                   GFP_LOCKED | GFP_PREFLT);
		self->ucd_blk_ext = bitset;
		return false;
	}
	self->ucd_blk_ext = bitset;
	return true;
}


/* Allocate physical memory for exactly `self->ucd_partsize' bytes of
 * memory, and store the results in:
 *   - self->ucd_copy_state
 *   - self->ucd_copy_mem
 *   - self->ucd_copy_mem_sc
 * Throws an exception on error.
 * @return: true:  Success
 * @return: false: Success, but the lock to `part' was lost */
PRIVATE NONNULL((1, 2)) bool FCALL
unsharecow_makememdat_or_unlock(struct unsharecow_data *__restrict self,
                                struct mpart *__restrict part) {
	size_t total_pages;
	assert(IS_ALIGNED(self->ucd_mapsize, PAGESIZE));
	total_pages = self->ucd_mapsize / PAGESIZE;
	return setcore_makememdat_or_unlock(&self->ucs_mem, part, total_pages);
}


/* Incref all of the mmans of copy-on-write nodes.
 * Dead mmans are silently ignored (returns `false' if all mmans are dead) */
PRIVATE NONNULL((1)) bool
NOTHROW(FCALL unsharecow_incref_mmans)(struct mpart *__restrict part) {
	bool result = false;
	struct mnode *node;
	LIST_FOREACH (node, &part->mp_copy, mn_link) {
		if (tryincref(node->mn_mman))
			result = true;
	}
	return result;
}

/* Decref all of the mmans of copy-on-write nodes.
 * mmans that were already dead are silently ignored. */
PRIVATE NONNULL((1)) void
NOTHROW(FCALL unsharecow_decref_mmans)(struct mpart *__restrict part) {
	struct mnode *node;
	LIST_FOREACH (node, &part->mp_copy, mn_link) {
		if (!wasdestroyed(node->mn_mman))
			decref_unlikely(node->mn_mman);
	}
}

PRIVATE NONNULL((1)) void
NOTHROW(FCALL unsharecow_decref_mmans_fast)(struct mpart *__restrict part) {
	struct mnode *node;
	LIST_FOREACH (node, &part->mp_copy, mn_link) {
		decref_unlikely(node->mn_mman);
	}
}

PRIVATE NONNULL((1, 2, 3)) bool
NOTHROW(FCALL mnode_list_contains_mman_until)(struct mnode *start_node,
                                              struct mnode *stop_node,
                                              struct mman *__restrict mm) {
	while (start_node != stop_node) {
		if (start_node->mn_mman == mm)
			return true;
		start_node = LIST_NEXT(start_node, mn_link);
	}
	return false;
}

PRIVATE NONNULL((1)) void
NOTHROW(FCALL unsharecow_unlock_unique_mmans_until)(struct mpart *__restrict part,
                                                    struct mnode *stop_node) {
	struct mnode *node;
	for (node = LIST_FIRST(&part->mp_copy); node != stop_node;
	     node = LIST_NEXT(node, mn_link)) {
		struct mman *mm = node->mn_mman;
		if (wasdestroyed(mm))
			continue;
		/* Check if we've already seen this mman */
		if (mnode_list_contains_mman_until(LIST_FIRST(&part->mp_copy),
		                                   node, mm))
			continue;
		sync_endwrite(mm);
	}
}

#define unsharecow_unlock_unique_mmans(part) \
	unsharecow_unlock_unique_mmans_until(part, NULL)

PRIVATE NONNULL((1)) void
NOTHROW(FCALL unsharecow_unlock_unique_mmans_fast)(struct mpart *__restrict part) {
	struct mnode *node;
	LIST_FOREACH (node, &part->mp_copy, mn_link) {
		struct mman *mm = node->mn_mman;
		assert(!wasdestroyed(mm));
		/* Check if we've already seen this mman */
		if (mnode_list_contains_mman_until(LIST_FIRST(&part->mp_copy),
		                                   node, mm))
			continue;
		sync_endwrite(mm);
	}
}

/* Acquire locks to all of the memory-managers in use by copy-on-write nodes of `self' */
PRIVATE NONNULL((1)) bool FCALL
unsharecow_lock_unique_mmans(struct mpart *__restrict part) {
	struct mnode *node;
	LIST_FOREACH (node, &part->mp_copy, mn_link) {
		struct mman *mm;
		mm = node->mn_mman;
		if (wasdestroyed(mm))
			continue;
		/* Check if we've already seen this mman */
		if (mnode_list_contains_mman_until(LIST_FIRST(&part->mp_copy), node, mm))
			continue;
		if (!sync_trywrite(mm)) {
			/* Found one that can't be locked immediately.
			 * -> Unlock all others and drop already-gathered references. */
			unsharecow_unlock_unique_mmans_until(part, node);

			/* Drop our lock to the original part. */
			mpart_lock_release_f(part);

			/* Wait until the lock of this mman becomes available. */
			while (!sync_canwrite(mm))
				task_yield();
			return false;
		}
	}
	return true;
}

PRIVATE NONNULL((1, 2)) void
NOTHROW(FCALL unprepare_mmans_until)(struct mnode *start_node,
                                     struct mnode *stop_node) {
	for (; start_node != stop_node; start_node = LIST_NEXT(start_node, mn_link)) {
		if unlikely(mnode_wasdestroyed(start_node))
			continue; /* Skip dead nodes. */
		pagedir_unprepare_map_p(start_node->mn_mman->mm_pdir_phys,
		                        mnode_getaddr(start_node),
		                        mnode_getsize(start_node));
	}
}

/* Prepare the backing memory of all page directories with copy-on-write mappings,
 * such that those regions may atomically be replaced with different bindings.
 * If this cannot be done, release all locks and throw an exception. */
PRIVATE NONNULL((1)) bool FCALL
prepare_mmans_or_unlock(struct mpart *__restrict part) {
	struct mnode *node;
	bool result = false;
	LIST_FOREACH (node, &part->mp_copy, mn_link) {
		if unlikely(mnode_wasdestroyed(node))
			continue; /* Skip dead nodes. */
		/* Prepare the page directory. */
		if unlikely(!pagedir_prepare_map_p(node->mn_mman->mm_pdir_phys,
		                                   mnode_getaddr(node),
		                                   mnode_getsize(node)))
			goto err_badalloc;
		result = true;
	}
	return result;
err_badalloc:
	/* Insufficient physical memory...
	 * -> Unprepare everything we've already prepared thus far,
	 *    then proceed by throwing an exception! */
	unprepare_mmans_until(LIST_FIRST(&part->mp_copy), node);
	unsharecow_unlock_unique_mmans(part);
	mpart_lock_release_f(part);
	THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
}




/* Same as `mpart_lock_acquire_and_setcore()', but also ensure that `LIST_EMPTY(&self->mp_copy)',
 * meaning that all copy-on-write mappings of the part have been unshared. This must
 * be done before the contents of the part can be written to directly, or be mapped
 * as writable for MAP_SHARED mappings of the part itself. */
PUBLIC NONNULL((1)) void FCALL
mpart_lock_acquire_and_setcore_unsharecow(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct mnode *node;
	struct unsharecow_data data;
	size_t block_count;
again:
	mpart_lock_acquire_and_setcore(self);
	/* Quick check: If there aren't any copy-on-write mappings, then
	 *              we don't actually need to do anything else! */
	if (LIST_EMPTY(&self->mp_copy))
		return;

#ifndef __OPTIMIZE_SIZE__
	/* Make sure that none of the remaining copy-nodes are actually dead. */
	if unlikely(mpart_deadnodes_mustreap(self)) {
		mpart_lock_release_f(self);
		mpart_deadnodes_reap(self);
		goto again;
	}
#endif /* !__OPTIMIZE_SIZE__ */

	/* Make sure to load all blocks (if necessary), and also make sure
	 * that there aren't any INIT-blocks left */
	if (!mpart_maybe_loadall_or_unlock(self))
		goto again;
	assert(!LIST_EMPTY(&self->mp_copy));

	/* Try to acquire references to all of the mmans from the copy-on-write list.
	 * If we fail to do this for all of them, then we're already done, since there
	 * are no (alive) copy-on-write mappings present! */
	if (!unsharecow_incref_mmans(self))
		return;

	unsharecow_data_init(&data);
again_alloc_data:
	/* Calculate the max-address needed to represent `self' */
	unsharecow_calculate_mapbounds(&data, self);
again_alloc_data_after_partsize:
	TRY {

		if (!unsharecow_makecopy_or_unlock(&data, self)) {
restart_with_init_data:
			mpart_lock_acquire_and_setcore(self);
			if unlikely(LIST_EMPTY(&self->mp_copy)) {
				unsharecow_data_fini(&data);
				return;
			}
#ifndef __OPTIMIZE_SIZE__
			/* Make sure that none of the remaining copy-nodes are actually dead. */
			if unlikely(mpart_deadnodes_mustreap(self)) {
				mpart_lock_release_f(self);
				mpart_deadnodes_reap(self);
				goto restart_with_init_data;
			}
#endif /* !__OPTIMIZE_SIZE__ */
		
			/* Make sure to load all blocks (if necessary), and also make sure
			 * that there aren't any INIT-blocks left */
			if (!mpart_maybe_loadall_or_unlock(self))
				goto restart_with_init_data;
			assert(!LIST_EMPTY(&self->mp_copy));
			goto again_alloc_data;
		}

		/* Allocate the block-extension bitset. */
		if (!unsharecow_makeblkext_or_unlock(&data, self))
			goto restart_with_init_data;

		/* Allocate low-level ram data. */
		if (!unsharecow_makememdat_or_unlock(&data, self))
			goto restart_with_init_data;

		/* (almost) lastly, acquire references & locks to all of the memory-managers
		 * associated with nodes from the copy-on-write mappings list. */
		if (!unsharecow_lock_unique_mmans(self))
			goto restart_with_init_data;

		/* And finally, make sure that we'll be able to re-map the backing
		 * page directory mappings of all of the copy-on-write nodes. After
		 * all: we _do_ intend to replace them with our new copy. */
		if (!prepare_mmans_or_unlock(self)) {
			/* Special case: All nodes had been destroyed! */
			unsharecow_unlock_unique_mmans(self);
			mpart_lock_release_f(self);
			unsharecow_data_fini(&data);
			unsharecow_decref_mmans(self);
			mpart_deadnodes_reap(self);
			goto again;
		}
	} EXCEPT {
		unsharecow_data_fini(&data);
		unsharecow_decref_mmans(self);
		mpart_deadnodes_reap(self);
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
	data.ucd_copy->mp_refcnt = 0;
	LIST_INIT(&data.ucd_copy->mp_copy);
	for (node = LIST_FIRST(&self->mp_copy); node;) {
		struct mnode *next_node;
		next_node = LIST_NEXT(node, mn_link);
		if likely(!wasdestroyed(node->mn_mman)) {
			if unlikely(node->mn_part == NULL) {
				/* Special case: this node (may) have been deleted after we've
				 *               calculated the original part-size needed for
				 *               the copy. If so, then the copy may be larger
				 *               than it would need to be. If that has happened,
				 *               then we must re-start building the new copy with
				 *               a smaller size. */
				size_t old_partsize;
				old_partsize = data.ucd_mapsize;
				unsharecow_calculate_mapbounds(&data, self);
				assert(data.ucd_mapsize <= old_partsize);
				if unlikely(data.ucd_mapsize < old_partsize) {
					/* Restore all of the already-stolen copy-nodes. */
					while (!LIST_EMPTY(&data.ucd_copy->mp_copy)) {
						node = LIST_FIRST(&data.ucd_copy->mp_copy);
						LIST_REMOVE(node, mn_link);
						assert(node->mn_part == self);
						LIST_INSERT_HEAD(&self->mp_copy, node, mn_link);
						incref(self);
					}
					unprepare_mmans_until(LIST_FIRST(&self->mp_copy), NULL);
					unsharecow_unlock_unique_mmans(self);
					mpart_lock_release_f(self);
					unsharecow_decref_mmans(self);
					goto again_alloc_data_after_partsize;
				}
			} else {
				/* Transfer this node to the new mem-part. */
				assert(node->mn_part == self);
				LIST_INSERT_HEAD(&data.ucd_copy->mp_copy, node, mn_link);
				++data.ucd_copy->mp_refcnt; /* New reference (to-be) held by `node->mn_part' */
				decref_nokill(self);        /* Old reference held by `node->mn_part' */
			}
		}
		node = next_node;
	}
	assert(!LIST_EMPTY(&data.ucd_copy->mp_copy));
	assert(data.ucd_copy->mp_refcnt != 0);
	assert(data.ucd_mapsize != 0);

	/* Initialize misc. fields of the mem-part copy. */
	data.ucd_copy->mp_flags = (self->mp_flags & MPART_F_MLOCK) | MPART_F_NO_GLOBAL_REF | MPART_F_LOCKBIT;
	data.ucd_copy->mp_file  = incref(&mfile_anon[self->mp_file->mf_blockshift]);
	LIST_INIT(&data.ucd_copy->mp_share);
	SLIST_INIT(&data.ucd_copy->mp_deadnodes);
	DBG_memset(&data.ucd_copy->mp_changed, 0xcc, sizeof(data.ucd_copy->mp_changed));
	data.ucd_copy->mp_minaddr = self->mp_minaddr + data.ucd_mapmin;
	data.ucd_copy->mp_maxaddr = self->mp_minaddr + data.ucd_mapmax;
	assert(data.ucd_copy->mp_maxaddr <= self->mp_maxaddr);
	DBG_memset(&data.ucd_copy->mp_filent, 0xcc, sizeof(data.ucd_copy->mp_filent));

	/* We need to copy the block-status bitset. */
	block_count = data.ucd_mapsize >> data.ucd_copy->mp_file->mf_blockshift;
	if (block_count <= BITSET_ITEMS_PER_WORD) {
		/* A single word is enough! */
		bitset_word_t word;
		word = self->mp_blkst_inl;
		if (!(self->mp_flags & MPART_F_BLKST_INL)) {
			word = MPART_BLOCK_REPEAT(MPART_BLOCK_ST_CHNG);
			if (self->mp_blkst_ptr != NULL)
				word = self->mp_blkst_ptr[0];
		}
		data.ucd_copy->mp_blkst_inl = word;
		data.ucd_copy->mp_flags |= MPART_F_BLKST_INL;
free_unused_block_status:
		if unlikely(data.ucd_blk_ext)
			kfree(data.ucd_blk_ext);
	} else if (self->mp_blkst_ptr == NULL) {
		data.ucd_copy->mp_blkst_ptr = NULL;
		goto free_unused_block_status;
	} else {
		/* This is the case where we need the dynamically allocated block-status bitset. */
		assert(data.ucd_blk_ext != NULL);
		assert((kmalloc_usable_size(data.ucd_blk_ext) *
		        BITSET_ITEMS_PER_WORD) >= block_count);
		assert(block_count <= mpart_getblockcount(self, self->mp_file));
		/* Copy over block-status bitset data. */
		data.ucd_copy->mp_blkst_ptr = (bitset_word_t *)memcpy(data.ucd_blk_ext,
		                                                      self->mp_blkst_ptr,
		                                                      block_count / BITSET_ITEMS_PER_WORD,
		                                                      sizeof(bitset_word_t));
	}

	/* Fill in information on the backing storage. */
	data.ucd_copy->mp_state = data.ucs_mem.scd_copy_state;
	memcpy(&data.ucd_copy->mp_mem,
	       &data.ucs_mem.scd_copy_mem,
	       MAX_C(sizeof(struct mchunk),
	             sizeof(struct mchunkvec)));

	/* For now, we don't copy mem-part meta-data. */
	data.ucd_copy->mp_meta = NULL;

	/* With that, the new mem-part has been initialized, however we must
	 * still copy over the contents of the old part into the new one! */
	mpart_copyram(data.ucd_copy, self,
	              data.ucd_mapmin,
	              data.ucd_mapsize);

	/* Tell all of the pre-existing nodes about the new backing part!
	 * We do this only now, so-as to ensure that we directly jump from
	 * one completely valid node to another. */
	LIST_FOREACH (node, &data.ucd_copy->mp_copy, mn_link) {
		node->mn_partoff -= data.ucd_mapmin;
		node->mn_part = data.ucd_copy;
	}

	/* With all of the software-structures updated to describe the new,
	 * valid state, time to have the hardware match us by updating the
	 * underlying page directories. */
	{
		u16 prot_mask = PAGEDIR_MAP_FEXEC | PAGEDIR_MAP_FWRITE | PAGEDIR_MAP_FREAD;
		assert(!LIST_EMPTY(&data.ucd_copy->mp_copy));
		/* We can map as writable if only a single copy-on-write node exists! */
		if (LIST_NEXT(LIST_FIRST(&data.ucd_copy->mp_copy), mn_link) != NULL)
			prot_mask &= ~PAGEDIR_MAP_FWRITE;
		LIST_FOREACH (node, &data.ucd_copy->mp_copy, mn_link) {
			struct mman *mm;
			void *addr;
			size_t size;
			u16 prot;
			STATIC_ASSERT(PAGEDIR_MAP_FEXEC == MNODE_F_PEXEC);
			STATIC_ASSERT(PAGEDIR_MAP_FWRITE == MNODE_F_PWRITE);
			STATIC_ASSERT(PAGEDIR_MAP_FREAD == MNODE_F_PREAD);
			mm = node->mn_mman;
			assert(!wasdestroyed(mm));

			/* Updated virtual memory mappings to point to the copied area. */
			addr = mnode_getaddr(node);
			size = mnode_getsize(node);
			prot = node->mn_flags & prot_mask;
			if (ADDR_ISUSER(addr))
				prot |= PAGEDIR_MAP_FUSER; /* XXX: Maybe get rid of this eventually? */

			mpart_mmap_p(data.ucd_copy, mm->mm_pdir_phys,
			             addr, size, node->mn_partoff, prot);

			/* Unlink the node from the writable-chain. */
			if (LIST_ISBOUND(node, mn_writable))
				LIST_UNBIND(node, mn_writable);

			/* With the new mapping in place, unprepare the page directory. */
			pagedir_unprepare_map_p(mm->mm_pdir_phys, addr, size);

			/* Sync memory within the affected area. After all: The backing
			 * physical memory location just changed, so we must flush tlb
			 * caches! */
			mman_sync_p(mm, addr, size);
		}
		if (prot_mask & PAGEDIR_MAP_FWRITE) {
			/* Insert the (only) writable node into it's mman's writable chain. */
			node = LIST_FIRST(&data.ucd_copy->mp_copy);
			if (node->mn_flags & MNODE_F_PWRITE)
				LIST_INSERT_HEAD(&node->mn_mman->mm_writable, node, mn_writable);
		}
	}

	/* Add the new part to the global list of parts. Once this has been done,
	 * some other thread may immediately attempt to off-load the part into
	 * swap, or do some other unspeakable things to it...
	 *
	 * In other words: We need to be damn sure we've finished initializing it! */
	COMPILER_WRITE_BARRIER();
	mpart_all_list_insert(data.ucd_copy);

	/* Drop locks to all of the new part's copy-on-write nodes.
	 * Note that we still have to be careful here to only unlock each
	 * unique mman once, since a single mman may have mapped our part
	 * multiple times. */
	unsharecow_unlock_unique_mmans_fast(data.ucd_copy);

	/* Drop all of the mman-references that we were still holding on to. */
	unsharecow_decref_mmans_fast(data.ucd_copy);

	/* Finally, release one last lock from the new mem-part
	 * (but keep on holding onto our lock to the original part!) */
	mpart_lock_release(data.ucd_copy);
}



/* Same as `mpart_lock_acquire_and_setcore()', but also ensure that all shared
 * mappings of the given mem-part are no longer mapped with write permissions:
 * >> LIST_FOREACH (node, &self->mp_share, mn_link) {
 * >>     mnode_clear_write(node);
 * >> }
 * Note that copy-on-write (i.e. `&self->mp_copy') nodes don't need to be updated.
 * But also note that copy-on-write mappings usually prevent each other from gaining
 * write access, simply by co-existing. Furthermore, copy-on-write mappings can't
 * gain write-access to underlying mem-parts if those parts might be accessed from
 * the outside world (which is the case when `!mfile_isanon(self->mp_file)').
 *
 * In other words: The only case where there may still be a node associated with
 * `self' that has write-access, applies when:
 *   >> mfile_isanon(self->mp_file) &&               // Backing file isn't anonymous
 *   >> LIST_EMPTY(&self->mp_share) &&               // No secondary shared mappings
 *   >> !LIST_EMPTY(&self->mp_copy) &&               // There is a copy-on-write mapping
 *   >> (LIST_NEXT(LIST_FIRST(&self->mp_copy), mn_link) == NULL) // There is exactly 1 copy-on-write mapping
 * In this case, the node described by `LIST_FIRST(&self->mp_copy)' may still have
 * write-access, and continue to modify the backing memory of `self' after this
 * function was called.
 *
 * However, the purpose of this function is to be used by `mpart_sync()', where
 * syncing an anonymous file wouldn't really make much sense (where the file being
 * anonymous is one of the conditions for a writable copy-on-write mapping to
 * continue to exist) */
FUNDEF NONNULL((1)) void FCALL
mpart_lock_acquire_and_setcore_unwrite(struct mpart *__restrict self)
		THROWS(E_WOULDBLOCK, E_BADALLOC) {
	struct mnode *node;
again:
	mpart_lock_acquire_and_setcore(self);
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
			mpart_lock_release_f(self);
			TRY {
				while (!sync_canwrite(mm))
					task_yield();
			} EXCEPT {
				decref_unlikely(mm);
				mpart_deadnodes_reap(self);
				RETHROW();
			}
			decref_unlikely(mm);
			goto again;
		}
		/* Hard error: bad allocation :( */
		assert(error == MNODE_CLEAR_WRITE_BADALLOC);
		mpart_lock_release(self);
		THROW(E_BADALLOC_INSUFFICIENT_PHYSICAL_MEMORY, 1);
	}
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MPART_LOCK_C */
