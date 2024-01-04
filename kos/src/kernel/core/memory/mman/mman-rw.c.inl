/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifdef __INTELLISENSE__
#include "mman-rw.c"
#define DEFINE_mman_read_nopf
//#define  DEFINE_mman_write_nopf
//#define DEFINE_mman_memset_nopf
//#define        DEFINE_mman_read
//#define       DEFINE_mman_write
//#define      DEFINE_mman_memset
#endif /* __INTELLISENSE__ */

#include <kernel/mman.h>
#include <kernel/mman/rw.h>
#include <sched/pertask.h>
#include <sched/task.h>

#include <kos/except.h>
#include <kos/nopf.h>

#include <alloca.h>
#include <stdbool.h>
#include <string.h>

DECL_BEGIN

#ifdef DEFINE_mman_read_nopf
/* Read/write  memory  to/form   the  address  space   of  a  given   mman
 * Note that these functions behave similar to memcpy_nopf(), in that they
 * will only ever copy _true_ RAM, and never access VIO or cause  LOA/COW.
 * @return: 0 : The copy operation completed without any problems.
 * @return: * : The number of bytes that could not be transferred.
 *              The affected memory range is:
 *               - `buf + num_bytes - return ... buf + num_bytes - 1' */
PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(KCALL mman_read_nopf)(struct mman *__restrict self, UNCHECKED void const *addr,
                              NCX void *buf, size_t num_bytes)
#define LOCAL_IS_NOPF
#define LOCAL_IS_READING
#elif defined(DEFINE_mman_write_nopf)
PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(KCALL mman_write_nopf)(struct mman *__restrict self, UNCHECKED void *addr,
                               NCX void const *buf, size_t num_bytes)
#define LOCAL_IS_NOPF
#define LOCAL_IS_WRITING
#elif defined(DEFINE_mman_memset_nopf)
PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(KCALL mman_memset_nopf)(struct mman *__restrict self, UNCHECKED void *addr,
                                int byte, size_t num_bytes)
#define LOCAL_IS_NOPF
#define LOCAL_IS_WRITING
#define LOCAL_IS_MEMSET
#elif defined(DEFINE_mman_read)
/* High-level  read/write   memory   to/from   the   given   `self'.
 * These functions do all the things necessary to read/write  memory
 * the same way a regular memory access would, including LOA/COW, as
 * well as properly accessing VIO.
 * @param: force_readable_source:      When true, force `addr' to be readable, ignoring `MNODE_F_PREAD'
 * @param: force_writable_destination: When true, force `addr' to be writable, invoking COW as needed. */
PUBLIC BLOCKING void KCALL
mman_read(struct mman *__restrict self,
          UNCHECKED void const *addr, NCX void *buf,
          size_t num_bytes, bool force_readable_source)
		THROWS(E_SEGFAULT, E_WOULDBLOCK)
#define LOCAL_IS_READING
#elif defined(DEFINE_mman_write)
PUBLIC BLOCKING void KCALL
mman_write(struct mman *__restrict self,
           UNCHECKED void *addr, NCX void const *buf,
           size_t num_bytes, bool force_writable_destination)
		THROWS(E_SEGFAULT, E_WOULDBLOCK)
#define LOCAL_IS_WRITING
#elif defined(DEFINE_mman_memset)
/* Same as `mman_write()', but implement memset() semantics instead. */
PUBLIC BLOCKING void KCALL
mman_memset(struct mman *__restrict self,
            UNCHECKED void *addr, int byte, size_t num_bytes,
            bool force_writable_destination)
		THROWS(E_SEGFAULT, E_WOULDBLOCK)
