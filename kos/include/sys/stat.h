/* HASH CRC-32:0x654fe262 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/stat.h) */
/* (#) Portability: DJGPP         (/include/sys/stat.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/stat.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/stat.h) */
/* (#) Portability: FreeBSD       (/sys/sys/stat.h) */
/* (#) Portability: GNU C Library (/io/sys/stat.h) */
/* (#) Portability: MSVC          (/include/sys/stat.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/sys/stat.h) */
/* (#) Portability: NetBSD        (/sys/sys/stat.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/stat.h) */
/* (#) Portability: OpenBSD       (/sys/sys/stat.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/stat.h) */
/* (#) Portability: Windows Kits  (/ucrt/sys/stat.h) */
/* (#) Portability: diet libc     (/include/sys/stat.h) */
/* (#) Portability: libc4/5       (/include/sys/stat.h) */
/* (#) Portability: mintlib       (/include/sys/stat.h) */
/* (#) Portability: musl libc     (/include/sys/stat.h) */
/* (#) Portability: uClibc        (/include/sys/stat.h) */
#ifndef _SYS_STAT_H
#define _SYS_STAT_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/os/stat.h>
#include <bits/os/stat.h>     /* `struct stat', `struct stat64' */
#include <bits/os/timespec.h> /* `struct timespec' */
#include <bits/types.h>

#ifdef __USE_DOS
#ifdef _BITS_OS_DOS_STAT_H
#ifdef __CC__
__DECL_BEGIN
struct __dos_stat32;
struct __dos_stat32i64;
struct __dos_stat64i32;
struct __dos_stat64;
__DECL_END
#endif /* __CC__ */
#else /* _BITS_OS_DOS_STAT_H */
#define __DEFINE_DOS_STAT_STRUCTURES
#include <bits/os/dos/stat.h>
#endif /* !_BITS_OS_DOS_STAT_H */
#endif /* __USE_DOS */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#include <time.h>
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#ifdef __USE_ATFILE
#if !defined(UTIME_NOW) && defined(__UTIME_NOW)
#define UTIME_NOW  __UTIME_NOW  /* for utimensat(): Set `times[0|1].tv_nsec' to this to use the current time instead. */
#endif /* !UTIME_NOW && __UTIME_NOW */
#if !defined(UTIME_OMIT) && defined(__UTIME_OMIT)
#define UTIME_OMIT __UTIME_OMIT /* for utimensat(): Set `times[0|1].tv_nsec' to this to not modify that timestamp. */
#endif /* !UTIME_OMIT && __UTIME_OMIT */
#endif /* __USE_ATFILE */

#ifdef __CC__
__SYSDECL_BEGIN

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __dev_t_defined
#define __dev_t_defined
typedef __dev_t dev_t;
#endif /* __dev_t_defined */

#ifndef __gid_t_defined
#define __gid_t_defined
typedef __gid_t gid_t;
#endif /* __gid_t_defined */

#ifndef __ino_t_defined
#define __ino_t_defined
typedef __ino_t ino_t;  /* INode number */
#endif /* __ino_t_defined */

#ifndef __mode_t_defined
#define __mode_t_defined
typedef __mode_t mode_t; /* INode type (Set of `S_*' from `<fcntl.h>' or `<sys/stat.h>') */
#endif /* __mode_t_defined */

#ifndef __nlink_t_defined
#define __nlink_t_defined
typedef __nlink_t nlink_t;
#endif /* __nlink_t_defined */

#ifndef __off_t_defined
#define __off_t_defined
typedef __off_t off_t;
#endif /* __off_t_defined */

#ifndef __uid_t_defined
#define __uid_t_defined
typedef __uid_t uid_t;
#endif /* __uid_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#ifdef __USE_UNIX98
#ifndef __blkcnt_t_defined
#define __blkcnt_t_defined
typedef __blkcnt_t   blkcnt_t;
#endif /* __blkcnt_t_defined */

#ifndef __blksize_t_defined
#define __blksize_t_defined
typedef __blksize_t blksize_t;
#endif /* __blksize_t_defined */
#endif /* __USE_UNIX98 */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#if !defined(S_IFMT) && defined(__S_IFMT)
#define S_IFMT  __S_IFMT /* These bits determine file type. */
#endif /* !S_IFMT && __S_IFMT */
#if !defined(S_IFDIR) && defined(__S_IFDIR)
#define S_IFDIR __S_IFDIR /* Directory. */
#endif /* !S_IFDIR && __S_IFDIR */
#if !defined(S_IFCHR) && defined(__S_IFCHR)
#define S_IFCHR __S_IFCHR /* Character device. */
#endif /* !S_IFCHR && __S_IFCHR */
#if !defined(S_IFBLK) && defined(__S_IFBLK)
#define S_IFBLK __S_IFBLK /* Block device. */
#endif /* !S_IFBLK && __S_IFBLK */
#if !defined(S_IFREG) && defined(__S_IFREG)
#define S_IFREG __S_IFREG /* Regular file. */
#endif /* !S_IFREG && __S_IFREG */
#if !defined(S_IFIFO) && defined(__S_IFIFO)
#define S_IFIFO __S_IFIFO /* FIFO. */
#endif /* !S_IFIFO && __S_IFIFO */
#if !defined(S_IFLNK) && defined(__S_IFLNK)
#define S_IFLNK __S_IFLNK /* Symbolic link. */
#endif /* !S_IFLNK && __S_IFLNK */
#if ((defined(__USE_MISC) || defined(__USE_UNIX98)) && \
     !defined(S_IFSOCK) && defined(__S_IFSOCK))
#define S_IFSOCK __S_IFSOCK /* Socket. */
#endif /* (__USE_MISC || __USE_UNIX98) && !S_IFSOCK && __S_IFSOCK */
#endif /* __USE_MISC || __USE_XOPEN */

#if !defined(__S_ISTYPE) && defined(__S_IFMT)
#define __S_ISTYPE(mode, mask) (((mode) & __S_IFMT) == (mask))
#endif /* !__S_ISTYPE && __S_IFMT */

/* File mode test macros. */
#if !defined(S_ISDIR) && defined(__S_ISDIR)
#define S_ISDIR(mode) __S_ISDIR(mode) /* Directory. */
#endif /* !S_ISDIR && __S_ISDIR */
#if !defined(S_ISCHR) && defined(__S_ISCHR)
#define S_ISCHR(mode) __S_ISCHR(mode) /* Character device. */
#endif /* !S_ISCHR && __S_ISCHR */
#if !defined(S_ISBLK) && defined(__S_ISBLK)
#define S_ISBLK(mode) __S_ISBLK(mode) /* Block device. */
#endif /* !S_ISBLK && __S_ISBLK */
#if !defined(S_ISREG) && defined(__S_ISREG)
#define S_ISREG(mode) __S_ISREG(mode) /* Regular file. */
#endif /* !S_ISREG && __S_ISREG */

