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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_MISALIGNED_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_MISALIGNED_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/malloc.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/phys.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include <kos/except.h>

#include <assert.h>
#include <format-printer.h>
#include <inttypes.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

struct misaligned_mfile: mfile {
	REF struct mfile *mam_base; /* [1..1][const] The underlying mem-file. */
	pos_t             mam_offs; /* [const] Offset addend added to every request. */
};

#define mfile_asmisaligned(self) ((struct misaligned_mfile *)(self))
#define mfile_ismisaligned(self) ((self)->mf_ops == &misaligned_mfile_ops)


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL misaligned_mfile_v_destroy)(struct mfile *__restrict self) {
	struct misaligned_mfile *me;
	me = mfile_asmisaligned(self);
	decref_unlikely(me->mam_base);
	kfree(me);
}

PRIVATE BLOCKING NONNULL((1, 5)) void KCALL
misaligned_mfile_v_loadblocks(struct mfile *__restrict self, pos_t addr,
                              physaddr_t buf, size_t num_bytes,
                              struct aio_multihandle *__restrict aio) {
	struct misaligned_mfile *me;
	struct mfile *base;
	me   = mfile_asmisaligned(self);
	base = me->mam_base;

	/* Apply addend */
	if (OVERFLOW_UADD(addr, me->mam_offs, &addr)) {
		/* Out-of-bounds --> always read zero-bytes. */
		bzerophyscc(buf, num_bytes);
		return;
	}

	/* Check if direct I/O is possible. */
	if (addr == ((addr >> base->mf_blockshift) << base->mf_blockshift)) {
		/* Can use direct I/O
		 * NOTE: No need to ensure that `buf' or `num_bytes' are proper aligned:
		 *  - `buf'       is properly aligned because `me->mf_iobashift == base->mf_iobashift'
		 *  - `num_bytes' is properly aligned because `me->mf_blockshift >= base->mf_blockshift' */
		pos_t filesize, io_bytes;

		/* Prevent the base file from being truncated. */
		mfile_lock_write(base);
		mfile_trunclock_inc(base);
		mfile_lock_endwrite(base);
		RAII_FINALLY { mfile_trunclock_dec(base); };

		/* Figure out how much data we can load from the base file. */
		filesize = mfile_getsize(base);
		filesize = CEIL_ALIGN(filesize, mfile_getblocksize(base));
		if (OVERFLOW_USUB(filesize, addr, &io_bytes))
			io_bytes = 0;
		if ((pos_t)num_bytes <= io_bytes) {
			/* Can load everything from the file */
			(*base->mf_ops->mo_loadblocks)(base, addr, buf, num_bytes, aio);
		} else {
			if (io_bytes != 0)
				(*base->mf_ops->mo_loadblocks)(base, addr, buf, (size_t)io_bytes, aio);

			/* Must zero-initialize trailing data. */
			bzerophyscc(buf + (size_t)io_bytes, num_bytes - (size_t)io_bytes);
		}
	} else {
		/* Must use buffered I/O */
		mfile_readall_p(base, buf, num_bytes, addr);
	}
}


PRIVATE BLOCKING WUNUSED NONNULL((1)) size_t KCALL
misaligned_mfile_v_pread(struct mfile *__restrict self, NCX void *dst,
                         size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	struct misaligned_mfile *me;
	me = mfile_asmisaligned(self);
	if (OVERFLOW_UADD(addr, me->mam_offs, &addr))
		return 0; /* TODO: Read from /dev/zero */
	return mfile_upread(me->mam_base, dst, num_bytes, addr, mode);
}

PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL
misaligned_mfile_v_preadv(struct mfile *__restrict self, struct iov_buffer *__restrict dst,
                          size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	struct misaligned_mfile *me;
	me = mfile_asmisaligned(self);
	if (OVERFLOW_UADD(addr, me->mam_offs, &addr))
		return 0; /* TODO: Read from /dev/zero */
	return mfile_upreadv(me->mam_base, dst, num_bytes, addr, mode);
}

PRIVATE BLOCKING WUNUSED NONNULL((1)) REF void * KCALL
misaligned_mfile_v_tryas(struct mfile *__restrict self,
                         uintptr_half_t wanted_type)
		THROWS(...) {
	struct misaligned_mfile *me;
	me = mfile_asmisaligned(self);
	return mfile_utryas(me->mam_base, wanted_type);
}

PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) ssize_t KCALL
misaligned_mfile_v_printlink(struct mfile *__restrict self,
                             pformatprinter printer, void *arg)
		THROWS(E_WOULDBLOCK, ...) {
	ssize_t temp, result;
	struct misaligned_mfile *me;
	me     = mfile_asmisaligned(self);
	result = (*printer)(arg, "misaligned:[", 12);
	if unlikely(result < 0)
		goto done;
	temp = mfile_uprintlink(me->mam_base, printer, arg);
	if unlikely(temp < 0)
		goto err;
	result += temp;
	temp = format_printf(printer, arg,
	                     ":+%" PRIuN(__SIZEOF_POS_T__) "]",
	                     me->mam_offs);
	if unlikely(temp < 0)
		goto err;
	result += temp;

done:
	return result;
err:
	return temp;
}

