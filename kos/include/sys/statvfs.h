/* HASH CRC-32:0x3c8dc24 */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/sys/statvfs.h) */
/* (#) Portability: DJGPP         (/include/sys/statvfs.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/statvfs.h) */
/* (#) Portability: FreeBSD       (/sys/sys/statvfs.h) */
/* (#) Portability: GNU C Library (/io/sys/statvfs.h) */
/* (#) Portability: NetBSD        (/sys/sys/statvfs.h) */
/* (#) Portability: OpenBSD       (/sys/sys/statvfs.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/statvfs.h) */
/* (#) Portability: diet libc     (/include/sys/statvfs.h) */
/* (#) Portability: mintlib       (/include/sys/statvfs.h) */
/* (#) Portability: musl libc     (/include/sys/statvfs.h) */
/* (#) Portability: uClibc        (/include/sys/statvfs.h) */
#ifndef _SYS_STATVFS_H
#define _SYS_STATVFS_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <asm/os/statvfs.h>  /* __ST_* */
#include <bits/os/statvfs.h> /* struct statvfs, struct statvfs64 */
#include <bits/types.h>

#if !defined(ST_RDONLY) && defined(__ST_RDONLY)
#define ST_RDONLY      __ST_RDONLY /* Disallow all file writes */
#endif /* !ST_RDONLY && __ST_RDONLY */
#if !defined(ST_NOSUID) && defined(__ST_NOSUID)
#define ST_NOSUID      __ST_NOSUID /* Ignore `S_ISUID' and `S_ISGID' */
#endif /* !ST_NOSUID && __ST_NOSUID */
#ifdef __USE_GNU
#if !defined(ST_NODEV) && defined(__ST_NODEV)
#define ST_NODEV       __ST_NODEV       /* ??? */
#endif /* !ST_NODEV && __ST_NODEV */
#if !defined(ST_NOEXEC) && defined(__ST_NOEXEC)
#define ST_NOEXEC      __ST_NOEXEC      /* ??? */
#endif /* !ST_NOEXEC && __ST_NOEXEC */
#if !defined(ST_SYNCHRONOUS) && defined(__ST_SYNCHRONOUS)
#define ST_SYNCHRONOUS __ST_SYNCHRONOUS /* ??? */
#endif /* !ST_SYNCHRONOUS && __ST_SYNCHRONOUS */
#if !defined(ST_MANDLOCK) && defined(__ST_MANDLOCK)
#define ST_MANDLOCK    __ST_MANDLOCK    /* ??? */
#endif /* !ST_MANDLOCK && __ST_MANDLOCK */
#if !defined(ST_WRITE) && defined(__ST_WRITE)
#define ST_WRITE       __ST_WRITE       /* ??? */
#endif /* !ST_WRITE && __ST_WRITE */
#if !defined(ST_APPEND) && defined(__ST_APPEND)
#define ST_APPEND      __ST_APPEND      /* ??? */
#endif /* !ST_APPEND && __ST_APPEND */
#if !defined(ST_IMMUTABLE) && defined(__ST_IMMUTABLE)
#define ST_IMMUTABLE   __ST_IMMUTABLE   /* ??? */
#endif /* !ST_IMMUTABLE && __ST_IMMUTABLE */
#if !defined(ST_NOATIME) && defined(__ST_NOATIME)
#define ST_NOATIME     __ST_NOATIME     /* ??? */
#endif /* !ST_NOATIME && __ST_NOATIME */
#if !defined(ST_NODIRATIME) && defined(__ST_NODIRATIME)
#define ST_NODIRATIME  __ST_NODIRATIME  /* ??? */
#endif /* !ST_NODIRATIME && __ST_NODIRATIME */
#if !defined(ST_RELATIME) && defined(__ST_RELATIME)
#define ST_RELATIME    __ST_RELATIME    /* ??? */
#endif /* !ST_RELATIME && __ST_RELATIME */
#endif /* __USE_GNU */


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __fsblkcnt_t_defined
#define __fsblkcnt_t_defined
typedef __FS_TYPE(fsblkcnt) fsblkcnt_t; /* Type to count file system blocks.  */
#endif /* !__fsblkcnt_t_defined */
#ifndef __fsfilcnt_t_defined
#define __fsfilcnt_t_defined
typedef __FS_TYPE(fsfilcnt) fsfilcnt_t; /* Type to count file system inodes.  */
#endif /* !__fsfilcnt_t_defined */

#if defined(__CRT_HAVE_statvfs) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,statvfs,(char const *__file, struct statvfs *__buf),(__file,__buf))
#elif defined(__CRT_HAVE_statvfs64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,statvfs,(char const *__file, struct statvfs *__buf),statvfs64,(__file,__buf))
#endif /* ... */
#if defined(__CRT_HAVE_fstatvfs) && (!defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstatvfs,(__fd_t __filedes, struct statvfs *__buf),(__filedes,__buf))
#elif defined(__CRT_HAVE_fstatvfs64) && (defined(__USE_FILE_OFFSET64) || __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__)
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstatvfs,(__fd_t __filedes, struct statvfs *__buf),fstatvfs64,(__filedes,__buf))
#endif /* ... */

#ifdef __USE_LARGEFILE64
#ifndef statvfs64
#if defined(__CRT_HAVE_statvfs) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,statvfs64,(const char *__file, struct statvfs64 *__buf),statvfs,(__file,__buf))
#elif defined(__CRT_HAVE_statvfs64)
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,statvfs64,(const char *__file, struct statvfs64 *__buf),(__file,__buf))
#endif /* ... */
#endif /* !statvfs64 */
#if defined(__CRT_HAVE_fstatvfs) && __SIZEOF_OFF32_T__ == __SIZEOF_OFF64_T__
__CREDIRECT(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstatvfs64,(__fd_t __filedes, struct statvfs64 *__buf),fstatvfs,(__filedes,__buf))
#elif defined(__CRT_HAVE_fstatvfs64)
__CDECLARE(__ATTR_NONNULL((2)),int,__NOTHROW_NCX,fstatvfs64,(__fd_t __filedes, struct statvfs64 *__buf),(__filedes,__buf))
#endif /* ... */
#endif /* __USE_LARGEFILE64 */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_SYS_STATVFS_H */
