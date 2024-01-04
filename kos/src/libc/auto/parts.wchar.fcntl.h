/* HASH CRC-32:0xbf417eea */
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
#ifndef GUARD_LIBC_AUTO_PARTS_WCHAR_FCNTL_H
#define GUARD_LIBC_AUTO_PARTS_WCHAR_FCNTL_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <parts/wchar/fcntl.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_RPC(VLIBDCALL libd_wopen)(char16_t const *filename, oflag_t oflags, ...);
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_RPC(VLIBKCALL libc_wopen)(char32_t const *filename, oflag_t oflags, ...);
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_RPC(LIBDCALL libd_wcreat)(char16_t const *filename, mode_t mode);
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_RPC(LIBKCALL libc_wcreat)(char32_t const *filename, mode_t mode);
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_RPC(VLIBDCALL libd_wopen64)(char16_t const *filename, oflag_t oflags, ...);
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_RPC(VLIBKCALL libc_wopen64)(char32_t const *filename, oflag_t oflags, ...);
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_RPC(LIBDCALL libd_wcreat64)(char16_t const *filename, mode_t mode);
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_RPC(LIBKCALL libc_wcreat64)(char32_t const *filename, mode_t mode);
INTDEF WUNUSED ATTR_IN(2) fd_t NOTHROW_RPC(VLIBDCALL libd_wopenat)(fd_t dirfd, char16_t const *filename, oflag_t oflags, ...);
INTDEF WUNUSED ATTR_IN(2) fd_t NOTHROW_RPC(VLIBKCALL libc_wopenat)(fd_t dirfd, char32_t const *filename, oflag_t oflags, ...);
INTDEF WUNUSED ATTR_IN(2) fd_t NOTHROW_RPC(VLIBDCALL libd_wopenat64)(fd_t dirfd, char16_t const *filename, oflag_t oflags, ...);
INTDEF WUNUSED ATTR_IN(2) fd_t NOTHROW_RPC(VLIBKCALL libc_wopenat64)(fd_t dirfd, char32_t const *filename, oflag_t oflags, ...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_PARTS_WCHAR_FCNTL_H */
