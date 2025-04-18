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
/*!replace_with_include <asm/os/mman.h>*/
#ifndef _ASM_OS_KOS_MMAN_H
#define _ASM_OS_KOS_MMAN_H 1

#include <__stdinc.h>

/************************************************************************/
/* KOS/LINUX                                                            */
/************************************************************************/

#define __PROT_NONE      0x00       /* Data cannot be accessed. */
#define __PROT_EXEC      0x01       /* Data can be executed. */
#define __PROT_WRITE     0x02       /* Data can be written. */
#define __PROT_READ      0x04       /* Data can be read. */
#define __PROT_SEM       0x08       /* Ignored... */
#define __PROT_MASK      0x0f       /* Mask of flags accessible from user-space. */
#define __PROT_GROWSDOWN 0x01000000 /* Same as `MAP_GROWSDOWN', but may be used with `mprotect()' */
#define __PROT_GROWSUP   0x02000000 /* Same as `MAP_GROWSUP', but may be used with `mprotect()' */
#ifdef __KOS__
#if __KOS_VERSION__ < 400
#if __KOS_VERSION__ >= 300
#define __PROT_LOOSE     0x10 /* Unmap the region within the when cloning a VM (`CLONE_VM'). */
#else /* __KOS_VERSION__ >= 300 */
#define __PROT_LOOSE     0x10 /* Unmap the region within the when cloning a VM (`CLONE_VM').
                               * NOTE: Implicitly set for all system-allocated user stacks,
                               *       except for that of the calling thread. */
#endif /* __KOS_VERSION__ < 300 */
#endif /* __KOS_VERSION__ <= 400 */
#define __PROT_SHARED    0x20 /* Changes are shared, even after the VM was cloned (`CLONE_VM').
                               * NOTE: Same as the `MAP_SHARED' map flag, but
                               *       can  be set like any other protection. */
#undef __PROT_MASK
#define __PROT_MASK      0x3f /* Mask of flags accessible from user-space. */
#if __KOS_VERSION__ < 400
#define __PROT_NOUSER    0x40 /* Map memory as inaccessible to user-space.
                               * WARNING: Not fully enforced for addresses within user-memory. */
#if __KOS_VERSION__ < 300
#define __PROT_CLEAN     0x80 /* Unset whenever user-space re-maps a page as writable. - Cannot be removed.
                               * NOTE: This flag is used to prevent rootfork() from working
                               *       when called from an otherwise read-only module after
                               *       some portion of the section containing the root-fork
                               *       system call has been mapped as writable.
                               *    >> rootfork() fails when any page in the calling section (.text)
                               *       isn't  part  of  a  root-module,  isn't  fully  mapped,   was
                               *       re-mapped somewhere else, or been made writable at any point. */
#endif /* __KOS_VERSION__ < 300 */
#endif /* __KOS_VERSION__ < 400 */
#endif /* __KOS__ */

#define __MAP_SHARED           0x00000001 /* Share changes. */
#define __MAP_PRIVATE          0x00000002 /* Changes are private. */
#define __MAP_TYPE             0x0000000f /* Mask for type of mapping. */
#define __MAP_FILE             0x00000000 /* Do use a file. */
#define __MAP_FIXED            0x00000010 /* Interpret addr exactly. */
#define __MAP_ANON             0x00000020 /* Don't use a file. */
#define __MAP_32BIT            0x00000040 /* Only give out 32-bit addresses. */
/*efine __MAP_                 0x00000080  * ... */
#define __MAP_GROWSDOWN        0x00000100 /* Stack-like segment. */
#define __MAP_GROWSUP          0x00000200 /* Stack-like segment growing upwards. */
/*efine __MAP_                 0x00000400  * ... */
#define __MAP_DENYWRITE        0x00000800 /* Ignored. */
#define __MAP_EXECUTABLE       0x00001000 /* Ignored. */
#define __MAP_LOCKED           0x00002000 /* Lock the mapping. */
#define __MAP_NORESERVE        0x00004000 /* Don't check for reservations. */
#define __MAP_POPULATE         0x00008000 /* Populate (prefault) pagetables. */
#define __MAP_NONBLOCK         0x00010000 /* Do not block on IO. */
#define __MAP_STACK            0x00020000 /* Allocation is for a stack.
                                           * NOTE: KOS  uses  this  flag  to  determine  where
                                           *       automatic memory mappings are allocated at. */
#define __MAP_SYNC             0x00000000 /* XXX: Implement me? */
#define __MAP_HUGETLB          0x00040000 /* Create huge page mapping. */
/*efine __MAP_                 0x00080000  * ... */
#define __MAP_FIXED_NOREPLACE  0x00100000 /* Don't  override  existing mappings  when `MAP_FIXED'  is passed.
                                           * Instead, throw an exception `E_BADALLOC_ADDRESS_ALREADY_EXISTS'. */
#define __MAP_UNINITIALIZED    0x04000000 /* For anonymous mmap, memory could be uninitialized. */
#define __MAP_HUGE_SHIFT       26
#define __MAP_HUGE_MASK        0x3f       /* 0xfc000000 */

#ifdef __KOS__
#define __MAP_AUTOMATIC        0x00000000 /* Use sharing behavior specified by `PROT_SHARED'. */
#if __KOS_VERSION__ >= 400
/*efine __MAP_                 0x20000000  * ... */
#define __MAP_NOASLR           0x40000000 /* Disable ASLR (iow: don't randomize automatically determined mmap addresses) */
#define __MAP_OFFSET64_POINTER 0x80000000 /* The `offset' argument of MMAP is actually a pointer to the 64-bit
                                           * unsigned  integer  that  should  actually  be  used  as   offset. */
