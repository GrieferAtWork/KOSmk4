/* HASH CRC-32:0xa0a7ccc8 */
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
#ifndef __local_c16noff_defined
#define __local_c16noff_defined 1
/* Dependency: "wcsnchrnul" from "wchar" */
#ifndef ____localdep_c16nchrnul_defined
#define ____localdep_c16nchrnul_defined 1
#if defined(__CRT_HAVE_wcsnchrnul) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16nchr', but return `c16nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16nchrnul,(__CHAR16_TYPE__ const *__restrict __haystack, __CHAR16_TYPE__ __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnchrnul)
/* Same as `c16nchr', but return `c16nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16nchrnul,(__CHAR16_TYPE__ const *__restrict __haystack, __CHAR16_TYPE__ __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnchrnul.h>
/* Same as `c16nchr', but return `c16nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_c16nchrnul(haystack, needle, maxlen) (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnchrnul))((__WCHAR_TYPE__ const *)(haystack), (__WCHAR_TYPE__)(needle), maxlen)
#else /* LIBC: c16nchrnul */
#include <local/wchar/c16nchrnul.h>
/* Same as `c16nchr', but return `c16nend(STR, MAX_CHARS)', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_c16nchrnul (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nchrnul))
#endif /* c16nchrnul... */
#endif /* !____localdep_c16nchrnul_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `c16nchrnul', but return the offset from `STR', rather than the actual address */
__LOCAL_LIBC(c16noff) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16noff))(__CHAR16_TYPE__ const *__restrict __haystack,
                                                     __CHAR16_TYPE__ __needle,
                                                     __SIZE_TYPE__ __maxlen) {
#line 2256 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_c16nchrnul(__haystack, __needle, __maxlen) - __haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16noff_defined */
