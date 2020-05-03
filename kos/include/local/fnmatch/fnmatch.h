/* HASH CRC-32:0xe657e883 */
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
#ifndef __local_fnmatch_defined
#define __local_fnmatch_defined 1
#include <__crt.h>
/* Dependency: "tolower" from "ctype" */
#ifndef ____localdep_tolower_defined
#define ____localdep_tolower_defined 1
#if __has_builtin(__builtin_tolower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tolower)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),tolower,{ return __builtin_tolower(__ch); })
#elif defined(__CRT_HAVE_tolower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),tolower,(__ch))
#elif defined(__CRT_HAVE__tolower)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_tolower,(int __ch),_tolower,(__ch))
#else /* LIBC: tolower */
#include <local/ctype/tolower.h>
#define __localdep_tolower (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tolower))
#endif /* tolower... */
#endif /* !____localdep_tolower_defined */

__NAMESPACE_LOCAL_BEGIN
/* Match NAME against the filename pattern PATTERN,
 * returning zero if it matches, FNM_NOMATCH if not */
__LOCAL_LIBC(fnmatch) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(fnmatch))(char const *__pattern,
                                                     char const *__name,
                                                     int __match_flags) {
#line 77 "kos/src/libc/magic/fnmatch.c"
	char __card_post;
	for (;;) {
		if (!*__name) {
			/* End of name (if the patter is empty, or only contains '*', we have a match) */
			while (*__pattern == '*')
				++__pattern;
			goto __nomatch;
		}
		if (!*__pattern)
			goto __nomatch; /* Pattern end doesn't match */
		if (*__pattern == '*') {
			/* Skip leading asterisks */
			do {
				++__pattern;
			} while (*__pattern == '*');
			if ((__card_post = *__pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (__card_post == '?')
				goto __next; /* Match any --> already found */
			for (;;) {
				char __ch = *__name++;
				if (__ch == __card_post ||
				    ((__match_flags & 0x10) &&
				     __localdep_tolower(__ch) == __localdep_tolower(__card_post))) {
					/* Recursively check if the rest of the name and pattern match */
					if (!__LIBC_LOCAL_NAME(fnmatch)(__name, __pattern, __match_flags))
						return 0;
				} else if (!__ch) {
					goto __nomatch; /* Wildcard suffix not found */
				} else if (__ch == '/') {
					if ((__match_flags & 0x01))
						goto __nomatch;
					if ((__match_flags & 0x04) &&
					    __name[0] == '.' && __card_post != '.')
						goto __nomatch;
				}
			}
		}
		if (*__pattern == *__name) {
__next:
			++__name;
			++__pattern;
			continue; /* single character match */
		}
		if (*__pattern == '?') {
			if (*__name == '/') {
				if (__match_flags & 0x01)
					goto __nomatch;
				if ((__match_flags & 0x04) &&
				    __name[1] == '.' && __pattern[1] != '.')
					goto __nomatch;
			}
			goto __next;
		}
		break; /* mismatch */
	}
__nomatch:
	return 1;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_fnmatch_defined */
