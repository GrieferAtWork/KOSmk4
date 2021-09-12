/* HASH CRC-32:0x1e371fad */
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
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/mman.h) */
/* (#) Portability: DJGPP         (/include/sys/mman.h) */
/* (#) Portability: FreeBSD       (/sys/sys/mman.h) */
/* (#) Portability: GNU C Library (/misc/sys/mman.h) */
/* (#) Portability: NetBSD        (/sys/sys/mman.h) */
/* (#) Portability: OpenBSD       (/sys/sys/mman.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/mman.h) */
/* (#) Portability: diet libc     (/include/sys/mman.h) */
/* (#) Portability: musl libc     (/include/sys/mman.h) */
/* (#) Portability: uClibc        (/include/sys/mman.h) */
#ifndef _SYS_MMAN_H
#define _SYS_MMAN_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <asm/os/mman.h>
#include <bits/types.h>


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


#if defined(__KOS__) && defined(__USE_KOS)
/* Unmap the region within the when cloning a VM (`CLONE_VM'). */
#if !defined(PROT_LOOSE) && defined(__PROT_LOOSE)
#define PROT_LOOSE __PROT_LOOSE
#endif /* !PROT_LOOSE && __PROT_LOOSE */

/* Changes are shared, even after the VM was cloned (`CLONE_VM').
 * NOTE: Same as the `MAP_SHARED' map flag, but
 *       can  be set like any other protection. */
#if !defined(PROT_SHARED) && defined(__PROT_SHARED)
#define PROT_SHARED __PROT_SHARED
#endif /* !PROT_SHARED && __PROT_SHARED */

#ifdef __USE_KOS_KERNEL
/* Map memory as inaccessible to user-space.
 * WARNING: Not fully enforced for addresses within user-memory. */
#if !defined(PROT_NOUSER) && defined(__PROT_NOUSER)
#define PROT_NOUSER __PROT_NOUSER
#endif /* !PROT_NOUSER && __PROT_NOUSER */

/* Unset whenever user-space re-maps a page as writable. - Cannot be removed.
 * NOTE: This flag is used to prevent rootfork() from working
 *       when called from an otherwise read-only module after
 *       some portion of the section containing the root-fork
 *       system call has been mapped as writable.
 *    >> rootfork() fails when any page in the calling section (.text)
 *       isn't  part  of  a  root-module,  isn't  fully  mapped,   was
 *       re-mapped somewhere else, or been made writable at any point. */
#if !defined(PROT_CLEAN) && defined(__PROT_CLEAN)
#define PROT_CLEAN __PROT_CLEAN
#endif /* !PROT_CLEAN && __PROT_CLEAN */

#endif /* __USE_KOS_KERNEL */
#endif /* __USE_KOS */

#ifdef __USE_KOS_KERNEL
 /* Mask of flags accessible from user-space. */
#if !defined(PROT_MASK) && defined(__PROT_MASK)
#define PROT_MASK __PROT_MASK
#endif /* !PROT_MASK && __PROT_MASK */
#endif /* __USE_KOS_KERNEL */



#ifdef __USE_KOS
/* Use sharing behavior specified by `PROT_SHARED'. */
#if !defined(MAP_AUTOMATIC) && defined(__MAP_AUTOMATIC)
#define MAP_AUTOMATIC __MAP_AUTOMATIC
#endif /* !MAP_AUTOMATIC && __MAP_AUTOMATIC */
#endif /* __USE_KOS */

/* Share changes. */
#if !defined(MAP_SHARED) && defined(__MAP_SHARED)
#define MAP_SHARED __MAP_SHARED
#endif /* !MAP_SHARED && __MAP_SHARED */

/* Changes are private. */
#if !defined(MAP_PRIVATE) && defined(__MAP_PRIVATE)
#define MAP_PRIVATE __MAP_PRIVATE
#endif /* !MAP_PRIVATE && __MAP_PRIVATE */

/* Interpret addr exactly. */
#if !defined(MAP_FIXED) && defined(__MAP_FIXED)
#define MAP_FIXED __MAP_FIXED
#endif /* !MAP_FIXED && __MAP_FIXED */


#ifdef __USE_MISC
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
#endif /* __USE_MISC */

/* Don't use a file. */
#if !defined(MAP_ANON) && defined(__MAP_ANON)
#define MAP_ANON __MAP_ANON
#endif /* !MAP_ANON && __MAP_ANON */


