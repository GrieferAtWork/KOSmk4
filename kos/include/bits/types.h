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
#ifndef _BITS_TYPES_H
#define _BITS_TYPES_H 1

#include <__crt.h>
#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <bits/typesizes.h>

__SYSDECL_BEGIN

#ifndef __SIZEOF_FD_T__
#define __SIZEOF_FD_T__             __SIZEOF_INT__
#endif /* !__SIZEOF_FD_T__ */
#ifndef __SIZEOF_ERRNO_T__
#define __SIZEOF_ERRNO_T__          __SIZEOF_INT__
#endif /* !__SIZEOF_ERRNO_T__ */
#ifndef __SIZEOF_OFLAG_T__
#define __SIZEOF_OFLAG_T__          __SIZEOF_INT__
#endif /* !__SIZEOF_OFLAG_T__ */
#ifndef __SIZEOF_SYSCALL_LONG_T__
#define __SIZEOF_SYSCALL_LONG_T__   __SIZEOF_REGISTER__
#endif /* !__SIZEOF_SYSCALL_LONG_T__ */
#ifndef __SIZEOF_MODE_T__
#define __SIZEOF_MODE_T__           4
#endif /* !__SIZEOF_MODE_T__ */
#ifndef __SIZEOF_ATFLAG_T__
#define __SIZEOF_ATFLAG_T__         __SIZEOF_INT__
#endif /* !__SIZEOF_ATFLAG_T__ */
#ifndef __SIZEOF_IOMODE_T__
#if __SIZEOF_POINTER__ >= 8
#define __SIZEOF_IOMODE_T__         4
#else /* __SIZEOF_POINTER__ >= 8 */
#define __SIZEOF_IOMODE_T__         2
#endif /* __SIZEOF_POINTER__ < 8 */
#endif /* !__SIZEOF_IOMODE_T__ */
#ifndef __SIZEOF_MAJOR_T__
#define __SIZEOF_MAJOR_T__          4
#endif /* !__SIZEOF_MAJOR_T__ */
#ifndef __SIZEOF_MINOR_T__
#define __SIZEOF_MINOR_T__          4
#endif /* !__SIZEOF_MINOR_T__ */
#ifndef __SIZEOF_DEV_T__
#define __SIZEOF_DEV_T__            8
#endif /* !__SIZEOF_DEV_T__ */
#ifndef __SIZEOF_ID_T__
#define __SIZEOF_ID_T__             4
#endif /* !__SIZEOF_ID_T__ */
#ifndef __SIZEOF_PID_T__
#define __SIZEOF_PID_T__            4
#endif /* !__SIZEOF_PID_T__ */
#ifndef __SIZEOF_KEY_T__
#define __SIZEOF_KEY_T__            4
#endif /* !__SIZEOF_KEY_T__ */
#ifndef __SIZEOF_DADDR_T__
#define __SIZEOF_DADDR_T__          4
#endif /* !__SIZEOF_DADDR_T__ */
#ifndef __SIZEOF_CADDR_T__
#define __SIZEOF_CADDR_T__          __SIZEOF_POINTER__
#endif /* !__SIZEOF_CADDR_T__ */
#ifndef __SIZEOF_FSID_T__
#define __SIZEOF_FSID_T__           8
#endif /* !__SIZEOF_FSID_T__ */
#ifndef __SIZEOF_BLKSIZE_T__
#define __SIZEOF_BLKSIZE_T__        __SIZEOF_SYSCALL_LONG_T__
#endif /* !__SIZEOF_BLKSIZE_T__ */
#ifndef __SIZEOF_NLINK_T__
#define __SIZEOF_NLINK_T__          4
#endif /* !__SIZEOF_NLINK_T__ */
#ifndef __SIZEOF_OFF32_T__
#define __SIZEOF_OFF32_T__          4
#endif /* !__SIZEOF_OFF32_T__ */
#ifndef __SIZEOF_OFF64_T__
#define __SIZEOF_OFF64_T__          8
#endif /* !__SIZEOF_OFF64_T__ */
#ifndef __SIZEOF_LOFF_T__
#define __SIZEOF_LOFF_T__           8
#endif /* !__SIZEOF_LOFF_T__ */
#ifndef __SIZEOF_BLKCNT32_T__
#define __SIZEOF_BLKCNT32_T__       4
#endif /* !__SIZEOF_BLKCNT32_T__ */
#ifndef __SIZEOF_BLKCNT64_T__
#define __SIZEOF_BLKCNT64_T__       8
#endif /* !__SIZEOF_BLKCNT64_T__ */
#ifndef __SIZEOF_FSBLKCNT32_T__
#define __SIZEOF_FSBLKCNT32_T__     4
#endif /* !__SIZEOF_FSBLKCNT32_T__ */
#ifndef __SIZEOF_FSBLKCNT64_T__
#define __SIZEOF_FSBLKCNT64_T__     8
#endif /* !__SIZEOF_FSBLKCNT64_T__ */
#ifndef __SIZEOF_FSFILCNT32_T__
#define __SIZEOF_FSFILCNT32_T__     4
#endif /* !__SIZEOF_FSFILCNT32_T__ */
#ifndef __SIZEOF_FSFILCNT64_T__
#define __SIZEOF_FSFILCNT64_T__     8
#endif /* !__SIZEOF_FSFILCNT64_T__ */
#ifndef __SIZEOF_INO32_T__
#define __SIZEOF_INO32_T__          4
#endif /* !__SIZEOF_INO32_T__ */
#ifndef __SIZEOF_INO64_T__
#define __SIZEOF_INO64_T__          8
#endif /* !__SIZEOF_INO64_T__ */
#ifndef __SIZEOF_RLIM32_T__
#define __SIZEOF_RLIM32_T__         4
#endif /* !__SIZEOF_RLIM32_T__ */
#ifndef __SIZEOF_RLIM64_T__
#define __SIZEOF_RLIM64_T__         8
#endif /* !__SIZEOF_RLIM64_T__ */
#ifndef __SIZEOF_TIME32_T__
#define __SIZEOF_TIME32_T__         4
#endif /* !__SIZEOF_TIME32_T__ */
#ifndef __SIZEOF_TIME64_T__
#define __SIZEOF_TIME64_T__         8
#endif /* !__SIZEOF_TIME64_T__ */
#ifndef __SIZEOF_SOCKLEN_T__
#define __SIZEOF_SOCKLEN_T__        __SIZEOF_SIZE_T__
#endif /* !__SIZEOF_SOCKLEN_T__ */
#ifndef __SIZEOF_QUANTUM_DIFF_T__
#define __SIZEOF_QUANTUM_DIFF_T__   4
#endif /* !__SIZEOF_QUANTUM_DIFF_T__ */
#ifndef __SIZEOF_CLOCK_T__
#define __SIZEOF_CLOCK_T__          __SIZEOF_SYSCALL_LONG_T__
#endif /* !__SIZEOF_CLOCK_T__ */
#ifndef __SIZEOF_USECOND_T__
#define __SIZEOF_USECOND_T__        4
#endif /* !__SIZEOF_USECOND_T__ */
#ifndef __SIZEOF_SUSECONDS_T__
#define __SIZEOF_SUSECONDS_T__      __SIZEOF_SYSCALL_LONG_T__
#endif /* !__SIZEOF_SUSECONDS_T__ */
#ifndef __SIZEOF_CLOCKID_T__
#define __SIZEOF_CLOCKID_T__        4
#endif /* !__SIZEOF_CLOCKID_T__ */
#ifndef __SIZEOF_GID_T__
#define __SIZEOF_GID_T__            4
#endif /* !__SIZEOF_GID_T__ */
#ifndef __SIZEOF_UID_T__
#define __SIZEOF_UID_T__            4
#endif /* !__SIZEOF_UID_T__ */
#ifndef __SIZEOF_JTIME_T__
#define __SIZEOF_JTIME_T__          8
#endif /* !__SIZEOF_JTIME_T__ */
#ifndef __SIZEOF_TIMER_T__
#define __SIZEOF_TIMER_T__          __SIZEOF_POINTER__
#endif /* !__SIZEOF_TIMER_T__ */
#ifndef __SIZEOF_FSWORD_T__
#define __SIZEOF_FSWORD_T__         __SIZEOF_SYSCALL_LONG_T__
#endif /* !__SIZEOF_FSWORD_T__ */


