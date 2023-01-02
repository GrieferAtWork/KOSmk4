/* HASH CRC-32:0x715e7541 */
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
#ifndef GUARD_LIBC_AUTO_CRYPT_H
#define GUARD_LIBC_AUTO_CRYPT_H 1

#include "../api.h"

#include <hybrid/typecore.h>
#include <kos/types.h>
#include <crypt.h>

DECL_BEGIN

#if !defined(__LIBCCALL_IS_LIBDCALL) && !defined(__KERNEL__)
/* >> setkey(3), setkey_r(3) */
INTDEF void NOTHROW_NCX(LIBDCALL libd_setkey)(char const *key);
/* >> crypt(3), crypt_r(3) */
INTDEF ATTR_IN(1) ATTR_IN(2) char *NOTHROW_NCX(LIBDCALL libd_crypt)(char const *key, char const *salt);
/* >> encrypt(3), encrypt_r(3) */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBDCALL libd_encrypt)(char *glibc_block, __STDC_INT_AS_UINT_T edflag);
/* >> crypt(3), crypt_r(3) */
INTDEF ATTR_IN(1) ATTR_IN(2) NONNULL((3)) char *NOTHROW_NCX(LIBDCALL libd_crypt_r)(char const *key, char const *salt, struct crypt_data *__restrict data);
/* >> setkey(3), setkey_r(3) */
INTDEF ATTR_IN(1) NONNULL((2)) void NOTHROW_NCX(LIBDCALL libd_setkey_r)(char const *key, struct crypt_data *__restrict data);
/* >> encrypt(3), encrypt_r(3) */
INTDEF NONNULL((1, 3)) void NOTHROW_NCX(LIBDCALL libd_encrypt_r)(char *glibc_block, int edflag, struct crypt_data *__restrict data);
#endif /* !__LIBCCALL_IS_LIBDCALL && !__KERNEL__ */

DECL_END

#endif /* !GUARD_LIBC_AUTO_CRYPT_H */
