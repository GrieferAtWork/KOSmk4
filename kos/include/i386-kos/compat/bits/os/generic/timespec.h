/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _I386_KOS_COMPAT_BITS_OS_GENERIC_TIMESPEC_H
#define _I386_KOS_COMPAT_BITS_OS_GENERIC_TIMESPEC_H 1

#include <hybrid/host.h>

#ifdef __x86_64__
#include <bits/os/generic/timespec32.h>
#define __OFFSET_COMPAT_TIMESPEC32_SEC  __OFFSET_TIMESPECX32_SEC
#define __OFFSET_COMPAT_TIMESPEC32_NSEC __OFFSET_TIMESPECX32_NSEC
#define __SIZEOF_COMPAT_TIMESPEC32      __SIZEOF_TIMESPECX32
#define __ALIGNOF_COMPAT_TIMESPEC32     __ALIGNOF_TIMESPECX32
#define __OFFSET_COMPAT_TIMESPEC64_SEC  __OFFSET_TIMESPECX32_64_SEC
#define __OFFSET_COMPAT_TIMESPEC64_NSEC __OFFSET_TIMESPECX32_64_NSEC
#define __SIZEOF_COMPAT_TIMESPEC64      __SIZEOF_TIMESPECX32_64
#define __ALIGNOF_COMPAT_TIMESPEC64     __ALIGNOF_TIMESPECX32_64
#define compat_timespec32               __timespecx32
#define compat_timespec64               __timespecx32_64
#endif /* __x86_64__ */

#endif /* !_I386_KOS_COMPAT_BITS_OS_GENERIC_TIMESPEC_H */
