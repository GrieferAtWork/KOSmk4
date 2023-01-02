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
#ifndef _COMPAT_BITS_TYPES_H
#define _COMPAT_BITS_TYPES_H 1

#include <__stdinc.h>

#include <compat/config.h>
#ifdef __ARCH_HAVE_COMPAT

#include <features.h>

#include <hybrid/typecore.h>

#include <bits/types.h>
#include <compat/bits/typesizes.h>

__DECL_BEGIN

/* Substitute missing values from <compat/config.h> */
#ifndef __ARCH_COMPAT_SIZEOF_POINTER
#define __ARCH_COMPAT_SIZEOF_POINTER __SIZEOF_POINTER__
#endif /* !__ARCH_COMPAT_SIZEOF_POINTER */
#ifndef __ARCH_COMPAT_SIZEOF_SIZE_T
#define __ARCH_COMPAT_SIZEOF_SIZE_T __ARCH_COMPAT_SIZEOF_POINTER
#endif /* !__ARCH_COMPAT_SIZEOF_SIZE_T */
#ifndef __ARCH_COMPAT_SIZEOF_REGISTER
#define __ARCH_COMPAT_SIZEOF_REGISTER __ARCH_COMPAT_SIZEOF_POINTER
#endif /* !__ARCH_COMPAT_SIZEOF_REGISTER */
#ifndef __ARCH_COMPAT_SREGISTER
#define __ARCH_COMPAT_SREGISTER __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_REGISTER)
#endif /* !__ARCH_COMPAT_SREGISTER */
#ifndef __ARCH_COMPAT_REGISTER
#define __ARCH_COMPAT_REGISTER __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_REGISTER)
#endif /* !__ARCH_COMPAT_REGISTER */

#ifndef __ARCH_COMPAT_SIZEOF_SHORT
#define __ARCH_COMPAT_SIZEOF_SHORT __SIZEOF_SHORT__
#endif /* !__ARCH_COMPAT_SIZEOF_SHORT */
#ifndef __ARCH_COMPAT_SHORT
#define __ARCH_COMPAT_SHORT __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_SHORT)
#endif /* !__ARCH_COMPAT_SHORT */
#ifndef __ARCH_COMPAT_USHORT
#define __ARCH_COMPAT_USHORT __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_SHORT)
#endif /* !__ARCH_COMPAT_USHORT */

#ifndef __ARCH_COMPAT_SIZEOF_INT
#define __ARCH_COMPAT_SIZEOF_INT __SIZEOF_INT__
#endif /* !__ARCH_COMPAT_SIZEOF_INT */
#ifndef __ARCH_COMPAT_INT
#define __ARCH_COMPAT_INT __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_INT)
#endif /* !__ARCH_COMPAT_INT */
#ifndef __ARCH_COMPAT_UINT
#define __ARCH_COMPAT_UINT __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_INT)
#endif /* !__ARCH_COMPAT_UINT */

#ifndef __ARCH_COMPAT_SIZEOF_LONG
#define __ARCH_COMPAT_SIZEOF_LONG __SIZEOF_LONG__
#endif /* !__ARCH_COMPAT_SIZEOF_LONG */
#ifndef __ARCH_COMPAT_LONG
#define __ARCH_COMPAT_LONG __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_LONG)
#endif /* !__ARCH_COMPAT_LONG */
#ifndef __ARCH_COMPAT_ULONG
#define __ARCH_COMPAT_ULONG __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_LONG)
#endif /* !__ARCH_COMPAT_ULONG */

#ifndef __ARCH_COMPAT_SIZEOF_LLONG
#ifdef __SIZEOF_LONG_LONG__
#define __ARCH_COMPAT_SIZEOF_LLONG __SIZEOF_LONG_LONG__
#endif /* __SIZEOF_LONG_LONG__ */
#endif /* !__ARCH_COMPAT_SIZEOF_LLONG */
#ifndef __ARCH_COMPAT_LLONG
#ifdef __ARCH_COMPAT_SIZEOF_LLONG
#define __ARCH_COMPAT_LLONG __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_LLONG)
#endif /* __ARCH_COMPAT_SIZEOF_LLONG */
#endif /* !__ARCH_COMPAT_LLONG */
#ifndef __ARCH_COMPAT_ULLONG
#ifdef __ARCH_COMPAT_SIZEOF_LLONG
#define __ARCH_COMPAT_ULLONG __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_LLONG)
#endif /* __ARCH_COMPAT_SIZEOF_LLONG */
#endif /* !__ARCH_COMPAT_ULLONG */