#if defined(__USE_KOS) && !defined(S_ISDEV) && defined(__S_ISDEV)
#define S_ISDEV(mode) __S_ISDEV(mode) /* S_ISCHR(mode) || S_ISBLK(mode) */
#endif /* __USE_KOS && !S_ISDEV && __S_ISDEV */

#if !defined(S_ISFIFO) && defined(__S_ISFIFO)
#define S_ISFIFO(mode) __S_ISFIFO(mode) /* FIFO. */
#endif /* !S_ISFIFO && __S_ISFIFO */

#ifndef S_ISLNK
#ifdef __S_ISLNK
#define S_ISLNK(mode) __S_ISLNK(mode) /* Symbolic link. */
#elif defined(__USE_MISC)
#define S_ISLNK(mode) 0               /* Symbolic link. */
#endif /* ... */
#endif /* !S_ISLNK */

#ifndef S_ISSOCK
#if ((defined(__USE_UNIX98) || defined(__USE_XOPEN2K)) && defined(__S_ISSOCK))
#define S_ISSOCK(mode) __S_ISSOCK(mode) /* Socket. */
#elif defined(__USE_XOPEN2K)
#define S_ISSOCK(mode) 0                /* Socket. */
#endif /* ... */
#endif /* !S_ISSOCK */

#ifdef __USE_POSIX199309
#ifndef S_TYPEISMQ
#ifdef __S_TYPEISMQ
#define S_TYPEISMQ(buf) __S_TYPEISMQ(buf)
#else /* __S_TYPEISMQ */
#define S_TYPEISMQ(buf) ((buf)->st_mode, 0)
#endif /* !__S_TYPEISMQ */
#endif /* !S_TYPEISMQ */

#ifndef S_TYPEISSEM
#ifdef __S_TYPEISSEM
#define S_TYPEISSEM(buf) __S_TYPEISSEM(buf)
#else /* __S_TYPEISSEM */
#define S_TYPEISSEM(buf) ((buf)->st_mode, 0)
#endif /* !__S_TYPEISSEM */
#endif /* !S_TYPEISSEM */

#ifndef S_TYPEISSHM
#ifdef __S_TYPEISSHM
#define S_TYPEISSHM(buf) __S_TYPEISSHM(buf)
#else /* __S_TYPEISSHM */
#define S_TYPEISSHM(buf) ((buf)->st_mode, 0)
#endif /* !__S_TYPEISSHM */
#endif /* !S_TYPEISSHM */
#endif /* __USE_POSIX199309 */

#if !defined(S_ISUID) && defined(__S_ISUID)
#define S_ISUID __S_ISUID /* Set user ID on execution. */
#endif /* !S_ISUID && __S_ISUID */

#if !defined(S_ISGID) && defined(__S_ISGID)
#define S_ISGID __S_ISGID /* Set group ID on execution. */
#endif /* !S_ISGID && __S_ISGID */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#if !defined(S_ISVTX) && defined(__S_ISVTX)
#define S_ISVTX __S_ISVTX
#endif /* !S_ISVTX && __S_ISVTX */
#endif /* __USE_MISC || __USE_XOPEN */

#ifndef S_IRUSR
#define S_IRUSR 0400 /* Read by owner. */
#define S_IWUSR 0200 /* Write by owner. */
#define S_IXUSR 0100 /* Execute by owner. */
#define S_IRWXU 0700
#define S_IRGRP 0040 /* Read by group. */
#define S_IWGRP 0020 /* Write by group. */
#define S_IXGRP 0010 /* Execute by group. */
#define S_IRWXG 0070
#define S_IROTH 0004 /* Read by others. */
#define S_IWOTH 0002 /* Write by others. */
#define S_IXOTH 0001 /* Execute by others. */
#define S_IRWXO 0007
#endif /* !S_IRWXO */



#ifdef __USE_KOS
/* As also seen in the linux kernel headers. */
#ifndef S_IRWXUGO
#define S_IRWXUGO 0777
#endif /* !S_IRWXUGO */
#ifndef S_IALLUGO
#define S_IALLUGO 07777
#endif /* !S_IALLUGO */
#ifndef S_IRUGO
#define S_IRUGO 0444
#endif /* !S_IRUGO */
#ifndef S_IWUGO
#define S_IWUGO 0222
#endif /* !S_IWUGO */
#ifndef S_IXUGO
#define S_IXUGO 0111
#endif /* !S_IXUGO */
#endif /* __USE_KOS */

#ifdef __USE_MISC
#ifndef ACCESSPERMS
#define ACCESSPERMS 0777 /* S_IRWXU | S_IRWXG | S_IRWXO */
#endif /* !ACCESSPERMS */
#ifndef ALLPERMS
#define ALLPERMS 07777 /* S_ISUID | S_ISGID | S_ISVTX | S_IRWXU | S_IRWXG | S_IRWXO */
#endif /* !ALLPERMS */
#ifndef DEFFILEMODE
#define DEFFILEMODE 0666 /* S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH */
#endif /* !DEFFILEMODE */
#ifndef S_BLKSIZE
#define S_BLKSIZE 512 /* Block size for `st_blocks'. */
#endif /* !S_BLKSIZE */
#endif /* __USE_MISC */

#ifdef __USE_DOS
#ifdef __S_IFMT
#define _S_IFMT   __S_IFMT
#endif /* __S_IFMT */
#ifdef __S_IFDIR
#define _S_IFDIR  __S_IFDIR
#endif /* __S_IFDIR */
#ifdef __S_IFCHR
#define _S_IFCHR  __S_IFCHR
#endif /* __S_IFCHR */
#ifdef __S_IFIFO
#define _S_IFIFO  __S_IFIFO
#endif /* __S_IFIFO */
#ifdef __S_IFREG
#define _S_IFREG  __S_IFREG
#endif /* __S_IFREG */
#define _S_IREAD  0400
#define _S_IWRITE 0200
#define _S_IEXEC  0100
#endif /* __USE_DOS */

#undef stat
#undef fstat
#undef lstat
#ifdef __USE_LARGEFILE64
#undef stat64
#undef fstat64
#undef lstat64
#endif /* __USE_LARGEFILE64 */

