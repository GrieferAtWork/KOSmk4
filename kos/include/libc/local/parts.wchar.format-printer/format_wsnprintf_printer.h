/* HASH CRC-32:0x3f31a2a5 */
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
#ifndef __local_format_wsnprintf_printer_defined
#define __local_format_wsnprintf_printer_defined
#include <__crt.h>
#include <bits/crt/wformat-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
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
__LOCAL_LIBC(format_wsnprintf_printer) __ATTR_ACCESS_ROS(2, 3) __ATTR_NONNULL((1)) __SSIZE_TYPE__
__NOTHROW_NCX(__WFORMATPRINTER_CC __LIBC_LOCAL_NAME(format_wsnprintf_printer))(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen) {
	struct __local_format_snprintf_data {
		__WCHAR_TYPE__  *__sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
		__SIZE_TYPE__ __sd_bufsiz; /* Remaining buffer size. */
	};
	struct __local_format_snprintf_data *__ctrl;
	__SIZE_TYPE__ __result = __datalen;
	__ctrl = (struct __local_format_snprintf_data *)__arg;
	if (__result > __ctrl->__sd_bufsiz)
		__result = __ctrl->__sd_bufsiz;
	(__NAMESPACE_LOCAL_SYM __localdep_memcpyc)(__ctrl->__sd_buffer, __data, __result, sizeof(__WCHAR_TYPE__));
	__ctrl->__sd_buffer += __datalen;
	__ctrl->__sd_bufsiz -= __result;
	return (__SSIZE_TYPE__)__datalen;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_format_wsnprintf_printer_defined
#define __local___localdep_format_wsnprintf_printer_defined
#define __localdep_format_wsnprintf_printer __LIBC_LOCAL_NAME(format_wsnprintf_printer)
#endif /* !__local___localdep_format_wsnprintf_printer_defined */
#endif /* !__local_format_wsnprintf_printer_defined */
