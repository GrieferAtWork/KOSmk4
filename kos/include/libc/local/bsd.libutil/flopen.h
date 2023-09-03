/* HASH CRC-32:0x418d2a2e */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_flopen_defined
#define __local_flopen_defined
#include <__crt.h>
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <features.h>
#include <bits/os/stat.h>
#include <bits/types.h>
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_flopenat) || (defined(__LOCK_EX) && (defined(__LOCK_NB) || !defined(__O_NONBLOCK)) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_flock) || defined(__CRT_HAVE___flock)) && ((defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstat) || defined(__CRT_HAVE_fstat64) || defined(__CRT_HAVE___fstat64_time64) || defined(__CRT_HAVE__fstat) || defined(__CRT_HAVE__fstat32) || defined(__CRT_HAVE__fstati64) || defined(__CRT_HAVE__fstat32i64) || defined(__CRT_HAVE__fstat64) || defined(__CRT_HAVE__fstat64i32)) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize) || !defined(__O_TRUNC))))) || (defined(__LOCK_EX) && (defined(__LOCK_NB) || !defined(__O_NONBLOCK)) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_flock) || defined(__CRT_HAVE___flock)) && ((defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstat) || defined(__CRT_HAVE_fstat64) || defined(__CRT_HAVE___fstat64_time64) || defined(__CRT_HAVE__fstat) || defined(__CRT_HAVE__fstat32) || defined(__CRT_HAVE__fstati64) || defined(__CRT_HAVE__fstat32i64) || defined(__CRT_HAVE__fstat64) || defined(__CRT_HAVE__fstat64i32)) && ((defined(__AT_FDCWD) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64))) || (defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_stat) || defined(__CRT_HAVE_stat64) || defined(__CRT_HAVE___stat64_time64) || defined(__CRT_HAVE__stat) || defined(__CRT_HAVE__stat32) || defined(__CRT_HAVE__stati64) || defined(__CRT_HAVE__stat32i64) || defined(__CRT_HAVE__stat64) || defined(__CRT_HAVE__stat64i32)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize) || !defined(__O_TRUNC)))
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_close_defined
#define __local___localdep_close_defined
#ifdef __CRT_HAVE_close
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),close,(__fd))
#elif defined(__CRT_HAVE__close)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),_close,(__fd))
#elif defined(__CRT_HAVE___close)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__close,(__fd))
#elif defined(__CRT_HAVE___libc_close)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_NCX,__localdep_close,(__fd_t __fd),__libc_close,(__fd))
#else /* ... */
#undef __local___localdep_close_defined
#endif /* !... */
#endif /* !__local___localdep_close_defined */
#ifndef __local___localdep_flock_defined
#define __local___localdep_flock_defined
#ifdef __CRT_HAVE_flock
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_RPC,__localdep_flock,(__fd_t __fd, __STDC_INT_AS_UINT_T __operation),flock,(__fd,__operation))
#elif defined(__CRT_HAVE___flock)
__CREDIRECT(__ATTR_FDARG(1),int,__NOTHROW_RPC,__localdep_flock,(__fd_t __fd, __STDC_INT_AS_UINT_T __operation),__flock,(__fd,__operation))
#else /* ... */
#undef __local___localdep_flock_defined
#endif /* !... */
#endif /* !__local___localdep_flock_defined */
#ifndef __local___localdep_flopenat_defined
#define __local___localdep_flopenat_defined
#ifdef __CRT_HAVE_flopenat
__CVREDIRECT(,__fd_t,__NOTHROW_RPC,__localdep_flopenat,(__fd_t __dirfd, const char *__path, __oflag_t __flags),flopenat,(__dirfd,__path,__flags),__flags,1,(__mode_t))
#elif defined(__LOCK_EX) && (defined(__LOCK_NB) || !defined(__O_NONBLOCK)) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_flock) || defined(__CRT_HAVE___flock)) && ((defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstat) || defined(__CRT_HAVE_fstat64) || defined(__CRT_HAVE___fstat64_time64) || defined(__CRT_HAVE__fstat) || defined(__CRT_HAVE__fstat32) || defined(__CRT_HAVE__fstati64) || defined(__CRT_HAVE__fstat32i64) || defined(__CRT_HAVE__fstat64) || defined(__CRT_HAVE__fstat64i32)) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize) || !defined(__O_TRUNC))
__NAMESPACE_LOCAL_END
#include <libc/local/bsd.libutil/flopenat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_flopenat __LIBC_LOCAL_NAME(flopenat)
#else /* ... */
#undef __local___localdep_flopenat_defined
#endif /* !... */
#endif /* !__local___localdep_flopenat_defined */
#ifndef __local___localdep_fstat_defined
#define __local___localdep_fstat_defined
#if defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat,(__fd_t __fd, struct stat *__restrict __buf),kfstat,(__fd,__buf))
#elif defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat,(__fd_t __fd, struct stat *__restrict __buf),kfstat64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstat64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstat64i32,(__fd,__buf))
#elif defined(__CRT_HAVE__fstati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstati64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstat32i64,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstat,(__fd,__buf))
#elif defined(__CRT_HAVE__fstat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat,(__fd_t __fd, struct stat *__restrict __buf),_fstat32,(__fd,__buf))
#elif defined(__CRT_HAVE___fstat64_time64) && defined(__USE_TIME_BITS64) && defined(__glc_stat64_time64)
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat,(__fd_t __fd, struct stat *__restrict __buf),__fstat64_time64,(__fd,__buf))
#elif defined(__CRT_HAVE_fstat) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64)) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat,(__fd_t __fd, struct stat *__restrict __buf),fstat,(__fd,__buf))
#elif defined(__CRT_HAVE_fstat64) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64)) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
__CREDIRECT(__ATTR_FDARG(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_fstat,(__fd_t __fd, struct stat *__restrict __buf),fstat64,(__fd,__buf))
#elif defined(__CRT_HAVE_fstat) || defined(__CRT_HAVE_fstat64) || defined(__CRT_HAVE___fstat64_time64) || defined(__CRT_HAVE__fstat) || defined(__CRT_HAVE__fstat32) || defined(__CRT_HAVE__fstati64) || defined(__CRT_HAVE__fstat32i64) || defined(__CRT_HAVE__fstat64) || defined(__CRT_HAVE__fstat64i32)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.stat/fstat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fstat __LIBC_LOCAL_NAME(fstat)
#else /* ... */
#undef __local___localdep_fstat_defined
#endif /* !... */
#endif /* !__local___localdep_fstat_defined */
#ifndef __local___localdep_ftruncate_defined
#define __local___localdep_ftruncate_defined
#if defined(__CRT_HAVE_ftruncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__NAMESPACE_LOCAL_END
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDWRITE(1),int,__NOTHROW_NCX,__localdep_ftruncate,(__fd_t __fd, __PIO_OFFSET __length),ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE___ftruncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__NAMESPACE_LOCAL_END
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDWRITE(1),int,__NOTHROW_NCX,__localdep_ftruncate,(__fd_t __fd, __PIO_OFFSET __length),__ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE___libc_ftruncate) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__NAMESPACE_LOCAL_END
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDWRITE(1),int,__NOTHROW_NCX,__localdep_ftruncate,(__fd_t __fd, __PIO_OFFSET __length),__libc_ftruncate,(__fd,__length))
#elif defined(__CRT_HAVE__chsize) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__NAMESPACE_LOCAL_END
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDWRITE(1),int,__NOTHROW_NCX,__localdep_ftruncate,(__fd_t __fd, __PIO_OFFSET __length),_chsize,(__fd,__length))
#elif defined(__CRT_HAVE_chsize) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__NAMESPACE_LOCAL_END
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDWRITE(1),int,__NOTHROW_NCX,__localdep_ftruncate,(__fd_t __fd, __PIO_OFFSET __length),chsize,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__NAMESPACE_LOCAL_END
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDWRITE(1),int,__NOTHROW_NCX,__localdep_ftruncate,(__fd_t __fd, __PIO_OFFSET __length),ftruncate64,(__fd,__length))
#elif defined(__CRT_HAVE__chsize_s) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__NAMESPACE_LOCAL_END
#ifndef __PIO_OFFSET
#ifdef __USE_KOS_ALTERATIONS
#define __PIO_OFFSET   __pos_t
#define __PIO_OFFSET64 __pos64_t
#else /* __USE_KOS_ALTERATIONS */
#define __PIO_OFFSET   __off_t
#define __PIO_OFFSET64 __off64_t
#endif /* !__USE_KOS_ALTERATIONS */
#endif /* !__PIO_OFFSET */
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDWRITE(1),int,__NOTHROW_NCX,__localdep_ftruncate,(__fd_t __fd, __PIO_OFFSET __length),_chsize_s,(__fd,__length))
#elif defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/ftruncate.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_ftruncate __LIBC_LOCAL_NAME(ftruncate)
#else /* ... */
#undef __local___localdep_ftruncate_defined
#endif /* !... */
#endif /* !__local___localdep_ftruncate_defined */
#ifndef __local___localdep_open_defined
#define __local___localdep_open_defined
#if defined(__CRT_HAVE_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE__open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___libc_open) && (!defined(__USE_FILE_OFFSET64) || !defined(__O_LARGEFILE) || !__O_LARGEFILE)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__libc_open,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE___open64)
__CVREDIRECT(__ATTR_WUNUSED __ATTR_IN(1),__fd_t,__NOTHROW_RPC,__localdep_open,(char const *__filename, __oflag_t __oflags),__open64,(__filename,__oflags),__oflags,1,(__mode_t))
#elif defined(__CRT_HAVE_open) || defined(__CRT_HAVE__open) || defined(__CRT_HAVE___open) || defined(__CRT_HAVE___libc_open) || (defined(__AT_FDCWD) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)))
__NAMESPACE_LOCAL_END
#include <libc/local/fcntl/open.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_open __LIBC_LOCAL_NAME(open)
#else /* ... */
#undef __local___localdep_open_defined
#endif /* !... */
#endif /* !__local___localdep_open_defined */
#ifndef __local___localdep_stat_defined
#define __local___localdep_stat_defined
#if defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),kstat,(__filename,__buf))
#elif defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),kstat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat64i32) && defined(__CRT_DOS_PRIMARY) && defined(__USE_TIME_BITS64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat64i32,(__filename,__buf))
#elif defined(__CRT_HAVE__stati64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stati64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32i64) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat32i64,(__filename,__buf))
#elif defined(__CRT_HAVE__stat) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat,(__filename,__buf))
#elif defined(__CRT_HAVE__stat32) && defined(__CRT_DOS_PRIMARY) && !defined(__USE_TIME_BITS64) && !defined(__USE_FILE_OFFSET64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),_stat32,(__filename,__buf))
#elif defined(__CRT_HAVE___stat64_time64) && defined(__USE_TIME_BITS64) && defined(__glc_stat64_time64)
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),__stat64_time64,(__filename,__buf))
#elif defined(__CRT_HAVE_stat) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64)) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),stat,(__filename,__buf))
#elif defined(__CRT_HAVE_stat64) && (!defined(__USE_TIME_BITS64) || !defined(__glc_stat64_time64)) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
__CREDIRECT(__ATTR_IN(1) __ATTR_OUT(2),int,__NOTHROW_NCX,__localdep_stat,(char const *__restrict __filename, struct stat *__restrict __buf),stat64,(__filename,__buf))
#elif (defined(__AT_FDCWD) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64))) || defined(__CRT_HAVE_stat) || defined(__CRT_HAVE_stat64) || defined(__CRT_HAVE___stat64_time64) || defined(__CRT_HAVE__stat) || defined(__CRT_HAVE__stat32) || defined(__CRT_HAVE__stati64) || defined(__CRT_HAVE__stat32i64) || defined(__CRT_HAVE__stat64) || defined(__CRT_HAVE__stat64i32)
__NAMESPACE_LOCAL_END
#include <libc/local/sys.stat/stat.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_stat __LIBC_LOCAL_NAME(stat)
#else /* ... */
#undef __local___localdep_stat_defined
#endif /* !... */
#endif /* !__local___localdep_stat_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(flopen) __fd_t
__NOTHROW_RPC(__VLIBCCALL __LIBC_LOCAL_NAME(flopen))(const char *__path, __oflag_t __flags, ...) {
#if defined(__AT_FDCWD) && (defined(__CRT_HAVE_flopenat) || (defined(__LOCK_EX) && (defined(__LOCK_NB) || !defined(__O_NONBLOCK)) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_flock) || defined(__CRT_HAVE___flock)) && ((defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstat) || defined(__CRT_HAVE_fstat64) || defined(__CRT_HAVE___fstat64_time64) || defined(__CRT_HAVE__fstat) || defined(__CRT_HAVE__fstat32) || defined(__CRT_HAVE__fstati64) || defined(__CRT_HAVE__fstat32i64) || defined(__CRT_HAVE__fstat64) || defined(__CRT_HAVE__fstat64i32)) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize) || !defined(__O_TRUNC))))
	__mode_t __mode;
	__builtin_va_list __args;
	__builtin_va_start(__args, __flags);
	__mode = __builtin_va_arg(__args, __mode_t);
	__builtin_va_end(__args);
	return (__NAMESPACE_LOCAL_SYM __localdep_flopenat)(__AT_FDCWD, __path, __flags, __mode);
#else /* __AT_FDCWD && (__CRT_HAVE_flopenat || (__LOCK_EX && (__LOCK_NB || !__O_NONBLOCK) && (__CRT_HAVE_openat64 || __CRT_HAVE_openat) && (__CRT_HAVE_flock || __CRT_HAVE___flock) && ((__CRT_HAVE_kfstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstat || __CRT_HAVE_fstat64 || __CRT_HAVE___fstat64_time64 || __CRT_HAVE__fstat || __CRT_HAVE__fstat32 || __CRT_HAVE__fstati64 || __CRT_HAVE__fstat32i64 || __CRT_HAVE__fstat64 || __CRT_HAVE__fstat64i32) && ((__CRT_HAVE_kfstatat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstatat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstatat || __CRT_HAVE_fstatat64 || __CRT_HAVE___fstatat64_time64) && (__CRT_HAVE_ftruncate64 || __CRT_HAVE__chsize_s || __CRT_HAVE_ftruncate || __CRT_HAVE___ftruncate || __CRT_HAVE___libc_ftruncate || __CRT_HAVE__chsize || __CRT_HAVE_chsize || !__O_TRUNC))) */
#ifdef __O_TRUNC
	int __should_trunc;
#endif /* __O_TRUNC */
	int __flock_op;
	__fd_t __result;
	__mode_t __mode;
	__builtin_va_list __args;
	__builtin_va_start(__args, __flags);
	__mode = __builtin_va_arg(__args, __mode_t);
	__builtin_va_end(__args);
	__flock_op = __LOCK_EX;
#ifdef __O_EXLOCK
	__flags &= ~__O_EXLOCK;
#endif /* __O_EXLOCK */
#if defined(__O_NONBLOCK) && defined(__LOCK_NB)
	if (__flags & __O_NONBLOCK)
		__flock_op |= __LOCK_NB;
#endif /* __O_NONBLOCK && __LOCK_NB */
#ifdef __O_TRUNC
	__should_trunc = __flags & __O_TRUNC;
	__flags &= ~__O_TRUNC;
#endif /* __O_TRUNC */

__again:
	__result = (__NAMESPACE_LOCAL_SYM __localdep_open)(__path, __flags, __mode);
	if __likely(__result != -1) {
		struct stat __st_path, __st_fd;
		if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_flock)(__result, __flock_op))
			goto __err_r;
		if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_stat)(__path, &__st_path))
			goto __restart; /* Race condition: file was deleted */
		if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_fstat)(__result, &__st_fd))
			goto __restart; /* Shouldn't happen */
		if __unlikely(__st_path.st_dev != __st_fd.st_dev ||
		            __st_path.st_ino != __st_fd.st_ino)
			goto __restart; /* File changed in the mean-time. */
