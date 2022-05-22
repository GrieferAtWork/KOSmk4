/* HASH CRC-32:0x82813c22 */
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
#ifndef __local_wildwcscmp_defined
#define __local_wildwcscmp_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wildwcscmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wildwcscmp))(__WCHAR_TYPE__ const *__pattern, __WCHAR_TYPE__ const *__string) {
	for (;;) {
		if (!*__string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*__pattern == '*')
				++__pattern;
			return -(int)(__WCHAR_TYPE__)*__pattern;
		}
		if (!*__pattern)
			return (int)(__WCHAR_TYPE__)*__string; /* Pattern end doesn't match */
		if (*__pattern == '*') {
			__WCHAR_TYPE__ __card_post;
			/* Skip stars */
			do {
				++__pattern;
			} while (*__pattern == '*');
			if ((__card_post = *__pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (__card_post == '?')
				goto __next; /* Match any --> already found */
			for (;;) {
				__WCHAR_TYPE__ __ch = *__string++;
				if (__ch == __card_post) {
					/* Recursively check if the rest of the string and pattern match */
					if (!(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildwcscmp))(__string, __pattern))
						return 0;
				} else if (!__ch) {
					return -(int)(__WCHAR_TYPE__)__card_post; /* Wildcard suffix not found */
				}
			}
		}
		if (*__pattern == *__string || *__pattern == '?') {
__next:
			++__string;
			++__pattern;
			continue; /* single character match */
		}
		break; /* mismatch */
	}
	return (int)((__WCHAR_TYPE__)*__string - (__WCHAR_TYPE__)*__pattern);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wildwcscmp_defined
#define __local___localdep_wildwcscmp_defined
#define __localdep_wildwcscmp __LIBC_LOCAL_NAME(wildwcscmp)
#endif /* !__local___localdep_wildwcscmp_defined */
#endif /* !__local_wildwcscmp_defined */