#ifdef __CC__
#define __CRT_PRIVATE_SINT_1   __INT8_TYPE__
#define __CRT_PRIVATE_SINT_2   __INT16_TYPE__
#define __CRT_PRIVATE_SINT_4   __INT32_TYPE__
#define __CRT_PRIVATE_UINT_1   __UINT8_TYPE__
#define __CRT_PRIVATE_UINT_2   __UINT16_TYPE__
#define __CRT_PRIVATE_UINT_4   __UINT32_TYPE__
#define __CRT_PRIVATE_SLNG_1   __INT8_TYPE__
#define __CRT_PRIVATE_SLNG_2   __INT16_TYPE__
#define __CRT_PRIVATE_SLNG_4   __LONG32_TYPE__
#define __CRT_PRIVATE_ULNG_1   __UINT8_TYPE__
#define __CRT_PRIVATE_ULNG_2   __UINT16_TYPE__
#define __CRT_PRIVATE_ULNG_4   __ULONG32_TYPE__

#ifdef __UINT64_TYPE__
#define __CRT_PRIVATE_SINT_8   __INT64_TYPE__
#define __CRT_PRIVATE_UINT_8   __UINT64_TYPE__
#define __CRT_PRIVATE_SLNG_8   __LONG64_TYPE__
#define __CRT_PRIVATE_ULNG_8   __ULONG64_TYPE__
#undef  __int64_t
typedef __INT64_TYPE__   __int64_t;
#define __int64_t        __int64_t
#undef  __uint64_t
typedef __UINT64_TYPE__  __uint64_t;
#define __uint64_t       __uint64_t
#else /* __UINT64_TYPE__ */
#undef  __int64_t
typedef struct { __INT32_TYPE__ __lo,__hi; } __int64_t;
#define __int64_t              __int64_t
#undef  __uint64_t
typedef struct { __UINT32_TYPE__ __lo,__hi; } __uint64_t;
#define __uint64_t             __uint64_t
#define __CRT_PRIVATE_SINT_8   __int64_t
#define __CRT_PRIVATE_UINT_8   __uint64_t
#define __CRT_PRIVATE_SLNG_8   __int64_t
#define __CRT_PRIVATE_ULNG_8   __uint64_t
#endif /* !__UINT64_TYPE__ */

