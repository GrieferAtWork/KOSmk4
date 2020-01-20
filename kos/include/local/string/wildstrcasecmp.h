/* HASH CRC-32:0xa9a5426e */
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
#ifndef __local_wildstrcasecmp_defined
#define __local_wildstrcasecmp_defined 1
/* Dependency: "tolower" from "ctype" */
#ifndef ____localdep_tolower_defined
#define ____localdep_tolower_defined 1
#if __has_builtin(__builtin_tolower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_tolower)
__EXTERNINLINE __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_tolower)(int __ch) { return __builtin_tolower(__ch); }
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
__LOCAL_LIBC(wildstrcasecmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wildstrcasecmp))(char const *__pattern,
                                                            char const *__string) {
#line 4161 "kos/src/libc/magic/string.c"
	char __card_post, __pattern_ch, __string_ch;
	for (;;) {
		if (!*__string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*__pattern == '*') ++__pattern;
			return -(int)*__pattern;
		}
		if (!*__pattern)
			return (int)*__string; /* Pattern end doesn't match */
		if (*__pattern == '*') {
			/* Skip stars */
			do {
				++__pattern;
			} while (*__pattern == '*');
			if ((__card_post = *__pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (__card_post == '?')
				goto __next; /* Match any --> already found */
			__card_post = __localdep_tolower(__card_post);
			for (;;) {
				char __ch = *__string++;
				if (__card_post == __ch || __card_post == __localdep_tolower(__ch)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!__LIBC_LOCAL_NAME(wildstrcasecmp)(__string, __pattern))
						return 0;
				} else if (!__ch) {
					return -(int)(unsigned char)__card_post; /* Wildcard suffix not found */
				}
			}
		}
		__pattern_ch = *__pattern;
		__string_ch = *__string;
		if (__pattern_ch == __string_ch || __pattern_ch == '?' ||
		   (__pattern_ch = __localdep_tolower(__pattern_ch),
		    __string_ch = __localdep_tolower(__string_ch),
		    __pattern_ch == __string_ch)) {
__next:
			++__string;
			++__pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((unsigned char)__string_ch - (unsigned char)__pattern_ch);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wildstrcasecmp_defined */
