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
#ifdef __INTELLISENSE__
#include "mfile-rw.c"
//#define        DEFINE_mfile_read
//#define      DEFINE_mfile_read_p
//#define       DEFINE_mfile_readv
//#define     DEFINE_mfile_readv_p
//#define    DEFINE_mfile_tailread
//#define  DEFINE_mfile_tailread_p
//#define   DEFINE_mfile_tailreadv
//#define DEFINE_mfile_tailreadv_p
#define       DEFINE_mfile_write
//#define      DEFINE_mfile_write_p
//#define       DEFINE_mfile_writev
//#define     DEFINE_mfile_writev_p
//#define    DEFINE_mfile_tailwrite
//#define  DEFINE_mfile_tailwrite_p
//#define   DEFINE_mfile_tailwritev
//#define DEFINE_mfile_tailwritev_p
#endif /* __INTELLISENSE__ */

#include <kernel/fs/node.h>
#include <kernel/fs/super.h>
#include <kernel/iovec.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/phys.h>
#include <misc/unlockinfo.h>
#include <sched/signal.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <kos/except.h>

#include <assert.h>
#include <stddef.h>
#include <string.h>

#include <libvio/access.h>

DECL_BEGIN

#ifndef DBG_memset
#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */
#endif /* !DBG_memset */

#if defined(DEFINE_mfile_read) || defined(DEFINE_mfile_tailread)
#ifdef DEFINE_mfile_tailread
#define LOCAL_TAILIO
#endif /* DEFINE_mfile_tailread */
#define LOCAL_READING
#define LOCAL_buffer_t           USER CHECKED void *
#define LOCAL_ubuffer_t          uintptr_t
#define LOCAL_mfile_viorw        mfile_vioread
#define LOCAL_mfile_normrw       mfile_read
#define LOCAL_mfile_tailrw       mfile_tailread
#define LOCAL_mpart_rw           mpart_read
#define LOCAL_mpart_rw_or_unlock mpart_read_or_unlock
#elif defined(DEFINE_mfile_write) || defined(DEFINE_mfile_tailwrite)
#ifdef DEFINE_mfile_tailwrite
#define LOCAL_TAILIO
#endif /* DEFINE_mfile_tailwrite */
#define LOCAL_WRITING
#define LOCAL_buffer_t           USER CHECKED void const *
#define LOCAL_ubuffer_t          uintptr_t
#define LOCAL_mfile_viorw        mfile_viowrite
#define LOCAL_mfile_normrw       mfile_write
#define LOCAL_mfile_tailrw       mfile_tailwrite
#define LOCAL_mpart_rw           mpart_write
#define LOCAL_mpart_rw_or_unlock mpart_write_or_unlock
#elif defined(DEFINE_mfile_readv) || defined(DEFINE_mfile_tailreadv)
#ifdef DEFINE_mfile_tailreadv
#define LOCAL_TAILIO
#endif /* DEFINE_mfile_tailreadv */
#define LOCAL_READING
#define LOCAL_BUFFER_IS_IOVEC
#define LOCAL_buffer_t           struct iov_buffer const *__restrict
#define LOCAL_buffer_ent_t       struct iov_entry
#define LOCAL_mfile_viorw        mfile_vioreadv
#define LOCAL_mfile_normrw       mfile_readv
#define LOCAL_mfile_tailrw       mfile_tailreadv
#define LOCAL_mpart_rw           mpart_readv
#define LOCAL_mpart_rw_or_unlock mpart_readv_or_unlock
#elif defined(DEFINE_mfile_writev) || defined(DEFINE_mfile_tailwritev)
#ifdef DEFINE_mfile_tailwritev
#define LOCAL_TAILIO
#endif /* DEFINE_mfile_tailwritev */
#define LOCAL_WRITING
#define LOCAL_BUFFER_IS_IOVEC
#define LOCAL_buffer_t           struct iov_buffer const *__restrict
#define LOCAL_buffer_ent_t       struct iov_entry
#define LOCAL_mfile_viorw        mfile_viowritev
#define LOCAL_mfile_normrw       mfile_writev
#define LOCAL_mfile_tailrw       mfile_tailwritev
#define LOCAL_mpart_rw           mpart_writev
#define LOCAL_mpart_rw_or_unlock mpart_writev_or_unlock
#elif defined(DEFINE_mfile_read_p) || defined(DEFINE_mfile_tailread_p)
#ifdef DEFINE_mfile_tailread_p
#define LOCAL_TAILIO
#endif /* DEFINE_mfile_tailread_p */
#define LOCAL_READING
#define LOCAL_BUFFER_IS_PHYS
#define LOCAL_buffer_t           physaddr_t
#define LOCAL_ubuffer_t          physaddr_t
#define LOCAL_mfile_viorw        mfile_vioread_p
#define LOCAL_mfile_normrw       mfile_read_p
#define LOCAL_mfile_tailrw       mfile_tailread_p
#define LOCAL_mpart_rw           mpart_read_p
#define LOCAL_mpart_rw_or_unlock mpart_read_or_unlock_p
#elif defined(DEFINE_mfile_write_p) || defined(DEFINE_mfile_tailwrite_p)
#ifdef DEFINE_mfile_tailwrite_p
#define LOCAL_TAILIO
#endif /* DEFINE_mfile_tailwrite_p */
#define LOCAL_WRITING
#define LOCAL_BUFFER_IS_PHYS
#define LOCAL_buffer_t           physaddr_t
#define LOCAL_ubuffer_t          physaddr_t
#define LOCAL_mfile_viorw        mfile_viowrite_p
#define LOCAL_mfile_normrw       mfile_write_p
#define LOCAL_mfile_tailrw       mfile_tailwrite_p
#define LOCAL_mpart_rw           mpart_write_p
#define LOCAL_mpart_rw_or_unlock mpart_write_or_unlock_p
#elif defined(DEFINE_mfile_readv_p) || defined(DEFINE_mfile_tailreadv_p)
#ifdef DEFINE_mfile_tailreadv_p
#define LOCAL_TAILIO
#endif /* DEFINE_mfile_tailreadv_p */
#define LOCAL_READING
#define LOCAL_BUFFER_IS_PHYS
#define LOCAL_BUFFER_IS_IOVEC
#define LOCAL_buffer_t           struct iov_physbuffer const *__restrict
#define LOCAL_buffer_ent_t       struct iov_physentry
#define LOCAL_mfile_viorw        mfile_vioreadv_p
#define LOCAL_mfile_normrw       mfile_readv_p
#define LOCAL_mfile_tailrw       mfile_tailreadv_p
#define LOCAL_mpart_rw           mpart_readv_p
#define LOCAL_mpart_rw_or_unlock mpart_readv_or_unlock_p
#elif defined(DEFINE_mfile_writev_p) || defined(DEFINE_mfile_tailwritev_p)
#ifdef DEFINE_mfile_tailwritev_p
#define LOCAL_TAILIO
#endif /* DEFINE_mfile_tailwritev_p */
#define LOCAL_WRITING
#define LOCAL_BUFFER_IS_PHYS
#define LOCAL_BUFFER_IS_IOVEC
#define LOCAL_buffer_t           struct iov_physbuffer const *__restrict
#define LOCAL_buffer_ent_t       struct iov_physentry
#define LOCAL_mfile_viorw        mfile_viowritev_p
#define LOCAL_mfile_normrw       mfile_writev_p
#define LOCAL_mfile_tailrw       mfile_tailwritev_p
#define LOCAL_mpart_rw           mpart_writev_p
#define LOCAL_mpart_rw_or_unlock mpart_writev_or_unlock_p
#else /* ... */
#error "Bad configuration"
#endif /* !... */