#if defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)
/* >> stat(2), stat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,stat,(char const *__restrict __filename, struct stat *__restrict __buf),kstat,(__filename,__buf))
#elif defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)
/* >> stat(2), stat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,stat,(char const *__restrict __filename, struct stat *__restrict __buf),kstat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
/* >> stat(2), stat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
/* >> stat(2), stat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat64i32,(__filename,__buf))
#elif defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
/* >> stat(2), stat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stati64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
/* >> stat(2), stat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat32i64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
/* >> stat(2), stat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
/* >> stat(2), stat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat32,(__filename,__buf))
#else /* ... */
#include <bits/os/stat.h>
#if defined(__CRT_HAVE___stat64_time64) && defined(__USE_TIME_BITS64) && defined(__glc_stat64_time64)
/* >> stat(2), stat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,stat,(char const *__restrict __filename, struct stat *__restrict __buf),__stat64_time64,(__filename,__buf))
#elif defined(__CRT_HAVE_stat) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64)) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
/* >> stat(2), stat64(2) */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,stat,(char const *__restrict __filename, struct stat *__restrict __buf),(__filename,__buf))
#elif defined(__CRT_HAVE_stat64) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64)) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
/* >> stat(2), stat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,stat,(char const *__restrict __filename, struct stat *__restrict __buf),stat64,(__filename,__buf))
#else /* ... */
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64))) || defined(__CRT_HAVE_stat) || defined(__CRT_HAVE_stat64) || defined(__CRT_HAVE___stat64_time64) || defined(__CRT_HAVE__stat) || defined(__CRT_HAVE__stat32) || defined(__CRT_HAVE__stati64) || defined(__CRT_HAVE__stat32i64) || defined(__CRT_HAVE__stat64) || defined(__CRT_HAVE__stat64i32)
#include <libc/local/sys.stat/stat.h>
/* >> stat(2), stat64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(stat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL stat)(char const *__restrict __filename, struct stat *__restrict __buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stat))(__filename, __buf); })
#endif /* (__AT_FDCWD && ((__CRT_HAVE_kfstatat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstatat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstatat || __CRT_HAVE_fstatat64 || __CRT_HAVE___fstatat64_time64)) || __CRT_HAVE_stat || __CRT_HAVE_stat64 || __CRT_HAVE___stat64_time64 || __CRT_HAVE__stat || __CRT_HAVE__stat32 || __CRT_HAVE__stati64 || __CRT_HAVE__stat32i64 || __CRT_HAVE__stat64 || __CRT_HAVE__stat64i32 */
#endif /* !... */
#endif /* !... */
#if defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)
/* >> fstat(2), fstat64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstat,(__fd_t __fd, struct stat *__restrict __buf),kfstat,(__fd,__buf))
#elif defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)
/* >> fstat(2), fstat64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstat,(__fd_t __fd, struct stat *__restrict __buf),kfstat64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
/* >> fstat(2), fstat64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstat64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
/* >> fstat(2), fstat64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstat64i32,(__fd,__buf))
#elif defined(__CRT_HAVE__fstati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
/* >> fstat(2), fstat64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstati64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
/* >> fstat(2), fstat64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstat32i64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
/* >> fstat(2), fstat64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstat,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
/* >> fstat(2), fstat64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstat32,(__fd,__buf))
#else /* ... */
#include <bits/os/stat.h>
#if defined(__CRT_HAVE___fstat64_time64) && defined(__USE_TIME_BITS64) && defined(__glc_stat64_time64)
/* >> fstat(2), fstat64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstat,(__fd_t __fd, struct stat *__restrict __buf),__fstat64_time64,(__fd,__buf))
#elif defined(__CRT_HAVE_fstat) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64)) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
/* >> fstat(2), fstat64(2) */
__CDECLARE(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstat,(__fd_t __fd, struct stat *__restrict __buf),(__fd,__buf))
#elif defined(__CRT_HAVE_fstat64) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64)) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
/* >> fstat(2), fstat64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstat,(__fd_t __fd, struct stat *__restrict __buf),fstat64,(__fd,__buf))
#elif defined(__CRT_HAVE_fstat) || defined(__CRT_HAVE_fstat64) || defined(__CRT_HAVE___fstat64_time64) || defined(__CRT_HAVE__fstat) || defined(__CRT_HAVE__fstat32) || defined(__CRT_HAVE__fstati64) || defined(__CRT_HAVE__fstat32i64) || defined(__CRT_HAVE__fstat64) || defined(__CRT_HAVE__fstat64i32)
#include <libc/local/sys.stat/fstat.h>
/* >> fstat(2), fstat64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fstat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL fstat)(__fd_t __fd, struct stat *__restrict __buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fstat))(__fd, __buf); })
#endif /* ... */
#endif /* !... */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#if defined(__CRT_HAVE_klstat) && defined(__CRT_KOS_PRIMARY)
/* >> lstat(2), lstat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,lstat,(char const *__restrict __filename, struct stat *__restrict __buf),klstat,(__filename,__buf))
#elif defined(__CRT_HAVE_klstat64) && defined(__CRT_KOS_PRIMARY)
/* >> lstat(2), lstat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,lstat,(char const *__restrict __filename, struct stat *__restrict __buf),klstat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
/* >> lstat(2), lstat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,lstat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
/* >> lstat(2), lstat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,lstat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat64i32,(__filename,__buf))
#elif defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
/* >> lstat(2), lstat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,lstat,(char const *__restrict __filename, struct stat *__restrict __buf),_stati64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
/* >> lstat(2), lstat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,lstat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat32i64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
/* >> lstat(2), lstat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,lstat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
/* >> lstat(2), lstat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,lstat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat32,(__filename,__buf))
#else /* ... */
#include <bits/os/stat.h>
#if defined(__CRT_HAVE___lstat64_time64) && defined(__USE_TIME_BITS64) && defined(__glc_stat64_time64)
/* >> lstat(2), lstat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,lstat,(char const *__restrict __filename, struct stat *__restrict __buf),__lstat64_time64,(__filename,__buf))
#elif defined(__CRT_HAVE_lstat) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64)) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
/* >> lstat(2), lstat64(2) */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,lstat,(char const *__restrict __filename, struct stat *__restrict __buf),(__filename,__buf))
#elif defined(__CRT_HAVE_lstat64) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64)) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
/* >> lstat(2), lstat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,lstat,(char const *__restrict __filename, struct stat *__restrict __buf),lstat64,(__filename,__buf))
#else /* ... */
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64))) || defined(__CRT_HAVE_lstat) || defined(__CRT_HAVE_lstat64) || defined(__CRT_HAVE___lstat64_time64) || defined(__CRT_HAVE__stat) || defined(__CRT_HAVE__stat32) || defined(__CRT_HAVE__stati64) || defined(__CRT_HAVE__stat32i64) || defined(__CRT_HAVE__stat64) || defined(__CRT_HAVE__stat64i32)
#include <libc/local/sys.stat/lstat.h>
/* >> lstat(2), lstat64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(lstat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL lstat)(char const *__restrict __filename, struct stat *__restrict __buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lstat))(__filename, __buf); })
#endif /* (__AT_FDCWD && __AT_SYMLINK_NOFOLLOW && ((__CRT_HAVE_kfstatat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstatat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstatat || __CRT_HAVE_fstatat64 || __CRT_HAVE___fstatat64_time64)) || __CRT_HAVE_lstat || __CRT_HAVE_lstat64 || __CRT_HAVE___lstat64_time64 || __CRT_HAVE__stat || __CRT_HAVE__stat32 || __CRT_HAVE__stati64 || __CRT_HAVE__stat32i64 || __CRT_HAVE__stat64 || __CRT_HAVE__stat64i32 */
#endif /* !... */
#endif /* !... */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)
/* >> stat(2), stat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,stat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),kstat,(__filename,__buf))
#elif defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)
/* >> stat(2), stat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,stat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),kstat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
/* >> stat(2), stat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,stat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),_stat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
/* >> stat(2), stat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,stat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),_stat64i32,(__filename,__buf))
#elif defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)
/* >> stat(2), stat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,stat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),_stati64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)
/* >> stat(2), stat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,stat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),_stat32i64,(__filename,__buf))
#else /* ... */
#include <bits/os/stat.h>
#if defined(__CRT_HAVE___stat64_time64) && defined(__USE_TIME_BITS64) && defined(__glc_stat64_time64)
/* >> stat(2), stat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,stat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),__stat64_time64,(__filename,__buf))
#elif defined(__CRT_HAVE_stat) && defined(__STAT32_MATCHES_STAT64)
/* >> stat(2), stat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,stat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),stat,(__filename,__buf))
#elif defined(__CRT_HAVE_stat64) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64))
/* >> stat(2), stat64(2) */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,stat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),(__filename,__buf))
#elif (defined(__AT_FDCWD) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64))) || defined(__CRT_HAVE_stat) || defined(__CRT_HAVE_stat64) || defined(__CRT_HAVE___stat64_time64) || defined(__CRT_HAVE__stat) || defined(__CRT_HAVE__stat32) || defined(__CRT_HAVE__stati64) || defined(__CRT_HAVE__stat32i64) || defined(__CRT_HAVE__stat64) || defined(__CRT_HAVE__stat64i32)
#include <libc/local/sys.stat/stat64.h>
/* >> stat(2), stat64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(stat64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL stat64)(char const *__restrict __filename, struct stat64 *__restrict __buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(stat64))(__filename, __buf); })
#endif /* ... */
#endif /* !... */
#if defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)
/* >> fstat(2), fstat64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstat64,(__fd_t __fd, struct stat64 *__restrict __buf),kfstat,(__fd,__buf))
#elif defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)
/* >> fstat(2), fstat64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstat64,(__fd_t __fd, struct stat64 *__restrict __buf),kfstat64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
/* >> fstat(2), fstat64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstat64,(__fd_t __fd, struct stat64 *__restrict __buf),_fstat64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
/* >> fstat(2), fstat64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstat64,(__fd_t __fd, struct stat64 *__restrict __buf),_fstat64i32,(__fd,__buf))
#elif defined(__CRT_HAVE__fstati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)
/* >> fstat(2), fstat64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstat64,(__fd_t __fd, struct stat64 *__restrict __buf),_fstati64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)
/* >> fstat(2), fstat64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstat64,(__fd_t __fd, struct stat64 *__restrict __buf),_fstat32i64,(__fd,__buf))
#else /* ... */
#include <bits/os/stat.h>
#if defined(__CRT_HAVE___fstat64_time64) && defined(__USE_TIME_BITS64) && defined(__glc_stat64_time64)
/* >> fstat(2), fstat64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstat64,(__fd_t __fd, struct stat64 *__restrict __buf),__fstat64_time64,(__fd,__buf))
#elif defined(__CRT_HAVE_fstat) && defined(__STAT32_MATCHES_STAT64)
/* >> fstat(2), fstat64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstat64,(__fd_t __fd, struct stat64 *__restrict __buf),fstat,(__fd,__buf))
#elif defined(__CRT_HAVE_fstat64) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64))
/* >> fstat(2), fstat64(2) */
__CDECLARE(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,fstat64,(__fd_t __fd, struct stat64 *__restrict __buf),(__fd,__buf))
#elif defined(__CRT_HAVE_fstat) || defined(__CRT_HAVE_fstat64) || defined(__CRT_HAVE___fstat64_time64) || defined(__CRT_HAVE__fstat) || defined(__CRT_HAVE__fstat32) || defined(__CRT_HAVE__fstati64) || defined(__CRT_HAVE__fstat32i64) || defined(__CRT_HAVE__fstat64) || defined(__CRT_HAVE__fstat64i32)
#include <libc/local/sys.stat/fstat64.h>
/* >> fstat(2), fstat64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(fstat64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL fstat64)(__fd_t __fd, struct stat64 *__restrict __buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fstat64))(__fd, __buf); })
#endif /* ... */
#endif /* !... */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#if defined(__CRT_HAVE_klstat) && defined(__CRT_KOS_PRIMARY)
/* >> lstat(2), lstat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,lstat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),klstat,(__filename,__buf))
#elif defined(__CRT_HAVE_klstat64) && defined(__CRT_KOS_PRIMARY)
/* >> lstat(2), lstat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,lstat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),klstat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
/* >> lstat(2), lstat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,lstat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),_stat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
/* >> lstat(2), lstat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,lstat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),_stat64i32,(__filename,__buf))
#elif defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)
/* >> lstat(2), lstat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,lstat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),_stati64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)
/* >> lstat(2), lstat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,lstat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),_stat32i64,(__filename,__buf))
#else /* ... */
#include <bits/os/stat.h>
#if defined(__CRT_HAVE___lstat64_time64) && defined(__USE_TIME_BITS64) && defined(__glc_stat64_time64)
/* >> lstat(2), lstat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,lstat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),__lstat64_time64,(__filename,__buf))
#elif defined(__CRT_HAVE_lstat) && defined(__STAT32_MATCHES_STAT64)
/* >> lstat(2), lstat64(2) */
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,lstat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),lstat,(__filename,__buf))
#elif defined(__CRT_HAVE_lstat64) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64))
/* >> lstat(2), lstat64(2) */
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,lstat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),(__filename,__buf))
#else /* ... */
#include <asm/os/fcntl.h>
#if (defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64))) || defined(__CRT_HAVE_lstat) || defined(__CRT_HAVE_lstat64) || defined(__CRT_HAVE___lstat64_time64) || defined(__CRT_HAVE__stat) || defined(__CRT_HAVE__stat32) || defined(__CRT_HAVE__stati64) || defined(__CRT_HAVE__stat32i64) || defined(__CRT_HAVE__stat64) || defined(__CRT_HAVE__stat64i32)
#include <libc/local/sys.stat/lstat64.h>
/* >> lstat(2), lstat64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(lstat64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) __ATTR_OUT(2) int __NOTHROW_NCX(__LIBCCALL lstat64)(char const *__restrict __filename, struct stat64 *__restrict __buf) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lstat64))(__filename, __buf); })
#endif /* (__AT_FDCWD && __AT_SYMLINK_NOFOLLOW && ((__CRT_HAVE_kfstatat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstatat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstatat || __CRT_HAVE_fstatat64 || __CRT_HAVE___fstatat64_time64)) || __CRT_HAVE_lstat || __CRT_HAVE_lstat64 || __CRT_HAVE___lstat64_time64 || __CRT_HAVE__stat || __CRT_HAVE__stat32 || __CRT_HAVE__stati64 || __CRT_HAVE__stat32i64 || __CRT_HAVE__stat64 || __CRT_HAVE__stat64i32 */
#endif /* !... */
#endif /* !... */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */
#endif /* __USE_LARGEFILE64 */



