/* HASH CRC-32:0xce38290 */
/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_wcsrstrip_defined
#define __local_wcsrstrip_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_iswspace_defined
#define __local___localdep_iswspace_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_iswspace) && defined(__CRT_HAVE_iswspace)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswspace,(__WINT_TYPE__ __wc),iswspace,{ return __crt_iswspace(__wc); })
#elif defined(__crt_iswspace)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_iswspace)(__WINT_TYPE__ __wc) { return __crt_iswspace(__wc); }
#elif __has_builtin(__builtin_iswspace) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswspace)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswspace,(__WINT_TYPE__ __wc),iswspace,{ return __builtin_iswspace(__wc); })
#elif defined(__CRT_HAVE_iswspace)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_iswspace,(__WINT_TYPE__ __wc),iswspace,(__wc))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/iswspace.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_iswspace __LIBC_LOCAL_NAME(iswspace)
#endif /* !... */
#endif /* !__local___localdep_iswspace_defined */
#ifndef __local___localdep_wcsend_defined
#define __local___localdep_wcsend_defined
#ifdef __CRT_HAVE_wcsend
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wcsend,(__WCHAR_TYPE__ const *__restrict __str),wcsend,(__str))
#else /* __CRT_HAVE_wcsend */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcsend __LIBC_LOCAL_NAME(wcsend)
#endif /* !__CRT_HAVE_wcsend */
#endif /* !__local___localdep_wcsend_defined */
__NAMESPACE_LOCAL_END
#include <libc/unicode.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcsrstrip) __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsrstrip))(__WCHAR_TYPE__ *__str) {
	__WCHAR_TYPE__ *__endp = (__NAMESPACE_LOCAL_SYM __localdep_wcsend)(__str);
#if defined(__CRT_HAVE___unicode_descriptor) && __SIZEOF_WCHAR_T__ == 1
	/* Unicode support */
	for (;;) {
		__WCHAR_TYPE__ __ch = (__WCHAR_TYPE__)__endp[-1];
		if ((__NAMESPACE_LOCAL_SYM __localdep_iswspace)(__ch)) {
			/* Fast-pass: ASCII space characters. */
			--__endp;
		} else if (__ch >= 0x80) {
			__WCHAR_TYPE__ const *__new_endp = __endp;
			__CHAR32_TYPE__ __uni;
			__uni = __libc_unicode_readutf8_rev_n(&__new_endp, __str);
			if (!__libc_unicode_isspace(__uni))
				break;
			__endp = (__WCHAR_TYPE__ *)__new_endp;
		} else {
			break;
		}
	}
#else /* __CRT_HAVE___unicode_descriptor && __SIZEOF_WCHAR_T__ == 1 */
#if __SIZEOF_WCHAR_T__ == 2
	/* NOTE: No  need for special  handling for UTF-16 surrogates:
	 *       there are no unicode whitespace characters that would
	 *       need to be  encoded using surrogates  (so any  UTF-16
	 *       character that  might be  a space  is always  encoded
	 *       using a single word) */
#endif /* __SIZEOF_WCHAR_T__ == 2 */
	while (__endp > __str && (__NAMESPACE_LOCAL_SYM __localdep_iswspace)((__WCHAR_TYPE__)__endp[-1]))
		--__endp;
#endif /* !__CRT_HAVE___unicode_descriptor || __SIZEOF_WCHAR_T__ != 1 */
	*__endp = '\0'; /* Delete trailing space. */
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcsrstrip_defined
#define __local___localdep_wcsrstrip_defined
#define __localdep_wcsrstrip __LIBC_LOCAL_NAME(wcsrstrip)
#endif /* !__local___localdep_wcsrstrip_defined */
#endif /* !__local_wcsrstrip_defined */
