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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_FLAGS_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_FLAGS_H 1

#include <kernel/compiler.h>

#include <kernel/malloc-defs.h> /* GFP_* */
#include <kernel/mman/kram.h>   /* GFP_MAP_* */
#include <kernel/mman/map.h>    /* PROT_*, MAP_* */
#include <kernel/mman/mnode.h>  /* MNODE_F_* */

#include <asm/os/mman.h>

#include <elf.h> /* PF_* */

/* Kernel-only flag: disallow use of mprotect(2) to gain write access. Trying  to
 * do so will throw `E_INVALID_HANDLE_OPERATION:E_INVALID_HANDLE_OPERATION_MMAP'. */
#ifndef PROT_DENYWRITE
#define PROT_DENYWRITE 0x10
#endif /* !PROT_DENYWRITE */

#ifdef __CC__
DECL_BEGIN

/* Helper macros  to (safely)  convert between  different types  of
 * flags used throughout  the memory management  system. Note  that
 * for this purpose, most flags with identical meaning are designed
 * to also share identical numerical values. */



/*
 * (intended, but not assumed) flags equivalences:
 *
 *                                 INTENDED                  UNINTENDED
 * GFP_NORMAL       0x00000000
 * GFP_LOCKED       0x00000001                               [MAP_SHARED]
 * GFP_PREFLT       0x00000002                               [MAP_PRIVATE]
 * GFP_CALLOC       0x00000004
 * GFP_NOCLRC       0x00000008
 * GFP_MAP_FIXED    0x00000010    [MAP_FIXED]
 * GFP_NOMMAP       0x00000020    [GFP_NOTRIM]               [MAP_ANON,MNODE_F_SHARED]
 * GFP_MAP_32BIT    0x00000040    [MAP_32BIT]                [MNODE_F_UNMAPPED]
 * GFP_MAP_PREPARED 0x00000080    [MAP_PREPARED,MNODE_F_MPREPARED]
 * GFP_MAP_BELOW    0x00000100    [MAP_GROWSDOWN]            [MNODE_F_COREPART]
 * GFP_MAP_ABOVE    0x00000200    [MAP_GROWSUP]              [MNODE_F_KERNPART]
 * -                0x00000400
 * GFP_ATOMIC       0x00000800    [O_NONBLOCK]
 * GFP_NOOVER       0x00001000
 * GFP_NOSWAP       0x00002000                               [MAP_LOCKED]
 * GFP_MCHEAP       0x00004000                               [MAP_NORESERVE]
 * GFP_NOMOVE       0x00008000    [MBNODE_F_POPULATE,MAP_POPULATE]               *GFP_NOMOVE overlap is not intended
 * -                0x00010000    [MBNODE_F_NONBLOCK,MAP_NONBLOCK]               *GFP_ATOMIC overlap would be nice, but not possible due to O_NONBLOCK
 * GFP_BLOCKING     0x00020000                               [MAP_STACK]
 * GFP_MAP_NOSPLIT  0x00040000    [MAP_NOSPLIT,MNODE_F_NOSPLIT]
 * GFP_MAP_NOMERGE  0x00080000    [MAP_NOMERGE,MNODE_F_NOMERGE]
 * -                0x00100000                               [MAP_FIXED_NOREPLACE]
 * -                0x04000000 [MAP_UNINITIALIZED]
 * GFP_MAP_NOASLR     0x40000000      [MAP_NOASLR]
 *
 */


/* >> uintptr_t mnodeflags_from_mapflags(unsigned int prot);
 * Convert `MAP_*' to `MNODE_F_*':
 *   - 0             ->  MNODE_F_NORMAL
 *   - MAP_PREPARED  ->  MNODE_F_MPREPARED
 *   - MAP_LOCKED    ->  MNODE_F_MLOCK
 *   - MAP_NOSPLIT   ->  MNODE_F_NOSPLIT
 *   - MAP_NOMERGE   ->  MNODE_F_NOMERGE */
#if (0 == MNODE_F_NORMAL &&               \
     MAP_PREPARED == MNODE_F_MPREPARED && \
     MAP_LOCKED == MNODE_F_MLOCK &&       \
     MAP_NOSPLIT == MNODE_F_NOSPLIT &&    \
     MAP_NOMERGE == MNODE_F_NOMERGE)
#define mnodeflags_from_mapflags(mapflags) \
	((mapflags) & (MAP_PREPARED | MAP_LOCKED | MAP_NOSPLIT | MAP_NOMERGE))
