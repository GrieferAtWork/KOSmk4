/* HASH CRC-32:0x9b4af38d */
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
#ifndef _FCNTL_H
#define _FCNTL_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <bits/fcntl.h>
#include <bits/types.h>
#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#include <asm/stdio.h>
#include <bits/stat.h>
#include <bits/timespec.h>
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */

__SYSDECL_BEGIN

#ifdef __O_TMPFILE
#   define __OPEN_NEEDS_MODE(oflags) (((oflags)&O_CREAT) || ((oflags)&__O_TMPFILE) == __O_TMPFILE)
#else /* __O_TMPFILE */
#   define __OPEN_NEEDS_MODE(oflags)  ((oflags)&O_CREAT)
#endif /* !__O_TMPFILE */

/* For XPG all symbols from <sys/stat.h> should also be available. */
#if !defined(S_IFMT) && (defined(__USE_XOPEN) || defined(__USE_XOPEN2K8))
#define S_IFMT     __S_IFMT
#define S_IFDIR    __S_IFDIR
#define S_IFCHR    __S_IFCHR
#define S_IFBLK    __S_IFBLK
#define S_IFREG    __S_IFREG
#ifdef __S_IFIFO
#define S_IFIFO __S_IFIFO
#endif /* __S_IFIFO */
#ifdef __S_IFLNK
#define S_IFLNK __S_IFLNK
#endif /* __S_IFLNK */
#if (defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)) && defined(__S_IFSOCK)
#define S_IFSOCK __S_IFSOCK
#endif /* (__USE_UNIX98 || __USE_XOPEN2K8) && __S_IFSOCK */
#define S_ISUID __S_ISUID /* Set user ID on execution. */
#define S_ISGID __S_ISGID /* Set group ID on execution. */
#if defined(__USE_MISC) || defined(__USE_XOPEN)
#define S_ISVTX __S_ISVTX
#endif /* __USE_MISC || __USE_XOPEN */
#define S_IRUSR  __S_IREAD  /* Read by owner. */
#define S_IWUSR  __S_IWRITE /* Write by owner. */
#define S_IXUSR  __S_IEXEC  /* Execute by owner. */
#define S_IRWXU (__S_IREAD|__S_IWRITE|__S_IEXEC)
#define S_IRGRP (S_IRUSR >> 3) /* Read by group. */
#define S_IWGRP (S_IWUSR >> 3) /* Write by group. */
#define S_IXGRP (S_IXUSR >> 3) /* Execute by group. */
#define S_IRWXG (S_IRWXU >> 3)
#define S_IROTH (S_IRGRP >> 3) /* Read by others. */
#define S_IWOTH (S_IWGRP >> 3) /* Write by others. */
#define S_IXOTH (S_IXGRP >> 3) /* Execute by others. */
#define S_IRWXO (S_IRWXG >> 3)
#endif /* !S_IFMT && (__USE_XOPEN || __USE_XOPEN2K8) */


#ifdef __USE_MISC
#ifndef R_OK
#define R_OK 4 /* Test for read permission. */
#define W_OK 2 /* Test for write permission. */
#define X_OK 1 /* Test for execute permission. */
#define F_OK 0 /* Test for existence. */
#endif /* !R_OK */
#endif /* __USE_MISC */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#ifndef SEEK_SET
#define SEEK_SET __SEEK_SET /* Seek from beginning of file. */
#define SEEK_CUR __SEEK_CUR /* Seek from current position. */
#define SEEK_END __SEEK_END /* Seek from end of file. */
#ifdef __USE_GNU
#ifdef __SEEK_DATA
#define SEEK_DATA __SEEK_DATA /* Seek to next data. */
#endif /* __SEEK_DATA */
#ifdef __SEEK_HOLE
#define SEEK_HOLE __SEEK_HOLE /* Seek to next hole. */
#endif /* __SEEK_HOLE */
#endif /* __USE_GNU */
#endif /* !SEEK_SET */
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */


#ifdef __CC__

