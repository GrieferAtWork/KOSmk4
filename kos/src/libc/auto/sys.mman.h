/* HASH CRC-32:0xab84fe0c */
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
#ifndef GUARD_LIBC_AUTO_SYS_MMAN_H
#define GUARD_LIBC_AUTO_SYS_MMAN_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/mman.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mmap(2), mmap64(2)
 * @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED'
 * @param flags: One of `MAP_SHARED', 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE  | MAP_STACK | MAP_SYNC  |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE' */
INTDEF WUNUSED ATTR_ACCESS_NONE(1) ATTR_FDARG(5) void *NOTHROW_NCX(LIBDCALL libd_mmap)(void *addr, size_t len, __STDC_INT_AS_UINT_T prot, __STDC_INT_AS_UINT_T flags, fd_t fd, __PIO_OFFSET offset);
/* >> munmap(2)
 * Unmap memory from `addr...+=len' */
INTDEF ATTR_ACCESS_NONE(1) int NOTHROW_NCX(LIBDCALL libd_munmap)(void *addr, size_t len);
/* >> mprotect(2)
 * @param prot: Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE |
 *              PROT_READ | PROT_SEM | PROT_GROWSUP | PROT_GROWSDOWN' */
INTDEF ATTR_ACCESS_NONE(1) int NOTHROW_NCX(LIBDCALL libd_mprotect)(void *addr, size_t len, __STDC_INT_AS_UINT_T prot);
/* >> msync(2)
 * @param flags: Set of `MS_ASYNC | MS_INVALIDATE | MS_SYNC' */
INTDEF ATTR_ACCESS_NONE(1) int NOTHROW_RPC(LIBDCALL libd_msync)(void *addr, size_t len, __STDC_INT_AS_UINT_T flags);
/* >> mlock(2) */
INTDEF ATTR_ACCESS_NONE(1) int NOTHROW_NCX(LIBDCALL libd_mlock)(void const *addr, size_t len);
/* >> munlock(2) */
INTDEF ATTR_ACCESS_NONE(1) int NOTHROW_NCX(LIBDCALL libd_munlock)(void const *addr, size_t len);
/* >> mlockall(2)
 * @param flags: Set of `MCL_CURRENT | MCL_FUTURE | MCL_ONFAULT' */
INTDEF int NOTHROW_NCX(LIBDCALL libd_mlockall)(__STDC_INT_AS_UINT_T flags);
/* Weird function that just returns "/dev/shm/" */
INTDEF const char *NOTHROW_NCX(LIBDCALL libd___shm_directory)(size_t *len);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* Weird function that just returns "/dev/shm/" */
INTDEF const char *NOTHROW_NCX(LIBCCALL libc___shm_directory)(size_t *len);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> shm_open(3) */
INTDEF ATTR_IN(1) fd_t NOTHROW_RPC(LIBDCALL libd_shm_open)(char const *name, oflag_t oflags, mode_t mode);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> shm_open(3) */
INTDEF ATTR_IN(1) fd_t NOTHROW_RPC(LIBCCALL libc_shm_open)(char const *name, oflag_t oflags, mode_t mode);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> shm_unlink(3) */
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_shm_unlink)(char const *name);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> shm_unlink(3) */
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBCCALL libc_shm_unlink)(char const *name);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> posix_madvise(3)
 * Advice on how memory should be managed by the kernel
 * @param: advice: One of `MADV_*' */
INTDEF ATTR_ACCESS_NONE(1) int NOTHROW_NCX(LIBDCALL libd_madvise)(void *addr, size_t len, __STDC_INT_AS_UINT_T advice);
INTDEF ATTR_ACCESS_NONE(1) int NOTHROW_NCX(LIBDCALL libd_mincore)(void *start, size_t len, unsigned char *vec);
/* >> mmap(2), mmap64(2)
 * @param prot:  Either `PROT_NONE', or set of `PROT_EXEC | PROT_WRITE | PROT_READ | PROT_SEM | PROT_SHARED'
 * @param flags: One of `MAP_SHARED', 'MAP_SHARED_VALIDATE' or `MAP_PRIVATE', optionally or'd
 *               with a set of `MAP_ANONYMOUS | MAP_FIXED | MAP_GROWSDOWN | MAP_LOCKED|
 *               MAP_NONBLOCK | MAP_NORESERVE | MAP_POPULATE  | MAP_STACK | MAP_SYNC  |
 *               MAP_UNINITIALIZED | MAP_DONT_MAP | MAP_FIXED_NOREPLACE' */
INTDEF WUNUSED ATTR_ACCESS_NONE(1) ATTR_FDARG(5) void *NOTHROW_NCX(LIBDCALL libd_mmap64)(void *addr, size_t len, __STDC_INT_AS_UINT_T prot, __STDC_INT_AS_UINT_T flags, fd_t fd, __PIO_OFFSET64 offset);
/* >> posix_madvise(3)
 * Wrapper around `madvise(2)'
 * @param: advice: One of `POSIX_MADV_*' */
INTDEF ATTR_ACCESS_NONE(1) errno_t NOTHROW_NCX(LIBDCALL libd_posix_madvise)(void *addr, size_t len, __STDC_INT_AS_UINT_T advice);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> posix_madvise(3)
 * Wrapper around `madvise(2)'
 * @param: advice: One of `POSIX_MADV_*' */
INTDEF ATTR_ACCESS_NONE(1) errno_t NOTHROW_NCX(LIBCCALL libc_posix_madvise)(void *addr, size_t len, __STDC_INT_AS_UINT_T advice);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> mremap(2)
 * @param flags: Set of `MREMAP_MAYMOVE | MREMAP_FIXED' */