#define mapflags_from_mnodeflags(mapflags) \
	((mapflags) & (MNODE_F_MPREPARED | MNODE_F_MLOCK | MNODE_F_NOSPLIT | MNODE_F_NOMERGE))
#else /* ... */
#define mnodeflags_from_mapflags(mapflags)                 \
	((((mapflags)&MAP_PREPARED) ? MNODE_F_MPREPARED : 0) | \
	 (((mapflags)&MAP_LOCKED) ? MNODE_F_MLOCK : 0) |       \
	 (((mapflags)&MAP_NOSPLIT) ? MNODE_F_NOSPLIT : 0) |    \
	 (((mapflags)&MAP_NOMERGE) ? MNODE_F_NOMERGE : 0))
#define mapflags_from_mnodeflags(mapflags)                 \
	((((mapflags)&MNODE_F_MPREPARED) ? MAP_PREPARED : 0) | \
	 (((mapflags)&MNODE_F_MLOCK) ? MAP_LOCKED : 0) |       \
	 (((mapflags)&MNODE_F_NOSPLIT) ? MAP_NOSPLIT : 0) |    \
	 (((mapflags)&MNODE_F_NOMERGE) ? MAP_NOMERGE : 0))
#endif /* !... */

/* >> uintptr_t mnodeflags_from_mapflags_usronly(unsigned int prot);
 * Convert `MAP_*' to `MNODE_F_*':
 *   - 0           ->  MNODE_F_NORMAL
 *   - MAP_LOCKED  ->  MNODE_F_MLOCK */
#if (0 == MNODE_F_NORMAL && \
     MAP_LOCKED == MNODE_F_MLOCK)
#define mnodeflags_from_mapflags_usronly(mapflags) \
	((mapflags) & (MAP_LOCKED))
#define mapflags_from_mnodeflags_usronly(mapflags) \
	((mapflags) & (MNODE_F_MLOCK))
#else /* ... */
#define mnodeflags_from_mapflags_usronly(mapflags) \
	((((mapflags)&MAP_LOCKED) ? MNODE_F_MLOCK : 0))
#define mapflags_from_mnodeflags_usronly(mapflags) \
	((((mapflags)&MNODE_F_MLOCK) ? MAP_LOCKED : 0))
#endif /* !... */

/* >> uintptr_t mbnodeflags_from_mapflags(unsigned int prot);
 * Convert   `MAP_*'   to    `MNODE_F_*'   |    `MBNODE_F_*':
 *   - 0             ->  MNODE_F_NORMAL
 *   - MAP_PREPARED  ->  MNODE_F_MPREPARED
 *   - MAP_LOCKED    ->  MNODE_F_MLOCK
 *   - MAP_POPULATE  ->  MBNODE_F_POPULATE
 *   - MAP_NONBLOCK  ->  MBNODE_F_NONBLOCK
 *   - MAP_NOSPLIT   ->  MNODE_F_NOSPLIT
 *   - MAP_NOMERGE   ->  MNODE_F_NOMERGE */
#if (0 == MNODE_F_NORMAL &&               \
     MAP_PREPARED == MNODE_F_MPREPARED && \
     MAP_LOCKED == MNODE_F_MLOCK &&       \
     MAP_POPULATE == MBNODE_F_POPULATE && \
     MAP_NONBLOCK == MBNODE_F_NONBLOCK && \
     MAP_NOSPLIT == MNODE_F_NOSPLIT &&    \
     MAP_NOMERGE == MNODE_F_NOMERGE)
#define mbnodeflags_from_mapflags(mapflags)      \
	((mapflags) & (MAP_PREPARED | MAP_LOCKED |   \
	               MAP_POPULATE | MAP_NONBLOCK | \
	               MAP_NOSPLIT | MAP_NOMERGE))
#define mapflags_from_mbnodeflags(mbnodeflags)                \
	((mbnodeflags) & (MNODE_F_MPREPARED | MNODE_F_MLOCK |     \
	                  MBNODE_F_POPULATE | MBNODE_F_NONBLOCK | \
	                  MNODE_F_NOSPLIT | MNODE_F_NOMERGE))
#define mbnodeflags_from_mapflags_usronly(mapflags)      \
	((mapflags) & (MAP_LOCKED | MAP_POPULATE | MAP_NONBLOCK))
