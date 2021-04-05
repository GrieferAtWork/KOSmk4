/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_RW_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_RW_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#ifdef CONFIG_USE_NEW_FS
#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>

#include <hybrid/align.h>

#include <kos/except.h>
#include <kos/except/reason/io.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#ifndef __OPTIMIZE_SIZE__
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mchunkvec_truncate)(struct mchunkvec *__restrict self,
                                  physpagecnt_t total_pages) {
	size_t keep, i;
	physpagecnt_t total = 0;
	assert(total_pages != 0);
	for (i = 0;; ++i) {
		assert(i < self->ms_c);
		total += self->ms_v[i].mc_size;
		if (total >= total_pages)
			break;
	}
	total -= self->ms_v[i].mc_size;
	keep = total_pages - total;
	assert(keep != 0);
	assert(keep <= self->ms_v[i].mc_size);
	if (keep < self->ms_v[i].mc_size) {
		page_free(self->ms_v[i].mc_start + keep,
		          self->ms_v[i].mc_size - keep);
		self->ms_v[i].mc_size = keep;
	}
	++i;
	assert(i <= self->ms_c);
	if (i < self->ms_c) {
		struct mchunk *vec;
		size_t j;
		for (j = i; j < self->ms_c; ++j) {
			page_free(self->ms_v[j].mc_start,
			          self->ms_v[j].mc_size);
		}
		vec = (struct mchunk *)krealloc_nx(self->ms_v,
		                                   i * sizeof(struct mchunk),
		                                   GFP_ATOMIC | GFP_PREFLT | GFP_LOCKED);
		if likely(vec != NULL)
			self->ms_v = vec;
		self->ms_c = i;
	}
}


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_truncate_restore)(struct mpart *__restrict self,
                                      PAGEDIR_PAGEALIGNED mpart_reladdr_t orig_size) {
	mpart_tree_removenode(&self->mp_file->mf_parts, self);
	self->mp_maxaddr = self->mp_minaddr + orig_size - 1;
	mpart_tree_insert(&self->mp_file->mf_parts, self);
	if (!(self->mp_flags & MPART_F_BLKST_INL) && self->mp_blkst_ptr != NULL) {
		size_t block_count, word_count;
		mpart_blkst_word_t *new_bitset;
		block_count = orig_size >> self->mp_file->mf_blockshift;
		word_count  = CEILDIV(block_count, MPART_BLKST_BLOCKS_PER_WORD);
		/* Try to release unused memory. */
		new_bitset = (mpart_blkst_word_t *)krealloc_nx(self->mp_blkst_ptr,
		                                               word_count * sizeof(mpart_blkst_word_t),
		                                               GFP_ATOMIC | GFP_PREFLT | GFP_LOCKED);
		if likely(new_bitset)
			self->mp_blkst_ptr = new_bitset;
	}
	switch (self->mp_state) {

	case MPART_ST_VOID:
		break;

	case MPART_ST_MEM: {
		physpagecnt_t num_pages;
		num_pages = orig_size >> PAGESHIFT;
		assert(self->mp_mem.mc_size >= num_pages);
		if (self->mp_mem.mc_size > num_pages) {
			page_free(self->mp_mem.mc_start + num_pages,
			          self->mp_mem.mc_size - num_pages);
			self->mp_mem.mc_size = num_pages;
		}
	}	break;

	case MPART_ST_MEM_SC: {
		physpagecnt_t num_pages;
		num_pages = orig_size >> PAGESHIFT;
		mchunkvec_truncate(&self->mp_mem_sc, num_pages);
	}	break;

	default: __builtin_unreachable();
	}
}


PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL mpart_truncate_undo)(struct mfile *__restrict file,
                                   /*inherit(always)*/ REF struct mpart *__restrict part,
                                   mpart_reladdr_t orig_size) {
	mpart_truncate_restore(part, orig_size);
	mpart_lock_release_f(part);
	mfile_lock_endwrite_f(file);
	mpart_lockops_reap(part);
	decref_unlikely(part);
	mfile_lockops_reap(file);
}


