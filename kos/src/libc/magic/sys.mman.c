/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */

%[define_replacement(fd_t = __fd_t)]
%[define_replacement(off_t = __FS_TYPE(off))]
%[define_replacement(pos_t = __FS_TYPE(pos))]
%[define_replacement(off32_t = __off32_t)]
%[define_replacement(off64_t = __off64_t)]
%[define_replacement(pos32_t = __pos32_t)]
%[define_replacement(pos64_t = __pos64_t)]
%[define_replacement(mode_t = __mode_t)]
%[define_replacement(oflag_t = __oflag_t)]
%[default_impl_section(.text.crt.system.mman)]

%{
#include <features.h>
#include <bits/types.h>
#include <bits/mman.h>

__SYSDECL_BEGIN

#ifdef __CC__
#ifndef __off_t_defined
#define __off_t_defined 1
typedef __typedef_off_t off_t;
#endif /* !__off_t_defined */

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __mode_t_defined
#define __mode_t_defined 1
typedef __mode_t mode_t;
#endif /* !__mode_t_defined */
#endif /* __CC__ */

#define PROT_NONE     0x00 /* Data cannot be accessed. */
#define PROT_EXEC     0x01 /* Data can be executed. */
#define PROT_WRITE    0x02 /* Data can be written. */
#define PROT_READ     0x04 /* Data can be read. */
#define PROT_SEM      0x08 /* Ignored... */


#if defined(__KOS__) && defined(__USE_KOS)
#if __KOS_VERSION__ >= 300
#define PROT_LOOSE    0x10 /* Unmap the region within the when cloning a VM (`CLONE_VM'). */
#else
#define PROT_LOOSE    0x10 /* Unmap the region within the when cloning a VM (`CLONE_VM').
                            * NOTE: Implicitly set for all system-allocated user stacks,
                            *       except for that of the calling thread. */
#endif
#define PROT_SHARED   0x20 /* Changes are shared, even after the VM was cloned (`CLONE_VM').
                            * NOTE: Same as the `MAP_SHARED' map flag, but
                            *       can be set like any other protection. */
#if defined(__USE_KOS_KERNEL) && __KOS_VERSION__ < 400
#define PROT_NOUSER   0x40 /* Map memory as inaccessible to user-space.
                            * WARNING: Not fully enforced for addresses within user-memory. */
#if __KOS_VERSION__ < 300
#define PROT_CLEAN    0x80 /* Unset whenever user-space re-maps a page as writable. - Cannot be removed.
                            * NOTE: This flag is used to prevent rootfork() from working
                            *       when called from an otherwise read-only module after
                            *       some portion of the section containing the root-fork
                            *       system call has been mapped as writable.
                            *    >> rootfork() fails when any page in the calling section (.text)
                            *       isn't part of a root-module, isn't fully mapped, was
                            *       re-mapped somewhere else, or been made writable at any point. */
#endif /* __KOS_VERSION__ < 300 */
#endif /* __USE_KOS_KERNEL && __KOS_VERSION__ < 400 */
#endif /* __USE_KOS */
#ifdef __USE_KOS_KERNEL
#define PROT_MASK     0x3f /* Mask of flags accessible from user-space. */
#endif /* __USE_KOS_KERNEL */



#if defined(__KOS__) && defined(__USE_KOS)
#ifndef MAP_AUTOMATIC
#define MAP_AUTOMATIC     0x00000000 /* Use sharing behavior specified by `PROT_SHARED'. */
#endif /* !MAP_AUTOMATIC */
#endif /* __KOS__ && __USE_KOS */
#ifndef MAP_SHARED
#define MAP_SHARED        0x00000001 /* Share changes. */
#endif /* !MAP_SHARED */
#ifndef MAP_PRIVATE
#define MAP_PRIVATE       0x00000002 /* Changes are private. */
#endif /* !MAP_PRIVATE */
#ifndef MAP_FIXED
#define MAP_FIXED         0x00000010 /* Interpret addr exactly. */
#endif /* !MAP_FIXED */

#ifdef __USE_MISC
#ifndef MAP_TYPE
#define MAP_TYPE          0x0000000f /* Mask for type of mapping. */
#endif /* !MAP_TYPE */
#ifndef MAP_FILE
#define MAP_FILE          0x00000000 /* Do use a file. */
#endif /* !MAP_FILE */
#ifndef MAP_ANONYMOUS
#ifdef MAP_ANON
#define MAP_ANONYMOUS     MAP_ANON   /* Don't use a file. */
#else /* MAP_ANON */
#define MAP_ANONYMOUS     0x00000020 /* Don't use a file. */
#endif /* !MAP_ANON */
#endif /* !MAP_ANONYMOUS */
#endif /* __USE_MISC */

#ifndef MAP_ANON
#ifdef MAP_ANONYMOUS
#define MAP_ANON          MAP_ANONYMOUS /* Don't use a file. */
#else /* MAP_ANONYMOUS */
#define MAP_ANON          0x00000020    /* Don't use a file. */
#endif /* !MAP_ANONYMOUS */
#endif /* !MAP_ANON */

/* Other flags. */
#ifdef __USE_MISC
#ifndef MAP_32BIT
#define MAP_32BIT         0x00000040 /* Only give out 32-bit addresses. */
#endif /* !MAP_32BIT */
#endif /* __USE_MISC */

/* These are Linux-specific (But also supported by KOS). */
#ifdef __USE_MISC
#ifndef MAP_GROWSDOWN
#define MAP_GROWSDOWN     0x00000100 /* Stack-like segment. */
#endif /* !MAP_GROWSDOWN */
#ifndef MAP_GROWSUP
#define MAP_GROWSUP       0x00000200 /* Stack-like segment growing upwards. */
#endif /* !MAP_GROWSUP */
#ifndef MAP_DENYWRITE
#define MAP_DENYWRITE     0x00000800 /* Ignored. */
#endif /* !MAP_DENYWRITE */
#ifndef MAP_EXECUTABLE
#define MAP_EXECUTABLE    0x00001000 /* Ignored. */
#endif /* !MAP_EXECUTABLE */
#ifndef MAP_LOCKED
#define MAP_LOCKED        0x00002000 /* Lock the mapping. */
#endif /* !MAP_LOCKED */
#ifndef MAP_NORESERVE
#define MAP_NORESERVE     0x00004000 /* Don't check for reservations. */
#endif /* !MAP_NORESERVE */
#ifndef MAP_POPULATE
#define MAP_POPULATE      0x00008000 /* Populate (prefault) pagetables. */
#endif /* !MAP_POPULATE */
#ifndef MAP_NONBLOCK
#define MAP_NONBLOCK      0x00010000 /* Do not block on IO. */
#endif /* !MAP_NONBLOCK */
#ifndef MAP_STACK
#define MAP_STACK         0x00020000 /* Allocation is for a stack.
                                      * NOTE: KOS uses this flag to determine where
                                      *       automatic memory mappings are allocated at. */
#endif /* !MAP_STACK */
#ifndef MAP_SYNC
#define MAP_SYNC          0x00000000 /* XXX: Implement me? */
#endif /* !MAP_SYNC */
#ifndef MAP_HUGETLB
#define MAP_HUGETLB       0x00040000 /* Create huge page mapping. */
#define MAP_HUGE_SHIFT    26
#define MAP_HUGE_MASK     0x3f
#endif /* !MAP_HUGETLB */
#ifndef MAP_UNINITIALIZED
#define MAP_UNINITIALIZED 0x04000000 /* For anonymous mmap, memory could be uninitialized.
                                      * NOTE: Implied for physical mappings.
                                      * NOTE: The kernel may initialize memory randomly in sandboxed threads. */
#endif /* !MAP_UNINITIALIZED */
#if __KOS_VERSION__ >= 400 && defined(__USE_KOS_KERNEL)
#define MAP_DONT_MAP         0x20000000 /* Don't actually map memory, but test the waters of a memory
                                         * location hasn't already been mapped, or locate a suitably
                                         * large free memory range.
                                         * This flag is usually followed by another call that sets
                                         * the `MAP_DONT_OVERRIDE' flag. */
#define MAP_DONT_OVERRIDE    0x40000000 /* Don't override existing mappings when `MAP_FIXED' is passed.
                                         * Instead, TODO:ERROR. */
#if __SIZEOF_POINTER__ < 8
#define MAP_OFFSET64_POINTER 0x80000000 /* The `OFFSET' argument of MMAP is actually a pointer to the 64-bit
                                         * unsigned integer that should actually be used as offset. */
#endif /* __SIZEOF_POINTER__ < 8 */
#endif
#endif /* __USE_MISC */

/* Error return value for `mmap()' */
#ifndef MAP_FAILED
#define MAP_FAILED   ((void *)-1)
#endif /* !MAP_FAILED */

/* Extended flags for use with `mprotect()' */
#define PROT_GROWSDOWN 0x01000000 /* Same as `MAP_GROWSDOWN', but may be used with `mprotect()' */
#define PROT_GROWSUP   0x02000000 /* Same as `MAP_GROWSUP', but may be used with `mprotect()' */

/* Flags accepted by `msync()'.  */
#define MS_ASYNC      0x01 /* Perform the operation asynchronously. */
#define MS_INVALIDATE 0x02 /* Invalidate caches. */
#define MS_SYNC       0x04 /* Wait for the sync to finish. */

/* Flags for 'mremap'. */
#ifdef __USE_GNU
#define MREMAP_MAYMOVE 0x01 /* Allowed to move to a different location */
#define MREMAP_FIXED   0x02 /* Allowed to move to a different location */
#endif /* __USE_GNU */

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


/* Advice to `madvise'. */
#ifdef __USE_MISC
#define MADV_NORMAL      0   /* No further special treatment. */
#define MADV_RANDOM      1   /* Expect random page references. */
#define MADV_SEQUENTIAL  2   /* Expect sequential page references. */
#define MADV_WILLNEED    3   /* Will need these pages. */
#define MADV_DONTNEED    4   /* Don't need these pages. */
#define MADV_REMOVE      9   /* Remove these pages and resources. */
#define MADV_DONTFORK    10  /* Do not inherit across fork. */
#define MADV_DOFORK      11  /* Do inherit across fork. */
#define MADV_MERGEABLE   12  /* KSM may merge identical pages. */
#define MADV_UNMERGEABLE 13  /* KSM may not merge identical pages. */
#define MADV_HUGEPAGE    14  /* Worth backing with hugepages. */
#define MADV_NOHUGEPAGE  15  /* Not worth backing with hugepages. */
#define MADV_DONTDUMP    16  /* Explicity exclude from the core dump, overrides the coredump filter bits. */
#define MADV_DODUMP      17  /* Clear the MADV_DONTDUMP flag. */
#define MADV_HWPOISON    100 /* Poison a page for testing. */
#endif /* __USE_MISC */

/* The POSIX people had to invent similar names for the same things.  */
#ifdef __USE_XOPEN2K
#define POSIX_MADV_NORMAL     0 /* No further special treatment. */
#define POSIX_MADV_RANDOM     1 /* Expect random page references. */
#define POSIX_MADV_SEQUENTIAL 2 /* Expect sequential page references. */
#define POSIX_MADV_WILLNEED   3 /* Will need these pages. */
#define POSIX_MADV_DONTNEED   4 /* Don't need these pages. */
#endif /* __USE_XOPEN2K */

/* Flags for `mlockall'.  */
#ifndef MCL_CURRENT
#define MCL_CURRENT 1 /* Lock all currently mapped pages. */
#define MCL_FUTURE  2 /* Lock all additions to address space. */
#define MCL_ONFAULT 4 /* Lock all pages that are faulted in. */
#endif /* !MCL_CURRENT */



#ifdef __CC__
}

