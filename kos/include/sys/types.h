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
/* (>) Standard: POSIX.1 (Issue 1, IEEE Std 1003.1-1988) */
/* (#) Portability: Cygwin        (/newlib/libc/include/sys/types.h) */
/* (#) Portability: DJGPP         (/include/sys/types.h) */
/* (#) Portability: DragonFly BSD (/sys/sys/types.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/sys/types.h) */
/* (#) Portability: FreeBSD       (/sys/sys/types.h) */
/* (#) Portability: GNU C Library (/posix/sys/types.h) */
/* (#) Portability: MSVC          (/include/sys/types.h) */
/* (#) Portability: MinGW         (/mingw-w64-headers/crt/sys/types.h) */
/* (#) Portability: NetBSD        (/sys/sys/types.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/sys/types.h) */
/* (#) Portability: OpenBSD       (/sys/sys/types.h) */
/* (#) Portability: OpenSolaris   (/usr/src/uts/common/sys/types.h) */
/* (#) Portability: Windows Kits  (/ucrt/sys/types.h) */
/* (#) Portability: avr-libc      (/include/sys/types.h) */
/* (#) Portability: diet libc     (/include/sys/types.h) */
/* (#) Portability: libc4/5       (/include/sys/types.h) */
/* (#) Portability: libcmini      (/include/sys/types.h) */
/* (#) Portability: mintlib       (/include/sys/types.h) */
/* (#) Portability: musl libc     (/include/sys/types.h) */
/* (#) Portability: uClibc        (/include/sys/types.h) */
#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H 1

#include <__stdinc.h>
#include <features.h>

#include <bits/types.h>

#ifdef __USE_MISC
#include <sys/select.h>
#include <sys/sysmacros.h>

#include <endian.h>
#endif /* __USE_MISC */

#if defined(__USE_POSIX199506) || defined(__USE_UNIX98)
#include <bits/crt/pthreadtypes.h>
#endif /* __USE_POSIX199506 || __USE_UNIX98 */

#ifdef __CC__
__DECL_BEGIN

#ifdef __USE_KOS
#ifndef __byte_t_defined
#define __byte_t_defined
typedef __byte_t byte_t;
#endif /* !__byte_t_defined */
#endif /* __USE_KOS */

#ifdef __USE_MISC
#ifndef __u_char_defined
#define __u_char_defined
typedef __u_char   u_char;
typedef __u_short  u_short;
typedef __u_int    u_int;
typedef __u_long   u_long;
#endif /* !__u_char_defined */

#ifndef __quad_t_defined
#define __quad_t_defined
typedef __quad_t   quad_t;
typedef __u_quad_t u_quad_t;
#endif /* !__quad_t_defined */

#ifndef __fsid_t_defined
#define __fsid_t_defined
typedef __fsid_t   fsid_t;
#endif /* !__fsid_t_defined */

#ifndef __daddr_t_defined
#define __daddr_t_defined
typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;
#endif /* !__daddr_t_defined */

#ifndef __ulong_defined
#define __ulong_defined
typedef unsigned long int  ulong;
typedef unsigned short int ushort;
typedef unsigned int       uint;
#endif /* !__ulong_defined */

#endif /* __USE_MISC */

#ifndef __loff_t_defined
#define __loff_t_defined
typedef __loff_t loff_t; /* Large file/device offset */
#endif /* !__loff_t_defined */

#ifndef __ino_t_defined
#define __ino_t_defined
typedef __ino_t ino_t;  /* INode number */
#endif /* !__ino_t_defined */

#ifdef __USE_LARGEFILE64
#ifndef __ino64_t_defined
#define __ino64_t_defined
typedef __ino64_t ino64_t;
#endif /* !__ino64_t_defined */

#ifndef __off64_t_defined
#define __off64_t_defined
typedef __off64_t off64_t;
#endif /* !__off64_t_defined */
#endif /* __USE_LARGEFILE64 */

#ifndef __dev_t_defined
#define __dev_t_defined
typedef __dev_t dev_t;
#endif /* !__dev_t_defined */

#ifndef __gid_t_defined
#define __gid_t_defined
typedef __gid_t gid_t;
#endif /* !__gid_t_defined */

#ifndef __mode_t_defined
#define __mode_t_defined
typedef __mode_t mode_t; /* INode type (Set of `S_*' from `<fcntl.h>' or `<sys/stat.h>') */
#endif /* !__mode_t_defined */

#ifndef __nlink_t_defined
#define __nlink_t_defined
typedef __nlink_t nlink_t;
#endif /* !__nlink_t_defined */

#ifndef __uid_t_defined
#define __uid_t_defined
typedef __uid_t uid_t;
#endif /* !__uid_t_defined */

#ifndef __off_t_defined
#define __off_t_defined
typedef __off_t off_t;
#endif /* !__off_t_defined */

#ifndef __pid_t_defined
#define __pid_t_defined
typedef __pid_t pid_t;
#endif /* !__pid_t_defined */

#if defined(__USE_XOPEN) || defined(__USE_XOPEN2K8)
#ifndef __id_t_defined
#define __id_t_defined
typedef __id_t id_t;
#endif /* !__id_t_defined */

#ifndef __clock_t_defined
#define __clock_t_defined
typedef __clock_t clock_t;
#endif /* !__clock_t_defined */
#endif /* __USE_XOPEN || __USE_XOPEN2K8 */

#ifndef __ssize_t_defined
#define __ssize_t_defined
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

#if defined (__USE_MISC) || defined(__USE_XOPEN)
#ifndef __key_t_defined
#define __key_t_defined
typedef __key_t key_t;
#endif /* !__key_t_defined */
#endif /* __USE_MISC || __USE_XOPEN */

