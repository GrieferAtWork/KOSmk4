/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _KOS_TYPES_H
#define _KOS_TYPES_H 1

#include <__stdinc.h>
#include <features.h>
#include <bits/types.h>

__DECL_BEGIN

#ifdef __CC__

#ifndef __int8_t_defined
#define __int8_t_defined 1
typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
#ifdef __INT64_TYPE__
typedef __int64_t int64_t;
#endif /* __INT64_TYPE__ */
#endif /* !__int8_t_defined */

#ifndef __uint8_t_defined
#define __uint8_t_defined 1
typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
#ifdef __INT64_TYPE__
typedef __uint64_t uint64_t;
#endif /* __INT64_TYPE__ */
#endif /* !__uint8_t_defined */

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __ssize_t_defined
#define __ssize_t_defined 1
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

#ifndef __intptr_t_defined
#define __intptr_t_defined 1
typedef __intptr_t intptr_t;
#endif /* !__intptr_t_defined */

#ifndef __uintptr_t_defined
#define __uintptr_t_defined 1
typedef __uintptr_t uintptr_t;
#endif /* !__uintptr_t_defined */

#ifndef __ptrdiff_t_defined
#define __ptrdiff_t_defined 1
typedef __ptrdiff_t ptrdiff_t;
#endif /* !__ptrdiff_t_defined */

#ifndef __byte_t_defined
#define __byte_t_defined 1
typedef __byte_t byte_t;
#endif /* !__byte_t_defined */

#ifndef __fd_t_defined
#define __fd_t_defined 1
typedef __fd_t fd_t;
#endif /* !__fd_t_defined */

#ifndef __socklen_t_defined
#define __socklen_t_defined 1
typedef __socklen_t socklen_t;
#endif /* !__socklen_t_defined */

#ifndef __time_t_defined
#define __time_t_defined 1
typedef __TM_TYPE(time) time_t; /* UNIX time in seconds since 01.01.1970 */
#endif /* !__time_t_defined */

#ifndef __time32_t_defined
#define __time32_t_defined 1
typedef __time32_t time32_t;   /* UNIX time in seconds since 01.01.1970 */
#endif /* !__time32_t_defined */

#ifndef __time64_t_defined
#define __time64_t_defined 1
typedef __time64_t time64_t;   /* UNIX time in seconds since 01.01.1970 */
#endif /* !__time64_t_defined */

#ifndef __dev_t_defined
#define __dev_t_defined 1
#if defined(__KERNEL__) && defined(ALTERNATIVE_TYPE)
typedef ALTERNATIVE_TYPE(__typedef_dev_t) dev_t;
#else
typedef __typedef_dev_t dev_t;
#endif
#endif /* !__dev_t_defined */

#ifndef __minor_t_defined
#define __minor_t_defined 1
typedef __minor_t minor_t;
#endif /* !__minor_t_defined */

#ifndef __major_t_defined
#define __major_t_defined 1
typedef __major_t major_t;
#endif /* !__major_t_defined */

#ifndef __off_t_defined
#define __off_t_defined 1
#if defined(__KERNEL__) && defined(ALTERNATIVE_TYPE)
typedef ALTERNATIVE_TYPE(__FS_TYPE(off)) off_t; /* File/device offset */
#else
typedef __FS_TYPE(off) off_t;                   /* File/device offset */
#endif
#endif /* !__off_t_defined */

#ifndef __pos_t_defined
#define __pos_t_defined 1
#if defined(__KERNEL__) && defined(ALTERNATIVE_TYPE)
typedef ALTERNATIVE_TYPE(__FS_TYPE(pos)) pos_t; /* File/device position */
#else
typedef __FS_TYPE(pos) pos_t;                   /* File/device position */
#endif
#endif /* !__pos_t_defined */

#ifndef __ino_t_defined
#define __ino_t_defined 1
#if defined(__KERNEL__) && defined(ALTERNATIVE_TYPE)
typedef ALTERNATIVE_TYPE(__FS_TYPE(ino)) ino_t; /* INode number */
#else
typedef __FS_TYPE(ino) ino_t;                   /* INode number */
#endif
#endif /* !__ino_t_defined */

#ifndef __off32_t_defined
#define __off32_t_defined 1
#if defined(__KERNEL__) && defined(ALTERNATIVE_TYPE)
typedef ALTERNATIVE_TYPE(__off32_t) off32_t; /* File/device offset */
#else
typedef __off32_t off32_t;                   /* File/device offset */
#endif
#endif /* !__off32_t_defined */
#ifndef __off64_t_defined
#define __off64_t_defined 1
#if defined(__KERNEL__) && defined(ALTERNATIVE_TYPE)
typedef off_t     off64_t;                   /* File/device offset */
#else
typedef __off64_t off64_t;                   /* File/device offset */
#endif
#endif /* !__off64_t_defined */

#ifndef __pos32_t_defined
#define __pos32_t_defined 1
#if defined(__KERNEL__) && defined(ALTERNATIVE_TYPE)
typedef ALTERNATIVE_TYPE(__pos32_t) pos32_t; /* File/device position */
#else
typedef __pos32_t pos32_t;                   /* File/device position */
#endif
#endif /* !__pos32_t_defined */
#ifndef __pos64_t_defined
#define __pos64_t_defined 1
#if defined(__KERNEL__) && defined(ALTERNATIVE_TYPE)
typedef pos_t     pos64_t;                   /* File/device position */
#else
typedef __pos64_t pos64_t;                   /* File/device position */
#endif
#endif /* !__pos64_t_defined */

