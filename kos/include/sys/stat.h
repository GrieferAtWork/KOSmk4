/* HASH CRC-32:0x9a5f154b */
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
#ifndef _SYS_STAT_H
#define _SYS_STAT_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/stat.h>
#include <bits/stat.h>
#include <bits/timespec.h>
#include <bits/types.h>

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#include <time.h>
#endif /* __USE_XOPEN || __USE_XOPEN2K */

__SYSDECL_BEGIN

#ifdef __CC__

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K)
#ifndef __dev_t_defined
#define __dev_t_defined 1
typedef __typedef_dev_t dev_t;
#endif /* __dev_t_defined */

#ifndef __gid_t_defined
#define __gid_t_defined 1
typedef __gid_t gid_t;
#endif /* __gid_t_defined */

#ifndef __ino_t_defined
#define __ino_t_defined 1
typedef __typedef_ino_t ino_t;  /* INode number */
#endif /* __ino_t_defined */

#ifndef __mode_t_defined
#define __mode_t_defined 1
typedef __mode_t mode_t; /* INode type (Set of `S_*' from `<fcntl.h>' or `<sys/stat.h>') */
#endif /* __mode_t_defined */

#ifndef __nlink_t_defined
#define __nlink_t_defined 1
typedef __nlink_t nlink_t;
#endif /* __nlink_t_defined */

#ifndef __off_t_defined
#define __off_t_defined 1
typedef __typedef_off_t off_t;
#endif /* __off_t_defined */

#ifndef __uid_t_defined
#define __uid_t_defined 1
typedef __uid_t uid_t;
#endif /* __uid_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K */

#ifdef __USE_UNIX98
#ifndef __blkcnt_t_defined
#define __blkcnt_t_defined 1
typedef __FS_TYPE(blkcnt)   blkcnt_t;
#endif /* __blkcnt_t_defined */

#ifndef __blksize_t_defined
#define __blksize_t_defined 1
typedef __blksize_t blksize_t;
#endif /* __blksize_t_defined */
#endif /* __USE_UNIX98 */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifndef S_IFMT
#define S_IFMT  __S_IFMT
#define S_IFDIR __S_IFDIR
#define S_IFCHR __S_IFCHR
#define S_IFBLK __S_IFBLK
#define S_IFREG __S_IFREG
#endif /* !S_IFMT */
#if !defined(S_IFIFO) && defined(__S_IFIFO)
#define S_IFIFO __S_IFIFO
#endif /* !S_IFIFO && __S_IFIFO */
#if !defined(S_IFLNK) && defined(__S_IFLNK)
#define S_IFLNK __S_IFLNK
#endif /* !S_IFLNK && __S_IFLNK */
#if ((defined(__USE_MISC) || defined(__USE_UNIX98)) && \
     !defined(S_IFSOCK) && defined(__S_IFSOCK))
#define S_IFSOCK __S_IFSOCK
#endif /* ... */
#endif /* __USE_MISC || __USE_XOPEN */

#ifndef __S_ISTYPE
#define __S_ISTYPE(mode, mask) (((mode) & __S_IFMT) == (mask))
#endif /* !__S_ISTYPE */

#ifndef S_ISDIR
#define S_ISDIR(mode) __S_ISTYPE((mode), __S_IFDIR)
#define S_ISCHR(mode) __S_ISTYPE((mode), __S_IFCHR)
#define S_ISBLK(mode) __S_ISTYPE((mode), __S_IFBLK)
#define S_ISREG(mode) __S_ISTYPE((mode), __S_IFREG)
#endif /* !S_ISDIR */

#if defined(__USE_KOS) && !defined(S_ISDEV)
#define S_ISDEV(mode) __S_ISDEV(mode)
#endif /* __USE_KOS && !S_ISDEV */
#if defined(__S_IFIFO) && !defined(S_ISFIFO)
#define S_ISFIFO(mode) __S_ISTYPE((mode), __S_IFIFO)
#endif /* __S_IFIFO && !S_ISFIFO */
#if defined(__S_IFLNK) && !defined(S_ISLNK)
#define S_ISLNK(mode) __S_ISTYPE((mode), __S_IFLNK)
#endif /* __S_IFLNK && !S_ISLNK */
#if defined(__USE_MISC) && !defined(S_ISLNK)
#define S_ISLNK(mode) 0
#endif /* __USE_MISC && !S_ISLNK */

