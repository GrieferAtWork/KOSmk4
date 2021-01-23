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

#include <kernel/malloc-defs.h>
#include <kernel/mman/mm-kram.h>
#include <kernel/mman/mm-map.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>

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
#if (PROT_NONE == 0 &&               \
     PROT_EXEC == MNODE_F_PEXEC &&   \
     PROT_WRITE == MNODE_F_PWRITE && \
     PROT_READ == MNODE_F_PREAD)
#define mnodeflags_from_prot_noshared(prot) \
	((prot) & (MNODE_F_PEXEC | MNODE_F_PWRITE | MNODE_F_PREAD))
#else /* ... */
#define mnodeflags_from_prot_noshared(prot)       \
	((((prot)&PROT_EXEC) ? MNODE_F_PEXEC : 0) |   \
	 (((prot)&PROT_WRITE) ? MNODE_F_PWRITE : 0) | \
	 (((prot)&PROT_READ) ? MNODE_F_PREAD : 0))
#endif /* !... */


/* Evaluates to non-zero if `after' is more restrictive than `before',
 * in that at least one of the permissions from `before' is no longer
 * apart of `after'. */
#define mnodeflags_prot_more_restrictive(before, after) \
	((((before) & ~(after)) & (MNODE_F_PEXEC | MNODE_F_PWRITE | MNODE_F_PREAD)) != 0)


/* >> unsigned int mapflags_from_gfp(gfp_t gfp);
 * Convert `GFP_*' to `MAP_*':
 *    GFP_MAP_32BIT  -> MAP_32BIT
 *    GFP_MAP_BELOW  -> MAP_GROWSDOWN
 *    GFP_MAP_ABOVE  -> MAP_GROWSUP
 *    GFP_MAP_NOASLR -> MAP_NOASLR */
#if (GFP_MAP_32BIT == __MAP_32BIT && GFP_MAP_BELOW == __MAP_GROWSDOWN && \
     GFP_MAP_ABOVE == __MAP_GROWSUP && GFP_MAP_NOASLR == __MAP_NOASLR)
#define mapflags_from_gfp(gfp) \
	((gfp) & (GFP_MAP_32BIT | GFP_MAP_BELOW | GFP_MAP_ABOVE | GFP_MAP_NOASLR))
#else /* ... */
#define mapflags_from_gfp(gfp)                      \
	((((gfp)&GFP_MAP_32BIT) ? __MAP_32BIT : 0) |     \
	 (((gfp)&GFP_MAP_BELOW) ? __MAP_GROWSDOWN : 0) | \
	 (((gfp)&GFP_MAP_ABOVE) ? __MAP_GROWSUP : 0) |   \
	 (((gfp)&GFP_MAP_NOASLR) ? __MAP_NOASLR : 0))
#endif /* !... */


/* >> unsigned int mnodeflags_from_gfp(gfp_t gfp);
 * Convert `GFP_*' to `MNODE_F_*':
 *    GFP_MAP_PREPARED -> MNODE_F_MPREPARED
 *    GFP_LOCKED       -> MNODE_F_MLOCK */
#if (GFP_MAP_PREPARED == MNODE_F_MPREPARED && \
     GFP_LOCKED == MNODE_F_MLOCK)
#define mnodeflags_from_gfp(gfp) \
	((gfp) & (GFP_MAP_PREPARED | GFP_LOCKED))
#elif (GFP_MAP_PREPARED == MNODE_F_MPREPARED)
#define mnodeflags_from_gfp(gfp)    \
	(((gfp) & (GFP_MAP_PREPARED)) | \
	 (((gfp)&GFP_LOCKED) ? MNODE_F_MLOCK : 0))
#else /* ... */
#define mnodeflags_from_gfp(gfp)                          \
	((((gfp)&GFP_MAP_PREPARED) ? MNODE_F_MPREPARED : 0) | \
	 (((gfp)&GFP_LOCKED) ? MNODE_F_MLOCK : 0))
#endif /* !... */


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_MM_FLAGS_H */