#ifndef __ino32_t_defined
#define __ino32_t_defined 1
#if defined(__KERNEL__) && defined(ALTERNATIVE_TYPE)
typedef ALTERNATIVE_TYPE(__ino32_t) ino32_t; /* INode number */
#else
typedef __ino32_t ino32_t;                   /* INode number */
#endif
#endif /* !__ino32_t_defined */
#ifndef __ino64_t_defined
#define __ino64_t_defined 1
#if defined(__KERNEL__) && defined(ALTERNATIVE_TYPE)
typedef ino_t     ino64_t;                   /* INode number */
#else
typedef __ino64_t ino64_t;                   /* INode number */
#endif
#endif /* !__ino64_t_defined */

#ifndef __oflag_t_defined
#define __oflag_t_defined 1
typedef __oflag_t oflag_t; /* File-open flags (Set of `O_*'). */
#endif /* !__oflag_t_defined */

#ifndef __mode_t_defined
#define __mode_t_defined 1
typedef __mode_t mode_t; /* INode type */
#endif /* !__mode_t_defined */

#ifndef __nlink_t_defined
#define __nlink_t_defined 1
#if defined(__KERNEL__) && defined(ALTERNATIVE_TYPE)
typedef ALTERNATIVE_TYPE(__nlink_t) nlink_t; /* File-open flags (Set of `O_*'). */
#else
typedef __nlink_t nlink_t;                   /* INode link counter */
#endif
#endif /* !__nlink_t_defined */

#ifndef __uid_t_defined
#define __uid_t_defined 1
#if defined(__KERNEL__) && defined(ALTERNATIVE_TYPE)
typedef ALTERNATIVE_TYPE(__uid_t) uid_t; /* User ID */
#else
typedef __uid_t uid_t;                   /* User ID */
#endif
#endif /* !__uid_t_defined */

#ifndef __gid_t_defined
#define __gid_t_defined 1
#if defined(__KERNEL__) && defined(ALTERNATIVE_TYPE)
typedef ALTERNATIVE_TYPE(__gid_t) gid_t; /* Group ID */
#else
typedef __gid_t gid_t;                   /* Group ID */
#endif
#endif /* !__gid_t_defined */

#ifndef __char16_t_defined
#define __char16_t_defined 1
typedef __CHAR16_TYPE__ char16_t;
typedef __CHAR32_TYPE__ char32_t;
#endif /* !__char16_t_defined */

#ifndef __syscall_slong_t_defined
#define __syscall_slong_t_defined 1
typedef __syscall_slong_t syscall_slong_t;
#endif /* !__syscall_slong_t_defined */

#ifndef __syscall_ulong_t_defined
#define __syscall_ulong_t_defined 1
typedef __syscall_ulong_t syscall_ulong_t;
#endif /* !__syscall_ulong_t_defined */

#ifndef __errno_t_defined
#define __errno_t_defined 1
typedef __errno_t errno_t;
#endif /* !errno_t_defined */

#ifndef __atflag_t_defined
#define __atflag_t_defined 1
typedef __atflag_t atflag_t;
#endif /* !atflag_t_defined */

#ifndef __pid_t_defined
#define __pid_t_defined 1
typedef __pid_t pid_t;
#endif /* !pid_t_defined */

#ifndef __upid_t_defined
#define __upid_t_defined 1
typedef __upid_t upid_t;
#endif /* !upid_t_defined */

#ifndef __iomode_t_defined
#define __iomode_t_defined 1
typedef __iomode_t iomode_t;
#endif /* !__iomode_t_defined */

#ifndef __useconds_t_defined
#define __useconds_t_defined 1
typedef __useconds_t useconds_t;
#endif /* !__useconds_t_defined */

#ifndef __suseconds_t_defined
#define __suseconds_t_defined 1
typedef __suseconds_t suseconds_t;
#endif /* !__suseconds_t_defined */

#ifndef __clockid_t_defined
#define __clockid_t_defined 1
typedef __clockid_t clockid_t;
#endif /* !__clockid_t_defined */

#ifndef __id_t_defined
#define __id_t_defined 1
typedef __id_t id_t;
#endif /* !__id_t_defined */

#ifndef __clock_t_defined
#define __clock_t_defined 1
typedef __typedef_clock_t clock_t;
#endif /* !__clock_t_defined */

#ifndef __blkcnt_t_defined
#define __blkcnt_t_defined 1
typedef __FS_TYPE(blkcnt) blkcnt_t;
#endif /* !__blkcnt_t_defined */
#ifndef __blkcnt32_t_defined
#define __blkcnt32_t_defined 1
typedef __blkcnt32_t blkcnt32_t;
#endif /* !__blkcnt32_t_defined */
#ifndef __blkcnt64_t_defined
#define __blkcnt64_t_defined 1
typedef __blkcnt64_t blkcnt64_t;
#endif /* !__blkcnt64_t_defined */
#ifndef __blksize_t_defined
#define __blksize_t_defined 1
typedef __blksize_t blksize_t;
#endif /* !__blksize_t_defined */

#ifndef __idtype_t_defined
#define __idtype_t_defined 1
typedef int idtype_t;
#endif /* !__idtype_t_defined */

#ifndef __intptr_half_t_defined
#define __intptr_half_t_defined 1
typedef __INTPTR_HALF_TYPE__ intptr_half_t;
#endif /* !__intptr_half_t_defined */

#ifndef __uintptr_half_t_defined
#define __uintptr_half_t_defined 1
typedef __UINTPTR_HALF_TYPE__ uintptr_half_t;
#endif /* !__uintptr_half_t_defined */

#ifndef __timer_t_defined
#define __timer_t_defined 1
typedef __timer_t timer_t;
#endif /* !__timer_t_defined */

#endif /* __CC__ */

__DECL_END

#endif /* !_KOS_TYPES_H */
