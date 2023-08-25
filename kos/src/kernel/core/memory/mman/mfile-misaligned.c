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
#define __WANT_MISALIGNED_MFILE__mam_lop
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/devfs.h>
#include <kernel/fs/null.h>
#include <kernel/malloc.h>
#include <kernel/mman/mfile-misaligned.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/phys.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>
#include <hybrid/sched/__preemption.h>

#include <kos/except.h>
#include <sys/stat.h>

#include <assert.h>
#include <atomic.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(LOCKOP_CC misaligned_mfile_remove_from_base_msalign_plop)(Tobpostlockop(mfile) *__restrict self,
                                                                  REF struct mfile *__restrict base) {
	struct misaligned_mfile *me;
	me = container_of(self, struct misaligned_mfile, _mam_plop);
	kfree(me);           /* Free the original, misaligned file. */
	decref_nokill(base); /* *_nokill since we know that our caller is also holding a reference! */
}

PRIVATE NOBLOCK NONNULL((1)) Tobpostlockop(mfile) *
NOTHROW(LOCKOP_CC misaligned_mfile_remove_from_base_msalign_lop)(Toblockop(mfile) *__restrict self,
                                                                 REF struct mfile *__restrict base) {
	struct misaligned_mfile *me;
	me = container_of(self, struct misaligned_mfile, _mam_lop);

	/* Remove from the list. */
	if (LIST_ISBOUND(me, mam_link))
		LIST_REMOVE(me, mam_link);

	/* Do the rest of the destruction of `me' in a post-lockop */
	me->_mam_plop.oplo_func = &misaligned_mfile_remove_from_base_msalign_plop;
	(void)base; /* Inherit reference */
	return &me->_mam_plop;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL misaligned_mfile_v_destroy)(struct mfile *__restrict self) {
	REF struct mfile *base;
	struct misaligned_mfile *me;
	me   = mfile_asmisaligned(self);
	base = me->mam_base;

	/* Remove from the list of misaligned sub-files of the base file. */
	if (LIST_ISBOUND(me, mam_link)) {
		if (mfile_lock_trywrite(base)) {
			COMPILER_BARRIER();
			if (LIST_ISBOUND(me, mam_link))
				LIST_REMOVE(me, mam_link);
			mfile_lock_endwrite(base);
		} else {
			/* Must remove the file through use of a lock-op on the base-file. */
			me->_mam_lop.olo_func = &misaligned_mfile_remove_from_base_msalign_lop;
			oblockop_enqueue(&base->mf_lockops, &me->_mam_lop);
			_mfile_lockops_reap(base); /* Inherit reference (to `base') */
			return;
		}
	}
	decref_unlikely(base);
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
		mfile_lock_read(base);
		mfile_trunclock_inc(base);
		mfile_lock_endread(base);
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
		return 0;
	return mfile_upread(me->mam_base, dst, num_bytes, addr, mode);
}

PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) size_t KCALL
misaligned_mfile_v_preadv(struct mfile *__restrict self, struct iov_buffer *__restrict dst,
                          size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...) {
	struct misaligned_mfile *me;
	me = mfile_asmisaligned(self);
	if (OVERFLOW_UADD(addr, me->mam_offs, &addr))
		return 0;
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

PRIVATE BLOCKING NONNULL_T((1)) void KCALL
misaligned_mfile_v_stat(struct mfile *__restrict self,
                        NCX struct stat *result)
		THROWS(...) {
	struct misaligned_mfile *me;
	me = mfile_asmisaligned(self);
	mfile_ustat(me->mam_base, result);

	/* Adjust the stat size value to account for misaligned leading bytes. */
	if (OVERFLOW_USUB(result->st_size, me->mam_offs, &result->st_size))
		result->st_size = 0;
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
	                     ":+%" PRIuSIZ "]",
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
	.mso_stat      = &misaligned_mfile_v_stat,
	.mso_tryas     = &misaligned_mfile_v_tryas,
	.mso_printlink = &misaligned_mfile_v_printlink,
	.mso_cc        = &misaligned_mfile_v_cc,
};

PUBLIC_CONST struct mfile_ops const misaligned_mfile_ops = {
	.mo_destroy    = &misaligned_mfile_v_destroy,
	.mo_loadblocks = &misaligned_mfile_v_loadblocks,
	.mo_stream     = &misaligned_mfile_v_stream_ops,
};



/* Create a wrapper file whose I/O cache is lazily populated from inner,
 * at offsets based on `*p_inner_fpos'. Note that the returned file will
 * probably not be writable, and that any modifications made to portions
 * of  `inner' that have  already been loaded by  `return' will _NOT_ be
 * visible (meaning that  the returned file  only works for  MAP_PRIVATE
 * mappings).
 *
 * This function is primarily used as a hacky wrapper for loading PE files
 * into memory (as those  sometimes have sub-page alignment  constraints).
 *
 * NOTES:
 * - The caller must ensure that `mfile_hasrawio(inner)'!
 * - This function will adjust `p_inner_fpos' such that (upon return) there
 *   is an invariant  `mfile_partaddr_aligned(return, OUT(*p_inner_fpos))'.
 * - This function doesn't necessarily return a misaligned file (hence  why
 *   its return type is just  `mfile'). When the effective alignment  turns
 *   out to be `0', it will just re-return `inner', and if another matching
 *   misaligned file already exists, that one is simply re-used. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1, 2)) REF struct mfile *FCALL
mfile_create_misaligned_wrapper(struct mfile *__restrict inner,
                                pos_t *__restrict p_inner_fpos)
		THROWS(E_BADALLOC) {
	size_t misalign;
	struct misaligned_mfile *used_predecessor;
	REF struct misaligned_mfile *predecessor;
	REF struct misaligned_mfile *result;
	shift_t blockshift;
	assertf(mfile_hasrawio(inner), "The underlying file must support RAW I/O");

	/* Cascade offsets to merge miss-alignments for readthru */
	if unlikely(mfile_ismisaligned(inner)) {
		struct misaligned_mfile *inner_miss = mfile_asmisaligned(inner);
		if (OVERFLOW_UADD(*p_inner_fpos, inner_miss->mam_offs, p_inner_fpos)) {
			/* Always out-of-bounds -> map to /dev/null
			 * XXX: This is technically incorrect, since /dev/null ignored writes,
			 *      but we'd need a file that doesn't implement write operators... */
			*p_inner_fpos = 0;
			return incref(&dev_null);
		}
		inner = inner_miss->mam_base;
		assert(!mfile_ismisaligned(inner));
	}

	/* Figure out the misalignment factor `misalign'.
	 * This acts as  the ID of  the misaligned  file. */
	misalign = (size_t)(*p_inner_fpos & inner->mf_part_amask);
	*p_inner_fpos -= misalign;

	if unlikely(inner->mf_ops->mo_loadblocks == NULL)
		goto return_inner; /* File offsets don't matter in this case! */
	if unlikely(misalign == 0)
		goto return_inner; /* No misalignment --> no need to create a wrapper! */

	/* mfile-s need to maintain a list of linked misaligned files, and the
	 * misaligned files themselves must NOT be anonymous from the  get-go.
	 *
	 * This is required so that `ftruncate(2)' can force-load  MAP_PRIVATE
	 * mappings of misaligned wrappers into memory before they are deleted
	 * from disk.
	 *
	 * Essentially,  misaligned wrappers need  the extra requirement that
	 * their misalignment must be `<= mam_base->mf_part_amask', and there
	 * needs to  be a  linked-list (sorted  by `mam_offs',  deleted  when
	 * `MFILE_F_DELETED' gets set,  and locked  by mfile_lock_read)  that
	 * keeps track of all currently allocated misaligned wrappers of some
	 * given mfile. */

	/* Check for an existing misaligned file with our desired offset. */
	mfile_lock_read(inner);
	predecessor = LIST_FIRST(&inner->mf_msalign);
	if (predecessor) {
		if (predecessor->mam_offs > misalign) {
			predecessor = NULL;
		} else {
			struct misaligned_mfile *next;
			while ((next = LIST_NEXT(predecessor, mam_link)) != NULL) {
				if (next->mam_offs > misalign)
					break;
				predecessor = next;
			}
			assert(predecessor->mam_offs <= misalign);
			if unlikely(!tryincref(predecessor)) {
				/* Predecessor just died, but has yet to remove itself */
				predecessor = NULL;
			} else if (predecessor->mam_offs == misalign) {
				/* File already exists! */
				mfile_lock_endread(inner);
				return predecessor;
			}
		}
	}
	mfile_lock_endread(inner);

	/* Allocate a new `struct misaligned_mfile' */
	TRY {
		result = (REF struct misaligned_mfile *)kmalloc(sizeof(struct misaligned_mfile), GFP_NORMAL);
	} EXCEPT {
		xdecref_unlikely(predecessor);
		RETHROW();
	}
	blockshift = inner->mf_blockshift;
	if (blockshift < PAGESHIFT) {
		/* Because  it's the most efficient shift, and  because we're free to pick whatever
		 * shift we want to pick for misaligned wrapper files, we can simply pick PAGESHIFT
		 * as our block-shift. */
		blockshift = PAGESHIFT;
	}
	_mfile_init(result, &misaligned_mfile_ops, blockshift, inner->mf_iobashift);
	result->mf_parts             = NULL;                  /* Still want to keep track of parts */
	result->mf_changed.slh_first = MFILE_PARTS_ANONYMOUS; /* No changes possible */
	atomic64_init(&result->mf_filesize, (uint64_t)-1);    /* We track file size and such manually. */

	/* Set-up flags and remaining fields. */
	result->mf_flags = MFILE_F_READONLY | MFILE_F_NOATIME |
	                   MFILE_F_NOMTIME | MFILE_F_FIXEDFILESIZE |
	                   MFILE_F_ROFLAGS;
	result->mam_base = incref(inner);
	result->mam_offs = misalign;

	/* Re-acquire a lock to the base file (and make it a write-lock this time) */
	TRY {
		mfile_lock_write(inner);
	} EXCEPT {
		destroy(result);
		xdecref_unlikely(predecessor);
		RETHROW();
	}

	/* Try  to inherit file timestamps (and check
	 * that the `inner' file hasn't been deleted) */
	mfile_tslock_acquire(inner);
	if unlikely(inner->mf_flags & MFILE_F_DELETED) {
		/* Deleted file --> don't create a misalignment wrapper! */
		mfile_tslock_release_br(inner);
		mfile_lock_endwrite(inner);
		destroy(result);
		xdecref_unlikely(predecessor);
		goto return_inner;
	}
	result->mf_atime = inner->mf_atime;
	result->mf_mtime = inner->mf_mtime;
	result->mf_ctime = inner->mf_ctime;
	result->mf_btime = inner->mf_btime;
	mfile_tslock_release(inner);

	/* Insert the new misaligned file into the base file's list. */
	if (predecessor) {
		/* Insert after `predecessor' */
		struct misaligned_mfile *next;
		used_predecessor = predecessor;
		while ((next = LIST_NEXT(used_predecessor, mam_link)) != NULL) {
			if (next->mam_offs > misalign)
				break;
			used_predecessor = next;
		}
	} else {
		struct misaligned_mfile *next;
		/* Must re-discover where to insert the new file. */
		used_predecessor = LIST_FIRST(&inner->mf_msalign);
		if (likely(used_predecessor == NULL) ||
		    used_predecessor->mam_offs > misalign) {
			/* Special case: insert at the front. */
			LIST_INSERT_HEAD(&inner->mf_msalign, result, mam_link);
			goto did_insert;
		}
		while ((next = LIST_NEXT(used_predecessor, mam_link)) != NULL) {
			if (next->mam_offs > misalign)
				break;
			used_predecessor = next;
		}
	}

	/* Highly unlikely case: some other thread created
	 * the file which  we just created,  too. In  this
	 * case, re-use the already-created file. */
	if unlikely(used_predecessor->mam_offs == misalign &&
	            tryincref(used_predecessor)) {
		mfile_lock_endwrite(inner);
		destroy(result);
		xdecref_unlikely(predecessor);
		return used_predecessor;
	}

	/* Insert after `used_predecessor' */
	LIST_INSERT_AFTER(used_predecessor, result, mam_link);
did_insert:
	mfile_lock_endwrite(inner);
	xdecref_unlikely(predecessor);

	return result;
return_inner:
	return incref(inner);
}

DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_MISALIGNED_C */