#ifndef S_ISSOCK
#if (defined(__USE_UNIX98) || defined(__USE_XOPEN2K)) && \
     defined(__S_IFSOCK)
#define S_ISSOCK(mode) __S_ISTYPE((mode), __S_IFSOCK)
#elif defined(__USE_XOPEN2K)
#define S_ISSOCK(mode) 0
#endif
#endif /* !S_ISSOCK */

#ifdef __USE_POSIX199309
#ifndef S_TYPEISMQ
#define S_TYPEISMQ(buf) __S_TYPEISMQ(buf)
#endif /* !S_TYPEISMQ */
#ifndef S_TYPEISSEM
#define S_TYPEISSEM(buf) __S_TYPEISSEM(buf)
#endif /* !S_TYPEISSEM */
#ifndef S_TYPEISSHM
#define S_TYPEISSHM(buf) __S_TYPEISSHM(buf)
#endif /* !S_TYPEISSHM */
#endif /* __USE_POSIX199309 */

#ifndef S_ISUID
#define S_ISUID __S_ISUID /* Set user ID on execution. */
#define S_ISGID __S_ISGID /* Set group ID on execution. */
#endif /* !S_ISUID */

#if defined(__USE_MISC) || defined(__USE_XOPEN)
#ifndef S_ISVTX
#define S_ISVTX __S_ISVTX
#endif /* !S_ISVTX */
#endif /* __USE_MISC || __USE_XOPEN */

#ifndef S_IRUSR
#define S_IRUSR __S_IREAD  /* Read by owner. */
#define S_IWUSR __S_IWRITE /* Write by owner. */
#define S_IXUSR __S_IEXEC  /* Execute by owner. */
#endif /* !S_IRUSR */
#ifndef S_IRWXU
#define S_IRWXU (__S_IREAD | __S_IWRITE | __S_IEXEC)
#endif /* !S_IRWXU */

#ifdef __USE_MISC
#ifndef S_IREAD
#define S_IREAD  S_IRUSR
#define S_IWRITE S_IWUSR
#define S_IEXEC  S_IXUSR
#endif /* !S_IREAD */
#endif /* __USE_MISC */

#ifndef S_IRGRP
#define S_IRGRP (S_IRUSR >> 3) /* Read by group. */
#define S_IWGRP (S_IWUSR >> 3) /* Write by group. */
#define S_IXGRP (S_IXUSR >> 3) /* Execute by group. */
#endif /* !S_IRGRP */
#ifndef S_IRWXG
#define S_IRWXG (S_IRWXU >> 3)
#endif /* !S_IRWXG */
#ifndef S_IROTH
#define S_IROTH (S_IRGRP >> 3) /* Read by others. */
#define S_IWOTH (S_IWGRP >> 3) /* Write by others. */
#define S_IXOTH (S_IXGRP >> 3) /* Execute by others. */
#endif /* !S_IROTH */
#ifndef S_IRWXO
#define S_IRWXO (S_IRWXG >> 3)
#endif /* !S_IRWXO */



#ifdef __USE_KOS
/* As also seen in the linux kernel headers. */
#ifndef S_IRWXUGO
#define S_IRWXUGO (S_IRWXU | S_IRWXG | S_IRWXO)
#endif /* !S_IRWXUGO */
#ifndef S_IALLUGO
#define S_IALLUGO (S_ISUID | S_ISGID | S_ISVTX | S_IRWXUGO)
#endif /* !S_IALLUGO */
#ifndef S_IRUGO
#define S_IRUGO (S_IRUSR | S_IRGRP | S_IROTH)
#endif /* !S_IRUGO */
#ifndef S_IWUGO
#define S_IWUGO (S_IWUSR | S_IWGRP | S_IWOTH)
#endif /* !S_IWUGO */
#ifndef S_IXUGO
#define S_IXUGO (S_IXUSR | S_IXGRP | S_IXOTH)
#endif /* !S_IXUGO */
#endif /* __USE_KOS */

#ifdef __USE_MISC
#ifndef ACCESSPERMS
#define ACCESSPERMS (S_IRWXU | S_IRWXG | S_IRWXO) /* 0777 */
#endif /* !ACCESSPERMS */
#ifndef ALLPERMS
#define ALLPERMS (S_ISUID | S_ISGID | S_ISVTX | S_IRWXU | S_IRWXG | S_IRWXO) /* 07777 */
#endif /* !ALLPERMS */
#ifndef DEFFILEMODE
#define DEFFILEMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) /* 0666*/
#endif /* !DEFFILEMODE */
#ifndef S_BLKSIZE
#define S_BLKSIZE 512 /* Block size for `st_blocks'. */
#endif /* !S_BLKSIZE */
#endif /* __USE_MISC */

