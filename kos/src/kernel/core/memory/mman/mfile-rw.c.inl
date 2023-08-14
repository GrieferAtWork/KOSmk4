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
#include "mfile-rw.c"
//#define       DEFINE_mfile_direct_read
//#define     DEFINE_mfile_direct_read_p
//#define      DEFINE_mfile_direct_readv
//#define    DEFINE_mfile_direct_readv_p
//#define      DEFINE_mfile_direct_write
//#define    DEFINE_mfile_direct_write_p
//#define     DEFINE_mfile_direct_writev
//#define   DEFINE_mfile_direct_writev_p
//#define DEFINE_mfile_direct_read_async
#define   DEFINE_mfile_direct_read_async_p
//#define    DEFINE_mfile_direct_readv_async
//#define  DEFINE_mfile_direct_readv_async_p
//#define    DEFINE_mfile_direct_write_async
//#define  DEFINE_mfile_direct_write_async_p
//#define   DEFINE_mfile_direct_writev_async
//#define DEFINE_mfile_direct_writev_async_p
//#define DEFINE_mfile_read
//#define       DEFINE_mfile_read_p
//#define        DEFINE_mfile_readv
//#define      DEFINE_mfile_readv_p
//#define     DEFINE_mfile_tailread
//#define   DEFINE_mfile_tailread_p
//#define    DEFINE_mfile_tailreadv
//#define  DEFINE_mfile_tailreadv_p
//#define        DEFINE_mfile_write
//#define      DEFINE_mfile_write_p
//#define       DEFINE_mfile_writev
//#define     DEFINE_mfile_writev_p
//#define    DEFINE_mfile_tailwrite
//#define  DEFINE_mfile_tailwrite_p
//#define   DEFINE_mfile_tailwritev
//#define DEFINE_mfile_tailwritev_p
#endif /* __INTELLISENSE__ */

#include <kernel/aio.h>
#include <kernel/fs/node.h>
#include <kernel/fs/notify.h>
#include <kernel/fs/super.h>
#include <kernel/iovec.h>
#include <kernel/mman/dma.h>
#include <kernel/mman/fault.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/phys.h>
#include <misc/unlockinfo.h>
#include <sched/sig.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/overflow.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>

#include <assert.h>
#include <atomic.h>
#include <stddef.h>
#include <string.h>

#include <libvio/api.h>

DECL_BEGIN

#ifndef DBG_memset
#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */
#endif /* !DBG_memset */

#if defined(DEFINE_mfile_direct_read) || defined(DEFINE_mfile_direct_read_async)
#ifdef DEFINE_mfile_direct_read_async
#define LOCAL_ASYNC
#endif /* DEFINE_mfile_direct_read_async */
#define LOCAL_DIRECT
#define LOCAL_mfile_normrw       mfile_direct_read
#define LOCAL_mfile_asyncrw      mfile_direct_read_async
#elif defined(DEFINE_mfile_direct_readv) || defined(DEFINE_mfile_direct_readv_async)
#ifdef DEFINE_mfile_direct_readv_async
#define LOCAL_ASYNC
#endif /* DEFINE_mfile_direct_readv_async */
#define LOCAL_DIRECT
#define LOCAL_BUFFER_IS_IOVEC
#define LOCAL_mfile_normrw       mfile_direct_readv
#define LOCAL_mfile_asyncrw      mfile_direct_readv_async
#elif defined(DEFINE_mfile_direct_write) || defined(DEFINE_mfile_direct_write_async)
#ifdef DEFINE_mfile_direct_write_async
#define LOCAL_ASYNC
#endif /* DEFINE_mfile_direct_write_async */
#define LOCAL_DIRECT
#define LOCAL_WRITING
#define LOCAL_mfile_normrw       mfile_direct_write
#define LOCAL_mfile_asyncrw      mfile_direct_write_async
#elif defined(DEFINE_mfile_direct_writev) || defined(DEFINE_mfile_direct_writev_async)
#ifdef DEFINE_mfile_direct_writev_async
#define LOCAL_ASYNC
#endif /* DEFINE_mfile_direct_writev_async */
#define LOCAL_DIRECT
#define LOCAL_WRITING
#define LOCAL_BUFFER_IS_IOVEC
#define LOCAL_mfile_normrw       mfile_direct_writev
#define LOCAL_mfile_asyncrw      mfile_direct_writev_async
#elif defined(DEFINE_mfile_direct_read_p) || defined(DEFINE_mfile_direct_read_async_p)
#ifdef DEFINE_mfile_direct_read_async_p
#define LOCAL_ASYNC
#endif /* DEFINE_mfile_direct_read_async_p */
#define LOCAL_DIRECT
#define LOCAL_BUFFER_IS_PHYS
#define LOCAL_mfile_normrw       mfile_direct_read_p
#define LOCAL_mfile_asyncrw      mfile_direct_read_async_p
#elif defined(DEFINE_mfile_direct_readv_p) || defined(DEFINE_mfile_direct_readv_async_p)
#ifdef DEFINE_mfile_direct_readv_async_p
#define LOCAL_ASYNC
#endif /* DEFINE_mfile_direct_readv_async_p */
#define LOCAL_DIRECT
#define LOCAL_BUFFER_IS_PHYS
#define LOCAL_BUFFER_IS_IOVEC
#define LOCAL_mfile_normrw       mfile_direct_readv_p
#define LOCAL_mfile_asyncrw      mfile_direct_readv_async_p
#elif defined(DEFINE_mfile_direct_write_p) || defined(DEFINE_mfile_direct_write_async_p)
#ifdef DEFINE_mfile_direct_write_async_p
#define LOCAL_ASYNC
#endif /* DEFINE_mfile_direct_write_async_p */
#define LOCAL_DIRECT
#define LOCAL_WRITING
#define LOCAL_BUFFER_IS_PHYS
#define LOCAL_mfile_normrw       mfile_direct_write_p
#define LOCAL_mfile_asyncrw      mfile_direct_write_async_p
#elif defined(DEFINE_mfile_direct_writev_p) || defined(DEFINE_mfile_direct_writev_async_p)
#ifdef DEFINE_mfile_direct_writev_async_p
#define LOCAL_ASYNC
#endif /* DEFINE_mfile_direct_writev_async_p */
#define LOCAL_DIRECT
#define LOCAL_WRITING
#define LOCAL_BUFFER_IS_PHYS
#define LOCAL_BUFFER_IS_IOVEC
#define LOCAL_mfile_normrw       mfile_direct_writev_p
#define LOCAL_mfile_asyncrw      mfile_direct_writev_async_p
#elif defined(DEFINE_mfile_read) || defined(DEFINE_mfile_tailread)
#ifdef DEFINE_mfile_tailread
#define LOCAL_TAILIO
#endif /* DEFINE_mfile_tailread */
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
#define LOCAL_mfile_viorw        mfile_viowrite
#define LOCAL_mfile_normrw       mfile_write
#define LOCAL_mfile_tailrw       mfile_tailwrite
#define LOCAL_mpart_rw           mpart_write
#define LOCAL_mpart_rw_or_unlock mpart_write_or_unlock
#elif defined(DEFINE_mfile_readv) || defined(DEFINE_mfile_tailreadv)
#ifdef DEFINE_mfile_tailreadv
#define LOCAL_TAILIO
#endif /* DEFINE_mfile_tailreadv */
#define LOCAL_BUFFER_IS_IOVEC
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
#define LOCAL_mfile_viorw        mfile_viowritev
#define LOCAL_mfile_normrw       mfile_writev
#define LOCAL_mfile_tailrw       mfile_tailwritev
#define LOCAL_mpart_rw           mpart_writev
#define LOCAL_mpart_rw_or_unlock mpart_writev_or_unlock
#elif defined(DEFINE_mfile_read_p) || defined(DEFINE_mfile_tailread_p)
#ifdef DEFINE_mfile_tailread_p
#define LOCAL_TAILIO
#endif /* DEFINE_mfile_tailread_p */
#define LOCAL_BUFFER_IS_PHYS
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
#define LOCAL_mfile_viorw        mfile_viowrite_p
#define LOCAL_mfile_normrw       mfile_write_p
#define LOCAL_mfile_tailrw       mfile_tailwrite_p
#define LOCAL_mpart_rw           mpart_write_p
#define LOCAL_mpart_rw_or_unlock mpart_write_or_unlock_p
#elif defined(DEFINE_mfile_readv_p) || defined(DEFINE_mfile_tailreadv_p)
#ifdef DEFINE_mfile_tailreadv_p
#define LOCAL_TAILIO
#endif /* DEFINE_mfile_tailreadv_p */
#define LOCAL_BUFFER_IS_PHYS
#define LOCAL_BUFFER_IS_IOVEC
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
#define LOCAL_mfile_viorw        mfile_viowritev_p
#define LOCAL_mfile_normrw       mfile_writev_p
#define LOCAL_mfile_tailrw       mfile_tailwritev_p
#define LOCAL_mpart_rw           mpart_writev_p
#define LOCAL_mpart_rw_or_unlock mpart_writev_or_unlock_p
#else /* ... */
#error "Bad configuration"
#endif /* !... */

