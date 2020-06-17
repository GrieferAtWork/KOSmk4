/* HASH CRC-32:0x7a938e6 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_SYS_MMAN_C
#define GUARD_LIBC_AUTO_DOSABI_SYS_MMAN_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/sys.mman.h"

DECL_BEGIN

/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE | MAP_STACK | MAP_SYNC |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_DONT_OVERRIDE' */
INTERN ATTR_SECTION(".text.crt.dos.heap.mman") WUNUSED void *
NOTHROW_NCX(LIBDCALL libd_mmap)(void *addr,
                                size_t len,
                                __STDC_INT_AS_UINT_T prot,
                                __STDC_INT_AS_UINT_T flags,
                                fd_t fd,
                                off_t offset) {
	return libc_mmap(addr, len, prot, flags, fd, offset);
}
/* Unmap memory from `addr...+=len' */
INTERN ATTR_SECTION(".text.crt.dos.heap.mman") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_munmap)(void *addr,
                                  size_t len) {
	return libc_munmap(addr, len);
}
/* @param prot: Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE |
 *              PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED |
 *              PROT_GROWSUP | PROT_GROWSDOWN' */
INTERN ATTR_SECTION(".text.crt.dos.system.mman") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_mprotect)(void *addr,
                                    size_t len,
                                    __STDC_INT_AS_UINT_T prot) {
	return libc_mprotect(addr, len, prot);
}
/* @param flags: Set of `MS_ASYNC | MS_INVALIDATE | MS_SYNC' */
INTERN ATTR_SECTION(".text.crt.dos.system.mman") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_msync)(void *addr,
                                 size_t len,
                                 __STDC_INT_AS_UINT_T flags) {
	return libc_msync(addr, len, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.system.mman") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_mlock)(void const *addr,
                                 size_t len) {
	return libc_mlock(addr, len);
}
INTERN ATTR_SECTION(".text.crt.dos.system.mman") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_munlock)(void const *addr,
                                   size_t len) {
	return libc_munlock(addr, len);
}
/* @param flags: Set of `MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT' */
INTERN ATTR_SECTION(".text.crt.dos.system.mman") int
NOTHROW_NCX(LIBDCALL libd_mlockall)(__STDC_INT_AS_UINT_T flags) {
	return libc_mlockall(flags);
}
INTERN ATTR_SECTION(".text.crt.dos.system.mman") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_shm_open)(char const *name,
                                    oflag_t oflags,
                                    mode_t mode) {
	return libc_shm_open(name, oflags, mode);
}
INTERN ATTR_SECTION(".text.crt.dos.system.mman") NONNULL((1)) int
NOTHROW_RPC(LIBDCALL libd_shm_unlink)(char const *name) {
	return libc_shm_unlink(name);
}
INTERN ATTR_SECTION(".text.crt.dos.system.mman") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_madvise)(void *addr,
                                   size_t len,
                                   __STDC_INT_AS_UINT_T advice) {
	return libc_madvise(addr, len, advice);
}
INTERN ATTR_SECTION(".text.crt.dos.system.mman") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_mincore)(void *start,
                                   size_t len,
                                   unsigned char *vec) {
	return libc_mincore(start, len, vec);
}
/* @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_LOOSE | PROT_SHARED'
 * @param flags: One of `MAP_SHARED`, 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE | MAP_STACK | MAP_SYNC |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_DONT_OVERRIDE' */
