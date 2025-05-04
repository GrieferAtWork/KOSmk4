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
#include <kernel/mman/mpart-blkst.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/phys.h>
#include <kernel/paging.h>
#include <misc/unlockinfo.h>
#include <sched/atomic64.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>
#include <hybrid/sequence/list.h>

#include <kos/except.h>
#include <kos/kernel/memory.h>
#include <kos/lockop.h>
#include <kos/types.h>
#include <sys/stat.h>

#include <assert.h>
#include <atomic.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
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
do_bzero:
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
		if unlikely(!mfile_trunclock_inc(base))
			goto do_bzero;
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
		size_t ok;
		ok = mfile_read_p(base, buf, num_bytes, addr);
		if (ok < num_bytes) {
			/* Must zero-initialize trailing data. */
			bzerophyscc(buf + ok, num_bytes - ok);
		}
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
	result->mam_offs = misalign;

	/* Re-acquire a lock to the base file (and make it a write-lock this time) */
	TRY {
again_lock_write_inner:
		mfile_lock_write(inner);

		/* We can't wait for `mf_trunclock' to become 0 because that would pose
		 * a potential soft-lock scenario when the calling thread is  currently
		 * holding a trunc-lock (because in that case, we'd be waiting forever)
		 *
		 * The reason why we might *want* to wait for `mf_trunclock == 0' is to
		 * ensure that no other thread is  currently in the process of  writing
		 * to  the file, in order to ensure that we don't end up mapping memory
		 * where it is undefined if that memory contains the old file contents,
		 * or the new file contents.
		 *
		 * But if you think about this, this check if completely pointless:
		 * - When 2 threads run in parallel, and one of them does a write(),
		 *   while the other does a mmap(MAP_PRIVATE), there *already* is no
		 *   guaranty as to what exactly the memory mapping will contain.
		 * - If we *were*  to wait for  `mf_trunclock == 0', the only  thing
		 *   we'd be ensuring is that there's no way for only *part* of  the
		 *   mapping to be the  old memory, and some  other part to be  new,
		 *   but there also isn't anything in the specs that says that write
		 *   operations  of arbitrary size have to be atomic (and then there
		 *   is also the mpart->block-level locks which will ensure that so-
		 *   long as you stay within  the same block (usually page),  memory
		 *   will consistently be either the old, or new contents)
		 * - As such, there is no  point in this check,  and as a matter  of
		 *   fact, this check also isn't done by `MAP_PRIVATE' or `read(2)',
		 *   so it's a mood point if we suddenly did it here.
		 *
		 * NOTE: This would all be about syncing with `mfile_msalign_makeanon_or_unlock()',
		 *       which usually gets called by  `mfile_write()' while holding a  trunc-lock,
		 *       and the idea *would* have been  to prevent new misaligned mem-files  being
		 *       created after that function just checked all existing ones.
		 *
		 * TLDR: This is unnecessary since  it's absence doesn't break  anything,
		 *       and read()/write() (CONSUMER/PRODUCER)  already need some  extra
		 *       locking mechanism if the intend is to sync them with each other.
		 */
#if 0
		/* Wait for `mf_trunclock' to become 0.
		 *
		 * This is required since new misaligned files must not be added while
		 * a write operation is in  progress (where write operations will  inc
		 * the `mf_trunclock' field to also suppress `ftruncate(2)')
		 *
		 * The reason for this is to ensure that we don't add+initialize new
		 * misaligned files during the small frame where `write(2)' is doing
		 * file I/O, has incremented `mf_trunclock', but has yet to  acquire
		 * a lock to an associated mpart. */
		if unlikely(atomic_read(&inner->mf_trunclock) != 0) {
			mfile_lock_endwrite(inner);
			mfile_trunclock_waitfor(inner);
			goto again_lock_write_inner;
		}
#endif

		/* Ensure that the `MFILE_F_DELETING'-flag isn't set on `inner'
		 *
		 * This is needed to sync  with `unlink(2)', which assumes  that
		 * the set of existing misaligned files doesn't change while the
		 * deleting-flag is set. */
		if unlikely(atomic_read(&inner->mf_flags) & MFILE_F_DELETING) {
			mfile_lock_endwrite(inner);
			if unlikely(!mfile_deleting_waitfor(inner))
				goto free_result_and_xdecref_predecessor_and_return_inner; /* File get *fully* deleted. */
			goto again_lock_write_inner;
		}
	} EXCEPT {
		kfree(result);
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
		goto free_result_and_xdecref_predecessor_and_return_inner;
	}
	result->mf_atime = inner->mf_atime;
	result->mf_mtime = inner->mf_mtime;
	result->mf_ctime = inner->mf_ctime;
	result->mf_btime = inner->mf_btime;
	mfile_tslock_release(inner);

	/* Deal  with special  case: when  the inner  file's parts are
	 * anonymous, then so must be those of the misaligned wrapper. */
	COMPILER_READ_BARRIER();
	if (inner->mf_parts == MFILE_PARTS_ANONYMOUS)
		result->mf_parts = MFILE_PARTS_ANONYMOUS;

	/* Insert the new misaligned file into the base file's list. */
	if (predecessor) {
		/* Insert after `predecessor' */
		used_predecessor = predecessor;
	} else {
		/* Must re-discover where to insert the new file. */
		used_predecessor = LIST_FIRST(&inner->mf_msalign);
		if (likely(used_predecessor == NULL) ||
		    used_predecessor->mam_offs > misalign) {
			/* Special case: insert at the front. */
			LIST_INSERT_HEAD(&inner->mf_msalign, result, mam_link);
			goto did_insert;
		}
	}

	/* Scan ahead to find the appropriate predecessor */
	{
		struct misaligned_mfile *next;
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
		kfree(result);
		xdecref_unlikely(predecessor);
		return used_predecessor;
	}

	/* Insert after `used_predecessor' */
	LIST_INSERT_AFTER(used_predecessor, result, mam_link);