/* Other flags. */
#ifdef __USE_MISC
/* Only give out 32-bit addresses. */
#if !defined(MAP_32BIT) && defined(__MAP_32BIT)
#define MAP_32BIT __MAP_32BIT
#endif /* !MAP_32BIT && __MAP_32BIT */
#endif /* __USE_MISC */



#ifdef __USE_MISC
/* Stack-like segment. */
#if !defined(MAP_GROWSDOWN) && defined(__MAP_GROWSDOWN)
#define MAP_GROWSDOWN __MAP_GROWSDOWN
#endif /* !MAP_GROWSDOWN && __MAP_GROWSDOWN */

/* Stack-like segment growing upwards. */
#if !defined(MAP_GROWSUP) && defined(__MAP_GROWSUP)
#define MAP_GROWSUP __MAP_GROWSUP
#endif /* !MAP_GROWSUP && __MAP_GROWSUP */

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

/* XXX: Implement me? */
#if !defined(MAP_SYNC) && defined(__MAP_SYNC)
#define MAP_SYNC __MAP_SYNC
#endif /* !MAP_SYNC && __MAP_SYNC */


/* Create huge page mapping. */
#if !defined(MAP_HUGETLB) && defined(__MAP_HUGETLB)
#define MAP_HUGETLB __MAP_HUGETLB
#endif /* !MAP_HUGETLB && __MAP_HUGETLB */
#if !defined(MAP_HUGE_SHIFT) && defined(__MAP_HUGE_SHIFT)
#define MAP_HUGE_SHIFT __MAP_HUGE_SHIFT
#endif /* !MAP_HUGE_SHIFT && __MAP_HUGE_SHIFT */
#if !defined(MAP_HUGE_MASK) && defined(__MAP_HUGE_MASK)
#define MAP_HUGE_MASK __MAP_HUGE_MASK
#endif /* !MAP_HUGE_MASK && __MAP_HUGE_MASK */


/* For anonymous mmap, memory could be uninitialized. */
#if !defined(MAP_UNINITIALIZED) && defined(__MAP_UNINITIALIZED)
#define MAP_UNINITIALIZED __MAP_UNINITIALIZED
#endif /* !MAP_UNINITIALIZED && __MAP_UNINITIALIZED */

/* Don't  override  existing mappings  when `MAP_FIXED'  is passed.
 * Instead, throw an exception `E_BADALLOC_ADDRESS_ALREADY_EXISTS'. */
#if !defined(MAP_FIXED_NOREPLACE) && defined(__MAP_FIXED_NOREPLACE)
#define MAP_FIXED_NOREPLACE __MAP_FIXED_NOREPLACE
#endif /* !MAP_FIXED_NOREPLACE && __MAP_FIXED_NOREPLACE */

#ifdef __USE_KOS_KERNEL
/* The `offset' argument of MMAP is actually a pointer to the 64-bit
 * unsigned  integer  that  should  actually  be  used  as   offset. */
#if !defined(MAP_OFFSET64_POINTER) && defined(__MAP_OFFSET64_POINTER)
#define MAP_OFFSET64_POINTER __MAP_OFFSET64_POINTER
#endif /* !MAP_OFFSET64_POINTER && __MAP_OFFSET64_POINTER */
#endif /* __USE_KOS_KERNEL */
#endif /* __USE_MISC */


/************************************************************************/
/* Error return value for `mmap()'                                      */
/************************************************************************/
#if !defined(MAP_FAILED) && defined(__MAP_FAILED)
#define MAP_FAILED __MAP_FAILED
#endif /* !MAP_FAILED && __MAP_FAILED */


/* Extended flags for use with `mprotect()' */

/* Same as `MAP_GROWSDOWN', but may be used with `mprotect()' */
#if !defined(PROT_GROWSDOWN) && defined(__PROT_GROWSDOWN)
#define PROT_GROWSDOWN __PROT_GROWSDOWN
#endif /* !PROT_GROWSDOWN && __PROT_GROWSDOWN */

