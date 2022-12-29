/* HASH CRC-32:0x8b900e80 */
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
/* (#) Portability: EMX kLIBC     (/libc/include/crypt.h) */
/* (#) Portability: FreeBSD       (/lib/libcrypt/crypt.h) */
/* (#) Portability: GNU C Library (/crypt/crypt.h) */
/* (#) Portability: GNU Hurd      (/usr/include/crypt.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/crypt.h) */
/* (#) Portability: libc6         (/include/crypt.h) */
/* (#) Portability: mintlib       (/include/crypt.h) */
/* (#) Portability: musl libc     (/include/crypt.h) */
/* (#) Portability: uClibc        (/include/crypt.h) */
#ifndef _CRYPT_H
#define _CRYPT_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#ifdef __USE_GNU
#include <bits/crt/crypt_data.h>
#endif /* __USE_GNU */

#ifdef __CC__
__SYSDECL_BEGIN

/* >> setkey(3), setkey_r(3) */
__CDECLARE_VOID_OPT(,__NOTHROW_NCX,setkey,(char const *__key),(__key))
#if !defined(__crypt_defined) && defined(__CRT_HAVE_crypt)
#define __crypt_defined
/* >> crypt(3), crypt_r(3) */
__CDECLARE(__ATTR_IN(1) __ATTR_IN(2),char *,__NOTHROW_NCX,crypt,(char const *__key, char const *__salt),(__key,__salt))
#endif /* !__crypt_defined && __CRT_HAVE_crypt */
#if !defined(__encrypt_defined) && defined(__CRT_HAVE_encrypt)
#define __encrypt_defined
/* >> encrypt(3), encrypt_r(3) */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,encrypt,(char *__glibc_block, __STDC_INT_AS_UINT_T __edflag),(__glibc_block,__edflag))
#endif /* !__encrypt_defined && __CRT_HAVE_encrypt */

#ifdef __USE_GNU
/* >> crypt(3), crypt_r(3) */
__CDECLARE_OPT(__ATTR_IN(1) __ATTR_IN(2) __ATTR_NONNULL((3)),char *,__NOTHROW_NCX,crypt_r,(char const *__key, char const *__salt, struct crypt_data *__restrict __data),(__key,__salt,__data))
/* >> setkey(3), setkey_r(3) */
__CDECLARE_VOID_OPT(__ATTR_IN(1) __ATTR_NONNULL((2)),__NOTHROW_NCX,setkey_r,(char const *__key, struct crypt_data *__restrict __data),(__key,__data))
/* >> encrypt(3), encrypt_r(3) */
__CDECLARE_VOID_OPT(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,encrypt_r,(char *__glibc_block, int __edflag, struct crypt_data *__restrict __data),(__glibc_block,__edflag,__data))
#endif /* __USE_GNU */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_CRYPT_H */