#ifdef __USE_GNU
#ifdef __CRT_HAVE_readahead
__CDECLARE(,__SSIZE_TYPE__,__NOTHROW_NCX,readahead,(__fd_t __fd, __off64_t __offset, __SIZE_TYPE__ __count),(__fd,__offset,__count))
#else /* __CRT_HAVE_readahead */
#include <local/fcntl/readahead.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(readahead, __FORCELOCAL __SSIZE_TYPE__ __NOTHROW_NCX(__LIBCCALL readahead)(__fd_t __fd, __off64_t __offset, __SIZE_TYPE__ __count) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(readahead))(__fd, __offset, __count); })
#endif /* !__CRT_HAVE_readahead */
#ifdef __CRT_HAVE_sync_file_range
__CDECLARE(,int,__NOTHROW_NCX,sync_file_range,(__fd_t __fd, __off64_t __offset, __off64_t __count, unsigned int __flags),(__fd,__offset,__count,__flags))
#else /* __CRT_HAVE_sync_file_range */
#include <local/fcntl/sync_file_range.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(sync_file_range, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL sync_file_range)(__fd_t __fd, __off64_t __offset, __off64_t __count, unsigned int __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(sync_file_range))(__fd, __offset, __count, __flags); })
#endif /* !__CRT_HAVE_sync_file_range */
struct iovec;
#ifdef __CRT_HAVE_vmsplice
__CDECLARE(,__SSIZE_TYPE__,__NOTHROW_RPC,vmsplice,(__fd_t __fdout, struct iovec const *__iov, __SIZE_TYPE__ __count, unsigned int __flags),(__fdout,__iov,__count,__flags))
#endif /* __CRT_HAVE_vmsplice */
#ifdef __CRT_HAVE_splice
__CDECLARE(,__SSIZE_TYPE__,__NOTHROW_RPC,splice,(__fd_t __fdin, __off64_t *__offin, __fd_t __fdout, __off64_t *__offout, __SIZE_TYPE__ __length, unsigned int __flags),(__fdin,__offin,__fdout,__offout,__length,__flags))
#endif /* __CRT_HAVE_splice */
#ifdef __CRT_HAVE_tee
__CDECLARE(,__SSIZE_TYPE__,__NOTHROW_RPC,tee,(__fd_t __fdin, __fd_t __fdout, __SIZE_TYPE__ __length, unsigned int __flags),(__fdin,__fdout,__length,__flags))
#endif /* __CRT_HAVE_tee */
#ifdef __CRT_HAVE_name_to_handle_at
__CDECLARE(,int,__NOTHROW_RPC,name_to_handle_at,(__fd_t __dirfd, char const *__name, struct file_handle *__handle, int *__mnt_id, int __flags),(__dirfd,__name,__handle,__mnt_id,__flags))
#endif /* __CRT_HAVE_name_to_handle_at */
#ifdef __CRT_HAVE_open_by_handle_at
__CDECLARE(,__fd_t,__NOTHROW_RPC,open_by_handle_at,(__fd_t __mountdirfd, struct file_handle *__handle, int __flags),(__mountdirfd,__handle,__flags))
#endif /* __CRT_HAVE_open_by_handle_at */
#if defined(__CRT_HAVE_fallocate64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(,int,__NOTHROW_NCX,fallocate,(__fd_t __fd, int __mode, __FS_TYPE(off) __offset, __FS_TYPE(off) __length),fallocate64,(__fd,__mode,__offset,__length))
#elif defined(__CRT_HAVE_fallocate) && !defined(__USE_FILE_OFFSET64)
__CDECLARE(,int,__NOTHROW_NCX,fallocate,(__fd_t __fd, int __mode, __FS_TYPE(off) __offset, __FS_TYPE(off) __length),(__fd,__mode,__offset,__length))
#else /* ... */
#include <local/fcntl/fallocate.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fallocate, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL fallocate)(__fd_t __fd, int __mode, __FS_TYPE(off) __offset, __FS_TYPE(off) __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fallocate))(__fd, __mode, __offset, __length); })
#endif /* !... */
#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_fallocate64
__CDECLARE(,int,__NOTHROW_NCX,fallocate64,(__fd_t __fd, int __mode, __off64_t __offset, __off64_t __length),(__fd,__mode,__offset,__length))
#elif defined(__CRT_HAVE_fallocate) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,int,__NOTHROW_NCX,fallocate64,(__fd_t __fd, int __mode, __off64_t __offset, __off64_t __length),fallocate,(__fd,__mode,__offset,__length))
#else /* ... */
#include <local/fcntl/fallocate64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(fallocate64, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL fallocate64)(__fd_t __fd, int __mode, __off64_t __offset, __off64_t __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fallocate64))(__fd, __mode, __offset, __length); })
#endif /* !... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_GNU */
#ifndef __fcntl_defined
#define __fcntl_defined 1
#ifdef __CRT_HAVE_fcntl
__LIBC __STDC_INT_AS_SSIZE_T __NOTHROW_NCX(__VLIBCCALL fcntl)(__fd_t __fd, int __cmd, ...) __CASMNAME_SAME("fcntl");
#elif defined(__CRT_HAVE___fcntl)
__CVREDIRECT(,__STDC_INT_AS_SSIZE_T,__NOTHROW_NCX,fcntl,(__fd_t __fd, int __cmd),__fcntl,(__fd,__cmd),__cmd,1,(void *))
#else /* ... */
#undef __fcntl_defined
#endif /* !... */
#endif /* !__fcntl_defined */
#ifndef __open_defined
#define __open_defined 1
#if defined(__CRT_HAVE_open64) && defined(__USE_FILE_OFFSET64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,open,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) && !defined(__USE_FILE_OFFSET64)
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t __NOTHROW_RPC(__VLIBCCALL open)(char const *__filename, __oflag_t __oflags, ...) __CASMNAME_SAME("open");
#elif defined(__CRT_HAVE__open) && !defined(__USE_FILE_OFFSET64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,open,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open) && !defined(__USE_FILE_OFFSET64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,open,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
#include <local/fcntl/open.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(open)
#else /* __cplusplus */
#define open (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(open))
#endif /* !__cplusplus */
#else /* ... */
#undef __open_defined
#endif /* !... */
#endif /* !__open_defined */
#ifndef __creat_defined
#define __creat_defined 1
#if defined(__CRT_HAVE_creat64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,creat,(char const *__filename, __mode_t __mode),creat64,(__filename,__mode))
#elif defined(__CRT_HAVE_creat) && !defined(__USE_FILE_OFFSET64)
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,creat,(char const *__filename, __mode_t __mode),(__filename,__mode))
#elif defined(__CRT_HAVE__creat)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,creat,(char const *__filename, __mode_t __mode),_creat,(__filename,__mode))
#elif (defined(__CRT_HAVE_creat64) || (defined(__CRT_HAVE_creat) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)) || (defined(__CRT_HAVE__creat) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)) || defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open)) && (defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || (defined(__CRT_AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat))))
#include <local/fcntl/creat.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(creat, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t __NOTHROW_RPC(__LIBCCALL creat)(char const *__filename, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(creat))(__filename, __mode); })
#else /* ... */
#undef __creat_defined
#endif /* !... */
#endif /* !__creat_defined */