#ifdef LOCAL_TAILIO
#define LOCAL_mfile_rw LOCAL_mfile_tailrw
#else /* LOCAL_TAILIO */
#define LOCAL_mfile_rw LOCAL_mfile_normrw
#endif /* !LOCAL_TAILIO */

#ifdef LOCAL_BUFFER_IS_IOVEC
#define LOCAL_buffer_advance(count) (buf_offset += (count))
#else /* LOCAL_BUFFER_IS_IOVEC */
#define LOCAL_buffer_advance(count) (buffer = (LOCAL_buffer_t)((LOCAL_ubuffer_t)buffer + (count)))
#endif /* !LOCAL_BUFFER_IS_IOVEC */





#ifdef LOCAL_READING
PUBLIC BLOCKING WUNUSED NONNULL((1)) size_t KCALL
#else /* LOCAL_READING */
PUBLIC BLOCKING NONNULL((1)) size_t KCALL
#endif /* !LOCAL_READING */
LOCAL_mfile_rw(struct mfile *__restrict self,
               LOCAL_buffer_t buffer,
#ifdef LOCAL_BUFFER_IS_IOVEC
               size_t buf_offset,
#endif /* LOCAL_BUFFER_IS_IOVEC */
               size_t num_bytes
#if defined(LOCAL_READING) || !defined(LOCAL_TAILIO)
               ,
               pos_t offset
#endif /* LOCAL_READING || !LOCAL_TAILIO */
               )
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
#if defined(LOCAL_READING) && defined(LOCAL_TAILIO)
	size_t result;
again:
#ifdef LOCAL_BUFFER_IS_IOVEC
	result = LOCAL_mfile_normrw(self, buffer, buf_offset, num_bytes, offset);
#else /* LOCAL_BUFFER_IS_IOVEC */
	result = LOCAL_mfile_normrw(self, buffer, num_bytes, offset);
#endif /* !LOCAL_BUFFER_IS_IOVEC */
	if (result == 0 && !mfile_isanon(self)) {
		/* Wait for data to become available. */
		task_connect(&self->mf_initdone);
		{
			struct task_connections cons;
			task_pushconnections(&cons);
			RAII_FINALLY { task_popconnections(); };
#ifdef LOCAL_BUFFER_IS_IOVEC
			result = LOCAL_mfile_normrw(self, buffer, buf_offset, num_bytes, offset);
#else /* LOCAL_BUFFER_IS_IOVEC */
			result = LOCAL_mfile_normrw(self, buffer, num_bytes, offset);
#endif /* !LOCAL_BUFFER_IS_IOVEC */
		}
		if likely(result == 0 && !mfile_isanon(self)) {
			task_waitfor();
			goto again;
		}
		task_disconnectall();
	}
	return result;
#else /* defined(LOCAL_READING) && defined(LOCAL_TAILIO) */
	size_t result = 0;
	PAGEDIR_PAGEALIGNED pos_t newpart_minaddr;
	pos_t newpart_maxaddr; /* Aligned at .+1 */
	size_t io_bytes;
	pos_t filesize;
#ifdef LOCAL_TAILIO
#ifdef __INTELLISENSE__
	pos_t &offset = filesize;
#else /* __INTELLISENSE__ */
#define offset filesize
#endif /* !__INTELLISENSE__ */
#endif /* LOCAL_TAILIO */
	REF struct mpart *part;
again:
	if (!num_bytes)
		goto done;
	mfile_lock_read(self);
	if unlikely(mfile_isanon(self)) {
		mfile_lock_endread(self);
#ifdef LIBVIO_CONFIG_ENABLED
		if (self->mf_ops->mo_vio) {
			/* TODO: Handling for VIO */
		}
#endif /* LIBVIO_CONFIG_ENABLED */

#ifdef LOCAL_WRITING
		/* Cannot write to anonymous files. If you try to, you'll get a READONLY error. */
		if likely(result == 0)
			THROW(E_FSERROR_READONLY);
#endif /* LOCAL_WRITING */
		goto done;
	}

#ifdef LOCAL_WRITING
	if unlikely(self->mf_flags & (MFILE_F_READONLY | MFILE_F_DELETED)) {
		mfile_lock_endread(self);
		if unlikely(result)
			goto done;
		THROW(E_FSERROR_READONLY);
	}
#endif /* LOCAL_WRITING */

	/* Load the current file size. */
	filesize = mfile_getsize(self);

#ifndef LOCAL_TAILIO
	/* Check if the given `offset' is in-bounds of the allocated file size. */
#ifdef LOCAL_READING
	if likely(offset < filesize)
#else /* LOCAL_READING */
	if (offset < filesize)
