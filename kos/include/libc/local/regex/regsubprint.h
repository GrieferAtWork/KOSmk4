/* HASH CRC-32:0x44f3e */
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
#ifndef __local_regsubprint_defined
#define __local_regsubprint_defined
#include <__crt.h>
#include <bits/crt/format-printer.h>
#include <bits/crt/regex.h>
#include <hybrid/typecore.h>
__NAMESPACE_LOCAL_BEGIN
#ifndef __local___localdep_regsubprintv_defined
#define __local___localdep_regsubprintv_defined
#ifdef __CRT_HAVE_regsubprintv
__NAMESPACE_LOCAL_END
#include <bits/os/iovec.h>
__NAMESPACE_LOCAL_BEGIN
__CREDIRECT(__ATTR_IN(3) __ATTR_INS(6, 5) __ATTR_NONNULL((1, 4)),__SSIZE_TYPE__,__NOTHROW_NCX,__localdep_regsubprintv,(__pformatprinter __printer, void *__arg, char const *__sed_format, struct iovec const *__srcbase, __SIZE_TYPE__ __nmatch, struct __regmatch const __pmatch[__restrict_arr]),regsubprintv,(__printer,__arg,__sed_format,__srcbase,__nmatch,__pmatch))
#else /* __CRT_HAVE_regsubprintv */
__NAMESPACE_LOCAL_END
#include <libc/local/regex/regsubprintv.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_regsubprintv __LIBC_LOCAL_NAME(regsubprintv)
#endif /* !__CRT_HAVE_regsubprintv */
#endif /* !__local___localdep_regsubprintv_defined */
__NAMESPACE_LOCAL_END
#include <bits/os/iovec.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(regsubprint) __ATTR_IN(3) __ATTR_INS(6, 5) __ATTR_NONNULL((1, 4)) __SSIZE_TYPE__
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(regsubprint))(__pformatprinter __printer, void *__arg, char const *__sed_format, void const *__srcbase, __SIZE_TYPE__ __nmatch, struct __regmatch const __pmatch[__restrict_arr]) {
	struct iovec __iov[1];
	__iov[0].iov_base = (void *)__srcbase;
	__iov[0].iov_len  = (__SIZE_TYPE__)-1;
	return (__NAMESPACE_LOCAL_SYM __localdep_regsubprintv)(__printer, __arg, __sed_format, __iov, __nmatch, __pmatch);
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep_regsubprint_defined
#define __local___localdep_regsubprint_defined
#define __localdep_regsubprint __LIBC_LOCAL_NAME(regsubprint)
#endif /* !__local___localdep_regsubprint_defined */
#endif /* !__local_regsubprint_defined */