did_insert:
	result->mam_base = incref(inner);
	mfile_lock_endwrite(inner);
	xdecref_unlikely(predecessor);

	return result;
free_result_and_xdecref_predecessor_and_return_inner:
	kfree(result);
	xdecref_unlikely(predecessor);
return_inner:
	return incref(inner);
}









/************************************************************************/
/* Misaligned file anonymization helpers                                */
/************************************************************************/

struct mpart_load_and_makeanon_unlockinfo: unlockinfo {
	struct misaligned_mfile *mlamaui_msalign; /* [1..1] The mis-aligned file, parts of which are being anonymized. */
	struct unlockinfo       *mlamaui_unlock;  /* [0..1] Extra user-defined unlock info. */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL mpart_load_and_makeanon_unlockinfo_cb)(struct unlockinfo *__restrict self) {
	struct mpart_load_and_makeanon_unlockinfo *me = (struct mpart_load_and_makeanon_unlockinfo *)self;
	mfile_lock_endwrite(me->mlamaui_msalign);
	unlockinfo_xunlock(me->mlamaui_unlock);
	mfile_lock_end(me->mlamaui_msalign->mam_base); /* !!! Important: must release the file lock *after* caller-given `unlock' (s.a. `mfile_unlock_parts_info_cb()') */
}


