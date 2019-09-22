/* HASH CRC-32:0x4a5bdf1 */
/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wildstrcasecmp_l_defined
#define __local_wildstrcasecmp_l_defined 1
/* Dependency: "tolower_l" from "ctype" */
#ifndef ____localdep_tolower_l_defined
#define ____localdep_tolower_l_defined 1
#if defined(__CRT_HAVE_tolower_l)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW_NCX,__localdep_tolower_l,(int __ch, __locale_t __locale),tolower_l,(__ch,__locale))
#else /* LIBC: tolower_l */
#include <local/ctype/tolower_l.h>
#define __localdep_tolower_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(tolower_l))
#endif /* tolower_l... */
#endif /* !____localdep_tolower_l_defined */

/* Dependency: "strcasecmp_l" from "string" */
#ifndef ____localdep_strcasecmp_l_defined
#define ____localdep_strcasecmp_l_defined 1
#if defined(__CRT_HAVE_strcasecmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),strcasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__stricmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_strcasecmp_l,(char const *__s1, char const *__s2, __locale_t __locale),_stricmp_l,(__s1,__s2,__locale))
#else /* LIBC: strcasecmp_l */
#include <local/string/strcasecmp_l.h>
#define __localdep_strcasecmp_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(strcasecmp_l))
#endif /* strcasecmp_l... */
#endif /* !____localdep_strcasecmp_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wildstrcasecmp_l) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wildstrcasecmp_l))(char const *__pattern,
                                                              char const *__string,
                                                              __locale_t __locale) {
#line 3723 "kos/src/libc/magic/string.c"
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
			__card_post = __localdep_tolower_l(__card_post, __locale);
			for (;;) {
				char __ch = *__string++;
				if (__card_post == __ch || __card_post == __localdep_tolower_l(__ch, __locale)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!__localdep_strcasecmp_l(__string, __pattern, __locale))
						return 0;
				} else if (!__ch) {
					return -(int)(unsigned char)__card_post; /* Wildcard suffix not found */
				}
			}
		}
		__pattern_ch = *__pattern;
		__string_ch = *__string;
		if (__pattern_ch == __string_ch || __pattern_ch == '?' ||
		   (__pattern_ch = __localdep_tolower_l(__pattern_ch, __locale),
		    __string_ch = __localdep_tolower_l(__string_ch, __locale),
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
#endif /* !__local_wildstrcasecmp_l_defined */
