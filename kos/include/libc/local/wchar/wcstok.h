/* HASH CRC-32:0xbf7f0c41 */
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
#ifndef __local_wcstok_defined
#define __local_wcstok_defined
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_wcscspn_defined
#define __local___localdep_wcscspn_defined
#ifdef __CRT_HAVE_wcscspn
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcscspn,(__WCHAR_TYPE__ const *__haystack, __WCHAR_TYPE__ const *__reject),wcscspn,(__haystack,__reject))
#else /* __CRT_HAVE_wcscspn */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcscspn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcscspn __LIBC_LOCAL_NAME(wcscspn)
#endif /* !__CRT_HAVE_wcscspn */
#endif /* !__local___localdep_wcscspn_defined */
#ifndef __local___localdep_wcsspn_defined
#define __local___localdep_wcsspn_defined
#ifdef __CRT_HAVE_wcsspn
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_ACCESS_RO(1) __ATTR_ACCESS_RO(2),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsspn,(__WCHAR_TYPE__ const *__haystack, __WCHAR_TYPE__ const *__accept),wcsspn,(__haystack,__accept))
#else /* __CRT_HAVE_wcsspn */
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsspn.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_wcsspn __LIBC_LOCAL_NAME(wcsspn)
#endif /* !__CRT_HAVE_wcsspn */
#endif /* !__local___localdep_wcsspn_defined */
__LOCAL_LIBC(wcstok) __ATTR_NONNULL((2, 3)) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcstok))(__WCHAR_TYPE__ *__str, __WCHAR_TYPE__ const *__restrict __delim, __WCHAR_TYPE__ **__restrict __save_ptr) {
	__WCHAR_TYPE__ *__end;
	if (!__str)
		__str = *__save_ptr;
	if (!*__str) {
		*__save_ptr = __str;
		return __NULLPTR;
	}
	__str += (__NAMESPACE_LOCAL_SYM __localdep_wcsspn)(__str, __delim);
	if (!*__str) {
		*__save_ptr = __str;
		return __NULLPTR;
	}
	__end = __str + (__NAMESPACE_LOCAL_SYM __localdep_wcscspn)(__str, __delim);
	if (!*__end) {
		*__save_ptr = __end;
		return __str;
	}
	*__end = '\0';
	*__save_ptr = __end + 1;
	return __str;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_wcstok_defined
#define __local___localdep_wcstok_defined
#define __localdep_wcstok __LIBC_LOCAL_NAME(wcstok)
#endif /* !__local___localdep_wcstok_defined */
#endif /* !__local_wcstok_defined */
