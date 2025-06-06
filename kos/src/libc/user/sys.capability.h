/* HASH CRC-32:0x13636dc7 */
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
#ifndef GUARD_LIBC_USER_SYS_CAPABILITY_H
#define GUARD_LIBC_USER_SYS_CAPABILITY_H 1

#include "../api.h"
#include "../auto/sys.capability.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/capability.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> capset(2) */
INTDEF int NOTHROW_NCX(LIBCCALL libc_capset)(cap_user_header_t header, cap_user_data_t data);
/* >> capget(2) */
INTDEF int NOTHROW_NCX(LIBCCALL libc_capget)(cap_user_header_t header, cap_user_data_t const data);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_CAPABILITY_H */
