/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_MMAN_H
#define _ASM_MMAN_H 1

#include <__crt.h>

#if defined(__KOS__) || defined(__linux__) || defined(__CRT_KOS) || defined(__CRT_KOS_KERNEL) || defined(__CRT_GLC)
#define __PROT_NONE  0x00 /* Data cannot be accessed. */
#define __PROT_EXEC  0x01 /* Data can be executed. */
#define __PROT_WRITE 0x02 /* Data can be written. */
#define __PROT_READ  0x04 /* Data can be read. */
#define __PROT_SEM   0x08 /* Ignored... */
#define __PROT_MASK  0x0f /* Mask of flags accessible from user-space. */
#endif /* ... */


#if defined(__KOS__) || defined(__CRT_KOS) || defined(__CRT_KOS_KERNEL)
#if __KOS_VERSION__ >= 300
#define __PROT_LOOSE    0x10 /* Unmap the region within the when cloning a VM (`CLONE_VM'). */
#else /* __KOS_VERSION__ >= 300 */
#define __PROT_LOOSE    0x10 /* Unmap the region within the when cloning a VM (`CLONE_VM').
                              * NOTE: Implicitly set for all system-allocated user stacks,
                              *       except for that of the calling thread. */
#endif /* __KOS_VERSION__ < 300 */
#define __PROT_SHARED   0x20 /* Changes are shared, even after the VM was cloned (`CLONE_VM').
                              * NOTE: Same as the `MAP_SHARED' map flag, but
                              *       can be set like any other protection. */
#undef __PROT_MASK
#define __PROT_MASK     0x3f /* Mask of flags accessible from user-space. */
#if __KOS_VERSION__ < 400
#define __PROT_NOUSER   0x40 /* Map memory as inaccessible to user-space.
                              * WARNING: Not fully enforced for addresses within user-memory. */
#if __KOS_VERSION__ < 300
#define __PROT_CLEAN    0x80 /* Unset whenever user-space re-maps a page as writable. - Cannot be removed.
                              * NOTE: This flag is used to prevent rootfork() from working
                              *       when called from an otherwise read-only module after
                              *       some portion of the section containing the root-fork
                              *       system call has been mapped as writable.
                              *    >> rootfork() fails when any page in the calling section (.text)
                              *       isn't part of a root-module, isn't fully mapped, was
                              *       re-mapped somewhere else, or been made writable at any point. */
#endif /* __KOS_VERSION__ < 300 */
#endif /* __KOS_VERSION__ < 400 */
#endif /* ... */


#if defined(__KOS__) || defined(__linux__) || defined(__CRT_KOS) || defined(__CRT_KOS_KERNEL) || defined(__CRT_GLC)
#define __MAP_SHARED        0x00000001 /* Share changes. */
#define __MAP_PRIVATE       0x00000002 /* Changes are private. */
#define __MAP_FIXED         0x00000010 /* Interpret addr exactly. */
#define __MAP_TYPE          0x0000000f /* Mask for type of mapping. */
#define __MAP_FILE          0x00000000 /* Do use a file. */
#define __MAP_ANON          0x00000020 /* Don't use a file. */
#define __MAP_32BIT         0x00000040 /* Only give out 32-bit addresses. */
#define __MAP_GROWSDOWN     0x00000100 /* Stack-like segment. */
#define __MAP_GROWSUP       0x00000200 /* Stack-like segment growing upwards. */
#define __MAP_DENYWRITE     0x00000800 /* Ignored. */
#define __MAP_EXECUTABLE    0x00001000 /* Ignored. */
#define __MAP_LOCKED        0x00002000 /* Lock the mapping. */
#define __MAP_NORESERVE     0x00004000 /* Don't check for reservations. */
#define __MAP_POPULATE      0x00008000 /* Populate (prefault) pagetables. */
#define __MAP_NONBLOCK      0x00010000 /* Do not block on IO. */
#define __MAP_STACK         0x00020000 /* Allocation is for a stack.
                                        * NOTE: KOS uses this flag to determine where
                                        *       automatic memory mappings are allocated at. */
#define __MAP_SYNC          0x00000000 /* XXX: Implement me? */
#define __MAP_HUGETLB       0x00040000 /* Create huge page mapping. */
#define __MAP_HUGE_SHIFT    26
#define __MAP_HUGE_MASK     0x3f
#define __MAP_UNINITIALIZED 0x04000000 /* For anonymous mmap, memory could be uninitialized.
                                        * NOTE: Implied for physical mappings.
                                        * NOTE: The kernel may initialize memory randomly in sandboxed threads. */
#endif /* ... */

#if defined(__KOS__) || defined(__CRT_KOS) || defined(__CRT_KOS_KERNEL)
#define __MAP_AUTOMATIC 0x00000000 /* Use sharing behavior specified by `PROT_SHARED'. */
#if __KOS_VERSION__ >= 400
#define __MAP_DONT_MAP         0x20000000 /* Don't actually map memory, but test the waters of a memory
                                           * location hasn't already been mapped, or locate a suitably
                                           * large free memory range.
                                           * This flag is usually followed by another call that sets
                                           * the `MAP_DONT_OVERRIDE' flag. */
#define __MAP_DONT_OVERRIDE    0x40000000 /* Don't override existing mappings when `MAP_FIXED' is passed.
                                           * Instead, TODO:ERROR. */
