/* HASH CRC-32:0x6c66861c */
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
#ifndef __local_vsprintf_defined
#define __local_vsprintf_defined
#include <__crt.h>
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_format_sprintf_printer_defined
#define __local___localdep_format_sprintf_printer_defined
#ifdef __CRT_HAVE_format_sprintf_printer
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_ACCESS_ROS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__FORMATPRINTER_CC,__localdep_format_sprintf_printer,(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen),format_sprintf_printer,(__arg,__data,__datalen))
#else /* __CRT_HAVE_format_sprintf_printer */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_sprintf_printer.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_sprintf_printer __LIBC_LOCAL_NAME(format_sprintf_printer)
#endif /* !__CRT_HAVE_format_sprintf_printer */
#endif /* !__local___localdep_format_sprintf_printer_defined */
#ifndef __local___localdep_format_vprintf_defined
#define __local___localdep_format_vprintf_defined
#ifdef __CRT_HAVE_format_vprintf
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_ACCESS_RO(3) __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__THROWING,__localdep_format_vprintf,(__pformatprinter __printer, void *__arg, char const *__restrict __format, __builtin_va_list __args),format_vprintf,(__printer,__arg,__format,__args))
#else /* __CRT_HAVE_format_vprintf */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_vprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vprintf __LIBC_LOCAL_NAME(format_vprintf)
#endif /* !__CRT_HAVE_format_vprintf */
#endif /* !__local___localdep_format_vprintf_defined */
__LOCAL_LIBC(vsprintf) __ATTR_ACCESS_RO(2) __ATTR_ACCESS_WR(1) __ATTR_LIBC_PRINTF(2, 0) __STDC_INT_AS_SSIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(vsprintf))(char *__restrict __dest, char const *__restrict __format, __builtin_va_list __args) {
	__STDC_INT_AS_SSIZE_T __result;
	char *__dest_pointer = __dest;
	__result = (__STDC_INT_AS_SSIZE_T)(__NAMESPACE_LOCAL_SYM __localdep_format_vprintf)(&(__NAMESPACE_LOCAL_SYM __localdep_format_sprintf_printer),
	                                               (void *)&__dest_pointer,
	                                               __format, __args);
	if (__result >= 0)
		*__dest_pointer = '\0';
	return __result;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vsprintf_defined
#define __local___localdep_vsprintf_defined
#define __localdep_vsprintf __LIBC_LOCAL_NAME(vsprintf)
#endif /* !__local___localdep_vsprintf_defined */
#endif /* !__local_vsprintf_defined */
