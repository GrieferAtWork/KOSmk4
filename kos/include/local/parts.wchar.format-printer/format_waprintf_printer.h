/* HASH CRC-32:0x158d2c2c */
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
#ifndef __local_format_waprintf_printer_defined
#if defined(__CRT_HAVE_realloc) || defined(__CRT_HAVE_format_waprintf_alloc)
#define __local_format_waprintf_printer_defined 1
#include <__crt.h>
/* Dependency: "format_waprintf_alloc" from "parts.wchar.format-printer" */
#ifndef ____localdep_format_waprintf_alloc_defined
#define ____localdep_format_waprintf_alloc_defined 1
#ifdef __CRT_HAVE_format_waprintf_alloc
/* Allocate a buffer of `num_wchars' wide-characters at the end of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized, or some other function is used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory */
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_format_waprintf_alloc,(struct format_waprintf_data *__restrict __self, __SIZE_TYPE__ __num_wchars),format_waprintf_alloc,(__self,__num_wchars))
#elif defined(__CRT_HAVE_realloc)
#include <local/parts.wchar.format-printer/format_waprintf_alloc.h>
/* Allocate a buffer of `num_wchars' wide-characters at the end of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized, or some other function is used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory */
#define __localdep_format_waprintf_alloc (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(format_waprintf_alloc))
#else /* CUSTOM: format_waprintf_alloc */
#undef ____localdep_format_waprintf_alloc_defined
#endif /* format_waprintf_alloc... */
#endif /* !____localdep_format_waprintf_alloc_defined */

/* Dependency: "wmemcpy" from "wchar" */
#ifndef ____localdep_wmemcpy_defined
#define ____localdep_wmemcpy_defined 1
#ifdef __CRT_HAVE_wmemcpy
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemcpy,(__WCHAR_TYPE__ *__restrict __dst, __WCHAR_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),wmemcpy,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyw) && (__SIZEOF_WCHAR_T__ == 2)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemcpy,(__WCHAR_TYPE__ *__restrict __dst, __WCHAR_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),memcpyw,(__dst,__src,__num_chars))
#elif defined(__CRT_HAVE_memcpyl) && (__SIZEOF_WCHAR_T__ == 4)
__CREDIRECT(__ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__WCHAR_TYPE__ *,__NOTHROW_NCX,__localdep_wmemcpy,(__WCHAR_TYPE__ *__restrict __dst, __WCHAR_TYPE__ const *__restrict __src, __SIZE_TYPE__ __num_chars),memcpyl,(__dst,__src,__num_chars))
#else /* LIBC: wmemcpy */
#include <local/wchar/wmemcpy.h>
#define __localdep_wmemcpy (__NAMESPACE_LOCAL_SYM __LIBC_LOCAL_NAME(wmemcpy))
#endif /* wmemcpy... */
#endif /* !____localdep_wmemcpy_defined */

__NAMESPACE_LOCAL_BEGIN
/* Print data to a dynamically allocated heap buffer. On error, -1 is returned */
__LOCAL_LIBC(format_waprintf_printer) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(format_waprintf_printer))(/*struct format_waprintf_data **/ void *__arg,
                                                                     __WCHAR_TYPE__ const *__restrict __data,
                                                                     __SIZE_TYPE__ __datalen) {
#line 334 "kos/src/libc/magic/parts.wchar.format-printer.c"
	__WCHAR_TYPE__ *__buf;
	__buf = __localdep_format_waprintf_alloc((struct format_waprintf_data *)__arg, __datalen);
	if __unlikely(!__buf)
		return -1;
	__localdep_wmemcpy(__buf, __data, __datalen);
	return (__SSIZE_TYPE__)__datalen;
}
__NAMESPACE_LOCAL_END
#endif /* __CRT_HAVE_realloc || __CRT_HAVE_format_waprintf_alloc */
#endif /* !__local_format_waprintf_printer_defined */