/* NOTE: This function *always* inherits both a lock and a reference to `self' */
PRIVATE BLOCKING NONNULL((1, 2)) bool FCALL
mpart_load_and_makeanon_and_decref_and_unlock(struct misaligned_mfile *__restrict msalign,
                                              REF struct mpart *__restrict self,
                                              struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_IOERROR, E_BADALLOC, ...) {
	struct mpart_load_and_makeanon_unlockinfo unlock_all;
	struct unlockinfo *used_unlock;
#define LOCAL_unlock_all()         \
	(mpart_lock_release(self),     \
	 mfile_lock_endwrite(msalign), \
	 unlockinfo_xunlock(unlock),   \
	 mfile_lock_end(msalign->mam_base)) /* !!! Important: must release the file lock *after* caller-given `unlock' (s.a. `mfile_unlock_parts_info_cb()') */
	assert(self->mp_file == msalign);

	unlock_all.ui_unlock       = &mpart_load_and_makeanon_unlockinfo_cb;
	unlock_all.mlamaui_msalign = msalign;
	unlock_all.mlamaui_unlock  = unlock;
	used_unlock = &unlock_all;
	TRY {
		/* Ensure that `self' has been allocated. */
again_check_incore:
		if (!MPART_ST_INCORE(self->mp_state)) {
			struct mpart_setcore_data sc_data;
			mpart_setcore_data_init(&sc_data);
			TRY {
				while (!mpart_setcore_or_unlock(self, used_unlock, &sc_data)) {
					used_unlock = NULL;
					mpart_lock_acquire(self);
				}
			} EXCEPT {
				mpart_setcore_data_fini(&sc_data);
				RETHROW();
			}
		}

		/* Ensure that `self' has been loaded into the core.
		 * NOTE: This also waits for all INIT-blocks to go away! */
		if (!mpart_load_or_unlock(self, &unlock_all, 0, mpart_getsize(self))) {
			used_unlock = NULL;
			mpart_lock_acquire(self);
			goto again_check_incore;
		}
	} EXCEPT {
		decref_unlikely(self);
		RETHROW();
	}

	/* With the part fully allocated+loaded, anonymize it! */
	assert(!mpart_isanon(self));
	mpart_tree_removenode(&msalign->mf_parts, self);
	DBG_memset(&self->mp_filent.rb_lhs, 0xcc, sizeof(self->mp_filent.rb_lhs));
	self->mp_filent.rb_rhs = NULL; /* Indicator for `mpart_trim()' */
	atomic_write(&self->mp_filent.rb_par, (struct mpart *)-1);
	assertf(!(self->mp_flags & MPART_F_CHANGED),
	        "Parts of misaligned files can't be changed (because the misaligned "
	        "file has its changed list marked as MFILE_PARTS_ANONYMOUS)");
	if (atomic_fetchand(&self->mp_flags, ~MPART_F_GLOBAL_REF) & MPART_F_GLOBAL_REF)
		decref_nokill(self);

	/* A blocks of `part' with status LOAD must be set to CHNG (needed for `system_cc()') */
	if (self->mp_flags & MPART_F_BLKST_INL) {
		self->mp_blkst_inl = MPART_BLOCK_REPEAT(MPART_BLOCK_ST_CHNG);
	} else if (self->mp_blkst_ptr) {
		kfree(self->mp_blkst_ptr);
		self->mp_blkst_ptr = NULL;
	}
	mpart_lock_release(self);

	/* Try to merge the part with adjacent parts.
	 *
	 * This optimizes memory mappings in this situation:
	 * >> char buf[64 * 1024];
	 * >> pread(fd, buf, sizeof(buf), 0);
	 * >> pwrite(fd, DATA1, 4096, 4096 * 0);
	 * >> pwrite(fd, DATA2, 4096, 4096 * 1);
	 * >> pwrite(fd, DATA3, 4096, 4096 * 2);
	 * >> pwrite(fd, DATA4, 4096, 4096 * 3);
	 * Every one of these writes needs to anonymize
	 */
	self = mpart_merge(self);
	mpart_trim(self); /* This will drop our final reference! */
	return used_unlock != NULL;
#undef LOCAL_unlock_all
}

PRIVATE BLOCKING NONNULL((1, 2)) bool FCALL
misaligned_mfile_part_makeanon_or_unlock(struct misaligned_mfile *__restrict msalign,
                                         struct mpart *__restrict self,
                                         struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_IOERROR, E_BADALLOC, ...) {
#define LOCAL_unlock_all()         \
	(mfile_lock_endwrite(msalign), \
	 unlockinfo_xunlock(unlock),   \
	 mfile_lock_end(msalign->mam_base)) /* !!! Important: must release the file lock *after* caller-given `unlock' (s.a. `mfile_unlock_parts_info_cb()') */

	if unlikely(!tryincref(self))
		return true; /* Can ignore this part! */

	/* Acquire a lock to the underlying part. */
	if (!mpart_lock_tryacquire(self)) {
		LOCAL_unlock_all();
		FINALLY_DECREF_UNLIKELY(self);
		mpart_lock_waitfor(self);
		return false;
	}

	/* NOTE: this call *always* inherits the lock and reference we created above! */
	return mpart_load_and_makeanon_and_decref_and_unlock(msalign, self, unlock);
#undef LOCAL_unlock_all
}

