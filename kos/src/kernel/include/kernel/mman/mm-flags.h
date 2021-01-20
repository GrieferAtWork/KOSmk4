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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MM_FLAGS_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MM_FLAGS_H 1

#include <kernel/compiler.h>

#include <kernel/mman/mm-map.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/mnode.h>

#ifdef __CC__
DECL_BEGIN

/* Helper macros to (safely) convert between different types of
 * flags used throughout the memory management system. Note that
 * for this purpose, most flags with identical meaning are designed
 * to also share identical numerical values. */


/* >> uintptr_t mnodeflags_from_mapflags(unsigned int prot);
 * Convert `MAP_*' to `MNODE_F_*':
 *   - 0            -> MNODE_F_NORMAL
 *   - MAP_PREPARED -> MNODE_F_MPREPARED
 *   - MAP_LOCKED   -> MNODE_F_MLOCK
 */
#if (0 == MNODE_F_NORMAL &&               \
     MAP_PREPARED == MNODE_F_MPREPARED && \
     MAP_LOCKED == MNODE_F_MLOCK)
#define mnodeflags_from_mapflags(mapflags) \
	((mapflags) & (MNODE_F_MPREPARED | MNODE_F_MLOCK))
#else /* ... */
#define mnodeflags_from_mapflags(mapflags)                 \
	((((mapflags)&MAP_PREPARED) ? MNODE_F_MPREPARED : 0) | \
	 (((mapflags)&MAP_LOCKED) ? MNODE_F_MLOCK : 0))
#endif /* !... */



/* >> uintptr_t mnodeflags_from_prot(unsigned int prot);
 * Convert `MAP_*' to `PROT_*':
 *    PROT_NONE   -> 0
 *    PROT_EXEC   -> MNODE_F_PEXEC
 *    PROT_WRITE  -> MNODE_F_PWRITE
 *    PROT_READ   -> MNODE_F_PREAD
 *    PROT_SHARED -> MNODE_F_SHARED
 */
#if (PROT_NONE == 0 &&               \
     PROT_EXEC == MNODE_F_PEXEC &&   \
     PROT_WRITE == MNODE_F_PWRITE && \
     PROT_READ == MNODE_F_PREAD &&   \
     PROT_SHARED == MNODE_F_SHARED)
#define mnodeflags_from_prot(prot)              \
	((prot) & (MNODE_F_PEXEC | MNODE_F_PWRITE | \
	           MNODE_F_PREAD | MNODE_F_SHARED))
#else /* ... */
#define mnodeflags_from_prot(prot)                \
	((((prot)&PROT_EXEC) ? MNODE_F_PEXEC : 0) |   \
	 (((prot)&PROT_WRITE) ? MNODE_F_PWRITE : 0) | \
	 (((prot)&PROT_READ) ? MNODE_F_PREAD : 0) |   \
	 (((prot)&PROT_SHARED) ? MNODE_F_SHARED : 0))
#endif /* !... */


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MM_FLAGS_H */
