/* HASH CRC-32:0xb024d84b */
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
/* Setup DES tables according KEY */
__CDECLARE_VOID_OPT(__ATTR_NONNULL((1)),__NOTHROW_NCX,setkey,(char const *__key),(__key))
#ifndef __crypt_defined
#define __crypt_defined 1
#ifdef __CRT_HAVE_crypt
/* Encrypt at most 8 characters from KEY using salt to perturb DES */
__CDECLARE(__ATTR_NONNULL((1, 2)),char *,__NOTHROW_NCX,crypt,(char const *__key, char const *__salt),(__key,__salt))
#else /* __CRT_HAVE_crypt */
#undef __crypt_defined
#endif /* !__CRT_HAVE_crypt */
#endif /* !__crypt_defined */
#ifndef __encrypt_defined
#define __encrypt_defined 1
#ifdef __CRT_HAVE_encrypt
/* Encrypt data in BLOCK in place if EDFLAG is zero; otherwise decrypt block in place */
__CDECLARE_VOID(__ATTR_NONNULL((1)),__NOTHROW_NCX,encrypt,(char *__glibc_block, __STDC_INT_AS_UINT_T __edflag),(__glibc_block,__edflag))
#else /* __CRT_HAVE_encrypt */
#undef __encrypt_defined
#endif /* !__CRT_HAVE_encrypt */
#endif /* !__encrypt_defined */

#ifdef __USE_GNU
/* Reentrant versions of the functions above.
 * The additional argument points to a structure where the results are placed in.  */

/* Encrypt at most 8 characters from KEY using salt to perturb DES */
__CDECLARE_OPT(__ATTR_NONNULL((1, 2, 3)),char *,__NOTHROW_NCX,crypt_r,(char const *__key, char const *__salt, struct crypt_data *__restrict __data),(__key,__salt,__data))
/* Setup DES tables according KEY */
__CDECLARE_VOID_OPT(__ATTR_NONNULL((1, 2)),__NOTHROW_NCX,setkey_r,(char const *__key, struct crypt_data *__restrict __data),(__key,__data))
/* Encrypt data in BLOCK in place if EDFLAG is zero; otherwise decrypt block in place */
__CDECLARE_VOID_OPT(__ATTR_NONNULL((1, 3)),__NOTHROW_NCX,encrypt_r,(char *__glibc_block, int __edflag, struct crypt_data *__restrict __data),(__glibc_block,__edflag,__data))
#endif /* __USE_GNU */

#endif /* __CC__ */

__SYSDECL_END

#endif /* !_CRYPT_H */