#endif /* !LOCAL_READING */
	{
		/* (try to) do I/O on a pre-existing part. */
		if (OVERFLOW_USUB(filesize, offset, &io_bytes))
			io_bytes = (size_t)-1;
		if (io_bytes > num_bytes)
			io_bytes = num_bytes;
		part = mpart_tree_locate(self->mf_parts, offset);
		if (part != NULL && tryincref(part)) {
			/* Found a pre-existing part which we can do I/O on! */
			mfile_trunclock_inc(self);
			mfile_lock_endread(self);
do_io_with_part_and_trunclock:
			{
				RAII_FINALLY {
					decref_unlikely(part);
					mfile_trunclock_dec(self);
				};
#ifdef LOCAL_BUFFER_IS_IOVEC
				io_bytes = LOCAL_mpart_rw(part, buffer, buf_offset, io_bytes, offset);
#else /* LOCAL_BUFFER_IS_IOVEC */
				io_bytes = LOCAL_mpart_rw(part, buffer, io_bytes, offset);
#endif /* !LOCAL_BUFFER_IS_IOVEC */
			}
			LOCAL_buffer_advance(io_bytes);
			num_bytes -= io_bytes;
			offset += io_bytes;
			result += io_bytes;
			goto again;
		}
		/* Create a new-, or extend an existing part within the bounds of the file */
		newpart_minaddr = offset;
		newpart_maxaddr = offset + io_bytes - 1;
		assert(newpart_maxaddr < filesize);
		newpart_minaddr = mfile_addr_flooralign(self, newpart_minaddr);
		newpart_maxaddr = mfile_addr_ceilalign(self, newpart_maxaddr + 1) - 1;
		assert(newpart_minaddr <= newpart_maxaddr);
		assert(!mpart_tree_locate(self->mf_parts, newpart_minaddr));
		/* We know that no part exists at `newpart_minaddr', but an existing  part
		 * may still exist somewhere else within the requested address range. When
		 * this  is the case, we must limit ourselves  to only do I/O up until the
		 * start of that later part. */
		{
			struct mpart_tree_minmax mima;
			struct mfile_extendpart_data extdat;
			mpart_tree_minmaxlocate(self->mf_parts, newpart_minaddr, newpart_maxaddr, &mima);
			if (mima.mm_min != NULL) {
				newpart_maxaddr = mpart_getminaddr(mima.mm_min) - 1;
				assert(newpart_minaddr <= newpart_maxaddr);
			}
			mfile_extendpart_data_init(&extdat);
			extdat.mep_minaddr = newpart_minaddr;
			extdat.mep_maxaddr = newpart_maxaddr;
again_extend_part:
			TRY {
				part = mfile_extendpart_or_unlock(self, &extdat, NULL);
			} EXCEPT {
				mfile_extendpart_data_fini(&extdat);
				RETHROW();
			}
			if (part == MFILE_EXTENDPART_OR_UNLOCK_AGAIN) {
				TRY {
					mfile_lock_write(self);
				} EXCEPT {
					mfile_extendpart_data_fini(&extdat);
					RETHROW();
				}
				if unlikely(mfile_isanon(self)) {
					mfile_lock_endwrite(self);
					mfile_extendpart_data_fini(&extdat);
					goto again;
				}
#ifdef LOCAL_WRITING
				if unlikely(self->mf_flags & (MFILE_F_READONLY | MFILE_F_DELETED)) {
					mfile_lock_endwrite(self);
					mfile_extendpart_data_fini(&extdat);
					THROW(E_FSERROR_READONLY);
				}
#endif /* LOCAL_WRITING */
				/* Make sure that there's still nothing within the accessed range. */
				part = mpart_tree_rlocate(self->mf_parts,
				                          newpart_minaddr,
				                          newpart_maxaddr);
				if unlikely(part != NULL) {
					/* Found a pre-existing part. */
restart_after_extendpart:
					mfile_lock_endwrite(self);
					mfile_extendpart_data_fini(&extdat);
					goto again;
				}
				/* Also make sure that the file hasn't been truncated in the mean time. */
				if unlikely(mfile_getsize(self) < filesize)
					goto restart_after_extendpart;
				goto again_extend_part;
			}
			if (part != MFILE_EXTENDPART_OR_UNLOCK_NOSIB) {
				/* Successfully managed to extend an existing part!
				 * As  such,  use  this   part  to  do  more   I/O! */
				incref(part);
				mpart_lock_release(part);
				mfile_trunclock_inc(self); /* Prevent `ftruncate(2)' until we're done */
				mfile_lock_endwrite(self);
				goto do_io_with_part_and_trunclock;
			}
		}
		mfile_lock_end(self);

		/* Create an entirely new part. */
		part = _mfile_newpart(self, newpart_minaddr, (size_t)(newpart_maxaddr - newpart_minaddr) + 1);

		/* Initialize remaining fields. */
		part->mp_refcnt = 2; /* +1: return, +1: MPART_F_GLOBAL_REF */
		part->mp_xflags = MPART_XF_NORMAL;
		part->mp_file   = incref(self);
		LIST_INIT(&part->mp_copy);
		LIST_INIT(&part->mp_share);
		SLIST_INIT(&part->mp_lockops);
		/*LIST_ENTRY_UNBOUND_INIT(&part->mp_allparts);*/ /* Initialized later... */
		part->mp_minaddr = newpart_minaddr;
		part->mp_maxaddr = newpart_maxaddr;
		DBG_memset(&part->mp_changed, 0xcc, sizeof(part->mp_changed));
		_mpart_init_asanon(part);
		part->mp_flags |= MPART_F_GLOBAL_REF;
		TRY {
			mfile_lock_write(self);
		} EXCEPT {
			LIST_ENTRY_UNBOUND_INIT(&part->mp_allparts);
			part->mp_refcnt = 0;
			mpart_destroy(part);
			RETHROW();
		}

		/* Verify that nothing's changed in the mean time. */
		if unlikely(mfile_isanon(self)) {
destroy_new_part_and_try_again:
			mfile_lock_endwrite(self);
			LIST_ENTRY_UNBOUND_INIT(&part->mp_allparts);
			part->mp_refcnt = 0;
			mpart_destroy(part);
			goto again;
		}
#ifdef LOCAL_WRITING
		if unlikely(self->mf_flags & (MFILE_F_READONLY | MFILE_F_DELETED))
			goto destroy_new_part_and_try_again;
#endif /* LOCAL_WRITING */

		/* Do I/O with the newly created part. */
		mfile_trunclock_inc(self);
		if unlikely(mfile_getsize(self) < filesize) {
			mfile_trunclock_dec(self);
			goto destroy_new_part_and_try_again;
		}
		TRY {
			REF struct mpart *rpart;
			/* Try to merge the new part, and release a write-lock to `self'. */
			rpart = mfile_insert_and_merge_part_and_unlock(self, part);
			if unlikely(!rpart) {
				mfile_trunclock_dec(self);
				goto destroy_new_part_and_try_again;
			}
			part = rpart;
		} EXCEPT {
			mfile_trunclock_dec(self);
			RETHROW();
		}

		/* This one inherits a reference to `part' for us!
		 * It also does the  `mfile_trunclock_dec(self);'. */
		goto do_io_with_part_and_trunclock;
	}
