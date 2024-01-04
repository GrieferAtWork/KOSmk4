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
#ifndef _I386_KOS_COMPAT_BITS_OS_KOS_STATFS_CONVERT_H
#define _I386_KOS_COMPAT_BITS_OS_KOS_STATFS_CONVERT_H 1

#include <hybrid/host.h> /* __x86_64__ */
#ifdef __x86_64__
#include <bits/os/kos/statfs-convert.h>
#define compat_statfs32_to_statfs   statfsx32_to_statfs32
#define compat_statfs64_to_statfs   statfsx32_64_to_statfs32
#define compat_statfs32_to_statfs32 statfsx32_to_statfs32
#define compat_statfs64_to_statfs32 statfsx32_64_to_statfs32
#define compat_statfs32_to_statfs64 statfsx32_to_statfs64
#define compat_statfs64_to_statfs64 statfsx32_64_to_statfs64
#define statfs_to_compat_statfs32   statfs32_to_statfsx32
#define statfs_to_compat_statfs64   statfs32_to_statfsx32_64
#define statfs32_to_compat_statfs32 statfs32_to_statfsx32
#define statfs32_to_compat_statfs64 statfs32_to_statfsx32_64
#define statfs64_to_compat_statfs32 statfs64_to_statfsx32
#define statfs64_to_compat_statfs64 statfs64_to_statfsx32_64

#endif /* !__x86_64__ */

#endif /* !_I386_KOS_COMPAT_BITS_OS_KOS_STATFS_CONVERT_H */
