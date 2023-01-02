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
#ifdef __INTELLISENSE__
#include "mpart-rw.c"
//#define DEFINE_mpart_read
#define DEFINE_mpart_write
//#define   DEFINE_mpart_read_p
//#define  DEFINE_mpart_write_p
//#define    DEFINE_mpart_readv
//#define   DEFINE_mpart_writev
//#define  DEFINE_mpart_readv_p
//#define DEFINE_mpart_writev_p
#endif /* __INTELLISENSE__ */

#include <kernel/iovec.h>
#include <kernel/mman/fault.h> /* mman_prefault(), mman_prefaultv() */
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/phys.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include <alloca.h>
#include <assert.h>
#include <string.h>

#include <libvio/access.h>

DECL_BEGIN

#if defined(DEFINE_mpart_read)
#define LOCAL_READING
#define LOCAL_buffer_t           USER CHECKED void *
#define LOCAL_ubuffer_t          uintptr_t
#define LOCAL_mfile_vio_rw       mfile_vioread
#define LOCAL_mpart_rw           mpart_read
#define LOCAL_mpart_rw_or_unlock mpart_read_or_unlock
#define LOCAL__mpart_buffered_rw _mpart_buffered_read
#define LOCAL_buffer_transfer_nopf(buffer_offset, mpart_physaddr, num_bytes) \
	copyfromphys_nopf((byte_t *)buffer + (buffer_offset), mpart_physaddr, num_bytes)
#elif defined(DEFINE_mpart_write)
#define LOCAL_WRITING
#define LOCAL_buffer_t           USER CHECKED void const *
#define LOCAL_ubuffer_t          uintptr_t
#define LOCAL_mfile_vio_rw       mfile_viowrite
#define LOCAL_mpart_rw           mpart_write
#define LOCAL_mpart_rw_or_unlock mpart_write_or_unlock
#define LOCAL__mpart_buffered_rw _mpart_buffered_write
#define LOCAL_buffer_transfer_nopf(buffer_offset, mpart_physaddr, num_bytes) \
	copytophys_nopf(mpart_physaddr, (byte_t const *)buffer + (buffer_offset), num_bytes)
#elif defined(DEFINE_mpart_read_p)
#define LOCAL_READING
#define LOCAL_buffer_t           physaddr_t
#define LOCAL_ubuffer_t          physaddr_t
#define LOCAL_mfile_vio_rw       mfile_vioread_p
#define LOCAL_mpart_rw           mpart_read_p
#define LOCAL_mpart_rw_or_unlock mpart_read_or_unlock_p
#define LOCAL_BUFFER_TRANSFER_NOEXCEPT
#define LOCAL_buffer_transfer_nopf(buffer_offset, mpart_physaddr, num_bytes) \
	copyinphys(buffer + (buffer_offset), mpart_physaddr, num_bytes)
#elif defined(DEFINE_mpart_write_p)
#define LOCAL_WRITING
#define LOCAL_buffer_t           physaddr_t
#define LOCAL_ubuffer_t          physaddr_t
#define LOCAL_mfile_vio_rw       mfile_viowrite_p
#define LOCAL_mpart_rw           mpart_write_p
#define LOCAL_mpart_rw_or_unlock mpart_write_or_unlock_p
#define LOCAL_BUFFER_TRANSFER_NOEXCEPT
#define LOCAL_buffer_transfer_nopf(buffer_offset, mpart_physaddr, num_bytes) \
	copyinphys(mpart_physaddr, buffer + (buffer_offset), num_bytes)
#elif defined(DEFINE_mpart_readv)
#define LOCAL_READING
#define LOCAL_BUFFER_IS_AIO
#define LOCAL_BUFFER_IS_IOV_BUFFER
#define LOCAL_buffer_t           struct iov_buffer const *__restrict
#define LOCAL_mfile_vio_rw       mfile_vioreadv
#define LOCAL_mpart_rw           mpart_readv
#define LOCAL_mpart_rw_or_unlock mpart_readv_or_unlock
#define LOCAL__mpart_buffered_rw _mpart_buffered_readv
#define LOCAL_buffer_transfer_nopf(buffer_offset, mpart_physaddr, num_bytes) \
	iov_buffer_copyfromphys_nopf(buffer, buf_offset + (buffer_offset), mpart_physaddr, num_bytes)
