/* HASH CRC-32:0x1ca523f8 */
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
#ifndef GUARD_LIBC_AUTO_PARTS_WCHAR_UTIME_H
#define GUARD_LIBC_AUTO_PARTS_WCHAR_UTIME_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <parts/wchar/utime.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_IN(1) ATTR_IN_OPT(2) int NOTHROW_RPC(LIBDCALL libd_wutime)(char16_t const *file, struct utimbuf const *file_times);
INTDEF ATTR_IN(1) ATTR_IN_OPT(2) int NOTHROW_RPC(LIBKCALL libc_wutime)(char32_t const *file, struct utimbuf const *file_times);
INTDEF ATTR_IN(1) ATTR_IN_OPT(2) int NOTHROW_RPC(LIBDCALL libd_wutime64)(char16_t const *file, struct utimbuf64 const *file_times);
INTDEF ATTR_IN(1) ATTR_IN_OPT(2) int NOTHROW_RPC(LIBKCALL libc_wutime64)(char32_t const *file, struct utimbuf64 const *file_times);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_PARTS_WCHAR_UTIME_H */
