/* HASH CRC-32:0x4ed94de0 */
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
#ifndef __local_vswprintf_defined
#define __local_vswprintf_defined
#include <__crt.h>
#include <features.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_format_vwprintf_defined
#define __local___localdep_format_vwprintf_defined
#ifdef __CRT_HAVE_format_vwprintf
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
#include <bits/crt/wformat-printer.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((1, 3)),__SSIZE_TYPE__,__THROWING,__localdep_format_vwprintf,(__pwformatprinter __printer, void *__arg, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),format_vwprintf,(__printer,__arg,__format,__args))
#else /* __CRT_HAVE_format_vwprintf */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.format-printer/format_vwprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vwprintf __LIBC_LOCAL_NAME(format_vwprintf)
#endif /* !__CRT_HAVE_format_vwprintf */
#endif /* !__local___localdep_format_vwprintf_defined */
#ifndef __local___localdep_format_wsnprintf_printer_defined
#define __local___localdep_format_wsnprintf_printer_defined
#ifdef __CRT_HAVE_format_wsnprintf_printer
__NAMESPACE_LOCAL_END
#include <bits/crt/wformat-printer.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_REDIRECT(__LIBC,__ATTR_NONNULL((1, 2)),__SSIZE_TYPE__,__NOTHROW_NCX,__WFORMATPRINTER_CC,__localdep_format_wsnprintf_printer,(void *__arg, __WCHAR_TYPE__ const *__restrict __data, __SIZE_TYPE__ __datalen),format_wsnprintf_printer,(__arg,__data,__datalen))
#else /* __CRT_HAVE_format_wsnprintf_printer */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.format-printer/format_wsnprintf_printer.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_wsnprintf_printer __LIBC_LOCAL_NAME(format_wsnprintf_printer)
#endif /* !__CRT_HAVE_format_wsnprintf_printer */
#endif /* !__local___localdep_format_wsnprintf_printer_defined */
__NAMESPACE_LOCAL_END
#ifndef ____format_wsnprintf_data_defined
#define ____format_wsnprintf_data_defined
struct __format_wsnprintf_data {
	__WCHAR_TYPE__      *__sd_buffer; /* [0..sd_bufsiz] Pointer to the next memory location to which to write. */
	__SIZE_TYPE__ __sd_bufsiz; /* Remaining buffer size. */
};
#endif /* !____format_wsnprintf_data_defined */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vswprintf) __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((3)) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(vswprintf))(__WCHAR_TYPE__ *__restrict __buf, __SIZE_TYPE__ __buflen, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args) {
	struct __format_wsnprintf_data __data;
	__STDC_INT_AS_SSIZE_T __result;
	__data.__sd_buffer = __buf;
	__data.__sd_bufsiz = __buflen;
	__result = (__STDC_INT_AS_SSIZE_T)(__NAMESPACE_LOCAL_SYM __localdep_format_vwprintf)(&(__NAMESPACE_LOCAL_SYM __localdep_format_wsnprintf_printer),
	                                                (void *)&__data, __format, __args);
	if (__result >= 0) {
		if (__data.__sd_bufsiz != 0) {
			*__data.__sd_buffer = (__WCHAR_TYPE__)'\0';
		} else {
			if (__buflen != 0)
				__buf[__buflen - 1] = (__WCHAR_TYPE__)'\0';
		}
	}
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vswprintf_defined
#define __local___localdep_vswprintf_defined
#define __localdep_vswprintf __LIBC_LOCAL_NAME(vswprintf)
#endif /* !__local___localdep_vswprintf_defined */
#endif /* !__local_vswprintf_defined */
