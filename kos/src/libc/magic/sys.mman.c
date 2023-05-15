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
%(c_prefix){
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/mman.h) */
/* (#) Portability: DJGPP         (/include/sys/mman.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/mman.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/mman.h) */
/* (#) Portability: FreeBSD       (/sys/sys/mman.h) */
/* (#) Portability: GNU C Library (/misc/sys/mman.h) */
/* (#) Portability: NetBSD        (/sys/sys/mman.h) */
/* (#) Portability: OpenBSD       (/sys/sys/mman.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/mman.h) */
/* (#) Portability: diet libc     (/include/sys/mman.h) */
/* (#) Portability: libc4/5       (/include/sys/mman.h) */
/* (#) Portability: musl libc     (/include/sys/mman.h) */
/* (#) Portability: uClibc        (/include/sys/mman.h) */
}

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(off_t = "__off_t")]
%[define_replacement(pos_t = "__pos_t")]
%[define_replacement(off32_t = __off32_t)]
%[define_replacement(off64_t = __off64_t)]
%[define_replacement(pos32_t = __pos32_t)]
%[define_replacement(pos64_t = __pos64_t)]
%[define_replacement(mode_t = __mode_t)]
%[define_replacement(oflag_t = __oflag_t)]
%[default:section(".text.crt{|.dos}.system.mman")]

%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <asm/os/mman.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{


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
/* Unmap the region within the when cloning a VM (`CLONE_VM'). (KOSmk3 only) */
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
/* Error return value for `mmap(2)'                                     */
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
/* Flags accepted by `msync(2)'                                         */
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
/* Flags for `mremap(2)'                                                */
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


/************************************************************************/
/* Advice to `madvise(2)'                                               */
/************************************************************************/
#ifdef __USE_MISC
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
#endif /* __USE_MISC */



/************************************************************************/
/* Advice to `posix_madvise(2)'.                                        */
/************************************************************************/
#ifdef __USE_XOPEN2K
/* ??? */
#if !defined(POSIX_MADV_NORMAL) && defined(__POSIX_MADV_NORMAL)
#define POSIX_MADV_NORMAL __POSIX_MADV_NORMAL
#endif /* !POSIX_MADV_NORMAL && __POSIX_MADV_NORMAL */

/* ??? */
#if !defined(POSIX_MADV_RANDOM) && defined(__POSIX_MADV_RANDOM)
#define POSIX_MADV_RANDOM __POSIX_MADV_RANDOM
#endif /* !POSIX_MADV_RANDOM && __POSIX_MADV_RANDOM */

/* ??? */
#if !defined(POSIX_MADV_SEQUENTIAL) && defined(__POSIX_MADV_SEQUENTIAL)
#define POSIX_MADV_SEQUENTIAL __POSIX_MADV_SEQUENTIAL
#endif /* !POSIX_MADV_SEQUENTIAL && __POSIX_MADV_SEQUENTIAL */

/* ??? */
#if !defined(POSIX_MADV_WILLNEED) && defined(__POSIX_MADV_WILLNEED)
#define POSIX_MADV_WILLNEED __POSIX_MADV_WILLNEED
#endif /* !POSIX_MADV_WILLNEED && __POSIX_MADV_WILLNEED */

/* ??? */
#if !defined(POSIX_MADV_DONTNEED) && defined(__POSIX_MADV_DONTNEED)
#define POSIX_MADV_DONTNEED __POSIX_MADV_DONTNEED
#endif /* !POSIX_MADV_DONTNEED && __POSIX_MADV_DONTNEED */
#endif /* __USE_XOPEN2K */



/************************************************************************/
/* Flags for `mlockall(2)'.                                             */
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



/************************************************************************/
/* Flags for `memfd_create(2)'                                          */
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

#ifdef __USE_KOS
/* Close-on-fork */
#if !defined(MFD_CLOFORK) && defined(__MFD_CLOFORK)
#define MFD_CLOFORK __MFD_CLOFORK
#endif /* !MFD_CLOFORK && __MFD_CLOFORK */
#endif /* __USE_KOS */



/************************************************************************/
/* Flags for `mlock2(2)'                                                */
/************************************************************************/

/* Delegate population of locked memory until the first access. */
#if !defined(MLOCK_ONFAULT) && defined(__MLOCK_ONFAULT)
#define MLOCK_ONFAULT __MLOCK_ONFAULT
#endif /* !MLOCK_ONFAULT && __MLOCK_ONFAULT */



/************************************************************************/
/* `ACCESS_RIGHTS' for `pkey_alloc(2)' and `pkey_set(2)'                */
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
#define __off_t_defined
typedef __off_t off_t;
#endif /* !__off_t_defined */

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __mode_t_defined
#define __mode_t_defined
typedef __mode_t mode_t; /* INode type (Set of `S_*' from `<fcntl.h>' or `<sys/stat.h>') */
#endif /* !__mode_t_defined */

}

%[define(DEFINE_PIO_OFFSET =
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
)]

%[insert:prefix(DEFINE_PIO_OFFSET)]

