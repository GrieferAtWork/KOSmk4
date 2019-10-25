/* HASH CRC-32:0x5c5318a6 */
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
#ifndef __local_wcstok_defined
#define __local_wcstok_defined 1
/* Dependency: "wcsspn" from "wchar" */
#ifndef ____localdep_wcsspn_defined
#define ____localdep_wcsspn_defined 1
#ifdef __std___localdep_wcsspn_defined
__NAMESPACE_STD_USING(__localdep_wcsspn)
#elif defined(__CRT_HAVE_wcsspn)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcsspn,(__WCHAR_TYPE__ const *__haystack, __WCHAR_TYPE__ const *__accept),wcsspn,(__haystack,__accept))
#else /* LIBC: wcsspn */
#include <local/wchar/wcsspn.h>
#define __localdep_wcsspn (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsspn))
#endif /* wcsspn... */
#endif /* !____localdep_wcsspn_defined */

/* Dependency: "wcscspn" from "wchar" */
#ifndef ____localdep_wcscspn_defined
#define ____localdep_wcscspn_defined 1
#ifdef __std___localdep_wcscspn_defined
__NAMESPACE_STD_USING(__localdep_wcscspn)
#elif defined(__CRT_HAVE_wcscspn)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_wcscspn,(__WCHAR_TYPE__ const *__haystack, __WCHAR_TYPE__ const *__reject),wcscspn,(__haystack,__reject))
#else /* LIBC: wcscspn */
#include <local/wchar/wcscspn.h>
#define __localdep_wcscspn (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscspn))
#endif /* wcscspn... */
#endif /* !____localdep_wcscspn_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(wcstok) __ATTR_NONNULL((2, 3)) __WCHAR_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcstok))(__WCHAR_TYPE__ *__string,
                                                    __WCHAR_TYPE__ const *__restrict __delim,
                                                    __WCHAR_TYPE__ **__restrict __save_ptr) {
#line 504 "kos/src/libc/magic/string.c"
	__WCHAR_TYPE__ *__end;
	if (!__string)
		__string = *__save_ptr;
	if (!*__string) {
		*__save_ptr = __string;
		return __NULLPTR;
	}
	__string += __localdep_wcsspn(__string, __delim);
	if (!*__string) {
		*__save_ptr = __string;
		return __NULLPTR;
	}
	__end = __string + __localdep_wcscspn(__string, __delim);
	if (!*__end) {
		*__save_ptr = __end;
		return __string;
	}
	*__end = '\0';
	*__save_ptr = __end + 1;
	return __string;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcstok_defined */
