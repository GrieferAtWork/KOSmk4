/* HASH CRC-32:0x34674f6 */
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
#ifndef __local_c16sroff_defined
#define __local_c16sroff_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: c16srchrnul from parts.uchar.string */
#ifndef __local___localdep_c16srchrnul_defined
#define __local___localdep_c16srchrnul_defined 1
#if defined(__CRT_HAVE_wcsrchrnul) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16srchrnul,(__CHAR16_TYPE__ const *__restrict __haystack, __CHAR16_TYPE__ __needle),wcsrchrnul,(__haystack,__needle))
#elif defined(__CRT_HAVE_DOS$wcsrchrnul)
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16srchrnul,(__CHAR16_TYPE__ const *__restrict __haystack, __CHAR16_TYPE__ __needle),wcsrchrnul,(__haystack,__needle))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsrchrnul.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_c16srchrnul (*(__CHAR16_TYPE__ *(__LIBDCALL *)(__CHAR16_TYPE__ const *__restrict, __CHAR16_TYPE__))&__LIBC_LOCAL_NAME(wcsrchrnul))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c16srchrnul.h>
__NAMESPACE_LOCAL_BEGIN
/* Same as `wcsrchr', but return `STR-1', rather than `NULL' if `NEEDLE' wasn't found. */
#define __localdep_c16srchrnul __LIBC_LOCAL_NAME(c16srchrnul)
#endif /* !... */
#endif /* !__local___localdep_c16srchrnul_defined */
/* Same as `wcsrchrnul', but return the offset from `STR', rather than the actual address */
__LOCAL_LIBC(c16sroff) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16sroff))(__CHAR16_TYPE__ const *__restrict __haystack, __CHAR16_TYPE__ __needle) {
	return (__SIZE_TYPE__)(__localdep_c16srchrnul(__haystack, __needle) - __haystack);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16sroff_defined
#define __local___localdep_c16sroff_defined 1
#define __localdep_c16sroff __LIBC_LOCAL_NAME(c16sroff)
#endif /* !__local___localdep_c16sroff_defined */
#endif /* !__local_c16sroff_defined */