#endif /* !LOCAL_TAILIO */

#ifdef LOCAL_READING
	mfile_lock_endread(self);
#else /* LOCAL_READING */
	/* Construct/extend new parts at the end. */

	/* Make sure that we're allowed to alter the size of the file. */
	if unlikely(self->mf_flags & MFILE_F_FIXEDFILESIZE) {
		mfile_lock_endread(self);
		THROW(E_FSERROR_FILE_TOO_BIG);
	}

	/* Make sure that the file won't grow too large. */
	if (mfile_isnode(self)) {
		pos_t max_file_size;
		max_file_size = mfile_asnode(self)->fn_super->fs_feat.sf_filesize_max;
		if (offset >= max_file_size) {
handle_write_impossible_too_big:
			/* Impossible to write anything at this point! */
			mfile_lock_endread(self);

			/* If we were able to write ~something~ up to this
			 * point,  then don't throw a disk-full exception. */
			if (result != 0)
				return result;

			/* If nothing was written, throw a file-too-big exception. */
			THROW(E_FSERROR_FILE_TOO_BIG);
		}

		/* Don't writ more than what can fit within the fs-specific disk limits. */
		max_file_size -= offset;
		assert(max_file_size != 0);
		if ((pos_t)num_bytes > max_file_size)
			num_bytes = (size_t)max_file_size;
		assert(num_bytes != 0);
	}

	/* Figure out the address range of the missing part. */
	newpart_minaddr = offset;
	if unlikely(OVERFLOW_UADD(offset, num_bytes - 1, &newpart_maxaddr)) {
		/* Even without a filesystem-specific limit, there is still a
		 * hard-limit  to how large a file can grow, which is imposed
		 * by the # of bits that fit into `pos_t'.
		 *
		 * If the last address which the caller wants to write would
		 * overflow, then clamp the allowed I/O range to what can be
		 * represented. */
		newpart_maxaddr = (pos_t)-1;
		num_bytes       = (size_t)(((pos_t)-1) - offset);
		if unlikely(num_bytes == 0) {
			/* This can happen when `offset == (pos_t)-1' */
			goto handle_write_impossible_too_big;
		}
	}
	newpart_minaddr = mfile_addr_flooralign(self, newpart_minaddr);
	if unlikely(OVERFLOW_UADD(newpart_maxaddr + 1, self->mf_part_amask, &newpart_maxaddr))
		newpart_maxaddr = 0; /* Results in (pos_t)-1 after the `&=' and `-=' below */
	newpart_maxaddr &= ~(pos_t)self->mf_part_amask;
	newpart_maxaddr -= 1;
	assert(newpart_minaddr <= newpart_maxaddr);

	/* Because the max-valid end address  of the last allocated  mem-part
	 * of any file is  that file's size `mfile_addr_ceilalign()'d,  there
	 * is the possibility that there is a pre-existing part that includes
	 * storage for those last, few  bytes that have already been  loaded,
	 * even though they're not considered to be apart of the file itself.
	 *
	 * For reference, read  up on linux's  (and KOS's) behavior  regarding
	 * reads/writes to the last part of a file-mapping, when the effective
	 * file-address of those reads/writes would be located past the end of
	 * said file.
	 *
	 * Essentially, we must write to those bytes here, and try to increase
	 * the  file's size  to include all  bytes from such  a trailing page. */
	part = mpart_tree_locate(self->mf_parts, newpart_minaddr);
	if (part != NULL && tryincref(part)) {
		io_bytes = (size_t)(mpart_getendaddr(part) - offset);
		assertf(io_bytes <= self->mf_part_amask,
		        "There should never be more than 1 byte less than "
		        "a single (block-aligned) page of trailing memory "
		        "allocated in a any file, based on that file's size");
		/* Still limit the max I/O by what has actually been requested. */
		if (io_bytes > num_bytes)
			io_bytes = num_bytes;

		/* In order to later increase the file's size, we must firstly
		 * acquire  a write-lock to the file, and be holding this lock
		 * when calling `mfile_trunclock_inc()'
		 * This way, another thread can also acquire a write-lock, and
		 * wait for `mf_trunclock' to become  zero in order to  ensure
		 * that a file's size doesn't change for a period of this.
		 *
		 * This kind of functionality is required for O_APPEND support! */
		if (!mfile_lock_tryupgrade(self)) {
			mfile_lock_endread(self);
			decref_unlikely(part);
			mfile_lock_waitwrite(self);
			goto again;
		}

#ifdef LOCAL_TAILIO
		/* In order to atomically append data at the end of the file,  we
		 * must ensure that no-one else might possibly be increasing  the
		 * file's size in the mean time. - This can be ensured by holding
		 * a lock to the file's `mf_lock', and waiting for `mf_trunclock'
		 * to become ZERO. */
		if (ATOMIC_READ(self->mf_trunclock) != 0) {
			mfile_lock_endwrite(self);
			decref_unlikely(part);
			task_connect(&self->mf_initdone);
			if unlikely(ATOMIC_READ(self->mf_trunclock) == 0) {
				task_disconnectall();
				goto again;
			}
			task_waitfor();
			goto again;
		}

		/* We can now be certain that `mf_filesize' won't increase
		 * before we're done writing  data into the given  `part'! */
		if (!mpart_lock_tryacquire(part)) {
			mfile_lock_endwrite(self);
waitfor_part_and_try_again:
			FINALLY_DECREF_UNLIKELY(part);
			mpart_lock_waitfor(part);
			goto again;
		}
		TRY {
			mpart_reladdr_t reladdr;
			struct mfile_unlockinfo unlock;
			reladdr = (mpart_reladdr_t)(offset - mpart_getminaddr(part));

			unlock.ui_unlock = &mfile_unlockinfo_cb;
			unlock.mfui_file = self;

			/* Make sure that `part' has been loaded into the core. */
			if (!MPART_ST_INCORE(part->mp_state)) {
				struct mpart_setcore_data sc_data;
part_setcore:
				mpart_setcore_data_init(&sc_data);
				TRY {
					while (!mpart_setcore_or_unlock(part, &unlock, &sc_data)) {
						/* Re-acquire locks and make sure that nothing's changed. */
						mfile_lock_write(self);
						if (filesize != mfile_getsize(self) || mfile_isanon(self) ||
						    (self->mf_flags & (MFILE_F_DELETED | MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE)) ||
						    part != mpart_tree_locate(self->mf_parts, newpart_minaddr)) {
							mfile_lock_endwrite_f(self);
							mpart_setcore_data_fini(&sc_data);
							mfile_lockops_reap(self);
							goto again;
						}
						if (!mpart_lock_tryacquire(part)) {
							mfile_lock_endwrite(self);
							mpart_setcore_data_fini(&sc_data);
							goto waitfor_part_and_try_again;
						}
					}
				} EXCEPT {
					mpart_setcore_data_fini(&sc_data);
					RETHROW();
				}
			}

			/* Ensure that copy-on-write mappings have been unshared */
			if (!LIST_EMPTY(&part->mp_copy)) {
				struct mpart_unsharecow_data uc_data;
				mpart_unsharecow_data_init(&uc_data);
				TRY {
					while (!mpart_unsharecow_or_unlock(part, &unlock, &uc_data, reladdr, io_bytes)) {
						/* Re-acquire locks and make sure that nothing's changed. */
						mfile_lock_write(self);
						if (filesize != mfile_getsize(self) || mfile_isanon(self) ||
						    (self->mf_flags & (MFILE_F_DELETED | MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE)) ||
						    part != mpart_tree_locate(self->mf_parts, newpart_minaddr)) {
							mfile_lock_endwrite_f(self);
							mpart_unsharecow_data_fini(&uc_data);
							mfile_lockops_reap(self);
							goto again;
						}
						if (!mpart_lock_tryacquire(part)) {
							mfile_lock_endwrite(self);
							mpart_unsharecow_data_fini(&uc_data);
							goto waitfor_part_and_try_again;
						}
						/* Must (once again) make sure that the part is in-core. */
						if unlikely(!MPART_ST_INCORE(part->mp_state)) {
							mpart_unsharecow_data_fini(&uc_data);
							goto part_setcore;
						}
					}
				} EXCEPT {
					mpart_unsharecow_data_fini(&uc_data);
					RETHROW();
				}
			}

			/* Now that the part has been forced into the expected state,
			 * do  the  actual  write  via   `LOCAL_mpart_rw_or_unlock()' */
#ifdef LOCAL_BUFFER_IS_IOVEC
			io_bytes = LOCAL_mpart_rw_or_unlock(part, buffer, buf_offset, io_bytes, reladdr, &unlock);
#else /* LOCAL_BUFFER_IS_IOVEC */
			io_bytes = LOCAL_mpart_rw_or_unlock(part, buffer, io_bytes, reladdr, &unlock);
#endif /* !LOCAL_BUFFER_IS_IOVEC */
		} EXCEPT {
			decref_unlikely(part);
			RETHROW();
		}

		/* Release our lock to the part, now that we no longer need it! */
		mpart_lock_release(part);

#ifndef LOCAL_BUFFER_IS_PHYS
		if (io_bytes == (size_t)-1) {
			mfile_lock_endwrite(self);
			decref_unlikely(part);
			/* Must perform the operation while blocking. */
#if defined(DEFINE_mfile_tailwrite)
			result += _mfile_buffered_tailwrite(self, buffer, num_bytes);
#elif defined(DEFINE_mfile_tailwritev)
			result += _mfile_buffered_tailwritev(self, buffer, buf_offset, num_bytes);
#else /* ... */
#error "Invalid configuration"
#endif /* !... */
			return result;
		}
#endif /* !LOCAL_BUFFER_IS_PHYS */

		if (io_bytes == 0) {
			/* Lock failure (try again) */
			decref_unlikely(part);
			goto again;
		}

		/* Seeing how we're still holding  a write-lock to `self', we  know
		 * that  no-one else (should)  have altered the  file's size in the
		 * mean time, meaning that the append-write above truly was atomic! */
		mfile_trunclock_inc(self);
		atomic64_write(&self->mf_filesize, (u64)(offset + io_bytes));
		mfile_changed(self, MFILE_F_ATTRCHANGED); /* Set the attributes-changed flag. */
		mfile_trunclock_dec_nosignal(self); /* *_nosignal, because we broadcast unconditionally below. */
		mfile_lock_endwrite(self);
		decref_unlikely(part);

#else /* LOCAL_TAILIO */
		mfile_trunclock_inc(self);
		mfile_lock_endwrite(self);
		TRY {
#ifdef LOCAL_BUFFER_IS_IOVEC
			io_bytes = LOCAL_mpart_rw(part, buffer, buf_offset, io_bytes, offset);
#else /* LOCAL_BUFFER_IS_IOVEC */
			io_bytes = LOCAL_mpart_rw(part, buffer, io_bytes, offset);
#endif /* !LOCAL_BUFFER_IS_IOVEC */
		} EXCEPT {
			decref_unlikely(part);
			mfile_trunclock_dec(self);
			RETHROW();
		}
		decref_unlikely(part);

		/* Atomically increase the file  size to `offset + io_bytes', but  do
		 * nothing if the file's size had already been increased to somewhere
		 * beyond that point. */
		{
			pos_t newsize, oldsize;
			newsize = offset + io_bytes;
			for (;;) {
				oldsize = (pos_t)atomic64_cmpxch_val(&self->mf_filesize,
				                                     (u64)filesize,
				                                     (u64)newsize);
				if (oldsize == filesize) {
					/* Successfully altered the file's size. */
					uintptr_t old_flags, new_flags;
					old_flags = ATOMIC_FETCHOR(self->mf_flags, MFILE_F_ATTRCHANGED);
					new_flags = old_flags | MFILE_F_ATTRCHANGED;
					if (old_flags != new_flags && self->mf_ops->mo_changed)
						(*self->mf_ops->mo_changed)(self, old_flags, new_flags);
					break;
				}
				filesize = oldsize;
				if (filesize >= newsize)
					break; /* Already increased further! */
			}
		}
		mfile_trunclock_dec_nosignal(self);
#endif /* !LOCAL_TAILIO */

		/* Always broadcast because we've just increased the file's size! */
		sig_broadcast(&self->mf_initdone);
		LOCAL_buffer_advance(io_bytes);
		num_bytes -= io_bytes;
		offset += io_bytes;
		result += io_bytes;
		goto again;
	}

	/* Try to extend an existing (preceding) part by using `mfile_extendpart_or_unlock()'
	 * Note that if we  later end up failing  to write all of  the relevant data to  that
	 * part, then we're entirely within out  rights to simply truncate block-status,  and
	 * any backing data we  like to get rid  of, since we know  that no-one can  possibly
	 * be  mapping  any   part  the  range   that  was  added   to  the  existing   part.
	 * For this purpose, we can  also assume that the  existing part was extended  above,
	 * since we  know that  no part  (should) have  existed anywhere  above the  accessed
	 * address range (since we know that the  accessed range lies above the file's  size) */