#define __CRT_PRIVATE_SINT2(sizeof) __CRT_PRIVATE_SINT_##sizeof
#define __CRT_PRIVATE_UINT2(sizeof) __CRT_PRIVATE_UINT_##sizeof
#define __CRT_PRIVATE_SLNG2(sizeof) __CRT_PRIVATE_SLNG_##sizeof
#define __CRT_PRIVATE_ULNG2(sizeof) __CRT_PRIVATE_ULNG_##sizeof
#define __CRT_PRIVATE_SINT(sizeof)  __CRT_PRIVATE_SINT2(sizeof)
#define __CRT_PRIVATE_UINT(sizeof)  __CRT_PRIVATE_UINT2(sizeof)
#define __CRT_PRIVATE_SLNG(sizeof)  __CRT_PRIVATE_SLNG2(sizeof)
#define __CRT_PRIVATE_ULNG(sizeof)  __CRT_PRIVATE_ULNG2(sizeof)

#ifndef ____s8_defined
#define ____s8_defined 1
typedef __INT8_TYPE__   __s8;
typedef __UINT8_TYPE__  __u8;
typedef __INT16_TYPE__  __s16;
typedef __UINT16_TYPE__ __u16;
typedef __INT32_TYPE__  __s32;
typedef __UINT32_TYPE__ __u32;
#ifdef __INT64_TYPE__
typedef __INT64_TYPE__  __s64;
#endif /* __INT64_TYPE__ */
#ifdef __UINT64_TYPE__
typedef __UINT64_TYPE__ __u64;
#endif /* __UINT64_TYPE__ */
#endif /* !____s8_defined */

/* Special integral types (defined via <hybrid/typecore.h>) */
#undef  __int8_t
typedef __CRT_PRIVATE_SINT_1 __int8_t;
#define __int8_t             __int8_t
#undef  __int16_t
typedef __CRT_PRIVATE_SINT_2 __int16_t;
#define __int16_t            __int16_t
#undef  __int32_t
typedef __CRT_PRIVATE_SINT_4 __int32_t;
#define __int32_t            __int32_t

#undef  __uint8_t
typedef __UINT8_TYPE__   __uint8_t;
#define __uint8_t        __uint8_t
#undef  __uint16_t
typedef __UINT16_TYPE__  __uint16_t;
#define __uint16_t       __uint16_t
#undef  __uint32_t
typedef __UINT32_TYPE__  __uint32_t;
#define __uint32_t       __uint32_t

