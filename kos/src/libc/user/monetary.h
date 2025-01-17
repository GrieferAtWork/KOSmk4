/* HASH CRC-32:0xfa46f3ab */
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
#ifndef GUARD_LIBC_USER_MONETARY_H
#define GUARD_LIBC_USER_MONETARY_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <monetary.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(3) ATTR_LIBC_STRFMON(3, 4) ATTR_OUTS(1, 2) ssize_t NOTHROW_NCX(VLIBDCALL libd_strfmon)(char *__restrict s, size_t maxsize, char const *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(3) ATTR_LIBC_STRFMON(3, 4) ATTR_OUTS(1, 2) ssize_t NOTHROW_NCX(VLIBCCALL libc_strfmon)(char *__restrict s, size_t maxsize, char const *__restrict format, ...);
#endif /* !__KERNEL__ */
#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF ATTR_IN(4) ATTR_LIBC_STRFMON(4, 5) ATTR_OUTS(1, 2) ssize_t NOTHROW_NCX(VLIBDCALL libd_strfmon_l)(char *__restrict s, size_t maxsize, locale_t loc, const char *__restrict format, ...);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */
#ifndef __KERNEL__
INTDEF ATTR_IN(4) ATTR_LIBC_STRFMON(4, 5) ATTR_OUTS(1, 2) ssize_t NOTHROW_NCX(VLIBCCALL libc_strfmon_l)(char *__restrict s, size_t maxsize, locale_t loc, const char *__restrict format, ...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_MONETARY_H */