#ifndef __OPTIMIZE_SIZE__
	{
		mpart_reladdr_t old_part_size;
		struct mfile_extendpart_data extdat;
		mfile_extendpart_data_init(&extdat);
		extdat.mep_minaddr = newpart_minaddr;
		extdat.mep_maxaddr = newpart_maxaddr;
again_extend_tailpart:
		TRY {
			part = mfile_extendpart_or_unlock(self, &extdat, NULL);
		} EXCEPT {
			mfile_extendpart_data_fini(&extdat);
			RETHROW();
		}
		if (part == MFILE_EXTENDPART_OR_UNLOCK_AGAIN) {
			TRY {
				mfile_lock_write(self);
			} EXCEPT {
				mfile_extendpart_data_fini(&extdat);
				RETHROW();
			}
			/* Make sure that nothing's changed. */
			if unlikely(mfile_isanon(self)) {
restart_after_extendpart_tail:
				mfile_lock_endwrite(self);
				mfile_extendpart_data_fini(&extdat);
				goto again;
			}
			if unlikely(self->mf_flags & (MFILE_F_DELETED | MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE))
				goto restart_after_extendpart_tail;
			if unlikely(mfile_getsize(self) != filesize)
				goto restart_after_extendpart_tail;
			part = mpart_tree_locate(self->mf_parts, newpart_minaddr);
			if unlikely(part && !wasdestroyed(part))
				goto restart_after_extendpart_tail;
			goto again_extend_tailpart;
		}
		if (part == MFILE_EXTENDPART_OR_UNLOCK_NOSIB)
			goto extend_failed;

		/* Figure out what must have been the part's original size. */
		old_part_size = (size_t)(filesize - mpart_getminaddr(part));
		old_part_size = mfile_size_ceilalign(self, old_part_size);

		/* Figure out how much we can write to the (now extended) part. */
		io_bytes = (size_t)(mpart_getendaddr(part) - offset);
		if (io_bytes > num_bytes)
			io_bytes = num_bytes;

#ifdef LOCAL_TAILIO
		/* In order to atomically append data at the end of the file,  we
		 * must ensure that no-one else might possibly be increasing  the
		 * file's size in the mean time. - This can be ensured by holding
		 * a lock to the file's `mf_lock', and waiting for `mf_trunclock'
		 * to become ZERO. */
		if (ATOMIC_READ(self->mf_trunclock) != 0) {
			mpart_truncate_undo(self, part, old_part_size);
			task_connect(&self->mf_initdone);
			if unlikely(ATOMIC_READ(self->mf_trunclock) == 0) {
				task_disconnectall();
				goto again;
			}
			task_waitfor();
			goto again;
		}
#endif /* LOCAL_TAILIO */
		TRY {
			mpart_reladdr_t reladdr;
			struct mpart_truncate_undo_unlockinfo unlock;
			reladdr = (mpart_reladdr_t)(offset - mpart_getminaddr(part));

			unlock.ui_unlock = &mpart_truncate_undo_unlockinfo_cb;
			unlock.mtuu_file      = self;
			unlock.mtuu_part      = part;
			unlock.mtuu_orig_size = old_part_size;

			/* Make sure that `part' has been loaded into the core. */
			if (!MPART_ST_INCORE(part->mp_state)) {
				struct mpart_setcore_data sc_data;
				mpart_setcore_data_init(&sc_data);
				TRY {
					if (!mpart_setcore_or_unlock(part, &unlock, &sc_data)) {
						mpart_setcore_data_fini(&sc_data);
						decref_unlikely(part);
						goto extend_failed;
					}
				} EXCEPT {
					mpart_setcore_data_fini(&sc_data);
					decref_unlikely(part);
					RETHROW();
				}
			}

			/* No need to  fiddle with unsharing  copy-on-write! The area  we're
			 * trying to write to has only been added by us right now, and since
			 * we've yet to release our lock to the part, we also know that said
			 * area can't possibly be shared with anyone! */

			/* Now that the part has been forced into the expected state,
			 * do  the  actual  write  via   `LOCAL_mpart_rw_or_unlock()' */
#ifdef LOCAL_BUFFER_IS_IOVEC
			io_bytes = LOCAL_mpart_rw_or_unlock(part, buffer, buf_offset, io_bytes, reladdr, &unlock);
#else /* LOCAL_BUFFER_IS_IOVEC */
			io_bytes = LOCAL_mpart_rw_or_unlock(part, buffer, io_bytes, reladdr, &unlock);
#endif /* !LOCAL_BUFFER_IS_IOVEC */
		} EXCEPT {
			decref_unlikely(part);
			RETHROW();
		}

#ifndef LOCAL_BUFFER_IS_PHYS
		if (io_bytes == (size_t)-1) {
			/* Undo, and repeat the entire call with buffered memory access! */
			mpart_truncate_undo(self, part, old_part_size);

			/* Must perform the operation while blocking. */
#if defined(DEFINE_mfile_tailwrite)
			result += _mfile_buffered_tailwrite(self, buffer, num_bytes);
#elif defined(DEFINE_mfile_tailwritev)
			result += _mfile_buffered_tailwritev(self, buffer, buf_offset, num_bytes);
#elif defined(DEFINE_mfile_write)
			result += _mfile_buffered_write(self, buffer, num_bytes, offset);
#elif defined(DEFINE_mfile_writev)
			result += _mfile_buffered_writev(self, buffer, buf_offset, num_bytes, offset);
#else /* ... */
#error "Invalid configuration"
#endif /* !... */
			return result;
		}
#endif /* !LOCAL_BUFFER_IS_PHYS */

		if (io_bytes == 0)
			goto extend_undo;

		/* Release our lock to the part, now that we no longer need it! */
		mpart_lock_release(part);

		/* Seeing how we're still holding  a write-lock to `self', we  know
		 * that  no-one else (should)  have altered the  file's size in the
		 * mean time, meaning that the append-write above truly was atomic! */
		mfile_trunclock_inc(self);
		atomic64_write(&self->mf_filesize, (u64)(offset + io_bytes));
		mfile_changed(self, MFILE_F_ATTRCHANGED); /* Set the attributes-changed flag. */
		mfile_trunclock_dec_nosignal(self); /* *_nosignal, because we broadcast unconditionally below. */
		mfile_lock_endwrite(self);
		decref_unlikely(part);

		/* Always broadcast because we've just increased the file's size! */
		sig_broadcast(&self->mf_initdone);
		LOCAL_buffer_advance(io_bytes);
		num_bytes -= io_bytes;
		offset += io_bytes;
		result += io_bytes;

		/* Because we altered the file's size, we must also set the ATTRCHANGED flag. */
		{
			uintptr_t old_flags;
			old_flags = ATOMIC_FETCHOR(self->mf_flags, MFILE_F_ATTRCHANGED);
			if (!(old_flags & MFILE_F_ATTRCHANGED) && self->mf_ops->mo_changed)
				(*self->mf_ops->mo_changed)(self, old_flags, old_flags | MFILE_F_ATTRCHANGED);
		}

		goto again;
extend_undo:
		mpart_truncate_restore(part, old_part_size);
		mpart_lock_release(part);
		decref_unlikely(part);
	}
