/* HASH CRC-32:0x7853d03e */
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
#ifndef __local_wildc16casecmp_defined
#define __local_wildc16casecmp_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_tolower16_defined
#define __local___localdep_tolower16_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_towlower) && defined(__CRT_HAVE_towlower) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW,__LIBDCALL,__localdep_tolower16,(__WINT16_TYPE__ __wc),towlower,{ return __crt_towlower(__wc); })
#elif defined(__crt_towlower) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL __ATTR_CONST __ATTR_WUNUSED __WINT16_TYPE__ __NOTHROW(__LIBDCALL __localdep_tolower16)(__WINT16_TYPE__ __wc) { return __crt_towlower(__wc); }
#elif __has_builtin(__builtin_towlower) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_towlower) && __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW,__LIBDCALL,__localdep_tolower16,(__WINT16_TYPE__ __wc),towlower,{ return __builtin_towlower(__wc); })
#elif defined(__CRT_HAVE_towlower) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW,__localdep_tolower16,(__WINT16_TYPE__ __wc),towlower,(__wc))
#elif defined(__CRT_HAVE_DOS$towlower)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_DOS(__ATTR_CONST __ATTR_WUNUSED,__WINT16_TYPE__,__NOTHROW,__localdep_tolower16,(__WINT16_TYPE__ __wc),towlower,(__wc))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/towlower.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tolower16 __NAMESPACE_LOCAL_TYPEHAX(__WINT16_TYPE__(__LIBDCALL*)(__WINT16_TYPE__),__WINT16_TYPE__(__LIBDCALL&)(__WINT16_TYPE__),towlower)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wctype/tolower16.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_tolower16 __LIBC_LOCAL_NAME(tolower16)
#endif /* !... */
#endif /* !__local___localdep_tolower16_defined */
__LOCAL_LIBC(wildc16casecmp) __ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2) int
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(wildc16casecmp))(__CHAR16_TYPE__ const *__pattern, __CHAR16_TYPE__ const *__string) {
	__CHAR16_TYPE__ __pattern_ch, __wcsing_ch;
	for (;;) {
		if (!*__string) {
			/* End of string (if the patter is empty, or only contains '*', we have a match) */
			while (*__pattern == '*')
				++__pattern;
			return -(int)*__pattern;
		}
		if (!*__pattern)
			return (int)*__string; /* Pattern end doesn't match */
		if (*__pattern == '*') {
			__CHAR16_TYPE__ __card_post;
			/* Skip stars */
			do {
				++__pattern;
			} while (*__pattern == '*');
			if ((__card_post = *__pattern++) == '\0')
				return 0; /* Pattern ends with '*' (matches everything) */
			if (__card_post == '?')
				goto __next; /* Match any --> already found */
			__card_post = (__CHAR16_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_tolower16)((__CHAR16_TYPE__)__card_post);
			for (;;) {
				__CHAR16_TYPE__ __ch = *__string++;
				if (__card_post == __ch || __card_post == (__CHAR16_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_tolower16)((__CHAR16_TYPE__)__ch)) {
					/* Recursively check if the rest of the string and pattern match */
					if (!(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wildc16casecmp))(__string, __pattern))
						return 0;
				} else if (!__ch) {
					return -(int)(__CHAR16_TYPE__)__card_post; /* Wildcard suffix not found */
				}
			}
		}
		__pattern_ch = *__pattern;
		__wcsing_ch  = *__string;
		if (__pattern_ch == __wcsing_ch || __pattern_ch == '?' ||
		    (__pattern_ch = (__CHAR16_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_tolower16)((__CHAR16_TYPE__)__pattern_ch),
		     __wcsing_ch  = (__CHAR16_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_tolower16)((__CHAR16_TYPE__)__wcsing_ch),
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
#ifndef __local___localdep_wildc16casecmp_defined
#define __local___localdep_wildc16casecmp_defined
#define __localdep_wildc16casecmp __LIBC_LOCAL_NAME(wildc16casecmp)
#endif /* !__local___localdep_wildc16casecmp_defined */
#endif /* !__local_wildc16casecmp_defined */
