/* HASH CRC-32:0x81c46e4c */
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
#ifndef GUARD_LIBC_AUTO_PARTS_WCHAR_STDLIB_H
#define GUARD_LIBC_AUTO_PARTS_WCHAR_STDLIB_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <parts/wchar/stdlib.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF int NOTHROW_RPC(LIBDCALL libd_wsystem)(char16_t const *cmd);
INTDEF int NOTHROW_RPC(LIBKCALL libc_wsystem)(char32_t const *cmd);
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT_OPT(2) char16_t *NOTHROW_RPC(LIBDCALL libd_wrealpath)(char16_t const *filename, char16_t *resolved);
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT_OPT(2) char32_t *NOTHROW_RPC(LIBKCALL libc_wrealpath)(char32_t const *filename, char32_t *resolved);
INTDEF WUNUSED ATTR_FDARG(1) ATTR_OUTS(2, 3) char16_t *NOTHROW_RPC(LIBDCALL libd_wfrealpath)(fd_t fd, char16_t *resolved, size_t buflen);
INTDEF WUNUSED ATTR_FDARG(1) ATTR_OUTS(2, 3) char32_t *NOTHROW_RPC(LIBKCALL libc_wfrealpath)(fd_t fd, char32_t *resolved, size_t buflen);
INTDEF WUNUSED ATTR_FDARG(1) ATTR_OUTS(2, 3) char16_t *NOTHROW_RPC(LIBDCALL libd_wfrealpath4)(fd_t fd, char16_t *resolved, size_t buflen, atflag_t flags);
INTDEF WUNUSED ATTR_FDARG(1) ATTR_OUTS(2, 3) char32_t *NOTHROW_RPC(LIBKCALL libc_wfrealpath4)(fd_t fd, char32_t *resolved, size_t buflen, atflag_t flags);
INTDEF WUNUSED ATTR_IN(2) ATTR_OUTS(3, 4) char16_t *NOTHROW_RPC(LIBDCALL libd_wfrealpathat)(fd_t dirfd, char16_t const *filename, char16_t *resolved, size_t buflen, atflag_t flags);
INTDEF WUNUSED ATTR_IN(2) ATTR_OUTS(3, 4) char32_t *NOTHROW_RPC(LIBKCALL libc_wfrealpathat)(fd_t dirfd, char32_t const *filename, char32_t *resolved, size_t buflen, atflag_t flags);
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) int NOTHROW_NCX(LIBDCALL libd_wtoi)(char16_t const *nptr);
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) int NOTHROW_NCX(LIBKCALL libc_wtoi)(char32_t const *nptr);
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) long NOTHROW_NCX(LIBDCALL libd_wtol)(char16_t const *nptr);
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) long NOTHROW_NCX(LIBKCALL libc_wtol)(char32_t const *nptr);
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) __LONGLONG NOTHROW_NCX(LIBDCALL libd_wtoll)(char16_t const *nptr);
INTDEF ATTR_PURE WUNUSED ATTR_IN(1) __LONGLONG NOTHROW_NCX(LIBKCALL libc_wtoll)(char32_t const *nptr);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_PARTS_WCHAR_STDLIB_H */
