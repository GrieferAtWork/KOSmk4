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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_RW_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_RW_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/iovec.h>
#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>
#include <kernel/refcountable.h>
#include <sched/task.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include <kos/except.h>
#include <kos/except/reason/io.h>

#include <alloca.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>

#include <libvio/api.h>

DECL_BEGIN

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
	_mpart_lock_release(part);
	mfile_lock_endwrite_f(file);
	mpart_lockops_reap(part);
	decref_unlikely(part);
	mfile_lockops_reap(file);
}

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
PRIVATE BLOCKING NOBLOCK NONNULL((1)) void FCALL
mfile_write_from_mempart_buffer(struct mfile *__restrict self,
                                struct mpart const *__restrict src,
                                mpart_reladdr_t start_offset,
                                mpart_reladdr_t num_bytes,
                                pos_t dst_offset)
		THROWS(...) {
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

PUBLIC BLOCKING NONNULL((1)) void KCALL
mfile_readall(struct mfile *__restrict self,
              NCX void *dst,
              size_t num_bytes, pos_t src_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	while (num_bytes) {
		size_t temp;
		temp = mfile_read(self, dst, num_bytes, src_offset);
		if (temp >= num_bytes)
			break;
		if (!temp)
			THROW(E_IOERROR_BADBOUNDS, (uintptr_t)E_IOERROR_SUBSYSTEM_FILE);
		dst = (NCX byte_t *)dst + temp;
		num_bytes -= temp;
		src_offset += temp;
	}
}

PUBLIC BLOCKING NONNULL((1)) void KCALL
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

PUBLIC BLOCKING NONNULL((1, 2)) void KCALL
mfile_readallv(struct mfile *__restrict self,
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

PUBLIC BLOCKING NONNULL((1, 2)) void KCALL
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

PUBLIC BLOCKING NONNULL((1)) void KCALL
mfile_writeall(struct mfile *__restrict self, NCX void const *src,
               size_t num_bytes, pos_t dst_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	if unlikely(mfile_write(self, src, num_bytes, dst_offset) < num_bytes)
		THROW(E_FSERROR_FILE_TOO_BIG);
}

PUBLIC BLOCKING NONNULL((1)) void KCALL
mfile_writeall_p(struct mfile *__restrict self, physaddr_t src,
                 size_t num_bytes, pos_t dst_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	if unlikely(mfile_write_p(self, src, num_bytes, dst_offset) < num_bytes)
		THROW(E_FSERROR_FILE_TOO_BIG);
}

PUBLIC BLOCKING NONNULL((1, 2)) void KCALL
mfile_writeallv(struct mfile *__restrict self, struct iov_buffer const *__restrict buf,
                size_t buf_offset, size_t num_bytes, pos_t dst_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	if unlikely(mfile_writev(self, buf, buf_offset, num_bytes, dst_offset) < num_bytes)
		THROW(E_FSERROR_FILE_TOO_BIG);
}

PUBLIC BLOCKING NONNULL((1, 2)) void KCALL
mfile_writeallv_p(struct mfile *__restrict self, struct iov_physbuffer const *__restrict buf,
                  size_t buf_offset, size_t num_bytes, pos_t dst_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, ...) {
	if unlikely(mfile_writev_p(self, buf, buf_offset, num_bytes, dst_offset) < num_bytes)
		THROW(E_FSERROR_FILE_TOO_BIG);
}


PRIVATE WUNUSED size_t
NOTHROW(FCALL get_stackbuf_size)(size_t num_bytes) {
	size_t result;
	result = get_stack_avail();
	if (OVERFLOW_USUB(result, 1024 * sizeof(void *), &result))
		result = 0;
	if (result >= num_bytes) {
		result = num_bytes;
	} else {
		if (result < 512)
			result = 512;
	}
	return result;
}

/* Same as the above, but these use an intermediate (stack) buffer for  transfer.
 * As such, these functions are called by the above when `memcpy_nopf()' produces
 * transfer errors that cannot be resolved by `mman_prefault()' */
PUBLIC BLOCKING NONNULL((1)) size_t KCALL
_mfile_buffered_read(struct mfile *__restrict self, NCX void *dst,
                     size_t num_bytes, pos_t filepos)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	size_t result      = 0;
	size_t stkbuf_size = get_stackbuf_size(num_bytes);
	byte_t *stkbuf     = (byte_t *)alloca(stkbuf_size);
	for (;;) {
		size_t temp, part;
		part = num_bytes;
		if (part > stkbuf_size)
			part = stkbuf_size;
		temp = mfile_read(self, stkbuf, part, filepos);
		assert(temp <= part);
		dst = mempcpy(dst, stkbuf, temp);
		result += temp;
		if (temp < part)
			break;
		num_bytes -= temp;
		filepos += temp;
	}
	return result;
}

PUBLIC BLOCKING NONNULL((1)) size_t KCALL
_mfile_buffered_write(struct mfile *__restrict self, NCX void const *src,
                      size_t num_bytes, pos_t filepos)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	size_t result      = 0;
	size_t stkbuf_size = get_stackbuf_size(num_bytes);
	byte_t *stkbuf     = (byte_t *)alloca(stkbuf_size);
	for (;;) {
		size_t temp, part;
		part = num_bytes;
		if (part > stkbuf_size)
			part = stkbuf_size;
		src  = mempcpy(stkbuf, src, part);
		temp = mfile_write(self, stkbuf, part, filepos);
		assert(temp <= part);
		result += temp;
		if (temp < part)
			break;
		num_bytes -= temp;
		filepos += temp;
	}
	return result;
}