#ifdef __USE_DOS
#define _S_IFMT   __S_IFMT
#define _S_IFDIR  __S_IFDIR
#define _S_IFCHR  __S_IFCHR
#define _S_IFIFO  __S_IFIFO
#define _S_IFREG  __S_IFREG
#define _S_IREAD  __S_IREAD
#define _S_IWRITE __S_IWRITE
#define _S_IEXEC  __S_IEXEC
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
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stat,(char const *__restrict __filename, struct stat *__restrict __buf),kstat,(__filename,__buf))
#elif defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stat,(char const *__restrict __filename, struct stat *__restrict __buf),kstat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat64i32,(__filename,__buf))
#elif defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stati64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat32i64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat32,(__filename,__buf))
#elif defined(__CRT_HAVE_stat64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stat,(char const *__restrict __filename, struct stat *__restrict __buf),stat64,(__filename,__buf))
#elif defined(__CRT_HAVE_stat) && !defined(__USE_FILE_OFFSET64)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stat,(char const *__restrict __filename, struct stat *__restrict __buf),(__filename,__buf))
#endif /* ... */

#if defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstat,(__fd_t __fd, struct stat *__restrict __buf),kfstat,(__fd,__buf))
#elif defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstat,(__fd_t __fd, struct stat *__restrict __buf),kfstat64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstat64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstat64i32,(__fd,__buf))
#elif defined(__CRT_HAVE__fstati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstati64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstat32i64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstat,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstat32,(__fd,__buf))
#elif defined(__CRT_HAVE_fstat64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstat,(__fd_t __fd, struct stat *__restrict __buf),fstat64,(__fd,__buf))
#elif defined(__CRT_HAVE_fstat) && !defined(__USE_FILE_OFFSET64)
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstat,(__fd_t __fd, struct stat *__restrict __buf),(__fd,__buf))
#endif /* ... */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#if defined(__CRT_HAVE_klstat) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,lstat,(char const *__restrict __filename, struct stat *__restrict __buf),klstat,(__filename,__buf))
#elif defined(__CRT_HAVE_klstat64) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,lstat,(char const *__restrict __filename, struct stat *__restrict __buf),klstat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,lstat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,lstat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat64i32,(__filename,__buf))
#elif defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,lstat,(char const *__restrict __filename, struct stat *__restrict __buf),_stati64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,lstat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat32i64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,lstat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,lstat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat32,(__filename,__buf))
#elif defined(__CRT_HAVE_lstat64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,lstat,(char const *__restrict __filename, struct stat *__restrict __buf),lstat64,(__filename,__buf))
#elif defined(__CRT_HAVE_lstat) && !defined(__USE_FILE_OFFSET64)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,lstat,(char const *__restrict __filename, struct stat *__restrict __buf),(__filename,__buf))
#endif /* ... */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),kstat,(__filename,__buf))
#elif defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),kstat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),_stat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),_stat64i32,(__filename,__buf))
#elif defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),_stati64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),_stat32i64,(__filename,__buf))
#elif defined(__CRT_HAVE_stat64)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,stat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),(__filename,__buf))
#endif /* ... */

#if defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstat64,(__fd_t __fd, struct stat64 *__restrict __buf),kfstat,(__fd,__buf))
#elif defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstat64,(__fd_t __fd, struct stat64 *__restrict __buf),kfstat64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstat64,(__fd_t __fd, struct stat64 *__restrict __buf),_fstat64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstat64,(__fd_t __fd, struct stat64 *__restrict __buf),_fstat64i32,(__fd,__buf))
#elif defined(__CRT_HAVE__fstati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstat64,(__fd_t __fd, struct stat64 *__restrict __buf),_fstati64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstat64,(__fd_t __fd, struct stat64 *__restrict __buf),_fstat32i64,(__fd,__buf))
#elif defined(__CRT_HAVE_fstat64)
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstat64,(__fd_t __fd, struct stat64 *__restrict __buf),(__fd,__buf))
#endif /* ... */

