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
#include "super.c"
#define DEFINE_fsuper_dev_rdsectors_async_chk
//#define DEFINE_fsuper_dev_wrsectors_async_chk
//#define       DEFINE_fsuper_dev_rdsectors_chk
//#define DEFINE_fsuper_dev_wrsectors_chk
#endif /* __INTELLISENSE__ */

#include <kernel/mman/phys.h>

#include <hybrid/overflow.h>

#if (defined(DEFINE_fsuper_dev_rdsectors_async_chk) + \
     defined(DEFINE_fsuper_dev_wrsectors_async_chk) + \
     defined(DEFINE_fsuper_dev_rdsectors_chk) +       \
     defined(DEFINE_fsuper_dev_wrsectors_chk)) != 1
#error "Must #define exactly one of these"
#endif /* ... */


DECL_BEGIN

/* Same as `fsuper_dev_*' above, but these perform an explicit check
 * for the requested address range to actually be in-bounds. When it
 * isn't, behavior depends on `fsuper_allow_fs_oob':
 *  - When set to `false' (default), throw `E_IOERROR_BADBOUNDS'
 *  - When set to `true', out-of-bounds writes are ignored, and reads yield all zeroes.
 *    In  this case, any area that is actually in-bounds will be forwarded like normal.
 * @assume(IS_ALIGNED(buf, (size_t)1 << self->fs_root.mf_iobashift));
 * @assume(IS_ALIGNED(addr, mfile_getblocksize(&self->fs_root)));
 * @assume(IS_ALIGNED(num_bytes, mfile_getblocksize(&self->fs_root)));
 * @assume(num_bytes != 0); */
#ifdef DEFINE_fsuper_dev_rdsectors_async_chk
#define LOCAL_IS_READING
#define LOCAL_IS_ASYNC
PUBLIC BLOCKING NONNULL((1, 5)) void KCALL
fsuper_dev_rdsectors_async_chk(struct fsuper *__restrict self, pos_t addr,
                               physaddr_t buf, size_t num_bytes,
                               struct aio_multihandle *__restrict aio)
		THROWS(E_IOERROR_BADBOUNDS, ...)
#elif defined(DEFINE_fsuper_dev_wrsectors_async_chk)
#define LOCAL_IS_WRITING
#define LOCAL_IS_ASYNC
PUBLIC BLOCKING NONNULL((1, 5)) void KCALL
fsuper_dev_wrsectors_async_chk(struct fsuper *__restrict self, pos_t addr, physaddr_t buf,
                               size_t num_bytes, struct aio_multihandle *__restrict aio)
		THROWS(E_IOERROR_BADBOUNDS, ...)
#elif defined(DEFINE_fsuper_dev_rdsectors_chk)
#define LOCAL_IS_READING
PUBLIC BLOCKING NONNULL((1)) void KCALL
fsuper_dev_rdsectors_chk(struct fsuper *__restrict self, pos_t addr,
                         physaddr_t buf, size_t num_bytes)
		THROWS(E_IOERROR_BADBOUNDS, ...)
#elif defined(DEFINE_fsuper_dev_wrsectors_chk)
#define LOCAL_IS_WRITING
PUBLIC BLOCKING NONNULL((1)) void KCALL
fsuper_dev_wrsectors_chk(struct fsuper *__restrict self, pos_t addr,
                         physaddr_t buf, size_t num_bytes)
		THROWS(E_IOERROR_BADBOUNDS, ...)
#else /* .. */
#error "Invalid configuration"
#endif /* !.. */
{
	pos_t endaddr, devsize;
	devsize = (pos_t)atomic64_read(&self->fs_dev->mf_filesize);
	if unlikely(OVERFLOW_UADD(addr, num_bytes, &endaddr) || endaddr > devsize) {
		size_t ok_io;
		/* I/O is actually allowed up until the device's next block-aligned boundary. */
		devsize = mfile_partaddr_ceilalign(self->fs_dev, devsize);
		if (OVERFLOW_USUB(devsize, addr, &ok_io))
			ok_io = 0; /* We get here when `addr > devsize' */
		if unlikely(ok_io >= num_bytes) {
			/* This can happen due to alignment near the end of the device. */
			goto do_io;
		}

		/* Check if out-ob-bounds I/O should be allowed. */
		if (!fsuper_allow_fs_oob)
			THROW(E_IOERROR_BADBOUNDS);

		/* Reading from out-of-bounds yields zeroes.
		 * -> For writes we don't do anything. */
#ifdef LOCAL_IS_READING
		bzerophyscc(buf + ok_io, num_bytes - ok_io);
#endif /* LOCAL_IS_READING */
		if (!ok_io)
			return;
		num_bytes = ok_io;
	}
do_io:
#ifdef LOCAL_IS_ASYNC
#ifdef LOCAL_IS_READING
	fsuper_dev_rdsectors_async(self, addr, buf, num_bytes, aio);
#else /* LOCAL_IS_READING */
	fsuper_dev_wrsectors_async(self, addr, buf, num_bytes, aio);
#endif /* !LOCAL_IS_READING */
#else /* LOCAL_IS_ASYNC */
#ifdef LOCAL_IS_READING
	fsuper_dev_rdsectors(self, addr, buf, num_bytes);
#else /* LOCAL_IS_READING */
	fsuper_dev_wrsectors(self, addr, buf, num_bytes);
#endif /* !LOCAL_IS_READING */
#endif /* !LOCAL_IS_ASYNC */
}

#undef LOCAL_IS_READING
#undef LOCAL_IS_WRITING
#undef LOCAL_IS_ASYNC

DECL_END

#undef DEFINE_fsuper_dev_wrsectors_chk
#undef DEFINE_fsuper_dev_rdsectors_chk
#undef DEFINE_fsuper_dev_wrsectors_async_chk
#undef DEFINE_fsuper_dev_rdsectors_async_chk