PRIVATE WUNUSED NONNULL((1)) bool FCALL
mpart_lock_and_maybe_split_or_decref_for_misaligned(struct misaligned_mfile *__restrict msalign,
                                                    /*inherit(return == false || EXCEPT)*/ REF struct mpart *__restrict part,
                                                    struct unlockinfo *unlock,
                                                    mpart_reladdr_t partrel_offset,
                                                    size_t num_bytes) {
#define LOCAL_unlock_all()         \
	(mfile_lock_endwrite(msalign), \
	 unlockinfo_xunlock(unlock),   \
	 mfile_lock_end(msalign->mam_base)) /* !!! Important: must release the file lock *after* caller-given `unlock' (s.a. `mfile_unlock_parts_info_cb()') */
	struct mpart_load_and_makeanon_unlockinfo unlock_all;
	if (!mpart_lock_tryacquire(part)) {
		LOCAL_unlock_all();
		FINALLY_DECREF_UNLIKELY(part);
		mpart_lock_waitfor(part);
		return false;
	}
	unlock_all.ui_unlock       = &mpart_load_and_makeanon_unlockinfo_cb;
	unlock_all.mlamaui_msalign = msalign;
	unlock_all.mlamaui_unlock  = unlock;
	TRY {
		if (!mpart_maybesplit_or_unlock(part, &unlock_all, partrel_offset, num_bytes)) {
			decref_unlikely(part);
			return false;
		}
	} EXCEPT {
		decref_unlikely(part);
		RETHROW();
	}
	return true;
#undef LOCAL_unlock_all
}