#define mapflags_from_mbnodeflags_usronly(mbnodeflags) \
	((mbnodeflags) & (MNODE_F_MLOCK | MBNODE_F_POPULATE | MBNODE_F_NONBLOCK))
#else /* ... */
#define mbnodeflags_from_mapflags(mapflags)                \
	((((mapflags)&MAP_PREPARED) ? MNODE_F_MPREPARED : 0) | \
	 (((mapflags)&MAP_LOCKED) ? MNODE_F_MLOCK : 0) |       \
	 (((mapflags)&MAP_POPULATE) ? MBNODE_F_POPULATE : 0) | \
	 (((mapflags)&MAP_NONBLOCK) ? MBNODE_F_NONBLOCK : 0) | \
	 (((mapflags)&MAP_NOSPLIT) ? MNODE_F_NOSPLIT : 0) |    \
	 (((mapflags)&MAP_NOMERGE) ? MNODE_F_NOMERGE : 0))
#define mapflags_from_mbnodeflags(mbnodeflags)                \
	((((mbnodeflags)&MNODE_F_MPREPARED) ? MAP_PREPARED : 0) | \
	 (((mbnodeflags)&MNODE_F_MLOCK) ? MAP_LOCKED : 0) |       \
	 (((mbnodeflags)&MBNODE_F_POPULATE) ? MAP_POPULATE : 0) | \
	 (((mbnodeflags)&MBNODE_F_NONBLOCK) ? MAP_NONBLOCK : 0) | \
	 (((mbnodeflags)&MNODE_F_NOSPLIT) ? MAP_NOSPLIT : 0) |    \
	 (((mbnodeflags)&MNODE_F_NOMERGE) ? MAP_NOMERGE : 0))
#define mbnodeflags_from_mapflags_usronly(mapflags)        \
	((((mapflags)&MAP_LOCKED) ? MNODE_F_MLOCK : 0) |       \
	 (((mapflags)&MAP_POPULATE) ? MBNODE_F_POPULATE : 0) | \
	 (((mapflags)&MAP_NONBLOCK) ? MBNODE_F_NONBLOCK : 0))
#define mapflags_from_mbnodeflags_usronly(mbnodeflags)        \
	((((mbnodeflags)&MNODE_F_MLOCK) ? MAP_LOCKED : 0) |       \
	 (((mbnodeflags)&MBNODE_F_POPULATE) ? MAP_POPULATE : 0) | \
	 (((mbnodeflags)&MBNODE_F_NONBLOCK) ? MAP_NONBLOCK : 0))
#endif /* !... */



/* >> uintptr_t mnodeflags_from_prot(unsigned int prot);
 * Convert `MAP_*' to `PROT_*':
 *   - PROT_NONE      ->  0
 *   - PROT_EXEC      ->  MNODE_F_PEXEC
 *   - PROT_WRITE     ->  MNODE_F_PWRITE
 *   - PROT_READ      ->  MNODE_F_PREAD
 *   - PROT_DENYWRITE ->  MNODE_F_PDENYWRITE   (Not in `mnodeflags_from_prot_noshared()')
 *   - PROT_SHARED    ->  MNODE_F_SHARED       (Not in `mnodeflags_from_prot_noshared()')
 */
#if (PROT_NONE == 0 &&                \
     PROT_EXEC == MNODE_F_PEXEC &&    \
     PROT_WRITE == MNODE_F_PWRITE &&  \
     PROT_READ == MNODE_F_PREAD &&    \
     PROT_SHARED == MNODE_F_SHARED && \
     PROT_DENYWRITE == MNODE_F_PDENYWRITE)
#define mnodeflags_from_prot(prot)              \
	((prot) & (MNODE_F_PEXEC | MNODE_F_PWRITE | \
	           MNODE_F_PREAD | MNODE_F_SHARED | \
	           MNODE_F_PDENYWRITE))
#define prot_from_mnodeflags(mnodeflags)       \
	((mnodeflags) & (PROT_EXEC | PROT_WRITE |  \
	                 PROT_READ | PROT_SHARED | \
	                 PROT_DENYWRITE))
#else /* ... */
#define mnodeflags_from_prot(prot)                 \
	((((prot)&PROT_EXEC) ? MNODE_F_PEXEC : 0) |    \
	 (((prot)&PROT_WRITE) ? MNODE_F_PWRITE : 0) |  \
	 (((prot)&PROT_READ) ? MNODE_F_PREAD : 0) |    \
	 (((prot)&PROT_SHARED) ? MNODE_F_SHARED : 0) | \
	 (((prot)&PROT_DENYWRITE) ? MNODE_F_PDENYWRITE : 0))