#elif defined(DEFINE_mpart_writev)
#define LOCAL_WRITING
#define LOCAL_BUFFER_IS_AIO
#define LOCAL_BUFFER_IS_IOV_BUFFER
#define LOCAL_buffer_t           struct iov_buffer const *__restrict
#define LOCAL_mfile_vio_rw       mfile_viowritev
#define LOCAL_mpart_rw           mpart_writev
#define LOCAL_mpart_rw_or_unlock mpart_writev_or_unlock
#define LOCAL__mpart_buffered_rw _mpart_buffered_writev
#define LOCAL_buffer_transfer_nopf(buffer_offset, mpart_physaddr, num_bytes) \
	iov_buffer_copytophys_nopf(buffer, mpart_physaddr, buf_offset + (buffer_offset), num_bytes)
#elif defined(DEFINE_mpart_readv_p)
#define LOCAL_READING
#define LOCAL_BUFFER_IS_AIO
#define LOCAL_BUFFER_IS_IOV_PHYSBUFFER
#define LOCAL_buffer_t           struct iov_physbuffer const *__restrict
#define LOCAL_mfile_vio_rw       mfile_vioreadv_p
#define LOCAL_mpart_rw           mpart_readv_p
#define LOCAL_mpart_rw_or_unlock mpart_readv_or_unlock_p
#define LOCAL_BUFFER_TRANSFER_NOEXCEPT
#define LOCAL_buffer_transfer_nopf(buffer_offset, mpart_physaddr, num_bytes) \
	iov_physbuffer_copyfromphys(buffer, buf_offset + (buffer_offset), mpart_physaddr, num_bytes)
#elif defined(DEFINE_mpart_writev_p)
#define LOCAL_WRITING
#define LOCAL_BUFFER_IS_AIO
#define LOCAL_BUFFER_IS_IOV_PHYSBUFFER
#define LOCAL_buffer_t           struct iov_physbuffer const *__restrict
#define LOCAL_mfile_vio_rw       mfile_viowritev_p
#define LOCAL_mpart_rw           mpart_writev_p
#define LOCAL_mpart_rw_or_unlock mpart_writev_or_unlock_p
#define LOCAL_BUFFER_TRANSFER_NOEXCEPT
#define LOCAL_buffer_transfer_nopf(buffer_offset, mpart_physaddr, num_bytes) \
	iov_physbuffer_copytophys(buffer, mpart_physaddr, buf_offset + (buffer_offset), num_bytes)
#else /* ... */
#error "Bad configuration"
#endif /* !... */

#ifdef LOCAL__mpart_buffered_rw
/* Same as the above, but these use an intermediate (stack) buffer for  transfer.
 * As such, these functions are called by the above when `memcpy_nopf()' produces
 * transfer errors that cannot be resolved by `mman_prefault()' */
PUBLIC BLOCKING ATTR_NOINLINE NONNULL((1)) size_t KCALL
LOCAL__mpart_buffered_rw(struct mpart *__restrict self,
                         LOCAL_buffer_t buffer,
#ifdef LOCAL_BUFFER_IS_AIO
                         size_t buf_offset,
#endif /* LOCAL_BUFFER_IS_AIO */
                         size_t num_bytes,
                         pos_t filepos)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	size_t bufsize, result = 0;
	void *stk_buf;
	bufsize = num_bytes;
	if (bufsize > 1024)
		bufsize = 1024;
	stk_buf = alloca(bufsize);
	while (num_bytes) {
		size_t part, ok;
		part = bufsize;
		if (part > num_bytes)
			part = num_bytes;
#ifdef LOCAL_WRITING
		/* Load data into `stk_buf' */
#ifdef LOCAL_BUFFER_IS_AIO
		iov_buffer_copytomem(buffer, stk_buf, buf_offset, part);
#else /* LOCAL_BUFFER_IS_AIO */
		memcpy(stk_buf, buffer, part);
#endif /* !LOCAL_BUFFER_IS_AIO */

		/* Write `stk_buf' to the file. */
		ok = mpart_write(self, stk_buf, part, filepos);
#else /* LOCAL_WRITING */

		/* Read `stk_buf' from the file. */
		ok = mpart_read(self, stk_buf, part, filepos);

		/* Copy data from `stk_buf' */
#ifdef LOCAL_BUFFER_IS_AIO
		iov_buffer_copyfrommem(buffer, buf_offset, stk_buf, ok);
#else /* LOCAL_BUFFER_IS_AIO */
		memcpy(buffer, stk_buf, ok);
#endif /* !LOCAL_BUFFER_IS_AIO */
#endif /* !LOCAL_WRITING */

		assert(ok <= part);
		result += ok;
		if (ok < part)
			break;
#ifdef LOCAL_BUFFER_IS_AIO
		buf_offset += ok;
#else /* LOCAL_BUFFER_IS_AIO */
		buffer = (LOCAL_buffer_t)((LOCAL_ubuffer_t)buffer + result);
#endif /* !LOCAL_BUFFER_IS_AIO */
		filepos += ok;
		num_bytes -= ok;
	}
	return result;
}
#endif /* LOCAL__mpart_buffered_rw */


