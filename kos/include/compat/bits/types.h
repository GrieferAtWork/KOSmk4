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
#ifndef _COMPAT_BITS_TYPES_H
#define _COMPAT_BITS_TYPES_H 1

#include <__stdinc.h>

#include <compat/config.h>
#ifdef __ARCH_HAVE_COMPAT

#include <features.h>

#include <hybrid/typecore.h>

#include <bits/types.h>
#include <compat/bits/typesizes.h>

__SYSDECL_BEGIN

#ifndef __ARCH_COMPAT_SIZEOF_FD_T
#define __ARCH_COMPAT_SIZEOF_FD_T             __ARCH_COMPAT_SIZEOF_INT
#endif /* !__ARCH_COMPAT_SIZEOF_FD_T */
#ifndef __ARCH_COMPAT_SIZEOF_ERRNO_T
#define __ARCH_COMPAT_SIZEOF_ERRNO_T          __ARCH_COMPAT_SIZEOF_INT
#endif /* !__ARCH_COMPAT_SIZEOF_ERRNO_T */
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
#define __ARCH_COMPAT_SIZEOF_MAJOR_T          4
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
#ifndef __ARCH_COMPAT_SIZEOF_QUANTUM_DIFF_T
#define __ARCH_COMPAT_SIZEOF_QUANTUM_DIFF_T   4
#endif /* !__ARCH_COMPAT_SIZEOF_QUANTUM_DIFF_T */
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
#ifndef __ARCH_COMPAT_SIZEOF_JTIME_T
#define __ARCH_COMPAT_SIZEOF_JTIME_T          8
#endif /* !__ARCH_COMPAT_SIZEOF_JTIME_T */
#ifndef __ARCH_COMPAT_SIZEOF_TIMER_T
#define __ARCH_COMPAT_SIZEOF_TIMER_T          __ARCH_COMPAT_SIZEOF_POINTER
#endif /* !__ARCH_COMPAT_SIZEOF_TIMER_T */
#ifndef __ARCH_COMPAT_SIZEOF_FSWORD_T
#define __ARCH_COMPAT_SIZEOF_FSWORD_T         __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T
#endif /* !__ARCH_COMPAT_SIZEOF_FSWORD_T */


#ifdef __CC__

#undef  __compat_short
typedef __ARCH_COMPAT_SHORT __compat_short;
#define __compat_short      __compat_short

#undef  __compat_u_short
typedef __ARCH_COMPAT_USHORT __compat_u_short;
#define __compat_u_short     __compat_u_short

#undef  __compat_int
typedef __ARCH_COMPAT_INT __compat_int;
#define __compat_int      __compat_int

#undef  __compat_u_int
typedef __ARCH_COMPAT_UINT __compat_u_int;
#define __compat_u_int     __compat_u_int

#undef  __compat_long
typedef __ARCH_COMPAT_LONG __compat_long;
#define __compat_long      __compat_long

#undef  __compat_u_long
typedef __ARCH_COMPAT_ULONG __compat_u_long;
#define __compat_u_long     __compat_u_long

#undef  __compat_ptrdiff_t
typedef __ARCH_COMPAT_PTRDIFF_T __compat_ptrdiff_t;
#define __compat_ptrdiff_t      __compat_ptrdiff_t

#undef  __compat_size_t
typedef __ARCH_COMPAT_SIZE_T __compat_size_t;
#define __compat_size_t      __compat_size_t
#undef  __compat_ssize_t
typedef __ARCH_COMPAT_SSIZE_T __compat_ssize_t;
#define __compat_ssize_t      __compat_ssize_t
#undef  __compat_intptr_t
typedef __ARCH_COMPAT_INTPTR_TYPE __compat_intptr_t;
#define __compat_intptr_t         __compat_intptr_t
#undef  __compat_uintptr_t
typedef __ARCH_COMPAT_UINTPTR_TYPE __compat_uintptr_t;
#define __compat_uintptr_t         __compat_uintptr_t

#undef  __compat_register_t
typedef __ARCH_COMPAT_REGISTER_T __compat_register_t;
#define __compat_register_t      __compat_register_t
#undef  __compat_sregister_t
typedef __ARCH_COMPAT_SREGISTER_T __compat_sregister_t;
#define __compat_sregister_t      __compat_sregister_t


#undef  __compat_syscall_slong_t
typedef __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T) __compat_syscall_slong_t;
#define __compat_syscall_slong_t __compat_syscall_slong_t
#undef  __compat_syscall_ulong_t
typedef __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T) __compat_syscall_ulong_t;
#define __compat_syscall_ulong_t __compat_syscall_ulong_t

#undef  __compat_errno_t
typedef __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_ERRNO_T) __compat_errno_t;
#define __compat_errno_t __compat_errno_t

#undef  __compat_oflag_t
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
typedef __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_OFLAG_T) __compat_oflag_t;
#else /* __USE_KOS || __USE_KOS_KERNEL */
typedef __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_OFLAG_T) __compat_oflag_t;
#endif /* !__USE_KOS && !__USE_KOS_KERNEL */
#define __compat_oflag_t __compat_oflag_t