#ifdef __O_TRUNC
		if (__should_trunc && __st_fd.st_size != 0) {
			if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_ftruncate)(__result, 0))
				goto __err_r; /* Shouldn't happen */
		}
#endif /* __O_TRUNC */
	}
	return __result;
__err_r:
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)
	(void)(__NAMESPACE_LOCAL_SYM __localdep_close)(__result);
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close */
	return -1;
__restart:
#if defined(__CRT_HAVE_close) || defined(__CRT_HAVE__close) || defined(__CRT_HAVE___close) || defined(__CRT_HAVE___libc_close)
	(void)(__NAMESPACE_LOCAL_SYM __localdep_close)(__result);
#endif /* __CRT_HAVE_close || __CRT_HAVE__close || __CRT_HAVE___close || __CRT_HAVE___libc_close */
	goto __again;
#endif /* !__AT_FDCWD || (!__CRT_HAVE_flopenat && (!__LOCK_EX || (!__LOCK_NB && __O_NONBLOCK) || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat) || (!__CRT_HAVE_flock && !__CRT_HAVE___flock) || ((!__CRT_HAVE_kfstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kfstat64 || !__CRT_KOS_PRIMARY) && !__CRT_HAVE_fstat && !__CRT_HAVE_fstat64 && !__CRT_HAVE___fstat64_time64 && !__CRT_HAVE__fstat && !__CRT_HAVE__fstat32 && !__CRT_HAVE__fstati64 && !__CRT_HAVE__fstat32i64 && !__CRT_HAVE__fstat64 && !__CRT_HAVE__fstat64i32) || ((!__CRT_HAVE_kfstatat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kfstatat64 || !__CRT_KOS_PRIMARY) && !__CRT_HAVE_fstatat && !__CRT_HAVE_fstatat64 && !__CRT_HAVE___fstatat64_time64) || (!__CRT_HAVE_ftruncate64 && !__CRT_HAVE__chsize_s && !__CRT_HAVE_ftruncate && !__CRT_HAVE___ftruncate && !__CRT_HAVE___libc_ftruncate && !__CRT_HAVE__chsize && !__CRT_HAVE_chsize && __O_TRUNC))) */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_flopen_defined
#define __local___localdep_flopen_defined
#define __localdep_flopen __LIBC_LOCAL_NAME(flopen)
#endif /* !__local___localdep_flopen_defined */
#else /* (__AT_FDCWD && (__CRT_HAVE_flopenat || (__LOCK_EX && (__LOCK_NB || !__O_NONBLOCK) && (__CRT_HAVE_openat64 || __CRT_HAVE_openat) && (__CRT_HAVE_flock || __CRT_HAVE___flock) && ((__CRT_HAVE_kfstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstat || __CRT_HAVE_fstat64 || __CRT_HAVE___fstat64_time64 || __CRT_HAVE__fstat || __CRT_HAVE__fstat32 || __CRT_HAVE__fstati64 || __CRT_HAVE__fstat32i64 || __CRT_HAVE__fstat64 || __CRT_HAVE__fstat64i32) && ((__CRT_HAVE_kfstatat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstatat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstatat || __CRT_HAVE_fstatat64 || __CRT_HAVE___fstatat64_time64) && (__CRT_HAVE_ftruncate64 || __CRT_HAVE__chsize_s || __CRT_HAVE_ftruncate || __CRT_HAVE___ftruncate || __CRT_HAVE___libc_ftruncate || __CRT_HAVE__chsize || __CRT_HAVE_chsize || !__O_TRUNC)))) || (__LOCK_EX && (__LOCK_NB || !__O_NONBLOCK) && (__CRT_HAVE_openat64 || __CRT_HAVE_openat) && (__CRT_HAVE_flock || __CRT_HAVE___flock) && ((__CRT_HAVE_kfstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstat || __CRT_HAVE_fstat64 || __CRT_HAVE___fstat64_time64 || __CRT_HAVE__fstat || __CRT_HAVE__fstat32 || __CRT_HAVE__fstati64 || __CRT_HAVE__fstat32i64 || __CRT_HAVE__fstat64 || __CRT_HAVE__fstat64i32) && ((__AT_FDCWD && ((__CRT_HAVE_kfstatat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstatat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstatat || __CRT_HAVE_fstatat64 || __CRT_HAVE___fstatat64_time64)) || (__CRT_HAVE_kstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kstat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_stat || __CRT_HAVE_stat64 || __CRT_HAVE___stat64_time64 || __CRT_HAVE__stat || __CRT_HAVE__stat32 || __CRT_HAVE__stati64 || __CRT_HAVE__stat32i64 || __CRT_HAVE__stat64 || __CRT_HAVE__stat64i32) && (__CRT_HAVE_ftruncate64 || __CRT_HAVE__chsize_s || __CRT_HAVE_ftruncate || __CRT_HAVE___ftruncate || __CRT_HAVE___libc_ftruncate || __CRT_HAVE__chsize || __CRT_HAVE_chsize || !__O_TRUNC)) */
#undef __local_flopen_defined
#endif /* (!__AT_FDCWD || (!__CRT_HAVE_flopenat && (!__LOCK_EX || (!__LOCK_NB && __O_NONBLOCK) || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat) || (!__CRT_HAVE_flock && !__CRT_HAVE___flock) || ((!__CRT_HAVE_kfstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kfstat64 || !__CRT_KOS_PRIMARY) && !__CRT_HAVE_fstat && !__CRT_HAVE_fstat64 && !__CRT_HAVE___fstat64_time64 && !__CRT_HAVE__fstat && !__CRT_HAVE__fstat32 && !__CRT_HAVE__fstati64 && !__CRT_HAVE__fstat32i64 && !__CRT_HAVE__fstat64 && !__CRT_HAVE__fstat64i32) || ((!__CRT_HAVE_kfstatat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kfstatat64 || !__CRT_KOS_PRIMARY) && !__CRT_HAVE_fstatat && !__CRT_HAVE_fstatat64 && !__CRT_HAVE___fstatat64_time64) || (!__CRT_HAVE_ftruncate64 && !__CRT_HAVE__chsize_s && !__CRT_HAVE_ftruncate && !__CRT_HAVE___ftruncate && !__CRT_HAVE___libc_ftruncate && !__CRT_HAVE__chsize && !__CRT_HAVE_chsize && __O_TRUNC)))) && (!__LOCK_EX || (!__LOCK_NB && __O_NONBLOCK) || (!__CRT_HAVE_openat64 && !__CRT_HAVE_openat) || (!__CRT_HAVE_flock && !__CRT_HAVE___flock) || ((!__CRT_HAVE_kfstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kfstat64 || !__CRT_KOS_PRIMARY) && !__CRT_HAVE_fstat && !__CRT_HAVE_fstat64 && !__CRT_HAVE___fstat64_time64 && !__CRT_HAVE__fstat && !__CRT_HAVE__fstat32 && !__CRT_HAVE__fstati64 && !__CRT_HAVE__fstat32i64 && !__CRT_HAVE__fstat64 && !__CRT_HAVE__fstat64i32) || ((!__AT_FDCWD || ((!__CRT_HAVE_kfstatat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kfstatat64 || !__CRT_KOS_PRIMARY) && !__CRT_HAVE_fstatat && !__CRT_HAVE_fstatat64 && !__CRT_HAVE___fstatat64_time64)) && (!__CRT_HAVE_kstat || !__CRT_KOS_PRIMARY) && (!__CRT_HAVE_kstat64 || !__CRT_KOS_PRIMARY) && !__CRT_HAVE_stat && !__CRT_HAVE_stat64 && !__CRT_HAVE___stat64_time64 && !__CRT_HAVE__stat && !__CRT_HAVE__stat32 && !__CRT_HAVE__stati64 && !__CRT_HAVE__stat32i64 && !__CRT_HAVE__stat64 && !__CRT_HAVE__stat64i32) || (!__CRT_HAVE_ftruncate64 && !__CRT_HAVE__chsize_s && !__CRT_HAVE_ftruncate && !__CRT_HAVE___ftruncate && !__CRT_HAVE___libc_ftruncate && !__CRT_HAVE__chsize && !__CRT_HAVE_chsize && __O_TRUNC)) */
#endif /* !__local_flopen_defined */
