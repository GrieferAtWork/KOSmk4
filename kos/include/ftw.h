/* HASH CRC-32:0x2c621dd0 */
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
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/ftw.h) */
/* (#) Portability: DJGPP         (/include/ftw.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/ftw.h) */
/* (#) Portability: FreeBSD       (/include/ftw.h) */
/* (#) Portability: GNU C Library (/io/ftw.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/ftw.h) */
/* (#) Portability: NetBSD        (/include/ftw.h) */
/* (#) Portability: OpenBSD       (/include/ftw.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/ftw.h) */
/* (#) Portability: diet libc     (/include/ftw.h) */
/* (#) Portability: libc4/5       (/include/ftw.h) */
/* (#) Portability: libc6         (/include/ftw.h) */
/* (#) Portability: mintlib       (/include/ftw.h) */
/* (#) Portability: musl libc     (/include/ftw.h) */
/* (#) Portability: uClibc        (/include/ftw.h) */
#ifndef _FTW_H
#define _FTW_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#include <bits/crt/ftw.h>
#include <bits/types.h>
#include <bits/os/stat.h>

#include <sys/stat.h>
#include <sys/types.h>


/* Values for `typeflag', as passed to ftw-callbacks */
#if !defined(FTW_F) && defined(__FTW_F)
#define FTW_F   __FTW_F   /* ??? */
#endif /* !FTW_F && __FTW_F */
#if !defined(FTW_D) && defined(__FTW_D)
#define FTW_D   __FTW_D   /* ??? */
#endif /* !FTW_D && __FTW_D */
#if !defined(FTW_DNR) && defined(__FTW_DNR)
#define FTW_DNR __FTW_DNR /* ??? */
#endif /* !FTW_DNR && __FTW_DNR */
#if !defined(FTW_NS) && defined(__FTW_NS)
#define FTW_NS  __FTW_NS  /* ??? */
#endif /* !FTW_NS && __FTW_NS */
#if defined(__USE_MISC) || defined(__USE_XOPEN_EXTENDED)
#if !defined(FTW_SL) && defined(__FTW_SL)
#define FTW_SL __FTW_SL /* ??? */
#endif /* !FTW_SL && __FTW_SL */
#endif /* __USE_MISC || __USE_XOPEN_EXTENDED */
#ifdef __USE_XOPEN_EXTENDED
#if !defined(FTW_DP) && defined(__FTW_DP)
#define FTW_DP  __FTW_DP  /* ??? Only for nftw(3) */
#endif /* !FTW_DP && __FTW_DP */
#if !defined(FTW_SLN) && defined(__FTW_SLN)
#define FTW_SLN __FTW_SLN /* ??? Only for nftw(3) */
#endif /* !FTW_SLN && __FTW_SLN */
#endif /* __USE_XOPEN_EXTENDED */

#ifdef __USE_XOPEN_EXTENDED

/* Values returned by user-defined callbacks (e.g. `__ftw_func_t'). */
#ifdef __USE_GNU
#if !defined(FTW_CONTINUE) && defined(__FTW_CONTINUE)
#define FTW_CONTINUE      __FTW_CONTINUE      /* ??? */
#endif /* !FTW_CONTINUE && __FTW_CONTINUE */
#if !defined(FTW_STOP) && defined(__FTW_STOP)
#define FTW_STOP          __FTW_STOP          /* ??? */
#endif /* !FTW_STOP && __FTW_STOP */
#if !defined(FTW_SKIP_SUBTREE) && defined(__FTW_SKIP_SUBTREE)
#define FTW_SKIP_SUBTREE  __FTW_SKIP_SUBTREE  /* ??? */
#endif /* !FTW_SKIP_SUBTREE && __FTW_SKIP_SUBTREE */
#if !defined(FTW_SKIP_SIBLINGS) && defined(__FTW_SKIP_SIBLINGS)
#define FTW_SKIP_SIBLINGS __FTW_SKIP_SIBLINGS /* ??? */
#endif /* !FTW_SKIP_SIBLINGS && __FTW_SKIP_SIBLINGS */
#endif /* __USE_GNU */

/* Values for `nftw(3)::descriptors' */
#if !defined(FTW_PHYS) && defined(__FTW_PHYS)
#define FTW_PHYS  __FTW_PHYS  /* ??? */
#endif /* !FTW_PHYS && __FTW_PHYS */
#if !defined(FTW_MOUNT) && defined(__FTW_MOUNT)
#define FTW_MOUNT __FTW_MOUNT /* ??? */
#endif /* !FTW_MOUNT && __FTW_MOUNT */
#if !defined(FTW_CHDIR) && defined(__FTW_CHDIR)
#define FTW_CHDIR __FTW_CHDIR /* ??? */
#endif /* !FTW_CHDIR && __FTW_CHDIR */
#if !defined(FTW_DEPTH) && defined(__FTW_DEPTH)
#define FTW_DEPTH __FTW_DEPTH /* ??? */
#endif /* !FTW_DEPTH && __FTW_DEPTH */
#ifdef __USE_GNU
#if !defined(FTW_ACTIONRETVAL) && defined(__FTW_ACTIONRETVAL)
#define FTW_ACTIONRETVAL __FTW_ACTIONRETVAL /* ??? */
#endif /* !FTW_ACTIONRETVAL && __FTW_ACTIONRETVAL */
#endif /* __USE_GNU */

#endif /* __USE_XOPEN_EXTENDED */


#ifdef __CC__
__SYSDECL_BEGIN