/* Read/write raw data to/from a given mem-part.
 * @return: * : The # of bytes that were transferred. May be less than `num_bytes' if the part
 *              is too small, or  if the given  `filepos' lies outside  of the part's  bounds. */
PUBLIC BLOCKING NONNULL((1)) size_t KCALL
LOCAL_mpart_rw(struct mpart *__restrict self,
               LOCAL_buffer_t buffer,
#ifdef LOCAL_BUFFER_IS_AIO
               size_t buf_offset,
#endif /* LOCAL_BUFFER_IS_AIO */
               size_t num_bytes,
               pos_t filepos)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	size_t result;
	struct mpart_physloc physloc;
	mpart_reladdr_t part_offs, part_size;

	/* Deal with VIO parts. */
#ifdef LIBVIO_CONFIG_ENABLED
	if unlikely(self->mp_state == MPART_ST_VIO) {
		REF struct mfile *file;
		mpart_lock_acquire(self);
		file = incref(self->mp_file);
		mpart_lock_release(self);

		/* Directly read to/from VIO */
		FINALLY_DECREF_UNLIKELY(file);

		/* The file may have been changed to something that doesn't support VIO
		 * This  is unlikely, but  can happen if the  file has been anonymized! */
		if unlikely(file->mf_ops->mo_vio == NULL)
			return 0;

		/* Technically, we're supposed to check that `filepos' is still in-bounds
		 * of our mem-part, but  doing so is kind-of  redundant, which is why  we
		 * don't actually do that check! */
		LOCAL_mfile_vio_rw(file, buffer,
#ifdef LOCAL_BUFFER_IS_AIO
		                   buf_offset,
#endif /* LOCAL_BUFFER_IS_AIO */
		                   num_bytes,
		                   filepos);
		return num_bytes;
	}
#endif /* LIBVIO_CONFIG_ENABLED */
	result = 0;

	/* Lock+load the part, unsharing the accessed address range if necessary. */
again:
#ifdef LOCAL_WRITING
	if (!mpart_lock_acquire_and_setcore_unsharecow(self, filepos, num_bytes))
		goto done;
#else /* LOCAL_WRITING */
	if (!mpart_lock_acquire_and_setcore_load(self, filepos, num_bytes))
		goto done;
#endif /* !LOCAL_WRITING */

	/* Figure out the part-relative offset+size */
	part_offs = (mpart_reladdr_t)(filepos - mpart_getminaddr(self));
	part_size = (mpart_reladdr_t)(mpart_getendaddr(self) - filepos);
	if (part_size > num_bytes)
		part_size = num_bytes;

	/* Load the physical location of the requested segment. */
again_memaddr:
#ifdef LOCAL_WRITING
	if (!mpart_memaddr_for_write(self, part_offs, part_size, &physloc))
#else /* LOCAL_WRITING */
	if (!mpart_memaddr_for_read(self, part_offs, part_size, &physloc))
