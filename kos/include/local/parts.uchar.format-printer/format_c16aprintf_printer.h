/* HASH CRC-32:0xa957a34e */
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
#ifndef __local_format_c16aprintf_printer_defined
#define __local_format_c16aprintf_printer_defined 1
#include <__crt.h>
#if (defined(__CRT_HAVE_format_waprintf_alloc) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)) || defined(__CRT_HAVE_DOS$format_waprintf_alloc) || defined(__CRT_HAVE_realloc)
__NAMESPACE_LOCAL_BEGIN
/* Dependency: format_c16aprintf_alloc from parts.uchar.format-printer */
#ifndef __local___localdep_format_c16aprintf_alloc_defined
#define __local___localdep_format_c16aprintf_alloc_defined 1
#if defined(__CRT_HAVE_format_waprintf_alloc) && (__SIZEOF_WCHAR_T__ == 2) && defined(__LIBCCALL_IS_LIBDCALL)
__NAMESPACE_LOCAL_END
#ifndef __format_waprintf_data_defined
#define __format_waprintf_data_defined 1
struct format_waprintf_data {
	__WCHAR_TYPE__      *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif
__NAMESPACE_LOCAL_BEGIN
/* Allocate a buffer of `num_wchars' wide-characters at the end of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized, or some other function is used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory */
__CREDIRECT(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_format_c16aprintf_alloc,(struct format_c16aprintf_data *__restrict __self, __SIZE_TYPE__ __num_wchars),format_waprintf_alloc,(__self,__num_wchars))
#elif defined(__CRT_HAVE_DOS$format_waprintf_alloc)
__NAMESPACE_LOCAL_END
#ifndef __format_waprintf_data_defined
#define __format_waprintf_data_defined 1
struct format_waprintf_data {
	__WCHAR_TYPE__      *ap_base;  /* [0..ap_used|ALLOC(ap_used+ap_avail)][owned] Buffer */
	__SIZE_TYPE__ ap_avail; /* Unused buffer size */
	__SIZE_TYPE__ ap_used;  /* Used buffer size */
};
#endif
__NAMESPACE_LOCAL_BEGIN
/* Allocate a buffer of `num_wchars' wide-characters at the end of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized, or some other function is used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory */
__CREDIRECT_DOS(__ATTR_MALLOC __ATTR_MALL_DEFAULT_ALIGNED __ATTR_WUNUSED __ATTR_NONNULL((1)),__CHAR16_TYPE__ *,__NOTHROW_NCX,__localdep_format_c16aprintf_alloc,(struct format_c16aprintf_data *__restrict __self, __SIZE_TYPE__ __num_wchars),format_waprintf_alloc,(__self,__num_wchars))
#elif defined(__CRT_HAVE_realloc) && (__SIZEOF_WCHAR_T__ == 2)
__NAMESPACE_LOCAL_END
#include <local/parts.wchar.format-printer/format_waprintf_alloc.h>
__NAMESPACE_LOCAL_BEGIN
/* Allocate a buffer of `num_wchars' wide-characters at the end of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized, or some other function is used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory */
#define __localdep_format_c16aprintf_alloc (*(__CHAR16_TYPE__ *(__LIBDCALL *)(struct format_c16aprintf_data *__restrict, __SIZE_TYPE__))&__LIBC_LOCAL_NAME(format_waprintf_alloc))
#elif defined(__CRT_HAVE_realloc)
__NAMESPACE_LOCAL_END
#include <local/parts.uchar.format-printer/format_c16aprintf_alloc.h>
__NAMESPACE_LOCAL_BEGIN
/* Allocate a buffer of `num_wchars' wide-characters at the end of `self'
 * The returned pointer remains valid until the next time this function is called,
 * the format_aprintf buffer `self' is finalized, or some other function is used
 * to append additional data to the end of `self'
 * @return: NULL: Failed to allocate additional memory */
#define __localdep_format_c16aprintf_alloc __LIBC_LOCAL_NAME(format_c16aprintf_alloc)
#else /* ... */
#undef __local___localdep_format_c16aprintf_alloc_defined
#endif /* !... */
#endif /* !__local___localdep_format_c16aprintf_alloc_defined */
/* Dependency: memcpyw from string */
#ifndef __local___localdep_memcpyw_defined
#define __local___localdep_memcpyw_defined 1
#ifdef __CRT_HAVE_memcpyw
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),memcpyw,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_wmemcpy) && (__SIZEOF_WCHAR_T__ == 2)
/* Copy memory between non-overlapping memory blocks. */
__CREDIRECT(__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__localdep_memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),wmemcpy,(__dst,__src,__n_words))
#elif defined(__CRT_HAVE_DOS$wmemcpy)
/* Copy memory between non-overlapping memory blocks. */
__COMPILER_REDIRECT(__LIBC,__ATTR_LEAF __ATTR_RETNONNULL __ATTR_NONNULL((1, 2)),__UINT16_TYPE__ *,__NOTHROW_NCX,__LIBCCALL,__localdep_memcpyw,(void *__restrict __dst, void const *__restrict __src, __SIZE_TYPE__ __n_words),DOS$wmemcpy,(__dst,__src,__n_words))
#else /* ... */
__NAMESPACE_LOCAL_END
#include <local/string/memcpyw.h>
__NAMESPACE_LOCAL_BEGIN
/* Copy memory between non-overlapping memory blocks. */
#define __localdep_memcpyw __LIBC_LOCAL_NAME(memcpyw)
#endif /* !... */
#endif /* !__local___localdep_memcpyw_defined */
/* Print data to a dynamically allocated heap buffer. On error, -1 is returned */
__LOCAL_LIBC(format_c16aprintf_printer) __ATTR_WUNUSED __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBDCALL __LIBC_LOCAL_NAME(format_c16aprintf_printer))(void *__arg, __CHAR16_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen) {
	__CHAR16_TYPE__ *__buf;
	__buf = __localdep_format_c16aprintf_alloc((struct format_c16aprintf_data *)__arg, __datalen);
	if __unlikely(!__buf)
		return -1;
	(__CHAR16_TYPE__ *)__localdep_memcpyw(__buf, __data, __datalen);
	return (__SSIZE_TYPE__)__datalen;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_format_c16aprintf_printer_defined
#define __local___localdep_format_c16aprintf_printer_defined 1
#define __localdep_format_c16aprintf_printer __LIBC_LOCAL_NAME(format_c16aprintf_printer)
#endif /* !__local___localdep_format_c16aprintf_printer_defined */
#else /* (__CRT_HAVE_format_waprintf_alloc && (__SIZEOF_WCHAR_T__ == 2) && __LIBCCALL_IS_LIBDCALL) || __CRT_HAVE_DOS$format_waprintf_alloc || __CRT_HAVE_realloc */
#undef __local_format_c16aprintf_printer_defined
#endif /* (!__CRT_HAVE_format_waprintf_alloc || !(__SIZEOF_WCHAR_T__ == 2) || !__LIBCCALL_IS_LIBDCALL) && !__CRT_HAVE_DOS$format_waprintf_alloc && !__CRT_HAVE_realloc */
#endif /* !__local_format_c16aprintf_printer_defined */