%[assume_defined_in_kos(PROT_NONE, __PROT_NONE)]
%[assume_defined_in_kos(PROT_EXEC, __PROT_EXEC)]
%[assume_defined_in_kos(PROT_WRITE, __PROT_WRITE)]
%[assume_defined_in_kos(PROT_READ, __PROT_READ)]
%[assume_defined_in_kos(PROT_SEM, __PROT_SEM)]
%[assume_defined_in_kos(PROT_MASK, __PROT_MASK)]
%[assume_defined_in_kos(PROT_GROWSDOWN, __PROT_GROWSDOWN)]
%[assume_defined_in_kos(PROT_GROWSUP, __PROT_GROWSUP)]
%[assume_defined_in_kos(MAP_SHARED, __MAP_SHARED)]
%[assume_defined_in_kos(MAP_PRIVATE, __MAP_PRIVATE)]
%[assume_defined_in_kos(MAP_TYPE, __MAP_TYPE)]
%[assume_defined_in_kos(MAP_FILE, __MAP_FILE)]
%[assume_defined_in_kos(MAP_FIXED, __MAP_FIXED)]
%[assume_defined_in_kos(MAP_ANON, __MAP_ANON)]
%[assume_defined_in_kos(MAP_32BIT, __MAP_32BIT)]
%[assume_defined_in_kos(MAP_GROWSDOWN, __MAP_GROWSDOWN)]
%[assume_defined_in_kos(MAP_GROWSUP, __MAP_GROWSUP)]
%[assume_defined_in_kos(MAP_DENYWRITE, __MAP_DENYWRITE)]
%[assume_defined_in_kos(MAP_EXECUTABLE, __MAP_EXECUTABLE)]
%[assume_defined_in_kos(MAP_LOCKED, __MAP_LOCKED)]
%[assume_defined_in_kos(MAP_NORESERVE, __MAP_NORESERVE)]
%[assume_defined_in_kos(MAP_POPULATE, __MAP_POPULATE)]
%[assume_defined_in_kos(MAP_NONBLOCK, __MAP_NONBLOCK)]
%[assume_defined_in_kos(MAP_STACK, __MAP_STACK)]
%[assume_defined_in_kos(MAP_SYNC, __MAP_SYNC)]
%[assume_defined_in_kos(MAP_HUGETLB, __MAP_HUGETLB)]
%[assume_defined_in_kos(MAP_FIXED_NOREPLACE, __MAP_FIXED_NOREPLACE)]
%[assume_defined_in_kos(MAP_UNINITIALIZED, __MAP_UNINITIALIZED)]
%[assume_defined_in_kos(MAP_HUGE_SHIFT, __MAP_HUGE_SHIFT)]
%[assume_defined_in_kos(MAP_HUGE_MASK, __MAP_HUGE_MASK)]
%[assume_defined_in_kos(MAP_AUTOMATIC, __MAP_AUTOMATIC)]
%[assume_defined_in_kos(MAP_NOASLR, __MAP_NOASLR)]
%[assume_defined_in_kos(MAP_OFFSET64_POINTER, __MAP_OFFSET64_POINTER)]
%[assume_defined_in_kos(MAP_FAILED, __MAP_FAILED)]
%[assume_defined_in_kos(MS_ASYNC, __MS_ASYNC)]
%[assume_defined_in_kos(MS_INVALIDATE, __MS_INVALIDATE)]
%[assume_defined_in_kos(MS_SYNC, __MS_SYNC)]
%[assume_defined_in_kos(MREMAP_MAYMOVE, __MREMAP_MAYMOVE)]
%[assume_defined_in_kos(MREMAP_FIXED, __MREMAP_FIXED)]
%[assume_defined_in_kos(MREMAP_32BIT, __MREMAP_32BIT)]
%[assume_defined_in_kos(MREMAP_GROWSDOWN, __MREMAP_GROWSDOWN)]
%[assume_defined_in_kos(MREMAP_GROWSUP, __MREMAP_GROWSUP)]
%[assume_defined_in_kos(MREMAP_POPULATE, __MREMAP_POPULATE)]
%[assume_defined_in_kos(MREMAP_NONBLOCK, __MREMAP_NONBLOCK)]
%[assume_defined_in_kos(MREMAP_STACK, __MREMAP_STACK)]
%[assume_defined_in_kos(MREMAP_FIXED_NOREPLACE, __MREMAP_FIXED_NOREPLACE)]
%[assume_defined_in_kos(MREMAP_NOASLR, __MREMAP_NOASLR)]
%[assume_defined_in_kos(MFD_CLOEXEC, __MFD_CLOEXEC)]
%[assume_defined_in_kos(MFD_ALLOW_SEALING, __MFD_ALLOW_SEALING)]
%[assume_defined_in_kos(MFD_HUGETLB, __MFD_HUGETLB)]
%[assume_defined_in_kos(MFD_CLOFORK, __MFD_CLOFORK)]
%[assume_defined_in_kos(MLOCK_ONFAULT, __MLOCK_ONFAULT)]
%[assume_defined_in_kos(PKEY_DISABLE_ACCESS, __PKEY_DISABLE_ACCESS)]
%[assume_defined_in_kos(PKEY_DISABLE_WRITE, __PKEY_DISABLE_WRITE)]
%[assume_defined_in_kos(MADV_NORMAL, __MADV_NORMAL)]
%[assume_defined_in_kos(MADV_RANDOM, __MADV_RANDOM)]
%[assume_defined_in_kos(MADV_SEQUENTIAL, __MADV_SEQUENTIAL)]
%[assume_defined_in_kos(MADV_WILLNEED, __MADV_WILLNEED)]
%[assume_defined_in_kos(MADV_DONTNEED, __MADV_DONTNEED)]
%[assume_defined_in_kos(MADV_REMOVE, __MADV_REMOVE)]
%[assume_defined_in_kos(MADV_DONTFORK, __MADV_DONTFORK)]
%[assume_defined_in_kos(MADV_DOFORK, __MADV_DOFORK)]
%[assume_defined_in_kos(MADV_MERGEABLE, __MADV_MERGEABLE)]
%[assume_defined_in_kos(MADV_UNMERGEABLE, __MADV_UNMERGEABLE)]
%[assume_defined_in_kos(MADV_HUGEPAGE, __MADV_HUGEPAGE)]
%[assume_defined_in_kos(MADV_NOHUGEPAGE, __MADV_NOHUGEPAGE)]
%[assume_defined_in_kos(MADV_DONTDUMP, __MADV_DONTDUMP)]
%[assume_defined_in_kos(MADV_DODUMP, __MADV_DODUMP)]
%[assume_defined_in_kos(MADV_HWPOISON, __MADV_HWPOISON)]
%[assume_defined_in_kos(POSIX_MADV_NORMAL, __POSIX_MADV_NORMAL)]
%[assume_defined_in_kos(POSIX_MADV_RANDOM, __POSIX_MADV_RANDOM)]
%[assume_defined_in_kos(POSIX_MADV_SEQUENTIAL, __POSIX_MADV_SEQUENTIAL)]
%[assume_defined_in_kos(POSIX_MADV_WILLNEED, __POSIX_MADV_WILLNEED)]
%[assume_defined_in_kos(POSIX_MADV_DONTNEED, __POSIX_MADV_DONTNEED)]
%[assume_defined_in_kos(MCL_CURRENT, __MCL_CURRENT)]
%[assume_defined_in_kos(MCL_FUTURE, __MCL_FUTURE)]
%[assume_defined_in_kos(MCL_ONFAULT, __MCL_ONFAULT)]