/* Same as `MAP_GROWSUP', but may be used with `mprotect()' */
#if !defined(PROT_GROWSUP) && defined(__PROT_GROWSUP)
#define PROT_GROWSUP __PROT_GROWSUP
#endif /* !PROT_GROWSUP && __PROT_GROWSUP */


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
/* Flags for 'mremap'.                                                  */
/************************************************************************/
#ifdef __USE_GNU
/* Allowed to move to a different location */
#if !defined(MREMAP_MAYMOVE) && defined(__MREMAP_MAYMOVE)
#define MREMAP_MAYMOVE __MREMAP_MAYMOVE
#endif /* !MREMAP_MAYMOVE && __MREMAP_MAYMOVE */

/* A 5th argument `new_address' is accepted that specifies the absolute, new position */
#if !defined(MREMAP_FIXED) && defined(__MREMAP_FIXED)
#define MREMAP_FIXED __MREMAP_FIXED
#endif /* !MREMAP_FIXED && __MREMAP_FIXED */

/* Used with `MREMAP_MAYMOVE': Don't delete the old mapping. */
#if !defined(MREMAP_DONTUNMAP) && defined(__MREMAP_DONTUNMAP)
#define MREMAP_DONTUNMAP __MREMAP_DONTUNMAP
#endif /* !MREMAP_DONTUNMAP && __MREMAP_DONTUNMAP */

#ifdef __USE_KOS
/* The following flags are accepted  by `mremap(2)', and affect  what
 * addresses are selected when the kernel has to choose a new address
 * for the resulting  mapping. (except  for `MREMAP_POPULATE',  which
 * simply pre-populates memory in case more got allocated) */
#if !defined(MREMAP_32BIT) && defined(__MREMAP_32BIT)
#define MREMAP_32BIT           __MREMAP_32BIT
#endif /* !MREMAP_32BIT && __MREMAP_32BIT */
#if !defined(MREMAP_GROWSDOWN) && defined(__MREMAP_GROWSDOWN)
#define MREMAP_GROWSDOWN       __MREMAP_GROWSDOWN
#endif /* !MREMAP_GROWSDOWN && __MREMAP_GROWSDOWN */
#if !defined(MREMAP_GROWSUP) && defined(__MREMAP_GROWSUP)
#define MREMAP_GROWSUP         __MREMAP_GROWSUP
#endif /* !MREMAP_GROWSUP && __MREMAP_GROWSUP */
#if !defined(MREMAP_STACK) && defined(__MREMAP_STACK)
#define MREMAP_STACK           __MREMAP_STACK
#endif /* !MREMAP_STACK && __MREMAP_STACK */
#if !defined(MREMAP_POPULATE) && defined(__MREMAP_POPULATE)
#define MREMAP_POPULATE        __MREMAP_POPULATE
#endif /* !MREMAP_POPULATE && __MREMAP_POPULATE */
#if !defined(MREMAP_NONBLOCK) && defined(__MREMAP_NONBLOCK)
#define MREMAP_NONBLOCK        __MREMAP_NONBLOCK
#endif /* !MREMAP_NONBLOCK && __MREMAP_NONBLOCK */
#if !defined(MREMAP_FIXED_NOREPLACE) && defined(__MREMAP_FIXED_NOREPLACE)
#define MREMAP_FIXED_NOREPLACE __MREMAP_FIXED_NOREPLACE
#endif /* !MREMAP_FIXED_NOREPLACE && __MREMAP_FIXED_NOREPLACE */
#if !defined(MREMAP_NOASLR) && defined(__MREMAP_NOASLR)
#define MREMAP_NOASLR          __MREMAP_NOASLR
#endif /* !MREMAP_NOASLR && __MREMAP_NOASLR */
#endif /* __USE_KOS */
#endif /* __USE_GNU */


/* DISCLAIMER: Documentation  strings for MADV_*, POSIX_MADV_* and MCL_* were
 *             taken from glibc /usr/include/i386-linux-gnu/bits/mman-linux.h */
/* Definitions for POSIX memory map interface.  Linux generic version.
   Copyright (C) 2001-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */


/************************************************************************/
/* Advice to `madvise(2)'.                                              */
/************************************************************************/
#ifdef __USE_MISC
/* No further special treatment. */
#if !defined(MADV_NORMAL) && defined(__MADV_NORMAL)
#define MADV_NORMAL __MADV_NORMAL
#endif /* !MADV_NORMAL && __MADV_NORMAL */

/* Expect random page references. */
#if !defined(MADV_RANDOM) && defined(__MADV_RANDOM)
#define MADV_RANDOM __MADV_RANDOM
#endif /* !MADV_RANDOM && __MADV_RANDOM */