#define prot_from_mnodeflags(mnodeflags)                 \
	((((mnodeflags)&MNODE_F_PEXEC) ? PROT_EXEC : 0) |    \
	 (((mnodeflags)&MNODE_F_PWRITE) ? PROT_WRITE : 0) |  \
	 (((mnodeflags)&MNODE_F_PREAD) ? PROT_READ : 0) |    \
	 (((mnodeflags)&MNODE_F_SHARED) ? PROT_SHARED : 0) | \
	 (((mnodeflags)&MNODE_F_PDENYWRITE) ? PROT_DENYWRITE : 0))
#endif /* !... */
#if (PROT_NONE == 0 &&               \
     PROT_EXEC == MNODE_F_PEXEC &&   \
     PROT_WRITE == MNODE_F_PWRITE && \
     PROT_READ == MNODE_F_PREAD)
#define mnodeflags_from_prot_noshared(prot) \
	((prot) & (MNODE_F_PEXEC | MNODE_F_PWRITE | MNODE_F_PREAD))
#define prot_from_mnodeflags_noshared(mnodeflags) \
	((mnodeflags) & (PROT_EXEC | PROT_WRITE | PROT_READ))
#else /* ... */
#define mnodeflags_from_prot_noshared(prot)       \
	((((prot)&PROT_EXEC) ? MNODE_F_PEXEC : 0) |   \
	 (((prot)&PROT_WRITE) ? MNODE_F_PWRITE : 0) | \
	 (((prot)&PROT_READ) ? MNODE_F_PREAD : 0))
#define prot_from_mnodeflags_noshared(mnodeflags)       \
	((((mnodeflags)&MNODE_F_PEXEC) ? PROT_EXEC : 0) |   \
	 (((mnodeflags)&MNODE_F_PWRITE) ? PROT_WRITE : 0) | \
	 (((mnodeflags)&MNODE_F_PREAD) ? PROT_READ : 0))
#endif /* !... */


/* Evaluates to non-zero if `after' is more restrictive than `before',
 * in that at least one of the permissions from `before' is no  longer
 * apart of `after'. */
#define mnodeflags_prot_more_restrictive(before, after) \
	((((before) & ~(after)) & (MNODE_F_PEXEC | MNODE_F_PWRITE | MNODE_F_PREAD)) != 0)


/* >> unsigned int mapfindflags_from_gfp(gfp_t gfp);
 * Convert `GFP_*' to `MAP_*':
 *   - GFP_MAP_BELOW   ->  MAP_GROWSDOWN
 *   - GFP_MAP_ABOVE   ->  MAP_GROWSUP
 *   - GFP_MAP_NOASLR  ->  MAP_NOASLR
 * NOTE: Intended to construct flags for `mman_findunmapped()' from `gfp'! */
#if (GFP_MAP_BELOW == MAP_GROWSDOWN && \
     GFP_MAP_ABOVE == MAP_GROWSUP &&   \
     GFP_MAP_NOASLR == MAP_NOASLR)
#define mapfindflags_from_gfp(gfp) \
	((gfp) & (GFP_MAP_BELOW | GFP_MAP_ABOVE | GFP_MAP_NOASLR))
#define gfp_from_mapflags(gfp) \
	((gfp) & (MAP_GROWSDOWN | MAP_GROWSUP | MAP_NOASLR))
#else /* ... */
#define mapfindflags_from_gfp(gfp)                 \
	((((gfp)&GFP_MAP_BELOW) ? MAP_GROWSDOWN : 0) | \
	 (((gfp)&GFP_MAP_ABOVE) ? MAP_GROWSUP : 0) |   \
	 (((gfp)&GFP_MAP_NOASLR) ? MAP_NOASLR : 0))
#define gfp_from_mapflags(gfp)                     \
	((((gfp)&MAP_GROWSDOWN) ? GFP_MAP_BELOW : 0) | \
	 (((gfp)&MAP_GROWSUP) ? GFP_MAP_ABOVE : 0) |   \
	 (((gfp)&MAP_NOASLR) ? GFP_MAP_NOASLR : 0))
#endif /* !... */


