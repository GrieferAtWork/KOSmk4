/* HASH CRC-32:0x30da35a3 */
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_vdprintf_defined
#define __local_vdprintf_defined 1
#include <__crt.h>
#if defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)
#include <features.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_format_vprintf_defined
#define __local___localdep_format_vprintf_defined 1
#ifdef __CRT_HAVE_format_vprintf
__NAMESPACE_LOCAL_END
#include <kos/anno.h>
#include <bits/crt/format-printer.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((1, 3)),__SSIZE_TYPE__,__THROWING,__localdep_format_vprintf,(__pformatprinter __printer, void *__arg, char const *__restrict __format, __builtin_va_list __args),format_vprintf,(__printer,__arg,__format,__args))
#else /* __CRT_HAVE_format_vprintf */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_vprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vprintf __LIBC_LOCAL_NAME(format_vprintf)
#endif /* !__CRT_HAVE_format_vprintf */
#endif /* !__local___localdep_format_vprintf_defined */
#ifndef __local___localdep_write_defined
#define __local___localdep_write_defined 1
#ifdef __CRT_HAVE_write
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE__write)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),_write,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE___write)
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_write,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),__write,(__fd,__buf,__bufsize))
#else /* ... */
#undef __local___localdep_write_defined
#endif /* !... */
#endif /* !__local___localdep_write_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/typecore.h>
#include <hybrid/host.h>
#include <bits/crt/format-printer.h>
#if !defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_INT__ != __SIZEOF_POINTER__
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vdprintf_printer) __ssize_t
(__FORMATPRINTER_CC __vdprintf_printer)(void *__arg, char const *__restrict __data, __size_t __datalen) {
	return (__ssize_t)(__NAMESPACE_LOCAL_SYM __localdep_write)((int)(unsigned int)(__UINTPTR_TYPE__)__arg, __data, __datalen);
}
__NAMESPACE_LOCAL_END
#endif /* !__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_INT__ != __SIZEOF_POINTER__ */
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vdprintf) __ATTR_LIBC_PRINTF(2, 0) __ATTR_NONNULL((2)) __STDC_INT_AS_SSIZE_T
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(vdprintf))(__fd_t __fd, char const *__restrict __format, __builtin_va_list __args) {
#if !defined(__LIBCCALL_IS_FORMATPRINTER_CC) || __SIZEOF_INT__ != __SIZEOF_POINTER__
	return __localdep_format_vprintf(&__NAMESPACE_LOCAL_SYM __vdprintf_printer,
	                      (void *)(__UINTPTR_TYPE__)(unsigned int)__fd,
	                      __format, __args);
#else /* !__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_INT__ != __SIZEOF_POINTER__ */
	return __localdep_format_vprintf((__pformatprinter)(void *)&__localdep_write,
	                      (void *)(__UINTPTR_TYPE__)(unsigned int)__fd,
	                      __format, __args);
#endif /* __LIBCCALL_IS_FORMATPRINTER_CC && __SIZEOF_INT__ == __SIZEOF_POINTER__ */
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vdprintf_defined
#define __local___localdep_vdprintf_defined 1
#define __localdep_vdprintf __LIBC_LOCAL_NAME(vdprintf)
#endif /* !__local___localdep_vdprintf_defined */
#else /* __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write */
#undef __local_vdprintf_defined
#endif /* !__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write */
#endif /* !__local_vdprintf_defined */
