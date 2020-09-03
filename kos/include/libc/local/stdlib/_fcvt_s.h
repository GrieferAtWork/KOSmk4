/* HASH CRC-32:0x828583c1 */
/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef __local__fcvt_s_defined
#define __local__fcvt_s_defined 1
#include <__crt.h>
#include <bits/types.h>
__NAMESPACE_LOCAL_BEGIN
/* Dependency: fcvt_r from stdlib */
#ifndef __local___localdep_fcvt_r_defined
#define __local___localdep_fcvt_r_defined 1
#ifdef __CRT_HAVE_fcvt_r
__CREDIRECT(__ATTR_NONNULL((3, 4, 5)),int,__NOTHROW_NCX,__localdep_fcvt_r,(double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign, char *__restrict __buf, __SIZE_TYPE__ __len),fcvt_r,(__val,__ndigit,__decptr,__sign,__buf,__len))
#else /* __CRT_HAVE_fcvt_r */
__NAMESPACE_LOCAL_END
#include <libc/local/stdlib/fcvt_r.h>
__NAMESPACE_LOCAL_BEGIN
#define __localdep_fcvt_r __LIBC_LOCAL_NAME(fcvt_r)
#endif /* !__CRT_HAVE_fcvt_r */
#endif /* !__local___localdep_fcvt_r_defined */
__NAMESPACE_LOCAL_END
#include <libc/errno.h>
__NAMESPACE_LOCAL_BEGIN
__LOCAL_LIBC(_fcvt_s) __ATTR_NONNULL((1, 5, 6)) __errno_t
__NOTHROW_NCX(__LIBCCALL __LIBC_LOCAL_NAME(_fcvt_s))(char *__buf, __SIZE_TYPE__ __buflen, double __val, int __ndigit, int *__restrict __decptr, int *__restrict __sign) {
	if (!__buf || !__decptr || !__sign)
		return __EINVAL;
	__localdep_fcvt_r(__val, __ndigit, __decptr, __sign, __buf, __buflen);
	return 0;
}
__NAMESPACE_LOCAL_END
#ifndef __local___localdep__fcvt_s_defined
#define __local___localdep__fcvt_s_defined 1
#define __localdep__fcvt_s __LIBC_LOCAL_NAME(_fcvt_s)
#endif /* !__local___localdep__fcvt_s_defined */
#endif /* !__local__fcvt_s_defined */