#endif /* !__OPTIMIZE_SIZE__ */

struct mfile_unlockinfo: unlockinfo {
	struct mfile *mfui_file; /* [1..1] The file to unlock. */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_unlockinfo_cb)(struct unlockinfo *__restrict self) {
	struct mfile_unlockinfo *me;
	me = (struct mfile_unlockinfo *)self;
	mfile_lock_endwrite(me->mfui_file);
}

struct mpart_truncate_undo_unlockinfo: unlockinfo {
	struct mfile    *mtuu_file;      /* [1..1] ... */
	struct mpart    *mtuu_part;      /* [1..1] ... */
	mpart_reladdr_t  mtuu_orig_size; /* ... */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_truncate_undo_unlockinfo_cb)(struct unlockinfo *__restrict self) {
	struct mpart_truncate_undo_unlockinfo *me;
	me = (struct mpart_truncate_undo_unlockinfo *)self;
	mpart_truncate_restore(me->mtuu_part, me->mtuu_orig_size);
	mfile_lock_endwrite(me->mtuu_file);
}

/* Write the  physical  memory  contents
 * of  `sec[start_offset...+=num_bytes]'
 * into `self[dst_offset...+=num_bytes]' */
PRIVATE NOBLOCK NONNULL((1)) void FCALL
mfile_write_from_mempart_buffer(struct mfile *__restrict self,
                                struct mpart const *__restrict src,
                                mpart_reladdr_t start_offset,
                                mpart_reladdr_t num_bytes,
                                pos_t dst_offset) {
	if (src->mp_state == MPART_ST_MEM) {
		physaddr_t srcaddr;
		srcaddr = physpage2addr(src->mp_mem.mc_start);
		srcaddr += start_offset;
		mfile_write_p(self, srcaddr, num_bytes, dst_offset);
	} else {
		size_t i;
		assert(src->mp_state == MPART_ST_MEM_SC);
		for (i = 0; i < src->mp_mem_sc.ms_c; ++i) {
			struct mchunk chunk;
			physaddr_t chunk_addr;
			size_t chunk_size;
			chunk      = src->mp_mem_sc.ms_v[i];
			chunk_addr = physpage2addr(chunk.mc_start);
			chunk_size = chunk.mc_size << PAGESHIFT;
			if (start_offset != 0) {
				if (start_offset >= chunk_size) {
					start_offset -= chunk_size;
					continue;
				}
				chunk_addr += start_offset;
				chunk_size -= start_offset;
				start_offset = 0;
			}
			if (chunk_size > num_bytes)
				chunk_size = num_bytes;
			mfile_write_p(self, chunk_addr, chunk_size, dst_offset);
			if (chunk_size >= num_bytes)
				break;
			num_bytes -= chunk_size;
			dst_offset += chunk_size;
		}
	}
}

PUBLIC WUNUSED NONNULL((1)) void KCALL
mfile_readall(struct mfile *__restrict self,
              USER CHECKED void *dst,
              size_t num_bytes, pos_t src_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	while (num_bytes) {
		size_t temp;
		temp = mfile_read(self, dst, num_bytes, src_offset);
		if (temp >= num_bytes)
			break;
		if (!temp)
			THROW(E_IOERROR_BADBOUNDS, (uintptr_t)E_IOERROR_SUBSYSTEM_FILE);
		dst = (USER CHECKED byte_t *)dst + temp;
		num_bytes -= temp;
		src_offset += temp;
	}
}

PUBLIC WUNUSED NONNULL((1)) void KCALL
mfile_readall_p(struct mfile *__restrict self,
                physaddr_t dst,
                size_t num_bytes, pos_t src_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	while (num_bytes) {
		size_t temp;
		temp = mfile_read_p(self, dst, num_bytes, src_offset);
		if (temp >= num_bytes)
			break;
		if (!temp)
			THROW(E_IOERROR_BADBOUNDS, (uintptr_t)E_IOERROR_SUBSYSTEM_FILE);
		dst += temp;
		num_bytes -= temp;
		src_offset += temp;
	}
}

