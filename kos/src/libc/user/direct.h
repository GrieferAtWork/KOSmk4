/* HASH CRC-32:0x98057ead */
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
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_DIRECT_H
#define GUARD_LIBC_USER_DIRECT_H 1

#include "../api.h"
#include "../auto/direct.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <direct.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF char *NOTHROW_RPC(LIBCCALL libc__getdcwd)(int drive, char *buf, size_t size);
INTDEF int NOTHROW_RPC(LIBCCALL libc__chdrive)(int drive);
INTDEF int NOTHROW_RPC(LIBCCALL libc__getdrive)(void);
INTDEF __ULONG32_TYPE__ NOTHROW_RPC(LIBCCALL libc__getdrives)(void);
INTDEF unsigned int NOTHROW_RPC(LIBCCALL libc__getdiskfree)(unsigned int drive, struct _diskfree_t *diskfree);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_DIRECT_H */