#endif /* !LOCAL_WRITING */
	{
		/* Must initialize more backing memory.
		 * NOTE: When writing, we only initialize a single block,
		 *       so-as to take  advantage of  the possibility  of
		 *       write  whole blocks without  having to load them
		 *       first! */
#ifdef LOCAL_WRITING
		/* NOTE: `mpart_memaddr_for_write()' won't fail for the trailing block
		 *       ~per se. Instead, it  will limit `physloc.mppl_size' to  stop
		 *       just shy of the trailing block, but still return `true'.
		 * That way, we will write however much we can, before looking  back
		 * around, at which point the used-to-be trailing block has suddenly
		 * become the leading block! */
		physloc.mppl_size = 1;
#endif /* LOCAL_WRITING */
		mpart_memload_and_unlock(self, part_offs, &physloc, NULL);
		goto again;
	}
	assert(physloc.mppl_size != 0);
	assert(physloc.mppl_size <= part_size);

	/* Actually transfer data! */
#ifdef LOCAL_BUFFER_TRANSFER_NOEXCEPT
	LOCAL_buffer_transfer_nopf(result,
	                           physloc.mppl_addr,
	                           physloc.mppl_size);
#else /* LOCAL_BUFFER_TRANSFER_NOEXCEPT */
	{
		size_t copy_error;
		copy_error = LOCAL_buffer_transfer_nopf(result,
		                                        physloc.mppl_addr,
		                                        physloc.mppl_size);
		if unlikely(copy_error != 0) {
			assert(copy_error <= physloc.mppl_size);

			/* Deal with the case where the copy-error isn't total. */
			if unlikely(copy_error < physloc.mppl_size) {
				size_t ok = physloc.mppl_size - copy_error;
#ifdef LOCAL_WRITING
				/* Commit the partial write success (and limit the # of
				 * successfully  written bytes to what we were actually
				 * able to commit). */
				ok = mpart_memaddr_for_write_commit(self, part_offs, ok);
#endif /* LOCAL_WRITING */
				result += ok;
				filepos += ok;
				num_bytes -= ok;
			}

			/* Can't use memcpy_nopf() to transfer memory from the given buffer.
			 * This can happen for 3 reasons:
			 *  - The buffer hasn't been loaded into memory
			 *  - The buffer is backed by VIO memory
			 *  - The buffer is actually invalid and represents a faulty address
			 * Assuming a well-behaved application, we can optimize performance
			 * for the first case by attempting to pre-fault the current target
			 * buffer. */
			mpart_lock_release(self);
#ifdef LOCAL_WRITING
#define LOCAL_prefault_flags MMAN_FAULT_F_NORMAL /* Writing from a buffer means we only need to read said buffer! */
#else /* LOCAL_WRITING */
#define LOCAL_prefault_flags MMAN_FAULT_F_WRITE /* Reading into a buffer means we must write to said buffer! */
#endif /* !LOCAL_WRITING */
#ifdef LOCAL_BUFFER_IS_IOV_BUFFER
			copy_error = mman_prefaultv(buffer, result, num_bytes,
			                            LOCAL_prefault_flags);
#else /* LOCAL_BUFFER_IS_IOV_BUFFER */
			copy_error = mman_prefault((byte_t *)buffer + result,
			                           num_bytes, LOCAL_prefault_flags);
#endif /* !LOCAL_BUFFER_IS_IOV_BUFFER */
#undef LOCAL_prefault_flags

			/* If we've managed to prefault memory, then re-attempt the direct transfer. */
			if (copy_error != 0)
				goto again;

			/* If  pre-faulting memory didn't work, then we
			 * must use an intermediate buffer for transfer */
#ifdef LOCAL_BUFFER_IS_AIO
			result += LOCAL__mpart_buffered_rw(self, buffer, buf_offset + result,
			                                   num_bytes, filepos);
#else /* LOCAL_BUFFER_IS_AIO */
			result += LOCAL__mpart_buffered_rw(self, (LOCAL_buffer_t)((LOCAL_ubuffer_t)buffer + result),
			                                   num_bytes, filepos);
#endif /* !LOCAL_BUFFER_IS_AIO */
			return result;
		} /* if unlikely(copy_error != 0) */
	}     /* scope... */
