/* HASH CRC-32:0xb1302fdf */
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
#ifndef __local_backtrace_symbols_fd_fmt_defined
#define __local_backtrace_symbols_fd_fmt_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#if (defined(__CRT_HAVE_write_printer) || defined(__CRT_HAVE_writeall) || defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write) || defined(__CRT_HAVE___libc_write)) && defined(__CRT_HAVE_backtrace_symbol_printf)
#include <features.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_backtrace_symbol_printf_defined
#define __local___localdep_backtrace_symbol_printf_defined
__CREDIRECT(__ATTR_IN_OPT(4) __ATTR_NONNULL((1)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_backtrace_symbol_printf,(__pformatprinter __printer, void *__arg, void const *__address, char const *__format),backtrace_symbol_printf,(__printer,__arg,__address,__format))
#endif /* !__local___localdep_backtrace_symbol_printf_defined */
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
__LOCAL_LIBC(backtrace_symbols_fd_fmt) __ATTR_FDWRITE(3) __ATTR_INS(1, 2) __ATTR_IN_OPT(4) int
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(backtrace_symbols_fd_fmt))(void *const *__array, __STDC_INT_AS_SIZE_T __size, __fd_t __fd, char const *__format) {
	__SIZE_TYPE__ __i;
	void *__fdarg;
	__fdarg = (void *)(__UINTPTR_TYPE__)(__CRT_PRIVATE_UINT(__SIZEOF_FD_T__))__fd;
	for (__i = 0; __i < (__SIZE_TYPE__)__size; ++__i) {
		if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_backtrace_symbol_printf)(&(__NAMESPACE_LOCAL_SYM __localdep_write_printer), __fdarg, __array[__i], __format) < 0)
			goto __err;
		if __unlikely((__NAMESPACE_LOCAL_SYM __localdep_write_printer)(__fdarg, "\n", 1) < 0)
			goto __err;
	}
	return 0;
__err:
	return -1;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_backtrace_symbols_fd_fmt_defined
#define __local___localdep_backtrace_symbols_fd_fmt_defined
#define __localdep_backtrace_symbols_fd_fmt __LIBC_LOCAL_NAME(backtrace_symbols_fd_fmt)
#endif /* !__local___localdep_backtrace_symbols_fd_fmt_defined */
#else /* (__CRT_HAVE_write_printer || __CRT_HAVE_writeall || __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write || __CRT_HAVE___libc_write) && __CRT_HAVE_backtrace_symbol_printf */
#undef __local_backtrace_symbols_fd_fmt_defined
#endif /* (!__CRT_HAVE_write_printer && !__CRT_HAVE_writeall && !__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write && !__CRT_HAVE___libc_write) || !__CRT_HAVE_backtrace_symbol_printf */
#endif /* !__local_backtrace_symbols_fd_fmt_defined */