#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_open64
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t __NOTHROW_RPC(__VLIBCCALL open64)(char const *__filename, __oflag_t __oflags, ...) __CASMNAME_SAME("open64");
#elif defined(__CRT_HAVE___open64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,open64,(char const *__filename, __oflag_t __oflags),__open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,open64,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,open64,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,open64,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open)
#include <local/fcntl/open64.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(open64)
#else /* __cplusplus */
#define open64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(open64))
#endif /* !__cplusplus */
#endif /* ... */
#ifndef __creat64_defined
#define __creat64_defined 1
#ifdef __CRT_HAVE_creat64
__CDECLARE(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,creat64,(char const *__filename, __mode_t __mode),(__filename,__mode))
#elif defined(__CRT_HAVE_creat) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,creat64,(char const *__filename, __mode_t __mode),creat,(__filename,__mode))
#elif defined(__CRT_HAVE_creat) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,creat64,(char const *__filename, __mode_t __mode),creat,(__filename,__mode))
#elif defined(__CRT_HAVE__creat) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((1)),__fd_t,__NOTHROW_RPC,creat64,(char const *__filename, __mode_t __mode),_creat,(__filename,__mode))
#elif defined(__CRT_HAVE_open64) || defined(__CRT_HAVE___open64) || defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open)
#include <local/fcntl/creat64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(creat64, __FORCELOCAL __ATTR_WUNUSED __ATTR_NONNULL((1)) __fd_t __NOTHROW_RPC(__LIBCCALL creat64)(char const *__filename, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(creat64))(__filename, __mode); })
#else /* ... */
#undef __creat64_defined
#endif /* !... */
#endif /* !__creat64_defined */
#endif /* __USE_LARGEFILE64 */