#ifdef __USE_ATFILE
#if defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)
/* >> fstatat(2), fstatat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,fstatat,(__fd_t __dirfd, char const *__restrict __filename, struct stat *__restrict __buf, __atflag_t __flags),kfstatat,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)
/* >> fstatat(2), fstatat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,fstatat,(__fd_t __dirfd, char const *__restrict __filename, struct stat *__restrict __buf, __atflag_t __flags),kfstatat64,(__dirfd,__filename,__buf,__flags))
#else /* ... */
#include <bits/os/stat.h>
#if defined(__CRT_HAVE___fstatat64_time64) && defined(__USE_TIME_BITS64) && defined(__glc_stat64_time64)
/* >> fstatat(2), fstatat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,fstatat,(__fd_t __dirfd, char const *__restrict __filename, struct stat *__restrict __buf, __atflag_t __flags),__fstatat64_time64,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_fstatat) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64)) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
/* >> fstatat(2), fstatat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CDECLARE(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,fstatat,(__fd_t __dirfd, char const *__restrict __filename, struct stat *__restrict __buf, __atflag_t __flags),(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_fstatat64) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64)) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
/* >> fstatat(2), fstatat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,fstatat,(__fd_t __dirfd, char const *__restrict __filename, struct stat *__restrict __buf, __atflag_t __flags),fstatat64,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64)
#include <libc/local/sys.stat/fstatat.h>
/* >> fstatat(2), fstatat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fstatat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUT(3) int __NOTHROW_NCX(__LIBCCALL fstatat)(__fd_t __dirfd, char const *__restrict __filename, struct stat *__restrict __buf, __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fstatat))(__dirfd, __filename, __buf, __flags); })
#endif /* ... */
#endif /* !... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)
/* >> fstatat(2), fstatat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,fstatat64,(__fd_t __dirfd, char const *__restrict __filename, struct stat64 *__restrict __buf, __atflag_t __flags),kfstatat,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)
/* >> fstatat(2), fstatat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,fstatat64,(__fd_t __dirfd, char const *__restrict __filename, struct stat64 *__restrict __buf, __atflag_t __flags),kfstatat64,(__dirfd,__filename,__buf,__flags))
#else /* ... */
#include <bits/os/stat.h>
#if defined(__CRT_HAVE___fstatat64_time64) && defined(__USE_TIME_BITS64) && defined(__glc_stat64_time64)
/* >> fstatat(2), fstatat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,fstatat64,(__fd_t __dirfd, char const *__restrict __filename, struct stat64 *__restrict __buf, __atflag_t __flags),__fstatat64_time64,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_fstatat) && defined(__STAT32_MATCHES_STAT64)
/* >> fstatat(2), fstatat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CREDIRECT(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,fstatat64,(__fd_t __dirfd, char const *__restrict __filename, struct stat64 *__restrict __buf, __atflag_t __flags),fstatat,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_fstatat64) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64))
/* >> fstatat(2), fstatat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CDECLARE(__ATTR_IN(2) __ATTR_OUT(3),int,__NOTHROW_NCX,fstatat64,(__fd_t __dirfd, char const *__restrict __filename, struct stat64 *__restrict __buf, __atflag_t __flags),(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64)
#include <libc/local/sys.stat/fstatat64.h>
/* >> fstatat(2), fstatat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fstatat64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_OUT(3) int __NOTHROW_NCX(__LIBCCALL fstatat64)(__fd_t __dirfd, char const *__restrict __filename, struct stat64 *__restrict __buf, __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fstatat64))(__dirfd, __filename, __buf, __flags); })
#endif /* ... */
#endif /* !... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_ATFILE */
#ifndef __mkdir_defined
#define __mkdir_defined
#ifdef __CRT_HAVE_mkdir
/* >> mkdir(2) */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,mkdir,(char const *__pathname, __mode_t __mode),(__pathname,__mode))
#elif defined(__CRT_HAVE___mkdir)
/* >> mkdir(2) */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,mkdir,(char const *__pathname, __mode_t __mode),__mkdir,(__pathname,__mode))
#elif defined(__CRT_HAVE___libc_mkdir)
/* >> mkdir(2) */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,mkdir,(char const *__pathname, __mode_t __mode),__libc_mkdir,(__pathname,__mode))
#else /* ... */
#include <asm/os/fcntl.h>
#if (defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir)) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_mkdirat) || defined(__CRT_HAVE_fmkdirat)))
#include <libc/local/sys.stat/mkdir.h>
/* >> mkdir(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(mkdir, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL mkdir)(char const *__pathname, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mkdir))(__pathname, __mode); })
#else /* (__CRT_DOS_PRIMARY && __CRT_HAVE__mkdir) || (__AT_FDCWD && (__CRT_HAVE_mkdirat || __CRT_HAVE_fmkdirat)) */
#undef __mkdir_defined
#endif /* (!__CRT_DOS_PRIMARY || !__CRT_HAVE__mkdir) && (!__AT_FDCWD || (!__CRT_HAVE_mkdirat && !__CRT_HAVE_fmkdirat)) */
#endif /* !... */
#endif /* !__mkdir_defined */
#ifndef __chmod_defined
#define __chmod_defined
#ifdef __CRT_HAVE_chmod
/* >> chmod(2) */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,chmod,(char const *__filename, __mode_t __mode),(__filename,__mode))
#elif defined(__CRT_HAVE__chmod)
/* >> chmod(2) */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,chmod,(char const *__filename, __mode_t __mode),_chmod,(__filename,__mode))
#elif defined(__CRT_HAVE___chmod)
/* >> chmod(2) */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,chmod,(char const *__filename, __mode_t __mode),__chmod,(__filename,__mode))
#elif defined(__CRT_HAVE___libc_chmod)
/* >> chmod(2) */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,chmod,(char const *__filename, __mode_t __mode),__libc_chmod,(__filename,__mode))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__CRT_HAVE_fchmodat)
#include <libc/local/sys.stat/chmod.h>
/* >> chmod(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(chmod, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL chmod)(char const *__filename, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(chmod))(__filename, __mode); })
#else /* __AT_FDCWD && __CRT_HAVE_fchmodat */
#undef __chmod_defined
#endif /* !__AT_FDCWD || !__CRT_HAVE_fchmodat */
#endif /* !... */
#endif /* !__chmod_defined */

