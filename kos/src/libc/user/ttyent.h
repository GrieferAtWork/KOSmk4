/* HASH CRC-32:0x9680cf2 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_TTYENT_H
#define GUARD_LIBC_USER_TTYENT_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <ttyent.h>

DECL_BEGIN

INTDEF struct ttyent *NOTHROW_RPC_KOS(LIBCCALL libc_getttyent)(void);
INTDEF NONNULL((1)) struct ttyent *NOTHROW_RPC_KOS(LIBCCALL libc_getttynam)(char const *tty);
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_setttyent)(void);
INTDEF int NOTHROW_RPC_KOS(LIBCCALL libc_endttyent)(void);

DECL_END

#endif /* !GUARD_LIBC_USER_TTYENT_H */