PRIVATE ATTR_BLOCKLIKE_CC(info) NONNULL((1)) void
NOTHROW(KCALL misaligned_mfile_v_cc)(struct mfile *__restrict self,
                                     struct ccinfo *__restrict info) {
	struct misaligned_mfile *me;
	struct mfile_stream_ops const *inner_stream;
	me           = mfile_asmisaligned(self);
	inner_stream = me->mam_base->mf_ops->mo_stream;
	if (inner_stream->mso_cc)
		(*inner_stream->mso_cc)(me->mam_base, info);
}

PRIVATE struct mfile_stream_ops const misaligned_mfile_v_stream_ops = {
	.mso_pread     = &misaligned_mfile_v_pread,
	.mso_preadv    = &misaligned_mfile_v_preadv,
	.mso_tryas     = &misaligned_mfile_v_tryas,
	.mso_printlink = &misaligned_mfile_v_printlink,
	.mso_cc        = &misaligned_mfile_v_cc,
};

PRIVATE struct mfile_ops const misaligned_mfile_ops = {
	.mo_destroy    = &misaligned_mfile_v_destroy,
	.mo_loadblocks = &misaligned_mfile_v_loadblocks,
	.mo_stream     = &misaligned_mfile_v_stream_ops,
};


/* Create a wrapper file whose I/O cache is lazily populated from  `inner',
 * with the given `inner_fpos' addend added to all file offsets. Note  that
 * writes  to the  returned file will  _NEVER_ be passed  along to `inner',
 * and that any modifications made to portions of `inner' that have already
 * been loaded by `return' will _NOT_ be visible.
 *
 * This function is primarily used as a hacky wrapper for loading PE files
 * into memory (as those  sometimes have sub-page alignment  constraints).
 *
 * NOTE: The caller must ensure that `mfile_hasrawio(inner)'! */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mfile *FCALL
mfile_create_misaligned_wrapper(struct mfile *__restrict inner,
                                pos_t inner_fpos)
		THROWS(E_BADALLOC) {
	REF struct misaligned_mfile *result;
	shift_t blockshift;
	assertf(mfile_hasrawio(inner), "The underlying file must support RAW I/O");

	/* TODO: mfile-s need to maintain a list of linked misaligned files,
	 *       and the misaligned files  themselves must NOT be  anonymous
	 *       from the get-go.
	 * This is required so that `ftruncate(2)' can force-load  MAP_PRIVATE
	 * mappings of misaligned wrappers into memory before they are deleted
	 * from disk.
	 *
	 * Essentially,  misaligned  wrappers need  the extra  requirement that
	 * their misalignment must  be `<= mam_base->mf_part_amask', and  there
	 * needs to  be a  singly-linked-list  (sorted by  `mam_offs',  deleted
	 * when `MFILE_F_DELETED' gets set, and locked by mfile_tslock_acquire)
	 * that keeps track of all  currently allocated misaligned wrappers  of
	 * some given mfile. */

	if unlikely(inner->mf_ops->mo_loadblocks == NULL)
		goto return_inner; /* File offsets don't matter in this case! */
	if unlikely(inner_fpos == 0)
		goto return_inner; /* No misalignment --> no need to create a wrapper! */

	/* Allocate a new `struct misaligned_mfile' */
	result = (REF struct misaligned_mfile *)kmalloc(sizeof(struct misaligned_mfile), GFP_NORMAL);
	blockshift = inner->mf_blockshift;
	if (blockshift < PAGESHIFT) {
		/* Because  it's the most efficient shift, and  because we're free to pick whatever
		 * shift we want to pick for misaligned wrapper files, we can simply pick PAGESHIFT
		 * as our block-shift. */
		blockshift = PAGESHIFT;
	}
	_mfile_init(result, &misaligned_mfile_ops, blockshift, inner->mf_iobashift);
	result->mf_parts             = MFILE_PARTS_ANONYMOUS;
	result->mf_changed.slh_first = MFILE_PARTS_ANONYMOUS;
	atomic64_init(&result->mf_filesize, (uint64_t)-1);

	/* Set-up flags */
	result->mf_flags = MFILE_F_READONLY | MFILE_F_NOATIME |
	                   MFILE_F_NOMTIME | MFILE_F_FIXEDFILESIZE;

	mfile_tslock_acquire(inner);
	if unlikely(inner->mf_flags & MFILE_F_DELETED) {
		mfile_tslock_release_br(inner);
		/* Deleted file --> don't create a misalignment wrapper! */
		goto kfree_result_and_return_inner;
	}
	result->mf_atime = inner->mf_atime;
	result->mf_mtime = inner->mf_mtime;
	result->mf_ctime = inner->mf_ctime;
	result->mf_btime = inner->mf_btime;
	mfile_tslock_release(inner);

	/* Fill in remaining fields. */
	if (mfile_ismisaligned(inner)) {
		/* Cascade offsets to merge miss-alignments for readthru */
		struct misaligned_mfile *inner_miss;
		inner_miss = mfile_asmisaligned(inner);
		if (OVERFLOW_UADD(inner_fpos, inner_miss->mam_offs, &inner_fpos)) {
			/* Reading  from out-of-bounds addresses yields ZEROes. In a
			 * situation where _all_ addresses are out-of-bounds, we can
			 * simply return /dev/zero instead of creating a new file! */
			kfree(result);
			return incref(&mfile_zero);
		}
		result->mam_base = incref(inner_miss->mam_base);
		result->mam_offs = inner_fpos;
	} else {
		result->mam_base = incref(inner);
		result->mam_offs = inner_fpos;
	}
	return result;
kfree_result_and_return_inner:
	kfree(result);
return_inner:
	return incref(inner);
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_MISALIGNED_C */