#if defined(__USE_XOPEN_EXTENDED) || defined(__USE_XOPEN2K)
#if defined(__CRT_HAVE_klstat) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,lstat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),klstat,(__filename,__buf))
#elif defined(__CRT_HAVE_klstat64) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,lstat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),klstat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,lstat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),_stat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,lstat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),_stat64i32,(__filename,__buf))
#elif defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,lstat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),_stati64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,lstat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),_stat32i64,(__filename,__buf))
#elif defined(__CRT_HAVE_lstat64)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,lstat64,(char const *__restrict __filename, struct stat64 *__restrict __buf),(__filename,__buf))
#endif /* ... */
#endif /* __USE_XOPEN_EXTENDED || __USE_XOPEN2K */
#endif /* __USE_LARGEFILE64 */



#ifdef __USE_ATFILE
#if defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
__CREDIRECT(__ATTR_NONNULL((2, 3)),int,__NOTHROW_NCX,fstatat,(__fd_t __dirfd, char const *__restrict __filename, struct stat *__restrict __buf, __atflag_t __flags),kfstatat,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
__CREDIRECT(__ATTR_NONNULL((2, 3)),int,__NOTHROW_NCX,fstatat,(__fd_t __dirfd, char const *__restrict __filename, struct stat *__restrict __buf, __atflag_t __flags),kfstatat64,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_fstatat64) && defined(__USE_FILE_OFFSET64)
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
__CREDIRECT(__ATTR_NONNULL((2, 3)),int,__NOTHROW_NCX,fstatat,(__fd_t __dirfd, char const *__restrict __filename, struct stat *__restrict __buf, __atflag_t __flags),fstatat64,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_fstatat) && !defined(__USE_FILE_OFFSET64)
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
__CDECLARE(__ATTR_NONNULL((2, 3)),int,__NOTHROW_NCX,fstatat,(__fd_t __dirfd, char const *__restrict __filename, struct stat *__restrict __buf, __atflag_t __flags),(__dirfd,__filename,__buf,__flags))
#endif /* ... */
#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
__CREDIRECT(__ATTR_NONNULL((2, 3)),int,__NOTHROW_NCX,fstatat64,(__fd_t __dirfd, char const *__restrict __filename, struct stat *__restrict __buf, __atflag_t __flags),kfstatat,(__dirfd,__filename,__buf,__flags))
#elif defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
__CREDIRECT(__ATTR_NONNULL((2, 3)),int,__NOTHROW_NCX,fstatat64,(__fd_t __dirfd, char const *__restrict __filename, struct stat *__restrict __buf, __atflag_t __flags),kfstatat64,(__dirfd,__filename,__buf,__flags))
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_ATFILE */

#ifndef __mkdir_defined
#define __mkdir_defined 1
#ifdef __CRT_HAVE_mkdir
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkdir,(char const *__pathname, __mode_t __mode),(__pathname,__mode))
#elif defined(__CRT_DOS_PRIMARY) && defined(__CRT_HAVE__mkdir)
#include <local/sys.stat/mkdir.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(mkdir, __FORCELOCAL __ATTR_NONNULL((1)) int __NOTHROW_RPC(__LIBCCALL mkdir)(char const *__pathname, __mode_t __mode) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(mkdir))(__pathname, __mode); })
#else /* ... */
#undef __mkdir_defined
#endif /* !... */
#endif /* !__mkdir_defined */

#ifndef __chmod_defined
#define __chmod_defined 1
#ifdef __CRT_HAVE_chmod
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,chmod,(char const *__filename, __mode_t __mode),(__filename,__mode))
#elif defined(__CRT_HAVE__chmod)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,chmod,(char const *__filename, __mode_t __mode),_chmod,(__filename,__mode))
#else /* ... */
#undef __chmod_defined
#endif /* !... */
#endif /* !__chmod_defined */

#ifdef __USE_MISC
#ifndef __lchmod_defined
#define __lchmod_defined 1
#ifdef __CRT_HAVE_lchmod
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,lchmod,(char const *__filename, __mode_t __mode),(__filename,__mode))
#elif defined(__CRT_HAVE__chmod) && defined(__CRT_DOS_PRIMARY)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,lchmod,(char const *__filename, __mode_t __mode),_chmod,(__filename,__mode))
#elif defined(__CRT_HAVE_chmod) && defined(__CRT_DOS_PRIMARY)
__CREDIRECT(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,lchmod,(char const *__filename, __mode_t __mode),chmod,(__filename,__mode))
#else /* ... */
#undef __lchmod_defined
#endif /* !... */
#endif /* !__lchmod_defined */
#endif /* __USE_MISC */

