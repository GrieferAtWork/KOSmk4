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
#ifndef _COMPAT_BITS_OS_GENERIC_TIMEVAL_H
#define _COMPAT_BITS_OS_GENERIC_TIMEVAL_H 1

#include <compat/config.h>
#ifdef __ARCH_HAVE_COMPAT
#include <bits/os/timeval.h>
#define __OFFSET_COMPAT_TIMEVAL32_SEC  __OFFSET_TIMEVAL32_SEC
#define __OFFSET_COMPAT_TIMEVAL32_USEC __OFFSET_TIMEVAL32_USEC
#define __SIZEOF_COMPAT_TIMEVAL32      __SIZEOF_TIMEVAL32
#define __ALIGNOF_COMPAT_TIMEVAL32     __ALIGNOF_TIMEVAL32
#define __OFFSET_COMPAT_TIMEVAL64_SEC  __OFFSET_TIMEVAL64_SEC
#define __OFFSET_COMPAT_TIMEVAL64_USEC __OFFSET_TIMEVAL64_USEC
#define __SIZEOF_COMPAT_TIMEVAL64      __SIZEOF_TIMEVAL64
#define __ALIGNOF_COMPAT_TIMEVAL64     __ALIGNOF_TIMEVAL64
#define compat_timeval32               __timeval32
#define compat_timeval64               __timeval64
#endif /* __ARCH_HAVE_COMPAT */

#endif /* !_COMPAT_BITS_OS_GENERIC_TIMEVAL_H */