#undef __compat_mode_t
typedef __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_MODE_T) __compat_mode_t;
#define __compat_mode_t __compat_mode_t

#undef __compat_atflag_t
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
typedef __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_ATFLAG_T) __compat_atflag_t;
#else /* __USE_KOS || __USE_KOS_KERNEL */
typedef __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_ATFLAG_T) __compat_atflag_t;
#endif /* !__USE_KOS && !__USE_KOS_KERNEL */
#define __compat_atflag_t __compat_atflag_t

#undef  __compat_iomode_t
typedef __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_IOMODE_T) __compat_iomode_t;
#define __compat_iomode_t __compat_iomode_t

#undef  __compat_fd_t
typedef __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_FD_T) __compat_fd_t;
#define __compat_fd_t __compat_fd_t
#undef  __compat_ufd_t
typedef __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_FD_T) __compat_ufd_t;
#define __compat_ufd_t __compat_ufd_t

#undef  __compat_major_t
typedef __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_MAJOR_T) __compat_major_t;
#define __compat_major_t __compat_major_t
#undef  __compat_minor_t
typedef __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_MINOR_T) __compat_minor_t;
#define __compat_minor_t __compat_minor_t
#undef  __compat_dev_t
typedef __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_DEV_T) __compat_dev_t;
#define __compat_dev_t __compat_dev_t

#undef  __compat_id_t
typedef __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_ID_T) __compat_id_t;
#define __compat_id_t __compat_id_t
#undef  __compat_pid_t
typedef __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_PID_T) __compat_pid_t;
#define __compat_pid_t __compat_pid_t
#undef  __compat_upid_t
typedef __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_PID_T) __compat_upid_t;
#define __compat_upid_t __compat_upid_t
#undef  __compat_key_t
typedef __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_KEY_T) __compat_key_t;
#define __compat_key_t __compat_key_t

#undef  __compat_daddr_t
typedef __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_DADDR_T) __compat_daddr_t;
#define __compat_daddr_t __compat_daddr_t
#undef  __compat_caddr_t
#if __ARCH_COMPAT_SIZEOF_CADDR_T == __ARCH_COMPAT_SIZEOF_POINTER
typedef __ARCH_COMPAT_PTR(char) __compat_caddr_t;
#else /* __ARCH_COMPAT_SIZEOF_CADDR_T == __ARCH_COMPAT_SIZEOF_POINTER */
typedef __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_CADDR_T) __compat_caddr_t;
#endif /* __ARCH_COMPAT_SIZEOF_CADDR_T != __ARCH_COMPAT_SIZEOF_POINTER */
#define __compat_caddr_t __compat_caddr_t

#undef  __compat_off32_t
typedef __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_OFF32_T) __compat_off32_t;
#define __compat_off32_t __compat_off32_t
#undef  __compat_off64_t
typedef __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_OFF64_T) __compat_off64_t;
#define __compat_off64_t __compat_off64_t
#undef  __compat_blkcnt32_t
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
typedef __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_BLKCNT32_T) __compat_blkcnt32_t;
#else /* __USE_KOS || __USE_KOS_KERNEL */
typedef __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_BLKCNT32_T) __compat_blkcnt32_t;
#endif /* !__USE_KOS && !__USE_KOS_KERNEL */
#define __compat_blkcnt32_t __compat_blkcnt32_t
#undef  __compat_blkcnt64_t
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
typedef __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_BLKCNT64_T) __compat_blkcnt64_t;
#else /* __USE_KOS || __USE_KOS_KERNEL */
typedef __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_BLKCNT64_T) __compat_blkcnt64_t;
#endif /* !__USE_KOS && !__USE_KOS_KERNEL */
#define __compat_blkcnt64_t __compat_blkcnt64_t
#undef  __compat_fsblkcnt32_t
typedef __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_FSBLKCNT32_T) __compat_fsblkcnt32_t;
#define __compat_fsblkcnt32_t __compat_fsblkcnt32_t
#undef  __compat_fsblkcnt64_t
typedef __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_FSBLKCNT64_T) __compat_fsblkcnt64_t;
#define __compat_fsblkcnt64_t __compat_fsblkcnt64_t
#undef  __compat_fsfilcnt32_t
typedef __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_FSFILCNT32_T) __compat_fsfilcnt32_t;
#define __compat_fsfilcnt32_t __compat_fsfilcnt32_t
#undef  __compat_fsfilcnt64_t
typedef __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_FSFILCNT64_T) __compat_fsfilcnt64_t;
#define __compat_fsfilcnt64_t __compat_fsfilcnt64_t
#undef  __compat_ino32_t
typedef __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_INO32_T) __compat_ino32_t;
#define __compat_ino32_t __compat_ino32_t
#undef  __compat_ino64_t
typedef __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_INO64_T) __compat_ino64_t;
#define __compat_ino64_t __compat_ino64_t
#undef  __compat_pos32_t
typedef __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_OFF32_T) __compat_pos32_t;
#define __compat_pos32_t __compat_pos32_t
#undef  __compat_pos64_t
typedef __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_OFF64_T) __compat_pos64_t;
#define __compat_pos64_t __compat_pos64_t
#undef  __compat_loff_t
typedef __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_LOFF_T) __compat_loff_t;
#define __compat_loff_t __compat_loff_t
#undef  __compat_lpos_t
typedef __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_LOFF_T) __compat_lpos_t;
#define __compat_lpos_t __compat_lpos_t

