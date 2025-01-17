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
/* (#) Portability: Linux (/usr/include/[...]/asm/mman.h) */
#ifndef _ASM_MMAN_H
#define _ASM_MMAN_H 1

#include <asm/os/mman.h>

/* Data cannot be accessed. */
#if !defined(PROT_NONE) && defined(__PROT_NONE)
#define PROT_NONE __PROT_NONE
#endif /* !PROT_NONE && __PROT_NONE */

/* Data can be executed. */
#if !defined(PROT_EXEC) && defined(__PROT_EXEC)
#define PROT_EXEC __PROT_EXEC
#endif /* !PROT_EXEC && __PROT_EXEC */

/* Data can be written. */
#if !defined(PROT_WRITE) && defined(__PROT_WRITE)
#define PROT_WRITE __PROT_WRITE
#endif /* !PROT_WRITE && __PROT_WRITE */

/* Data can be read. */
#if !defined(PROT_READ) && defined(__PROT_READ)
#define PROT_READ __PROT_READ
#endif /* !PROT_READ && __PROT_READ */

/* Ignored... */
#if !defined(PROT_SEM) && defined(__PROT_SEM)
#define PROT_SEM __PROT_SEM
#endif /* !PROT_SEM && __PROT_SEM */

/* Same as `MAP_GROWSDOWN', but may be used with `mprotect()' */
#if !defined(PROT_GROWSDOWN) && defined(__PROT_GROWSDOWN)
#define PROT_GROWSDOWN __PROT_GROWSDOWN
#endif /* !PROT_GROWSDOWN && __PROT_GROWSDOWN */

/* Same as `MAP_GROWSUP', but may be used with `mprotect()' */
#if !defined(PROT_GROWSUP) && defined(__PROT_GROWSUP)
#define PROT_GROWSUP __PROT_GROWSUP
#endif /* !PROT_GROWSUP && __PROT_GROWSUP */

#if !defined(PROT_BTI) && defined(__PROT_BTI)
#define PROT_BTI __PROT_BTI /* ??? */
#endif /* !PROT_BTI && __PROT_BTI */
#if !defined(PROT_MTE) && defined(__PROT_MTE)
#define PROT_MTE __PROT_MTE /* ??? */
#endif /* !PROT_MTE && __PROT_MTE */

/* Mask for type of mapping. */
#if !defined(MAP_TYPE) && defined(__MAP_TYPE)
#define MAP_TYPE __MAP_TYPE
#endif /* !MAP_TYPE && __MAP_TYPE */

/* Do use a file. */
#if !defined(MAP_FILE) && defined(__MAP_FILE)
#define MAP_FILE __MAP_FILE
#endif /* !MAP_FILE && __MAP_FILE */

/* Don't use a file. */
#if !defined(MAP_ANONYMOUS) && defined(__MAP_ANON)
#define MAP_ANONYMOUS __MAP_ANON
#endif /* !!MAP_ANONYMOUS && __MAP_ANONMAP_ANON */

/* Interpret addr exactly. */
#if !defined(MAP_FIXED) && defined(__MAP_FIXED)
#define MAP_FIXED __MAP_FIXED
#endif /* !MAP_FIXED && __MAP_FIXED */

/* Populate (prefault) pagetables. */
#if !defined(MAP_POPULATE) && defined(__MAP_POPULATE)
#define MAP_POPULATE __MAP_POPULATE
#endif /* !MAP_POPULATE && __MAP_POPULATE */

/* Do not block on IO. */
#if !defined(MAP_NONBLOCK) && defined(__MAP_NONBLOCK)
#define MAP_NONBLOCK __MAP_NONBLOCK
#endif /* !MAP_NONBLOCK && __MAP_NONBLOCK */

/* Allocation is for a stack.
 * NOTE: KOS  uses  this  flag  to  determine  where
 *       automatic memory mappings are allocated at. */