PRIVATE BLOCKING NONNULL((1)) bool FCALL
misaligned_mfile_range_makeanon_or_unlock(struct misaligned_mfile *__restrict msalign,
                                          pos_t msalign_minaddr,
                                          pos_t msalign_maxaddr,
                                          struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_IOERROR, E_BADALLOC, ...) {
#define LOCAL_unlock_all()         \
	(mfile_lock_endwrite(msalign), \
	 unlockinfo_xunlock(unlock),   \
	 mfile_lock_end(msalign->mam_base)) /* !!! Important: must release the file lock *after* caller-given `unlock' (s.a. `mfile_unlock_parts_info_cb()') */
	struct mpart *next;
	struct mpart_tree_minmax mima;
	mpart_tree_minmaxlocate(msalign->mf_parts, msalign_minaddr, msalign_maxaddr, &mima);
	assert((mima.mm_min != NULL) == (mima.mm_max != NULL));
	if (!mima.mm_min)
		return true;

	/* Split mem-parts so we don't have to load address ranges unnecessarily. */
	if ((msalign_minaddr > mpart_getminaddr(mima.mm_min)) ||
	    (msalign_maxaddr < mpart_getmaxaddr(mima.mm_max))) {
		if (mima.mm_min == mima.mm_max) {
			/* Special case: trim the same part twice */
			mpart_reladdr_t retain_minaddr;
			mpart_reladdr_t retain_maxaddr;
			if (!tryincref(mima.mm_min))
				return true;
			if (OVERFLOW_USUB(msalign_minaddr, mpart_getminaddr(mima.mm_min), &retain_minaddr))
				retain_minaddr = 0;
			assert(msalign_maxaddr >= mpart_getminaddr(mima.mm_min));
			retain_maxaddr = (mpart_reladdr_t)(msalign_maxaddr - mpart_getminaddr(mima.mm_min));
			assert(retain_minaddr <= retain_maxaddr);
			if (!mpart_lock_and_maybe_split_or_decref_for_misaligned(msalign, mima.mm_min,
			                                                         unlock, retain_minaddr,
			                                                         (retain_maxaddr - retain_minaddr) + 1))
				return false;
			return mpart_load_and_makeanon_and_decref_and_unlock(msalign, mima.mm_min, unlock);
		} else {
			if (msalign_minaddr > mpart_getminaddr(mima.mm_min)) {
				mpart_reladdr_t retain_minaddr;
				mpart_reladdr_t retain_endaddr;
				if (!tryincref(mima.mm_min))
					return true;
				retain_minaddr = (mpart_reladdr_t)(msalign_minaddr - mpart_getminaddr(mima.mm_min));
				retain_endaddr = mpart_getsize(mima.mm_min);
				assert(retain_minaddr < retain_endaddr);
				if (!mpart_lock_and_maybe_split_or_decref_for_misaligned(msalign, mima.mm_min,
				                                                         unlock, retain_minaddr,
				                                                         retain_endaddr - retain_minaddr))
					return false;
				if (!mpart_load_and_makeanon_and_decref_and_unlock(msalign, mima.mm_min, unlock))
					return false;
				mima.mm_min = mpart_tree_nextnode(mima.mm_min);
			}
			if (msalign_maxaddr < mpart_getminaddr(mima.mm_max)) {
				mpart_reladdr_t retain_endaddr;
				if (!tryincref(mima.mm_max))
					return true;
				retain_endaddr = (mpart_reladdr_t)(msalign_maxaddr - mpart_getminaddr(mima.mm_max)) + 1;
				assert(retain_endaddr > 0);
				if (!mpart_lock_and_maybe_split_or_decref_for_misaligned(msalign, mima.mm_max,
				                                                         unlock, 0, retain_endaddr))
					return false;
				if (!mpart_load_and_makeanon_and_decref_and_unlock(msalign, mima.mm_max, unlock))
					return false;
				if (mima.mm_min == mima.mm_max)
					return true; /* Special case when there were 2 parts originally. */
				mima.mm_max = mpart_tree_prevnode(mima.mm_max);
			}
		}
	}

	while (mima.mm_min != mima.mm_max) {
		next = mpart_tree_nextnode(mima.mm_min);
		if (!misaligned_mfile_part_makeanon_or_unlock(msalign, mima.mm_min, unlock))
			return false;
		mima.mm_min = next;
	}
	return misaligned_mfile_part_makeanon_or_unlock(msalign, mima.mm_min, unlock);
#undef LOCAL_unlock_all
}


/* Same as `_mfile_msalign_makeanon_all_locked()', except that the
 * caller only needs to be holding a lock to `file', and that this
 * function will manage all of the other locks
 * @return: true:  Success (locks are still held)
 * @return: false: Try again (locks were lost)
 * @THROW: Error (locks were lost) */
FUNDEF BLOCKING WUNUSED NONNULL((1)) bool KCALL
_mfile_msalign_makeanon_locked_or_unlock(struct mfile *__restrict file,
                                         pos_t minaddr, pos_t maxaddr,
                                         struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_IOERROR, E_BADALLOC, ...)
		ASMNAME("mfile_msalign_makeanon_locked_or_unlock");
