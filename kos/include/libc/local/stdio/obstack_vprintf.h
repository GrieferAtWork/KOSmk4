/* HASH CRC-32:0x34bec2e6 */
/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_obstack_vprintf_defined
#define __local_obstack_vprintf_defined
#include <__crt.h>
#include <bits/crt/obstack.h>
#if defined(__CRT_HAVE_obstack_printer) || defined(__CRT_HAVE__obstack_newchunk) || defined(__LOCAL_obstack_alloc_failed_handler) || defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE_xexit)
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_format_vprintf_defined
#define __local___localdep_format_vprintf_defined
#ifdef __CRT_HAVE_format_vprintf
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(3) __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,__localdep_format_vprintf,(__pformatprinter __printer, void *__arg, char const *__restrict __format, __builtin_va_list __args),format_vprintf,(__printer,__arg,__format,__args))
#else /* __CRT_HAVE_format_vprintf */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_vprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vprintf __LIBC_LOCAL_NAME(format_vprintf)
#endif /* !__CRT_HAVE_format_vprintf */
#endif /* !__local___localdep_format_vprintf_defined */
#ifndef __local___localdep_obstack_printer_defined
#define __local___localdep_obstack_printer_defined
#ifdef __CRT_HAVE_obstack_printer
__NAMESPACE_LOCAL_END
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__COMPILER_CREDIRECT(__LIBC,__ATTR_WUNUSED __ATTR_INS(2, 3) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__FORMATPRINTER_CC,__localdep_obstack_printer,(void *__arg, char const *__restrict __data, __SIZE_TYPE__ __datalen),obstack_printer,(__arg,__data,__datalen))
#elif defined(__CRT_HAVE__obstack_newchunk) || defined(__LOCAL_obstack_alloc_failed_handler) || defined(__CRT_HAVE_exit) || defined(__CRT_HAVE_quick_exit) || defined(__CRT_HAVE__exit) || defined(__CRT_HAVE__Exit) || defined(__CRT_HAVE_xexit)
__NAMESPACE_LOCAL_END
#include <libc/local/obstack/obstack_printer.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_obstack_printer __LIBC_LOCAL_NAME(obstack_printer)
#else /* ... */
#undef __local___localdep_obstack_printer_defined
#endif /* !... */
#endif /* !__local___localdep_obstack_printer_defined */
__LOCAL_LIBC(obstack_vprintf) __ATTR_IN(2) __ATTR_INOUT(1) __ATTR_LIBC_PRINTF(2, 0) __STDC_INT_AS_SIZE_T
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(obstack_vprintf))(struct obstack *__restrict __self, char const *__restrict __format, __builtin_va_list __args) {
	return (__STDC_INT_AS_SIZE_T)(__NAMESPACE_LOCAL_SYM __localdep_format_vprintf)(&(__NAMESPACE_LOCAL_SYM __localdep_obstack_printer), __self, __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_obstack_vprintf_defined
#define __local___localdep_obstack_vprintf_defined
#define __localdep_obstack_vprintf __LIBC_LOCAL_NAME(obstack_vprintf)
#endif /* !__local___localdep_obstack_vprintf_defined */
#else /* __CRT_HAVE_obstack_printer || __CRT_HAVE__obstack_newchunk || __LOCAL_obstack_alloc_failed_handler || __CRT_HAVE_exit || __CRT_HAVE_quick_exit || __CRT_HAVE__exit || __CRT_HAVE__Exit || __CRT_HAVE_xexit */
#undef __local_obstack_vprintf_defined
#endif /* !__CRT_HAVE_obstack_printer && !__CRT_HAVE__obstack_newchunk && !__LOCAL_obstack_alloc_failed_handler && !__CRT_HAVE_exit && !__CRT_HAVE_quick_exit && !__CRT_HAVE__exit && !__CRT_HAVE__Exit && !__CRT_HAVE_xexit */
#endif /* !__local_obstack_vprintf_defined */
