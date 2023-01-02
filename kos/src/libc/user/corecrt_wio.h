/* HASH CRC-32:0x7b6ccaf1 */
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
#ifndef GUARD_LIBC_USER_CORECRT_WIO_H
#define GUARD_LIBC_USER_CORECRT_WIO_H 1

#include "../api.h"
#include "../auto/corecrt_wio.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <corecrt_wio.h>

DECL_BEGIN

#ifndef __KERNEL__
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(2) intptr_t NOTHROW_RPC(LIBDCALL libd__wfindfirst32)(char16_t const *__restrict filename, struct _wfinddata32_t *__restrict finddata);
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(2) intptr_t NOTHROW_RPC(LIBKCALL libc__wfindfirst32)(char32_t const *__restrict filename, struct _wfinddata32_t *__restrict finddata);
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(2) intptr_t NOTHROW_RPC(LIBDCALL libd__wfindfirst32i64)(char16_t const *__restrict filename, struct _wfinddata32i64_t *__restrict finddata);
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(2) intptr_t NOTHROW_RPC(LIBKCALL libc__wfindfirst32i64)(char32_t const *__restrict filename, struct _wfinddata32i64_t *__restrict finddata);
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(2) intptr_t NOTHROW_RPC(LIBDCALL libd__wfindfirst64)(char16_t const *__restrict filename, struct _wfinddata64_t *__restrict finddata);
INTDEF WUNUSED ATTR_IN(1) ATTR_OUT(2) intptr_t NOTHROW_RPC(LIBKCALL libc__wfindfirst64)(char32_t const *__restrict filename, struct _wfinddata64_t *__restrict finddata);
INTDEF ATTR_OUT(2) int NOTHROW_RPC(LIBDCALL libd__wfindnext32)(intptr_t findfd, struct _wfinddata32_t *__restrict finddata);
INTDEF ATTR_OUT(2) int NOTHROW_RPC(LIBKCALL libc__wfindnext32)(intptr_t findfd, struct _wfinddata32_t *__restrict finddata);
INTDEF ATTR_OUT(2) int NOTHROW_RPC(LIBDCALL libd__wfindnext32i64)(intptr_t findfd, struct _wfinddata32i64_t *__restrict finddata);
INTDEF ATTR_OUT(2) int NOTHROW_RPC(LIBKCALL libc__wfindnext32i64)(intptr_t findfd, struct _wfinddata32i64_t *__restrict finddata);
INTDEF ATTR_OUT(2) int NOTHROW_RPC(LIBDCALL libd__wfindnext64)(intptr_t findfd, struct _wfinddata64_t *__restrict finddata);
INTDEF ATTR_OUT(2) int NOTHROW_RPC(LIBKCALL libc__wfindnext64)(intptr_t findfd, struct _wfinddata64_t *__restrict finddata);
#endif /* !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_USER_CORECRT_WIO_H */