/* >> unsigned int mnodeflags_from_gfp(gfp_t gfp);
 * Convert `GFP_*' to `MNODE_F_*':
 *   - GFP_MAP_PREPARED  ->  MNODE_F_MPREPARED
 *   - GFP_LOCKED        ->  MNODE_F_MLOCK
 *   - GFP_MAP_NOSPLIT   ->  MNODE_F_NOSPLIT
 *   - GFP_MAP_NOMERGE   ->  MNODE_F_NOMERGE */
#if (GFP_MAP_PREPARED == MNODE_F_MPREPARED && \
     GFP_LOCKED == MNODE_F_MLOCK &&           \
     GFP_MAP_NOSPLIT == MNODE_F_NOSPLIT &&    \
     GFP_MAP_NOMERGE == MNODE_F_NOMERGE)
#define mnodeflags_from_gfp(gfp) \
	((gfp) & (GFP_MAP_PREPARED | GFP_LOCKED | GFP_MAP_NOSPLIT | GFP_MAP_NOMERGE))
#elif (GFP_MAP_PREPARED == MNODE_F_MPREPARED && \
       GFP_MAP_NOSPLIT == MNODE_F_NOSPLIT &&    \
       GFP_MAP_NOMERGE == MNODE_F_NOMERGE)
#define mnodeflags_from_gfp(gfp)                                        \
	(((gfp) & (GFP_MAP_PREPARED | GFP_MAP_NOSPLIT | GFP_MAP_NOMERGE)) | \
	 (((gfp)&GFP_LOCKED) ? MNODE_F_MLOCK : 0))
#else /* ... */
#define mnodeflags_from_gfp(gfp)                          \
	((((gfp)&GFP_MAP_PREPARED) ? MNODE_F_MPREPARED : 0) | \
	 (((gfp)&GFP_LOCKED) ? MNODE_F_MLOCK : 0) |           \
	 (((gfp)&GFP_MAP_NOSPLIT) ? MNODE_F_NOSPLIT : 0) |    \
	 (((gfp)&GFP_MAP_NOMERGE) ? MNODE_F_NOMERGE : 0))
#endif /* !... */



/* >> unsigned int prot_from_elfpf(unsigned int elfpf);
 * Convert ELF's `PF_*' to `PROT_*':
 *   - PF_X  ->  PROT_EXEC
 *   - PF_W  ->  PROT_WRITE
 *   - PF_R  ->  PROT_READ */
#if (PF_X == PROT_EXEC && PF_W == PROT_WRITE && PF_R == PROT_READ)
#define prot_from_elfpf(elfpf) \
	((elfpf) & (PF_X | PF_W | PF_R))
#define elfpf_from_prot(prot) \
	((prot) & (PROT_EXEC | PROT_WRITE | PROT_READ))
#else /* ... */
#define prot_from_elfpf(elfpf)           \
	((((elfpf)&PF_X) ? PROT_EXEC : 0) |  \
	 (((elfpf)&PF_W) ? PROT_WRITE : 0) | \
	 (((elfpf)&PF_R) ? PROT_READ : 0))
#define elfpf_from_prot(prot)           \
	((((prot)&PROT_EXEC) ? PF_X : 0) |  \
	 (((prot)&PROT_WRITE) ? PF_W : 0) | \
	 (((prot)&PROT_READ) ? PF_R : 0))
#endif /* !... */



/* >> uintptr_t mnodeflags_from_elfpf(unsigned int elfpf);
 * Convert ELF's `PF_*' to `MNODE_F_P*':
 *   - PF_X  ->  MNODE_F_PEXEC
 *   - PF_W  ->  MNODE_F_PWRITE
 *   - PF_R  ->  MNODE_F_PREAD */
#if (PF_X == MNODE_F_PEXEC &&  \
     PF_W == MNODE_F_PWRITE && \
     PF_R == MNODE_F_PREAD)
#define mnodeflags_from_elfpf(elfpf) \
	((elfpf) & (PF_X | PF_W | PF_R))
#define elfpf_from_mnodeflags(mnodeflags) \
	((mnodeflags) & (MNODE_F_PEXEC | MNODE_F_PWRITE | MNODE_F_PREAD))
#else /* ... */
#define mnodeflags_from_elfpf(elfpf)         \
	((((elfpf)&PF_X) ? MNODE_F_PEXEC : 0) |  \
	 (((elfpf)&PF_W) ? MNODE_F_PWRITE : 0) | \
	 (((elfpf)&PF_R) ? MNODE_F_PREAD : 0))