/* Expect sequential page references. */
#if !defined(MADV_SEQUENTIAL) && defined(__MADV_SEQUENTIAL)
#define MADV_SEQUENTIAL __MADV_SEQUENTIAL
#endif /* !MADV_SEQUENTIAL && __MADV_SEQUENTIAL */

/* Will need these pages. */
#if !defined(MADV_WILLNEED) && defined(__MADV_WILLNEED)
#define MADV_WILLNEED __MADV_WILLNEED
#endif /* !MADV_WILLNEED && __MADV_WILLNEED */

/* Don't need these pages. */
#if !defined(MADV_DONTNEED) && defined(__MADV_DONTNEED)
#define MADV_DONTNEED __MADV_DONTNEED
#endif /* !MADV_DONTNEED && __MADV_DONTNEED */

/* Remove these pages and resources. */
#if !defined(MADV_REMOVE) && defined(__MADV_REMOVE)
#define MADV_REMOVE __MADV_REMOVE
#endif /* !MADV_REMOVE && __MADV_REMOVE */

/* Do not inherit across fork. */
#if !defined(MADV_DONTFORK) && defined(__MADV_DONTFORK)
#define MADV_DONTFORK __MADV_DONTFORK
#endif /* !MADV_DONTFORK && __MADV_DONTFORK */

/* Do inherit across fork. */
#if !defined(MADV_DOFORK) && defined(__MADV_DOFORK)
#define MADV_DOFORK __MADV_DOFORK
#endif /* !MADV_DOFORK && __MADV_DOFORK */

/* KSM may merge identical pages. */
#if !defined(MADV_MERGEABLE) && defined(__MADV_MERGEABLE)
#define MADV_MERGEABLE __MADV_MERGEABLE
#endif /* !MADV_MERGEABLE && __MADV_MERGEABLE */

/* KSM may not merge identical pages. */
#if !defined(MADV_UNMERGEABLE) && defined(__MADV_UNMERGEABLE)
#define MADV_UNMERGEABLE __MADV_UNMERGEABLE
#endif /* !MADV_UNMERGEABLE && __MADV_UNMERGEABLE */

/* Worth backing with hugepages. */
#if !defined(MADV_HUGEPAGE) && defined(__MADV_HUGEPAGE)
#define MADV_HUGEPAGE __MADV_HUGEPAGE
#endif /* !MADV_HUGEPAGE && __MADV_HUGEPAGE */

/* Not worth backing with hugepages. */
#if !defined(MADV_NOHUGEPAGE) && defined(__MADV_NOHUGEPAGE)
#define MADV_NOHUGEPAGE __MADV_NOHUGEPAGE
#endif /* !MADV_NOHUGEPAGE && __MADV_NOHUGEPAGE */

/* Explicity exclude from the core dump, overrides the coredump filter bits. */
#if !defined(MADV_DONTDUMP) && defined(__MADV_DONTDUMP)
#define MADV_DONTDUMP __MADV_DONTDUMP
#endif /* !MADV_DONTDUMP && __MADV_DONTDUMP */

/* Clear the MADV_DONTDUMP flag. */
#if !defined(MADV_DODUMP) && defined(__MADV_DODUMP)
#define MADV_DODUMP __MADV_DODUMP
#endif /* !MADV_DODUMP && __MADV_DODUMP */

/* Poison a page for testing. */
#if !defined(MADV_HWPOISON) && defined(__MADV_HWPOISON)
#define MADV_HWPOISON __MADV_HWPOISON
#endif /* !MADV_HWPOISON && __MADV_HWPOISON */
#endif /* __USE_MISC */


/************************************************************************/
/* The POSIX people had to invent similar names for the same things.    */
/************************************************************************/
#ifdef __USE_XOPEN2K
/* No further special treatment. */
#if !defined(POSIX_MADV_NORMAL) && defined(__POSIX_MADV_NORMAL)
#define POSIX_MADV_NORMAL __POSIX_MADV_NORMAL
#endif /* !POSIX_MADV_NORMAL && __POSIX_MADV_NORMAL */

/* Expect random page references. */
#if !defined(POSIX_MADV_RANDOM) && defined(__POSIX_MADV_RANDOM)
#define POSIX_MADV_RANDOM __POSIX_MADV_RANDOM
#endif /* !POSIX_MADV_RANDOM && __POSIX_MADV_RANDOM */

