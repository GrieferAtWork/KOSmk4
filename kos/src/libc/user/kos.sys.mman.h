/* HASH CRC-32:0x3d271f3d */
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
#ifndef GUARD_LIBC_USER_KOS_SYS_MMAN_H
#define GUARD_LIBC_USER_KOS_SYS_MMAN_H 1

#include "../api.h"
#include "../auto/kos.sys.mman.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/sys/mman.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> mmap(2), mmap64(2)
 * @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED'
 * @param flags: One of `MAP_SHARED', 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE  | MAP_STACK | MAP_SYNC  |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE' */
INTDEF WUNUSED ATTR_ACCESS_NONE(1) ATTR_FDARG(5) void *(LIBCCALL libc_MMap)(void *addr, size_t len, __STDC_INT_AS_UINT_T prot, __STDC_INT_AS_UINT_T flags, fd_t fd, pos_t offset) THROWS(...);
/* >> munmap(2)
 * Unmap memory from `addr...+=len' */
INTDEF ATTR_ACCESS_NONE(1) void (LIBCCALL libc_MUnmap)(void *addr, size_t len) THROWS(...);
/* >> mprotect(2)
 * @param prot: Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE |
 *              PROT_READ | PROT_SEM | PROT_GROWSUP | PROT_GROWSDOWN' */
INTDEF ATTR_ACCESS_NONE(1) void (LIBCCALL libc_MProtect)(void *addr, size_t len, __STDC_INT_AS_UINT_T prot) THROWS(...);
/* >> msync(2)
 * @param flags: Set of `MS_ASYNC | MS_INVALIDATE | MS_SYNC' */
INTDEF ATTR_ACCESS_NONE(1) void (LIBCCALL libc_MSync)(void *addr, size_t len, __STDC_INT_AS_UINT_T flags) THROWS(...);
/* >> mlock(2) */
INTDEF ATTR_ACCESS_NONE(1) void (LIBCCALL libc_MLock)(void const *addr, size_t len) THROWS(...);
/* >> munlock(2) */
INTDEF ATTR_ACCESS_NONE(1) void (LIBCCALL libc_MUnlock)(void const *addr, size_t len) THROWS(...);
/* >> mlockall(2)
 * @param flags: Set of `MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT' */
INTDEF void (LIBCCALL libc_MLockAll)(__STDC_INT_AS_UINT_T flags) THROWS(...);
/* >> munlockall(2) */
INTDEF void (LIBCCALL libc_MUnlockAll)(void) THROWS(...);
/* >> posix_madvise(3)
 * Advice on how memory should be managed by the kernel
 * @param: advice: One of `MADV_*' */
INTDEF ATTR_ACCESS_NONE(1) void (LIBCCALL libc_MAdvise)(void *addr, size_t len, __STDC_INT_AS_UINT_T advice) THROWS(...);
INTDEF ATTR_ACCESS_NONE(1) void (LIBCCALL libc_MInCore)(void *start, size_t len, unsigned char *vec) THROWS(...);
/* >> mmap(2), mmap64(2)
 * @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED'
 * @param flags: One of `MAP_SHARED', 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE  | MAP_STACK | MAP_SYNC  |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE' */
INTDEF WUNUSED ATTR_ACCESS_NONE(1) ATTR_FDARG(5) void *(LIBCCALL libc_MMap64)(void *addr, size_t len, __STDC_INT_AS_UINT_T prot, __STDC_INT_AS_UINT_T flags, fd_t fd, pos64_t offset) THROWS(...);
/* >> posix_madvise(3)
 * Wrapper around `madvise(2)'
 * @param: advice: One of `POSIX_MADV_*' */
INTDEF ATTR_ACCESS_NONE(1) void (LIBCCALL libc_PosixMAdvise)(void *addr, size_t len, __STDC_INT_AS_UINT_T advice) THROWS(...);
/* >> mremap(2)
 * @param flags: Set of `MREMAP_MAYMOVE | MREMAP_FIXED' */
INTDEF ATTR_ACCESS_NONE(1) void *(VLIBCCALL libc_MRemap)(void *addr, size_t old_len, size_t new_len, __STDC_INT_AS_UINT_T flags, ...) THROWS(...);
/* >> remap_file_pages(2) */
INTDEF ATTR_ACCESS_NONE(1) void (LIBCCALL libc_RemapFilePages)(void *start, size_t size, __STDC_INT_AS_UINT_T prot, size_t pgoff, __STDC_INT_AS_UINT_T flags) THROWS(...);
/* >> memfd_create(2)
 * @param: name:  Set `/proc/[pid]/fd/[return]' = "memfd:${name}"
 * @param: flags: Set of `MFD_CLOEXEC | MFD_CLOFORK | MFD_ALLOW_SEALING | MFD_HUGETLB' */
INTDEF fd_t (LIBCCALL libc_MemFdCreate)(char const *name, unsigned int flags) THROWS(...);
/* >> mlock2(2) */
INTDEF ATTR_ACCESS_NONE(1) void (LIBCCALL libc_MLock2)(void const *addr, size_t length, unsigned int flags) THROWS(...);
#endif /* !__KERNEL__ */
#include <asm/pkey.h>
#if !defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY)
/* >> pkey_alloc(2) */
INTDEF int (LIBCCALL libc_PKeyAlloc)(unsigned int flags, unsigned int access_rights) THROWS(...);
/* >> pkey_free(2) */
INTDEF void (LIBCCALL libc_PKeyFree)(int pkey) THROWS(...);
/* >> pkey_mprotect(2) */
INTDEF ATTR_ACCESS_NONE(1) void (LIBCCALL libc_PKeyMProtect)(void *addr, size_t len, __STDC_INT_AS_UINT_T prot, int pkey) THROWS(...);
#endif /* !__KERNEL__ && __ARCH_HAVE_PKEY */

DECL_END

#endif /* !GUARD_LIBC_USER_KOS_SYS_MMAN_H */