/* Substitute missing values from <compat/bits/typesizes.h> */
#ifndef __ARCH_COMPAT_SIZEOF_FD_T
#define __ARCH_COMPAT_SIZEOF_FD_T             __ARCH_COMPAT_SIZEOF_INT
#endif /* !__ARCH_COMPAT_SIZEOF_FD_T */
#ifndef __ARCH_COMPAT_SIZEOF_ERRNO_T
#define __ARCH_COMPAT_SIZEOF_ERRNO_T          __ARCH_COMPAT_SIZEOF_INT
#endif /* !__ARCH_COMPAT_SIZEOF_ERRNO_T */
#ifndef __ARCH_COMPAT_SIZEOF_SIGNO_T
#define __ARCH_COMPAT_SIZEOF_SIGNO_T          __ARCH_COMPAT_SIZEOF_INT
#endif /* !__ARCH_COMPAT_SIZEOF_SIGNO_T */
#ifndef __ARCH_COMPAT_SIZEOF_OFLAG_T
#define __ARCH_COMPAT_SIZEOF_OFLAG_T          __ARCH_COMPAT_SIZEOF_INT
#endif /* !__ARCH_COMPAT_SIZEOF_OFLAG_T */
#ifndef __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T
#define __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T   __ARCH_COMPAT_SIZEOF_REGISTER
#endif /* !__ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T */
#ifndef __ARCH_COMPAT_SIZEOF_MODE_T
#define __ARCH_COMPAT_SIZEOF_MODE_T           4
#endif /* !__ARCH_COMPAT_SIZEOF_MODE_T */
#ifndef __ARCH_COMPAT_SIZEOF_ATFLAG_T
#define __ARCH_COMPAT_SIZEOF_ATFLAG_T         __ARCH_COMPAT_SIZEOF_INT
#endif /* !__ARCH_COMPAT_SIZEOF_ATFLAG_T */
#ifndef __ARCH_COMPAT_SIZEOF_IOMODE_T
#if __ARCH_COMPAT_SIZEOF_POINTER >= 8
#define __ARCH_COMPAT_SIZEOF_IOMODE_T         4
#else /* __ARCH_COMPAT_SIZEOF_POINTER >= 8 */
#define __ARCH_COMPAT_SIZEOF_IOMODE_T         2
#endif /* __ARCH_COMPAT_SIZEOF_POINTER < 8 */
#endif /* !__ARCH_COMPAT_SIZEOF_IOMODE_T */
#ifndef __ARCH_COMPAT_SIZEOF_MAJOR_T
#define __ARCH_COMPAT_SIZEOF_MAJOR_T          8
#endif /* !__ARCH_COMPAT_SIZEOF_MAJOR_T */
#ifndef __ARCH_COMPAT_SIZEOF_MINOR_T
#define __ARCH_COMPAT_SIZEOF_MINOR_T          4
#endif /* !__ARCH_COMPAT_SIZEOF_MINOR_T */
#ifndef __ARCH_COMPAT_SIZEOF_DEV_T
#define __ARCH_COMPAT_SIZEOF_DEV_T            8
#endif /* !__ARCH_COMPAT_SIZEOF_DEV_T */
#ifndef __ARCH_COMPAT_SIZEOF_ID_T
#define __ARCH_COMPAT_SIZEOF_ID_T             4
#endif /* !__ARCH_COMPAT_SIZEOF_ID_T */
#ifndef __ARCH_COMPAT_SIZEOF_PID_T
#define __ARCH_COMPAT_SIZEOF_PID_T            4
#endif /* !__ARCH_COMPAT_SIZEOF_PID_T */
#ifndef __ARCH_COMPAT_SIZEOF_KEY_T
#define __ARCH_COMPAT_SIZEOF_KEY_T            4
#endif /* !__ARCH_COMPAT_SIZEOF_KEY_T */
#ifndef __ARCH_COMPAT_SIZEOF_DADDR_T
#define __ARCH_COMPAT_SIZEOF_DADDR_T          4
#endif /* !__ARCH_COMPAT_SIZEOF_DADDR_T */
#ifndef __ARCH_COMPAT_SIZEOF_CADDR_T
#define __ARCH_COMPAT_SIZEOF_CADDR_T          __ARCH_COMPAT_SIZEOF_POINTER
#endif /* !__ARCH_COMPAT_SIZEOF_CADDR_T */
#ifndef __ARCH_COMPAT_SIZEOF_FSID_T
#define __ARCH_COMPAT_SIZEOF_FSID_T           8
#endif /* !__ARCH_COMPAT_SIZEOF_FSID_T */
#ifndef __ARCH_COMPAT_SIZEOF_BLKSIZE_T
#define __ARCH_COMPAT_SIZEOF_BLKSIZE_T        __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T
#endif /* !__ARCH_COMPAT_SIZEOF_BLKSIZE_T */
#ifndef __ARCH_COMPAT_SIZEOF_NLINK_T
#define __ARCH_COMPAT_SIZEOF_NLINK_T          4
#endif /* !__ARCH_COMPAT_SIZEOF_NLINK_T */
#ifndef __ARCH_COMPAT_SIZEOF_OFF32_T
#define __ARCH_COMPAT_SIZEOF_OFF32_T          4
#endif /* !__ARCH_COMPAT_SIZEOF_OFF32_T */
#ifndef __ARCH_COMPAT_SIZEOF_OFF64_T
#define __ARCH_COMPAT_SIZEOF_OFF64_T          8
#endif /* !__ARCH_COMPAT_SIZEOF_OFF64_T */
#ifndef __ARCH_COMPAT_SIZEOF_LOFF_T
#define __ARCH_COMPAT_SIZEOF_LOFF_T           8
#endif /* !__ARCH_COMPAT_SIZEOF_LOFF_T */
#ifndef __ARCH_COMPAT_SIZEOF_BLKCNT32_T
#define __ARCH_COMPAT_SIZEOF_BLKCNT32_T       4
#endif /* !__ARCH_COMPAT_SIZEOF_BLKCNT32_T */
#ifndef __ARCH_COMPAT_SIZEOF_BLKCNT64_T
#define __ARCH_COMPAT_SIZEOF_BLKCNT64_T       8
#endif /* !__ARCH_COMPAT_SIZEOF_BLKCNT64_T */
#ifndef __ARCH_COMPAT_SIZEOF_FSBLKCNT32_T
#define __ARCH_COMPAT_SIZEOF_FSBLKCNT32_T     4
#endif /* !__ARCH_COMPAT_SIZEOF_FSBLKCNT32_T */
#ifndef __ARCH_COMPAT_SIZEOF_FSBLKCNT64_T
#define __ARCH_COMPAT_SIZEOF_FSBLKCNT64_T     8
#endif /* !__ARCH_COMPAT_SIZEOF_FSBLKCNT64_T */
#ifndef __ARCH_COMPAT_SIZEOF_FSFILCNT32_T
#define __ARCH_COMPAT_SIZEOF_FSFILCNT32_T     4
#endif /* !__ARCH_COMPAT_SIZEOF_FSFILCNT32_T */
#ifndef __ARCH_COMPAT_SIZEOF_FSFILCNT64_T
#define __ARCH_COMPAT_SIZEOF_FSFILCNT64_T     8
#endif /* !__ARCH_COMPAT_SIZEOF_FSFILCNT64_T */
#ifndef __ARCH_COMPAT_SIZEOF_INO32_T
#define __ARCH_COMPAT_SIZEOF_INO32_T          4
#endif /* !__ARCH_COMPAT_SIZEOF_INO32_T */
#ifndef __ARCH_COMPAT_SIZEOF_INO64_T
#define __ARCH_COMPAT_SIZEOF_INO64_T          8
#endif /* !__ARCH_COMPAT_SIZEOF_INO64_T */
#ifndef __ARCH_COMPAT_SIZEOF_RLIM32_T
#define __ARCH_COMPAT_SIZEOF_RLIM32_T         4
#endif /* !__ARCH_COMPAT_SIZEOF_RLIM32_T */
#ifndef __ARCH_COMPAT_SIZEOF_RLIM64_T
#define __ARCH_COMPAT_SIZEOF_RLIM64_T         8
#endif /* !__ARCH_COMPAT_SIZEOF_RLIM64_T */
#ifndef __ARCH_COMPAT_SIZEOF_TIME32_T
#define __ARCH_COMPAT_SIZEOF_TIME32_T         4
#endif /* !__ARCH_COMPAT_SIZEOF_TIME32_T */
#ifndef __ARCH_COMPAT_SIZEOF_TIME64_T
#define __ARCH_COMPAT_SIZEOF_TIME64_T         8
#endif /* !__ARCH_COMPAT_SIZEOF_TIME64_T */
#ifndef __ARCH_COMPAT_SIZEOF_SOCKLEN_T
#define __ARCH_COMPAT_SIZEOF_SOCKLEN_T        __ARCH_COMPAT_SIZEOF_SIZE_T
#endif /* !__ARCH_COMPAT_SIZEOF_SOCKLEN_T */
#ifndef __ARCH_COMPAT_SIZEOF_CLOCK_T
#define __ARCH_COMPAT_SIZEOF_CLOCK_T          __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T
#endif /* !__ARCH_COMPAT_SIZEOF_CLOCK_T */
#ifndef __ARCH_COMPAT_SIZEOF_USECOND_T
#define __ARCH_COMPAT_SIZEOF_USECOND_T        4
#endif /* !__ARCH_COMPAT_SIZEOF_USECOND_T */
#ifndef __ARCH_COMPAT_SIZEOF_SUSECONDS_T
#define __ARCH_COMPAT_SIZEOF_SUSECONDS_T      __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T
#endif /* !__ARCH_COMPAT_SIZEOF_SUSECONDS_T */
#ifndef __ARCH_COMPAT_SIZEOF_CLOCKID_T
#define __ARCH_COMPAT_SIZEOF_CLOCKID_T        4
#endif /* !__ARCH_COMPAT_SIZEOF_CLOCKID_T */
#ifndef __ARCH_COMPAT_SIZEOF_GID_T
#define __ARCH_COMPAT_SIZEOF_GID_T            4
#endif /* !__ARCH_COMPAT_SIZEOF_GID_T */
#ifndef __ARCH_COMPAT_SIZEOF_UID_T
#define __ARCH_COMPAT_SIZEOF_UID_T            4
#endif /* !__ARCH_COMPAT_SIZEOF_UID_T */
#ifndef __ARCH_COMPAT_SIZEOF_TIMER_T
#define __ARCH_COMPAT_SIZEOF_TIMER_T          __ARCH_COMPAT_SIZEOF_POINTER
#endif /* !__ARCH_COMPAT_SIZEOF_TIMER_T */
#ifndef __ARCH_COMPAT_SIZEOF_FSWORD_T
#define __ARCH_COMPAT_SIZEOF_FSWORD_T         __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T
#endif /* !__ARCH_COMPAT_SIZEOF_FSWORD_T */