#if !defined(MAP_STACK) && defined(__MAP_STACK)
#define MAP_STACK __MAP_STACK
#endif /* !MAP_STACK && __MAP_STACK */

/* Create huge page mapping. */
#if !defined(MAP_HUGETLB) && defined(__MAP_HUGETLB)
#define MAP_HUGETLB __MAP_HUGETLB
#endif /* !MAP_HUGETLB && __MAP_HUGETLB */

/* XXX: Implement me? */
#if !defined(MAP_SYNC) && defined(__MAP_SYNC)
#define MAP_SYNC __MAP_SYNC
#endif /* !MAP_SYNC && __MAP_SYNC */

/* Don't  override  existing mappings  when `MAP_FIXED'  is passed.
 * Instead, throw an exception `E_BADALLOC_ADDRESS_ALREADY_EXISTS'. */
#if !defined(MAP_FIXED_NOREPLACE) && defined(__MAP_FIXED_NOREPLACE)
#define MAP_FIXED_NOREPLACE __MAP_FIXED_NOREPLACE
#endif /* !MAP_FIXED_NOREPLACE && __MAP_FIXED_NOREPLACE */

/* For anonymous mmap, memory could be uninitialized. */
#if !defined(MAP_UNINITIALIZED) && defined(__MAP_UNINITIALIZED)
#define MAP_UNINITIALIZED __MAP_UNINITIALIZED
#endif /* !MAP_UNINITIALIZED && __MAP_UNINITIALIZED */

/* Stack-like segment. */
#if !defined(MAP_GROWSDOWN) && defined(__MAP_GROWSDOWN)
#define MAP_GROWSDOWN __MAP_GROWSDOWN
#endif /* !MAP_GROWSDOWN && __MAP_GROWSDOWN */

/* Ignored. */
#if !defined(MAP_DENYWRITE) && defined(__MAP_DENYWRITE)
#define MAP_DENYWRITE __MAP_DENYWRITE
#endif /* !MAP_DENYWRITE && __MAP_DENYWRITE */

/* Ignored. */
#if !defined(MAP_EXECUTABLE) && defined(__MAP_EXECUTABLE)
#define MAP_EXECUTABLE __MAP_EXECUTABLE
#endif /* !MAP_EXECUTABLE && __MAP_EXECUTABLE */

/* Lock the mapping. */
#if !defined(MAP_LOCKED) && defined(__MAP_LOCKED)
#define MAP_LOCKED __MAP_LOCKED
#endif /* !MAP_LOCKED && __MAP_LOCKED */

/* Don't check for reservations. */
#if !defined(MAP_NORESERVE) && defined(__MAP_NORESERVE)
#define MAP_NORESERVE __MAP_NORESERVE
#endif /* !MAP_NORESERVE && __MAP_NORESERVE */

/* Delegate population of locked memory until the first access. */
#if !defined(MLOCK_ONFAULT) && defined(__MLOCK_ONFAULT)
#define MLOCK_ONFAULT __MLOCK_ONFAULT
#endif /* !MLOCK_ONFAULT && __MLOCK_ONFAULT */

/************************************************************************/
/* Flags accepted by `msync()'.                                         */
/************************************************************************/

/* Perform the operation asynchronously. */
#if !defined(MS_ASYNC) && defined(__MS_ASYNC)
#define MS_ASYNC __MS_ASYNC
#endif /* !MS_ASYNC && __MS_ASYNC */

/* Invalidate caches. */
#if !defined(MS_INVALIDATE) && defined(__MS_INVALIDATE)
#define MS_INVALIDATE __MS_INVALIDATE
#endif /* !MS_INVALIDATE && __MS_INVALIDATE */

/* Wait for the sync to finish. */
#if !defined(MS_SYNC) && defined(__MS_SYNC)
#define MS_SYNC __MS_SYNC
#endif /* !MS_SYNC && __MS_SYNC */


