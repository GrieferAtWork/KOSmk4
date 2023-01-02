/* HASH CRC-32:0xf279012 */
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
#ifndef GUARD_LIBC_AUTO_CORECRT_WIO_H
#define GUARD_LIBC_AUTO_CORECRT_WIO_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <corecrt_wio.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(1) errno_t NOTHROW_RPC(LIBDCALL libd__waccess_s)(char16_t const *file, __STDC_INT_AS_UINT_T type);
INTDEF WUNUSED ATTR_IN(1) errno_t NOTHROW_RPC(LIBKCALL libc__waccess_s)(char32_t const *file, __STDC_INT_AS_UINT_T type);
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBDCALL libd__wmktemp_s)(char16_t *template_, size_t bufsize);
INTDEF ATTR_INOUTS(1, 2) errno_t NOTHROW_NCX(LIBKCALL libc__wmktemp_s)(char32_t *template_, size_t bufsize);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) char16_t *NOTHROW_NCX(LIBDCALL libd__wmktemp)(char16_t *template_);
INTDEF ATTR_RETNONNULL ATTR_INOUT(1) char32_t *NOTHROW_NCX(LIBKCALL libc__wmktemp)(char32_t *template_);
INTDEF ATTR_IN(2) ATTR_OUT(1) errno_t NOTHROW_RPC(LIBDCALL libd__wsopen_s)(fd_t *fd, char16_t const *filename, oflag_t oflags, int sflags, mode_t mode);
INTDEF ATTR_IN(2) ATTR_OUT(1) errno_t NOTHROW_RPC(LIBKCALL libc__wsopen_s)(fd_t *fd, char32_t const *filename, oflag_t oflags, int sflags, mode_t mode);
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(5) errno_t NOTHROW_RPC(LIBDCALL libd__wsopen_dispatch)(char16_t const *filename, oflag_t oflags, int sflags, mode_t mode, fd_t *fd, int bsecure);
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(5) errno_t NOTHROW_RPC(LIBKCALL libc__wsopen_dispatch)(char32_t const *filename, oflag_t oflags, int sflags, mode_t mode, fd_t *fd, int bsecure);
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_RPC(VLIBDCALL libd__wsopen)(char16_t const *filename, oflag_t oflags, int sflags, ...);
INTDEF WUNUSED ATTR_IN(1) fd_t NOTHROW_RPC(VLIBKCALL libc__wsopen)(char32_t const *filename, oflag_t oflags, int sflags, ...);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_CORECRT_WIO_H */
