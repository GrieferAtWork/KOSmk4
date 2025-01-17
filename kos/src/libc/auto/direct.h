/* HASH CRC-32:0x1be2c73 */
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
#ifndef GUARD_LIBC_AUTO_DIRECT_H
#define GUARD_LIBC_AUTO_DIRECT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <direct.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_OUTS(2, 3) char *NOTHROW_RPC(LIBDCALL libd__getdcwd)(int drive, char *buf, size_t bufsize);
INTDEF ATTR_OUTS(2, 3) char *NOTHROW_RPC(LIBCCALL libc__getdcwd)(int drive, char *buf, size_t bufsize);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF int NOTHROW_RPC(LIBDCALL libd__chdrive)(int drive);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF int NOTHROW_RPC(LIBCCALL libc__chdrive)(int drive);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_OUT(2) unsigned int NOTHROW_RPC(LIBDCALL libd__getdiskfree)(unsigned int drive, struct _diskfree_t *diskfree);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd__mkdir)(char const *path);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBCCALL libc__mkdir)(char const *path);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_DIRECT_H */