/************************************************************************/
/* Advice to `madvise(2)'.                                              */
/************************************************************************/
/* ??? */
#if !defined(MADV_NORMAL) && defined(__MADV_NORMAL)
#define MADV_NORMAL __MADV_NORMAL
#endif /* !MADV_NORMAL && __MADV_NORMAL */

/* ??? */
#if !defined(MADV_RANDOM) && defined(__MADV_RANDOM)
#define MADV_RANDOM __MADV_RANDOM
#endif /* !MADV_RANDOM && __MADV_RANDOM */

/* ??? */
#if !defined(MADV_SEQUENTIAL) && defined(__MADV_SEQUENTIAL)
#define MADV_SEQUENTIAL __MADV_SEQUENTIAL
#endif /* !MADV_SEQUENTIAL && __MADV_SEQUENTIAL */

/* ??? */
#if !defined(MADV_WILLNEED) && defined(__MADV_WILLNEED)
#define MADV_WILLNEED __MADV_WILLNEED
#endif /* !MADV_WILLNEED && __MADV_WILLNEED */

/* ??? */
#if !defined(MADV_DONTNEED) && defined(__MADV_DONTNEED)
#define MADV_DONTNEED __MADV_DONTNEED
#endif /* !MADV_DONTNEED && __MADV_DONTNEED */

/* ??? */
#if !defined(MADV_REMOVE) && defined(__MADV_REMOVE)
#define MADV_REMOVE __MADV_REMOVE
#endif /* !MADV_REMOVE && __MADV_REMOVE */

/* ??? */
#if !defined(MADV_DONTFORK) && defined(__MADV_DONTFORK)
#define MADV_DONTFORK __MADV_DONTFORK
#endif /* !MADV_DONTFORK && __MADV_DONTFORK */

/* ??? */
#if !defined(MADV_DOFORK) && defined(__MADV_DOFORK)
#define MADV_DOFORK __MADV_DOFORK
#endif /* !MADV_DOFORK && __MADV_DOFORK */

/* ??? */
#if !defined(MADV_MERGEABLE) && defined(__MADV_MERGEABLE)
#define MADV_MERGEABLE __MADV_MERGEABLE
#endif /* !MADV_MERGEABLE && __MADV_MERGEABLE */

/* ??? */
#if !defined(MADV_UNMERGEABLE) && defined(__MADV_UNMERGEABLE)
#define MADV_UNMERGEABLE __MADV_UNMERGEABLE
#endif /* !MADV_UNMERGEABLE && __MADV_UNMERGEABLE */

/* ??? */
#if !defined(MADV_HUGEPAGE) && defined(__MADV_HUGEPAGE)
#define MADV_HUGEPAGE __MADV_HUGEPAGE
#endif /* !MADV_HUGEPAGE && __MADV_HUGEPAGE */

/* ??? */
#if !defined(MADV_NOHUGEPAGE) && defined(__MADV_NOHUGEPAGE)
#define MADV_NOHUGEPAGE __MADV_NOHUGEPAGE
#endif /* !MADV_NOHUGEPAGE && __MADV_NOHUGEPAGE */

/* ??? */
#if !defined(MADV_DONTDUMP) && defined(__MADV_DONTDUMP)
#define MADV_DONTDUMP __MADV_DONTDUMP
#endif /* !MADV_DONTDUMP && __MADV_DONTDUMP */

/* ??? */
#if !defined(MADV_DODUMP) && defined(__MADV_DODUMP)
#define MADV_DODUMP __MADV_DODUMP
#endif /* !MADV_DODUMP && __MADV_DODUMP */

/* ??? */
#if !defined(MADV_HWPOISON) && defined(__MADV_HWPOISON)
#define MADV_HWPOISON __MADV_HWPOISON
#endif /* !MADV_HWPOISON && __MADV_HWPOISON */