extend_failed:
#endif /* !__OPTIMIZE_SIZE__ */

	/* Must create a new part for the accessed address range, and directly write to said
	 * part. Afterwards, try to  insert this new  part into the  file, and increase  the
	 * file's size. (do this using `mfile_insert_and_merge_part_and_unlock()').
	 *
	 * However,  if this part fails (i.e. `NULL' is returned), then we must not immediately
	 * discard the part if the caller-given buffer  is located in virtual memory, but  must
	 * instead using its backing physical memory as a new physical source buffer from which
	 * to copy data to-be written  to the file. (this way,  we can prevent duplicate  reads
	 * from VIO memory when this kind of memory was used as origin buffer) */
	mfile_lock_end(self);
	/*io_bytes = num_bytes;*/

	/* Construct the new part. */
	part = _mfile_newpart(self, newpart_minaddr,
	                      (size_t)(newpart_maxaddr -
	                               newpart_minaddr) +
	                      1);
	/* Initialize remaining fields. */
	part->mp_refcnt = 3; /* +1: return:mfile_insert_and_merge_part_and_unlock,
	                      * +1: MPART_F_CHANGED
	                      * +1: MPART_F_GLOBAL_REF */
	part->mp_xflags = MPART_XF_NORMAL;
	part->mp_file   = incref(self);
	LIST_INIT(&part->mp_copy);
	LIST_INIT(&part->mp_share);
	SLIST_INIT(&part->mp_lockops);
	/*LIST_ENTRY_UNBOUND_INIT(&part->mp_allparts);*/ /* Initialized later... */
	part->mp_minaddr = newpart_minaddr;
	part->mp_maxaddr = newpart_maxaddr;
	DBG_memset(&part->mp_changed, 0xcc, sizeof(part->mp_changed));
	_mpart_init_asanon(part);
	/* NOTE: Setting `MPART_F_CHANGED' here will cause `mfile_insert_and_merge_part_and_unlock()'
	 *       to add  automatically  add  the  part  to  the  list  of  changed  parts  of  `self' */
	part->mp_flags |= MPART_F_GLOBAL_REF | MPART_F_CHANGED;

	/* Make sure that the part has been allocated. Afterwards, copy the
	 * caller-provided buffer into the correct offset within the  part.
	 *
	 * Note that since we're not holding any locks while doing this, we
	 * don't even have to take any care of prefaulting and/or VIO. - We
	 * can simply access memory directly! */
	TRY {
#ifdef LOCAL_BUFFER_IS_IOVEC
#ifdef LOCAL_BUFFER_IS_PHYS
#define LOCAL_BUFFER_copy2phys(dstaddr, src_offset, num_bytes) iov_physbuffer_copytophys(buffer, dstaddr, buf_offset + (src_offset), num_bytes)
#else /* LOCAL_BUFFER_IS_PHYS */
#define LOCAL_BUFFER_copy2phys(dstaddr, src_offset, num_bytes) iov_buffer_copytophys(buffer, dstaddr, buf_offset + (src_offset), num_bytes)
#endif /* !LOCAL_BUFFER_IS_PHYS */
#else /* LOCAL_BUFFER_IS_IOVEC */
#ifdef LOCAL_BUFFER_IS_PHYS
#define LOCAL_BUFFER_copy2phys(dstaddr, src_offset, num_bytes) copyinphys(dstaddr, buffer + (src_offset), num_bytes)
#else /* LOCAL_BUFFER_IS_PHYS */
#define LOCAL_BUFFER_copy2phys(dstaddr, src_offset, num_bytes) copytophys(dstaddr, (byte_t *)buffer + (src_offset), num_bytes)
#endif /* !LOCAL_BUFFER_IS_PHYS */
#endif /* !LOCAL_BUFFER_IS_IOVEC */
		mpart_reladdr_t partmin;
		size_t blki, minblk, maxblk;

		if (!MPART_ST_INCORE(part->mp_state))
			mpart_ll_allocmem(part, mpart_getsize(part) >> PAGESHIFT);
		partmin = (mpart_reladdr_t)(offset - mpart_getminaddr(part));
		assert(partmin <= self->mf_part_amask);
		if (part->mp_state == MPART_ST_MEM) {
			physaddr_t dst;
			size_t total_bytes, source_end;
			dst = physpage2addr(part->mp_mem.mc_start);
			LOCAL_BUFFER_copy2phys(dst + partmin, 0, num_bytes);
			total_bytes = part->mp_mem.mc_size << PAGESHIFT;
			source_end  = partmin + num_bytes;
			/* Force zero-initialization of the head/tail region. */
			bzerophyscc(dst, partmin);
			bzerophyscc(dst + source_end, total_bytes - source_end);
		} else {
			size_t i;
			mpart_reladdr_t src_offset = 0;
			size_t src_bytes = num_bytes;
			assert(part->mp_state == MPART_ST_MEM_SC);
			/* Copy memory from the caller's buffer into the chunk-vector. */
			for (i = 0; i < part->mp_mem_sc.ms_c; ++i) {
				struct mchunk chunk;
				physaddr_t chunk_addr;
				size_t chunk_size;
				chunk      = part->mp_mem_sc.ms_v[i];
				chunk_addr = physpage2addr(chunk.mc_start);
				chunk_size = chunk.mc_size << PAGESHIFT;
				if (partmin != 0) {
					bzerophyscc(chunk_addr, partmin);
					chunk_addr += partmin;
					chunk_size -= partmin;
					partmin = 0;
				}
				if (src_bytes >= chunk_size) {
					LOCAL_BUFFER_copy2phys(chunk_addr, src_offset, chunk_size);
					src_bytes -= chunk_size;
					src_offset += chunk_size;
				} else {
					if (src_bytes != 0) {
						LOCAL_BUFFER_copy2phys(chunk_addr, src_offset, src_bytes);
						chunk_addr += src_bytes;
						chunk_size -= src_bytes;
					}
					bzerophyscc(chunk_addr, chunk_size);
				}
			}
			partmin = (mpart_reladdr_t)(offset - mpart_getminaddr(part));
		}
		/* Mark all blocks that we've wrote data to as changed. */
		minblk = (partmin) >> self->mf_blockshift;
		maxblk = (partmin + num_bytes - 1) >> self->mf_blockshift;
		assert(minblk <= maxblk);
		for (blki = minblk; blki <= maxblk; ++blki)
			mpart_setblockstate(part, blki, MPART_BLOCK_ST_CHNG);
#undef LOCAL_BUFFER_copy2phys

		/* Re-acquire a lock to the file, so we can insert the new mem-part. */
		mfile_lock_write(self);
	} EXCEPT {
		LIST_ENTRY_UNBOUND_INIT(&part->mp_allparts);
		part->mp_refcnt = 0;
		mpart_destroy(part);
		RETHROW();
	}

	/* Make sure that the file hasn't become anonymous. */
	if unlikely(mfile_isanon(self))
		goto handle_part_insert_failure;

	/* Make sure that the file's size can still be altered. */
	if unlikely(self->mf_flags & (MFILE_F_DELETED | MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE))
		goto handle_part_insert_failure;

	/* Try to insert the new part into the file, as
	 * well as merge it with its neighboring parts. */
	{
		uintptr_t changes;
		pos_t newsize, oldsize;
		REF struct mpart *inserted_part;
		mfile_trunclock_inc(self);
		inserted_part = mfile_insert_and_merge_part_and_unlock(self, part);
		if unlikely(!inserted_part) {
#ifndef LOCAL_BUFFER_IS_PHYS
			mpart_reladdr_t partoff;
#endif /* !LOCAL_BUFFER_IS_PHYS */
			mfile_trunclock_dec(self);
handle_part_insert_failure:
			mfile_lock_endwrite(self);
			RAII_FINALLY {
				LIST_ENTRY_UNBOUND_INIT(&part->mp_allparts);
				part->mp_refcnt = 0;
				mpart_destroy(part);
			};
#ifdef LOCAL_BUFFER_IS_PHYS
			goto again;
#else /* LOCAL_BUFFER_IS_PHYS */
			/* To prevent repeated reads from memory that may be backed by  VIO,
			 * handle this case by simply (ab-)using `part' as the source buffer
			 * from which to take memory to-be written to the file. */
			partoff = (mpart_reladdr_t)(offset - mpart_getminaddr(part));
			assert(partoff <= self->mf_part_amask);
			assert(part->mp_state == MPART_ST_MEM ||
			       part->mp_state == MPART_ST_MEM_SC);
			mfile_write_from_mempart_buffer(self, part, partoff, num_bytes, offset);
			result += num_bytes;
			goto done;
#endif /* !LOCAL_BUFFER_IS_PHYS */
		}

		/* Have the file's `mf_changed' list inherit a reference to `inserted_part'.
		 *
		 * With  the inclusion of the new changed part, we must always mark the file
		 * as (possibly) containing modified parts.  We're allowed to set this  flag
		 * even  if  `mfile_insert_and_merge_part_and_unlock()' didn't  add anything
		 * to  the changed part list (because the  file may have become anonymous in
		 * the mean time), since this flag only means: there _may_ be changed parts. */
		changes = MFILE_F_CHANGED;

		/* Atomically increase the file size to `offset + num_bytes', but  do
		 * nothing if the file's size had already been increased to somewhere
		 * beyond that point. */
		newsize = offset + num_bytes;
		for (;;) {
			oldsize = (pos_t)atomic64_cmpxch_val(&self->mf_filesize,
			                                     (u64)filesize,
			                                     (u64)newsize);
			if (oldsize == filesize) {
				changes |= MFILE_F_ATTRCHANGED;
				break;
			}
			filesize = oldsize;
			if (filesize >= newsize)
				break; /* Already increased further! */
		}
		mfile_trunclock_dec_nosignal(self);
		/* Always broadcast because we've just increased the file's size! */
		sig_broadcast(&self->mf_initdone);

		/* Update the last-modified timestamp. */
		if (!(self->mf_flags & MFILE_F_NOMTIME)) {
			struct timespec now = realtime();
			mfile_tslock_acquire(self);
			COMPILER_READ_BARRIER();
			if (!(self->mf_flags & (MFILE_F_NOMTIME | MFILE_F_DELETED))) {
				self->mf_mtime = now;
				changes |= MFILE_F_ATTRCHANGED;
			}
			mfile_tslock_release(self);
		}

		mfile_changed(self, changes);
		result += num_bytes;

		/* Drop the reference from `mfile_insert_and_merge_part_and_unlock()' */
		decref_unlikely(inserted_part);
	} /* Scope.... */

	/* Since we've just written _all_ of the trailing data, we're
	 * finally  done and don't  have to loop  back to write more! */
