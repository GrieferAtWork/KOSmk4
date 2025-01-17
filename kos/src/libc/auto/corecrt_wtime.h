/* HASH CRC-32:0xf78fbda5 */
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
#ifndef GUARD_LIBC_AUTO_CORECRT_WTIME_H
#define GUARD_LIBC_AUTO_CORECRT_WTIME_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <corecrt_wtime.h>

DECL_BEGIN

#include <time.h>
#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(1) char16_t *NOTHROW_NCX(LIBDCALL libd__wasctime)(struct tm const *tp);
INTDEF WUNUSED ATTR_IN(1) char32_t *NOTHROW_NCX(LIBKCALL libc__wasctime)(struct tm const *tp);
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__wasctime_s)(char16_t *buf, size_t buflen, struct tm const *tp);
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBKCALL libc__wasctime_s)(char32_t *buf, size_t buflen, struct tm const *tp);
INTDEF WUNUSED ATTR_IN(1) char16_t *NOTHROW_NCX(LIBDCALL libd__wctime32)(time32_t const *timer);
INTDEF WUNUSED ATTR_IN(1) char32_t *NOTHROW_NCX(LIBKCALL libc__wctime32)(time32_t const *timer);
INTDEF WUNUSED ATTR_IN(1) char16_t *NOTHROW_NCX(LIBDCALL libd__wctime64)(time64_t const *timer);
INTDEF WUNUSED ATTR_IN(1) char32_t *NOTHROW_NCX(LIBKCALL libc__wctime64)(time64_t const *timer);
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__wctime32_s)(char16_t *buf, size_t buflen, time32_t const *timer);
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBKCALL libc__wctime32_s)(char32_t *buf, size_t buflen, time32_t const *timer);
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__wctime64_s)(char16_t *buf, size_t buflen, time64_t const *timer);
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBKCALL libc__wctime64_s)(char32_t *buf, size_t buflen, time64_t const *timer);
INTDEF ATTR_OUT(1) char16_t *NOTHROW_NCX(LIBDCALL libd__wstrtime)(char16_t buf[9]);
INTDEF ATTR_OUT(1) char32_t *NOTHROW_NCX(LIBKCALL libc__wstrtime)(char32_t buf[9]);
INTDEF ATTR_OUT(1) char16_t *NOTHROW_NCX(LIBDCALL libd__wstrdate)(char16_t buf[9]);
INTDEF ATTR_OUT(1) char32_t *NOTHROW_NCX(LIBKCALL libc__wstrdate)(char32_t buf[9]);
INTDEF ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__wstrtime_s)(char16_t *buf, size_t buflen);
INTDEF ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBKCALL libc__wstrtime_s)(char32_t *buf, size_t buflen);
INTDEF ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__wstrdate_s)(char16_t *buf, size_t buflen);
INTDEF ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBKCALL libc__wstrdate_s)(char32_t *buf, size_t buflen);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_CORECRT_WTIME_H */