#ifdef __USE_MISC
#ifndef __lchmod_defined
#define __lchmod_defined
#ifdef __CRT_HAVE_lchmod
/* >> lchmod(2) */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,lchmod,(char const *__filename, __mode_t __mode),(__filename,__mode))
#elif defined(__CRT_HAVE__chmod) && defined(__CRT_DOS_PRIMARY)
/* >> lchmod(2) */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,lchmod,(char const *__filename, __mode_t __mode),_chmod,(__filename,__mode))
#elif defined(__CRT_HAVE_chmod) && defined(__CRT_DOS_PRIMARY)
/* >> lchmod(2) */
__CREDIRECT(__ATTR_IN(1),int,__NOTHROW_RPC,lchmod,(char const *__filename, __mode_t __mode),chmod,(__filename,__mode))
#else /* ... */
#include <asm/os/fcntl.h>
#if defined(__AT_FDCWD) && defined(__AT_SYMLINK_NOFOLLOW) && defined(__CRT_HAVE_fchmodat)
#include <libc/local/sys.stat/lchmod.h>
/* >> lchmod(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(lchmod, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL lchmod)(char const *__filename, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(lchmod))(__filename, __mode); })
#else /* __AT_FDCWD && __AT_SYMLINK_NOFOLLOW && __CRT_HAVE_fchmodat */
#undef __lchmod_defined
#endif /* !__AT_FDCWD || !__AT_SYMLINK_NOFOLLOW || !__CRT_HAVE_fchmodat */
#endif /* !... */
#endif /* !__lchmod_defined */
#endif /* __USE_MISC */
#ifndef __umask_defined
#define __umask_defined
#ifdef __CRT_HAVE_umask
/* >> umask(2) */
__CDECLARE(,__mode_t,__NOTHROW_NCX,umask,(__mode_t __mode),(__mode))
#elif defined(__CRT_HAVE__umask)
/* >> umask(2) */
__CREDIRECT(,__mode_t,__NOTHROW_NCX,umask,(__mode_t __mode),_umask,(__mode))
#elif defined(__CRT_HAVE___umask)
/* >> umask(2) */
__CREDIRECT(,__mode_t,__NOTHROW_NCX,umask,(__mode_t __mode),__umask,(__mode))
#elif defined(__CRT_HAVE___libc_umask)
/* >> umask(2) */
__CREDIRECT(,__mode_t,__NOTHROW_NCX,umask,(__mode_t __mode),__libc_umask,(__mode))
#else /* ... */
#undef __umask_defined
#endif /* !... */
#endif /* !__umask_defined */

