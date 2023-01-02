/* HASH CRC-32:0xf3ec9573 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c32tok_defined
#define __local_c32tok_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c32cspn_defined
#define __local___localdep_c32cspn_defined
#if defined(__CRT_HAVE_wcscspn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32cspn,(__CHAR32_TYPE__ const *__haystack, __CHAR32_TYPE__ const *__reject),wcscspn,(__haystack,__reject))
#elif defined(__CRT_HAVE_KOS$wcscspn)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32cspn,(__CHAR32_TYPE__ const *__haystack, __CHAR32_TYPE__ const *__reject),wcscspn,(__haystack,__reject))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcscspn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32cspn __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBKCALL*)(__CHAR32_TYPE__ const *,__CHAR32_TYPE__ const *),__SIZE_TYPE__(__LIBKCALL&)(__CHAR32_TYPE__ const *,__CHAR32_TYPE__ const *),wcscspn)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32cspn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32cspn __LIBC_LOCAL_NAME(c32cspn)
#endif /* !... */
#endif /* !__local___localdep_c32cspn_defined */
#ifndef __local___localdep_c32spn_defined
#define __local___localdep_c32spn_defined
#if defined(__CRT_HAVE_wcsspn) && __SIZEOF_WCHAR_T__ == 4 && defined(__LIBCCALL_IS_LIBKCALL)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32spn,(__CHAR32_TYPE__ const *__haystack, __CHAR32_TYPE__ const *__accept),wcsspn,(__haystack,__accept))
#elif defined(__CRT_HAVE_KOS$wcsspn)
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_IN(1) __ATTR_IN(2),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32spn,(__CHAR32_TYPE__ const *__haystack, __CHAR32_TYPE__ const *__accept),wcsspn,(__haystack,__accept))
#elif __SIZEOF_WCHAR_T__ == 4
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsspn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32spn __NAMESPACE_LOCAL_TYPEHAX(__SIZE_TYPE__(__LIBKCALL*)(__CHAR32_TYPE__ const *,__CHAR32_TYPE__ const *),__SIZE_TYPE__(__LIBKCALL&)(__CHAR32_TYPE__ const *,__CHAR32_TYPE__ const *),wcsspn)
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c32spn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c32spn __LIBC_LOCAL_NAME(c32spn)
#endif /* !... */
#endif /* !__local___localdep_c32spn_defined */
__LOCAL_LIBC(c32tok) __ATTR_IN(2) __ATTR_INOUT(3) __ATTR_INOUT_OPT(1) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32tok))(__CHAR32_TYPE__ *__str, __CHAR32_TYPE__ const *__restrict __delim, __CHAR32_TYPE__ **__restrict __save_ptr) {
	__CHAR32_TYPE__ *__end;
	if (!__str)
		__str = *__save_ptr;
	if (!*__str) {
		*__save_ptr = __str;
		return __NULLPTR;
	}
	__str += (__NAMESPACE_LOCAL_SYM __localdep_c32spn)(__str, __delim);
	if (!*__str) {
		*__save_ptr = __str;
		return __NULLPTR;
	}
	__end = __str + (__NAMESPACE_LOCAL_SYM __localdep_c32cspn)(__str, __delim);
	if (!*__end) {
		*__save_ptr = __end;
		return __str;
	}
	*__end = '\0';
	*__save_ptr = __end + 1;
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32tok_defined
#define __local___localdep_c32tok_defined
#define __localdep_c32tok __LIBC_LOCAL_NAME(c32tok)
#endif /* !__local___localdep_c32tok_defined */
#endif /* !__local_c32tok_defined */