[doc_alias(mmap)][section(.text.crt.heap.mman)]
[ignore] mmap32:(void *addr, size_t len, int prot, int flags, $fd_t fd, $off32_t offset) -> void * = mmap?;

@@@param prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
@@@param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
@@              with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
@@              MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
@@              MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE'
[section(.text.crt.heap.mman)]
[if(defined(__USE_FILE_OFFSET64)), preferred_alias(mmap64)]
[if(!defined(__USE_FILE_OFFSET64)), preferred_alias(mmap)]
[alias_args(mmap64:(void *addr, size_t len, int prot, int flags, $fd_t fd, $off64_t offset) -> void *)]
[alias_args(mmap:(void *addr, size_t len, int prot, int flags, $fd_t fd, $off32_t offset) -> void *)]
[noexport][ATTR_WUNUSED][requires(defined(__CRT_HAVE_mmap) || defined(__CRT_HAVE_mmap64))]
mmap:(void *addr, size_t len, int prot, int flags, $fd_t fd, $off_t offset) -> void * {
#ifdef __CRT_HAVE_mmap64
	return mmap64(addr, len, prot, flags, fd, (__off32_t)offset);
#else /* __CRT_HAVE_mmap64 */
	return mmap32(addr, len, prot, flags, fd, (__off32_t)offset);
#endif /* !__CRT_HAVE_mmap64 */
}