[[decl_include("<features.h>", "<bits/types.h>")]]
[[doc_alias("mmap"), ignore, nocrt, alias("mmap", "__mmap")]]
void *mmap32([[access(none)]] void *addr, size_t len, __STDC_INT_AS_UINT_T prot,
             __STDC_INT_AS_UINT_T flags, $fd_t fd, $off32_t offset);

@@>> mmap(2), mmap64(2)
@@@param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED'
@@@param flags: One of `MAP_SHARED', 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
@@              with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
@@              MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE  | MAP_STACK | MAP_SYNC  |
@@              MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE'
[[wunused, decl_include("<features.h>", "<bits/types.h>"), decl_prefix(DEFINE_PIO_OFFSET), no_crt_self_import]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>")!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("mmap", "__mmap")]]
[[if($extended_include_prefix("<features.h>", "<bits/types.h>") defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), alias("mmap64")]]
[[userimpl, requires($has_function(mmap32) || $has_function(mmap64))]]
[[section(".text.crt{|.dos}.heap.mman")]]
void *mmap([[access(none)]] void *addr, size_t len, __STDC_INT_AS_UINT_T prot,
           __STDC_INT_AS_UINT_T flags, $fd_t fd, __PIO_OFFSET offset) {
@@pp_if $has_function(mmap64)@@
	return mmap64(addr, len, prot, flags, fd, (__PIO_OFFSET64)offset);
@@pp_else@@
	return mmap32(addr, len, prot, flags, fd, (off32_t)(off_t)(pos_t)offset);
@@pp_endif@@
}

@@>> munmap(2)
@@Unmap memory from `addr...+=len'
[[section(".text.crt{|.dos}.heap.mman")]]
[[decl_include("<hybrid/typecore.h>")]]
[[export_alias("__munmap", "__libc_munmap")]]
int munmap([[access(none)]] void *addr, size_t len);

@@>> mprotect(2)
@@@param prot: Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE |
@@             PROT_READ | PROT_SEM | PROT_GROWSUP | PROT_GROWSDOWN'
[[decl_include("<features.h>", "<hybrid/typecore.h>"), section(".text.crt{|.dos}.system.mman")]]
[[export_alias("__mprotect", "__libc_mprotect")]]
int mprotect([[access(none)]] void *addr, size_t len, __STDC_INT_AS_UINT_T prot);

@@>> msync(2)
@@@param flags: Set of `MS_ASYNC | MS_INVALIDATE | MS_SYNC'
[[cp, decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[export_alias("__msync", "__libc_msync")]]
int msync([[access(none)]] void *addr, size_t len, __STDC_INT_AS_UINT_T flags);

@@>> mlock(2)
[[decl_include("<hybrid/typecore.h>")]]
[[export_alias("__mlock", "__libc_mlock")]]
int mlock([[access(none)]] void const *addr, size_t len);

@@>> munlock(2)
[[decl_include("<hybrid/typecore.h>")]]
[[export_alias("__munlock", "__libc_munlock")]]
int munlock([[access(none)]] void const *addr, size_t len);

@@>> mlockall(2)
@@@param flags: Set of `MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT'
[[decl_include("<features.h>")]]
[[export_alias("__mlockall", "__libc_mlockall")]]
int mlockall(__STDC_INT_AS_UINT_T flags);

@@>> munlockall(2)
[[export_alias("__munlockall", "__libc_munlockall")]]
int munlockall();

@@>> shm_open(3)
[[cp, decl_include("<bits/types.h>"), requires_function(open)]]
[[impl_include("<asm/os/paths.h>", "<asm/os/oflags.h>")]]
[[impl_include("<parts/malloca.h>", "<libc/errno.h>")]]
[[impl_include("<bits/types.h>")]]
$fd_t shm_open([[in]] char const *name,
               $oflag_t oflags, mode_t mode) {
	fd_t result;
	char *fullname;
	size_t namelen;
@@pp_if defined(O_DOSPATH)@@
	if (oflags & O_DOSPATH) {
		while (*name == '/' || *name == '\\')
			++name;
	} else {
		while (*name == '/')
			++name;
	}
@@pp_elif defined(_WIN32)@@
	while (*name == '/' || *name == '\\')
		++name;
@@pp_else@@
	while (*name == '/')
		++name;
@@pp_endif@@
	namelen  = strlen(name);
	fullname = (char *)__malloca((__COMPILER_STRLEN(__PATH_SHM) + 1 +
	                              namelen + 1) *
	                             sizeof(char));
	if unlikely(!fullname)
		return -1;
	memcpy(mempcpy(fullname, __PATH_SHM "/",
	               (__COMPILER_STRLEN(__PATH_SHM) + 1) *
	               sizeof(char)),
	       fullname,
	       (namelen + 1) *
	       sizeof(char));
	result = open(fullname, oflags, mode);
@@pp_if defined(ENOENT) && defined(O_CREAT) && $has_function(mkdir)@@
	if (result < 0 && (oflags & O_CREAT) != 0 && __libc_geterrno_or(ENOENT) == ENOENT) {
		/* Lazily create the SHM directory (/dev/shm), if it hadn't been created already.
		 * XXX:   This    assumes    that    `headof(__PATH_SHM)'    already    exists... */
		mkdir(__PATH_SHM, 0777);
		result = open(fullname, oflags, mode);
	}
@@pp_endif@@
	__freea(fullname);
	return result;
}

@@>> shm_unlink(3)
[[cp, requires_function(unlink)]]
[[impl_include("<asm/os/paths.h>")]]
[[impl_include("<hybrid/typecore.h>")]]
[[impl_include("<parts/malloca.h>")]]
int shm_unlink([[in]] char const *name) {
	int result;
	char *fullname;
	size_t namelen;
@@pp_ifdef _WIN32@@
	while (*name == '/' || *name == '\\')
		++name;
@@pp_else@@
	while (*name == '/')
		++name;
@@pp_endif@@
	namelen  = strlen(name);
	fullname = (char *)__malloca((__COMPILER_STRLEN(__PATH_SHM) + 1 +
	                              namelen + 1) *
	                             sizeof(char));
	if unlikely(!fullname)
		return -1;
	memcpy(mempcpy(fullname, __PATH_SHM "/",
	               (__COMPILER_STRLEN(__PATH_SHM) + 1) *
	               sizeof(char)),
	       fullname,
	       (namelen + 1) *
	       sizeof(char));
	result = unlink(fullname);
	__freea(fullname);
	return result;
}


