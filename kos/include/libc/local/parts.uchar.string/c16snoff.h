/* HASH CRC-32:0xaa0b6785 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_c16snoff_defined
#define __local_c16snoff_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_c16snchrnul_defined
#define __local___localdep_c16snchrnul_defined 1
#if defined(__CRT_HAVE_wcsnchrnul) && __SIZEOF_WCHAR_T__ == 2 && defined(__LIBCCALL_IS_LIBDCALL)
__CREDIRECT(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16snchrnul,(__CHAR16_TYPE__ const *__restrict __haystack, __CHAR16_TYPE__ __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
#elif defined(__CRT_HAVE_DOS$wcsnchrnul)
__CREDIRECT_DOS(__ATTR_PURE __ATTR_RETNONNULL __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_c16snchrnul,(__CHAR16_TYPE__ const *__restrict __haystack, __CHAR16_TYPE__ __needle, __SIZE_TYPE__ __maxlen),wcsnchrnul,(__haystack,__needle,__maxlen))
#elif __SIZEOF_WCHAR_T__ == 2
__NAMESPACE_LOCAL_END
#include <libc/local/wchar/wcsnchrnul.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16snchrnul (*(__CHAR16_TYPE__ *(__LIBDCALL *)(__CHAR16_TYPE__ const *__restrict, __CHAR16_TYPE__, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(wcsnchrnul))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.uchar.string/c16snchrnul.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_c16snchrnul __LIBC_LOCAL_NAME(c16snchrnul)
#endif /* !... */
#endif /* !__local___localdep_c16snchrnul_defined */
__LOCAL_LIBC(c16snoff) __ATTR_PURE __ATTR_WUNUSED __ATTR_NONNULL((1)) __SIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(c16snoff))(__CHAR16_TYPE__ const *__restrict __haystack, __CHAR16_TYPE__ __needle, __SIZE_TYPE__ __maxlen) {
	return (__SIZE_TYPE__)(__localdep_c16snchrnul(__haystack, __needle, __maxlen) - __haystack);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_c16snoff_defined
#define __local___localdep_c16snoff_defined 1
#define __localdep_c16snoff __LIBC_LOCAL_NAME(c16snoff)
#endif /* !__local___localdep_c16snoff_defined */
#endif /* !__local_c16snoff_defined */