#ifdef __CC__


#define __compat_short           __ARCH_COMPAT_SHORT
#define __compat_u_short         __ARCH_COMPAT_USHORT
#define __compat_int             __ARCH_COMPAT_INT
#define __compat_u_int           __ARCH_COMPAT_UINT
#define __compat_long            __ARCH_COMPAT_LONG
#define __compat_u_long          __ARCH_COMPAT_ULONG
#define __compat_ptrdiff_t       __ARCH_COMPAT_PTRDIFF_T
#define __compat_size_t          __ARCH_COMPAT_SIZE_T
#define __compat_ssize_t         __ARCH_COMPAT_SSIZE_T
#define __compat_intptr_t        __ARCH_COMPAT_INTPTR_TYPE
#define __compat_uintptr_t       __ARCH_COMPAT_UINTPTR_TYPE
#define __compat_register_t      __ARCH_COMPAT_REGISTER_T
#define __compat_sregister_t     __ARCH_COMPAT_SREGISTER_T
#define __compat_syscall_slong_t __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T)
#define __compat_syscall_ulong_t __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T)
#define __compat_errno_t         __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_ERRNO_T)
#define __compat_signo_t         __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_SIGNO_T)
#define __compat_mode_t          __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_MODE_T)
#define __compat_iomode_t        __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_IOMODE_T)
#define __compat_fd_t            __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_FD_T)
#define __compat_ufd_t           __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_FD_T)
#define __compat_major_t         __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_MAJOR_T)
#define __compat_minor_t         __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_MINOR_T)
#define __compat_dev_t           __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_DEV_T)
#define __compat_id_t            __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_ID_T)
#define __compat_pid_t           __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_PID_T)
#define __compat_upid_t          __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_PID_T)
#define __compat_key_t           __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_KEY_T)
#define __compat_daddr_t         __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_DADDR_T)
#define __compat_off32_t         __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_OFF32_T)
#define __compat_off64_t         __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_OFF64_T)
#define __compat_fsblkcnt32_t    __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_FSBLKCNT32_T)
#define __compat_fsblkcnt64_t    __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_FSBLKCNT64_T)
#define __compat_fsfilcnt32_t    __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_FSFILCNT32_T)
#define __compat_fsfilcnt64_t    __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_FSFILCNT64_T)
#define __compat_ino32_t         __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_INO32_T)
#define __compat_ino64_t         __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_INO64_T)
#define __compat_pos32_t         __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_OFF32_T)
#define __compat_pos64_t         __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_OFF64_T)
#define __compat_loff_t          __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_LOFF_T)
#define __compat_lpos_t          __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_LOFF_T)
#define __compat_socklen_t       __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_SOCKLEN_T)
#define __compat_ssocklen_t      __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_SOCKLEN_T)
#define __compat_rlim32_t        __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_RLIM32_T)
#define __compat_rlim64_t        __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_RLIM64_T)
#define __compat_nlink_t         __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_NLINK_T)
#define __compat_time32_t        __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_TIME32_T)
#define __compat_time64_t        __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_TIME64_T)
#define __compat_clock_t         __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_CLOCK_T)
#define __compat_suseconds_t     __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_SUSECONDS_T)
#define __compat_clockid_t       __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_CLOCKID_T)
#define __compat_gid_t           __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_GID_T)
#define __compat_uid_t           __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_UID_T)
#define __compat_useconds_t      __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_USECOND_T)
#define __compat_fsword_t        __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_FSWORD_T)

