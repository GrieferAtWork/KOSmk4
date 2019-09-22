/* Copyright (c) 2019 Griefer@Work                                            *
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
#ifndef GUARD_LIBC_USER_CRYPT_C
#define GUARD_LIBC_USER_CRYPT_C 1

#include "../api.h"
#include "crypt.h"

DECL_BEGIN





/*[[[start:implementation]]]*/

/*[[[head:crypt,hash:CRC-32=0xfbc2fdb5]]]*/
/* Encrypt at most 8 characters from KEY using salt to perturb DES */
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.encrypt.crypt") char *
NOTHROW_NCX(LIBCCALL libc_crypt)(char const *key,
                                 char const *salt)
/*[[[body:crypt]]]*/
{
	CRT_UNIMPLEMENTED("crypt"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:crypt]]]*/

/*[[[head:setkey,hash:CRC-32=0x7bf52d68]]]*/
/* Setup DES tables according KEY */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.encrypt.setkey") void
NOTHROW_NCX(LIBCCALL libc_setkey)(char const *key)
/*[[[body:setkey]]]*/
{
	CRT_UNIMPLEMENTED("setkey"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:setkey]]]*/

/*[[[head:encrypt,hash:CRC-32=0x4ca25de7]]]*/
/* Encrypt data in BLOCK in place if EDFLAG is zero; otherwise decrypt block in place */
INTERN NONNULL((1))
ATTR_WEAK ATTR_SECTION(".text.crt.string.encrypt.encrypt") void
NOTHROW_NCX(LIBCCALL libc_encrypt)(char *glibc_block,
                                   int edflag)
/*[[[body:encrypt]]]*/
{
	CRT_UNIMPLEMENTED("encrypt"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:encrypt]]]*/

/*[[[head:crypt_r,hash:CRC-32=0x1e1f0b]]]*/
/* Encrypt at most 8 characters from KEY using salt to perturb DES */
INTERN NONNULL((1, 2, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.string.encrypt.crypt_r") char *
NOTHROW_NCX(LIBCCALL libc_crypt_r)(char const *key,
                                   char const *salt,
                                   struct crypt_data *__restrict data)
/*[[[body:crypt_r]]]*/
{
	CRT_UNIMPLEMENTED("crypt_r"); /* TODO */
	libc_seterrno(ENOSYS);
	return NULL;
}
/*[[[end:crypt_r]]]*/

/*[[[head:setkey_r,hash:CRC-32=0x84fb22b1]]]*/
INTERN NONNULL((1, 2))
ATTR_WEAK ATTR_SECTION(".text.crt.string.encrypt.setkey_r") void
NOTHROW_NCX(LIBCCALL libc_setkey_r)(char const *key,
                                    struct crypt_data *__restrict data)
/*[[[body:setkey_r]]]*/
{
	CRT_UNIMPLEMENTED("setkey_r"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:setkey_r]]]*/

/*[[[head:encrypt_r,hash:CRC-32=0x5ac3c828]]]*/
/* Encrypt data in BLOCK in place if EDFLAG is zero; otherwise decrypt block in place */
INTERN NONNULL((1, 3))
ATTR_WEAK ATTR_SECTION(".text.crt.string.encrypt.encrypt_r") void
NOTHROW_NCX(LIBCCALL libc_encrypt_r)(char *glibc_block,
                                     int edflag,
                                     struct crypt_data *__restrict data)
/*[[[body:encrypt_r]]]*/
{
	CRT_UNIMPLEMENTED("encrypt_r"); /* TODO */
	libc_seterrno(ENOSYS);
}
/*[[[end:encrypt_r]]]*/

/*[[[end:implementation]]]*/



/*[[[start:exports,hash:CRC-32=0xd7ded9a8]]]*/
DEFINE_PUBLIC_WEAK_ALIAS(setkey, libc_setkey);
DEFINE_PUBLIC_WEAK_ALIAS(crypt, libc_crypt);
DEFINE_PUBLIC_WEAK_ALIAS(encrypt, libc_encrypt);
DEFINE_PUBLIC_WEAK_ALIAS(crypt_r, libc_crypt_r);
DEFINE_PUBLIC_WEAK_ALIAS(setkey_r, libc_setkey_r);
DEFINE_PUBLIC_WEAK_ALIAS(encrypt_r, libc_encrypt_r);
/*[[[end:exports]]]*/

DECL_END

#endif /* !GUARD_LIBC_USER_CRYPT_C */
