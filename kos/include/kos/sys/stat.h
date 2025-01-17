/* HASH CRC-32:0x88d87897 */
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
#ifndef _KOS_SYS_STAT_H
#define _KOS_SYS_STAT_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>
#include <sys/stat.h>
#include <kos/anno.h>
#include <bits/os/stat.h>

#ifdef __CC__
__SYSDECL_BEGIN

#if defined(__CRT_HAVE_KStat) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
/* >> stat(2), stat64(2) */
__CREDIRECT_VOID(__ATTR_IN(1) __ATTR_OUT(2),__THROWING(...),Stat,(char const *__restrict __filename, struct stat *__restrict __buf),KStat,(__filename,__buf))
#elif defined(__CRT_HAVE_KStat64) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
/* >> stat(2), stat64(2) */
__CREDIRECT_VOID(__ATTR_IN(1) __ATTR_OUT(2),__THROWING(...),Stat,(char const *__restrict __filename, struct stat *__restrict __buf),KStat64,(__filename,__buf))
#endif /* ... */

#if defined(__CRT_HAVE_KFStat) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
/* >> fstat(2), fstat64(2) */
__CREDIRECT_VOID(__ATTR_FDARG(1) __ATTR_OUT(2),__THROWING(...),FStat,(__fd_t __fd, struct stat *__restrict __buf),KFStat,(__fd,__buf))
#elif defined(__CRT_HAVE_KFStat64) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
/* >> fstat(2), fstat64(2) */
__CREDIRECT_VOID(__ATTR_FDARG(1) __ATTR_OUT(2),__THROWING(...),FStat,(__fd_t __fd, struct stat *__restrict __buf),KFStat64,(__fd,__buf))
#endif /* ... */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#if defined(__CRT_HAVE_KLStat) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
/* >> lstat(2), lstat64(2) */
__CREDIRECT_VOID(__ATTR_IN(1) __ATTR_OUT(2),__THROWING(...),LStat,(char const *__restrict __filename, struct stat *__restrict __buf),KLStat,(__filename,__buf))
#elif defined(__CRT_HAVE_KLStat64) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
/* >> lstat(2), lstat64(2) */
__CREDIRECT_VOID(__ATTR_IN(1) __ATTR_OUT(2),__THROWING(...),LStat,(char const *__restrict __filename, struct stat *__restrict __buf),KLStat64,(__filename,__buf))
#endif /* ... */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_KFStatAt) && defined(__STAT32_MATCHES_STAT64)
/* >> stat(2), stat64(2) */
__CREDIRECT_VOID(__ATTR_IN(1) __ATTR_OUT(2),__THROWING(...),Stat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),KFStatAt,(__filename,__buf))
#elif defined(__CRT_HAVE_KStat64)
/* >> stat(2), stat64(2) */
__CREDIRECT_VOID(__ATTR_IN(1) __ATTR_OUT(2),__THROWING(...),Stat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),KStat64,(__filename,__buf))
#endif /* ... */
#if defined(__CRT_HAVE_KFStatAt) && defined(__STAT32_MATCHES_STAT64)
/* >> fstat(2), fstat64(2) */
__CREDIRECT_VOID(__ATTR_FDARG(1) __ATTR_OUT(2),__THROWING(...),FStat64,(__fd_t __fd, struct stat64 *__restrict __buf),KFStatAt,(__fd,__buf))
#elif defined(__CRT_HAVE_KFStat64)
/* >> fstat(2), fstat64(2) */
__CREDIRECT_VOID(__ATTR_FDARG(1) __ATTR_OUT(2),__THROWING(...),FStat64,(__fd_t __fd, struct stat64 *__restrict __buf),KFStat64,(__fd,__buf))
#endif /* ... */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#if defined(__CRT_HAVE_KFStatAt) && defined(__STAT32_MATCHES_STAT64)
/* >> lstat(2), lstat64(2) */
__CREDIRECT_VOID(__ATTR_IN(1) __ATTR_OUT(2),__THROWING(...),LStat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),KFStatAt,(__filename,__buf))
#elif defined(__CRT_HAVE_KLStat64)
/* >> lstat(2), lstat64(2) */
__CREDIRECT_VOID(__ATTR_IN(1) __ATTR_OUT(2),__THROWING(...),LStat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),KLStat64,(__filename,__buf))
#endif /* ... */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */
#endif /* __USE_LARGEFILE64 */