%
%#ifdef __USE_MISC

[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[userimpl, export_alias("__madvise")]]
int madvise([[access(none)]] void *addr, size_t len,
            __STDC_INT_AS_UINT_T advice) {
	/* Implement as a no-op, since this function is merely meant as a hint */
	COMPILER_IMPURE();
	(void)addr;
	(void)len;
	(void)advice;
	return 0;
}

[[decl_include("<hybrid/typecore.h>")]]
int mincore([[access(none)]] void *start, size_t len, unsigned char *vec);

%#endif /* __USE_MISC */


%
%#ifdef __USE_LARGEFILE64
[[decl_include("<features.h>", "<bits/types.h>")]]
[[wunused, section(".text.crt{|.dos}.heap.mman")]]
[[doc_alias("mmap"), preferred_off64_variant_of(mmap)]]
[[if($extended_include_prefix("<bits/types.h>")__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__), preferred_alias("__mmap")]]
[[userimpl, requires_function(mmap32), decl_prefix(DEFINE_PIO_OFFSET)]]
void *mmap64([[access(none)]] void *addr, size_t len, __STDC_INT_AS_UINT_T prot,
             __STDC_INT_AS_UINT_T flags, $fd_t fd, __PIO_OFFSET64 offset) {
	return mmap32(addr, len, prot, flags, fd, (off32_t)(pos32_t)(pos64_t)offset);
}
%#endif /* __USE_LARGEFILE64 */


%
%#ifdef __USE_XOPEN2K

[[userimpl, decl_include("<features.h>", "<hybrid/typecore.h>")]]
int posix_madvise([[access(none)]] void *addr, size_t len,
                  __STDC_INT_AS_UINT_T advice) {
	/* Implement as a no-op, since this function is merely meant as a hint */
	COMPILER_IMPURE();
	(void)addr;
	(void)len;
	(void)advice;
	return 0;
}

%#endif /* __USE_XOPEN2K */

%
%#ifdef __USE_GNU

@@>> mremap(2)
@@@param flags: Set of `MREMAP_MAYMOVE | MREMAP_FIXED'
[[section(".text.crt{|.dos}.heap.mman"), vartypes(void *)]]
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[export_alias("__mremap", "__libc_mremap")]]
void *mremap([[access(none)]] void *addr, size_t old_len, size_t new_len,
             __STDC_INT_AS_UINT_T flags, ... /* void *new_address */);

@@>> remap_file_pages(2)
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
int remap_file_pages([[access(none)]] void *start, size_t size,
                     __STDC_INT_AS_UINT_T prot, size_t pgoff,
                     __STDC_INT_AS_UINT_T flags);

@@>> memfd_create(2)
@@@param: name:  Set `/proc/[pid]/fd/[return]' = "memfd:${name}"
@@@param: flags: Set of `MFD_CLOEXEC | MFD_CLOFORK | MFD_ALLOW_SEALING | MFD_HUGETLB'
[[decl_include("<bits/types.h>")]]
$fd_t memfd_create(char const *name, unsigned int flags);

@@>> mlock2(2)
[[decl_include("<hybrid/typecore.h>")]]
int mlock2([[access(none)]] void const *addr, size_t length, unsigned int flags);

@@>> pkey_alloc(2)
[[crt_impl_if($extended_include_prefix("<asm/pkey.h>")!defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY))]]
int pkey_alloc(unsigned int flags, unsigned int access_rights);

@@>> pkey_set(3)
[[crt_impl_if($extended_include_prefix("<asm/pkey.h>")!defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY))]]
[[impl_include("<libc/errno.h>"), requires_include("<asm/pkey.h>"), requires(defined(__ARCH_HAVE_PKEY))]]
int pkey_set(int pkey, unsigned int access_rights) {
	if unlikely(!__arch_pkey_verify_key(pkey) ||
	            !__arch_pkey_verify_rights(access_rights))
		goto badkey_or_rights;
	__arch_pkey_set(pkey, access_rights);
	return 0;
badkey_or_rights:
@@pp_ifdef EINVAL@@
	return libc_seterrno(EINVAL);
@@pp_else@@
	return -1;
@@pp_endif@@
}

@@>> pkey_get(3)
[[crt_impl_if($extended_include_prefix("<asm/pkey.h>")!defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY))]]
[[impl_include("<libc/errno.h>"), requires_include("<asm/pkey.h>"), requires(defined(__ARCH_HAVE_PKEY))]]
int pkey_get(int pkey) {
	if unlikely(!__arch_pkey_verify_key(pkey))
		goto badkey;
	return __arch_pkey_get(pkey);
badkey:
@@pp_ifdef EINVAL@@
	return libc_seterrno(EINVAL);
@@pp_else@@
	return -1;
@@pp_endif@@
}

@@>> pkey_free(2)
[[crt_impl_if($extended_include_prefix("<asm/pkey.h>")!defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY))]]
int pkey_free(int pkey);

@@>> pkey_mprotect(2)
[[decl_include("<features.h>", "<hybrid/typecore.h>")]]
[[crt_impl_if($extended_include_prefix("<asm/pkey.h>")!defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY))]]
int pkey_mprotect([[access(none)]] void *addr, size_t len, __STDC_INT_AS_UINT_T prot, int pkey);


%#endif /* __USE_GNU */


%#ifdef __USE_KOS
%__SYSDECL_END
%[insert:prefix(
#include <bits/crt/mapfile.h>
)]
%__SYSDECL_BEGIN

%
%/* Possible values for `flags' argument of `fmapfile(3)' & friends */
%{
#if !defined(FMAPFILE_READALL) && defined(__FMAPFILE_READALL)
#define FMAPFILE_READALL   __FMAPFILE_READALL   /* Flag: use `preadall(3)' / `readall(3)' instead of `pread(2)' / `read(2)' */
#endif /* !FMAPFILE_READALL && __FMAPFILE_READALL */
#if !defined(FMAPFILE_MUSTMMAP) && defined(__FMAPFILE_MUSTMMAP)
#define FMAPFILE_MUSTMMAP  __FMAPFILE_MUSTMMAP  /* Flag: require the use of a mmap(2) */
#endif /* !FMAPFILE_MUSTMMAP && __FMAPFILE_MUSTMMAP */
#if !defined(FMAPFILE_MAPSHARED) && defined(__FMAPFILE_MAPSHARED)
#define FMAPFILE_MAPSHARED __FMAPFILE_MAPSHARED /* Flag: when using mmap, don't map as MAP_PRIVATE, but use MAP_SHARED (don't pass a non-zero `num_trailing_nulbytes' in this case!) */
#endif /* !FMAPFILE_MAPSHARED && __FMAPFILE_MAPSHARED */
#if !defined(FMAPFILE_ATSTART) && defined(__FMAPFILE_ATSTART)
#define FMAPFILE_ATSTART   __FMAPFILE_ATSTART /* Flag: assume that the given file's pointer is located at the file's beginning (pass `offset=0' when using this flag) */
#endif /* !FMAPFILE_ATSTART && __FMAPFILE_ATSTART */
}

