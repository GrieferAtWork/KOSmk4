/* HASH CRC-32:0xcffab29e */
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
#ifndef __local_format_wprintf_defined
#define __local_format_wprintf_defined
#include <__crt.h>
#include <kos/anno.h>
#include <bits/crt/wformat-printer.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_format_vwprintf_defined
#define __local___localdep_format_vwprintf_defined
#ifdef __CRT_HAVE_format_vwprintf
__CREDIRECT(__ATTR_IN(3) __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_vwprintf,(__pwformatprinter __printer, void *__arg, __WCHAR_TYPE__ const *__restrict __format, __builtin_va_list __args),format_vwprintf,(__printer,__arg,__format,__args))
#else /* __CRT_HAVE_format_vwprintf */
__NAMESPACE_LOCAL_END
#include <libc/local/parts.wchar.format-printer/format_vwprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vwprintf __LIBC_LOCAL_NAME(format_vwprintf)
#endif /* !__CRT_HAVE_format_vwprintf */
#endif /* !__local___localdep_format_vwprintf_defined */
__LOCAL_LIBC(format_wprintf) __ATTR_IN(3) __ATTR_LIBC_WPRINTF(3, 0) __ATTR_NONNULL((1)) __SSIZE_TYPE__
(__LIBCCALL __LIBC_LOCAL_NAME(format_wprintf))(__pwformatprinter __printer, void *__arg, __WCHAR_TYPE__ const *__restrict __format, ...) __THROWS(...) {
	__SSIZE_TYPE__ __result;
	__builtin_va_list __args;
	__builtin_va_start(__args, __format);
	__result = (__NAMESPACE_LOCAL_SYM __localdep_format_vwprintf)(__printer, __arg, __format, __args);
	__builtin_va_end(__args);
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_format_wprintf_defined
#define __local___localdep_format_wprintf_defined
#define __localdep_format_wprintf __LIBC_LOCAL_NAME(format_wprintf)
#endif /* !__local___localdep_format_wprintf_defined */
#endif /* !__local_format_wprintf_defined */