#endif /* !LOCAL_BUFFER_TRANSFER_NOEXCEPT */

#ifdef LOCAL_WRITING
	/* Commit written data.
	 * NOTE: In this case,  `mpart_memaddr_for_write_commit()' should  always
	 *       re-return `physloc.mppl_size', but we don't actually assert this
	 *       here! */
	physloc.mppl_size = mpart_memaddr_for_write_commit(self, part_offs,
	                                                   physloc.mppl_size);
#endif /* LOCAL_WRITING */

	result += physloc.mppl_size;

	/* Check if there is more data for us to transfer. */
	if (part_size > physloc.mppl_size) {
		part_offs += physloc.mppl_size;
		filepos += physloc.mppl_size;
		part_size -= physloc.mppl_size;
		num_bytes -= physloc.mppl_size;
		goto again_memaddr;
	}
	mpart_lock_release(self);
done:
	return result;
}



/* Perform I/O while holding  a lock to `self'.  If this isn't possible,  then
 * unlock all locks,  try to  work towards  that goal,  and return  `0'. If  a
 * virtual buffer is given,  and that buffer cannot  be faulted (e.g.: it  may
 * be backed by VIO, or may even be faulty), return `(size_t)-1', after having
 * released all locks, which is  indicative that the caller should  re-attempt
 * the operation with buffered I/O.
 * Locking logic:
 *    IN:                   mpart_lock_acquired(self);
 *    EXCEPT:               mpart_lock_release(self); unlock();
 *    return == 0:          mpart_lock_release(self); unlock();
 *    return == (size_t)-1: mpart_lock_release(self); unlock();  (never returned by *_p variants)
 *    return == *:          mpart_lock_acquired(self);
 * Upon success, return the (non-zero) # of transferred bytes.
 * The caller must ensure that:
 *    >> num_bytes != 0
 *    >> MPART_ST_INCORE(self->mp_state)   // Can be ensured by `mpart_setcore_or_unlock()'
 *    >> mpart_unsharecow_or_unlock(...)   // Only for `mpart_write*', and only within the target address range
 */
PUBLIC BLOCKING NONNULL((1)) size_t KCALL
LOCAL_mpart_rw_or_unlock(struct mpart *__restrict self,
                         LOCAL_buffer_t buffer,
#ifdef LOCAL_BUFFER_IS_AIO
                         size_t buf_offset,
#endif /* LOCAL_BUFFER_IS_AIO */
                         size_t num_bytes,
                         mpart_reladdr_t offset,
                         struct unlockinfo *unlock)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	size_t result = 0;
	struct mpart_physloc physloc;
	assert(mpart_lock_acquired(self));
	assert(offset + num_bytes > offset);
	assert(offset + num_bytes <= mpart_getsize(self));
	assert(MPART_ST_INCORE(self->mp_state));

	/* Load the physical location of the requested segment. */
again_memaddr:
#ifdef LOCAL_WRITING
	if (!mpart_memaddr_for_write(self, offset, num_bytes, &physloc))
#else /* LOCAL_WRITING */
	if (!mpart_memaddr_for_read(self, offset, num_bytes, &physloc))
#endif /* !LOCAL_WRITING */
	{
		/* Must initialize more backing memory.
		 * NOTE: When writing, we only initialize a single block,
		 *       so-as to take  advantage of  the possibility  of
		 *       write  whole blocks without  having to load them
		 *       first! */
#ifdef LOCAL_WRITING
		physloc.mppl_size = 1;
#endif /* LOCAL_WRITING */
		mpart_memload_and_unlock(self, offset, &physloc, unlock);
		return 0;
	}
	assert(physloc.mppl_size != 0);
	assert(physloc.mppl_size <= num_bytes);

	/* Actually transfer data! */
#ifdef LOCAL_BUFFER_TRANSFER_NOEXCEPT
	LOCAL_buffer_transfer_nopf(result,
	                           physloc.mppl_addr,
	                           physloc.mppl_size);