#ifndef LOCAL_WRITING
#define LOCAL_READING
#endif /* !LOCAL_WRITING */

#ifdef LOCAL_ASYNC
#define LOCAL_DIRECT
#endif /* LOCAL_ASYNC */

#if defined(LOCAL_BUFFER_IS_PHYS) && defined(LOCAL_BUFFER_IS_IOVEC)
#define LOCAL_buffer_t           struct iov_physbuffer const *__restrict
#define LOCAL_buffer_ent_t       struct iov_physentry
#elif defined(LOCAL_BUFFER_IS_PHYS)
#define LOCAL_buffer_t           physaddr_t
#define LOCAL_ubuffer_t          physaddr_t
#elif defined(LOCAL_BUFFER_IS_IOVEC)
#define LOCAL_buffer_t           struct iov_buffer const *__restrict
#define LOCAL_buffer_ent_t       struct iov_entry
#elif defined(LOCAL_WRITING)
#define LOCAL_buffer_t           NCX void const *
#define LOCAL_ubuffer_t          uintptr_t
#else /* ... */
#define LOCAL_buffer_t           NCX void *
#define LOCAL_ubuffer_t          uintptr_t
#endif /* !... */

#if defined(LOCAL_DIRECT) && defined(LOCAL_ASYNC)
#define LOCAL_mfile_rw LOCAL_mfile_asyncrw
#elif defined(LOCAL_TAILIO)
#define LOCAL_mfile_rw LOCAL_mfile_tailrw
#else /* ... */
#define LOCAL_mfile_rw LOCAL_mfile_normrw
#endif /* !... */

#ifdef LOCAL_BUFFER_IS_IOVEC
#define LOCAL_buffer_advance(count) (buf_offset += (count))
#else /* LOCAL_BUFFER_IS_IOVEC */
#define LOCAL_buffer_advance(count) (buffer = (LOCAL_buffer_t)((LOCAL_ubuffer_t)buffer + (count)))
#endif /* !LOCAL_BUFFER_IS_IOVEC */


#if defined(LOCAL_DIRECT) && defined(LOCAL_ASYNC) && !defined(LOCAL_BUFFER_IS_PHYS)
#ifdef LOCAL_WRITING
#define LOCAL_dma_callback mfile_dma_write_cb
#ifndef __mfile_dma_write_cb_defined
#define __mfile_dma_write_cb_defined
#define LOCAL_WANT_dma_callback
#endif /* !__mfile_dma_write_cb_defined */
#else /* LOCAL_WRITING */
#define LOCAL_dma_callback mfile_dma_read_cb
#ifndef __mfile_dma_read_cb_defined
#define __mfile_dma_read_cb_defined
#define LOCAL_WANT_dma_callback
#endif /* !__mfile_dma_read_cb_defined */
#endif /* !LOCAL_WRITING */
#ifndef __mfile_dma_info_defined
#define __mfile_dma_info_defined
struct mfile_dma_info {
	struct mfile            *mdi_fil; /* [1..1][const] The file on which to perform I/O. */
	struct aio_multihandle  *mdi_aio; /* [1..1][const] AIO controller. */
	struct refcountable     *mdi_msc; /* [0..1][const] Misc inner object to store alongside AIO handles. */
	size_t                   mdi_iob; /* [in|out] Sum of bytes for which I/O was initiated */
	pos_t                    mdi_pos; /* [in|out] File position of next segment */
};
#endif /* !__mfile_dma_info_defined */

#ifdef LOCAL_WRITING
#define LOCAL_mfile_direct_io_async_p mfile_direct_write_async_p
#else /* LOCAL_WRITING */
#define LOCAL_mfile_direct_io_async_p mfile_direct_read_async_p
#endif /* !LOCAL_WRITING */

