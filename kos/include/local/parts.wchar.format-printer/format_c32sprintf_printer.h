/* HASH CRC-32:0x985617ef */
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
#ifndef __local_format_c32sprintf_printer_defined
#define __local_format_c32sprintf_printer_defined 1
/* Dependency: "wmempcpy" from "wchar" */
#ifndef ____localdep_c32mempcpy_defined
#define ____localdep_c32mempcpy_defined 1
#if defined(__CRT_HAVE_wmempcpy) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32mempcpy,(__CHAR32_TYPE__ *__restrict __dst, __CHAR32_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),wmempcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_mempcpyl)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__CHAR32_TYPE__ *,__NOTHROW_NCX,__localdep_c32mempcpy,(__CHAR32_TYPE__ *__restrict __dst, __CHAR32_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),mempcpyl,(__dst,__src,__num_chars))
#elif __SIZEOF_WCHAR_T__ == 4
#include <local/wchar/wmempcpy.h>
#define __localdep_c32mempcpy (*(__CHAR32_TYPE__ *(__LIBCCALL*)(__CHAR32_TYPE__ *__restrict, __CHAR32_TYPE__ const *__restrict, __SIZE_TYPE__))&(__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmempcpy)))
#else /* LIBC: c32mempcpy */
#include <local/wchar/c32mempcpy.h>
#define __localdep_c32mempcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(c32mempcpy))
#endif /* c32mempcpy... */
#endif /* !____localdep_c32mempcpy_defined */

__NAMESPACE_LOCAL_BEGIN
/* Format-printer implementation for printing to a string buffer like `wsprintf' would
 * WARNING: No trailing NUL-character is implicitly appended */
__LOCAL_LIBC(format_c32sprintf_printer) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(format_c32sprintf_printer))(/*wchar_t ***/ void *__arg,
                                                                       __CHAR32_TYPE__ const *__restrict __data,
                                                                       __SIZE_TYPE__ __datalen) {
#line 958 "kos/src/libc/magic/format-printer.c"

	*(__CHAR32_TYPE__ **)__arg = (__CHAR32_TYPE__ *)__localdep_c32mempcpy(*(__CHAR32_TYPE__ **)__arg, __data, __datalen);



	return (__SSIZE_TYPE__)__datalen;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_format_c32sprintf_printer_defined */