#ifndef __umask_defined
#define __umask_defined 1
#ifdef __CRT_HAVE_umask
__CDECLARE(,__mode_t,__NOTHROW_NCX,umask,(__mode_t __mode),(__mode))
#elif defined(__CRT_HAVE__umask)
__CREDIRECT(,__mode_t,__NOTHROW_NCX,umask,(__mode_t __mode),_umask,(__mode))
#else /* ... */
#undef __umask_defined
#endif /* !... */
#endif /* !__umask_defined */

#ifdef __USE_GNU
#ifdef __CRT_HAVE_getumask
/* Return the current umask.
 * WARNING: This function isn't thread-safe */
__CDECLARE(,__mode_t,__NOTHROW_NCX,getumask,(void),())
#elif defined(__CRT_HAVE_umask) || defined(__CRT_HAVE__umask)
#include <local/sys.stat/getumask.h>
/* Return the current umask.
 * WARNING: This function isn't thread-safe */
__NAMESPACE_LOCAL_USING_OR_IMPL(getumask, __FORCELOCAL __mode_t __NOTHROW_NCX(__LIBCCALL getumask)(void) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(getumask))(); })
#endif /* ... */
#endif /* __USE_GNU */

#if defined(__USE_KOS) && defined(__USE_ATFILE)
#ifdef __CRT_HAVE_fmkdirat
/* @param flags: Set of `0 | AT_DOSPATH' */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,fmkdirat,(__fd_t __dirfd, char const *__pathname, __mode_t __mode, __atflag_t __flags),(__dirfd,__pathname,__mode,__flags))
#endif /* __CRT_HAVE_fmkdirat */
#ifdef __CRT_HAVE_fmknodat
/* @param flags: Set of `0 | AT_DOSPATH' */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,fmknodat,(__fd_t __dirfd, char const *__nodename, __mode_t __mode, __dev_t __dev, __atflag_t __flags),(__dirfd,__nodename,__mode,__dev,__flags))
#endif /* __CRT_HAVE_fmknodat */
#endif

#ifdef __CRT_HAVE_mkfifo
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,mkfifo,(char const *__fifoname, __mode_t __mode),(__fifoname,__mode))
#endif /* __CRT_HAVE_mkfifo */

#ifdef __USE_ATFILE
#ifdef __CRT_HAVE_fchmodat
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_DOSPATH' */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,fchmodat,(__fd_t __dirfd, char const *__filename, __mode_t __mode, __atflag_t __flags),(__dirfd,__filename,__mode,__flags))
#endif /* __CRT_HAVE_fchmodat */
#ifdef __CRT_HAVE_mkdirat
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,mkdirat,(__fd_t __dirfd, char const *__pathname, __mode_t __mode),(__dirfd,__pathname,__mode))
#endif /* __CRT_HAVE_mkdirat */
#ifdef __CRT_HAVE_mkfifoat
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,mkfifoat,(__fd_t __dirfd, char const *__fifoname, __mode_t __mode),(__dirfd,__fifoname,__mode))
#endif /* __CRT_HAVE_mkfifoat */
#endif /* __USE_ATFILE */

#ifdef __USE_POSIX
#ifdef __CRT_HAVE_fchmod
__CDECLARE(,int,__NOTHROW_RPC,fchmod,(__fd_t __fd, __mode_t __mode),(__fd,__mode))
#endif /* __CRT_HAVE_fchmod */
#endif /* __USE_POSIX */

#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
#ifdef __CRT_HAVE_mknod
__CDECLARE(__ATTR_NONNULL((1)),int,__NOTHROW_RPC,mknod,(char const *__nodename, __mode_t __mode, __dev_t __dev),(__nodename,__mode,__dev))
#endif /* __CRT_HAVE_mknod */
#ifdef __USE_ATFILE
#ifdef __CRT_HAVE_mknodat
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,mknodat,(__fd_t __dirfd, char const *__nodename, __mode_t __mode, __dev_t __dev),(__dirfd,__nodename,__mode,__dev))
#endif /* __CRT_HAVE_mknodat */
#endif /* __USE_ATFILE */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */

