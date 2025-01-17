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
#ifndef _COMPAT_KOS_TYPES_H
#define _COMPAT_KOS_TYPES_H 1

#include <__stdinc.h>

#include <compat/config.h>

#ifdef __ARCH_HAVE_COMPAT
#include <hybrid/typecore.h>

#include <compat/bits/types.h>

__DECL_BEGIN

#ifdef __CC__

#ifndef __compat_size_t_defined
#define __compat_size_t_defined
typedef __compat_size_t compat_size_t;
#endif /* !__compat_size_t_defined */

#ifndef __compat_ssize_t_defined
#define __compat_ssize_t_defined
typedef __compat_ssize_t compat_ssize_t;
#endif /* !__compat_ssize_t_defined */

#ifndef __compat_intptr_t_defined
#define __compat_intptr_t_defined
typedef __compat_intptr_t compat_intptr_t;
#endif /* !__compat_intptr_t_defined */

#ifndef __compat_uintptr_t_defined
#define __compat_uintptr_t_defined
typedef __compat_uintptr_t compat_uintptr_t;
#endif /* !__compat_uintptr_t_defined */

#ifndef __compat_longptr_t_defined
#define __compat_longptr_t_defined
typedef __ARCH_COMPAT_LONGPTR_TYPE compat_longptr_t;
#endif /* !__compat_longptr_t_defined */

#ifndef __compat_ulongptr_t_defined
#define __compat_ulongptr_t_defined
typedef __ARCH_COMPAT_ULONGPTR_TYPE compat_ulongptr_t;
#endif /* !__compat_ulongptr_t_defined */

#ifndef __compat_ptrdiff_t_defined
#define __compat_ptrdiff_t_defined
typedef __compat_ptrdiff_t compat_ptrdiff_t;
#endif /* !__compat_ptrdiff_t_defined */

#ifndef __compat_fd_t_defined
#define __compat_fd_t_defined
typedef __compat_fd_t compat_fd_t;
#endif /* !__compat_fd_t_defined */

#ifndef __compat_socklen_t_defined
#define __compat_socklen_t_defined
typedef __compat_socklen_t compat_socklen_t;
#endif /* !__compat_socklen_t_defined */

#ifndef __compat_time32_t_defined
#define __compat_time32_t_defined
typedef __compat_time32_t compat_time32_t;   /* UNIX time in seconds since 01.01.1970 */
#endif /* !__compat_time32_t_defined */

#ifndef __compat_time64_t_defined
#define __compat_time64_t_defined
typedef __compat_time64_t compat_time64_t;   /* UNIX time in seconds since 01.01.1970 */
#endif /* !__compat_time64_t_defined */

#ifndef __compat_dev_t_defined
#define __compat_dev_t_defined
typedef __compat_dev_t compat_dev_t;
#endif /* !__compat_dev_t_defined */

#ifndef __compat_minor_t_defined
#define __compat_minor_t_defined
typedef __compat_minor_t compat_minor_t;
#endif /* !__compat_minor_t_defined */

#ifndef __compat_major_t_defined
#define __compat_major_t_defined
typedef __compat_major_t compat_major_t;
#endif /* !__compat_major_t_defined */

#ifndef __compat_off32_t_defined
#define __compat_off32_t_defined
typedef __compat_off32_t compat_off32_t; /* File/device offset */
#endif /* !__compat_off32_t_defined */

#ifndef __compat_off64_t_defined
#define __compat_off64_t_defined
typedef __compat_off64_t compat_off64_t; /* File/device offset */
#endif /* !__compat_off64_t_defined */

#ifndef __compat_pos32_t_defined
#define __compat_pos32_t_defined
typedef __compat_pos32_t compat_pos32_t; /* File/device position */
#endif /* !__compat_pos32_t_defined */

#ifndef __compat_pos64_t_defined
#define __compat_pos64_t_defined
typedef __compat_pos64_t compat_pos64_t; /* File/device position */
#endif /* !__compat_pos64_t_defined */

#ifndef __compat_ino32_t_defined
#define __compat_ino32_t_defined
typedef __compat_ino32_t compat_ino32_t; /* INode number */
#endif /* !__compat_ino32_t_defined */

#ifndef __compat_ino64_t_defined
#define __compat_ino64_t_defined
typedef __compat_ino64_t compat_ino64_t; /* INode number */
#endif /* !__compat_ino64_t_defined */

#ifndef __compat_oflag_t_defined
#define __compat_oflag_t_defined
typedef __compat_oflag_t compat_oflag_t; /* File-open flags (Set of `O_*'). */
#endif /* !__compat_oflag_t_defined */

#ifndef __compat_mode_t_defined
#define __compat_mode_t_defined
typedef __compat_mode_t compat_mode_t; /* INode type */
#endif /* !__compat_mode_t_defined */

#ifndef __compat_nlink_t_defined
#define __compat_nlink_t_defined
typedef __compat_nlink_t compat_nlink_t; /* INode link counter */
#endif /* !__compat_nlink_t_defined */

