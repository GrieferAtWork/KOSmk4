/* HASH CRC-32:0x9994685c */
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
#ifndef GUARD_LIBC_USER_TTYENT_H
#define GUARD_LIBC_USER_TTYENT_H 1

#include "../api.h"
#include "../auto/ttyent.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <ttyent.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> getttyent(3) */
INTDEF struct ttyent *NOTHROW_RPC_KOS(LIBCCALL libc_getttyent)(void);
/* >> setttyent(3)
 * @return: 1 : Success
 * @return: 0 : Error */
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_setttyent)(void);
/* >> endttyent(3)
 * @return: 1 : Success
 * @return: 0 : Error */
INTDEF int NOTHROW_NCX(LIBCCALL libc_endttyent)(void);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_TTYENT_H */
