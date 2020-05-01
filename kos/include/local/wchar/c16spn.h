/* HASH CRC-32:0xd7a0681 */
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
#ifndef __local_c16spn_defined
#define __local_c16spn_defined 1
#include <__crt.h>
/* Dependency: "wcschr" from "wchar" */
#ifndef ____localdep_c16chr_defined
#define ____localdep_c16chr_defined 1
#if defined(__CRT_HAVE_wcschr) && (__SIZEOF_WCHAR_T__ == 2)
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16chr,(__CHAR16_TYPE__ const *__restrict __haystack, __CHAR16_TYPE__ __needle),wcschr,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcschr)
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16chr,(__CHAR16_TYPE__ const *__restrict __haystack, __CHAR16_TYPE__ __needle),wcschr,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcschr.h>
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
#define __localdep_c16chr (*(__CHAR16_TYPE__ *(__LIBCCALL*)(__CHAR16_TYPE__ const *__restrict, __CHAR16_TYPE__))&(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcschr)))
#else /* LIBC: c16chr */
#include <local/wchar/c16chr.h>
/* Return the pointer of the first instance of `NEEDLE', or `NULL' if `NEEDLE' wasn't found. */
#define __localdep_c16chr (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16chr))
#endif /* c16chr... */
#endif /* !____localdep_c16chr_defined */

__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(c16spn) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16spn))(__CHAR16_TYPE__ const *__haystack,
                                                    __CHAR16_TYPE__ const *__accept) {
#line 384 "kos/src/libc/magic/string.c"
	__CHAR16_TYPE__ const *__iter = __haystack;
	while (__localdep_c16chr(__accept, *__iter))
		++__iter;
	return (__SIZE_TYPE__)(__iter - __haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16spn_defined */