#ifdef __USE_KOS_ALTERATIONS
#define __compat_oflag_t    __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_OFLAG_T)
#define __compat_atflag_t   __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_ATFLAG_T)
#define __compat_blkcnt32_t __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_BLKCNT32_T)
#define __compat_blkcnt64_t __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_BLKCNT64_T)
#define __compat_blksize_t  __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_BLKSIZE_T)
#else /* __USE_KOS_ALTERATIONS */
#define __compat_oflag_t    __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_OFLAG_T)
#define __compat_atflag_t   __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_ATFLAG_T)
#define __compat_blkcnt32_t __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_BLKCNT32_T)
#define __compat_blkcnt64_t __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_BLKCNT64_T)
#define __compat_blksize_t  __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_BLKSIZE_T)
#endif /* !__USE_KOS_ALTERATIONS */

#if __ARCH_COMPAT_SIZEOF_CADDR_T == __ARCH_COMPAT_SIZEOF_POINTER
#define __compat_caddr_t __ARCH_COMPAT_PTR(char)
#else /* __ARCH_COMPAT_SIZEOF_CADDR_T == __ARCH_COMPAT_SIZEOF_POINTER */
#define __compat_caddr_t __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_CADDR_T)
#endif /* __ARCH_COMPAT_SIZEOF_CADDR_T != __ARCH_COMPAT_SIZEOF_POINTER */

