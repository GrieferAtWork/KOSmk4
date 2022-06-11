/* HASH CRC-32:0xcc0d36d9 */
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
#ifndef __local_c32rstrip_defined
#define __local_c32rstrip_defined
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32end_defined
#define __local___localdep_c32end_defined
#if defined(__CRT_HAVE_wcsend) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32end,(__CHAR32_TYPE__ const *__restrict __str),wcsend,(__str))
#elif defined(__CRT_HAVE_KOS$wcsend)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32end,(__CHAR32_TYPE__ const *__restrict __str),wcsend,(__str))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsend.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32end __NAMESPACE_LOCAL_TYPEHAX(__CHAR32_TYPE__ *(__LIBKCALL*)(__CHAR32_TYPE__ const *__restrict),__CHAR32_TYPE__ *(__LIBKCALL&)(__CHAR32_TYPE__ const *__restrict),wcsend)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32end.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32end __LIBC_LOCAL_NAME(c32end)
#endif /* !... */
#endif /* !__local___localdep_c32end_defined */
#ifndef __local___localdep_isspace32_defined
#define __local___localdep_isspace32_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/wctype.h>
__NAMESPACE_LOCAL_BEGIN
#if defined(__crt_iswspace) && defined(__CRT_HAVE_iswspace) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,__localdep_isspace32,(__WINT32_TYPE__ __wc),iswspace,{ return __crt_iswspace(__wc); })
#elif defined(__crt_iswspace) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL __ATTR_CONST __ATTR_WUNUSED int __NOTHROW(__LIBKCALL __localdep_isspace32)(__WINT32_TYPE__ __wc) { return __crt_iswspace(__wc); }
#elif __has_builtin(__builtin_iswspace) && defined(__LIBC_BIND_CRTBUILTINS) && defined(__CRT_HAVE_iswspace) && __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CEIREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__LIBKCALL,__localdep_isspace32,(__WINT32_TYPE__ __wc),iswspace,{ return __builtin_iswspace(__wc); })
#elif defined(__CRT_HAVE_iswspace) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace32,(__WINT32_TYPE__ __wc),iswspace,(__wc))
#elif defined(__CRT_HAVE_KOS$iswspace)
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT_KOS(__ATTR_CONST __ATTR_WUNUSED,int,__NOTHROW,__localdep_isspace32,(__WINT32_TYPE__ __wc),iswspace,(__wc))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wctype/iswspace.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isspace32 __NAMESPACE_LOCAL_TYPEHAX(int(__LIBKCALL*)(__WINT32_TYPE__),int(__LIBKCALL&)(__WINT32_TYPE__),iswspace)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.wctype/isspace32.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_isspace32 __LIBC_LOCAL_NAME(isspace32)
#endif /* !... */
#endif /* !__local___localdep_isspace32_defined */
__NAMESPACE_LOCAL_END
#include <libc/unicode.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32rstrip) __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_IN(1) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32rstrip))(__CHAR32_TYPE__ *__str) {
	__CHAR32_TYPE__ *__endp = (__NAMESPACE_LOCAL_SYM __localdep_c32end)(__str);


























	while (__endp > __str && (__NAMESPACE_LOCAL_SYM __localdep_isspace32)((__CHAR32_TYPE__)__endp[-1]))
		--__endp;

	*__endp = '\0'; /* Delete trailing space. */
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32rstrip_defined
#define __local___localdep_c32rstrip_defined
#define __localdep_c32rstrip __LIBC_LOCAL_NAME(c32rstrip)
#endif /* !__local___localdep_c32rstrip_defined */
#endif /* !__local_c32rstrip_defined */
