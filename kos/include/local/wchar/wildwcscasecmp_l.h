/* HASH CRC-32:0x7b422f96 */
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
#ifndef __local_wildwcscasecmp_l_defined
#define __local_wildwcscasecmp_l_defined 1
/* Dependency: "towlower_l" from "wctype" */
#ifndef ____localdep_towlower_l_defined
#define ____localdep_towlower_l_defined 1
#if defined(__CRT_HAVE_towlower_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),towlower_l,(__wc,__locale))
#elif defined(__CRT_HAVE__towlower_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),_towlower_l,(__wc,__locale))
#elif defined(__CRT_HAVE___towlower_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),__towlower_l,(__wc,__locale))
#else /* LIBC: towlower_l */
#include <local/wctype/towlower_l.h>
#define __localdep_towlower_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(towlower_l))
#endif /* towlower_l... */
#endif /* !____localdep_towlower_l_defined */

/* Dependency: "wcscasecmp_l" from "wchar" */
#ifndef ____localdep_wcscasecmp_l_defined
#define ____localdep_wcscasecmp_l_defined 1
#if defined(__CRT_HAVE_wcscasecmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcscasecmp_l,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcscasecmp_l,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_wcsicmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcscasecmp_l,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2, __locale_t __locale),wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscasecmp_l)
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_wcscasecmp_l,(__WCHAR_TYPE__ const *__s1, __WCHAR_TYPE__ const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#else /* LIBC: wcscasecmp_l */
#include <local/wchar/wcscasecmp_l.h>
#define __localdep_wcscasecmp_l (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscasecmp_l))
#endif /* wcscasecmp_l... */
#endif /* !____localdep_wcscasecmp_l_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wildwcscasecmp_l) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wildwcscasecmp_l))(__WCHAR_TYPE__ const *__pattern,
                                                              __WCHAR_TYPE__ const *__string,
                                                              __locale_t __locale) {
#line 3808 "kos/src/libc/magic/string.c"
	__WCHAR_TYPE__ __card_post, __pattern_ch, __wcsing_ch;
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
			__card_post = (__WCHAR_TYPE__)__localdep_towlower_l(__card_post, __locale);
			for (;;) {
				__WCHAR_TYPE__ __ch = *__string++;
				if (__card_post == __ch || __card_post == (__WCHAR_TYPE__)__localdep_towlower_l(__ch, __locale)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!__localdep_wcscasecmp_l(__string, __pattern, __locale))
						return 0;
				} else if (!__ch) {
					return -(int)(__WCHAR_TYPE__)__card_post; /* Wildcard suffix not found */
				}
			}
		}
		__pattern_ch = *__pattern;
		__wcsing_ch = *__string;
		if (__pattern_ch == __wcsing_ch || __pattern_ch == '?' ||
		   (__pattern_ch = (__WCHAR_TYPE__)__localdep_towlower_l(__pattern_ch, __locale),
		    __wcsing_ch = (__WCHAR_TYPE__)__localdep_towlower_l(__wcsing_ch, __locale),
		    __pattern_ch == __wcsing_ch)) {
__next:
			++__string;
			++__pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((__WCHAR_TYPE__)__wcsing_ch - (__WCHAR_TYPE__)__pattern_ch);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wildwcscasecmp_l_defined */