#endif /* __KOS_VERSION__ >= 400 */
#endif /* __KOS__ */


#define __MAP_FAILED (__CCAST(void *)-1)

#define __MS_ASYNC      0x01 /* Perform the operation asynchronously. */
#define __MS_INVALIDATE 0x02 /* Invalidate caches. */
#define __MS_SYNC       0x04 /* Wait for the sync to finish. */

#define __MREMAP_MAYMOVE   0x01 /* Allowed to move to a different location */
#define __MREMAP_FIXED     0x02 /* A 5th argument `new_address' is accepted that specifies the absolute, new position */
#ifdef __linux__
#define __MREMAP_DONTUNMAP 0x04 /* Used with `MREMAP_MAYMOVE': Don't delete the old mapping. */
#endif /* __linux__ */
#ifdef __KOS__
#if __KOS_VERSION__ >= 400
/* The following flags are accepted  by `mremap(2)', and affect  what
 * addresses are selected when the kernel has to choose a new address
 * for the resulting  mapping. (except  for `MREMAP_POPULATE',  which
 * simply pre-populates memory in case more got allocated) */
#define __MREMAP_32BIT           __MAP_32BIT
#define __MREMAP_GROWSDOWN       __MAP_GROWSDOWN
#define __MREMAP_GROWSUP         __MAP_GROWSUP
#define __MREMAP_POPULATE        __MAP_POPULATE
#define __MREMAP_NONBLOCK        __MAP_NONBLOCK
#define __MREMAP_STACK           __MAP_STACK
#define __MREMAP_FIXED_NOREPLACE __MAP_FIXED_NOREPLACE
#define __MREMAP_NOASLR          __MAP_NOASLR
#endif /* __KOS_VERSION__ >= 400 */
#endif /* __KOS__ */

#define __MFD_CLOEXEC       0x0000001 /* Close-on-exec */
#define __MFD_ALLOW_SEALING 0x0000002 /* Allow use of `F_ADD_SEALS' and `F_GET_SEALS' (when not given, `F_SEAL_SEAL' is set on creation) */
#define __MFD_HUGETLB       0x0000004 /* ... */
#ifdef __KOS__
#define __MFD_CLOFORK       0x1000000 /* Close-on-fork */
#endif /* __KOS__ */

#define __MLOCK_ONFAULT 0x1 /* Delegate population of locked memory until the first access. */

#define __PKEY_DISABLE_ACCESS 0x1
#define __PKEY_DISABLE_WRITE  0x2
#define __PKEY_ACCESS_MASK    0x3

#define __MADV_NORMAL         0   /* Remove any hints given on how memory will be used */
#define __MADV_RANDOM         1   /* Hint that memory will be accessed randomly */
#define __MADV_SEQUENTIAL     2   /* Hint that memory will be accessed sequentially */
#define __MADV_WILLNEED       3   /* Hint that memory will be accessed soon */
#define __MADV_DONTNEED       4   /* Hint that memory will probably not be used */
#define __MADV_FREE           8   /* Kernel is allowed to free memory (changes may be lost, but memory is allocated again if accessed) */
#define __MADV_REMOVE         9   /* ??? */
#define __MADV_DONTFORK       10  /* Exclude this mapping during forks */
#define __MADV_DOFORK         11  /* Include this mapping during forks (default) */
#define __MADV_MERGEABLE      12  /* Enable Kernel Samepage Merging (KSM) for this range */
#define __MADV_UNMERGEABLE    13  /* Disable Kernel Samepage Merging (KSM) for this range (default) */
#define __MADV_HUGEPAGE       14  /* Allow huge-page merging for this range (default; on KOS, this cannot be turned off) */
#define __MADV_NOHUGEPAGE     15  /* Disallow huge-page merging for this range (ignored on KOS) */
#define __MADV_DONTDUMP       16  /* Exclude mapping in coredumps */
#define __MADV_DODUMP         17  /* Include mapping in coredumps (default) */
#define __MADV_WIPEONFORK     18  /* Replace with a fresh MAP_PRIVATE|MAP_ANONYMOUS mapping during fork (not supported on KOS, yet) */
#define __MADV_KEEPONFORK     19  /* Retain mapping during fork (default) */
#define __MADV_COLD           20  /* Hint that mapping can be unloaded as one of the first candidates when memory runs low */
#define __MADV_PAGEOUT        21  /* Sync all changes to MAP_FILE|MAP_SHARED to disk, write changes to MAP_ANON to swap, and unload all unmodified file mappings */
#define __MADV_POPULATE_READ  22  /* Prefault for read access */
#define __MADV_POPULATE_WRITE 23  /* Prefault for write access */
#define __MADV_HWPOISON       100 /* ??? */
#define __MADV_SOFT_OFFLINE   101 /* ??? */

#define __POSIX_MADV_NORMAL     0 /* Remove any hints given on how memory will be used */
#define __POSIX_MADV_RANDOM     1 /* Hint that memory will be accessed randomly */
#define __POSIX_MADV_SEQUENTIAL 2 /* Hint that memory will be accessed sequentially */
#define __POSIX_MADV_WILLNEED   3 /* Hint that memory will be accessed soon */
#define __POSIX_MADV_DONTNEED   4 /* Hint that memory will probably not be used */

#define __MCL_CURRENT 1 /* ??? */
#define __MCL_FUTURE  2 /* ??? */
#define __MCL_ONFAULT 4 /* Delegate population of locked memory until the first access. */

#endif /* !_ASM_OS_KOS_MMAN_H */