#undef  __u_char
typedef unsigned char  __u_char;
#define __u_char       __u_char
#undef  __u_short
typedef unsigned short __u_short;
#define __u_short      __u_short
#undef  __u_int
typedef unsigned int   __u_int;
#define __u_int        __u_int
#undef  __u_long
typedef unsigned long  __u_long;
#define __u_long       __u_long

#undef  __ptrdiff_t
typedef __PTRDIFF_TYPE__ __ptrdiff_t;
#define __ptrdiff_t      __ptrdiff_t
#undef  __size_t
typedef __SIZE_TYPE__    __size_t;
#define __size_t         __size_t
#undef  __ssize_t
typedef __SSIZE_TYPE__   __ssize_t;
#define __ssize_t        __ssize_t
#undef  __intptr_t
typedef __INTPTR_TYPE__  __intptr_t;
#define __intptr_t       __intptr_t
#undef  __uintptr_t
typedef __UINTPTR_TYPE__ __uintptr_t;
#define __uintptr_t      __uintptr_t
#undef  __byte_t
typedef __BYTE_TYPE__    __byte_t;
#define __byte_t         __byte_t
#undef  __register_t
typedef __REGISTER_TYPE__  __register_t;
#define __register_t       __register_t
#undef  __sregister_t
typedef __SREGISTER_TYPE__ __sregister_t;
#define __sregister_t      __sregister_t


#undef __quad_t
typedef __CRT_PRIVATE_SLNG_8 __quad_t;
#define __quad_t             __quad_t
#undef __u_quad_t
typedef __CRT_PRIVATE_ULNG_8 __u_quad_t;
#define __u_quad_t           __u_quad_t

#undef  __syscall_slong_t
typedef __CRT_PRIVATE_SLNG(__SIZEOF_SYSCALL_LONG_T__) __syscall_slong_t;
#define __syscall_slong_t       __syscall_slong_t
#undef  __syscall_ulong_t
typedef __CRT_PRIVATE_ULNG(__SIZEOF_SYSCALL_LONG_T__) __syscall_ulong_t;
#define __syscall_ulong_t       __syscall_ulong_t

#undef  __errno_t
typedef __CRT_PRIVATE_SINT(__SIZEOF_ERRNO_T__) __errno_t;
#define __errno_t __errno_t

#undef  __oflag_t
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
typedef __CRT_PRIVATE_UINT(__SIZEOF_OFLAG_T__) __oflag_t;
#else /* __USE_KOS || __USE_KOS_KERNEL */
typedef __CRT_PRIVATE_SINT(__SIZEOF_OFLAG_T__) __oflag_t;
#endif /* !__USE_KOS && !__USE_KOS_KERNEL */
#define __oflag_t       __oflag_t

#undef  __mode_t
#ifdef __CRT_DOS_PRIMARY
typedef __CRT_PRIVATE_SINT(__SIZEOF_MODE_T__) __mode_t; /* Simple enough: DOS defines this one as signed, rather than unsigned. */
#else /* __CRT_DOS_PRIMARY */
typedef __CRT_PRIVATE_UINT(__SIZEOF_MODE_T__) __mode_t;
#endif /* !__CRT_DOS_PRIMARY */
#define __mode_t        __mode_t

#undef __atflag_t
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
typedef __CRT_PRIVATE_UINT(__SIZEOF_ATFLAG_T__) __atflag_t;
#else /* __USE_KOS || __USE_KOS_KERNEL */
typedef __CRT_PRIVATE_SINT(__SIZEOF_ATFLAG_T__) __atflag_t;
#endif /* !__USE_KOS && !__USE_KOS_KERNEL */
#define __atflag_t      __atflag_t

#undef  __iomode_t
typedef __CRT_PRIVATE_UINT(__SIZEOF_IOMODE_T__) __iomode_t;
#define __iomode_t      __iomode_t

#undef  __fd_t
typedef __CRT_PRIVATE_SINT(__SIZEOF_FD_T__) __fd_t;
#define __fd_t          __fd_t
#undef  __ufd_t
typedef __CRT_PRIVATE_UINT(__SIZEOF_FD_T__) __ufd_t;
#define __ufd_t         __ufd_t

