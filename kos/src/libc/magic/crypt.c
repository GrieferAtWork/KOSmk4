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

%[default:section(".text.crt{|.dos}.string.encrypt")]

%{
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
}

@@Setup DES tables according KEY
void setkey([[nonnull]] char const *key);

@@Encrypt at most 8 characters from KEY using salt to perturb DES
[[guard]]
char *crypt([[nonnull]] char const *key, [[nonnull]] char const *salt);

@@Encrypt data in BLOCK in place if EDFLAG is zero; otherwise decrypt block in place
[[guard, decl_include("<features.h>")]]
void encrypt([[nonnull]] char *glibc_block, __STDC_INT_AS_UINT_T edflag);

%
%#ifdef __USE_GNU
%/* Reentrant versions of the functions above.
% * The additional argument points to a structure where the results are placed in.  */
%

[[doc_alias("crypt"), decl_include("<bits/crt/crypt_data.h>")]]
char *crypt_r([[nonnull]] char const *key,
              [[nonnull]] char const *salt,
              [[nonnull]] struct crypt_data *__restrict data);

[[doc_alias("setkey"), decl_include("<bits/crt/crypt_data.h>")]]
void setkey_r([[nonnull]] char const *key,
              [[nonnull]] struct crypt_data *__restrict data);

[[doc_alias("encrypt"), decl_include("<bits/crt/crypt_data.h>")]]
void encrypt_r([[nonnull]] char *glibc_block, int edflag,
               [[nonnull]] struct crypt_data *__restrict data);

%#endif /* __USE_GNU */

%{

#endif /* __CC__ */

__SYSDECL_END

}