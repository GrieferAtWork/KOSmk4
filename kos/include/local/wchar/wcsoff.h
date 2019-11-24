/* HASH CRC-32:0xcc6b7918 */
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
#ifndef __local_wcsoff_defined
#define __local_wcsoff_defined 1
/* Dependency: "wcschrnul" from "wchar" */
#ifndef ____localdep_wcschrnul_defined
#define ____localdep_wcschrnul_defined 1
#ifdef __CRT_HAVE_wcschrnul
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wcschrnul,(__WCHAR_TYPE__ const *__haystack, __WCHAR_TYPE__ __needle),wcschrnul,(__haystack,__needle))
#else /* LIBC: wcschrnul */
#include <local/wchar/wcschrnul.h>
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_wcschrnul (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))
#endif /* wcschrnul... */
#endif /* !____localdep_wcschrnul_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
__LOCAL_LIBC(wcsoff) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsoff))(__WCHAR_TYPE__ const *__restrict __haystack,
                                                    __WCHAR_TYPE__ __needle) {
#line 2577 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_wcschrnul(__haystack, __needle) - __haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcsoff_defined */
