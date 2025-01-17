/* HASH CRC-32:0xf54be681 */
/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local_WritePrinter_defined
#define __local_WritePrinter_defined
#include <__crt.h>
#include <hybrid/typecore.h>
#include <bits/crt/format-printer.h>
#if defined(__CRT_HAVE_WriteAll) || (defined(__CRT_HAVE_WritePrinter) && defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__) || defined(__CRT_HAVE_Write)
#include <kos/anno.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_WriteAll_defined
#define __local___localdep_WriteAll_defined
#ifdef __CRT_HAVE_WriteAll
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),__SIZE_TYPE__,__THROWING(...),__localdep_WriteAll,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),WriteAll,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE_WritePrinter) && defined(__LIBCCALL_IS_FORMATPRINTER_CC) && __SIZEOF_INT__ == __SIZEOF_POINTER__
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_FDWRITE(1) __ATTR_INS(2, 3),__SIZE_TYPE__,__THROWING(...),__localdep_WriteAll,(__fd_t __fd, void const *__buf, __SIZE_TYPE__ __bufsize),WritePrinter,(__fd,__buf,__bufsize))
#elif defined(__CRT_HAVE_Write)
__NAMESPACE_LOCAL_END
#include <libc/local/kos.unistd/WriteAll.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_WriteAll __LIBC_LOCAL_NAME(WriteAll)
#else /* ... */
#undef __local___localdep_WriteAll_defined
#endif /* !... */
#endif /* !__local___localdep_WriteAll_defined */
__NAMESPACE_LOCAL_END
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(WritePrinter) __ATTR_INS(2, 3) __SSIZE_TYPE__
(__FORMATPRINTER_CC __LIBC_LOCAL_NAME(WritePrinter))(void *__fd, char const *__restrict __buf, __SIZE_TYPE__ __bufsize) __THROWS(...) {
	return (__SSIZE_TYPE__)(__NAMESPACE_LOCAL_SYM __localdep_WriteAll)((__fd_t)(__CRT_PRIVATE_UINT(__SIZEOF_FD_T__))(__UINTPTR_TYPE__)__fd, __buf, __bufsize);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_WritePrinter_defined
#define __local___localdep_WritePrinter_defined
#define __localdep_WritePrinter __LIBC_LOCAL_NAME(WritePrinter)
#endif /* !__local___localdep_WritePrinter_defined */
#else /* __CRT_HAVE_WriteAll || (__CRT_HAVE_WritePrinter && __LIBCCALL_IS_FORMATPRINTER_CC && __SIZEOF_INT__ == __SIZEOF_POINTER__) || __CRT_HAVE_Write */
#undef __local_WritePrinter_defined
#endif /* !__CRT_HAVE_WriteAll && (!__CRT_HAVE_WritePrinter || !__LIBCCALL_IS_FORMATPRINTER_CC || __SIZEOF_INT__ != __SIZEOF_POINTER__) && !__CRT_HAVE_Write */
#endif /* !__local_WritePrinter_defined */