INTDEF ATTR_ACCESS_NONE(1) void *NOTHROW_NCX(VLIBDCALL libd_mremap)(void *addr, size_t old_len, size_t new_len, __STDC_INT_AS_UINT_T flags, ...);
/* >> remap_file_pages(2) */
INTDEF ATTR_ACCESS_NONE(1) int NOTHROW_NCX(LIBDCALL libd_remap_file_pages)(void *start, size_t size, __STDC_INT_AS_UINT_T prot, size_t pgoff, __STDC_INT_AS_UINT_T flags);
/* >> memfd_create(2)
 * @param: name:  Set `/proc/[pid]/fd/[return]' = "memfd:${name}"
 * @param: flags: Set of `MFD_CLOEXEC | MFD_CLOFORK | MFD_ALLOW_SEALING | MFD_HUGETLB' */
INTDEF fd_t NOTHROW_NCX(LIBDCALL libd_memfd_create)(char const *name, unsigned int flags);
/* >> mlock2(2) */
INTDEF ATTR_ACCESS_NONE(1) int NOTHROW_NCX(LIBDCALL libd_mlock2)(void const *addr, size_t length, unsigned int flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#include <asm/pkey.h>
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY)
/* >> pkey_alloc(2) */
INTDEF int NOTHROW_NCX(LIBDCALL libd_pkey_alloc)(unsigned int flags, unsigned int access_rights);
/* >> pkey_set(3) */
INTDEF int NOTHROW_NCX(LIBDCALL libd_pkey_set)(int pkey, unsigned int access_rights);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ && __ARCH_HAVE_PKEY */
#if !defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY)
/* >> pkey_set(3) */
INTDEF int NOTHROW_NCX(LIBCCALL libc_pkey_set)(int pkey, unsigned int access_rights);
#endif /* !__KERNEL__ && __ARCH_HAVE_PKEY */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY)
/* >> pkey_get(3) */
INTDEF int NOTHROW_NCX(LIBDCALL libd_pkey_get)(int pkey);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ && __ARCH_HAVE_PKEY */
#if !defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY)
/* >> pkey_get(3) */
INTDEF int NOTHROW_NCX(LIBCCALL libc_pkey_get)(int pkey);
#endif /* !__KERNEL__ && __ARCH_HAVE_PKEY */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__) && defined(__ARCH_HAVE_PKEY)
/* >> pkey_free(2) */
INTDEF int NOTHROW_NCX(LIBDCALL libd_pkey_free)(int pkey);
/* >> pkey_mprotect(2) */
INTDEF ATTR_ACCESS_NONE(1) int NOTHROW_NCX(LIBDCALL libd_pkey_mprotect)(void *addr, size_t len, __STDC_INT_AS_UINT_T prot, int pkey);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ && __ARCH_HAVE_PKEY */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> fmapfile(3)
 * A function that can be used to map a specific sub-range of some file into memory.
 * This function tries the following (in this order) in order to create the mapping:
 *  - mmap(2):                        If `fd' can be mmap'd, then that is how the mapping is created
 *  - malloc(3) + pread(2):           If `fd' supports pread(2), use that to fill a buffer
 *  - malloc(3) + lseek(2) + read(2): For a non-zero offset, try to use lseek(2) to move to `offset'
 *  - malloc(3) + read(2):            When lseek(2) returns an error, use read(2) to skip `offset',
 *                                    after which  up  to  `max_bytes'  bytes  are  read  normally.
 * Upon success (return == 0), the given `mapping' must be deleted using `unmapfile(3)'
 * @param: fd:        The file that should be loaded into memory.
 * @param: mapping:   Filled with mapping information. This structure contains at least 2 fields:
 *                     - mf_addr: Filled with the base address of a mapping of the file's contents
 *                     - mf_size: The actual number of mapped bytes (excluding `num_trailing_nulbytes')
 *                                This will always be `>= min_bytes && <= max_bytes'.
 *                     - Other fields are implementation-specific
 *                    Note that the memory located at `mapping->mf_addr' is writable, though changes  to
 *                    it are guarantied not to be written back to `fd'. iow: it behaves like MAP_PRIVATE
 *                    mapped as PROT_READ|PROT_WRITE.
 * @param: offset:    File offset / number of leading bytes that should not be  mapped
 *                    When set to `(Dee_pos_t)-1', use the fd's current file position.
 * @param: min_bytes: The  min number of bytes (excluding num_trailing_nulbytes) that should be mapped
 *                    starting  at `offset'. If the file is smaller than this, or indicates EOF before
 *                    this number of bytes has been reached,  nul bytes are mapped for its  remainder.
 *                    Note that this doesn't include `num_trailing_nulbytes', meaning that (e.g.) when
 *                    an entirely empty file is mapped you get a buffer like:
 *                    >> mf_addr = calloc(min_size + num_trailing_nulbytes);
 *                    >> mf_size = min_size;
 *                    This argument essentially acts as if `fd' was at least `min_bytes' bytes large
 *                    by filling the non-present address range with all zeroes.
 * @param: max_bytes: The  max number of bytes (excluding num_trailing_nulbytes) that should be mapped
 *                    starting  at `offset'. If the file is smaller than this, or indicates EOF before
 *                    this number of bytes has been reached, simply stop there. - The actual number of
 *                    mapped bytes (excluding `num_trailing_nulbytes') is `mapping->mf_size'.
 * @param: num_trailing_nulbytes: When non-zero, append this many trailing NUL-bytes at the end of
 *                    the mapping. More bytes than this may be appended if necessary, but at least
 *                    this many are guarantied  to be. - Useful  if you want to  load a file as  a
 *                    string,  in which case you can specify `1' to always have a trailing '\0' be
 *                    appended:
 *                    >> bzero(mapping->mf_addr + mapping->mf_size, num_trailing_nulbytes);
 * @param: flags:     Set of `FMAPFILE_*'
 * @return: 0 : Success (the given `mapping' must be deleted using `unmapfile(3)')
 * @return: -1: [errno=EINVAL]  The given `flags' contains invalid bits.
 * @return: -1: [errno=EINVAL]  `FMAPFILE_MAPSHARED' was set,  an mmap  was
 *                              attempted, and `num_trailing_nulbytes != 0'
 * @return: -1: [errno=EPERM]   `fd' doesn't support read(2)ing
 * @return: -1: [errno=ENOMEM]  Out of memory (or file is too large for a continuous heap-buffer to be posible)
 * @return: -1: [errno=EBADF]   Invalid `fd'
 * @return: -1: [errno=ENOTSUP] `FMAPFILE_ONLYMMAP' was given, and mmap  wasn't possible, either because a  call
 *                              to  `mmap(2)' with the  given `fd' returned an  error (including indicating that
 *                              the file doesn't support mmap(), or that there isn't enough space t map the file
 *                              in its entirety), or because  `max_bytes == (size_t)-1', and the effective  area
 *                              that you are trying to map is larger than the entirety of your address space.
 * @return: -1: [errno=*]       Read error */
INTDEF WUNUSED ATTR_FDARG(2) ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_fmapfile)(struct mapfile *__restrict mapping, fd_t fd, pos64_t offset, size_t min_bytes, size_t max_bytes, size_t num_trailing_nulbytes, unsigned int flags);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> fmapfile(3)
 * A function that can be used to map a specific sub-range of some file into memory.
 * This function tries the following (in this order) in order to create the mapping:
 *  - mmap(2):                        If `fd' can be mmap'd, then that is how the mapping is created
 *  - malloc(3) + pread(2):           If `fd' supports pread(2), use that to fill a buffer
 *  - malloc(3) + lseek(2) + read(2): For a non-zero offset, try to use lseek(2) to move to `offset'
 *  - malloc(3) + read(2):            When lseek(2) returns an error, use read(2) to skip `offset',
 *                                    after which  up  to  `max_bytes'  bytes  are  read  normally.
 * Upon success (return == 0), the given `mapping' must be deleted using `unmapfile(3)'
 * @param: fd:        The file that should be loaded into memory.
 * @param: mapping:   Filled with mapping information. This structure contains at least 2 fields:
 *                     - mf_addr: Filled with the base address of a mapping of the file's contents
 *                     - mf_size: The actual number of mapped bytes (excluding `num_trailing_nulbytes')
 *                                This will always be `>= min_bytes && <= max_bytes'.
 *                     - Other fields are implementation-specific
 *                    Note that the memory located at `mapping->mf_addr' is writable, though changes  to
 *                    it are guarantied not to be written back to `fd'. iow: it behaves like MAP_PRIVATE
 *                    mapped as PROT_READ|PROT_WRITE.
 * @param: offset:    File offset / number of leading bytes that should not be  mapped
 *                    When set to `(Dee_pos_t)-1', use the fd's current file position.
 * @param: min_bytes: The  min number of bytes (excluding num_trailing_nulbytes) that should be mapped
 *                    starting  at `offset'. If the file is smaller than this, or indicates EOF before
 *                    this number of bytes has been reached,  nul bytes are mapped for its  remainder.
 *                    Note that this doesn't include `num_trailing_nulbytes', meaning that (e.g.) when
 *                    an entirely empty file is mapped you get a buffer like:
 *                    >> mf_addr = calloc(min_size + num_trailing_nulbytes);
 *                    >> mf_size = min_size;
 *                    This argument essentially acts as if `fd' was at least `min_bytes' bytes large
 *                    by filling the non-present address range with all zeroes.
 * @param: max_bytes: The  max number of bytes (excluding num_trailing_nulbytes) that should be mapped
 *                    starting  at `offset'. If the file is smaller than this, or indicates EOF before
 *                    this number of bytes has been reached, simply stop there. - The actual number of
 *                    mapped bytes (excluding `num_trailing_nulbytes') is `mapping->mf_size'.
 * @param: num_trailing_nulbytes: When non-zero, append this many trailing NUL-bytes at the end of
 *                    the mapping. More bytes than this may be appended if necessary, but at least
 *                    this many are guarantied  to be. - Useful  if you want to  load a file as  a
 *                    string,  in which case you can specify `1' to always have a trailing '\0' be
 *                    appended:
 *                    >> bzero(mapping->mf_addr + mapping->mf_size, num_trailing_nulbytes);
 * @param: flags:     Set of `FMAPFILE_*'
 * @return: 0 : Success (the given `mapping' must be deleted using `unmapfile(3)')
 * @return: -1: [errno=EINVAL]  The given `flags' contains invalid bits.
 * @return: -1: [errno=EINVAL]  `FMAPFILE_MAPSHARED' was set,  an mmap  was
 *                              attempted, and `num_trailing_nulbytes != 0'
 * @return: -1: [errno=EPERM]   `fd' doesn't support read(2)ing
 * @return: -1: [errno=ENOMEM]  Out of memory (or file is too large for a continuous heap-buffer to be posible)
 * @return: -1: [errno=EBADF]   Invalid `fd'
 * @return: -1: [errno=ENOTSUP] `FMAPFILE_ONLYMMAP' was given, and mmap  wasn't possible, either because a  call
 *                              to  `mmap(2)' with the  given `fd' returned an  error (including indicating that
 *                              the file doesn't support mmap(), or that there isn't enough space t map the file
 *                              in its entirety), or because  `max_bytes == (size_t)-1', and the effective  area
 *                              that you are trying to map is larger than the entirety of your address space.
 * @return: -1: [errno=*]       Read error */
INTDEF WUNUSED ATTR_FDARG(2) ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_fmapfile)(struct mapfile *__restrict mapping, fd_t fd, pos64_t offset, size_t min_bytes, size_t max_bytes, size_t num_trailing_nulbytes, unsigned int flags);
/* >> fmapfileat(3)
 * Map the specified `filename' into memory. s.a. `fmapfile(3)'
 * @param: atflags: Set of `0 | AT_DOSPATH | AT_EMPTY_PATH' */
INTDEF WUNUSED ATTR_IN(3) ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_fmapfileat)(struct mapfile *__restrict mapping, fd_t dirfd, char const *filename, pos64_t offset, size_t min_bytes, size_t max_bytes, size_t num_trailing_nulbytes, unsigned int flags, atflag_t atflags);
/* >> fmapfileat(3)
 * Map the specified `filename' into memory. s.a. `fmapfile(3)'
 * @param: atflags: Set of `0 | AT_DOSPATH | AT_EMPTY_PATH' */
INTDEF WUNUSED ATTR_IN(3) ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_fmapfileat)(struct mapfile *__restrict mapping, fd_t dirfd, char const *filename, pos64_t offset, size_t min_bytes, size_t max_bytes, size_t num_trailing_nulbytes, unsigned int flags, atflag_t atflags);
/* >> mapfile(3)
 * Map the specified `filename' into memory. s.a. `fmapfile(3)' */
INTDEF WUNUSED ATTR_IN(2) ATTR_OUT(1) int NOTHROW_NCX(LIBDCALL libd_mapfile)(struct mapfile *__restrict mapping, char const *filename, pos64_t offset, size_t min_bytes, size_t max_bytes, size_t num_trailing_nulbytes, unsigned int flags);
/* >> mapfile(3)
 * Map the specified `filename' into memory. s.a. `fmapfile(3)' */
INTDEF WUNUSED ATTR_IN(2) ATTR_OUT(1) int NOTHROW_NCX(LIBCCALL libc_mapfile)(struct mapfile *__restrict mapping, char const *filename, pos64_t offset, size_t min_bytes, size_t max_bytes, size_t num_trailing_nulbytes, unsigned int flags);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> unmapfile(3)
 * Delete a file mapping previously created by `mapfile(3)' */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBDCALL libd_unmapfile)(struct mapfile *__restrict mapping);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
/* >> unmapfile(3)
 * Delete a file mapping previously created by `mapfile(3)' */
INTDEF ATTR_INOUT(1) int NOTHROW_NCX(LIBCCALL libc_unmapfile)(struct mapfile *__restrict mapping);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SYS_MMAN_H */
