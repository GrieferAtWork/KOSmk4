/* HASH CRC-32:0xeb46e96d */
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
#ifndef _NL_TYPES_H
#define _NL_TYPES_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

#define NL_SETD 1
#define NL_CAT_LOCALE 1

#ifdef __CC__
__SYSDECL_BEGIN

typedef void *nl_catd;
typedef int nl_item;

__CDECLARE_OPT(__ATTR_IN(1),nl_catd,__NOTHROW_RPC,catopen,(char const *__cat_name, int __flag),(__cat_name,__flag))
__CDECLARE_OPT(,char *,__NOTHROW_NCX,catgets,(nl_catd __catalog, int __set, int __number, char const *__string),(__catalog,__set,__number,__string))
__CDECLARE_OPT(,int,__NOTHROW_NCX,catclose,(nl_catd __catalog),(__catalog))

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_NL_TYPES_H */
