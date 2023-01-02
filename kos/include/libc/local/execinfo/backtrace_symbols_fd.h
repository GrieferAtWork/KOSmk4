/* HASH CRC-32:0x2417cd7d */
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
#ifndef __local_backtrace_symbols_fd_defined
#define __local_backtrace_symbols_fd_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#if defined(__CRT_HAVE_backtrace_symbols_fd_fmt) || defined(__CRT_HAVE___backtrace_symbols_fd) || ((defined(__CRT_HAVE_write_printer) || defined(__CRT_HAVE_writeall) || defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && defined(__CRT_HAVE_backtrace_symbol_printf))
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_backtrace_symbols_fd_fmt_defined
#define __local___localdep_backtrace_symbols_fd_fmt_defined
#ifdef __CRT_HAVE_backtrace_symbols_fd_fmt
__CREDIRECT(__ATTR_INS(1, 2) __ATTR_IN_OPT(4),int,__NOTHROW_NCX,__localdep_backtrace_symbols_fd_fmt,(void *const *__array, __STDC_INT_AS_SIZE_T __size, __fd_t __fd, char const *__format),backtrace_symbols_fd_fmt,(__array,__size,__fd,__format))
#elif defined(__CRT_HAVE___backtrace_symbols_fd)
__CREDIRECT(__ATTR_INS(1, 2) __ATTR_IN_OPT(4),int,__NOTHROW_NCX,__localdep_backtrace_symbols_fd_fmt,(void *const *__array, __STDC_INT_AS_SIZE_T __size, __fd_t __fd, char const *__format),__backtrace_symbols_fd,(__array,__size,__fd,__format))
#elif (defined(__CRT_HAVE_write_printer) || defined(__CRT_HAVE_writeall) || defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && defined(__CRT_HAVE_backtrace_symbol_printf)
__NAMESPACE_LOCAL_END
#include <libc/local/execinfo/backtrace_symbols_fd_fmt.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_backtrace_symbols_fd_fmt __LIBC_LOCAL_NAME(backtrace_symbols_fd_fmt)
#else /* ... */
#undef __local___localdep_backtrace_symbols_fd_fmt_defined
#endif /* !... */
#endif /* !__local___localdep_backtrace_symbols_fd_fmt_defined */
__LOCAL_LIBC(backtrace_symbols_fd) __ATTR_INS(1, 2) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(backtrace_symbols_fd))(void *const *__array, __STDC_INT_AS_SIZE_T __size, __fd_t __fd) {
	return (__NAMESPACE_LOCAL_SYM __localdep_backtrace_symbols_fd_fmt)(__array, __size, __fd, __NULLPTR);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_backtrace_symbols_fd_defined
#define __local___localdep_backtrace_symbols_fd_defined
#define __localdep_backtrace_symbols_fd __LIBC_LOCAL_NAME(backtrace_symbols_fd)
#endif /* !__local___localdep_backtrace_symbols_fd_defined */
#else /* __CRT_HAVE_backtrace_symbols_fd_fmt || __CRT_HAVE___backtrace_symbols_fd || ((__CRT_HAVE_write_printer || __CRT_HAVE_writeall || __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && __CRT_HAVE_backtrace_symbol_printf) */
#undef __local_backtrace_symbols_fd_defined
#endif /* !__CRT_HAVE_backtrace_symbols_fd_fmt && !__CRT_HAVE___backtrace_symbols_fd && ((!__CRT_HAVE_write_printer && !__CRT_HAVE_writeall && !__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write) || !__CRT_HAVE_backtrace_symbol_printf) */
#endif /* !__local_backtrace_symbols_fd_defined */
