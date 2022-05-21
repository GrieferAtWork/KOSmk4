/* HASH CRC-32:0x2eeeb8de */
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
#ifndef GUARD_LIBC_USER_CORECRT_WSTDIO_H
#define GUARD_LIBC_USER_CORECRT_WSTDIO_H 1

#include "../api.h"
#include "../auto/corecrt_wstdio.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <corecrt_wstdio.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF WUNUSED ATTR_ACCESS_RO_OPT(1) ATTR_ACCESS_RO_OPT(2) char16_t *NOTHROW_NCX(LIBDCALL libd__wtempnam)(char16_t const *directory, char16_t const *file_prefix);
INTDEF WUNUSED ATTR_ACCESS_RO_OPT(1) ATTR_ACCESS_RO_OPT(2) char32_t *NOTHROW_NCX(LIBKCALL libc__wtempnam)(char32_t const *directory, char32_t const *file_prefix);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBDCALL libd__wtmpnam_s)(char16_t *dst, size_t wchar_count);
INTDEF NONNULL((1)) errno_t NOTHROW_NCX(LIBKCALL libc__wtmpnam_s)(char32_t *dst, size_t wchar_count);
INTDEF char16_t *NOTHROW_NCX(LIBDCALL libd__wtmpnam)(char16_t *buf);
INTDEF char32_t *NOTHROW_NCX(LIBKCALL libc__wtmpnam)(char32_t *buf);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_CORECRT_WSTDIO_H */
