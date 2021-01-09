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
#include "mpart.c"
#define DEFINE_mpart_writev
#endif /* __INTELLISENSE__ */

#include <kernel/iovec.h>
#include <kernel/mman/mm-fault.h> /* mman_prefault(), mman_prefaultv() */
#include <kernel/vm/phys.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include <alloca.h>

#include <libvio/access.h>

DECL_BEGIN

#if defined(DEFINE_mpart_read)
#define LOCAL_READING
#define LOCAL_buffer_t           USER CHECKED void *
#define LOCAL_ubuffer_t          uintptr_t
#define LOCAL_mfile_vio_rw       mfile_vio_read
#define LOCAL_mpart_rw           mpart_read
#define LOCAL__mpart_buffered_rw _mpart_buffered_read
#define LOCAL_buffer_transfer_nopf(buffer_offset, mpart_physaddr, num_bytes) \
	vm_copyfromphys_nopf((byte_t *)buffer + (buffer_offset), mpart_physaddr, num_bytes)
#elif defined(DEFINE_mpart_write)
#define LOCAL_WRITING
#define LOCAL_buffer_t           USER CHECKED void const *
#define LOCAL_ubuffer_t          uintptr_t
#define LOCAL_mfile_vio_rw       mfile_vio_write
#define LOCAL_mpart_rw           mpart_write
#define LOCAL__mpart_buffered_rw _mpart_buffered_write
#define LOCAL_buffer_transfer_nopf(buffer_offset, mpart_physaddr, num_bytes) \
	vm_copytophys_nopf(mpart_physaddr, (byte_t const *)buffer + (buffer_offset), num_bytes)
#elif defined(DEFINE_mpart_read_p)
#define LOCAL_READING
#define LOCAL_buffer_t     physaddr_t
#define LOCAL_ubuffer_t    physaddr_t
#define LOCAL_mfile_vio_rw mfile_vio_read_p
#define LOCAL_mpart_rw     mpart_read_p
#define LOCAL_BUFFER_TRANSFER_NOEXCEPT
#define LOCAL_buffer_transfer_nopf(buffer_offset, mpart_physaddr, num_bytes) \
	vm_copyinphys(buffer + (buffer_offset), mpart_physaddr, num_bytes)
#elif defined(DEFINE_mpart_write_p)
#define LOCAL_WRITING
#define LOCAL_buffer_t     physaddr_t
#define LOCAL_ubuffer_t    physaddr_t
#define LOCAL_mfile_vio_rw mfile_vio_write_p
#define LOCAL_mpart_rw     mpart_write_p
#define LOCAL_BUFFER_TRANSFER_NOEXCEPT
#define LOCAL_buffer_transfer_nopf(buffer_offset, mpart_physaddr, num_bytes) \
	vm_copyinphys(mpart_physaddr, buffer + (buffer_offset), num_bytes)
#elif defined(DEFINE_mpart_readv)
#define LOCAL_READING
#define LOCAL_BUFFER_IS_AIO
#define LOCAL_BUFFER_IS_AIO_BUFFER
#define LOCAL_buffer_t           struct aio_buffer const *__restrict
#define LOCAL_mfile_vio_rw       mfile_vio_readv
#define LOCAL_mpart_rw           mpart_readv
#define LOCAL__mpart_buffered_rw _mpart_buffered_readv
#define LOCAL_buffer_transfer_nopf(buffer_offset, mpart_physaddr, num_bytes) \
	aio_buffer_copyfromphys_nopf(buffer, buf_offset + (buffer_offset), mpart_physaddr, num_bytes)
