/* HASH CRC-32:0xfea833c5 */
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
#ifndef __local_strrstrip_defined
#define __local_strrstrip_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_isspace_defined
#define __local___localdep_isspace_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/ctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_isspace) && defined(__CRT_HAVE_isspace)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace,(int __ch),isspace,{ return __crt_isspace(__ch); })
#elif defined(__crt_isspace)
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBCCALL __localdep_isspace)(int __ch) { return __crt_isspace(__ch); }
#elif __has_builtin(__builtin_isspace) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_isspace)
__CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace,(int __ch),isspace,{ return __builtin_isspace(__ch); })
#elif defined(__CRT_HAVE_isspace)
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace,(int __ch),isspace,(__ch))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/ctype/isspace.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isspace __LIBC_LOCAL_NAME(isspace)
#endif /* !... */
#endif /* !__local___localdep_isspace_defined */
#ifndef __local___localdep_strend_defined
#define __local___localdep_strend_defined
#ifdef __CRT_HAVE_strend
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),char *,__NOTHROW_NCX,__localdep_strend,(char const *__restrict __str),strend,(__str))
#else /* __CRT_HAVE_strend */
__NAMESPACE_LOCAL_END
#include <libc/local/string/strend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_strend __LIBC_LOCAL_NAME(strend)
#endif /* !__CRT_HAVE_strend */
#endif /* !__local___localdep_strend_defined */
__NAMESPACE_LOCAL_END
#include <libc/unicode.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(strrstrip) __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) char *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(strrstrip))(char *__str) {
	char *__endp = (__NAMESPACE_LOCAL_SYM __localdep_strend)(__str);
#ifdef __CRT_HAVE___unicode_descriptor
	/* Unicode support */
	for (;;) {
		unsigned char __ch = (unsigned char)__endp[-1];
		if ((__NAMESPACE_LOCAL_SYM __localdep_isspace)(__ch)) {
			/* Fast-pass: ASCII space characters. */
			--__endp;
		} else if (__ch >= 0x80) {
			char const *__new_endp = __endp;
			__CHAR32_TYPE__ __uni;
			__uni = __libc_unicode_readutf8_rev_n(&__new_endp, __str);
			if (!__libc_unicode_isspace(__uni))
				break;
			__endp = (char *)__new_endp;
		} else {
			break;
		}
	}
#else /* __CRT_HAVE___unicode_descriptor */







	while (__endp > __str && (__NAMESPACE_LOCAL_SYM __localdep_isspace)((unsigned char)__endp[-1]))
		--__endp;
#endif /* !__CRT_HAVE___unicode_descriptor */
	*__endp = '\0'; /* Delete trailing space. */
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_strrstrip_defined
#define __local___localdep_strrstrip_defined
#define __localdep_strrstrip __LIBC_LOCAL_NAME(strrstrip)
#endif /* !__local___localdep_strrstrip_defined */
#endif /* !__local_strrstrip_defined */
