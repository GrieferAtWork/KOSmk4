/* HASH CRC-32:0x62f6f23a */
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
#ifndef GUARD_LIBC_USER_SYS_TIMEX_H
#define GUARD_LIBC_USER_SYS_TIMEX_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/timex.h>

DECL_BEGIN

INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_adjtimex)(struct timex *__restrict ntx);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_ntp_gettime)(struct ntptimeval *__restrict ntv);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_ntp_adjtime)(struct timex *__restrict tntx);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_adjtimex64)(struct timex64 *__restrict ntx);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_ntp_adjtime64)(struct timex64 *__restrict tntx);
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_ntp_gettime64)(struct ntptimeval64 *__restrict ntv);

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_TIMEX_H */