PUBLIC BLOCKING NONNULL((1)) size_t KCALL
_mfile_buffered_tailwrite(struct mfile *__restrict self,
                          NCX void const *src,
                          size_t num_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	size_t result      = 0;
	size_t stkbuf_size = get_stackbuf_size(num_bytes);
	byte_t *stkbuf     = (byte_t *)alloca(stkbuf_size);
	for (;;) {
		size_t temp, part;
		part = num_bytes;
		if (part > stkbuf_size)
			part = stkbuf_size;
		src = mempcpy(stkbuf, src, part);
		temp = mfile_tailwrite(self, stkbuf, part);
		assert(temp <= part);
		result += temp;
		if (temp < part)
			break;
		num_bytes -= temp;
	}
	return result;
}

PUBLIC BLOCKING NONNULL((1, 2)) size_t KCALL
_mfile_buffered_readv(struct mfile *__restrict self, struct iov_buffer const *__restrict buf,
                      size_t buf_offset, size_t num_bytes, pos_t filepos)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	size_t result = 0;
	struct iov_entry ent;
	IOV_BUFFER_FOREACH(ent, buf) {
		size_t temp;
		if (buf_offset) {
			if (ent.ive_size >= buf_offset) {
				buf_offset -= ent.ive_size;
				continue;
			}
			ent.ive_base += buf_offset;
			ent.ive_size -= buf_offset;
			buf_offset = 0;
		}
		if (ent.ive_size > num_bytes)
			ent.ive_size = num_bytes;
		temp = _mfile_buffered_read(self, ent.ive_base, ent.ive_size, filepos);
		result += temp;
		if (temp < ent.ive_size)
			break;
		num_bytes -= temp;
		filepos += temp;
	}
	return result;
}

PUBLIC BLOCKING NONNULL((1, 2)) size_t KCALL
_mfile_buffered_writev(struct mfile *__restrict self, struct iov_buffer const *__restrict buf,
                       size_t buf_offset, size_t num_bytes, pos_t filepos)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	size_t result = 0;
	struct iov_entry ent;
	IOV_BUFFER_FOREACH(ent, buf) {
		size_t temp;
		if (buf_offset) {
			if (ent.ive_size >= buf_offset) {
				buf_offset -= ent.ive_size;
				continue;
			}
			ent.ive_base += buf_offset;
			ent.ive_size -= buf_offset;
			buf_offset = 0;
		}
		if (ent.ive_size > num_bytes)
			ent.ive_size = num_bytes;
		temp = _mfile_buffered_write(self, ent.ive_base, ent.ive_size, filepos);
		result += temp;
		if (temp < ent.ive_size)
			break;
		num_bytes -= temp;
		filepos += temp;
	}
	return result;
}

PUBLIC BLOCKING NONNULL((1, 2)) size_t KCALL
_mfile_buffered_tailwritev(struct mfile *__restrict self,
                           struct iov_buffer const *__restrict buf,
                           size_t buf_offset, size_t num_bytes)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	size_t result = 0;
	struct iov_entry ent;
	IOV_BUFFER_FOREACH(ent, buf) {
		size_t temp;
		if (buf_offset) {
			if (ent.ive_size >= buf_offset) {
				buf_offset -= ent.ive_size;
				continue;
			}
			ent.ive_base += buf_offset;
			ent.ive_size -= buf_offset;
			buf_offset = 0;
		}
		if (ent.ive_size > num_bytes)
			ent.ive_size = num_bytes;
		temp = _mfile_buffered_tailwrite(self, ent.ive_base, ent.ive_size);
		result += temp;
		if (temp < ent.ive_size)
			break;
		num_bytes -= temp;
	}
	return result;
}


struct mfile_trunclock_dec_object: refcountable {
	REF struct mfile *mtldo_file; /* [1..1][const] File to unlock upon destruction. */
};

#define mfile_trunclock_dec_object_fini(self) \
	(mfile_trunclock_dec((self)->mtldo_file), \
	 decref_unlikely((self)->mtldo_file))
#define mfile_trunclock_dec_object_fini_without_unlock(self) \
	(decref_unlikely((self)->mtldo_file))

