/* HASH CRC-32:0xb3c8b5aa */
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
/* (>) Standard: POSIX.2 (Issue 4, IEEE Std 1003.2-1992) */
/* (#) Portability: Cygwin        (/newlib/libc/include/fnmatch.h) */
/* (#) Portability: DJGPP         (/include/fnmatch.h) */
/* (#) Portability: DragonFly BSD (/include/fnmatch.h) */
/* (#) Portability: EMX kLIBC     (/libc/include/fnmatch.h) */
/* (#) Portability: FreeBSD       (/include/fnmatch.h) */
/* (#) Portability: GNU C Library (/posix/fnmatch.h) */
/* (#) Portability: GNU Hurd      (/usr/include/fnmatch.h) */
/* (#) Portability: NetBSD        (/include/fnmatch.h) */
/* (#) Portability: Newlib        (/newlib/libc/include/fnmatch.h) */
/* (#) Portability: OpenBSD       (/include/fnmatch.h) */
/* (#) Portability: OpenSolaris   (/usr/src/head/fnmatch.h) */
/* (#) Portability: diet libc     (/include/fnmatch.h) */
/* (#) Portability: libc4/5       (/include/fnmatch.h) */
/* (#) Portability: libc6         (/include/fnmatch.h) */
/* (#) Portability: mintlib       (/include/fnmatch.h) */
/* (#) Portability: musl libc     (/include/fnmatch.h) */
/* (#) Portability: uClibc        (/include/fnmatch.h) */
#ifndef _FNMATCH_H
#define _FNMATCH_H 1

#include "__stdinc.h"
#include "__crt.h"

#ifdef __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER
#pragma GCC system_header
#endif /* __COMPILER_HAVE_PRAGMA_GCC_SYSTEM_HEADER */

#include <features.h>

/* TODO: These constants should go into <asm/crt/fnmatch.h> */
#define FNM_PATHNAME    0x01 /* The wildcard character ('*') doesn't match slashes ('/') */
#define FNM_NOESCAPE    0x02 /* Backslashes characters ('\\') don't escape the follow-up character. */
#define FNM_PERIOD      0x04 /* A leading '.' can only be matched explicitly. */
#if (!defined(_POSIX_C_SOURCE) || _POSIX_C_SOURCE < 2 || defined(__USE_GNU))
#define FNM_FILE_NAME   FNM_PATHNAME /* GNU alias. */
#define FNM_LEADING_DIR 0x08 /* Ignore a sub-string '/...' when a match was already made. */
#define FNM_CASEFOLD    0x10 /* Ignore casing during character compares. */
#define FNM_EXTMATCH    0x20 /* Make use of ksh-like extended matching. */
#endif /* !_POSIX_C_SOURCE || _POSIX_C_SOURCE < 2 || __USE_GNU */
#define FNM_NOMATCH      1 /* The given `pattern' isn't matched. */
#ifdef __USE_XOPEN
#define FNM_NOSYS (-1) /* Never returned (would indicate that `fnmatch()' is not implemented) */
#endif /* __USE_XOPEN */

#ifdef __CC__
__SYSDECL_BEGIN

#ifdef __CRT_HAVE_fnmatch
/* >> fnmatch(3)
 * Match the given `name' against `pattern', returning
 * `0'  if  they match,  and  `FNM_NOMATCH' otherwise.
 * @param: match_flags:   Set of `FNM_*'
 * @return: 0           : `name' is matched by `pattern'
 * @return: FNM_NOMATCH : `name' is not matched by `pattern' */
__CDECLARE(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),int,__NOTHROW_NCX,fnmatch,(char const *__pattern, char const *__name, __STDC_INT_AS_UINT_T __match_flags),(__pattern,__name,__match_flags))
#else /* __CRT_HAVE_fnmatch */
#include <libc/local/fnmatch/fnmatch.h>
/* >> fnmatch(3)
 * Match the given `name' against `pattern', returning
 * `0'  if  they match,  and  `FNM_NOMATCH' otherwise.
 * @param: match_flags:   Set of `FNM_*'
 * @return: 0           : `name' is matched by `pattern'
 * @return: FNM_NOMATCH : `name' is not matched by `pattern' */
__NAMESPACE_LOCAL_USING_OR_IMPL(fnmatch, __FORCELOCAL __ATTR_ARTIFICIAL __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int __NOTHROW_NCX(__LIBCCALL fnmatch)(char const *__pattern, char const *__name, __STDC_INT_AS_UINT_T __match_flags) { return (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(fnmatch))(__pattern, __name, __match_flags); })
#endif /* !__CRT_HAVE_fnmatch */

__SYSDECL_END
#endif /* __CC__ */

#endif /* !_FNMATCH_H */
