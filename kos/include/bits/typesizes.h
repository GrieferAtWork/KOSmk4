/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
/* (#) Portability: GNU C Library (/bits/typesizes.h) */
#ifndef _BITS_TYPESIZES_H
#define _BITS_TYPESIZES_H 1

#include <__stdinc.h>

#include <hybrid/typecore.h>

#if 0 /* Available type size overrides */
#define __SIZEOF_FD_T__             __SIZEOF_INT__
#define __SIZEOF_ERRNO_T__          __SIZEOF_INT__
#define __SIZEOF_SIGNO_T__          __SIZEOF_INT__
#define __SIZEOF_OFLAG_T__          __SIZEOF_INT__
#define __SIZEOF_SYSCALL_LONG_T__   __SIZEOF_REGISTER__
#define __SIZEOF_MODE_T__           4
#define __SIZEOF_ATFLAG_T__         __SIZEOF_INT__
#if __SIZEOF_POINTER__ >= 8
#define __SIZEOF_IOMODE_T__         4
#else /* __SIZEOF_POINTER__ >= 8 */
#define __SIZEOF_IOMODE_T__         2
#endif /* __SIZEOF_POINTER__ < 8 */
#define __SIZEOF_MAJOR_T__          4
#define __SIZEOF_MINOR_T__          4
#define __SIZEOF_DEV_T__            8
#define __SIZEOF_ID_T__             4
#define __SIZEOF_PID_T__            4
#define __SIZEOF_KEY_T__            4
#define __SIZEOF_DADDR_T__          4
#define __SIZEOF_CADDR_T__          __SIZEOF_POINTER__
#define __SIZEOF_FSID_T__           8
#define __SIZEOF_BLKSIZE_T__        __SIZEOF_SYSCALL_LONG_T__
#define __SIZEOF_NLINK_T__          4
#define __SIZEOF_OFF32_T__          4
#define __SIZEOF_OFF64_T__          8
#define __SIZEOF_LOFF_T__           8
#define __SIZEOF_BLKCNT32_T__       4
#define __SIZEOF_BLKCNT64_T__       8
#define __SIZEOF_FSBLKCNT32_T__     4
#define __SIZEOF_FSBLKCNT64_T__     8
#define __SIZEOF_FSFILCNT32_T__     4
#define __SIZEOF_FSFILCNT64_T__     8
#define __SIZEOF_INO32_T__          4
#define __SIZEOF_INO64_T__          8
#define __SIZEOF_RLIM32_T__         4
#define __SIZEOF_RLIM64_T__         8
#define __SIZEOF_TIME32_T__         4
#define __SIZEOF_TIME64_T__         8
#define __SIZEOF_SOCKLEN_T__        __SIZEOF_SIZE_T__
#define __SIZEOF_QUANTUM_DIFF_T__   4
#define __SIZEOF_CLOCK_T__          __SIZEOF_SYSCALL_LONG_T__
#define __SIZEOF_USECONDS_T__       4
#define __SIZEOF_SUSECONDS_T__      __SIZEOF_SYSCALL_LONG_T__
#define __SIZEOF_CLOCKID_T__        4
#define __SIZEOF_GID_T__            4
#define __SIZEOF_UID_T__            4
#define __SIZEOF_TIMER_T__          __SIZEOF_POINTER__
#define __SIZEOF_FSWORD_T__         __SIZEOF_SYSCALL_LONG_T__
#define __SIZEOF_PHYSADDR_T__       __SIZEOF_POINTER__
#define __SIZEOF_PHYSPAGE_T__       __SIZEOF_POINTER__
#define __SIZEOF_SA_FAMILY_T__      2
#endif

#endif /* !_BITS_TYPESIZES_H */