/* Expect sequential page references. */
#if !defined(POSIX_MADV_SEQUENTIAL) && defined(__POSIX_MADV_SEQUENTIAL)
#define POSIX_MADV_SEQUENTIAL __POSIX_MADV_SEQUENTIAL
#endif /* !POSIX_MADV_SEQUENTIAL && __POSIX_MADV_SEQUENTIAL */

/* Will need these pages. */
#if !defined(POSIX_MADV_WILLNEED) && defined(__POSIX_MADV_WILLNEED)
#define POSIX_MADV_WILLNEED __POSIX_MADV_WILLNEED
#endif /* !POSIX_MADV_WILLNEED && __POSIX_MADV_WILLNEED */

/* Don't need these pages. */
#if !defined(POSIX_MADV_DONTNEED) && defined(__POSIX_MADV_DONTNEED)
#define POSIX_MADV_DONTNEED __POSIX_MADV_DONTNEED
#endif /* !POSIX_MADV_DONTNEED && __POSIX_MADV_DONTNEED */
#endif /* __USE_XOPEN2K */


/************************************************************************/
/* Flags for `mlockall()'.                                              */
/************************************************************************/
#ifndef MCL_CURRENT
/* Lock all currently mapped pages. */
#if !defined(MCL_CURRENT) && defined(__MCL_CURRENT)
#define MCL_CURRENT __MCL_CURRENT
#endif /* !MCL_CURRENT && __MCL_CURRENT */

/* Lock all additions to address space. */
#if !defined(MCL_FUTURE) && defined(__MCL_FUTURE)
#define MCL_FUTURE __MCL_FUTURE
#endif /* !MCL_FUTURE && __MCL_FUTURE */

/* Lock all pages that are faulted in. */
#if !defined(MCL_ONFAULT) && defined(__MCL_ONFAULT)
#define MCL_ONFAULT __MCL_ONFAULT
#endif /* !MCL_ONFAULT && __MCL_ONFAULT */
#endif /* !MCL_CURRENT */


/************************************************************************/
/* Flags for `memfd_create()'                                           */
/************************************************************************/

/* Close-on-exec */
#if !defined(MFD_CLOEXEC) && defined(__MFD_CLOEXEC)
#define MFD_CLOEXEC __MFD_CLOEXEC
#endif /* !MFD_CLOEXEC && __MFD_CLOEXEC */

/* Allow use of `F_ADD_SEALS' and `F_GET_SEALS' (when not given, `F_SEAL_SEAL' is set on creation) */
#if !defined(MFD_ALLOW_SEALING) && defined(__MFD_ALLOW_SEALING)
#define MFD_ALLOW_SEALING __MFD_ALLOW_SEALING
#endif /* !MFD_ALLOW_SEALING && __MFD_ALLOW_SEALING */

/* ... */
#if !defined(MFD_HUGETLB) && defined(__MFD_HUGETLB)
#define MFD_HUGETLB __MFD_HUGETLB
#endif /* !MFD_HUGETLB && __MFD_HUGETLB */


/************************************************************************/
/* Flags for `mlock2()'                                                 */
/************************************************************************/

/* Delegate population of locked memory until the first access. */
#if !defined(MLOCK_ONFAULT) && defined(__MLOCK_ONFAULT)
#define MLOCK_ONFAULT __MLOCK_ONFAULT
#endif /* !MLOCK_ONFAULT && __MLOCK_ONFAULT */


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



#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __off_t_defined
#define __off_t_defined 1
typedef __FS_TYPE(off) off_t;
#endif /* !__off_t_defined */

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __mode_t_defined
#define __mode_t_defined 1
typedef __mode_t mode_t; /* INode type (Set of `S_*' from `<fcntl.h>' or `<sys/stat.h>') */
#endif /* !__mode_t_defined */

