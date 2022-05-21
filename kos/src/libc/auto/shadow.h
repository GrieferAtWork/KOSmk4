/* HASH CRC-32:0x2207e2c */
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
#ifndef GUARD_LIBC_AUTO_SHADOW_H
#define GUARD_LIBC_AUTO_SHADOW_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <shadow.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
INTDEF NONNULL((1)) struct spwd *NOTHROW_RPC(LIBDCALL libd_getspnam)(char const *__restrict name);
INTDEF NONNULL((1)) struct spwd *NOTHROW_RPC(LIBDCALL libd_sgetspent)(char const *__restrict string);
INTDEF ATTR_ACCESS_RW(1) struct spwd *NOTHROW_RPC(LIBDCALL libd_fgetspent)(FILE *__restrict stream);
INTDEF ATTR_ACCESS_RW(2) NONNULL((1)) int NOTHROW_RPC(LIBDCALL libd_putspent)(struct spwd const *__restrict p, FILE *__restrict stream);
INTDEF NONNULL((1, 2, 4)) int NOTHROW_RPC(LIBDCALL libd_getspent_r)(struct spwd *__restrict result_buf, char *__restrict buffer, size_t buflen, struct spwd **__restrict result);
INTDEF NONNULL((1, 2, 3, 5)) int NOTHROW_RPC(LIBDCALL libd_getspnam_r)(char const *__restrict name, struct spwd *__restrict result_buf, char *__restrict buffer, size_t buflen, struct spwd **__restrict result);
INTDEF NONNULL((1, 2, 3, 5)) int NOTHROW_RPC(LIBDCALL libd_sgetspent_r)(char const *__restrict string, struct spwd *__restrict result_buf, char *__restrict buffer, size_t buflen, struct spwd **__restrict result);
INTDEF ATTR_ACCESS_RW(1) NONNULL((2, 3, 5)) int NOTHROW_RPC(LIBDCALL libd_fgetspent_r)(FILE *__restrict stream, struct spwd *__restrict result_buf, char *__restrict buffer, size_t buflen, struct spwd **__restrict result);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_SHADOW_H */