#elif defined(DEFINE_mpart_writev)
#define LOCAL_WRITING
#define LOCAL_BUFFER_IS_AIO
#define LOCAL_BUFFER_IS_AIO_BUFFER
#define LOCAL_buffer_t           struct aio_buffer const *__restrict
#define LOCAL_mfile_vio_rw       mfile_vio_writev
#define LOCAL_mpart_rw           mpart_writev
#define LOCAL__mpart_buffered_rw _mpart_buffered_writev
#define LOCAL_buffer_transfer_nopf(buffer_offset, mpart_physaddr, num_bytes) \
	aio_buffer_copytophys_nopf(buffer, mpart_physaddr, buf_offset + (buffer_offset), num_bytes)
#elif defined(DEFINE_mpart_readv_p)
#define LOCAL_READING
#define LOCAL_BUFFER_IS_AIO
#define LOCAL_BUFFER_IS_AIO_PBUFFER
#define LOCAL_buffer_t     struct aio_pbuffer const *__restrict
#define LOCAL_mfile_vio_rw mfile_vio_readv_p
#define LOCAL_mpart_rw     mpart_readv_p
#define LOCAL_BUFFER_TRANSFER_NOEXCEPT
#define LOCAL_buffer_transfer_nopf(buffer_offset, mpart_physaddr, num_bytes) \
	aio_pbuffer_copyfromphys(buffer, buf_offset + (buffer_offset), mpart_physaddr, num_bytes)
#elif defined(DEFINE_mpart_writev_p)
#define LOCAL_WRITING
#define LOCAL_BUFFER_IS_AIO
#define LOCAL_BUFFER_IS_AIO_PBUFFER
#define LOCAL_buffer_t     struct aio_pbuffer const *__restrict
#define LOCAL_mfile_vio_rw mfile_vio_writev_p
#define LOCAL_mpart_rw     mpart_writev_p
#define LOCAL_BUFFER_TRANSFER_NOEXCEPT
#define LOCAL_buffer_transfer_nopf(buffer_offset, mpart_physaddr, num_bytes) \
	aio_pbuffer_copytophys(buffer, mpart_physaddr, buf_offset + (buffer_offset), num_bytes)
#else /* ... */
#error "Bad configuration"
#endif /* !... */

#ifdef LOCAL__mpart_buffered_rw
PUBLIC ATTR_NOINLINE NONNULL((1)) size_t KCALL
LOCAL__mpart_buffered_rw(struct mpart *__restrict self,
                         LOCAL_buffer_t buffer,
#ifdef LOCAL_BUFFER_IS_AIO
                         size_t buf_offset,
#endif /* LOCAL_BUFFER_IS_AIO */
                         size_t num_bytes,
                         mpart_reladdr_t partrel_offset)
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
		aio_buffer_copytomem(buffer, stk_buf, buf_offset, part);
#else /* LOCAL_BUFFER_IS_AIO */
		memcpy(stk_buf, buffer, part);
#endif /* !LOCAL_BUFFER_IS_AIO */

		/* Write `stk_buf' to the file. */
		ok = mpart_write(self, stk_buf, part, partrel_offset);
#else /* LOCAL_WRITING */

		/* Read `stk_buf' from the file. */
		ok = mpart_read(self, stk_buf, part, partrel_offset);

		/* Copy data from `stk_buf' */
#ifdef LOCAL_BUFFER_IS_AIO
		aio_buffer_copyfrommem(buffer, buf_offset, stk_buf, ok);
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
		partrel_offset += ok;
		num_bytes -= ok;
	}
	return result;
}
#endif /* LOCAL__mpart_buffered_rw */