#if !defined(MADV_FREE) && defined(__MADV_FREE)
#define MADV_FREE __MADV_FREE /* ??? */
#endif /* !MADV_FREE && __MADV_FREE */
#if !defined(MADV_SOFT_OFFLINE) && defined(__MADV_SOFT_OFFLINE)
#define MADV_SOFT_OFFLINE __MADV_SOFT_OFFLINE /* ??? */
#endif /* !MADV_SOFT_OFFLINE && __MADV_SOFT_OFFLINE */
#if !defined(MADV_WIPEONFORK) && defined(__MADV_WIPEONFORK)
#define MADV_WIPEONFORK __MADV_WIPEONFORK /* ??? */
#endif /* !MADV_WIPEONFORK && __MADV_WIPEONFORK */
#if !defined(MADV_KEEPONFORK) && defined(__MADV_KEEPONFORK)
#define MADV_KEEPONFORK __MADV_KEEPONFORK /* ??? */
#endif /* !MADV_KEEPONFORK && __MADV_KEEPONFORK */
#if !defined(MADV_COLD) && defined(__MADV_COLD)
#define MADV_COLD __MADV_COLD /* ??? */
#endif /* !MADV_COLD && __MADV_COLD */
#if !defined(MADV_PAGEOUT) && defined(__MADV_PAGEOUT)
#define MADV_PAGEOUT __MADV_PAGEOUT /* ??? */
#endif /* !MADV_PAGEOUT && __MADV_PAGEOUT */
#if !defined(MADV_POPULATE_READ) && defined(__MADV_POPULATE_READ)
#define MADV_POPULATE_READ __MADV_POPULATE_READ /* ??? */
#endif /* !MADV_POPULATE_READ && __MADV_POPULATE_READ */
#if !defined(MADV_POPULATE_WRITE) && defined(__MADV_POPULATE_WRITE)
#define MADV_POPULATE_WRITE __MADV_POPULATE_WRITE /* ??? */
#endif /* !MADV_POPULATE_WRITE && __MADV_POPULATE_WRITE */

/************************************************************************/
/* `ACCESS_RIGHTS' for `pkey_alloc()' and `pkey_set()'                  */
/************************************************************************/

/* ... */
#if !defined(PKEY_DISABLE_ACCESS) && defined(__PKEY_DISABLE_ACCESS)
#define PKEY_DISABLE_ACCESS __PKEY_DISABLE_ACCESS
#endif /* !PKEY_DISABLE_ACCESS && __PKEY_DISABLE_ACCESS */

/* ... */
#if !defined(PKEY_DISABLE_WRITE) && defined(__PKEY_DISABLE_WRITE)
#define PKEY_DISABLE_WRITE __PKEY_DISABLE_WRITE
#endif /* !PKEY_DISABLE_WRITE && __PKEY_DISABLE_WRITE */

/* ... */
#if !defined(PKEY_ACCESS_MASK) && defined(__PKEY_ACCESS_MASK)
#define PKEY_ACCESS_MASK __PKEY_ACCESS_MASK
#endif /* !PKEY_ACCESS_MASK && __PKEY_ACCESS_MASK */

/************************************************************************/
/* Flags for `mlockall()'.                                              */
/************************************************************************/

/* ??? */
#if !defined(MCL_CURRENT) && defined(__MCL_CURRENT)
#define MCL_CURRENT __MCL_CURRENT
#endif /* !MCL_CURRENT && __MCL_CURRENT */

/* ??? */
#if !defined(MCL_FUTURE) && defined(__MCL_FUTURE)
#define MCL_FUTURE __MCL_FUTURE
#endif /* !MCL_FUTURE && __MCL_FUTURE */

/* Delegate population of locked memory until the first access. */
#if !defined(MCL_ONFAULT) && defined(__MCL_ONFAULT)
#define MCL_ONFAULT __MCL_ONFAULT
#endif /* !MCL_ONFAULT && __MCL_ONFAULT */

#endif /* !_ASM_MMAN_H */
