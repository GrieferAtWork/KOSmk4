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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _ASM_POSIX_TYPES_H
#define _ASM_POSIX_TYPES_H 1

#include <asm/bitsperlong.h>
#include <hybrid/typecore.h>
#include <bits/types.h>

#ifdef __CC__
#ifndef __kernel_long_t
typedef long          __kernel_long_t;
typedef unsigned long __kernel_ulong_t;
#endif
#ifndef __kernel_ino_t
typedef __ino64_t __kernel_ino_t;
#endif
#ifndef __kernel_mode_t
typedef __mode_t __kernel_mode_t;
#endif
#ifndef __kernel_pid_t
typedef __pid_t __kernel_pid_t;
#endif
#ifndef __kernel_ipc_pid_t
typedef __pid_t __kernel_ipc_pid_t;
#endif
#ifndef __kernel_uid_t
typedef __uid_t __kernel_uid_t;
typedef __gid_t __kernel_gid_t;
#endif
#ifndef __kernel_suseconds_t
typedef __suseconds_t __kernel_suseconds_t;
#endif
#ifndef __kernel_daddr_t
typedef __daddr_t __kernel_daddr_t;
#endif
#ifndef __kernel_uid32_t
typedef __UINT32_TYPE__ __kernel_uid32_t;
typedef __UINT32_TYPE__ __kernel_gid32_t;
#endif
#ifndef __kernel_old_uid_t
typedef __kernel_uid_t __kernel_old_uid_t;
typedef __kernel_gid_t __kernel_old_gid_t;
#endif
#ifndef __kernel_old_dev_t
typedef __UINT32_TYPE__ __kernel_old_dev_t;
#endif
#ifndef __kernel_size_t
typedef __SIZE_TYPE__    __kernel_size_t;
typedef __SSIZE_TYPE__   __kernel_ssize_t;
typedef __PTRDIFF_TYPE__ __kernel_ptrdiff_t;
#endif
#ifndef __kernel_fsid_t
typedef __fsid_t __kernel_fsid_t;
#endif

typedef __off64_t __kernel_off_t;
typedef __loff_t __kernel_loff_t;
typedef __time64_t __kernel_time_t;
typedef __clock_t __kernel_clock_t;
typedef __timer_t __kernel_timer_t;
typedef __clockid_t __kernel_clockid_t;
typedef __caddr_t __kernel_caddr_t;
typedef __UINT16_TYPE__ __kernel_uid16_t;
typedef __UINT16_TYPE__ __kernel_gid16_t;
#endif /* __CC__ */

#endif /* !_ASM_POSIX_TYPES_H */