PUBLIC BLOCKING WUNUSED NONNULL((1)) bool KCALL
_mfile_msalign_makeanon_locked_or_unlock(struct mfile *__restrict file,
                                         pos_t minaddr, pos_t maxaddr,
                                         struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_IOERROR, E_BADALLOC, ...) {
#define LOCAL_unlock_all()       \
	(unlockinfo_xunlock(unlock), \
	 mfile_lock_end(file)) /* !!! Important: must release the file lock *after* caller-given `unlock' (s.a. `mfile_unlock_parts_info_cb()') */
	struct misaligned_mfile *msalign;
	LIST_FOREACH (msalign, &file->mf_msalign, mam_link) {
		bool ok;
		pos_t msalign_minaddr;
		pos_t msalign_maxaddr;
		struct mpart *msalign_parts_root;
		msalign_parts_root = atomic_read(&msalign->mf_parts);
		if unlikely(msalign_parts_root == NULL ||
		            msalign_parts_root == MFILE_PARTS_ANONYMOUS)
			continue; /* No parts here :) */
		if unlikely(!tryincref(msalign))
			continue; /* Dead part (ignore) */
		FINALLY_DECREF_UNLIKELY(msalign);
		if (!mfile_lock_trywrite(msalign)) {
			/* Blocking-wait for the lock to become available. */
			LOCAL_unlock_all();
			mfile_lock_waitwrite(msalign);
			return false;
		}

		/* Calculate the file-relative, aligned min/max bounds that need to be anonymized. */
		if (OVERFLOW_USUB(minaddr, msalign->mam_offs, &msalign_minaddr))
			msalign_minaddr = 0;
		if unlikely(OVERFLOW_USUB(maxaddr, msalign->mam_offs, &msalign_maxaddr))
			continue;

		msalign_minaddr = mfile_partaddr_flooralign(msalign, msalign_minaddr);
		msalign_maxaddr = mfile_partaddr_ceilalign(msalign, msalign_maxaddr + 1) - 1;
		assert(msalign_minaddr <= msalign_maxaddr);
		assert(msalign->mam_base == file);
		ok = misaligned_mfile_range_makeanon_or_unlock(msalign,
		                                               msalign_minaddr,
		                                               msalign_maxaddr,
		                                               unlock);
		if (!ok)
			return false;
	}
	return true;
#undef LOCAL_unlock_all
}


/* Same as `_mfile_msalign_makeanon_locked_or_unlock()', except that
 * the caller doesn't need to worry about holding a lock to  `self'.
 * @return: true:  Success (locks are still held)
 * @return: false: Try again (locks were lost)
 * @THROW: Error (locks were lost) */
FUNDEF BLOCKING WUNUSED NONNULL((1)) bool KCALL
_mfile_msalign_makeanon_or_unlock(struct mfile *__restrict self,
                                  pos_t minaddr, pos_t maxaddr,
                                  struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_IOERROR, E_BADALLOC, ...)
		ASMNAME("mfile_msalign_makeanon_or_unlock");
PUBLIC BLOCKING WUNUSED NONNULL((1)) bool KCALL
_mfile_msalign_makeanon_or_unlock(struct mfile *__restrict self,
                                  pos_t minaddr, pos_t maxaddr,
                                  struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_IOERROR, E_BADALLOC, ...) {
	/* Without this special makeanon handling, the following would break:
	 * >> static char buf[64 * 1024];
	 * >> int offset = 4 * getpagesize();
	 * >> pwrite(fd, "BAR", 3, offset);
	 * >> pread(fd, buf, sizeof(buf), 0);  // This will trigger the mmapread system
	 * >> pwrite(fd, "FOO", 3, offset);
	 * >> // Because memory wasn't unshared during the write, the buffer now also contains "FOO"
	 * >> assert(bcmp(buf + offset, "BAR") == 0);
	 *
	 * In  order to fix this, we essentially treat the mpart-s of misaligned files the
	 * same way we  treat copy-on-write  nodes (as per  `mpart::mp_copy'). This  means
	 * that everywhere we do copy-on-write unsharing, we also have to search for  mem-
	 * parts  that depend on  the to-be-unshared file-range, and  then proceed to make
	 * those  parts anonymous (thus  removing them from the  list of misaligned files,
	 * meaning  that the next time part of  the base file should be misaligned-mapped,
	 * new mpart-s are created which will then lazily initialize to new memory-content
	 * of the underlying file) */
	bool result;

	/* Ensure that we've got a read-lock to `self' */
	if (!mfile_lock_tryread(self)) {
		unlockinfo_xunlock(unlock);
		mfile_lock_waitread(self);
		return false;
	}

	/* Use `_mfile_msalign_makeanon_locked_or_unlock()' now that we have a lock to the file. */
	result = _mfile_msalign_makeanon_locked_or_unlock(self, minaddr, maxaddr, unlock);

	/* Upon success, have to release the read-lock to `self'
	 * In the error-case,  this lock  was already  released. */
	if (result)
		mfile_lock_endread(self);
	return result;
}



DECL_END

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_MFILE_MISALIGNED_C */
