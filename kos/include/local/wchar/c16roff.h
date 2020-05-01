/* HASH CRC-32:0x40e5f7fa */
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
#ifndef __local_c16roff_defined
#define __local_c16roff_defined 1
#include <__crt.h>
/* Dependency: "wcsrchrnul" from "wchar" */
#ifndef ____localdep_c16rchrnul_defined
#define ____localdep_c16rchrnul_defined 1
#if defined(__CRT_HAVE_wcsrchrnul) && (__SIZEOF_WCHAR_T__ == 2)
/* Same as `c16rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16rchrnul,(__CHAR16_TYPE__ const *__restrict __haystack, __CHAR16_TYPE__ __needle),wcsrchrnul,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcsrchrnul)
/* Same as `c16rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16rchrnul,(__CHAR16_TYPE__ const *__restrict __haystack, __CHAR16_TYPE__ __needle),wcsrchrnul,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 2
#include <local/wchar/wcsrchrnul.h>
/* Same as `c16rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_c16rchrnul (*(__CHAR16_TYPE__ *(__LIBCCALL*)(__CHAR16_TYPE__ const *__restrict, __CHAR16_TYPE__))&(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wcsrchrnul)))
#else /* LIBC: c16rchrnul */
#include <local/wchar/c16rchrnul.h>
/* Same as `c16rchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_c16rchrnul (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c16rchrnul))
#endif /* c16rchrnul... */
#endif /* !____localdep_c16rchrnul_defined */

__NAMESPACE_LOCAL_BEGIN
/* Same as `c16rchrnul', but return the offset from `STR', rather than the actual address */
__LOCAL_LIBC(c16roff) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16roff))(__CHAR16_TYPE__ const *__restrict __haystack,
                                                     __CHAR16_TYPE__ __needle) {
#line 2621 "kos/src/libc/magic/string.c"
	return (__SIZE_TYPE__)(__localdep_c16rchrnul(__haystack, __needle) - __haystack);
}
__NAMESPACE_LOCAL_END
#endif /* !__local_c16roff_defined */
