/* HASH CRC-32:0x9745dff8 */
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
#ifndef __local_wcsnroff_defined
#define __local_wcsnroff_defined 1
/* Dependency: "wcsnrchrnul" from "wchar" */
#ifndef ____localdep_wcsnrchrnul_defined
#define ____localdep_wcsnrchrnul_defined 1
#if defined(__CRT_HAVE_wcsnrchrnul)
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wcsnrchrnul,(__WCHAR_TYPE__ const *__restrict __haystack, __WCHAR_TYPE__ __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
#else /* LIBC: wcsnrchrnul */
#include <local/wchar/wcsnrchrnul.h>
/* Same as `wcsnrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_wcsnrchrnul (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))
#endif /* wcsnrchrnul... */
#endif /* !____localdep_wcsnrchrnul_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `wcsnrchrnul', but return the offset from `STR', rather than the actual address */
__LOCAL_LIBC(wcsnroff) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(wcsnroff))(__WCHAR_TYPE__ const *__restrict __haystack,
                                                      __WCHAR_TYPE__ __needle,
                                                      __SIZE_TYPE__ __maxlen) {
#line 2165 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_wcsnrchrnul(__haystack, __needle, __maxlen) - __haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_wcsnroff_defined */
