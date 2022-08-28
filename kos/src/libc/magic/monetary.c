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
%(c_prefix){
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/winsup/cygwin/include/monetary.h) */
/* (#) Portability: DragonFly BSD (/include/monetary.h) */
/* (#) Portability: FreeBSD       (/include/monetary.h) */
/* (#) Portability: GNU C Library (/stdlib/monetary.h) */
/* (#) Portability: NetBSD        (/include/monetary.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/monetary.h) */
/* (#) Portability: libc6         (/include/monetary.h) */
/* (#) Portability: musl libc     (/include/monetary.h) */
}

%[default:section(".text.crt{|.dos}.utility.monetary")]


%[insert:prefix(
#include <features.h>
)]%[insert:prefix(
#include <bits/types.h>
)]%{

#ifdef __USE_XOPEN2K8
#include <xlocale.h>
#endif /* __USE_XOPEN2K8 */

#ifdef __CC__
__SYSDECL_BEGIN

#ifndef __size_t_defined
#define __size_t_defined
typedef __size_t size_t;
#endif /* !__size_t_defined */

#ifndef __ssize_t_defined
#define __ssize_t_defined
typedef __ssize_t ssize_t;
#endif /* !__ssize_t_defined */

}

[[decl_include("<hybrid/typecore.h>")]]
ssize_t strfmon([[out(return <= maxsize)]] char *__restrict s, size_t maxsize,
                [[in, format("strfmon")]] char const *__restrict format, ...);

%#ifdef __USE_XOPEN2K8
[[decl_include("<hybrid/typecore.h>")]]
[[export_alias("__strfmon_l")]]
ssize_t strfmon_l([[out(return <= maxsize)]] char *__restrict s, size_t maxsize, $locale_t loc,
                  [[in, format("strfmon")]] const char *__restrict format, ...);
%#endif /* __USE_XOPEN2K8 */


%{

__SYSDECL_END
#endif /* __CC__ */

}
