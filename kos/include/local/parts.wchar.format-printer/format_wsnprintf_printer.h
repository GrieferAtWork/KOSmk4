/* HASH CRC-32:0xf2cfafe */
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
#ifndef __local_format_wsnprintf_printer_defined
#define __local_format_wsnprintf_printer_defined 1
#include <hybrid/typecore.h>
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
/* Format-printer implementation for printing to a string buffer like `wsnprintf' would
 * WARNING: No trailing NUL-character is implicitly appended
 * NOTE: The number of written characters is `ORIG_BUFSIZE - ARG->sd_bufsiz'
 * NOTE: The number of required characters is `ARG->sd_buffer - ORIG_BUF', or alternatively the sum of return values of all calls to `format_snprintf_printer()' */
__LOCAL_LIBC(format_wsnprintf_printer) __ATTR_NONNULL((1, 2)) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(format_wsnprintf_printer))(/*struct format_wsnprintf_data**/ void *__arg,
                                                                      __WCHAR_TYPE__ const *__restrict __data,
                                                                      __SIZE_TYPE__ __datalen) {
#line 1004 "kos/src/libc/magic/format-printer.c"
	struct __format_snprintf_data_ {
		__WCHAR_TYPE__         *__sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
		__SIZE_TYPE__ __sd_bufsiz; /* Remaining buffer size. */
	};
	struct __format_snprintf_data_ *__ctrl;
	__SIZE_TYPE__ __result = __datalen;
	__ctrl = (struct __format_snprintf_data_ *)__arg;
	if (__result > __ctrl->__sd_bufsiz)
		__result = __ctrl->__sd_bufsiz;

	__localdep_wmemcpy(__ctrl->__sd_buffer, __data, __result);



	__ctrl->__sd_buffer += __datalen;
	__ctrl->__sd_bufsiz -= __result;
	return (__SSIZE_TYPE__)__datalen;
}
__NAMESPACE_LOCAL_END
#endif /* !__local_format_wsnprintf_printer_defined */