#ifdef __USE_ATFILE
#ifndef __openat_defined
#define __openat_defined 1
#if defined(__CRT_HAVE_openat64) && defined(__USE_FILE_OFFSET64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__fd_t,__NOTHROW_RPC,openat,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),openat64,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_openat) && !defined(__USE_FILE_OFFSET64)
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((2)) __fd_t __NOTHROW_RPC(__VLIBCCALL openat)(__fd_t __dirfd, char const *__filename, __oflag_t __oflags, ...) __CASMNAME_SAME("openat");
#elif defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)
#include <local/fcntl/openat.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(openat)
#else /* __cplusplus */
#define openat (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(openat))
#endif /* !__cplusplus */
#else /* ... */
#undef __openat_defined
#endif /* !... */
#endif /* !__openat_defined */
#ifdef __USE_LARGEFILE64
#ifndef __openat64_defined
#define __openat64_defined 1
#ifdef __CRT_HAVE_openat64
__LIBC __ATTR_WUNUSED __ATTR_NONNULL((2)) __fd_t __NOTHROW_RPC(__VLIBCCALL openat64)(__fd_t __dirfd, char const *__filename, __oflag_t __oflags, ...) __CASMNAME_SAME("openat64");
#elif defined(__CRT_HAVE_openat) && (!defined(__O_LARGEFILE) || (__O_LARGEFILE+0) == 0)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_NONNULL((2)),__fd_t,__NOTHROW_RPC,openat64,(__fd_t __dirfd, char const *__filename, __oflag_t __oflags),openat,(__dirfd,__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_openat)
#include <local/fcntl/openat64.h>
#ifdef __cplusplus
__NAMESPACE_LOCAL_USING(openat64)
#else /* __cplusplus */
#define openat64 (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(openat64))
#endif /* !__cplusplus */
#else /* ... */
#undef __openat64_defined
#endif /* !... */
#endif /* !__openat64_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_ATFILE */

#ifdef __USE_XOPEN2K
#if defined(__CRT_HAVE_posix_fadvise64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(,int,__NOTHROW_NCX,posix_fadvise,(__fd_t __fd, __FS_TYPE(off) __offset, __FS_TYPE(off) __length, int __advise),posix_fadvise64,(__fd,__offset,__length,__advise))
#elif defined(__CRT_HAVE_posix_fadvise) && !defined(__USE_FILE_OFFSET64)
__CDECLARE(,int,__NOTHROW_NCX,posix_fadvise,(__fd_t __fd, __FS_TYPE(off) __offset, __FS_TYPE(off) __length, int __advise),(__fd,__offset,__length,__advise))
#else /* ... */
#include <local/fcntl/posix_fadvise.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_fadvise, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL posix_fadvise)(__fd_t __fd, __FS_TYPE(off) __offset, __FS_TYPE(off) __length, int __advise) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_fadvise))(__fd, __offset, __length, __advise); })
#endif /* !... */
#if defined(__CRT_HAVE_posix_fallocate64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(,int,__NOTHROW_NCX,posix_fallocate,(__fd_t __fd, __FS_TYPE(off) __offset, __FS_TYPE(off) __length),posix_fallocate64,(__fd,__offset,__length))
#elif defined(__CRT_HAVE_posix_fallocate) && !defined(__USE_FILE_OFFSET64)
__CDECLARE(,int,__NOTHROW_NCX,posix_fallocate,(__fd_t __fd, __FS_TYPE(off) __offset, __FS_TYPE(off) __length),(__fd,__offset,__length))
#else /* ... */
#include <local/fcntl/posix_fallocate.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_fallocate, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL posix_fallocate)(__fd_t __fd, __FS_TYPE(off) __offset, __FS_TYPE(off) __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_fallocate))(__fd, __offset, __length); })
#endif /* !... */
#ifdef __USE_LARGEFILE64
#ifdef __CRT_HAVE_posix_fadvise64
__CDECLARE(,int,__NOTHROW_NCX,posix_fadvise64,(__fd_t __fd, __off64_t __offset, __off64_t __length, int __advise),(__fd,__offset,__length,__advise))
#elif defined(__CRT_HAVE_posix_fadvise) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,int,__NOTHROW_NCX,posix_fadvise64,(__fd_t __fd, __off64_t __offset, __off64_t __length, int __advise),posix_fadvise,(__fd,__offset,__length,__advise))
#else /* ... */
#include <local/fcntl/posix_fadvise64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_fadvise64, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL posix_fadvise64)(__fd_t __fd, __off64_t __offset, __off64_t __length, int __advise) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_fadvise64))(__fd, __offset, __length, __advise); })
#endif /* !... */
#ifdef __CRT_HAVE_posix_fallocate64
__CDECLARE(,int,__NOTHROW_NCX,posix_fallocate64,(__fd_t __fd, __off64_t __offset, __off64_t __length),(__fd,__offset,__length))
#elif defined(__CRT_HAVE_posix_fallocate) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,int,__NOTHROW_NCX,posix_fallocate64,(__fd_t __fd, __off64_t __offset, __off64_t __length),posix_fallocate,(__fd,__offset,__length))
#else /* ... */
#include <local/fcntl/posix_fallocate64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(posix_fallocate64, __FORCELOCAL int __NOTHROW_NCX(__LIBCCALL posix_fallocate64)(__fd_t __fd, __off64_t __offset, __off64_t __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(posix_fallocate64))(__fd, __offset, __length); })
#endif /* !... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN2K */

