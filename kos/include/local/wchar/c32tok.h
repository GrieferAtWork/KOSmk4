/* HASH CRC-32:0xcfdbebf5 */
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
#ifndef __local_c32tok_defined
#define __local_c32tok_defined 1
/* Dependency: "wcsspn" from "wchar" */
#ifndef ____localdep_c32spn_defined
#define ____localdep_c32spn_defined 1
#if defined(__CRT_HAVE_wcsspn) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32spn,(__CHAR32_TYPE__ const *__haystack, __CHAR32_TYPE__ const *__accept),wcsspn,(__haystack,__accept))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsspn.h>
#define __localdep_c32spn(haystack, accept) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsspn))((__WCHAR_TYPE__ const *)(haystack), (__WCHAR_TYPE__ const *)(accept))
#else /* LIBC: c32spn */
#include <local/wchar/c32spn.h>
#define __localdep_c32spn (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32spn))
#endif /* c32spn... */
#endif /* !____localdep_c32spn_defined */

/* Dependency: "wcscspn" from "wchar" */
#ifndef ____localdep_c32cspn_defined
#define ____localdep_c32cspn_defined 1
#if defined(__CRT_HAVE_wcscspn) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c32cspn,(__CHAR32_TYPE__ const *__haystack, __CHAR32_TYPE__ const *__reject),wcscspn,(__haystack,__reject))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcscspn.h>
#define __localdep_c32cspn(haystack, reject) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscspn))((__WCHAR_TYPE__ const *)(haystack), (__WCHAR_TYPE__ const *)(reject))
#else /* LIBC: c32cspn */
#include <local/wchar/c32cspn.h>
#define __localdep_c32cspn (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32cspn))
#endif /* c32cspn... */
#endif /* !____localdep_c32cspn_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c32tok) __ATTR_NONNULL((2, 3)) __CHAR32_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c32tok))(__CHAR32_TYPE__ *__string,
                                                    __CHAR32_TYPE__ const *__restrict __delim,
                                                    __CHAR32_TYPE__ **__restrict __save_ptr) {
#line 566 "kos/src/libc/magic/string.c"
	__CHAR32_TYPE__ *__end;
	if (!__string)
		__string = *__save_ptr;
	if (!*__string) {
		*__save_ptr = __string;
		return __NULLPTR;
	}
	__string += __localdep_c32spn(__string, __delim);
	if (!*__string) {
		*__save_ptr = __string;
		return __NULLPTR;
	}
	__end = __string + __localdep_c32cspn(__string, __delim);
	if (!*__end) {
		*__save_ptr = __end;
		return __string;
	}
	*__end = '\0';
	*__save_ptr = __end + 1;
	return __string;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c32tok_defined */
