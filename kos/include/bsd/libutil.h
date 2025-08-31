/* HASH CRC-32:0x4540d3f6 */
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
/* (#) Portability: libbsd (/include/bsd/libutil.h) */
/*!always_includes <libutil.h>*/
#ifndef _BSD_LIBUTIL_H
#define _BSD_LIBUTIL_H 1

#include <__stdinc.h>
#include <__crt.h>

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <asm/crt/humanize_number.h>
#include <features.h>
#include <libutil.h>
#include <bits/types.h>
#include <sys/types.h>
#include <stdint.h>
#include <stdio.h>

/* Flags for `humanize_number(3)::flags' */
#if !defined(HN_DECIMAL) && defined(__HN_DECIMAL)
#define HN_DECIMAL      __HN_DECIMAL
#endif /* !HN_DECIMAL && __HN_DECIMAL */
#if !defined(HN_NOSPACE) && defined(__HN_NOSPACE)
#define HN_NOSPACE      __HN_NOSPACE
#endif /* !HN_NOSPACE && __HN_NOSPACE */
#if !defined(HN_B) && defined(__HN_B)
#define HN_B            __HN_B
#endif /* !HN_B && __HN_B */
#if !defined(HN_DIVISOR_1000) && defined(__HN_DIVISOR_1000)
#define HN_DIVISOR_1000 __HN_DIVISOR_1000
#endif /* !HN_DIVISOR_1000 && __HN_DIVISOR_1000 */
#if !defined(HN_IEC_PREFIXES) && defined(__HN_IEC_PREFIXES)
#define HN_IEC_PREFIXES __HN_IEC_PREFIXES
#endif /* !HN_IEC_PREFIXES && __HN_IEC_PREFIXES */

/* Flags for `humanize_number(3)::scale' */
#if !defined(HN_GETSCALE) && defined(__HN_GETSCALE)
#define HN_GETSCALE     __HN_GETSCALE
#endif /* !HN_GETSCALE && __HN_GETSCALE */
#if !defined(HN_AUTOSCALE) && defined(__HN_AUTOSCALE)
#define HN_AUTOSCALE    __HN_AUTOSCALE
#endif /* !HN_AUTOSCALE && __HN_AUTOSCALE */

#ifdef __CC__
__SYSDECL_BEGIN

#if !defined(__humanize_number_defined) && defined(__CRT_HAVE_humanize_number)
#define __humanize_number_defined
/* >> humanize_number(3), dehumanize_number(3)
 * @param: scale: Set of `HN_GETSCALE | HN_AUTOSCALE'
 * @param: flags: Set of `HN_DECIMAL | HN_NOSPACE | HN_B | HN_DIVISOR_1000 | HN_IEC_PREFIXES' */