#define LOCAL_IS_WRITING
#define LOCAL_IS_MEMSET
#else /* ... */
#error "Invalid configuration"
#endif /* !... */
{
#ifdef LOCAL_IS_NOPF
	size_t error;
#else /* LOCAL_IS_NOPF */
#ifdef LOCAL_IS_READING
	(void)force_readable_source;      /* TODO: Support me! */
#else /* LOCAL_IS_READING */
	(void)force_writable_destination; /* TODO: Support me! */
#endif /* !LOCAL_IS_READING */
#endif /* !LOCAL_IS_NOPF */

#ifndef LOCAL_IS_MEMSET
	if (ADDRRANGE_ISKERN(buf, (byte_t *)buf + num_bytes))
#endif /* !LOCAL_IS_MEMSET */
	{
		if (THIS_MMAN == self) {
#if defined(LOCAL_IS_MEMSET) && defined(LOCAL_IS_NOPF)
			error = memset_nopf(addr, byte, num_bytes);
#elif defined(LOCAL_IS_MEMSET)
			memset(addr, byte, num_bytes);
#elif defined(LOCAL_IS_READING) && defined(LOCAL_IS_NOPF)
			error = memcpy_nopf(buf, addr, num_bytes);
#elif defined(LOCAL_IS_READING)
			memcpy(buf, addr, num_bytes);
#elif defined(LOCAL_IS_WRITING) && defined(LOCAL_IS_NOPF)
			error = memcpy_nopf(addr, buf, num_bytes);
#elif defined(LOCAL_IS_WRITING)
			memcpy(addr, buf, num_bytes);
#else /* ... */
#error "Invalid configuration"
#endif /* !... */
		} else {
			REF struct mman *oldmm;
			oldmm = task_xchmman(self);
#ifdef LOCAL_IS_NOPF
#if defined(LOCAL_IS_MEMSET) && defined(LOCAL_IS_NOPF)
			error = memset_nopf(addr, byte, num_bytes);
#elif defined(LOCAL_IS_READING) && defined(LOCAL_IS_NOPF)
			error = memcpy_nopf(buf, addr, num_bytes);
#elif defined(LOCAL_IS_WRITING) && defined(LOCAL_IS_NOPF)
			error = memcpy_nopf(addr, buf, num_bytes);
#else /* ... */
#error "Invalid configuration"
#endif /* ... */
			task_setmman_inherit(oldmm);
#else /* LOCAL_IS_NOPF */
			RAII_FINALLY { task_setmman_inherit(oldmm); };
#if defined(LOCAL_IS_MEMSET)
			memset(addr, byte, num_bytes);
#elif defined(LOCAL_IS_READING)
			memcpy(buf, addr, num_bytes);
#elif defined(LOCAL_IS_WRITING)
			memcpy(addr, buf, num_bytes);
#else /* ... */
#error "Invalid configuration"
#endif /* ... */
#endif /* !LOCAL_IS_NOPF */
		}
	}
#ifndef LOCAL_IS_MEMSET
#ifdef LOCAL_IS_NOPF
	else if unlikely(!num_bytes) {
		error = 0;
	}
#endif /* LOCAL_IS_NOPF */
	else {
		size_t tempbuf_size;
		byte_t *tempbuf;

		/* Copy via an intermediate buffer. */
		tempbuf_size = get_stack_avail() / 2;
		if (tempbuf_size > num_bytes)
			tempbuf_size = num_bytes;
		if (tempbuf_size < 64)
			tempbuf_size = 64;
		tempbuf = (byte_t *)alloca(tempbuf_size);
		do {
			size_t transfer;
			transfer = tempbuf_size;
			if (transfer > num_bytes)
				transfer = num_bytes;

#if defined(LOCAL_IS_READING) && defined(LOCAL_IS_NOPF)
			error = mman_read_nopf(self, addr, tempbuf, transfer);
			error += memcpy_nopf(buf, tempbuf, transfer - __builtin_expect(error, 0));
#elif defined(LOCAL_IS_READING)
			mman_read(self, addr, tempbuf, transfer, force_readable_source);
#elif defined(LOCAL_IS_WRITING) && defined(LOCAL_IS_NOPF)
			error = memcpy_nopf(tempbuf, buf, transfer);
			error += mman_write_nopf(self, addr, tempbuf, transfer - __builtin_expect(error, 0));
#elif defined(LOCAL_IS_WRITING)
			mman_write(self, addr, tempbuf, transfer);
#endif /* ... */

			addr = (UNCHECKED byte_t *)addr + transfer;
			buf  = (byte_t *)buf + transfer;
			num_bytes -= transfer;

#ifdef LOCAL_IS_NOPF
			/* Handle transfer error. */
			if (error != 0) {
				error += num_bytes; /* Total # of bytes not transferred */
				break;
			}
#endif /* LOCAL_IS_NOPF */
		} while (num_bytes);
	}
#endif /* !LOCAL_IS_MEMSET */

#ifdef LOCAL_IS_NOPF
	return error;
#endif /* LOCAL_IS_NOPF */
}

#undef LOCAL_IS_NOPF
#undef LOCAL_IS_READING
#undef LOCAL_IS_WRITING
#undef LOCAL_IS_MEMSET

DECL_END

#undef DEFINE_mman_read_nopf
#undef DEFINE_mman_write_nopf
#undef DEFINE_mman_memset_nopf
#undef DEFINE_mman_read
#undef DEFINE_mman_write
#undef DEFINE_mman_memset