#undef  __major_t
typedef __CRT_PRIVATE_UINT(__SIZEOF_MAJOR_T__) __major_t;
#define __major_t       __major_t
#undef  __minor_t
typedef __CRT_PRIVATE_UINT(__SIZEOF_MINOR_T__) __minor_t;
#define __minor_t       __minor_t
#undef  __dev_t
typedef __CRT_PRIVATE_UINT(__SIZEOF_DEV_T__) __dev_t;
#define __dev_t         __dev_t

#undef  __id_t
typedef __CRT_PRIVATE_UINT(__SIZEOF_ID_T__) __id_t;
#define __id_t           __id_t
#undef  __pid_t
typedef __CRT_PRIVATE_SINT(__SIZEOF_PID_T__) __pid_t;
#define __pid_t          __pid_t
#undef  __upid_t
typedef __CRT_PRIVATE_UINT(__SIZEOF_PID_T__) __upid_t;
#define __upid_t         __upid_t
#undef  __key_t
typedef __CRT_PRIVATE_SINT(__SIZEOF_KEY_T__) __key_t;
#define __key_t          __key_t

#undef  __daddr_t
typedef __CRT_PRIVATE_SINT(__SIZEOF_DADDR_T__) __daddr_t;
#define __daddr_t        __daddr_t
#undef  __caddr_t
#if __SIZEOF_CADDR_T__ == __SIZEOF_POINTER__
typedef char            *__caddr_t;
#else
typedef __CRT_PRIVATE_ULNG(__SIZEOF_CADDR_T__) __caddr_t;
#endif
#define __caddr_t        __caddr_t
#undef  __qaddr_t
typedef __quad_t         __qaddr_t;
#define __qaddr_t        __qaddr_t

#undef  __off32_t
typedef __CRT_PRIVATE_SLNG(__SIZEOF_OFF32_T__) __off32_t;
#define __off32_t       __off32_t
#undef  __off64_t
typedef __CRT_PRIVATE_SLNG(__SIZEOF_OFF64_T__) __off64_t;
#define __off64_t       __off64_t
#undef  __blkcnt32_t
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
typedef __CRT_PRIVATE_ULNG(__SIZEOF_BLKCNT32_T__) __blkcnt32_t;
#else /* __USE_KOS || __USE_KOS_KERNEL */
typedef __CRT_PRIVATE_SLNG(__SIZEOF_BLKCNT32_T__) __blkcnt32_t;
#endif /* !__USE_KOS && !__USE_KOS_KERNEL */
#define __blkcnt32_t    __blkcnt32_t
#undef  __blkcnt64_t
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
typedef __CRT_PRIVATE_ULNG(__SIZEOF_BLKCNT64_T__) __blkcnt64_t;
#else /* __USE_KOS || __USE_KOS_KERNEL */
typedef __CRT_PRIVATE_SLNG(__SIZEOF_BLKCNT64_T__) __blkcnt64_t;
#endif /* !__USE_KOS && !__USE_KOS_KERNEL */
#define __blkcnt64_t    __blkcnt64_t
#undef  __fsblkcnt32_t
typedef __CRT_PRIVATE_ULNG(__SIZEOF_FSBLKCNT32_T__) __fsblkcnt32_t;
#define __fsblkcnt32_t   __fsblkcnt32_t
#undef  __fsblkcnt64_t
typedef __CRT_PRIVATE_ULNG(__SIZEOF_FSBLKCNT64_T__) __fsblkcnt64_t;
#define __fsblkcnt64_t   __fsblkcnt64_t
#undef  __fsfilcnt32_t
typedef __CRT_PRIVATE_ULNG(__SIZEOF_FSFILCNT32_T__) __fsfilcnt32_t;
#define __fsfilcnt32_t   __fsfilcnt32_t
#undef  __fsfilcnt64_t
typedef __CRT_PRIVATE_ULNG(__SIZEOF_FSFILCNT64_T__) __fsfilcnt64_t;
#define __fsfilcnt64_t   __fsfilcnt64_t
#undef  __ino32_t
typedef __CRT_PRIVATE_ULNG(__SIZEOF_INO32_T__) __ino32_t;
#define __ino32_t        __ino32_t
#undef  __ino64_t
typedef __CRT_PRIVATE_ULNG(__SIZEOF_INO64_T__) __ino64_t;
#define __ino64_t        __ino64_t
#undef  __pos32_t
typedef __CRT_PRIVATE_ULNG(__SIZEOF_OFF32_T__) __pos32_t;
#define __pos32_t        __pos32_t
#undef  __pos64_t
typedef __CRT_PRIVATE_ULNG(__SIZEOF_OFF64_T__) __pos64_t;
#define __pos64_t        __pos64_t
#undef  __loff_t
typedef __CRT_PRIVATE_SLNG(__SIZEOF_LOFF_T__) __loff_t;
#define __loff_t         __loff_t
#undef  __lpos_t
typedef __CRT_PRIVATE_ULNG(__SIZEOF_LOFF_T__) __lpos_t;
#define __lpos_t         __lpos_t

