/* HASH CRC-32:0x288f25a8 */
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
#ifndef GUARD_LIBC_AUTO_KOS_GUID_H
#define GUARD_LIBC_AUTO_KOS_GUID_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <kos/guid.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> guid_fromstr(3)
 * Convert a given `string' into a GUID
 * >> guid_t g;
 * >> guid_fromstr("054b1def-b2ae-4d99-a99c-54b9730c3dc3", &g);
 * @return: string + GUID_STRLEN: Success
 * @return: NULL:                 `string' isn't a valid GUID. */
INTDEF ATTR_IN(1) ATTR_OUT(2) char const *NOTHROW_NCX(LIBDCALL libd_guid_fromstr)(char const string[__GUID_STRLEN], guid_t *__restrict result);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
/* >> guid_fromstr(3)
 * Convert a given `string' into a GUID
 * >> guid_t g;
 * >> guid_fromstr("054b1def-b2ae-4d99-a99c-54b9730c3dc3", &g);
 * @return: string + GUID_STRLEN: Success
 * @return: NULL:                 `string' isn't a valid GUID. */
INTDEF ATTR_IN(1) ATTR_OUT(2) char const *NOTHROW_NCX(LIBCCALL libc_guid_fromstr)(char const string[__GUID_STRLEN], guid_t *__restrict result);

DECL_END

#endif /* !GUARD_LIBC_AUTO_KOS_GUID_H */