#endif /* !LOCAL_READING */

done:
	return result;
#undef offset
#endif /* !LOCAL_READING || !LOCAL_TAILIO */
}


#undef LOCAL_buffer_advance
#undef LOCAL_TAILIO
#undef LOCAL_BUFFER_IS_PHYS
#undef LOCAL_BUFFER_IS_IOVEC
#undef LOCAL_ubuffer_t
#undef LOCAL_buffer_t
#undef LOCAL_buffer_ent_t
#undef LOCAL_mpart_rw
#undef LOCAL_mpart_rw_or_unlock
#undef LOCAL_mfile_rw
#undef LOCAL_mfile_viorw
#undef LOCAL_mfile_normrw
#undef LOCAL_mfile_tailrw
#undef LOCAL_READING
#undef LOCAL_WRITING

DECL_END

#undef DEFINE_mfile_read
#undef DEFINE_mfile_read_p
#undef DEFINE_mfile_readv
#undef DEFINE_mfile_readv_p
#undef DEFINE_mfile_tailread
#undef DEFINE_mfile_tailread_p
#undef DEFINE_mfile_tailreadv
#undef DEFINE_mfile_tailreadv_p
#undef DEFINE_mfile_write
#undef DEFINE_mfile_write_p
#undef DEFINE_mfile_writev
#undef DEFINE_mfile_writev_p
#undef DEFINE_mfile_tailwrite
#undef DEFINE_mfile_tailwrite_p
#undef DEFINE_mfile_tailwritev
#undef DEFINE_mfile_tailwritev_p
