/* HASH CRC-32:0xdee26e75 */
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
#ifndef __local_vdprintf_defined
#define __local_vdprintf_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#if defined(__CRT_HAVE_write_printer) || defined(__CRT_HAVE_writeall) || defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_format_vprintf_defined
#define __local___localdep_format_vprintf_defined
#ifdef __CRT_HAVE_format_vprintf
__CREDIRECT(__ATTR_IN(3) __ATTR_LIBC_PRINTF(3, 0) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_CB,__localdep_format_vprintf,(__pformatprinter __printer, void *__arg, char const *__restrict __format, __builtin_va_list __args),format_vprintf,(__printer,__arg,__format,__args))
#else /* __CRT_HAVE_format_vprintf */
__NAMESPACE_LOCAL_END
#include <libc/local/format-printer/format_vprintf.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_format_vprintf __LIBC_LOCAL_NAME(format_vprintf)
#endif /* !__CRT_HAVE_format_vprintf */
#endif /* !__local___localdep_format_vprintf_defined */
#ifndef __local___localdep_write_printer_defined
#define __local___localdep_write_printer_defined
#if defined(__CRT_HAVE_writeall) && defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__FORMATPRINTER_CC,__localdep_write_printer,(void *__fd, char const *__restrict __buf, __SIZE_TYPE__ __bufsize),writeall,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE_write_printer)
__COMPILER_CREDIRECT(__LIBC,__ATTR_INS(2, 3),__SSIZE_TYPE__,__NOTHROW_RPC,__FORMATPRINTER_CC,__localdep_write_printer,(void *__fd, char const *__restrict __buf, __SIZE_TYPE__ __bufsize),write_printer,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE_writeall) || defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/write_printer.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_write_printer __LIBC_LOCAL_NAME(write_printer)
#else /* ... */
#undef __local___localdep_write_printer_defined
#endif /* !... */
#endif /* !__local___localdep_write_printer_defined */
__NAMESPACE_LOCAL_END
#include <hybrid/host.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(vdprintf) __ATTR_IN(2) __ATTR_LIBC_PRINTF(2, 0) __STDC_INT_AS_SSIZE_T
__NOTHROW_RPC(__LIBCCALL __LIBC_LOCAL_NAME(vdprintf))(__fd_t __fd, char const *__restrict __format, __builtin_va_list __args) {
	return (__NAMESPACE_LOCAL_SYM __localdep_format_vprintf)(&(__NAMESPACE_LOCAL_SYM __localdep_write_printer),
	                      (void *)(__UINTPTR_TYPE__)(__CRT_PRIVATE_UINT(__SIZEOF_FD_T__))__fd,
	                      __format, __args);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_vdprintf_defined
#define __local___localdep_vdprintf_defined
#define __localdep_vdprintf __LIBC_LOCAL_NAME(vdprintf)
#endif /* !__local___localdep_vdprintf_defined */
#else /* __CRT_HAVE_write_printer || __CRT_HAVE_writeall || __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write */
#undef __local_vdprintf_defined
#endif /* !__CRT_HAVE_write_printer && !__CRT_HAVE_writeall && !__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write */
#endif /* !__local_vdprintf_defined */
