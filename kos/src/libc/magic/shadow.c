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
/* (#) Portability: GNU C Library (/shadow/shadow.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/shadow.h) */
/* (#) Portability: diet libc     (/include/shadow.h) */
/* (#) Portability: musl libc     (/include/shadow.h) */
/* (#) Portability: uClibc        (/include/shadow.h) */
}

%[define_replacement(sigset_t = "struct __sigset_struct")]
%[default:section(".text.crt{|.dos}.database.shadow")]


%{
#include <features.h>
#include <paths.h>

#include <bits/crt/db/spwd.h>

#ifdef _PATH_SHADOW
#define SHADOW _PATH_SHADOW /* `/etc/shadow' */
#endif /* _PATH_SHADOW */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __std_FILE_defined
#define __std_FILE_defined 1
__NAMESPACE_STD_BEGIN
typedef __FILE FILE;
__NAMESPACE_STD_END
#endif /* !__std_FILE_defined */

#ifndef __CXX_SYSTEM_HEADER
#ifndef __FILE_defined
#define __FILE_defined 1
__NAMESPACE_STD_USING(FILE)
#endif /* !__FILE_defined */
#endif /* !__CXX_SYSTEM_HEADER */

#ifndef __size_t_defined
#define __size_t_defined 1
typedef __SIZE_TYPE__ size_t;
#endif /* !__size_t_defined */

}


[[cp]]
void setspent();

[[cp_nokos]]
void endspent();

[[cp, decl_include("<bits/crt/db/spwd.h>")]]
struct spwd *getspent();

[[cp, decl_include("<bits/crt/db/spwd.h>")]]
struct spwd *getspnam([[nonnull]] char const *__restrict name);

[[cp, decl_include("<bits/crt/db/spwd.h>")]]
struct spwd *sgetspent([[nonnull]] char const *__restrict string);

[[cp, decl_include("<bits/crt/db/spwd.h>")]]
struct spwd *fgetspent([[nonnull]] $FILE *__restrict stream);

[[cp, decl_include("<bits/crt/db/spwd.h>")]]
int putspent([[nonnull]] struct spwd const *__restrict p,
             [[nonnull]] $FILE *__restrict stream);

%
%#ifdef __USE_MISC
[[cp, decl_include("<bits/crt/db/spwd.h>")]]
int getspent_r([[nonnull]] struct spwd *__restrict result_buf,
               [[outp(buflen)]] char *__restrict buffer, size_t buflen,
               [[nonnull]] struct spwd **__restrict result);

[[cp, doc_alias("getspent_r"), decl_include("<bits/crt/db/spwd.h>")]]
int getspnam_r([[nonnull]] char const *__restrict name,
               [[nonnull]] struct spwd *__restrict result_buf,
               [[nonnull]] char *__restrict buffer, size_t buflen,
               [[nonnull]] struct spwd **__restrict result);

[[cp, doc_alias("getspent_r"), decl_include("<bits/crt/db/spwd.h>")]]
int sgetspent_r([[nonnull]] char const *__restrict string,
                [[nonnull]] struct spwd *__restrict result_buf,
                [[nonnull]] char *__restrict buffer, size_t buflen,
                [[nonnull]] struct spwd **__restrict result);

[[cp, doc_alias("getspent_r"), decl_include("<bits/crt/db/spwd.h>")]]
int fgetspent_r([[nonnull]] $FILE *__restrict stream,
                [[nonnull]] struct spwd *__restrict result_buf,
                [[nonnull]] char *__restrict buffer, size_t buflen,
                [[nonnull]] struct spwd **__restrict result);
%#endif /* __USE_MISC */

[[cp_kos]] int lckpwdf();
int ulckpwdf();


%{

__SYSDECL_END
#endif /* __CC__ */

}