PUBLIC NONNULL((1)) size_t KCALL
LOCAL_mpart_rw(struct mpart *__restrict self,
               LOCAL_buffer_t buffer,
#ifdef LOCAL_BUFFER_IS_AIO
               size_t buf_offset,
#endif /* LOCAL_BUFFER_IS_AIO */
               size_t num_bytes,
               mpart_reladdr_t partrel_offset)
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...) {
	size_t result;
	unsigned int status;
	struct mpart_physloc physloc;
	/* Deal with VIO parts. */
	if unlikely(self->mp_state == MPART_ST_VIO) {
		REF struct mfile *file;
		mpart_lock_acquire(self);
		file = incref(self->mp_file);
		mpart_lock_release(self);
		/* Directly read to/from VIO */
		FINALLY_DECREF_UNLIKELY(file);
		/* The file may have been changed to something that doesn't support VIO
		 * This is unlikely, but can happen if the file has been anonymized! */
		if unlikely(file->mf_ops->mo_vio == NULL)
			return 0;
		LOCAL_mfile_vio_rw(file, self, buffer,
#ifdef LOCAL_BUFFER_IS_AIO
		                   buf_offset,
#endif /* LOCAL_BUFFER_IS_AIO */
		                   num_bytes,
		                   (pos_t)(self->mp_minaddr +
		                           partrel_offset));
		return num_bytes;
	}
	result = 0;

again: ATTR_UNUSED;
#ifdef LOCAL_WRITING
	/* Special case: Must also unshare copy-on-write mappings. */
	if (!LIST_EMPTY(&self->mp_copy)) {
		REF struct mfile *file;
		mpart_reladdr_t hirel;
		size_t avail;
do_unshare_cow:
		mpart_lock_acquire(self);
		file  = incref(self->mp_file);
		avail = mpart_getsize(self);
		mpart_lock_release_f(self);
		/* Diminish the overhead of unsharecow by truncating the data-part. */
		if (partrel_offset > file->mf_part_amask) {
			/* Can truncate some leading blocks. */
			REF struct mpart *hipart;
			size_t addend;
			addend = partrel_offset & ~file->mf_part_amask;
			decref_unlikely(file),
			mpart_deadnodes_reap(self);
			partrel_offset -= addend;
			hipart = mpart_split(self, addend);
			if unlikely(!hipart)
				return 0; /* Part is too small. */
			FINALLY_DECREF_UNLIKELY(hipart);
			result += LOCAL_mpart_rw(hipart, buffer,
#ifdef LOCAL_BUFFER_IS_AIO
			                         buf_offset,
#endif /* LOCAL_BUFFER_IS_AIO */
			                         num_bytes,
			                         partrel_offset);
			return result;
		}
		if (avail <= partrel_offset) {
			decref_unlikely(file);
			mpart_deadnodes_reap(self);
			return result; /* Part is too small. */
		}
		hirel = (partrel_offset + num_bytes + file->mf_part_amask) & ~file->mf_part_amask;
		decref_unlikely(file);
		if (hirel > avail) {
			/* Can truncate some trailing blocks. */
			REF struct mpart *hipart;
			xdecref(mpart_split(self, hirel));
			goto again;
		}
		/* Now load the part into the core, and ensure that
		 * copy-on-write mappings have been unshared. */
		mpart_lock_acquire_and_setcore_unsharecow(self);
	} else
#endif /* LOCAL_WRITING */
	{
		/* Lock the part and make sure that in-core data is available. */
		mpart_lock_acquire_and_setcore(self);
#ifdef LOCAL_WRITING
		/* Special case: Must also unshare copy-on-write mappings. */
		if unlikely(!LIST_EMPTY(&self->mp_copy)) {
			mpart_lock_release(self);
			goto do_unshare_cow;
		}
#endif /* LOCAL_WRITING */
	}

	/* Load the physical location of the requested segment. */
again_memaddr:
#ifdef LOCAL_WRITING
	status = mpart_memaddr_for_write(self, partrel_offset, num_bytes, &physloc);
#else /* LOCAL_WRITING */
	status = mpart_memaddr_for_read(self, partrel_offset, num_bytes, &physloc);
#endif /* !LOCAL_WRITING */
	if (status != MPART_MEMADDR_SUCCESS) {
		if (status == MPART_MEMADDR_BAD_BOUNDS)
			goto done;
		assert(status == MPART_MEMADDR_NOT_LOADED);

		/* Must initialize more backing memory.
		 * NOTE: When writing, we only initialize a single block,
		 *       so-as to take advantage of the possibility of
		 *       write whole blocks without having to load them
		 *       first! */
#ifdef LOCAL_WRITING
		physloc.mppl_size = 1;
#endif /* LOCAL_WRITING */
		mpart_memload_and_unlock(self, partrel_offset, &physloc);
		mpart_lock_acquire_and_setcore(self);

#ifdef LOCAL_WRITING
		/* Must make sure that there still aren't any copy-on-write mappings.
		 * New ones may have appeared since `mpart_memload_relock()' had to
		 * temporarily release our lock on `self' */
		if unlikely(!LIST_EMPTY(&self->mp_copy)) {
			mpart_lock_release_f(self);
			goto again;
		}
#endif /* LOCAL_WRITING */

		goto again_memaddr;
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
				 * successfully written bytes to what we were actually
				 * able to commit). */
				ok = mpart_memaddr_for_write_commit(self, partrel_offset, ok);
#endif /* LOCAL_WRITING */
				result += ok;
				partrel_offset += ok;
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
#define LOCAL_for_writing true
#else /* LOCAL_WRITING */
#define LOCAL_for_writing false
#endif /* !LOCAL_WRITING */
#ifdef LOCAL_BUFFER_IS_AIO_BUFFER
			copy_error = mman_prefaultv(buffer, result, num_bytes, LOCAL_for_writing);
#else /* LOCAL_BUFFER_IS_AIO_BUFFER */
			copy_error = mman_prefault((byte_t *)buffer + result,
			                           num_bytes, LOCAL_for_writing);
#endif /* !LOCAL_BUFFER_IS_AIO_BUFFER */
#undef LOCAL_for_writing
			/* If we've managed to prefault memory, then re-attempt the direct transfer. */
			if (copy_error != 0)
				goto again;
			/* If pre-faulting memory didn't work, then we
			 * must use an intermediate buffer for transfer */
#ifdef LOCAL_BUFFER_IS_AIO
			result += LOCAL__mpart_buffered_rw(self, buffer, buf_offset + result,
			                                   num_bytes, partrel_offset);
#else /* LOCAL_BUFFER_IS_AIO */
			result += LOCAL__mpart_buffered_rw(self, (LOCAL_buffer_t)((LOCAL_ubuffer_t)buffer + result),
			                                   num_bytes, partrel_offset);
#endif /* !LOCAL_BUFFER_IS_AIO */
			return result;
		} /* if unlikely(copy_error != 0) */
	}     /* scope... */