#ifdef __USE_ATFILE
#if defined(__CRT_HAVE_KFStatAt) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
/* >> fstatat(2), fstatat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CREDIRECT_VOID(__ATTR_IN(2) __ATTR_OUT(3),__THROWING(...),FStatAt,(__fd_t __dirfd, char const *__restrict __filename, struct stat *__restrict __buf, __atflag_t __flags),KFStatAt,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_KFStatAt64) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
/* >> fstatat(2), fstatat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CREDIRECT_VOID(__ATTR_IN(2) __ATTR_OUT(3),__THROWING(...),FStatAt,(__fd_t __dirfd, char const *__restrict __filename, struct stat *__restrict __buf, __atflag_t __flags),KFStatAt64,(__dirfd,__filename,__buf,__flags))
#endif /* ... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_KFStatAt) && defined(__STAT32_MATCHES_STAT64)
/* >> fstatat(2), fstatat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CREDIRECT_VOID(__ATTR_IN(2) __ATTR_OUT(3),__THROWING(...),FStatAt64,(__fd_t __dirfd, char const *__restrict __filename, struct stat64 *__restrict __buf, __atflag_t __flags),KFStatAt,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_KFStatAt64)
/* >> fstatat(2), fstatat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CREDIRECT_VOID(__ATTR_IN(2) __ATTR_OUT(3),__THROWING(...),FStatAt64,(__fd_t __dirfd, char const *__restrict __filename, struct stat64 *__restrict __buf, __atflag_t __flags),KFStatAt64,(__dirfd,__filename,__buf,__flags))
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_ATFILE */
/* >> mkdir(2) */
__CDECLARE_VOID_OPT(__ATTR_IN(1),__THROWING(...),MkDir,(char const *__pathname, __mode_t __mode),(__pathname,__mode))
/* >> chmod(2) */
__CDECLARE_VOID_OPT(__ATTR_IN(1),__THROWING(...),ChMod,(char const *__filename, __mode_t __mode),(__filename,__mode))

#ifdef __USE_MISC
/* >> lchmod(2) */
__CDECLARE_VOID_OPT(__ATTR_IN(1),__THROWING(...),LChMod,(char const *__filename, __mode_t __mode),(__filename,__mode))
#endif /* __USE_MISC */

#if defined(__USE_KOS) && defined(__USE_ATFILE)
/* >> fmkdirat(2)
 * @param flags: Set of `0 | AT_DOSPATH' */
__CDECLARE_VOID_OPT(__ATTR_IN(2),__THROWING(...),FMkDirAt,(__fd_t __dirfd, char const *__pathname, __mode_t __mode, __atflag_t __flags),(__dirfd,__pathname,__mode,__flags))
/* >> fmknodat(2)
 * @param flags: Set of `0 | AT_DOSPATH' */
__CDECLARE_VOID_OPT(__ATTR_IN(2),__THROWING(...),FMkNodAt,(__fd_t __dirfd, char const *__nodename, __mode_t __mode, __dev_t __dev, __atflag_t __flags),(__dirfd,__nodename,__mode,__dev,__flags))
#endif /* __USE_KOS && __USE_ATFILE */
/* >> mkfifo(2) */
__CDECLARE_VOID_OPT(__ATTR_IN(1),__THROWING(...),MkFiFo,(char const *__fifoname, __mode_t __mode),(__fifoname,__mode))

#ifdef __USE_ATFILE
/* >> fchmodat(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CDECLARE_VOID_OPT(__ATTR_IN(2),__THROWING(...),FChModAt,(__fd_t __dirfd, char const *__filename, __mode_t __mode, __atflag_t __flags),(__dirfd,__filename,__mode,__flags))
/* >> mkdirat(2) */
__CDECLARE_VOID_OPT(__ATTR_IN(2),__THROWING(...),MkDirAt,(__fd_t __dirfd, char const *__pathname, __mode_t __mode),(__dirfd,__pathname,__mode))
/* >> mkfifoat(2) */
__CDECLARE_VOID_OPT(__ATTR_IN(2),__THROWING(...),MkFiFoAt,(__fd_t __dirfd, char const *__fifoname, __mode_t __mode),(__dirfd,__fifoname,__mode))
#endif /* __USE_ATFILE */

#ifdef __USE_POSIX
/* >> fchmod(2) */
__CDECLARE_VOID_OPT(__ATTR_FDARG(1),__THROWING(...),FChMod,(__fd_t __fd, __mode_t __mode),(__fd,__mode))
#endif /* __USE_POSIX */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
/* >> mknod(2) */
__CDECLARE_VOID_OPT(__ATTR_IN(1),__THROWING(...),MkNod,(char const *__nodename, __mode_t __mode, __dev_t __dev),(__nodename,__mode,__dev))
#ifdef __USE_ATFILE
/* >> mknodat(2) */
__CDECLARE_VOID_OPT(__ATTR_IN(2),__THROWING(...),MkNodAt,(__fd_t __dirfd, char const *__nodename, __mode_t __mode, __dev_t __dev),(__dirfd,__nodename,__mode,__dev))
#endif /* __USE_ATFILE */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