INTERN ATTR_SECTION(".text.crt.dos.heap.mman") WUNUSED void *
NOTHROW_NCX(LIBDCALL libd_mmap64)(void *addr,
                                  size_t len,
                                  __STDC_INT_AS_UINT_T prot,
                                  __STDC_INT_AS_UINT_T flags,
                                  fd_t fd,
                                  off64_t offset) {
	return libc_mmap64(addr, len, prot, flags, fd, offset);
}
INTERN ATTR_SECTION(".text.crt.dos.system.mman") NONNULL((1)) int
NOTHROW_NCX(LIBDCALL libd_posix_madvise)(void *addr,
                                         size_t len,
                                         __STDC_INT_AS_UINT_T advice) {
	return libc_posix_madvise(addr, len, advice);
}
/* @param flags: Set of `MREMAP_MAYMOVE | MREMAP_FIXED' */
INTERN ATTR_SECTION(".text.crt.dos.heap.mman") void *
NOTHROW_NCX(VLIBDCALL libd_mremap)(void *addr,
                                   size_t old_len,
                                   size_t new_len,
                                   __STDC_INT_AS_UINT_T flags,
                                   ...) {
	va_list args;
	void *v0;
	va_start(args, flags);
	v0 = va_arg(args, void *);
	va_end(args);
	return libc_mremap(addr, old_len, new_len, flags, v0);
}
INTERN ATTR_SECTION(".text.crt.dos.system.mman") int
NOTHROW_NCX(LIBDCALL libd_remap_file_pages)(void *start,
                                            size_t size,
                                            __STDC_INT_AS_UINT_T prot,
                                            size_t pgoff,
                                            __STDC_INT_AS_UINT_T flags) {
	return libc_remap_file_pages(start, size, prot, pgoff, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.system.mman") fd_t
NOTHROW_NCX(LIBDCALL libd_memfd_create)(char const *name,
                                        unsigned int flags) {
	return libc_memfd_create(name, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.system.mman") int
NOTHROW_NCX(LIBDCALL libd_mlock2)(void const *addr,
                                  size_t length,
                                  unsigned int flags) {
	return libc_mlock2(addr, length, flags);
}
INTERN ATTR_SECTION(".text.crt.dos.system.mman") int
NOTHROW_NCX(LIBDCALL libd_pkey_alloc)(unsigned int flags,
                                      unsigned int access_rights) {
	return libc_pkey_alloc(flags, access_rights);
}
INTERN ATTR_SECTION(".text.crt.dos.system.mman") int
NOTHROW_NCX(LIBDCALL libd_pkey_set)(int key,
                                    unsigned int access_rights) {
	return libc_pkey_set(key, access_rights);
}
INTERN ATTR_SECTION(".text.crt.dos.system.mman") int
NOTHROW_NCX(LIBDCALL libd_pkey_get)(int key) {
	return libc_pkey_get(key);
}
INTERN ATTR_SECTION(".text.crt.dos.system.mman") int
NOTHROW_NCX(LIBDCALL libd_pkey_free)(int key) {
	return libc_pkey_free(key);
}
INTERN ATTR_SECTION(".text.crt.dos.system.mman") int
NOTHROW_NCX(LIBDCALL libd_pkey_mprotect)(void *addr,
                                         size_t len,
                                         __STDC_INT_AS_UINT_T prot,
                                         int pkey) {
	return libc_pkey_mprotect(addr, len, prot, pkey);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$mmap, libd_mmap);
DEFINE_PUBLIC_ALIAS(DOS$munmap, libd_munmap);
DEFINE_PUBLIC_ALIAS(DOS$mprotect, libd_mprotect);
DEFINE_PUBLIC_ALIAS(DOS$msync, libd_msync);
DEFINE_PUBLIC_ALIAS(DOS$mlock, libd_mlock);
DEFINE_PUBLIC_ALIAS(DOS$munlock, libd_munlock);
DEFINE_PUBLIC_ALIAS(DOS$mlockall, libd_mlockall);
DEFINE_PUBLIC_ALIAS(DOS$shm_open, libd_shm_open);
DEFINE_PUBLIC_ALIAS(DOS$shm_unlink, libd_shm_unlink);
DEFINE_PUBLIC_ALIAS(DOS$__madvise, libd_madvise);
DEFINE_PUBLIC_ALIAS(DOS$madvise, libd_madvise);
DEFINE_PUBLIC_ALIAS(DOS$mincore, libd_mincore);
DEFINE_PUBLIC_ALIAS(DOS$mmap64, libd_mmap64);
DEFINE_PUBLIC_ALIAS(DOS$posix_madvise, libd_posix_madvise);
DEFINE_PUBLIC_ALIAS(DOS$mremap, libd_mremap);
DEFINE_PUBLIC_ALIAS(DOS$remap_file_pages, libd_remap_file_pages);
DEFINE_PUBLIC_ALIAS(DOS$memfd_create, libd_memfd_create);
DEFINE_PUBLIC_ALIAS(DOS$mlock2, libd_mlock2);
DEFINE_PUBLIC_ALIAS(DOS$pkey_alloc, libd_pkey_alloc);
DEFINE_PUBLIC_ALIAS(DOS$pkey_set, libd_pkey_set);
DEFINE_PUBLIC_ALIAS(DOS$pkey_get, libd_pkey_get);
DEFINE_PUBLIC_ALIAS(DOS$pkey_free, libd_pkey_free);
DEFINE_PUBLIC_ALIAS(DOS$pkey_mprotect, libd_pkey_mprotect);

#endif /* !GUARD_LIBC_AUTO_DOSABI_SYS_MMAN_C */
