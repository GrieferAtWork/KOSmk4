/* HASH CRC-32:0x22dc91e */
/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_format_c32sprintf_printer_defined
#define __local_format_c32sprintf_printer_defined
#include <__crt.h>
#include <bits/crt/uformat-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_mempcpyc_defined
#define __local___localdep_mempcpyc_defined
#ifdef __CRT_HAVE_mempcpyc
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),void *,__NOTHROW_NCX,__localdep_mempcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),mempcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_mempcpyc */
__NAMESPACE_LOCAL_END
#include <libc/local/string/mempcpyc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_mempcpyc __LIBC_LOCAL_NAME(mempcpyc)
#endif /* !__CRT_HAVE_mempcpyc */
#endif /* !__local___localdep_mempcpyc_defined */
__LOCAL_LIBC(format_c32sprintf_printer) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__
__NOTHROW_NCX(__C32FORMATPRINTER_CC __LIBC_LOCAL_NAME(format_c32sprintf_printer))(void *__arg, __CHAR32_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen) {
	*(__CHAR32_TYPE__ **)__arg = (__CHAR32_TYPE__ *)(__NAMESPACE_LOCAL_SYM __localdep_mempcpyc)(*(__CHAR32_TYPE__ **)__arg, __data, __datalen, sizeof(__CHAR32_TYPE__));
	return (__SSIZE_TYPE__)__datalen;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_format_c32sprintf_printer_defined
#define __local___localdep_format_c32sprintf_printer_defined
#define __localdep_format_c32sprintf_printer __LIBC_LOCAL_NAME(format_c32sprintf_printer)
#endif /* !__local___localdep_format_c32sprintf_printer_defined */
#endif /* !__local_format_c32sprintf_printer_defined */
