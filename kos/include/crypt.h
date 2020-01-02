/* HASH CRC-32:0x9a56845c */
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
#ifndef _CRYPT_H
#define _CRYPT_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

/* Derived from GLibc: /usr/include/crypt.h */
/*
 * UFC-crypt: ultra fast crypt(3) implementation
 *
 * Copyright (C) 1991-2016 Free Software Foundation, Inc.
 *
 * The GNU C Library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * The GNU C Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the GNU C Library; if not, see
 * <http://www.gnu.org/licenses/>.
 *
 * @(#)crypt.h	1.5 12/20/96
 *
 */

__SYSDECL_BEGIN

#ifdef __CC__
#ifdef __CRT_HAVE_setkey
/* Setup DES tables according KEY */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,setkey,(char const *__key),(__key))
#endif /* setkey... */
#ifndef __crypt_defined
#define __crypt_defined 1
#ifdef __CRT_HAVE_crypt
/* Encrypt at most 8 characters from KEY using salt to perturb DES */
__CDECLARE(__ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,crypt,(char const *__key, char const *__salt),(__key,__salt))
#else /* LIBC: crypt */
#undef __crypt_defined
#endif /* crypt... */
#endif /* !__crypt_defined */
#ifndef __encrypt_defined
#define __encrypt_defined 1
#ifdef __CRT_HAVE_encrypt
/* Encrypt data in BLOCK in place if EDFLAG is zero; otherwise decrypt block in place */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,encrypt,(char *__glibc_block, int __edflag),(__glibc_block,__edflag))
#else /* LIBC: encrypt */
#undef __encrypt_defined
#endif /* encrypt... */
#endif /* !__encrypt_defined */

#ifdef __USE_GNU
/* Reentrant versions of the functions above.
 * The additional argument points to a structure where the results are placed in.  */
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma push_macro("keysched")
#pragma push_macro("sb0")
#pragma push_macro("sb1")
#pragma push_macro("sb2")
#pragma push_macro("sb3")
#pragma push_macro("crypt_3_buf")
#pragma push_macro("current_salt")
#pragma push_macro("current_saltbits")
#pragma push_macro("direction")
#pragma push_macro("initialized")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */
#undef keysched
#undef sb0
#undef sb1
#undef sb2
#undef sb3
#undef crypt_3_buf
#undef current_salt
#undef current_saltbits
#undef direction
#undef initialized
struct crypt_data {
	char             keysched[16 * 8];
	char             sb0[32768];
	char             sb1[32768];
	char             sb2[32768];
	char             sb3[32768];
	/* end-of-aligment-critical-data */
	char             crypt_3_buf[14];
	char             current_salt[2];
	__LONGPTR_TYPE__ current_saltbits;
	__INT32_TYPE__   direction;
	__INT32_TYPE__   initialized;
};
#ifdef __COMPILER_HAVE_PRAGMA_PUSHMACRO
#pragma pop_macro("initialized")
#pragma pop_macro("direction")
#pragma pop_macro("current_saltbits")
#pragma pop_macro("current_salt")
#pragma pop_macro("crypt_3_buf")
#pragma pop_macro("sb3")
#pragma pop_macro("sb2")
#pragma pop_macro("sb1")
#pragma pop_macro("sb0")
#pragma pop_macro("keysched")
#endif /* __COMPILER_HAVE_PRAGMA_PUSHMACRO */

#ifdef __CRT_HAVE_crypt_r
/* Encrypt at most 8 characters from KEY using salt to perturb DES */
__CDECLARE(__ATTR_NONNULL((1, 2, 3)),char *,__NOTHROW_NCX,crypt_r,(char const *__key, char const *__salt, struct crypt_data *__restrict __data),(__key,__salt,__data))
#endif /* crypt_r... */
#ifdef __CRT_HAVE_setkey_r
__CDECLARE_VOID(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,setkey_r,(char const *__key, struct crypt_data *__restrict __data),(__key,__data))
#endif /* setkey_r... */
#ifdef __CRT_HAVE_encrypt_r
/* Encrypt data in BLOCK in place if EDFLAG is zero; otherwise decrypt block in place */
__CDECLARE_VOID(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,encrypt_r,(char *__glibc_block, int __edflag, struct crypt_data *__restrict __data),(__glibc_block,__edflag,__data))
#endif /* encrypt_r... */
#endif /* __USE_GNU */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_CRYPT_H */
