/* HASH CRC-32:0x20aa8e76 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_CORECRT_WDIRECT_H
#define GUARD_LIBC_AUTO_CORECRT_WDIRECT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <corecrt_wdirect.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_OUTS(2, 3) char16_t *NOTHROW_RPC(LIBDCALL libd__wgetdcwd)(int drive, char16_t *buf, size_t size);
INTDEF ATTR_OUTS(2, 3) char32_t *NOTHROW_RPC(LIBKCALL libc__wgetdcwd)(int drive, char32_t *buf, size_t size);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd__wmkdir)(char16_t const *path);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBKCALL libc__wmkdir)(char32_t const *path);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_CORECRT_WDIRECT_H */
