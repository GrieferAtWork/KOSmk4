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
#ifndef _COMPAT_BITS_TYPESIZES_H
#define _COMPAT_BITS_TYPESIZES_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#include <compat/config.h>

#if 0 /* Available type size overrides */
#define __ARCH_COMPAT_SIZEOF_FD_T           __ARCH_COMPAT_INT
#define __ARCH_COMPAT_SIZEOF_ERRNO_T        __ARCH_COMPAT_INT
#define __ARCH_COMPAT_SIZEOF_SIGNO_T        __ARCH_COMPAT_INT
#define __ARCH_COMPAT_SIZEOF_OFLAG_T        __ARCH_COMPAT_INT
#define __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T __ARCH_COMPAT_SIZEOF_REGISTER
#define __ARCH_COMPAT_SIZEOF_MODE_T         4
#define __ARCH_COMPAT_SIZEOF_ATFLAG_T       __ARCH_COMPAT_INT
#if __ARCH_COMPAT_SIZEOF_POINTER >= 8
#define __ARCH_COMPAT_SIZEOF_IOMODE_T       4
#else /* __ARCH_COMPAT_SIZEOF_POINTER >= 8 */
#define __ARCH_COMPAT_SIZEOF_IOMODE_T       2
#endif /* __ARCH_COMPAT_SIZEOF_POINTER < 8 */
#define __ARCH_COMPAT_SIZEOF_MAJOR_T        4
#define __ARCH_COMPAT_SIZEOF_MINOR_T        4
#define __ARCH_COMPAT_SIZEOF_DEV_T          8
#define __ARCH_COMPAT_SIZEOF_ID_T           4
#define __ARCH_COMPAT_SIZEOF_PID_T          4
#define __ARCH_COMPAT_SIZEOF_KEY_T          4
#define __ARCH_COMPAT_SIZEOF_DADDR_T        4
#define __ARCH_COMPAT_SIZEOF_CADDR_T        __ARCH_COMPAT_SIZEOF_POINTER
#define __ARCH_COMPAT_SIZEOF_FSID_T         8
#define __ARCH_COMPAT_SIZEOF_BLKSIZE_T      __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T
#define __ARCH_COMPAT_SIZEOF_NLINK_T        4
#define __ARCH_COMPAT_SIZEOF_OFF32_T        4
#define __ARCH_COMPAT_SIZEOF_OFF64_T        8
#define __ARCH_COMPAT_SIZEOF_LOFF_T         8
#define __ARCH_COMPAT_SIZEOF_BLKCNT32_T     4
#define __ARCH_COMPAT_SIZEOF_BLKCNT64_T     8
#define __ARCH_COMPAT_SIZEOF_FSBLKCNT32_T   4
#define __ARCH_COMPAT_SIZEOF_FSBLKCNT64_T   8
#define __ARCH_COMPAT_SIZEOF_FSFILCNT32_T   4
#define __ARCH_COMPAT_SIZEOF_FSFILCNT64_T   8
#define __ARCH_COMPAT_SIZEOF_INO32_T        4
#define __ARCH_COMPAT_SIZEOF_INO64_T        8
#define __ARCH_COMPAT_SIZEOF_RLIM32_T       4
#define __ARCH_COMPAT_SIZEOF_RLIM64_T       8
#define __ARCH_COMPAT_SIZEOF_TIME32_T       4
#define __ARCH_COMPAT_SIZEOF_TIME64_T       8
#define __ARCH_COMPAT_SIZEOF_SOCKLEN_T      __ARCH_COMPAT_SIZEOF_SIZE_T
#define __ARCH_COMPAT_SIZEOF_CLOCK_T        __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T
#define __ARCH_COMPAT_SIZEOF_USECOND_T      4
#define __ARCH_COMPAT_SIZEOF_SUSECONDS_T    __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T
#define __ARCH_COMPAT_SIZEOF_CLOCKID_T      4
#define __ARCH_COMPAT_SIZEOF_GID_T          4
#define __ARCH_COMPAT_SIZEOF_UID_T          4
#define __ARCH_COMPAT_SIZEOF_TIMER_T        __ARCH_COMPAT_SIZEOF_POINTER
#define __ARCH_COMPAT_SIZEOF_FSWORD_T       __ARCH_COMPAT_SIZEOF_SYSCALL_LONG_T
#endif

#endif /* !_COMPAT_BITS_TYPESIZES_H */