%[define_replacement(FMAPFILE_READALL   = __FMAPFILE_READALL)]
%[define_replacement(FMAPFILE_MUSTMMAP  = __FMAPFILE_MUSTMMAP)]
%[define_replacement(FMAPFILE_MAPSHARED = __FMAPFILE_MAPSHARED)]
%[define_replacement(FMAPFILE_ATSTART   = __FMAPFILE_ATSTART)]


@@>> fmapfile(3)
@@A function that can be used to map a specific sub-range of some file into memory.
@@This  function tries the following (in order)  when trying to create the mapping:
@@ - mmap(2):                        If `fd' can be mmap'd, then that is how the mapping is created
@@ - malloc(3) + pread(2):           If `fd' supports pread(2), use that to fill a buffer
@@ - malloc(3) + lseek(2) + read(2): For a non-zero offset, try to use lseek(2) to move to `offset'
@@ - malloc(3) + read(2):            When lseek(2) returns an error, use read(2) to skip `offset',
@@                                   after which  up  to  `max_bytes'  bytes  are  read  normally.
@@Upon success (return == 0), the given `mapping' must be deleted using `unmapfile(3)'
@@@param: fd:        The file that should be loaded into memory.
@@@param: mapping:   Filled with mapping information. This structure contains at least 2 fields:
@@                    - mf_addr: Filled with the base address of a mapping of the file's contents
@@                    - mf_size: The actual number of mapped bytes (excluding `num_trailing_nulbytes')
@@                               This will always be `>= min_bytes && <= max_bytes'.
@@                    - Other fields are implementation-specific
@@                   Note that the memory located at `mapping->mf_addr' is writable, though changes  to
@@                   it are guarantied not to be written back to `fd'. iow: it behaves like MAP_PRIVATE
@@                   mapped as PROT_READ|PROT_WRITE.
@@@param: offset:    File offset / number of leading bytes that should not be  mapped
@@                   When set to `(Dee_pos_t)-1', use the fd's current file position.
@@@param: min_bytes: The  min number of bytes (excluding num_trailing_nulbytes) that should be mapped
@@                   starting  at `offset'. If the file is smaller than this, or indicates EOF before
@@                   this number of bytes has been reached,  nul bytes are mapped for its  remainder.
@@                   Note that this doesn't include `num_trailing_nulbytes', meaning that (e.g.) when
@@                   an entirely empty file is mapped you get a buffer like:
@@                   >> mf_addr = calloc(min_size + num_trailing_nulbytes);
@@                   >> mf_size = min_size;
@@                   This argument essentially acts as if `fd' was at least `min_bytes' bytes large
@@                   by filling the non-present address range with all zeroes.
@@@param: max_bytes: The  max number of bytes (excluding num_trailing_nulbytes) that should be mapped
@@                   starting  at `offset'. If the file is smaller than this, or indicates EOF before
@@                   this number of bytes has been reached, simply stop there. - The actual number of
@@                   mapped bytes (excluding `num_trailing_nulbytes') is `mapping->mf_size'.
@@@param: num_trailing_nulbytes: When non-zero, append this many trailing NUL-bytes at the end of
@@                   the mapping. More bytes than this may be appended if necessary, but at least
@@                   this many are guarantied  to be. - Useful  if you want to  load a file as  a
@@                   string,  in which case you can specify `1' to always have a trailing '\0' be
@@                   appended:
@@                   >> bzero(mapping->mf_addr + mapping->mf_size, num_trailing_nulbytes);
@@@param: flags:     Set of `FMAPFILE_*'
@@@return: 0 : Success (the given `mapping' must be deleted using `unmapfile(3)')
@@@return: -1: [errno=EINVAL]  The given `flags' contains invalid bits.
@@@return: -1: [errno=EINVAL]  `FMAPFILE_MAPSHARED' was set,  an mmap  was
@@                             attempted, and `num_trailing_nulbytes != 0'
@@@return: -1: [errno=EPERM]   `fd' doesn't support read(2)ing
@@@return: -1: [errno=ENOMEM]  Out of memory (or file is too large for a continuous heap-buffer to be posible)
@@@return: -1: [errno=EBADF]   Invalid `fd'
@@@return: -1: [errno=ENOTSUP] `FMAPFILE_ONLYMMAP' was given, and mmap  wasn't possible, either because a  call
@@                             to  `mmap(2)' with the  given `fd' returned an  error (including indicating that
@@                             the file doesn't support mmap(), or that there isn't enough space t map the file
@@                             in its entirety), or because  `max_bytes == (size_t)-1', and the effective  area
@@                             that you are trying to map is larger than the entirety of your address space.
@@@return: -1: [errno=*]       Read error
[[wunused, decl_include("<bits/types.h>", "<bits/crt/mapfile.h>")]]
[[requires_function(read, malloc, realloc)]]
[[impl_include("<bits/os/stat.h>", "<bits/crt/mapfile.h>")]]
[[impl_include("<asm/os/mman.h>", "<libc/errno.h>")]]
[[impl_include("<asm/os/stdio.h>", "<hybrid/__overflow.h>")]]
[[impl_include("<asm/crt/malloc.h>")]]
int fmapfile([[out]] struct mapfile *__restrict mapping, $fd_t fd,
             $pos64_t offset, size_t min_bytes, size_t max_bytes,
             size_t num_trailing_nulbytes, unsigned int flags) {
	byte_t *buf;
	size_t bufsize;
	size_t bufused;
	size_t buffree;

	/* Validate the given `flags' */
	if unlikely(flags & ~(__FMAPFILE_READALL | __FMAPFILE_MUSTMMAP |
	                      __FMAPFILE_MAPSHARED | __FMAPFILE_ATSTART)) {
@@pp_ifdef EINVAL@@
		return __libc_seterrno(EINVAL);
@@pp_else@@
		return __libc_seterrno(1);
@@pp_endif@@
	}

	/* Try to use mmap(2) */
@@pp_if defined(__PROT_READ) && defined(__PROT_WRITE) && defined(__MAP_PRIVATE) && defined(__SEEK_SET) && $has_function(mmap64, fstat64, lseek64)@@
	{
		@struct stat64@ st;
		if (fstat64(fd, &st) == 0) {
@@pp_if defined(__libc_geterrno) && defined(__libc_seterrno)@@
			errno_t saved_errno = __libc_geterrno();
@@pp_endif@@
			pos64_t map_offset = offset;
			size_t map_bytes;
			if (map_offset == (pos64_t)-1) {
				if unlikely(flags & __FMAPFILE_ATSTART) {
					map_offset = 0;
				} else {
					/* Use the file descriptors current offset. */
					map_offset = (pos64_t)lseek64(fd, 0, __SEEK_CUR);
					if (map_offset == (pos64_t)-1)
						goto after_mmap_attempt;
				}
			}
			if (__hybrid_overflow_usub(st.@st_size@, map_offset, &map_bytes)) {
				map_bytes = 0;
				if (st.@st_size@ > map_offset)
					map_bytes = (size_t)-1;
			}
			if (map_bytes >= max_bytes) {
				map_bytes = max_bytes;
@@pp_if __SIZEOF_SIZE_T__ < __SIZEOF_OFF64_T__@@
				if (map_bytes == (size_t)-1) {
					/* Special case: caller wants to map the entire file, but it's too large. */
					uint64_t true_size = st.@st_size@ - map_offset;
					if (true_size > (uint64_t)(size_t)-1) {
						/* File is too large to be loaded into memory in its entirety. */
						if (flags & __FMAPFILE_MUSTMMAP) {
@@pp_ifdef ENOTSUP@@
							return __libc_seterrno(ENOTSUP);
@@pp_elif defined(EOPNOTSUPP)@@
							return __libc_seterrno(EOPNOTSUPP);
@@pp_else@@
							return __libc_seterrno(1);
@@pp_endif@@
						}

						/* File is too large for a continuous heap-buffer to be posible */
@@pp_ifdef ENOMEM@@
						return __libc_seterrno(ENOMEM);
@@pp_else@@
						return __libc_seterrno(1);
@@pp_endif@@
					}
				}
@@pp_endif@@
			}
			if (map_bytes) {
				/* Map file into memory. */
				size_t mapsize, used_nulbytes;
				used_nulbytes = num_trailing_nulbytes;
				if (min_bytes > map_bytes)
					used_nulbytes += min_bytes - map_bytes;
				mapsize = map_bytes + used_nulbytes;
@@pp_ifdef __MAP_SHARED@@
				if (flags & __FMAPFILE_MAPSHARED) {
					if unlikely(num_trailing_nulbytes) {
@@pp_ifdef EINVAL@@
						return __libc_seterrno(EINVAL);
@@pp_else@@
						return __libc_seterrno(1);
@@pp_endif@@
					}
					buf = (byte_t *)mmap64(NULL, mapsize, __PROT_READ | __PROT_WRITE,
					                       __MAP_SHARED, fd, (__PIO_OFFSET64)map_offset);
				} else {
					buf = (byte_t *)mmap64(NULL, mapsize, __PROT_READ | __PROT_WRITE,
					                       __MAP_PRIVATE, fd, (__PIO_OFFSET64)map_offset);
				}
@@pp_else@@
				if unlikely(flags & __FMAPFILE_MAPSHARED) {
					/* Shared memory mappings aren't supposed :( */
@@pp_ifdef ENOSYS@@
					return __libc_seterrno(ENOSYS);
@@pp_elif defined(ENOTSUP)@@
					return __libc_seterrno(ENOTSUP);
@@pp_elif defined(EOPNOTSUPP)@@
					return __libc_seterrno(EOPNOTSUPP);
@@pp_else@@
					return __libc_seterrno(1);
@@pp_endif@@
				}
				buf = (byte_t *)mmap64(NULL, mapsize,
				                       __PROT_READ | __PROT_WRITE,
				                       __MAP_PRIVATE, fd,
				                       (__PIO_OFFSET64)map_offset);
@@pp_endif@@
				if (buf != (byte_t *)__MAP_FAILED) {
					/* Clear  out the caller-required trailing NUL bytes.
					 * We do this in a kind-of special way that tries not
					 * to write-fault memory if it already contains NULs. */
					byte_t *nul = buf + map_bytes;
					while (used_nulbytes) {
						if (*nul) {
							bzero(nul, used_nulbytes);
							break;
						}
						--used_nulbytes;
						++nul;
					}
					mapping->@mf_addr@ = buf;
					mapping->@mf_size@ = map_bytes;
					mapping->@__mf_mapsize@ = mapsize;
					return 0;
				}
@@pp_if defined(__libc_geterrno) && defined(__libc_seterrno)@@
				__libc_seterrno(saved_errno);
@@pp_endif@@
			} else {
				/* Special files from procfs indicate their size as `0',  even
				 * though they aren't actually empty. - As such, we can't just
				 * use the normal approach of read(2)-ing the file.
				 *
				 * Only if at that point it still indicates being empty, are we
				 * actually allowed to believe that claim! */
			}
		}
	}
after_mmap_attempt:
@@pp_endif@@

	/* Check if we're to error out if mmap can't be used */
	if (flags & __FMAPFILE_MUSTMMAP) {
@@pp_ifdef ENOTSUP@@
		return __libc_seterrno(ENOTSUP);
@@pp_elif defined(EOPNOTSUPP)@@
		return __libc_seterrno(EOPNOTSUPP);
@@pp_else@@
		return __libc_seterrno(1);
@@pp_endif@@
	}

	/* Allocate a heap buffer. */
	bufsize = max_bytes;
	if (bufsize > 0x10000)
		bufsize = 0x10000;
	if (bufsize < min_bytes)
		bufsize = min_bytes;
	buf = (byte_t *)malloc(bufsize + num_trailing_nulbytes);
	if unlikely(!buf) {
		bufsize = 1;
		if (bufsize < min_bytes)
			bufsize = min_bytes;
		buf = (byte_t *)malloc(bufsize + num_trailing_nulbytes);
		if unlikely(!buf)
			return -1;
	}
	bufused = 0;
	buffree = bufsize;

	if (offset != (pos64_t)-1 && (offset != 0 || !(flags & __FMAPFILE_ATSTART))) {
		/* Try to use pread(2) */
@@pp_if $has_function(pread64)@@
		for (;;) {
			ssize_t error;
			error = pread64(fd, buf + bufused, buffree, offset);
			if (error <= 0 || (!(flags & __FMAPFILE_READALL) && (size_t)error < buffree)) {
				if ((size_t)error < buffree) {
					/* End-of-file! */
					byte_t *newbuf;
					size_t used_nulbytes;
					bufused += (size_t)error;
					used_nulbytes = num_trailing_nulbytes;
					if (min_bytes > bufused)
						used_nulbytes += min_bytes - bufused;
					newbuf = (byte_t *)realloc(buf, bufused + used_nulbytes);
					if likely(newbuf)
						buf = newbuf;
					bzero(buf + bufused, used_nulbytes); /* Trailing NUL-bytes */
					mapping->@mf_addr@ = buf;
					mapping->@mf_size@ = bufused;
					mapping->@__mf_mapsize@ = 0;
					return 0;
				}
				if (bufused == 0)
					break; /* File probably doesn't support `pread(2)'... */
				/* Read error */
				goto err_buf;
			}
			offset  += (size_t)error;
			bufused += (size_t)error;
			buffree -= (size_t)error;
			if (buffree < 1024) {
				byte_t *newbuf;
				size_t newsize = bufsize * 2;
				newbuf = (byte_t *)realloc(buf, newsize + num_trailing_nulbytes);
				if (!newbuf) {
					newsize = bufsize + 1024;
					newbuf = (byte_t *)realloc(buf, newsize + num_trailing_nulbytes);
					if (!newbuf) {
						if (!buffree) {
							newsize = bufsize + 1;
							newbuf  = (byte_t *)realloc(buf, newsize + num_trailing_nulbytes);
							if unlikely(!newbuf)
								goto err_buf;
						} else {
							newsize = bufsize;
							newbuf  = buf;
						}
					}
				}
				buffree += newsize - bufsize;
				bufsize = newsize;
				buf     = newbuf;
			}
		}
@@pp_endif@@

		/* For a custom offset, try to use lseek() (or read()) */
@@pp_if $has_function(lseek64) && defined(__SEEK_SET)@@
		if (lseek64(fd, (off64_t)offset, __SEEK_SET) != -1) {
			/* Was able to lseek(2) */
		} else
@@pp_endif@@
		{
			/* Try to use read(2) to skip leading data. */
			while (offset) {
				ssize_t error;
				size_t skip = bufsize + num_trailing_nulbytes;
				if ((pos64_t)skip > offset)
					skip = (size_t)offset;
				error = read(fd, buf, skip);
				if (error <= 0 || (!(flags & __FMAPFILE_READALL) && (size_t)error < skip)) {
					if (error < 0)
						goto err_buf;
					goto empty_file; /* EOF reached before `offset' */
				}
				offset -= error;
			}
		}
	}

	/* Use read(2) as fallback */
	for (;;) {
		ssize_t error;
		error = read(fd, buf + bufused, buffree);
		if (error <= 0 || (!(flags & __FMAPFILE_READALL) && (size_t)error < buffree)) {
			if (error >= 0) {
				/* End-of-file! */
				byte_t *newbuf;
				size_t used_nulbytes;
				bufused += (size_t)error;
				used_nulbytes = num_trailing_nulbytes;
				if (min_bytes > bufused)
					used_nulbytes += min_bytes - bufused;
				newbuf = (byte_t *)realloc(buf, bufused + used_nulbytes);
				if likely(newbuf)
					buf = newbuf;
				bzero(buf + bufused, used_nulbytes); /* Trailing NUL-bytes */
				mapping->@mf_addr@ = buf;
				mapping->@mf_size@ = bufused;
				mapping->@__mf_mapsize@ = 0;
				return 0;
			}
			/* Read error */
			goto err_buf;
		}
		bufused += (size_t)error;
		buffree -= (size_t)error;
		if (buffree < 1024) {
			byte_t *newbuf;
			size_t newsize = bufsize * 2;
			newbuf = (byte_t *)realloc(buf, newsize + num_trailing_nulbytes);
			if (!newbuf) {
				newsize = bufsize + 1024;
				newbuf = (byte_t *)realloc(buf, newsize + num_trailing_nulbytes);
				if (!newbuf) {
					if (!buffree) {
						newsize = bufsize + 1;
						newbuf  = (byte_t *)realloc(buf, newsize + num_trailing_nulbytes);
						if unlikely(!newbuf)
							goto err_buf;
					} else {
						newsize = bufsize;
						newbuf  = buf;
					}
				}
			}
			buffree += newsize - bufsize;
			bufsize = newsize;
			buf     = newbuf;
		}
	}

	/*--------------------------------------------------------------------*/
	{
		byte_t *newbuf;
		size_t used_nulbytes;
		/* Because of how large our original buffer was, and because at this
		 * point all  we want  to do  is return  a  `num_trailing_nulbytes'-
		 * large buffer of  all NUL-bytes, it's  probably more efficient  to
		 * allocate a new  (small) buffer,  than trying to  realloc the  old
		 * buffer. If we try  to do realloc(), the  heap might see that  all
		 * we're  trying to do  is truncate the buffer,  and so might choose
		 * not to alter its base  address, which (if done repeatedly)  might
		 * lead to memory becoming very badly fragmented. */
empty_file:
		used_nulbytes = min_bytes + num_trailing_nulbytes;
		newbuf = (byte_t *)calloc(1, used_nulbytes);
		if likely(newbuf) {
@@pp_if $has_function(free)@@
			free(buf);
@@pp_endif@@
		} else {
@@pp_ifndef __REALLOC_ZERO_IS_NONNULL@@
			if unlikely(!used_nulbytes)
				used_nulbytes = 1;
@@pp_endif@@
			newbuf = (byte_t *)realloc(buf, used_nulbytes);
			if (!newbuf)
				newbuf = buf;
			bzero(newbuf, used_nulbytes);
		}
		mapping->@mf_addr@ = newbuf;
		mapping->@mf_size@ = 0;
		mapping->@__mf_mapsize@ = 0;
	}
	return 0;
err_buf:
@@pp_if $has_function(free)@@
	free(buf);
@@pp_endif@@
	return -1;
}



