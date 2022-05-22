/* HASH CRC-32:0xcf74fec9 */
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
#ifndef GUARD_LIBC_USER_PARTS_WCHAR_UNISTD_H
#define GUARD_LIBC_USER_PARTS_WCHAR_UNISTD_H 1

#include "../api.h"
#include "../auto/parts.wchar.unistd.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <parts/wchar/unistd.h>

DECL_BEGIN

#ifndef __KERNEL__
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTDEF ATTR_ACCESS_WRS(2, 3) int NOTHROW_RPC(LIBDCALL libd_wttyname_r)(fd_t fd, char16_t *buf, size_t buflen);
/* >> ttyname_r(3)
 * Return the name of a TTY given its file descriptor */
INTDEF ATTR_ACCESS_WRS(2, 3) int NOTHROW_RPC(LIBKCALL libc_wttyname_r)(fd_t fd, char32_t *buf, size_t buflen);
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_WRS(3, 4) ssize_t NOTHROW_RPC(LIBDCALL libd_wreadlinkat)(fd_t dfd, char16_t const *path, char16_t *buf, size_t buflen);
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_WRS(3, 4) ssize_t NOTHROW_RPC(LIBKCALL libc_wreadlinkat)(fd_t dfd, char32_t const *path, char32_t *buf, size_t buflen);
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_WRS(3, 4) ssize_t NOTHROW_RPC(LIBDCALL libd_wfreadlinkat)(fd_t dfd, char16_t const *path, char16_t *buf, size_t buflen, atflag_t flags);
INTDEF ATTR_ACCESS_RO(2) ATTR_ACCESS_WRS(3, 4) ssize_t NOTHROW_RPC(LIBKCALL libc_wfreadlinkat)(fd_t dfd, char32_t const *path, char32_t *buf, size_t buflen, atflag_t flags);
INTDEF ATTR_ACCESS_RO(1) ATTR_ACCESS_WRS(2, 3) ssize_t NOTHROW_RPC(LIBDCALL libd_wreadlink)(char16_t const *path, char16_t *buf, size_t buflen);
INTDEF ATTR_ACCESS_RO(1) ATTR_ACCESS_WRS(2, 3) ssize_t NOTHROW_RPC(LIBKCALL libc_wreadlink)(char32_t const *path, char32_t *buf, size_t buflen);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_PARTS_WCHAR_UNISTD_H */
