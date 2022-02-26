/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MLOCK_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MLOCK_H 1

#include <kernel/compiler.h>

#include <kernel/types.h>

#include <asm/os/mman.h>
#include <kos/kernel/paging.h>

/* Helper functions for locking/unlocking memory mappings. */



/************************************************************************/
/* Flags for `mman_mlock()' and `mman_munlock()'                        */
/************************************************************************/

/* Default behavior: Populate locked memory immediately */
#ifndef MLOCK_NOW
#define MLOCK_NOW 0
#endif /* !MLOCK_NOW */

/* Delegate population of locked memory until the first access. */
#ifndef MLOCK_ONFAULT
#define MLOCK_ONFAULT __MLOCK_ONFAULT
#endif /* !MLOCK_ONFAULT */

/* Ignore (skip) unmapped parts of the given address range. */
#ifndef MLOCK_IFMAPPED
#define MLOCK_IFMAPPED 0x8000
#endif /* !MLOCK_IFMAPPED */


#ifdef __CC__
DECL_BEGIN

struct mman;

/* Set the `MNODE_F_MLOCK' flag for  all mem-nodes within the  given
 * address range, and potentially pre-populate all nodes within said
 * range for immediate use.
 * @param: flags: Set of `MLOCK_NOW | MLOCK_ONFAULT | MLOCK_IFMAPPED'
 * @throws: *:E_INVALID_ARGUMENT_CONTEXT_MLOCK_SIZE: [...]
 * @throws: E_SEGFAULT_UNMAPPED: When `MLOCK_IFMAPPED' isn't given, this exception is
 *                               thrown for the first address of the given range that
 *                               isn't  mapped. When this  happens, no mem-nodes will
 *                               have had their MLOCK-state altered. */
FUNDEF BLOCKING_IF(!(flags & MLOCK_ONFAULT)) NONNULL((1)) void FCALL
mman_mlock(struct mman *__restrict self, void const *addr,
           size_t num_bytes, unsigned int flags DFL(0))
		THROWS(E_INVALID_ARGUMENT_BAD_VALUE, E_SEGFAULT_UNMAPPED,
		       E_BADALLOC, ...);


/* Clear the `MNODE_F_MLOCK' flag for all mem-nodes within the given address range.
 * @param: flags: Set of `0 | MLOCK_IFMAPPED'
 * @throws: *:E_INVALID_ARGUMENT_CONTEXT_MUNLOCK_SIZE: [...]
 * @throws: E_SEGFAULT_UNMAPPED: When `MLOCK_IFMAPPED' isn't given, this exception is
 *                               thrown for the first address of the given range that
 *                               isn't  mapped. When this  happens, no mem-nodes will
 *                               have had their MLOCK-state altered. */
FUNDEF NONNULL((1)) void FCALL
mman_munlock(struct mman *__restrict self, void const *addr,
             size_t num_bytes, unsigned int flags DFL(0))
		THROWS(E_INVALID_ARGUMENT_BAD_VALUE, E_SEGFAULT_UNMAPPED,
		       E_BADALLOC);

/* Lock or unlock all of userspace */
#ifdef USERSPACE_END
#define mman_mlockall(self, flags) mman_mlock(self, (void const *)0, (size_t)USERSPACE_END, (flags) | MLOCK_IFMAPPED)
#define mman_munlockall(self)      mman_munlock(self, (void const *)0, (size_t)USERSPACE_END, MLOCK_IFMAPPED)
#else /* USERSPACE_END */
#define mman_mlockall(self, flags) mman_mlock(self, (void const *)USERSPACE_START, (size_t)0 - (size_t)USERSPACE_START, (flags) | MLOCK_IFMAPPED)
#define mman_munlockall(self)      mman_munlock(self, (void const *)USERSPACE_START, (size_t)0 - (size_t)USERSPACE_START, MLOCK_IFMAPPED)
#endif /* !USERSPACE_END */



DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MLOCK_H */