#if defined(__USE_MISC) || (defined(__USE_XOPEN_EXTENDED) && !defined(__USE_POSIX))
#ifndef F_LOCK
#define F_ULOCK 0 /* Unlock a previously locked region. */
#define F_LOCK  1 /* Lock a region for exclusive use. */
#define F_TLOCK 2 /* Test and lock a region for exclusive use. */
#define F_TEST  3 /* Test a region for other processes locks. */
#endif /* !F_LOCK */
#ifndef __lockf_defined
#define __lockf_defined 1
#if defined(__CRT_HAVE_lockf64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(,int,__NOTHROW_RPC,lockf,(__fd_t __fd, int __cmd, __FS_TYPE(off) __length),lockf64,(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf) && !defined(__USE_FILE_OFFSET64)
__CDECLARE(,int,__NOTHROW_RPC,lockf,(__fd_t __fd, int __cmd, __FS_TYPE(off) __length),(__fd,__cmd,__length))
#elif defined(__CRT_HAVE__locking) && !defined(__USE_FILE_OFFSET64)
__CREDIRECT(,int,__NOTHROW_RPC,lockf,(__fd_t __fd, int __cmd, __FS_TYPE(off) __length),_locking,(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf64) || defined(__CRT_HAVE_lockf) || defined(__CRT_HAVE_locking) || defined(__CRT_HAVE__locking)
#include <local/fcntl/lockf.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(lockf, __FORCELOCAL int __NOTHROW_RPC(__LIBCCALL lockf)(__fd_t __fd, int __cmd, __FS_TYPE(off) __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lockf))(__fd, __cmd, __length); })
#else /* ... */
#undef __lockf_defined
#endif /* !... */
#endif /* !__lockf_defined */
#ifdef __USE_LARGEFILE64
#ifndef __lockf64_defined
#define __lockf64_defined 1
#ifdef __CRT_HAVE_lockf64
__CDECLARE(,int,__NOTHROW_RPC,lockf64,(__fd_t __fd, int __cmd, __off64_t __length),(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf) && (__SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(,int,__NOTHROW_RPC,lockf64,(__fd_t __fd, int __cmd, __off64_t __length),lockf,(__fd,__cmd,__length))
#elif defined(__CRT_HAVE_lockf) || defined(__CRT_HAVE_locking) || defined(__CRT_HAVE__locking)
#include <local/fcntl/lockf64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(lockf64, __FORCELOCAL int __NOTHROW_RPC(__LIBCCALL lockf64)(__fd_t __fd, int __cmd, __off64_t __length) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lockf64))(__fd, __cmd, __length); })
#else /* ... */
#undef __lockf64_defined
#endif /* !... */
#endif /* !__lockf64_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_MISC || (__USE_XOPEN_EXTENDED && !__USE_POSIX) */

#endif /* __CC__ */

__SYSDECL_END

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_FCNTL_H)
#include <parts/uchar/fcntl.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_FCNTL_H */
#endif /* __USE_UTF */

#endif /* !_FCNTL_H */
