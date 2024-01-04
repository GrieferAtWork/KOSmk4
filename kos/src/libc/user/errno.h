/* HASH CRC-32:0x31a8a3bd */
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
#ifndef GUARD_LIBC_USER_ERRNO_H
#define GUARD_LIBC_USER_ERRNO_H 1

#include "../api.h"
#include "../auto/errno.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <errno.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> __errno_location(3) */
INTDEF ATTR_CONST ATTR_RETNONNULL WUNUSED errno_t *NOTHROW(LIBCCALL libc___errno_location)(void);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_ERRNO_H */