@@>> fmapfileat(3)
@@Map the specified `filename' into memory. s.a. `fmapfile(3)'
@@@param: atflags: Set of `0 | AT_DOSPATH | AT_EMPTY_PATH'
[[wunused, decl_include("<bits/types.h>", "<bits/crt/mapfile.h>")]]
[[requires_include("<asm/os/oflags.h>")]]
[[requires(defined(__O_RDONLY) && $has_function(openat, fmapfile))]]
[[impl_include("<asm/os/oflags.h>", "<asm/os/fcntl.h>")]]
[[impl_include("<libc/errno.h>")]]
[[crt_dos_variant({ impl: {
	return libc_fmapfileat(mapping, dirfd, filename, offset,
	                       min_bytes, max_bytes, num_trailing_nulbytes,
	                       flags, atflags | libd_AT_DOSPATH);
}})]]
int fmapfileat([[out]] struct mapfile *__restrict mapping,
               $fd_t dirfd, [[in]] char const *filename,
               $pos64_t offset, size_t min_bytes, size_t max_bytes,
               size_t num_trailing_nulbytes, unsigned int flags,
               $atflag_t atflags) {
	fd_t fd;
	int result;
	oflag_t oflags = __O_RDONLY | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK;
@@pp_if defined(__AT_DOSPATH) && defined(__O_DOSPATH)@@
	if (atflags & __AT_DOSPATH) {
		oflags |= __O_DOSPATH;
		atflags &= ~__AT_DOSPATH;
	}
@@pp_endif@@
@@pp_if defined(__AT_EMPTY_PATH)@@
	if (atflags & __AT_EMPTY_PATH) {
		if (!*filename) {
			return fmapfile(mapping, dirfd,
			                offset, min_bytes, max_bytes,
			                num_trailing_nulbytes, flags);
		}
		atflags &= ~__AT_EMPTY_PATH;
	}
@@pp_endif@@
	if unlikely(atflags != 0) {
@@pp_ifdef EINVAL@@
		return libc_seterrno(EINVAL);
@@pp_else@@
		return libc_seterrno(1);
@@pp_endif@@
	}
	fd = openat(dirfd, filename, oflags);
	if unlikely(fd < 0)
		return -1;
	result = fmapfile(mapping, fd,
	                  offset, min_bytes, max_bytes,
	                  num_trailing_nulbytes,
	                  flags | __FMAPFILE_ATSTART);
@@pp_if $has_function(close)@@
	close(fd);
@@pp_endif@@
	return result;
}



@@>> mapfile(3)
@@Map the specified `filename' into memory. s.a. `fmapfile(3)'
[[wunused, decl_include("<bits/types.h>", "<bits/crt/mapfile.h>")]]
[[requires_include("<asm/os/fcntl.h>", "<asm/os/oflags.h>")]]
[[requires((defined(__AT_FDCWD) && $has_function(fmapfileat)) ||
           (defined(__O_RDONLY) && $has_function(open, fmapfile)))]]