#if __ARCH_COMPAT_SIZEOF_FSID_T == 8
typedef struct { __INT32_TYPE__ __val[2]; } __compat_fsid_t;
#elif __ARCH_COMPAT_SIZEOF_FSID_T == 4
typedef struct { __INT32_TYPE__ __val[1]; } __compat_fsid_t;
#elif __ARCH_COMPAT_SIZEOF_FSID_T == 2
typedef struct { __INT16_TYPE__ __val[1]; } __compat_fsid_t;
#else /* __ARCH_COMPAT_SIZEOF_FSID_T == ... */
typedef struct { __INT8_TYPE__  __val[__ARCH_COMPAT_SIZEOF_FSID_T]; } __compat_fsid_t;
#endif /* __ARCH_COMPAT_SIZEOF_FSID_T != ... */
#define __compat_fsid_t __compat_fsid_t

#if __ARCH_COMPAT_SIZEOF_TIMER_T == __ARCH_COMPAT_SIZEOF_POINTER
#define __compat_timer_t __ARCH_COMPAT_PTR(void)
#else /* __ARCH_COMPAT_SIZEOF_TIMER_T == __ARCH_COMPAT_SIZEOF_POINTER */
#define __compat_timer_t __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_TIMER_T)
#endif /* __ARCH_COMPAT_SIZEOF_TIMER_T != __ARCH_COMPAT_SIZEOF_POINTER */
#endif /* __CC__ */

__DECL_END
#endif /* __ARCH_HAVE_COMPAT */

#endif /* !_COMPAT_BITS_TYPES_H */
