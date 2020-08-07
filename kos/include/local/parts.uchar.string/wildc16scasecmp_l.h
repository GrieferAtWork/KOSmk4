/* HASH CRC-32:0xc4a14220 */
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
#ifndef __local_wildc16scasecmp_l_defined
#define __local_wildc16scasecmp_l_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c16scasecmp_l from parts.uchar.string */
#ifndef __local___localdep_c16scasecmp_l_defined
#define __local___localdep_c16scasecmp_l_defined 1
#if defined(__CRT_HAVE_wcscasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c16scasecmp_l,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$wcscasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c16scasecmp_l,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __locale_t __locale),wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE__wcsicmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c16scasecmp_l,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$_wcsicmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c16scasecmp_l,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __locale_t __locale),_wcsicmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE___wcscasecmp_l) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c16scasecmp_l,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#elif defined(__CRT_HAVE_DOS$__wcscasecmp_l)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),int,__NOTHROW_NCX,__localdep_c16scasecmp_l,(__CHAR16_TYPE__ const *__s1, __CHAR16_TYPE__ const *__s2, __locale_t __locale),__wcscasecmp_l,(__s1,__s2,__locale))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <local/wchar/wcscasecmp_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16scasecmp_l (*(int(__LIBDCALL *)(__CHAR16_TYPE__ const *, __CHAR16_TYPE__ const *, __locale_t))&__LIBC_LOCAL_NAME(wcscasecmp_l))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c16scasecmp_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16scasecmp_l __LIBC_LOCAL_NAME(c16scasecmp_l)
#endif /* !... */
#endif /* !__local___localdep_c16scasecmp_l_defined */
/* Dependency: towlower_l from wctype */
#ifndef __local___localdep_towlower_l_defined
#define __local___localdep_towlower_l_defined 1
#ifdef __CRT_HAVE_towlower_l
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),towlower_l,(__wc,__locale))
#elif defined(__CRT_HAVE__towlower_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),_towlower_l,(__wc,__locale))
#elif defined(__CRT_HAVE___towlower_l)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED,__WINT_TYPE__,__NOTHROW_NCX,__localdep_towlower_l,(__WINT_TYPE__ __wc, __locale_t __locale),__towlower_l,(__wc,__locale))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/wctype/towlower_l.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_towlower_l __LIBC_LOCAL_NAME(towlower_l)
#endif /* !... */
#endif /* !__local___localdep_towlower_l_defined */
__LOCAL_LIBC(wildc16scasecmp_l) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(wildc16scasecmp_l))(__CHAR16_TYPE__ const *__pattern, __CHAR16_TYPE__ const *__string, __locale_t __locale) {
	__CHAR16_TYPE__ __card_post, __pattern_ch, __wcsing_ch;
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
			__card_post = (__CHAR16_TYPE__)__localdep_towlower_l(__card_post, __locale);
			for (;;) {
				__CHAR16_TYPE__ __ch = *__string++;
				if (__card_post == __ch || __card_post == (__CHAR16_TYPE__)__localdep_towlower_l(__ch, __locale)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!__localdep_c16scasecmp_l(__string, __pattern, __locale))
						return 0;
				} else if (!__ch) {
					return -(int)(__CHAR16_TYPE__)__card_post; /* Wildcard suffix not found */
				}
			}
		}
		__pattern_ch = *__pattern;
		__wcsing_ch = *__string;
		if (__pattern_ch == __wcsing_ch || __pattern_ch == '?' ||
		   (__pattern_ch = (__CHAR16_TYPE__)__localdep_towlower_l(__pattern_ch, __locale),
		    __wcsing_ch = (__CHAR16_TYPE__)__localdep_towlower_l(__wcsing_ch, __locale),
		    __pattern_ch == __wcsing_ch)) {
__next:
			++__string;
			++__pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((__CHAR16_TYPE__)__wcsing_ch - (__CHAR16_TYPE__)__pattern_ch);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wildc16scasecmp_l_defined
#define __local___localdep_wildc16scasecmp_l_defined 1
#define __localdep_wildc16scasecmp_l __LIBC_LOCAL_NAME(wildc16scasecmp_l)
#endif /* !__local___localdep_wildc16scasecmp_l_defined */
#endif /* !__local_wildc16scasecmp_l_defined */