#ifndef __compat_uid_t_defined
#define __compat_uid_t_defined
typedef __compat_uid_t compat_uid_t; /* User ID */
#endif /* !__compat_uid_t_defined */

#ifndef __compat_gid_t_defined
#define __compat_gid_t_defined
typedef __compat_gid_t compat_gid_t; /* Group ID */
#endif /* !__compat_gid_t_defined */

#ifndef __compat_syscall_slong_t_defined
#define __compat_syscall_slong_t_defined
typedef __compat_syscall_slong_t compat_syscall_slong_t;
#endif /* !__compat_syscall_slong_t_defined */

#ifndef __compat_syscall_ulong_t_defined
#define __compat_syscall_ulong_t_defined
typedef __compat_syscall_ulong_t compat_syscall_ulong_t;
#endif /* !__compat_syscall_ulong_t_defined */

#ifndef __compat_errno_t_defined
#define __compat_errno_t_defined
typedef __compat_errno_t compat_errno_t;
#endif /* !__compat_errno_t_defined */

#ifndef __compat_signo_t_defined
#define __compat_signo_t_defined
typedef __compat_signo_t compat_signo_t;
#endif /* !__compat_signo_t_defined */

#ifndef __compat_atflag_t_defined
#define __compat_atflag_t_defined
typedef __compat_atflag_t compat_atflag_t;
#endif /* !atcompat_flag_t_defined */

#ifndef __compat_pid_t_defined
#define __compat_pid_t_defined
typedef __compat_pid_t compat_pid_t;
#endif /* !picompat_d_t_defined */

#ifndef __compat_upid_t_defined
#define __compat_upid_t_defined
typedef __compat_upid_t compat_upid_t;
#endif /* !upcompat_id_t_defined */

#ifndef __compat_iomode_t_defined
#define __compat_iomode_t_defined
typedef __compat_iomode_t compat_iomode_t; /* Set of `IO_*' */
#endif /* !__compat_iomode_t_defined */

#ifndef __compat_useconds_t_defined
#define __compat_useconds_t_defined
typedef __compat_useconds_t compat_useconds_t;
#endif /* !__compat_useconds_t_defined */

#ifndef __compat_suseconds_t_defined
#define __compat_suseconds_t_defined
typedef __compat_suseconds_t compat_suseconds_t;
#endif /* !__compat_suseconds_t_defined */

#ifndef __compat_clockid_t_defined
#define __compat_clockid_t_defined
typedef __compat_clockid_t compat_clockid_t;
#endif /* !__compat_clockid_t_defined */

#ifndef __compat_id_t_defined
#define __compat_id_t_defined
typedef __compat_id_t compat_id_t;
#endif /* !__compat_id_t_defined */

#ifndef __compat_clock_t_defined
#define __compat_clock_t_defined
typedef __compat_clock_t compat_clock_t;
#endif /* !__compat_clock_t_defined */

#ifndef __compat_blkcnt32_t_defined
#define __compat_blkcnt32_t_defined
typedef __compat_blkcnt32_t compat_blkcnt32_t;
#endif /* !__compat_blkcnt32_t_defined */

#ifndef __compat_blkcnt64_t_defined
#define __compat_blkcnt64_t_defined
typedef __compat_blkcnt64_t compat_blkcnt64_t;
#endif /* !__compat_blkcnt64_t_defined */

#ifndef __compat_blksize_t_defined
#define __compat_blksize_t_defined
typedef __compat_blksize_t compat_blksize_t;
#endif /* !__compat_blksize_t_defined */

#ifndef __compat_intptr_half_t_defined
#define __compat_intptr_half_t_defined
#if __ARCH_COMPAT_SIZEOF_POINTER == 8
typedef __INT32_TYPE__ compat_intptr_half_t;
#elif __ARCH_COMPAT_SIZEOF_POINTER == 4
typedef __INT16_TYPE__ compat_intptr_half_t;
#elif __ARCH_COMPAT_SIZEOF_POINTER == 2
typedef __INT8_TYPE__ compat_intptr_half_t;
#endif
#endif /* !__compat_intptr_half_t_defined */

#ifndef __compat_uintptr_half_t_defined
#define __compat_uintptr_half_t_defined
#if __ARCH_COMPAT_SIZEOF_POINTER == 8
typedef __UINT32_TYPE__ compat_uintptr_half_t;
#elif __ARCH_COMPAT_SIZEOF_POINTER == 4
typedef __UINT16_TYPE__ compat_uintptr_half_t;
#elif __ARCH_COMPAT_SIZEOF_POINTER == 2
typedef __UINT8_TYPE__ compat_uintptr_half_t;
#endif
#endif /* !__compat_uintptr_half_t_defined */

#ifndef __compat_timer_t_defined
#define __compat_timer_t_defined
typedef __compat_timer_t compat_timer_t;
#endif /* !__compat_timer_t_defined */

#endif /* __CC__ */

__DECL_END
#endif /* __ARCH_HAVE_COMPAT */

#endif /* !_COMPAT_KOS_TYPES_H */
