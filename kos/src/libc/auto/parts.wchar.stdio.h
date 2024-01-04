/* HASH CRC-32:0xb62207f7 */
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
#ifndef GUARD_LIBC_AUTO_PARTS_WCHAR_STDIO_H
#define GUARD_LIBC_AUTO_PARTS_WCHAR_STDIO_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <parts/wchar/stdio.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBDCALL libd_wremove)(char16_t const *filename);
INTDEF ATTR_IN(1) int NOTHROW_RPC(LIBKCALL libc_wremove)(char32_t const *filename);
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_wrename)(char16_t const *oldname, char16_t const *newname_or_path);
INTDEF ATTR_IN(1) ATTR_IN(2) int NOTHROW_RPC(LIBKCALL libc_wrename)(char32_t const *oldname, char32_t const *newname_or_path);
INTDEF ATTR_IN(2) ATTR_IN(4) int NOTHROW_RPC(LIBDCALL libd_wrenameat)(fd_t oldfd, char16_t const *oldname, fd_t newfd, char16_t const *newname_or_path);
INTDEF ATTR_IN(2) ATTR_IN(4) int NOTHROW_RPC(LIBKCALL libc_wrenameat)(fd_t oldfd, char32_t const *oldname, fd_t newfd, char32_t const *newname_or_path);
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBDCALL libd_wremoveat)(fd_t dirfd, char16_t const *filename);
INTDEF ATTR_IN(2) int NOTHROW_RPC(LIBKCALL libc_wremoveat)(fd_t dirfd, char32_t const *filename);
INTDEF ATTR_IN(2) ATTR_IN(4) int NOTHROW_RPC(LIBDCALL libd_wrenameat2)(fd_t oldfd, char16_t const *oldname, fd_t newfd, char16_t const *newname_or_path, atflag_t flags);
INTDEF ATTR_IN(2) ATTR_IN(4) int NOTHROW_RPC(LIBKCALL libc_wrenameat2)(fd_t oldfd, char32_t const *oldname, fd_t newfd, char32_t const *newname_or_path, atflag_t flags);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) FILE *NOTHROW_NCX(LIBDCALL libd_wfopen)(char16_t const *filename, char16_t const *mode);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) FILE *NOTHROW_NCX(LIBKCALL libc_wfopen)(char32_t const *filename, char32_t const *mode);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_INOUT(3) FILE *NOTHROW_NCX(LIBDCALL libd_wfreopen)(char16_t const *filename, char16_t const *mode, FILE *stream);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) ATTR_INOUT(3) FILE *NOTHROW_NCX(LIBKCALL libc_wfreopen)(char32_t const *filename, char32_t const *mode, FILE *stream);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) FILE *NOTHROW_NCX(LIBDCALL libd_wpopen)(char16_t const *command, char16_t const *mode);
INTDEF WUNUSED ATTR_IN(1) ATTR_IN(2) FILE *NOTHROW_NCX(LIBKCALL libc_wpopen)(char32_t const *command, char32_t const *mode);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_PARTS_WCHAR_STDIO_H */
