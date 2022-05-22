/* HASH CRC-32:0x4d67a5bd */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_CORECRT_WSTRING_H
#define GUARD_LIBC_USER_CORECRT_WSTRING_H 1

#include "../api.h"
#include "../auto/corecrt_wstring.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <corecrt_wstring.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF char16_t *NOTHROW_NCX(LIBDCALL libd__wcserror)(errno_t errno_value);
INTDEF char32_t *NOTHROW_NCX(LIBKCALL libc__wcserror)(errno_t errno_value);
INTDEF ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__wcserror_s)(char16_t *buf, size_t bufsize, errno_t errno_value);
INTDEF ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBKCALL libc__wcserror_s)(char32_t *buf, size_t bufsize, errno_t errno_value);
INTDEF ATTR_IN(1) char16_t *NOTHROW_NCX(LIBDCALL libd___wcserror)(char16_t const *message);
INTDEF ATTR_IN(1) char32_t *NOTHROW_NCX(LIBKCALL libc___wcserror)(char32_t const *message);
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd___wcserror_s)(char16_t *buf, size_t bufsize, char16_t const *message);
INTDEF ATTR_IN(3) ATTR_OUTS(1, 2) errno_t NOTHROW_NCX(LIBKCALL libc___wcserror_s)(char32_t *buf, size_t bufsize, char32_t const *message);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_CORECRT_WSTRING_H */
