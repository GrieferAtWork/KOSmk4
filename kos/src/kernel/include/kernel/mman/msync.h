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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MSYNC_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MSYNC_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <asm/os/mman.h>

/* Helper functions for syncing SHARED file
 * mappings, such that changes are  written
 * back to disk. */


/************************************************************************/
/* Flags for `mman_msync()'                                             */
/************************************************************************/

/* Ignored (not supported) */
#ifndef MS_ASYNC
#define MS_ASYNC __MS_ASYNC
#endif /* !MS_ASYNC */

/* Ignored (meaningless / always the case: KOS implements unified I/O buffers) */
#ifndef MS_INVALIDATE
#define MS_INVALIDATE __MS_INVALIDATE
#endif /* !MS_INVALIDATE */

/* Ignored (always the case) */
#ifndef MS_SYNC
#define MS_SYNC __MS_SYNC
#endif /* !MS_SYNC */

/* Ignore (skip) unmapped parts of the given address range. */
#ifndef MS_IFMAPPED
#define MS_IFMAPPED 0x8000
#endif /* !MS_IFMAPPED */


#ifdef __CC__
DECL_BEGIN

struct mman;

/* Sync  the backing mem-parts  of all MNODE_F_SHARED nodes
 * within the given address range. Note that this operation
 * is done distinct steps, meaning that some writes done by
 * a different process prior to this function returning may
 * get synced, whilst other  writes that might even  happen
 * after a prior write that  did end up being synced  don't
 * end up synced.
 *
 * Additionally,  if this function fails (by throwing an
 * exception), it is still possible that some writes may
 * have gotten synced while others weren't.
 *
 * However, anything written by the calling thread within
 * the given  range before  this  function is  called  is
 * guarantied to end up synced upon success.
 *
 * @param: flags: Set of `MS_*' (see above)
 * @throws: *:E_INVALID_ARGUMENT_CONTEXT_MSYNC_SIZE: [...]
 * @throws: E_SEGFAULT_UNMAPPED: When `MS_IFMAPPED' isn't given, this exception is
 *                               thrown for the first  address of the given  range
 *                               that isn't mapped. */
FUNDEF BLOCKING NONNULL((1)) void FCALL
mman_msync(struct mman *__restrict self, void *addr,
           size_t num_bytes, unsigned int flags DFL(0))
		THROWS(E_INVALID_ARGUMENT_BAD_VALUE, E_SEGFAULT_UNMAPPED, ...);

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MSYNC_H */
