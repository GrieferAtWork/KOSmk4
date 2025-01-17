/* HASH CRC-32:0x12525734 */
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
#ifndef GUARD_LIBC_AUTO_REGEXP_C
#define GUARD_LIBC_AUTO_REGEXP_C 1

#include "../api.h"
#include <hybrid/typecore.h>
#include <kos/types.h>
#include "regexp.h"
#include "../user/regex.h"

DECL_BEGIN

#include "../libc/globals.h"
#ifndef __KERNEL__
#include <libc/template/locN.h>
/* >> step(3)
 * Find the next matching position in `string', given `expbuf' as previously passed to `compile(3)'
 * @return: 0: No match
 * @return: 1: Match was found in range `[loc1,loc2)' (yes: these are global variables) */
INTERN ATTR_SECTION(".text.crt.compat.glibc.regex") int
NOTHROW_NCX(LIBCCALL libc_step)(char const *string,
                                char const *expbuf) {
	regmatch_t match;
	expbuf = (char *)((__UINTPTR_TYPE__)(expbuf + __COMPILER_ALIGNOF(regex_t) /*- 1*/) & /* Missing "-1" for compat with Glibc bug */
	                  ~(__COMPILER_ALIGNOF(regex_t) - 1));
	if (libc_regexec((regex_t const *)expbuf, string, 1, &match, __REG_NOTEOL) != 0)
		return 0;
	loc1 = (char *)string + match.rm_so;
	loc2 = (char *)string + match.rm_eo;
	return 1;
}
#include <libc/template/locN.h>
/* >> advance(3)
 * Match the beginning of `string' against `expbuf' as previously passed to `compile(3)'
 * @return: 0: No match (or just not at the beginning of `string')
 * @return: 1: Match was found in range `[string,loc2)' (`string' being the first
 *             argument  to this  function, and  `loc2' being  a global variable) */
INTERN ATTR_SECTION(".text.crt.compat.glibc.regex") int
NOTHROW_NCX(LIBCCALL libc_advance)(char const *string,
                                   char const *expbuf) {
	regmatch_t match;
	expbuf = (char *)((__UINTPTR_TYPE__)(expbuf + __COMPILER_ALIGNOF(regex_t) /*- 1*/) & /* Missing "-1" for compat with Glibc bug */
	                  ~(__COMPILER_ALIGNOF(regex_t) - 1));
	if (libc_regexec((regex_t const *)expbuf, string, 1, &match, __REG_NOTEOL) != 0)
		return 0;
	if (match.rm_so != 0)
		return 0;
	loc2 = (char *)string + match.rm_eo;
	return 1;
}
#endif /* !__KERNEL__ */

DECL_END

#ifndef __KERNEL__
DEFINE_PUBLIC_ALIAS_P(__step,libc_step,,int,NOTHROW_NCX,LIBCCALL,(char const *string, char const *expbuf),(string,expbuf));
DEFINE_PUBLIC_ALIAS_P(step,libc_step,,int,NOTHROW_NCX,LIBCCALL,(char const *string, char const *expbuf),(string,expbuf));
DEFINE_PUBLIC_ALIAS_P(__advance,libc_advance,,int,NOTHROW_NCX,LIBCCALL,(char const *string, char const *expbuf),(string,expbuf));
DEFINE_PUBLIC_ALIAS_P(advance,libc_advance,,int,NOTHROW_NCX,LIBCCALL,(char const *string, char const *expbuf),(string,expbuf));
#endif /* !__KERNEL__ */

#endif /* !GUARD_LIBC_AUTO_REGEXP_C */
