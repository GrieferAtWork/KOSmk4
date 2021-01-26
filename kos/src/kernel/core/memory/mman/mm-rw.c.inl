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
#include "mm-rw.c"
#define DEFINE_mman_read_nopf
//#define DEFINE_mman_write_nopf
//#define DEFINE_mman_memset_nopf
//#define DEFINE_mman_read
//#define DEFINE_mman_write
//#define DEFINE_mman_memset
#endif /* __INTELLISENSE__ */

#include <kernel/mman.h>
#include <kernel/mman/mm-rw.h>

#include <kos/except.h>

#include <stdbool.h>

DECL_BEGIN

#ifdef DEFINE_mman_read_nopf
/* Read/write memory to/form the address space of a given mman
 * Note that these functions behave similar to memcpy_nopf(), in that they
 * will only ever copy _true_ RAM, and never access VIO or cause LOA/COW.
 * @return: 0 : The copy operation completed without any problems.
 * @return: * : The number of bytes that could not be transfered.
 *              The affected memory range is:
 *               - `buf + num_bytes - return ... buf + num_bytes - 1' */
PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(KCALL mman_read_nopf)(struct mman *__restrict self, UNCHECKED void const *addr,
                              USER CHECKED void *buf, size_t num_bytes)
#define LOCAL_IS_NOPF
#define LOCAL_IS_READING
#elif defined(DEFINE_mman_write_nopf)
PUBLIC NOBLOCK NONNULL((1)) size_t
NOTHROW(KCALL mman_write_nopf)(struct mman *__restrict self, UNCHECKED void *addr,
                               USER CHECKED void const *buf, size_t num_bytes)
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
/* High-level read/write memory to/from the given `self'.
 * These functions do all the things necessary to read/write memory
 * the same way a regular memory access would, including LOA/COW, as
 * well as properly accessing VIO.
 * @param: force_readable_source:      When true, force `addr' to be readable, ignoring `MNODE_F_PREAD'
 * @param: force_writable_destination: When true, force `addr' to be writable, invoking COW as needed.  */
PUBLIC void KCALL
mman_read(struct mman *__restrict self,
        UNCHECKED void const *addr, USER CHECKED void *buf,
        size_t num_bytes, bool force_readable_source)
		THROWS(E_SEGFAULT, E_WOULDBLOCK)
#define LOCAL_IS_READING
#elif defined(DEFINE_mman_write)
PUBLIC void KCALL
mman_write(struct mman *__restrict self,
           UNCHECKED void *addr, USER CHECKED void const *buf,
           size_t num_bytes, bool force_writable_destination)
		THROWS(E_SEGFAULT, E_WOULDBLOCK)
#define LOCAL_IS_WRITING
#elif defined(DEFINE_mman_memset)
/* Same as `mman_write()', but implement memset() semantics instead. */
PUBLIC void KCALL
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
	(void)self;
	(void)addr;
	(void)num_bytes;
#ifdef LOCAL_IS_MEMSET
	(void)byte;
#else /* LOCAL_IS_MEMSET */
	(void)buf;
#endif /* !LOCAL_IS_MEMSET */
#ifndef LOCAL_IS_NOPF
#ifdef LOCAL_IS_WRITING
	(void)force_writable_destination;
#else /* LOCAL_IS_WRITING */
	(void)force_readable_source;
#endif /* !LOCAL_IS_WRITING */
#endif /* !LOCAL_IS_NOPF */

	/* TODO */
#ifdef LOCAL_IS_NOPF
	return num_bytes;
#else /* LOCAL_IS_NOPF */
	THROW(E_NOT_IMPLEMENTED_TODO);
#endif /* !LOCAL_IS_NOPF */
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