#ifdef __USE_GNU
#ifdef __CRT_HAVE_getumask
/* >> getumask(2)
 * Return the current umask.
 * WARNING: This function isn't thread-safe */
__CDECLARE(,__mode_t,__NOTHROW_NCX,getumask,(void),())
#elif defined(__CRT_HAVE_umask) || defined(__CRT_HAVE__umask) || defined(__CRT_HAVE___umask) || defined(__CRT_HAVE___libc_umask)
#include <libc/local/sys.stat/getumask.h>
/* >> getumask(2)
 * Return the current umask.
 * WARNING: This function isn't thread-safe */
__NAMESPACE_LOCAL_USING_OR_IMPL(getumask, __FORCELOCAL __ATTR_ARTIFICIAL __mode_t __NOTHROW_NCX(__LIBCCALL getumask)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getumask))(); })
#endif /* ... */
#endif /* __USE_GNU */

#if defined(__USE_KOS) && defined(__USE_ATFILE)
/* >> fmkdirat(2)
 * @param flags: Set of `0 | AT_DOSPATH' */
__CDECLARE_OPT(__ATTR_IN(2),int,__NOTHROW_RPC,fmkdirat,(__fd_t __dirfd, char const *__pathname, __mode_t __mode, __atflag_t __flags),(__dirfd,__pathname,__mode,__flags))
/* >> fmknodat(2)
 * @param flags: Set of `0 | AT_DOSPATH' */
__CDECLARE_OPT(__ATTR_IN(2),int,__NOTHROW_RPC,fmknodat,(__fd_t __dirfd, char const *__nodename, __mode_t __mode, __dev_t __dev, __atflag_t __flags),(__dirfd,__nodename,__mode,__dev,__flags))
#endif /* __USE_KOS && __USE_ATFILE */
#ifdef __CRT_HAVE_mkfifo
/* >> mkfifo(2) */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,mkfifo,(char const *__fifoname, __mode_t __mode),(__fifoname,__mode))
#else /* __CRT_HAVE_mkfifo */
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_mknod) || ((defined(__CRT_HAVE_mknodat) || defined(__CRT_HAVE_fmknodat)) && defined(__AT_FDCWD))) && defined(__S_IFIFO)
#include <libc/local/sys.stat/mkfifo.h>
/* >> mkfifo(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(mkfifo, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL mkfifo)(char const *__fifoname, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mkfifo))(__fifoname, __mode); })
#endif /* (__CRT_HAVE_mknod || ((__CRT_HAVE_mknodat || __CRT_HAVE_fmknodat) && __AT_FDCWD)) && __S_IFIFO */
#endif /* !__CRT_HAVE_mkfifo */