#ifndef ____ftw_func_t_defined
#define ____ftw_func_t_defined
struct stat;
typedef int (__LIBKCALL *__ftw_func_t)(char const *__fpath, struct stat const *__sb, int __typeflag);
#endif /* !____ftw_func_t_defined */
#ifdef __USE_LARGEFILE64
#ifndef ____ftw64_func_t_defined
#define ____ftw64_func_t_defined
struct stat64;
typedef int (__LIBKCALL *__ftw64_func_t)(char const *__fpath, struct stat64 const *__sb, int __typeflag);
#endif /* !____ftw64_func_t_defined */
#endif /* __USE_LARGEFILE64 */
#ifdef __USE_XOPEN_EXTENDED
#ifndef ____nftw_func_t_defined
#define ____nftw_func_t_defined
struct stat;
#ifdef __USE_XOPEN_EXTENDED
struct FTW;
typedef int (__LIBKCALL *__nftw_func_t)(char const *__fpath, struct stat const *__sb, int __typeflag, struct FTW *__ftwbuf);
#else /* __USE_XOPEN_EXTENDED */
struct __FTW;
typedef int (__LIBKCALL *__nftw_func_t)(char const *__fpath, struct stat const *__sb, int __typeflag, struct __FTW *__ftwbuf);
#endif /* !__USE_XOPEN_EXTENDED */
#endif /* !____nftw_func_t_defined */
#ifdef __USE_LARGEFILE64
#ifndef ____nftw64_func_t_defined
#define ____nftw64_func_t_defined
struct stat64;
#ifdef __USE_XOPEN_EXTENDED
struct FTW;
typedef int (__LIBKCALL *__nftw64_func_t)(char const *__fpath, struct stat64 const *__sb, int __typeflag, struct FTW *__ftwbuf);
#else /* __USE_XOPEN_EXTENDED */
struct __FTW;
typedef int (__LIBKCALL *__nftw64_func_t)(char const *__fpath, struct stat64 const *__sb, int __typeflag, struct __FTW *__ftwbuf);
#endif /* !__USE_XOPEN_EXTENDED */
#endif /* !____nftw64_func_t_defined */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN_EXTENDED */
#if defined(__CRT_HAVE_ftw) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
/* >> ftw(3), ftw64(3) */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,ftw,(char const *__dir, __ftw_func_t __func, __STDC_INT_AS_UINT_T __nopenfd),(__dir,__func,__nopenfd))
#elif defined(__CRT_HAVE_ftw64) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
/* >> ftw(3), ftw64(3) */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,ftw,(char const *__dir, __ftw_func_t __func, __STDC_INT_AS_UINT_T __nopenfd),ftw64,(__dir,__func,__nopenfd))
#endif /* ... */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_ftw) && defined(__STAT32_MATCHES_STAT64)
/* >> ftw(3), ftw64(3) */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,ftw64,(char const *__dir, __ftw64_func_t __func, __STDC_INT_AS_UINT_T __nopenfd),ftw,(__dir,__func,__nopenfd))
#elif defined(__CRT_HAVE_ftw64)
/* >> ftw(3), ftw64(3) */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,ftw64,(char const *__dir, __ftw64_func_t __func, __STDC_INT_AS_UINT_T __nopenfd),(__dir,__func,__nopenfd))
#endif /* ... */
#endif /* __USE_LARGEFILE64 */

#ifdef __USE_XOPEN_EXTENDED
#if defined(__CRT_HAVE_nftw) && (!defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
/* >> nftw(3), nftw64(3)
 * @param: flags: Set of `FTW_PHYS | FTW_MOUNT | FTW_CHDIR | FTW_DEPTH | FTW_ACTIONRETVAL' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,nftw,(char const *__dir, __nftw_func_t __func, __STDC_INT_AS_UINT_T __descriptors, __STDC_INT_AS_UINT_T __flags),(__dir,__func,__descriptors,__flags))
#elif defined(__CRT_HAVE_nftw64) && (defined(__USE_FILE_OFFSET64) || defined(__STAT32_MATCHES_STAT64))
/* >> nftw(3), nftw64(3)
 * @param: flags: Set of `FTW_PHYS | FTW_MOUNT | FTW_CHDIR | FTW_DEPTH | FTW_ACTIONRETVAL' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,nftw,(char const *__dir, __nftw_func_t __func, __STDC_INT_AS_UINT_T __descriptors, __STDC_INT_AS_UINT_T __flags),nftw64,(__dir,__func,__descriptors,__flags))
#endif /* ... */

#ifdef __USE_LARGEFILE64
#if defined(__CRT_HAVE_nftw) && defined(__STAT32_MATCHES_STAT64)
/* >> nftw(3), nftw64(3)
 * @param: flags: Set of `FTW_PHYS | FTW_MOUNT | FTW_CHDIR | FTW_DEPTH | FTW_ACTIONRETVAL' */
__CREDIRECT(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,nftw64,(char const *__dir, __nftw64_func_t __func, __STDC_INT_AS_UINT_T __descriptors, __STDC_INT_AS_UINT_T __flags),nftw,(__dir,__func,__descriptors,__flags))
#elif defined(__CRT_HAVE_nftw64)
/* >> nftw(3), nftw64(3)
 * @param: flags: Set of `FTW_PHYS | FTW_MOUNT | FTW_CHDIR | FTW_DEPTH | FTW_ACTIONRETVAL' */
__CDECLARE(__ATTR_NONNULL((1, 2)),int,__NOTHROW_RPC,nftw64,(char const *__dir, __nftw64_func_t __func, __STDC_INT_AS_UINT_T __descriptors, __STDC_INT_AS_UINT_T __flags),(__dir,__func,__descriptors,__flags))
#endif /* ... */
#endif /* __USE_LARGEFILE64 */
#endif /* __USE_XOPEN_EXTENDED */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_FTW_H */
