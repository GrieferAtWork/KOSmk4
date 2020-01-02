/* HASH CRC-32:0x2196b5b8 */
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
#ifndef GUARD_LIBC_USER_SYS_TIMEB_H
#define GUARD_LIBC_USER_SYS_TIMEB_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <sys/timeb.h>

DECL_BEGIN

/* Fill in TIMEBUF with information about the current time */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc__ftime32)(struct __timeb32 *timebuf);
/* Fill in TIMEBUF with information about the current time */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc__ftime64)(struct __timeb64 *timebuf);
/* Fill in TIMEBUF with information about the current time */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc__ftime32_s)(struct __timeb32 *timebuf);
/* Fill in TIMEBUF with information about the current time */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd__ftime32_s)(struct __timeb32 *timebuf);
/* Fill in TIMEBUF with information about the current time */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBCCALL libc__ftime64_s)(struct __timeb64 *timebuf);
/* Fill in TIMEBUF with information about the current time */
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd__ftime64_s)(struct __timeb64 *timebuf);
/* Fill in TIMEBUF with information about the current time */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_ftime)(struct timeb *timebuf);
/* Fill in TIMEBUF with information about the current time */
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc_ftime64)(struct timeb64 *timebuf);

DECL_END

#endif /* !GUARD_LIBC_USER_SYS_TIMEB_H */