#if defined(__CRT_HAVE_mmap64) && defined(__USE_FILE_OFFSET64)
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE  | MAP_STACK | MAP_SYNC  |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE' */
__CREDIRECT(__ATTR_WUNUSED,void *,__NOTHROW_NCX,mmap,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __FS_TYPE(off) __offset),mmap64,(__addr,__len,__prot,__flags,__fd,__offset))
#elif defined(__CRT_HAVE_mmap) && !defined(__USE_FILE_OFFSET64)
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE  | MAP_STACK | MAP_SYNC  |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE' */
__CDECLARE(__ATTR_WUNUSED,void *,__NOTHROW_NCX,mmap,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __FS_TYPE(off) __offset),(__addr,__len,__prot,__flags,__fd,__offset))
#elif defined(__CRT_HAVE_mmap64) || defined(__CRT_HAVE_mmap)
#include <libc/local/sys.mman/mmap.h>
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE  | MAP_STACK | MAP_SYNC  |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mmap, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED void *__NOTHROW_NCX(__LIBCCALL mmap)(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __FS_TYPE(off) __offset) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mmap)(__addr, __len, __prot, __flags, __fd, __offset); })
#endif /* ... */
/* Unmap memory from `addr...+=len' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,munmap,(void *__addr, size_t __len),(__addr,__len))
/* @param prot: Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE |
 *              PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED |
 *              PROT_GROWSUP | PROT_GROWSDOWN' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,mprotect,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot),(__addr,__len,__prot))
/* @param flags: Set of `MS_ASYNC | MS_INVALIDATE | MS_SYNC' */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,msync,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __flags),(__addr,__len,__flags))
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,mlock,(void const *__addr, size_t __len),(__addr,__len))
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,munlock,(void const *__addr, size_t __len),(__addr,__len))
/* @param flags: Set of `MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT' */
__CDECLARE_OPT(,int,__NOTHROW_NCX,mlockall,(__STDC_INT_AS_UINT_T __flags),(__flags))
__CDECLARE_OPT(,int,__NOTHROW_NCX,munlockall,(void),())
#ifdef __CRT_HAVE_shm_open
__CDECLARE(__ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,shm_open,(char const *__name, __oflag_t __oflags, mode_t __mode),(__name,__oflags,__mode))
#else /* __CRT_HAVE_shm_open */
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <libc/local/sys.mman/shm_open.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(shm_open, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) __fd_t __NOTHROW_RPC(__LIBCCALL shm_open)(char const *__name, __oflag_t __oflags, mode_t __mode) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shm_open)(__name, __oflags, __mode); })
#endif /* __CRT_HAVE_open64 || __CRT_HAVE___open64 || __CRT_HAVE_open || __CRT_HAVE__open || __CRT_HAVE___open || (__AT_FDCWD && (__CRT_HAVE_openat64 || __CRT_HAVE_openat)) */
#endif /* !__CRT_HAVE_shm_open */
#ifdef __CRT_HAVE_shm_unlink
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,shm_unlink,(char const *__name),(__name))
#else /* __CRT_HAVE_shm_unlink */
#include <asm/os/fcntl.h>
#if defined(__CRT_HAVE_unlink) || defined(__CRT_HAVE__unlink) || (defined(__AT_FDCWD) && defined(__CRT_HAVE_unlinkat))
#include <libc/local/sys.mman/shm_unlink.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(shm_unlink, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL shm_unlink)(char const *__name) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(shm_unlink)(__name); })
#endif /* __CRT_HAVE_unlink || __CRT_HAVE__unlink || (__AT_FDCWD && __CRT_HAVE_unlinkat) */
#endif /* !__CRT_HAVE_shm_unlink */

#ifdef __USE_MISC
#ifdef __CRT_HAVE_madvise
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,madvise,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __advice),(__addr,__len,__advice))
#elif defined(__CRT_HAVE___madvise)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,madvise,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __advice),__madvise,(__addr,__len,__advice))
#else /* ... */
#include <libc/local/sys.mman/madvise.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(madvise, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL madvise)(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __advice) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(madvise)(__addr, __len, __advice); })
#endif /* !... */
__CDECLARE_OPT(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,mincore,(void *__start, size_t __len, unsigned char *__vec),(__start,__len,__vec))
#endif /* __USE_MISC */

