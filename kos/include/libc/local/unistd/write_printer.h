/* HASH CRC-32:0x8551f278 */
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
#ifndef __local_write_printer_defined
#define __local_write_printer_defined 1
#include <__crt.h>
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#if defined(__CRT_HAVE_writeall) || (defined(__CRT_HAVE_write_printer) && defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__) || defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_writeall_defined
#define __local___localdep_writeall_defined 1
#ifdef __CRT_HAVE_writeall
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_writeall,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),writeall,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE_write_printer) && defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_NONNULL((2)),__SSIZE_TYPE__,__NOTHROW_RPC,__localdep_writeall,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),write_printer,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE_write) || defined(__CRT_HAVE__write) || defined(__CRT_HAVE___write)
__NAMESPACE_LOCAL_END
#include <libc/local/unistd/writeall.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_writeall __LIBC_LOCAL_NAME(writeall)
#else /* ... */
#undef __local___localdep_writeall_defined
#endif /* !... */
#endif /* !__local___localdep_writeall_defined */
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(write_printer) __ATTR_NONNULL((2)) __SSIZE_TYPE__
__NOTHROW_RPC(__FORMATPRINTER_CC __LIBC_LOCAL_NAME(write_printer))(void *__fd, char const *__restrict __buf, __SIZE_TYPE__ __bufsize) {
	return __localdep_writeall((__fd_t)(__CRT_PRIVATE_UINT(__SIZEOF_FD_T__))(__UINTPTR_TYPE__)__fd, __buf, __bufsize);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_write_printer_defined
#define __local___localdep_write_printer_defined 1
#define __localdep_write_printer __LIBC_LOCAL_NAME(write_printer)
#endif /* !__local___localdep_write_printer_defined */
#else /* __CRT_HAVE_writeall || (__CRT_HAVE_write_printer && __LIBCCALL_IS_FORMATPRINTER_CC && __SIZEOF_INT__ == __SIZEOF_POINTER__) || __CRT_HAVE_write || __CRT_HAVE__write || __CRT_HAVE___write */
#undef __local_write_printer_defined
#endif /* !__CRT_HAVE_writeall && (!__CRT_HAVE_write_printer || !__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_INT__ != __SIZEOF_POINTER__) && !__CRT_HAVE_write && !__CRT_HAVE__write && !__CRT_HAVE___write */
#endif /* !__local_write_printer_defined */