#define __MAP_OFFSET64_POINTER 0x80000000 /* The `OFFSET' argument of MMAP is actually a pointer to the 64-bit
                                           * unsigned integer that should actually be used as offset. */
#endif /* __KOS_VERSION__ >= 400 */
#endif /* ... */


#if defined(__KOS__) || defined(__linux__) || defined(__CRT_KOS) || defined(__CRT_KOS_KERNEL) || defined(__CRT_GLC)
#define __MAP_FAILED __CCAST(void *)(-1)
#define __PROT_GROWSDOWN 0x01000000 /* Same as `MAP_GROWSDOWN', but may be used with `mprotect()' */
#define __PROT_GROWSUP   0x02000000 /* Same as `MAP_GROWSUP', but may be used with `mprotect()' */
#define __MS_ASYNC       0x01 /* Perform the operation asynchronously. */
#define __MS_INVALIDATE  0x02 /* Invalidate caches. */
#define __MS_SYNC        0x04 /* Wait for the sync to finish. */
#define __MREMAP_MAYMOVE 0x01 /* Allowed to move to a different location */
#define __MREMAP_FIXED   0x02 /* Allowed to move to a different location */
#define __MFD_CLOEXEC       0x1 /* Close-on-exec */
#define __MFD_ALLOW_SEALING 0x2 /* Allow use of `F_ADD_SEALS' and `F_GET_SEALS' (when not given, `F_SEAL_SEAL' is set on creation) */
#define __MFD_HUGETLB       0x4 /* ... */
#define __MLOCK_ONFAULT 0x1
#define __PKEY_DISABLE_ACCESS 0x1
#define __PKEY_DISABLE_WRITE  0x2

/* DISCLAIMER: Documentation strings for MADV_*, POSIX_MADV_* and MCL_* were
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
#define __MADV_NORMAL           0   /* No further special treatment. */
#define __MADV_RANDOM           1   /* Expect random page references. */
#define __MADV_SEQUENTIAL       2   /* Expect sequential page references. */
#define __MADV_WILLNEED         3   /* Will need these pages. */
#define __MADV_DONTNEED         4   /* Don't need these pages. */
#define __MADV_REMOVE           9   /* Remove these pages and resources. */
#define __MADV_DONTFORK         10  /* Do not inherit across fork. */
#define __MADV_DOFORK           11  /* Do inherit across fork. */
#define __MADV_MERGEABLE        12  /* KSM may merge identical pages. */
#define __MADV_UNMERGEABLE      13  /* KSM may not merge identical pages. */
#define __MADV_HUGEPAGE         14  /* Worth backing with hugepages. */
#define __MADV_NOHUGEPAGE       15  /* Not worth backing with hugepages. */
#define __MADV_DONTDUMP         16  /* Explicity exclude from the core dump, overrides the coredump filter bits. */
#define __MADV_DODUMP           17  /* Clear the MADV_DONTDUMP flag. */
#define __MADV_HWPOISON         100 /* Poison a page for testing. */
#define __POSIX_MADV_NORMAL     0   /* No further special treatment. */
#define __POSIX_MADV_RANDOM     1   /* Expect random page references. */
#define __POSIX_MADV_SEQUENTIAL 2   /* Expect sequential page references. */
#define __POSIX_MADV_WILLNEED   3   /* Will need these pages. */
#define __POSIX_MADV_DONTNEED   4   /* Don't need these pages. */
#define __MCL_CURRENT           1   /* Lock all currently mapped pages. */
#define __MCL_FUTURE            2   /* Lock all additions to address space. */
#define __MCL_ONFAULT           4   /* Lock all pages that are faulted in. */
#endif /* ... */

#endif /* !_ASM_MMAN_H */
