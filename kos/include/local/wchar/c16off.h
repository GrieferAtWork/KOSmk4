/* HASH CRC-32:0x6ade9fae */
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
#ifndef __local_c16off_defined
#define __local_c16off_defined 1
/* Dependency: "wcschrnul" from "wchar" */
#ifndef ____localdep_c16chrnul_defined
#define ____localdep_c16chrnul_defined 1
#if defined(__CRT_HAVE_wcschrnul) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16chr', but return `c16end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16chrnul,(__CHAR16_TYPE__ const *__haystack, __CHAR16_TYPE__ __needle),wcschrnul,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcschrnul)
/* Same as `c16chr', but return `c16end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16chrnul,(__CHAR16_TYPE__ const *__haystack, __CHAR16_TYPE__ __needle),wcschrnul,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcschrnul.h>
/* Same as `c16chr', but return `c16end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_c16chrnul(haystack, needle) (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschrnul))((__WCHAR_TYPE__ const *)(haystack), (__WCHAR_TYPE__)(needle))
#else /* LIBC: c16chrnul */
#include <local/wchar/c16chrnul.h>
/* Same as `c16chr', but return `c16end(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_c16chrnul (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chrnul))
#endif /* c16chrnul... */
#endif /* !____localdep_c16chrnul_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `c16chrnul', but return the offset from `STR', rather than the actual address */
__LOCAL_LIBC(c16off) __ATTR_WUNUSED __ATTR_PURE __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(c16off))(__CHAR16_TYPE__ const *__restrict __haystack,
                                                    __CHAR16_TYPE__ __needle) {
#line 2147 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_c16chrnul(__haystack, __needle) - __haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16off_defined */