#ifdef __USE_ATFILE
#if defined(__CRT_HAVE_utimensat64) && defined(__USE_TIME_BITS64)
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,utimensat,(__fd_t __dirfd, char const *__filename, struct timespec const __times[2 /*or:3*/], __atflag_t __flags),utimensat64,(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_utimensat) && !defined(__USE_TIME_BITS64)
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,utimensat,(__fd_t __dirfd, char const *__filename, struct timespec const __times[2 /*or:3*/], __atflag_t __flags),(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_utimensat) || defined(__CRT_HAVE_utimensat64)
#include <local/sys.stat/utimensat.h>
/* @param flags: Set of `0|AT_SYMLINK_NOFOLLOW|AT_CHANGE_CTIME|AT_DOSPATH' */
__NAMESPACE_LOCAL_USING_OR_IMPL(utimensat, __FORCELOCAL __ATTR_NONNULL((2)) int __NOTHROW_RPC(__LIBCCALL utimensat)(__fd_t __dirfd, char const *__filename, struct timespec const __times[2 /*or:3*/], __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(utimensat))(__dirfd, __filename, __times, __flags); })
#endif /* ... */
#ifdef __USE_TIME64
#ifdef __CRT_HAVE_utimensat64
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,utimensat64,(__fd_t __dirfd, char const *__filename, struct timespec64 const __times[2 /*or:3*/], __atflag_t __flags),(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_utimensat) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_RPC,utimensat64,(__fd_t __dirfd, char const *__filename, struct timespec64 const __times[2 /*or:3*/], __atflag_t __flags),utimensat,(__dirfd,__filename,__times,__flags))
#elif defined(__CRT_HAVE_utimensat)
#include <local/sys.stat/utimensat64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(utimensat64, __FORCELOCAL __ATTR_NONNULL((2)) int __NOTHROW_RPC(__LIBCCALL utimensat64)(__fd_t __dirfd, char const *__filename, struct timespec64 const __times[2 /*or:3*/], __atflag_t __flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(utimensat64))(__dirfd, __filename, __times, __flags); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_ATFILE */

#ifdef __USE_XOPEN2K8
#if defined(__CRT_HAVE_futimens64) && defined(__USE_TIME_BITS64)
__CREDIRECT(,int,__NOTHROW_RPC,futimens,(__fd_t __fd, struct timespec const __times[2 /*or:3*/]),futimens64,(__fd,__times))
#elif defined(__CRT_HAVE_futimens) && !defined(__USE_TIME_BITS64)
__CDECLARE(,int,__NOTHROW_RPC,futimens,(__fd_t __fd, struct timespec const __times[2 /*or:3*/]),(__fd,__times))
#elif defined(__CRT_HAVE_futimens) || defined(__CRT_HAVE_futimens64)
#include <local/sys.stat/futimens.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(futimens, __FORCELOCAL int __NOTHROW_RPC(__LIBCCALL futimens)(__fd_t __fd, struct timespec const __times[2 /*or:3*/]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futimens))(__fd, __times); })
#endif /* ... */
#ifdef __USE_TIME64
#ifdef __CRT_HAVE_futimens64
__CDECLARE(,int,__NOTHROW_RPC,futimens64,(__fd_t __fd, struct timespec64 const __times[2 /*or:3*/]),(__fd,__times))
#elif defined(__CRT_HAVE_futimens) && (__SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__)
__CREDIRECT(,int,__NOTHROW_RPC,futimens64,(__fd_t __fd, struct timespec64 const __times[2 /*or:3*/]),futimens,(__fd,__times))
#elif defined(__CRT_HAVE_futimens)
#include <local/sys.stat/futimens64.h>
__NAMESPACE_LOCAL_USING_OR_IMPL(futimens64, __FORCELOCAL int __NOTHROW_RPC(__LIBCCALL futimens64)(__fd_t __fd, struct timespec64 const __times[2 /*or:3*/]) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(futimens64))(__fd, __times); })
#endif /* ... */
#endif /* __USE_TIME64 */
#endif /* __USE_XOPEN2K8 */


