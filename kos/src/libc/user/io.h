/* HASH CRC-32:0xb6384d64 */
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
#ifndef GUARD_LIBC_USER_IO_H
#define GUARD_LIBC_USER_IO_H 1

#include "../api.h"
#include "../auto/io.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <io.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF int NOTHROW_NCX(LIBCCALL libc__findclose)(intptr_t findfd);
INTDEF WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_WR(2) intptr_t NOTHROW_RPC(LIBDCALL libd__findfirst32)(char const *__restrict filename, struct _finddata32_t *__restrict finddata);
INTDEF WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_WR(2) intptr_t NOTHROW_RPC(LIBCCALL libc__findfirst32)(char const *__restrict filename, struct _finddata32_t *__restrict finddata);
INTDEF WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_WR(2) intptr_t NOTHROW_RPC(LIBDCALL libd__findfirst32i64)(char const *__restrict filename, struct _finddata32i64_t *__restrict finddata);
INTDEF WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_WR(2) intptr_t NOTHROW_RPC(LIBCCALL libc__findfirst32i64)(char const *__restrict filename, struct _finddata32i64_t *__restrict finddata);
INTDEF WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_WR(2) intptr_t NOTHROW_RPC(LIBDCALL libd__findfirst64)(char const *__restrict filename, struct __finddata64_t *__restrict finddata);
INTDEF WUNUSED ATTR_ACCESS_RO(1) ATTR_ACCESS_WR(2) intptr_t NOTHROW_RPC(LIBCCALL libc__findfirst64)(char const *__restrict filename, struct __finddata64_t *__restrict finddata);
INTDEF ATTR_ACCESS_WR(2) int NOTHROW_RPC(LIBCCALL libc__findnext32)(intptr_t findfd, struct _finddata32_t *__restrict finddata);
INTDEF ATTR_ACCESS_WR(2) int NOTHROW_RPC(LIBCCALL libc__findnext32i64)(intptr_t findfd, struct _finddata32i64_t *__restrict finddata);
INTDEF ATTR_ACCESS_WR(2) int NOTHROW_RPC(LIBCCALL libc__findnext64)(intptr_t findfd, struct __finddata64_t *__restrict finddata);
INTDEF ATTR_ACCESS_RWS(1, 2) errno_t NOTHROW_NCX(LIBCCALL libc__mktemp_s)(char *template_, size_t size);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_IO_H */
