/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_MISSALIGNED_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_MISSALIGNED_C 1
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

struct missaligned_mfile: mfile {
	REF struct mfile *mam_base; /* [1..1][const] The underlying mem-file. */
	pos_t             mam_offs; /* [const] Offset addend added to every request. */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL missaligned_mfile_v_destroy)(struct mfile *__restrict self) {
	struct missaligned_mfile *me;
	me = (struct missaligned_mfile *)self;
	decref_unlikely(me->mam_base);
	kfree(me);
}

PRIVATE BLOCKING NONNULL((1, 5)) void KCALL
missaligned_mfile_v_loadblocks(struct mfile *__restrict self, pos_t addr,
                               physaddr_t buf, size_t num_bytes,
                               struct aio_multihandle *__restrict aio) {
	struct missaligned_mfile *me;
	struct mfile *base;
	me   = (struct missaligned_mfile *)self;
	base = me->mam_base;

	/* Apply addend */
	addr += me->mam_offs;

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
missaligned_mfile_v_pread(struct mfile *__restrict self, USER CHECKED void *dst,
                          size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	struct missaligned_mfile *me;
	me = (struct missaligned_mfile *)self;
	if (OVERFLOW_UADD(addr, me->mam_offs, &addr))
		return 0;
	return mfile_upread(me->mam_base, dst, num_bytes, addr, mode);
}

PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL
missaligned_mfile_v_preadv(struct mfile *__restrict self, struct iov_buffer *__restrict dst,
                           size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	struct missaligned_mfile *me;
	me = (struct missaligned_mfile *)self;
	if (OVERFLOW_UADD(addr, me->mam_offs, &addr))
		return 0;
	return mfile_upreadv(me->mam_base, dst, num_bytes, addr, mode);
}

PRIVATE BLOCKING WUNUSED NONNULL((1)) REF void * KCALL
missaligned_mfile_v_tryas(struct mfile *__restrict self,
                          uintptr_half_t wanted_type)
		THROWS(...) {
	struct missaligned_mfile *me;
	me = (struct missaligned_mfile *)self;
	return mfile_utryas(me->mam_base, wanted_type);
}

PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) ssize_t KCALL
missaligned_mfile_v_printlink(struct mfile *__restrict self,
                              pformatprinter printer, void *arg)
		THROWS(E_WOULDBLOCK, ...) {
	ssize_t temp, result;
	struct missaligned_mfile *me;
	me     = (struct missaligned_mfile *)self;
	result = (*printer)(arg, "[", 1);
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

PRIVATE NOBLOCK_IF(ccinfo_noblock(info)) NONNULL((1)) void
NOTHROW(KCALL missaligned_mfile_v_cc)(struct mfile *__restrict self,
                                      struct ccinfo *__restrict info) {
	struct missaligned_mfile *me;
	struct mfile_stream_ops const *inner_stream;
	me           = (struct missaligned_mfile *)self;
	inner_stream = me->mam_base->mf_ops->mo_stream;
	if (inner_stream->mso_cc)
		(*inner_stream->mso_cc)(me->mam_base, info);
}

PRIVATE struct mfile_stream_ops const missaligned_mfile_v_stream_ops = {
	.mso_pread     = &missaligned_mfile_v_pread,
	.mso_preadv    = &missaligned_mfile_v_preadv,
	.mso_tryas     = &missaligned_mfile_v_tryas,
	.mso_printlink = &missaligned_mfile_v_printlink,
	.mso_cc        = &missaligned_mfile_v_cc,
};

PRIVATE struct mfile_ops const missaligned_mfile_ops = {
	.mo_destroy    = &missaligned_mfile_v_destroy,
	.mo_loadblocks = &missaligned_mfile_v_loadblocks,
	.mo_stream     = &missaligned_mfile_v_stream_ops,
};

/* Create a wrapper file whose I/O cache is lazily populated from  `inner',
 * with the given `inner_fpos' addend added to all file offsets. Note  that
 * writes  to the  returned file will  _NEVER_ be passed  along to `inner',
 * and that any modifications made to portions of `inner' that have already
 * been loaded by `return' will _NOT_ be visible.
 *
 * This function is primarily used as a hacky wrapper for loading PE files
 * into memory (as those  sometimes have sub-page alignment  constraints). */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct mfile *FCALL
mfile_create_missaligned_wrapper(struct mfile *__restrict inner,
                                 pos_t inner_fpos)
		THROWS(E_BADALLOC) {
	REF struct missaligned_mfile *result;
	shift_t blockshift;
	if unlikely(inner->mf_ops->mo_loadblocks == NULL)
		return incref(inner); /* File offsets don't matter in this case! */
	result = (REF struct missaligned_mfile *)kmalloc(sizeof(struct missaligned_mfile), GFP_NORMAL);
	blockshift = inner->mf_blockshift;
	if (blockshift < PAGESHIFT)
		blockshift = PAGESHIFT;
	_mfile_init(result, &missaligned_mfile_ops, blockshift, inner->mf_iobashift);
	result->mf_parts             = MFILE_PARTS_ANONYMOUS;
	result->mf_changed.slh_first = MFILE_PARTS_ANONYMOUS;
	atomic64_init(&result->mf_filesize, (uint64_t)-1);

	/* Set-up flags */
	result->mf_flags = MFILE_F_READONLY | MFILE_F_NOATIME |
	                   MFILE_F_NOMTIME | MFILE_F_FIXEDFILESIZE;

	mfile_tslock_acquire(inner);
	if (!(inner->mf_flags & MFILE_F_DELETED)) {
		result->mf_atime = inner->mf_atime;
		result->mf_mtime = inner->mf_mtime;
		result->mf_ctime = inner->mf_ctime;
		result->mf_btime = inner->mf_btime;
	} else {
		result->mf_atime = realtime();
		result->mf_mtime = result->mf_atime;
		result->mf_ctime = result->mf_atime;
		result->mf_btime = result->mf_atime;
	}
	mfile_tslock_release(inner);

	/* Fill in remaining fields. */
	result->mam_base = incref(inner);
	result->mam_offs = inner_fpos;
	return result;
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_MISSALIGNED_C */