#ifdef __USE_ATFILE
/* >> fchmodat(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH' */
__CDECLARE_OPT(__ATTR_IN(2),int,__NOTHROW_RPC,fchmodat,(__fd_t __dirfd, char const *__filename, __mode_t __mode, __atflag_t __flags),(__dirfd,__filename,__mode,__flags))
#ifdef __CRT_HAVE_mkdirat
/* >> mkdirat(2) */
__CDECLARE(__ATTR_IN(2),int,__NOTHROW_RPC,mkdirat,(__fd_t __dirfd, char const *__pathname, __mode_t __mode),(__dirfd,__pathname,__mode))
#elif defined(__CRT_HAVE_fmkdirat)
#include <libc/local/sys.stat/mkdirat.h>
/* >> mkdirat(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(mkdirat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) int __NOTHROW_RPC(__LIBCCALL mkdirat)(__fd_t __dirfd, char const *__pathname, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mkdirat))(__dirfd, __pathname, __mode); })
#endif /* ... */
#ifdef __CRT_HAVE_mkfifoat
/* >> mkfifoat(2) */
__CDECLARE(__ATTR_IN(2),int,__NOTHROW_RPC,mkfifoat,(__fd_t __dirfd, char const *__fifoname, __mode_t __mode),(__dirfd,__fifoname,__mode))
#elif (defined(__CRT_HAVE_mknodat) || defined(__CRT_HAVE_fmknodat)) && defined(__S_IFIFO)
#include <libc/local/sys.stat/mkfifoat.h>
/* >> mkfifoat(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(mkfifoat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) int __NOTHROW_RPC(__LIBCCALL mkfifoat)(__fd_t __dirfd, char const *__fifoname, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mkfifoat))(__dirfd, __fifoname, __mode); })
#endif /* ... */
#endif /* __USE_ATFILE */

#ifdef __USE_POSIX
#ifdef __CRT_HAVE_fchmod
/* >> fchmod(2) */
__CDECLARE(__ATTR_FDARG(1),int,__NOTHROW_RPC,fchmod,(__fd_t __fd, __mode_t __mode),(__fd,__mode))
#elif defined(__CRT_HAVE___fchmod)
/* >> fchmod(2) */
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_RPC,fchmod,(__fd_t __fd, __mode_t __mode),__fchmod,(__fd,__mode))
#elif defined(__CRT_HAVE___libc_fchmod)
/* >> fchmod(2) */
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_RPC,fchmod,(__fd_t __fd, __mode_t __mode),__libc_fchmod,(__fd,__mode))
#endif /* ... */
#endif /* __USE_POSIX */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
#ifdef __CRT_HAVE_mknod
/* >> mknod(2) */
__CDECLARE(__ATTR_IN(1),int,__NOTHROW_RPC,mknod,(char const *__nodename, __mode_t __mode, __dev_t __dev),(__nodename,__mode,__dev))
#else /* __CRT_HAVE_mknod */
#include <asm/os/fcntl.h>
#if (defined(__CRT_HAVE_mknodat) || defined(__CRT_HAVE_fmknodat)) && defined(__AT_FDCWD)
#include <libc/local/sys.stat/mknod.h>
/* >> mknod(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(mknod, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(1) int __NOTHROW_RPC(__LIBCCALL mknod)(char const *__nodename, __mode_t __mode, __dev_t __dev) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mknod))(__nodename, __mode, __dev); })
#endif /* (__CRT_HAVE_mknodat || __CRT_HAVE_fmknodat) && __AT_FDCWD */
#endif /* !__CRT_HAVE_mknod */
#ifdef __USE_ATFILE
#ifdef __CRT_HAVE_mknodat
/* >> mknodat(2) */
__CDECLARE(__ATTR_IN(2),int,__NOTHROW_RPC,mknodat,(__fd_t __dirfd, char const *__nodename, __mode_t __mode, __dev_t __dev),(__dirfd,__nodename,__mode,__dev))
#elif defined(__CRT_HAVE_fmknodat)
#include <libc/local/sys.stat/mknodat.h>
/* >> mknodat(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(mknodat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) int __NOTHROW_RPC(__LIBCCALL mknodat)(__fd_t __dirfd, char const *__nodename, __mode_t __mode, __dev_t __dev) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mknodat))(__dirfd, __nodename, __mode, __dev); })
#endif /* ... */
#endif /* __USE_ATFILE */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

#ifdef __USE_ATFILE
#if defined(__CRT_HAVE_utimensat) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
__CDECLARE(__ATTR_IN(2) __ATTR_IN_OPT(3),int,__NOTHROW_RPC,utimensat,(__fd_t __dirfd, char const *__filename, struct timespec const __times[2 /*or:3*/], __atflag_t __flags),(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_utimensat64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
__CREDIRECT(__ATTR_IN(2) __ATTR_IN_OPT(3),int,__NOTHROW_RPC,utimensat,(__fd_t __dirfd, char const *__filename, struct timespec const __times[2 /*or:3*/], __atflag_t __flags),utimensat64,(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE___utimensat64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
__CREDIRECT(__ATTR_IN(2) __ATTR_IN_OPT(3),int,__NOTHROW_RPC,utimensat,(__fd_t __dirfd, char const *__filename, struct timespec const __times[2 /*or:3*/], __atflag_t __flags),__utimensat64,(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_utimensat64) || defined(__CRT_HAVE___utimensat64) || defined(__CRT_HAVE_utimensat)
#include <libc/local/sys.stat/utimensat.h>
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(utimensat, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_IN_OPT(3) int __NOTHROW_RPC(__LIBCCALL utimensat)(__fd_t __dirfd, char const *__filename, struct timespec const __times[2 /*or:3*/], __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(utimensat))(__dirfd, __filename, __times, __flags); })
#endif /* ... */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_utimensat) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
__CREDIRECT(__ATTR_IN(2) __ATTR_IN_OPT(3),int,__NOTHROW_RPC,utimensat64,(__fd_t __dirfd, char const *__filename, struct timespec64 const __times[2 /*or:3*/], __atflag_t __flags),utimensat,(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_utimensat64)
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
__CDECLARE(__ATTR_IN(2) __ATTR_IN_OPT(3),int,__NOTHROW_RPC,utimensat64,(__fd_t __dirfd, char const *__filename, struct timespec64 const __times[2 /*or:3*/], __atflag_t __flags),(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE___utimensat64)
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
__CREDIRECT(__ATTR_IN(2) __ATTR_IN_OPT(3),int,__NOTHROW_RPC,utimensat64,(__fd_t __dirfd, char const *__filename, struct timespec64 const __times[2 /*or:3*/], __atflag_t __flags),__utimensat64,(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_utimensat)
#include <libc/local/sys.stat/utimensat64.h>
/* >> utimensat(2), utimensat64(2)
 * @param flags: Set of `0 | AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(utimensat64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_IN(2) __ATTR_IN_OPT(3) int __NOTHROW_RPC(__LIBCCALL utimensat64)(__fd_t __dirfd, char const *__filename, struct timespec64 const __times[2 /*or:3*/], __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(utimensat64))(__dirfd, __filename, __times, __flags); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_ATFILE */

#ifdef __USE_XOPEN2K8
#if defined(__CRT_HAVE_futimens) && (!defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> futimens(2), futimens64(2) */
__CDECLARE(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,futimens,(__fd_t __fd, struct timespec const __times[2 /*or:3*/]),(__fd,__times))
#elif defined(__CRT_HAVE_futimens64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> futimens(2), futimens64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,futimens,(__fd_t __fd, struct timespec const __times[2 /*or:3*/]),futimens64,(__fd,__times))
#elif defined(__CRT_HAVE___futimens64) && (defined(__USE_TIME_BITS64) || __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
/* >> futimens(2), futimens64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,futimens,(__fd_t __fd, struct timespec const __times[2 /*or:3*/]),__futimens64,(__fd,__times))
#elif defined(__CRT_HAVE_futimens64) || defined(__CRT_HAVE___futimens64) || defined(__CRT_HAVE_futimens)
#include <libc/local/sys.stat/futimens.h>
/* >> futimens(2), futimens64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(futimens, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__LIBCCALL futimens)(__fd_t __fd, struct timespec const __times[2 /*or:3*/]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futimens))(__fd, __times); })
#endif /* ... */
#ifdef __USE_TIME64
#if defined(__CRT_HAVE_futimens) && __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
/* >> futimens(2), futimens64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,futimens64,(__fd_t __fd, struct timespec64 const __times[2 /*or:3*/]),futimens,(__fd,__times))
#elif defined(__CRT_HAVE_futimens64)
/* >> futimens(2), futimens64(2) */
__CDECLARE(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,futimens64,(__fd_t __fd, struct timespec64 const __times[2 /*or:3*/]),(__fd,__times))
#elif defined(__CRT_HAVE___futimens64)
/* >> futimens(2), futimens64(2) */
__CREDIRECT(__ATTR_FDARG(1) __ATTR_IN_OPT(2),int,__NOTHROW_RPC,futimens64,(__fd_t __fd, struct timespec64 const __times[2 /*or:3*/]),__futimens64,(__fd,__times))
#elif defined(__CRT_HAVE_futimens)
#include <libc/local/sys.stat/futimens64.h>
/* >> futimens(2), futimens64(2) */
__NAMESPACE_LOCAL_USING_OR_IMPL(futimens64, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_FDARG(1) __ATTR_IN_OPT(2) int __NOTHROW_RPC(__LIBCCALL futimens64)(__fd_t __fd, struct timespec64 const __times[2 /*or:3*/]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futimens64))(__fd, __times); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_XOPEN2K8 */


