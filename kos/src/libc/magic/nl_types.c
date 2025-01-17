/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
%(c_prefix){
/* (#) Portability: Cygwin        (/winsup/cygwin/include/nl_types.h) */
/* (#) Portability: DragonFly BSD (/include/nl_types.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/nl_types.h) */
/* (#) Portability: FreeBSD       (/include/nl_types.h) */
/* (#) Portability: GNU C Library (/catgets/nl_types.h) */
/* (#) Portability: GNU Hurd      (/usr/include/nl_types.h) */
/* (#) Portability: NetBSD        (/include/nl_types.h) */
/* (#) Portability: OpenBSD       (/include/nl_types.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/nl_types.h) */
/* (#) Portability: diet libc     (/include/nl_types.h) */
/* (#) Portability: libc4/5       (/include/nl_types.h) */
/* (#) Portability: libc6         (/include/nl_types.h) */
/* (#) Portability: musl libc     (/include/nl_types.h) */
/* (#) Portability: uClibc        (/include/nl_types.h) */
}

%[define_replacement(locale_t = __locale_t)]
%[default:section(".text.crt.dos.heap.malloc")]

%[insert:prefix(
#include <features.h>
)]%{

#define NL_SETD 1
#define NL_CAT_LOCALE 1

#ifdef __CC__
__SYSDECL_BEGIN

typedef void *nl_catd;
typedef int nl_item;

}

%[define_replacement(nl_catd = "void *")]
%[define_replacement(nl_item = "int")]

[[cp]] nl_catd catopen([[in]] char const *cat_name, int flag);
char *catgets([[inout]] nl_catd catalog, int set, int number, char const *string);
int catclose([[inout]] nl_catd catalog);

%{

__SYSDECL_END
#endif /* __CC__ */

}