__CDECLARE(,int,__NOTHROW_NCX,humanize_number,(char *__buf, __SIZE_TYPE__ __len, __INT64_TYPE__ __bytes, char const *__suffix, int __scale, int __flags),(__buf,__len,__bytes,__suffix,__scale,__flags))
#endif /* !__humanize_number_defined && __CRT_HAVE_humanize_number */
#ifdef __CRT_HAVE_flopen
__LIBC __fd_t __NOTHROW_RPC(__VLIBCCALL flopen)(char const *__path, __oflag_t __flags, ...) __CASMNAME_SAME("flopen");
#else /* __CRT_HAVE_flopen */
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <bits/os/stat.h>
#if (defined(__AT_FDCWD) && (defined(__CRT_HAVE_flopenat) || (defined(__LOCK_EX) && (defined(__LOCK_NB) || !defined(__O_NONBLOCK)) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_flock) || defined(__CRT_HAVE___flock)) && ((defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstat) || defined(__CRT_HAVE_fstat64) || defined(__CRT_HAVE___fstat64_time64) || defined(__CRT_HAVE__fstat) || defined(__CRT_HAVE__fstat32) || defined(__CRT_HAVE__fstati64) || defined(__CRT_HAVE__fstat32i64) || defined(__CRT_HAVE__fstat64) || defined(__CRT_HAVE__fstat64i32)) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize) || !defined(__O_TRUNC))))) || (defined(__LOCK_EX) && (defined(__LOCK_NB) || !defined(__O_NONBLOCK)) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_flock) || defined(__CRT_HAVE___flock)) && ((defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstat) || defined(__CRT_HAVE_fstat64) || defined(__CRT_HAVE___fstat64_time64) || defined(__CRT_HAVE__fstat) || defined(__CRT_HAVE__fstat32) || defined(__CRT_HAVE__fstati64) || defined(__CRT_HAVE__fstat32i64) || defined(__CRT_HAVE__fstat64) || defined(__CRT_HAVE__fstat64i32)) && ((defined(__AT_FDCWD) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64))) || (defined(__CRT_HAVE_kstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kstat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_stat) || defined(__CRT_HAVE_stat64) || defined(__CRT_HAVE___stat64_time64) || defined(__CRT_HAVE__stat) || defined(__CRT_HAVE__stat32) || defined(__CRT_HAVE__stati64) || defined(__CRT_HAVE__stat32i64) || defined(__CRT_HAVE__stat64) || defined(__CRT_HAVE__stat64i32)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize) || !defined(__O_TRUNC)))
#include <libc/local/bsd.libutil/flopen.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(flopen, __FORCELOCAL __ATTR_ARTIFICIAL __fd_t __NOTHROW_RPC(__VLIBCCALL flopen)(char const *__path, __oflag_t __flags, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(flopen))(__path, __flags, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define flopen(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(flopen))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* (__AT_FDCWD && (__CRT_HAVE_flopenat || (__LOCK_EX && (__LOCK_NB || !__O_NONBLOCK) && (__CRT_HAVE_openat64 || __CRT_HAVE_openat) && (__CRT_HAVE_flock || __CRT_HAVE___flock) && ((__CRT_HAVE_kfstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstat || __CRT_HAVE_fstat64 || __CRT_HAVE___fstat64_time64 || __CRT_HAVE__fstat || __CRT_HAVE__fstat32 || __CRT_HAVE__fstati64 || __CRT_HAVE__fstat32i64 || __CRT_HAVE__fstat64 || __CRT_HAVE__fstat64i32) && ((__CRT_HAVE_kfstatat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstatat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstatat || __CRT_HAVE_fstatat64 || __CRT_HAVE___fstatat64_time64) && (__CRT_HAVE_ftruncate64 || __CRT_HAVE__chsize_s || __CRT_HAVE_ftruncate || __CRT_HAVE___ftruncate || __CRT_HAVE___libc_ftruncate || __CRT_HAVE__chsize || __CRT_HAVE_chsize || !__O_TRUNC)))) || (__LOCK_EX && (__LOCK_NB || !__O_NONBLOCK) && (__CRT_HAVE_openat64 || __CRT_HAVE_openat) && (__CRT_HAVE_flock || __CRT_HAVE___flock) && ((__CRT_HAVE_kfstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstat || __CRT_HAVE_fstat64 || __CRT_HAVE___fstat64_time64 || __CRT_HAVE__fstat || __CRT_HAVE__fstat32 || __CRT_HAVE__fstati64 || __CRT_HAVE__fstat32i64 || __CRT_HAVE__fstat64 || __CRT_HAVE__fstat64i32) && ((__AT_FDCWD && ((__CRT_HAVE_kfstatat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstatat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstatat || __CRT_HAVE_fstatat64 || __CRT_HAVE___fstatat64_time64)) || (__CRT_HAVE_kstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kstat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_stat || __CRT_HAVE_stat64 || __CRT_HAVE___stat64_time64 || __CRT_HAVE__stat || __CRT_HAVE__stat32 || __CRT_HAVE__stati64 || __CRT_HAVE__stat32i64 || __CRT_HAVE__stat64 || __CRT_HAVE__stat64i32) && (__CRT_HAVE_ftruncate64 || __CRT_HAVE__chsize_s || __CRT_HAVE_ftruncate || __CRT_HAVE___ftruncate || __CRT_HAVE___libc_ftruncate || __CRT_HAVE__chsize || __CRT_HAVE_chsize || !__O_TRUNC)) */
#endif /* !__CRT_HAVE_flopen */
#ifdef __CRT_HAVE_flopenat
__LIBC __fd_t __NOTHROW_RPC(__VLIBCCALL flopenat)(__fd_t __dirfd, char const *__path, __oflag_t __flags, ...) __CASMNAME_SAME("flopenat");
#else /* __CRT_HAVE_flopenat */
#include <asm/os/fcntl.h>
#include <asm/os/oflags.h>
#include <bits/os/stat.h>
#if defined(__LOCK_EX) && (defined(__LOCK_NB) || !defined(__O_NONBLOCK)) && (defined(__CRT_HAVE_openat64) || defined(__CRT_HAVE_openat)) && (defined(__CRT_HAVE_flock) || defined(__CRT_HAVE___flock)) && ((defined(__CRT_HAVE_kfstat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstat) || defined(__CRT_HAVE_fstat64) || defined(__CRT_HAVE___fstat64_time64) || defined(__CRT_HAVE__fstat) || defined(__CRT_HAVE__fstat32) || defined(__CRT_HAVE__fstati64) || defined(__CRT_HAVE__fstat32i64) || defined(__CRT_HAVE__fstat64) || defined(__CRT_HAVE__fstat64i32)) && ((defined(__CRT_HAVE_kfstatat) && defined(__CRT_KOS_PRIMARY)) || (defined(__CRT_HAVE_kfstatat64) && defined(__CRT_KOS_PRIMARY)) || defined(__CRT_HAVE_fstatat) || defined(__CRT_HAVE_fstatat64) || defined(__CRT_HAVE___fstatat64_time64)) && (defined(__CRT_HAVE_ftruncate64) || defined(__CRT_HAVE__chsize_s) || defined(__CRT_HAVE_ftruncate) || defined(__CRT_HAVE___ftruncate) || defined(__CRT_HAVE___libc_ftruncate) || defined(__CRT_HAVE__chsize) || defined(__CRT_HAVE_chsize) || !defined(__O_TRUNC))
#include <libc/local/bsd.libutil/flopenat.h>
#if defined(__cplusplus) && __has_builtin(__builtin_va_arg_pack)
__NAMESPACE_LOCAL_USING_OR_IMPL(flopenat, __FORCELOCAL __ATTR_ARTIFICIAL __fd_t __NOTHROW_RPC(__VLIBCCALL flopenat)(__fd_t __dirfd, char const *__path, __oflag_t __flags, ...) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(flopenat))(__dirfd, __path, __flags, __builtin_va_arg_pack()); })
#else /* __cplusplus && __has_builtin(__builtin_va_arg_pack) */
#define flopenat(...) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(flopenat))(__VA_ARGS__)
#endif /* !__cplusplus || !__has_builtin(__builtin_va_arg_pack) */
#endif /* __LOCK_EX && (__LOCK_NB || !__O_NONBLOCK) && (__CRT_HAVE_openat64 || __CRT_HAVE_openat) && (__CRT_HAVE_flock || __CRT_HAVE___flock) && ((__CRT_HAVE_kfstat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstat || __CRT_HAVE_fstat64 || __CRT_HAVE___fstat64_time64 || __CRT_HAVE__fstat || __CRT_HAVE__fstat32 || __CRT_HAVE__fstati64 || __CRT_HAVE__fstat32i64 || __CRT_HAVE__fstat64 || __CRT_HAVE__fstat64i32) && ((__CRT_HAVE_kfstatat && __CRT_KOS_PRIMARY) || (__CRT_HAVE_kfstatat64 && __CRT_KOS_PRIMARY) || __CRT_HAVE_fstatat || __CRT_HAVE_fstatat64 || __CRT_HAVE___fstatat64_time64) && (__CRT_HAVE_ftruncate64 || __CRT_HAVE__chsize_s || __CRT_HAVE_ftruncate || __CRT_HAVE___ftruncate || __CRT_HAVE___libc_ftruncate || __CRT_HAVE__chsize || __CRT_HAVE_chsize || !__O_TRUNC) */
#endif /* !__CRT_HAVE_flopenat */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_BSD_LIBUTIL_H */
