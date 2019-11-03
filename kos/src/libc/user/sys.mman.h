/* HASH CRC-32:0x7ca1aab4 */
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
#ifndef GUARD_LIBC_USER_SYS_MMAN_H
#define GUARD_LIBC_USER_SYS_MMAN_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/mman.h>

DECL_BEGIN

/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE' */
INTDEF WUNUSED void *NOTHROW_NCX(LIBCCALL libc_mmap)(void *addr, size_t len, int prot, int flags, fd_t fd, off_t offset);
/* Unmap memory from `addr...+=len' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_munmap)(void *addr, size_t len);
/* @param prot: Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|
 *              PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED|PROT_GROWSUP|
 *              PROT_GROWSDOWN' */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_mprotect)(void *addr, size_t len, int prot);
/* @param flags: Set of `MS_ASYNC|MS_INVALIDATE|MS_SYNC' */
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_msync)(void *addr, size_t len, int flags);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_mlock)(void const *addr, size_t len);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_munlock)(void const *addr, size_t len);
/* @param flags: Set of `MCL_CURRENT|MCL_FUTURE|MCL_ONFAULT' */
INTDEF int NOTHROW_NCX(LIBCCALL libc_mlockall)(int flags);
INTDEF int NOTHROW_NCX(LIBCCALL libc_munlockall)(void);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_shm_open)(char const *name, oflag_t oflags, mode_t mode);
INTDEF NONNULL((1)) int NOTHROW_RPC(LIBCCALL libc_shm_unlink)(char const *name);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_madvise)(void *addr, size_t len, int advice);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_mincore)(void *start, size_t len, unsigned char *vec);
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC|PROT_WRITE|PROT_READ|PROT_SEM|PROT_LOOSE|PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS|MAP_FIXED|MAP_GROWSDOWN|MAP_LOCKED|
 *               MAP_NONBLOCK|MAP_NORESERVE|MAP_POPULATE|MAP_STACK|MAP_SYNC|
 *               MAP_UNINITIALIZED|MAP_DONT_MAP|MAP_DONT_OVERRIDE' */
INTDEF WUNUSED void *NOTHROW_NCX(LIBCCALL libc_mmap64)(void *addr, size_t len, int prot, int flags, fd_t fd, off64_t offset);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_posix_madvise)(void *addr, size_t len, int advice);
/* @param flags: Set of `MREMAP_MAYMOVE|MREMAP_FIXED' */
INTDEF void *NOTHROW_NCX(VLIBCCALL libc_mremap)(void *addr, size_t old_len, size_t new_len, int flags, ... /* void *new_address */);
INTDEF int NOTHROW_NCX(LIBCCALL libc_remap_file_pages)(void *start, size_t size, int prot, size_t pgoff, int flags);

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_MMAN_H */