#undef  __compat_socklen_t
typedef __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_SOCKLEN_T) __compat_socklen_t;
#define __compat_socklen_t __compat_socklen_t
#undef  __compat_ssocklen_t
typedef __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_SOCKLEN_T) __compat_ssocklen_t;
#define __compat_ssocklen_t __compat_ssocklen_t
#undef  __compat_rlim32_t
typedef __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_RLIM32_T) __compat_rlim32_t;
#define __compat_rlim32_t __compat_rlim32_t
#undef  __compat_rlim64_t
typedef __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_RLIM64_T) __compat_rlim64_t;
#define __compat_rlim64_t __compat_rlim64_t


#undef  __compat_blksize_t
#if defined(__USE_KOS) || defined(__USE_KOS_KERNEL)
typedef __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_BLKSIZE_T) __compat_blksize_t;
#else /* __USE_KOS || __USE_KOS_KERNEL */
typedef __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_BLKSIZE_T) __compat_blksize_t;
#endif /* !__USE_KOS && !__USE_KOS_KERNEL */
#define __compat_blksize_t  __compat_blksize_t

#undef  __compat_nlink_t
typedef __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_NLINK_T) __compat_nlink_t;
#define __compat_nlink_t __compat_nlink_t

#undef  __compat_fsid_t
#if __ARCH_COMPAT_SIZEOF_FSID_T == 8
typedef struct { __INT32_TYPE__ __val[2]; } __compat_fsid_t;
#elif __ARCH_COMPAT_SIZEOF_FSID_T == 4
typedef struct { __INT32_TYPE__ __val[1]; } __compat_fsid_t;
#elif __ARCH_COMPAT_SIZEOF_FSID_T == 2
typedef struct { __INT16_TYPE__ __val[1]; } __compat_fsid_t;
#else
typedef struct { __INT8_TYPE__  __val[__ARCH_COMPAT_SIZEOF_FSID_T]; } __compat_fsid_t;
#endif
#define __compat_fsid_t __compat_fsid_t


#undef  __compat_time32_t
typedef __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_TIME32_T) __compat_time32_t;
#define __compat_time32_t __compat_time32_t
#undef  __compat_time64_t
typedef __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_TIME64_T) __compat_time64_t;
#define __compat_time64_t __compat_time64_t

#undef  __compat_quantum_diff_t
typedef __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_QUANTUM_DIFF_T) __compat_quantum_diff_t;
#define __compat_quantum_diff_t __compat_quantum_diff_t
#undef  __compat_clock_t
typedef __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_CLOCK_T) __compat_clock_t;
#define __compat_clock_t __compat_clock_t
#undef  __compat_suseconds_t
typedef __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_SUSECONDS_T) __compat_suseconds_t;
#define __compat_suseconds_t __compat_suseconds_t
#undef  __compat_clockid_t
typedef __CRT_PRIVATE_SINT(__ARCH_COMPAT_SIZEOF_CLOCKID_T) __compat_clockid_t;
#define __compat_clockid_t __compat_clockid_t
#undef  __compat_gid_t
typedef __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_GID_T) __compat_gid_t;
#define __compat_gid_t __compat_gid_t
#undef  __compat_uid_t
typedef __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_UID_T) __compat_uid_t;
#define __compat_uid_t __compat_uid_t
#undef  __compat_useconds_t
typedef __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_USECOND_T) __compat_useconds_t;
#define __compat_useconds_t __compat_useconds_t
#undef  __compat_jtime_t
typedef __CRT_PRIVATE_UINT(__ARCH_COMPAT_SIZEOF_JTIME_T) __compat_jtime_t;
#define __compat_jtime_t __compat_jtime_t

#undef  __compat_timer_t
#if __ARCH_COMPAT_SIZEOF_TIMER_T == __ARCH_COMPAT_SIZEOF_POINTER
typedef __ARCH_COMPAT_PTR(void) __compat_timer_t;
#else /* __ARCH_COMPAT_SIZEOF_TIMER_T == __ARCH_COMPAT_SIZEOF_POINTER */
typedef __CRT_PRIVATE_ULNG(__ARCH_COMPAT_SIZEOF_TIMER_T) __compat_timer_t;
#endif /* __ARCH_COMPAT_SIZEOF_TIMER_T != __ARCH_COMPAT_SIZEOF_POINTER */
#define __compat_timer_t __compat_timer_t

#undef  __compat_fsword_t
typedef __CRT_PRIVATE_SLNG(__ARCH_COMPAT_SIZEOF_FSWORD_T) __compat_fsword_t;
#define __compat_fsword_t __compat_fsword_t

#endif /* __CC__ */

__SYSDECL_END
#endif /* __ARCH_HAVE_COMPAT */

#endif /* !_COMPAT_BITS_TYPES_H */