/* Define DOS's redundant stat() functions. */
#ifdef __USE_DOS
#ifdef __CRT_HAVE__stat
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stat32,(char const *__restrict __filename, struct __dos_stat32 *__restrict __buf),_stat,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stat32,(char const *__restrict __filename, struct __dos_stat32 *__restrict __buf),(__filename,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__stati64
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stat32i64,(char const *__restrict __filename, struct __dos_stat32i64 *__restrict __buf),_stati64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32i64)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stat32i64,(char const *__restrict __filename, struct __dos_stat32i64 *__restrict __buf),(__filename,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__stat64
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stat64i32,(char const *__restrict __filename, struct __dos_stat64i32 *__restrict __buf),_stat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64i32)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stat64i32,(char const *__restrict __filename, struct __dos_stat64i32 *__restrict __buf),(__filename,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__stat64
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stat64,(char const *__restrict __filename, struct __dos_stat64 *__restrict __buf),(__filename,__buf))
#elif defined(__CRT_HAVE__stat64i32)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_stat64,(char const *__restrict __filename, struct __dos_stat64 *__restrict __buf),_stat64i32,(__filename,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__fstat
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,_fstat32,(__fd_t __fd, struct __dos_stat32 *__restrict __buf),_fstat,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat32)
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,_fstat32,(__fd_t __fd, struct __dos_stat32 *__restrict __buf),(__fd,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__fstati64
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,_fstat32i64,(__fd_t __fd, struct __dos_stat32i64 *__restrict __buf),_fstati64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat32i64)
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,_fstat32i64,(__fd_t __fd, struct __dos_stat32i64 *__restrict __buf),(__fd,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__fstat64
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,_fstat64i32,(__fd_t __fd, struct __dos_stat64i32 *__restrict __buf),_fstat64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat64i32)
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,_fstat64i32,(__fd_t __fd, struct __dos_stat64i32 *__restrict __buf),(__fd,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__fstat64
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,_fstat64,(__fd_t __fd, struct __dos_stat64 *__restrict __buf),(__fd,__buf))
#elif defined(__CRT_HAVE__fstat64i32)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,_fstat64,(__fd_t __fd, struct __dos_stat64 *__restrict __buf),_fstat64i32,(__fd,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__wstat32
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wstat32,(__WCHAR_TYPE__ const *__filename, struct __dos_stat32 *__buf),(__filename,__buf))
#elif defined(__CRT_HAVE_DOS$_wstat32) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wstat32,(__CHAR32_TYPE__ const *__filename, struct __dos_stat32 *__buf),_wstat32,(__filename,__buf))
#elif defined(__CRT_HAVE_DOS$_wstat32) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wstat32,(__CHAR16_TYPE__ const *__filename, struct __dos_stat32 *__buf),_wstat32,(__filename,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__wstat64
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wstat64,(__WCHAR_TYPE__ const *__filename, struct __dos_stat64 *__buf),(__filename,__buf))
#elif defined(__CRT_HAVE_DOS$_wstat64) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wstat64,(__CHAR32_TYPE__ const *__filename, struct __dos_stat64 *__buf),_wstat64,(__filename,__buf))
#elif defined(__CRT_HAVE_DOS$_wstat64) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wstat64,(__CHAR16_TYPE__ const *__filename, struct __dos_stat64 *__buf),_wstat64,(__filename,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__wstat32i64
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wstat32i64,(__WCHAR_TYPE__ const *__filename, struct __dos_stat32i64 *__buf),(__filename,__buf))
#elif defined(__CRT_HAVE_DOS$_wstat32i64) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wstat32i64,(__CHAR32_TYPE__ const *__filename, struct __dos_stat32i64 *__buf),_wstat32i64,(__filename,__buf))
#elif defined(__CRT_HAVE_DOS$_wstat32i64) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wstat32i64,(__CHAR16_TYPE__ const *__filename, struct __dos_stat32i64 *__buf),_wstat32i64,(__filename,__buf))
#endif /* ... */
#ifdef __CRT_HAVE__wstat64i32
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wstat64i32,(__WCHAR_TYPE__ const *__filename, struct __dos_stat64i32 *__buf),(__filename,__buf))
#elif defined(__CRT_HAVE_DOS$_wstat64i32) && __SIZEOF_WCHAR_T__ == 4
__CREDIRECT_KOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wstat64i32,(__CHAR32_TYPE__ const *__filename, struct __dos_stat64i32 *__buf),_wstat64i32,(__filename,__buf))
#elif defined(__CRT_HAVE_DOS$_wstat64i32) && __SIZEOF_WCHAR_T__ == 2
__CREDIRECT_DOS(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,_wstat64i32,(__CHAR16_TYPE__ const *__filename, struct __dos_stat64i32 *__buf),_wstat64i32,(__filename,__buf))
#endif /* ... */
#endif /* __USE_DOS */

#endif /* __CC__ */

__SYSDECL_END

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