/* Define DOS's redundant stat() functions. */
#ifdef __USE_DOS
#ifdef __CRT_HAVE__stat
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_stat32,(char const *__restrict __filename, struct __dos_stat32 *__restrict __buf),_stat,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32)
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_stat32,(char const *__restrict __filename, struct __dos_stat32 *__restrict __buf),(__filename,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__stati64
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_stat32i64,(char const *__restrict __filename, struct __dos_stat32i64 *__restrict __buf),_stati64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32i64)
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_stat32i64,(char const *__restrict __filename, struct __dos_stat32i64 *__restrict __buf),(__filename,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__stat64
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_stat64i32,(char const *__restrict __filename, struct __dos_stat64i32 *__restrict __buf),_stat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64i32)
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_stat64i32,(char const *__restrict __filename, struct __dos_stat64i32 *__restrict __buf),(__filename,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__stat64
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_stat64,(char const *__restrict __filename, struct __dos_stat64 *__restrict __buf),(__filename,__buf))
#elif defined(__CRT_HAVE__stat64i32)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_stat64,(char const *__restrict __filename, struct __dos_stat64 *__restrict __buf),_stat64i32,(__filename,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__fstat
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_fstat32,(__fd_t __fd, struct __dos_stat32 *__restrict __buf),_fstat,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat32)
__CDECLARE(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_fstat32,(__fd_t __fd, struct __dos_stat32 *__restrict __buf),(__fd,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__fstati64
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_fstat32i64,(__fd_t __fd, struct __dos_stat32i64 *__restrict __buf),_fstati64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat32i64)
__CDECLARE(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_fstat32i64,(__fd_t __fd, struct __dos_stat32i64 *__restrict __buf),(__fd,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__fstat64
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_fstat64i32,(__fd_t __fd, struct __dos_stat64i32 *__restrict __buf),_fstat64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat64i32)
__CDECLARE(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_fstat64i32,(__fd_t __fd, struct __dos_stat64i32 *__restrict __buf),(__fd,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__fstat64
__CDECLARE(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_fstat64,(__fd_t __fd, struct __dos_stat64 *__restrict __buf),(__fd,__buf))
#elif defined(__CRT_HAVE__fstat64i32)
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_fstat64,(__fd_t __fd, struct __dos_stat64 *__restrict __buf),_fstat64i32,(__fd,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__wstat32
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_wstat32,(__WCHAR_TYPE__ const *__filename, struct __dos_stat32 *__buf),(__filename,__buf))
#elif defined(__CRT_HAVE__wstat)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_wstat32,(__WCHAR_TYPE__ const *__filename, struct __dos_stat32 *__buf),_wstat,(__filename,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__wstat64
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_wstat64,(__WCHAR_TYPE__ const *__filename, struct __dos_stat64 *__buf),(__filename,__buf))
#elif defined(__CRT_HAVE__wstat64i32)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_wstat64,(__WCHAR_TYPE__ const *__filename, struct __dos_stat64 *__buf),_wstat64i32,(__filename,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__wstat32i64
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_wstat32i64,(__WCHAR_TYPE__ const *__filename, struct __dos_stat32i64 *__buf),(__filename,__buf))
#elif defined(__CRT_HAVE__wstati64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_wstat32i64,(__WCHAR_TYPE__ const *__filename, struct __dos_stat32i64 *__buf),_wstati64,(__filename,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__wstat64i32
__CDECLARE(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_wstat64i32,(__WCHAR_TYPE__ const *__filename, struct __dos_stat64i32 *__buf),(__filename,__buf))
#elif defined(__CRT_HAVE__wstat64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,_wstat64i32,(__WCHAR_TYPE__ const *__filename, struct __dos_stat64i32 *__buf),_wstat64,(__filename,__buf))
#endif /* ... */
#endif /* __USE_DOS */

__SYSDECL_END
#endif /* __CC__ */

#ifdef __USE_KOS
#if defined(_WCHAR_H) && !defined(_PARTS_WCHAR_SYS_STAT_H)
#include <parts/wchar/sys/stat.h>
#endif /* _WCHAR_H && !_PARTS_WCHAR_SYS_STAT_H */
#endif /* __USE_KOS */

#ifdef __USE_UTF
#if defined(_UCHAR_H) && !defined(_PARTS_UCHAR_SYS_STAT_H)
#include <parts/uchar/sys/stat.h>
#endif /* _UCHAR_H && !_PARTS_UCHAR_SYS_STAT_H */
#endif /* __USE_UTF */

#endif /* !_SYS_STAT_H */