struct mfile_trunclock_dec_object_ex: mfile_trunclock_dec_object {
	REF struct refcountable *mtldo_inner; /* [0..1][const] Inner object. */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_trunclock_dec_object_destroy)(struct refcountable *__restrict self) {
	struct mfile_trunclock_dec_object *me;
	me = (struct mfile_trunclock_dec_object *)self;
	mfile_trunclock_dec_object_fini(me);
	kfree(me);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_trunclock_dec_object_ex_destroy)(struct refcountable *__restrict self) {
	struct mfile_trunclock_dec_object_ex *me;
	me = (struct mfile_trunclock_dec_object_ex *)self;
	decref(me->mtldo_inner);
	mfile_trunclock_dec_object_fini(me);
	kfree(me);
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mfile_trunclock_dec_object_destroy_without_unlock)(struct refcountable *__restrict self) {
	struct mfile_trunclock_dec_object_ex *me;
	me = (struct mfile_trunclock_dec_object_ex *)self;
	if (me->rca_destroy == &mfile_trunclock_dec_object_ex_destroy)
		decref(me->mtldo_inner);
	mfile_trunclock_dec_object_fini_without_unlock(me);
	kfree(me);
}


/* Try to create a refcountable object to drop a trunc-lock from `self'
 * once  that object gets destroyed. References to this object are then
 * stored alongside `aio_handle's constructed to perform async reads or
 * writes to/from `self' in `mfile_direct_read_async()' & friends.
 *
 * This function behaves as follows:
 * @throws:        Already called `mfile_trunclock_dec(self)'
 * @return: false: Already called `mfile_trunclock_dec(self)' (try again)
 * @return: true:  `*p_result' is now non-NULL */
PRIVATE WUNUSED bool KCALL
mfile_create_trunclock_dec_or_unlock(struct mfile *__restrict self,
                                     REF struct refcountable **__restrict p_result,
                                     struct refcountable *inner)
		THROWS(E_BADALLOC) {
	bool locked = true;
	size_t objsiz;
	struct mfile_trunclock_dec_object_ex *result;
	if (*p_result)
		goto done; /* Already allocated :) */
	objsiz = inner ? sizeof(struct mfile_trunclock_dec_object_ex)
	               : sizeof(struct mfile_trunclock_dec_object);
	result = (struct mfile_trunclock_dec_object_ex *)kmalloc_nx(objsiz, GFP_ATOMIC);
	if (!result) {
		/* Must unlock in order to allocate while blocking. */
		mfile_trunclock_dec(self);
		result = (struct mfile_trunclock_dec_object_ex *)kmalloc(objsiz, GFP_NORMAL);
		locked = false;
	}

	/* Initialize the lock holder. */
	result->mtldo_file = incref(self);
	result->rca_refcnt = 1;
	if (inner != NULL) {
		result->mtldo_inner = incref(inner);
		result->rca_destroy = &mfile_trunclock_dec_object_ex_destroy;
	} else {
		result->rca_destroy = &mfile_trunclock_dec_object_destroy;
	}
	*p_result = result;
done:
	return locked;
}


DECL_END


#ifndef __INTELLISENSE__
#ifdef LIBVIO_CONFIG_ENABLED
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
#endif /* LIBVIO_CONFIG_ENABLED */

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

/* "direct" I/O */
#define DEFINE_mfile_direct_read
#include "mfile-rw.c.inl"
#define DEFINE_mfile_direct_readv
#include "mfile-rw.c.inl"
#define DEFINE_mfile_direct_write
#include "mfile-rw.c.inl"
#define DEFINE_mfile_direct_writev
#include "mfile-rw.c.inl"
#define DEFINE_mfile_direct_read_p
#include "mfile-rw.c.inl"
#define DEFINE_mfile_direct_readv_p
#include "mfile-rw.c.inl"
#define DEFINE_mfile_direct_write_p
#include "mfile-rw.c.inl"
#define DEFINE_mfile_direct_writev_p
#include "mfile-rw.c.inl"
#define DEFINE_mfile_direct_read_async
#include "mfile-rw.c.inl"
#define DEFINE_mfile_direct_readv_async
#include "mfile-rw.c.inl"
#define DEFINE_mfile_direct_write_async
#include "mfile-rw.c.inl"
#define DEFINE_mfile_direct_writev_async
#include "mfile-rw.c.inl"
#define DEFINE_mfile_direct_read_async_p
#include "mfile-rw.c.inl"
#define DEFINE_mfile_direct_readv_async_p
#include "mfile-rw.c.inl"
#define DEFINE_mfile_direct_write_async_p
#include "mfile-rw.c.inl"
#define DEFINE_mfile_direct_writev_async_p
#include "mfile-rw.c.inl"
#endif /* !__INTELLISENSE__ */

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_RW_C */