PUBLIC WUNUSED NONNULL((1, 2)) void KCALL
mfile_readvall(struct mfile *__restrict self,
               struct iov_buffer const *__restrict buf,
               size_t buf_offset, size_t num_bytes,
               pos_t src_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	while (num_bytes) {
		size_t temp;
		temp = mfile_readv(self, buf, buf_offset, num_bytes, src_offset);
		if (temp >= num_bytes)
			break;
		if (!temp)
			THROW(E_IOERROR_BADBOUNDS, (uintptr_t)E_IOERROR_SUBSYSTEM_FILE);
		buf_offset += temp;
		num_bytes -= temp;
		src_offset += temp;
	}
}

PUBLIC WUNUSED NONNULL((1, 2)) void KCALL
mfile_readallv_p(struct mfile *__restrict self,
                 struct iov_physbuffer const *__restrict buf,
                 size_t buf_offset, size_t num_bytes,
                 pos_t src_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	while (num_bytes) {
		size_t temp;
		temp = mfile_readv_p(self, buf, buf_offset, num_bytes, src_offset);
		if (temp >= num_bytes)
			break;
		if (!temp)
			THROW(E_IOERROR_BADBOUNDS, (uintptr_t)E_IOERROR_SUBSYSTEM_FILE);
		buf_offset += temp;
		num_bytes -= temp;
		src_offset += temp;
	}
}


DECL_END
#endif /* CONFIG_USE_NEW_FS */


#ifndef __INTELLISENSE__
#define DEFINE_mfile_vioread
#include "mfile-rw-vio.c.inl"
#define DEFINE_mfile_vioread_p
#include "mfile-rw-vio.c.inl"
#define DEFINE_mfile_vioreadv
#include "mfile-rw-vio.c.inl"
#define DEFINE_mfile_vioreadv_p
#include "mfile-rw-vio.c.inl"
#define DEFINE_mfile_viowrite
#include "mfile-rw-vio.c.inl"
#define DEFINE_mfile_viowrite_p
#include "mfile-rw-vio.c.inl"
#define DEFINE_mfile_viowritev
#include "mfile-rw-vio.c.inl"
#define DEFINE_mfile_viowritev_p
#include "mfile-rw-vio.c.inl"

#define DEFINE_mfile_read
#include "mfile-rw.c.inl"
#define DEFINE_mfile_read_p
#include "mfile-rw.c.inl"
#define DEFINE_mfile_readv
#include "mfile-rw.c.inl"
#define DEFINE_mfile_readv_p
#include "mfile-rw.c.inl"
#define DEFINE_mfile_tailread
#include "mfile-rw.c.inl"
#define DEFINE_mfile_tailread_p
#include "mfile-rw.c.inl"
#define DEFINE_mfile_tailreadv
#include "mfile-rw.c.inl"
#define DEFINE_mfile_tailreadv_p
#include "mfile-rw.c.inl"

#define DEFINE_mfile_write
#include "mfile-rw.c.inl"
#define DEFINE_mfile_write_p
#include "mfile-rw.c.inl"
#define DEFINE_mfile_writev
#include "mfile-rw.c.inl"
#define DEFINE_mfile_writev_p
#include "mfile-rw.c.inl"
#define DEFINE_mfile_tailwrite
#include "mfile-rw.c.inl"
#define DEFINE_mfile_tailwrite_p
#include "mfile-rw.c.inl"
#define DEFINE_mfile_tailwritev
#include "mfile-rw.c.inl"
#define DEFINE_mfile_tailwritev_p
#include "mfile-rw.c.inl"
#endif /* !__INTELLISENSE__ */


#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_RW_C */
