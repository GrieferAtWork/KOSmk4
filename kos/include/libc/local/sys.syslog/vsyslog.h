/* HASH CRC-32:0xa0127b3b */
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
#ifndef __local_vsyslog_defined
#define __local_vsyslog_defined
#include <__crt.h>
#ifdef __CRT_HAVE_syslog_printer
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_format_vprintf_defined
#define __local___localdep_format_vprintf_defined
#ifdef __CRT_HAVE_format_vprintf
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(3) __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_vprintf,(__pformatprinter __printer, void *__arg, char const *__restrict __format, __builtin_va_list __args),format_vprintf,(__printer,__arg,__format,__args))
#else /* __CRT_HAVE_format_vprintf */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_vprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vprintf __LIBC_LOCAL_NAME(format_vprintf)
#endif /* !__CRT_HAVE_format_vprintf */
#endif /* !__local___localdep_format_vprintf_defined */
#ifndef __local___localdep_syslog_printer_defined
#define __local___localdep_syslog_printer_defined
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__FORMATPRINTER_CC,__localdep_syslog_printer,(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen),syslog_printer,(__arg,__data,__datalen))
#endif /* !__local___localdep_syslog_printer_defined */
__LOCAL_LIBC(vsyslog) __ATTR_IN(2) __ATTR_LIBC_PRINTF(2, 0) void
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(vsyslog))(__STDC_INT_AS_UINT_T __level, char const *__format, __builtin_va_list __args) {
	(__NAMESPACE_LOCAL_SYM __localdep_format_vprintf)(&(__NAMESPACE_LOCAL_SYM __localdep_syslog_printer),
	               (void *)(__UINTPTR_TYPE__)(unsigned int)__level,
	               __format,
	               __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vsyslog_defined
#define __local___localdep_vsyslog_defined
#define __localdep_vsyslog __LIBC_LOCAL_NAME(vsyslog)
#endif /* !__local___localdep_vsyslog_defined */
#else /* __CRT_HAVE_syslog_printer */
#undef __local_vsyslog_defined
#endif /* !__CRT_HAVE_syslog_printer */
#endif /* !__local_vsyslog_defined */
