/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: FreeBSD       (/lib/libcrypt/crypt.h) */
/* (#) Portability: GNU C Library (/crypt/crypt.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/crypt.h) */
/* (#) Portability: musl libc     (/include/crypt.h) */
/* (#) Portability: uClibc        (/include/crypt.h) */
}

%[default:section(".text.crt{|.dos}.string.encrypt")]

%[insert:prefix(
#include <features.h>
)]%{

#ifdef __USE_GNU
#include <bits/crt/crypt_data.h>
#endif /* __USE_GNU */

#ifdef __CC__
__SYSDECL_BEGIN

}

void setkey([[nonnull]] char const *key);

[[guard]]
char *crypt([[nonnull]] char const *key, [[nonnull]] char const *salt);

[[guard, decl_include("<features.h>")]]
void encrypt([[nonnull]] char *glibc_block, __STDC_INT_AS_UINT_T edflag);

%
%#ifdef __USE_GNU
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

__SYSDECL_END
#endif /* __CC__ */

}
