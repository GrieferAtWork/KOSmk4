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
#ifndef _COMPAT_BITS_OS_GENERIC_STATFS_CONVERT_H
#define _COMPAT_BITS_OS_GENERIC_STATFS_CONVERT_H 1

#include <compat/config.h>
#ifdef __ARCH_HAVE_COMPAT
#include <bits/os/statfs-convert.h>
#include <bits/os/statfs.h>

#include <libc/string.h>
#define compat_statfs32_to_statfs32(self, result)                      \
	__libc_memcpy(__COMPILER_REQTYPE(struct __statfs32 *, result),     \
	              __COMPILER_REQTYPE(struct __statfs32 const *, self), \
	              sizeof(struct __statfs32))
#define compat_statfs32_to_statfs64(self, result) statfs32_to_statfs64(self, result)
#define compat_statfs64_to_statfs32(self, result) statfs64_to_statfs32(self, result)
#define compat_statfs64_to_statfs64(self, result)                      \
	__libc_memcpy(__COMPILER_REQTYPE(struct __statfs64 *, result),     \
	              __COMPILER_REQTYPE(struct __statfs64 const *, self), \
	              sizeof(struct __statfs64))
#define statfs32_to_compat_statfs32(self, result)                      \
	__libc_memcpy(__COMPILER_REQTYPE(struct __statfs32 *, result),     \
	              __COMPILER_REQTYPE(struct __statfs32 const *, self), \
	              sizeof(struct __statfs32))
#define statfs32_to_compat_statfs64(self, result) statfs32_to_statfs64(self, result)
#define statfs64_to_compat_statfs32(self, result) statfs64_to_statfs32(self, result)
#define statfs64_to_compat_statfs64(self, result)                      \
	__libc_memcpy(__COMPILER_REQTYPE(struct __statfs64 *, result),     \
	              __COMPILER_REQTYPE(struct __statfs64 const *, self), \
	              sizeof(struct __statfs64))
#endif /* __ARCH_HAVE_COMPAT */

#endif /* !_COMPAT_BITS_OS_GENERIC_STATFS_CONVERT_H */