#ifdef __USE_ATFILE
#include <bits/types.h>
#if defined(__CRT_HAVE_UTimensAt) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
__CDECLARE_VOID(__ATTR_IN(2) __ATTR_IN_OPT(3),__THROWING(...),UTimensAt,(__fd_t __dirfd, char const *__filename, struct timespec const __times[2 /*or:3*/], __atflag_t __flags),(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_UTimensAt64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
__CREDIRECT_VOID(__ATTR_IN(2) __ATTR_IN_OPT(3),__THROWING(...),UTimensAt,(__fd_t __dirfd, char const *__filename, struct timespec const __times[2 /*or:3*/], __atflag_t __flags),UTimensAt64,(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_UTimensAt64) || defined(__CRT_HAVE_UTimensAt)
#include <libc/local/kos.sys.stat/UTimensAt.h>
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(UTimensAt, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_IN_OPT(3) void (__LIBCCALL UTimensAt)(__fd_t __dirfd, char const *__filename, struct timespec const __times[2 /*or:3*/], __atflag_t __flags) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(UTimensAt))(__dirfd, __filename, __times, __flags); })
#endif /* ... */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_UTimensAt) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
__CREDIRECT_VOID(__ATTR_IN(2) __ATTR_IN_OPT(3),__THROWING(...),UTimensAt64,(__fd_t __dirfd, char const *__filename, struct timespec64 const __times[2 /*or:3*/], __atflag_t __flags),UTimensAt,(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_UTimensAt64)
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
__CDECLARE_VOID(__ATTR_IN(2) __ATTR_IN_OPT(3),__THROWING(...),UTimensAt64,(__fd_t __dirfd, char const *__filename, struct timespec64 const __times[2 /*or:3*/], __atflag_t __flags),(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_UTimensAt)
#include <libc/local/kos.sys.stat/UTimensAt64.h>
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(UTimensAt64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_IN_OPT(3) void (__LIBCCALL UTimensAt64)(__fd_t __dirfd, char const *__filename, struct timespec64 const __times[2 /*or:3*/], __atflag_t __flags) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(UTimensAt64))(__dirfd, __filename, __times, __flags); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_ATFILE */

#ifdef __USE_XOPEN2K8
#if defined(__CRT_HAVE_FUTimens) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> futimens(2), futimens64(2) */
__CDECLARE_VOID(__ATTR_FDARG(1) __ATTR_IN_OPT(2),__THROWING(...),FUTimens,(__fd_t __fd, struct timespec const __times[2 /*or:3*/]),(__fd,__times))
#elif defined(__CRT_HAVE_FUTimens64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> futimens(2), futimens64(2) */
__CREDIRECT_VOID(__ATTR_FDARG(1) __ATTR_IN_OPT(2),__THROWING(...),FUTimens,(__fd_t __fd, struct timespec const __times[2 /*or:3*/]),FUTimens64,(__fd,__times))
#elif defined(__CRT_HAVE_FUTimens64) || defined(__CRT_HAVE_FUTimens)
#include <libc/local/kos.sys.stat/FUTimens.h>
/* >> futimens(2), futimens64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(FUTimens, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __ATTR_IN_OPT(2) void (__LIBCCALL FUTimens)(__fd_t __fd, struct timespec const __times[2 /*or:3*/]) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(FUTimens))(__fd, __times); })
#endif /* ... */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_FUTimens) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> futimens(2), futimens64(2) */
__CREDIRECT_VOID(__ATTR_FDARG(1) __ATTR_IN_OPT(2),__THROWING(...),FUTimens64,(__fd_t __fd, struct timespec64 const __times[2 /*or:3*/]),FUTimens,(__fd,__times))
#elif defined(__CRT_HAVE_FUTimens64)
/* >> futimens(2), futimens64(2) */
__CDECLARE_VOID(__ATTR_FDARG(1) __ATTR_IN_OPT(2),__THROWING(...),FUTimens64,(__fd_t __fd, struct timespec64 const __times[2 /*or:3*/]),(__fd,__times))
#elif defined(__CRT_HAVE_FUTimens)
#include <libc/local/kos.sys.stat/FUTimens64.h>
/* >> futimens(2), futimens64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(FUTimens64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __ATTR_IN_OPT(2) void (__LIBCCALL FUTimens64)(__fd_t __fd, struct timespec64 const __times[2 /*or:3*/]) __THROWS(...) { (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(FUTimens64))(__fd, __times); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_XOPEN2K8 */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_KOS_SYS_STAT_H */
