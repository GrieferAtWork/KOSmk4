/* HASH CRC-32:0x6d422556 */
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
#ifndef __local_c16tok_defined
#define __local_c16tok_defined 1
/* Dependency: "wcsspn" from "wchar" */
#ifndef ____localdep_c16spn_defined
#define ____localdep_c16spn_defined 1
#if defined(__CRT_HAVE_wcsspn) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16spn,(__CHAR16_TYPE__ const *__haystack, __CHAR16_TYPE__ const *__accept),wcsspn,(__haystack,__accept))
#elif defined(__CRT_HAVE_DOS$wcsspn)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16spn,(__CHAR16_TYPE__ const *__haystack, __CHAR16_TYPE__ const *__accept),wcsspn,(__haystack,__accept))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsspn.h>
#define __localdep_c16spn(haystack, accept) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsspn))((__WCHAR_TYPE__ const *)(haystack), (__WCHAR_TYPE__ const *)(accept))
#else /* LIBC: c16spn */
#include <local/wchar/c16spn.h>
#define __localdep_c16spn (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16spn))
#endif /* c16spn... */
#endif /* !____localdep_c16spn_defined */

/* Dependency: "wcscspn" from "wchar" */
#ifndef ____localdep_c16cspn_defined
#define ____localdep_c16cspn_defined 1
#if defined(__CRT_HAVE_wcscspn) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16cspn,(__CHAR16_TYPE__ const *__haystack, __CHAR16_TYPE__ const *__reject),wcscspn,(__haystack,__reject))
#elif defined(__CRT_HAVE_DOS$wcscspn)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)),__SIZE_TYPE__,__NOTHROW_NCX,__localdep_c16cspn,(__CHAR16_TYPE__ const *__haystack, __CHAR16_TYPE__ const *__reject),wcscspn,(__haystack,__reject))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcscspn.h>
#define __localdep_c16cspn(haystack, reject) (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcscspn))((__WCHAR_TYPE__ const *)(haystack), (__WCHAR_TYPE__ const *)(reject))
#else /* LIBC: c16cspn */
#include <local/wchar/c16cspn.h>
#define __localdep_c16cspn (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16cspn))
#endif /* c16cspn... */
#endif /* !____localdep_c16cspn_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16tok) __ATTR_NONNULL((2, 3)) __CHAR16_TYPE__ *
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c16tok))(__CHAR16_TYPE__ *__string,
                                                    __CHAR16_TYPE__ const *__restrict __delim,
                                                    __CHAR16_TYPE__ **__restrict __save_ptr) {
#line 504 "kos/src/libc/magic/string.c"
	__CHAR16_TYPE__ *__end;
	if (!__string)
		__string = *__save_ptr;
	if (!*__string) {
		*__save_ptr = __string;
		return __NULLPTR;
	}
	__string += __localdep_c16spn(__string, __delim);
	if (!*__string) {
		*__save_ptr = __string;
		return __NULLPTR;
	}
	__end = __string + __localdep_c16cspn(__string, __delim);
	if (!*__end) {
		*__save_ptr = __end;
		return __string;
	}
	*__end = '\0';
	*__save_ptr = __end + 1;
	return __string;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16tok_defined */
