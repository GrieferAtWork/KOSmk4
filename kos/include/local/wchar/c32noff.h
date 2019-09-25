/* HASH CRC-32:0xb9b78187 */
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
#ifndef __local_c32noff_defined
#define __local_c32noff_defined 1
/* Dependency: "wcsnchrnul" from "wchar" */
#ifndef ____localdep_c32nchrnul_defined
#define ____localdep_c32nchrnul_defined 1
#if defined(__CRT_HAVE_wcsnchrnul) && (__SIZEOF_WCHAR_T__ == 4)
/* Same as `c32nchr', but return `c32nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_WUNUSED __ATTR_PURE __ATTR_RETNONNULL __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32nchrnul,(__CHAR32_TYPE__ const *__restrict __haystack, __CHAR32_TYPE__ __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wcsnchrnul.h>
/* Same as `c32nchr', but return `c32nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_c32nchrnul(haystack, needle, maxlen) (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)(haystack), (__WCHAR_TYPE__)(needle), maxlen)
#else /* LIBC: c32nchrnul */
#include <local/wchar/c32nchrnul.h>
/* Same as `c32nchr', but return `c32nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_c32nchrnul (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32nchrnul))
#endif /* c32nchrnul... */
#endif /* !____localdep_c32nchrnul_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `c32nchrnul', but return the offset from `STR', rather than the actual address */
__LOCAL_LIBC(c32noff) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c32noff))(__CHAR32_TYPE__ const *__restrict __haystack,
                                                     __CHAR32_TYPE__ __needle,
                                                     __SIZE_TYPE__ __maxlen) {
#line 2168 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_c32nchrnul(__haystack, __needle, __maxlen) - __haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c32noff_defined */