#ifdef LOCAL_WANT_dma_callback
#undef LOCAL_WANT_dma_callback
PRIVATE NONNULL((1, 4)) ssize_t KCALL
LOCAL_dma_callback(void *cookie, physaddr_t paddr, size_t num_bytes,
                   /*inherit(always)*/ mdma_lock_t lock) {
	size_t result;
	struct mfile_dma_info *info;
	struct refcountable_dmalock *rlck;
	info = (struct mfile_dma_info *)cookie;
	rlck = (struct refcountable_dmalock *)info->mdi_aio->am_obj;

	/* If necessary, construct a new DMA lock controller for `lock' */
	if (rlck == NULL || rlck->rld_lock != lock) {
		REF struct refcountable_dmalock *newlock;
		newlock = refcountable_dmalock_new(lock, info->mdi_msc);
		xdecref(rlck);
		info->mdi_aio->am_obj = newlock;
	} else {
		/* Existing lock can be re-used (but must still inherit `lock') */
		mdma_lock_release_nokill(lock);
	}

	/* Do I/O. When this creates new AIO handles, those handles
	 * will hold references to the currently relevant DMA lock. */
	result = LOCAL_mfile_direct_io_async_p(info->mdi_fil, paddr, num_bytes,
	                                       info->mdi_pos, info->mdi_aio);

	/* Account for the amount of I/O performed. */
	info->mdi_iob += result;
	if (result < num_bytes)
		return -1; /* Incomplete I/O count (stop trying to advance further into the file) */

	/* Advance further into the file. */
	info->mdi_pos += result;
	return 0;
}
#endif /* LOCAL_WANT_dma_callback */

#undef LOCAL_mfile_direct_io_async_p
#endif /* LOCAL_DIRECT && LOCAL_ASYNC && !LOCAL_BUFFER_IS_PHYS */



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
#ifdef LOCAL_ASYNC
               ,
               struct aio_multihandle *__restrict aio
#endif /* LOCAL_ASYNC */
               )
#ifdef LOCAL_DIRECT
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...)
#else /* LOCAL_DIRECT */
		THROWS(E_WOULDBLOCK, E_BADALLOC, E_SEGFAULT, ...)