[[crt_dos_variant]]
int mapfile([[out]] struct mapfile *__restrict mapping,
            [[in]] char const *filename,
            $pos64_t offset, size_t min_bytes, size_t max_bytes,
            size_t num_trailing_nulbytes, unsigned int flags) {
@@pp_if defined(__AT_FDCWD) && $has_function(fmapfileat)@@
	return fmapfileat(mapping, __AT_FDCWD, filename,
	                  offset, min_bytes, max_bytes,
	                  num_trailing_nulbytes, flags, 0);
@@pp_else@@
	fd_t fd = open(filename, __O_RDONLY | __PRIVATE_O_CLOEXEC | __PRIVATE_O_CLOFORK);
	if unlikely(fd < 0)
		return -1;
	result = fmapfile(mapping, fd,
	                  offset, min_bytes, max_bytes,
	                  num_trailing_nulbytes,
	                  flags | __FMAPFILE_ATSTART);
@@pp_if $has_function(close)@@
	close(fd);
@@pp_endif@@
	return result;
@@pp_endif@@
}




@@>> unmapfile(3)
@@Delete a file mapping previously created by `mapfile(3)'
[[decl_include("<bits/crt/mapfile.h>"), requires_function(free)]]
int unmapfile([[inout]] struct mapfile *__restrict mapping) {
	if (mapping->@__mf_mapsize@) {
@@pp_if $has_function(munmap)@@
		return munmap(mapping->@mf_addr@, mapping->@__mf_mapsize@);
@@pp_endif@@
	} else {
		free(mapping->@mf_addr@);
	}
	return 0;
}

%#endif /* __USE_KOS */

%{

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_SYS_MMAN_H)
#include <parts/uchar/sys/mman.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_SYS_MMAN_H */
#endif /* __USE_UTF */

}
