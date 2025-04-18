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
/* (#) Portability: Linux (/usr/include/linux/posix_types.h) */
/*!always_includes <linux/bits/posix_types.h>*/
#ifndef _LINUX_POSIX_TYPES_H
#define _LINUX_POSIX_TYPES_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <asm/os/fd_set.h> /* __FD_SETSIZE */
#include <bits/types.h>
#include <linux/bits/posix_types.h>

#include "stddef.h"

/* NOTE: This stuff isn't actually used by the KOS  kernel,
 *       which uses the same structures/types as userspace. */

#ifndef __BITS_PER_LONG
#include <hybrid/typecore.h>
#define __BITS_PER_LONG __INTPTR_WIDTH__
#endif /* !__BITS_PER_LONG */

#ifdef __CC__
__DECL_BEGIN

#ifndef __kernel_long_t
#define __kernel_long_t __LONGPTR_TYPE__
#endif /* !__kernel_long_t */
#ifndef __kernel_ulong_t
#define __kernel_ulong_t __ULONGPTR_TYPE__
#endif /* !__kernel_ulong_t */
#ifndef __kernel_ino_t
#define __kernel_ino_t __ino64_t
#endif /* !__kernel_ino_t */
#ifndef __kernel_mode_t
#define __kernel_mode_t __mode_t
#endif /* !__kernel_mode_t */
#ifndef __kernel_pid_t
#define __kernel_pid_t __pid_t
#endif /* !__kernel_pid_t */
#ifndef __kernel_ipc_pid_t
#define __kernel_ipc_pid_t __pid_t
#endif /* !__kernel_ipc_pid_t */
#ifndef __kernel_uid_t
#define __kernel_uid_t __uid_t
#define __kernel_gid_t __gid_t
#endif /* !__kernel_uid_t */
#ifndef __kernel_suseconds_t
#define __kernel_suseconds_t __suseconds_t
#endif /* !__kernel_suseconds_t */
#ifndef __kernel_daddr_t
#define __kernel_daddr_t __daddr_t
#endif /* !__kernel_daddr_t */
#ifndef __kernel_uid32_t
#define __kernel_uid32_t __UINT32_TYPE__
#endif /* !__kernel_uid32_t */
#ifndef __kernel_gid32_t
#define __kernel_gid32_t __UINT32_TYPE__
#endif /* !__kernel_gid32_t */
#ifndef __kernel_old_uid_t
#define __kernel_old_uid_t __kernel_uid_t
#endif /* !__kernel_old_uid_t */
#ifndef __kernel_old_gid_t
#define __kernel_old_gid_t __kernel_gid_t
#endif /* !__kernel_old_gid_t */
#ifndef __kernel_old_dev_t
#define __kernel_old_dev_t __UINT32_TYPE__
#endif /* !__kernel_old_dev_t */
#ifndef __kernel_size_t
typedef __SIZE_TYPE__ __kernel_size_t;
#define __kernel_size_t __kernel_size_t
#endif /* !__kernel_size_t */
#ifndef __kernel_ssize_t
typedef __SSIZE_TYPE__ __kernel_ssize_t;
#define __kernel_ssize_t __kernel_ssize_t
#endif /* !__kernel_ssize_t */
#ifndef __kernel_ptrdiff_t
#define __kernel_ptrdiff_t __PTRDIFF_TYPE__
#endif /* !__kernel_ptrdiff_t */
#ifndef __kernel_fsid_t
#define __kernel_fsid_t __fsid_t
#endif /* !__kernel_fsid_t */

#ifndef __kernel_off_t
#define __kernel_off_t __off64_t
#endif /* !__kernel_off_t */
#ifndef __kernel_loff_t
#define __kernel_loff_t __loff_t
#endif /* !__kernel_loff_t */
#ifndef __kernel_time_t
#define __kernel_time_t __time64_t
#endif /* !__kernel_time_t */
#ifndef __kernel_clock_t
#define __kernel_clock_t __clock_t
#endif /* !__kernel_clock_t */
#ifndef __kernel_timer_t
#define __kernel_timer_t __timer_t
#endif /* !__kernel_timer_t */
#ifndef __kernel_clockid_t
#define __kernel_clockid_t __clockid_t
#endif /* !__kernel_clockid_t */
#ifndef __kernel_caddr_t
#define __kernel_caddr_t __caddr_t
#endif /* !__kernel_caddr_t */
#ifndef __kernel_uid16_t
#define __kernel_uid16_t __UINT16_TYPE__
#endif /* !__kernel_uid16_t */
#ifndef __kernel_gid16_t
#define __kernel_gid16_t __UINT16_TYPE__
#endif /* !__kernel_gid16_t */

#ifndef __kernel_old_time_t
#define __kernel_old_time_t __time32_t
#endif /* !__kernel_old_time_t */
#ifndef __kernel_time64_t
#define __kernel_time64_t __time64_t
#endif /* !__kernel_time64_t */


typedef struct {
	__ULONGPTR_TYPE__ fds_bits[__FD_SETSIZE / (8 * sizeof(__ULONGPTR_TYPE__))];
} __kernel_fd_set;

typedef void (*__kernel_sighandler_t)(int);
#define __kernel_key_t int
#define __kernel_mqd_t int

__DECL_END
#endif /* __CC__ */


#endif /* !_LINUX_POSIX_TYPES_H */
