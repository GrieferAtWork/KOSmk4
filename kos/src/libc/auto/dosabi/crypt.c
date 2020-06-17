/* HASH CRC-32:0x868a6312 */
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
#ifndef GUARD_LIBC_AUTO_DOSABI_CRYPT_C
#define GUARD_LIBC_AUTO_DOSABI_CRYPT_C 1

#include "../../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "../../user/crypt.h"

DECL_BEGIN

/* Setup DES tables according KEY */
INTERN ATTR_SECTION(".text.crt.dos.string.encrypt") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd_setkey)(char const *key) {
	libc_setkey(key);
}
/* Encrypt at most 8 characters from KEY using salt to perturb DES */
INTERN ATTR_SECTION(".text.crt.dos.string.encrypt") NONNULL((1, 2)) char *
NOTHROW_NCX(LIBDCALL libd_crypt)(char const *key,
                                 char const *salt) {
	return libc_crypt(key, salt);
}
/* Encrypt data in BLOCK in place if EDFLAG is zero; otherwise decrypt block in place */
INTERN ATTR_SECTION(".text.crt.dos.string.encrypt") NONNULL((1)) void
NOTHROW_NCX(LIBDCALL libd_encrypt)(char *glibc_block,
                                   int edflag) {
	libc_encrypt(glibc_block, edflag);
}
/* Encrypt at most 8 characters from KEY using salt to perturb DES */
INTERN ATTR_SECTION(".text.crt.dos.string.encrypt") NONNULL((1, 2, 3)) char *
NOTHROW_NCX(LIBDCALL libd_crypt_r)(char const *key,
                                   char const *salt,
                                   struct crypt_data *__restrict data) {
	return libc_crypt_r(key, salt, data);
}
/* Setup DES tables according KEY */
INTERN ATTR_SECTION(".text.crt.dos.string.encrypt") NONNULL((1, 2)) void
NOTHROW_NCX(LIBDCALL libd_setkey_r)(char const *key,
                                    struct crypt_data *__restrict data) {
	libc_setkey_r(key, data);
}
/* Encrypt data in BLOCK in place if EDFLAG is zero; otherwise decrypt block in place */
INTERN ATTR_SECTION(".text.crt.dos.string.encrypt") NONNULL((1, 3)) void
NOTHROW_NCX(LIBDCALL libd_encrypt_r)(char *glibc_block,
                                     int edflag,
                                     struct crypt_data *__restrict data) {
	libc_encrypt_r(glibc_block, edflag, data);
}

DECL_END

DEFINE_PUBLIC_ALIAS(DOS$setkey, libd_setkey);
DEFINE_PUBLIC_ALIAS(DOS$crypt, libd_crypt);
DEFINE_PUBLIC_ALIAS(DOS$encrypt, libd_encrypt);
DEFINE_PUBLIC_ALIAS(DOS$crypt_r, libd_crypt_r);
DEFINE_PUBLIC_ALIAS(DOS$setkey_r, libd_setkey_r);
DEFINE_PUBLIC_ALIAS(DOS$encrypt_r, libd_encrypt_r);

#endif /* !GUARD_LIBC_AUTO_DOSABI_CRYPT_C */