@@Unmap memory from `addr...+=len'
[section(.text.crt.heap.mman)]
munmap:([nonnull] void *addr, size_t len) -> int;

@@@param prot: Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|
@@             PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED|PROT_GROWSUP|
@@             PROT_GROWSDOWN'
[section(.text.crt.system.mman)]
mprotect:([nonnull] void *addr, size_t len, int prot) -> int;

@@@param flags: Set of `MS_ASYNC|MS_INVALIDATE|MS_SYNC'
[cp] msync:([nonnull] void *addr, size_t len, int flags) -> int;
mlock:([nonnull] void const *addr, size_t len) -> int;
munlock:([nonnull] void const *addr, size_t len) -> int;

@@@param flags: Set of `MCL_CURRENT|MCL_FUTURE|MCL_ONFAULT'
mlockall:(int flags) -> int;

munlockall:() -> int;
[cp] shm_open:([nonnull] char const *name, $oflag_t oflag, mode_t mode) -> int;
[cp] shm_unlink:([nonnull] char const *name) -> int;

%
%#ifdef __USE_MISC

[noexport]
[export_alias(__madvise)]
madvise:([nonnull] void *addr, size_t len, int advice) -> int {
	/* Implement as a no-op, since this function is merely meant as a hint */
	(void)addr;
	(void)len;
	(void)advice;
	return 0;
}
mincore:([nonnull] void *start, size_t len, unsigned char *vec) -> int;

%#endif /* __USE_MISC */


%
%#ifdef __USE_LARGEFILE64
[section(.text.crt.heap.mman)][off64_variant_of(mmap)]
[doc_alias(mmap)][noexport][ATTR_WUNUSED][requires(defined(__CRT_HAVE_mmap))]
mmap64:(void *addr, size_t len, int prot, int flags, $fd_t fd, $off64_t offset) -> void * {
	return mmap32(addr, len, prot, flags, fd, (off32_t)offset);
}
%#endif /* __USE_LARGEFILE64 */


%
%#ifdef __USE_XOPEN2K

[noexport]
posix_madvise:([nonnull] void *addr, size_t len, int advice) -> int {
	/* Implement as a no-op, since this function is merely meant as a hint */
	(void)addr;
	(void)len;
	(void)advice;
	return 0;
}

%#endif /* __USE_XOPEN2K */

%
%#ifdef __USE_GNU

@@@param flags: Set of `MREMAP_MAYMOVE|MREMAP_FIXED'
[section(.text.crt.heap.mman)][vartypes(void *)]
mremap:(void *addr, size_t old_len, size_t new_len, int flags, ... /* void *new_address */) -> void *;

remap_file_pages:(void *start, size_t size, int prot, size_t pgoff, int flags) -> int;

%#endif /* __USE_GNU */

%{

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_SYS_MMAN_H)
#include <parts/uchar/sys/mman.h>
#endif
#endif /* __USE_UTF */

}