#define elfpf_from_mnodeflags(mnodeflags)         \
	((((mnodeflags)&MNODE_F_PEXEC) ? PF_X : 0) |  \
	 (((mnodeflags)&MNODE_F_PWRITE) ? PF_W : 0) | \
	 (((mnodeflags)&MNODE_F_PREAD) ? PF_R : 0))
#endif /* !... */



/* >> unsigned int mapflags_from_remapflags(unsigned int elfpf);
 * Convert `MREMAP_*' to `MAP_*':
 *   - MREMAP_FIXED           -> MAP_FIXED
 *   - MREMAP_32BIT           -> MAP_32BIT
 *   - MREMAP_GROWSDOWN       -> MAP_GROWSDOWN
 *   - MREMAP_GROWSUP         -> MAP_GROWSUP
 *   - MREMAP_STACK           -> MAP_STACK
 *   - MREMAP_POPULATE        -> MAP_POPULATE
 *   - MREMAP_NONBLOCK        -> MAP_NONBLOCK
 *   - MREMAP_FIXED_NOREPLACE -> MAP_FIXED_NOREPLACE
 *   - MREMAP_NOASLR          -> MAP_NOASLR */
#if (__MREMAP_FIXED == __MAP_FIXED &&                     \
     __MREMAP_32BIT == __MAP_32BIT &&                     \
     __MREMAP_GROWSDOWN == __MAP_GROWSDOWN &&             \
     __MREMAP_GROWSUP == __MAP_GROWSUP &&                 \
     __MREMAP_STACK == __MAP_STACK &&                     \
     __MREMAP_POPULATE == __MAP_POPULATE &&               \
     __MREMAP_NONBLOCK == __MAP_NONBLOCK &&               \
     __MREMAP_FIXED_NOREPLACE == __MAP_FIXED_NOREPLACE && \
     __MREMAP_NOASLR == __MAP_NOASLR)
#define mapflags_from_remapflags(remapflags)                        \
	((remapflags) & (__MREMAP_FIXED | __MREMAP_32BIT |              \
	                 __MREMAP_GROWSDOWN | __MREMAP_GROWSUP |        \
	                 __MREMAP_STACK | __MREMAP_POPULATE |           \
	                 __MREMAP_NONBLOCK | __MREMAP_FIXED_NOREPLACE | \
	                 __MREMAP_NOASLR))
#define remapflags_from_mapflags(mapflags)                  \
	((mapflags) & (__MAP_FIXED | __MAP_32BIT |              \
	               __MAP_GROWSDOWN | __MAP_GROWSUP |        \
	               __MAP_STACK | __MAP_POPULATE |           \
	               __MAP_NONBLOCK | __MAP_FIXED_NOREPLACE | \
	               __MAP_NOASLR))
#elif (__MREMAP_32BIT == __MAP_32BIT &&                     \
       __MREMAP_GROWSDOWN == __MAP_GROWSDOWN &&             \
       __MREMAP_GROWSUP == __MAP_GROWSUP &&                 \
       __MREMAP_STACK == __MAP_STACK &&                     \
       __MREMAP_POPULATE == __MAP_POPULATE &&               \
       __MREMAP_NONBLOCK == __MAP_NONBLOCK &&               \
       __MREMAP_FIXED_NOREPLACE == __MAP_FIXED_NOREPLACE && \
       __MREMAP_NOASLR == __MAP_NOASLR)
#define mapflags_from_remapflags(remapflags)                         \
	(((remapflags) & (__MREMAP_32BIT | __MREMAP_GROWSDOWN |          \
	                  __MREMAP_GROWSUP | __MREMAP_STACK |            \
	                  __MREMAP_POPULATE | __MREMAP_NONBLOCK |        \
	                  __MREMAP_FIXED_NOREPLACE | __MREMAP_NOASLR)) | \
	 (((remapflags)&__MREMAP_FIXED) ? __MAP_FIXED : 0))
#define remapflags_from_mapflags(mapflags)                   \
	(((mapflags) & (__MAP_32BIT | __MAP_GROWSDOWN |          \
	                __MAP_GROWSUP | __MAP_STACK |            \
	                __MAP_POPULATE | __MAP_NONBLOCK |        \
	                __MAP_FIXED_NOREPLACE | __MAP_NOASLR)) | \
	 (((mapflags)&__MAP_FIXED) ? __MREMAP_FIXED : 0))
