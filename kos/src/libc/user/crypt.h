/* HASH CRC-32:0x5e78a411 */
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBC_USER_CRYPT_H
#define GUARD_LIBC_USER_CRYPT_H 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include <crypt.h>

DECL_BEGIN

/* Setup DES tables according KEY */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_setkey)(char const *key);
/* Encrypt at most 8 characters from KEY using salt to perturb DES */
INTDEF NONNULL((1, 2)) char *NOTHROW_NCX(LIBCCALL libc_crypt)(char const *key, char const *salt);
/* Encrypt data in BLOCK in place if EDFLAG is zero; otherwise decrypt block in place */
INTDEF NONNULL((1)) void NOTHROW_NCX(LIBCCALL libc_encrypt)(char *glibc_block, int edflag);
/* Encrypt at most 8 characters from KEY using salt to perturb DES */
INTDEF NONNULL((1, 2, 3)) char *NOTHROW_NCX(LIBCCALL libc_crypt_r)(char const *key, char const *salt, struct crypt_data *__restrict data);
INTDEF NONNULL((1, 2)) void NOTHROW_NCX(LIBCCALL libc_setkey_r)(char const *key, struct crypt_data *__restrict data);
/* Encrypt data in BLOCK in place if EDFLAG is zero; otherwise decrypt block in place */
INTDEF NONNULL((1, 3)) void NOTHROW_NCX(LIBCCALL libc_encrypt_r)(char *glibc_block, int edflag, struct crypt_data *__restrict data);

DECL_END

#endif /* !GUARD_LIBC_USER_CRYPT_H */