#undef  __socklen_t
typedef __CRT_PRIVATE_UINT(__SIZEOF_SOCKLEN_T__) __socklen_t;
#define __socklen_t      __socklen_t
#undef  __ssocklen_t
typedef __CRT_PRIVATE_SINT(__SIZEOF_SOCKLEN_T__) __ssocklen_t;
#define __ssocklen_t     __ssocklen_t
#undef  __rlim32_t
typedef __CRT_PRIVATE_UINT(__SIZEOF_RLIM32_T__) __rlim32_t;
#define __rlim32_t       __rlim32_t
#undef  __rlim64_t
typedef __CRT_PRIVATE_UINT(__SIZEOF_RLIM64_T__) __rlim64_t;
#define __rlim64_t       __rlim64_t


#undef  __blksize_t
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
typedef __CRT_PRIVATE_ULNG(__SIZEOF_BLKSIZE_T__) __blksize_t;
#else /* __USE_KOS || __USE_KOS_KERNEL */
typedef __CRT_PRIVATE_SLNG(__SIZEOF_BLKSIZE_T__) __blksize_t;
#endif /* !__USE_KOS && !__USE_KOS_KERNEL */
#define __blksize_t  __blksize_t

#undef  __nlink_t
typedef __CRT_PRIVATE_ULNG(__SIZEOF_NLINK_T__) __nlink_t;
#define __nlink_t    __nlink_t

#undef  __fsid_t
#if __SIZEOF_FSID_T__ == 8
typedef struct { __INT32_TYPE__ __val[2]; } __fsid_t;
#elif __SIZEOF_FSID_T__ == 4
typedef struct { __INT32_TYPE__ __val[1]; } __fsid_t;
#elif __SIZEOF_FSID_T__ == 2
typedef struct { __INT16_TYPE__ __val[1]; } __fsid_t;
#else
typedef struct { __INT8_TYPE__  __val[__SIZEOF_FSID_T__]; } __fsid_t;
#endif
#define __fsid_t __fsid_t


#undef  __time32_t
#ifndef _TIME32_T_DEFINED
#define _TIME32_T_DEFINED 1
typedef __CRT_PRIVATE_SINT(__SIZEOF_TIME32_T__) __time32_t;
#define __time32_t              __time32_t
#else /* !_TIME32_T_DEFINED */
typedef __CRT_PRIVATE_SINT(__SIZEOF_TIME32_T__) __real_time32_t;
#define __time32_t              __real_time32_t
#endif /* _TIME32_T_DEFINED */

#undef  __time64_t
#ifndef _TIME64_T_DEFINED
#define _TIME64_T_DEFINED 1
typedef __CRT_PRIVATE_SINT(__SIZEOF_TIME64_T__) __time64_t;
#define __time64_t              __time64_t
#else /* !_TIME64_T_DEFINED */
typedef __CRT_PRIVATE_SINT(__SIZEOF_TIME64_T__) __real_time64_t;
#define __time64_t              __real_time64_t
#endif /* _TIME64_T_DEFINED */

#undef  __quantum_diff_t
typedef __CRT_PRIVATE_UINT(__SIZEOF_QUANTUM_DIFF_T__) __quantum_diff_t;
#define __quantum_diff_t __quantum_diff_t
#undef  __clock_t
typedef __CRT_PRIVATE_SLNG(__SIZEOF_CLOCK_T__) __clock_t;
#define __clock_t         __clock_t
#undef  __suseconds_t
typedef __CRT_PRIVATE_SLNG(__SIZEOF_SUSECONDS_T__) __suseconds_t;
#define __suseconds_t     __suseconds_t
#undef  __clockid_t
typedef __CRT_PRIVATE_SINT(__SIZEOF_CLOCKID_T__) __clockid_t;
#define __clockid_t       __clockid_t
#undef  __gid_t
typedef __CRT_PRIVATE_UINT(__SIZEOF_GID_T__) __gid_t;
#define __gid_t           __gid_t
#undef  __uid_t
typedef __CRT_PRIVATE_UINT(__SIZEOF_UID_T__) __uid_t;
#define __uid_t           __uid_t
#undef  __useconds_t
typedef __CRT_PRIVATE_UINT(__SIZEOF_USECOND_T__) __useconds_t;
#define __useconds_t      __useconds_t
#undef  __jtime_t
typedef __CRT_PRIVATE_UINT(__SIZEOF_JTIME_T__) __jtime_t;
#define __jtime_t         __jtime_t

