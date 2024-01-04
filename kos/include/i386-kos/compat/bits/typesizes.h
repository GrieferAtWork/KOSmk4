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
#ifndef _I386_KOS_COMPAT_BITS_TYPESIZES_H
#define _I386_KOS_COMPAT_BITS_TYPESIZES_H 1

#include <__stdinc.h>

#include <hybrid/host.h>

#ifdef __x86_64__
/* Override: Due to historical reasons, sizeof(socklen_t) == sizeof(int) */
#define __ARCH_COMPAT_SIZEOF_SOCKLEN_T    4
#define __ARCH_COMPAT_SIZEOF_OFF32_T      4
#define __ARCH_COMPAT_SIZEOF_BLKCNT32_T   4
#define __ARCH_COMPAT_SIZEOF_FSBLKCNT32_T 4
#define __ARCH_COMPAT_SIZEOF_FSFILCNT32_T 4
#define __ARCH_COMPAT_SIZEOF_INO32_T      4
#define __ARCH_COMPAT_SIZEOF_RLIM32_T     4
#define __ARCH_COMPAT_SIZEOF_TIME32_T     4
#define __ARCH_COMPAT_SIZEOF_USECOND_T    4
#define __ARCH_COMPAT_SIZEOF_SUSECONDS_T  4
#define __ARCH_COMPAT_SIZEOF_CLOCKID_T    4
#define __ARCH_COMPAT_SIZEOF_CLOCK_T      4
#define __ARCH_COMPAT_SIZEOF_IOMODE_T     2
#endif /* __x86_64__ */

#endif /* !_I386_KOS_COMPAT_BITS_TYPESIZES_H */