#else /* LOCAL_BUFFER_TRANSFER_NOEXCEPT */
	{
		size_t copy_error;
		copy_error = LOCAL_buffer_transfer_nopf(result,
		                                        physloc.mppl_addr,
		                                        physloc.mppl_size);
		if unlikely(copy_error != 0) {
			assert(copy_error <= physloc.mppl_size);

			/* Deal with the case where the copy-error isn't total. */
			if unlikely(copy_error < physloc.mppl_size) {
				size_t ok = physloc.mppl_size - copy_error;
#ifdef LOCAL_WRITING
				/* Commit the partial write success (and limit the # of
				 * successfully  written bytes to what we were actually
				 * able to commit). */
				ok = mpart_memaddr_for_write_commit(self, offset, ok);
#endif /* LOCAL_WRITING */
				result += ok;
				/*offset += ok;*/
				num_bytes -= ok;
			}

			/* Can't use memcpy_nopf() to transfer memory from the given buffer.
			 * This can happen for 3 reasons:
			 *  - The buffer hasn't been loaded into memory
			 *  - The buffer is backed by VIO memory
			 *  - The buffer is actually invalid and represents a faulty address
			 * Assuming a well-behaved application, we can optimize performance
			 * for the first case by attempting to pre-fault the current target
			 * buffer. */
			_mpart_lock_release(self);
			unlockinfo_xunlock(unlock);
			mpart_lockops_reap(self);

#ifdef LOCAL_WRITING
#define LOCAL_prefault_flags MMAN_FAULT_F_NORMAL /* Writing from a buffer means we only need to read said buffer! */
#else /* LOCAL_WRITING */
#define LOCAL_prefault_flags MMAN_FAULT_F_WRITE /* Reading into a buffer means we must write to said buffer! */
#endif /* !LOCAL_WRITING */
#ifdef LOCAL_BUFFER_IS_IOV_BUFFER
			copy_error = mman_prefaultv(buffer, result, num_bytes,
			                            LOCAL_prefault_flags);
#else /* LOCAL_BUFFER_IS_IOV_BUFFER */
			copy_error = mman_prefault((byte_t *)buffer + result,
			                           num_bytes, LOCAL_prefault_flags);
#endif /* !LOCAL_BUFFER_IS_IOV_BUFFER */
#undef LOCAL_prefault_flags
			/* If we've managed to prefault memory, then re-attempt the direct transfer. */
			if (copy_error != 0 || result != 0)
				return result; /* Try again */
			return (size_t)-1; /* Must use buffered I/O */
		} /* if unlikely(copy_error != 0) */
	}     /* scope... */
#endif /* !LOCAL_BUFFER_TRANSFER_NOEXCEPT */

#ifdef LOCAL_WRITING
	/* Commit written data.
	 * NOTE: In this case,  `mpart_memaddr_for_write_commit()' should  always
	 *       re-return `physloc.mppl_size', but we don't actually assert this
	 *       here! */
	physloc.mppl_size = mpart_memaddr_for_write_commit(self, offset,
	                                                   physloc.mppl_size);
#endif /* LOCAL_WRITING */

	result += physloc.mppl_size;

	/* Check if there is more data for us to transfer. */
	if (num_bytes > physloc.mppl_size) {
		offset += physloc.mppl_size;
		num_bytes -= physloc.mppl_size;
		goto again_memaddr;
	}
	return result;
}


#undef LOCAL_BUFFER_TRANSFER_NOEXCEPT
#undef LOCAL_buffer_transfer_nopf
#undef LOCAL_BUFFER_IS_AIO
#undef LOCAL_BUFFER_IS_IOV_BUFFER
#undef LOCAL_BUFFER_IS_IOV_PHYSBUFFER
#undef LOCAL_ubuffer_t
#undef LOCAL_buffer_t
#undef LOCAL_mfile_vio_rw
#undef LOCAL__mpart_buffered_rw
#undef LOCAL_mpart_rw_or_unlock
#undef LOCAL_mpart_rw
#undef LOCAL_READING
#undef LOCAL_WRITING

DECL_END

#undef DEFINE_mpart_read
#undef DEFINE_mpart_write
#undef DEFINE_mpart_read_p
#undef DEFINE_mpart_write_p
#undef DEFINE_mpart_readv
#undef DEFINE_mpart_writev
#undef DEFINE_mpart_readv_p
#undef DEFINE_mpart_writev_p