#else /* ... */
#define mapflags_from_remapflags(remapflags)                                 \
	((((remapflags)&__MREMAP_32BIT) ? __MAP_32BIT : 0) |                     \
	 (((remapflags)&__MREMAP_GROWSDOWN) ? __MAP_GROWSDOWN : 0) |             \
	 (((remapflags)&__MREMAP_GROWSUP) ? __MAP_GROWSUP : 0) |                 \
	 (((remapflags)&__MREMAP_STACK) ? __MAP_STACK : 0) |                     \
	 (((remapflags)&__MREMAP_POPULATE) ? __MAP_POPULATE : 0) |               \
	 (((remapflags)&__MREMAP_NONBLOCK) ? __MAP_NONBLOCK : 0) |               \
	 (((remapflags)&__MREMAP_FIXED_NOREPLACE) ? __MAP_FIXED_NOREPLACE : 0) | \
	 (((remapflags)&__MREMAP_NOASLR) ? __MAP_NOASLR : 0) |                   \
	 (((remapflags)&__MREMAP_FIXED) ? __MAP_FIXED : 0))
#define remapflags_from_mapflags(mapflags)                                 \
	((((mapflags)&__MAP_32BIT) ? __MREMAP_32BIT : 0) |                     \
	 (((mapflags)&__MAP_GROWSDOWN) ? __MREMAP_GROWSDOWN : 0) |             \
	 (((mapflags)&__MAP_GROWSUP) ? __MREMAP_GROWSUP : 0) |                 \
	 (((mapflags)&__MAP_STACK) ? __MREMAP_STACK : 0) |                     \
	 (((mapflags)&__MAP_POPULATE) ? __MREMAP_POPULATE : 0) |               \
	 (((mapflags)&__MAP_NONBLOCK) ? __MREMAP_NONBLOCK : 0) |               \
	 (((mapflags)&__MAP_FIXED_NOREPLACE) ? __MREMAP_FIXED_NOREPLACE : 0) | \
	 (((mapflags)&__MAP_NOASLR) ? __MREMAP_NOASLR : 0) |                   \
	 (((mapflags)&__MAP_FIXED) ? __MREMAP_FIXED : 0))
#endif /* !... */

/* >> unsigned int mapflags_from_remapflags_fndonly(unsigned int elfpf);
 * Convert `MREMAP_*' to `MAP_*':
 *   - MREMAP_FIXED           -> MAP_FIXED
 *   - MREMAP_32BIT           -> MAP_32BIT
 *   - MREMAP_GROWSDOWN       -> MAP_GROWSDOWN
 *   - MREMAP_GROWSUP         -> MAP_GROWSUP
 *   - MREMAP_STACK           -> MAP_STACK
 *   - MREMAP_FIXED_NOREPLACE -> MAP_FIXED_NOREPLACE
 *   - MREMAP_NOASLR          -> MAP_NOASLR */
#if (__MREMAP_FIXED == __MAP_FIXED &&                     \
     __MREMAP_32BIT == __MAP_32BIT &&                     \
     __MREMAP_GROWSDOWN == __MAP_GROWSDOWN &&             \
     __MREMAP_GROWSUP == __MAP_GROWSUP &&                 \
     __MREMAP_STACK == __MAP_STACK &&                     \
     __MREMAP_FIXED_NOREPLACE == __MAP_FIXED_NOREPLACE && \
     __MREMAP_NOASLR == __MAP_NOASLR)
#define mapflags_from_remapflags_fndonly(remapflags)             \
	((remapflags) & (__MREMAP_FIXED | __MREMAP_32BIT |           \
	                 __MREMAP_GROWSDOWN | __MREMAP_GROWSUP |     \
	                 __MREMAP_STACK | __MREMAP_FIXED_NOREPLACE | \
	                 __MREMAP_NOASLR))
#define remapflags_from_mapflags_fndonly(mapflags)       \
	((mapflags) & (__MAP_FIXED | __MAP_32BIT |           \
	               __MAP_GROWSDOWN | __MAP_GROWSUP |     \
	               __MAP_STACK | __MAP_FIXED_NOREPLACE | \
	               __MAP_NOASLR))