#endif /* !LOCAL_BUFFER_TRANSFER_NOEXCEPT */

#ifdef LOCAL_WRITING
	/* Commit written data.
	 * NOTE: In this case, `mpart_memaddr_for_write_commit()' should always
	 *       re-return `physloc.mppl_size', but we don't actually assert this
	 *       here! */
	physloc.mppl_size = mpart_memaddr_for_write_commit(self,
	                                                   partrel_offset,
	                                                   physloc.mppl_size);
#endif /* LOCAL_WRITING */

	result += physloc.mppl_size;

	/* Check if there is more data for us to transfer. */
	if (result < num_bytes) {
		partrel_offset += physloc.mppl_size;
		num_bytes -= physloc.mppl_size;
		goto again_memaddr;
	}

done:
	mpart_lock_release(self);
	return result;
}

#undef LOCAL_BUFFER_TRANSFER_NOEXCEPT
#undef LOCAL_buffer_transfer_nopf
#undef LOCAL_BUFFER_IS_AIO
#undef LOCAL_BUFFER_IS_AIO_BUFFER
#undef LOCAL_BUFFER_IS_AIO_PBUFFER
#undef LOCAL_ubuffer_t
#undef LOCAL_buffer_t
#undef LOCAL_mfile_vio_rw
#undef LOCAL__mpart_buffered_rw
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