#ifndef __time_t_defined
#define __time_t_defined
typedef __time_t time_t;
#endif /* !__time_t_defined */

#ifndef __clockid_t_defined
#define __clockid_t_defined
typedef __clockid_t clockid_t;
#endif /* !__clockid_t_defined */

#ifndef __timer_t_defined
#define __timer_t_defined
typedef __timer_t timer_t;
#endif /* !__timer_t_defined */

#ifdef __USE_XOPEN
#ifndef __useconds_t_defined
#define __useconds_t_defined
typedef __useconds_t useconds_t;
#endif /* !__useconds_t_defined */

#ifndef __suseconds_t_defined
#define __suseconds_t_defined
typedef __suseconds_t suseconds_t;
#endif /* !__suseconds_t_defined */
#endif /* !__USE_XOPEN */

#ifndef __size_t_defined
#define __size_t_defined
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

#ifndef __BIT_TYPES_DEFINED__
#define __BIT_TYPES_DEFINED__ 1 /* Keep this macro! Some programs test for it. */
#ifndef __int8_t_defined
#define __int8_t_defined
#ifdef __INT8_TYPE__
typedef __INT8_TYPE__ int8_t;
#endif /* __INT8_TYPE__ */
#ifdef __INT16_TYPE__
typedef __INT16_TYPE__ int16_t;
#endif /* __INT16_TYPE__ */
#ifdef __INT32_TYPE__
typedef __INT32_TYPE__ int32_t;
#endif /* __INT32_TYPE__ */
#ifdef __INT64_TYPE__
typedef __INT64_TYPE__ int64_t;
#endif /* __INT64_TYPE__ */
#endif /* __int8_t_defined */

#ifndef __uint8_t_defined
#define __uint8_t_defined
#ifdef __UINT8_TYPE__
typedef __UINT8_TYPE__ uint8_t;
#endif /* __UINT8_TYPE__ */
#ifdef __UINT16_TYPE__
typedef __UINT16_TYPE__ uint16_t;
#endif /* __UINT16_TYPE__ */
#ifdef __UINT32_TYPE__
typedef __UINT32_TYPE__ uint32_t;
#endif /* __UINT32_TYPE__ */
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ uint64_t;
#endif /* __UINT64_TYPE__ */
#endif /* !__uint8_t_defined */

#ifndef __u_int8_t_defined
#define __u_int8_t_defined
#ifdef __UINT8_TYPE__
typedef __UINT8_TYPE__ u_int8_t;
#endif /* __UINT8_TYPE__ */
#ifdef __UINT16_TYPE__
typedef __UINT16_TYPE__ u_int16_t;
#endif /* __UINT16_TYPE__ */
#ifdef __UINT32_TYPE__
typedef __UINT32_TYPE__ u_int32_t;
#endif /* __UINT32_TYPE__ */
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ u_int64_t;
#endif /* __UINT64_TYPE__ */
#endif /* !__u_int8_t_defined */

#ifndef __register_t_defined
#define __register_t_defined
typedef __sregister_t register_t; /* This one's signed in GLIBc, so we make it such, too. */
#endif /* !__register_t_defined */
#endif /* !__BIT_TYPES_DEFINED__ */

#if defined(__USE_UNIX98) || defined(__USE_XOPEN2K8)
#ifndef __blksize_t_defined
#define __blksize_t_defined
typedef __blksize_t blksize_t;
#endif /* !__blksize_t_defined */
#endif /* __USE_UNIX98 || __USE_XOPEN2K8 */

#ifndef __blkcnt_t_defined
#define __blkcnt_t_defined
typedef __blkcnt_t blkcnt_t;
#endif /* !__blkcnt_t_defined */

#ifndef __fsblkcnt_t_defined
#define __fsblkcnt_t_defined
typedef __fsblkcnt_t fsblkcnt_t;
#endif /* !__fsblkcnt_t_defined */

#ifndef __fsfilcnt_t_defined
#define __fsfilcnt_t_defined
typedef __fsfilcnt_t fsfilcnt_t;
#endif /* !__fsfilcnt_t_defined */

#ifdef __USE_LARGEFILE64
#ifndef __blkcnt64_t_defined
#define __blkcnt64_t_defined
typedef __blkcnt64_t blkcnt64_t;
#endif /* !__blkcnt64_t_defined */

#ifndef __fsblkcnt64_t_defined
#define __fsblkcnt64_t_defined
typedef __fsblkcnt64_t fsblkcnt64_t;
#endif /* !__fsblkcnt64_t_defined */

#ifndef __fsfilcnt64_t_defined
#define __fsfilcnt64_t_defined
typedef __fsfilcnt64_t fsfilcnt64_t;
#endif /* !__fsfilcnt64_t_defined */
#endif /* !__USE_LARGEFILE64 */

#ifdef __USE_DOS
/* Define ~~"aliases"~~ used by DOS. */
#ifndef _INO_T_DEFINED
#define _INO_T_DEFINED 1
typedef __ino_t _ino_t;
#endif /* !_INO_T_DEFINED */

#ifndef _DEV_T_DEFINED
#define _DEV_T_DEFINED 1
typedef __dev_t _dev_t;
#endif /* !_DEV_T_DEFINED */

#ifndef _OFF_T_DEFINED
#define _OFF_T_DEFINED 1
typedef __off_t _off_t;
#endif /* !_OFF_T_DEFINED */
#endif /* __USE_DOS */

__DECL_END
#endif /* __CC__ */

#endif /* !_SYS_TYPES_H */