#endif /* !LOCAL_DIRECT */
{
#if defined(LOCAL_READING) && defined(LOCAL_TAILIO)
	size_t result;
again:
#ifdef LOCAL_BUFFER_IS_IOVEC
	result = LOCAL_mfile_normrw(self, buffer, buf_offset, num_bytes, offset);
#else /* LOCAL_BUFFER_IS_IOVEC */
	result = LOCAL_mfile_normrw(self, buffer, num_bytes, offset);
#endif /* !LOCAL_BUFFER_IS_IOVEC */
	if (result == 0 && !mfile_isanon(self) && num_bytes != 0) {
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
#elif defined(LOCAL_DIRECT) && !defined(LOCAL_ASYNC)
	size_t result;
	struct aio_multihandle_generic hand;
	aio_multihandle_generic_init(&hand);
	TRY {
		/* Do async IO */
#ifdef LOCAL_BUFFER_IS_IOVEC
		result = LOCAL_mfile_asyncrw(self, buffer, buf_offset, num_bytes, offset, &hand);
#else /* LOCAL_BUFFER_IS_IOVEC */
		result = LOCAL_mfile_asyncrw(self, buffer, num_bytes, offset, &hand);
#endif /* !LOCAL_BUFFER_IS_IOVEC */
		aio_multihandle_done(&hand);
	} EXCEPT {
		aio_multihandle_fail(&hand);
		result = 0; /* Silence warnings... */
	}

	/* Wait for AIO completion. */
	RAII_FINALLY { aio_multihandle_generic_fini(&hand); };
	aio_multihandle_generic_waitfor(&hand);
	aio_multihandle_generic_checkerror(&hand);
	return result;
#elif defined(LOCAL_DIRECT) && defined(LOCAL_ASYNC) && !defined(LOCAL_BUFFER_IS_PHYS)
#ifdef LOCAL_READING
#define LOCAL_DMA_FLAGS MMAN_FAULT_F_WRITE /* read-from-file / WRITE-to-buffer */
#else /* LOCAL_READING */
#define LOCAL_DMA_FLAGS 0                  /* write-to-file / READ-from-buffer */
#endif /* !LOCAL_READING */
	struct mfile_dma_info info;
	info.mdi_fil = self;
	info.mdi_aio = aio;
	info.mdi_msc = aio->am_obj;
	info.mdi_iob = 0;
	info.mdi_pos = offset;
	aio->am_obj  = NULL;
	RAII_FINALLY {
		/* Release buffered AIO lock and restore old misc-object. */
		if (aio->am_obj) {
			assert(aio->am_obj->rca_destroy == &refcountable_dmalock_destroy);
			decref(aio->am_obj);
		}
		aio->am_obj = info.mdi_msc;
	};

	/* Enumerate DMA ranges and initiate I/O */
#ifdef LOCAL_BUFFER_IS_IOVEC
	mman_dmav(&LOCAL_dma_callback, &info, buffer, buf_offset, num_bytes, LOCAL_DMA_FLAGS);
#else /* LOCAL_BUFFER_IS_IOVEC */
	mman_dma(&LOCAL_dma_callback, &info, (void *)buffer, num_bytes, LOCAL_DMA_FLAGS);
#endif /* !LOCAL_BUFFER_IS_IOVEC */

	/* Return the total # of bytes for which I/O was performed. */
	return info.mdi_iob;
#undef LOCAL_DMA_FLAGS
#elif defined(LOCAL_DIRECT) && defined(LOCAL_ASYNC) && defined(LOCAL_BUFFER_IS_PHYS)
	REF struct refcountable *unlock_cookie;
	REF struct refcountable *saved_aio_obj;
	size_t result;
	shift_t blockshift = self->mf_blockshift;
	size_t io_bytes;
#ifdef LOCAL_WRITING
#define LOCAL_direct_io_operator(file) ((file)->mf_ops->mo_saveblocks)
#else /* LOCAL_WRITING */
#define LOCAL_direct_io_operator(file) ((file)->mf_ops->mo_loadblocks)
#endif /* !LOCAL_WRITING */

	/* Validate alignment of file position and buffer size. */
	if unlikely(offset != ((offset >> blockshift) << blockshift)) {
		THROW(E_INVALID_ARGUMENT_BAD_ALIGNMENT,
		      E_INVALID_ARGUMENT_CONTEXT_O_DIRECT_BADPOS,
		      (uintptr_t)offset, ((size_t)1 << blockshift) - 1);
	}
	if unlikely(num_bytes != ((num_bytes >> blockshift) << blockshift)) {
		THROW(E_INVALID_ARGUMENT_BAD_ALIGNMENT,
		      E_INVALID_ARGUMENT_CONTEXT_O_DIRECT_BADSIZ,
		      num_bytes, ((size_t)1 << blockshift) - 1);
	}

	/* Also validate alignment of buffers (which uses a different shift) */
	{
		shift_t ioba_shift = self->mf_iobashift;
#ifdef LOCAL_BUFFER_IS_IOVEC
		LOCAL_buffer_ent_t ent;
		size_t temp_offset = buf_offset;
		size_t temp_bytes  = num_bytes;
		pos_t temp_fpos    = offset;
		IOV_PHYSBUFFER_FOREACH_N(ent, buffer)
#endif /* LOCAL_BUFFER_IS_IOVEC */
		{
			physaddr_t bufaddr;
#ifdef LOCAL_READING
			size_t bufsize;
#endif /* LOCAL_READING */
#ifdef LOCAL_BUFFER_IS_IOVEC
			if (temp_offset) {
				if (temp_offset >= ent.ive_size) {
					temp_offset -= ent.ive_size;
					continue;
				}
				ent.ive_base += temp_offset;
				ent.ive_size -= temp_offset;
				temp_offset = 0;
			}
			if (ent.ive_size > temp_bytes)
				ent.ive_size = temp_bytes;

			/* Validate buffer size / file position at this location. */
			if unlikely(temp_fpos != ((temp_fpos >> blockshift) << blockshift)) {
				THROW(E_INVALID_ARGUMENT_BAD_ALIGNMENT,
				      E_INVALID_ARGUMENT_CONTEXT_O_DIRECT_BADPOS,
				      (uintptr_t)temp_fpos, ((size_t)1 << blockshift) - 1);
			}
			if unlikely(ent.ive_size != ((ent.ive_size >> blockshift) << blockshift)) {
				THROW(E_INVALID_ARGUMENT_BAD_ALIGNMENT,
				      E_INVALID_ARGUMENT_CONTEXT_O_DIRECT_BADSIZ,
				      ent.ive_size, ((size_t)1 << blockshift) - 1);
			}

			bufaddr = ent.ive_base;
#ifdef LOCAL_READING
			bufsize = ent.ive_size;
#endif /* LOCAL_READING */
#else /* LOCAL_BUFFER_IS_IOVEC */
			bufaddr = buffer;
#ifdef LOCAL_READING
			bufsize = num_bytes;
#endif /* LOCAL_READING */
#endif /* !LOCAL_BUFFER_IS_IOVEC */

			/* Validate buffer address. */
			if (bufaddr != ((bufaddr >> ioba_shift) << ioba_shift)) {
				/* NOTE: It's OK if  this ends up  leaking physical memory  addresses
				 *       into user-space (I think). Aside from possibly some unwanted
				 *       introspection on system state, I can't think of any way this
				 *       could be used by a malicious program. */
				THROW(E_INVALID_ARGUMENT_BAD_ALIGNMENT,
				      E_INVALID_ARGUMENT_CONTEXT_O_DIRECT_BADBUF,
				      (uintptr_t)bufaddr, ((size_t)1 << ioba_shift) - 1);
			}

			/* When loading blocks, allocator  functions are allowed to  assume
			 * that the state of `page_iszero()' can be trusted (as is normally
			 * the case since `mo_loadblocks' is  mainly used to populated  ram
			 * that has been freshly allocated)
			 *
			 * However, to prevent `mo_loadblocks' from skipping any blocks that
			 * used to be zero'd, but no longer are, we must manually clear  the
			 * page-frame allocator's idea of  zero-pages for the address  range
			 * we're trying to initialize. */
#ifdef LOCAL_READING
			bufsize += (size_t)(bufaddr & PAGEMASK);
			bufaddr >>= PAGESHIFT;
			bufaddr += PAGEMASK;
			bufsize >>= PAGESHIFT;
			page_resetzero((physpage_t)bufaddr, (physpagecnt_t)bufsize);
#endif /* LOCAL_READING */

#ifdef LOCAL_BUFFER_IS_IOVEC
			if (ent.ive_size >= temp_bytes)
				break;
			temp_bytes -= ent.ive_size;
			temp_fpos += ent.ive_size;
#endif /* LOCAL_BUFFER_IS_IOVEC */
		}
	}

	/* Special handling for ramfs-style files
	 * In this case we simply forward the request to the non-direct operators. */
	if unlikely(self->mf_flags & MFILE_F_PERSISTENT) {
#if defined(LOCAL_WRITING) && defined(LOCAL_BUFFER_IS_IOVEC)
		return mfile_writev_p(self, buffer, buf_offset, num_bytes, offset);
#elif defined(LOCAL_WRITING) && !defined(LOCAL_BUFFER_IS_IOVEC)
		return mfile_write_p(self, buffer, num_bytes, offset);
#elif defined(LOCAL_READING) && defined(LOCAL_BUFFER_IS_IOVEC)
		return mfile_readv_p(self, buffer, buf_offset, num_bytes, offset);
#elif defined(LOCAL_READING) && !defined(LOCAL_BUFFER_IS_IOVEC)
		return mfile_read_p(self, buffer, num_bytes, offset);
#else /* ... */
#error "Invalid configuration"
#endif /* !... */
	}

	/* Check if direct I/O of this kind is even possible. */
	if unlikely(!LOCAL_direct_io_operator(self)) {
#ifdef LOCAL_WRITING
		THROW(E_FSERROR_READONLY);
#else /* LOCAL_WRITING */
		return 0;
#endif /* !LOCAL_WRITING */
	}

	/* Initialize the unlock-cookie, and make sure */
	unlock_cookie = NULL;
again_direct_io_lockfile:
	TRY {
		mfile_lock_read(self);

		/* Check if the file has been deleted (or is read-only). */
#ifdef LOCAL_WRITING
		if unlikely(self->mf_flags & (MFILE_F_DELETED | MFILE_F_READONLY))
#else /* LOCAL_WRITING */
		if unlikely(self->mf_flags & (MFILE_F_DELETED))
#endif /* !LOCAL_WRITING */
		{
			mfile_lock_endread(self);
#ifdef LOCAL_WRITING
			THROW(E_FSERROR_READONLY);
#else /* LOCAL_WRITING */
			if (unlock_cookie != NULL)
				mfile_trunclock_dec_object_destroy_without_unlock(unlock_cookie);
			return 0;
#endif /* !LOCAL_WRITING */
		}

#ifdef LOCAL_WRITING
		if (!(self->mf_flags & MFILE_F_FIXEDFILESIZE)) {
			/* If necessary, increase file size.
			 * NOTE: Even if the write below fails, we don't decrease the
			 *       file size (since that would require additional locks
			 *       and can't be done safely because the new size  would
			 *       have already been globally visible)
			 * Also: The only reason anything below might fail is a hardware
			 *       failure, or an interrupt, both of which are allowed  to
			 *       leave the file in a state where data has been partially
			 *       written.
			 * NOTE: Only increase the file size when `num_bytes != 0' */
			uintptr_t changes;
			pos_t old_filesize, new_filesize;
			pos_t max_file_size = (pos_t)-1;
			if (mfile_isnode(self))
				max_file_size = mfile_asnode(self)->fn_super->fs_feat.sf_filesize_max;
			if (OVERFLOW_USUB(max_file_size, offset, &result)) {
#if __SIZEOF_POS_T__ < __SIZEOF_SIZE_T__
				if (offset < max_file_size) {
					result = (size_t)-1;
				} else
#endif /* __SIZEOF_POS_T__ < __SIZEOF_SIZE_T__ */
				{
					mfile_lock_endread(self);
					THROW(E_FSERROR_FILE_TOO_BIG);
				}
			}
			if (result >= num_bytes) {
				result   = num_bytes;
				io_bytes = num_bytes;
			} else {
				/* Because `sf_filesize_max' may not be block-aligned, but align `result' now. */
				io_bytes = CEIL_ALIGN(result, (size_t)1 << blockshift);
				assertf(io_bytes <= num_bytes,
				        "Because `num_bytes' was asserted to be block-"
				        "aligned, this should continue to hold true");
			}

			changes      = 0;
			new_filesize = offset + result;
again_read_old_filesize:
			old_filesize = mfile_getsize(self);
			if (new_filesize > old_filesize) {
				/* Increase file size. */
				if (!atomic64_cmpxch_weak(&self->mf_filesize,
				                          (uint64_t)old_filesize,
				                          (uint64_t)new_filesize))
					goto again_read_old_filesize;
				changes |= MFILE_F_ATTRCHANGED;
			}
			mfile_trunclock_inc(self);
			mfile_lock_endread(self);

			/* Update the last-modified timestamp (if necessary) */
			if (!(self->mf_flags & MFILE_F_NOMTIME)) {
				struct timespec now = realtime();
				mfile_tslock_acquire(self);
				COMPILER_READ_BARRIER();
				if (!(self->mf_flags & (MFILE_F_NOMTIME | MFILE_F_DELETED))) {
					self->mf_mtime = now;
					self->mf_ctime = now;
					changes |= MFILE_F_ATTRCHANGED;
				}
				mfile_tslock_release(self);
			}

			/* (possibly) mark file attributes as having changed. */
			if (changes != 0) {
				mfile_changed(self, changes);
				mfile_inotify_modified(self); /* Post `IN_MODIFY' */
			}
		} else
#endif /* LOCAL_WRITING */
		{
			/* Do I/O within allocated file bounds. */
			pos_t filesize = mfile_getsize(self);
			if (OVERFLOW_USUB(filesize, offset, &result)) {
				result = 0;
#if __SIZEOF_POS_T__ > __SIZEOF_SIZE_T__
				if (filesize > offset) {
					result = (size_t)-1;
				} else
#endif /* __SIZEOF_POS_T__ > __SIZEOF_SIZE_T__ */
				{
#ifdef LOCAL_WRITING
					mfile_lock_endread(self);
					THROW(E_FSERROR_FILE_TOO_BIG);
#endif /* LOCAL_WRITING */
				}
			}
			if (result > num_bytes)
				result = num_bytes;

			/* Figure out how much I/O we're allowed to perform. */
			io_bytes = CEIL_ALIGN(result, (size_t)1 << blockshift);
			assertf(io_bytes <= num_bytes, "Must be the case because `num_bytes' is block-aligned");

			/* Prevent the file's size from being lowered. */
			mfile_trunclock_inc(self);
			mfile_lock_endread(self);
		}
	} EXCEPT {
		if (unlock_cookie != NULL)
			mfile_trunclock_dec_object_destroy_without_unlock(unlock_cookie);
		RETHROW();
	}

	/* NOTE: At this point:
	 * >> result <= io_bytes <= num_bytes
	 * - result:    how much I/O we want to indicate to the caller (as
	 *              limited by the file's  size during reads, and  the
	 *              file's max possible size during writes)
	 * - io_bytes:  the ceil-block-aligned value of `result'
	 * - num_bytes: the block-aligned count for how much I/O the caller
	 *              wanted us to do. */

	/* Always release the trunc-lock once we're done, but only do
	 * so once all AIO has completed! */
	if (!mfile_create_trunclock_dec_or_unlock(self, &unlock_cookie, aio->am_obj))
		goto again_direct_io_lockfile;

	/* Store a reference to the unlock-cookie in the AIO-controller.
	 * When sub-handles are created, those sub-handles will each get
	 * a reference to `unlock_cookie'
	 *
	 * Once we're done here, restore the original AIO-object. */
	saved_aio_obj = aio->am_obj;   /* Inherit reference */
	aio->am_obj   = unlock_cookie; /* Inherit reference */
	RAII_FINALLY {
		assert(aio->am_obj == unlock_cookie);
		aio->am_obj = saved_aio_obj;    /* Inherit reference (x2) */
		decref_unlikely(unlock_cookie); /* Drop reference inherited in previous line */
	};

	/* Actually do I/O */
#ifndef LOCAL_BUFFER_IS_IOVEC
	if likely(io_bytes != 0)
		(*LOCAL_direct_io_operator(self))(self, offset, buffer, io_bytes, aio);
#else /* !LOCAL_BUFFER_IS_IOVEC */
	{
		LOCAL_buffer_ent_t ent;
		IOV_PHYSBUFFER_FOREACH_N(ent, buffer) {
			if (buf_offset) {
				if (buf_offset >= ent.ive_size) {
					buf_offset -= ent.ive_size;
					continue;
				}
				ent.ive_base += buf_offset;
				ent.ive_size -= buf_offset;
				buf_offset = 0;
			}
			if (ent.ive_size > io_bytes)
				ent.ive_size = io_bytes;

			/* Must explicitly skip empty entries (load/save-blocks assumes non-empty requests) */
			if likely(ent.ive_size != 0)
				(*LOCAL_direct_io_operator(self))(self, offset, ent.ive_base, ent.ive_size, aio);
			if (ent.ive_size >= io_bytes)
				break;
			io_bytes -= ent.ive_size;
			offset += ent.ive_size;
		}
	}
#endif /* LOCAL_BUFFER_IS_IOVEC */
#undef LOCAL_direct_io_operator
	return result;
#else /* ... */
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
#ifdef LIBVIO_CONFIG_ENABLED
		/* Even when a file is anonymous, we're allowed to dispatch through  VIO,
		 * so-long as the file isn't deleted and access happens within the file's
		 * bounds (which we're not allowed to increase in the case of a write). */
		if (self->mf_ops->mo_vio && !(self->mf_flags & MFILE_F_DELETED)) {
			filesize = mfile_getsize(self);
			if (OVERFLOW_USUB(filesize, offset, &io_bytes)) {
#if __SIZEOF_POS_T__ > __SIZEOF_SIZE_T__
				if (offset < filesize) {
					io_bytes = (size_t)-1;
				} else
#endif /* __SIZEOF_POS_T__ > __SIZEOF_SIZE_T__ */
				{
					goto dont_handle_vio;
				}
			}

			/* Acquire a trunc-lock so the file's size can't be decreased. */
			mfile_trunclock_inc(self);
			mfile_lock_endread(self);
			RAII_FINALLY { mfile_trunclock_dec(self); };

			/* Dispatch VIO */
			if (io_bytes > num_bytes)
				io_bytes = num_bytes;
#ifdef LOCAL_BUFFER_IS_IOVEC
			LOCAL_mfile_viorw(self, buffer, buf_offset, io_bytes, offset);
#else /* LOCAL_BUFFER_IS_IOVEC */
			LOCAL_mfile_viorw(self, buffer, io_bytes, offset);
#endif /* !LOCAL_BUFFER_IS_IOVEC */

			result += io_bytes;
		} else
dont_handle_vio:
#endif /* LIBVIO_CONFIG_ENABLED */
		{
			mfile_lock_endread(self);
		}

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
		newpart_minaddr = mfile_partaddr_flooralign(self, newpart_minaddr);
		newpart_maxaddr = mfile_partaddr_ceilalign(self, newpart_maxaddr + 1) - 1;
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
			mpart_destroy(part);
			RETHROW();
		}

		/* Verify that nothing's changed in the mean time. */
		if unlikely(mfile_isanon(self)) {
destroy_new_part_and_try_again:
			mfile_lock_endwrite(self);
			LIST_ENTRY_UNBOUND_INIT(&part->mp_allparts);
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

		/* Don't write more than what can fit within the fs-specific disk limits. */
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
	newpart_minaddr = mfile_partaddr_flooralign(self, newpart_minaddr);
	if unlikely(OVERFLOW_UADD(newpart_maxaddr + 1, self->mf_part_amask, &newpart_maxaddr))
		newpart_maxaddr = 0; /* Results in (pos_t)-1 after the `&=' and `-=' below */
	newpart_maxaddr &= ~(pos_t)self->mf_part_amask;
	newpart_maxaddr -= 1;
	assert(newpart_minaddr <= newpart_maxaddr);

	/* Because  the max-valid  end address  of the  last allocated mem-part
	 * of any file is that file's size `mfile_partaddr_ceilalign()'d, there
	 * is the possibility that there  is a pre-existing part that  includes
	 * storage for those  last, few  bytes that have  already been  loaded,
	 * even though they're not considered to  be apart of the file  itself.
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
		 * that  a file's size doesn't change for some period of time.
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
		if (atomic_read(&self->mf_trunclock) != 0) {
			mfile_lock_endwrite(self);
			decref_unlikely(part);
			task_connect(&self->mf_initdone);
			if unlikely(atomic_read(&self->mf_trunclock) == 0) {
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
					old_flags = atomic_fetchor(&self->mf_flags, MFILE_F_ATTRCHANGED);
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

	/* Because  we're about to increase the file's size, there can't possibly
	 * be another pre-existing mem-part beyond `newpart_minaddr'. The special
	 * case for a part overlapping with the trailing page was already handled
	 * above! */
	assert(!mpart_tree_rlocate(self->mf_parts, newpart_minaddr, newpart_maxaddr));

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
		old_part_size = mfile_partsize_ceilalign(self, old_part_size);

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
		if (atomic_read(&self->mf_trunclock) != 0) {
			mpart_truncate_undo(self, part, old_part_size);
			task_connect(&self->mf_initdone);
			if unlikely(atomic_read(&self->mf_trunclock) == 0) {
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
			old_flags = atomic_fetchor(&self->mf_flags, MFILE_F_ATTRCHANGED);
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

#ifdef LOCAL_BUFFER_IS_IOVEC
#ifdef LOCAL_BUFFER_IS_PHYS
#define LOCAL_BUFFER_copy2phys(dstaddr, src_offset, copy_bytes) iov_physbuffer_copytophys(buffer, dstaddr, buf_offset + (src_offset), copy_bytes)
#else /* LOCAL_BUFFER_IS_PHYS */
#define LOCAL_BUFFER_copy2phys(dstaddr, src_offset, copy_bytes) iov_buffer_copytophys(buffer, dstaddr, buf_offset + (src_offset), copy_bytes)
#endif /* !LOCAL_BUFFER_IS_PHYS */
#else /* LOCAL_BUFFER_IS_IOVEC */
#ifdef LOCAL_BUFFER_IS_PHYS
#define LOCAL_BUFFER_copy2phys(dstaddr, src_offset, copy_bytes) copyinphys(dstaddr, buffer + (src_offset), copy_bytes)
#else /* LOCAL_BUFFER_IS_PHYS */
#define LOCAL_BUFFER_copy2phys(dstaddr, src_offset, copy_bytes) copytophys(dstaddr, (byte_t *)buffer + (src_offset), copy_bytes)
#endif /* !LOCAL_BUFFER_IS_PHYS */
#endif /* !LOCAL_BUFFER_IS_IOVEC */

	/* Must create a new part for the accessed address range, and directly write to said
	 * part. Afterwards, try to  insert this new  part into the  file, and increase  the
	 * file's size. (do this using `mfile_insert_and_merge_part_and_unlock()').
	 *
	 * However,  if this part fails (i.e. `NULL' is returned), then we must not immediately
	 * discard the part if the caller-given buffer  is located in virtual memory, but  must
	 * instead using its backing physical memory as a new physical source buffer from which
	 * to copy data to-be written  to the file. (this way,  we can prevent duplicate  reads
	 * from VIO memory when this kind of memory was used as origin buffer) */
	{
		/*
		 * ```
		 *            parthead_disk
		 *            │    parthead_size
		 *            │    │           parttail_disk
		 *            │    │           │    parttail_size
		 *            v    │           v    │
		 *            [--] v           [--] v
		 *            [----]           [----]
		 *  PART: [???DDDD00***********DDDD00???]
		 *            ^     ^          ^
		 *            │     │          │
		 *            │     │          parttail_base
		 *            │     content_base
		 *            parthead_base
		 * ```
		 *
		 * Also: Both the parthead and parttail regions
		 *       may overlap  with  the  content  area! */

		mpart_reladdr_t content_base;
		mpart_reladdr_t parthead_base, parttail_base;
		mpart_reladdr_t parthead_size, parttail_size;
		mpart_reladdr_t parthead_disk, parttail_disk;
		pos_t parthead_pos, parttail_pos;
		size_t changed_minblk, changed_maxblk;

		/* Figure out how much memory must be loaded from disk due to an unaligned write. */
		content_base = (mpart_reladdr_t)(offset - newpart_minaddr);
		assert(content_base <= self->mf_part_amask);
		changed_minblk = (content_base) >> self->mf_blockshift;
		changed_maxblk = (content_base + num_bytes - 1) >> self->mf_blockshift;
		assert(changed_minblk <= changed_maxblk);
		parthead_base = changed_minblk << self->mf_blockshift;
		assert(content_base >= parthead_base);
		parthead_size = content_base - parthead_base;
		parthead_size = CEIL_ALIGN(parthead_size, mfile_getblocksize(self));
		assert(parthead_size == 0 || parthead_size == mfile_getblocksize(self));
		parttail_base = content_base + num_bytes;
		parttail_base = FLOOR_ALIGN(parttail_base, mfile_getblocksize(self));
		assert(((changed_maxblk + 1) << self->mf_blockshift) >= parttail_base);
		parttail_size = ((changed_maxblk + 1) << self->mf_blockshift) - parttail_base;
		assert(parttail_size == 0 || parttail_size == mfile_getblocksize(self));
		parthead_pos = newpart_minaddr + parthead_base;
		parttail_pos = newpart_minaddr + parttail_base;
		if (OVERFLOW_USUB(filesize, parthead_pos, &parthead_disk))
			parthead_disk = 0;
		if (OVERFLOW_USUB(filesize, parttail_pos, &parttail_disk))
			parttail_disk = 0;
		parthead_disk = CEIL_ALIGN(parthead_disk, mfile_getblocksize(self));
		parttail_disk = CEIL_ALIGN(parttail_disk, mfile_getblocksize(self));
		if (parthead_disk > parthead_size)
			parthead_disk = parthead_size;
		if (parttail_disk > parttail_size)
			parttail_disk = parttail_size;
		assert(parthead_disk == 0 || parthead_disk == mfile_getblocksize(self));
		assert(parttail_disk == 0 || parttail_disk == mfile_getblocksize(self));

		/* If there is any unaligned block access to already-allocated
		 * parts of the file, then we need a trunc lock to prevent the
		 * file's size from being lowered beyond the area of the parts
		 * which we need to load from disk. */
		if (parthead_disk || parttail_disk)
			mfile_trunclock_inc(self);
		mfile_lock_end(self);
		TRY {

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

			TRY {
				/* Make sure that the part has been allocated. Afterwards, copy the
				 * caller-provided buffer into the correct offset within the  part.
				 *
				 * Note that since we're not holding any locks while doing this, we
				 * don't even have to take any care of prefaulting and/or VIO. - We
				 * can simply access memory directly! */
				if (!MPART_ST_INCORE(part->mp_state))
					mpart_ll_allocmem(part, mpart_getsize(part) >> PAGESHIFT);

				if (parthead_disk || parttail_disk) {
					/* Complicated case: have to load a portion of the new part from disk.
					 * - Load partially written to block from disk
					 * - bzero memory that is beyond the file's size and also isn't written to
					 * - Copy memory from the user's buffer (ala~ LOCAL_BUFFER_copy2phys) */


					/* Check for special case: the  write is so small that the entire
					 *                         part needs to be pre-loaded from disk.
					 * In  this case, head/tail  areas either touch  of overlap, and as
					 * such can (read: need) to be loaded simultaneously. Without  this
					 * special handling, the `mpart_ll_bzeromemcc()' of the normal case
					 * below  would clear out the memory we painfully loaded from disk. */
					if (parthead_base + parthead_disk >= parttail_base) {
						size_t loadsize;
						/* The leading/trailing blocks that need to be loaded from disk overlap. */
						loadsize = (size_t)((parttail_base + parttail_disk) - parthead_base);
						assert(mpart_getsize(part) >= loadsize);
						mpart_ll_populate(part, parthead_base, loadsize);
						/* Potentially have to bzero some remaining portion of the tail. */
						if (parttail_size > parttail_disk) {
							mpart_ll_bzeromemcc(part,
							                    parthead_base + loadsize,
							                    parttail_size - parttail_disk);
						}
					} else {
						/* Need to load leading/trailing blocks. */
						if (parthead_disk != 0)
							mpart_ll_populate(part, parthead_base, parthead_disk);
						if (parttail_disk != 0)
							mpart_ll_populate(part, parttail_base, parttail_disk);
						/* Must bzero any difference between disk load and actual allocation. */
						if (parthead_size > parthead_disk)
							mpart_ll_bzeromemcc(part, parthead_base + parthead_disk, parthead_size - parthead_disk);
						if (parttail_size > parttail_disk)
							mpart_ll_bzeromemcc(part, parttail_base + parttail_disk, parttail_size - parttail_disk);
					}
				} else {
					/* No  unaligned part of  the file needs to  be loaded fro disk.
					 * This can  happen when  doing an  unaligned write  beyond  the
					 * previously allocated bounds of the  file, and can be  handled
					 * much simpler since it doesn't require complicated calculation
					 * of file blocks. (All unaligned data is just bzero'd)
					 *
					 * In this case we can also further optimize which regions we do
					 * actually zero-fill, since we don't  have to worry about  file
					 * alignments! */
					mpart_reladdr_t content_end, parttail_end;
					if (parthead_base < content_base)
						mpart_ll_bzeromemcc(part, parthead_base, content_base - parthead_base);
					content_end  = content_base + num_bytes;
					parttail_end = parttail_base + parttail_size;
					if (parttail_end > content_end)
						mpart_ll_bzeromemcc(part, content_end, (size_t)(parttail_end - content_end));
				}

				/* Finally, write memory from the actual user-buffer into the part. */
				if (part->mp_state == MPART_ST_MEM) {
					physaddr_t dst = physpage2addr(part->mp_mem.mc_start);
					LOCAL_BUFFER_copy2phys(dst + content_base, 0, num_bytes);
				} else {
					size_t i;
					mpart_reladdr_t src_offset = 0;
					size_t src_bytes = num_bytes;
					size_t skip = content_base;
					assert(part->mp_state == MPART_ST_MEM_SC);
					/* Copy memory from the caller's buffer into the chunk-vector. */
					for (i = 0;; ++i) {
						struct mchunk chunk;
						physaddr_t chunk_addr;
						size_t chunk_size;
						assert(i < part->mp_mem_sc.ms_c);
						chunk      = part->mp_mem_sc.ms_v[i];
						chunk_size = chunk.mc_size << PAGESHIFT;
						if (skip >= chunk_size) {
							skip -= chunk_size;
							continue;
						}
						chunk_addr = physpage2addr(chunk.mc_start);
						chunk_addr += skip;
						chunk_size -= skip;
						skip = 0;
						if (src_bytes <= chunk_size) {
							LOCAL_BUFFER_copy2phys(chunk_addr, src_offset, src_bytes);
							break;
						}
						LOCAL_BUFFER_copy2phys(chunk_addr, src_offset, chunk_size);
						src_bytes -= chunk_size;
						src_offset += chunk_size;
					}
				}

				/* Mark all blocks that we've wrote data to as changed. */
				{
					size_t blki;
					for (blki = changed_minblk; blki <= changed_maxblk; ++blki)
						mpart_setblockstate(part, blki, MPART_BLOCK_ST_CHNG);
				}

				/* Re-acquire a lock to the file, so we can insert the new mem-part. */
				mfile_lock_write(self);
			} EXCEPT {
				LIST_ENTRY_UNBOUND_INIT(&part->mp_allparts);
				mpart_destroy(part);
				RETHROW();
			}
		} EXCEPT {
			if (parthead_disk || parttail_disk)
				mfile_trunclock_dec(self);
			RETHROW();
		}

		/* If we haven't already done so above, acquire a trunc-lock. */
		if (!parthead_disk && !parttail_disk)
			mfile_trunclock_inc(self);

		/* Make sure that the file hasn't become anonymous. */
		if unlikely(mfile_isanon(self))
			goto handle_part_insert_failure;

		/* Make sure that the file's size can still be altered. */
		if unlikely(self->mf_flags & (MFILE_F_DELETED | MFILE_F_READONLY | MFILE_F_FIXEDFILESIZE))
			goto handle_part_insert_failure;

		/* When  any portion of the new part  had to be zero-initialized, then we
		 * have to ensure that in the mean time the file's size hasn't increased.
		 *
		 * Normally, an increase in file size that overlaps with our new  `part'
		 * would mean that `mfile_insert_and_merge_part_and_unlock()' would fail
		 * since there would now be another  part which ours overlaps with.  But
		 * this doesn't happen if said other part has already been unloaded.
		 *
		 * As  such, we have to manually check  if the file's size has increased,
		 * though in the case  where it will increase  after we make this  check,
		 * `mfile_insert_and_merge_part_and_unlock()' would fail due to the other
		 * pre-existing part.
		 *
		 * Without this, it becomes possible to increase a file's size while doing
		 * a simultaneous write to the file's size, at which point a small area of
		 * the file might end up (wrongfully) zero-initialized. */
		if ((parthead_size > parthead_disk) ||
		    (parttail_size > parttail_disk)) {
			pos_t new_filesize = (pos_t)atomic64_read(&self->mf_filesize);
			if (new_filesize > filesize) {
				pos_t first_bzero_pos;
				first_bzero_pos = parthead_pos + parthead_disk;
				if (parthead_size <= parthead_disk)
					first_bzero_pos = parttail_pos + parttail_disk;
				assert(first_bzero_pos >= filesize);
				if (first_bzero_pos < new_filesize) {
					/* One of our bzero positions is no longer out-of-bounds
					 * -> We can't insert this  part as-is into the  file
					 *    because doing so would lead to file corruption! */
					goto handle_part_insert_failure;
				}
			}
		}
	}
#undef LOCAL_BUFFER_copy2phys

	/* Try to insert the new part into the file, as
	 * well as merge it with its neighboring parts. */
	{
		uintptr_t changes;
		pos_t newsize, oldsize;
		REF struct mpart *inserted_part;
		inserted_part = mfile_insert_and_merge_part_and_unlock(self, part);
		if unlikely(!inserted_part) {
#ifndef LOCAL_BUFFER_IS_PHYS
			mpart_reladdr_t partoff;
#endif /* !LOCAL_BUFFER_IS_PHYS */
handle_part_insert_failure:
			mfile_trunclock_dec(self);
			mfile_lock_endwrite(self);
			RAII_FINALLY {
				LIST_ENTRY_UNBOUND_INIT(&part->mp_allparts);
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
		assert(newsize > filesize);
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
				self->mf_ctime = now;
				changes |= MFILE_F_ATTRCHANGED;
			}
			mfile_tslock_release(self);
		}

		mfile_changed(self, changes);
		result += num_bytes;
		mfile_inotify_modified(self); /* Post `IN_MODIFY' */

		/* Drop the reference from `mfile_insert_and_merge_part_and_unlock()' */
		decref_unlikely(inserted_part);
	} /* Scope.... */

	/* Since we've just written _all_ of the trailing data, we're
	 * finally  done and don't  have to loop  back to write more! */
#endif /* !LOCAL_READING */

done:
	return result;
#undef offset
#endif /* !... */
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
#undef LOCAL_mfile_asyncrw
#undef LOCAL_dma_callback
#undef LOCAL_READING
#undef LOCAL_WRITING
#undef LOCAL_ASYNC
#undef LOCAL_DIRECT

DECL_END

#undef DEFINE_mfile_direct_read
#undef DEFINE_mfile_direct_read_p
#undef DEFINE_mfile_direct_readv
#undef DEFINE_mfile_direct_readv_p
#undef DEFINE_mfile_direct_write
#undef DEFINE_mfile_direct_write_p
#undef DEFINE_mfile_direct_writev
#undef DEFINE_mfile_direct_writev_p
#undef DEFINE_mfile_direct_read_async
#undef DEFINE_mfile_direct_read_async_p
#undef DEFINE_mfile_direct_readv_async
#undef DEFINE_mfile_direct_readv_async_p
#undef DEFINE_mfile_direct_write_async
#undef DEFINE_mfile_direct_write_async_p
#undef DEFINE_mfile_direct_writev_async
#undef DEFINE_mfile_direct_writev_async_p
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
