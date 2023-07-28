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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_RW_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_RW_H 1

#include <kernel/compiler.h>

#include <kernel/paging.h>
#include <kernel/types.h>

#ifdef __CC__
DECL_BEGIN

/* Read/write  memory  to/form   the  address  space   of  a  given   mman
 * Note that these functions behave similar to memcpy_nopf(), in that they
 * will only ever copy _true_ RAM, and never access VIO or cause  LOA/COW.
 * @return: 0 : The copy operation completed without any problems.
 * @return: * : The number of bytes that could not be transferred.
 *              The affected memory range is:
 *               - `buf + num_bytes - return ... buf + num_bytes - 1' */
FUNDEF NOBLOCK NONNULL((1)) size_t
NOTHROW(KCALL mman_read_nopf)(struct mman *__restrict self, UNCHECKED void const *addr,
                              NCX void *buf, size_t num_bytes);
FUNDEF NOBLOCK NONNULL((1)) size_t
NOTHROW(KCALL mman_write_nopf)(struct mman *__restrict self, UNCHECKED void *addr,
                               NCX void const *buf, size_t num_bytes);
FUNDEF NOBLOCK NONNULL((1)) size_t
NOTHROW(KCALL mman_memset_nopf)(struct mman *__restrict self, UNCHECKED void *addr,
                                int byte, size_t num_bytes);

/* High-level  read/write   memory   to/from   the   given   `self'.
 * These functions do all the things necessary to read/write  memory
 * the same way a regular memory access would, including LOA/COW, as
 * well as properly accessing VIO.
 * @param: force_readable_source:      When true, force `addr' to be readable, ignoring `MNODE_F_PREAD'
 * @param: force_writable_destination: When true, force `addr' to be writable, invoking COW as needed. */
FUNDEF BLOCKING void KCALL
mman_read(struct mman *__restrict self,
          UNCHECKED void const *addr, NCX void *buf,
          size_t num_bytes, __BOOL force_readable_source DFL(0))
		THROWS(E_SEGFAULT, E_WOULDBLOCK);
FUNDEF BLOCKING void KCALL
mman_write(struct mman *__restrict self,
           UNCHECKED void *addr, NCX void const *buf,
           size_t num_bytes, __BOOL force_writable_destination DFL(0))
		THROWS(E_SEGFAULT, E_WOULDBLOCK);
/* Same as `mman_write()', but implement memset() semantics instead. */
FUNDEF BLOCKING void KCALL
mman_memset(struct mman *__restrict self,
            UNCHECKED void *addr, int byte, size_t num_bytes,
            __BOOL force_writable_destination DFL(0))
		THROWS(E_SEGFAULT, E_WOULDBLOCK);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_RW_H */
