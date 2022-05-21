/* HASH CRC-32:0xbe129ee5 */
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
#ifndef __local_format_aprintf_printer_defined
#define __local_format_aprintf_printer_defined
#include <__crt.h>
#if defined(__CRT_HAVE_format_aprintf_alloc) || defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_format_aprintf_alloc_defined
#define __local___localdep_format_aprintf_alloc_defined
#ifdef __CRT_HAVE_format_aprintf_alloc
__NAMESPACE_LOCAL_END
struct format_aprintf_data;
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_ACCESS_RW(1) __ATTR_ALLOC_SIZE((2)),char *,__NOTHROW_NCX,__localdep_format_aprintf_alloc,(struct format_aprintf_data *__restrict __self, __SIZE_TYPE__ __num_chars),format_aprintf_alloc,(__self,__num_chars))
#elif defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE___libc_realloc)
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_aprintf_alloc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_aprintf_alloc __LIBC_LOCAL_NAME(format_aprintf_alloc)
#else /* ... */
#undef __local___localdep_format_aprintf_alloc_defined
#endif /* !... */
#endif /* !__local___localdep_format_aprintf_alloc_defined */
#ifndef __local___localdep_memcpyc_defined
#define __local___localdep_memcpyc_defined
#ifdef __CRT_HAVE_memcpyc
__CREDIRECT(__ATTR_LEAF __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1),void *,__NOTHROW_NCX,__localdep_memcpyc,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __elem_count, __SIZE_TYPE__ __elem_size),memcpyc,(__dst,__src,__elem_count,__elem_size))
#else /* __CRT_HAVE_memcpyc */
__NAMESPACE_LOCAL_END
#include <libc/local/string/memcpyc.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_memcpyc __LIBC_LOCAL_NAME(memcpyc)
#endif /* !__CRT_HAVE_memcpyc */
#endif /* !__local___localdep_memcpyc_defined */
__LOCAL_LIBC(format_aprintf_printer) __ATTR_WUNUSED __ATTR_ACCESS_ROS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_NCX(__FORMATPRINTER_CC __LIBC_LOCAL_NAME(format_aprintf_printer))(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen) {
	char *__buf;
	__buf = (__NAMESPACE_LOCAL_SYM __localdep_format_aprintf_alloc)((struct format_aprintf_data *)__arg,
	                           __datalen);
	if __unlikely(!__buf)
		goto __err;
	(__NAMESPACE_LOCAL_SYM __localdep_memcpyc)(__buf, __data, __datalen, sizeof(char));
	return (__SSIZE_TYPE__)__datalen;
__err:
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_format_aprintf_printer_defined
#define __local___localdep_format_aprintf_printer_defined
#define __localdep_format_aprintf_printer __LIBC_LOCAL_NAME(format_aprintf_printer)
#endif /* !__local___localdep_format_aprintf_printer_defined */
#else /* __CRT_HAVE_format_aprintf_alloc || __CRT_HAVE_realloc || __CRT_HAVE___libc_realloc */
#undef __local_format_aprintf_printer_defined
#endif /* !__CRT_HAVE_format_aprintf_alloc && !__CRT_HAVE_realloc && !__CRT_HAVE___libc_realloc */
#endif /* !__local_format_aprintf_printer_defined */
