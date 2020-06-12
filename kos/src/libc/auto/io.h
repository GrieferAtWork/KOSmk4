/* HASH CRC-32:0xb230ba2e */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_AUTO_IO_H
#define GUARD_LIBC_AUTO_IO_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <io.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF NONNULL((1)) int NOTHROW_NCX(LIBCCALL libc__pipe)(fd_t pipedes[2], uint32_t pipesize, oflag_t textmode);
INTDEF WUNUSED int64_t NOTHROW_NCX(LIBCCALL libc__filelengthi64)(fd_t fd);
INTDEF WUNUSED int64_t NOTHROW_NCX(LIBCCALL libc__telli64)(fd_t fd);
INTDEF errno_t NOTHROW_NCX(LIBCCALL libc_umask_s)(mode_t newmode, mode_t *oldmode);
INTDEF ATTR_PURE WUNUSED intptr_t NOTHROW_NCX(LIBCCALL libc__get_osfhandle)(fd_t fd);
INTDEF WUNUSED fd_t NOTHROW_NCX(LIBCCALL libc__open_osfhandle)(intptr_t osfd, oflag_t flags);
INTDEF oflag_t NOTHROW_NCX(LIBCCALL libc_setmode)(fd_t fd, oflag_t mode);
INTDEF WUNUSED NONNULL((1)) fd_t NOTHROW_RPC(VLIBCCALL libc_sopen)(char const *filename, oflag_t oflags, int sflags, ...);
INTDEF WUNUSED __LONG32_TYPE__ NOTHROW_NCX(LIBCCALL libc__filelength)(fd_t fd);
INTDEF WUNUSED __LONG32_TYPE__ NOTHROW_NCX(LIBCCALL libc__tell)(fd_t fd);
INTDEF WUNUSED int NOTHROW_NCX(LIBCCALL libc__eof)(fd_t fd);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_IO_H */