#elif (__MREMAP_32BIT == __MAP_32BIT &&                     \
       __MREMAP_GROWSDOWN == __MAP_GROWSDOWN &&             \
       __MREMAP_GROWSUP == __MAP_GROWSUP &&                 \
       __MREMAP_STACK == __MAP_STACK &&                     \
       __MREMAP_FIXED_NOREPLACE == __MAP_FIXED_NOREPLACE && \
       __MREMAP_NOASLR == __MAP_NOASLR)
#define mapflags_from_remapflags_fndonly(remapflags)                 \
	(((remapflags) & (__MREMAP_32BIT | __MREMAP_GROWSDOWN |          \
	                  __MREMAP_GROWSUP | __MREMAP_STACK |            \
	                  __MREMAP_FIXED_NOREPLACE | __MREMAP_NOASLR)) | \
	 (((remapflags)&__MREMAP_FIXED) ? __MAP_FIXED : 0))
#define remapflags_from_mapflags_fndonly(mapflags)           \
	(((mapflags) & (__MAP_32BIT | __MAP_GROWSDOWN |          \
	                __MAP_GROWSUP | __MAP_STACK |            \
	                __MAP_FIXED_NOREPLACE | __MAP_NOASLR)) | \
	 (((mapflags)&__MAP_FIXED) ? __MREMAP_FIXED : 0))
#else /* ... */
#define mapflags_from_remapflags_fndonly(remapflags)                         \
	((((remapflags)&__MREMAP_32BIT) ? __MAP_32BIT : 0) |                     \
	 (((remapflags)&__MREMAP_GROWSDOWN) ? __MAP_GROWSDOWN : 0) |             \
	 (((remapflags)&__MREMAP_GROWSUP) ? __MAP_GROWSUP : 0) |                 \
	 (((remapflags)&__MREMAP_STACK) ? __MAP_STACK : 0) |                     \
	 (((remapflags)&__MREMAP_FIXED_NOREPLACE) ? __MAP_FIXED_NOREPLACE : 0) | \
	 (((remapflags)&__MREMAP_NOASLR) ? __MAP_NOASLR : 0) |                   \
	 (((remapflags)&__MREMAP_FIXED) ? __MAP_FIXED : 0))
#define remapflags_from_mapflags_fndonly(mapflags)                         \
	((((mapflags)&__MAP_32BIT) ? __MREMAP_32BIT : 0) |                     \
	 (((mapflags)&__MAP_GROWSDOWN) ? __MREMAP_GROWSDOWN : 0) |             \
	 (((mapflags)&__MAP_GROWSUP) ? __MREMAP_GROWSUP : 0) |                 \
	 (((mapflags)&__MAP_STACK) ? __MREMAP_STACK : 0) |                     \
	 (((mapflags)&__MAP_FIXED_NOREPLACE) ? __MREMAP_FIXED_NOREPLACE : 0) | \
	 (((mapflags)&__MAP_NOASLR) ? __MREMAP_NOASLR : 0) |                   \
	 (((mapflags)&__MAP_FIXED) ? __MREMAP_FIXED : 0))
#endif /* !... */

/* >> unsigned int mapflags_from_remapflags_poponly(unsigned int elfpf);
 * Convert `MREMAP_*' to `MAP_*':
 *   - MREMAP_POPULATE        -> MAP_POPULATE
 *   - MREMAP_NONBLOCK        -> MAP_NONBLOCK */
#if (__MREMAP_POPULATE == __MAP_POPULATE && \
     __MREMAP_NONBLOCK == __MAP_NONBLOCK)
#define mapflags_from_remapflags_poponly(remapflags) \
	((remapflags) & (__MREMAP_POPULATE | __MREMAP_NONBLOCK))
#define remapflags_from_mapflags_poponly(mapflags) \
	((mapflags) & (__MAP_POPULATE | __MAP_NONBLOCK))
#else /* ... */
#define mapflags_from_remapflags_poponly(remapflags)           \
	((((remapflags)&__MREMAP_POPULATE) ? __MAP_POPULATE : 0) | \
	 (((remapflags)&__MREMAP_NONBLOCK) ? __MAP_NONBLOCK : 0))
#define remapflags_from_mapflags_poponly(mapflags)           \
	((((mapflags)&__MAP_POPULATE) ? __MREMAP_POPULATE : 0) | \
	 (((mapflags)&__MAP_NONBLOCK) ? __MREMAP_NONBLOCK : 0))
#endif /* !... */


DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_FLAGS_H */
