/* HASH CRC-32:0x459d9e4f */
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
#ifndef __local_c32off_defined
#define __local_c32off_defined 1
#include <__crt.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c32chrnul from parts.uchar.string */
#ifndef __local___localdep_c32chrnul_defined
#define __local___localdep_c32chrnul_defined 1
#if defined(__CRT_HAVE_wcschrnul) && (__SIZEOF_WCHAR_T__ == 4) && defined(__LIBCCALL_IS_LIBKCALL)
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__COMPILER_REDIRECT(__LIBC,__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__LIBKCALL,__localdep_c32chrnul,(__CHAR32_TYPE__ const *__haystack, __CHAR32_TYPE__ __needle),wcschrnul,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcschrnul)
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_KOS(__ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32chrnul,(__CHAR32_TYPE__ const *__haystack, __CHAR32_TYPE__ __needle),wcschrnul,(__haystack,__needle))
#elif (__SIZEOF_WCHAR_T__ == 4)
__NAMESPACE_LOCAL_END
#include <local/wchar/wcschrnul.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_c32chrnul (*(__CHAR32_TYPE__ *(__LIBKCALL *)(__CHAR32_TYPE__ const *, __CHAR32_TYPE__))&__LIBC_LOCAL_NAME(wcschrnul))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.string/c32chrnul.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `wcschr', but return `wcsend(STR)', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_c32chrnul (*(__CHAR32_TYPE__ *(__LIBKCALL *)(__CHAR32_TYPE__ const *, __CHAR32_TYPE__))&__LIBC_LOCAL_NAME(c32chrnul))
#endif /* !... */
#endif /* !__local___localdep_c32chrnul_defined */
/* Same as `wcschrnul', but return the offset from `STR', rather than the actual address */
__LOCAL_LIBC(c32off) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBKCALL __LIBC_LOCAL_NAME(c32off))(__CHAR32_TYPE__ const *__restrict __haystack, __CHAR32_TYPE__ __needle) {
	return (__SIZE_TYPE__)(__localdep_c32chrnul(__haystack, __needle) - __haystack);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c32off_defined
#define __local___localdep_c32off_defined 1
#define __localdep_c32off __LIBC_LOCAL_NAME(c32off)
#endif /* !__local___localdep_c32off_defined */
#endif /* !__local_c32off_defined */
