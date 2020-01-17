/* HASH CRC-32:0xc3d191a */
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
#ifndef __local_c16nroff_defined
#define __local_c16nroff_defined 1
/* Dependency: "wcsnrchrnul" from "wchar" */
#ifndef ____localdep_c16nrchrnul_defined
#define ____localdep_c16nrchrnul_defined 1
#if defined(__CRT_HAVE_wcsnrchrnul) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16nrchrnul,(__CHAR16_TYPE__ const *__restrict __haystack, __CHAR16_TYPE__ __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnrchrnul)
/* Same as `c16nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16nrchrnul,(__CHAR16_TYPE__ const *__restrict __haystack, __CHAR16_TYPE__ __needle, __SIZE_TYPE__ __maxlen),wcsnrchrnul,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsnrchrnul.h>
/* Same as `c16nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_c16nrchrnul(haystack, needle, maxlen) (__CHAR16_TYPE__ *)(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsnrchrnul))((__WCHAR_TYPE__ const *)(haystack), (__WCHAR_TYPE__)(needle), maxlen)
#else /* LIBC: c16nrchrnul */
#include <local/wchar/c16nrchrnul.h>
/* Same as `c16nrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_c16nrchrnul (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16nrchrnul))
#endif /* c16nrchrnul... */
#endif /* !____localdep_c16nrchrnul_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `c16nrchrnul', but return the offset from `STR', rather than the actual address */
__LOCAL_LIBC(c16nroff) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16nroff))(__CHAR16_TYPE__ const *__restrict __haystack,
                                                      __CHAR16_TYPE__ __needle,
                                                      __SIZE_TYPE__ __maxlen) {
#line 2596 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_c16nrchrnul(__haystack, __needle, __maxlen) - __haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16nroff_defined */