#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_mmap64
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE  | MAP_STACK | MAP_SYNC  |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE' */
__CDECLARE(__ATTR_WUNUSED,void *,__NOTHROW_NCX,mmap64,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __off64_t __offset),(__addr,__len,__prot,__flags,__fd,__offset))
#elif defined(__CRT_HAVE_mmap) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE  | MAP_STACK | MAP_SYNC  |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE' */
__CREDIRECT(__ATTR_WUNUSED,void *,__NOTHROW_NCX,mmap64,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __off64_t __offset),mmap,(__addr,__len,__prot,__flags,__fd,__offset))
#elif defined(__CRT_HAVE_mmap)
#include <libc/local/sys.mman/mmap64.h>
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE  | MAP_STACK | MAP_SYNC  |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE' */
__NAMESPACE_LOCAL_USING_OR_IMPL(mmap64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_WUNUSED void *__NOTHROW_NCX(__LIBCCALL mmap64)(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot, __STDC_INT_AS_UINT_T __flags, __fd_t __fd, __off64_t __offset) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mmap64)(__addr, __len, __prot, __flags, __fd, __offset); })
#endif /* ... */
#endif /* __USE_LARGEFILE64 */

#ifdef __USE_XOPEN2K
#ifdef __CRT_HAVE_posix_madvise
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_NCX,posix_madvise,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __advice),(__addr,__len,__advice))
#else /* __CRT_HAVE_posix_madvise */
#include <libc/local/sys.mman/posix_madvise.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_madvise, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_NONNULL((1)) int __NOTHROW_NCX(__LIBCCALL posix_madvise)(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __advice) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_madvise)(__addr, __len, __advice); })
#endif /* !__CRT_HAVE_posix_madvise */
#endif /* __USE_XOPEN2K */

#ifdef __USE_GNU
#ifdef __CRT_HAVE_mremap
/* @param flags: Set of `MREMAP_MAYMOVE | MREMAP_FIXED' */
__LIBC void *__NOTHROW_NCX(__VLIBCCALL mremap)(void *__addr, size_t __old_len, size_t __new_len, __STDC_INT_AS_UINT_T __flags, ...) __CASMNAME_SAME("mremap");
#endif /* __CRT_HAVE_mremap */
__CDECLARE_OPT(,int,__NOTHROW_NCX,remap_file_pages,(void *__start, size_t __size, __STDC_INT_AS_UINT_T __prot, size_t __pgoff, __STDC_INT_AS_UINT_T __flags),(__start,__size,__prot,__pgoff,__flags))
__CDECLARE_OPT(,__fd_t,__NOTHROW_NCX,memfd_create,(char const *__name, unsigned int __flags),(__name,__flags))
__CDECLARE_OPT(,int,__NOTHROW_NCX,mlock2,(void const *__addr, size_t __length, unsigned int __flags),(__addr,__length,__flags))
__CDECLARE_OPT(,int,__NOTHROW_NCX,pkey_alloc,(unsigned int __flags, unsigned int __access_rights),(__flags,__access_rights))
#ifdef __CRT_HAVE_pkey_set
__CDECLARE(,int,__NOTHROW_NCX,pkey_set,(int __pkey, unsigned int __access_rights),(__pkey,__access_rights))
#else /* __CRT_HAVE_pkey_set */
#include <asm/pkey.h>
#ifdef __ARCH_HAVE_PKEY
#include <libc/local/sys.mman/pkey_set.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(pkey_set, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL pkey_set)(int __pkey, unsigned int __access_rights) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pkey_set)(__pkey, __access_rights); })
#endif /* __ARCH_HAVE_PKEY */
#endif /* !__CRT_HAVE_pkey_set */
#ifdef __CRT_HAVE_pkey_get
__CDECLARE(,int,__NOTHROW_NCX,pkey_get,(int __pkey),(__pkey))
#else /* __CRT_HAVE_pkey_get */
#include <asm/pkey.h>
#ifdef __ARCH_HAVE_PKEY
#include <libc/local/sys.mman/pkey_get.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(pkey_get, __FORCELOCAL __ATTR_ARTIFICIAL int __NOTHROW_NCX(__LIBCCALL pkey_get)(int __pkey) { return __NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(pkey_get)(__pkey); })
#endif /* __ARCH_HAVE_PKEY */
#endif /* !__CRT_HAVE_pkey_get */
__CDECLARE_OPT(,int,__NOTHROW_NCX,pkey_free,(int __pkey),(__pkey))
__CDECLARE_OPT(,int,__NOTHROW_NCX,pkey_mprotect,(void *__addr, size_t __len, __STDC_INT_AS_UINT_T __prot, int __pkey),(__addr,__len,__prot,__pkey))
#endif /* __USE_GNU */

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_SYS_MMAN_H)
#include <parts/uchar/sys/mman.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_SYS_MMAN_H */
#endif /* __USE_UTF */

#endif /* !_SYS_MMAN_H */