#undef  __timer_t
#if __SIZEOF_TIMER_T__ == __SIZEOF_POINTER__
typedef void                   *__timer_t;
#else
typedef __CRT_PRIVATE_ULNG(__SIZEOF_TIMER_T__) __timer_t;
#endif
#define __timer_t    __timer_t

#undef  __fsword_t
typedef __CRT_PRIVATE_SLNG(__SIZEOF_FSWORD_T__) __fsword_t;
#define __fsword_t   __fsword_t

#if 0
#undef __CRT_PRIVATE_ULNG
#undef __CRT_PRIVATE_UINT
#undef __CRT_PRIVATE_SLNG
#undef __CRT_PRIVATE_SINT
#undef __CRT_PRIVATE_ULNG2
#undef __CRT_PRIVATE_UINT2
#undef __CRT_PRIVATE_SLNG2
#undef __CRT_PRIVATE_SINT2
#undef __CRT_PRIVATE_ULNG_8
#undef __CRT_PRIVATE_SLNG_8
#undef __CRT_PRIVATE_UINT_8
#undef __CRT_PRIVATE_SINT_8
#undef __CRT_PRIVATE_ULNG_4
#undef __CRT_PRIVATE_ULNG_2
#undef __CRT_PRIVATE_ULNG_1
#undef __CRT_PRIVATE_SLNG_4
#undef __CRT_PRIVATE_SLNG_2
#undef __CRT_PRIVATE_SLNG_1
#undef __CRT_PRIVATE_UINT_4
#undef __CRT_PRIVATE_UINT_2
#undef __CRT_PRIVATE_UINT_1
#undef __CRT_PRIVATE_SINT_4
#undef __CRT_PRIVATE_SINT_2
#undef __CRT_PRIVATE_SINT_1
#endif

#endif /* __CC__ */


#define __SIZEOF_DOS_DEV_T__   4
#define __dos_dev_t            __UINT32_TYPE__
#define __SIZEOF_DOS_INO_T__   2
#define __dos_ino_t            __UINT16_TYPE__
#define __SIZEOF_DOS_OFF_T__   4
#define __dos_off_t            __INT32_TYPE__
#define __SIZEOF_DOS_CLOCK_T__ 4
#define __dos_clock_t          __LONG32_TYPE__

#ifdef __CRT_DOS_PRIMARY
/* DOS filesystem headers contain different types for these... */
#define __typedef_dev_t            __dos_dev_t
#define __typedef_ino_t            __dos_ino_t
#define __typedef_off_t            __dos_off_t
#define __typedef_clock_t          __dos_clock_t
#define __SIZEOF_TYPEDEF_DEV_T__   __SIZEOF_DOS_DEV_T__
#define __SIZEOF_TYPEDEF_INO_T__   __SIZEOF_DOS_INO_T__
#define __SIZEOF_TYPEDEF_OFF_T__   __SIZEOF_DOS_OFF_T__
#define __SIZEOF_TYPEDEF_CLOCK_T__ __SIZEOF_DOS_CLOCK_T__
#else /* __CRT_DOS_PRIMARY */
#define __typedef_dev_t            __dev_t
#define __typedef_ino_t            __FS_TYPE(ino)
#define __typedef_off_t            __FS_TYPE(off)
#define __typedef_clock_t          __clock_t
#define __SIZEOF_TYPEDEF_DEV_T__   __SIZEOF_DEV_T__
#define __SIZEOF_TYPEDEF_INO_T__   __FS_SIZEOF(INO)
#define __SIZEOF_TYPEDEF_OFF_T__   __FS_SIZEOF(OFF)
#define __SIZEOF_TYPEDEF_CLOCK_T__ __SIZEOF_CLOCK_T__
#endif /* !__CRT_DOS_PRIMARY */

__SYSDECL_END

#endif /* !_BITS_TYPES_H */
